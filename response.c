#include "response.h"

int handle_response(request_return request, int fd) {

	printf("Response Code: %i\n", request.response);

	if(request.response == 200) {
		char* header = (char*) malloc(50000);
		bzero(header, 50000);
		char* data = get_file(request.file);

		char data_len[200];
		int file_len = (int) get_file_size(request.file);
		itos(file_len, data_len);

		strcpy(header, "HTTP/1.1 200 OK\r\nContent-Type: ");
		strcat(header, request.mime);
		strcat(header, "\r\nContent-Length: ");
		strcat(header, data_len);
		strcat(header, "\r\nContent-Language: ");
		strcat(header, request.lang);
		strcat(header, "\r\nServer: ServeMe Webserver\r\n");
		strcat(header, "Connection: Closed\r\n\r\n");

		write(fd, header, strlen(header));

		if(request.method == 0) {
			char* ptr = data;
			int size = file_len;
			while(size > 0) {
				int num = write(fd, ptr, size);
				ptr += num;
				size -= num;
			}
		}

		free(data);
		free(header);
	}
	else {
		char header[30000];
		char* body = get_file("error.html");
		char code[200];
		itos(request.response, code);
		replace(body, "ERROR", code);
		char body_len[200];
		itos(strlen(body), body_len);
		if(request.response == 404) {
			strcpy(header, "HTTP/1.1 404 Not Found\r\nContent-Length: ");
		}
		else if(request.response == 400) {
			strcpy(header, "HTTP/1.1 400 Bad Request\r\nContent-Length: ");
		}
		else if(request.response == 505) {
			strcpy(header, "HTTP/1.1 505 HTTP Version Not Supported\r\nContent-Length: ");
		}
		else if(request.response == 501) {
			strcpy(header, "HTTP/1.1 501 Not Implemented\r\nContent-Length: ");
		}
		else if(request.response == 406) {
			strcpy(header, "HTTP/1.1 406 Not Acceptable\r\nContent-Length: ");
		}

		strcat(header, body_len);
		strcat(header, "\r\nContent-Language: en\r\n");
		strcat(header, "Content-Type: text/html\r\nServer: ServeMe Webserver\r\nConnection: Closed\r\n\r\n");
		strcat(header, body);

		write(fd, header, strlen(header));

		free(body);
	}

	return 0;
}
