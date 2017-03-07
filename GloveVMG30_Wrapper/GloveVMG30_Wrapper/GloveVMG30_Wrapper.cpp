// This is the main DLL file.

#include "stdafx.h"

#include "VMG30.h"

#include "GloveVMG30_Wrapper.h"

#include "C:\Users\BAKARA\Documents\Visual Studio 2015\Projects\GloveVMG30\GloveVMG30\GloveVMG30.h"
#include "C:\Users\BAKARA\Documents\Visual Studio 2015\Projects\GloveVMG30\GloveVMG30\GloveVMG30.cpp"

#define FINGER_POS_ARR_SIZE 3
#define FINGER_BEND_ARR_SIZE 10
#define FINGER_ABD_ARR_SIZE 4
#define FINGER_PRESS_ARR_SIZE 5


// Constructor implementaion
GloveWrapper::GloveVMG30_Wrapper::GloveVMG30_Wrapper()
{
	myGlove = new GloveVMG30(); //initiate C++ class's instance
}

// Methods implementaion

// Connect Glove
int GloveWrapper::GloveVMG30_Wrapper::ConnectGlove(int comport, int StreamMode, long timeout)
{
	return myGlove->ConnectGlove(comport, StreamMode, timeout);
}
//Disconnect Glove
int GloveWrapper::GloveVMG30_Wrapper::DisconnectGlove()
{
	return myGlove->DisconnectGlove();
}

int GloveWrapper::GloveVMG30_Wrapper::GetFeedback(int Finger, int Intensity) 
{
	return myGlove->GetFeedback(Finger, Intensity);
}

void GloveWrapper::GloveVMG30_Wrapper::StreamInfo()
{
	myGlove->StreamInfo();
}
//
//void GloveWrapper::GloveVMG30_Wrapper::GetXPos()
//{
//	//array<double>^ xData = gcnew array<double>(VMG_POS_ARR_SIZE);
//	double *c = myGlove->xData;
//	for (int i = 0; i < VMG_POS_ARR_SIZE; i++)
//	{
//		xData[i] = *(c + i);
//	}
//}
//
//void GloveWrapper::GloveVMG30_Wrapper::GetYPos()
//{
//	//array<double>^ yData = gcnew array<double>(VMG_POS_ARR_SIZE);
//	double *c = myGlove->yData;
//	for (int i = 0; i < VMG_POS_ARR_SIZE; i++)
//	{
//		yData[i] = *(c + i);
//	}
//}
//
//void GloveWrapper::GloveVMG30_Wrapper::GetZPos()
//{	//array<double>^ 
//	//array<double>^ zData = gcnew array<double>(VMG_POS_ARR_SIZE);
//	double *c = myGlove->zData;
//	for (int i = 0; i < VMG_POS_ARR_SIZE; i++)
//	{
//		zData[i] = *(c + i);
//	}
//	//return zData;
//}
void GloveWrapper::GloveVMG30_Wrapper::GetPressInfo()
{
	double *p = myGlove->Press;
	for (int i = 0; i < FINGER_PRESS_ARR_SIZE; i++)
	{
		Press[i] = *(p + i);
	}
}

void GloveWrapper::GloveVMG30_Wrapper::GetHandPos()
{
	double *c00 = myGlove->Thumb0;
	double *c01 = myGlove->Thumb1;
	double *c02 = myGlove->Thumb2;
	double *c03 = myGlove->Thumb3;
	double *c10 = myGlove->Index0;
	double *c11 = myGlove->Index1;
	double *c12 = myGlove->Index2;
	double *c13 = myGlove->Index3;
	double *c20 = myGlove->Middle0;
	double *c21 = myGlove->Middle1;
	double *c22 = myGlove->Middle2;
	double *c23 = myGlove->Middle3;
	double *c30 = myGlove->Ring0;
	double *c31 = myGlove->Ring1;
	double *c32 = myGlove->Ring2;
	double *c33 = myGlove->Ring3;
	double *c40 = myGlove->Little0;
	double *c41 = myGlove->Little1;
	double *c42 = myGlove->Little2;
	double *c43 = myGlove->Little3;
	double *c50 = myGlove->Wrist;
	double *c51 = myGlove->Hand;
	double *c60 = myGlove->RPY_Wrist;
	double *c61 = myGlove->RPY_Hand;

	for (int i = 0; i < FINGER_POS_ARR_SIZE; i++)
	{
		Thumb0[i] = *(c00 + i);
		Thumb1[i] = *(c01 + i);
		Thumb2[i] = *(c02 + i);
		Thumb3[i] = *(c03 + i);
		Index0[i] = *(c10 + i);
		Index1[i] = *(c11 + i);
		Index2[i] = *(c12 + i);
		Index3[i] = *(c13 + i);
		Middle0[i] = *(c20 + i);
		Middle1[i] = *(c21 + i);
		Middle2[i] = *(c22 + i);
		Middle3[i] = *(c23 + i);
		Ring0[i] = *(c30 + i);
		Ring1[i] = *(c31 + i);
		Ring2[i] = *(c32 + i);
		Ring3[i] = *(c33 + i);
		Little0[i] = *(c40 + i);
		Little1[i] = *(c41 + i);
		Little2[i] = *(c42 + i);
		Little3[i] = *(c43 + i);
		Wrist[i] = *(c50 + i);
		Hand[i] = *(c51 + i);
		RPY_Wrist[i] = *(c60 + i);
		RPY_Hand[i] = *(c61 + i);
	}
	// creating an array of finger's bending values - using pointers
	c01 = myGlove->FingerBend;
	for (int i = 0; i < FINGER_BEND_ARR_SIZE; i++) {
		FingerBend[i] = *(c01 + i);
	}
	// creating an array of finger's abduction values - using pointers
	c02 = myGlove->FingerAbd;
	for (int i = 0; i < FINGER_ABD_ARR_SIZE; i++)
	{
		FingerAbd[i] = *(c02 + i);
	}
	// exporting the thumb cross-over and palm-arch values
	ThumbCO = myGlove->ThumbCO;
	PalmArch = myGlove->PalmArch;

}







