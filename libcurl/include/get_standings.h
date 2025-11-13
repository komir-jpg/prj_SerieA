#ifndef GET_STANDINGS_H
#define GET_STANDINGS_H

#include"../include/api_libcurl.h"
#include<cjson/cJSON.h>
#include<stdbool.h>

#define MAX_TEAMS 20

struct team_s{

    unsigned int team_ID;
    unsigned int pos;
    unsigned int played;
    unsigned int wins;
    unsigned int draws;
    unsigned int losses;
    unsigned int goal_diff;
    unsigned int pts;
    char *team_name;
};

struct standings{

    unsigned int league_ID;
    struct team_s *team_list;
};

bool parse_standings( cJSON *obj, struct standings **s );

#endif
