randmain:
	$(CC) $(CFLAGS) -c randmain.c -o randmain.o
	$(CC) $(CFLAGS) -c randcpuid.c -o randcpuid.o
	$(CC) $(CFLAGS) -ldl -Wl,-rpath=$(PWD) randmain.o randcpuid.o -o randmain

randlibhw.so:
	$(CC) $(CFLAGS) -fPIC -c randlibhw.c -o randlibhw.o
	$(CC) $(CFLAGS) -shared -o randlibhw.so randlibhw.o

randlibsw.so:
	$(CC) $(CFLAGS) -fPIC -c randlibsw.c -o randlibsw.o
	$(CC) $(CFLAGS) -shared	-o randlibsw.so randlibsw.o
