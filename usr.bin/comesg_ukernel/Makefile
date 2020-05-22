.include <src.opts.mk>

PROG =	comesg_ukernel
SRCS=	comesg_kern.c sys_comutex.c coport_utils.c ukern_mman.c ukern_commap.c
CFLAGS+=-fPIE -pie -fuse-ld=lld -Wno-error=pointer-arith -lcomsg
LIBADD=	pthread
NEED_CHERI=	pure
MK_CHERI_SHARED_PROG:=yes

WARNS?= 5

.include <bsd.prog.mk>

