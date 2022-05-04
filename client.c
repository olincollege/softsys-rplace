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
	int game_state[63][N_COLS];
    recv(server_sock, game_state, (sizeof(game_state))*5, 0);

	for (int i = 0 ; i < 63 ; i++){
		for (int j = 0 ; j < N_COLS ; j++){
			printf("%d ", game_state[i][j]);
		}
		printf("\n End of row %d\n", i+1);
	}

    // game_state into draw command
	
	// keep communicating with server
	for (;;)
	{
		printf("Enter message: ");
		scanf("%s", message);
		
		// Send some data
		if(send(server_sock, message, strlen(message), 0) < 0)
		{
			puts("Send failed");
			return 1;
		}
		
		// Receive a reply from the server
		if( recv(server_sock, server_reply, 2000, 0) < 0)
		{
			puts("recv failed");
			break;
		}
		
		puts("Server reply: ");
		puts(server_reply);
	}
	
	close(server_sock);
	return 0;
}