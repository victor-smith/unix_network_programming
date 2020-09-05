#include ../Makefile.defines.in

APPS =  daytimetcpcli daytimetcpsrv

all:${APPS}

daytimetcpcli: daytimetcpcli.o
	${CC} ${CFLAGS} -o $@ daytimetcpcli.o

daytimetcpsrv: daytimetcpsrv.o
	${CC} ${CFLAGS} -o $@ daytimetcpsrv.o

clean:
	rm -fr ${APPS} *.o
