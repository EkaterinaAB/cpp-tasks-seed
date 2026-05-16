#include <vector>
#include <cstdint>
#include <string>
#include <stdexcept>
#include <cstring>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
#include <iostream>

#include "base85ed.h"

static const char base85_alphabet[] =
    "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz!#$%&()*+-;<=>?@^_`{|}~";


// TODO: implement this in C++
std::vector<uint8_t> base85::encode(std::vector<uint8_t> const &bytes)
{
    std::vector<uint8_t> res;
    size_t i = 0;
    const size_t n = bytes.size();

    while (i + 4 <= n)
    {

        uint32_t value = (static_cast<uint32_t>(bytes[i]) << 24) |
                         (static_cast<uint32_t>(bytes[i+1]) << 16) |
                         (static_cast<uint32_t>(bytes[i+2]) << 8) |
                         static_cast<uint32_t>(bytes[i+3]);

        uint8_t digits[5];
        for (int j = 4; j >= 0; --j)
        {
            digits[j] = value % 85;
            value /= 85;
        }

        for (int j = 0; j < 5; ++j)
        {
            res.push_back(static_cast<uint8_t>(base85_alphabet[digits[j]]));
        }
        i += 4;
    }


    if (i < n)
    {
        uint32_t value = 0;
        uint8_t block[4] = {0, 0, 0, 0};
        size_t cnt = n - i;

        for (size_t j = 0; j < cnt; ++j)
        {
            block[j] = bytes[i + j];
        }

        value = (static_cast<uint32_t>(block[0]) << 24) |
                (static_cast<uint32_t>(block[1]) << 16) |
                (static_cast<uint32_t>(block[2]) << 8) |
                static_cast<uint32_t>(block[3]);

        std::cout<<block[0]<<' ' << value <<'\n';

        uint8_t digits[5];
        for (int j = 4; j >= 0; --j)
        {
            digits[j] = value % 85;
            value /= 85;
        }

        for (size_t j = 0; j < cnt + 1; ++j)
        {
            res.push_back(static_cast<uint8_t>(base85_alphabet[digits[j]]));
        }
    }

    return res;
}

static const uint8_t* build_map()
{
    static uint8_t base85_table[256];
    static bool initialized = false;
    if (!initialized)
    {
        for (int i = 0; i < 256; ++i) base85_table[i] = 255;
        for (int i = 0; i < 85; ++i)
        {
            base85_table[static_cast<uint8_t>(base85_alphabet[i])] = i;
        }
        initialized = true;
    }
    return base85_table;
}



// TODO: implement this in C++
std::vector<uint8_t> base85::decode(std::vector<uint8_t> const &b85str)
{
    const uint8_t* base85_table = build_map();
    std::vector<uint8_t> res;
    size_t i = 0;
    const size_t n = b85str.size();

    while (i < n)
    {
        uint8_t indices[5];
        size_t b85str_size = 0;
        while (i < n && b85str_size < 5)
        {
            uint8_t ch = b85str[i];
            uint8_t index = base85_table[ch];
            indices[b85str_size++] = index;
            ++i;
        }

        if (b85str_size == 0) continue;

        size_t res_bytes = (b85str_size == 5) ? 4 : (b85str_size - 1);

        while (b85str_size < 5)
        {
            indices[b85str_size++] = 84;
        }

        uint32_t value = 0;
        for (size_t j = 0; j < 5; ++j)
        {
            value = value * 85 + indices[j];
        }

        uint8_t bytes[4];
        bytes[0] = (value >> 24) & 0xFF;
        bytes[1] = (value >> 16) & 0xFF;
        bytes[2] = (value >> 8) & 0xFF;
        bytes[3] = value & 0xFF;

        res.insert(res.end(), bytes, bytes + res_bytes);
    }
    return res;
}
