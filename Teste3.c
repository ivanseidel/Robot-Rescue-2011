#pragma config(Sensor, S4,     AS,                  sensorSONAR)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#define PORT_ARD S1

#include "DL-lib.c"
#include "MSDIST-driver.h"

tByteArray USData;

task main(){
  DL_Init();

  SensorType[S1] = sensorI2CCustom;

  string Datalog;

  int v1,v2;
  while(nNxtButtonPressed<0){
    v1=SensorValue[AS]; //MSDISTreadDist(S1);
    //v2=MSDISTreadVoltage(S1);
		nxtDisplayBigTextLine(2, "S1: %i", v1);
		nxtDisplayBigTextLine(4, "S2: %i", v2);
  }

  for (int pos=0;pos<520;pos++)
  {
    v1=SensorValue[AS];//MSDISTreadDist(S1);
    //v2=MSDISTreadVoltage(S1);
		nxtDisplayBigTextLine(2, "S1: %i", v1);
		//nxtDisplayBigTextLine(4, "S2: %i", v2);

  	sprintf(Datalog,"%i", v1/*,v2,v1-v2*/);

  	DL_Insert(Datalog);

  	motor[motorA]=80;
  	while(abs(nMotorEncoder[motorA])<pos*2);
  	motor[motorA]=0;
  	motor[motorB]=-80;
  	while(abs(nMotorEncoder[motorB])<pos*2);
  	motor[motorB]=0;

  }
  DL_Close();
  wait1Msec(2000);
}
