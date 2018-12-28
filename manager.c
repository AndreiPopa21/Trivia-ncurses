#include <ncurses.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "manager.h"
#include "structs.h"
#include <menu.h>

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

    char copyright[]={"copyright © Popa Stefan-Andrei"};
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
   // char del_mess[]={"Oops! Erased!"};
   // mvprintw(LINES/2,(COLS-strlen(del_mess))/2,del_mess);
    refresh();
}

void show_start_menu(GameStat* gameStat, int canResume){

    char* choices[]={
        "New Game",
        "Resume Game",
        "Quit",
    };

    char welcome_text[]={"Welcome to Trivia"};
    mvprintw(2,(COLS-strlen(welcome_text))/2,"%s",welcome_text);
    refresh();

    print_copyrights(stdscr);

    ITEM **my_items;
    MENU *myMenu;
    int n_choices=3;
    ITEM* curr_item;
    WINDOW* my_menu_window;

    int width=26;

    my_menu_window=newwin(10,width,LINES/2-5,COLS/2-width/2);
    keypad(my_menu_window,TRUE);

    my_items=(ITEM **)calloc(n_choices+1,sizeof(ITEM *));
    
    int i;
    for(i=0;i<n_choices;++i){
        my_items[i]=new_item(choices[i],NULL);
    }
    my_items[n_choices]=(ITEM*)NULL;
    myMenu=new_menu((ITEM**)my_items);

    set_menu_win(NULL,my_menu_window);
    set_menu_sub(myMenu,derwin(my_menu_window,6,width-2,3,2));
    set_menu_mark(myMenu," ");
    
    box(my_menu_window,0,0);


    post_menu(myMenu);
    wrefresh(my_menu_window);

    int break_out=false;
    
    int c;
    while(!break_out)
	{   
        c = wgetch(my_menu_window);    
        switch(c)
	        {	case KEY_DOWN:
				menu_driver(myMenu, REQ_DOWN_ITEM);
				break;
			case KEY_UP:
				menu_driver(myMenu, REQ_UP_ITEM);
				break;
			case 10:
				//mvprintw(LINES-2,1,"BUNAA\n");
				//refresh();
                break_out=true;
				break;
            case KEY_F(1):
                break_out=true;
                break;
		    }
            
        wrefresh(my_menu_window);
	}	

    unpost_menu(myMenu);
   
    for(i = 0; i < n_choices; ++i){
        free_item(my_items[i]);
    }
    free_menu(myMenu);
    wborder(my_menu_window, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
    wrefresh(my_menu_window);
    delwin(my_menu_window);
    //refresh();
    getch();
}

void display_question(Question* question){
    move(0,0);
    hline('%',COLS);
    vline('H',LINES);
    mvvline(0,COLS-1,'H',LINES);
    mvhline(LINES-1,0,'%',COLS);
    refresh();
  }

void start_new_game(){

}

void resume_game(GameStat* gameStat){

}

void quit_trivia(){

}

void print_copyrights(WINDOW* wind){

    char copyright[]={"copyright © Popa Stefan-Andrei"};
    mvwprintw(wind,LINES-2,(COLS-strlen(copyright))/2,"%s",copyright);
    refresh();
}