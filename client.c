// Authors: Chris Allum, Berwin Lan, Maya Sivanandan

#include "header.h"

//

int main(int argc, char *argv[]) {
	int server_sock;
	struct sockaddr_in address;
	char message[1000] , server_reply[2000];
	
	// Create socket to connect to
	server_sock = socket(AF_INET, SOCK_STREAM, 0);
	if (server_sock == -1)
	{
		printf("Could not create socket");
	}
	puts("Socket created");
	
	// type of socket created
    address.sin_addr.s_addr = inet_addr("127.0.0.1");
	address.sin_family = AF_INET;
	address.sin_port = htons(9999);

	// Connect to host server
	if (connect(server_sock, (struct sockaddr *)&address, sizeof(address)) < 0)
	{
		perror("connect failed. Error");
		return 1;
	}
	
	puts("Connected\n");
    // open the game terminal/board here?
	
	
	int (game_state)[N_ROWS][N_COLS];
    recv(server_sock, *game_state, (sizeof(game_state)), 0);

    // game_state into draw command
	
	// keep communicating with server
	for (;;)
	{

		//Set up buffer hold of mouse click location and color choice

		// if (enter pressed)
			//send(server_sock, *pixel_array_out, sizeof(pixel_array_out), 0);
			// Fork to semaphore/mutex to stop sending but keep receiving for 1 min

		// Receive change from server and update
		//recv(server_sock, *pixel_array_in, sizeof(pixel_array_in), 0);
		//game_state[pixelarray_in[0]][pixelarray_in[1]] = [pixelarray_in[2]];
		
	}
	
	close(server_sock);
	return 0;
}