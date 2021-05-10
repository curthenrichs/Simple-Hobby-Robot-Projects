namespace Bubbles_Brain
{
    partial class form1
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
            this.videoSourcePlayer1 = new AForge.Controls.VideoSourcePlayer();
            this.KeyBoardRadio = new System.Windows.Forms.RadioButton();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.autoRadio = new System.Windows.Forms.RadioButton();
            this.JoystickRadio = new System.Windows.Forms.RadioButton();
            this.CommandRadio = new System.Windows.Forms.RadioButton();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.label6 = new System.Windows.Forms.Label();
            this.commandsOpen = new System.Windows.Forms.Button();
            this.label7 = new System.Windows.Forms.Label();
            this.label8 = new System.Windows.Forms.Label();
            this.textBox1 = new System.Windows.Forms.TextBox();
            this.enterButton = new System.Windows.Forms.Button();
            this.button1 = new System.Windows.Forms.Button();
            this.bubblesHardware = new System.IO.Ports.SerialPort(this.components);
            this.label9 = new System.Windows.Forms.Label();
            this.label10 = new System.Windows.Forms.Label();
            this.timer1 = new System.Windows.Forms.Timer(this.components);
            this.groupBox1.SuspendLayout();
            this.SuspendLayout();
            // 
            // videoSourcePlayer1
            // 
            this.videoSourcePlayer1.BackColor = System.Drawing.SystemColors.ControlDark;
            this.videoSourcePlayer1.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.videoSourcePlayer1.Location = new System.Drawing.Point(12, 12);
            this.videoSourcePlayer1.Name = "videoSourcePlayer1";
            this.videoSourcePlayer1.Size = new System.Drawing.Size(801, 385);
            this.videoSourcePlayer1.TabIndex = 0;
            this.videoSourcePlayer1.Text = "videoSourcePlayer1";
            this.videoSourcePlayer1.VideoSource = null;
            this.videoSourcePlayer1.NewFrame += new AForge.Controls.VideoSourcePlayer.NewFrameHandler(this.videoSourcePlayer1_NewFrame);
            // 
            // KeyBoardRadio
            // 
            this.KeyBoardRadio.AutoSize = true;
            this.KeyBoardRadio.Location = new System.Drawing.Point(6, 13);
            this.KeyBoardRadio.Name = "KeyBoardRadio";
            this.KeyBoardRadio.Size = new System.Drawing.Size(140, 21);
            this.KeyBoardRadio.TabIndex = 1;
            this.KeyBoardRadio.Text = "KeyBoard Control";
            this.KeyBoardRadio.UseVisualStyleBackColor = true;
            this.KeyBoardRadio.CheckedChanged += new System.EventHandler(this.KeyBoardRadio_CheckedChanged);
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.autoRadio);
            this.groupBox1.Controls.Add(this.JoystickRadio);
            this.groupBox1.Controls.Add(this.CommandRadio);
            this.groupBox1.Controls.Add(this.KeyBoardRadio);
            this.groupBox1.Location = new System.Drawing.Point(12, 403);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(801, 40);
            this.groupBox1.TabIndex = 2;
            this.groupBox1.TabStop = false;
            // 
            // autoRadio
            // 
            this.autoRadio.AutoSize = true;
            this.autoRadio.Checked = true;
            this.autoRadio.Location = new System.Drawing.Point(685, 13);
            this.autoRadio.Name = "autoRadio";
            this.autoRadio.Size = new System.Drawing.Size(108, 21);
            this.autoRadio.TabIndex = 10;
            this.autoRadio.TabStop = true;
            this.autoRadio.Text = "Autonomous";
            this.autoRadio.UseVisualStyleBackColor = true;
            this.autoRadio.CheckedChanged += new System.EventHandler(this.autoRadio_CheckedChanged);
            // 
            // JoystickRadio
            // 
            this.JoystickRadio.AutoSize = true;
            this.JoystickRadio.Location = new System.Drawing.Point(232, 13);
            this.JoystickRadio.Name = "JoystickRadio";
            this.JoystickRadio.Size = new System.Drawing.Size(128, 21);
            this.JoystickRadio.TabIndex = 3;
            this.JoystickRadio.Text = "Joystick Control";
            this.JoystickRadio.UseVisualStyleBackColor = true;
            this.JoystickRadio.CheckedChanged += new System.EventHandler(this.JoystickRadio_CheckedChanged);
            // 
            // CommandRadio
            // 
            this.CommandRadio.AutoSize = true;
            this.CommandRadio.Location = new System.Drawing.Point(457, 13);
            this.CommandRadio.Name = "CommandRadio";
            this.CommandRadio.Size = new System.Drawing.Size(141, 21);
            this.CommandRadio.TabIndex = 2;
            this.CommandRadio.Text = "Command Control";
            this.CommandRadio.UseVisualStyleBackColor = true;
            this.CommandRadio.CheckedChanged += new System.EventHandler(this.CommandRadio_CheckedChanged);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(12, 467);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(114, 17);
            this.label1.TabIndex = 3;
            this.label1.Text = "        \'A\' to go left";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(12, 450);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(143, 17);
            this.label2.TabIndex = 4;
            this.label2.Text = "Use \'W\' to go forward";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(12, 488);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(124, 17);
            this.label3.TabIndex = 5;
            this.label3.Text = "        \'D\' to go right";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(12, 509);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(125, 17);
            this.label4.TabIndex = 6;
            this.label4.Text = "        \'S\' to go back";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(231, 450);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(141, 17);
            this.label5.TabIndex = 7;
            this.label5.Text = "No Joystick Detected";
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(466, 446);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(109, 17);
            this.label6.TabIndex = 9;
            this.label6.Text = "Enter Command";
            // 
            // commandsOpen
            // 
            this.commandsOpen.Location = new System.Drawing.Point(469, 499);
            this.commandsOpen.Name = "commandsOpen";
            this.commandsOpen.Size = new System.Drawing.Size(82, 27);
            this.commandsOpen.TabIndex = 10;
            this.commandsOpen.Text = "Commands";
            this.commandsOpen.UseVisualStyleBackColor = true;
            this.commandsOpen.Click += new System.EventHandler(this.commandsOpen_Click);
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(676, 446);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(137, 17);
            this.label7.TabIndex = 11;
            this.label7.Text = "Speech and Remote";
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Location = new System.Drawing.Point(688, 470);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(118, 17);
            this.label8.TabIndex = 12;
            this.label8.Text = " Access Available";
            // 
            // textBox1
            // 
            this.textBox1.Location = new System.Drawing.Point(469, 470);
            this.textBox1.Name = "textBox1";
            this.textBox1.Size = new System.Drawing.Size(154, 22);
            this.textBox1.TabIndex = 13;
            // 
            // enterButton
            // 
            this.enterButton.Location = new System.Drawing.Point(560, 499);
            this.enterButton.Name = "enterButton";
            this.enterButton.Size = new System.Drawing.Size(63, 27);
            this.enterButton.TabIndex = 14;
            this.enterButton.Text = "ENTER";
            this.enterButton.UseVisualStyleBackColor = true;
            this.enterButton.Click += new System.EventHandler(this.enterButton_Click);
            // 
            // button1
            // 
            this.button1.Font = new System.Drawing.Font("Microsoft Sans Serif", 19.8F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.button1.ForeColor = System.Drawing.Color.Red;
            this.button1.Location = new System.Drawing.Point(12, 550);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(801, 45);
            this.button1.TabIndex = 15;
            this.button1.Text = "ESTOP";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // label9
            // 
            this.label9.AutoSize = true;
            this.label9.Location = new System.Drawing.Point(41, 530);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(116, 17);
            this.label9.TabIndex = 16;
            this.label9.Text = "Spacebar to stop";
            // 
            // label10
            // 
            this.label10.AutoSize = true;
            this.label10.BackColor = System.Drawing.SystemColors.ControlDark;
            this.label10.Location = new System.Drawing.Point(363, 178);
            this.label10.Name = "label10";
            this.label10.Size = new System.Drawing.Size(109, 17);
            this.label10.TabIndex = 17;
            this.label10.Text = "No Video Signal";
            // 
            // timer1
            // 
            this.timer1.Enabled = true;
            this.timer1.Tick += new System.EventHandler(this.timer1_Tick);
            // 
            // form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(825, 607);
            this.Controls.Add(this.label10);
            this.Controls.Add(this.label9);
            this.Controls.Add(this.button1);
            this.Controls.Add(this.enterButton);
            this.Controls.Add(this.textBox1);
            this.Controls.Add(this.label8);
            this.Controls.Add(this.label7);
            this.Controls.Add(this.commandsOpen);
            this.Controls.Add(this.label6);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.groupBox1);
            this.Controls.Add(this.videoSourcePlayer1);
            this.KeyPreview = true;
            this.Name = "form1";
            this.Text = "Bubble Command Server";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.form1_FormClosing);
            this.KeyDown += new System.Windows.Forms.KeyEventHandler(this.form1_KeyDown);
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private AForge.Controls.VideoSourcePlayer videoSourcePlayer1;
        private System.Windows.Forms.RadioButton KeyBoardRadio;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.RadioButton JoystickRadio;
        private System.Windows.Forms.RadioButton CommandRadio;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.RadioButton autoRadio;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.Button commandsOpen;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.TextBox textBox1;
        private System.Windows.Forms.Button enterButton;
        private System.Windows.Forms.Button button1;
        private System.IO.Ports.SerialPort bubblesHardware;
        private System.Windows.Forms.Label label9;
        private System.Windows.Forms.Label label10;
        private System.Windows.Forms.Timer timer1;
    }
}

