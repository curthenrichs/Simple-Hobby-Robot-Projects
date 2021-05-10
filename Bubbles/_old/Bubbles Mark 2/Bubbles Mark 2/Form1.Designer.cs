namespace Bubbles_Mark_2
{
    partial class MainGUI
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
            this.components = new System.ComponentModel.Container();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(MainGUI));
            this.videoSourcePlayer1 = new AForge.Controls.VideoSourcePlayer();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.autonomousOption = new System.Windows.Forms.RadioButton();
            this.commandOption = new System.Windows.Forms.RadioButton();
            this.joystickOption = new System.Windows.Forms.RadioButton();
            this.keyboardOption = new System.Windows.Forms.RadioButton();
            this.keyuselabel1 = new System.Windows.Forms.Label();
            this.keyuselabel2 = new System.Windows.Forms.Label();
            this.keyuselabel3 = new System.Windows.Forms.Label();
            this.keyuselabel4 = new System.Windows.Forms.Label();
            this.keyuselabel5 = new System.Windows.Forms.Label();
            this.ESTOP = new System.Windows.Forms.Button();
            this.joystickDetectionLabel = new System.Windows.Forms.Label();
            this.commandLabel1 = new System.Windows.Forms.Label();
            this.commandText = new System.Windows.Forms.TextBox();
            this.CommandsButton = new System.Windows.Forms.Button();
            this.enterButton = new System.Windows.Forms.Button();
            this.autonLabel1 = new System.Windows.Forms.Label();
            this.AutonLabel2 = new System.Windows.Forms.Label();
            this.Cycle = new System.Windows.Forms.Timer(this.components);
            this.joyXlabel = new System.Windows.Forms.Label();
            this.joyYlabel = new System.Windows.Forms.Label();
            this.VisionProcessingCheckBox = new System.Windows.Forms.CheckBox();
            this.groupBox1.SuspendLayout();
            this.SuspendLayout();
            // 
            // videoSourcePlayer1
            // 
            this.videoSourcePlayer1.Location = new System.Drawing.Point(12, 12);
            this.videoSourcePlayer1.Name = "videoSourcePlayer1";
            this.videoSourcePlayer1.Size = new System.Drawing.Size(752, 435);
            this.videoSourcePlayer1.TabIndex = 0;
            this.videoSourcePlayer1.Text = "player";
            this.videoSourcePlayer1.VideoSource = null;
            this.videoSourcePlayer1.NewFrame += new AForge.Controls.VideoSourcePlayer.NewFrameHandler(this.videoSourcePlayer1_NewFrame);
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.autonomousOption);
            this.groupBox1.Controls.Add(this.commandOption);
            this.groupBox1.Controls.Add(this.joystickOption);
            this.groupBox1.Controls.Add(this.keyboardOption);
            this.groupBox1.Location = new System.Drawing.Point(12, 454);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(752, 46);
            this.groupBox1.TabIndex = 1;
            this.groupBox1.TabStop = false;
            // 
            // autonomousOption
            // 
            this.autonomousOption.AutoSize = true;
            this.autonomousOption.Checked = true;
            this.autonomousOption.Location = new System.Drawing.Point(608, 15);
            this.autonomousOption.Name = "autonomousOption";
            this.autonomousOption.Size = new System.Drawing.Size(108, 21);
            this.autonomousOption.TabIndex = 3;
            this.autonomousOption.TabStop = true;
            this.autonomousOption.Text = "Autonomous";
            this.autonomousOption.UseVisualStyleBackColor = true;
            this.autonomousOption.CheckedChanged += new System.EventHandler(this.autonomousOption_CheckedChanged);
            // 
            // commandOption
            // 
            this.commandOption.AutoSize = true;
            this.commandOption.Location = new System.Drawing.Point(398, 15);
            this.commandOption.Name = "commandOption";
            this.commandOption.Size = new System.Drawing.Size(141, 21);
            this.commandOption.TabIndex = 2;
            this.commandOption.Text = "Command Control";
            this.commandOption.UseVisualStyleBackColor = true;
            this.commandOption.CheckedChanged += new System.EventHandler(this.commandOption_CheckedChanged);
            // 
            // joystickOption
            // 
            this.joystickOption.AutoSize = true;
            this.joystickOption.Location = new System.Drawing.Point(207, 15);
            this.joystickOption.Name = "joystickOption";
            this.joystickOption.Size = new System.Drawing.Size(128, 21);
            this.joystickOption.TabIndex = 1;
            this.joystickOption.Text = "Joystick Control";
            this.joystickOption.UseVisualStyleBackColor = true;
            this.joystickOption.CheckedChanged += new System.EventHandler(this.joystickOption_CheckedChanged);
            // 
            // keyboardOption
            // 
            this.keyboardOption.AutoSize = true;
            this.keyboardOption.Location = new System.Drawing.Point(7, 15);
            this.keyboardOption.Name = "keyboardOption";
            this.keyboardOption.Size = new System.Drawing.Size(144, 21);
            this.keyboardOption.TabIndex = 0;
            this.keyboardOption.Text = "Key Board Control";
            this.keyboardOption.UseVisualStyleBackColor = true;
            this.keyboardOption.CheckedChanged += new System.EventHandler(this.keyboardOption_CheckedChanged);
            // 
            // keyuselabel1
            // 
            this.keyuselabel1.AutoSize = true;
            this.keyuselabel1.Location = new System.Drawing.Point(19, 507);
            this.keyuselabel1.Name = "keyuselabel1";
            this.keyuselabel1.Size = new System.Drawing.Size(143, 17);
            this.keyuselabel1.TabIndex = 2;
            this.keyuselabel1.Text = "Use \'W\' to go forward";
            // 
            // keyuselabel2
            // 
            this.keyuselabel2.AutoSize = true;
            this.keyuselabel2.Location = new System.Drawing.Point(49, 528);
            this.keyuselabel2.Name = "keyuselabel2";
            this.keyuselabel2.Size = new System.Drawing.Size(82, 17);
            this.keyuselabel2.TabIndex = 3;
            this.keyuselabel2.Text = "\'A\' to go left";
            // 
            // keyuselabel3
            // 
            this.keyuselabel3.AutoSize = true;
            this.keyuselabel3.Location = new System.Drawing.Point(49, 549);
            this.keyuselabel3.Name = "keyuselabel3";
            this.keyuselabel3.Size = new System.Drawing.Size(92, 17);
            this.keyuselabel3.TabIndex = 4;
            this.keyuselabel3.Text = "\'D\' to go right";
            // 
            // keyuselabel4
            // 
            this.keyuselabel4.AutoSize = true;
            this.keyuselabel4.Location = new System.Drawing.Point(50, 570);
            this.keyuselabel4.Name = "keyuselabel4";
            this.keyuselabel4.Size = new System.Drawing.Size(93, 17);
            this.keyuselabel4.TabIndex = 5;
            this.keyuselabel4.Text = "\'S\' to go back";
            // 
            // keyuselabel5
            // 
            this.keyuselabel5.AutoSize = true;
            this.keyuselabel5.Location = new System.Drawing.Point(51, 591);
            this.keyuselabel5.Name = "keyuselabel5";
            this.keyuselabel5.Size = new System.Drawing.Size(116, 17);
            this.keyuselabel5.TabIndex = 6;
            this.keyuselabel5.Text = "Spacebar to stop";
            // 
            // ESTOP
            // 
            this.ESTOP.Font = new System.Drawing.Font("Microsoft Sans Serif", 19.8F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.ESTOP.ForeColor = System.Drawing.Color.Red;
            this.ESTOP.Location = new System.Drawing.Point(12, 619);
            this.ESTOP.Name = "ESTOP";
            this.ESTOP.Size = new System.Drawing.Size(745, 60);
            this.ESTOP.TabIndex = 7;
            this.ESTOP.Text = "ESTOP";
            this.ESTOP.UseVisualStyleBackColor = true;
            this.ESTOP.Click += new System.EventHandler(this.button1_Click);
            // 
            // joystickDetectionLabel
            // 
            this.joystickDetectionLabel.AutoSize = true;
            this.joystickDetectionLabel.Location = new System.Drawing.Point(219, 507);
            this.joystickDetectionLabel.Name = "joystickDetectionLabel";
            this.joystickDetectionLabel.Size = new System.Drawing.Size(141, 17);
            this.joystickDetectionLabel.TabIndex = 8;
            this.joystickDetectionLabel.Text = "No Joystick Detected";
            // 
            // commandLabel1
            // 
            this.commandLabel1.AutoSize = true;
            this.commandLabel1.Location = new System.Drawing.Point(410, 507);
            this.commandLabel1.Name = "commandLabel1";
            this.commandLabel1.Size = new System.Drawing.Size(109, 17);
            this.commandLabel1.TabIndex = 9;
            this.commandLabel1.Text = "Enter Command";
            // 
            // commandText
            // 
            this.commandText.Location = new System.Drawing.Point(410, 528);
            this.commandText.Name = "commandText";
            this.commandText.Size = new System.Drawing.Size(151, 22);
            this.commandText.TabIndex = 10;
            // 
            // CommandsButton
            // 
            this.CommandsButton.Location = new System.Drawing.Point(410, 556);
            this.CommandsButton.Name = "CommandsButton";
            this.CommandsButton.Size = new System.Drawing.Size(86, 31);
            this.CommandsButton.TabIndex = 11;
            this.CommandsButton.Text = "Commands";
            this.CommandsButton.UseVisualStyleBackColor = true;
            this.CommandsButton.Click += new System.EventHandler(this.CommandsButton_Click);
            // 
            // enterButton
            // 
            this.enterButton.Location = new System.Drawing.Point(502, 556);
            this.enterButton.Name = "enterButton";
            this.enterButton.Size = new System.Drawing.Size(59, 30);
            this.enterButton.TabIndex = 12;
            this.enterButton.Text = "Enter";
            this.enterButton.UseVisualStyleBackColor = true;
            this.enterButton.Click += new System.EventHandler(this.enterButton_Click);
            // 
            // autonLabel1
            // 
            this.autonLabel1.AutoSize = true;
            this.autonLabel1.Location = new System.Drawing.Point(620, 507);
            this.autonLabel1.Name = "autonLabel1";
            this.autonLabel1.Size = new System.Drawing.Size(137, 17);
            this.autonLabel1.TabIndex = 13;
            this.autonLabel1.Text = "Speech and Remote";
            // 
            // AutonLabel2
            // 
            this.AutonLabel2.AutoSize = true;
            this.AutonLabel2.Location = new System.Drawing.Point(635, 528);
            this.AutonLabel2.Name = "AutonLabel2";
            this.AutonLabel2.Size = new System.Drawing.Size(107, 17);
            this.AutonLabel2.TabIndex = 14;
            this.AutonLabel2.Text = "Acess Available";
            // 
            // Cycle
            // 
            this.Cycle.Interval = 250;
            this.Cycle.Tick += new System.EventHandler(this.Cycle_Tick);
            // 
            // joyXlabel
            // 
            this.joyXlabel.AutoSize = true;
            this.joyXlabel.Location = new System.Drawing.Point(219, 532);
            this.joyXlabel.Name = "joyXlabel";
            this.joyXlabel.Size = new System.Drawing.Size(53, 17);
            this.joyXlabel.TabIndex = 15;
            this.joyXlabel.Text = "X = 0.0";
            // 
            // joyYlabel
            // 
            this.joyYlabel.AutoSize = true;
            this.joyYlabel.Location = new System.Drawing.Point(219, 556);
            this.joyYlabel.Name = "joyYlabel";
            this.joyYlabel.Size = new System.Drawing.Size(53, 17);
            this.joyYlabel.TabIndex = 16;
            this.joyYlabel.Text = "Y = 0.0";
            // 
            // VisionProcessingCheckBox
            // 
            this.VisionProcessingCheckBox.AutoSize = true;
            this.VisionProcessingCheckBox.Location = new System.Drawing.Point(620, 553);
            this.VisionProcessingCheckBox.Name = "VisionProcessingCheckBox";
            this.VisionProcessingCheckBox.Size = new System.Drawing.Size(142, 21);
            this.VisionProcessingCheckBox.TabIndex = 17;
            this.VisionProcessingCheckBox.Text = "Vision Processing";
            this.VisionProcessingCheckBox.UseVisualStyleBackColor = true;
            this.VisionProcessingCheckBox.CheckedChanged += new System.EventHandler(this.VisionProcessingCheckBox_CheckedChanged);
            // 
            // MainGUI
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(776, 691);
            this.Controls.Add(this.VisionProcessingCheckBox);
            this.Controls.Add(this.joyYlabel);
            this.Controls.Add(this.joyXlabel);
            this.Controls.Add(this.AutonLabel2);
            this.Controls.Add(this.autonLabel1);
            this.Controls.Add(this.enterButton);
            this.Controls.Add(this.CommandsButton);
            this.Controls.Add(this.commandText);
            this.Controls.Add(this.commandLabel1);
            this.Controls.Add(this.joystickDetectionLabel);
            this.Controls.Add(this.ESTOP);
            this.Controls.Add(this.keyuselabel5);
            this.Controls.Add(this.keyuselabel4);
            this.Controls.Add(this.keyuselabel3);
            this.Controls.Add(this.keyuselabel2);
            this.Controls.Add(this.keyuselabel1);
            this.Controls.Add(this.groupBox1);
            this.Controls.Add(this.videoSourcePlayer1);
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.KeyPreview = true;
            this.Name = "MainGUI";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Bubbles Brain Mark 2";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.MainGUI_FormClosing);
            this.KeyDown += new System.Windows.Forms.KeyEventHandler(this.MainGUI_KeyDown);
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private AForge.Controls.VideoSourcePlayer videoSourcePlayer1;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.RadioButton autonomousOption;
        private System.Windows.Forms.RadioButton commandOption;
        private System.Windows.Forms.RadioButton joystickOption;
        private System.Windows.Forms.RadioButton keyboardOption;
        private System.Windows.Forms.Label keyuselabel1;
        private System.Windows.Forms.Label keyuselabel2;
        private System.Windows.Forms.Label keyuselabel3;
        private System.Windows.Forms.Label keyuselabel4;
        private System.Windows.Forms.Label keyuselabel5;
        private System.Windows.Forms.Button ESTOP;
        private System.Windows.Forms.Label joystickDetectionLabel;
        private System.Windows.Forms.Label commandLabel1;
        private System.Windows.Forms.TextBox commandText;
        private System.Windows.Forms.Button CommandsButton;
        private System.Windows.Forms.Button enterButton;
        private System.Windows.Forms.Label autonLabel1;
        private System.Windows.Forms.Label AutonLabel2;
        private System.Windows.Forms.Timer Cycle;
        private System.Windows.Forms.Label joyXlabel;
        private System.Windows.Forms.Label joyYlabel;
        private System.Windows.Forms.CheckBox VisionProcessingCheckBox;
    }
}

