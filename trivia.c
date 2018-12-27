#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>
#include "manager.h"
#include "utils.h"

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
   
        for(int i=0;i< questions_count;i++){
           printf("%s\n",questions[i].question);
           printf("%s\n",questions[i].right_answer);
           printf("%s\n",questions[i].a_answer);
           printf("%s\n",questions[i].b_answer);
           printf("%s\n",questions[i].c_answer);
           printf("%s\n",questions[i].d_answer);
        }
        free_questions_memory(questions,questions_count);
    }

    initscr();
    cbreak();   
    curs_set(0); 
    //printw("Hello Ncurses\n");
    splash_screen();
    getch();
    endwin();
    return 0;
}



