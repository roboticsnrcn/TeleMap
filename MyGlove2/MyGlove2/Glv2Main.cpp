#include <iostream>
#include <stdio.h>
#include <string>
#include <windows.h>
#include "VMG30.h"



using namespace std;

void main()
//int argc, char* argv[]
{
	double remap(double x, double Xmin, double Xmax, double Ymin, double Ymax);

	VMG30HANDLE gloveH = GetVMGlove();

	char ipaddr[15];sprintf_s(ipaddr, "127.0.0.1");
	int comport = 5;
	VMGloveSetConnPar(gloveH, comport, ipaddr);


	int comp;
	char ip[15];
	VMGloveGetConnPar(gloveH, &comp, ip);
	fprintf(stderr, "COMP:%d IP:%s\n", comp, ip);


	int cs = VMGloveDisconnect(gloveH);
	Sleep(500);

	// need to connect in PKG_QUAT_FINGER
	int cs1 = VMGloveConnect(gloveH, CONN_USB, PKG_QUAT_FINGER);
	int cnt = 0;
	long start = ::GetTickCount();

	cs = VMGloveSetLeftHanded(gloveH, 0);
	int ConnStat;
	while ((::GetTickCount() - start) < 60000) {
		ConnStat = VMGloveGetConnectionStatus(gloveH);
		Sleep(50);
		fprintf(stderr, "CONNSTATUS: %d\n", ConnStat);

		if (ConnStat == USB_CONNECTED)
			break;
		cnt++;
	}
	fprintf(stderr, "%d\n", ConnStat);
	// initializing t1 for integration of droll/dt, dyaw/dt, dpitch/dt
	//long t1 = ::GetTickCount();

	//cout << "Hi" << endl;
	while (ConnStat == USB_CONNECTED) {
		double x, y, z, x1, y1, z1;
		VMGloveGetPosition(gloveH, "WRIST", &x, &y, &z);
		fprintf(stderr, "Wrist x: %.1f Wrist y:%.1f Wrist z:%.1f \n",
			x, y, z);
		VMGloveGetPosition(gloveH, "THUMB3", &x, &y, &z);
		fprintf(stderr, "THUMB3 x: %.1f THUMB3 y:%.1f THUMB3 z:%.1f \n",
			x, y, z);
		VMGloveGetPosition(gloveH, "INDEX3", &x1, &y1, &z1);
		fprintf(stderr, "INDEX3 x: %.1f INDEX3 y:%.1f INDEX3 z:%.1f \n",
			x1, y1, z1);
		double Xdiff = sqrt((z1 - z)*(z1 - z) + (y1 - y)*(y1 - y) + (x1 - x)*(x1 - x)); //the correct values for difference
		VMGloveGetPosition(gloveH, "MIDDLE3", &x, &y, &z);
		fprintf(stderr, "MIDDLE3 x: %.1f MIDDLE3 y:%.1f MIDDLE3 z:%.1f \n",
			x, y, z);
		double Xdiff1 = sqrt((z - z1)*(z - z1) + (y - y1)*(y - y1) + (x - x1)*(x - x1)); //the correct values for difference
		VMGloveGetPosition(gloveH, "RING3", &x1, &y1, &z1);
		fprintf(stderr, "RING3 x: %.1f RING3 y:%.1f RING3 z:%.1f \n",
			x, y, z);
		double Xdiff2 = sqrt((z1 - z)*(z1 - z) + (y1 - y)*(y1 - y) + (x1 - x)*(x1 - x)); //the correct values for difference
		VMGloveGetPosition(gloveH, "LITTLE3", &x, &y, &z);
		fprintf(stderr, "LITTLE3 x: %.1f LITTLE3 y:%.1f LITTLE3 z:%.1f \n",
			x, y, z);
		double Xdiff3 = sqrt((z - z1)*(z - z1) + (y - y1)*(y - y1) + (x - x1)*(x - x1)); //the correct values for difference

		double fingerBend[10];
		VMGloveGetFingers(gloveH, fingerBend);
		fprintf(stderr, "THUMB 1: %.1f THUMB 2:%.1f \n",
			fingerBend[0], fingerBend[1]);
		fprintf(stderr, "INDEX 1: %.1f INDEX 2:%.1f \n",
			fingerBend[2], fingerBend[3]);
		fprintf(stderr, "MIDDLE 1: %.1f MIDDLE 2:%.1f \n",
			fingerBend[4], fingerBend[5]);
		fprintf(stderr, "RING 1: %.1f RING 2:%.1f \n",
			fingerBend[6], fingerBend[7]);
		fprintf(stderr, "LITTLE 1: %.1f LITTLE 2:%.1f \n",
			fingerBend[8], fingerBend[9]);
		// not in the class yet
		// trying to acquire abduction values between the fingers 0 max bending - 1000 min bending - doesn't give any info also in VMG's software
		double fingerAbd[4];
		int check = VMGloveGetAbductions(gloveH, fingerAbd);
		fprintf(stderr, "THUMB to INDEX: %.1f \n",
			fingerAbd[0]);
		fprintf(stderr, "INDEX to MIDDLE: %.1f \n",
			fingerAbd[1]);
		fprintf(stderr, "MIDDLE to RING: %.1f \n",
			fingerAbd[2]);
		fprintf(stderr, "RING to LITTLE: %.1f \n",
			fingerAbd[3]);

		double palmarch, thumbCO;
		VMGloveGetPalmArch(gloveH, &palmarch);
		VMGloveGetThumbCrossOver(gloveH, &thumbCO);
		fprintf(stderr, "THUMB CROSS OVER: %.1f \n", thumbCO);
		fprintf(stderr, "PALM ARCH: %.1f \n", palmarch);
		// need to also add to the class the roll,pitch,yaw info and pressures (optional)
		//get wrist alttitude
		double roll, pitch, yaw;
		//double quat1, quat2, quat3, quat4;
		VMGloveGetAttitudeWrist(gloveH, &roll, &pitch, &yaw);
		fprintf(stderr, "WRIST ROLL: %.1f PITCH:%.1f YAW:%.1f\n", roll, pitch, yaw);

		//VMGloveGetQuaternionHand(gloveH, &quat1, &quat2, &quat3, &quat4);
		//fprintf(stderr, "WRIST QUAT1: %.1f QUAT2:%.1f QUAT3:%.1f QUAT4:%.1f\n", quat1, quat2, quat3, quat4);
		//get hand alttitude
		VMGloveGetAttitudeHand(gloveH, &roll, &pitch, &yaw);
		fprintf(stderr, "HAND ROLL: %.1f PITCH:%.1f YAW:%.1f\n", roll, pitch, yaw);

		int i;
		double press[5];
		VMGloveGetPressures(gloveH, press);
		for (i = 0;i<5;i++) {
			fprintf(stderr, "PRESS%d: %.1f\n", i + 1, press[i]);
		}
		int testVibro;

		//test of ramp ->0-100-0 in the vibration
		for (i = 0; i < 100; i++)
		{
			//testVibro = VMGloveSetVibrotactile(gloveH, VIBRO_AUX, 100);
			Sleep(30);
			testVibro = VMGloveSetVibrotactile(gloveH, VIBRO_LITTLE, i);
			testVibro = VMGloveSetVibrotactile(gloveH, VIBRO_RING, i);
			testVibro = VMGloveSetVibrotactile(gloveH, VIBRO_INDEX, i);
			testVibro = VMGloveSetVibrotactile(gloveH, VIBRO_THUMB, i);

		}
		//Sleep(1000);
		for (i = 0; i < 100; i++)
		{
			//testVibro = VMGloveSetVibrotactile(gloveH, VIBRO_AUX, 100);
			Sleep(30);
			testVibro = VMGloveSetVibrotactile(gloveH, VIBRO_LITTLE, 100 - i);
			testVibro = VMGloveSetVibrotactile(gloveH, VIBRO_RING, 100 - i);
			testVibro = VMGloveSetVibrotactile(gloveH, VIBRO_INDEX, 100 - i);
			testVibro = VMGloveSetVibrotactile(gloveH, VIBRO_THUMB, 100 - i);
		}



		fprintf(stderr, "TestVibro: %d\n", testVibro);
	}
	VMGloveDisconnect(gloveH);
	Sleep(1000);

}

