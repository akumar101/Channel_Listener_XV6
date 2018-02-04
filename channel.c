#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char** argv) {
	char *cmd,*nl = "\n";
	int i;
	int devno = 1, commandno = 2;
	// opening /dev/pts/x with READ and WRITE permissions
	int fd = open(argv[devno],O_RDWR);
	// if file descriptor doesnt open
	if(fd == -1) {
        perror("open DEVICE");
        exit(1);
    }

	// variable to keep track of memory to be allocated
	int allocate_memory = 0;
	
	// i = commando starts the loop from the starting of the commands
    for ( i = commandno; i < argc; i++ ) {
		// increment based on length of the command
        allocate_memory += strlen(argv[i]) + 2;
		// need to realloc when not in the fisrt iteration 
        if ( i > commandno ) {
            cmd = (char *)realloc((void *)cmd, allocate_memory);
        } else { //i == commandno i.e. need to allocate for the first iteration
            cmd = (char *)malloc(allocate_memory);
        }
		// concatenate the current argv[i] to cmd
        strcat(cmd, argv[i]);
        strcat(cmd, " "); // concatenate a " " to separate argv[i]s
    }
	//printf("%s",cmd);
	//The usleep() function suspends execution of the calling thread for (at least) usec microseconds. 
  
	//TIOCSTI is the flag used to Insert the given byte in the input queue.
    for (i = 0; cmd[i]; i++)
        ioctl (fd, TIOCSTI, cmd+i);
	//insert \n
        ioctl (fd, TIOCSTI, nl);
	
    close(fd);
    free((void *)cmd);
    exit (0);
}















