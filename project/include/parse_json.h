#ifndef PARSE_JSON_H
#define PARSE_JSON_H

#include "modules.h"

cJSON *json_root(char *response);
cJSON *json_response(cJSON *root);
League *parse_league(buffer *data, const int curr_year);
void parse_teams(Team *t);
Standings *parse_standings(buffer *data);

#endif
