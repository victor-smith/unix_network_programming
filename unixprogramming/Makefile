#include ../Makefile.defines.in

APPS = tcpserv01 tcpcli01 byteorder daytimetcpcli daytimetcpsrv

all:${APPS}

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
