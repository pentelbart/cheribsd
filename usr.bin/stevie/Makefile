# $FreeBSD$

.include <src.opts.mk>

PROG=		stevie
SRCS=		stevie.c
MAN=

#CFLAGS+=	-fPIE -pie -Wno-error=deprecated-declarations -fuse-ld=lld
CFLAGS+=	-Wno-error=deprecated-declarations
LIBADD=		pthread
#NEED_CHERI=	hybrid
NEED_CHERI=     pure

WARNS?=	5

.include <bsd.prog.mk>
