.include <src.opts.mk>

PROG=	memcpy_bmark
SRCS=	memcpy_bmark.c
CFLAGS+=-fPIE -pie -Wno-error=pointer-arith -fuse-ld=lld -Wl,-znow -lstatcounters
NEED_CHERI=	pure
MK_CHERI_SHARED_PROG:=yes

WARNS?= 5

.include <bsd.prog.mk>