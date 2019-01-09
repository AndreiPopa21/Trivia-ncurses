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

    //char line0[]={"                                  "};
    char line1[]={"MMMMMMMMMM         O            O         "};
    char line2[]={"    HH    MMMMM                     ####  "};
    char line3[]={"    HH    H    H   W W       W  W  H    H "};
    char line4[]={"    HH    HMMMM    W  W     W   W  WRRRRW "};
    char line5[]={"    HH    H  W     W   W   W    W  W    W "};
    char line6[]={"    HH    H   W    W    W W     W  H    H "};
    char line7[]={"    HH    H    W   W     W      W  H    H "};

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
    move(LINES-2,midX-strlen(copyright)/2);
    for( i=0;i<strlen(copyright);i++){
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
    refresh();
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

GameStat start_menu(GameStat gameStat,Question* all_questions, int q_total_count){

    int quitGame=0;
    while(!quitGame){

        clear();
        move(0,0);
        hline('%',COLS);
        vline('H',LINES);
        mvvline(0,COLS-1,'H',LINES);
        mvhline(LINES-1,0,'%',COLS);
        
        int breakOut = 0;
        int createNewGame = 0;
        int howToPlay=0;
        int leaderboard=0;

        print_welcome_message(stdscr);
        wmove(stdscr,LINES/4,COLS/2);
        print_question_mark(stdscr,3,3);
        print_question_mark(stdscr,3,COLS-15);
        print_copyrights(stdscr);

         
        char* choices[]={
                "New Game",
                "Resume Game",
                "Quit",
                "How to play",
                "Leaderboard"
            };
        ITEM **my_items;
        MENU *myMenu;
        int n_choices=5;
        //ITEM* curr_item;
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


        if(gameStat.toResume){
            print_resume_for_game();
        }

        int c;
        while(!breakOut)
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
                    breakOut=0;
                    ITEM* cur = current_item(myMenu);
                    int curr_item_index = item_index(cur);
                    unprint_no_game_to_resume();

                    switch(curr_item_index){
                        case 0:
                            breakOut=1;
                            createNewGame=1;
                            mvprintw(LINES/2,2,"Create");
                            refresh();
                            break;

                        case 1:
                            if(gameStat.toResume){
                                mvprintw(LINES/2,2,"Resume");
                                refresh();
                                breakOut=1;
                            }else{
                               // mvprintw(LINES/2,2,"create first!!");
                                //refresh();
                                print_no_game_to_resume();
                            }
                            break;

                        case 2:
                            mvprintw(LINES/2,2,"Quit");
                            refresh();
                            breakOut=1;
                            quitGame=1;
                            break;
                        
                        case 3:
                            //show_how_to_play();
                            breakOut=1;
                            howToPlay=1;
                            break;
                        
                        case 4:
                            breakOut=1;
                            leaderboard=1;
                            break;

                        default:
                            break;
                    }       
                    wrefresh(my_menu_window);
                    break;

                default:
                    break;
	        }
        }	
        
        unpost_menu(myMenu);
   
        for(i = 0; i < n_choices; ++i){
            free_item(my_items[i]);
        }
        //free(my_items);
        free_menu(myMenu);
        wborder(my_menu_window, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
        wrefresh(my_menu_window);
        delwin(my_menu_window);
        refresh();
        erase();
        refresh();
        
        if(quitGame){
            // printf("You chose to quit the game\n");
            //quitting game
            //show Are You sure you want to leave?
        }else{
            if(createNewGame){
                createNewGame=0;

                gameStat = initializeGameStat();

                //Question* session_questions = (Question*)malloc((gameStat.questions_count+1)*sizeof(Question));
                shuffleQuestions(all_questions,q_total_count,gameStat);

                /*for(int i=0;i<=gameStat.questions_count;i++){
                    session_questions[i]=all_questions[i];
                }*/
                gameStat.random_set=all_questions;
                
                gameStat=game_session(gameStat);
                
                //free(session_questions);

            }else{
                if(howToPlay){
                    show_how_to_play();
                }else{
                    if(leaderboard){
                        display_leaderboard();
                    }
                    else{
                        if(gameStat.toResume){

                        printf("A game is being resumed...\n");
                        gameStat.toResume = 0;

                        gameStat = game_session(gameStat);

                        }
                    }
                }
               //else an Options screen could be implemented
            }
        }
    }
    return gameStat;
   // getch();
}

GameStat game_session(GameStat gameStat){

    int startIndex = gameStat.curr_question_index;
    if(gameStat.didSkip){
        startIndex-=1;
    }
    int maxIndex = gameStat.questions_count;
    int i=0;

    for(i=startIndex;i<=maxIndex && !gameStat.toResume; ){
           
            gameStat = show_question(gameStat,i);
            if(gameStat.toResume){
               /* mvprintw(LINES/2+2,2,"B");
                refresh();
                getch();*/
            }else{
                if(gameStat.skipping){
                    gameStat.skipping=0;
                    gameStat.curr_question_index+=1;
                
                 }else{
                    gameStat.curr_question_index+=1;
                    gameStat.fiftyEncoded = 0;
                 
                    i++;
                }
            }
            
    }

    if(i>maxIndex){
        gameStat.isGameFinished = 1;
        gameStat.toResume = 0;
    }

    if(gameStat.isGameFinished){
        show_score(gameStat);
    }

    return gameStat;
}

GameStat show_question(GameStat gameStat,int i){

    clear();
    refresh();
    move(0,0);
    hline('%',COLS);
    vline('H',LINES);
    mvvline(0,COLS-1,'H',LINES);
    mvhline(LINES-1,0,'%',COLS);
    refresh();

    print_copyrights(stdscr);
    print_question_index(stdscr,i,gameStat.questions_count);
    print_indications(stdscr);

    Question* curr_question = gameStat.random_set+(gameStat.curr_question_index-1); //atata timp cat indexul incepe cu 1
    print_question_sentence(stdscr,curr_question->question);

    if(!gameStat.didSkip){
        print_skip_option(stdscr);
    }
    
    int right_answer_index = get_right_answer_index(curr_question);

    int navigation_map[4]={1,2,3,4};
    int show_options_map[4]={1,1,1,1};

    if(!gameStat.didFifty){
         print_fifty_option(stdscr);
    }else{
        if(gameStat.fiftyEncoded!=0){
            int firstOption = gameStat.fiftyEncoded % 10;
            int secondOption = gameStat.fiftyEncoded / 10;

            if(firstOption>secondOption){
                int aux = firstOption;
                firstOption=secondOption;
                secondOption=aux;
            }

            navigation_map[0] = firstOption;
            navigation_map[1] = secondOption;
            navigation_map[2] = firstOption;
            navigation_map[3] = secondOption;
            
            int i; 
            for(i=0;i<4;i++){
                show_options_map[i]=0;
            }
            show_options_map[firstOption-1]=1;
            show_options_map[secondOption-1]=1;
        }
    }
   
    refresh_current_score(gameStat);
    refresh_local_hour_date(stdscr);

    WINDOW* answers_window;

    int len_a= strlen(curr_question->a_answer);
    int len_b= strlen(curr_question->b_answer);
    int len_c= strlen(curr_question->c_answer);
    int len_d= strlen(curr_question->d_answer);

    int len[4]={len_a,len_b,len_c,len_d};

    int max1= len[0];
    for(int i=1;i<4;i++){
        if(len[i]>max1){
            max1=len[i];
        }
    }
    
    answers_window=newwin(11,max1+8,LINES/2-LINES/8,(COLS-max1-8)/2);
    keypad(answers_window,TRUE);

    print_answers(answers_window,curr_question,show_options_map,len_a,len_b,len_c,len_d);
    print_answers_cursor(gameStat,answers_window,show_options_map);
    
    wrefresh(answers_window);
    box(answers_window,0,0);
    wrefresh(answers_window);
    refresh();
    
    int c;
    int breakOut = 0;
    int oldPosition;
    int newPosition;
    int j;


    while(!breakOut){
        

        c=wgetch(answers_window);
        switch(c){
            case KEY_UP:
                gameStat = navigate_answers(navigation_map,gameStat,1,answers_window);
                break;

            case KEY_DOWN:
                gameStat = navigate_answers(navigation_map,gameStat,0,answers_window);
                break;
            
            case 97:
                if(show_options_map[0]){
                 
                    oldPosition = (*(navigation_map+gameStat.curr_nav_position))*2;
                    mvwprintw(answers_window,oldPosition,1,"  ");
                    for(j=0;j<4;j++){
                        if(navigation_map[j]==1){
                            gameStat.curr_nav_position=j;
                            break;
                        }
                    }
                    newPosition = (*(navigation_map+gameStat.curr_nav_position))*2;
                    mvwprintw(answers_window,newPosition,1,"->");
                    wrefresh(answers_window);
                }
                break;
            
            case 98:
                if(show_options_map[1]){
                 
                    oldPosition = (*(navigation_map+gameStat.curr_nav_position))*2;
                    mvwprintw(answers_window,oldPosition,1,"  ");
                    for(j=0;j<4;j++){
                        if(navigation_map[j]==2){
                            gameStat.curr_nav_position=j;
                            break;
                        }
                    }
                    newPosition = (*(navigation_map+gameStat.curr_nav_position))*2;
                    mvwprintw(answers_window,newPosition,1,"->");
                    wrefresh(answers_window);
                }
                break;
            
            case 99:
                if(show_options_map[2]){
                   
                    oldPosition = (*(navigation_map+gameStat.curr_nav_position))*2;
                    mvwprintw(answers_window,oldPosition,1,"  ");
                    for(j=0;j<4;j++){
                        if(navigation_map[j]==3){
                            gameStat.curr_nav_position=j;
                            break;
                        }
                    }
                    newPosition = (*(navigation_map+gameStat.curr_nav_position))*2;
                    mvwprintw(answers_window,newPosition,1,"->");
                    wrefresh(answers_window);
                }
                break;
            
            case 100:
                if(show_options_map[3]){
              
                    oldPosition = (*(navigation_map+gameStat.curr_nav_position))*2;
                    mvwprintw(answers_window,oldPosition,1,"  ");
                    for(j=0;j<4;j++){
                        if(navigation_map[j]==4){
                            gameStat.curr_nav_position=j;
                            break;
                        }
                    }
                    newPosition = (*(navigation_map+gameStat.curr_nav_position))*2;
                    mvwprintw(answers_window,newPosition,1,"->");
                    wrefresh(answers_window);
                }
                break;

            case 10:
                breakOut=1;
                int player_choice = navigation_map[gameStat.curr_nav_position];
                if(player_choice==right_answer_index){
                    mvprintw(LINES/2,2,"BRAVO! AI SELECTAT CORECT");
                    gameStat.right_answers+=1;
                }else{
                    mvprintw(LINES/2,2,"UPS,NU AI FACUT FOARTE BINE");
                    gameStat.wrong_answers+=1;
                }
                gameStat.curr_nav_position=0;
               
                break;

            case 102:
                if(!gameStat.didFifty){
                    gameStat.didFifty=1;
                    
                    unprint_fifty_option(stdscr);
                    gameStat = useFifty(gameStat,curr_question,navigation_map,show_options_map);
                  
                    wclear(answers_window);
                    box(answers_window,0,0);
                    print_answers(answers_window,curr_question,show_options_map,len_a,len_b,len_c,len_d);
                    gameStat=print_answers_cursor(gameStat,answers_window,show_options_map);
                    
                    refresh();
                }
                break;

            case 103:
                if(!gameStat.didSkip){
                    gameStat.didSkip=1;
                    gameStat.skipping=1;
                    gameStat.fiftyEncoded=0;
                    gameStat.curr_nav_position=0;
                    unprint_skip_option(stdscr);
                    refresh();
                    breakOut=1;
                }
                break;

            case 113:
                breakOut=1;
                gameStat.toResume=1;
                gameStat.curr_nav_position=0;
                break;

            case 114:
                refresh_local_hour_date();
                break;

            default:
                break;
        }
    }
    wclear(answers_window);
    clear();
    refresh();
    

    return gameStat;
}

void show_score(GameStat gameStat){

    move(0,0);
    hline('%',COLS);
    vline('H',LINES);
    mvvline(0,COLS-1,'H',LINES);
    mvhline(LINES-1,0,'%',COLS);
    refresh();
    
    double right_percentage = ((double)gameStat.right_answers * 100)/(double)gameStat.questions_count;

    if(right_percentage>=75){
        print_happy_score(stdscr,gameStat);
    }else{
        if(right_percentage>=50){
            print_normal_score(stdscr,gameStat);
        }else{
            print_sad_score(stdscr,gameStat);
        }
    }
    print_copyrights(stdscr);
    getch();
    clear();
    save_score_to_leaderboard(gameStat);
}

void show_how_to_play(){
    
    clear();
    move(0,0);
    hline('%',COLS);
    vline('H',LINES);
    mvvline(0,COLS-1,'H',LINES);
    mvhline(LINES-1,0,'%',COLS);

    int vertical_offset=4;
    char up_down_nav_mess[]={"Navigation in menus is done with UP and DOWN keys, ENTER for selection"};
    char a_b_c_d_mess[]={"You could press A, B, C, D for faster selection, then press ENTER to confirm"};
    char menu_highlight_mess[]={"Every current option is highlighted"};
    char fifty_option[]={"Press F in oder to use Fifty-Fifty option inside game"};
    char skip_option[]={"Press B in order to use Skip option inside game"};
    char quite_option[]={"Press Q in order to turn back in-game to the Main Menu"};
    char refresh_date[]={"Press R in-game if you wish to refresh the current date and time"};
    char return_to_menu[]={"-press any key-"};

    mvprintw(vertical_offset-1,4,"%s",up_down_nav_mess);
    mvprintw(vertical_offset,4,"%s",a_b_c_d_mess);
    mvprintw(vertical_offset+1,4,"%s",menu_highlight_mess);
    mvprintw(vertical_offset+3,4,"%s",fifty_option);
    mvprintw(vertical_offset+4,4,"%s",skip_option);
    mvprintw(vertical_offset+6,4,"%s",quite_option);
    mvprintw(vertical_offset+7,4,"%s",refresh_date);
    mvprintw(LINES-3,(COLS-strlen(return_to_menu))/2,"%s",return_to_menu);

    refresh();
    getch();
    clear();
}

void save_score_to_leaderboard(GameStat gameStat){
    clear();
    move(0,0);
    hline('%',COLS);
    vline('H',LINES);
    mvvline(0,COLS-1,'H',LINES);
    mvhline(LINES-1,0,'%',COLS);
    refresh();

    char type_name[]={"Type your name (max.20): "};
    mvprintw(LINES/2,6,"%s",type_name);
    curs_set(1);
    echo();
    refresh();
    int breakOut=0;
    char name[20]={0};
    int charCount=0;

    int toCommitToLeaderbooard=0;

    while(!breakOut && charCount<=20){
        char c = getch();
        int c_code= c;
        switch(c_code){
            case 10:
                if(charCount>0){
                    toCommitToLeaderbooard=1;
                }
                breakOut=1;
                break;
            default:
                strcat(name,&c);
                charCount++;
                break;
        }
    }
    if(toCommitToLeaderbooard){
        char toCommit[30]={0};
        sprintf(toCommit,"%s:%d",name,gameStat.right_answers*10+gameStat.wrong_answers*(-5));
        commit_name_to_leaderboard(toCommit);
    }

    curs_set(0);
    noecho();
}

void display_leaderboard(){

    clear();
    move(0,0);
    hline('%',COLS);
    vline('H',LINES);
    mvvline(0,COLS-1,'H',LINES);
    mvhline(LINES-1,0,'%',COLS);
    refresh();

    char leaderboard_mess[]={"LEADERBOARD"};
    
    mvprintw(5,(COLS-strlen(leaderboard_mess))/2,"%s",leaderboard_mess);

    FILE* fh= fopen("leaderboard.txt","r");
    char nameBuffer[30]={0};
    
    int vertical_offset=10;
    while(fgets(nameBuffer,30,fh)!=NULL){
        char* token=strtok(nameBuffer, ":\n");
        mvprintw(vertical_offset,5,"%s .......................................", token);
        token=strtok(NULL,":\n");
        printw("%s",token);
        vertical_offset++;
    }
    print_copyrights(stdscr);
    fclose(fh);
    getch();
    clear();
}