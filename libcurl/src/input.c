#include "../include/input.h"
#include <time.h>


//TODO key should not be visible
//TODO get matches by current date
//TODO get matches by given date
//TODO get given match stats lineup etc..
//TODO get current standings
//TODO get player stats

char *get_current_date(){

    time_t now = time( NULL );
    struct tm *tm_info = localtime( &now );

    //free after the api call
    char *date = malloc( DATE_STR_SIZE*sizeof( char ) );
    strftime( date, DATE_STR_SIZE, "%Y-%m-%d", tm_info );

    return date;

}

char* set_api_key(){

    const char *env_key = getenv( "API_KEY" );
    int size = snprintf( NULL, 0, API_KEY, env_key );
    
    char *api_header = malloc( size + 1 );
    if( !api_header ){ fprintf( stderr, "malloc error\n" ); return NULL;  }

    snprintf( api_header, size + 1, API_KEY, env_key );
    printf("\n%s\n", api_header);
    return api_header;
}


void setup_api_headers( char **api_key_header, char **host_header ){

    size_t str_len = strlen( API_HOST );

    *host_header = malloc( str_len + 1 );
    if( !*host_header ){ fprintf( stderr, "malloc error\n" ); return; }

    snprintf( *host_header, str_len + 1, API_HOST );

    *api_key_header = set_api_key();

}

void get_match_current_date_url( char **api_call_url ){
    //here the usern gets no prompt the program figures itself current date
    char *date = get_current_date(); 
    //first we get the size of the string concatenation
    unsigned int size = snprintf( NULL, 0, CALL_FIX_CURR_DATE, date );

    *api_call_url = malloc( size + 1 );
    if( !*api_call_url ){ fprintf( stderr, "malloc error\n" ); return; }

    snprintf( *api_call_url, size + 1,  CALL_FIX_CURR_DATE, date );
    printf("\n%s\n", *api_call_url );
}
