build: trivia

trivia: trivia.c manager.c utils.c
	gcc -g $^ -lmenu -lncurses -o $@

run: trivia
	./trivia file1.txt file2.txt

clean: 
	rm -f trivia

