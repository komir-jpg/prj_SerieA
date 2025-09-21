#include "../include/input.h"
#include <time.h>


//TODO key should not be visible
//TODO get matches by current date
//TODO get matches by given date
//TODO get given match stats lineup ecc..
//TODO get current standings
//TODO get player stats

void get_current_date( char **date ){

    time_t now = time( NULL );
    struct tm *tm_info = localtime( &now );

    //free after the api call
    *date = malloc( DATE_STR_SIZE*sizeof( char ) );
    strftime( *date, DATE_STR_SIZE, "%Y-%m-%d", tm_info );

}

char* set_api_key(){

    const char *env_key = getenv( "API_KEY" );
    int size = snprintf( NULL, 0, API_KEY, env_key );
    
    //free before program ends
    char *api_header = malloc( size + 1 );
    if( !api_header ){ fprintf( stderr, "malloc error\n" ); return NULL;  }

    snprintf( api_header, size + 1, API_KEY, env_key );
    return api_header;
}


void setup_api_headers( char **api_header, char **host_header ){

    size_t str_len = strlen( API_HOST );

    //free before program ends
    *host_header = malloc( str_len + 1 );
    if( !*host_header ){ fprintf( stderr, "malloc error\n" ); return; }

    snprintf( *host_header, str_len + 1, API_HOST );

    *api_header = set_api_key();

}


