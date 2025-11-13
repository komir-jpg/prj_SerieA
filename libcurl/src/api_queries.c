#include "../include/api_queries.h"
#include <time.h>


//TODO key should not be visible
//TODO get matches by current date
//TODO get matches by given date
//TODO get given match stats lineup etc..
//TODO get current standings
//TODO get player stats

static char *get_current_date(){
    time_t now = time(NULL);
    struct tm *tm_info = localtime(&now);

    //free after the api call
    char *date = malloc(DATE_STR_SIZE*sizeof(char));
    strftime(date, DATE_STR_SIZE, "%Y%m%d", tm_info);

    return date;
}

static char* set_api_key(){
    const char *env_key = getenv("API_KEY");
    size_t str_len = snprintf(NULL, 0, API_KEY, env_key);
    
    char *api_header = malloc(str_len + 1);
    if(!api_header){fprintf(stderr, "malloc error\n"); return NULL;}

    snprintf(api_header, str_len + 1, API_KEY, env_key);

    return api_header;
}


static void setup_headers(query_url *query){
    size_t str_len = strlen(API_HOST);

    query->api_host = malloc(str_len + 1);
    if(!query->api_host){fprintf(stderr, "malloc error\n"); return;}

    snprintf(query->api_host, str_len + 1, API_HOST);

    query->api_key = set_api_key();
}

static void matchday_query_url(query_url *query){
    //here the usern gets no prompt the program figures itself current date
    char *date = get_current_date(); 
    //first we get the size of the string concatenation
    unsigned int size = snprintf(NULL, 0, CALL_FIX_CURR_DATE, date);

    query->url = malloc(size + 1);
    if(!query->url){fprintf(stderr, "malloc error\n"); return;}

    snprintf(query->url, size + 1,  CALL_FIX_CURR_DATE, date);
    free(date);
}

static void standings_query_url(query_url *query){
    unsigned int size = snprintf(NULL, 0, GET_LEAGUE_STANDINGS, LEAGUE_ID);
    query->url = malloc(size + 1);
    snprintf(query->url, size+1, GET_LEAGUE_STANDINGS, LEAGUE_ID);
}

static void league_query_url(query_url *query){
    query->url = malloc(strlen(GET_LEAGUE));
    strcpy(query->url, GET_LEAGUE);
}

void standings_query(query_url *query){
    setup_headers(query); 
    standings_query_url(query);
}

void matchday_query(query_url *query){
    setup_headers(query);
    matchday_query_url(query);
}

void league_query(query_url *query){
    setup_headers(query);
    league_query_url(query);
}
