# $FreeBSD$

.include <src.opts.mk>

PROG=		copong
SRCS=		copong.c

CFLAGS+=	-fPIE -pie -Wno-error=deprecated-declarations -fuse-ld=lld
#NEED_CHERI=	hybrid
NEED_CHERI=	pure
MK_CHERI_SHARED_PROG:=yes

WARNS?=	5

.include <bsd.prog.mk>
