#include "GloveVMG30.h"
#include <stdio.h>
#include "VMG30.h"
void main() {

	VMG30HANDLE myVMG = new VMG30HANDLE();
	myVMG = GetVMGlove();

	int param = VIBRO_THUMB, Intensity = 20;

	int comport = 5;
	long timeout = 60000; //ms

	char ipaddr[15];sprintf_s(ipaddr, "127.0.0.1");
	// setting connection parameters
	VMGloveSetConnPar(myVMG, comport, ipaddr);
	int comp;

	VMGloveConnect(myVMG, CONN_USB, 1);

	Sleep(1000);

	int ConnStat = VMGloveGetConnectionStatus(myVMG);

	printf("\n%d\n\n", ConnStat);

	Sleep(1000);

	for (int i = 1; i < 100; i++)
	{
		Sleep(1000);
		int CheckFB = VMGloveSetVibrotactile(myVMG, param, Intensity);
		printf("\n%d\n\n", CheckFB);
	}






	getchar();

};