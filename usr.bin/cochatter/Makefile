.include <src.opts.mk>

PROG=	cochatter
SRCS=	comsg_chatterer.c
CFLAGS+=-fPIE -pie -Wno-error=pointer-arith -fuse-ld=lld -Wl,-znow -static-pie -lcomsg -lpthread
NEED_CHERI=	pure
MK_CHERI_SHARED_PROG:=yes

WARNS?= 5

.include <bsd.prog.mk>