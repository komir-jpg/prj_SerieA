#ifndef GET_MATCHDAY_H
#define GET_MATCHDAY_H

#include"../include/api_libcurl.h"
#include<cjson/cJSON.h>
#include<stdbool.h>

struct team{
    
    unsigned int team_ID;
    unsigned int team_score;
    char *team_name;
};
struct status{

    bool started;
    bool cancelled;
    bool finished;
};
struct match{

    unsigned int match_ID;
    char *match_time;
    char *match_stage;
    struct status *m_status;
    struct team *home;
    struct team *away;

};
struct league_matches{

    unsigned int league_ID;
    char *league_name; //allocate when parsing
    struct match *td_matches;
    unsigned int num_matches;
};


void create_json_obj( struct memory *data, cJSON **root );
void get_response( cJSON *obj, cJSON **response );
bool parse_lm( cJSON *obj, const char *key, struct league_matches **lm ); 
static void parse_matches( cJSON *obj, struct league_matches *lm );

static void parse_status( cJSON *obj, struct match *match );
static void parse_team( cJSON *obj, struct match *match, const char *team );

#endif
