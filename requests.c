#include "requests.h"

request_return handle_request(char* request) {
	char** lines = (char**) malloc(100*sizeof(char*));
	bzero(lines, 400);
	split_by_line(request, lines);

	char* file = NULL;
	char mime[100];
	char lang[20];
  int res = 0;
	int me = -1;

	char* request_line = lines[0];
	if(request_line == NULL) {
		printf("Invalid request\n");
		res = 400;
		goto return_here;
	}

	char* request_pieces[3];
	get_request_line_params(request_line, request_pieces);
	char* method = request_pieces[0];

	if(strcmp(request_pieces[2], "HTTP/1.1\r") != 0) {
		printf("Invalid Protocol: %s\n", request_pieces[2]);
		res = 505;
		goto return_here;
	}

	if(strcmp(method, "GET") == 0 || strcmp(method, "HEAD") == 0) {
		if(strcmp(method, "GET") == 0) {
			me = 0;
		}
		else {
			me = 1;
		}
		char* resource = request_pieces[1];
		file = translate_url_to_file(resource);
		if(strcmp(file, "ERROR: File Not Found") == 0) {
			//printf("File Not Found\n");
      res = 404;
			file = NULL;
		}
		else {
			header_return* headers = handle_headers(lines, file);
			if(headers == NULL) {
				res = 406;
				goto return_here;
			}

			strcpy(mime, headers->mime);
			strcpy(lang, headers->lang);
			free(headers);
			//printf("Valid file\n");
			res = 200;
		}
	}
	else {
		printf("Invalid method: %s\n", method);
		res = 501;
	}

return_here:
	; // Wow C is dumb with labels, can't believe this is actually necessary for compiling
  request_return ret;
  ret.response = res;
	ret.method = me;

	if(file != NULL) {
		//printf("File isn't null\n");
    strcpy(ret.file, file);
		strcpy(ret.mime, mime);
		strcpy(ret.lang, lang);
		free(file);
	}

	free_request(lines);
	free(request);

	return ret;
}



void split_by_line(char* request, char** lines) {
	char* line = NULL;
	int i = 0;
	line = strtok(request, "\n");
	while(line != NULL) {
		lines[i] = (char*) malloc(300);
		strcpy(lines[i], line);
		line = strtok(NULL, "\n");
		i++;
	}
}

void get_request_line_params(char* request, char** res) {
		char* piece = strtok(request, " ");
		int i = 0;
		while(piece != NULL) {
			//printf("%s\n", piece);
			res[i] = piece;
			piece = strtok(NULL, " ");
			i++;
		}
}

void free_request(char** request) {
	for(int i = 0; i < 100; i++) {
		if(request[i] == NULL) {
			break;
		}
		free(request[i]);
	}
	free(request);
}

char* translate_url_to_file(char* url) {
	if(strcmp(url, "/") == 0) {
		url = "/index.html";
	}
	char* file = (char*) malloc(200);
	strcpy(file, "files");
	file = strcat(file, url);

	if(access(file, F_OK) != -1) {
		return file;
	}
	else {
		free(file);
		return "ERROR: File Not Found";
	}
}
