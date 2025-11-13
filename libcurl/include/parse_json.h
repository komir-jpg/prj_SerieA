#ifndef PARSE_JSON_H
#define PARSE_JSON_H

#include "modules.h"

static cJSON* json_root(char *response);
static cJSON* json_response(cJSON *root);
League *parse_league(buffer *data);
void parse_teams(Team *t);
void parse_standings(Standings *s);

#endif 
