using Microsoft.Win32;
using System;
using System.Diagnostics;
using System.Globalization;
using System.IO;
using System.Threading;
using System.Windows;
using System.Windows.Media;
using System.Windows.Media.Imaging;

namespace Retouch_Detector_Win_Edition
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        private void window_1_on()
        {
            loadImageButton.Visibility = Visibility.Visible;
            title.Visibility = Visibility.Visible;
            explanation.Visibility = Visibility.Visible;
        }

        public void window_2_on()
        {
            loadedImageBox.Visibility = Visibility.Visible;
            progressBar.Visibility = Visibility.Visible;
            accuracyValue.Visibility = Visibility.Visible;
            againButton.Visibility = Visibility.Visible;
        }
        private void window_1_off()
        {
            loadImageButton.Visibility = Visibility.Hidden;
            title.Visibility = Visibility.Hidden;
            explanation.Visibility = Visibility.Hidden;
        }

        public void window_2_off()
        {
            loadedImageBox.Visibility = Visibility.Hidden;
            progressBar.Visibility = Visibility.Hidden;
            accuracyValue.Visibility = Visibility.Hidden;
            againButton.Visibility = Visibility.Hidden;
        }



        public MainWindow()
        {
            InitializeComponent();
            window_2_off();
            predicting.Visibility = Visibility.Hidden;
        }

        private void loadImageButton_Click(object sender, RoutedEventArgs e)
        {
            window_1_off();
            predicting.Visibility = Visibility.Visible;
            loadImage();
        }

        private void loadImage()
        {
            string value = "";

            OpenFileDialog op = new OpenFileDialog();
            op.Title = "Select a picture";
            op.Filter = "All supported graphics|*.jpg;*.jpeg;| JPEG (*.jpg;*.jpeg)|*.jpg;*.jpeg";
            if (op.ShowDialog() == true)
            {
                window_1_off();
                predicting.Visibility = Visibility.Visible;
                Console.WriteLine(op.FileName);

                string root = $"{ AppDomain.CurrentDomain.BaseDirectory }";
                // C:\Users\cetin\source\repos\Retouch Detector Win Edition\Retouch Detector Win Edition\bin\Debug\netcoreapp3.1\
                string path = $"{root}predict.py";
                //string path = "C:\\Users\\cetin\\Desktop\\predict.py";
                string pythonPath = Environment.GetEnvironmentVariable("PYTHONPATH") + "\\python.exe";

                if (!Directory.Exists(Environment.GetEnvironmentVariable("PYTHONPATH")))
                {
                    MessageBox.Show("To run python files Set python.exe to your environment settings as PYTHONPATH", "Missing", MessageBoxButton.OK, MessageBoxImage.Error);
                }
                else
                {
                    string imagePath = op.FileName;
                   
                    ProcessStartInfo myProcessStartInfo = new ProcessStartInfo(pythonPath);
                    myProcessStartInfo.UseShellExecute = false;
                    myProcessStartInfo.CreateNoWindow = true;
                    myProcessStartInfo.RedirectStandardOutput = true;
                    myProcessStartInfo.Arguments = path + " " + imagePath;

                    Process myProcess = new Process();
                    myProcess.StartInfo = myProcessStartInfo;

                    Console.WriteLine("Calling Python script with arguments {0}", imagePath);

                    myProcess.Start();

                    StreamReader myStreamReader = myProcess.StandardOutput;
                    value = myStreamReader.ReadLine();

                    myProcess.WaitForExit();
                    myProcess.Close();

                    // write the output we got from python app 
                    Console.WriteLine("Value received from script: " + value);
                    if(value != null)
                        UpdateValue(value);
                    loadedImageBox.Source = new BitmapImage(new Uri(op.FileName));
                    window_2_on();
                    predicting.Visibility = Visibility.Hidden;
                }
            }
            else
            {
                window_1_on();
                predicting.Visibility = Visibility.Hidden;
            }
        }

        private void UpdateValue(string value)
        {
            progressBar.Minimum = 0;
            progressBar.Maximum = 100;
            string status = "";
            double v = ConvertToDouble(value);
            if(v > 0.5)
            {
                status = "ORIGINAL";
                progressBar.Foreground = Brushes.Green;
            }
            else
            {
                status = "RETOUCHED";
                progressBar.Foreground = Brushes.Red;
                v = 1 - v;
            }
            v = v * 100;
            int result = (int)v;
            accuracyValue.Text = result + "% " + status;
            progressBar.Value = result;
            
        }

        private void againButton_Click(object sender, RoutedEventArgs e)
        {
            window_2_off();
            window_1_on();
        }

        private double ConvertToDouble(string s)
        {
            char systemSeparator = Thread.CurrentThread.CurrentCulture.NumberFormat.CurrencyDecimalSeparator[0];
            double result = 0;
            try
            {
                if (s != null)
                    if (!s.Contains(","))
                        result = double.Parse(s, CultureInfo.InvariantCulture);
                    else
                        result = Convert.ToDouble(s.Replace(".", systemSeparator.ToString()).Replace(",", systemSeparator.ToString()));
            }
            catch (Exception e)
            {
                try
                {
                    result = Convert.ToDouble(s);
                }
                catch
                {
                    try
                    {
                        result = Convert.ToDouble(s.Replace(",", ";").Replace(".", ",").Replace(";", "."));
                    }
                    catch
                    {
                        throw new Exception("Wrong string-to-double format");
                    }
                }
            }
            return result;
        }
    }
}
