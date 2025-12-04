#ifndef PARSE_JSON_H
#define PARSE_JSON_H

#include "types.h"
#include <cjson/cJSON.h>
#include <string.h>

cJSON *json_root(char *response);
League *parse_league(buffer *data, const int curr_year);
void parse_teams(Team *t);
Standings *parse_standings(buffer *data);

#endif
