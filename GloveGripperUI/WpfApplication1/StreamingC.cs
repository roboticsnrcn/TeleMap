using GloveWrapper;
using System.Threading;


namespace GloveGripperUI
{
    class StreamingC
    {

        private VMG30 vmg30;
        private GloveVMG30_Wrapper myGlv;

        public StreamingC(VMG30 vmg30, GloveVMG30_Wrapper myGlv)
        {
            this.vmg30 = vmg30;
            this.myGlv = myGlv;
        }

        public void Track()
        {
            while (true)
            {
                myGlv.StreamInfo();
                Thread.Sleep(1);
                myGlv.GetHandPos();
                myGlv.GetPressInfo();

                //passing variables obtained using myGlv.GetHandPos and myGlv.GetPress -> vmg30 struct using getters/setters 
                #region HandPosInfo
                vmg30.Thumb0 = myGlv.Thumb0;
                vmg30.Thumb1 = myGlv.Thumb1;
                vmg30.Thumb2 = myGlv.Thumb2;
                vmg30.Thumb3 = myGlv.Thumb3;

                vmg30.Index0 = myGlv.Index0;
                vmg30.Index1 = myGlv.Index1;
                vmg30.Index2 = myGlv.Index2;
                vmg30.Index3 = myGlv.Index3;

                vmg30.Middle0 = myGlv.Middle0;
                vmg30.Middle0 = myGlv.Middle1;
                vmg30.Middle2 = myGlv.Middle2;
                vmg30.Middle3 = myGlv.Middle3;

                vmg30.Ring0 = myGlv.Ring0;
                vmg30.Ring1 = myGlv.Ring1;
                vmg30.Ring2 = myGlv.Ring2;
                vmg30.Ring3 = myGlv.Ring3;

                vmg30.Little0 = myGlv.Little0;
                vmg30.Little0 = myGlv.Little1;
                vmg30.Little2 = myGlv.Little2;
                vmg30.Little3 = myGlv.Little3;

                vmg30.Wrist = myGlv.Wrist;
                vmg30.Hand = myGlv.Hand;

                vmg30.FingerBend = myGlv.FingerBend;
                vmg30.FingerAbd = myGlv.FingerAbd;

                vmg30.RPY_Wrist = myGlv.RPY_Wrist;
                vmg30.RPY_Hand = myGlv.RPY_Hand;

                vmg30.ThumbCO = myGlv.ThumbCO;
                vmg30.PalmArch = myGlv.PalmArch;
                #endregion

                #region PressureInfo
                vmg30.Press = myGlv.Press;
                #endregion
            }

        }
    }
}
