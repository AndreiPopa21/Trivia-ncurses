build: trivia

install:
	sudo apt-get install libncurses5-dev libncursesw5-dev

trivia: trivia.c manager.c utils.c
	gcc -g $^ -lmenu -lncurses -o $@

run: trivia
	./trivia questions/file1.txt questions/file2.txt

clean: 
	rm -f trivia

