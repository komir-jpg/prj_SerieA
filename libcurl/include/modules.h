#ifndef MODULES_H
#define MODULES_H

#include <stdlib.h>
#include <cjson/cJSON.h>
#include <string.h>

#define ANSI_COLOR_GREEN    "\x1b[32m"
#define ANSI_COLOR_RED      "\x1b[32m"
#define ANSI_COLOR_RESET    "\x1b[32m"

typedef struct{
    char *response;
    size_t size;
}buffer;

typedef struct{
    unsigned int team_ID;
    char *t_name;
}Team;

typedef struct{
     Team *t;
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
}Team_standing;

typedef struct{
    unsigned int num_teams;
    Team_standing *ts;
}Standings;

typedef struct{
    unsigned int league_ID;
    unsigned int year;
    char *l_name;
    Standings *standings;
}League;

void free_buffer(buffer *buf);
void free_league(League *l);
void free_standings(Standings *s);
void free_team_standing(Team_standing *ts);
void free_team(Team *t);

#endif
