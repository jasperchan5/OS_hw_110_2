#include <sys/wait.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <string.h>

int main(){
    int n = 0;
    scanf("%d",&n);
    int shm_fd;
    void* ptr;
    const char* name = "hw1-3";
    const int SIZE = 4096;
    shm_fd = shm_open(name,O_CREAT|O_RDWR,0666);
    ftruncate(shm_fd,SIZE);
    ptr = mmap(0,SIZE,PROT_WRITE,MAP_SHARED,shm_fd,0);
    pid_t pid;
    pid = fork();
    if(pid < 0){
        fprintf(stderr,"Forked failed\n");
        return 1;
    }
    else if(pid == 0){
        char initNum[SIZE];
        sprintf(initNum,"%d",n);
        sprintf(ptr,"%s",initNum);
        ptr += strlen(initNum);
        while(n > 1){
            if(n % 2 == 0){
                n = n/2;
            }
            else{
                n = 3*n + 1;
            }
            char nStr[SIZE];
            sprintf(ptr,",");
            ptr += 1;
            sprintf(nStr,"%d",n);
            sprintf(ptr,"%s",nStr);
            ptr += strlen(nStr);
        }
    }
    else{
        wait(NULL);
        printf("%s\n",(char*) ptr);
        shm_unlink(name);
    }
    return 0;
}