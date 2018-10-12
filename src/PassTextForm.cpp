#include "include/PassTextForm.h"

std::string PassTextForm::get_pass()
{
    std::string p(pass.begin(), pass.end());

    return p;
}
