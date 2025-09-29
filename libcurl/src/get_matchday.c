#include "../include/get_matchday.h"

cJSON* create_json_obj( struct memory *data, cJSON **root ){

    *root = cJSON_Parse( data->response );
    if( !*root ){ fprintf( stderr, ANSI_COLOR_RED "can't parse the json file\n" ANSI_COLOR_RESET ); }
    
    return NULL;
}

cJSON* get_response( cJSON *obj, cJSON **response ){
    *response = cJSON_GetObjectItem( obj, "response" );
    if( !*response ){ fprintf( stderr, ANSI_COLOR_RED "can't get response item form json\n" ANSI_COLOR_RESET ); }

    return NULL;
    
}

struct league_matches *parse_lm( cJSON *obj, const char *value, struct league_matches **lm ){

    cJSON *league;
    //TODO free after usage
    *lm = calloc( 1, sizeof( struct league_matches ) );
    cJSON_ArrayForEach( league, obj ){
        cJSON *league_name = cJSON_GetObjectItem( league, "name" );

        if(  league_name && cJSON_IsString( league_name ) && ( strcmp( league_name->valuestring, value ) == 0 )){
           //get league id
           cJSON *league_ID = cJSON_GetObjectItem( league, "id" );
           if( cJSON_IsNumber( league_ID ) ){ (*lm)->league_ID = league_ID->valueint; }
           //get league_name
           //TODO free after usage
           (*lm)->league_name = malloc( strlen( league_name->valuestring ) + 1 );
           strcpy( (*lm)->league_name, league_name->valuestring );
           //get matches 
           parse_matches( league, *lm );

           break;
        }
    }

    return NULL;
}

void parse_matches( cJSON *obj, struct league_matches *lm ){

    cJSON *curr_m;
    cJSON *matches = cJSON_GetObjectItem( obj, "matches" );
    //get the number of matches
    unsigned int num_m = cJSON_GetArraySize( matches );

    //TODO free after usage
    struct match *m_list = calloc( num_m, sizeof( struct match ));
    if( !m_list ){ fprintf( stderr, ANSI_COLOR_RED "error malloc struct match\n" ANSI_COLOR_RESET ); }


    unsigned int index = 0;
    cJSON_ArrayForEach( curr_m, matches ){

        struct match *m_struct = &m_list[ index++ ];
        //get match id
        cJSON *match_id = cJSON_GetObjectItem( curr_m, "id" );
        if( cJSON_IsNumber( match_id ) ){ m_struct->match_ID = match_id->valueint; }
        //get match time
        cJSON *match_time = cJSON_GetObjectItem( curr_m, "time" );
        if( cJSON_IsString( match_time )){
            //TODO free after usage
            m_struct->match_time = malloc( strlen( match_time->valuestring ) + 1 );
            strcpy( m_struct->match_time, match_time->valuestring );
        } 
        //get match stage
        cJSON *match_stage = cJSON_GetObjectItem( curr_m, "tournamentStage" );
        if( cJSON_IsString( match_stage )){
            //TODO free after usage
            m_struct->match_stage = malloc( strlen( match_stage->valuestring ) + 1 );
            strcpy( m_struct->match_stage, match_stage->valuestring );
        } 
        //get match status
        parse_status( curr_m, m_struct );
        //get team home
        parse_team( curr_m, m_struct, "home" );
        //get team away
        parse_team( curr_m, m_struct, "away" );
        
    }
    lm->td_matches = m_list;

}
void parse_status( cJSON *obj, struct match *match ){

    cJSON *match_status = cJSON_GetObjectItem( obj, "status" );

    //TODO free after usage
    struct status *st = calloc( 1, sizeof( struct status ));
        
    cJSON *started_s = cJSON_GetObjectItem( match_status, "started" );
    if( cJSON_IsBool( started_s )){ st->started = cJSON_IsTrue( started_s ) ? true : false;
    }

    cJSON *cancelled_s= cJSON_GetObjectItem( match_status, "cancelled" );
    if( cJSON_IsBool( cancelled_s )){ st->cancelled = cJSON_IsTrue( cancelled_s ) ? true : false;
    }

    cJSON *finished_s = cJSON_GetObjectItem( match_status, "finished" );
    if( cJSON_IsBool( finished_s )){ st->finished = cJSON_IsTrue( finished_s ) ? true : false;
    }

    match->m_status = st;

}
void parse_team( cJSON *obj, struct match *match, const char *team ){

    cJSON *json_team = cJSON_GetObjectItem( obj, team );

    //TODO free after usage
    struct team *team_s = calloc( 1, sizeof( struct team ));
    
    cJSON *team_id = cJSON_GetObjectItem( json_team, "id" );
    if( cJSON_IsNumber( team_id )){ team_s->team_ID = team_id->valueint; }

    cJSON *team_score = cJSON_GetObjectItem( json_team, "score" );
    if( cJSON_IsNumber( team_score )){ team_s->team_score = team_score->valueint; 
    }

    cJSON *team_name = cJSON_GetObjectItem( json_team, "name" );
    if( cJSON_IsString( team_name )){ 
        //TODO free after usage
        team_s->team_name = malloc( strlen( team_name->valuestring) + 1);
        strcpy( team_s->team_name, team_name->valuestring );
    }

    if( strcmp( "home", team )){ match->home = team_s; }
    else { match->away = team_s; }
}
