run: trivia.c
	gcc trivia.c -lncurses -o trivia
	./trivia file1.txt

build: trivia.c
	gcc trivia.c -lncurses -o trivia

clean: 
	rm -f trivia
