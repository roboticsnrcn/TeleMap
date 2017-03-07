using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using GloveWrapper;

namespace ConsoleApplication1
{
    class Program
    {
        #region consts
        private const int PKG_QUAT_FINGER = 1;
        private const int PKG_RAW_FINGER = 3;

        GloveVMG30_Wrapper myGlv = new GloveVMG30_Wrapper();
        private int comport = 5, timeout = 60000;
        static void Main(string[] args)
        {
            myGlv.ConnectGlove(comport, PKG_QUAT_FINGER, timeout);
        }
    }
}
