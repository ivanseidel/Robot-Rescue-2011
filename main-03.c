#pragma config(Motor,  motorA,          MA,            tmotorNormal, openLoop, encoder)
#pragma config(Motor,  motorB,          ,              tmotorNormal, openLoop, encoder)
#pragma config(Motor,  motorC,          MC,            tmotorNormal, openLoop, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*
************************************************
******************* PORTAS DOS SENSORES
************************************************
*/

tSensors PORT_ARD  = S3;
tSensors PORT_COMP = S2;
tSensors PORT_ACC  = S1;
//tSensors PORT_T1   = S3;
//tSensors PORT_T2   = S3;


/*
************************************************
******************* DEFINICOES GERAIS
************************************************
*/

#define BT_LEFT  2
#define BT_ENTER 3
#define BT_RIGHT 1


/*
************************************************
******************* INCLUDES
************************************************
*/

//Sensores
#include "HTMC-driver.h"
#include "HTAC-driver.h"
#include "ARDU-driver.h"

//Commom
#include "INC-ERRO_HANDLE.c"
#include "INC-CONFIG_TESTS.c"
#include "INC-Controle.c"
#include "INC-Move.c"


/*
************************************************
******************* FUNCOES DE ESTADOS (SETUP)
************************************************
*/

#define ST_INIT      0
#define ST_CONFIG    1
#define ST_WAIT      2
#define ST_LINHA     3 //MT_ACCEL
#define ST_GAP       4 //MT_ACCEL MT_TOQUE
#define ST_OBSTACULO 5
#define ST_SOBE      6
#define ST_ENTRA     7
#define ST_RADAR     8
#define ST_LATA      9
#define ST_DEPOSITA  10

int P_ESTADO_MAX = 10;

string STATE_TABLE[11] = {
"INIT",
"CONFIG",
"WAIT",
"LINHA",
"GAP",
"OBSTACULO",
"SOBE",
"ENTRA",
"RADAR",
"LATA",
"DEPOSITA"};

#include "INC-STATES.c"


/*
************************************************
******************* VARIAVEIS PING DE SENSORES
************************************************
*/

//Configurao dos sensores
#define ACCEL_AXIS_RAMPA 1
#define ACCEL_DELTA      40
int ACCEL_Offset = 0;

//Valores dos sensores
int US[3]={0,0,0};
int ACCEL[3]={0,0,0};
int ACCEL_Filter = 0;
bool ACCEL_Rampa = false;

/*
************************************************
******************* FUNCOES DE MULTI-TAREFA
************************************************
*/

#define MT_DEFAULT       0
#define MT_BEEP          1
#define MT_STOP_BUTTON   2
#define MT_ACCEL         3
#define MT_TOQUE         4

sub MTASK_DOTASK(int MTASK_ID){
  switch (MTASK_ID)
  {
    //********
    case MT_DEFAULT:
	    wait1Msec(1);
	    break;

    //********
    case MT_BEEP:
	    PlayTone(200, 12);
	    wait10Msec(120);
	    break;

    //********
	  case MT_STOP_BUTTON:
	    if(nNxtButtonPressed==BT_ENTER)
	    {
	      int static TimeDif;
	      TimeDif=time10[T4];
	      while(nNxtButtonPressed==BT_ENTER){
	        if(time10[T4]-TimeDif>50)
	        {
    	      MV_StopMotors();
    	      ClearSounds();
	          PlaySound(soundBlip);
	          ESTADO_SET_TARGET(ST_WAIT);
	          break;
	        }
	      }
	    }
	    break;

	  //********
    case MT_ACCEL:
      static int LastTime;
      if(time1[T3]-LastTime >= 3)
      {
        HTACreadAllAxes(PORT_ACC,ACCEL[0],ACCEL[1],ACCEL[2]);
        if(abs(ACCEL[ACCEL_AXIS_RAMPA]-ACCEL_Offset)>ACCEL_DELTA){
          if (ACCEL_Filter++ > 2){
            ACCEL_Rampa = true;
            ACCEL_Filter = 3;
          }
        }else{
          if (ACCEL_Filter-- < 2){
            ACCEL_Filter = 0;
            ACCEL_Rampa = false;
          }
        }
        LastTime=time1[T3];
      }
	    break;

	  //********
    case MT_TOQUE:
	    wait1Msec(1);
	    break;
  }
}

#include "INC-MULTI_TASKING.c"


/*
************************************************
******************* FUNCOES DE ESTADOS (FUNCOES)
************************************************
*/


//************************
// Funcoes a serem rodadas
// 1 vez no comeco do
// programa.
//************************
void F_STATE_INIT()
{
  MTASK_SET_RUN();

  while(ESTADO_IS_CURRENT())
  {
    //=====================================
    ESTADO_SET_TARGET(ST_CONFIG);
    //=====================================
  }
}


//************************
//Configura sensores e joga erros na tela
//************************
void F_STATE_CONFIG()
{
  MTASK_SET_RUN(MT_BEEP);
  //Enquanto o estado atual for o estado target

  eraseDisplay();
  nxtDisplayCenteredBigTextLine(3, "WAIT");

  while(ESTADO_IS_CURRENT())
  {
    //=====================================
    wait10Msec(100);

    //Seta os tipos de porta no NXT
    SensorType[PORT_ARD] = sensorI2CCustom;
    SensorType[PORT_ACC] = sensorI2CCustom;
    SensorType[PORT_COMP] = sensorI2CCustom;

    //Inicia Arduino
    while(!ERRO_SET_CODE(" CF: ARDU ERR",ARDUinit(PORT_ARD)));

    //Inicia Acc Sensor
    while(!ERRO_SET_CODE(" CF: ACC ERR",HTACinit(PORT_ACC)));

    HTACreadAllAxes(PORT_ACC,ACCEL[0],ACCEL[1],ACCEL[2]);
    ACCEL_Offset=ACCEL[ACCEL_AXIS_RAMPA];

    //Inicia Line Leader
    //while(!ERRO_SET_CODE(" CF: LL ERR",LLinit(PORT_LL)));

    //Inicia Bussola
    //while(!ERRO_SET_CODE(" CF: COMP ERR",HTMCreadHeading(PORT_COMP)>=0));

    //Testa motores
    while(!ERRO_SET_CODE(" CF: MOTOR A",TEST_MOTOR(MA)));

    while(!ERRO_SET_CODE(" CF: MOTOR C",TEST_MOTOR(MC)));

    bMotorReflected[MA] = true;
    bMotorReflected[MC] = true;

    GARRA_H(PORT_ARD, GARRA_H_FECHA);
    wait10Msec(20);


    GARRA_V(PORT_ARD,GARRA_V_SOBE);
    wait10Msec(30);
    GARRA_V(PORT_ARD,GARRA_V_PARA);
    GARRA_H(PORT_ARD, GARRA_H_PARA);

    ESTADO_SET_TARGET(ST_WAIT);
    //=====================================
  }
}


//************************
//Pausa e despausa programa
//-= < Para iniciar maze
//-= > Para ultima sala
//************************
void F_STATE_WAIT()
{
  MTASK_SET_RUN(MT_DEFAULT,MT_ACCEL);

  tByteArray USwall;

  eraseDisplay();
  while(ESTADO_IS_CURRENT())
  {
    //=====================================
    motor[MA]=0;
    motor[MC]=0;
    nxtDisplayCenteredBigTextLine(4, "MENU");
    nxtDisplayString(7, " LINHA  -  ENTRA");

    while(nNxtButtonPressed != BT_LEFT && nNxtButtonPressed != BT_RIGHT){
      nxtDisplayCenteredTextLine(1, "R=%i T=%i", ACCEL_Rampa, ReadTouch(PORT_ARD)==0*);

      // Le arduino para pingar os ultrasons
	    wait1Msec(30);
	    ReadAllUS_short(PORT_ARD,USwall);

	    nxtDisplayCenteredTextLine(2, "%3i  %3i  %3i", USwall[0],USwall[1],USwall[2]);
    }

    if(nNxtButtonPressed==BT_LEFT){
      ESTADO_SET_TARGET(ST_LINHA);
    }else{
      ESTADO_SET_TARGET(ST_ENTRA);
    }

    while(nNxtButtonPressed!=-1);
    PlaySound(soundBlip);
    eraseDisplay();
    //=====================================
  }
}

//************************
// Segue Linha
//************************
void F_STATE_LINHA()
{
  MTASK_SET_RUN(MT_ACCEL,MT_STOP_BUTTON);

  while(ESTADO_IS_CURRENT())
  {
    //=====================================

    motor[MA]=70;
    motor[MC]=70;

    //Se detectou rampa com acceleracao, sobe a rampa
    if(ACCEL_Rampa)ESTADO_SET_TARGET(ST_SOBE);
    //=====================================
  }
}

//************************
// Passa do GAP
//************************
void F_STATE_GAP()
{
  MTASK_SET_RUN(MT_ACCEL,MT_STOP_BUTTON);

  while(ESTADO_IS_CURRENT())
  {
    //=====================================

    //Se detectou rampa com acceleracao, sobe a rampa
    if(ACCEL_Rampa)ESTADO_SET_TARGET(ST_SOBE);
    //=====================================
  }
}

//************************
// Sobe a Rampa
//************************
void F_STATE_SOBE()
{
  PlayTone(500,10);

  MTASK_SET_RUN(MT_ACCEL,MT_STOP_BUTTON);

  int USminDist = 999, USdist,USdelta,Lado1,Lado2;

  float Error = 0, vI = 0, vP = 0, vD = 0, kI = 0.3, kP = 1.5, kD = 1, lD=4;

  tByteArray USwall;

  time1[T1]=0;

  while(ESTADO_IS_CURRENT())
  {
    //=====================================

    // Le arduino para pingar os ultrasons
    wait10Msec(3);
    ReadAllUS_short(PORT_ARD,USwall);

    // Filtra dados

    //// Seta as variaveis locais como locais
    //// para nao dar bug (alterar o valor na outra task)
    Lado1=USwall[0];
    Lado2=USwall[2];

    //// Acha a menor distancia que o robo fica das paredes
    //if(Lado1+Lado2<USminDist)USminDist=USdist;

    //// Filtra paredes (existe ou nao)
    if(Lado1>60)Lado1=60-Lado2;
    if(Lado2>60)Lado2=60-Lado1;

    // Calcula o Error
    vD =  time1[T1] * ((Lado1 - Lado2) - vD) / 1000;
    lD =  vD;
    vP =  (Lado1 - Lado2);
    vI += time1[T1] * vP / 1000;

    //Aplica constantes
    vP *= kP;
    vI *= kI;
    vD *= kD;

    if(vI>20)  vI = 20;
    if(vI<-20) vI = -20;

    Error = vP+
            vI-
            vD;

    time1[T1]=0;

    // Aplica erro aos motores
    motor[MA]=70 - Error;
    motor[MC]=70 + Error;

    //Mostra no display os valores P, I, D e Stering final (Error)
    eraseDisplay();
    nxtDisplayString(2,"P = %i", (int)vP);
    nxtDisplayString(3,"I = %i", (int)vI);
    nxtDisplayString(4,"D = %i", (int)vD);
    nxtDisplayBigStringAt(46 - Error, 24, "|");

    //Se saiu da rampa com acceleracao, entra na sala
    if(!ACCEL_Rampa)ESTADO_SET_TARGET(ST_ENTRA);
    //=====================================
  }
}

//************************
// Entra na Sala
//************************
void F_STATE_ENTRA()
{
  PlayTone(500,10);
  MTASK_SET_RUN(MT_STOP_BUTTON);

  while(ESTADO_IS_CURRENT())
  {
    //=====================================


    setSafe(0,5000);
    MV_Reto_Unlimited(60);
    while(getSafe(0)/* && !ReadTouch(PORT_ARD)==0*/);
    MV_Reto(80,0,7);
    MV_Reto(-60,100);
    ESTADO_SET_TARGET(ST_WAIT);
    //=====================================
  }
}


/*
************************************************
******************* TASK MAIN
************************************************
*/
task main(){
  StartTask(MULTI_TASKING);
  while(1)
  {
    //Seleciona estado atual
    ESTADO_SET_ESTADO();
    nxtDisplayTextLine(0, "ST= %s", STATE_TABLE[G_ESTADO_TARGET]);
    switch(G_ESTADO_TARGET)
    {

      //Funcoes realizadas somente no comeco do programa
      case ST_INIT:
        F_STATE_INIT();
        break;

      //Configura sensores
      case ST_CONFIG:
        F_STATE_CONFIG();
        break;

      //Pausa e despausa programa
      case ST_WAIT:
        F_STATE_WAIT();
        break;

      case ST_LINHA:
        F_STATE_LINHA();
        break;

      case ST_GAP:
        F_STATE_GAP();
        break;

      case ST_OBSTACULO:
        F_STATE_CONFIG();
        break;

      case ST_SOBE:
        F_STATE_SOBE();
        break;

      case ST_ENTRA:
        F_STATE_ENTRA();
        break;

      case ST_RADAR:
        F_STATE_CONFIG();
        break;

      case ST_LATA:
        F_STATE_CONFIG();
        break;

      case ST_DEPOSITA:
        F_STATE_CONFIG();
        break;

      default:
        ERRO_SET_CODE("ESTADO INEXISTENTE");
        break;
    }
  }
}