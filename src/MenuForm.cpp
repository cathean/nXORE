#include "include/MenuForm.h"

MenuForm::MenuForm(std::vector<std::string> names, std::vector<std::string> desc, int arrsize)
{
    boxv = 0;
    boxh = 0;
    item_size = arrsize;

    for(int i = 0; i < arrsize; i++)
    {
        optnames.push_back(names[i]);
        optdesc.push_back(desc[i]);
    }

    optnames.push_back(std::string());
    optdesc.push_back(std::string());
}

MenuForm::~MenuForm()
{
    unpost_menu(menu);
    free_menu(menu);

    for(int i = 0; i < item_size + 1; i++)
        free_item(item[i]);

    delete [] item;

    delwin(loc_win);
}

int MenuForm::set_color(int window_background, int menu_color)
{
    winbk = window_background;
    menbk = menu_color;
}

int MenuForm::set_win_pos(int lines, int cols, int starty, int startx)
{
    wl = lines;
    wc = cols;
    wy = starty;
    wx = startx;
}

int MenuForm::set_menu_pos(int lines, int cols, int starty, int startx)
{
    ml = lines;
    mc = cols;
    my = starty;
    mx = startx;
}

int MenuForm::set_box_style(int v, int h)
{
    boxv = v;
    boxh = h;
}

int MenuForm::init()
{
    item = new ITEM *[item_size + 1];

    for(int i = 0; i < item_size + 1; i++)
        item[i] = new_item(optnames[i].c_str(), optdesc[i].c_str());

    menu = new_menu(item);
    loc_win = newwin(wl, wc, wy, wx);

    keypad(loc_win, TRUE);
    set_menu_win(menu, loc_win);
    set_menu_sub(menu, derwin(loc_win, ml, mc, my, mx));
    set_menu_mark(menu, ">");
    set_menu_back(menu, COLOR_PAIR(menbk));
    wbkgd(loc_win, COLOR_PAIR(winbk));

    box(loc_win, boxv, boxh);
    refresh();
}

void MenuForm::post()
{
    post_menu(menu);
    refresh();
    wrefresh(loc_win);
}

void MenuForm::unpost()
{
    unpost_menu(menu);
    refresh();
    wrefresh(loc_win);
}
