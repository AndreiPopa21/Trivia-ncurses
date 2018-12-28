#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>
#include "manager.h"
#include "utils.h"
#include "structs.h"

#define INITIAL_QUESTIONS_CONTAINER_SIZE 4


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
        display_questions(questions,questions_count);

        initscr();
        cbreak();   
        curs_set(0); 
        noecho();
    
        splash_screen();
        del_splash_screen();

        GameStat* gameStat=NULL;   
        show_start_menu(gameStat,0); 
        //erase();
        // printw("Erased");
        //Question* quest;
        //display_question(quest);
        //getch();
        //display_question(questions);
        //getch();


        quit_trivia();

        free_questions_memory(questions,questions_count);
    }

    return 0;
}





