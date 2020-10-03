#include "cpph.h"

void str_cli(FILE *fp, int sockfd)
{
	char sendline[MAXLINE];
	struct args args;
	struct result result;
	while(fgets(sendline, MAXLINE, fp) != NULL)
	{
		if(sscanf(sendline, "%ld%ld", &args.arg1, &args.arg2) != 2)
		{
			printf("intput 2 long number.\n");
			continue;
		}
		printf("read :%ld, %ld\n", args.arg1, args.arg2);
		write(sockfd, &args, sizeof(args));
		if(read(sockfd, &result, sizeof(result)) == 0)
		{
			printf("%s read failed\n", __FUNCTION__);
			exit(1);
		}
		printf("%ld\n", result.sum);
	}
}

int main(int argc, char** argv)
{
	if(argc != 2)
	{
		printf("usage: %s <server ip>\n", __FILE__);
		exit(-1);
	}

	int sockfd;
	struct sockaddr_in servaddr;
	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = SERVER_PORT;
	inet_pton(AF_INET, argv[1], &servaddr.sin_addr);

	connect(sockfd, &servaddr, sizeof(servaddr));
	printf("connecting was ok\n");
	str_cli(stdin, sockfd);

	exit(0);
}
