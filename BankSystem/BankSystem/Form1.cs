using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Threading;

namespace BankSystem
{
    public partial class Form1 : Form
    {
        Thread th;
        public Form1()
        {
            InitializeComponent();
        }

        private void textBox1_TextChanged(object sender, EventArgs e)
        {
           
        }
        //function for threading 

        private void opens(object obj)
        {
            Application.Run(new Form2());
        }

        private void button1_Click(object sender, EventArgs e)
        {
            if (textBox1.Text == "Mikis" && textBox2.Text == "elkin")
            {
                this.Close();
                th = new Thread(opens);
                th.SetApartmentState(ApartmentState.STA);
                th.Start();
            }
            else
            {
                string error_message = "Wrong data. Try again.";
                MessageBox.Show(error_message);
            }
        }
    }
}
