.include <src.opts.mk>

LIB=	comsg

SRCS=	libcomsg.c		\
	coproc.c		\
	commap.c

INCS=	comsg.h 		\
	coproc.h		\
	coport.h		\
	sys_comsg.h		\
	commap.h

INCSDIR=	${INCLUDEDIR}/cheri

CFLAGS+=	-I${.CURDIR}
CFLAGS+=	-I${.CURDIR}/${MACHINE}


INCSDIR=	${INCLUDEDIR}/cheri

CFLAGS+=	-I${.CURDIR}/../libc/include \
		-I${.CURDIR}/../libc/locale

SHLIB_MAJOR=	1

.if !defined(NEED_CHERI)
NEED_CHERI=	pure
.endif

.include <bsd.lib.mk>
