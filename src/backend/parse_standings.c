#include "parse_json.h"
static Standings *mem_standing(const uint num_teams) {
    // free after usage
    Standings *s = malloc(sizeof(Standings));
    s->num_teams = num_teams;
    s->ts = calloc(num_teams, sizeof(Team_standing)); // list might be better
    return s;
}
static Team *mem_team(const uint team_ID, char *t_name) {
    // free after usage
    Team *t = malloc(sizeof(Team));
    t->team_ID = team_ID;
    t->t_name = strdup(t_name);
    return t;
}
Standings *parse_standings(buffer *buff) {
    if (!buff) {
        return NULL;
    }
    cJSON *root = json_root(buff->response);
    cJSON *groups = cJSON_GetObjectItem(root, "groups");
    // TODO check if groups is a valid array
    cJSON *group = cJSON_GetArrayItem(groups, 0);
    cJSON *standings = cJSON_GetObjectItem(group, "standings");
    // TODO check if standing is a valid array
    const uint team_num = cJSON_GetArraySize(standings);

    // create the structure
    Standings *s = mem_standing(team_num);

    // Parse standings
    size_t index = 0;
    cJSON *current_obj = NULL;
    cJSON_ArrayForEach(current_obj, standings) {
        cJSON *pos = cJSON_GetObjectItem(current_obj, "position");
        cJSON *pts = cJSON_GetObjectItem(current_obj, "points");
        cJSON *team = cJSON_GetObjectItem(current_obj, "team");
        cJSON *total = cJSON_GetObjectItem(current_obj, "total");

        cJSON *team_ID = cJSON_GetObjectItem(team, "id");
        cJSON *t_name = cJSON_GetObjectItem(team, "name");

        cJSON *played = cJSON_GetObjectItem(total, "games");
        cJSON *win = cJSON_GetObjectItem(total, "wins");
        cJSON *draw = cJSON_GetObjectItem(total, "draws");
        cJSON *loss = cJSON_GetObjectItem(total, "loses");
        cJSON *g_scored = cJSON_GetObjectItem(total, "scoredGoals");
        cJSON *g_conceded = cJSON_GetObjectItem(total, "receivedGoals");

        Team *t = mem_team(team_ID->valueint, t_name->valuestring);

        s->ts[index].t = t;
        if (cJSON_IsNumber(pos)) {
            s->ts[index].pos = pos->valueint;
        }
        if (cJSON_IsNumber(pts)) {
            s->ts[index].pts = pts->valueint;
        }
        if (cJSON_IsNumber(played)) {
            s->ts[index].played = played->valueint;
        }
        if (cJSON_IsNumber(win)) {
            s->ts[index].win = win->valueint;
        }
        if (cJSON_IsNumber(draw)) {
            s->ts[index].draw = draw->valueint;
        }
        if (cJSON_IsNumber(loss)) {
            s->ts[index].loss = loss->valueint;
        }
        if (cJSON_IsNumber(g_scored)) {
            s->ts[index].g_scored = g_scored->valueint;
        }
        if (cJSON_IsNumber(g_conceded)) {
            s->ts[index].g_conceded = g_conceded->valueint;
        }

        s->ts[index].g_diff =
            (int)s->ts[index].g_scored - (int)s->ts[index].g_conceded;
        s->ts[index].form = "";

        index++;
    }
    cJSON_Delete(root);
    return s;
}
