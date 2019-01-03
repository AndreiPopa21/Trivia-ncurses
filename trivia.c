#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>
#include "manager.h"
#include "utils.h"
#include "structs.h"

#define INITIAL_QUESTIONS_CONTAINER_SIZE 4

GameStat customizeGameStat();

int main(int argc, char* argv[]){

    if(argc<2){
        fprintf(stderr,"Nu s-au dat argumente in linia de comanda\n");
        return 1;   
    }else{
        fprintf(stdout,"Ai dat suficiente argumente\n");

        Question* questions=(Question*)malloc(INITIAL_QUESTIONS_CONTAINER_SIZE*sizeof(Question));

        int curr_container_size=INITIAL_QUESTIONS_CONTAINER_SIZE;
        int questions_count=0;

        FILE* src;
        for(int i=1;i<argc;i++){
            src = fopen(argv[i],"r");
            if(!src){
                fprintf(stderr,"Nu s-a putut deschide fisierul cu indexul: %d\n",i);
                return 0;
            }else{
                fprintf(stdout,"S-a putut deschide fisierul cu indexul: %d\n",i);
                
                questions=get_questions(src,&questions_count,questions,&curr_container_size);
                
                fclose(src);
            }
        }
        
        printf("Numarul de intrebari este: %d\n",questions_count);
        //display_questions(questions,questions_count);

        
        initscr();
        cbreak();   
        curs_set(0); 
        noecho();

        //GameStat gameStat = initializeGameStat();
        //gameStat=start_menu(gameStat,questions,questions_count);
        /*
        shuffleQuestions(questions,questions_count,gameStat);
        Question* random_set = (Question*)malloc(gameStat.questions_count*sizeof(Question));
        for(int i=0;i<gameStat.questions_count;i++){
            random_set[i]=questions[i];
        }*/
        //display_questions(random_set,gameStat.questions_count);
        //start_menu(gameStat,questions,questions_count);

        splash_screen();
        del_splash_screen();

        //GameStat* gameStat=NULL;   
        //show_start_menu(gameStat,0); 
        //erase();



        GameStat gameStat= customizeGameStat();
        gameStat.random_set=questions+3;
        //gameStat = game_session(gameStat);
        gameStat = start_menu(gameStat,questions,questions_count);
        //show_question(gameStat);
        //show_score(gameStat);
        quit_trivia();
        //printf("Gata\n");


        //printf("Cate intrebari: %d\n",gameStat.questions_count);
        //display_questions(gameStat.random_set,gameStat.questions_count);

        free_questions_memory(questions,questions_count);
    }
    return 0;
}


GameStat customizeGameStat(){
    GameStat gameStat;
    gameStat.random_set=NULL;
    gameStat.questions_count=4;
    gameStat.curr_question_index=1;
    gameStat.curr_nav_position=0;
    gameStat.wrong_answers=0;
    gameStat.right_answers=0;
    gameStat.didFifty=0;
    gameStat.fiftyEncoded=0;
    gameStat.didSkip=0;
    gameStat.skipping=0;
    gameStat.timeLeft=0;
    gameStat.toResume=0;
    gameStat.isGameFinished=0;
    return gameStat;
}


