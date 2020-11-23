hello.o: hello.c
	docker exec compiler arm-linux-gnueabi-gcc -I/usr/local/include hello.c -o hello.o /usr/local/lib/libev3dev-c.a

run: hello.o
	docker exec compiler qemu-arm-static hello.o

run_docker: 
	docker run --rm -dit --name compiler -v `pwd`:/src -w /src ev3cc
	docker exec compiler bash -c 'cd ev3dev-c/source/ev3/;make;make install' 
	docker exec compiler bash -c "cd ev3dev-c;pwd"

stop_docker:
	docker stop compiler

clean:
	-rm -f *.o
