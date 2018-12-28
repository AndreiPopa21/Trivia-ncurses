#ifndef STRUCTS_H
#define STRUCTS_H

typedef struct Question{
    char* question;
    char* a_answer;
    char* b_answer;
    char* c_answer;
    char* d_answer;
    char* right_answer;
} Question;

typedef struct GameStat{
    char* curr_question;
    int curr_question_index;
    int wrong_answers;
    int right_answers;
    int didFifty; //tells the program whether the fifty-fifty option has been used
    int didSkip; //tells the program whether the skip option has been used
}GameStat;

#endif