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
            ((System.ComponentModel.ISupportInitialize)(this.servoAUpDown)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.servoBUpDown)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.servoCUpDown)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.servoATrackBar)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.servoBTrackBar)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.servoCTrackBar)).BeginInit();
            this.SuspendLayout();
            // 
            // servoAUpDown
            // 
            this.servoAUpDown.Location = new System.Drawing.Point(82, 92);
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
            this.servoBUpDown.Location = new System.Drawing.Point(82, 120);
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
            this.servoCUpDown.Location = new System.Drawing.Point(82, 148);
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
            this.label1.Location = new System.Drawing.Point(14, 94);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(62, 17);
            this.label1.TabIndex = 3;
            this.label1.Text = "Servo A:";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(14, 122);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(62, 17);
            this.label2.TabIndex = 4;
            this.label2.Text = "Servo B:";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(14, 150);
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
            this.servoATrackBar.Location = new System.Drawing.Point(159, 92);
            this.servoATrackBar.Maximum = 180;
            this.servoATrackBar.Name = "servoATrackBar";
            this.servoATrackBar.Size = new System.Drawing.Size(629, 22);
            this.servoATrackBar.TabIndex = 6;
            this.servoATrackBar.Scroll += new System.EventHandler(this.servoATrackBar_Scroll);
            // 
            // servoBTrackBar
            // 
            this.servoBTrackBar.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.servoBTrackBar.AutoSize = false;
            this.servoBTrackBar.Location = new System.Drawing.Point(159, 120);
            this.servoBTrackBar.Maximum = 180;
            this.servoBTrackBar.Name = "servoBTrackBar";
            this.servoBTrackBar.Size = new System.Drawing.Size(629, 22);
            this.servoBTrackBar.TabIndex = 7;
            this.servoBTrackBar.Scroll += new System.EventHandler(this.servoBTrackBar_Scroll);
            // 
            // servoCTrackBar
            // 
            this.servoCTrackBar.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.servoCTrackBar.AutoSize = false;
            this.servoCTrackBar.Location = new System.Drawing.Point(159, 148);
            this.servoCTrackBar.Maximum = 180;
            this.servoCTrackBar.Name = "servoCTrackBar";
            this.servoCTrackBar.Size = new System.Drawing.Size(629, 22);
            this.servoCTrackBar.TabIndex = 8;
            this.servoCTrackBar.Scroll += new System.EventHandler(this.servoCTrackBar_Scroll);
            // 
            // updateServosButton
            // 
            this.updateServosButton.Location = new System.Drawing.Point(17, 176);
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
            this.receivingDataLabel.BackColor = System.Drawing.Color.Green;
            this.receivingDataLabel.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.receivingDataLabel.Location = new System.Drawing.Point(12, 9);
            this.receivingDataLabel.Name = "receivingDataLabel";
            this.receivingDataLabel.Size = new System.Drawing.Size(170, 65);
            this.receivingDataLabel.TabIndex = 12;
            this.receivingDataLabel.Text = "Receiving Data";
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
            this.statusTextBox.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.statusTextBox.Location = new System.Drawing.Point(12, 250);
            this.statusTextBox.Multiline = true;
            this.statusTextBox.Name = "statusTextBox";
            this.statusTextBox.ReadOnly = true;
            this.statusTextBox.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
            this.statusTextBox.Size = new System.Drawing.Size(776, 188);
            this.statusTextBox.TabIndex = 14;
            // 
            // label4
            // 
            this.label4.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(14, 230);
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
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(800, 450);
            this.Controls.Add(this.turnOffButton);
            this.Controls.Add(this.igniteButton);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.statusTextBox);
            this.Controls.Add(this.flowSwitchLabel);
            this.Controls.Add(this.receivingDataLabel);
            this.Controls.Add(this.ignitionLabel);
            this.Controls.Add(this.updateServosButton);
            this.Controls.Add(this.servoCTrackBar);
            this.Controls.Add(this.servoBTrackBar);
            this.Controls.Add(this.servoATrackBar);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.servoCUpDown);
            this.Controls.Add(this.servoBUpDown);
            this.Controls.Add(this.servoAUpDown);
            this.Name = "Form1";
            this.Text = "Propulsion Ground Test (Temp)";
            this.Load += new System.EventHandler(this.Form1_Load);
            ((System.ComponentModel.ISupportInitialize)(this.servoAUpDown)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.servoBUpDown)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.servoCUpDown)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.servoATrackBar)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.servoBTrackBar)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.servoCTrackBar)).EndInit();
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
    }
}

