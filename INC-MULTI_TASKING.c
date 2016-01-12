/*
*******************FUNCOES DE MULTITAREFA****************************
*/

/*#define MT_DEFAULT  0
#define MT_BEEP     1*/

int G_MTASK_MAX = 4;

int P_MTASK_RUN [4];

int G_MTASK_CURRENT = 0;



/*sub MTASK_DOTASK(int MTASK_ID){
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

  }
}*/

sub MTASK_SET_RUN(int MTASK1=0, int MTASK2=0, int MTASK3=0, int MTASK4=0){
  P_MTASK_RUN[0]=MTASK1;
  P_MTASK_RUN[1]=MTASK2;
  P_MTASK_RUN[2]=MTASK3;
  P_MTASK_RUN[3]=MTASK4;
}

task MULTI_TASKING(){
  while(1)
  {
    int i;
    for(i=0;i<G_MTASK_MAX;i++){
      MTASK_DOTASK(P_MTASK_RUN[i]);
    }
  }
}
