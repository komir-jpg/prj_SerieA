#include "parse_json.h"
League *parse_league(buffer *buff, const int curr_year) {
    if (!buff) {
        return NULL;
    }
    cJSON *root = json_root(buff->response);
    cJSON *response = json_response(root);
    cJSON *current_obj;

    League *l = malloc(sizeof(League));
    l->l_name = NULL;
    l->league_ID = 0;
    l->year = 0;

    cJSON_ArrayForEach(current_obj, response) {
        // check if league exists
        cJSON *id = cJSON_GetObjectItem(current_obj, "id");
        if (cJSON_IsNumber(id))
            l->league_ID = id->valueint;

        cJSON *name = cJSON_GetObjectItem(current_obj, "name");
        if (cJSON_IsString(name)) {
            l->l_name = strdup(name->valuestring);
        }
        cJSON *seasons = cJSON_GetObjectItem(current_obj, "seasons");
        cJSON *curr_s = NULL;
        cJSON_ArrayForEach(curr_s, seasons) {
            if (cJSON_IsObject(curr_s)) {
                cJSON *year = cJSON_GetObjectItem(curr_s, "season");
                if (cJSON_IsNumber(year) && year->valueint == curr_year) {
                    l->year = year->valueint;
                }
            }
        }
    }
    cJSON_Delete(root);
    return l;
}
