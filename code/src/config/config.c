#include "config.h"

const char CONFIG_SUCCESS = 0;
const char CONFIG_COULD_NOT_OPEN_FILE = 1;
const char CONFIG_INVALID_FORMAT = 2;

const char * KEYS[] = {
    "p",
    "a",
    "b",
    "G_x",
    "G_y",
    "n",
    "h"
};

int read_config_file(EllipticCurveParameter *parameters, const char* filename)
{
    FILE *fp;
    fp = fopen(filename, "r");
    if(fp == NULL)
    {
	return CONFIG_COULD_NOT_OPEN_FILE;
    }

    char buf[BUFFER_SIZE];
    
    int i = 0;
    BigInt p, a, b, g_x, g_y, n, h;
    Point g;
    while (fgets (buf, sizeof(buf), fp) != NULL)
    {
	int length = strlen(buf);
	// remove \n
	buf[length-1] = '\0';
	char *key;
	char *val;
	
	if(parse_line(buf, &key, &val) && is_valid_key(key, i))
	{
	    if(!is_valid_hex_string(val))
	    {
		fclose(fp);
		return CONFIG_INVALID_FORMAT;
	    }
	    switch(i)
	    {
	    case 0: bigint_from_hex_string(&p, val); break;
	    case 1: bigint_from_hex_string(&a, val); break;
	    case 2: bigint_from_hex_string(&b, val); break;
	    case 3: bigint_from_hex_string(&g_x, val); break;
	    case 4: bigint_from_hex_string(&g_y, val); break;
	    case 5: bigint_from_hex_string(&n, val); break;
	    case 6: bigint_from_hex_string(&h, val); break;
	    }
	}
	else
	{
	    fclose(fp);
	    return CONFIG_INVALID_FORMAT;
	}
	++i;
	free(key);
	free(val);
    }

    create_point(&g, &g_x, &g_y);
    ec_create_parameters(parameters, &p, &a, &b, &g, &n, &h);
    
    bigint_free(&p);
    bigint_free(&a);
    bigint_free(&b);
    point_free(&g);
    bigint_free(&g_x);
    bigint_free(&g_y);
    bigint_free(&n);
    bigint_free(&h);
    fclose(fp);
    return CONFIG_SUCCESS;
}

int parse_line(char *buf, char **key, char **val)
{
    const char t[] = "=";
    char *token;
    token = strtok(buf, t);
    if(token == NULL)
    {
	return 0;
    }
    int n = strlen(token);
    *key = malloc(sizeof(char)*(n+1));
    strncpy(*key, token, n+1);
    token = strtok(NULL, t);
    if(token == NULL)
    {
	free(*key);
	return 0;
    }
    n = strlen(token);
    *val = malloc(sizeof(char)*(n+1));
    strncpy(*val, token, n+1);

    return 1;
}

int is_valid_key(char *key, int i)
{
    if(strcmp(KEYS[i], key) == 0)
    {
	return 1;
    }
    return 0;
}

int is_valid_hex_string(const char *val) 
{
    if(strlen(val) == 0)
    {
	return 0;
    }
    for(unsigned int i = 0; i < strlen(val); i++)
    {
	if(!isxdigit(val[i]))
	{
	    return 0;
	}
    }
    return 1;
}
