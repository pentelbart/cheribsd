.include <src.opts.mk>

PROG =	ipc
SRCS=	ipc.c
CFLAGS+=-fPIE -pie -fuse-ld=lld -Wno-error=pointer-arith -Wno-error=sign-compare -dynamic -DPROGNAME=\"ipc-dynamic\"
LIBADD=	pthread
NEED_CHERI=	pure
MK_CHERI_SHARED_PROG:=yes

WARNS?= 5

.include <bsd.prog.mk>

