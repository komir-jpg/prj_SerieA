#ifndef INPUT_H
#define INPUT_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define API_KEY "x-rapidapi-key: %s"
#define API_HOST "x-rapidapi-host: sportapi7.p.rapidapi.com"

#define LEAGUE_ID 135

#define DATE_STR_SIZE 11
#define CALL_FIX_CURR_DATE "https://sportapi7.p.rapidapi.com/api/v1/sport/football/scheduled-events/%s/inverse"


void setup_api_headers( char **api_key_header, char **host_header );
char *get_current_date();
char* set_api_key();
void get_match_current_date_url( char **api_call_url );

#endif

