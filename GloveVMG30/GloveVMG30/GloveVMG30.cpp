#include <iostream>
#include <stdio.h>
#include <string>
#include <windows.h>
#include "VMG30.h"
#include "GloveVMG30.h"
#pragma once

GloveVMG30::GloveVMG30()
{
	//initialize glove handle
	gloveH = GetVMGlove();
}


int GloveVMG30::ConnectGlove(int comport, int StreamMode, long timeout)
{
	char ipaddr[15];sprintf_s(ipaddr, "127.0.0.1");
	// setting connection parameters
	VMGloveSetConnPar(gloveH, comport, ipaddr);
	int comp;
	char ip[15];
	//getting feedback about the connection
	VMGloveGetConnPar(gloveH, &comp, ip);
	fprintf(stderr, "COMP:%d IP:%s\n", comp, ip);
	//First close existing communication to glove
	GloveVMG30::DisconnectGlove();

	VMGloveConnect(gloveH, CONN_USB, StreamMode);
	long start = ::GetTickCount(); //GetTickCount is the computer current time
	int cnt = 0;

	while ((::GetTickCount() - start) < timeout) {
		ConnStat = VMGloveGetConnectionStatus(gloveH);
		Sleep(50);
		fprintf(stderr, "CONNSTATUS: %d\n", ConnStat);
		if (ConnStat == USB_CONNECTED)
			break;
		cnt++;
	}
	return ConnStat;
}

int GloveVMG30::DisconnectGlove()
{
	int cs = VMGloveDisconnect(gloveH);
	Sleep(500);

	return cs;
}

//This function declares - if the hand is right/left handed
int GloveVMG30::GloveHandType(int lefthanded) //if the glove is for left handed this value must be 1
{
	int cs = VMGloveSetLeftHanded(gloveH, lefthanded);

	return cs;
}

void GloveVMG30::StreamInfo()
{
	//inserting x,y,z values of thumb finger data
	VMGloveGetPosition(gloveH, "THUMB0", &Thumb0[0], &Thumb0[1], &Thumb0[2]);
	VMGloveGetPosition(gloveH, "THUMB1", &Thumb1[0], &Thumb1[1], &Thumb1[2]);
	VMGloveGetPosition(gloveH, "THUMB2", &Thumb2[0], &Thumb2[1], &Thumb2[2]);
	VMGloveGetPosition(gloveH, "THUMB3", &Thumb3[0], &Thumb3[1], &Thumb3[2]);
	////inserting x,y,z values of index finger data
	VMGloveGetPosition(gloveH, "INDEX0", &Index0[0], &Index0[1], &Index0[2]);
	VMGloveGetPosition(gloveH, "INDEX1", &Index1[0], &Index1[1], &Index1[2]);
	VMGloveGetPosition(gloveH, "INDEX2", &Index2[0], &Index2[1], &Index2[2]);
	VMGloveGetPosition(gloveH, "INDEX3", &Index3[0], &Index3[1], &Index3[2]);
	//inserting x,y,z values of middle finger data
	VMGloveGetPosition(gloveH, "MIDDLE0", &Middle0[0], &Middle0[1], &Middle0[2]);
	VMGloveGetPosition(gloveH, "MIDDLE1", &Middle1[0], &Middle1[1], &Middle1[2]);
	VMGloveGetPosition(gloveH, "MIDDLE2", &Middle2[0], &Middle2[1], &Middle2[2]);
	VMGloveGetPosition(gloveH, "MIDDLE3", &Middle3[0], &Middle3[1], &Middle3[2]);
	////inserting x,y,z values of ring finger data
	VMGloveGetPosition(gloveH, "RING0", &Ring0[0], &Ring0[1], &Ring0[2]);
	VMGloveGetPosition(gloveH, "RING1", &Ring1[0], &Ring1[1], &Ring1[2]);
	VMGloveGetPosition(gloveH, "RING2", &Ring2[0], &Ring2[1], &Ring2[2]);
	VMGloveGetPosition(gloveH, "RING3", &Ring3[0], &Ring3[1], &Ring3[2]);
	////inserting x,y,z values of little finger data
	VMGloveGetPosition(gloveH, "LITTLE0", &Little0[0], &Little0[1], &Little0[2]);
	VMGloveGetPosition(gloveH, "LITTLE1", &Little1[0], &Little1[1], &Little1[2]);
	VMGloveGetPosition(gloveH, "LITTLE2", &Little2[0], &Little2[1], &Little2[2]);
	VMGloveGetPosition(gloveH, "LITTLE3", &Little3[0], &Little3[1], &Little3[2]);
	////inserting x,y,z values of Wrist data
	VMGloveGetPosition(gloveH, "WRIST", &Wrist[0], &Wrist[1], &Wrist[2]);
	////inserting x,y,z values of Hand data
	VMGloveGetPosition(gloveH, "HAND", &Hand[0], &Hand[1], &Hand[2]);

	//inserting bending, abduction, thumbcrossover and palmarch finger's values
	VMGloveGetFingers(gloveH, FingerBend);
	VMGloveGetAbductions(gloveH, FingerAbd);
	VMGloveGetPalmArch(gloveH, &PalmArch);
	VMGloveGetThumbCrossOver(gloveH, &ThumbCO);
	//get wrist and hand attitude
	VMGloveGetAttitudeWrist(gloveH, &RPY_Wrist[0], &RPY_Wrist[1], &RPY_Wrist[2]);
	VMGloveGetAttitudeHand(gloveH, &RPY_Hand[0], &RPY_Hand[1], &RPY_Hand[2]);
	//get finger tip's pressure values
	VMGloveGetPressures(gloveH, Press);
}
int GloveVMG30::GetFeedback(int Finger, int Intensity)
{
	int checkFB;
	
	if (Finger == VIBRO_THUMB) {
		checkFB = VMGloveSetVibrotactile(gloveH, VIBRO_THUMB, Intensity);
	}
	if (Finger == VIBRO_INDEX)
	{
		checkFB = VMGloveSetVibrotactile(gloveH, VIBRO_INDEX, Intensity);
	}
	if (Finger == VIBRO_MIDDLE) {
		checkFB = VMGloveSetVibrotactile(gloveH, VIBRO_MIDDLE, Intensity);
	}
	if (Finger == VIBRO_RING)
	{
		checkFB = VMGloveSetVibrotactile(gloveH, VIBRO_RING, Intensity);
	}
	if (Finger == VIBRO_LITTLE)
	{
		checkFB = VMGloveSetVibrotactile(gloveH, VIBRO_LITTLE, Intensity);
	}
	else
	{
		checkFB = VMGloveSetVibrotactile(gloveH, VIBRO_AUX, Intensity);
	}
	
	return checkFB;
}

