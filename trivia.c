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

    /*se citesc fisierele date ca argument si din fiecare
      se extrag intrebarile si se salveaza in memoria programului */ 
    if(argc<2){
        /*in caz ca nu au fost date argumente in linia de comanda,
          se termina programul returnand 1*/
        fprintf(stderr,"[Eroare]: Nu s-au dat argumente in linia de comanda\n");
        return 1;   

    }else{
        /*initializarea containerului de intrebari*/
        Question* questions=(Question*)malloc(INITIAL_QUESTIONS_CONTAINER_SIZE*sizeof(Question));
        int curr_container_size=INITIAL_QUESTIONS_CONTAINER_SIZE;
        int questions_count=0;

        FILE* src;
        int i;
        for(i=1;i<argc;i++){
            src = fopen(argv[i],"r");
            if(!src){
                /*in caz ca un fisier nu a putut fi deschis, se termina programul returnand 1*/
                fprintf(stderr,"[Eroare]: Fisierul %s nu poate fi deschis\n",argv[i]);
                free_questions_memory(questions,questions_count);
                return 1;

            }else{
                /*odata ce fisierul a putut fi deschis cu succes, se incepe procesarea acestuia*/
                questions=get_questions(src,&questions_count,questions,&curr_container_size);        
                fclose(src);
            }
        }
        
        /*daca s-a ajuns pana in acest stadiu, inseamna ca toate fisierele au fost
          procesate cu succes si se poate incepe jocul*/
        initscr();
        cbreak();   
        curs_set(0); 
        noecho();
        
        /*jocul incepe cu o animatie de tip Splash Screen care serveste pe post de intro*/
        splash_screen();
        /*dupa ce utilizatorul apasa un buton, se termina animatia si se trece la meniul principal*/
        delete_splash_screen();
        
        /*GameStat este structura din structs.h care stocheaza si se updateaza la fiecare pas
          cu informatiile actuale despre joc. Structura retine informatii precum:
          intrebarile din joc, intrebarea curenta, daca s-au folosit optiunile de 
          50/50 sau Skip, etc. Pentru mai multe detalii, a se consulta structs.h*/
        GameStat gameStat=initializeGameStat();

        /*Se intra in meniul principal. Odata ce s-a iesit din aceasta functie,
          jocul s-a terminat si se inchide ncurses.*/
        gameStat = start_menu(gameStat,questions,questions_count);
        
        /*functia in care se inchide ncurses si care marcheaza sfarsitul jocului*/
        quit_trivia();

        /*se elibereaza memoria alocata pentru intrebari, precum si pentru campurile acestora*/
        free_questions_memory(questions,questions_count);
    }
    return 0;
}



