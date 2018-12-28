#ifndef UTILS_H
#define UTILS_H

#include "structs.h"

Question* get_questions(FILE* src,int* questions_count,Question* questions,int* curr_container_size);
void free_questions_memory(Question* questions, int quest_count);
Question* resize_questions_container(Question* questions, int* curr_container_size);
void display_questions(Question* questions,int questions_count);

#endif