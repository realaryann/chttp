#include "main.hpp"
/*
Create a socket – This gives an endpoint for communication.

Bind the socket to a port – So the server knows where to listen.

Listen – This enables the server to accept incoming connections.

Accept – When a client connects, accept the connection and get a new socket to communicate.

*/

int main() {
    int server_fd = create_socket();

    set_socket_options(server_fd);

    bind_socket_to_port(server_fd, PORT);

    start_listening(server_fd);

    while(true) {
        int client_fd = accept_connection(server_fd);
        std::cout << client_fd;
    }

    return 0;
}

int accept_connection(int server_skt) {
    sockaddr_in client_addr;
    socklen_t client_len = sizeof(client_addr);

    int client_fd = accept(server_skt, (struct sockaddr*)&client_addr, &client_len);
    if (client_fd < 0) {
        std::cerr << "accept_connection() failed";
        close(server_skt);
        exit(EXIT_FAILURE);
    }

    std::cout << "Connection Accepted from" <<
    inet_ntoa(client_addr.sin_addr) << ":" << ntohs(client_addr.sin_port) << "\n";

    return client_fd;

}

void start_listening(int server_fd) {
    if (listen(server_fd, BACKLOG) < 0) {
        std::cerr << "start_listening() failed";
        close(server_fd);
        exit(EXIT_FAILURE);
    }
}

void bind_socket_to_port(int server_fd, int port) {
    // IPv4 Structure
    sockaddr_in address;
    std::memset(&address,0,sizeof(address));

    address.sin_family = AF_INET; // Set to IPv4 family
    address.sin_addr.s_addr = INADDR_ANY; // Accept connections from any IP
    address.sin_port = htons(port); // convert port to network byte order

    if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
        std::cerr << "bind_socket_to_port() failed";
        close(server_fd);
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

void set_socket_options(int server_fd) {
    int optval = 1;

    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)) < 0) {
        std::cerr << "set_socket_options failed";
        close(server_fd);
        exit(EXIT_FAILURE);
    }

}
