namespace Bubbles_Mark_2
{
    partial class VisionGUI
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(VisionGUI));
            this.BeforePictureBox = new System.Windows.Forms.PictureBox();
            this.AfterPictureBox = new System.Windows.Forms.PictureBox();
            this.BeforeLabel = new System.Windows.Forms.Label();
            this.AfterLabel = new System.Windows.Forms.Label();
            this.trackingColorOptions = new System.Windows.Forms.GroupBox();
            this.UserOption = new System.Windows.Forms.RadioButton();
            this.PurpleOption = new System.Windows.Forms.RadioButton();
            this.BlueOption = new System.Windows.Forms.RadioButton();
            this.GreenOption = new System.Windows.Forms.RadioButton();
            this.YellowOption = new System.Windows.Forms.RadioButton();
            this.OrangeOption = new System.Windows.Forms.RadioButton();
            this.RedOption = new System.Windows.Forms.RadioButton();
            this.ColorDialog = new System.Windows.Forms.ColorDialog();
            this.UserMinGroup = new System.Windows.Forms.GroupBox();
            this.label8 = new System.Windows.Forms.Label();
            this.label7 = new System.Windows.Forms.Label();
            this.label6 = new System.Windows.Forms.Label();
            this.userMinBlue = new System.Windows.Forms.TextBox();
            this.label5 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.userMinRed = new System.Windows.Forms.TextBox();
            this.userMinGreen = new System.Windows.Forms.TextBox();
            this.userMinColorButton = new System.Windows.Forms.Button();
            this.userMaxColorButton = new System.Windows.Forms.Button();
            this.UserMaxGroup = new System.Windows.Forms.GroupBox();
            this.label9 = new System.Windows.Forms.Label();
            this.label10 = new System.Windows.Forms.Label();
            this.label11 = new System.Windows.Forms.Label();
            this.userMaxBlue = new System.Windows.Forms.TextBox();
            this.label12 = new System.Windows.Forms.Label();
            this.label13 = new System.Windows.Forms.Label();
            this.label14 = new System.Windows.Forms.Label();
            this.userMaxRed = new System.Windows.Forms.TextBox();
            this.userMaxGreen = new System.Windows.Forms.TextBox();
            ((System.ComponentModel.ISupportInitialize)(this.BeforePictureBox)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.AfterPictureBox)).BeginInit();
            this.trackingColorOptions.SuspendLayout();
            this.UserMinGroup.SuspendLayout();
            this.UserMaxGroup.SuspendLayout();
            this.SuspendLayout();
            // 
            // BeforePictureBox
            // 
            this.BeforePictureBox.BackColor = System.Drawing.SystemColors.ButtonShadow;
            this.BeforePictureBox.Location = new System.Drawing.Point(12, 30);
            this.BeforePictureBox.Name = "BeforePictureBox";
            this.BeforePictureBox.Size = new System.Drawing.Size(382, 252);
            this.BeforePictureBox.SizeMode = System.Windows.Forms.PictureBoxSizeMode.StretchImage;
            this.BeforePictureBox.TabIndex = 0;
            this.BeforePictureBox.TabStop = false;
            // 
            // AfterPictureBox
            // 
            this.AfterPictureBox.BackColor = System.Drawing.SystemColors.ButtonShadow;
            this.AfterPictureBox.Location = new System.Drawing.Point(12, 321);
            this.AfterPictureBox.Name = "AfterPictureBox";
            this.AfterPictureBox.Size = new System.Drawing.Size(382, 252);
            this.AfterPictureBox.SizeMode = System.Windows.Forms.PictureBoxSizeMode.StretchImage;
            this.AfterPictureBox.TabIndex = 1;
            this.AfterPictureBox.TabStop = false;
            // 
            // BeforeLabel
            // 
            this.BeforeLabel.AutoSize = true;
            this.BeforeLabel.Location = new System.Drawing.Point(13, 10);
            this.BeforeLabel.Name = "BeforeLabel";
            this.BeforeLabel.Size = new System.Drawing.Size(50, 17);
            this.BeforeLabel.TabIndex = 2;
            this.BeforeLabel.Text = "Before";
            // 
            // AfterLabel
            // 
            this.AfterLabel.AutoSize = true;
            this.AfterLabel.Location = new System.Drawing.Point(13, 301);
            this.AfterLabel.Name = "AfterLabel";
            this.AfterLabel.Size = new System.Drawing.Size(38, 17);
            this.AfterLabel.TabIndex = 3;
            this.AfterLabel.Text = "After";
            // 
            // trackingColorOptions
            // 
            this.trackingColorOptions.Controls.Add(this.UserOption);
            this.trackingColorOptions.Controls.Add(this.PurpleOption);
            this.trackingColorOptions.Controls.Add(this.BlueOption);
            this.trackingColorOptions.Controls.Add(this.GreenOption);
            this.trackingColorOptions.Controls.Add(this.YellowOption);
            this.trackingColorOptions.Controls.Add(this.OrangeOption);
            this.trackingColorOptions.Controls.Add(this.RedOption);
            this.trackingColorOptions.Location = new System.Drawing.Point(414, 33);
            this.trackingColorOptions.Name = "trackingColorOptions";
            this.trackingColorOptions.Size = new System.Drawing.Size(251, 215);
            this.trackingColorOptions.TabIndex = 4;
            this.trackingColorOptions.TabStop = false;
            this.trackingColorOptions.Text = "Select Tracking Color";
            // 
            // UserOption
            // 
            this.UserOption.AutoSize = true;
            this.UserOption.Location = new System.Drawing.Point(7, 190);
            this.UserOption.Name = "UserOption";
            this.UserOption.Size = new System.Drawing.Size(71, 21);
            this.UserOption.TabIndex = 6;
            this.UserOption.Text = "User...";
            this.UserOption.UseVisualStyleBackColor = true;
            this.UserOption.CheckedChanged += new System.EventHandler(this.UserOption_CheckedChanged);
            // 
            // PurpleOption
            // 
            this.PurpleOption.AutoSize = true;
            this.PurpleOption.Location = new System.Drawing.Point(7, 162);
            this.PurpleOption.Name = "PurpleOption";
            this.PurpleOption.Size = new System.Drawing.Size(70, 21);
            this.PurpleOption.TabIndex = 5;
            this.PurpleOption.Text = "Purple";
            this.PurpleOption.UseVisualStyleBackColor = true;
            this.PurpleOption.CheckedChanged += new System.EventHandler(this.PurpleOption_CheckedChanged);
            // 
            // BlueOption
            // 
            this.BlueOption.AutoSize = true;
            this.BlueOption.Location = new System.Drawing.Point(7, 134);
            this.BlueOption.Name = "BlueOption";
            this.BlueOption.Size = new System.Drawing.Size(57, 21);
            this.BlueOption.TabIndex = 4;
            this.BlueOption.Text = "Blue";
            this.BlueOption.UseVisualStyleBackColor = true;
            this.BlueOption.CheckedChanged += new System.EventHandler(this.BlueOption_CheckedChanged);
            // 
            // GreenOption
            // 
            this.GreenOption.AutoSize = true;
            this.GreenOption.Location = new System.Drawing.Point(7, 106);
            this.GreenOption.Name = "GreenOption";
            this.GreenOption.Size = new System.Drawing.Size(69, 21);
            this.GreenOption.TabIndex = 3;
            this.GreenOption.Text = "Green";
            this.GreenOption.UseVisualStyleBackColor = true;
            this.GreenOption.CheckedChanged += new System.EventHandler(this.GreenOption_CheckedChanged);
            // 
            // YellowOption
            // 
            this.YellowOption.AutoSize = true;
            this.YellowOption.Location = new System.Drawing.Point(7, 78);
            this.YellowOption.Name = "YellowOption";
            this.YellowOption.Size = new System.Drawing.Size(69, 21);
            this.YellowOption.TabIndex = 2;
            this.YellowOption.Text = "Yellow";
            this.YellowOption.UseVisualStyleBackColor = true;
            this.YellowOption.CheckedChanged += new System.EventHandler(this.YellowOption_CheckedChanged);
            // 
            // OrangeOption
            // 
            this.OrangeOption.AutoSize = true;
            this.OrangeOption.Location = new System.Drawing.Point(7, 50);
            this.OrangeOption.Name = "OrangeOption";
            this.OrangeOption.Size = new System.Drawing.Size(77, 21);
            this.OrangeOption.TabIndex = 1;
            this.OrangeOption.Text = "Orange";
            this.OrangeOption.UseVisualStyleBackColor = true;
            this.OrangeOption.CheckedChanged += new System.EventHandler(this.OrangeOption_CheckedChanged);
            // 
            // RedOption
            // 
            this.RedOption.AutoSize = true;
            this.RedOption.Checked = true;
            this.RedOption.Location = new System.Drawing.Point(7, 22);
            this.RedOption.Name = "RedOption";
            this.RedOption.Size = new System.Drawing.Size(55, 21);
            this.RedOption.TabIndex = 0;
            this.RedOption.TabStop = true;
            this.RedOption.Text = "Red";
            this.RedOption.UseVisualStyleBackColor = true;
            this.RedOption.CheckedChanged += new System.EventHandler(this.RedOption_CheckedChanged);
            // 
            // UserMinGroup
            // 
            this.UserMinGroup.Controls.Add(this.label8);
            this.UserMinGroup.Controls.Add(this.label7);
            this.UserMinGroup.Controls.Add(this.label6);
            this.UserMinGroup.Controls.Add(this.userMinBlue);
            this.UserMinGroup.Controls.Add(this.label5);
            this.UserMinGroup.Controls.Add(this.label4);
            this.UserMinGroup.Controls.Add(this.label3);
            this.UserMinGroup.Controls.Add(this.userMinRed);
            this.UserMinGroup.Controls.Add(this.userMinGreen);
            this.UserMinGroup.Location = new System.Drawing.Point(414, 255);
            this.UserMinGroup.Name = "UserMinGroup";
            this.UserMinGroup.Size = new System.Drawing.Size(251, 111);
            this.UserMinGroup.TabIndex = 5;
            this.UserMinGroup.TabStop = false;
            this.UserMinGroup.Text = "User Selected Min";
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Location = new System.Drawing.Point(138, 81);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(71, 17);
            this.label8.TabIndex = 6;
            this.label8.Text = "( 0 - 255 )";
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(137, 53);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(71, 17);
            this.label7.TabIndex = 5;
            this.label7.Text = "( 0 - 255 )";
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(138, 24);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(71, 17);
            this.label6.TabIndex = 4;
            this.label6.Text = "( 0 - 255 )";
            // 
            // userMinBlue
            // 
            this.userMinBlue.Location = new System.Drawing.Point(32, 79);
            this.userMinBlue.Name = "userMinBlue";
            this.userMinBlue.Size = new System.Drawing.Size(100, 22);
            this.userMinBlue.TabIndex = 2;
            this.userMinBlue.Text = "0";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(8, 81);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(17, 17);
            this.label5.TabIndex = 3;
            this.label5.Text = "B";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(7, 53);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(19, 17);
            this.label4.TabIndex = 2;
            this.label4.Text = "G";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(7, 25);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(18, 17);
            this.label3.TabIndex = 0;
            this.label3.Text = "R";
            // 
            // userMinRed
            // 
            this.userMinRed.Location = new System.Drawing.Point(31, 22);
            this.userMinRed.Name = "userMinRed";
            this.userMinRed.Size = new System.Drawing.Size(100, 22);
            this.userMinRed.TabIndex = 1;
            this.userMinRed.Text = "0";
            // 
            // userMinGreen
            // 
            this.userMinGreen.Location = new System.Drawing.Point(31, 50);
            this.userMinGreen.Name = "userMinGreen";
            this.userMinGreen.Size = new System.Drawing.Size(100, 22);
            this.userMinGreen.TabIndex = 0;
            this.userMinGreen.Text = "0";
            // 
            // userMinColorButton
            // 
            this.userMinColorButton.Location = new System.Drawing.Point(413, 372);
            this.userMinColorButton.Name = "userMinColorButton";
            this.userMinColorButton.Size = new System.Drawing.Size(251, 39);
            this.userMinColorButton.TabIndex = 6;
            this.userMinColorButton.Text = "Select Custom Color";
            this.userMinColorButton.UseVisualStyleBackColor = true;
            this.userMinColorButton.Click += new System.EventHandler(this.userMinColorButton_Click);
            // 
            // userMaxColorButton
            // 
            this.userMaxColorButton.Location = new System.Drawing.Point(416, 534);
            this.userMaxColorButton.Name = "userMaxColorButton";
            this.userMaxColorButton.Size = new System.Drawing.Size(251, 39);
            this.userMaxColorButton.TabIndex = 8;
            this.userMaxColorButton.Text = "Select Custom Color";
            this.userMaxColorButton.UseVisualStyleBackColor = true;
            this.userMaxColorButton.Click += new System.EventHandler(this.userMaxColorButton_Click);
            // 
            // UserMaxGroup
            // 
            this.UserMaxGroup.Controls.Add(this.label9);
            this.UserMaxGroup.Controls.Add(this.label10);
            this.UserMaxGroup.Controls.Add(this.label11);
            this.UserMaxGroup.Controls.Add(this.userMaxBlue);
            this.UserMaxGroup.Controls.Add(this.label12);
            this.UserMaxGroup.Controls.Add(this.label13);
            this.UserMaxGroup.Controls.Add(this.label14);
            this.UserMaxGroup.Controls.Add(this.userMaxRed);
            this.UserMaxGroup.Controls.Add(this.userMaxGreen);
            this.UserMaxGroup.Location = new System.Drawing.Point(415, 417);
            this.UserMaxGroup.Name = "UserMaxGroup";
            this.UserMaxGroup.Size = new System.Drawing.Size(251, 111);
            this.UserMaxGroup.TabIndex = 7;
            this.UserMaxGroup.TabStop = false;
            this.UserMaxGroup.Text = "User Selected Max";
            // 
            // label9
            // 
            this.label9.AutoSize = true;
            this.label9.Location = new System.Drawing.Point(138, 83);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(71, 17);
            this.label9.TabIndex = 15;
            this.label9.Text = "( 0 - 255 )";
            // 
            // label10
            // 
            this.label10.AutoSize = true;
            this.label10.Location = new System.Drawing.Point(137, 55);
            this.label10.Name = "label10";
            this.label10.Size = new System.Drawing.Size(71, 17);
            this.label10.TabIndex = 14;
            this.label10.Text = "( 0 - 255 )";
            // 
            // label11
            // 
            this.label11.AutoSize = true;
            this.label11.Location = new System.Drawing.Point(138, 26);
            this.label11.Name = "label11";
            this.label11.Size = new System.Drawing.Size(71, 17);
            this.label11.TabIndex = 13;
            this.label11.Text = "( 0 - 255 )";
            // 
            // userMaxBlue
            // 
            this.userMaxBlue.Location = new System.Drawing.Point(32, 81);
            this.userMaxBlue.Name = "userMaxBlue";
            this.userMaxBlue.Size = new System.Drawing.Size(100, 22);
            this.userMaxBlue.TabIndex = 10;
            this.userMaxBlue.Text = "255";
            // 
            // label12
            // 
            this.label12.AutoSize = true;
            this.label12.Location = new System.Drawing.Point(8, 83);
            this.label12.Name = "label12";
            this.label12.Size = new System.Drawing.Size(17, 17);
            this.label12.TabIndex = 12;
            this.label12.Text = "B";
            // 
            // label13
            // 
            this.label13.AutoSize = true;
            this.label13.Location = new System.Drawing.Point(7, 55);
            this.label13.Name = "label13";
            this.label13.Size = new System.Drawing.Size(19, 17);
            this.label13.TabIndex = 11;
            this.label13.Text = "G";
            // 
            // label14
            // 
            this.label14.AutoSize = true;
            this.label14.Location = new System.Drawing.Point(7, 27);
            this.label14.Name = "label14";
            this.label14.Size = new System.Drawing.Size(18, 17);
            this.label14.TabIndex = 7;
            this.label14.Text = "R";
            // 
            // userMaxRed
            // 
            this.userMaxRed.Location = new System.Drawing.Point(31, 24);
            this.userMaxRed.Name = "userMaxRed";
            this.userMaxRed.Size = new System.Drawing.Size(100, 22);
            this.userMaxRed.TabIndex = 9;
            this.userMaxRed.Text = "255";
            // 
            // userMaxGreen
            // 
            this.userMaxGreen.Location = new System.Drawing.Point(31, 52);
            this.userMaxGreen.Name = "userMaxGreen";
            this.userMaxGreen.Size = new System.Drawing.Size(100, 22);
            this.userMaxGreen.TabIndex = 8;
            this.userMaxGreen.Text = "255";
            // 
            // VisionGUI
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(674, 582);
            this.Controls.Add(this.userMaxColorButton);
            this.Controls.Add(this.UserMaxGroup);
            this.Controls.Add(this.userMinColorButton);
            this.Controls.Add(this.UserMinGroup);
            this.Controls.Add(this.trackingColorOptions);
            this.Controls.Add(this.AfterLabel);
            this.Controls.Add(this.BeforeLabel);
            this.Controls.Add(this.AfterPictureBox);
            this.Controls.Add(this.BeforePictureBox);
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.Name = "VisionGUI";
            this.Text = "VisionGUI";
            ((System.ComponentModel.ISupportInitialize)(this.BeforePictureBox)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.AfterPictureBox)).EndInit();
            this.trackingColorOptions.ResumeLayout(false);
            this.trackingColorOptions.PerformLayout();
            this.UserMinGroup.ResumeLayout(false);
            this.UserMinGroup.PerformLayout();
            this.UserMaxGroup.ResumeLayout(false);
            this.UserMaxGroup.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.PictureBox BeforePictureBox;
        private System.Windows.Forms.PictureBox AfterPictureBox;
        private System.Windows.Forms.Label BeforeLabel;
        private System.Windows.Forms.Label AfterLabel;
        private System.Windows.Forms.GroupBox trackingColorOptions;
        private System.Windows.Forms.RadioButton UserOption;
        private System.Windows.Forms.RadioButton PurpleOption;
        private System.Windows.Forms.RadioButton BlueOption;
        private System.Windows.Forms.RadioButton GreenOption;
        private System.Windows.Forms.RadioButton YellowOption;
        private System.Windows.Forms.RadioButton OrangeOption;
        private System.Windows.Forms.RadioButton RedOption;
        private System.Windows.Forms.ColorDialog ColorDialog;
        private System.Windows.Forms.GroupBox UserMinGroup;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.TextBox userMinBlue;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.TextBox userMinRed;
        private System.Windows.Forms.TextBox userMinGreen;
        private System.Windows.Forms.Button userMinColorButton;
        private System.Windows.Forms.Button userMaxColorButton;
        private System.Windows.Forms.GroupBox UserMaxGroup;
        private System.Windows.Forms.Label label9;
        private System.Windows.Forms.Label label10;
        private System.Windows.Forms.Label label11;
        private System.Windows.Forms.TextBox userMaxBlue;
        private System.Windows.Forms.Label label12;
        private System.Windows.Forms.Label label13;
        private System.Windows.Forms.Label label14;
        private System.Windows.Forms.TextBox userMaxRed;
        private System.Windows.Forms.TextBox userMaxGreen;
    }
}