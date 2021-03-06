# $FreeBSD$

MDSRCS+= \
	ffs.S \
	strlen.S

.if ! ${MACHINE_ABI:Mpurecap}
MDSRCS+= \
	bcmp.S \
	bzero.S \
	memset.S \
	strchr.S \
	strcmp.S \
	strrchr.S
.endif

.if ${MACHINE_ABI:Mpurecap} || ${MK_CHERI} == "yes"
CHERI_MDSRCS=	\
		memcpy_c.c \
		memmove_c.c \
		memset_c.c
CHERI_MISRCS=	\
		bcopy.c \
		memcpy.c \
		memmove.c \

MDSRCS+=	${CHERI_MDSRCS}

.if ! ${MACHINE_ABI:Mpurecap}
.if ${MK_CHERI128} == "yes"
_CHERIBITS=128
.else
_CHERIBITS=256
.endif
.for src in ${CHERI_MDSRCS} ${CHERI_MISRCS}
CC.${src}=	${CC} -target cheri-unknown-freebsd -cheri=${_CHERIBITS}
.endfor
.endif

SYM_MAPS+=	${LIBC_SRCTOP}/mips/string/Symbol.map
.endif
