#ifndef MINIMAX_H
#define MINIMAX_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "tcurses.h"

extern int board[9];

void minimax_init(int board[9]){
    for(int i = 0; i < 9; i++){
        board[i] = 0;
    }
}

char minimax_parse(int n){
    switch (n)
    {
        case -1: return 'X';
        case  1: return 'O';
        default: return ' ';
    }
}

int minimax_win(const int board[9]) {
    // determina se algum jogador ganhou
    unsigned wins[8][3] = {{0,1,2},{3,4,5},{6,7,8},{0,3,6},{1,4,7},{2,5,8},{0,4,8},{2,4,6}};
    int i;
    for(i = 0; i < 8; ++i) {
        if(board[wins[i][0]] != 0 &&
           board[wins[i][0]] == board[wins[i][1]] &&
           board[wins[i][0]] == board[wins[i][2]])
            return board[wins[i][2]];
    }
    return 0;
}

int minimax(int board[9], int player){
	int winner = minimax_win(board);
	if(winner != 0)
		return winner*player;
	int move = -1;
	// Jogadas perdedoras sao preferiveis a nenhuma
    int score = -2;
	int i;
    for(i = 0; i < 9; ++i) { // para todos os campos,
        if(board[i] == 0) { // se for possivel jogar,
            board[i] = player; // tente mover
            int thisScore = -minimax(board, player*-1);
            // caso exista uma jogada melhor
            if(thisScore > score) {
                score = thisScore;
                move = i;
            } // joga onde for pior pro oponente            
			board[i] = 0;// reseta o tabuleiro
        }
    }
    if(move == -1)
		return 0;
    return score;
}

void minimax_move(int board[9], int player) {
		
    int move 	= -1;
    int score 	= -2;
        
    int i;
    for(i = 0; i < 9; ++i) {
        if(board[i] == 0) {
            board[i] = player;
            int tempScore = -minimax(board, player*-1);
            board[i] = 0;
            if(tempScore > score) {
                score = tempScore;
                move = i;
            }
        }
    }
    // retorna uma pontuacao baseada na arvore minimax 
    board[move] = player;
    
}

void minimax_rng_move(int board[9], int player, int jogadas){
	srand(rand()%time(NULL));
	int N_RNG = (rand()%2)+1;
	if(jogadas < N_RNG){ // primeira jogada RNG
		tcurses_render_string("RNG ativado\n", 5);
		int n;
		do {
			n = rand()%9;			
		} while(board[n] != 0);
		board[n] = player;
	} else {		
		minimax_move(board, player);		
	}
}

void minimax_draw(int b[9], int v[2]) {
	system("clear");
	printf(
        "vitorias:\nPlayer 1(O) -> %d\nPlayer 2(X) -> %d\n", v[0], v[1]);

    printf(" %c | %c | %c\n",minimax_parse(b[0]),minimax_parse(b[1]),minimax_parse(b[2]));
    printf("---+---+---\n");
    printf(" %c | %c | %c\n",minimax_parse(b[3]),minimax_parse(b[4]),minimax_parse(b[5]));
    printf("---+---+---\n");
    printf(" %c | %c | %c\n",minimax_parse(b[6]),minimax_parse(b[7]),minimax_parse(b[8]));
    printf("\n");
}

#endif  // MINIMAX_H
