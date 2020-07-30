#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>

int main()
{
    int fd[2], n;
    char c;
    pid_t childpid;

    pipe(fd);
    if((childpid=fork())==0)
    {
        sleep(1);
        read(fd[0], &c, 1);
        printf("%d get %c\n", getpid(), c);
        write(fd[0],"p",1);
    }

    write(fd[1], "c", 1);
    while((n=read(fd[1],&c,1))>0)
    {
        printf("%d gets %c\n", getpid(), c);
    }

    return 0;
}
