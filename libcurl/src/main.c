#include "../include/input.h"
#include "../include/api_libcurl.h"
#include "../include/get_matchday.h"
#include "../include/get_standings.h"

int main(){

    int success;
    bool ok_parse = false;

    char *url;
    char *api_key;
    char *host;
    char *err_buffer;

    cJSON *root = NULL;
    cJSON *response = NULL;


    struct memory data = {0};
    struct league_matches *lm; 
    struct standings *ts = NULL;
    struct curl_slist *header_list = NULL;

    CURL *handle = init_curl_wrapper();

    //get headers
    setup_api_headers( &api_key, &host );
    //get query url
    get_league_standings( &url ); 
    printf("%s\n", url );
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
    //ok_parse = parse_lm( response, "Serie A", &lm ); 
    //if( !ok_parse ){ return -1; }
    ok_parse = parse_standings( response, &ts );
    if( !ok_parse ){ return -1; }


    
    for( unsigned int index = 0; index < 20; index++ ){

        printf("%d ", ts->team_list[index].pos);
        printf("%s\n", ts->team_list[index].team_name);
        free( ts->team_list[index].team_name );
    }
    
    free( (void*)err_buffer );

    free( data.response );
    data.response = NULL;
    data.size = 0;
    curl_slist_free_all( header_list );
    curl_easy_cleanup( handle );
    cJSON_Delete( root );
    free( ts->team_list );
    free( ts );
    //free( lm->league_name );
    //free( lm->td_matches->match_time );
    //free( lm->td_matches->match_stage );
    //free( lm->td_matches->m_status);
    //free( lm->td_matches->home->team_name);
    //free( lm->td_matches->home);
    //free( lm->td_matches->away->team_name);
    //free( lm->td_matches->away);

}
