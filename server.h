#include "dependencies.h"
#include "requests.h"
#include "utility.h"
#include "response.h"

// Constants

#define PORT 80


// Structs

typedef struct response_args {
	int fd;
	char ip[30];
	int port;
} response_args;


// Method Declarations

void listen_for_requests();

void* handle_connection(void* args);

void print_splash();
