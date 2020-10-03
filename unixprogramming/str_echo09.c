#include "cpph.h"

void str_echo(int sockfd)
{
	ssize_t n;
	struct args args;
	struct result result;

	for(;;)
	{
		if( (n=read(sockfd, &args, sizeof(args)+1)) == 0){
			printf("server read error");
			return;
		}
		printf("server read: %d %d\n", args.arg1, args.arg2);
		result.sum = args.arg1 + args.arg2;
		write(sockfd, &result, sizeof(result));
	}
}

int main()
{
	int sockfd, connfd;
	int clilen;
	struct sockaddr_in servaddr, cliaddr;
	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(SERVER_PORT);
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

	bind(sockfd, &servaddr, sizeof(servaddr));
	listen(sockfd, 1024);

	for(;;)
	{
		clilen = sizeof(cliaddr);
		if((connfd = accept(sockfd, &cliaddr, sizeof(cliaddr)))<0)
		{
			if(errno == EINTR)
				continue;
			else
				err_sys("accept failed\n");

		}
		str_echo(connfd);
		close(connfd);
	}
	
	return 0;
}
