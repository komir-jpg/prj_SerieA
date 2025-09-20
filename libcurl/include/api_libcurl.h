#ifndef API_LIBCURL
#define API_LIBCURL

#include<curl/curl.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct memory{
    char *response;
    size_t size;
};

int setup_CURL( CURL *handle, const char *URL, const char *api_key, const char *host, struct memory *chunk, FILE **fd );
static size_t write_callback( char *data, size_t size, size_t nmemb, void *clientp );
void print_file( FILE **fd, struct memory *data );
char *error_buffer_init();
void perform_curl_query( CURL *handle, FILE **fd, struct memory *data, char *error_buffer );
CURL* init_curl_wrapper();
short check_perform( CURLcode code, char *error_buffer );

#endif
