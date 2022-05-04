// Authors: Chris Allum, Berwin Lan, Maya Sivanandan

#include "header.h"


int catch_signal(int sig, void (*handler) (int)) {
    struct sigaction action;
    action.sa_handler = handler;
    sigemptyset(&action.sa_mask);
    action.sa_flags = 0;
    return sigaction(sig, &action, NULL);
}

void end_game(int sig)
{   
    endwin();
    system("xdotool key Ctrl+plus");
    system("xdotool key Ctrl+plus");
    system("resize -s 24 80 > /dev/null");

    printf("\033[?1003l\n");
    
    exit(EXIT_SUCCESS);
}  
 
void get_grid_loc(int mouse_loc[2], int grid_loc[2])
{
	int x =  mouse_loc[0];
	int y =  mouse_loc[1];

    int x_start =  (COLS - N_COLS) / 2;
    int y_start = (LINES - N_ROWS ) / 2;
	
    int grid_x, grid_y;

	if (x_start <= x && x < x_start + N_COLS -1 && y_start <= y && y < y_start + N_ROWS){
        grid_x = (floor(x/2)*2 + x_start%2 - x_start)/2;
        grid_y = y - y_start;
	}
    else{
        grid_x = -1;
        grid_y = -1;
    }

    grid_loc[0] = grid_x;
    grid_loc[1] = grid_y;
}


void get_color(int ch, PlayerState* player_state)
{
    if (ch == KEY_LEFT)
        player_state->color -= 1;
    else if (ch == KEY_RIGHT)
        player_state->color += 1;

    if (player_state->color == -1)
        player_state->color = 0;
    else if (player_state->color == 8)
        player_state->color = 7;
}

void child_func(PlayerState * player_state){
    player_state->locked = 1;
    //exit(1);
}


int main(int argc, char *argv[]) {
    catch_signal(SIGINT, end_game);
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
    recv(server_sock, game_state, sizeof(game_state), 0);

	// Initalize player_state values
	for (int r = 0; r < N_ROWS; r++){
		for (int c = 0; c < N_COLS/2; c++){
			player_state->grid[r][c] = game_state[r][c];
		}
	}
	player_state->loc_x = 0;
	player_state->loc_y = 0;
	player_state->color = 1;
    player_state->locked = 0;




    // game_state into draw command
    
    // until the program closes, check for updates and then push
    system("xdotool key Ctrl+minus");
    system("xdotool key Ctrl+minus");
    // system("xdotool key Ctrl+minus");

    system("resize -s 70 222 > /dev/null");
    init_screen();
    init_mouse();


    int mouse_loc[2];
    int grid_loc[2];
    int ch;

    pid_t pid;
	
	// keep communicating with server
	for (;;)
	{
        ch = getch();

        get_mouse_loc(ch, mouse_loc);


        get_grid_loc(mouse_loc, grid_loc);
        get_color(ch, player_state);

        
        player_state->loc_x = grid_loc[0];
        player_state->loc_y = grid_loc[1];

		if (ch == KEY_DOWN && player_state->locked != 1){
            
			if((player_state->loc_x != -1) && (player_state->loc_y != -1)){
                pid = fork();
                                       
                    
                    // int pixel_array_out[3];
                    // pixel_array_out[0] = player_state->loc_y;
                    // pixel_array_out[1] = player_state->loc_x;
                    // pixel_array_out[2] = player_state->color;
                    // send(server_sock, pixel_array_out, (sizeof(pixel_array_out)), 0);
        	}
        }
        if (pid == 0){
            child_func(player_state);
        }
        else{
            draw_all(player_state);
        }


        
        


		// Receive change from server and update
		// int pixel_array_in[3];
        // recv(server_sock, pixel_array_in, sizeof(pixel_array_in), 0);
        // player_state->grid[pixel_array_in[0]][pixel_array_in[1]] = pixel_array_in[2];

	}
	
	close(server_sock);
	return 0;
}