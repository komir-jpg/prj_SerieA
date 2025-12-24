#include "api_calls.h"
#include "api_libcurl.h"
#include "api_queries.h"
#include "modules.h"
#include "parse_json.h"
#include <menu.h>
#include <ncurses.h>
#include <panel.h>
#include <stdlib.h>
#include <string.h>

#define ARR_SIZE(a) (sizeof(a) / sizeof(a[0]))

typedef void (*MenuAction)(void);

typedef struct {
    CURL *handle;
    struct curl_slist *header_list;
    buffer data;
    char *err_buffer;
    query_url *q;
    uint cached_league_id;
} AppSession;

static AppSession session = {0};

typedef struct {
    size_t height;
    size_t width;
} LogoDim;

typedef struct {
    char *label;
    MenuAction action;
} MenuItemDef;

void show_standings(void);
void show_matchday(void) {};
void show_team_stats(void) {};
void show_player_stats(void) {};
void exit_w(void) {};

MenuItemDef main_menu_config[] = {
    {"GET LEAGUE STANDINGS", show_standings},
    {"MATCHDAY", show_matchday},
    {"GET TEAM STATS", show_team_stats},
    {"GET PLAYER STATS", show_player_stats},
    {"EXIT", exit_w},
};

#define MENU_SIZE (sizeof(main_menu_config) / sizeof(MenuItemDef))

LogoDim get_logo_dim(const char *fn) {
    FILE *fp = fopen(fn, "r");
    LogoDim ld = {0, 0};

    if (!fp) {
        return ld;
    }

    char line[256];
    while (fgets(line, sizeof(line), fp)) {
        line[strcspn(line, "\r\n")] = 0;
        size_t width = strlen(line);
        if (width > ld.width)
            ld.width = width;
        ld.height++;
    }
    fclose(fp);
    return ld;
}

void print_ascii_from_file(WINDOW *win, const char *file_n, int start_y) {
    FILE *fp = fopen(file_n, "r");
    LogoDim logo_dim = get_logo_dim(file_n);
    if (!fp) {
        mvwprintw(win, start_y, 1, "Cannot open logo file");
        return;
    }
    char line[256];
    size_t win_w = getmaxx(win);
    size_t start_x = (win_w - logo_dim.width) / 2;
    if (start_x < 0)
        start_x = 0;

    size_t curr_row = 0;
    while (fgets(line, sizeof(line), fp)) {
        line[strcspn(line, "\r\n")] = 0;
        mvwprintw(win, start_y + curr_row, start_x, "%s", line);

        size_t len = strlen(line);
        for (size_t i = 0; i < len; i++) {
            if (line[i] == ' ')
                continue;

            size_t abs_x = start_x + i;
            size_t abs_y = start_y + curr_row;

            size_t dg_val = (i + curr_row) / 2;

            int color_id = 0;
            int r = dg_val % 3; // numbers of total colros in the title
            if (r == 0)
                color_id = 1; // Green
            else if (r == 1)
                color_id = 2; // White
            else
                color_id = 3; // Red

            mvwchgat(win, abs_y, abs_x, 1, A_BOLD, color_id, NULL);
        }
        curr_row++;
    }
    fclose(fp);
}

WINDOW *create_window(size_t h, size_t w, size_t st_x, size_t st_y) {
    WINDOW *local_w;
    local_w = newwin(h, w, st_x, st_y);

    // wrefresh(local_w); // needed with panel?

    return local_w;
}

WINDOW *win_menu(WINDOW *win_m, size_t w, size_t h) {
    /*
     * this function takes a window and creates a new centered window
     * based on the dimensions given
     * */
    size_t width_mw = 0, height_mw = 0;
    size_t width_cw = w, height_cw = h;

    getmaxyx(win_m, height_mw, width_mw);

    size_t start_y = (height_mw - height_cw) / 2;
    size_t start_x = (width_mw - width_cw) / 2;

    // check if childern coord are bigger then mother coord
    if ((start_y < 0))
        start_y = 0;
    if ((start_x < 0))
        start_x = 0;

    return derwin(win_m, h, w, start_y, start_x);
}

void menu_control(WINDOW *menu_w, MENU *menu) {
    keypad(menu_w, TRUE);
    int c = 0;
    post_menu(menu);
    while ((c = wgetch(menu_w)) != KEY_F(1)) {
        switch (c) {
        case KEY_DOWN:
            menu_driver(menu, REQ_DOWN_ITEM);
            break;
        case KEY_UP:
            menu_driver(menu, REQ_UP_ITEM);
            break;
        case 10:
            // add enter feature
            ITEM *curr = current_item(menu);
            MenuAction action = (MenuAction)item_userptr(curr);
            if (action)
                action();
            touchwin(stdscr);
            refresh();
            pos_menu_cursor(menu);
            break;
        }
        update_panels();
        doupdate();
    }
}
void create_menu(WINDOW *menu_w) {
    ITEM **items;
    MENU *menu;

    size_t vec_size = MENU_SIZE;

    items = (ITEM **)calloc(vec_size, sizeof(ITEM *));
    for (int i = 0; i < vec_size; i++) {
        items[i] = new_item(main_menu_config[i].label, " ");
        set_item_userptr(items[i], (void *)main_menu_config[i].action);
    }
    items[vec_size] = NULL;

    menu = new_menu((ITEM **)items);
    set_menu_win(menu, menu_w);
    set_menu_sub(menu, derwin(menu_w, vec_size, 30, 1, 1));
    set_menu_mark(menu, "->");

    menu_control(menu_w, menu);
    unpost_menu(menu);
    free_menu(menu); // this may cause problems if we go back to menu panel

    for (int i = 0; i < vec_size; i++) {
        free_item(items[i]);
    }
    free(items);
}
void main_w() {
    size_t h_main = 0, w_main = 0, h_title = 10, h_menu = 0;

    getmaxyx(stdscr, h_main, w_main);

    WINDOW *main_w = create_window(h_main, w_main, 0, 0);
    PANEL *main_w_p = new_panel(main_w);

    WINDOW *title_w = derwin(main_w, h_title, w_main, 0, 0);
    print_ascii_from_file(title_w, "logo.txt", 0);

    h_menu = h_main - h_title;

    WINDOW *menu_w = derwin(main_w, h_menu, w_main, h_title, 0);
    WINDOW *menu = win_menu(menu_w, 35, 20);

    box(menu, 0, 0);

    update_panels();
    doupdate();

    create_menu(menu);
}

void print_standings(WINDOW *w, Standings *s) {
    int y_start = 2;
    wattron(w, A_BOLD | A_REVERSE);
    mvwprintw(w, 1, 1, "%-3s %-20s %5s %5s %5s %5s %5s %5s %5s %5s", "Pos",
              "Team", "PG", "V", "N", "D", "GD", "GC", "GD", "PTS");
    wattroff(w, A_BOLD | A_REVERSE);

    for (uint i = 0; i < s->num_teams; i++) {
        mvwprintw(w, y_start + i, 1,
                  "%-3d %-20.19s %5d %5d %5d %5d %5d %5d %5d", s->ts[i].pos,
                  s->ts[i].t->t_name, s->ts[i].played, s->ts[i].win,
                  s->ts[i].draw, s->ts[i].loss, s->ts[i].g_scored,
                  s->ts[i].g_conceded, s->ts[i].g_diff);
    }
}

void init_app() {
    session.handle = setup(&session.header_list, &session.data,
                           &session.err_buffer, &session.q);
    if (!session.handle) {
        endwin();
        fprintf(stderr, "Error while setting session CURL handle\n");
        exit(1);
    }
    League *l = perform_league_query(session.handle, &session.data,
                                     session.err_buffer, session.q);
    if (l) {
        session.cached_league_id = l->league_ID;
        free_league(l);
    } else {
        session.cached_league_id = 0;
    }
}
void close_app() {
    mem_clean(session.handle, session.header_list, &session.data,
              session.err_buffer, session.q, NULL, NULL);
}
void show_standings() {
    /*
     *  this function creates the new window
     *  show info on screen
     *  performs the switch between panels(can be dealt by another function)
     *  the query is already done before creating the window
     *  we pass to this function only the info
     * */
    if (session.cached_league_id == 0)
        return;

    Standings *s = perform_get_standings_query(session.handle, &session.data,
                                               session.err_buffer, session.q,
                                               session.cached_league_id);
    size_t h_wstandings = 0, w_wstandings = 0;

    getmaxyx(stdscr, h_wstandings, w_wstandings);

    WINDOW *standings_w = create_window(h_wstandings, w_wstandings, 0, 0);
    PANEL *standings_w_p = new_panel(standings_w);

    print_standings(standings_w, s);

    update_panels();
    doupdate();

    free_standings(s);
}

int main() {
    init_app();
    initscr();
    start_color();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);

    init_pair(1, COLOR_GREEN, COLOR_BLACK);
    init_pair(2, COLOR_WHITE, COLOR_BLACK);
    init_pair(3, COLOR_RED, COLOR_BLACK);

    main_w();
    endwin();
    close_app();
}
