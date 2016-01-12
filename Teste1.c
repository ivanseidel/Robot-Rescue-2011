task main(){
  while(1){
    eraseDisplay();
    nxtDisplayCenteredBigTextLine(4, "%i",nMotorEncoder[motorA]);
    if(nNxtButtonPressed!=-1){
      nMotorEncoder[motorA]=0;
    }
    wait10Msec(50);
  }
}
