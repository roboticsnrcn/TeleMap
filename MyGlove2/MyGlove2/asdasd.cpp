//
//#include <iostream>
//#include <stdio.h>
//#include <string>
//#include <windows.h>
//#include "VMG30.h"
//
//
//
//
//using namespace std;
//
//
//void main()
////int argc, char* argv[]
//{
//	double remap(double x, double Xmin, double Xmax, double Ymin, double Ymax);
//
//	VMG30HANDLE gloveH = GetVMGlove();
//
//	char ipaddr[15];sprintf_s(ipaddr, "127.0.0.1");
//	int comport = 5, testVibro = 0, ctr = 0;
//	VMGloveSetConnPar(gloveH, comport, ipaddr);
//
//	int cs1 = VMGloveConnect(gloveH, CONN_USB, PKG_QUAT_FINGER);
//	int comp;
//	char ip[15];
//	VMGloveGetConnPar(gloveH, &comp, ip);
//	fprintf(stderr, "COMP:%d IP:%s\n", comp, ip);
//
//	while (testVibro == 0)
//	{
//		testVibro = VMGloveSetVibrotactile(gloveH, VIBRO_THUMB, 100);
//		ctr++;
//		//	for (int i = 0; i < 100; i++)
//		//	{
//		//		//testVibro = VMGloveSetVibrotactile(gloveH, VIBRO_AUX, 100);
//		//		Sleep(30);
//		//		testVibro = VMGloveSetVibrotactile(gloveH, VIBRO_LITTLE, i);
//		//		testVibro = VMGloveSetVibrotactile(gloveH, VIBRO_RING, i);
//		//		testVibro = VMGloveSetVibrotactile(gloveH, VIBRO_INDEX, i);
//		//		testVibro = VMGloveSetVibrotactile(gloveH, VIBRO_THUMB, i);
//
//		//	}
//		//	//Sleep(1000);
//		//	for (int i = 0; i < 100; i++)
//		//	{
//		//		//testVibro = VMGloveSetVibrotactile(gloveH, VIBRO_AUX, 100);
//		//		Sleep(30);
//		//		testVibro = VMGloveSetVibrotactile(gloveH, VIBRO_LITTLE, 100 - i);
//		//		testVibro = VMGloveSetVibrotactile(gloveH, VIBRO_RING, 100 - i);
//		//		testVibro = VMGloveSetVibrotactile(gloveH, VIBRO_INDEX, 100 - i);
//		//		testVibro = VMGloveSetVibrotactile(gloveH, VIBRO_THUMB, 100 - i);
//		//	}
//	}
//	printf("%d\n", ctr);
//	getchar();
//
//}
