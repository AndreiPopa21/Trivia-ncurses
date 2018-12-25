run: trivia.c
	gcc trivia.c -lncurses -o trivia
	./trivia

build: trivia.c
	gcc trivia.c -lncurses -o trivia

clean: 
	rm -f trivia

