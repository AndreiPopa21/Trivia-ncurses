#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>

#define BUFMAX 300
#define ANSWER_BUFF 30
#define QUESTION_BUFF 300
#define RIGHT_ANSWER_BUFF 2
#define INITIAL_QUESTIONS_CONTAINER_SIZE 4

typedef struct Question{
    char* question;
    char* a_answer;
    char* b_answer;
    char* c_answer;
    char* d_answer;
    char* right_answer;
} Question;

void splash_screen();
Question* get_questions(FILE* src,int* questions_count,Question* questions,int* curr_container_size);
void free_questions_memory(Question* questions, int quest_count);
Question* resize_questions_container(Question* questions, int* curr_container_size);

int main(int argc, char* argv[]){

    if(argc<2){
        fprintf(stderr,"Nu s-au dat argumente in linia de comanda\n");
        return 1;   
    }else{
        fprintf(stdout,"Ai dat suficiente argumente\n");

        Question* questions=(Question*)malloc(INITIAL_QUESTIONS_CONTAINER_SIZE*sizeof(Question));
        //int* questions_count=(int*)malloc(sizeof(int));
        //int* curr_container_size = (int*)malloc(sizeof(int));

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

    /*initscr();
    cbreak();   
    curs_set(0); 
    //printw("Hello Ncurses\n");
    splash_screen();
    getch();
    endwin();*/ 
    return 0;
}

void splash_screen(){
    //printw("Dimensiunile ecranului sunt: %d| %d\n", LINES,COLS);
    //mvprintw(LINES-1,COLS-1,"+");
    //vline("*",1);
    hline('*',COLS);
    vline('|',LINES);
    mvvline(0,COLS-1,'|',LINES);
    mvhline(LINES-1,0,'*',COLS);
    
    char line0[]={"                                  "};
    char line1[]={"MMMMMMMMMM        o           o       "};
    char line2[]={"    HH    MMMM                    ### "};
    char line3[]={"    HH    H   H   H  V     V  H  I   I"};
    char line4[]={"    HH    HMMM    H   V   V   H  W R W"};
    char line5[]={"    HH    H  H    H    V V    H  W   W"};
    char line6[]={"    HH    H   H   H     V     H  H   H"};
    char line7[]={"                                  "};

    int midY= LINES/2;
    int midX= COLS/2;
    //mvprintw(midY,midX,"Hello");
    
    int i;
    int offset = -(midY-LINES/4);
    move(midY+offset,midX-strlen(line1)/2);
    printw("%s",line1);
    move(midY+offset+1,midX-strlen(line2)/2);
    printw("%s",line2);
    move(midY+offset+2,midX-strlen(line3)/2);
    printw("%s",line3);
    move(midY+offset+3,midX-strlen(line4)/2);   
    printw("%s",line4);
    move(midY+offset+4,midX-strlen(line5)/2);
    printw("%s",line5);
    move(midY+offset+5,midX-strlen(line6)/2);
    printw("%s",line6);   

    char copyright[]={"copyright - Popa Stefan"};
    move(LINES-3,midX-strlen(copyright)/2);
    printw("%s",copyright); 
    
    
    char press_any_key[]={"- press any key to continue -"};
    int yLoc = midY+ LINES/4;
    
  //  while(1){
        /*char c = getch();   
        if(c!=0){
            break;
        }*/
       /* if((c=getch())!=0){
            break;
        }*/
   //     for(int i=0;i<6;i++){
        attron(A_REVERSE);
        move(yLoc,midX-strlen(press_any_key)/2);
        printw("%s",press_any_key);
        refresh();
        napms(500);
        attroff(A_REVERSE);
        move(yLoc,midX-strlen(press_any_key)/2);
        printw("%s",press_any_key);
         refresh();
        napms(500);
       
   // }
    
}

Question* get_questions(FILE* src,int* questions_count,Question* questions,int *curr_container_size){
   
    char buff_question[BUFMAX];
    char buff_answers[BUFMAX];

    int quest_index = *questions_count;
    while(fgets(buff_question,BUFMAX,src)!=NULL){


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

            fgets(buff_answers,BUFMAX,src);
            
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



