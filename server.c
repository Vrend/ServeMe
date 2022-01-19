#include "server.h"

volatile sig_atomic_t running;


int main() {
	running = 1;
	print_splash();
	listen_for_requests();
	printf("OK!\n");
	return 0;
}



void print_splash() {

	printf("   _____                     __  __      \n");
	printf("  / ____|                   |  \\/  |     \n");
	printf(" | (___   ___ _ ____   _____| \\  / | ___ \n");
	printf("  \\___ \\ / _ \\ '__\\ \\ / / _ \\ |\\/| |/ _ \\\n");
	printf("  ____) |  __/ |   \\ V /  __/ |  | |  __/\n");
	printf(" |_____/ \\___|_|    \\_/ \\___|_|  |_|\\___|\n");
	printf("                                         \n");
	printf("                                         \n");

	printf("ServeME Copyright (C) 2019 Vrend\nServeMe comes with ABSOLUTELY NO WARRANTY.\nThis is free software, and you are welcome to redistribute it under certain conditions.\nFor more information, see the LICENSE file and the README.\n\n");
}

void handle_sigint(int signum) {
	running = 0;
	printf("\nShutting down server...");
}


void listen_for_requests() {
	struct sockaddr_in address;
	int fd = socket(AF_INET, SOCK_STREAM, 0);

	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(PORT);

	int addr_len = sizeof(address);

	int opt = 1;

	if(setsockopt(fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
		printf("Failed at setsockopt, exiting...\n");
		exit(1);
	}

	if(bind(fd, (struct sockaddr*) &address, addr_len) < 0) {
		printf("Server failed to bind, exiting...\n");
		exit(1);
	}


	int flags = fcntl(fd, F_GETFL);
	fcntl(fd, F_SETFL, flags | O_NONBLOCK);

	if(listen(fd, 99) < 0) {
		printf("Server failed to listen, exiting...\n");
		exit(1);
	}

	signal(SIGINT, handle_sigint);
	while(running) {
		//printf("Waiting for requests\n");
		int new_connection = accept(fd, (struct sockaddr*) &address, (socklen_t*) &addr_len);
		if(new_connection < 0) {
			sleep(0.1);
			continue;
		}

		pthread_t client;
		response_args* args = (response_args*) malloc(sizeof(response_args));
		args->fd = new_connection;
		strcpy(args->ip, inet_ntoa(address.sin_addr));
		args->port = (int) ntohs(address.sin_port);
		pthread_create(&client, NULL, handle_connection, (void*) args);
		//sleep(1);
	}

	close(fd);
}

void* handle_connection(void* args) {
	pthread_detach(pthread_self());
	int fd = ((response_args*) args)->fd;
	char ip[30];
	strcpy(ip, ((response_args*) args)->ip);
	int port = ((response_args*) args)->port;
	free(args);

	char* read_buffer = (char*) malloc(30000);
	bzero(read_buffer, 30000);

	read(fd, read_buffer, 30000);

	//printf("%s\n", read_buffer);

	printf("Request from %s on port %d\n", ip, port);

	request_return request = handle_request(read_buffer);

	handle_response(request, fd);

	close(fd);

	pthread_exit(0);
}
