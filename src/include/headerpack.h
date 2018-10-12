#ifndef HEADERPACK_H_INCLUDED
#define HEADERPACK_H_INCLUDED

#include <iostream>
#include <ncurses.h>
#include <form.h>
#include <menu.h>
#include <boost/filesystem.hpp>
#include <vector>
#include <string>
#include <fstream>
#include <streambuf>
namespace bfs = boost::filesystem;

enum returntype {RET_ERR = -1, RET_NORM, RET_EX};
enum themetype {th_WHALE = 1, th_SPIDER};
enum infoFlag {currentPath, filesFlag, keyFlag, filesCount};


#endif // HEADERPACK_H_INCLUDED
