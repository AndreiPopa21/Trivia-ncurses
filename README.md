# Trivia
> Trivia game implemented in C using the NCurses library: http://www.cs.ukzn.ac.za/~hughm/os/notes/ncurses.html.  
> To be played in a Linux terminal window, ideally in a resolution between **90 X 25** and **120 X 35**  

Link to screenshots: [https://github.com/AndreiPopa21/Trivia-ncurses/tree/master/screenshots](https://github.com/AndreiPopa21/Trivia-ncurses/tree/master/screenshots)

  
  
  
## Instructions for play:  
* Navigation in menus is done with UP and DOWN keys, ENTER for selection  
* Press A, B, C, D for faster selection, then press ENTER to confirm  
* Press F in oder to use Fifty-Fifty option inside game *(only once per game)*   
* Press G in order to use Skip option inside game *(only once per game)*  
* Press Q in order to turn back to the Main Menu  
* Press R in-game if you wish to refresh the current date and time  
  
  

## Customize questions  

Customize questions by editing/adding files in **questions** directory.    
When adding new question files, make sure to modify **Makefile** by appending new file name to the **run** command.  
When adding new question, pay attention to the format:  

`<question_body>|<right_answer_letter>`  
`A.<a_answer>|B.<b_answer>|C.<c_answer>|D.<d_answer>`  
`<newline>`  

## Build and run game  
Use `cd` to navigate into project root directory.  
Use the **Makefile** for building and running the executable.  
Run `make` command for building the game.  
Run `make run` for running the executable.  
Run `make clean` for cleaning the executable.  


## App info

### Author

Stefan-Andrei Popa

### Version  

1.0.0
