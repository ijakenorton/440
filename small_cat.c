#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
int main(int argc, void *argv[]){

	//extern int errno;
	printf("%s\n", argv[1]);
	int fd = open(argv[1], O_RDONLY);
	if (fd == -1){
		perror(strerror(errno));
		exit(1);
	}
	char buf[100];
	int read_status;
	while((read_status = read(fd, buf, 100)) > 0){
		write(1, buf, read_status);
	}

		printf("\n");

	exit(0);
}
