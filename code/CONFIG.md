Here are some guidelines on how to compile openssl from source and link it to the fastcode project.

	1. Download openssl version 1.0.2h (https://www.openssl.org/source/openssl-1.0.2h.tar.gz)
	2. Untar to [fastcode]/code/lib
	3. Run "mkdir [fastcode]/code/lib/openssl","mkdir [fastcode]/code/lib/openssl/etc","mkdir [fastcode]/code/lib/openssl/usr"
	4. cd in [fastcode]/code/lib/openssl-1.0.2h
	4. Run "./config -fPIC shared --prefix=[ABSOLUTE_PATH TO FASTCODE]/code/lib/openssl/usr --openssldir=[ABSOLUTE_PATH TO FASTCODE]/code/lib/etc
	5. Run "make"
	6. Run "make install INSTALL_PREFIX=[ABSOLUTE_PATH TO FASTCODE]/code/lib/openssl"

If not done already, you need to change the include path in the code so that it now points to the new local openssl. (should be done)

Before compiling our code, set the environement variable LD_LIBRARY_PATH (or LIBRARY_PATH depending on your system) to point to our newly compiled libcrypto.a.




