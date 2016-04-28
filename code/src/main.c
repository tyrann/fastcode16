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
	else
	{
	    BigInt d;
	    Point P, result, expected;

	    point_copy(&P, &(parameter.generator));
	    bigint_copy(&d, &(parameter.n));
	    create_point_inf(&expected);
	    ec_point_mul(&result, &d, &P, &parameter);
	    printf("%i", point_are_equal(&result, &expected));
	    bigint_free(&d);
	    point_free(&P);
	    point_free(&result);
	    point_free(&expected);
	    ec_free(&parameter);
	}
	
    }

    return 0;
}
