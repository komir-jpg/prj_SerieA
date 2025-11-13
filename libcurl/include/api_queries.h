#ifndef API_QUERIES_H
#define API_QUERIES_H

//TODO setting up the url with the headers can be 
//done in a struct


#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define API_KEY "x-rapidapi-key: %s"
#define API_HOST "x-rapidapi-host: v3.football.api-sports.io"

#define LEAGUE_ID "52df5453a0628c0a"
#define DATE_STR_SIZE 11
#define GET_LEAGUE "https://v3.football.api-sports.io/leagues?name=Serie A&code=IT&current=true"

typedef struct{
    char *api_key;
    char *api_host;
    char *url;
}query_url;


static void setup_headers(query_url *query);
static char *get_current_date();
static char *set_api_key();
static void standings_query_url(query_url *query);
static void matchday_query_url(query_url *query);
static void league_query_url(query_url *query);
void standings_query(query_url *query);
void matchday_query(query_url *query);
void league_query(query_url *query);

#endif

