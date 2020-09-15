#include "cpph.h"

void sig_chld(int singno)
{
	pid_t pid;
	int stat;
	while((pid = waitpid(-1, &stat, WNOHANG)) > 0)
		printf("child %d terminated\n", pid);
	return ;
}
void str_echo(int sockfd)
{
	ssize_t n;
	char buf[MAXLINE];

again:
	while((n=read(sockfd, buf, MAXLINE)) >0)
		write(sockfd, buf, n);

	if(n<0 && errno == EINTR)
		goto again;
	else if(n<0)
	{
		printf("%s read error\n", __FUNCTION__);
		exit(0);
	}
}

int main()
{
	int listenfd, connfd;
	pid_t childpid;
	socklen_t chilen;
	struct sockaddr_in cliaddr, servaddr;
	
	listenfd = socket(AF_INET, SOCK_STREAM, 0);
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = SERVER_PORT;
	bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr));

	listen(listenfd, 1024);
	//signal(SIGCHLD, sig_chld);

	for(;;)
	{
		chilen = sizeof(cliaddr);
		if((connfd = accept(listenfd,(struct sockaddr*) &cliaddr, &chilen))<0)
			if(errno = EINTR)
				continue;
			else
			{
				printf("accept error\n");
				exit(0);
			}
		if((childpid=fork()) == 0)
		{
			close(listenfd);
			str_echo(connfd);
			exit(0);
		}
		close(connfd);
	}
	return 0;
}
