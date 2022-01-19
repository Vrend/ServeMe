#ifndef DEPENDENCIES_H
#define DEPENDENCIES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <pthread.h>
#include <fcntl.h>
#include <signal.h>
#include <arpa/inet.h>

// Structs

typedef struct request_return {
	int response;
	int method;
	char file[200];
	char mime[100];
	char lang[20];
} request_return;

typedef struct header_return {
	char mime[100];
	char lang[20];
} header_return;


#endif
