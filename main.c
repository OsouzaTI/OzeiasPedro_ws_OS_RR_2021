#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>
#include <unistd.h>
#include "minimax.h"
#include "tcurses.h"

// prototipo
void* 	jogarIA(void* data);
void* 	finalizaJogo(void* data);
int 	ganhador();
void 	verificaGanhador(int* semID);
void 	verificaErro(int err);

// globais do minimax.h
int  board[9] = {0, 0, 0, 0, 0, 0,	0, 0, 0};
// globais do main
int  vitorias[2] 	= { 0 };     // vitorias do jogador 1 e 2
int  ultSemaforo	=  0; 		 // ID do ultimo semaforo utilizado
int  jogadas		=  0;		 // numero de jogadas
int  time_ms		=  10000;    // tempo de espera entre jogadas
// definindo os semaforos
sem_t S[3]; 					 // semaforos
int main()
{
	int err, i;		
	pthread_t tIA[2];  			// threads da IA
	pthread_t tGanhador; 		// thread que espera o fim do jogo

	// inicializando o curses
	tcurses_init();	

	// inicializando os semaforos
	for(i = 0; i < 3; i++)
		sem_init(&S[i], 0, 0);	
	
	// iniciando o primeiro semaforo
	sem_post(&S[0]);
	
	// ordem de execucao das threads
	int id[] = {0, 1, 2};
	for(i = 0; i < 2; i++){	
		err = pthread_create(&tIA[i], NULL, jogarIA, (void*)&id[i]);
		verificaErro(err);
	}
	err = pthread_create(&tGanhador, NULL, finalizaJogo, (void*)&id[2]);
	verificaErro(err);

	// espera alguem ganhar e termina a execucao
	pthread_join(tGanhador, NULL);	
	
	// finalizando o curses
	tcurses_end();
    return 0;
}

void verificaErro(int err){
	if(err != 0){
		printf("Erro na criacao da thread\n");
		exit(-1);
	}
}

// funcao que verifica se alguem ganhou
void verificaGanhador(int* semID){

	// variavel que indica se o numero de jogadas deve ser resetado
	int resetaJogadas = 0; 
	tcurses_render_board(board, vitorias);
	// verifica se alguem ganhou
	int verifica = minimax_win(board);	
	if(verifica == 0){	
		// verifica se o jogo empatou
		if(jogadas > 8){
			minimax_init(board);
			resetaJogadas = 1;
		}	
		sem_post(&S[ (*semID+1) % 2 ]);
	} else {
		getchar();
		// inicializa o tabuleiro
		minimax_init(board);
		resetaJogadas = 1;
		sem_post(&S[2]);	
	}
	// reseta as jogadas
	if(resetaJogadas)
		jogadas = 0;
}

// thread que espera um ganhador
void* finalizaJogo(void* data){
	int* semID = (int*)data;
	while(1){
		sem_wait(&S[*semID]);		
		vitorias[ultSemaforo]++;		
		sem_post(&S[0]);
	}
	pthread_exit(NULL);
}

// thread que faz a jogada da IA
void* jogarIA(void* data){
	// recebe seu id do semaforo
	int* semID = (int*)data;
	// id do player que esta jogando
	int playerID = (*semID) == 0 ? 1 : -1;	
	while(1){
		// espera o semaforo
		sem_wait(&S[*semID]);
		// guarda o semaforo atual
		ultSemaforo = *semID;		
		// jogando
		minimax_rng_move(board, playerID, jogadas);	
		// incrementa o numero de jogadas	
		jogadas++;		
		// espera x ms para verificar se alguem ganhou
		usleep(time_ms);
		verificaGanhador(semID);		
	}
	pthread_exit(NULL);	
}

