#include "../include/input.h"
#include "../include/api_libcurl.h"
#include "../include/get_matchday.h"

int main(){

    int success;

    char *url;
    char *api_key;
    char *host;
    char *err_buffer;

    cJSON *root = NULL;
    cJSON *response = NULL;


    struct memory data = {0};
    struct league_matches *lm; 
    struct curl_slist *header_list = NULL;

    CURL *handle = init_curl_wrapper();

    //get headers
    setup_api_headers( &api_key, &host );
    //get query url
    get_match_current_date_url( &url );
    
    success = setup_CURL( handle, api_key, host, header_list,  &data, &err_buffer);
    if( success < 0 ){ 
        
        fprintf( stderr, "Unable to setup headers\n" ); 
        free( err_buffer );
        free( err_buffer );
        free( data.response );
        data.response = NULL;
        data.size = 0;
        curl_slist_free_all( header_list );
        curl_easy_cleanup( handle );
        return -1; 
    }

    perform_curl_query( handle, &data, err_buffer, url ); 

    create_json_obj( &data, &root );
    get_response( root, &response );
    parse_lm( response, "Serie A", &lm ); 

    
    //free( (void*)err_buffer );

    printf( "league match home: %s\n", lm->td_matches[0].home->team_name );
    printf( "league match away: %s\n", lm->td_matches[0].away->team_name);
    free( data.response );
    data.response = NULL;
    data.size = 0;
    curl_slist_free_all( header_list );
    curl_easy_cleanup( handle );
    cJSON_Delete( root );
    free( lm->league_name );
    free( lm->td_matches->match_time );
    free( lm->td_matches->match_stage );
    free( lm->td_matches->m_status);
    free( lm->td_matches->home->team_name);
    free( lm->td_matches->home);
    free( lm->td_matches->away->team_name);
    free( lm->td_matches->away);

}
