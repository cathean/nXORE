#include "include/TextForm.h"

TextForm::TextForm()
{

}

TextForm::~TextForm()
{
    //unpost_form(form);        //This thing causes SEGMENTATION FAULT
    free_form(form);
    free_field(field[0]);
    //free_field(field[1]);     //This one too

    delwin(loc_win);
}
int TextForm::set_color(int window_background, int form_color)
{
    winbk = window_background;
    forcol = form_color;
}

int TextForm::set_win_pos(int lines, int cols, int starty, int startx)
{
    wl = lines;
    wc = cols;
    wy = starty;
    wx = startx;
}

int TextForm::set_field_pos(int lines, int cols)
{
    fl = lines;
    fc = cols;
}

int TextForm::post_desc(const char *txt, int posy, int posx)
{
    mvwprintw(loc_win, posy, posx, "%s", txt);
}

int TextForm::init()
{
    field[0] = new_field(1, 10, fl, fc, 0, 0);
    field[1] = NULL;

    set_field_fore(field[0], COLOR_PAIR(forcol));
    set_field_back(field[0], COLOR_PAIR(forcol));
    field_opts_off(field[0], O_AUTOSKIP);

    form = new_form(field);

    loc_win = newwin(wl, wc, wy, wx);
    keypad(loc_win, TRUE);
    set_form_win(form, loc_win);

    wbkgd(loc_win, COLOR_PAIR(winbk));
    box(loc_win, '|', '#');
}

void TextForm::post()
{
    post_form(form);
    refresh();
    wrefresh(loc_win);
}

void TextForm::unpost()
{
    unpost_form(form);
    refresh();
    wrefresh(loc_win);
}
