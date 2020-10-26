#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <pthread.h>
#include "wrap.h"


struct client_sock_info{
	int cfd;
	struct sockaddr_in client_sock;
};

void *srv_action_cb(void * argv)
{
	struct client_sock_info *info = (struct client_sock_info*)argv;

	char buff[1024] = {0};
	int n;

	pthread_detach(pthread_self());

	while(1)
	{
		n=Read(info->cfd, buff, sizeof(buff));

		if(n<=0)
		{
			break;
		}
		else 
		{
			Write(info->cfd, buff, n);
		}
	}
	close(info->cfd);
}

int main(int agrc, char **argv)
{
	int lfd, cfd;
	struct sockaddr_in srv_addr, cli_addr;
	size_t clien_len;
	pthread_t tid;
	
	lfd = Socket(AF_INET, SOCK_STREAM, 0);

	bzero(&srv_addr, sizeof(srv_addr));
	srv_addr.sin_family = AF_INET;
	srv_addr.sin_port = htons(8000);
	srv_addr.sin_addr.s_addr = htonl(INADDR_ANY);


	Bind(lfd, (struct sockaddr*)&srv_addr, sizeof(srv_addr));
	Listen(lfd, 1024);

	while(1)
	{
		cfd = Accept(lfd, (struct sockaddr *)&cli_addr, &clien_len);

		struct client_sock_info client_info;
		client_info.cfd = cfd;
		client_info.client_sock = cli_addr;

		pthread_create(&tid, NULL, srv_action_cb, &client_info);
	}

	close(lfd);
	return 0;
}

//int pthread_create(pthread_t *thread, const pthread_attr_t *attr,
//                          void *(*start_routine) (void *), void *arg);
