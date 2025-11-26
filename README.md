# pwn

## Reverse Shell

Has the ability to hijack an existing socket connection eg. a tcp socket and then use the hijacked socket descriptors in its own process space and send and receive network packets

This is a covert channel since the admin and the system thinks the original legitimate process is the one sending the packets out
