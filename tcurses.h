#ifndef RENDER_CURSES_H
#define RENDER_CURSES_H

#include <stdio.h>
#include <stdlib.h> 
#include <curses.h> 
#include <unistd.h>

void tcurses_render_string(const char* str, int color_pair){
    attron(COLOR_PAIR(color_pair));
    printw("%s", str);                
    attroff(COLOR_PAIR(color_pair));
}
void tcurses_render_char(const char c, int color_pair){
    attron(COLOR_PAIR(color_pair));
    printw(" %c ", c);                
    attroff(COLOR_PAIR(color_pair));
}

char tcurses_parse(int n){
    switch (n)
    {
        case -1: return 'X';
        case  1: return 'O';
        default: return ' ';
    }
}

void tcurses_init(){
    initscr();    
    start_color();
    init_pair(1, COLOR_RED,     COLOR_BLACK);
    init_pair(2, COLOR_BLUE,    COLOR_BLACK);
    init_pair(3, COLOR_GREEN,   COLOR_BLACK);
    init_pair(4, COLOR_YELLOW,  COLOR_BLACK);
    init_pair(5, COLOR_MAGENTA, COLOR_BLACK);
}

void tcurses_end(){
    endwin();
}


void tcurses_render_board(int board[9], int v[2]){
    clear();
    attron(COLOR_PAIR(4));
    printw("vitorias:\nPlayer 1(O) -> %d\nPlayer 2(X) -> %d\n", v[0], v[1]);
    attron(COLOR_PAIR(4));
    printw("\n");
    for(int i = 0; i < 9; i++){     
        int cond = (((i+1) % 3) == 0);
        if(board[i] == -1)
            tcurses_render_char(tcurses_parse(board[i]), 1);                                
        else if(board[i] == 1)
            tcurses_render_char(tcurses_parse(board[i]), 3);                
        else
            tcurses_render_char(' ', 1);
        if(cond){
            printw("\n");
            if(i < 8)tcurses_render_string("----+-----+----\n", 2);        
        }else{ tcurses_render_char('|', 2); }

    }
    usleep(500000);
    refresh();
}

#endif