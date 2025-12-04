#ifndef API_QUERIES_H
#define API_QUERIES_H

// TODO setting up the url with the headers can be
// done in a struct

#include "types.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define API_KEY "x-rapidapi-key: %s"
#define API_HOST "x-rapidapi-host: football-highlights-api.p.rapidapi.com"

#define DATE_STR_SIZE 11
#define GET_LEAGUE                                                             \
    "https://football-highlights-api.p.rapidapi.com/"                          \
    "leagues?leagueName=Serie%%20A&offset=0&countryCode=IT&season=%d"
#define GET_LEAGUE_STANDINGS                                                   \
    "https://football-highlights-api.p.rapidapi.com/"                          \
    "standings?leagueId=%d&season=%d"
#define CALL_FIX_CURR_DATE "foo"

void setup_headers(query_url *query);
void standings_query(query_url *query, const int league_id);
void matchday_query(query_url *query);
void league_query(query_url *query, int *curr_year);

#endif
