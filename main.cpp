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
const int BACKLOG = 10;

int create_socket();
void set_socket_options(int skt);
void bind_socket_to_port(int skt, int port);
void start_listening(int skt);

int main() {
    int skt = create_socket();

    set_socket_options(skt);

    bind_socket_to_port(skt, PORT);

    start_listening(skt);

    return 0;
}

void start_listening(int skt) {
    if (listen(skt, BACKLOG) < 0) {
        std::cerr << "start_listening() failed";
        close(skt);
        exit(EXIT_FAILURE);
    }
}

void bind_socket_to_port(int skt, int port) {
    // IPv4 Structure
    sockaddr_in address;
    std::memset(&address,0,sizeof(address));

    address.sin_family = AF_INET; // Set to IPv4 family
    address.sin_addr.s_addr = INADDR_ANY; // Accept connections from any IP
    address.sin_port = htons(port); // convert port to network byte order

    if (bind(skt, (struct sockaddr*)&address, sizeof(address)) < 0) {
        std::cerr << "bind_socket_to_port() failed";
        close(skt);
        exit(EXIT_FAILURE);
    }

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
