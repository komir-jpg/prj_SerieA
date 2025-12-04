#ifndef TYPES_H
#define TYPES_H

#include <stdlib.h>

typedef struct {
    char *api_key;
    char *host_url;
    char *url;
} query_url;

typedef struct {
    char *response;
    size_t size;
} buffer;

typedef struct {
    unsigned int team_ID;
    char *t_name;
} Team;

typedef struct {
    Team *t; // reference to Team struct
    unsigned int pos;
    unsigned int pts;
    unsigned int played;
    unsigned int win;
    unsigned int draw;
    unsigned int loss;
    unsigned int g_scored;
    unsigned int g_conceded;
    int g_diff;
    char *form;
} Team_standing;

typedef struct {
    uint num_teams;
    Team_standing *ts; // list of all teams with all info for the standings
} Standings;

typedef struct {
    unsigned int league_ID;
    unsigned int year;
    char *l_name;
} League;

#endif
