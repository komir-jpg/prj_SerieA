#ifndef INPUT_H
#define INPUT_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define API_KEY "x-rapidapi-key: %s"
#define API_HOST "x-rapidapi-host: v3.football.api-sports.io"

#define LEAGUE_ID 135

#define DATE_STR_SIZE 11
#define CALL_FIX_CURR_DATE "https://v3.football.api-sports.io/fixtures?date=%s&league=%d"


void parse_input( char **url, char **api_key, char **host );
void get_current_date( char **date );
char* set_api_key();

#endif

