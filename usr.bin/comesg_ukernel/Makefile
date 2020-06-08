.include <src.opts.mk>

PROG =	comesg_ukernel
SRCS=	comesg_kern.c sys_comutex.c coport_utils.c ukern_mman.c ukern_tables.c ukern_requests.c ukern_utils.c ukern_commap.c ukern_msg_malloc.c
CFLAGS+=-fPIE -pie -fuse-ld=lld -Wno-error=pointer-arith -Wl,-znow -static-pie -lcomsg
LIBADD=	pthread statcounters 
NEED_CHERI=	pure
MK_CHERI_SHARED_PROG:=yes

WARNS?= 5

.include <bsd.prog.mk>

