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

int create_socket() {
    // Create a TCP socket
    int res = socket(AF_INET, SOCK_STREAM, 0);
    if (res == 0) {
        perror("create_socket() failed");
        exit(1);
    }
    return res;
}

int main() {
    int skt = create_socket();
    return 0;
}