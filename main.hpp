#pragma once

#include <iostream>
#include <string>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>

const int PORT=8080;
const int BACKLOG = 10;

int create_socket();
void set_socket_options(int server_fd);
void bind_socket_to_port(int server_fd, int port);
void start_listening(int server_fd);
int accept_connection(int server_skt);
