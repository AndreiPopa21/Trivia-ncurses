#include <ncurses.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "manager.h"
#include "structs.h"
#include "utils.h"
#include <menu.h>


void splash_screen(){
 
    initialize_screen_margins();

    draw_trivia_logo_with_animation();   

    draw_copyrights_with_animation();
   
    wait_for_any_key_pressed();
}


void quit_trivia(){
    endwin();
}


void show_score(GameStat gameStat){

    initialize_screen_margins();
    
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
    save_score_to_scoreboard(gameStat);
}


void show_how_to_play(){
    
    initialize_screen_margins();

    int vertical_offset=4;
    char up_down_nav_mess[]={"Navigation in menus is done with UP and DOWN keys, ENTER for selection"};
    char a_b_c_d_mess[]={"Press A, B, C, D for faster selection, then press ENTER to confirm"};
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
    mvprintw(LINES-4,(COLS-strlen(return_to_menu))/2,"%s",return_to_menu);
    print_copyrights(stdscr);

    refresh();
    getch();
    clear();
}


void save_score_to_scoreboard(GameStat gameStat){
   
    initialize_screen_margins();

    char type_name[]={"Type your name (max.20): "};
    char press_enter[]={"Press Enter to skip or confirm"};

    mvprintw(LINES-4,(COLS-strlen(press_enter))/2,"%s",press_enter);
    mvprintw(LINES/2,6,"%s",type_name);
   
    curs_set(1);
    echo();
    refresh();
    int breakOut=0;
    char name[20]={0};
    int charCount=0;

    int toCommitToScorebooard=0;

    while(!breakOut && charCount<=20){
        char c = getch();
        int c_code= c;
        switch(c_code){
            case 10:
                if(charCount>0){
                    toCommitToScorebooard=1;
                }
                breakOut=1;
                break;
            default:
                strcat(name,&c);
                charCount++;
                break;
        }
    }
    if(toCommitToScorebooard){
        char toCommit[30]={0};
        sprintf(toCommit,"%s:%d",name,gameStat.right_answers*10+gameStat.wrong_answers*(-5));
        commit_name_to_scoreboard(toCommit);
    }

    curs_set(0);
    noecho();
}


void display_scoreboard(){

    initialize_screen_margins();

    char leaderboard_mess[]={"LEADERBOARD"};
    
    mvprintw(5,(COLS-strlen(leaderboard_mess))/2,"%s",leaderboard_mess);

    FILE* fh= fopen("leaderboard.txt","r");
    char nameBuffer[30]={0};
    
    int vertical_offset=8;
    while(fgets(nameBuffer,30,fh)!=NULL){
        char* token=strtok(nameBuffer, ":\n");
        mvprintw(vertical_offset,5,"%s ", token);
        mvhline(vertical_offset,7+strlen(token),'.',COLS-7-strlen(token)-9);

        token=strtok(NULL,":\n");
        mvprintw(vertical_offset,COLS-8,"%s",token);
       
        vertical_offset+=2;
    }
    refresh();
    print_copyrights(stdscr);
    fclose(fh);
    getch();
    clear();
}


GameStat start_menu(GameStat gameStat,Question* all_questions, int q_total_count){

    int quitGame=0;
    while(!quitGame){

        initialize_screen_margins();
        
        int breakOut = 0;
        int createNewGame = 0;
        int howToPlay=0;
        int scoreboard=0;

        print_welcome_message(stdscr);
        wmove(stdscr,LINES/4,COLS/2);
        print_question_mark(stdscr,LINES/4,3);
        print_question_mark(stdscr,LINES/4,COLS-15);
        print_copyrights(stdscr);

        if(gameStat.toResume){
            print_resume_for_game();
        }

        /*se construieste grafica meniului principal*/
        char* choices[]={
                "New Game",
                "Resume Game",
                "Quit",
                "How to play",
                "Scoreboard"
            };
        ITEM **my_items;
        MENU *myMenu;
        int n_choices=5;
       
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
       
        /*navigarea prin meniu, iesirea din while se face odata ce
          o optiune dintre cele 5 a fost selectata*/
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
                        case 0: /*Option for creating a new game*/
                            breakOut=1;
                            createNewGame=1;
                            break;

                        case 1: /*Option for handling the Resume*/
                            if(gameStat.toResume){
                                breakOut=1;
                            }else{
                                print_no_game_to_resume();
                            }
                            break;

                        case 2: /*Optioune for quitting*/ 
                            breakOut=1;
                            quitGame=1;
                            break;
                        
                        case 3: /*Option for opening How To Play*/
                            breakOut=1;
                            howToPlay=1;
                            break;
                        
                        case 4: /*Option for opening the Scoreboard*/
                            breakOut=1;
                            scoreboard=1;
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
        /*eliberarea memoriei meniului (incompleta din libraria ncurses)*/
        unpost_menu(myMenu);
        for(i = 0; i < n_choices; ++i){
            free_item(my_items[i]);
        }
        free_menu(myMenu);
        wborder(my_menu_window, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
        wrefresh(my_menu_window);
        delwin(my_menu_window);
        erase();
        refresh();
        
        /*optiunea selectata in meniu se analizeaza si se ia aici o decizie*/
        gameStat = decide_game_next_state(gameStat,all_questions,q_total_count,quitGame,createNewGame,howToPlay,scoreboard);
    }

    return gameStat;
}


GameStat game_session(GameStat gameStat){

    /*functia de sesiune de joc*/
    int startIndex = gameStat.curr_question_index;
    if(gameStat.didSkip){
        startIndex-=1;
    }
    int maxIndex = gameStat.questions_count;
    int i=0;

    for(i=startIndex;i<=maxIndex && !gameStat.toResume; ){
           
        gameStat = show_question(gameStat,i);
        if(gameStat.toResume){
            /*do nothing*/
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
    /*daca jocul s-a terminat parcurgand toate cele 10 intrebari*/
    if(i>maxIndex){
        gameStat.isGameFinished = 1;
        gameStat.toResume = 0;
    }

    if(gameStat.isGameFinished){
        show_score(gameStat);
    }
    /*daca s-a apasat Q, gameStat.toResume are valoarea 1*/
    return gameStat;
}


GameStat show_question(GameStat gameStat,int i){

    /*se deseneaza elementele grafice*/
    initialize_screen_margins();

    print_copyrights(stdscr);
    print_question_index(stdscr,i,gameStat.questions_count);
    print_indications(stdscr);

    /*atata timp cat indexul incepe cu 1*/
    Question* curr_question = gameStat.random_set+(gameStat.curr_question_index-1); 
    print_question_sentence(stdscr,curr_question->question);

    if(!gameStat.didSkip){
        print_skip_option(stdscr);
    }
    
    int right_answer_index = get_right_answer_index(curr_question);

    /*ordinea de navigare a raspunsurilor este date de aceasta "harta"
    daca s-a apasat 50/50, o ordine posibila a elementelor in aceasta harta poate fi {1,2,1,2} */
    int navigation_map[4]={1,2,3,4};

    /*raspunsurile care trebuie afisate pe ecran sunt date de aceasta "hara"
      utila mai ales odata ce optiunea de 50/50 a fost apasata*/
    int show_options_map[4]={1,1,1,1};
    
    /*se verifica daca s-a folosit deja optiunea de 50/50 si daca
      optiunea este inca activa pentru intrebarea curenta*/
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
    
    /*se creeaza un box in jurul raspunsurilor*/
    WINDOW* answers_window;

    int max1=calculate_box_around_answers(curr_question);
    answers_window=newwin(11,max1+8,LINES/2-LINES/8,(COLS-max1-8)/2);
    box(answers_window,0,0);
    wrefresh(answers_window);
    keypad(answers_window,TRUE);

    int len_a= strlen(curr_question->a_answer);
    int len_b= strlen(curr_question->b_answer);
    int len_c= strlen(curr_question->c_answer);
    int len_d= strlen(curr_question->d_answer);
    print_answers(answers_window,curr_question,show_options_map,len_a,len_b,len_c,len_d);
    print_answers_cursor(gameStat,answers_window,show_options_map);
    
    wrefresh(answers_window);
    refresh();
    
    int c;
    int breakOut = 0;

    /*se navigheaza prin raspunsuri si se astepta o comanda valida a utilizatorului*/
    while(!breakOut){
    
        c=wgetch(answers_window);
        switch(c){
            /*sistemul de navigare cu sagetile*/
            case KEY_UP:
                gameStat = navigate_answers_with_up_down_keys(navigation_map,gameStat,1,answers_window);
                break;

            case KEY_DOWN:
                gameStat = navigate_answers_with_up_down_keys(navigation_map,gameStat,0,answers_window);
                break;
            /*sostemul de navigare cu A, B, C, D*/
            case 97:
                if(show_options_map[0]){
                    gameStat = navigate_answers_with_a_b_c_d(navigation_map,1,gameStat,answers_window);
                }
                break;
            
            case 98:
                if(show_options_map[1]){
                    gameStat = navigate_answers_with_a_b_c_d(navigation_map,2,gameStat,answers_window);
                }
                break;
            
            case 99:
                if(show_options_map[2]){
                    gameStat = navigate_answers_with_a_b_c_d(navigation_map,3,gameStat,answers_window);
                }
                break;
            
            case 100:
                if(show_options_map[3]){
                    gameStat = navigate_answers_with_a_b_c_d(navigation_map,4,gameStat,answers_window);
                }
                break;

            case 10:
                breakOut=1;
                int player_choice = navigation_map[gameStat.curr_nav_position];

                if(player_choice==right_answer_index){
                    gameStat.right_answers+=1;
                }else{
                    gameStat.wrong_answers+=1;
                }
                gameStat.curr_nav_position=0;
               
                break;

            case 102:
                /*optiunea de 50/50 valabila doar daca nu a mai fost apasata inainte*/
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
                /*optiunea de Skip valabila doar daca nu a mai fost apasata inainte*/
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
                /*se apasa Q pentur a se iesi din joc*/
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
