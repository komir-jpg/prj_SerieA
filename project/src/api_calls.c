#include "api_calls.h"
CURL *setup(struct curl_slist **header_list, buffer *data, char **err_buffer,
            query_url **q) {
  CURL *handle = init_curl_wrapper();

  if (*q) {
    free((*q)->url);
    free(*q);
  }
  *q = malloc(sizeof(query_url));
  (*q)->url = NULL;
  setup_headers(*q);

  if (!setup_CURL(handle, *q, header_list, data, err_buffer)) {
    fprintf(stderr, "Unable to setup headers\n");
    curl_slist_free_all(*header_list);
    curl_easy_cleanup(handle);
    return NULL;
  }
  return handle;
}

League *perform_league_query(CURL *handle, buffer *data, char *err_buffer,
                             query_url *q) {
  int year = 0;

  league_query(q, &year);
  free_buffer(data);
  perform_curl_query(handle, data, err_buffer, q->url);

  return parse_league(data, (const int)(year));
}

Standings *perform_get_standings_query(CURL *handle, buffer *data,
                                       char *err_buffer, query_url *q,
                                       const int league_ID) {
  standings_query(q, league_ID);
  free_buffer(data);
  perform_curl_query(handle, data, err_buffer, q->url);

  return parse_standings(data);
}
void mem_clean(CURL *handle, struct curl_slist *hl, buffer *data,
               char *err_buffer, query_url *q, League *l, Standings *s) {
  free_league(l);
  free_standings(s);
  free_buffer(data);
  free(err_buffer);
  curl_slist_free_all(hl);
  curl_easy_cleanup(handle);
  curl_global_cleanup();
  if (q) {
    free(q->url);
    free(q);
  }
}
