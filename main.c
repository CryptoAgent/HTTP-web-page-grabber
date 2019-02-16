#include "stdio.h"
#include "stdlib.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

int main(int argc,char * argv[]){

	char * addr;
	addr=argv[1];

	int sock_fd = socket(AF_INET,SOCK_STREAM,0);
	struct sockaddr_in server_addr;
	server_addr.sin_family=AF_INET;
	server_addr.sin_port=htons(80);
	inet_aton(addr,&server_addr.sin_addr.s_addr);
	connect(sock_fd,(struct sockaddr*)&server_addr,sizeof(server_addr));

	char request[]="GET / HTTP/1.1\r\n\r\n";
	char response[4096];
	send(sock_fd,&request,sizeof(request),0);
	recv(sock_fd,&response,4096,0);
	printf("%s\r\n",response);
	close(sock_fd);
	return 0;
}