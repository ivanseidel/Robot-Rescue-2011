/*
*******************TRATAMENTO DE ERROS****************************
*/
#define P_ERRO_DEBUG 1

string P_ERRO_CODE = "NO-ERRO";

void Warning(){
  //if(!bSoundActive){
    ClearSounds();
    PlaySound(soundException);
  //}
}

bool ERRO_SET_CODE(string ERRO_CODE, bool ERRO = false){
  if(!ERRO)
  {
    Warning();
	  P_ERRO_CODE = ERRO_CODE;
	  if(P_ERRO_DEBUG==1){
	    eraseDisplay();
      nxtDisplayCenteredBigTextLine(2, "ERROR");
	    nxtDisplayTextLine(6, ERRO_CODE);
	    while(nNxtButtonPressed==-1)wait1Msec(5);
	    if(nNxtButtonPressed==BT_ENTER){
	      while(nNxtButtonPressed>=0);
	      return false;
	    }
      if(nNxtButtonPressed==BT_RIGHT)return true;
	    while(nNxtButtonPressed!=-1)wait1Msec(5);
	    eraseDisplay();
	  }
	  wait1Msec(10);
	}
	return ERRO;
}


long SafeLimit[10] = {0,0,0,0,0,0,0,0,0,0};
long SafeTimer[10] = {0,0,0,0,0,0,0,0,0,0};

void setSafe(int SafeID, long Time){
  SafeTimer[SafeID] = time10[T4]*10;
  SafeLimit[SafeID] = abs(Time);
}

bool getSafe(int SafeID){
  if(time10[T4]*10- SafeTimer[SafeID] >= SafeLimit[SafeID]){
    ClearSounds();
    PlayTone(300, 10);
    return false;
  }else{
    return true;
  }
}

long getSafeDif(int SafeID){
  return time10[T4]*10 - SafeTimer[SafeID];
}
