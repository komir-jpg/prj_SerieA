#ifndef MODULES_H
#define MODULES_H

#include "types.h"
#include <cjson/cJSON.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define ANSI_COLOR_GREEN "\x1b[32m"
#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_RESET "\x1b[0m"

void free_buffer(buffer *buf);
void free_league(League *l);
void free_standings(Standings *s);
void free_team_standing(Team_standing *ts);
void free_team(Team *t);

#endif
