#include "../include/input.h"
#include "../include/api_libcurl.h"

int main(){

    int success;

    char *url;
    char *api_key;
    char *host;
    char *err_buffer;

    FILE *fd = NULL;

    struct memory data = {0};
    struct curl_slist *header_list = NULL;

    CURL *handle = init_curl_wrapper();
    
    //get api key
    //get headers
    //get url
    //put all in setup function
    //result

    //get headers
    setup_api_headers( &api_key, &host );
    //get query url
    get_match_current_date_url( &url );
    
    success = setup_CURL( handle, api_key, host, header_list,  &data, &err_buffer);
    if( success < 0 ){ 
        
        fprintf( stderr, "Unable to setup headers\n" ); 
        //free( err_buffer );
        curl_slist_free_all( header_list );
        curl_easy_cleanup( handle );
        return -1; 
    }

    perform_curl_query( handle, &fd, &data, err_buffer, url ); 
    //free( err_buffer );
    curl_slist_free_all( header_list );
    curl_easy_cleanup( handle );

}
