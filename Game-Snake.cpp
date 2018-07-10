#include <conio.h>
#include <math.h>
#include <stdio.h>
#include <windows.h>
#include<stdlib.h>
#include<time.h>

void mgotoxy (int x, int y){
	COORD p = {x,y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),p);
}

void setaMatriz (int altura, int largura){
	int x, y, mx, my;
    
    /* Muda a cor do texto */
    system("COLOR F0");
    
	/* Esquerda - Vertical */
	for (y=0; y<altura+2; y++){
		mgotoxy(0,y);
		printf("%c", 177);
	}
	
	/* Superior - Horizontal */
	for (x=0; x<largura+2; x++){
		mgotoxy(x,0);
		printf("%c", 177);
	}
	
	/* Direita - Vertical */ 
	for (y=0; y<altura+2; y++){
		mgotoxy(largura+1,y);
		printf("%c", 177);
	}
	
	/* Inferior - Horizontal */
	for (x=0; x<largura+2; x++){
		mgotoxy(x,altura+1);
		printf("%c", 177);
	}
}

void mudaCor (int tamanho){
	if (tamanho > 3){
		/* Muda a cor do texto */
    	system("COLOR F1");
	}
	if (tamanho > 6){
		/* Muda a cor do texto */
    	system("COLOR F2");
	}
	if (tamanho > 9){
		/* Muda a cor do texto */
    	system("COLOR F3");
	}
	if (tamanho > 12){
		/* Muda a cor do texto */
    	system("COLOR F4");
	}
	if (tamanho > 15){
		/* Muda a cor do texto */
    	system("COLOR F5");
	}
	if (tamanho > 18){
		/* Muda a cor do texto */
    	system("COLOR F6");
	}
	if (tamanho > 21){
		/* Muda a cor do texto */
    	system("COLOR F8");
	}
	if (tamanho > 25){
		/* Muda a cor do texto */
    	system("COLOR F9");
	}
	if (tamanho > 30){
		/* Muda a cor do texto */
    	system("COLOR FA");
	}
	if (tamanho > 40){
		/* Muda a cor do texto */
    	system("COLOR FB");
	}
	if (tamanho > 50){
		/* Muda a cor do texto */
    	system("COLOR FC");
	}
	if (tamanho > 100){
		/* Muda a cor do texto */
    	system("COLOR FD");
	}
}

int mexe (int altura, int largura, int pausa, int frutaX, int frutaY){
	char tecla = 'a';
	int direcao = 2, cobraX[300] = {1, 2}, cobraY[300] = {1, 2}, tamanho = 1, x, pontos = 0;
	
	while (tecla != 's'){
		while (tecla != 's' && !(tecla = kbhit())){
			/* Seta	 a cobra */
			for (x = tamanho; x > 0; x--){
				cobraX[x] = cobraX[x-1];
				cobraY[x] = cobraY[x-1];
			}
			
			if (direcao == 0) /* Move para a Esquerda */
			  cobraX[0]--;
			if (direcao == 1) /* Move para Baixo */
			  cobraY[0]--;
			if (direcao == 2) /* Move para a Direita */
			  cobraX[0]++;
			if (direcao == 3) /* Move para Cima */
			  cobraY[0]++;
			
			/* Desenha a cobra */
			mgotoxy(cobraX[tamanho], cobraY[tamanho]);
			printf(" ");
			mgotoxy(cobraX[0], cobraY[0]);
			printf("%c", 178);
			
			Sleep(pausa);
			
			/* Se a cobra colidir com a parede encerra a execução */
			if (cobraY[0] == 0 || cobraY[0] == altura + 1 || cobraX[0] == 0 || cobraX[0] == largura + 1){
				tecla = 's';
				/* Muda a cor do texto */
    			//system("COLOR OC");
				return pontos;
			}
			
			/* Verifica se a cobra comeu a fruta e reposiciona a mesma */
			if (cobraX[0] == frutaX && cobraY[0] == frutaY){
				tamanho++;
				pontos++;
				
				mudaCor (tamanho);
				
				/* Aumenta a velocidade a cada 3 pontos */
				if (pontos % 3 == 0)
					pausa -= 5;
				frutaX = (rand() % largura) + 1;
   				frutaY = (rand() % altura) + 1;
				
				/* Verifica se a fruta foi posicionada no corpo da cobra, se sim, reposiona a mesma */
				for(x = 0; x < tamanho; x++)
					if(frutaX == cobraX[x] && frutaY == cobraY[x]){
						frutaX = (rand() % largura) + 1;
   						frutaY = (rand() % altura) + 1;
					}
				
				mgotoxy (frutaX, frutaY);
				printf ("%c", 42);
			}
			
			/* Se a cobra colidir com a ela mesma encerra a execução */
			for(x = 1; x < tamanho; x++)
				if(cobraX[0] == cobraX[x] && cobraY[0] == cobraY[x]){
					tecla = 's';
					/* Muda a cor do texto */
    				//system("COLOR OC");
					return pontos;
				}
		}
		
		/* Guarda o valor da direção */
		if (tecla != 's')
			tecla = getch();
		if (tecla == 'K' && direcao != 2)       /* Move para a Esquerda */
			direcao = 0;
		else if (tecla == 'K' && direcao != 2)  /* Mantém movendo para a Direita */
			direcao = 2;
		if (tecla == 'H' && direcao != 3)       /* Move para Baixo */
			direcao = 1;
		else if (tecla == 'H' && direcao == 3)  /* Mantém movendo para Cima */
			direcao = 3;
		if (tecla == 'M' && direcao != 0)       /* Move para a Direita */
			direcao = 2;
		else if (tecla == 'M' && direcao == 0)  /* Mantém movendo para a Esquerda */
			direcao = 0;
		if (tecla == 'P' && direcao != 1)       /* Move para Cima */
			direcao = 3;
		else if (tecla == 'P' && direcao != 1)  /* Mantém movendo para Baixo */
			direcao = 1;
	}
}


int main(){
	int altura = 15, largura = 70, pausa = 100, frutaX, frutaY, pontos, velocidade;
	srand (time(NULL));
	
	frutaX = (rand() % largura) + 1;
   	frutaY = (rand() % altura) + 1;
    mgotoxy (frutaX, frutaY);
	printf ("%c", 42);
	
	mgotoxy (0,0);
	setaMatriz (altura, largura);
	
	pontos = mexe (altura, largura, pausa, frutaX, frutaY);
	velocidade = pausa + (pontos / 3) * 5;
	
	mgotoxy (0, altura + 1);
	printf("\n\nGAME OVER!");
	printf("\nTu fizeste %d pontos!", pontos);
	printf("\nSua velocidade final foi de %d!\n\n", velocidade);
}
