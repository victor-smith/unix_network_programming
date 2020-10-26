#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/select.h>
#include <sys/time.h>
#include <stdio.h>
#include <strings.h>
#include <stdlib.h>

int main(int argc, char ** argv)
{
	int listenfd, clientfd;
	struct sockaddr_in  servaddr, caddr;
	int clen;

	listenfd = socket(AF_INET, SOCK_STREAM, 0);
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(9999);
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

	bind(listenfd,(struct sockaddr*) &servaddr, sizeof(servaddr));
	
	listen(listenfd, 1024);
	
	int maxfd = listenfd, maxi = -1, i, sockfd;
	int clients[1024];
	int n, iclients;
	fd_set allset, rset;
	char buff[1024];

	FD_ZERO(&allset);
	FD_SET(listenfd, &allset);
	
	clients[0] = listenfd;
	maxi = 0;
	for(i=1; i<1024; i++)
		clients[i] = -1;

	for(;;)
	{
		rset = allset;
		n = select(maxfd+1, &rset, NULL, NULL, NULL);	
		if(n == -1)
		{
			printf("select error");
			exit(-1);
		}
		if(FD_ISSET(listenfd, &rset))
		{
			// accept client connect
			clientfd = accept(listenfd, (struct sockaddr*)&caddr, &clen);
			maxfd = clientfd > maxfd ? clientfd: maxfd;
			for(iclients=1; iclients<1024; i++)
			{
				if(clients[iclients] == -1)
				{
					clients[iclients] = clientfd;
					break;
				}
			}
			if(iclients > 1024)
			{
				printf("exceed 1024");
				exit(1);
			}
			maxi = maxi < iclients?iclients: maxi;
			maxfd = maxfd<clientfd ? clientfd: sockfd;
			FD_SET(clientfd, &allset);

			if(--n == 0)
				continue;
		}
		for(i=0; i<=maxi; i++)
		{
			sockfd = clients[i];
			if(sockfd == -1)
				continue;
			if(FD_ISSET(sockfd, &rset))
			{
				//read client socket and responce socket
				int rlen = read(sockfd, buff, sizeof(buff));
				if(rlen == 0)
				{
					//close client socket
					close(sockfd);
					clients[i]=-1;
					FD_CLR(sockfd,&allset);
				}
				else
				{
					//printf("server:%s", buff);
					write(sockfd, buff, rlen);
				}
				if(--n == 0)
					break;
			}
		}
	}
	close(listenfd);
	return 0;
}
