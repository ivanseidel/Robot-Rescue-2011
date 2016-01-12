/*
*******************FUNCOES DE ESTADOS****************************
*/

/*Estados existentes
#define ST_DEFAULT 0
#define ST_INIT    1


int    P_ESTADO_MAX       = 1;*/
int    G_ESTADO_TARGET    = 0;
int    G_ESTADO_ATUAL     = 0;

//Seta o estado no qual deseja estar
bool ESTADO_SET_TARGET(int ESTADO_TARGET){

  if(ESTADO_TARGET<=P_ESTADO_MAX)
  {
    G_ESTADO_TARGET=ESTADO_TARGET;
    return true;
  }else{
    ERRO_SET_CODE("ESTADO INEXISTENTE");
    return false;
  }
}

//Chamado para dizer em qual estado esta, no comeco de cada funcao de estado
sub ESTADO_SET_ESTADO()
{
  G_ESTADO_ATUAL = G_ESTADO_TARGET;

}

//Retorna FALSO se tiver que mudar de estado
bool ESTADO_IS_CURRENT(){
  return G_ESTADO_TARGET==G_ESTADO_ATUAL? true:false;
}

/*
task main(){
  //StartTask(MULTI_TASKING);
  while(1)
  {
    //Seleciona estado atual
    ESTADO_SET_ESTADO();
    switch(G_ESTADO_TARGET)
    {

      //default
      case ST_DEFAULT:
        F_STATE_0();
        break;

      //estado 1
      case ST_INIT:
        F_STATE_1();
        break;

      default:
        ERRO_SET_CODE("ESTADO INEXISTENTE");
        break;
    }
  }
}
*/
