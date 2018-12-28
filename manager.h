#ifndef MANAGER_H
#define MANAGER_H

#include "structs.h"

void splash_screen();

void del_splash_screen();

void display_question(Question* question);

void show_start_menu(GameStat* gameStat,int canResume);

void start_new_game();

void resume_game(GameStat* gameStat);

void quit_trivia();

#endif