#include <ncurses.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "manager.h"

void splash_screen(){
    
    hline('%',COLS);
    vline('H',LINES);
    mvvline(0,COLS-1,'H',LINES);
    mvhline(LINES-1,0,'%',COLS);
    refresh();

    char line0[]={"                                  "};
    char line1[]={"MMMMMMMMMM         O            O         "};
    char line2[]={"    HH    MMMMM                     ####  "};
    char line3[]={"    HH    H    H   H V       V  H  I    I "};
    char line4[]={"    HH    HMMMM    H  V     V   H  WRRRRW "};
    char line5[]={"    HH    H  H     H   V   V    H  W    W "};
    char line6[]={"    HH    H   H    H    V V     H  H    H "};
    char line7[]={"    HH    H    H   H     V      H  H    H "};

    int midY= LINES/2;
    int midX= COLS/2;
    
    int i;
    int offset = -(midY-LINES/4);
    move(midY+offset,midX-strlen(line1)/2);
    printw("%s",line1);
    refresh();
    napms(42);
    move(midY+offset+1,midX-strlen(line2)/2);
    printw("%s",line2);
    refresh();
    napms(42);
    move(midY+offset+2,midX-strlen(line3)/2);
    printw("%s",line3);
    refresh();
    napms(42);
    move(midY+offset+3,midX-strlen(line4)/2);   
    printw("%s",line4);
    refresh();
    napms(42);
    move(midY+offset+4,midX-strlen(line5)/2);
    printw("%s",line5);
    refresh();
    napms(42);
    move(midY+offset+5,midX-strlen(line6)/2);
    printw("%s",line6);
    refresh();
    napms(42);
    move(midY+offset+6,midX-strlen(line7)/2);
    printw("%s",line7);
    refresh();
    napms(42);   

    char copyright[]={"copyright © Popa Stefan"};
    move(LINES-3,midX-strlen(copyright)/2);
    for(int i=0;i<strlen(copyright);i++){
        printw("%c",copyright[i]);
        refresh();
        napms(42);
    }
    
    char press_any_key[]={"- press any key to continue -"};
    int yLoc = midY+ LINES/4;
    nodelay(stdscr,TRUE);

    char c;
       while(1){
           c = getch();
           if(c>0){
               nodelay(stdscr,FALSE);
               break;
           }
        attron(A_REVERSE);
        move(yLoc,midX-strlen(press_any_key)/2);
        printw("%s",press_any_key);
        refresh();
        napms(400);
        c = getch();
           if(c>0){  
               nodelay(stdscr,FALSE);
               break;
           }
        attroff(A_REVERSE);
        move(yLoc,midX-strlen(press_any_key)/2);
        printw("%s",press_any_key);
         refresh();
        napms(400);
       }
    
}

void del_splash_screen(){
    attroff(A_REVERSE);
    int i,j;
    for(i=LINES-1;i>=0;i--){
        for(j=0;j<COLS;j++){
            mvprintw(i,j," ");
        }
        refresh();
        napms(42);
    }
    char del_mess[]={"Oops! Erased!"};
    mvprintw(LINES/2,(COLS-strlen(del_mess))/2,del_mess);
    refresh();
}
