using GloveWrapper;
using System;
using System.ComponentModel;
using System.Runtime.CompilerServices;


namespace GloveGripperUI
{
    class VMG30 : INotifyPropertyChanged
    {
        #region Declerations
        private double[] thumb0;
        private double[] thumb1;
        private double[] thumb2;
        private double[] thumb3;

        private double[] index0;
        private double[] index1;
        private double[] index2;
        private double[] index3;

        private double[] middle0;
        private double[] middle1;
        private double[] middle2;
        private double[] middle3;

        private double[] ring0;
        private double[] ring1;
        private double[] ring2;
        private double[] ring3;

        private double[] little0;
        private double[] little1;
        private double[] little2;
        private double[] little3;

        private double[] wrist;
        private double[] hand;

        private double[] fingerBend;
        private double[] fingerAbd;

        private double[] rpywrist;
        private double[] rpyhand;
        private double[] press;

        private double thumbCO;
        private double palmArch;

        private int[] fingerFeedBackVal = new int[5]; //defining array of 5 int for the feedback from the glove

        #endregion

        #region getters/setters
        public int[] FingerFeedBackVal //feedback value's array
        {
            get
            {
                return fingerFeedBackVal;
            }
            set
            {
                fingerFeedBackVal = value;
                NotifyPropertyChanged();
            }
        }

        public double[] Hand
        {
            get
            {
                return hand;
            }
            set
            {
                hand = value;
                NotifyPropertyChanged();
            }
        }

        public double[] Index0
        {
            get
            {
                return index0;
            }
            set
            {
                index0 = value;
                NotifyPropertyChanged();
            }
        }

        public double[] Index1
        {
            get
            {
                return index1;
            }
            set
            {
                index1 = value;
                NotifyPropertyChanged();
            }
        }

        public double[] Index2
        {
            get
            {
                return index2;
            }
            set
            {
                index2 = value;
                NotifyPropertyChanged();
            }
        }

        public double[] Index3
        {
            get
            {
                return index3;
            }
            set
            {
                index3 = value;
                NotifyPropertyChanged();
            }
        }

        //public double initVal;
        public double[] Little0
        {
            get
            {
                return little0;
            }
            set
            {
                little0 = value;
                NotifyPropertyChanged();
            }
        }

        public double[] Little1
        {
            get
            {
                return little1;
            }
            set
            {
                little1  = value;
                NotifyPropertyChanged();
            }
        }

        public double[] Little2
        {
            get
            {
                return little2;
            }
            set
            {
                little2 = value;
                NotifyPropertyChanged();
            }
        }

        public double[] Little3
        {
            get
            {
                return little3;
            }
            set
            {
                little3 = value;
                NotifyPropertyChanged();
            }
        }

        public double[] Middle0
        {
            get
            {
                return middle0;
            }
            set
            {
                middle0 = value;
                NotifyPropertyChanged();
            }
        }

        public double[] Middle1
        {
            get
            {
                return middle1;
            }
            set
            {
                middle1 = value;
                NotifyPropertyChanged();
            }
        }

        public double[] Middle2
        {
            get
            {
                return middle2;
            }
            set
            {
                middle2 = value;
                NotifyPropertyChanged();
            }
        }

        public double[] Middle3
        {
            get
            {
                return middle3;
            }
            set
            {
                middle3 = value;
                NotifyPropertyChanged();
            }
        }

        public double[] Ring0
        {
            get
            {
                return ring0;
            }
            set
            {
                ring0 = value;
                NotifyPropertyChanged();
            }
        }

        public double[] Ring1
        {
            get
            {
                return ring1;
            }
            set
            {
                ring1 = value;
                NotifyPropertyChanged();
            }
        }

        public double[] Ring2
        {
            get
            {
                return ring2;
            }
            set
            {
                ring2 = value;
                NotifyPropertyChanged();
            }
        }

        public double[] Ring3
        {
            get
            {
                return ring3;
            }
            set
            {
                ring3 = value;
                NotifyPropertyChanged();
            }
        }

        public double[] Thumb0 {
            get
            {
                return thumb0;
            }
            set
            {
                thumb0 = value;
                NotifyPropertyChanged();
            }
        }

        public double[] Thumb1{
            get
            {
                return thumb1;
            }
            set
            {
                thumb1 = value;
                NotifyPropertyChanged();
            }
        }

        public double[] Thumb2
        {
            get
            {
                return thumb2;
            }
            set
            {
                thumb2 = value;
                NotifyPropertyChanged();
            }
        }

        public double[] Thumb3
        {
            get
            {
                return thumb3;
            }
            set
            {
                thumb3 = value;
                NotifyPropertyChanged();
            }
        }

        public double[] Wrist
        {
            get
            {
                return wrist;
            }
            set
            {
                wrist = value;
                NotifyPropertyChanged();
            }
        }

        public double[] FingerBend
        {
            get
            {
                return fingerBend;
            }
            set
            {
                fingerBend = value;
                NotifyPropertyChanged();
            }
        }

        public double[] FingerAbd
        {
            get
            {
                return fingerAbd;
            }
            set
            {
                fingerAbd = value;
                NotifyPropertyChanged();
            }
        }

        public double[] RPY_Wrist
        {
            get
            {
                return rpywrist;
            }
            set
            {
                rpywrist = value;
                NotifyPropertyChanged();
            }
        }

        public double[] RPY_Hand
        {
            get
            {
                return rpyhand;
            }
            set
            {
                rpyhand = value;
                NotifyPropertyChanged();
            }
        }

        public double ThumbCO
        {
            get
            {
                return thumbCO;
            }
            set
            {
                thumbCO = value;
                NotifyPropertyChanged();
            }
        }

        public double PalmArch
        {
            get
            {
                return palmArch;
            }
            set
            {
                palmArch = value;
                NotifyPropertyChanged();
            }
        }

        public double[] Press
        {
            get
            {
                return press;
            }
            set
            {
                press = value;
                NotifyPropertyChanged();
            }
        }

        #endregion

        public event PropertyChangedEventHandler PropertyChanged;
        // This method is called by the Set accessor of each property.
        // The CallerMemberName attribute that is applied to the optional propertyName
        // parameter causes the property name of the caller to be substituted as an argument.
        private void NotifyPropertyChanged([CallerMemberName] String propertyName = "")
        {
            if (PropertyChanged != null)
            {
                PropertyChanged(this, new PropertyChangedEventArgs(propertyName));
            }
        }
    }

}
