#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(int argc, char *argv[])
{
	int local_sock, remote_sock;
	struct sockaddr_in6 server;
	struct sockaddr_in6 client;
	socklen_t len;
	char *paddr_str;
	int sock_client, client_port, server_port;
	char buff[128], *ip;

	if(argc<3 || argc>4){
		printf("Usage: atop_client ([local Port]) [Server IP] [Server Port]\n");
		printf("Example: atop_client 2400 192.168.4.155 2404\n");
		printf("         atop_client 192.168.4.155 2404, local port is assigned by OS\n");
		exit(1);
	}
	
	if(argc ==3){
		server_port = atoi(argv[2]);
		ip = argv[1];
	}
	else{
		client_port = atoi(argv[1]);
		server_port = atoi(argv[3]);
		ip = argv[2];

		local_sock = socket(AF_INET6, SOCK_STREAM, 0);
		client.sin6_family = AF_INET6;
		client.sin6_port = htons(client_port);
		client.sin6_addr = in6addr_any;

		bind(local_sock, (struct sockaddr *)&client, sizeof(client));
	}

	remote_sock = socket(AF_INET6, SOCK_STREAM, 0);
	server.sin6_family = AF_INET6;
	server.sin6_port = htons(server_port);
	inet_pton(AF_INET6, ip, &server.sin6_addr);

	connect(remote_sock, (struct sockaddr *)&server, sizeof(server));
	printf("Connect to server %s:%d\n", ip, server_port);

	memset(buff, 0, sizeof(buff));
	read(remote_sock, buff, sizeof(buff));
	printf("Server: %s\n", buff);

	close(remote_sock);
	close(local_sock);
	printf("Close connection\n");

	return 0;
}

