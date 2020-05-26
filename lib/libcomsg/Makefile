
.include <src.opts.mk>

LIB=	comsg

SRCS=	libcomsg.c		\
	coproc.c		\
	commap.c 		\
	statcounters.c

INCS=	comsg.h 		\
	coproc.h		\
	coport.h		\
	sys_comsg.h		\
	commap.h		\
	statcounters.h	\
	statcounters_mips.h \
	statcounters_mips.inc

INCSDIR=	${INCLUDEDIR}/cheri

CFLAGS+=	-I${.CURDIR}
CFLAGS+=	-I${BUILDDIR}
CFLAGS+=	-Ilib/libstatcounters
CFLAGS+=	-I${.CURDIR}/../libc/include \
		-I${.CURDIR}/../libc/locale

SHLIB_MAJOR=	2

.if !defined(NEED_CHERI)
NEED_CHERI=	pure
.endif

.include <bsd.lib.mk>


