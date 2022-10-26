CC = clang
CFLAGS = -Wall -Werror -Wextra -Wpedantic
all: gen dec err
gen: generator.o hamming.o bm.o
	$(CC) -o gen generator.o hamming.o bm.o
dec: decoder.o hamming.o bm.o
	$(CC) -o dec decoder.o hamming.o bm.o
err: error.o
	$(CC) -o err error.o
decoder.o: decoder.c
	$(CC) $(CFLAGS) -c decoder.c
error.o: error.c
	$(CC) $(CFLAGS) -c error.c
generator.o: generator.c
	$(CC) $(CFLAGS) -c generator.c
hamming.o: hamming.c
	$(CC) $(CFLAGS) -c hamming.c
bm.o: bm.c
	$(CC) $(CFLAGS) -c bm.c
clean:
	rm -f gen *.o
	rm -f err *.o
	rm -f dec *.o
format:
	clang-format -i -style=file decoder.c
	clang-format -i -style=file generator.c
	clang-format -i -style=file bm.h
	clang-format -i -style=file bm.c
	clang-format -i -style=file hamming.h
	clang-format -i -style=file hamming.c
	clang-format -i -style=file error.c
