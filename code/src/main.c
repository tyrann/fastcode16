#include "main.h"

int main(int argc, char *argv[])
{
    if(argc != 2)
    {
	printf("elliptic curve cryptography expects one parameter\n");
	printf("example ./ecc configfile.txt\n");
    }
    else
    {
	EllipticCurveParameter parameter;
	int code = read_config_file(&parameter, argv[1]);
	if(code == CONFIG_COULD_NOT_OPEN_FILE)
	{
	    fprintf(stderr, "Could not open file \"%s\"\n", argv[1]);
	    return -1;
	}
	else if(code == CONFIG_INVALID_FORMAT)
	{
	    fprintf(stderr, "The config file \"%s\" is invalid\n", argv[1]);
	    return -1;
	}
	
    }

    return 0;
}
