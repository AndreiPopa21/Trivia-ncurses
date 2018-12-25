#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>

int main(){

    initscr();
    cbreak();    
    printw("Hello Ncurses\n");
    getch();
    endwin(); 
    return 0;
}