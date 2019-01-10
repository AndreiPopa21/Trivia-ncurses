#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>
#include <time.h>
#include "manager.h"
#include "utils.h"
#include "structs.h"

#define INITIAL_QUESTIONS_CONTAINER_SIZE 4

int main(int argc, char* argv[]){

    
    if(argc<2){
        fprintf(stderr,"Nu s-au dat argumente in linia de comanda\n");

        exit(1);
        return 1;   
    }else{

        Question* questions=(Question*)malloc(INITIAL_QUESTIONS_CONTAINER_SIZE*sizeof(Question));

        int curr_container_size=INITIAL_QUESTIONS_CONTAINER_SIZE;
        int questions_count=0;

        FILE* src;
        int i;
        for(i=1;i<argc;i++){
            src = fopen(argv[i],"r");
            if(!src){
                fprintf(stderr,"Nu s-a putut deschide fisierul cu indexul: %d\n",i);
                return 0;
            }else{
              
                questions=get_questions(src,&questions_count,questions,&curr_container_size);        
                fclose(src);
            }
        }
        
        initscr();
        cbreak();   
        curs_set(0); 
        noecho();

        splash_screen();
        delete_splash_screen();

        GameStat gameStat=initializeGameStat();
        gameStat = start_menu(gameStat,questions,questions_count);
  
        quit_trivia();

        free_questions_memory(questions,questions_count);
    }
    return 0;
}



