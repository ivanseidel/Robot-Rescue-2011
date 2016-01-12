
#pragma platform(NXT)
#pragma systemFile

#define ROOM1 0
#define ROOM2 1
#define ROOM3 2

// BIT: 1 2 3 4 5 6 7 8
// VAL: - - - V W N E S
// V = Visitado

byte Vpat = 0b00010000;
byte Wpat = 0b00001000;
byte Npat = 0b00000100;
byte Epat = 0b00000010;
byte Spat = 0b00000001;

int MZ_pat[4]={Wpat,Npat,Epat,Spat};
#define RM_w 4
#define RM_h 3

int RM1[RM_w][RM_h];
int RM2[RM_w][RM_h];
int RM3[RM_w][RM_h];

int ROOMS[3]={&RM1,&RM2,&RM3};

int MZ_FLOOD1[RM_w][RM_h];
int MZ_FLOOD2[RM_w][RM_h];
int MZ_FLOOD3[RM_w][RM_h];



#define W 0
#define N 1
#define E 2
#define S 3

int MZ_Relative[4][4]={
{W,N,E,S},
{S,W,N,E},
{E,S,W,N},
{N,E,S,W}};

int MZ_SideWall[4]={2,3,0,1};


// 3 variaveis definem a posio atual do robo na arena:
// SALA - FACING - X - Y
// -=DIRECAO:
//     | 1
// 0 -[ ]- 2
//     | 3
#define MZ_ROOM   0
#define MZ_FACING 1
#define MZ_XPOS   2
#define MZ_YPOS   3

//             ROOM  F X Y
int MZ_POS[4]={ROOM1,W,3,0};


/*
*        N=1
*      _______
*     |_|_|_|_|
* W=0 |_|_|_|_|   E=2
*     |_|_|_|_|
*
*        S=3
*/

int* SelectRoom(int room){
  switch (room){
    case ROOM1:
      return (int*)RM1;
      break;

    case ROOM2:
      return (int*)RM2;
      break;

    case ROOM3:
      return (int*)RM3;
      break;
  }
  return false;
}

/*bool MZ_ReadWall(int Xpos, int Ypos, int face, int room=MZ_POS[MZ_ROOM]){
  int Current=SelectRoom(0);
  int abb=Current[0][0];
  return true;
}

void MZ_SetWall(int RelWall, int Xpos = MZ_POS[MZ_XPOS],int Ypos = MZ_POS[MZ_YPOS]){
  int AbsWall=MZ_Relative[MZ_POS[MZ_FACING]][RelWall];
  if(Xpos >= 0 && Xpos <RM_w && Ypos >= 0 && Ypos <RM_h)
  {

  }else{
    PlayTone(300,20);
    wait10Msec(20);
  }
}*/

void MZ_ShowOnDisplay(){
  eraseDisplay();
  for(int y=0; y<3; y++){
    string tmp,Line="";
    for(int x=0; x<4; x++){
      if(MZ_POS[MZ_YPOS] == y && MZ_POS[MZ_XPOS] == x){
        strcat(Line,"|x");
      }else{
        strcat(Line,"|_");
      }
    }
    strcat(Line,"|");
    nxtDisplayCenteredBigTextLine(5-(y*2),"%s",Line);
  }
  /*for(int y=0; y<3; y++){
	  string tmp,Line="";
	  for(int x=0; x<4; x++){
	    //nxtFillRect(x*5*, Top, Right, Bottom);

	    if(MZ_POS[MZ_YPOS] == y && MZ_POS[MZ_XPOS] == x){
	    }else{
	    }
	  }
	}*/
}

void MZ_MV_Front(){
  int tpX=0;
  int tpY=0;
  switch(MZ_POS[MZ_FACING]){
    case W:
      tpX=-1;
      break;

    case N:
      tpY=1;
      break;

    case E:
      tpX=1;
      break;

    case S:
      tpY=-1;
      break;
  }
  MZ_POS[MZ_XPOS]+=tpX;
  MZ_POS[MZ_YPOS]+=tpY;
  MZ_ShowOnDisplay();
}

void MZ_MV_Left(){
  MZ_POS[MZ_FACING]=MZ_Relative[MZ_POS[MZ_FACING]][3];
  MZ_ShowOnDisplay();
}
void MZ_MV_Right(){
  MZ_POS[MZ_FACING]=MZ_Relative[MZ_POS[MZ_FACING]][1];
  MZ_ShowOnDisplay();
}

/*task main(){
  int a=ROOMS[0];
  //StartTask(Show);
  MZ_ShowOnDisplay();
  wait10Msec(100);
  MZ_MV_Front();
  MZ_ShowOnDisplay();
  wait10Msec(100);
  MZ_MV_Right();
  MZ_ShowOnDisplay();
  wait10Msec(50);
  MZ_MV_Front();
  MZ_ShowOnDisplay();
  wait10Msec(100);
  MZ_MV_Front();
  MZ_ShowOnDisplay();
  wait10Msec(50);
}*/
