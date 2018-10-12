#ifndef PATHITERATE_H_INCLUDED
#define PATHITERATE_H_INCLUDED

#include "headerpack.h"

class PathIterate
{
    protected:
        bfs::path loc_path;
    public:
        std::vector<std::string> vname;
        std::vector<std::string> vdesc;
        unsigned int count_data;

        PathIterate();
        ~PathIterate();
        int set_path(std::string p);
        int iterate_dir();
    private:

};






#endif // PATHITERATE_H_INCLUDED
