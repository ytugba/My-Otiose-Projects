namespace CurrencyCalculator
{
    partial class CurrencyCalculator
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

        private System.Windows.Forms.Label ConvertFrom;
        private System.Windows.Forms.Label ConvertTo;
        private System.Windows.Forms.Label EnterAmount;
        private System.Windows.Forms.Button Convert;
        private System.Windows.Forms.ComboBox ConvertFromCBox;
        private System.Windows.Forms.ComboBox ConvertToCBox;
        private System.Windows.Forms.TextBox EnterAmountBox;
        private System.Windows.Forms.Label Title;
        private System.Windows.Forms.Label Result;
        private System.Windows.Forms.TextBox ResultBox;
    }
}

