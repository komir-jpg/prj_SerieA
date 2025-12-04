#ifndef API_CALLS_H
#define API_CALLS_H

#include "api_libcurl.h"
#include "api_queries.h"
#include "modules.h"
#include "parse_json.h"
#include "types.h"
#include <cjson/cJSON.h>
#include <curl/curl.h>
CURL *setup(struct curl_slist **header_list, buffer *data, char **err_buffer,
            query_url **q);
League *perform_league_query(CURL *handle, buffer *data, char *err_buffer,
                             query_url *q);
Standings *perform_get_standings_query(CURL *handle, buffer *data,
                                       char *err_buffer, query_url *q,
                                       const int league_ID);
void mem_clean(CURL *handle, struct curl_slist *hl, buffer *data,
               char *err_buffer, query_url *q, League *l, Standings *s);
#endif
