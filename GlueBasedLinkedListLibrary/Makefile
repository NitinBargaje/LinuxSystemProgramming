target:build/glthread.a
build/glthread.a: build/glthread.o
	ar rs build/glthread.a build/glthread.o
build/glthread.o: src/glthread.c
	gcc -g -c -I src src/glthread.c -o build/glthread.o
clean:
	rm -r build/*