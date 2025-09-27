#include "../include/get_matchday.h"

cJSON* create_json_obj( struct memory *data ){

    cJSON *root = cJSON_Parse( data->response );
    if( !root ){ fprintf( stderr, ANSI_COLOR_RED "can't parse the json file\n" ANSI_COLOR_RESET ); }
    
    return root;
}

cJSON* get_response( cJSON *obj ){
    cJSON *response = cJSON_GetObjectItem( obj, "response" );
    if( !response ){ fprintf( stderr, ANSI_COLOR_RED "can't get response item form json\n" ANSI_COLOR_RESET ); }

    return response;
    
}

struct league_matches *lm( cJSON *obj, const char *value ){

    cJSON *league;
    cJSON_ArrayForEach( league, obj ){
        cJSON *league_name = cJSON_GetObjectItem( league, "name" );
        if( league_name && cJSON_IsString( league_name ) && strcmp( league_name->valuestring, value )){
           //get league id
           //get match stage 
           //get matches 

        }
    }

    return NULL;
}
