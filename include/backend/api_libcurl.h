#ifndef API_LIBCURL_H
#define API_LIBCURL_H

#include "modules.h"
#include "types.h"
#include <curl/curl.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// delete this now we have it in module.h

bool setup_CURL(CURL *handle, const query_url *q,
                struct curl_slist **header_slist, buffer *buff,
                char **error_buffer);
void error_buffer_init(char **error_buffer);
void perform_curl_query(CURL *handle, buffer *buff, char *error_buffer,
                        const char *url);
CURL *init_curl_wrapper();
short check_perform(CURLcode code, char *error_buffer);
#endif
