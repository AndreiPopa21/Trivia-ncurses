#ifndef STRUCTS_H
#define STRUCTS_H

typedef struct Question{
    char* question;
    char* a_answer;
    char* b_answer;
    char* c_answer;
    char* d_answer;
    char* right_answer;
}Question;

typedef struct GameStat{
    
    Question* random_set;
    
    /*by default, it will be set to 10 | later with Options you could change the number*/
    int questions_count;

    int curr_question_index;

    /*useful when communicating with navigation
    useful when resuming the game, saves the option pointed by the cursor 
    takes values : 0 1 2 3*/
    int curr_nav_position;

    int wrong_answers;
    
    int right_answers;
    
    /*tells the program whether the fifty-fifty option has been used*/
    int didFifty; 
    
    /*two-digit number that encodes the indeces of two remaining questions 
    only valueable if(didFity && fiftyEncoded!=0)*/
    int fiftyEncoded; 
    
    /*tells the program whether the skip option has been used*/
    int didSkip; 

    int skipping;
    
    int timeLeft;
    
    int toResume;
    
    int isGameFinished;
}GameStat;

#endif