#include "GloveVMG30.h"
#include <stdio.h>
#include "VMG30.h"
void main() {
	GloveVMG30 MyGlv;
	int comport = 5;
	long timeout = 60000; //ms

						  // a connection must be done using PKG_QUAT_FINGER
	int ConnStat = MyGlv.ConnectGlove(comport, PKG_QUAT_FINGER, timeout);



	//MyGlv.StreamInfo("THUMB3", ConnStat); 
	MyGlv.StreamInfo(); 

	fprintf(stderr, "THUMB x0: %.1f y0: %.1f z0: %.1f \n",
		MyGlv.Thumb0[0], MyGlv.Thumb0[1], MyGlv.Thumb0[2]);

	fprintf(stderr, "THUMB x3: %.1f y3: %.1f z3: %.1f \n",
		MyGlv.Thumb3[0], MyGlv.Thumb3[1], MyGlv.Thumb3[2]);

	fprintf(stderr, "INDEX x0: %.1f y0: %.1f z0: %.1f \n",
		MyGlv.Index0[0], MyGlv.Index0[1], MyGlv.Index0[2]);

	fprintf(stderr, "INDEX x3: %.1f y3: %.1f z3: %.1f \n",
		MyGlv.Index3[0], MyGlv.Index3[1], MyGlv.Index3[2]);

	fprintf(stderr, "MIDDLE x0: %.1f y0: %.1f z0: %.1f \n",
		MyGlv.Middle0[0], MyGlv.Middle0[1], MyGlv.Middle0[2]);

	fprintf(stderr, "MIDDLE x3: %.1f y3: %.1f z3: %.1f \n",
		MyGlv.Middle3[0], MyGlv.Middle3[1], MyGlv.Middle3[2]);

	fprintf(stderr, "RING x0: %.1f y0: %.1f z0: %.1f \n",
		MyGlv.Ring0[0], MyGlv.Ring0[1], MyGlv.Ring0[2]);

	fprintf(stderr, "RING x3: %.1f y3: %.1f z3: %.1f \n",
		MyGlv.Ring3[0], MyGlv.Ring3[1], MyGlv.Ring3[2]);

	fprintf(stderr, "LITTLE x0: %.1f y0: %.1f z0: %.1f \n",
		MyGlv.Little0[0], MyGlv.Little0[1], MyGlv.Little0[2]);

	fprintf(stderr, "LITTLE x3: %.1f y3: %.1f z3: %.1f \n",
		MyGlv.Little3[0], MyGlv.Little3[1], MyGlv.Little3[2]);

	fprintf(stderr, "WRIST x: %.1f y: %.1f z: %.1f \n",
		MyGlv.Wrist[0], MyGlv.Wrist[1], MyGlv.Wrist[2]);

	fprintf(stderr, "HAND x: %.1f y: %.1f z: %.1f \n",
		MyGlv.Hand[0], MyGlv.Hand[1], MyGlv.Hand[2]);
	// testing the finger's bending values -> need to send that to the wrapper
	fprintf(stderr, "THUMB 1: %.1f THUMB 2:%.1f \n",
		MyGlv.FingerBend[0], MyGlv.FingerBend[1]);
	fprintf(stderr, "INDEX 1: %.1f INDEX 2:%.1f \n",
		MyGlv.FingerBend[2], MyGlv.FingerBend[3]);
	fprintf(stderr, "MIDDLE 1: %.1f MIDDLE 2:%.1f \n",
		MyGlv.FingerBend[4], MyGlv.FingerBend[5]);
	fprintf(stderr, "RING 1: %.1f RING 2:%.1f \n",
		MyGlv.FingerBend[6], MyGlv.FingerBend[7]);
	fprintf(stderr, "LITTLE 1: %.1f LITTLE 2:%.1f \n",
		MyGlv.FingerBend[8], MyGlv.FingerBend[9]);
	// testing the finger's abduction values and thumbcross-over and palmarch values
	fprintf(stderr, "THUMB to INDEX: %.1f \n",
		MyGlv.FingerAbd[0]);
	fprintf(stderr, "INDEX to MIDDLE: %.1f \n",
		MyGlv.FingerAbd[1]);
	fprintf(stderr, "MIDDLE to RING: %.1f \n",
		MyGlv.FingerAbd[2]);
	fprintf(stderr, "RING to LITTLE: %.1f \n",
		MyGlv.FingerAbd[3]);
	fprintf(stderr, "THUMB CROSS OVER: %.1f \n", MyGlv.ThumbCO);
	fprintf(stderr, "PALM ARCH: %.1f \n", MyGlv.PalmArch);
	// testing the wrist and hand's yaw/pitch/roll values
	fprintf(stderr, "WRIST ROLL: %.1f PITCH:%.1f YAW:%.1f\n", MyGlv.RPY_Wrist[0], MyGlv.RPY_Wrist[1], MyGlv.RPY_Wrist[2]);
	fprintf(stderr, "HAND ROLL: %.1f PITCH:%.1f YAW:%.1f\n", MyGlv.RPY_Hand[0], MyGlv.RPY_Hand[1], MyGlv.RPY_Hand[2]);
	// testing the finger tip's pressure values
	fprintf(stderr, "THUMB Pressure: %.1f \n", MyGlv.Press[0]);
	fprintf(stderr, "INDEX Pressure: %.1f \n", MyGlv.Press[1]);
	fprintf(stderr, "MIDDLE Pressure: %.1f \n", MyGlv.Press[2]);
	fprintf(stderr, "RING Pressure: %.1f \n", MyGlv.Press[3]);
	fprintf(stderr, "LITTLE Pressure: %.1f \n", MyGlv.Press[4]);
	int i;
	int FBCheck;
	//while (true)
	//{
	//	Sleep(30);
	//	FBCheck=MyGlv.GetFeedback(0, 0);
	//	printf("%d", FBCheck);
	//}
	//if (MyGlv.Press[0] < 15.0)
	//{
	for (i = 0; i < 100; i++)
	{
		//testVibro = VMGloveSetVibrotactile(gloveH, VIBRO_AUX, 100);
		Sleep(30);
		FBCheck = MyGlv.GetFeedback(0, 100);
		FBCheck = MyGlv.GetFeedback(1, 0);
		FBCheck = MyGlv.GetFeedback(2, 0);
		FBCheck = MyGlv.GetFeedback(3, 100);
		FBCheck = MyGlv.GetFeedback(4, 0);

	}

	//test of ramp ->0-100-0 in the vibration
	int testVibro;

	for (i = 0; i < 100; i++)
	{
		//testVibro = VMGloveSetVibrotactile(gloveH, VIBRO_AUX, 100);
		Sleep(30);
		testVibro = MyGlv.GetFeedback(VIBRO_LITTLE, i);
		testVibro = MyGlv.GetFeedback(VIBRO_RING, i);
		testVibro = MyGlv.GetFeedback(VIBRO_INDEX, i);
		testVibro = MyGlv.GetFeedback(VIBRO_THUMB, i);

	}
	Sleep(1000);
	for (i = 0; i < 100; i++)
	{
		//testVibro = VMGloveSetVibrotactile(gloveH, VIBRO_AUX, 100);
		Sleep(30);
		testVibro = MyGlv.GetFeedback(VIBRO_LITTLE, 100 - i);
		testVibro = MyGlv.GetFeedback(VIBRO_RING, 100 - i);
		testVibro = MyGlv.GetFeedback(VIBRO_INDEX, 100 - i);
		testVibro = MyGlv.GetFeedback(VIBRO_THUMB, 100 - i);
	}
	//}
	//else {
	//	if ((MyGlv.Press[0] > 15.0) && (MyGlv.Press[0] < 80.0))
	//	{
	//		for (i = 0; i < 100; i++)
	//		{
	//			//testVibro = VMGloveSetVibrotactile(gloveH, VIBRO_AUX, 100);
	//			Sleep(30);
	//			FBCheck = MyGlv.GetFeedback(0, 100 - i);
	//			FBCheck = MyGlv.GetFeedback(1, 100 - i);
	//			FBCheck = MyGlv.GetFeedback(2, 100 - i);
	//			FBCheck = MyGlv.GetFeedback(3, 100 - i);
	//			FBCheck = MyGlv.GetFeedback(4, 100 - i);
	//		}

	//	}

	//	else
	//	{
	//		for (i = 0; i < 100; i++)
	//		{
	//			//testVibro = VMGloveSetVibrotactile(gloveH, VIBRO_AUX, 100);
	//			Sleep(30);
	//			FBCheck = MyGlv.GetFeedback(0, 0);
	//			FBCheck = MyGlv.GetFeedback(1, 0);
	//			FBCheck = MyGlv.GetFeedback(2, 0);
	//			FBCheck = MyGlv.GetFeedback(3, 0);
	//			FBCheck = MyGlv.GetFeedback(4, 0);

	//		}
	//	}
	//}

	int a = 1;
	//place to put breakpt for checking the code
};