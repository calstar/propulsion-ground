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
    public partial class COMPortDialog : Form
    {
        public string COMPort = null;

        public COMPortDialog()
        {
            InitializeComponent();
        }

        void loadPorts()
        {
            selectButton.Enabled = false;
            portsComboBox.Items.Clear();
            portsComboBox.Items.AddRange(SerialPort.GetPortNames());
            if (portsComboBox.Items.Count > 0)
            {
                portsComboBox.SelectedIndex = 0;
                selectButton.Enabled = true;
                selectButton.Select();
            }
        }

        private void COMPortDialog_Load(object sender, EventArgs e)
        {
            loadPorts();
        }

        private void refreshButton_Click(object sender, EventArgs e)
        {
            loadPorts();
        }

        private void selectButton_Click(object sender, EventArgs e)
        {
            this.COMPort = (string)portsComboBox.SelectedItem;
        }
    }
}
