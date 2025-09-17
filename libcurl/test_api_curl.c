#include<stdio.h>
#include<stdlib.h>
#include<curl/curl.h>
#include<string.h>

//TODO easy perform 
//TODO get url api key host 
//TODO write the buffer of the perform into file (test solution)
//TODO get the json
//TODO parse the json

struct memory{
    char *response;
    size_t size;
};


int setup_CURL( CURL *handle, const char *URL, const char *api_key, const char *host, struct memory *chunk, FILE *fd );
static size_t write_callback( char *data, size_t size, size_t nmemb, void *clientp );
void print_file( FILE *fd );
char *error_buffer_init();
void perform_curl_query( CURL *handle, FILE *fd );
CURL* init_curl_wrapper();
short check_perform( CURLcode code );



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

int setup_CURL( CURL* handle, const char *URL, const char *api_key, const char *host, struct memory *chunk, FILE *fd ){

    struct curl_slist *header_slist = NULL;
    struct curl_slist *temp = NULL;

     

    char *error_buffer = error_buffer_init();
    curl_easy_setopt( handle, CURLOPT_ERRORBUFFER, error_buffer );
    
    curl_easy_setopt( handle, CURLOPT_HTTPGET, 1L );
    curl_easy_setopt( handle, CURLOPT_URL, URL );

    header_slist = curl_slist_append( header_slist, api_key );
    if( !header_slist ){ return -1; }
    
    temp = curl_slist_append( header_slist, host );
    if( !temp ){ 
	    curl_slist_free_all( header_slist );
	    return -1; 
    }
    
    header_slist=temp;

    curl_easy_setopt( handle, CURLOPT_HTTPHEADER, header_slist );
    
    curl_easy_setopt( handle, CURLOPT_WRITEFUNCTION, write_callback );
    curl_easy_setopt( handle, CURLOPT_WRITEDATA, ( void * )chunk ); 

    /*
     * all set perform the query 
     * */
    perform_curl_query( handle, fd );
    
    /* after perform */
    free( chunk->response );
    chunk->response = NULL;
    chunk->size = 0;
    
    return 0;

}

static size_t write_callback( char *data, size_t size, size_t nmemb, void* clientp ){
    size_t real_size = size * nmemb;
    struct memory *mem = ( struct memory * )clientp;

    char *ptr = realloc( mem->response, mem->size + real_size + 1 );
    if( !ptr ){ return 0; } /* realloc error out of memory */

    mem->response = ptr;
    memcpy( &( mem->response[ mem->size ] ), data, real_size ); 
    mem->size += real_size;
    mem->response[ mem->size ] = 0;

    return real_size;
}

void perform_curl_query( CURL *handle, FILE *fd ){
    CURLcode code;
    short result = -1;
    code  = curl_easy_perform( handle );

    result = check_perform( code );
    if( result < 0 ){ return; }
    else{ print_file( fd ); } /* put result into file */
    
}


