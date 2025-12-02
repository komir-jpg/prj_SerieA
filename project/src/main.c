#include "api_libcurl.h"
#include "api_queries.h"
#include "modules.h"
#include "parse_json.h"

int main() {

    int success;

    char *err_buffer;

    buffer data = {0};
    struct curl_slist *header_list = NULL;
    query_url *q = malloc(sizeof(query_url));
    int year;

    League *l = NULL;

    CURL *handle = init_curl_wrapper();

    // get headers
    // get query url
    league_query(q, &year);
    success = setup_CURL(handle, q, header_list, &data, &err_buffer);
    if (success < 0) {

        fprintf(stderr, "Unable to setup headers\n");
        free(err_buffer);
        free_buffer(&data);
        curl_slist_free_all(header_list);
        curl_easy_cleanup(handle);
        return -1;
    }

    perform_curl_query(handle, &data, err_buffer, q->url);
    l = parse_league(&data, (const int)(year));
    printf("league name: %s\n", l->l_name);
    printf("league id: %d\n", l->league_ID);
    printf("league year: %d\n", l->year);

    // ok_parse = parse_lm( response, "Serie A", &lm );
    // if( !ok_parse ){ return -1; }

    free((void *)err_buffer);

    free_buffer(&data);
    free(q);
    free_league(l);
    curl_slist_free_all(header_list);
    curl_easy_cleanup(handle);
    curl_global_cleanup();
}
