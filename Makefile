all: server client graphics_test

server: server.c header.h graphics.c pack.c 
	gcc server.c graphics.c pack.c  -o server -lncurses

client: client.c header.h graphics.c pack.c 
	gcc client.c graphics.c pack.c -o client -lncurses

graphics_test: graphics_test.c header.h mouse.c graphics.c
	gcc graphics_test.c graphics.c mouse.c -o graphics_test -lncurses