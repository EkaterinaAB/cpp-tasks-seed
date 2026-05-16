#include <gtest/gtest.h>

#include <unistd.h>
#include <sys/wait.h>
#include <vector>
#include <cstdint>
#include <stdexcept>
#include <string.h>

#include "base85ed.h"

const std::vector<std::pair<const char *, const char * >> short_cases =
{
    { "",     ""     },
    { "F#",   "1"    },
    { "F){",  "12"   },
    { "F)}j", "123"  },
    { "F)}kW","1234" }
};

static std::vector<uint8_t> cstr2v(const char *s)
{
    return std::vector<uint8_t>(
               s,
               s + std::string(s).size()
           );
}

// Тесты encode
TEST(Base85ShortsEncode, TrivialShortEncodes)
{
    for (const auto &p : short_cases)
    {
        EXPECT_EQ(base85::encode(cstr2v(p.second)), cstr2v(p.first));
    }
}

// Тесты decode
TEST(Base85ShortsDecode, TrivialShortDecodes)
{
    for (const auto &p : short_cases)
    {
        EXPECT_EQ(base85::decode(cstr2v(p.first)), cstr2v(p.second));
    }
}

const std::vector<std::pair<const char*, const char*>> long_cases =
{
    { "F)}kWH8wXmIR",     "123456789"  },
    { "F)}kWH8wXmIWP",    "1234567890" },
    { "NM&qnZ!92pZ*pv8Ap", "Hello, world!" },
    { "VPRomVPRomVPO",    "aaaaaaaaaa" },
    { "WM*|?Xm(_4YG`(8WjHf3IXEgNWNU6_M@I",    "dfuahvdkjhvie83298*&dknfGG" },
};


TEST(Base85LongEncode, LongEncodes)
{
    for (const auto &p : long_cases)
    {
        EXPECT_EQ(base85::encode(cstr2v(p.second)), cstr2v(p.first));
    }
}

TEST(Base85LongDecode, LongDecodes)
{
    for (const auto &p : long_cases)
    {
        EXPECT_EQ(base85::decode(cstr2v(p.first)), cstr2v(p.second));
    }
}

TEST(Base85DecodeEncodeShort, RoundShort_1)
{
    for (const auto &p : short_cases)
    {
        auto true_word = cstr2v(p.second);
        auto result = base85::decode(base85::encode(true_word));
        EXPECT_EQ(result, true_word);
    }
}

TEST(Base85DecodeEncodeShort, RoundShort_2)
{
    for (const auto &p : short_cases)
    {
        auto true_word = cstr2v(p.first);
        auto result = base85::encode(base85::decode(true_word));
        EXPECT_EQ(result, true_word);
    }
}

TEST(Base85DecodeEncodeLong, RoundLong_1)
{
    for (const auto &p : long_cases)
    {
        auto true_word = cstr2v(p.second);
        auto result = base85::decode(base85::encode(true_word));
        EXPECT_EQ(result, true_word);
    }
}

TEST(Base85DecodeEncodeLong, RoundLong_2)
{
    for (const auto &p : long_cases)
    {
        auto true_word = cstr2v(p.first);
        auto result = base85::encode(base85::decode(true_word));
        EXPECT_EQ(result, true_word);
    }
}

TEST(Base85Error, InvalidCharacter)
{
    std::vector<uint8_t> string_with_invalid = cstr2v("F/F");
    EXPECT_THROW(base85::decode(string_with_invalid), std::runtime_error);
}
