#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int parse_input( char *url, char *api_key, char *host ){

    char API_URL[ 1024 ] = {0};
    char API_KEY[ 1024 ] = {0};
    char API_HOST[ 1024 ] = {0};

    char *temp_key = "x-rapidapi-key: ";
    char *temp_host = "x-rapidapi-host: ";

    size_t len;

    printf( "insert API query URL: " );
    fflush( stdout );
    fgets( API_URL, sizeof( API_URL ), stdin );
    printf( "insert API key: " );
    fflush( stdout );
    fgets( API_KEY, sizeof( API_KEY), stdin );
    printf( "insert API host: " );
    fflush( stdout );
    fgets( API_HOST, sizeof( API_HOST), stdin );

    API_URL[ strcspn( API_URL, "\n" ) ] = '\0';
    API_KEY[ strcspn( API_KEY, "\n" ) ] = '\0';
    API_HOST[ strcspn( API_HOST, "\n" ) ] = '\0';

    len = strlen( API_KEY );
    api_key = malloc( len + 1 );
    if( !api_key ){ perror ( "malloc" ); exit(1); }
    strcpy( api_key, API_KEY);
    api_key = strcat( temp_key, api_key );
    
    
    len = strlen( API_HOST );
    host = malloc( len + 1 );
    if( !host){ perror ( "malloc" ); exit(1); }
    strcpy( host, API_HOST );
    host = strcat( temp_host, host );

    return 0;


}
