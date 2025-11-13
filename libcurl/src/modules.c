#include "../include/modules.h"

void clean_buffer(buffer *buff){
    if(!buff){return;}
    buff->response ? free(buff->response) : NULL; 
    buff->size=0;
}

void free_buffer(buffer *buff){
    clean_buffer(buff);
    free(buff);
}

void free_league(League *l){
    if(!l){return;}
    l->l_name ? free(l->l_name) : NULL;
    free_standings(l->standings);
    free(l);
}

void free_standings(Standings *s){
    if(!s){return;}
    if(!s->ts){free(s); return;}
    size_t num_t = s->num_teams; 
    while(num_t--){free_team_standing(&s->ts[num_t]);}
    free(s);
}

void free_team_standing(Team_standing *ts){
    if(!ts){return;}
    ts->form ? free(ts->form) : NULL;
    if(!ts->t){free(ts); return;}
    free_team(ts->t);
    free(ts);
}

void free_team(Team *t){
    if(!t){return;}
    t->t_name ? free(t->t_name) : NULL;
    free(t);
}
