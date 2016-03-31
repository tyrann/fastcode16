#ifndef __CONFIG_H_
#define __CONFIG_H_

#include "../ec_parameters.h"
#include "../bigint.h"
#include <stdlib.h> 
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define BUFFER_SIZE 512

// return values for read_config_file
const char CONFIG_SUCCESS = 0;
const char CONFIG_COULD_NOT_OPEN_FILE = 1;
const char CONFIG_INVALID_FORMAT = 2;

// If the return value is not equal to 0, parameter will be in an undefined state
/*
The following file format is expected
p=HEX String
a=HEX String
b=HEX String
G_x=HEX String
G_y=HEX String
n=HEX String
h=HEX Sring
*/
int read_config_file(EllipticCurveParameter *parameters, const char* filename);

int parse_line(char *buf, char **key, char **val);
int is_valid_key(char *key, int i);
int is_valid_hex_string(const char *val);

#endif
