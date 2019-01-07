#ifndef UTILS_H
#define UTILS_H

#include "structs.h"

Question* get_questions(FILE* src,int* questions_count,Question* questions,int* curr_container_size);

void free_questions_memory(Question* questions, int quest_count);

Question* resize_questions_container(Question* questions, int* curr_container_size);

void display_questions(Question* questions,int questions_count);

void print_copyrights(WINDOW* wind);

void print_question_mark(WINDOW* wind,int beginY,int beginX);

void print_question_index(WINDOW* wind,int index,int total);

void print_question_sentence(WINDOW* wind, char* question_body);

void print_fifty_option(WINDOW* wind);

void unprint_fifty_option(WINDOW* wind);

void print_skip_option(WINDOW* wind);

void unprint_skip_option(WINDOW* wind);

void print_indications(WINDOW* wind);

void print_welcome_message(WINDOW* wind);

void print_answers(WINDOW* wind,Question* question,int* show_options_map,int len_a,int len_b,int len_c,int len_d);

void print_happy_score(WINDOW* wind, GameStat gameStat);

void print_normal_score(WINDOW* wind, GameStat gameStat);

void print_sad_score(WINDOW* wind, GameStat gameStat);

void print_resume_for_game();

void print_points(WINDOW* wind, GameStat gameStat,int y, int x);

void refresh_local_hour_date();

void refresh_current_score(GameStat gameStat);

int get_right_answer_index(Question* question);

void print_no_game_to_resume();

void unprint_no_game_to_resume();

///MODULAR - NEW 

void shuffleQuestions(Question* all_questions,int q_total_count,GameStat gameStat);

//sets the curr_question_index to 0
GameStat initializeGameStat();

GameStat navigate_answers(int* navigation_map,GameStat gameStat, int upPressed, WINDOW* answer_window);

GameStat useFifty(GameStat gameStat,Question* question,int* navigation_map, int* show_options_map);

GameStat print_answers_cursor(GameStat gameStat, WINDOW* wind,int* show_options_map);

#endif