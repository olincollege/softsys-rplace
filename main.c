// Authors: Chris Allum, Berwin Lan, Maya Sivanandan

# include "header.h"


int main(int argc, char *argv[])
{
    // ----------SETUP--------------
    int is_host;


    // run as host
    if (argc == 2 && !strcmp(argv[1],"-host"))
    {
        puts("Running as Host");

        // do server setup things here
        // Open socket
        int listener_d = socket(PF_INET, SOCK_STREAM, 0);
        if (listener_d == -1)
            error("Can't open socket");
        
        // Bind to port
        bind_to_port(listener_d, 30000);

        // Listen with a max queue of 3
        if (listen(listener_d, 3) == -1)
            error("Can't listen");

        // Accept a connection
        while (1) {
            struct sockaddr_storage client_addr;
            unsigned int address_size = sizeof(client_addr);
            int connect_d = accept(listener_d, (struct sockaddr *)&client_addr, &address_size);
            if (connect_d == -1)
                error("Can't open secondary socket");

            // Test send to client
            char *msg = "Hello from the server!\n";
            say(connect_d, msg);

            chose(connect_d);
        }

        is_host = 1;
    }
    
    // run as player
    else if (argc == 3 && !strcmp(argv[1],"-join"))
    {
        puts("Running as player");
        // do player join stuff here
        // do fork - looking at Beej's guide, I think the server forks? -BL
        is_host = 0;
    }
    else {
        puts("ERROR \nTo run r/place as host:\n./main -host\nTo run as a player:\n./main -join [IP]");
        return 0;
    }

    // -----------MAIN-----------------

    if (is_host)
    {
        State* state = init();

    }
    else
    {
        // do fork stuff
    }

    // draw state temporary place for testing stuff
    
    init_screen();
    for (;;){
        draw_all();
    }

}

