#include "../include/get_standings.h"

bool parse_standings( cJSON *obj, struct standings **s ){

    if( !obj ){ return false; }
    cJSON *team_s = cJSON_GetObjectItem( obj, "standing" );
    cJSON *curr_ts;

    *s = calloc( 1, sizeof( struct standings ));

    struct team_s *tsl = calloc( MAX_TEAMS, sizeof( struct team_s ));
    if( !tsl ){ fprintf(stderr, ANSI_COLOR_RED "error malloc team_standings" ANSI_COLOR_RESET); return false; }

    unsigned int index = 0;
    cJSON_ArrayForEach( curr_ts, team_s ){

        struct team_s *ts = &tsl[ index++ ];

        
        cJSON *team_ID = cJSON_GetObjectItem( curr_ts, "id" );
        if( cJSON_IsNumber( team_ID )){ ts->team_ID = team_ID->valueint; }
        
        cJSON *pos = cJSON_GetObjectItem( curr_ts, "idx" );
        if( cJSON_IsNumber( pos )){ ts->pos = pos->valueint; }
        
        cJSON *played = cJSON_GetObjectItem( curr_ts, "played" );
        if( cJSON_IsNumber( played )){ ts->played = played->valueint; }

        cJSON *wins = cJSON_GetObjectItem( curr_ts, "wins" );
        if( cJSON_IsNumber( wins )){ ts->wins = wins->valueint; }

        cJSON *draws = cJSON_GetObjectItem( curr_ts, "id" );
        if( cJSON_IsNumber( draws )){ ts->draws = draws->valueint; }

        cJSON *losses = cJSON_GetObjectItem( curr_ts, "losses" );
        if( cJSON_IsNumber( losses )){ ts->losses = losses->valueint; }

        cJSON *goal_diff = cJSON_GetObjectItem( curr_ts, "GoalConDiff" );
        if( cJSON_IsNumber( goal_diff )){ ts->goal_diff = goal_diff->valueint; }

        cJSON *pts = cJSON_GetObjectItem( curr_ts, "pts" );
        if( cJSON_IsNumber( pts )){ ts->pts = pts->valueint; }

        cJSON *team_name = cJSON_GetObjectItem( curr_ts, "name" );
        if( cJSON_IsString( team_name )){ 
            
            ts->team_name = malloc( strlen( team_name->valuestring ) + 1 );
            strcpy( ts->team_name, team_name->valuestring );
        }
    }
    (*s)->team_list = tsl;

}
