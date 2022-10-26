CC = clang
CFLAGS = -Wall -Werror -Wextra -Wpedantic
all: banhammer
banhammer: banhammer.o speck.o hash.o ll.o node.o bf.o bv.o parser.o
	$(CC) -o banhammer banhammer.o speck.o hash.o ll.o node.o bf.o bv.o parser.o
banhammer.o: banhammer.c
	$(CC) $(CFLAGS) -c banhammer.c
speck.o: speck.c
	$(CC) $(CFLAGS) -c speck.c
hash.o: hash.c
	$(CC) $(CFLAGS) -c hash.c
ll.o: ll.c
	$(CC) $(CFLAGS) -c ll.c
node.o: node.c
	$(CC) $(CFLAGS) -c node.c
bf.o: bf.c
	$(CC) $(CFLAGS) -c bf.c
bv.o: bv.c
	$(CC) $(CFLAGS) -c bv.c
parser.o: parser.c
	$(CC) $(CFLAGS) -c parser.c
clean:
	rm -f banhammer *.o
format:
	clang-format -i -style=file banhammer.c
	clang-format -i -style=file speck.h
	clang-format -i -style=file speck.c
	clang-format -i -style=file hash.h
	clang-format -i -style=file hash.c
	clang-format -i -style=file ll.h
	clang-format -i -style=file ll.c
	clang-format -i -style=file node.h
	clang-format -i -style=file node.c
	clang-format -i -style=file bf.h
	clang-format -i -style=file bf.c
	clang-format -i -style=file bv.h
	clang-format -i -style=file bv.c
	clang-format -i -style=file parser.h
	clang-format -i -style=file parser.c
