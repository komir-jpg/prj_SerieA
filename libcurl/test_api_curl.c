#include<stdio.h>
#include<stdlib.h>
#include<curl/curl.h>

CURL* init_curl_wrapper();
void set_curl_opt_GET( CURL *handle, char *URL, char *api_key, char *host);
char *error_buffer_init();

int main(){
}


CURL* init_curl_wrapper(){
    
    CURL *handle=NULL;
    CURLcode global_result = curl_global_init( CURL_GLOBAL_ALL );

    if ( global_result != CURLE_OK ){
        fprintf( stderr, "Critical error curl_global_init() failed: %s\n", curl_easy_strerror( global_result ) );
        exit ( EXIT_FAILURE );
    }

    handle = curl_easy_init();

    if( !handle ){ 
        fprintf( stderr, "Critical error curl_easy_init failed\n" ); 
        curl_global_cleanup();
        exit( EXIT_FAILURE );
    }

    return handle;
}

char *error_buffer_init(){
    
    /* remember to free the buffer when calling curl_easy_cleanup */

    char *error_buffer = NULL;
    error_buffer = ( char* )calloc( CURL_ERROR_SIZE, sizeof( char ) );
    
    return error_buffer;
}

void set_curl_opt_GET( CURL* handler, char *URL, char *api_key, char *host ){

    struct curl_slist *header_slist = NULL;
    struct curl_slist *temp = NULL;
    char *url = NULL;

    char *error_buffer = error_buffer_init();
    curl_easy_setopt( handler, CURLOPT_ERRORBUFFER, error_buffer );
    curl_easy_setopt( handler, CURLOPT_HTTPGET, 1L );

    curl_easy_setopt( handler, CURLOPT_URL, URL );


}





