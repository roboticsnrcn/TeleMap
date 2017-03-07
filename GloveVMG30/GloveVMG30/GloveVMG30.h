#pragma once
#include "VMG30.h"


//using namespace std;

//class FingerVMG30
//{
//public:
//	double x0, y0, z0;
//};

class GloveVMG30
{
	// creating an handle to the VMG30 original class - a connection must be done using PKG_QUAT_FINGER
	VMG30HANDLE gloveH;
public:
	GloveVMG30();

	//x,y,z values of each node in the format -> [nodex,nodey,nodez];
	double Thumb0[3], Thumb1[3], Thumb2[3], Thumb3[3],
		Index0[3], Index1[3], Index2[3], Index3[3],
		Middle0[3], Middle1[3], Middle2[3], Middle3[3],
		Ring0[3], Ring1[3], Ring2[3], Ring3[3],
		Little0[3], Little1[3], Little2[3], Little3[3],
		Wrist[3], Hand[3]; 
	// bending values -> 0 min bend - 100 max bend
	// abduction values -> 0 max abd - 100 min abd
	// Thumb cross over value -> 0 min bend - 100 max bend
	// Palm arch value -> 0 min bend - 100 max bend
	double FingerBend[10], FingerAbd[4], ThumbCO, PalmArch;
	// roll,pitch,yaw values of the wrist and hand
	double RPY_Wrist[3], RPY_Hand[3];
	// finger tip's pressure values -> 0 max pressure - 100 min pressure
	double Press[5];
	//connection status 
	int ConnStat;
	// function of glove connecting
	int ConnectGlove(int comport, int StreamMode, long timeout);
	// function of glove disconnecting
	int DisconnectGlove();
	// function of glove left/right hand selection
	int GloveHandType(int lefthanded);
	// function of streaming info from the sensors in the glove 
	void StreamInfo();
	// function of sending feedback to the glove
	int GetFeedback(int Finger, int Intensity);
};



