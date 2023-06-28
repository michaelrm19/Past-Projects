CC = clang
CFLAGS = -Wall -Werror -Wextra -Wpedantic
all: sorting
sorting: sorting.o set.o bubble.o shell.o quick.o heap.o stack.o
	$(CC) -o sorting sorting.o set.o bubble.o shell.o quick.o heap.o stack.o
sorting.o: sorting.c
	$(CC) $(CFLAGS) -c sorting.c
set.o: set.c
	$(CC) $(CFLAGS) -c set.c
bubble.o: bubble.c
	$(CC) $(CFLAGS) -c bubble.c
shell.o: shell.c
	$(CC) $(CFLAGS) -c shell.c
quick.o: quick.c
	$(CC) $(CFLAGS) -c quick.c
heap.o: heap.c
	$(CC) $(CFLAGS) -c heap.c
stack.o: stack.c
	$(CC) $(CFLAGS) -c stack.c
clean:
	rm -f sorting *.o
format:
	clang-format -i -style=file bubble.h
	clang-format -i -style=file bubble.c
	clang-format -i -style=file gaps.h
	clang-format -i -style=file shell.h
	clang-format -i -style=file shell.c
	clang-format -i -style=file quick.h
	clang-format -i -style=file quick.c
	clang-format -i -style=file stack.h
	clang-format -i -style=file stack.c
	clang-format -i -style=file heap.h
	clang-format -i -style=file heap.c
	clang-format -i -style=file set.h
	clang-format -i -style=file set.c
	clang-format -i -style=file sorting.c
