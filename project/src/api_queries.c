#include "api_queries.h"

// TODO key should not be visible
// TODO get matches by current date
// TODO get matches by given date
// TODO get given match stats lineup etc..
// TODO get current standings
// TODO get player stats

static char *get_current_date() {
    time_t now = time(NULL);
    struct tm *tm_info = localtime(&now);

    // free after the api call
    char *date = malloc(DATE_STR_SIZE * sizeof(char));
    strftime(date, DATE_STR_SIZE, "%Y%m%d", tm_info);

    return date;
}

static int get_current_year() {
    time_t now = time(NULL);
    struct tm *tm_info = localtime(&now);

    // free after the api call
    return tm_info->tm_year + 1900;
}

static char *set_api_key() {
    const char *env_key = getenv("API_KEY");
    size_t str_len = snprintf(NULL, 0, API_KEY, env_key);

    char *api_header = malloc(str_len + 1);
    if (!api_header) {
        fprintf(stderr, "malloc error\n");
        return NULL;
    }

    snprintf(api_header, str_len + 1, API_KEY, env_key);

    return api_header;
}
static char *set_host_url() { return strdup(API_HOST); }

void setup_headers(query_url *query) {
    query->api_key = set_api_key();
    query->host_url = set_host_url();
}

static void matchday_query_url(query_url *query) {}

static void standings_query_url(query_url *query, const int league_id) {
    int year = get_current_year();
    size_t size = snprintf(NULL, 0, GET_LEAGUE_STANDINGS, league_id, year);
    query->url = realloc(query->url, size + 1);
    snprintf(query->url, size + 1, GET_LEAGUE_STANDINGS, league_id, year);
}

static void league_query_url(query_url *query, int *curr_year) {
    int year = get_current_year();
    *curr_year = year;
    size_t size = snprintf(NULL, 0, GET_LEAGUE, year);
    query->url = realloc(query->url, size + 1);
    snprintf(query->url, size + 1, GET_LEAGUE, year);
}

void standings_query(query_url *query, const int league_id) {
    standings_query_url(query, league_id);
}

void matchday_query(query_url *query) { matchday_query_url(query); }

void league_query(query_url *query, int *curr_year) {
    league_query_url(query, curr_year);
}
