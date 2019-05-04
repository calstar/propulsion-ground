using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO.Ports;

namespace PropLaptopTemp
{
    public partial class Form1 : Form
    {
        SerialPort port;
        string buffer = "";

        public Form1()
        {
            InitializeComponent();
        }

        bool linkValues = true;
        private void servoAUpDown_ValueChanged(object sender, EventArgs e)
        {
            if (linkValues)
            {
                linkValues = false;
                servoATrackBar.Value = (int)servoAUpDown.Value;
                linkValues = true;
            }
        }
        private void servoBUpDown_ValueChanged(object sender, EventArgs e)
        {
            if (linkValues)
            {
                linkValues = false;
                servoBTrackBar.Value = (int)servoBUpDown.Value;
                linkValues = true;
            }
        }

        private void servoCUpDown_ValueChanged(object sender, EventArgs e)
        {
            if (linkValues)
            {
                linkValues = false;
                servoCTrackBar.Value = (int)servoCUpDown.Value;
                linkValues = true;
            }
        }

        private void servoATrackBar_Scroll(object sender, EventArgs e)
        {
            if (linkValues)
            {
                linkValues = false;
                servoAUpDown.Value = servoATrackBar.Value;
                linkValues = true;
            }
        }

        private void servoBTrackBar_Scroll(object sender, EventArgs e)
        {
            if (linkValues)
            {
                linkValues = false;
                servoBUpDown.Value = servoBTrackBar.Value;
                linkValues = true;
            }
        }

        private void servoCTrackBar_Scroll(object sender, EventArgs e)
        {
            if (linkValues)
            {
                linkValues = false;
                servoCUpDown.Value = servoCTrackBar.Value;
                linkValues = true;
            }
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            COMPortDialog dialog = new COMPortDialog();
            if (dialog.ShowDialog() != DialogResult.OK)
            {
                Application.Exit();
            }

            string portName = dialog.COMPort;
            this.Text += " - " + portName;

            this.port = new SerialPort(portName, 9600);
            this.port.DtrEnable = true;
            this.port.DataReceived += (s, ev) => receiveSerialData();
            this.port.Open();
            this.port.Write("![NO_RETRY]!\n");
        }

        void receiveSerialData()
        {
            buffer += port.ReadExisting();
            if (buffer.Contains("\n"))
            {
                int eolIndex = buffer.IndexOf("\n");
                string line = buffer.Substring(0, eolIndex).Trim();
                buffer = buffer.Substring(eolIndex + 1);

                // Seems like there's no easy JSON library in .NET, so we'll just do our own for now
                JSONObject obj = JSONObject.fromString(line);
                if (obj != null && obj.type == JSONObject.Type.Object)
                {
                    if (obj.children.Keys.Contains("flowSwitch"))
                    {
                        JSONObject fsObj = obj.children["flowSwitch"];
                        if (fsObj.type == JSONObject.Type.Bool)
                        {
                            invoke(flowSwitchLabel, () =>
                            {
                                flowSwitchLabel.BackColor = fsObj.boolValue ? Color.Green : Color.Red;
                            });
                        }
                    }
                    if (obj.children.Keys.Contains("igniting"))
                    {
                        JSONObject ignObj = obj.children["igniting"];
                        if (ignObj.type == JSONObject.Type.Bool)
                        {
                            invoke(ignitionLabel, () =>
                            {
                                if (ignObj.boolValue)
                                {
                                    ignitionLabel.BackColor = Color.Green;
                                    ignitionLabel.Text = "Igniting!";
                                }
                                else
                                {
                                    ignitionLabel.BackColor = Color.Yellow;
                                    ignitionLabel.Text = "Ignition Ready";
                                }
                            });
                        }
                    }
                    if (obj.children.Keys.Contains("servos"))
                    {
                        JSONObject servosObj = obj.children["servos"];
                        if (servosObj.type == JSONObject.Type.Array)
                        {
                            if (servosObj.items.Length == 3 && servosObj.items.All(s => s.type == JSONObject.Type.Int))
                            {
                                linkValues = false;
                                try { servoAUpDown.Value = servoATrackBar.Value = servosObj.items[0].intValue; } catch (Exception _) { }
                                try { servoBUpDown.Value = servoBTrackBar.Value = servosObj.items[1].intValue; } catch (Exception _) { }
                                try { servoCUpDown.Value = servoCTrackBar.Value = servosObj.items[2].intValue; } catch (Exception _) { }
                                linkValues = true;
                                invoke(statusTextBox, () => {
                                    statusTextBox.AppendText("Servos updated to " + servosObj.items[0].intValue + "," + servosObj.items[1].intValue + "," + servosObj.items[2].intValue + "\r\n");
                                });
                            }
                        }
                    }
                    else if (obj.children.Keys.Contains("status"))
                    {
                        JSONObject statusObj = obj.children["status"];
                        if (statusObj.type == JSONObject.Type.String)
                        {
                            invoke(statusTextBox, () => {
                                statusTextBox.AppendText(statusObj.strValue + "\r\n");
                            });
                        }
                    }
                }
            }
        }

        void invoke(Control ctrl, Action action)
        {
            if (ctrl.InvokeRequired) ctrl.BeginInvoke(action);
            else action();
        }

        private void updateServosButton_Click(object sender, EventArgs e)
        {
            port.Write("a" + servoAUpDown.Value.ToString().PadLeft(3, '0') +
                       "b" + servoBUpDown.Value.ToString().PadLeft(3, '0') +
                       "c" + servoCUpDown.Value.ToString().PadLeft(3, '0') + "\n");
        }

        private void igniteButton_Click(object sender, EventArgs e)
        {
            port.Write("ignite\n");
        }

        private void turnOffButton_Click(object sender, EventArgs e)
        {
            port.Write("off\n");
        }
    }

    class JSONObject
    {
        public enum Type { Object, Array, String, Int, Bool }
        
        public Type type;
        public Dictionary<string, JSONObject> children;
        public JSONObject[] items;
        public string strValue;
        public int intValue;
        public bool boolValue;

        public static JSONObject fromString(string str)
        {
            // Note: this doesn't actually work LMAO
            // But it works for what we need
            // Trees of objects do not work
            str = str.Trim();
            if (str.StartsWith("{"))
            {
                // object
                if (!str.EndsWith("}")) return null;
                str = str.Substring(1, str.Length - 2);
                string[] parts = str.Split(',');
                Dictionary<string, JSONObject> dict = new Dictionary<string, JSONObject>();
                foreach (string part in parts)
                {
                    if (!part.Contains(":")) return null;
                    string[] kvpParts = part.Split(':');
                    if (kvpParts.Length != 2) return null;
                    string key = kvpParts[0], value = kvpParts[1];
                    if (!key.StartsWith("\"") || !key.EndsWith("\"")) return null;
                    key = key.Substring(1, key.Length - 2);
                    if (value != "null")
                    {
                        JSONObject obj = fromString(value);
                        if (obj == null) return null;
                        dict.Add(key, obj);
                    }
                }
                return new JSONObject()
                {
                    type = Type.Object,
                    children = dict
                };
            }
            else if (str.StartsWith("["))
            {
                // array
                if (!str.EndsWith("]")) return null;
                str = str.Substring(1, str.Length - 2);
                string[] parts = str.Split(';');
                JSONObject[] objs = (from p in parts select fromString(p)).ToArray();
                if (objs.Contains(null)) return null;
                return new JSONObject()
                {
                    type = Type.Array,
                    items = objs
                };
            }
            else if (str.StartsWith("\""))
            {
                // string
                if (!str.EndsWith("\"")) return null;
                str = str.Substring(1, str.Length - 2);
                return new JSONObject()
                {
                    type = Type.String,
                    strValue = str
                };
            }
            else
            {
                if (int.TryParse(str, out int intValue))
                {
                    return new JSONObject()
                    {
                        type = Type.Int,
                        intValue = intValue
                    };
                }
                else if (bool.TryParse(str, out bool boolValue))
                {
                    return new JSONObject()
                    {
                        type = Type.Bool,
                        boolValue = boolValue
                    };
                }
            }
            return null;
        }
    }
}
