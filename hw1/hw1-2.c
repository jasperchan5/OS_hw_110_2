#include <sys/wait.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(){
    int n = 0;
    scanf("%d",&n);
    pid_t pid;
    pid = fork();
    if(pid < 0){
        fprintf(stderr,"Forked failed\n");
        return 1;
    }
    else if(pid == 0){
        printf("%d",n);
        while(n > 1){
            if(n % 2 == 0){
                n = n/2;
            }
            else{
                n = 3*n + 1;
            }
            printf(",%d",n);
        }
        printf("\n");
    }
    else{
        wait(NULL);
    }
    return 0;
}