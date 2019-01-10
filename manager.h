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

void show_score(GameStat gameStat);

void show_how_to_play();

void save_score_to_leaderboard(GameStat gameStat);

void display_leaderboard();

GameStat start_menu(GameStat gameStat, Question* all_questions, int q_total_count);

GameStat game_session(GameStat gameStat);

GameStat show_question(GameStat gameStat,int i);

#endif