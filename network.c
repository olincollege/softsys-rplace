#include "header.h"

int read_in(int socket, char *buf, int len) {
    char *s = buf;
    int slen = len;
    int c = recv(socket, s, slen, 0);

    while ((c > 0) && (s[c-1] != '\n')) {
        s += c;
        slen -= c;
        c = recv(socket, s, slen, 0);
    }
    if (c < 0)      // error checking
        return c;
    else if (c == 0)    // nothing read, empty string
        buf[0] = '\0';
    else
        s[c-1] = '\0';  // replace \r with \0
    return len - slen;
}

void error(char *msg) {
    fprintf(stderr, "%s: %s\n", msg, strerror(errno));
    exit(1);
}

int open_listener_socket() {
    int s = socket(PF_INET, SOCK_STREAM, 0);
    if (s == -1)
        error("Can't open socket");
    return s;
}

// Bind a socket to a port
void bind_to_port(int socket, int port) {
    struct sockaddr_in name;
    name.sin_family = PF_INET;
    name.sin_port = (in_port_t)htons(port);
    name.sin_addr.s_addr = htonl(INADDR_ANY);
    // Set reuse option on port before binding
    int reuse = 1;
    if (setsockopt(socket, SOL_SOCKET, SO_REUSEADDR, (char*)&reuse, sizeof(int)) == -1)
        error("Can't set the reuse option on the socket");
    if (bind(socket, (struct sockaddr *) &name, sizeof(name)) == -1)
        error("Can't bind the port");
}

// Send string from server to client
int say(int socket, char *s) {
    int res = send(socket, s, strlen(s), 0);
    if (res == -1)
        fprintf(stderr, "%s: %s\n", "Error talking to the client", strerror(errno));
    return res;
}