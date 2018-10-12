#ifndef MENUFORM_H_INCLUDED
#define MENUFORM_H_INCLUDED

#include "headerpack.h"

class MenuForm
{
    protected:
        int winbk, menbk;
        int wl, wc, wy, wx;
        int ml, mc, my, mx;
        int item_size;
        int boxv, boxh;
    public:
        WINDOW *loc_win;
        MENU *menu;
        ITEM **item;
        std::vector<std::string> optnames;
        std::vector<std::string> optdesc;
        unsigned int keypress;

        MenuForm(std::vector<std::string> names, std::vector<std::string> desc, int arrsize);
        ~MenuForm();
        int set_color(int window_background, int menu_color);
        int set_win_pos(int lines, int cols, int starty, int startx);
        int set_menu_pos(int lines, int cols, int starty, int startx);
        int set_box_style(int v, int h);
        int init();
        void post();
        void unpost();
};


#endif // MENUFORM_H_INCLUDED
