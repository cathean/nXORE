#ifndef PASSTEXTFORM_H_INCLUDED
#define PASSTEXTFORM_H_INCLUDED

#include "TextForm.h"

class PassTextForm : public TextForm
{
    public:
        std::vector<char> pass;
        std::string get_pass();
};

#endif // PASSTEXTFORM_H_INCLUDED
