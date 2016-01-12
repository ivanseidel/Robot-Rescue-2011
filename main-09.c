#define BT_LEFT  2
#define BT_ENTER 3
#define BT_RIGHT 1
void SG(int AUlt, int samples){

  int SG_jump;
  int SG_ySpace;
	int SG_yScale;
	int SG_update;
	int SG_exit;
	int SG_pos;
	int SG_xSpace;
	//espera 20 segundos, se passar deste tempo, o nxt desliga
	//caso alguma tecla seja apertada, ira mostrar o grafico deleitura
	time100[T1]=0;
	int SleepTime=150;
	while(true){
		if(time100[T1]>SleepTime){
			powerOff();
		}else if(nNxtButtonPressed == 3){
			break;
		}
	}
	while(nNxtButtonPressed == 3){
	}
	PlayTone(300,10);
	//De quantos em quantos valores ele ira ler
	if(samples<=100){
		SG_jump=1;
	}else{
		SG_jump=2;
	}
	//Configs: Jump, yScale, EXIT
	while(true){
		eraseDisplay();
		SG_ySpace=0;
		SG_yScale=17;
		SG_update=0;
		SG_exit=0;
		SG_pos=1;
		SG_xSpace=0;
		while(SG_exit==0){
			SG_Button();
			if(SG_update==0){
				eraseDisplay();
				for(int i=1;i<100 && i<samples/SG_jump;i++){
				  nxtDrawRect(i+SG_xSpace, SG_ySpace+AUlt[(i-1)*SG_jump]/SG_yScale,i+1+SG_xSpace,SG_ySpace+AUlt[i*SG_jump]/SG_yScale);
			  }
				SG_Config(0);
			  SG_update=1;
			}
		}
	}
}
