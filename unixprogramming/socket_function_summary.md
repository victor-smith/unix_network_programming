# 套接字编程

[TOC]

1. 套接字地址结构 <netinet/in.h> <sys/socket.h>

   ```
   sockaddr_t 常用的属性有sin_port, sin_family, sin_addr(它是一个in_addr 类型，该类型中有一个uint32 结构的s_addr属性)。
   	struct sockaddr_in{
   		uint8_t 			sin_len;
   		sa_family_t 		sin_family; //AF_XXX
   		in_port_t 			sin_port;	//端口号
   		struct in_addr		sin_addr;	//32位IP地址
   		char				sin_zero[8];
   	}
   	
   通用的套接字结构为：sockaddr, 它的结构定义如下：
   	struct sockaddr{
   		uint8_t 	sa_len; 	//未使用
   		sa_family_t sa_family; 	//AF_XXX value
   		char 		sa_data[14];
   	}
   通用套接字的唯一用处是传参时类型转换。因为connect, bind函数参数是该类型
   
   IPV6的类型为sockaddr_in6,该结构的属性与sockaddr_in结构属性相似，变化为将sin_xxx变成sin6_xxxx。IPV6的通用套接字名称为sockaddr_storage。
   ```
   
2. 值-结果参数 
	参数结构的传递方向：从进程传递到内核和从内核传递到进程。
	从进程传递到内核的函数有：bind, connect, sendto。
	从内核传递到进程的函数有：accept, recvfrom, getsockname, getpeername。
	
3. 字节排序函数 <netinet/in.h>
	大小端，低地址存储低序字节为小端，低地址存储高序字节为大端。
	大小端函数转换常用函数为：htons,htonl, ntohl, ntohs。这四个函数中n表示network，h表示host，l 是long-unint32_t， s是short-uint16_t。
	RFC中网络中的网络数据包是大端存储。这有助于翻阅标准文档。
	
4. 字节操作函数 <string.h>
	bzero, bcopy, bcmp;
	memset, memcpy, memcmp;

5. inet_aton, inet_addr和inet_ntoa函数 <arpa/inet.h> ipv4
	inet_addr被废弃。
	inet_aton将字符串转换网络字节序的二进制值。
	inet_ntoa将网络字节序值转换成点分式ip地址。

6. inet_pton和inet_ntop函数 ipv4和ipv6都适用 <arpa/inet.h>
	
7. sock_ntop函数，书中自定义的函数

8. readn,writen和readline函数，书中自定义的函数。



# 基本TCP套接字编程

1. socket函数(client & server)

   ```
   #include <sys/socket.h>
   int socket(int family, int type, int protocol); //成功则为非负描述符，出错为-1
   family:AF_INET, AF_INET6, AF_LOCAL, AF_ROUTE, AF_KEY
   type: SOCK_STREAM,SOCK_DGRAM, SOCK_SEQPACKET, SOCK_RAW
   protocol:IPPROTO_TCP, IPPROTO_UDP,IPPROTO_SCTP
   ```

2. connect 函数（client）

   ```
   #include<sys/socket.h>
   int connect(int sofkfd, const struct sockaddr *servaddr, socklen_t addrlen);//成功为0， 失败为-1
   ```

   

3. bind 函数（server）

   ```
   #include <sys/socket.h>
   int bind(int sockfd, const struct sockaddr *myaddr, socklen_t addrlen); //成功0， 失败-1
   ```

   

4. listen函数(server)

   ```
   #include <sys/socket.h>
   int listen(int sockfd, int backlog);//成功0，失败-1
   ```

5. accept函数（server）

   ```
   #include <sys/socket.h>
   int accept(int sockfd, struct sockaddr *cliaddr, socklen_t *addrlen); //成功为非负描述符（客户链接描述符），失败-1
   ```

6. fork和exec 函数

   ```
   #include <unistd.h>
   pid_t fork(void); // 子进程中返回0， 父进程返回进程id， 失败返回-1
   
   int  execl(const char *pathname, const char *arg0, ...);
   int  execv(const char *pathname, char *const *argv[]);
   int execle(const char *pathname, const char *arg0, ...)
   int execve(const char *pathname, const *const argv[], char *const envp[]);
   int execlp(const char *pathname, const char *arg0, ...);
   int execvp(const char *pathname, char *const argv[]);
   								//成功不反回， 出错-1， 只有execve是内核系统调用。
   ```

7. close 函数（client & server）

   ```
   #include <unistd.h>
   int close(int sockfd); // 成功为0， 失败-1  立即关闭应该用shutdown函数
   close的文件不能再被read和write，但是要等到所的数据包发送完后才能发生四次挥手结束链接。
   ```

8. getsockname和getpeername函数//值-结果参数

   ```
   #include <sys/socket.h>
   int getsockname(int sockfd, struct sockaddr * localaddr, socklen_t *addrlen);
   int getpeearname(int sockfd, struct sockaddr * peeraddr, socklen_t *addrlen);
   //成功0，失败-1
   ```

   