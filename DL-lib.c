//Programa que cria arquivo e data loga por determinado tempo, numero de vezes ou infinitamente
const string sFileName = "DataLog.txt";
TFileIOResult nIoResult;
TFileHandle hFileHandle;
int nFileSize 					= 7000;
bool setup=false;

//Inicia um datalog
void DL_Init(int read=0){
	setup=true;
	Delete(sFileName, nIoResult);
	hFileHandle = 0;
	OpenWrite(hFileHandle, nIoResult, sFileName, nFileSize);
}
//Insere dados
void DL_Insert(string data){
	if(setup){
	  WriteString(hFileHandle, nIoResult, data+"\n");
	}
}
//Fecha um datalog
void DL_Close(){
	if(setup){
    Close(hFileHandle, nIoResult);
  }
}
