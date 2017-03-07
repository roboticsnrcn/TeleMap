using GloveWrapper;
using System.Threading;

namespace GloveGripperUI
{
    class GlvFeedBackC
    {
        private VMG30 vmg30;
        private GloveVMG30_Wrapper myGlv;

        public GlvFeedBackC(VMG30 vmg30, GloveVMG30_Wrapper myGlv)
        {
            this.vmg30 = vmg30;
            this.myGlv = myGlv;
        }

        public void Vibration()
        {
            while(true) 
            {
                myGlv.GetFeedback(0, vmg30.FingerFeedBackVal[0]);
                myGlv.GetFeedback(1, vmg30.FingerFeedBackVal[1]);
                myGlv.GetFeedback(3, vmg30.FingerFeedBackVal[2]);
                myGlv.GetFeedback(2, vmg30.FingerFeedBackVal[3]);
                myGlv.GetFeedback(4, vmg30.FingerFeedBackVal[4]);
                Thread.Sleep(1);

                //passing variables obtained using myGlv.GetFeedBack -> vmg30 struct using getters/setters 
            }
        }
    }
}
