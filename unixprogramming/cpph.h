/*
 * cpph.h
 *
 *  Created on: 2020年9月5日
 *      Author: jerray
 */

#ifndef CPPH_H_
#define CPPH_H_
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <string.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <stdarg.h>
#include <time.h>
#include <signal.h>

#define MAXLINE 1024
#define SERVER_PORT 8808

static void  
err_doit(int errnoflag, int error, const char *fmt, va_list ap)  
{  
        char    buf[MAXLINE];  
        vsnprintf(buf, MAXLINE, fmt, ap);  
        if (errnoflag)  
        snprintf(buf+strlen(buf), MAXLINE-strlen(buf), ": %s",strerror(error));  
        strcat(buf, " ");  
        fflush(stdout);     /* in case stdout and stderr are the same */  
        fputs(buf, stderr);  
        fflush(NULL);       /* flushes all stdio output streams */  
}

void
err_sys(const char *fmt, ...)
{
        va_list     ap;

        va_start(ap, fmt);
        err_doit(1, errno, fmt, ap);
        va_end(ap);
        exit(1);
}

struct args{
	long arg1;
	long arg2;
};

struct result{
	long sum;
};

#endif /* CPPH_H_ */
