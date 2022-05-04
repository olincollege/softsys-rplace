// Authors: Chris Allum, Berwin Lan, Maya Sivanandan

#include "header.h"

//

int main(int argc, char *argv[]) {
	int server_sock;
	struct sockaddr_in address;
	char message[1000] , server_reply[2000];
	PlayerState *player_state = malloc(sizeof(PlayerState));
	
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
	
	
	int (game_state)[N_ROWS][N_COLS/2];
    recv(server_sock, *game_state, sizeof(game_state), 0);

	// Initalize player_state values
	for (int r = 0; r < N_ROWS; r++){
		for (int c = 0; c < N_COLS/2; c++){
			player_state->grid[r][c] = game_state[r][c];
		}
	}
	player_state->loc_x = 0;
	player_state->loc_y = 0;
	player_state->color = 0;




    // game_state into draw command
	
	// keep communicating with server
	for (;;)
	{

		//if num/arrow key pressed
			// player_state->color = num pressed

		// if click
			//int mouse_temp = mouse_loc()
			// player_state->loc_x = mouse_loc[0];
			// player_state->loc_y = mouse_loc[1];


		// if (enter pressed) and 
			if((player_state->loc_x != -1) && (player_state->loc_y != -1)){
				int pixel_array_out[3];
				pixel_array_out[0] = player_state->loc_x;
				pixel_array_out[1] = player_state->loc_y;
				pixel_array_out[2] = player_state->color;
				send(server_sock, pixel_array_out, (sizeof(pixel_array_out)), 0);
			// Fork to semaphore/mutex to stop sending but keep receiving for delay time
			}

		// Receive change from server and update
		//recv(server_sock, *pixel_array_in, sizeof(pixel_array_in), 0);
		//game_state[pixelarray_in[0]][pixelarray_in[1]] = [pixelarray_in[2]];
		
	}
	
	close(server_sock);
	return 0;
}