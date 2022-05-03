server: server.c header.h board.c graphics.c
	gcc server.c board.c graphics.c -o server -lncurses

