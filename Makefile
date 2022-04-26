main: main.c header.h board.c graphics.c
	gcc main.c board.c graphics.c -o main -lncurses

