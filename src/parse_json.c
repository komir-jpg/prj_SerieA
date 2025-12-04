#include "parse_json.h"

cJSON *json_root(char *response) {
    if (!response) {
        return NULL;
    }
    return cJSON_Parse(response);
}
