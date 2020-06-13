.include <src.opts.mk>

PROG=	ipc
SRCS=	ipc.c
CFLAGS+=-fPIE -pie -Wno-error=pointer-arith -fuse-ld=lld -Wl,-znow -lstatcounters -lpthread -DPROGNAME="\"ipc-dynamic\"" -DWITH_STATCOUNTERS -DWITH_QTRACE -DWITH_RUSAGE
NEED_CHERI=	pure
MK_CHERI_SHARED_PROG:=yes

WARNS?= 5

.include <bsd.prog.mk>