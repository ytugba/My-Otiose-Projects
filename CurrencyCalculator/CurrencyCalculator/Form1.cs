using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.IO;
using System.Net;
using Newtonsoft.Json;
using Newtonsoft.Json.Linq;
using System.Web;

namespace CurrencyCalculator
{
    public class Quotes
    {
        public double USDEUR { get; set; }
        public double USDTRY { get; set; }
    }

    public class RootObject
    {
        public bool success { get; set; }
        public string terms { get; set; }
        public string privacy { get; set; }
        public int timestamp { get; set; }
        public string source { get; set; }
        public Quotes quotes { get; set; }
    }

    public partial class CurrencyCalculator : Form
    {
        public CurrencyCalculator()
        {
            InitializeComponent();
        }

        private void InitializeComponent()
        {
            this.ConvertFrom = new System.Windows.Forms.Label();
            this.ConvertTo = new System.Windows.Forms.Label();
            this.EnterAmount = new System.Windows.Forms.Label();
            this.Convert = new System.Windows.Forms.Button();
            this.ConvertFromCBox = new System.Windows.Forms.ComboBox();
            this.ConvertToCBox = new System.Windows.Forms.ComboBox();
            this.EnterAmountBox = new System.Windows.Forms.TextBox();
            this.Title = new System.Windows.Forms.Label();
            this.Result = new System.Windows.Forms.Label();
            this.ResultBox = new System.Windows.Forms.TextBox();
            this.SuspendLayout();
            // 
            // ConvertFrom
            // 
            this.ConvertFrom.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.ConvertFrom.AutoSize = true;
            this.ConvertFrom.Font = new System.Drawing.Font("Prime", 15.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.ConvertFrom.ForeColor = System.Drawing.Color.White;
            this.ConvertFrom.Location = new System.Drawing.Point(66, 131);
            this.ConvertFrom.Name = "ConvertFrom";
            this.ConvertFrom.Size = new System.Drawing.Size(139, 25);
            this.ConvertFrom.TabIndex = 0;
            this.ConvertFrom.Text = "Convert From";
            // 
            // ConvertTo
            // 
            this.ConvertTo.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.ConvertTo.AutoSize = true;
            this.ConvertTo.Font = new System.Drawing.Font("Prime", 15.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.ConvertTo.ForeColor = System.Drawing.Color.White;
            this.ConvertTo.Location = new System.Drawing.Point(66, 193);
            this.ConvertTo.Name = "ConvertTo";
            this.ConvertTo.Size = new System.Drawing.Size(116, 25);
            this.ConvertTo.TabIndex = 1;
            this.ConvertTo.Text = "Convert To";
            // 
            // EnterAmount
            // 
            this.EnterAmount.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.EnterAmount.AutoSize = true;
            this.EnterAmount.Font = new System.Drawing.Font("Prime", 15.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.EnterAmount.ForeColor = System.Drawing.Color.White;
            this.EnterAmount.Location = new System.Drawing.Point(66, 253);
            this.EnterAmount.Name = "EnterAmount";
            this.EnterAmount.Size = new System.Drawing.Size(144, 25);
            this.EnterAmount.TabIndex = 2;
            this.EnterAmount.Text = "Enter Amount";
            // 
            // Convert
            // 
            this.Convert.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.Convert.AutoSize = true;
            this.Convert.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowAndShrink;
            this.Convert.BackgroundImageLayout = System.Windows.Forms.ImageLayout.None;
            this.Convert.Cursor = System.Windows.Forms.Cursors.Hand;
            this.Convert.DialogResult = System.Windows.Forms.DialogResult.OK;
            this.Convert.FlatStyle = System.Windows.Forms.FlatStyle.Popup;
            this.Convert.Font = new System.Drawing.Font("Prime", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.Convert.ForeColor = System.Drawing.Color.White;
            this.Convert.Location = new System.Drawing.Point(339, 316);
            this.Convert.Name = "Convert";
            this.Convert.Size = new System.Drawing.Size(75, 29);
            this.Convert.TabIndex = 3;
            this.Convert.Text = "Convert";
            this.Convert.TextImageRelation = System.Windows.Forms.TextImageRelation.TextAboveImage;
            this.Convert.UseVisualStyleBackColor = false;
            this.Convert.Click += new System.EventHandler(this.Convert_Click);
            // 
            // ConvertFromCBox
            // 
            this.ConvertFromCBox.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.ConvertFromCBox.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.ConvertFromCBox.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.ConvertFromCBox.FormattingEnabled = true;
            this.ConvertFromCBox.Items.AddRange(new object[] {
            "USD",
            "EUR",
            "TRY"});
            this.ConvertFromCBox.Location = new System.Drawing.Point(233, 128);
            this.ConvertFromCBox.Name = "ConvertFromCBox";
            this.ConvertFromCBox.Size = new System.Drawing.Size(121, 28);
            this.ConvertFromCBox.Sorted = true;
            this.ConvertFromCBox.TabIndex = 4;
            // 
            // ConvertToCBox
            // 
            this.ConvertToCBox.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.ConvertToCBox.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.ConvertToCBox.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.ConvertToCBox.FormattingEnabled = true;
            this.ConvertToCBox.Items.AddRange(new object[] {
            "USD",
            "EUR",
            "TRY"});
            this.ConvertToCBox.Location = new System.Drawing.Point(233, 193);
            this.ConvertToCBox.Name = "ConvertToCBox";
            this.ConvertToCBox.Size = new System.Drawing.Size(121, 28);
            this.ConvertToCBox.Sorted = true;
            this.ConvertToCBox.TabIndex = 5;
            // 
            // EnterAmountBox
            // 
            this.EnterAmountBox.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.EnterAmountBox.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.EnterAmountBox.Location = new System.Drawing.Point(233, 254);
            this.EnterAmountBox.Name = "EnterAmountBox";
            this.EnterAmountBox.Size = new System.Drawing.Size(121, 26);
            this.EnterAmountBox.TabIndex = 6;
            this.EnterAmountBox.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.EnterAmountBox_KeyPress);
            // 
            // Title
            // 
            this.Title.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.Title.AutoSize = true;
            this.Title.Font = new System.Drawing.Font("Prime", 26.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.Title.ForeColor = System.Drawing.SystemColors.Control;
            this.Title.Location = new System.Drawing.Point(24, 37);
            this.Title.Name = "Title";
            this.Title.Size = new System.Drawing.Size(438, 42);
            this.Title.TabIndex = 7;
            this.Title.Text = "CURRENCY CALCULATOR";
            // 
            // Result
            // 
            this.Result.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.Result.AutoSize = true;
            this.Result.Font = new System.Drawing.Font("Prime", 15.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.Result.ForeColor = System.Drawing.Color.White;
            this.Result.Location = new System.Drawing.Point(66, 375);
            this.Result.Name = "Result";
            this.Result.Size = new System.Drawing.Size(71, 25);
            this.Result.TabIndex = 8;
            this.Result.Text = "Result";
            this.Result.Visible = false;
            // 
            // ResultBox
            // 
            this.ResultBox.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.ResultBox.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(40)))), ((int)(((byte)(40)))), ((int)(((byte)(40)))));
            this.ResultBox.BorderStyle = System.Windows.Forms.BorderStyle.None;
            this.ResultBox.Cursor = System.Windows.Forms.Cursors.Default;
            this.ResultBox.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.ResultBox.ForeColor = System.Drawing.Color.White;
            this.ResultBox.Location = new System.Drawing.Point(233, 374);
            this.ResultBox.Name = "ResultBox";
            this.ResultBox.ReadOnly = true;
            this.ResultBox.Size = new System.Drawing.Size(181, 19);
            this.ResultBox.TabIndex = 9;
            this.ResultBox.Visible = false;
            // 
            // CurrencyCalculator
            // 
            this.AcceptButton = this.Convert;
            this.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowAndShrink;
            this.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(40)))), ((int)(((byte)(40)))), ((int)(((byte)(40)))));
            this.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Center;
            this.ClientSize = new System.Drawing.Size(484, 461);
            this.Controls.Add(this.ResultBox);
            this.Controls.Add(this.Result);
            this.Controls.Add(this.Title);
            this.Controls.Add(this.EnterAmountBox);
            this.Controls.Add(this.ConvertToCBox);
            this.Controls.Add(this.ConvertFromCBox);
            this.Controls.Add(this.Convert);
            this.Controls.Add(this.EnterAmount);
            this.Controls.Add(this.ConvertTo);
            this.Controls.Add(this.ConvertFrom);
            this.Name = "CurrencyCalculator";
            this.Text = "Currency Calculator";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        private void Convert_Click(object sender, EventArgs e)
        {
            this.Result.Visible = true;
            this.ResultBox.Visible = true;
            double amount = 0.0;

            string url = "http://apilayer.net/api/live?access_key=ea009d1bcf8120225204fe3985b2e156&currencies=EUR,TRY&source=USD&format=1";
            var json = new WebClient().DownloadString(url);
            string jsondata = "";
            using (WebClient response = new WebClient())
            {
                jsondata = response.DownloadString(url);
            }
            RootObject realtimevalue = JsonConvert.DeserializeObject<RootObject>(jsondata);

            if (this.EnterAmountBox.Text != "")
            {
                amount = double.Parse(this.EnterAmountBox.Text);
            }
            if (this.EnterAmountBox.Text == "")
            {
                this.EnterAmountBox.Text = "0.0";
            }          

            //From Dollar
            if(ConvertFromCBox.Text == "USD" && ConvertToCBox.Text == "TRY")
            {
                this.ResultBox.Text = (amount * realtimevalue.quotes.USDTRY).ToString();
            }
            else if (ConvertFromCBox.Text == "USD" && ConvertToCBox.Text == "EUR")
            {
                this.ResultBox.Text = (amount * realtimevalue.quotes.USDEUR).ToString();
            }

            //From Euro
            else if (ConvertFromCBox.Text == "EUR" && ConvertToCBox.Text == "USD")
            {
                this.ResultBox.Text = (amount / realtimevalue.quotes.USDEUR).ToString();
            }
            else if (ConvertFromCBox.Text == "EUR" && ConvertToCBox.Text == "TRY")
            {
                this.ResultBox.Text = (realtimevalue.quotes.USDTRY / realtimevalue.quotes.USDEUR * amount).ToString();
            }

            //From Turkish Lira
            else if (ConvertFromCBox.Text == "TRY" && ConvertToCBox.Text == "USD")
            {
                this.ResultBox.Text = (amount / realtimevalue.quotes.USDTRY).ToString();
            }
            else if (ConvertFromCBox.Text == "TRY" && ConvertToCBox.Text == "EUR")
            {
                this.ResultBox.Text = (realtimevalue.quotes.USDEUR / realtimevalue.quotes.USDTRY * amount).ToString();
            }

            else if ((ConvertFromCBox.Text == "USD" && ConvertToCBox.Text == "USD") 
                     || (ConvertFromCBox.Text == "EUR" && ConvertToCBox.Text == "EUR") 
                     || (ConvertFromCBox.Text == "TRY" && ConvertToCBox.Text == "TRY"))
            {
                this.ResultBox.Text = amount.ToString();
            }

            // this.ResultBox.Text = realtimevalue.quotes.USDEUR;

            if (this.ConvertFromCBox.SelectedItem == null || this.ConvertToCBox.SelectedItem == null)
                {
                this.ResultBox.Text = "Missing Information";
                }

        }

        private void EnterAmountBox_KeyPress(object sender, KeyPressEventArgs e)
        {
                if (!char.IsControl(e.KeyChar) && !char.IsDigit(e.KeyChar) && (e.KeyChar != '.'))
                {
                    e.Handled = true;
                }
        }
    }
}
