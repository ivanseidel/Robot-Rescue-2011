int MOV_1; // Motor Esquerdo
int MOV_2; // Motor Direito

void MOVinit(int Mot1, int Mot2){
  MOV_1=Mot1;
  MOV_2=Mot2;
}



bool MOVtestMotor(int Mot){
  bool ret=false;
  int motorLast=nMotorEncoder[Mot];
  int timeLast=time10[T4];
  motor[Mot]=50;
  while(time10[T4]-timeLast<90){
    if(motorLast!=nMotorEncoder[Mot])
    {
      ret=true;
      break;
    }
  }
  motor[Mot]=0;
  return ret;
}
