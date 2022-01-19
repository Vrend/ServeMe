#include "dependencies.h"
#include "headers.h"

// Methods

request_return handle_request(char* request);

void split_by_line(char* request, char** lines);

void get_request_line_params(char* request, char** res);

void free_request(char** request);

char* translate_url_to_file(char* url);
