#include ../Makefile.defines.in

APPS = tcpserv04 tcpcli04 tcpserv01 tcpcli01 byteorder daytimetcpcli daytimetcpsrv

all:${APPS}

tcpserv04: tcpserv04.o
	${CC} ${CFLAGS} -o $@ tcpserv04.o

tcpcli04: tcpcli04.o
	${CC} ${CFLAGS} -o $@ tcpcli04.o

tcpserv01: tcpserv01.o
	${CC} ${CFLAGS} -o $@ tcpserv01.o

tcpcli01: tcpcli01.o
	${CC} ${CFLAGS} -o $@ tcpcli01.o

byteorder: byteorder.o
	${CC} ${CFLAGS} -o $@ byteorder.o


daytimetcpcli: daytimetcpcli.o
	${CC} ${CFLAGS} -o $@ daytimetcpcli.o

daytimetcpsrv: daytimetcpsrv.o
	${CC} ${CFLAGS} -o $@ daytimetcpsrv.o

clean:
	rm -fr ${APPS} *.o
