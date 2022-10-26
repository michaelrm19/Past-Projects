CC = clang
CFLAGS = -Wall -Werror -Wextra -Wpedantic
all: encode decode
encode: encode.o trie.o word.o io.o
	$(CC) -o encode encode.o trie.o word.o io.o
decode: decode.o trie.o word.o io.o
	$(CC) -o decode decode.o trie.o word.o io.o
encode.o: encode.c
	$(CC) $(CFLAGS) -c encode.c
decode.o: decode.c
	$(CC) $(CFLAGS) -c decode.c
trie.o: trie.c
	$(CC) $(CFLAGS) -c trie.c
word.o: word.c
	$(CC) $(CFLAGS) -c word.c
io.o: io.c
	$(CC) $(CFLAGS) -c io.c
clean:
	rm -f encode *.o
	rm -f decode *.o
format:
	clang-format -i -style=file encode.c
	clang-format -i -style=file decode.c
	clang-format -i -style=file trie.c
	clang-format -i -style=file trie.h
	clang-format -i -style=file word.c
	clang-format -i -style=file word.h
	clang-format -i -style=file io.c
	clang-format -i -style=file io.h
	clang-format -i -style=file endian.h
	clang-format -i -style=file code.h
