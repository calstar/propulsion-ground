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
using System.Web.Script.Serialization;

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
                return;
            }

            string portName = dialog.COMPort;
            this.Text += " - " + portName;

            this.port = new SerialPort(portName, 9600);
            this.port.DtrEnable = true;
            this.port.DataReceived += (s, ev) => receiveSerialData();
            try
            {
                this.port.Open();
            }
            catch (Exception error)
            {
                MessageBox.Show(error.Message, "Error: Could not open " + portName, MessageBoxButtons.OK, MessageBoxIcon.Error);
                Application.Exit();
                return;
            }
            
            this.port.Write("![NO_RETRY]!\n");
        }

        DateTime lastReceivedTime;
        void receiveSerialData()
        {
            buffer += port.ReadExisting();
            if (buffer.Contains("\n"))
            {
                int eolIndex = buffer.IndexOf("\n");
                string line = buffer.Substring(0, eolIndex).Trim();
                buffer = buffer.Substring(eolIndex + 1);

                try
                {
                    Dictionary<string, object> obj = (Dictionary<string, object>)new JavaScriptSerializer().DeserializeObject(line);
                    if (obj.Keys.Contains("status"))
                    {
                        string status = (string)obj["status"];
                        statusTextBox.TryInvoke(() => statusTextBox.AppendText(status + "\r\n"));
                    }
                    else if (obj.Keys.Contains("update"))
                    {
                        Dictionary<string, object> update = (Dictionary<string, object>)obj["update"];
                        bool fs = (bool)update["flowSwitch"];
                        bool igniting = (bool)update["igniting"];
                        int[] servos = (from s in (object[])update["servos"] select (int)s).ToArray();
                        flowSwitchLabel.TryInvoke(() => flowSwitchLabel.BackColor = fs ? Color.Green : Color.Red);
                        ignitionLabel.TryInvoke(() =>
                        {
                            if (igniting)
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
                        linkValues = false;
                        servoAUpDownReadout.TryInvoke(() => servoAUpDownReadout.Value = servos[0]);
                        servoBUpDownReadout.TryInvoke(() => servoBUpDownReadout.Value = servos[1]);
                        servoCUpDownReadout.TryInvoke(() => servoCUpDownReadout.Value = servos[2]);
                        servoATrackBarReadout.TryInvoke(() => servoATrackBarReadout.Value = servos[0]);
                        servoBTrackBarReadout.TryInvoke(() => servoBTrackBarReadout.Value = servos[1]);
                        servoCTrackBarReadout.TryInvoke(() => servoCTrackBarReadout.Value = servos[2]);
                        linkValues = true;
                    }


                }
                catch (Exception e)
                {
                    statusTextBox.TryInvoke(() => {
                        statusTextBox.AppendText("Error: Could not parse \"" + line + "\": " + e.Message + "\r\n");
                    });
                }
            }
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

    /*class JSONObject
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
    }*/
    static class Util
    {
        public static void TryInvoke(this Control ctrl, Action action)
        {
            if (ctrl.InvokeRequired) ctrl.BeginInvoke(action);
            else action();
        }
    }
}
