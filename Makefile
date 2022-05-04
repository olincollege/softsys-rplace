all: server client mouse graphics_test

server: server.c header.h board.c graphics.c pack.c mouse.c
	gcc server.c board.c graphics.c pack.c mouse.c -o server -lncurses

client: client.c header.h board.c graphics.c pack.c mouse.c
	gcc client.c board.c graphics.c pack.c mouse.c -o client -lncurses

mouse: mouse.c header.h graphics.c
	gcc mouse.c graphics.c -o mouse -lncurses

graphics_test:  header.h board.c graphics.c
	gcc graphics_test.c board.c graphics.c -o graphics_test -lncurses