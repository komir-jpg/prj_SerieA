#include "modules.h"

void clean_buffer(buffer *buff) {
    if (!buff) {
        return;
    }
    if (buff->response) {
        free(buff->response);
        buff->response = NULL;
    }
    buff->size = 0;
}

void free_buffer(buffer *buff) {
    if (!buff) {
        return;
    }
    clean_buffer(buff);
}

void free_league(League *l) {
    if (!l) {
        return;
    }
    if (l->l_name) {
        free(l->l_name);
        l->l_name = NULL;
    }
    free(l);
}

void free_standings(Standings *s) {
    if (!s) {
        return;
    }
    if (s->ts) {
        for (size_t i = 0; i < s->num_teams; ++i) {
            free_team_standing(&s->ts[i]);
        }
        free(s->ts);
        s->ts = NULL;
    }
    free(s);
}

void free_team_standing(Team_standing *ts) {
    if (!ts) {
        return;
    }
    if (ts->form) {
        free(ts->form);
        ts->form = NULL;
    }
    if (ts->t) {
        free_team(ts->t);
        ts->t = NULL;
    }
}

void free_team(Team *t) {
    if (!t) {
        return;
    }
    if (t->t_name) {
        free(t->t_name);
        t->t_name = NULL;
    }
    free(t);
}
