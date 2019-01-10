#include <stdio.h>
#include <ncurses.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "utils.h"
#include "manager.h"
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
            }
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
            int i;
            for(i=0;i<3;i++){
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

    *questions_count=quest_index;
    return questions;
}

/*containerul isi dubleaza capacitatea*/
Question* resize_questions_container(Question* questions, int* curr_container_size){
    
    Question *addr;
    addr= (Question*)realloc(questions,(*curr_container_size)*2*sizeof(Question));
    *curr_container_size = (*curr_container_size)*2;
    return addr;
}

/*functia care elibereaza memoria ocupata de intrebari*/
void free_questions_memory(Question* questions, int quest_count){
    int i;
    for(i=0;i<quest_count;i++){
        free(questions[i].question);
        free(questions[i].right_answer);
        free(questions[i].a_answer);
        free(questions[i].b_answer);
        free(questions[i].c_answer);
        free(questions[i].d_answer);
    }
    free(questions);
}

/*Functie utilizata de-a lungul dezvoltarii pentru debugging.
  Scopul ei era de-a afisa intrebarile una dupa alta.
  Starea actuala: Neutilizata*/
void display_questions(Question* questions, int questions_count){
    
    int i;
    for(i=0;i< questions_count;i++){
           printf("%s\n",questions[i].question);
           printf("%s\n",questions[i].right_answer);
           printf("%s\n",questions[i].a_answer);
           printf("%s\n",questions[i].b_answer);
           printf("%s\n",questions[i].c_answer);
           printf("%s\n",questions[i].d_answer);
        }
}

/*functie care deseneaza pe ecran la o pozitie data un semn de intrebare*/
void print_question_mark(WINDOW* wind,int beginY,int beginX){

    wmove(wind,beginY,beginX);
    wprintw(wind,"  _______   ");
    wmove(wind,beginY+1,beginX);
    wprintw(wind," / _____ \\ ");
    wmove(wind,beginY+2,beginX);
    wprintw(wind,"/_/     \\ \\ ");
    wmove(wind,beginY+3,beginX);
    wprintw(wind,"        | | ");
    wmove(wind,beginY+4,beginX);
    wprintw(wind,"       / /  ");
    wmove(wind,beginY+5,beginX);
    wprintw(wind,"      / /   ");
    wmove(wind,beginY+6,beginX);
    wprintw(wind,"     / /   ");
    wmove(wind,beginY+7,beginX);
    wprintw(wind,"    / /    ");
    wmove(wind,beginY+8,beginX);
    wprintw(wind,"   / /     ");
    wmove(wind,beginY+9,beginX);
    wprintw(wind,"   | |     ");
    wmove(wind,beginY+10,beginX);
    wprintw(wind,"   |_|     ");
    wmove(wind,beginY+11,beginX);
    wprintw(wind,"           ");
    wmove(wind,beginY+12,beginX);
    wprintw(wind,"    O      ");
}

/*functie care afiseaza copyrights-urile in partea de jos a ecranului*/
void print_copyrights(WINDOW* wind){

    char copyright[]={"copyrights © Popa Stefan-Andrei"};
    mvwprintw(wind,LINES-2,(COLS-strlen(copyright))/2,"%s",copyright);
    refresh();
}

/*functie care printeaza un mesaj in meniul principal si care aduce la
  cunostinta faptul ca o sesiune de joc este in desfasurare*/
void print_resume_for_game(){
    char resume_mess[]={"- in-game, press Resume Game to continue current session - "};
    mvprintw(LINES-LINES/6,(COLS-strlen(resume_mess))/2,"%s",resume_mess);
    refresh();
}

/*functie care printeaza in joc un mesaj cu indexul intrebarii curente*/
void print_question_index(WINDOW* wind,int index,int total){
    
    wmove(wind,LINES/4-LINES/8,0);
    clrtoeol();
    mvwprintw(wind,LINES/4-LINES/8,0,"H");
    mvwprintw(wind,LINES/4-LINES/8,COLS-1,"H");
    char quesion_title[]={"Question: "};
    mvwprintw(wind,LINES/4-LINES/8,(COLS-(strlen(quesion_title)+5))/2,"%s %d/%d",quesion_title,index,total);
    wrefresh(wind);
}

/*functie care printeaza cerinta intrebarii curente din joc*/
void print_question_sentence(WINDOW* wind, char* question_body){
    int line = LINES/4;
    wmove(wind,line,0);
    clrtoeol();
    mvwprintw(wind,line,0,"H");
    mvwprintw(wind,line,COLS-1,"H");
    mvwprintw(wind,line,(COLS-strlen(question_body))/2,"%s",question_body);
    wrefresh(wind);
}

/*functie care printeaza in ecranul jocului posibilitatea de utiliza 50/50*/
void print_fifty_option(WINDOW* wind){
    char press[]={"Press F"};
    attron(A_BOLD);
    mvwprintw(wind,LINES/2,COLS/8-2,"50/50");
    attroff(A_BOLD);
    mvwprintw(wind,LINES/2+1,COLS/8-strlen(press)/2,"%s",press);
    wrefresh(wind);
}

/*functie care sterge de pe ecran PRESS 50/50 si care, totodata, aduce
  la cunostinta faptul ca aceasta optiune nu mai poate fi folosita*/
void unprint_fifty_option(WINDOW* wind){
    char press[]={"       "};
    mvwprintw(wind,LINES/2+1,COLS/8-strlen(press)/2,"       ");
    mvwprintw(wind,LINES/2,COLS/8-2,"     ");
    wrefresh(wind);
}

/*functie care printeaza in ecranul jocului posibilitatea de a utiliza Skip*/
void print_skip_option(WINDOW* wind){
    char press[]={"Press G"};
    attron(A_BOLD);
    mvwprintw(wind,LINES/2,COLS-COLS/8-2,"SKIP");
    attroff(A_BOLD);
    mvwprintw(wind,LINES/2+1,COLS-COLS/8-strlen(press)/2,"%s",press);
    wrefresh(wind);
}

/*functie care sterge de pe ecran PRESS SKIP si care, totodata, aduce
  la cunostinta faptul ca aceasta optiune nu mai poate fi folosita*/
void unprint_skip_option(WINDOW* wind){
    char press[]={"       "};
    mvwprintw(wind,LINES/2+1,COLS-COLS/8-strlen(press)/2,"%s",press);
    mvwprintw(wind,LINES/2,COLS-COLS/8-2,"    ");
    wrefresh(stdscr);
}

/*functie care afiseaza indicatii de navigare prin tastatura pe ecranul jocului*/
void print_indications(WINDOW* wind){
    char indic[]={"- navigate with UP and DOWN keys -"};
    mvwprintw(wind,7*LINES/8,(COLS-strlen(indic))/2,"%s",indic);
    wrefresh(wind);
}

/*functie care afiseaza in Splash Screen un mesaj de salut pentru jucator*/
void print_welcome_message(WINDOW* wind){
    char welcome_text[]={"Welcome to Trivia"};
    mvwprintw(wind,2,(COLS-strlen(welcome_text))/2,"%s",welcome_text);
    wrefresh(wind);
}

/*functie care deseneaza ecranul de afisaj al scorului in cazul unui scor bun*/
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

/*functie care deseneaza ecranul de afisaj al scorului in cazul unui scor mediu*/
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

/*functie care deseneaza ecranul de afisaj al scorului in cazul unui scor slab*/
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

/*functie care afiseaza un mesaj pentru utilizator in caz ca acesta 
  a apasat Resume Game, desi nu era nicio sesiune de joc in desfasurare*/
void print_no_game_to_resume(){
    char message[]={"There is no game to be resume"};
    mvprintw(LINES-4,(COLS-strlen(message))/2,"%s",message);
    refresh();
}

/*functie care sterge mesajul afisat pentru utilizator in caz ca acesta
  a apasat Resume Game, desi nu era nicio sesiune de joc in desfasurare*/
void unprint_no_game_to_resume(){
    char message[]={"                             "};
    mvprintw(LINES-4,(COLS-strlen(message))/2,"%s",message);
    refresh();
}

/*functie care reactulizeaza ora si data pe ecranul jocului*/
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

/*functie care afiseaza in ecranul de scor numarul de raspunsuri corecte, 
  gresite, precum si scorul calculat din acestea*/
void print_points(WINDOW* wind, GameStat gameStat,int y, int x){

    char right_mess[]={"Right answers: ............ "};
    char wrong_mess[]={"Wrong answers: ............ "};
    char final_score[]={"Your final score is: "};

    mvprintw(y,(COLS-strlen(right_mess)-5)/2,"%s %d/%d",right_mess,gameStat.right_answers,gameStat.questions_count);
    mvprintw(y+1,(COLS- strlen(wrong_mess)-5)/2,"%s %d/%d",wrong_mess,gameStat.wrong_answers,gameStat.questions_count);
    mvprintw(y+3,(COLS-strlen(final_score))/2,"%s%d",final_score,gameStat.right_answers*10+(-5)*gameStat.wrong_answers);
    wrefresh(wind);
}

/*functie care deseneaza marginile ecranului*/
void initialize_screen_margins(){
    clear();
    move(0,0);
    hline('%',COLS);
    vline('H',LINES);
    mvvline(0,COLS-1,'H',LINES);
    mvhline(LINES-1,0,'%',COLS);
    refresh();
}

/*functie care amesteca intrebarile inainte de inceperea unei sesiuni noi de joc*/
void shuffleQuestions(Question* all_questions,int q_total_count,GameStat gameStat){

    time_t t;
    int i;
    srand((unsigned) time(&t));
    
    for(i=q_total_count-1;i>1;i--){
        int pair_seed = rand()%i;
        Question aux;
        aux = *(all_questions+i);
        *(all_questions+i)= *(all_questions+pair_seed);
        *(all_questions+pair_seed)=aux;
    }

}

/*functie care afiseaza raspunsurile intrebarii in joc, 
  in functie de "harta de afisare" data ca si argument*/
void print_answers(WINDOW* wind,Question* question,int* show_options_map,int len_a,int len_b,int len_c,int len_d){

    int win_x;
    int win_y;
    getmaxyx(wind,win_y,win_x);
    win_y=win_y;

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

/*functie care actualizeaza scorul curent in joc*/
void refresh_current_score(GameStat gameStat){
    int curr_score = 10 * gameStat.right_answers + (-5)*gameStat.wrong_answers;
    char score_mess[]={"Score: "};
    mvprintw(LINES/8,COLS/8-2,"%s%d",score_mess,curr_score);
    refresh();
}

/*functie care salveaza in fisier numele si scorul jucatorului*/
void commit_name_to_leaderboard(char* name){
    FILE* fh = fopen("leaderboard.txt", "a");
    fputs(name,fh);
    fputc('\n',fh);
    fclose(fh);
}

/*functie care asteapta ca utlizatorul sa apese orice tasta ca sa continue*/
void wait_for_any_key_pressed(){

    char press_any_key[]={"- press any key to continue -"};
    int yLoc = LINES/2+ LINES/4;
    nodelay(stdscr,TRUE);

    char c;
    while(1){
        c = getch();
        if(c>0){
            nodelay(stdscr,FALSE);
            break;
        }
        attron(A_REVERSE);
        move(yLoc,COLS/2-strlen(press_any_key)/2);
        printw("%s",press_any_key);
        refresh();
        napms(400);
        c = getch();
        if(c>0){  
            nodelay(stdscr,FALSE);
            break;
        }
        attroff(A_REVERSE);
        move(yLoc,COLS/2-strlen(press_any_key)/2);
        printw("%s",press_any_key);
        refresh();
        napms(400);
    }
}

/*functie care deseneaza in Splash Screen logo-ul trivia folosind o animatie*/
void draw_trivia_logo_with_animation(){

    char line1[]={"MMMMMMMMMM         O            O         "};
    char line2[]={"    HH    MMMMM                     ####  "};
    char line3[]={"    HH    H    H   W W       W  W  H    H "};
    char line4[]={"    HH    HMMMM    W  W     W   W  WRRRRW "};
    char line5[]={"    HH    H  W     W   W   W    W  W    W "};
    char line6[]={"    HH    H   W    W    W W     W  H    H "};
    char line7[]={"    HH    H    W   W     W      W  H    H "};

    int midY= LINES/2;
    int midX= COLS/2;
    
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
}

/*functie care deseneaza in Splash Screen copyrights-urile folosind o animatie*/
void draw_copyrights_with_animation(){
    
    int i;
    char copyright[]={"copyrights © Popa Stefan-Andrei"};
    move(LINES-2,COLS/2-strlen(copyright)/2);
    for( i=0;i<strlen(copyright);i++){
        printw("%c",copyright[i]);
        refresh();
        napms(42);
    }
}

/*functie care sterge ecranul de Splash Screen*/
void delete_splash_screen(){
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

/*functia care calculeaza dimensiunile chenarului in care vor fi incadrate raspunsurile in joc*/
int calculate_box_around_answers(Question* curr_question){
    
    int len_a= strlen(curr_question->a_answer);
    int len_b= strlen(curr_question->b_answer);
    int len_c= strlen(curr_question->c_answer);
    int len_d= strlen(curr_question->d_answer);

    int len[4]={len_a,len_b,len_c,len_d};

    int max1= len[0];
    int i;
    for(i=1;i<4;i++){
        if(len[i]>max1){
            max1=len[i];
        }
    }

    return max1; 
   
}

/*functie care determina indexul raspunsului corect al intrebarii date
  functia returneaza 1,2,3 sau 4 */
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

/*functie care initiliazeaza o structura de tip GameStat
  Nota: se poate schimba numarul de intrebari din sesiunea de joc
  modificand campul gameStat.questions_count*/
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

/*functie care decide in ce stare evolueaza jocul 
dupa ce s-a facut o selectie in meniul principal*/
GameStat decide_game_next_state(GameStat gameStat, Question* all_questions, int q_total_count,int quitGame, int createNewGame, int howToPlay, int leaderboard){
    
    if(quitGame){
        /*quitting game
         show message: Are You sure you want to leave?, for future implementation*/

    }else{
        if(createNewGame){
            createNewGame=0;
            gameStat = initializeGameStat();

            shuffleQuestions(all_questions,q_total_count,gameStat);
            gameStat.random_set=all_questions;
                
            gameStat=game_session(gameStat);
        
        }else{
            if(howToPlay){
                show_how_to_play();
            }else{
                if(leaderboard){
                    display_leaderboard();
                }else{
                    if(gameStat.toResume){

                        gameStat.toResume = 0;
                        gameStat = game_session(gameStat);
                    }
                }
            }   /*else an Options screen could be implemented*/
        }
    }
    return gameStat;
}

/*functie care navigheaza cursorul si selectia in ecranul jocului
  cu ajutorul sagetilor UP and DOWN de la tastatura*/
GameStat navigate_answers_with_up_down_keys(int* navigation_map,GameStat gameStat,int upPressed, WINDOW* answers_window){

    /*this is the position in the navigation map*/
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
    return gameStat;
}

/*functie care navigheaza cursorul si selectia cu ajutorul 
  tastelor A,B,C si D*/
GameStat navigate_answers_with_a_b_c_d(int* navigation_map,int index,GameStat gameStat,WINDOW* answers_window){
    int newPosition;
    int oldPosition = (*(navigation_map+gameStat.curr_nav_position))*2;
    mvwprintw(answers_window,oldPosition,1,"  ");
    int j;
    for(j=0;j<4;j++){
        if(navigation_map[j]==index){
            gameStat.curr_nav_position=j;
            break;
        }
    }
    newPosition = (*(navigation_map+gameStat.curr_nav_position))*2;
    mvwprintw(answers_window,newPosition,1,"->");
    wrefresh(answers_window);
    return gameStat;
}

/*functie care printeaza la inceput cursorul pe ecran, 
  orientandu-se dupa "harta de afisare"*/
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

/*functie care implementeaza functionalitatea de 50/50 si care face 
  actualizarile corespunzatoare atat pe ecran, cat si in structura de tip GameStat*/
GameStat useFifty(GameStat gameStat,Question* question,int* navigation_map, int* show_options_map){

    char right_answer = *(question->right_answer);
    int fiftyEncoded=0;
    int forSelection[3]={0};
    int a=0;
    int i;

    for(i=0;i<4;i++){
        show_options_map[i]=0;
    }

    switch(right_answer){
        
        case 'A':
            a=1;
            forSelection[0]=2;
            forSelection[1]=3;
            forSelection[2]=4;
            show_options_map[0]=1;
            break;

        case 'B':
            a=2;
            forSelection[0]=1;
            forSelection[1]=3;
            forSelection[2]=4;    
            show_options_map[1]=1;
            break;

        case 'C':
            a=3;
            forSelection[0]=1;
            forSelection[1]=2;
            forSelection[2]=4;
            show_options_map[2]=1;
            break;

        case 'D':
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

    navigation_map[0]=a;
    navigation_map[1]=b;
    navigation_map[2]=a;
    navigation_map[3]=b;
    show_options_map[forSelection[choice]-1]=1;

    return gameStat;
}
