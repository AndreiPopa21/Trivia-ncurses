build: trivia.c
	gcc trivia.c -lncurses -o trivia
run: trivia.c
	gcc trivia.c -lncurses -o trivia
	./trivia
clean: 
	rm -f trivia

