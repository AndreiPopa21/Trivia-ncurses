#include <stdio.h>
#include <ncurses.h>
#include <string.h>
#include <stdlib.h>
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
                printf("S-a marit containerul\n");
            }
            printf("The curr size: %d | The occupied size: %d \n",(*curr_container_size),quest_index+1);

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

    char copyright[]={"copyright © Popa Stefan-Andrei"};
    mvwprintw(wind,LINES-2,(COLS-strlen(copyright))/2,"%s",copyright);
    refresh();
}