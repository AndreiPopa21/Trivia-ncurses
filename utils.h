#ifndef UTILS_H
#define UTILS_H

#include "structs.h"

/*in acest header s-au pus definitiile pentru diferite functii care contribuie
  la imbunatatirea experientei jocului si la prelucrarea informatiilor repetitive
  printre utilitatile functiilor de mai jos, se remarca urmatoarele: 
  decorarea ecranului cu mesaje text si elemente vizuale,
  prelucrarea fisierelor si a informatiilor din acestea,
  actualizarea elementelor de grafica in functie de inputul jucatorului,
  curatarea memoriei*/

/*functia care proceseaza fiecare fisier si care adauga
  intrebarile la containerul de intrebari*/
Question* get_questions(FILE* src,int* questions_count,Question* questions,int* curr_container_size);

Question* resize_questions_container(Question* questions, int* curr_container_size);

void free_questions_memory(Question* questions, int quest_count);

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

void print_no_game_to_resume();

void unprint_no_game_to_resume();

void initialize_screen_margins();

void commit_name_to_leaderboard(char* name);

void shuffleQuestions(Question* all_questions,int q_total_count,GameStat gameStat);

void draw_trivia_logo_with_animation();

void draw_copyrights_with_animation();

void wait_for_any_key_pressed();

void delete_splash_screen();

int calculate_box_around_answers(Question* curr_question);

int get_right_answer_index(Question* question);

GameStat initializeGameStat();

GameStat customizeGameStat();

GameStat decide_game_next_state(GameStat gameStat, Question* all_questions, int q_total_count,int quitGame, int createNewGame, int howToPlay, int leaderboard);

GameStat navigate_answers_with_up_down_keys(int* navigation_map,GameStat gameStat, int upPressed, WINDOW* answer_window);

GameStat navigate_answers_with_a_b_c_d(int* navigation_map,int index,GameStat gameStat,WINDOW* answer_window);

GameStat useFifty(GameStat gameStat,Question* question,int* navigation_map, int* show_options_map);

GameStat print_answers_cursor(GameStat gameStat, WINDOW* wind,int* show_options_map);

#endif