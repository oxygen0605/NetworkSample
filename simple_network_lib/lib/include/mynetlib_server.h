#ifndef MYNETLIB_SERVER_H
#define MYNETLIB_SERVER_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>

struct server{
    int id;
    int sock;
    struct sockaddr_in sock_info;
    int sock_client;
    struct sockaddr_in sock_client_info;
    //int is_tcp;
    //int status;
    //struct *service;
};

struct server* new_server(int id);
int initialize_server(struct server *s);
int start_server_forever(struct server *s);
void delete_server(struct server **s);

#endif