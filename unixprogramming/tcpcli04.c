#include "cpph.h"

void str_cli(FILE *fp, int sockfd)
{
	char sendline[MAXLINE], recvline[MAXLINE];

	while(fgets(sendline, MAXLINE, fp) != NULL)
	{
		write(sockfd, sendline, strlen(sendline));
		if(read(sockfd, recvline, MAXLINE) == 0)
		{
			printf("read end\n");
			exit(0);
		}
		fputs(recvline, stdout);
	}
}

int main(int argc, char **argv)
{
	int i, sockfd[5];
	struct sockaddr_in servaddr;
	if(argc != 2)
	{
		printf("commands usage:%s <IPAddress>\n", __FILE__);
		exit(0);
	}
	for(i=0; i<5; i++)
	{
		sockfd[i] = socket(AF_INET, SOCK_STREAM, 0);
		bzero(&servaddr, sizeof(servaddr));
		servaddr.sin_family = AF_INET;
		servaddr.sin_port = SERVER_PORT;
		inet_pton(AF_INET, argv[1], &servaddr.sin_addr);

		connect(sockfd[i],(struct sockaddr *) &servaddr, sizeof(servaddr));
	}

	str_cli(stdin, sockfd[0]);
	exit(0);
}
