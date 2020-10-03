#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>

#define MAX_LEN 10000

struct region {
    int len;
    char buf[MAX_LEN];
};

int fd;

int main(void){

    struct region *ptr;
    //Create shared memory
    fd = shm_open("lab", O_CREAT | O_RDWR,  S_IRUSR | S_IWUSR);
    if (fd < 0){
        perror("shm memory error: ");
        exit(EXIT_FAILURE);
    }
    //Expand to meet the desirable size
    //ftruncate(fd, MAX_LEN*sizeof(struct region));
    if (ftruncate(fd, sizeof(struct region)) == -1){
        perror("Truncation failed: ");
        exit(EXIT_FAILURE);
    }

    int tam=0;
    int contador=0;
    while(contador<3){
        pid_t pid = fork();
        if (pid == 0){
            printf("[HIJO] pid = %d\n",getpid());
            struct timespec ts1,ts2;
            clock_gettime(CLOCK_REALTIME,&ts1);
            time_t iTotal_sec=time(0);
            struct tm *ptm= localtime((const time_t*)&iTotal_sec);
            char tiempo[8];
            strftime(tiempo, 100, "%H:%M:%S", ptm);
            //printf("[%s] ",tiempo);
			//solo crearemos los milisegundos
			sleep(2);
			clock_gettime(CLOCK_REALTIME, &ts2);
			if (ts2.tv_nsec < ts1.tv_nsec) {
				ts2.tv_nsec += 1000000000;
				ts2.tv_sec--;
			}

			//printf("[HIJO] El proceso hijo se creo con PID = %d\n",getpid());
            ptr = mmap(NULL,sizeof(struct region), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
            if (ptr == MAP_FAILED)
                printf("Error\n");

            

            ptr->buf[tam]=getpid();
            tam++;
            //printf("Esto es PID amigo [%d] ,\n", ptr->len);          

        }else if (pid > 0){
            printf("[PADRE] con ppid = %d\n",getppid());
            struct timespec ts1,ts2;
            clock_gettime(CLOCK_REALTIME,&ts1);
            time_t iTotal_sec=time(0);
            struct tm *ptm= localtime((const time_t*)&iTotal_sec);
            char tiempo[8];
            strftime(tiempo, 100, "%H:%M:%S", ptm);
            printf("[%s] ",tiempo);
			//solo crearemos los milisegundos
			sleep(2);
			clock_gettime(CLOCK_REALTIME, &ts2);
			if (ts2.tv_nsec < ts1.tv_nsec) {
				ts2.tv_nsec += 1000000000;
				ts2.tv_sec--;
			}

			printf("P(%d): creando proceso  %d (%s)\n",getppid(),getpid(),tiempo);

            ptr = mmap(NULL, sizeof(struct region), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
            if (ptr == MAP_FAILED)
                printf("Error\n");
            
        }else{
            printf("Error: fork\n");
        }
    }
    shm_unlink("/myregion"); 
    close(fd);
    return 0;
}
