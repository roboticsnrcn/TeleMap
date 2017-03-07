using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

using GloveWrapper;

namespace GloveGripperUI
{
    public partial class Form1 : Form
    {
        GloveVMG30_Wrapper myGlv = new GloveVMG30_Wrapper();
        private int comport = 5, timeout = 60000;
        public Form1()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            myGlv.ConnectGlove(comport, 1, timeout);
        }
    }
}
