#include "parse_json.h"

cJSON *json_root(char *response) {
    if (!response) {
        return NULL;
    }
    return cJSON_Parse(response);
}

cJSON *json_response(cJSON *root) {
    if (!root) {
        return NULL;
    }
    return cJSON_GetObjectItem(root, "data");
}
