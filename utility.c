#include "utility.h"


// Implementation limited to files smaller than 4gb due to fseek() limitations
char* get_file(char* file) {
	FILE* fp = fopen(file, "rb");
	char* buffer = 0;

	fseek(fp, 0, SEEK_END);
	long len = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	buffer = malloc(len+1);
	if(buffer) {
		fread(buffer, 1, len, fp);
	}
	buffer[len] = '\0';
	fclose(fp);
	return buffer;
}

long get_file_size(char* file) {
	FILE* fp = fopen(file, "r");
	fseek(fp, 0, SEEK_END);
	long len = ftell(fp);
	fclose(fp);
	return len;
}

void itos(int num, char* str) {
	sprintf(str, "%d", num);
}

void ltos(long num, char* str) {
	sprintf(str, "%ld", num);
}

// No check for if the replacement is bigger than the original substring
void replace(char* str, char* replace, char* replacement) {
	char res[30000] = {0};
	char* ip = &res[0];

	int o_len = strlen(replace);
	int n_len = strlen(replacement);

	char* tmp = str;

	while(1) {
		char* p = strstr(tmp, replace);

		if(p == NULL) {
			strcpy(ip, tmp);
			break;
		}

		memcpy(ip, tmp, p - tmp);
		ip += p - tmp;

		memcpy(ip, replacement, n_len);
		ip += n_len;

		tmp = p + o_len;
	}

	strcpy(str, res);
}


void get_mime_type(char* file, char* mime) {
	if(strstr(file, ".html")) {
		strcpy(mime, "text/html");
	}
	else if(strstr(file, ".css")) {
		strcpy(mime, "text/css");
	}
	else if(strstr(file, ".js")) {
		strcpy(mime, "text/javascript");
	}
	else if(strstr(file, ".txt")) {
		strcpy(mime, "text/plain");
	}
	else if(strstr(file, ".aac")) {
		strcpy(mime, "audio/aac");
	}
	else if(strstr(file, ".avi")) {
		strcpy(mime, "video/x-msvideo");
	}
	else if(strstr(file, ".bmp")) {
		strcpy(mime, "image/bmp");
	}
	else if(strstr(file, ".bz")) {
		strcpy(mime, "application/x-bzip");
	}
	else if(strstr(file, ".bz2")) {
		strcpy(mime, "application/x-bzip2");
	}
	else if(strstr(file, ".csh")) {
		strcpy(mime, "application/x-csh");
	}
	else if(strstr(file, ".css")) {
		strcpy(mime, "text/css");
	}
	else if(strstr(file, ".csv")) {
		strcpy(mime, "text/csv");
	}
	else if(strstr(file, ".doc")) {
		strcpy(mime, "application/msword");
	}
	else if(strstr(file, ".gz")) {
		strcpy(mime, "application/gzip");
	}
	else if(strstr(file, ".gif")) {
		strcpy(mime, "image/gif");
	}
	else if(strstr(file, ".ico")) {
		strcpy(mime, "image/vnd.microsoft.icon");
	}
	else if(strstr(file, ".jar")) {
		strcpy(mime, "application/java-archive");
	}
	else if(strstr(file, ".jpg")) {
		strcpy(mime, "image/jpeg");
	}
	else if(strstr(file, ".jpeg")) {
		strcpy(mime, "image/jpeg");
	}
	else if(strstr(file, ".json")) {
		strcpy(mime, "application/json");
	}
	else if(strstr(file, ".mjs")) {
		strcpy(mime, "text/javascript");
	}
	else if(strstr(file, ".mp3")) {
		strcpy(mime, "audio/mpeg");
	}
	else if(strstr(file, ".mpeg")) {
		strcpy(mime, "video/mpeg");
	}
	else if(strstr(file, ".mpkg")) {
		strcpy(mime, "application/vnd.apple.installer+xml");
	}
	else if(strstr(file, ".odp")) {
		strcpy(mime, "application/vnd.oasis.opendocument.presentation");
	}
	else if(strstr(file, ".ods")) {
		strcpy(mime, "application/vnd.oasis.opendocument.spreadsheet");
	}
	else if(strstr(file, ".odt")) {
		strcpy(mime, "application/vnd.oasis.opendocument.text");
	}
	else if(strstr(file, ".oga")) {
		strcpy(mime, "audio/ogg");
	}
	else if(strstr(file, ".ogv")) {
		strcpy(mime, "video/ogg");
	}
	else if(strstr(file, ".ogx")) {
		strcpy(mime, "application/ogg");
	}
	else if(strstr(file, ".otf")) {
		strcpy(mime, "font/otf");
	}
	else if(strstr(file, ".png")) {
		strcpy(mime, "image/png");
	}
	else if(strstr(file, ".pdf")) {
		strcpy(mime, "application/pdf");
	}
	else if(strstr(file, ".ppt")) {
		strcpy(mime, "application/vnd.ms-powerpoint");
	}
	else if(strstr(file, ".rar")) {
		strcpy(mime, "application/x-rar-compressed");
	}
	else if(strstr(file, ".rtf")) {
		strcpy(mime, "application/rtf");
	}
	else if(strstr(file, ".sh")) {
		strcpy(mime, "application/x-sh");
	}
	else if(strstr(file, ".svg")) {
		strcpy(mime, "image/svg+xml");
	}
	else if(strstr(file, ".tar")) {
		strcpy(mime, "application/x-tar");
	}
	else if(strstr(file, ".tif")) {
		strcpy(mime, "image/tiff");
	}
	else if(strstr(file, ".tiff")) {
		strcpy(mime, "image/tiff");
	}
	else if(strstr(file, ".wav")) {
		strcpy(mime, "audio/wav");
	}
	else if(strstr(file, ".weba")) {
		strcpy(mime, "audio/webm");
	}
	else if(strstr(file, ".webm")) {
		strcpy(mime, "video/webm");
	}
	else if(strstr(file, ".webp")) {
		strcpy(mime, "image/webp");
	}
	else if(strstr(file, ".xhtml")) {
		strcpy(mime, "application/xhtml+xml");
	}
	else if(strstr(file, ".xls")) {
		strcpy(mime, "application/vnd.ms-excel");
	}
	else if(strstr(file, ".xml")) {
		strcpy(mime, "text/xml");
	}
	else if(strstr(file, ".xul")) {
		strcpy(mime, "application/vnd.mozilla.xul+xml");
	}
	else if(strstr(file, ".zip")) {
		strcpy(mime, "application/zip");
	}
	else if(strstr(file, ".7z")) {
		strcpy(mime, "application/x-7z-compressed");
	}
	else {
		strcpy(mime, "application/octet-stream");
	}
}
