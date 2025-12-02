#ifndef API_QUERIES_H
#define API_QUERIES_H

// TODO setting up the url with the headers can be
// done in a struct

#include "modules.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define API_KEY "x-rapidapi-key: %s"
#define API_HOST "x-rapidapi-host: football-highlights-api.p.rapidapi.com"

#define DATE_STR_SIZE 11
#define GET_LEAGUE                                                             \
    "https://football-highlights-api.p.rapidapi.com/"                          \
    "leagues?leagueName=Serie%%20A&offset=0&countryCode=IT&season=%d"
#define GET_LEAGUE_STANDINGS "foo"
#define CALL_FIX_CURR_DATE "foo"

static void setup_headers(query_url *query);
static char *get_current_date();
static int get_current_year();
static char *set_api_key();
static char *set_host_url();
static void standings_query_url(query_url *query, const int league_id);
static void matchday_query_url(query_url *query);
static void league_query_url(query_url *query, int *curr_year);
void standings_query(query_url *query, const int league_id);
void matchday_query(query_url *query);
void league_query(query_url *query, int *curr_year);

#endif
