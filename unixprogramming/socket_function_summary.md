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
	
	