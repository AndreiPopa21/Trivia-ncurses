#ifndef MANAGER_H
#define MANAGER_H

#include "structs.h"

/*functia care afiseaza ecranul de Splash Screen*/
void splash_screen();

/*functia care iese din joc*/
void quit_trivia();

/*functia care afiseaza ecranul de scor*/
void show_score(GameStat gameStat);

/*functia care afiseaza ecranul de How To Play*/
void show_how_to_play();

/*functia care afiseaza ecranul in care se poate tasta numele spre
  a fi salvat alaturi de scor in Leaderboard. In caz ca niciun nume
  nu a fost tastat, atunci nu se va salva nimic in Leaderboard*/
void save_score_to_scoreboard(GameStat gameStat);

/*functia care afiseaza ecranul de Leaderboard*/
void display_scoreboard();

/*functia care afiseaza ecranul de meniu principal*/
GameStat start_menu(GameStat gameStat, Question* all_questions, int q_total_count);

/*functia de sesiune, care coordoneaza evolutia jocului intre starea de meniu principal
  si stare de joc in desfasurare (mai multe explicatii in README)*/
GameStat game_session(GameStat gameStat);

/*functie care coordoneaza sesiunea de raspuns la o intrebare
  se construieste ecranul alaturi de elementele decorative,
  se afiseaza mesajele corespunzatoare, 
  se coordoneaza inputul jucatorului si actualizeaza mai 
  departe datele despre sesiunea de joc curent*/
GameStat show_question(GameStat gameStat,int i);

#endif