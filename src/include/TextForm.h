#ifndef TEXTFORM_H_INCLUDED
#define TEXTFORM_H_INCLUDED

#include "headerpack.h"

class TextForm
{
    protected:
        int winbk, forcol;
        int wl, wc, wy, wx;
        int fl, fc;
    public:
        WINDOW *loc_win;
        FORM *form;
        FIELD *field[1];
        unsigned int keypress;

        TextForm();
        ~TextForm();
        int set_color(int window_background, int form_color);
        int set_win_pos(int lines, int cols, int starty, int startx);
        int set_field_pos(int lines, int cols);
        int post_desc(const char *txt, int posy, int posx);
        int init();
        void post();
        void unpost();
};

#endif // TEXTFORM_H_INCLUDED
