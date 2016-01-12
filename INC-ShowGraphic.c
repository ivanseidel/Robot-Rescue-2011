int AUlt[500];
//Modifica as configuracoes do grafico
int SG_pos=1, SG_configs=4,SG_jump=1, SG_update, SG_exit,SG_ySpace=1,SG_yScale=1,SG_xSpace=1;
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
		  	nxtDisplayTextLine(1, "Jump: %i", SG_jump);
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
		  	nxtDisplayTextLine(1, "yScale: %i", SG_yScale);
		  }else{
		  	SG_yScale+=change;
		  }
		  break;
	  //Case 4: Exit
		case 4:
		  if(change==0){
		  	nxtDisplayTextLine(1, "ySpace: %i", SG_ySpace);
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
	if(nNxtButtonPressed == 3){
		while(nNxtButtonPressed != -1 && time100[T1]<3){
	  }
		PlayTone(100,4);
	  SG_Change();
	}
	if(nNxtButtonPressed == 1){
		while(nNxtButtonPressed != -1 && time100[T1]<3){
	  }
		PlayTone(250,4);
		SG_Config(1);
	}
	if(nNxtButtonPressed == 2){
		while(nNxtButtonPressed != -1 && time100[T1]<3){
	  }
		PlayTone(250,4);
		SG_Config(-1);
	}
}
void SG(int samples){

	PlayTone(300,10);
	//De quantos em quantos valores ele ira ler
	if(samples<=100){
		SG_jump=1;
	}else{
		SG_jump=2;
	}
	//Configs: Jump, yScale, EXIT
	eraseDisplay();
	SG_ySpace=0;
	SG_yScale=2;
	SG_update=0;
	SG_exit=0;
	SG_pos=1;
	SG_xSpace=1;
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
