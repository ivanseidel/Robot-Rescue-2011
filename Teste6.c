#include "HTAC-driver.h"
task main(){
  SensorType[S1] = sensorI2CCustom;
  int x, y, z;
  while(1){
    HTACreadAllAxes(S1,x,y,z);
	 nxtDisplayBigTextLine(1, "%i",x);
	 nxtDisplayBigTextLine(3, "%i",y);
	 nxtDisplayBigTextLine(5, "%i",z);
  }
}
