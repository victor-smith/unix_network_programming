/*
 * tcpcli01.c
 *
 *  Created on: 2020年9月10日
 *      Author: jerray
 */
#include "cpph.h"

void str_cli(FILE* fp, int sockfd)
{
	char sendline[MAXLINE], recvline[MAXLINE];
	while(fgets(sendline, MAXLINE, fp)>0)
	{
		write(sockfd, sendline, strlen(sendline));
		if(read(sockfd, recvline, MAXLINE)>0)
		{
			fputs(recvline, stdout);
		}
	}
}

int main(int argc, char** argv)
{
	int sockfd;
	struct sockaddr_in servaddr;

	if(argc != 2)
	{
		printf("usage: tcpcli <IPAddres>\n");
		exit(-1);
	}

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(SERVER_PORT);
	inet_pton(AF_INET, argv[1], &servaddr.sin_addr);
	connect(sockfd, &servaddr, sizeof(servaddr));
	str_cli(stdin, sockfd);

	return 0;
}



