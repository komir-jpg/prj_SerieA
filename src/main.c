#include "api_calls.h"
#include "api_libcurl.h"
#include "api_queries.h"
#include "modules.h"
#include "parse_json.h"

int main() {

    char *err_buffer = NULL;

    buffer data = {0};

    struct curl_slist *header_list = NULL;

    query_url *q = NULL;

    League *l = NULL;
    Standings *s = NULL;

    CURL *handle = setup(&header_list, &data, &err_buffer, &q);
    l = perform_league_query(handle, &data, err_buffer, q);
    s = perform_get_standings_query(handle, &data, err_buffer, q, l->league_ID);
    mem_clean(handle, header_list, &data, err_buffer, q, l, s);
}
