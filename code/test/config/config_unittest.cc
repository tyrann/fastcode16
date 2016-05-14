extern "C" {
    #include "config/config.h"
    #include "ec_parameters.h"
}
#include "gtest/gtest.h"
#include <unistd.h>
#include <stdio.h>

TEST(read_config_file, file_does_not_exists)
{
    const char file_name[] = "config_file_does_not_exists.txt";
    EllipticCurveParameter params;
    int code = read_config_file(&params, file_name);
    ASSERT_EQ(CONFIG_COULD_NOT_OPEN_FILE, code);
}

TEST(parse_line, no_equal_sign)
{
    char buffer[] = "testtest";
    char *key;
    char *val;
    ASSERT_FALSE(parse_line(buffer, &key, &val));
}

TEST(parse_line, correct_example)
{
    char buffer[] = "p=1234";
    char *key;
    char *val;
    ASSERT_TRUE(parse_line(buffer, &key, &val));
    ASSERT_TRUE(strcmp("p", key) == 0);
    ASSERT_TRUE(strcmp("1234", val) == 0);
    free(key);
    free(val);
}

TEST(is_valid_hex_string, empty_string) 
{
    ASSERT_FALSE(is_valid_hex_string(""));
}

TEST(is_valid_hex_string, invalid_inputs) 
{
    ASSERT_FALSE(is_valid_hex_string("11111_"));
    ASSERT_FALSE(is_valid_hex_string("G"));
    ASSERT_FALSE(is_valid_hex_string("?"));
}

TEST(is_valid_hex_string, correct_inputs) 
{
    ASSERT_TRUE(is_valid_hex_string("11111"));
    ASSERT_TRUE(is_valid_hex_string("ABCD"));
    ASSERT_TRUE(is_valid_hex_string("1111BBBCCC"));
}
