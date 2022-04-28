main: main.c header.h board.c graphics.c
	gcc main.c board.c graphics.c network.c -o main -lpanel -lncurses

