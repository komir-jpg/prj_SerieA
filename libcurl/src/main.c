#include "../include/input.h"
#include "../include/api_libcurl.h"

int main(){

    int success;

    char *url;
    char *api_key;
    char *host;

    FILE *fd = NULL;

    struct memory data = {0};

    CURL *handle = init_curl_wrapper();
    
    parse_input( &url, &api_key, &host ); 


    success = setup_CURL( handle, url, api_key, host, &data, &fd );
    if( success < 0 ){ fprintf( stderr, "Unable to setup headers\n" ); return -1; }

}
