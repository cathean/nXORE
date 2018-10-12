#include "include/headerpack.h"
#include "include/PassTextForm.h"
#include "include/MenuForm.h"
#include "include/PathIterate.h"
#include "include/Encryptor.h"
#include "include/SettingMenu.h"
#include "include/main_func.h"

#define ARRAY_SIZE(a) (sizeof(a)/sizeof(a[0]))

void loginForm();
int mainForm();
int pathForm(std::string pname);
int encryptingForm();
int setKeyForm();
int settingForm();
int infoForm(std::vector<std::string> names, std::vector<std::string> desc);
int encryptResultForm(std::vector<std::string> Input, std::vector<std::string> Output);

//Private function
int getDataSize();

Encryptor enc;
std::vector<std::string> choosen;
std::vector<std::string> DataSize;
std::vector<std::string> DataResult;
std::string choosenpath = "/";

std::vector<std::string> infoFlag_desc = {
                                "Current path = ",
                                "Select files : ",
                                "Set key : ",
                                "Files selected = "
                                };

std::vector<std::string> infoFlag_value = {
                                "/",
                                "NO",
                                "NO (Default)",
                                "NONE"
                                };

int main()
{
    enc.set_key("admin");

    initscr();
    cbreak();
    noecho();
    start_color();

    init_pair(1, COLOR_WHITE, COLOR_BLUE);
    init_pair(2, COLOR_RED, COLOR_WHITE);

    loginForm();
    clear();

    int f_mainForm;

    do
    {
        infoForm(infoFlag_desc, infoFlag_value);
        f_mainForm = mainForm();
        clear();
    }while(f_mainForm == RET_NORM);
    clear();

    refresh();
    getch();
    endwin();
    return 0;
}

void loginForm()
{
    bfs::path p("setting.txt");
    std::string pass;

    if(!bfs::exists(p))
    {
        std::ofstream ofs("setting.txt");

        ofs << "root" <<std::endl;
        ofs.close();
    }

    std::ifstream ifs("setting.txt");
    ifs >> pass;
    ifs.close();


    PassTextForm login;
    std::string txt = "ENTER PASSWORD";

    login.set_color(th_WHALE, th_SPIDER);
    login.set_win_pos(LINES, COLS, 0, 0);
    login.set_field_pos((LINES / 2) - 1, (COLS - 10) / 2);
    login.init();
    login.post_desc(txt.c_str(), (LINES / 2) - 2, (COLS - txt.length()) / 2);
    login.post();


    while((login.keypress = wgetch(login.loc_win)) != KEY_F(1))
    {
        switch(login.keypress)
        {
            case 10:

                if(login.get_pass() == pass)
                    break;
                else
                    continue;
            default:
                form_driver(login.form, '*');
                login.pass.push_back(login.keypress);
                break;
        }

        refresh();

        if (login.keypress == 10)
            break;
    }

    refresh();
}

int mainForm()
{
    enum opttype {encrypt_data, select_data, set_key, sett_form, exit};
    opttype START_OPT = encrypt_data;
    opttype SELECT_FILES_OPT = select_data;
    opttype SET_KEY_OPT = set_key;
    opttype SETT_FORM = sett_form;
    opttype EXIT_OPT = exit;

    std::vector<std::string> mainname;
    mainname.insert(mainname.end(), {"ENCRYPT/DECRYPT", "SELECT FILES", "SET KEY", "SETTINGS", "EXIT"});
    std::vector<std::string> maindesc;
    maindesc.insert(maindesc.end(), {"<Start>", "<Set data from path>", "<Set 3 character key>", "<Go to settings", "<Exit program>"});

    MenuForm mainmenu(mainname, maindesc, mainname.size());
    mainmenu.set_color(th_WHALE, th_WHALE);
    mainmenu.set_win_pos(LINES / 2, COLS / 2, 0, 0);
    mainmenu.set_menu_pos((LINES / 2) - 1, (COLS / 2) - 1, 1, 1);

    mainmenu.init();
    set_menu_spacing(mainmenu.menu, 0, 2, 0);
    mainmenu.post();

    while((mainmenu.keypress = wgetch(mainmenu.loc_win)) != KEY_F(1))
    {
        switch(mainmenu.keypress)
        {
            case KEY_UP:
                menu_driver(mainmenu.menu, REQ_UP_ITEM);
                break;
            case KEY_DOWN:
                menu_driver(mainmenu.menu, REQ_DOWN_ITEM);
                break;
            case 10:
            {
                if(current_item(mainmenu.menu) == mainmenu.item[START_OPT])
                {
                    encryptingForm();
                    return RET_NORM;
                }
                else if(current_item(mainmenu.menu) == mainmenu.item[SELECT_FILES_OPT])
                {
                    pathForm("/");
                    return RET_NORM;
                }
                else if(current_item(mainmenu.menu) == mainmenu.item[SET_KEY_OPT])
                {
                    setKeyForm();
                    return RET_NORM;
                }
                else if(current_item(mainmenu.menu) == mainmenu.item[SETT_FORM])
                {
                    settingForm();
                    return RET_NORM;
                }
                else if(current_item(mainmenu.menu) == mainmenu.item[EXIT_OPT])
                    return RET_EX;
                    break;

                break;
            }
            default:
                break;
        }

        if(mainmenu.keypress == ' ')
            break;

        wrefresh(mainmenu.loc_win);
    }

    refresh();
}

int pathForm(std::string pname)
{
    PathIterate pExplorer;
    pExplorer.set_path(pname);
    pExplorer.iterate_dir();

    MenuForm pathmenu(pExplorer.vname, pExplorer.vdesc, pExplorer.count_data);
    pathmenu.set_color(th_WHALE, th_WHALE);
    pathmenu.set_win_pos(LINES, COLS / 2, 0, COLS / 2);
    pathmenu.set_menu_pos(LINES - 1, (COLS / 2) - 1, 1, 1);

    pathmenu.init();
    set_menu_format(pathmenu.menu, LINES - 2, 0);
    menu_opts_off(pathmenu.menu, O_ONEVALUE);
    pathmenu.post();

    infoFlag_value[currentPath] = choosenpath;
    infoForm(infoFlag_desc, infoFlag_value);

    while((pathmenu.keypress = wgetch(pathmenu.loc_win)) != KEY_F(1))
    {
        switch(pathmenu.keypress)
        {
            case KEY_UP:
                menu_driver(pathmenu.menu, REQ_UP_ITEM);
                break;
            case KEY_DOWN:
                menu_driver(pathmenu.menu, REQ_DOWN_ITEM);
                break;
            case KEY_RIGHT:
                menu_driver(pathmenu.menu, REQ_TOGGLE_ITEM);
                break;
            case 10:
            {
                std::string dirname = item_name(current_item(pathmenu.menu));
                std::string temp_path = pname + dirname + "/";

                if(bfs::is_directory(temp_path))
                {
                    choosenpath = bfs::path(temp_path).lexically_normal().string();
                    choosenpath.pop_back();
                    pathForm(temp_path);
                }
                else
                    break;
            }

            case ' ':
            {

                for(int i = 0; i < item_count(pathmenu.menu); i++)
                {
                    if(item_value(pathmenu.item[i]) == TRUE)
                    {
                        choosen.push_back(item_name(pathmenu.item[i]));
                    }
                }

                if(choosen.size())
                {
                    infoFlag_value[filesFlag] = "YES";
                    infoFlag_value[filesCount] = std::to_string(choosen.size());
                }

                return RET_NORM;
            }
            default:
                break;
        }

        wrefresh(pathmenu.loc_win);
    }

    refresh();
}

int encryptingForm()
{
    if(infoFlag_value[keyFlag] != "YES" || infoFlag_value[filesCount] == "NONE")
        return RET_ERR;

    Encryptor filenameEnc;
    std::string inputFile, outputFile;
    std::vector<std::string> InputVec, OutputVec;
    bfs::path p;

    filenameEnc.set_key("root");

    for(int i = 0; i < choosen.size(); i++)
    {
        p = choosen[i];

        if(p.extension() == ".enc")
        {
            inputFile = choosenpath + choosen[i];
            outputFile = choosenpath + filenameEnc.str_encrypt(p.stem().string());


            p = inputFile; InputVec.push_back(p.filename().string());
            p = outputFile; OutputVec.push_back(p.filename().string());
            DataResult.push_back("|DECRYPTED");
        }
        else
        {
            inputFile = choosenpath + choosen[i];
            outputFile = choosenpath + filenameEnc.str_encrypt(choosen[i]) + ".enc";

            p = inputFile; InputVec.push_back(p.filename().string());
            p = outputFile; OutputVec.push_back(p.filename().string());
            DataResult.push_back("|ENCRYPTED");
        }

        enc.file_encrypt(inputFile, outputFile);
    }

    encryptResultForm(InputVec, OutputVec);

    return RET_NORM;
}

int setKeyForm()
{
    TextForm s_key;
    std::string txt = "SET KEY";
    std::vector<char> key_char;
    int row_l = 6;
    int col_l = 30;

    s_key.set_color(th_WHALE, th_SPIDER);
    s_key.set_win_pos(row_l, col_l, (LINES - row_l) / 2, (COLS - col_l) / 2);
    s_key.set_field_pos((LINES / 2) - 1, (COLS - 10) / 2);
    s_key.init();
    s_key.post_desc(txt.c_str(), (row_l / 2) - 2, (col_l - txt.length()) / 2);
    s_key.post();

    while((s_key.keypress = wgetch(s_key.loc_win)) != KEY_F(1))
    {
        switch(s_key.keypress)
        {
            case 10:
            {
                std::string s(key_char.begin(), key_char.end());

                enc.set_key(s);
                infoFlag_value[keyFlag] = "YES";
                break;
            }
            default:
                form_driver(s_key.form, s_key.keypress);
                key_char.push_back(s_key.keypress);
                break;
        }

        refresh();

        if (s_key.keypress == 10)
            break;
    }

    refresh();
}

int settingForm()
{
    SettingMenu sett;

    enum opttype {set_pass, reset_setting, exit};
    opttype SETPASS_OPT = set_pass;
    opttype RES_SETT = reset_setting;
    opttype EXIT_OPT = exit;

    std::vector<std::string> mainname;
    mainname.insert(mainname.end(), {"SET PASSWORD", "RESET SETTING", "EXIT"});
    std::vector<std::string> maindesc;
    maindesc.insert(maindesc.end(), {"<Default: root>", "<Reset to default>", "<Exit program>"});

    MenuForm settmenu(mainname, maindesc, mainname.size());
    settmenu.set_color(th_WHALE, th_WHALE);
    settmenu.set_win_pos(LINES / 2, COLS / 2, 0, 0);
    settmenu.set_menu_pos((LINES / 2) - 1, (COLS / 2) - 1, 1, 1);

    settmenu.init();
    set_menu_spacing(settmenu.menu, 0, 3, 0);
    settmenu.post();

    while((settmenu.keypress = wgetch(settmenu.loc_win)) != KEY_F(1))
    {
        switch(settmenu.keypress)
        {
            case KEY_UP:
                menu_driver(settmenu.menu, REQ_UP_ITEM);
                break;
            case KEY_DOWN:
                menu_driver(settmenu.menu, REQ_DOWN_ITEM);
                break;
            case 10:
            {
                if(current_item(settmenu.menu) == settmenu.item[SETPASS_OPT])
                {
                    sett.SetPass();
                    return RET_NORM;
                }
                else if(current_item(settmenu.menu) == settmenu.item[RES_SETT])
                {
                    sett.ResetSettings();
                    return RET_NORM;
                }
                else if(current_item(settmenu.menu) == settmenu.item[EXIT_OPT])
                    return RET_EX;
                    break;

                break;
            }
            default:
                break;
        }

        wrefresh(settmenu.loc_win);
    }

    refresh();
}

int infoForm(std::vector<std::string> names, std::vector<std::string> desc)
{
    getDataSize();

    MenuForm info(names, desc, names.size());
    info.set_color(NULL, NULL);
    info.set_win_pos(LINES / 2, COLS / 2, LINES / 2, 0);
    info.set_menu_pos((LINES / 2) - 1, (COLS / 2) - 1, 1, 1);

    info.init();
    set_menu_mark(info.menu, NULL);
    set_menu_fore(info.menu, A_NORMAL);
    info.post();

    wrefresh(info.loc_win);
    refresh();
}


int encryptResultForm(std::vector<std::string> Input, std::vector<std::string> Output)
{
    std::vector<std::string> DataList;

    for(int i = 0; i < choosen.size(); i++)
    {
        std::string temp = Input[i] + "~>" + Output[i];
        DataList.push_back(temp);
    }

    MenuForm encRes(DataList, DataResult, DataList.size());

    encRes.set_color(th_WHALE, th_WHALE);
    encRes.set_win_pos(LINES - 8, COLS / 2, 4, COLS / 4);
    encRes.set_menu_pos(LINES - 10, (COLS / 2) - 1, 2, 1);
    encRes.set_box_style('|', '+');

    encRes.init();
    set_menu_format(encRes.menu, LINES - 2, 0);
    menu_opts_off(encRes.menu, O_ONEVALUE);

    std::string location = "PATH = " + choosenpath;
    mvwprintw(encRes.loc_win, 1, 1, location.c_str());

    encRes.post();

    while((encRes.keypress = wgetch(encRes.loc_win)) != KEY_F(1))
    {
        switch(encRes.keypress)
        {
            case KEY_UP:
                menu_driver(encRes.menu, REQ_UP_ITEM);
                break;
            case KEY_DOWN:
                menu_driver(encRes.menu, REQ_DOWN_ITEM);
                break;
            case 10:
                return RET_NORM;
            default:
                break;
        }

        wrefresh(encRes.loc_win);
    }

    refresh();
}


//Private Function==========
int getDataSize()
{
    bfs::path p;

    for(int i = 0; i < choosen.size(); i++)
    {
        p = choosenpath + choosen[i];
        DataSize.push_back(std::to_string(p.size()));
    }

    return RET_NORM;
}
