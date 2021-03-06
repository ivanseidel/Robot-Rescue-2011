#pragma config(Sensor, S2,     ,                    sensorI2CCustom)
#pragma config(Sensor, S4,     AS,                  sensorSONAR)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#define PORT_ARD S1

#include "ARDU-driver.h"
#include "DL-lib.c"
#include "MSDIST-driver.h"

tByteArray USData;
int AUlt[700];
int AIR[700];
int samples=0;


#define BT_LEFT  2
#define BT_ENTER 3
#define BT_RIGHT 1

//----------------------------------------------------------------------------------------------------------------
//Modifica as configuracoes do grafico
int SG_pos=1, SG_configs=4,SG_jump, SG_update, SG_exit,SG_ySpace,SG_yScale=0,SG_xSpace;
void SG_Config(int change){
	switch(SG_pos){
		//Case 1: Exit
		case 1:
		  if(change==0){
		  	nxtDisplayTextLine(1, "SAIR: <> Sim");
		  }else{
		  	SG_exit=1;
		  }
		  break;

		//Case 2: Jump
		case 2:
		  if(change==0){
		  	nxtDisplayTextLine(1, "Jump: " + (string)SG_jump);
		  }else{
		  	SG_jump+=change;
		  	if(SG_jump<=0){
		  		SG_jump=1;
		  	}
		  }
		  break;

		//Case 3: yScale
		case 3:
		  if(change==0){
		  	nxtDisplayTextLine(1, "yScale: "+ (string)SG_yScale);
		  }else{
		  	SG_yScale+=change;
		  }
		  break;
	  //Case 4: Exit
		case 4:
		  if(change==0){
		  	nxtDisplayTextLine(1, "ySpace: "+ (string)SG_ySpace);
		  }else{
		  	SG_ySpace+=change;
		  }
		  break;
	}
	SG_update=0;
}

//Aumenta a variavel SG_pos ate o limite
//depois retorna ao 1
void SG_Change(){
	SG_pos++;
	if(SG_pos>SG_configs){
		SG_pos=1;
	}
	SG_update=0;
}
//Switch dos botoes
void SG_Button(){
	//Le se apertou algum botao
	time100[T1]=0;
	if(nNxtButtonPressed == BT_ENTER){
		while(nNxtButtonPressed != -1 && time100[T1]<3){
	  }
		PlayTone(100,4);
	  SG_Change();
	}
	if(nNxtButtonPressed == BT_RIGHT){
		while(nNxtButtonPressed != -1 && time100[T1]<3){
	  }
		PlayTone(250,4);
		SG_Config(1);
	}
	if(nNxtButtonPressed == BT_LEFT){
		while(nNxtButtonPressed != -1 && time100[T1]<3){
	  }
		PlayTone(250,4);
		SG_Config(-1);
	}
}
//Mostra o grafico
void SG(){

	//espera 20 segundos, se passar deste tempo, o nxt desliga
	//caso alguma tecla seja apertada, ira mostrar o grafico deleitura
	time100[T1]=0;
	int SleepTime=150;
	while(true){
		if(time100[T1]>SleepTime){
			powerOff();
		}else if(nNxtButtonPressed == BT_ENTER){
			break;
		}
	}
	while(nNxtButtonPressed == BT_ENTER){
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
		SG_yScale=0;
		SG_update=0;
		SG_exit=0;
		SG_pos=1;
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

		eraseDisplay();
		SG_ySpace=32;
    SG_yScale=1;
		SG_update=0;
		SG_exit=0;
		SG_pos=1;
		while(SG_exit==0){
			SG_Button();
			if(SG_update==0){
				eraseDisplay();
				for(int i=1;i<100 && i<samples/SG_jump;i++){
					nxtDrawRect(i+SG_xSpace, SG_ySpace+AIR[(i-1)*SG_jump]/SG_yScale,i+1+SG_xSpace,SG_ySpace+AIR[i*SG_jump]/SG_yScale);
				}
				SG_Config(0);
			  SG_update=1;
			}
		}
	}
}

task main(){
  MSDISTreadDist(S2);
  ARDUinit(PORT_ARD);
  DL_Init();

  string Datalog;

  while(nNxtButtonPressed==-1){
    PingUS(PORT_ARD);
    wait10Msec(2);
    time1[T1]=0;
    ReadAllUS(PORT_ARD,USData);
		nxtDisplayBigTextLine(2, "S1: %i", USData[0]);
  	nxtDisplayBigTextLine(4, "S2: %i", MSDISTreadDist(S2));

  	sprintf(Datalog,"%i,%i,%i", USData[0],USData[1],USData[0]-USData[1]);

  }
  for (samples=0;samples<170;samples++)
  {

    PingUS(PORT_ARD);
    wait10Msec(2);
    time1[T1]=0;
    ReadAllUS(PORT_ARD,USData);

    AUlt[samples]=USData[0];
		AIR[samples]=MSDISTreadDist(S2);

		nxtDisplayBigTextLine(2, "S1: %i", AUlt[samples]);
  	nxtDisplayBigTextLine(4, "S2: %i", AIR[samples]);

  	sprintf(Datalog,"%i,%i,%i", USData[0],USData[1],USData[0]-USData[1]);

  	DL_Insert(Datalog);

  	motor[motorA]=-100;
  	motor[motorB]=-100;
  	while(abs(nMotorEncoder[motorA])<samples*5);
  	motor[motorA]=0;
  	motor[motorB]=0;


    /*writeDebugStreamLine("------");
    writeDebugStreamLine("A:%i | B:%i | C:%i | D:%i | E:%i" ,USData[0],USData[1],USFilt[2],USFilt[3],USFilt[4]);
    writeDebugStreamLine("TIME:%i" ,time1[T1]);*/

  }
  DL_Close();
  SG();
  wait1Msec(2000);
}
