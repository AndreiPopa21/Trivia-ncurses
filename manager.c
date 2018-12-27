#include <ncurses.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "manager.h"


void splash_screen(){
    //printw("Dimensiunile ecranului sunt: %d| %d\n", LINES,COLS);
    //mvprintw(LINES-1,COLS-1,"+");
    //vline("*",1);
    hline('*',COLS);
    vline('|',LINES);
    mvvline(0,COLS-1,'|',LINES);
    mvhline(LINES-1,0,'*',COLS);
    
    char line0[]={"                                  "};
    char line1[]={"MMMMMMMMMM        o           o       "};
    char line2[]={"    HH    MMMM                    ### "};
    char line3[]={"    HH    H   H   H  V     V  H  I   I"};
    char line4[]={"    HH    HMMM    H   V   V   H  W R W"};
    char line5[]={"    HH    H  H    H    V V    H  W   W"};
    char line6[]={"    HH    H   H   H     V     H  H   H"};
    char line7[]={"                                  "};

    int midY= LINES/2;
    int midX= COLS/2;
    //mvprintw(midY,midX,"Hello");
    
    int i;
    int offset = -(midY-LINES/4);
    move(midY+offset,midX-strlen(line1)/2);
    printw("%s",line1);
    move(midY+offset+1,midX-strlen(line2)/2);
    printw("%s",line2);
    move(midY+offset+2,midX-strlen(line3)/2);
    printw("%s",line3);
    move(midY+offset+3,midX-strlen(line4)/2);   
    printw("%s",line4);
    move(midY+offset+4,midX-strlen(line5)/2);
    printw("%s",line5);
    move(midY+offset+5,midX-strlen(line6)/2);
    printw("%s",line6);   

    char copyright[]={"copyright - Popa Stefan"};
    move(LINES-3,midX-strlen(copyright)/2);
    printw("%s",copyright); 
    
    
    char press_any_key[]={"- press any key to continue -"};
    int yLoc = midY+ LINES/4;
    nodelay(stdscr,TRUE);

       while(1){
           char c = getch();
           if(c>=97){
               
               nodelay(stdscr,FALSE);
               break;
           }
        attron(A_REVERSE);
        move(yLoc,midX-strlen(press_any_key)/2);
        printw("%s",press_any_key);
        refresh();
        napms(500);
        attroff(A_REVERSE);
        move(yLoc,midX-strlen(press_any_key)/2);
        printw("%s",press_any_key);
         refresh();
        napms(500);
       }
    printf("DOamne\n");
}