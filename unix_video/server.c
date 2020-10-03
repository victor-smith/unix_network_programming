#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>

int main()
{
	int sfd, cfd;
	struct sockaddr_in saddr, caddr;
	int caddr_len, n;


	sfd = socket(AF_INET, SOCK_STREAM, 0);
	saddr.sin_family = AF_INET;
	saddr.sin_port = htons(8084);
	saddr.sin_addr.s_addr = htonl(INADDR_ANY);

	bind(sfd, (struct sockaddr *)&saddr, sizeof(saddr));
	listen(sfd, 1024);

	while(1)
	{
		char buff[BUFSIZ] = {0};
		cfd = accept(sfd, (struct sockaddr *)&caddr, &caddr_len);
		if(cfd == -1)
		    printf("accept error ");
	        while((	n=read(cfd, buff, BUFSIZ)) >0)
		{
		    printf("server:%s", buff);
		    write(cfd, buff,n);
		}
		close(cfd);
	}

	close(sfd);
	return 0;
}
