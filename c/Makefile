CC=gcc

main:
	mkdir build
	$(CC) -c src/lib/utils.c -o build/utils.o
	$(CC) -c src/box.c -o build/box.o
	$(CC) -o build/box build/utils.o build/box.o
	ln -s build/box box

clean:
	rm -rf build
	rm box
