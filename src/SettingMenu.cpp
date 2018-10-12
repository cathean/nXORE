#include "include/SettingMenu.h"
#include "include/TextForm.h"

SettingMenu::SettingMenu()
{
    ReadSetting();
}

SettingMenu::~SettingMenu()
{
    WriteSetting();
}

int SettingMenu::ReadSetting()
{
    std::ifstream ifs("setting.txt");

    ifs >> pass;
    ifs.close();
}

int SettingMenu::WriteSetting()
{
    std::ofstream ofs("setting.txt");

    ofs << pass <<std::endl;
    ofs.close();
}

int SettingMenu::SetPass()
{
    TextForm s_pass;
    std::string txt = "SET PASSWORD";
    std::vector<char> key_char;
    int row_l = 6;
    int col_l = 30;

    s_pass.set_color(th_WHALE, th_SPIDER);
    s_pass.set_win_pos(row_l, col_l, (LINES - row_l) / 2, (COLS - col_l) / 2);
    s_pass.set_field_pos((LINES / 2) - 1, (COLS - 10) / 2);
    s_pass.init();
    s_pass.post_desc(txt.c_str(), (row_l / 2) - 2, (col_l - txt.length()) / 2);
    s_pass.post();

    while((s_pass.keypress = wgetch(s_pass.loc_win)) != KEY_F(1))
    {
        switch(s_pass.keypress)
        {
            case 10:
            {
                std::string s(key_char.begin(), key_char.end());
                pass = s;
                break;
            }
            default:
                form_driver(s_pass.form, s_pass.keypress);
                key_char.push_back(s_pass.keypress);
                break;
        }

        refresh();

        if (s_pass.keypress == 10)
            break;
    }

    refresh();
}

int SettingMenu::ResetSettings()
{
    pass = default_pass;
    std::ofstream ofs("setting.txt");
    ofs << pass;
    ofs.close();
}
