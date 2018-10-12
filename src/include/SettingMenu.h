#ifndef SETTINGMENU_H_INCLUDED
#define SETTINGMENU_H_INCLUDED

#include "headerpack.h"

class SettingMenu
{
    protected:
    private:
        std::string default_pass = "root";
        std::string pass;

        int ReadSetting();
        int WriteSetting();
    public:
        SettingMenu();
        ~SettingMenu();
        int SetPass();
        int ResetSettings();
};

#endif // SETTINGMENU_H_INCLUDED
