PROGRAM = tcp_client tcp_server
CC = gcc
SRCS = tcp_client.c tcp_server.c
OBJS = $(SRCS:.c=.o)

all: $(PROGRAM)
	@echo "make done!"

tcp_server: tcp_server.o
	$(CC) $< -o $@

tcp_client: tcp_client.o
	$(CC) $< -o $@

clean:
	@rm -rf *.o $(PROGRAM)
	@echo "clean done!"

.PHONY:all clean
