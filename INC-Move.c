//----------------------------------------------//
//----------------------------------------------//
//Library que possui as funcoes de mover motores//
//----------------------------------------------//
//----------------------------------------------//
#pragma platform(NXT)
#pragma systemFile

#define MV_EMotor    motorA
#define MV_DMotor    motorC
#define MV_GarraMotor     motorB
#define MV_TimeLimit 70 //5 secs
#define MV_divise 2

void MV_StopMotors(){
	motor[MV_EMotor] = 0;
  motor[MV_DMotor] = 0;
  motor[MV_GarraMotor]  = 0;
}

void MV_Reto(int forca, int degree, int tempo=0){

	nMotorEncoder[MA]=0;
	nMotorEncoder[MC]=0;
	float I=0,P=0,erro;
  float kI = 0.001;
  int kP = 4;
  time100[T2]=0;
	if(degree>0){
		while(abs(nMotorEncoder[MV_EMotor])<degree && time100[T2]<MV_TimeLimit){
  	  //Aplica PI no encoder
		  I+=time1[T3]/1000*kI;
		  time1[T3]=0;
		  erro=nMotorEncoder[MA]-nMotorEncoder[MC];
		  P=erro * kP;
		  motor[MA]=forca-P-I;
		  motor[MC]=forca+P+I;
		  wait1Msec(2);
		}
	}else if(tempo>0){
		while(time100[T2]<tempo){
		  //Aplica PI no encoder
		  I+=time1[T3]/1000*kI;
		  time1[T3]=0;
		  erro=nMotorEncoder[MA]-nMotorEncoder[MC];
		  P=erro * kP;
		  motor[MA]=forca-P-I;
		  motor[MC]=forca+P+I;
		  wait1Msec(2);
		}
	}
	MV_StopMotors();
}

void MV_Reto_Unlimited(int forca,int steering=0){
	motor[MV_EMotor]=forca+steering;
	motor[MV_DMotor]=forca-steering;
}
void MV_Spin_Unlimited(int forca){
	motor[MV_EMotor]=forca/MV_divise;
	motor[MV_DMotor]=-forca/MV_divise;
}

void MV_Vira(int forca, int degree,int lado, int tempo=0){
	time100[T2]=0;
	if(degree>0){
		nMotorEncoder[lado]=0;
		while(nMotorEncoder[lado]<degree && nMotorEncoder[lado]>-degree && time100[T2]<MV_TimeLimit){
			motor[lado]=forca/MV_divise;
		}
		MV_StopMotors();
	}else if(tempo>0){
		time100[T1]=0;
		while(time100[T1]<tempo){
			motor[lado]=forca/MV_divise;
			motor[lado]=forca/MV_divise;
		}
		MV_StopMotors();
	}
}

void MV_Spin(int forca, int degree, int tempo=0){
	time100[T2]=0;
	nMotorEncoder[MV_EMotor]=0;
	nMotorEncoder[MV_DMotor]=0;
	int neg = abs(forca)/forca;
	if(degree>0){
		while(abs(nMotorEncoder[MV_EMotor])<degree && time100[T2]<MV_TimeLimit){
		  motor[MV_EMotor]=forca+time10[T2]/5*neg;
			motor[MV_DMotor]=-forca+time10[T2]/5*-neg;
		}
	}else if(tempo>0){
		time100[T1]=0;
		while(time100[T1]<tempo){
			motor[MV_EMotor]=forca/MV_divise;
			motor[MV_DMotor]=-forca/MV_divise;
		}
	}
	MV_StopMotors();
}

void MV_Garra(int pos,int degree=999)
{
	nMotorEncoder[MV_GarraMotor]=0;
	int ciclo=1, DPC=10;
	time100[T2]=0;
	if(pos==0){
		while(time100[T2]<50 && nMotorEncoder[MV_GarraMotor]<degree && nMotorEncoder[MV_GarraMotor]>-degree){
			while(time100[T2]<50 && nMotorEncoder[MV_GarraMotor]<degree && nMotorEncoder[MV_GarraMotor]>-degree && nMotorEncoder[MV_GarraMotor]<nMotorEncoder[MV_GarraMotor]+DPC*ciclo && nMotorEncoder[MV_GarraMotor]>-nMotorEncoder[MV_GarraMotor]-DPC*ciclo){
			  motor[MV_GarraMotor]=-70;
		  }
		  motor[MV_GarraMotor]=0;
		  wait1Msec(20);
		  ciclo++;
		}
	}else if(pos==1){
		while(time100[T2]<30 && nMotorEncoder[MV_GarraMotor]<degree && nMotorEncoder[MV_GarraMotor]>-degree){
			motor[MV_GarraMotor]=70;
		}
	}
	motor[MV_GarraMotor]=0;
}
/*
void MV_SpinCompass(int forca,int graus,tSensors link){
	HTMCsetTarget(link,HTMCreadHeading(link)-graus);
	time100[T1]=0;
	int P=10;
	while(time100[T1]<25 || abs(P)>10){

    P=HTMCreadRelativeHeading(link);
    if(P>0){
      motor[MA]=forca;
      motor[MC]=-forca;
    }else{
      motor[MA]=-forca;
      motor[MC]=forca;
    }

    nxtDisplayCenteredBigTextLine(4, "%i",P);
  }
	MV_StopMotors();
}*/

void MV_SpinCompass(tSensors link,int graus){
  MV_StopMotors();
  wait10Msec(10);
	HTMCsetTarget(link,HTMCreadHeading(link)+graus);
	time100[T4]  = 0;
	time1[T3]  = 0;

	int Rel = 0;
	int Erro     = 0;

	bool Exit    = false;
	int out      = 0;

	float Integral = 0;

	while(time100[T4]<20 && !Exit){
	  Rel=HTMCreadRelativeHeading(link);

	  if(abs(Rel)<30){
	    Integral += time1[T3]*Rel*0.0005;
	  }else{
	    Integral = 0;
	  }

	  time1[T3]=0;
	  Erro = Rel*1.5+Integral;//abs(Rel)/Rel*time100[T4]/2;

	  if(Erro > 70){
	    Erro = 70;
	  }else if(Erro < -70){
	    Erro = -70;
	  }

	  motor[MV_EMotor] = Erro;
	  motor[MV_DMotor] = -Erro;

	  if(abs(Rel)<5){
	    out++;
	  }else{
	    out=0;
	  }

	  if(out>15){
	    Exit=true;
	  }
	  eraseDisplay();
	  nxtDisplayCenteredBigTextLine(2, "%i",Erro);
    nxtDisplayCenteredBigTextLine(4, "%i",Rel);
    nxtDisplayCenteredBigTextLine(6, "%i",Integral);

	  wait10Msec(6);
  }
  PlayTone(2000,10);
	MV_StopMotors();
}
