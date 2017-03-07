// GloveVMG30_Wrapper.h

#pragma once

#include "VMG30.h"

#include "C:\Users\BAKARA\Documents\Visual Studio 2015\Projects\GloveVMG30\GloveVMG30\GloveVMG30.h"
#include "C:\Users\BAKARA\Documents\Visual Studio 2015\Projects\GloveVMG30\GloveVMG30\GloveVMG30.cpp"
//#include "C:\Users\BAKARA\Dropbox\teleoperation\mapping\VMG\VMGx0_SDK_1_2_2\GloveVMG30\GloveVMG30\GloveVMG30.h"
//#include "C:\Users\BAKARA\Dropbox\teleoperation\mapping\VMG\VMGx0_SDK_1_2_2\GloveVMG30\GloveVMG30\GloveVMG30.cpp"

//#define VMG_POS_ARR_SIZE 22
#define FINGER_POS_ARR_SIZE 3
#define FINGER_BEND_ARR_SIZE 10
#define FINGER_ABD_ARR_SIZE 4
#define FINGER_PRESS_ARR_SIZE 5

using namespace System;

namespace GloveWrapper {

	public ref class GloveVMG30_Wrapper
	{
	public:
		// constructor
		GloveVMG30_Wrapper();
		
		//wrapper methods
		int ConnectGlove(int comport, int StreamMode, long timeout);
		int DisconnectGlove();
		void StreamInfo();
		
		//void GetXPos();
		//void GetYPos();
		//void GetZPos();

		void GetHandPos();
		void GetPressInfo();
		int GetFeedback(int Finger, int Intensity);

//changed the structure instead of that to the structure shown above
		//array<double>^ GetYPos();
		//array<double>^ GetZPos();

		//array<double>^ xData = gcnew array<double>(VMG_POS_ARR_SIZE);
		//array<double>^ yData = gcnew array<double>(VMG_POS_ARR_SIZE);
		//array<double>^ zData = gcnew array<double>(VMG_POS_ARR_SIZE);

		array<double>^ Thumb0 = gcnew array<double>(FINGER_POS_ARR_SIZE);
		array<double>^ Thumb1 = gcnew array<double>(FINGER_POS_ARR_SIZE);
		array<double>^ Thumb2 = gcnew array<double>(FINGER_POS_ARR_SIZE);
		array<double>^ Thumb3 = gcnew array<double>(FINGER_POS_ARR_SIZE);
		array<double>^ Index0 = gcnew array<double>(FINGER_POS_ARR_SIZE);
		array<double>^ Index1 = gcnew array<double>(FINGER_POS_ARR_SIZE);
		array<double>^ Index2 = gcnew array<double>(FINGER_POS_ARR_SIZE);
		array<double>^ Index3 = gcnew array<double>(FINGER_POS_ARR_SIZE);
		array<double>^ Middle0 = gcnew array<double>(FINGER_POS_ARR_SIZE);
		array<double>^ Middle1 = gcnew array<double>(FINGER_POS_ARR_SIZE);
		array<double>^ Middle2 = gcnew array<double>(FINGER_POS_ARR_SIZE);
		array<double>^ Middle3 = gcnew array<double>(FINGER_POS_ARR_SIZE);
		array<double>^ Ring0 = gcnew array<double>(FINGER_POS_ARR_SIZE);
		array<double>^ Ring1 = gcnew array<double>(FINGER_POS_ARR_SIZE);
		array<double>^ Ring2 = gcnew array<double>(FINGER_POS_ARR_SIZE);
		array<double>^ Ring3 = gcnew array<double>(FINGER_POS_ARR_SIZE);
		array<double>^ Little0 = gcnew array<double>(FINGER_POS_ARR_SIZE);
		array<double>^ Little1 = gcnew array<double>(FINGER_POS_ARR_SIZE);
		array<double>^ Little2 = gcnew array<double>(FINGER_POS_ARR_SIZE);
		array<double>^ Little3 = gcnew array<double>(FINGER_POS_ARR_SIZE);
		array<double>^ Wrist = gcnew array<double>(FINGER_POS_ARR_SIZE);
		array<double>^ Hand = gcnew array<double>(FINGER_POS_ARR_SIZE);
		array<double>^ FingerBend = gcnew array<double>(FINGER_BEND_ARR_SIZE);
		array<double>^ FingerAbd = gcnew array<double>(FINGER_ABD_ARR_SIZE);
		array<double>^ RPY_Wrist = gcnew array<double>(FINGER_POS_ARR_SIZE);
		array<double>^ RPY_Hand = gcnew array<double>(FINGER_POS_ARR_SIZE);
		array<double>^ Press = gcnew array<double>(FINGER_PRESS_ARR_SIZE);


		// public variable
		double initVal, ThumbCO, PalmArch;
		 
		int ConnStat;

	private:
		GloveVMG30 *myGlove;

	};
}


