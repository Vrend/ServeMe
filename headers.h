#include "dependencies.h"
#include "utility.h"

// Methods

header_return* handle_headers(char** headers, char* req);

int handle_header(char* header, char* req, header_return* ret, int* mime_set);
