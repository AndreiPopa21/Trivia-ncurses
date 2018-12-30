#ifndef UTILS_H
#define UTILS_H

#include "structs.h"

Question* get_questions(FILE* src,int* questions_count,Question* questions,int* curr_container_size);

void free_questions_memory(Question* questions, int quest_count);

Question* resize_questions_container(Question* questions, int* curr_container_size);

void display_questions(Question* questions,int questions_count);

void print_copyrights(WINDOW* wind);

void print_question_mark(WINDOW* wind,int beginY,int beginX);

void print_question_index(WINDOW* wind,int index);

void print_question_sentence(WINDOW* wind, char* question_body);

void print_fifty_option(WINDOW* wind);

void print_skip_option(WINDOW* wind);

void print_indications(WINDOW* wind);

///MODULAR - NEW 

Question* pickRandomSet(Question* all_questions,Question* random_set,GameStat gameStat);

#endif