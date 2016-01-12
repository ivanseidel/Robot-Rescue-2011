bool TEST_MOTOR(int TEST_MOTOR){
  bool ret=false;
  int MOTOR_LAST_POS=nMotorEncoder[TEST_MOTOR];
  setSafe(0,0);
  motor[TEST_MOTOR]=50;
  while(getSafeDif(0)<90){
    if(MOTOR_LAST_POS!=nMotorEncoder[TEST_MOTOR])
    {
      ret=true;
      break;
    }
  }
  motor[TEST_MOTOR]=0;
  return ret;
}
