/*
 * daytimetcpsrv.c
 *
 *  Created on: 2020年9月5日
 *      Author: jerray
 */

#include "cpph.h"

int main(int argc, char **argv)
{
	int listenfd, connfd;
	struct sockaddr_in servaddr;
	char buff[MAXLINE];
	time_t ticks;
	listenfd = socket(AF_INET, SOCK_STREAM, 0);

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(SERVER_PORT);
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

	bind(listenfd, &servaddr, sizeof(servaddr));

	listen(listenfd, 20);

	for(;;)
	{
		connfd = accept(listenfd, NULL, NULL);
		ticks = time(NULL);
		snprintf(buff, sizeof(buff), "%.24s\r\n", ctime(&ticks));
		write(connfd, buff, strlen(buff));
		close(connfd);
	}

	return 0;
}

