#ifndef MANAGER_H
#define MANAGER_H

#include "structs.h"

void splash_screen();

void del_splash_screen();

void display_question(Question* question, int index);

void show_start_menu(GameStat* gameStat,int canResume);

void start_new_game();

void resume_game(GameStat* gameStat);

void quit_trivia();

//////MODULAR NEW

//functia trebuie sa primeasca un GameStat care are isGameFinished=false
void start_menu(GameStat gameStat);

GameStat game_session(GameStat gameStat);

GameStat show_question(GameStat gameStat);

void show_score(GameStat gameStat);

#endif