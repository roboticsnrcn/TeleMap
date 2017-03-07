using System;
using System.Threading;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;

// adding the serial comm for testing the SVH SCHUNK
using System.IO.Ports;
using System.Windows.Threading;
using System.Windows.Documents;
using System.Text;
//using the wrapper for the VMG glove
using GloveWrapper;

namespace GloveGripperUI
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        #region Declerations
        public const int PKG_QUAT_FINGER = 1;
        public const int PKG_RAW_FINGER = 3;
        public const int USB_CONNECTED = 4;
        public const int VIBRO_THUMB = 0;
        public const int VIBRO_INDEX = 1;
        public const int VIBRO_MIDDLE = 3;
        public const int VIBRO_RING = 2;
        public const int VIBRO_LITTLE = 4;
        GloveVMG30_Wrapper myGlv;
        VMG30 vmg30;
        StreamingC streaming;
        GlvFeedBackC glv_feedback;

        int comport = 5, timeout = 60000, checkFB;
        int ThumbFeedBackVal, IndexFeedBackVal, MiddleFeedBackVal, RingFeedBackVal, LittleFeedBackVal;
        private Thread StreamData;
        private Thread GlvFeedback;

        //Richtextbox
        FlowDocument mcFlowDoc = new FlowDocument();
        Paragraph para = new Paragraph();
        //Serial
        SerialPort mySerial = new SerialPort();
        string received_data;
        
        #endregion

        #region BinderClass
        private Binding CreateBinder(object Source, string path)
        {
            Binding myBinding = new Binding(path);
            myBinding.Source = Source;
            myBinding.Mode = BindingMode.TwoWay;
            myBinding.StringFormat = "{0:F2}";
            return myBinding;
        }

        private void BindLabel(Label LabelToBind, Binding Binder)
        {
            LabelToBind.SetBinding(Label.ContentProperty, Binder);
        }
        private void BindTextBox(TextBox TextboxToBind, Binding Binder)
        {
            TextboxToBind.SetBinding(TextBox.TextProperty, Binder);
        }

        private void BindObjectToLabel(object Source, string path, Label label)
        {
            BindLabel(label, CreateBinder(Source, path));
        }

        private void SchunkCOMConnect_Btn_Click(object sender, RoutedEventArgs e)
        {
            if (SchunkCOMConnect_Btn.Content == "Connect")
            {
                //Set up Serial communication for SVH SCHUNK gripper
                mySerial.PortName = Comm_Port_Names.Text; //COM Port names
                mySerial.BaudRate = Convert.ToInt32(Baud_Rates.Text); //Baud Rates
                mySerial.Handshake = Handshake.None; //no handshake
                mySerial.Parity = Parity.None; //no parity
                mySerial.DataBits = 8;
                mySerial.StopBits = StopBits.One;
                mySerial.ReadTimeout = 200;
                mySerial.WriteTimeout = 50;
                mySerial.Open();

                //Sets new button state and Creates function call on data received
                SchunkCOMConnect_Btn.Content = "Disconnect";
                mySerial.DataReceived += new System.IO.Ports.SerialDataReceivedEventHandler(Receive);
            }
            else
            {
                try //in case serial port is not open close
                {
                    mySerial.Close();
                    SchunkCOMConnect_Btn.Content = "Connect";
                }
                catch
                {
                }
            }
        }

        #region receiving data
        private delegate void UpdateUiTextDelegate(string text);
        private void Receive(object sender, System.IO.Ports.SerialDataReceivedEventArgs e)
        {
            // Collecting the characters received to our 'buffer' (string).
            received_data = mySerial.ReadExisting();
            Dispatcher.Invoke(DispatcherPriority.Send, new UpdateUiTextDelegate(WriteData), received_data);
        }

        private void WriteData(string text)
        {
            // Assign the value of the recieved_data to the RichTextBox.
            para.Inlines.Add(text);
            mcFlowDoc.Blocks.Add(para);
            CommData.Document = mcFlowDoc;
        }
        #endregion

        #region Sending        

        private void Send_Data(object sender, RoutedEventArgs e)
        {
            SerialCmdSend(SerialData.Text);
            SerialData.Text = "";
        }
        public void SerialCmdSend(string data)
        {
            if (mySerial.IsOpen)
            {
                try
                {
                    // Send the binary data out the port
                    byte[] hexstring = Encoding.ASCII.GetBytes(data);
                    //There is a intermitant problem that I came across
                    //If I write more than one byte in succesion without a 
                    //delay the PIC i'm communicating with will Crash
                    //I expect this id due to PC timing issues ad they are
                    //not directley connected to the COM port the solution
                    //Is a ver small 1 millisecound delay between chracters
                    foreach (byte hexval in hexstring)
                    {
                        byte[] _hexval = new byte[] { hexval }; // need to convert byte to byte[] to write
                        mySerial.Write(_hexval, 0, 1);
                        Thread.Sleep(1);
                    }
                }
                catch (Exception ex)
                {
                    para.Inlines.Add("Failed to SEND" + data + "\n" + ex + "\n");
                    mcFlowDoc.Blocks.Add(para);
                    CommData.Document = mcFlowDoc;
                }
            }
            else
            {
            }
        }

        #endregion

        private void BindObjectToTextBox(object Source, string path, TextBox textbox)
        {
            BindTextBox(textbox, CreateBinder(Source, path));
        }

        #endregion



        public MainWindow()
        {
            InitializeComponent();

            myGlv = new GloveVMG30_Wrapper();
            vmg30 = new VMG30();
            streaming = new StreamingC(vmg30, myGlv);
            glv_feedback = new GlvFeedBackC(vmg30, myGlv);
            //myBinding.Source = myGlv.Thumb0[0];
            BindObjectToLabel(vmg30, "Thumb3[0]", xLabel_Thumb);
            BindObjectToLabel(vmg30, "Thumb3[1]", yLabel_Thumb);
            BindObjectToLabel(vmg30, "Thumb3[2]", zLabel_Thumb);
            BindObjectToLabel(vmg30, "Index3[0]", xLabel_Index);
            BindObjectToLabel(vmg30, "Index3[1]", yLabel_Index);
            BindObjectToLabel(vmg30, "Index3[2]", zLabel_Index);
            BindObjectToLabel(vmg30, "Middle3[0]", xLabel_Middle);
            BindObjectToLabel(vmg30, "Middle3[1]", yLabel_Middle);
            BindObjectToLabel(vmg30, "Middle3[2]", zLabel_Middle);
            BindObjectToLabel(vmg30, "Ring3[0]", xLabel_Ring);
            BindObjectToLabel(vmg30, "Ring3[1]", yLabel_Ring);
            BindObjectToLabel(vmg30, "Ring3[2]", zLabel_Ring);
            BindObjectToLabel(vmg30, "Little3[0]", xLabel_Little);
            BindObjectToLabel(vmg30, "Little3[1]", yLabel_Little);
            BindObjectToLabel(vmg30, "Little3[2]", zLabel_Little);
            //binding the finger's bending values to the wpf elements
            BindObjectToLabel(vmg30, "FingerBend[0]", FB1Label_Thumb);
            BindObjectToLabel(vmg30, "FingerBend[1]", FB2Label_Thumb);
            BindObjectToLabel(vmg30, "FingerBend[2]", FB1Label_Index);
            BindObjectToLabel(vmg30, "FingerBend[3]", FB2Label_Index);
            BindObjectToLabel(vmg30, "FingerBend[4]", FB1Label_Middle);
            BindObjectToLabel(vmg30, "FingerBend[5]", FB2Label_Middle);
            BindObjectToLabel(vmg30, "FingerBend[6]", FB1Label_Ring);
            BindObjectToLabel(vmg30, "FingerBend[7]", FB2Label_Ring);
            BindObjectToLabel(vmg30, "FingerBend[8]", FB1Label_Little);
            BindObjectToLabel(vmg30, "FingerBend[9]", FB2Label_Little);
            //binding the finger's abduction valus to the wpf elements
            BindObjectToLabel(vmg30, "FingerAbd[0]", FABD1Label);
            BindObjectToLabel(vmg30, "FingerAbd[1]", FABD2Label);
            BindObjectToLabel(vmg30, "FingerAbd[2]", FABD3Label);
            BindObjectToLabel(vmg30, "FingerAbd[3]", FABD4Label);
            //binding the ThumbCO and PalmArch values to the wpf elements
            BindObjectToLabel(vmg30, "ThumbCO", ThumbCOLabel);
            BindObjectToLabel(vmg30, "PalmArch", PalmArchLabel);
            //binding the roll,pitch,yaw hand and wrist valus to the wpf elements
            BindObjectToLabel(vmg30, "RPY_Wrist[0]", RollLabel_Wrist);
            BindObjectToLabel(vmg30, "RPY_Wrist[1]", PitchLabel_Wrist);
            BindObjectToLabel(vmg30, "RPY_Wrist[2]", YawLabel_Wrist);
            BindObjectToLabel(vmg30, "RPY_Hand[0]", RollLabel_Hand);
            BindObjectToLabel(vmg30, "RPY_Hand[1]", PitchLabel_Hand);
            BindObjectToLabel(vmg30, "RPY_Hand[2]", YawLabel_Hand);
            //binding the finger tip's pressure values to the wpf elements
            BindObjectToLabel(vmg30, "Press[0]", PressLabel_Thumb);
            BindObjectToLabel(vmg30, "Press[1]", PressLabel_Index);
            BindObjectToLabel(vmg30, "Press[2]", PressLabel_Middle);
            BindObjectToLabel(vmg30, "Press[3]", PressLabel_Ring);
            BindObjectToLabel(vmg30, "Press[4]", PressLabel_Little);
            //binding the finger feedback values from the vibration motors
            BindObjectToTextBox(vmg30, "FingerFeedBackVal[0]", ThumbVal);
            BindObjectToTextBox(vmg30, "FingerFeedBackVal[1]", IndexVal);
            BindObjectToTextBox(vmg30, "FingerFeedBackVal[2]", MiddleVal);
            BindObjectToTextBox(vmg30, "FingerFeedBackVal[3]", RingVal);
            BindObjectToTextBox(vmg30, "FingerFeedBackVal[4]", LittleVal);

            //overwrite to ensure correct state
            SchunkCOMConnect_Btn.Content = "Connect";
        }

        private void StreamBtn_Click(object sender, RoutedEventArgs e)
        {
            //starting a new thread to perform tracking of x,y,z while running
            StreamData = new Thread(() => streaming.Track());
            StreamData.Start(); // starting the thread
            StreamBtn.IsEnabled = false;
        }

// in the meantime i'll keep the Feedback and stop feedback buttons but i can delete it
        private void FeedBackBtn_Click(object sender, RoutedEventArgs e)
        {
            // starting a new thread to get feedback

            // entering the feedback values obtained using textbox to the feedback function
            int.TryParse(IndexVal.Text, out IndexFeedBackVal);
            int.TryParse(MiddleVal.Text, out MiddleFeedBackVal);
            int.TryParse(RingVal.Text, out RingFeedBackVal);
            int.TryParse(LittleVal.Text, out LittleFeedBackVal);
            int.TryParse(ThumbVal.Text, out ThumbFeedBackVal);

            checkFB = myGlv.GetFeedback(VIBRO_THUMB, ThumbFeedBackVal);
            checkFB = myGlv.GetFeedback(VIBRO_INDEX, IndexFeedBackVal);
            checkFB = myGlv.GetFeedback(VIBRO_MIDDLE, MiddleFeedBackVal);
            checkFB = myGlv.GetFeedback(VIBRO_RING, RingFeedBackVal);
            checkFB = myGlv.GetFeedback(VIBRO_LITTLE, LittleFeedBackVal);
            //}
        }

        private void StpFeedBackBtn_Click(object sender, RoutedEventArgs e)
        {
            checkFB = myGlv.GetFeedback(VIBRO_THUMB, 0);
            checkFB = myGlv.GetFeedback(VIBRO_INDEX, 0);
            checkFB = myGlv.GetFeedback(VIBRO_MIDDLE, 0);
            checkFB = myGlv.GetFeedback(VIBRO_RING, 0);
            checkFB = myGlv.GetFeedback(VIBRO_LITTLE, 0);
        }

        private void StartConnectionBtn_Click(object sender, RoutedEventArgs e)
        {
            // a connection must be done using PKG_QUAT_FINGER if we want to see hand/wrist attitude
            int cs = myGlv.ConnectGlove(comport, PKG_QUAT_FINGER, timeout);
            label.Content = cs;
            if (cs == 4)
            {
                GlvFeedback = new Thread(() => glv_feedback.Vibration());
                GlvFeedback.Start(); //starting the Feedback Thread
            }
        }
    }
}
