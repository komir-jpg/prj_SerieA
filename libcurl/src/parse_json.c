#include "../include/parse_json.h"

static cJSON* json_root(char *response){
    if(!response){return NULL;}
    return cJSON_Parse(response);
}

static cJSON* json_response(cJSON *root){
    if(!root){return NULL;}
    return cJSON_GetObjectItem(root, "response");
}

League* parse_league(buffer *buff){
    if(!buff){return NULL;}
    cJSON *root = json_root(buff->response);
    cJSON *response = json_response(root);
    
    League *l = malloc(sizeof(League));

    cJSON *current_obj;
    cJSON_ArrayForEach(current_obj, response){
        cJSON *id = cJSON_GetObjectItem(current_obj, "id");
        if(cJSON_IsNumber(id)) l->league_ID = id->valueint;

        cJSON *name = cJSON_GetObjectItem(current_obj, "name");
        if(cJSON_IsString(name)){
            l->l_name = malloc(strlen(name->valuestring)+1);
            strcpy(l->l_name, name->valuestring);
        }

        cJSON *season = cJSON_GetObjectItem(current_obj, "season");
        cJSON_ArrayForEach(current_obj, season){}
    }


    


    

}
