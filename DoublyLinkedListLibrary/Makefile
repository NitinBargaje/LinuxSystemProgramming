TARGET:build/application
build/application:application.o libdll.a
	gcc build/application.o -o build/application -L build/ -l dll
application.o:src/application.c
	gcc -g -c -I src src/application.c -o build/application.o
libdll.a:dll.o dll_utils.o
	ar rs build/libdll.a build/dll.o build/dll_utils.o
dll.o:src/dll.c
	gcc -g -c -I src src/dll.c -o build/dll.o
dll_utils.o:src/dll_utils.c
	gcc -g -c -I src src/dll_utils.c -o build/dll_utils.o
clean:
	rm -r build/*
