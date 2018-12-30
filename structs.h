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
    Question* random_set;
    int questions_count; //by default, it will be set to 10 | later with Options you could change the number
    int curr_question_index;
    int curr_ans_highlighted; //useful when communicating with navigation
                              //useful when resuming the game, saves the option pointed by the cursor 
    int wrong_answers;
    int right_answers;
    int didFifty; //tells the program whether the fifty-fifty option has been used
    int fiftyEncoded; //two-digit number that encodes the indeces of two remaining questions 
                    // only valueable if(didFity && fiftyEncoded!=0)
    int didSkip; //tells the program whether the skip option has been used
    int timeLeft;
    int toResume;
    int isGameFinished;

}GameStat;

#endif