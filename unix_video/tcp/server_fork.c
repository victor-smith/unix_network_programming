#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <strings.h>
#include <signal.h>
#include <wait.h>

void child_handler(int signo )
{
	printf("%s:%d signo is %d,SIGCHLD=%d\n", __func__, __LINE__, signo, SIGCHLD);
	while(waitpid(0,NULL,WNOHANG)>0)
		;
}

int main()
{
	int listenfd, connfd, n;
	pid_t pid;
	char buff[BUFSIZ];
	struct sockaddr_in saddr, caddr;
	int clen;

	struct sigaction my_act;
	my_act.sa_handler = child_handler;
	sigemptyset(&my_act.sa_mask);
	my_act.sa_flags = 0;

	sigaction(SIGCHLD, &my_act, NULL);

	listenfd = socket(AF_INET, SOCK_STREAM, 0);

	bzero(&saddr, sizeof(saddr));
	saddr.sin_family = AF_INET;
	saddr.sin_port = htons(8000);
	saddr.sin_addr.s_addr = htonl(INADDR_ANY);
	bind(listenfd,(struct sockaddr *) &saddr, sizeof(saddr));

	listen(listenfd, 1024);

	for(;;)
	{
		connfd = accept(listenfd,(struct sockaddr *) &caddr,&clen);
		if(connfd>0 && (pid = fork()) == 0)
		{
			if((pid = fork()) == 0)
			{
				close(listenfd);
				while((n = read(connfd, &buff, BUFSIZ))>0)
				{
					write(connfd, buff, n);
					write(1, buff, n);
				}
				if(n==0)
					close(connfd);
				}
			close(connfd);
			exit(1);
		}
	}

	return 0;
}
