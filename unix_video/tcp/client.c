#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "wrap.h"

int main(int argc, char** argv)
{
	int caddr, n;
	struct sockaddr_in saddr;
	char buff[BUFSIZ];

	short port = 8084;
	if(argc == 2)
		port = atoi(argv[1]);

	caddr = Socket(AF_INET, SOCK_STREAM, 0);
	saddr.sin_family = AF_INET;
	saddr.sin_port = htons(port);
	inet_pton(AF_INET, "127.0.0.1", &saddr.sin_addr.s_addr);

	Connect(caddr, (struct sockaddr*)&saddr, sizeof(saddr));
	{
		while(fgets(buff, sizeof(buff), stdin) != NULL)
		{
			Write(caddr, buff,strlen(buff));
			//buff={0};
			n=Read(caddr,&buff, sizeof(buff));
			if(n==0)
			{
				printf("the other side has been closed\n");
				break;
			}
			else
				Write(stdout, buff, n);
			memset(&buff, 0, sizeof(buff));
		}
	}
	close(caddr);
	return 0;
}
