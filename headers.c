#include "headers.h"

header_return* handle_headers(char** headers, char* req) {
	int mime_set = 0;

	if(strcmp(req, "ERROR: File Not Found") == 0) {
		return NULL;
	}

	header_return* ret = (header_return*) malloc(sizeof(header_return));
	for(int i = 0; i < 100; i++) {
		char* header = headers[i];
		if(header == NULL) {
			break;
		}
		int succ = handle_header(header, req, ret, &mime_set);
		if(succ < 0) {
			return NULL;
		}
	}
	if(mime_set == 0) {
		strcpy(ret->mime, "application/octet-stream");
	}
	strcpy(ret->lang, "en");

	return ret;
}

int handle_header(char* header, char* req, header_return* ret, int* mime_set) {
	char start[strlen(header)+1];
	bzero(start, sizeof(start));
	char* end = NULL;
	for(int i = 0; i < strlen(header); i++) {
		char ch = header[i];
		if(ch == ':') {
			end = &header[i+1];
			strncpy(start, header, i);
			start[i] = '\0';
			break;
		}
	}

	if(strcmp(start, "Accept") == 0) {
		char mime[100];
		get_mime_type(req, mime);
		if(strstr(end, mime) || strstr(end, "*/*")) {
			strcpy(ret->mime, mime);
			*mime_set = 1;
		}
		else {
			return -1;
		}
	}
	else if(strcmp(start, "Accept-Charset") == 0) {
		if(strstr(end, "utf-8") == NULL) {
			return -1;
		}
	}
	else if(strcmp(start, "Accept-Language") == 0) {
		if(strstr(end, "en") == NULL) {
			return -1;
		}
	}

	return 0;
}
