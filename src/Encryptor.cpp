#include "include/Encryptor.h"

std::string Encryptor::xor_encryptor(std::string buffer)
{
    std::string encrypted_buffer = buffer;

    for(int i = 0; i < buffer.size(); i++)
        encrypted_buffer[i] = buffer[i] ^ key[i % key.length()];

    return encrypted_buffer;
}

std::string Encryptor::Istr_encryptor(std::string buffer)
{
    std::string encrypted_buffer = buffer;

    if(buffer[buffer.size() - 1] != 'n')
    {
        for(int i = 0; i < buffer.size(); i++)
        {
            if(buffer[i] == '.')
                encrypted_buffer[i] = '}';
            else
                encrypted_buffer[i] = char(++buffer[i]);
        }

        encrypted_buffer += "n";
    }
    else
    {
        encrypted_buffer.pop_back();

        for(int i = 0; i < buffer.size(); i++)
        {
            if(buffer[i] == '}')
                encrypted_buffer[i] = '.';
            else
                encrypted_buffer[i] = char(--buffer[i]);

        }
    }

    return encrypted_buffer;
}

void Encryptor::set_key(std::string k)
{
    key = k;
}

int Encryptor::file_encrypt(std::string origin_path, std::string output_path)
{
    std::ifstream t(origin_path);
    std::string buffer(std::istreambuf_iterator<char>(t), {});
    std::ofstream out(output_path);

    out << xor_encryptor(buffer);
    t.close();
    out.close();
}

std::string Encryptor::str_encrypt(std::string str)
{
    return Istr_encryptor(str);
}
