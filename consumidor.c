#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <string.h>
#include <signal.h>
#include <sys/wait.h>


#define MAX_LEN 10000

struct region{
    int len;
    char buf[MAX_LEN];
};

int fd;

int main(void)
{

	struct region *ptr;
    fd = shm_open("lab", O_RDONLY, 0666);
	if (fd == -1) {
		perror("shm memory error: ");
        exit(EXIT_FAILURE);
	}
	ptr = mmap(NULL,sizeof(struct region), PROT_READ, MAP_SHARED,fd, 0);
	if (ptr == MAP_FAILED) {
		perror("Mapping failed: ");
        exit(EXIT_FAILURE);
	}
	int i=0;

	int tam=0;
	while(i<3)
	{
		printf("Matando al proceso su PID es = %d\n",ptr->buf[tam]);
		kill(ptr->len, SIGKILL);
		tam++;
	}
	shm_unlink("/myregion"); 
    close(fd);
    return 0;
}