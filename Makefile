PROGRAM = tcp_client tcp_server tcp6_client tcp6_server
CC = $(CROSS_COMPILE)gcc
SRCS = tcp_client.c tcp_server.c tcp6_client.c tcp6_server.c
OBJS = $(SRCS:.c=.o)

all: $(PROGRAM)
	@echo "make done!"

tcp6_server: tcp6_server.o
	$(CC) $< -o $@

tcp_server: tcp_server.o
	$(CC) $< -o $@

tcp6_client: tcp6_client.o
	$(CC) $< -o $@

tcp_client: tcp_client.o
	$(CC) $< -o $@

clean:
	@rm -rf *.o $(PROGRAM)
	@echo "clean done!"

.PHONY:all clean
