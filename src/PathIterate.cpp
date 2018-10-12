#include "include/PathIterate.h"

PathIterate::PathIterate()
{
    count_data = 0;
}

PathIterate::~PathIterate()
{

}

int PathIterate::set_path(std::string p)
{
    loc_path = p;

    try
    {
        if(bfs::exists(p))
            return RET_NORM;
    }
    catch(const bfs::filesystem_error &ex)
    {
        printw("%s", ex.what());
    }
}

int PathIterate::iterate_dir()
{
    std::vector<bfs::path> v;

    try
    {
        if(bfs::is_regular_file(loc_path))
            return RET_NORM;
        else if(bfs::is_directory(loc_path))
        {
            for(auto&& x : bfs::directory_iterator(loc_path))
                v.push_back(x.path());

            v.push_back(".");
            v.push_back("..");
            std::sort(v.begin(), v.end());

            for(auto&& x : v)
            {
                vname.push_back(x.filename().string());

                if(bfs::is_regular_file(x))
                    vdesc.push_back("<FILE>");
                else if(bfs::is_directory(x))
                    vdesc.push_back("<DIR>");
                else
                    vdesc.push_back("<???>");

                count_data++;
            }
        }
    }
    catch(const bfs::filesystem_error &ex)
    {
        printw("%s", ex.what());
    }
}
