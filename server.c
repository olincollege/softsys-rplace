// Authors: Chris Allum, Berwin Lan, Maya Sivanandan

#include "header.h"

#define PORT 9999

int catch_signal(int sig, void (*handler) (int)) {
    struct sigaction action;
    action.sa_handler = handler;
    sigemptyset(&action.sa_mask);
    action.sa_flags = 0;
    return sigaction(sig, &action, NULL);
}

void end_game(int sig)
{   
    printf("\033[?1003l\n"); // Disable mouse movement events, as l = low
    endwin();
    // system("xdotool key Ctrl+parenright");
    system("xdotool key Ctrl+plus");
    system("xdotool key Ctrl+plus");
    system("resize -s 24 80 > /dev/null");
    system("reset");
    
    exit(EXIT_SUCCESS);
}

int main(int argc, char *argv[])
{
    catch_signal(SIGINT, end_game);
    // do initialization stuff for network here 

    int opt = TRUE;
	int master_socket, addrlen, new_socket, client_socket[30],
		max_clients = 30, activity, i, valread, sd, input_socket;
	int max_sd;
	struct sockaddr_in address;
		
	char buffer[1025]; //data buffer of 1K
		
	// set of socket descriptors
	fd_set readfds;
		
    // create a new instance of the game
    int game_state[N_ROWS][N_COLS/2] = {0};
    

	
	// initialise all client_socket[] to 0 so not checked
	for (i = 0; i < max_clients; i++)
	{
		client_socket[i] = 0;
	}
		
	// create a master socket
	if( (master_socket = socket(AF_INET, SOCK_STREAM, 0)) == 0)
	{
		perror("socket failed");
		exit(EXIT_FAILURE);
	}
	
	// set master socket to allow multiple connections
	if( setsockopt(master_socket, SOL_SOCKET, SO_REUSEADDR, (char *)&opt,
		sizeof(opt)) < 0 )
	{
		perror("setsockopt");
		exit(EXIT_FAILURE);
	}
	
	// type of socket created
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons( PORT );
		
	// bind the socket to localhost port 9999
	if (bind(master_socket, (struct sockaddr *)&address, sizeof(address))<0)
	{
		perror("bind failed");
		exit(EXIT_FAILURE);
	}
	printf("Listener on port %d \n", PORT);
		
	// try to specify maximum of 3 pending connections for the master socket
	if (listen(master_socket, 3) < 0)
	{
		perror("listen");
		exit(EXIT_FAILURE);
	}
		
	// accept the incoming connection
	addrlen = sizeof(address);
	puts("Waiting for connections ...");
		
	for (;;)
	{
		// clear the socket set
		FD_ZERO(&readfds);
	
		// add master socket to set
		FD_SET(master_socket, &readfds);
		max_sd = master_socket;
			
		// add child sockets to set
		for (i = 0; i < max_clients; i++)
		{
			// socket descriptor
			sd = client_socket[i];
				
			// if valid socket descriptor then add to read list
			if (sd > 0)
				FD_SET( sd, &readfds);
				
			// highest file descriptor number, need it for the select function
			if (sd > max_sd)
				max_sd = sd;
		}
	
		// wait for an activity on one of the sockets, timeout is NULL,
		// so wait indefinitely
		activity = select(max_sd + 1, &readfds, NULL, NULL, NULL);
	
		if ((activity < 0) && (errno!=EINTR))
			printf("select error");
			
		
        // If something happened on the master socket ,
		// then its an incoming connection
		if (FD_ISSET(master_socket, &readfds))
		{
			if ((new_socket = accept(master_socket,
					(struct sockaddr *)&address, (socklen_t*)&addrlen))<0)
			{
				perror("accept");
				exit(EXIT_FAILURE);
			}
			
			// inform user of socket number - used in send and receive commands
			printf("New connection, socket fd is %d, ip is: %s, port: %d \n", 
                    new_socket, inet_ntoa(address.sin_addr), ntohs
				    (address.sin_port));
		

            // Send board state to new client
            if( send(new_socket, *game_state, (sizeof(game_state)), 0) != sizeof(game_state) )
			{
				perror("send");
			}
				
			// add new socket to array of sockets
			for (i = 0; i < max_clients; i++) {
				// if position is empty
				if (client_socket[i] == 0)
				{
					client_socket[i] = new_socket;
					printf("Adding to list of sockets as %d\n", i);
						
					break;
				}
			}
		}
			
		// else it's some IO operation on some other socket
		for (i = 0; i < max_clients; i++) {
			input_socket = client_socket[i];
				
			if (FD_ISSET(input_socket, &readfds)) {
				// Check if it was for closing, and also read the incoming message
				if ((valread = read(input_socket, buffer, 1024)) == 0) {
					// Somebody disconnected, get their details and print
					getpeername(input_socket, (struct sockaddr*)&address, \
						(socklen_t*)&addrlen);
					printf("Host disconnected, ip %s, port %d \n" ,
						inet_ntoa(address.sin_addr), ntohs(address.sin_port));
						
					// Close the socket and mark as 0 in list for reuse
					close(input_socket);
					client_socket[i] = 0;
				}
					
				// Echo back the message that came in
				else {
					// set the string terminating NULL byte on the end
					// of the data read
					buffer[valread] = '\0';
					send(sd, buffer, strlen(buffer), 0 );
				}
			}
		}
	}


    // until the program closes, check for updates and then push
    system("xdotool key Ctrl+minus");
    system("xdotool key Ctrl+minus");
    // system("xdotool key Ctrl+minus");

    system("resize -s 75 300 > /dev/null");
    init_screen();
    for (;;) {
        // check for read data

        

        //draw_all();







    }
    return 0;


}