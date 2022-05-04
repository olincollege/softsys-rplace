all: server client mouse graphics_test

server: server.c header.h graphics.c pack.c mouse.c
	gcc server.c graphics.c pack.c mouse.c -o server -lncurses

client: client.c header.h graphics.c pack.c mouse.c
	gcc client.c graphics.c pack.c mouse.c -o client -lncurses

mouse: mouse.c header.h graphics.c
	gcc mouse.c graphics.c -o mouse -lncurses

graphics_test:  header.h graphics.c
	gcc graphics_test.c graphics.c -o graphics_test -lncurses