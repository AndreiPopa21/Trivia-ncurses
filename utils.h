#ifndef UTILS_H
#define UTILS_H

#include "structs.h"

/*in acest header s-au pus definitiile pentru diferite functii care contribuie
  la imbunatatirea experientei jocului si la prelucrarea informatiilor repetitive
  printre utilitatile functiilor de mai jos, se remarca urmatoarele: 
  decorarea ecranului cu mesaje text si elemente vizuale,
  prelucrarea fisierelor si a informatiilor din acestea,
  actualizarea elementelor de grafica in functie de inputul jucatorului,
  curatarea memoriei*/

/*functia care proceseaza fiecare fisier si care adauga
  intrebarile la containerul de intrebari*/
Question* get_questions(FILE* src,int* questions_count,Question* questions,int* curr_container_size);

/*containerul isi dubleaza capacitatea*/
Question* resize_questions_container(Question* questions, int* curr_container_size);

/*functia care elibereaza memoria ocupata de intrebari*/
void free_questions_memory(Question* questions, int quest_count);

/*Functie utilizata de-a lungul dezvoltarii pentru debugging.
  Scopul ei era de-a afisa intrebarile una dupa alta.
  Starea actuala: Neutilizata*/
void display_questions(Question* questions,int questions_count);

/*functie care afiseaza copyrights-urile in partea de jos a ecranului*/
void print_copyrights(WINDOW* wind);

/*functie care deseneaza pe ecran la o pozitie data un semn de intrebare*/
void print_question_mark(WINDOW* wind,int beginY,int beginX);

/*functie care printeaza in joc un mesaj cu indexul intrebarii curente*/
void print_question_index(WINDOW* wind,int index,int total);

/*functie care printeaza cerinta intrebarii curente din joc*/
void print_question_sentence(WINDOW* wind, char* question_body);

/*functie care printeaza in ecranul jocului posibilitatea de utiliza 50/50*/
void print_fifty_option(WINDOW* wind);

/*functie care sterge de pe ecran PRESS 50/50 si care, totodata, aduce
  la cunostinta faptul ca aceasta optiune nu mai poate fi folosita*/
void unprint_fifty_option(WINDOW* wind);

/*functie care printeaza in ecranul jocului posibilitatea de a utiliza Skip*/
void print_skip_option(WINDOW* wind);

/*functie care sterge de pe ecran PRESS SKIP si care, totodata, aduce
  la cunostinta faptul ca aceasta optiune nu mai poate fi folosita*/
void unprint_skip_option(WINDOW* wind);

/*functie care afiseaza indicatii de navigare prin tastatura pe ecranul jocului*/
void print_indications(WINDOW* wind);

/*functie care afiseaza in Splash Screen un mesaj de salut pentru jucator*/
void print_welcome_message(WINDOW* wind);

/*functie care afiseaza raspunsurile intrebarii in joc, 
  in functie de "harta de afisare" data ca si argument*/
void print_answers(WINDOW* wind,Question* question,int* show_options_map,int len_a,int len_b,int len_c,int len_d);

/*functie care deseneaza ecranul de afisaj al scorului in cazul unui scor bun*/
void print_happy_score(WINDOW* wind, GameStat gameStat);

/*functie care deseneaza ecranul de afisaj al scorului in cazul unui scor mediu*/
void print_normal_score(WINDOW* wind, GameStat gameStat);

/*functie care deseneaza ecranul de afisaj al scorului in cazul unui scor slab*/
void print_sad_score(WINDOW* wind, GameStat gameStat);

/*functie care printeaza un mesaj in meniul principal si care aduce la
  cunostinta faptul ca o sesiune de joc este in desfasurare*/
void print_resume_for_game();

/*functie care afiseaza in ecranul de scor numarul de raspunsuri corecte, 
  gresite, precum si scorul calculat din acestea*/
void print_points(WINDOW* wind, GameStat gameStat,int y, int x);

/*functie care reactulizeaza ora si data pe ecranul jocului*/
void refresh_local_hour_date();

/*functie care actualizeaza scorul curent in joc*/
void refresh_current_score(GameStat gameStat);

/*functie care afiseaza un mesaj pentru utilizator in caz ca acesta 
  a apasat Resume Game, desi nu era nicio sesiune de joc in desfasurare*/
void print_no_game_to_resume();

/*functie care sterge mesajul afisat pentru utilizator in caz ca acesta
  a apasat Resume Game, desi nu era nicio sesiune de joc in desfasurare*/
void unprint_no_game_to_resume();

/*functie care deseneaza marginile ecranului*/
void initialize_screen_margins();

/*functie care salveaza in fisier numele si scorul jucatorului*/
void commit_name_to_scoreboard(char* name);

/*functie care amesteca intrebarile inainte de inceperea unei sesiuni noi de joc*/
void shuffleQuestions(Question* all_questions,int q_total_count,GameStat gameStat);

/*functie care deseneaza in Splash Screen logo-ul trivia folosind o animatie*/
void draw_trivia_logo_with_animation();

/*functie care deseneaza in Splash Screen copyrights-urile folosind o animatie*/
void draw_copyrights_with_animation();

/*functie care asteapta ca utlizatorul sa apese orice tasta ca sa continue*/
void wait_for_any_key_pressed();

/*functie care sterge ecranul de Splash Screen*/
void delete_splash_screen();

/*functia care calculeaza dimensiunile chenarului in care vor fi incadrate raspunsurile in joc*/
int calculate_box_around_answers(Question* curr_question);

/*functie care determina indexul raspunsului corect al intrebarii date
  functia returneaza 1,2,3 sau 4 */
int get_right_answer_index(Question* question);

/*functie care initiliazeaza o structura de tip GameStat
  Nota: se poate schimba numarul de intrebari din sesiunea de joc
  modificand campul gameStat.questions_count*/
GameStat initializeGameStat();

/*functie care decide in ce stare evolueaza jocul 
dupa ce s-a facut o selectie in meniul principal*/
GameStat decide_game_next_state(GameStat gameStat, Question* all_questions, int q_total_count,int quitGame, int createNewGame, int howToPlay, int scoreboard);

/*functie care navigheaza cursorul si selectia in ecranul jocului
  cu ajutorul sagetilor UP and DOWN de la tastatura*/
GameStat navigate_answers_with_up_down_keys(int* navigation_map,GameStat gameStat, int upPressed, WINDOW* answer_window);

/*functie care navigheaza cursorul si selectia cu ajutorul 
  tastelor A,B,C si D*/
GameStat navigate_answers_with_a_b_c_d(int* navigation_map,int index,GameStat gameStat,WINDOW* answer_window);

/*functie care implementeaza functionalitatea de 50/50 si care face 
  actualizarile corespunzatoare atat pe ecran, cat si in structura de tip GameStat*/
GameStat useFifty(GameStat gameStat,Question* question,int* navigation_map, int* show_options_map);

/*functie care printeaza la inceput cursorul pe ecran, 
  orientandu-se dupa "harta de afisare"*/
GameStat print_answers_cursor(GameStat gameStat, WINDOW* wind,int* show_options_map);

#endif
