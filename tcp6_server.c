#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(int argc, char *argv[])
{
	int sock;
	struct sockaddr_in6 addr;
	struct sockaddr_in6 client;
	socklen_t len;
	char *paddr_str;
	int sock_client, port;
	char buff[]="Hello Client";

	if(argc!=2){
		printf("Usage: atop_server [Server port]\n");
		return 0;
	}

	port = atoi(argv[1]);
	sock = socket(AF_INET6, SOCK_STREAM, 0);

	addr.sin6_family = AF_INET6;
	addr.sin6_port = htons(port);
	addr.sin6_addr = in6addr_any;

	bind(sock, (struct sockaddr *)&addr, sizeof(addr));
	printf("Binding port %d\n", port);

	listen(sock, 5);
	printf("Listening...\n");

	len = sizeof(client);
	sock_client = accept(sock, (struct sockaddr *)&client, &len);
	printf("Receive connection\n");

	write(sock_client, buff, sizeof(buff));
	printf("Send message: %s\n", buff);

	close(sock_client);
	printf("Close connection\n");

	close(sock);

	return 0;
}

