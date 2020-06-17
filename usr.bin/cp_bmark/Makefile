.include <src.opts.mk>

PROG=	cp_bmark
SRCS=	cp_bmark.c
CFLAGS+=-fPIE -pie -Wno-error=pointer-arith -fuse-ld=lld -Wl,-znow
NEED_CHERI=	pure
MK_CHERI_SHARED_PROG:=yes

WARNS?= 5

.include <bsd.prog.mk>