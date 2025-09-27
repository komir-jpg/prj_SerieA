#ifndef GET_MATCHDAY_H
#define GET_MATCHDAY_H

#include"../include/api_libcurl.h"
#include<cjson/cJSON.h>
#include<stdbool.h>

struct team{
    
    unsigned int team_ID;
    char *team_name;
    char *team_score;
};
struct status{

    bool started;
    bool cancelled;
    bool finished;
};
struct match{

    unsigned int match_ID;
    char *match_time;
    struct status m_status;
    struct team *home;
    struct team *away;

};
struct league_matches{

    unsigned int league_ID;
    char *league_name; //allocate when parsing
    char *match_stage;
    struct match *td_matches;
};


cJSON* create_json_obj( struct memory *data );
struct league_matches *lm( cJSON *obj, const char *key ); 
#endif
