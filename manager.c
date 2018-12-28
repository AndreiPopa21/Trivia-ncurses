#include <ncurses.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "manager.h"
#include "structs.h"
#include "utils.h"
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

    char copyright[]={"copyrights © Popa Stefan-Andrei"};
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

    wmove(stdscr,LINES/4,COLS/2);
    print_question_mark(stdscr,3,3);
    print_question_mark(stdscr,3,COLS-15);

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
    set_item_userptr(my_items[0],start_new_game);
    set_item_userptr(my_items[1],resume_game);
    set_item_userptr(my_items[2],quit_trivia);

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
    int toQuit=0;

    while(!break_out)
	{   
        c = wgetch(my_menu_window);    
        switch(c)
	        {	
            case KEY_DOWN:
				menu_driver(myMenu, REQ_DOWN_ITEM);
				break;

			case KEY_UP:
				menu_driver(myMenu, REQ_UP_ITEM);
				break;

			case 10:
                break_out=true;
                ITEM* cur = current_item(myMenu);
                int curr_item_index = item_index(cur);
                switch(curr_item_index){
                    case 0:
                        start_new_game();
                        break;
                    case 1:
                        resume_game(NULL);
                        break;
                    case 2:
                        toQuit=true;
                        break;
                }
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
    refresh();
    erase();
    refresh();
    //getch();
    if(toQuit){
        quit_trivia();
    }
    //getch();
}

void display_question(Question* question, int index){
    move(0,0);
    hline('%',COLS);
    vline('H',LINES);
    mvvline(0,COLS-1,'H',LINES);
    mvhline(LINES-1,0,'%',COLS);
    refresh();
    print_copyrights(stdscr);
    print_question_index(stdscr,index);
    print_question_sentence(stdscr,question->question);
    print_fifty_option(stdscr);
    print_skip_option(stdscr);
    print_indications(stdscr);

   /* ITEM **my_items;
    MENU *my_menu;
    WINDOW *my_menu_win;
    int n_choices=4;

    my_items = (ITEM **)calloc(n_choices, sizeof(ITEM *));
   // my_items[0]=(ITEM*)NULL;
    my_items[0]=new_item(question->a_answer,NULL);
    my_items[1]=new_item(question->b_answer,NULL);
    my_items[2]=new_item(question->c_answer,NULL);
    my_items[3]=new_item(question->d_answer,NULL);

  

    my_menu = new_menu((ITEM **)my_items);

   // menu_opts_off(my_menu, O_SHOWDESC);

    my_menu_win = newwin(10,COLS/2+COLS/4,LINES/2,COLS/8);
    keypad(my_menu_win, TRUE);
   
    set_menu_win(my_menu, my_menu_win);
    WINDOW* subwind = derwin(my_menu_win, 8, COLS/2+COLS/4 -2,1,1);
    set_menu_sub(my_menu, subwind );
    
    set_menu_format(my_menu, 2, 4);

    post_menu(my_menu);

   
    box(my_menu_win,0,0);
    box(subwind,0,0);
    wrefresh(subwind);
    wrefresh(my_menu_win);
    refresh();*/

    WINDOW* answers_window;

    int len_a= strlen(question->a_answer);
    int len_b= strlen(question->b_answer);
    int len_c= strlen(question->c_answer);
    int len_d= strlen(question->d_answer);

    int len[4]={len_a,len_b,len_c,len_d};

    int max1= len[0];
    for(int i=1;i<4;i++){
        if(len[i]>max1){
            max1=len[i];
        }
    }
    //printw(1,1,"%d",max1);
    //printf("%d\n",max1);
    //refresh();  
    answers_window=newwin(11,max1+8,LINES/2-LINES/8,(COLS-max1-8)/2);
    keypad(answers_window,TRUE);
    int win_x;
    int win_y;
    getmaxyx(answers_window,win_y,win_x);
    //printf("%d | %d\n",win_y,win_x);
    mvwprintw(answers_window,2,(win_x-len_a)/2,"%s",question->a_answer);
    mvwprintw(answers_window,4,(win_x-len_b)/2,"%s",question->b_answer);
    mvwprintw(answers_window,6,(win_x-len_c)/2,"%s",question->c_answer);
    mvwprintw(answers_window,8,(win_x-len_d)/2,"%s",question->d_answer);
    wrefresh(answers_window);

    box(answers_window,0,0);
    wrefresh(answers_window);
    refresh();

    int curr_selected=0;
    int breakOut=0;
    int toHighlight=0;
    int c;
    int line=2;

    mvwprintw(answers_window,line,1,"->");
    wrefresh(answers_window);

    while(!breakOut){

        toHighlight=0;
        c=wgetch(answers_window);
        switch(c){
            case KEY_UP:
                curr_selected-=1;
                if(curr_selected<0)
                    curr_selected+=4;
                curr_selected=curr_selected%4;
                //mvprintw(LINES-2,1,"%d",curr_selected);
                //refresh();
                toHighlight=1;
                break;
            case KEY_DOWN:
                curr_selected+=1;
                curr_selected=curr_selected%4;
                toHighlight=1;
                //mvprintw(LINES-2,1,"%d",curr_selected);
                //refresh();
                break;
            case 10:
                breakOut=1;
                mvprintw(LINES-2,1," Ai selectat: %d",curr_selected+1);
                refresh();
                break;
            case 113:
                breakOut=1;
                break;
            default:
                break;
        }
        mvwprintw(answers_window,line,1,"  ");
        wrefresh(answers_window);
        if(toHighlight){
             switch(curr_selected){
            case 0:
                line=2;
                break;
            case 1:
                line =4;
                break;
            case 2:
                line =6;
                break;
            case 3:
                line = 8;
                break;
        }
        mvwprintw(answers_window,line,1,"->");
        wrefresh(answers_window);
        }    
    }


   /* int A_POS_X = 2;
    int A_POS_Y = 2;
    int B_POS_X= COLS/2+1;
    int B_POS_Y = 2;
    int C_POS_X = 2;
    int C_POS_Y = 4;
    int D_POS_X = COLS/2+1;
    int D_POS_Y = 4;

    mvwprintw(answers_window,A_POS_Y,A_POS_X,question->a_answer); 
    mvwprintw(answers_window,B_POS_Y,B_POS_X,question->b_answer); 
    mvwprintw(answers_window,C_POS_Y,C_POS_X,question->c_answer); 
    mvwprintw(answers_window,D_POS_Y,D_POS_X,question->d_answer); */


    getch();
}

void start_new_game(){
    char start_game_mess[]={"You pressed start game"};
    move(LINES-4,0);
    clrtoeol();
    mvprintw(LINES-4,(COLS-strlen(start_game_mess))/2,"%s",start_game_mess);
    refresh();
    getch();
}

void resume_game(GameStat* gameStat){
    char resume_game_mess[]={"You pressed resume game"};
    move(LINES-4,0);
    clrtoeol();
    mvprintw(LINES-4,(COLS-strlen(resume_game_mess))/2,"%s",resume_game_mess);
    refresh();
    getch();
}

void quit_trivia(){
    endwin();
}

