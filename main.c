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
        // Set up socket
        int listener_d = socket(PF_INET, SOCK_STREAM, 0);
        if (listener_d == -1)
            error("Can't open socket");
        
        // Bind to a port
        struct sockaddr_in name;
        name.sin_family = PF_INET;
        name.sin_port = (in_port_t)htons(30000);
        name.sin_addr.s_addr = htonl(INADDR_ANY);
        int c = bind (listener_d, (struct sockaddr *) &name, sizeof(name));

        is_host = 1;
    }
    
    // run as player
    else if (argc == 3 && !strcmp(argv[1],"-join"))
    {
        puts("Running as player");
        // do player join stuff here
        // do fork
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

