#include <vector>
#include <cstdint>
#include <string>
#include <stdexcept>
#include <cstring>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

#include "base85ed.h"

static const char base85_alphabet[] = 
    "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz!#$%&()*+-;<=>?@^_`{|}~";

// TODO: implement this in C++
std::vector<uint8_t> base85::encode(std::vector<uint8_t> const &bytes)
{
    std::vector<uint8_t> res;
    size_t i = 0;
    const size_t n = bytes.size();

    while (i + 4 <= n) {

        uint32_t value = (static_cast<uint32_t>(bytes[i]) << 24) |
                         (static_cast<uint32_t>(bytes[i+1]) << 16) |
                         (static_cast<uint32_t>(bytes[i+2]) << 8) |
                         static_cast<uint32_t>(bytes[i+3]);

        uint8_t digits[5];
        for (int j = 4; j >= 0; --j) {
            digits[j] = value % 85;
            value /= 85;
        }

        for (int j = 0; j < 5; ++j) {
            res.push_back(static_cast<uint8_t>(base85_alphabet[digits[j]]));
        }
        i += 4;
    }

   
    if (i < n) {
        uint32_t value = 0;
        uint8_t block[4] = {0, 0, 0, 0};
        size_t cnt = n - i;  

        for (size_t j = 0; j < cnt; ++j) {
            block[j] = bytes[i + j];
        }

        value = (static_cast<uint32_t>(block[0]) << 24) |
                (static_cast<uint32_t>(block[1]) << 16) |
                (static_cast<uint32_t>(block[2]) << 8) |
                static_cast<uint32_t>(block[3]);

        std::cout<<block[0]<<' ' << value <<'\n';

        uint8_t digits[5];
        for (int j = 4; j >= 0; --j) {
            digits[j] = value % 85;
            value /= 85;
        }
    
        for (size_t j = 0; j < cnt + 1; ++j) {
            res.push_back(static_cast<uint8_t>(base85_alphabet[digits[j]]));
        }
    }

    return res;
}


// TODO: implement this in C++
std::vector<uint8_t> base85::decode(std::vector<uint8_t> const &b85str)
{
 
}
