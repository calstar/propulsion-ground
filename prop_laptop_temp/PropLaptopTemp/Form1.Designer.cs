namespace PropLaptopTemp
{
    partial class Form1
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.servoAUpDown = new System.Windows.Forms.NumericUpDown();
            this.servoBUpDown = new System.Windows.Forms.NumericUpDown();
            this.servoCUpDown = new System.Windows.Forms.NumericUpDown();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.servoATrackBar = new System.Windows.Forms.TrackBar();
            this.servoBTrackBar = new System.Windows.Forms.TrackBar();
            this.servoCTrackBar = new System.Windows.Forms.TrackBar();
            this.updateServosButton = new System.Windows.Forms.Button();
            this.ignitionLabel = new System.Windows.Forms.Label();
            this.receivingDataLabel = new System.Windows.Forms.Label();
            this.flowSwitchLabel = new System.Windows.Forms.Label();
            this.statusTextBox = new System.Windows.Forms.TextBox();
            this.label4 = new System.Windows.Forms.Label();
            this.igniteButton = new System.Windows.Forms.Button();
            this.turnOffButton = new System.Windows.Forms.Button();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.label5 = new System.Windows.Forms.Label();
            this.servoAUpDownReadout = new System.Windows.Forms.NumericUpDown();
            this.servoBUpDownReadout = new System.Windows.Forms.NumericUpDown();
            this.servoCUpDownReadout = new System.Windows.Forms.NumericUpDown();
            this.label6 = new System.Windows.Forms.Label();
            this.label7 = new System.Windows.Forms.Label();
            this.servoATrackBarReadout = new System.Windows.Forms.TrackBar();
            this.servoBTrackBarReadout = new System.Windows.Forms.TrackBar();
            this.servoCTrackBarReadout = new System.Windows.Forms.TrackBar();
            this.thermocouple1Label = new System.Windows.Forms.Label();
            this.thermocouple2Label = new System.Windows.Forms.Label();
            this.thermocouple3Label = new System.Windows.Forms.Label();
            this.pressureTransducerLabel = new System.Windows.Forms.Label();
            this.loadCellLabel = new System.Windows.Forms.Label();
            ((System.ComponentModel.ISupportInitialize)(this.servoAUpDown)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.servoBUpDown)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.servoCUpDown)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.servoATrackBar)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.servoBTrackBar)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.servoCTrackBar)).BeginInit();
            this.groupBox1.SuspendLayout();
            this.groupBox2.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.servoAUpDownReadout)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.servoBUpDownReadout)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.servoCUpDownReadout)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.servoATrackBarReadout)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.servoBTrackBarReadout)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.servoCTrackBarReadout)).BeginInit();
            this.SuspendLayout();
            // 
            // servoAUpDown
            // 
            this.servoAUpDown.Location = new System.Drawing.Point(74, 22);
            this.servoAUpDown.Maximum = new decimal(new int[] {
            180,
            0,
            0,
            0});
            this.servoAUpDown.Name = "servoAUpDown";
            this.servoAUpDown.Size = new System.Drawing.Size(71, 22);
            this.servoAUpDown.TabIndex = 0;
            this.servoAUpDown.ValueChanged += new System.EventHandler(this.servoAUpDown_ValueChanged);
            // 
            // servoBUpDown
            // 
            this.servoBUpDown.Location = new System.Drawing.Point(74, 50);
            this.servoBUpDown.Maximum = new decimal(new int[] {
            180,
            0,
            0,
            0});
            this.servoBUpDown.Name = "servoBUpDown";
            this.servoBUpDown.Size = new System.Drawing.Size(71, 22);
            this.servoBUpDown.TabIndex = 1;
            this.servoBUpDown.ValueChanged += new System.EventHandler(this.servoBUpDown_ValueChanged);
            // 
            // servoCUpDown
            // 
            this.servoCUpDown.Location = new System.Drawing.Point(74, 78);
            this.servoCUpDown.Maximum = new decimal(new int[] {
            180,
            0,
            0,
            0});
            this.servoCUpDown.Name = "servoCUpDown";
            this.servoCUpDown.Size = new System.Drawing.Size(71, 22);
            this.servoCUpDown.TabIndex = 2;
            this.servoCUpDown.ValueChanged += new System.EventHandler(this.servoCUpDown_ValueChanged);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(6, 24);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(62, 17);
            this.label1.TabIndex = 3;
            this.label1.Text = "Servo A:";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(6, 52);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(62, 17);
            this.label2.TabIndex = 4;
            this.label2.Text = "Servo B:";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(6, 80);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(62, 17);
            this.label3.TabIndex = 5;
            this.label3.Text = "Servo C:";
            // 
            // servoATrackBar
            // 
            this.servoATrackBar.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.servoATrackBar.AutoSize = false;
            this.servoATrackBar.Location = new System.Drawing.Point(151, 22);
            this.servoATrackBar.Maximum = 180;
            this.servoATrackBar.Name = "servoATrackBar";
            this.servoATrackBar.Size = new System.Drawing.Size(944, 22);
            this.servoATrackBar.TabIndex = 6;
            this.servoATrackBar.Scroll += new System.EventHandler(this.servoATrackBar_Scroll);
            // 
            // servoBTrackBar
            // 
            this.servoBTrackBar.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.servoBTrackBar.AutoSize = false;
            this.servoBTrackBar.Location = new System.Drawing.Point(151, 50);
            this.servoBTrackBar.Maximum = 180;
            this.servoBTrackBar.Name = "servoBTrackBar";
            this.servoBTrackBar.Size = new System.Drawing.Size(944, 22);
            this.servoBTrackBar.TabIndex = 7;
            this.servoBTrackBar.Scroll += new System.EventHandler(this.servoBTrackBar_Scroll);
            // 
            // servoCTrackBar
            // 
            this.servoCTrackBar.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.servoCTrackBar.AutoSize = false;
            this.servoCTrackBar.Location = new System.Drawing.Point(151, 78);
            this.servoCTrackBar.Maximum = 180;
            this.servoCTrackBar.Name = "servoCTrackBar";
            this.servoCTrackBar.Size = new System.Drawing.Size(944, 22);
            this.servoCTrackBar.TabIndex = 8;
            this.servoCTrackBar.Scroll += new System.EventHandler(this.servoCTrackBar_Scroll);
            // 
            // updateServosButton
            // 
            this.updateServosButton.Location = new System.Drawing.Point(9, 106);
            this.updateServosButton.Name = "updateServosButton";
            this.updateServosButton.Size = new System.Drawing.Size(136, 32);
            this.updateServosButton.TabIndex = 9;
            this.updateServosButton.Text = "Update Servos";
            this.updateServosButton.UseVisualStyleBackColor = true;
            this.updateServosButton.Click += new System.EventHandler(this.updateServosButton_Click);
            // 
            // ignitionLabel
            // 
            this.ignitionLabel.BackColor = System.Drawing.Color.Yellow;
            this.ignitionLabel.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.ignitionLabel.Location = new System.Drawing.Point(217, 9);
            this.ignitionLabel.Name = "ignitionLabel";
            this.ignitionLabel.Size = new System.Drawing.Size(188, 34);
            this.ignitionLabel.TabIndex = 10;
            this.ignitionLabel.Text = "Ignition Ready";
            this.ignitionLabel.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // receivingDataLabel
            // 
            this.receivingDataLabel.BackColor = System.Drawing.Color.Red;
            this.receivingDataLabel.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.receivingDataLabel.Location = new System.Drawing.Point(12, 9);
            this.receivingDataLabel.Name = "receivingDataLabel";
            this.receivingDataLabel.Size = new System.Drawing.Size(170, 65);
            this.receivingDataLabel.TabIndex = 12;
            this.receivingDataLabel.Text = "Receiving Data\r\n(Last 2 Seconds)";
            this.receivingDataLabel.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // flowSwitchLabel
            // 
            this.flowSwitchLabel.BackColor = System.Drawing.Color.Red;
            this.flowSwitchLabel.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.flowSwitchLabel.Location = new System.Drawing.Point(445, 9);
            this.flowSwitchLabel.Name = "flowSwitchLabel";
            this.flowSwitchLabel.Size = new System.Drawing.Size(188, 65);
            this.flowSwitchLabel.TabIndex = 13;
            this.flowSwitchLabel.Text = "Flow Switch";
            this.flowSwitchLabel.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // statusTextBox
            // 
            this.statusTextBox.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.statusTextBox.Location = new System.Drawing.Point(12, 449);
            this.statusTextBox.Multiline = true;
            this.statusTextBox.Name = "statusTextBox";
            this.statusTextBox.ReadOnly = true;
            this.statusTextBox.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
            this.statusTextBox.Size = new System.Drawing.Size(1101, 203);
            this.statusTextBox.TabIndex = 14;
            // 
            // label4
            // 
            this.label4.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(12, 429);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(90, 17);
            this.label4.TabIndex = 15;
            this.label4.Text = "Status Texts:";
            // 
            // igniteButton
            // 
            this.igniteButton.Location = new System.Drawing.Point(308, 46);
            this.igniteButton.Name = "igniteButton";
            this.igniteButton.Size = new System.Drawing.Size(97, 28);
            this.igniteButton.TabIndex = 16;
            this.igniteButton.Text = "Ignite!";
            this.igniteButton.UseVisualStyleBackColor = true;
            this.igniteButton.Click += new System.EventHandler(this.igniteButton_Click);
            // 
            // turnOffButton
            // 
            this.turnOffButton.Location = new System.Drawing.Point(217, 46);
            this.turnOffButton.Name = "turnOffButton";
            this.turnOffButton.Size = new System.Drawing.Size(85, 28);
            this.turnOffButton.TabIndex = 17;
            this.turnOffButton.Text = "Turn Off";
            this.turnOffButton.UseVisualStyleBackColor = true;
            this.turnOffButton.Click += new System.EventHandler(this.turnOffButton_Click);
            // 
            // groupBox1
            // 
            this.groupBox1.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.groupBox1.Controls.Add(this.label1);
            this.groupBox1.Controls.Add(this.servoAUpDown);
            this.groupBox1.Controls.Add(this.servoBUpDown);
            this.groupBox1.Controls.Add(this.servoCUpDown);
            this.groupBox1.Controls.Add(this.label2);
            this.groupBox1.Controls.Add(this.label3);
            this.groupBox1.Controls.Add(this.servoATrackBar);
            this.groupBox1.Controls.Add(this.servoBTrackBar);
            this.groupBox1.Controls.Add(this.updateServosButton);
            this.groupBox1.Controls.Add(this.servoCTrackBar);
            this.groupBox1.Location = new System.Drawing.Point(12, 151);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(1101, 151);
            this.groupBox1.TabIndex = 18;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Servo Uplink";
            // 
            // groupBox2
            // 
            this.groupBox2.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.groupBox2.Controls.Add(this.label5);
            this.groupBox2.Controls.Add(this.servoAUpDownReadout);
            this.groupBox2.Controls.Add(this.servoBUpDownReadout);
            this.groupBox2.Controls.Add(this.servoCUpDownReadout);
            this.groupBox2.Controls.Add(this.label6);
            this.groupBox2.Controls.Add(this.label7);
            this.groupBox2.Controls.Add(this.servoATrackBarReadout);
            this.groupBox2.Controls.Add(this.servoBTrackBarReadout);
            this.groupBox2.Controls.Add(this.servoCTrackBarReadout);
            this.groupBox2.Location = new System.Drawing.Point(12, 308);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(1101, 113);
            this.groupBox2.TabIndex = 19;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "Servo Downlink";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(6, 24);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(62, 17);
            this.label5.TabIndex = 3;
            this.label5.Text = "Servo A:";
            // 
            // servoAUpDownReadout
            // 
            this.servoAUpDownReadout.Enabled = false;
            this.servoAUpDownReadout.Location = new System.Drawing.Point(74, 22);
            this.servoAUpDownReadout.Maximum = new decimal(new int[] {
            180,
            0,
            0,
            0});
            this.servoAUpDownReadout.Name = "servoAUpDownReadout";
            this.servoAUpDownReadout.ReadOnly = true;
            this.servoAUpDownReadout.Size = new System.Drawing.Size(71, 22);
            this.servoAUpDownReadout.TabIndex = 0;
            // 
            // servoBUpDownReadout
            // 
            this.servoBUpDownReadout.Enabled = false;
            this.servoBUpDownReadout.Location = new System.Drawing.Point(74, 50);
            this.servoBUpDownReadout.Maximum = new decimal(new int[] {
            180,
            0,
            0,
            0});
            this.servoBUpDownReadout.Name = "servoBUpDownReadout";
            this.servoBUpDownReadout.ReadOnly = true;
            this.servoBUpDownReadout.Size = new System.Drawing.Size(71, 22);
            this.servoBUpDownReadout.TabIndex = 1;
            // 
            // servoCUpDownReadout
            // 
            this.servoCUpDownReadout.Enabled = false;
            this.servoCUpDownReadout.Location = new System.Drawing.Point(74, 78);
            this.servoCUpDownReadout.Maximum = new decimal(new int[] {
            180,
            0,
            0,
            0});
            this.servoCUpDownReadout.Name = "servoCUpDownReadout";
            this.servoCUpDownReadout.ReadOnly = true;
            this.servoCUpDownReadout.Size = new System.Drawing.Size(71, 22);
            this.servoCUpDownReadout.TabIndex = 2;
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(6, 52);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(62, 17);
            this.label6.TabIndex = 4;
            this.label6.Text = "Servo B:";
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(6, 80);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(62, 17);
            this.label7.TabIndex = 5;
            this.label7.Text = "Servo C:";
            // 
            // servoATrackBarReadout
            // 
            this.servoATrackBarReadout.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.servoATrackBarReadout.AutoSize = false;
            this.servoATrackBarReadout.Enabled = false;
            this.servoATrackBarReadout.Location = new System.Drawing.Point(151, 22);
            this.servoATrackBarReadout.Maximum = 180;
            this.servoATrackBarReadout.Name = "servoATrackBarReadout";
            this.servoATrackBarReadout.Size = new System.Drawing.Size(944, 22);
            this.servoATrackBarReadout.TabIndex = 6;
            // 
            // servoBTrackBarReadout
            // 
            this.servoBTrackBarReadout.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.servoBTrackBarReadout.AutoSize = false;
            this.servoBTrackBarReadout.Enabled = false;
            this.servoBTrackBarReadout.Location = new System.Drawing.Point(151, 50);
            this.servoBTrackBarReadout.Maximum = 180;
            this.servoBTrackBarReadout.Name = "servoBTrackBarReadout";
            this.servoBTrackBarReadout.Size = new System.Drawing.Size(944, 22);
            this.servoBTrackBarReadout.TabIndex = 7;
            // 
            // servoCTrackBarReadout
            // 
            this.servoCTrackBarReadout.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.servoCTrackBarReadout.AutoSize = false;
            this.servoCTrackBarReadout.Enabled = false;
            this.servoCTrackBarReadout.Location = new System.Drawing.Point(151, 78);
            this.servoCTrackBarReadout.Maximum = 180;
            this.servoCTrackBarReadout.Name = "servoCTrackBarReadout";
            this.servoCTrackBarReadout.Size = new System.Drawing.Size(944, 22);
            this.servoCTrackBarReadout.TabIndex = 8;
            // 
            // thermocouple1Label
            // 
            this.thermocouple1Label.BackColor = System.Drawing.SystemColors.Control;
            this.thermocouple1Label.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.thermocouple1Label.Location = new System.Drawing.Point(650, 9);
            this.thermocouple1Label.Name = "thermocouple1Label";
            this.thermocouple1Label.Size = new System.Drawing.Size(147, 65);
            this.thermocouple1Label.TabIndex = 20;
            this.thermocouple1Label.Text = "Thermocouple 1:\r\n739°C";
            this.thermocouple1Label.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // thermocouple2Label
            // 
            this.thermocouple2Label.BackColor = System.Drawing.SystemColors.Control;
            this.thermocouple2Label.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.thermocouple2Label.Location = new System.Drawing.Point(803, 9);
            this.thermocouple2Label.Name = "thermocouple2Label";
            this.thermocouple2Label.Size = new System.Drawing.Size(147, 65);
            this.thermocouple2Label.TabIndex = 21;
            this.thermocouple2Label.Text = "Thermocouple 2:\r\n739°C";
            this.thermocouple2Label.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // thermocouple3Label
            // 
            this.thermocouple3Label.BackColor = System.Drawing.SystemColors.Control;
            this.thermocouple3Label.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.thermocouple3Label.Location = new System.Drawing.Point(956, 9);
            this.thermocouple3Label.Name = "thermocouple3Label";
            this.thermocouple3Label.Size = new System.Drawing.Size(147, 65);
            this.thermocouple3Label.TabIndex = 22;
            this.thermocouple3Label.Text = "Thermocouple 3:\r\n739°C";
            this.thermocouple3Label.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // pressureTransducerLabel
            // 
            this.pressureTransducerLabel.BackColor = System.Drawing.SystemColors.Control;
            this.pressureTransducerLabel.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.pressureTransducerLabel.Location = new System.Drawing.Point(803, 83);
            this.pressureTransducerLabel.Name = "pressureTransducerLabel";
            this.pressureTransducerLabel.Size = new System.Drawing.Size(203, 65);
            this.pressureTransducerLabel.TabIndex = 24;
            this.pressureTransducerLabel.Text = "Pressure Transducer:\r\n0 PSI";
            this.pressureTransducerLabel.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // loadCellLabel
            // 
            this.loadCellLabel.BackColor = System.Drawing.SystemColors.Control;
            this.loadCellLabel.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.loadCellLabel.Location = new System.Drawing.Point(650, 83);
            this.loadCellLabel.Name = "loadCellLabel";
            this.loadCellLabel.Size = new System.Drawing.Size(147, 65);
            this.loadCellLabel.TabIndex = 23;
            this.loadCellLabel.Text = "Load Cell:\r\n0 lbs";
            this.loadCellLabel.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1125, 664);
            this.Controls.Add(this.pressureTransducerLabel);
            this.Controls.Add(this.loadCellLabel);
            this.Controls.Add(this.thermocouple3Label);
            this.Controls.Add(this.thermocouple2Label);
            this.Controls.Add(this.thermocouple1Label);
            this.Controls.Add(this.groupBox2);
            this.Controls.Add(this.groupBox1);
            this.Controls.Add(this.turnOffButton);
            this.Controls.Add(this.igniteButton);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.statusTextBox);
            this.Controls.Add(this.flowSwitchLabel);
            this.Controls.Add(this.receivingDataLabel);
            this.Controls.Add(this.ignitionLabel);
            this.Name = "Form1";
            this.Text = "Propulsion Ground Test (Temp)";
            this.Load += new System.EventHandler(this.Form1_Load);
            ((System.ComponentModel.ISupportInitialize)(this.servoAUpDown)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.servoBUpDown)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.servoCUpDown)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.servoATrackBar)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.servoBTrackBar)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.servoCTrackBar)).EndInit();
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.groupBox2.ResumeLayout(false);
            this.groupBox2.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.servoAUpDownReadout)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.servoBUpDownReadout)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.servoCUpDownReadout)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.servoATrackBarReadout)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.servoBTrackBarReadout)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.servoCTrackBarReadout)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.NumericUpDown servoAUpDown;
        private System.Windows.Forms.NumericUpDown servoBUpDown;
        private System.Windows.Forms.NumericUpDown servoCUpDown;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.TrackBar servoATrackBar;
        private System.Windows.Forms.TrackBar servoBTrackBar;
        private System.Windows.Forms.TrackBar servoCTrackBar;
        private System.Windows.Forms.Button updateServosButton;
        private System.Windows.Forms.Label ignitionLabel;
        private System.Windows.Forms.Label receivingDataLabel;
        private System.Windows.Forms.Label flowSwitchLabel;
        private System.Windows.Forms.TextBox statusTextBox;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Button igniteButton;
        private System.Windows.Forms.Button turnOffButton;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.NumericUpDown servoAUpDownReadout;
        private System.Windows.Forms.NumericUpDown servoBUpDownReadout;
        private System.Windows.Forms.NumericUpDown servoCUpDownReadout;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.TrackBar servoATrackBarReadout;
        private System.Windows.Forms.TrackBar servoBTrackBarReadout;
        private System.Windows.Forms.TrackBar servoCTrackBarReadout;
        private System.Windows.Forms.Label thermocouple1Label;
        private System.Windows.Forms.Label thermocouple2Label;
        private System.Windows.Forms.Label thermocouple3Label;
        private System.Windows.Forms.Label pressureTransducerLabel;
        private System.Windows.Forms.Label loadCellLabel;
    }
}

