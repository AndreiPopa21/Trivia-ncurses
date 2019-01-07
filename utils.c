#include <stdio.h>
#include <ncurses.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "utils.h"
#include "structs.h"

#define BUFMAX 300
#define ANSWER_BUFF 30
#define QUESTION_BUFF 300
#define RIGHT_ANSWER_BUFF 2
#define INITIAL_QUESTIONS_CONTAINER_SIZE 4


Question* get_questions(FILE* src,int* questions_count,Question* questions,int *curr_container_size){
   
  
    char buff_question[BUFMAX];
    char buff_answers[BUFMAX];

    int quest_index = *questions_count;
    while(fgets(buff_question,BUFMAX,src)!=NULL && fgets(buff_answers,BUFMAX,src)!=NULL){


            if(quest_index>=(*curr_container_size)){
                questions= resize_questions_container(questions,curr_container_size);
                //printf("S-a marit containerul\n");
            }
            //printf("The curr size: %d | The occupied size: %d \n",(*curr_container_size),quest_index+1);

            char* token=strtok(buff_question, "|\n");
           
            questions[quest_index].question=(char*)malloc(QUESTION_BUFF*sizeof(char));
            strcpy(questions[quest_index].question,token);
            
            token=strtok(NULL,"|\n");
            
          
            questions[quest_index].right_answer=(char*) malloc(RIGHT_ANSWER_BUFF*sizeof(char));
            strcpy(questions[quest_index].right_answer,token);

            
            
            token=strtok(buff_answers, "|\n");
            questions[quest_index].a_answer=(char*)malloc(ANSWER_BUFF*sizeof(char));
            questions[quest_index].b_answer=(char*)malloc(ANSWER_BUFF*sizeof(char));
            questions[quest_index].c_answer=(char*)malloc(ANSWER_BUFF*sizeof(char));
            questions[quest_index].d_answer=(char*)malloc(ANSWER_BUFF*sizeof(char));
            strcpy(questions[quest_index].a_answer,token);
            for(int i=0;i<3;i++){
                token=strtok(NULL,"|\n");
                switch(i){
                    case 0:
                        strcpy(questions[quest_index].b_answer,token);
                        break;
                    case 1:
                        strcpy(questions[quest_index].c_answer,token);
                        break;
                    case 2:
                         strcpy(questions[quest_index].d_answer,token);
                        break;
                }
            }
            fgets(buff_question,BUFMAX,src);
            quest_index++;
    }

    fclose(src);
    *questions_count=quest_index;
    return questions;
}

void free_questions_memory(Question* questions, int quest_count){
    for(int i=0;i<quest_count;i++){
        free(questions[i].question);
        free(questions[i].right_answer);
        free(questions[i].a_answer);
        free(questions[i].b_answer);
        free(questions[i].c_answer);
        free(questions[i].d_answer);
    }
    free(questions);
}

Question* resize_questions_container(Question* questions, int* curr_container_size){
    Question *addr;
    addr= (Question*)realloc(questions,(*curr_container_size)*2*sizeof(Question));
    *curr_container_size = (*curr_container_size)*2;
    return addr;
}

void display_questions(Question* questions, int questions_count){
      for(int i=0;i< questions_count;i++){
           printf("%s\n",questions[i].question);
           printf("%s\n",questions[i].right_answer);
           printf("%s\n",questions[i].a_answer);
           printf("%s\n",questions[i].b_answer);
           printf("%s\n",questions[i].c_answer);
           printf("%s\n",questions[i].d_answer);
        }
}

void print_question_mark(WINDOW* wind,int beginY,int beginX){

    wmove(wind,beginY,beginX);
    wprintw(wind,"  _______   \n");
    wmove(wind,beginY+1,beginX);
    wprintw(wind," / _____ \\ \n");
    wmove(wind,beginY+2,beginX);
    wprintw(wind,"/_/     \\ \\ \n");
    wmove(wind,beginY+3,beginX);
    wprintw(wind,"        | | \n");
    wmove(wind,beginY+4,beginX);
    wprintw(wind,"       / /  \n");
    wmove(wind,beginY+5,beginX);
    wprintw(wind,"      / /   \n");
    wmove(wind,beginY+6,beginX);
    wprintw(wind,"     / /   \n");
    wmove(wind,beginY+7,beginX);
    wprintw(wind,"    / /    \n");
    wmove(wind,beginY+8,beginX);
    wprintw(wind,"   / /     \n");
    wmove(wind,beginY+9,beginX);
    wprintw(wind,"   | |     \n");
    wmove(wind,beginY+10,beginX);
    wprintw(wind,"   |_|     \n");
    wmove(wind,beginY+11,beginX);
    wprintw(wind,"           \n");
    wmove(wind,beginY+12,beginX);
    wprintw(wind,"    O      \n");
}

void print_copyrights(WINDOW* wind){

    char copyright[]={"copyrights © Popa Stefan-Andrei"};
    mvwprintw(wind,LINES-2,(COLS-strlen(copyright))/2,"%s",copyright);
    refresh();
}

void print_question_index(WINDOW* wind,int index,int total){
    wmove(wind,LINES/4-LINES/8,0);
    clrtoeol();
    mvwprintw(wind,LINES/4-LINES/8,0,"H");
    mvwprintw(wind,LINES/4-LINES/8,COLS-1,"H");
    char quesion_title[]={"Question: "};
    mvwprintw(wind,LINES/4-LINES/8,(COLS-(strlen(quesion_title)+5))/2,"%s %d/%d",quesion_title,index,total);
    wrefresh(wind);

}

void print_question_sentence(WINDOW* wind, char* question_body){
    int line = LINES/4;
    wmove(wind,line,0);
    clrtoeol();
    mvwprintw(wind,line,0,"H");
    mvwprintw(wind,line,COLS-1,"H");
    mvwprintw(wind,line,(COLS-strlen(question_body))/2,"%s",question_body);
    wrefresh(wind);
}

void print_fifty_option(WINDOW* wind){
    char press[]={"Press F"};
    attron(A_BOLD);
    mvwprintw(wind,LINES/2,COLS/8-2,"50/50");
    attroff(A_BOLD);
    mvwprintw(wind,LINES/2+1,COLS/8-strlen(press)/2,"%s",press);
    wrefresh(wind);
}

void unprint_fifty_option(WINDOW* wind){
    char press[]={"       "};
    mvwprintw(wind,LINES/2+1,COLS/8-strlen(press)/2,"       ");
    mvwprintw(wind,LINES/2,COLS/8-2,"     ");
    wrefresh(wind);
}

void print_skip_option(WINDOW* wind){
    char press[]={"Press B"};
    attron(A_BOLD);
    mvwprintw(wind,LINES/2,COLS-COLS/8-2,"SKIP");
    attroff(A_BOLD);
    mvwprintw(wind,LINES/2+1,COLS-COLS/8-strlen(press)/2,"%s",press);
    wrefresh(wind);
}

void unprint_skip_option(WINDOW* wind){
    char press[]={"       "};
    mvwprintw(wind,LINES/2+1,COLS-COLS/8-strlen(press)/2,"%s",press);
    mvwprintw(wind,LINES/2,COLS-COLS/8-2,"    ");
    wrefresh(stdscr);
}

void print_indications(WINDOW* wind){
    char indic[]={"- navigate with UP and DOWN keys -"};
    mvwprintw(wind,7*LINES/8,(COLS-strlen(indic))/2,"%s",indic);
    wrefresh(wind);
}

void print_welcome_message(WINDOW* wind){
    char welcome_text[]={"Welcome to Trivia"};
    mvwprintw(wind,2,(COLS-strlen(welcome_text))/2,"%s",welcome_text);
    wrefresh(wind);
}

void print_happy_score(WINDOW* wind, GameStat gameStat){
    
    char line0[]={"   HHHHHHHH   "};
    char line1[]={"  H        H  "};
    char line2[]={" H  M    M  H "};
    char line3[]={"H            H"};
    char line4[]={" H  \\____/  H "};
    char line5[]={"  H        H  "};
    char line6[]={"   HHHHHHHH   "};

    char message[]={"Congratulations! Your score looks very good!"};

    int offset=0;

    mvprintw(LINES/8+offset,(COLS-strlen(line0))/2,"%s",line0);
    mvprintw(LINES/8+offset+1,(COLS-strlen(line1))/2,"%s",line1);
    mvprintw(LINES/8+offset+2,(COLS-strlen(line2))/2,"%s",line2);
    mvprintw(LINES/8+offset+3,(COLS-strlen(line3))/2,"%s",line3);
    mvprintw(LINES/8+offset+4,(COLS-strlen(line4))/2,"%s",line4);
    mvprintw(LINES/8+offset+5,(COLS-strlen(line5))/2,"%s",line5);
    mvprintw(LINES/8+offset+6,(COLS-strlen(line6))/2,"%s",line6);

    mvprintw(LINES/8+offset+9,(COLS-strlen(message))/2,"%s",message);

    print_points(stdscr,gameStat,LINES/8+offset+12,5);

    wrefresh(wind);
}

void print_normal_score(WINDOW* wind, GameStat gameStat){

    char line0[]={"   HHHHHHHH   "};
    char line1[]={"  H        H  "};
    char line2[]={" H  M    M  H "};
    char line3[]={"H            H"};
    char line4[]={" H  ______  H "};
    char line5[]={"  H        H  "};
    char line6[]={"   HHHHHHHH   "};

    char message[]={"Good job! Keep up the good work!"};

    int offset=0;

    mvprintw(LINES/8+offset,(COLS-strlen(line0))/2,"%s",line0);
    mvprintw(LINES/8+offset+1,(COLS-strlen(line1))/2,"%s",line1);
    mvprintw(LINES/8+offset+2,(COLS-strlen(line2))/2,"%s",line2);
    mvprintw(LINES/8+offset+3,(COLS-strlen(line3))/2,"%s",line3);
    mvprintw(LINES/8+offset+4,(COLS-strlen(line4))/2,"%s",line4);
    mvprintw(LINES/8+offset+5,(COLS-strlen(line5))/2,"%s",line5);
    mvprintw(LINES/8+offset+6,(COLS-strlen(line6))/2,"%s",line6);

    mvprintw(LINES/8+offset+9,(COLS-strlen(message))/2,"%s",message);

    print_points(stdscr,gameStat,LINES/8+offset+12,5);

    wrefresh(wind);
}

void print_sad_score(WINDOW* wind, GameStat gameStat){

    char line0[]={"   HHHHHHHH   "};
    char line1[]={"  H        H  "};
    char line2[]={" H  M    M  H "};
    char line3[]={"H    ____ ,  H"};
    char line4[]={" H  /    \\  H "};
    char line5[]={"  H        H  "};
    char line6[]={"   HHHHHHHH   "};

    char message[]={"Don't worry! Better next time!"};

    int offset=0;

    mvprintw(LINES/8+offset,(COLS-strlen(line0))/2,"%s",line0);
    mvprintw(LINES/8+offset+1,(COLS-strlen(line1))/2,"%s",line1);
    mvprintw(LINES/8+offset+2,(COLS-strlen(line2))/2,"%s",line2);
    mvprintw(LINES/8+offset+3,(COLS-strlen(line3))/2,"%s",line3);
    mvprintw(LINES/8+offset+4,(COLS-strlen(line4))/2,"%s",line4);
    mvprintw(LINES/8+offset+5,(COLS-strlen(line5))/2,"%s",line5);
    mvprintw(LINES/8+offset+6,(COLS-strlen(line6))/2,"%s",line6);

    mvprintw(LINES/8+offset+9,(COLS-strlen(message))/2,"%s",message);

    print_points(stdscr,gameStat,LINES/8+offset+12,5);

    wrefresh(wind);
}

void print_no_game_to_resume(){
    char message[]={"There is no game to be resume"};
    mvprintw(LINES-4,(COLS-strlen(message))/2,"%s",message);
    refresh();
}

void unprint_no_game_to_resume(){
    char message[]={"                             "};
    mvprintw(LINES-4,(COLS-strlen(message))/2,"%s",message);
    refresh();
}

void refresh_local_hour_date(){

    mvprintw(LINES/8,COLS-COLS/8-2,"         ");
    refresh();


    time_t rawtime;
    struct tm * timeinfo;

    time ( &rawtime );
    timeinfo = localtime ( &rawtime );
    if(timeinfo->tm_hour < 10){
        mvprintw(LINES/8,COLS-COLS/8-2,"0%d:",timeinfo->tm_hour);
        refresh();
    }else{
        mvprintw(LINES/8,COLS-COLS/8-2,"%d:",timeinfo->tm_hour);
        refresh();
    }
    
    if(timeinfo->tm_min < 10){
        mvprintw(LINES/8,COLS-COLS/8+1,"0%d:",timeinfo->tm_min);
        refresh();
    }else{
        mvprintw(LINES/8,COLS-COLS/8+1,"%d:",timeinfo->tm_min);
        refresh();
    }

    if(timeinfo->tm_sec < 10){
        mvprintw(LINES/8,COLS-COLS/8+4,"0%d",timeinfo->tm_sec);
        refresh();
    }else{
        mvprintw(LINES/8,COLS-COLS/8+4,"%d",timeinfo->tm_sec);
        refresh();
    }
    mvprintw(LINES/8+1,COLS-COLS/8-2,"          ");
    mvprintw(LINES/8+1,COLS-COLS/8-2,"%d/%d/%d\n", timeinfo->tm_mday,timeinfo->tm_mon+1,timeinfo->tm_year+1900);
    mvprintw(LINES/8+1,COLS-1,"%s","H");
    refresh();
}

void print_points(WINDOW* wind, GameStat gameStat,int y, int x){

    char right_mess[]={"Right answers: ............ "};
    char wrong_mess[]={"Wrong answers: ............ "};

    mvprintw(y,(COLS-strlen(right_mess)-5)/2,"%s %d/%d",right_mess,gameStat.right_answers,gameStat.questions_count);
    mvprintw(y+1,(COLS- strlen(wrong_mess)-5)/2,"%s %d/%d",wrong_mess,gameStat.wrong_answers,gameStat.questions_count);
    wrefresh(wind);
}

GameStat navigate_answers(int* navigation_map,GameStat gameStat,int upPressed, WINDOW* answers_window){

    //this is the position in the navigation map
    int currentPosition = gameStat.curr_nav_position;

    if(upPressed){
        currentPosition -= 1;
        if(currentPosition<0){
            currentPosition+=4;
        }
        int oldPosition = (*(navigation_map+gameStat.curr_nav_position))*2;
        int newPosition = (*(navigation_map+currentPosition))*2;
        mvwprintw(answers_window,oldPosition,1,"  ");
        mvwprintw(answers_window,newPosition,1,"->");
        gameStat.curr_nav_position = currentPosition;
    }else{
        currentPosition+=1;
        currentPosition = currentPosition % 4;
        int oldPosition = (*(navigation_map+gameStat.curr_nav_position))*2;
        int newPosition = (*(navigation_map+currentPosition))*2;
        mvwprintw(answers_window,oldPosition,1,"  ");
        mvwprintw(answers_window,newPosition,1,"->");
        gameStat.curr_nav_position = currentPosition;
    }

    //mvprintw(LINES/2,3,"%d",gameStat.curr_nav_position);
    //refresh();

    return gameStat;
}

GameStat initializeGameStat(){

    GameStat gameStat;
    gameStat.random_set = NULL;
    gameStat.questions_count = 10;
    gameStat.curr_question_index = 1;
    gameStat.curr_nav_position = 0;
    gameStat.wrong_answers = 0;
    gameStat.right_answers = 0;
    gameStat.didFifty = 0;
    gameStat.fiftyEncoded = 0;
    gameStat.didSkip = 0;
    gameStat.skipping = 0;
    gameStat.timeLeft = 0;
    gameStat.toResume = 0;
    gameStat.isGameFinished = 0;

    return gameStat;
}

void shuffleQuestions(Question* all_questions,int q_total_count,GameStat gameStat){

    int how_many_to_choose = gameStat.questions_count;
    time_t t;
    srand((unsigned) time(&t));
    Question* chosen_set = (Question*)malloc(how_many_to_choose*sizeof(Question));
    
    for(int i=q_total_count-1;i>1;i--){
      
        int pair_seed = rand()%i;
        Question aux;
        aux = *(all_questions+i);
        *(all_questions+i)= *(all_questions+pair_seed);
        *(all_questions+pair_seed)=aux;
    }

}

GameStat useFifty(GameStat gameStat,Question* question,int* navigation_map, int* show_options_map){

    //Question* question = gameStat.random_set + (gameStat.curr_question_index -1);
    char right_answer = *(question->right_answer);

    int fiftyEncoded=0;
    int forSelection[3]={0};
    int a=0;
    

    for(int i=0;i<4;i++){
        show_options_map[i]=0;
    }

    switch(right_answer){
        case 'A':

           // mvprintw(LINES/2,3,"Uite A");

            a=1;
            forSelection[0]=2;
            forSelection[1]=3;
            forSelection[2]=4;

            show_options_map[0]=1;
            break;
        case 'B':

           // mvprintw(LINES/2,3,"Uite B");

            a=2;
            forSelection[0]=1;
            forSelection[1]=3;
            forSelection[2]=4;

    
            show_options_map[1]=1;
            break;
        case 'C':

          //  mvprintw(LINES/2,3,"Uite C");

            a=3;
            forSelection[0]=1;
            forSelection[1]=2;
            forSelection[2]=4;

          
            show_options_map[2]=1;
            break;
        case 'D':

          //  mvprintw(LINES/2,3,"Uite A");

            a=4;
            forSelection[0]=1;
            forSelection[1]=2;
            forSelection[2]=3;

            show_options_map[3]=1;
            break;
    }

    time_t t;
    srand((unsigned) time(&t));
    int choice= rand()%3;
    
    int b = forSelection[choice];

    if(a>b){
        int aux = a;
        a= b;
        b= aux;
    }

    fiftyEncoded= b*10 + a;
    gameStat.fiftyEncoded=fiftyEncoded;

    //mvprintw(LINES/2,2,"Choice: %d",gameStat.fiftyEncoded);
    navigation_map[0]=a;
    navigation_map[1]=b;
    navigation_map[2]=a;
    navigation_map[3]=b;
    show_options_map[forSelection[choice]-1]=1;

    return gameStat;
}

void print_answers(WINDOW* wind,Question* question,int* show_options_map,int len_a,int len_b,int len_c,int len_d){

    int win_x;
    int win_y;
    getmaxyx(wind,win_y,win_x);

    if(show_options_map[0]){
        mvwprintw(wind,2,(win_x-len_a)/2,"%s",question->a_answer);
    }
    if(show_options_map[1]){
        mvwprintw(wind,4,(win_x-len_b)/2,"%s",question->b_answer);
    }
    if(show_options_map[2]){
        mvwprintw(wind,6,(win_x-len_c)/2,"%s",question->c_answer);
    }
    if(show_options_map[3]){
        mvwprintw(wind,8,(win_x-len_d)/2,"%s",question->d_answer);
    }
}

GameStat print_answers_cursor(GameStat gameStat, WINDOW* wind,int* show_options_map){


    int alreadyInitCursor=0;
    if(show_options_map[0]){
         if(!alreadyInitCursor){
             mvwprintw(wind,2,1,"->");
             gameStat.curr_nav_position = 0;
             alreadyInitCursor = 1;
        }
    }
    if(show_options_map[1]){
        if(!alreadyInitCursor){
             mvwprintw(wind,4,1,"->");
             gameStat.curr_nav_position = 0;
             alreadyInitCursor = 1;
        }
    }
    if(show_options_map[2]){
          if(!alreadyInitCursor){
             mvwprintw(wind,6,1,"->");
             gameStat.curr_nav_position = 0;
             alreadyInitCursor = 1;
        }
    }
    if(show_options_map[3]){
        if(!alreadyInitCursor){
             mvwprintw(wind,8,1,"->");
             gameStat.curr_nav_position = 0;
             alreadyInitCursor = 1;
        }
    }

    return gameStat;
}

int get_right_answer_index(Question* question){
    char c = *(question->right_answer);
    int right_answer_index;
    switch(c){
        case 'A':
            right_answer_index=1;
            break;
        case 'B':
            right_answer_index=2;
            break;
        case 'C':
            right_answer_index=3;
            break;
        case 'D':
            right_answer_index=4;
            break;
    }   return right_answer_index;

}

void refresh_current_score(GameStat gameStat){
    int curr_score = 10 * gameStat.right_answers + (-5)*gameStat.wrong_answers;
    char score_mess[]={"Score: "};
    mvprintw(LINES/8,COLS/8-2,"%s%d",score_mess,curr_score);
    refresh();
}