#ifndef UTILS_H
#define UTILS_H

typedef struct Question{
    char* question;
    char* a_answer;
    char* b_answer;
    char* c_answer;
    char* d_answer;
    char* right_answer;
} Question;

Question* get_questions(FILE* src,int* questions_count,Question* questions,int* curr_container_size);
void free_questions_memory(Question* questions, int quest_count);
Question* resize_questions_container(Question* questions, int* curr_container_size);

#endif