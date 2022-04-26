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

