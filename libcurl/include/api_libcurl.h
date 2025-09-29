#ifndef API_LIBCURL_H
#define API_LIBCURL_H

#include<curl/curl.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_RESET   "\x1b[0m"

struct memory{
    char *response;
    size_t size;
};

int setup_CURL( CURL *handle, const char *api_key, const char *host,struct curl_slist *header_slist, struct memory *chunk, char **error_buffer );
static size_t write_callback( char *data, size_t size, size_t nmemb, void *clientp );
char *error_buffer_init();
void perform_curl_query( CURL *handle, struct memory *data, char *error_buffer, const char *url);
CURL* init_curl_wrapper();
short check_perform( CURLcode code, char *error_buffer );
#endif
