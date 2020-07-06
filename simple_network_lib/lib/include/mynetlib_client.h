#ifndef MYNETLIB_CLIENT_H
#define MYNETLIB_CLIENT_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<netdb.h>

struct client{
	int id;
	int sock;
	struct sockaddr_in server;
  	unsigned int **addrptr;
	char *ipv4_deststr; // "xxx.xxx.xxx.xxx\0" で最大16バイト
	//int is_tcp;
	//int status;
	//int service_ids[10];
};

struct client* new_client(int id);
int connect_server(struct client *c, char* deststr);
void delete_client(struct client **c);
void print_client_info(struct client *client);

#endif