#ifndef MODULES_H
#define MODULES_H

#include <cjson/cJSON.h>
#include <stdlib.h>
#include <string.h>

#define ANSI_COLOR_GREEN "\x1b[32m"
#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_RESET "\x1b[0m"

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
    unsigned int num_teams;
    Team_standing *ts; // list of all teams with all info for the standings
} Standings;

typedef struct {
    unsigned int league_ID;
    unsigned int year;
    char *l_name;
} League;

void free_buffer(buffer *buf);
void free_league(League *l);
void free_standings(Standings *s);
void free_team_standing(Team_standing *ts);
void free_team(Team *t);

#endif
