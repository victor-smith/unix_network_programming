/*
 * daytimetcpcli.c
 *
 *  Created on: 2020年9月5日
 *      Author: jerray
 */

#include "cpph.h"

int main(int argc, char** argv)
{
	int sockfd, n;
	char revline[MAXLINE+1];
	struct sockaddr_in servaddr;

	if(argc != 2)
	{
		printf("using: %s <IPADDRESS>\n", argv[0]);
		exit(-1);
	}

	if((sockfd = socket(AF_INET, SOCK_STREAM, 0))<0)
	{
		printf("socket error.\n");
		exit(-1);
	}

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(SERVER_PORT);
	if(inet_pton(AF_INET, argv[1], &servaddr.sin_addr) <= 0)
	{
		printf("inet_pton error for %s\n", argv[1]);
		exit(-1);
	}

	if(connect(sockfd,&servaddr, sizeof(servaddr))<0)
	{
		printf("connect error\n");
		exit(-1);
	}

	while((n=read(sockfd, revline, MAXLINE))>0)
	{
		revline[n] = 0;
		if(fputs(revline, stdout) == EOF)
		{
			err_sys("fputs error");
		}
	}
	if(n<0)
	{
		err_sys("read error");
	}

	return 0;
}
