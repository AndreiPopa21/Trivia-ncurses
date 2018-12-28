run: trivia.c
	gcc trivia.c manager.c utils.c -lmenu -lncurses -o trivia
	./trivia file1.txt file2.txt

build: trivia.c
	gcc trivia.c manager.c utils.c -lmenu -lncurses -o trivia

clean: 
	rm -f trivia

