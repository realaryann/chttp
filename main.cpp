#include <iostream>
#include <string>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>

/*
Create a socket – This gives an endpoint for communication.

Bind the socket to a port – So the server knows where to listen.

Listen – This enables the server to accept incoming connections.

Accept – When a client connects, accept the connection and get a new socket to communicate.

*/

const int PORT=8080;

int create_socket();
void set_socket_options(int skt);

int main() {
    int skt = create_socket();

    set_socket_options(skt);

    return 0;
}

int create_socket() {
    // Create a TCP socket
    int res = socket(AF_INET, SOCK_STREAM, 0);
    if (res == -1) {
        std::cerr << "create_socket() failed";
        exit(EXIT_FAILURE);
    }
    return res;
}

void set_socket_options(int skt) {
    int optval = 1;

    if (setsockopt(skt, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)) < 0) {
        std::cerr << "set_socket_options failed";
        close(skt);
        exit(EXIT_FAILURE);
    }

}
