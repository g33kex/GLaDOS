hello.o: hello.c
	arm-linux-gnueabi-gcc -I/usr/local/include hello.c -o hello.o /usr/local/lib/libev3dev-c.a

run: hello.o
	qemu-arm-static hello.o

clean:
	-rm -f *.o
