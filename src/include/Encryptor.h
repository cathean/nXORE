#ifndef ENRYPTOR_H_INCLUDED
#define ENRYPTOR_H_INCLUDED

#include "headerpack.h"

class Encryptor
{
    protected:
        std::string xor_encryptor(std::string buffer);
        std::string Istr_encryptor(std::string buffer);
        std::string key;
    public:
        void set_key(std::string k);
        int file_encrypt(std::string origin_path, std::string output_path);
        std::string str_encrypt(std::string str);
};

#endif // ENRYPTOR_H_INCLUDED
