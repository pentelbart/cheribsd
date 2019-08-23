/*
 * System call names.
 *
 * DO NOT EDIT-- this file is automatically @generated.
 * $FreeBSD$
 */

const char *freebsd64_syscallnames[] = {
	"syscall",			/* 0 = syscall */
	"exit",			/* 1 = exit */
	"fork",			/* 2 = fork */
	"freebsd64_read",			/* 3 = freebsd64_read */
	"freebsd64_write",			/* 4 = freebsd64_write */
	"freebsd64_open",			/* 5 = freebsd64_open */
	"close",			/* 6 = close */
	"freebsd64_wait4",			/* 7 = freebsd64_wait4 */
	"obs_ocreat",			/* 8 = obsolete ocreat */
	"freebsd64_link",			/* 9 = freebsd64_link */
	"freebsd64_unlink",			/* 10 = freebsd64_unlink */
	"obs_execv",			/* 11 = obsolete execv */
	"freebsd64_chdir",			/* 12 = freebsd64_chdir */
	"fchdir",			/* 13 = fchdir */
	"compat11.freebsd64_mknod",		/* 14 = freebsd11 freebsd64_mknod */
	"freebsd64_chmod",			/* 15 = freebsd64_chmod */
	"freebsd64_chown",			/* 16 = freebsd64_chown */
	"freebsd64_break",			/* 17 = freebsd64_break */
	"obs_freebsd4_getfsstat",			/* 18 = obsolete freebsd4_getfsstat */
	"obs_olseek",			/* 19 = obsolete olseek */
	"getpid",			/* 20 = getpid */
	"freebsd64_mount",			/* 21 = freebsd64_mount */
	"freebsd64_unmount",			/* 22 = freebsd64_unmount */
	"setuid",			/* 23 = setuid */
	"getuid",			/* 24 = getuid */
	"geteuid",			/* 25 = geteuid */
	"freebsd64_ptrace",			/* 26 = freebsd64_ptrace */
	"freebsd64_recvmsg",			/* 27 = freebsd64_recvmsg */
	"freebsd64_sendmsg",			/* 28 = freebsd64_sendmsg */
	"freebsd64_recvfrom",			/* 29 = freebsd64_recvfrom */
	"freebsd64_accept",			/* 30 = freebsd64_accept */
	"freebsd64_getpeername",			/* 31 = freebsd64_getpeername */
	"freebsd64_getsockname",			/* 32 = freebsd64_getsockname */
	"freebsd64_access",			/* 33 = freebsd64_access */
	"freebsd64_chflags",			/* 34 = freebsd64_chflags */
	"fchflags",			/* 35 = fchflags */
	"sync",			/* 36 = sync */
	"kill",			/* 37 = kill */
	"obs_ostat",			/* 38 = obsolete ostat */
	"getppid",			/* 39 = getppid */
	"obs_olstat",			/* 40 = obsolete olstat */
	"dup",			/* 41 = dup */
	"compat10.pipe",		/* 42 = freebsd10 pipe */
	"getegid",			/* 43 = getegid */
	"freebsd64_profil",			/* 44 = freebsd64_profil */
	"freebsd64_ktrace",			/* 45 = freebsd64_ktrace */
	"obs_osigaction",			/* 46 = obsolete osigaction */
	"getgid",			/* 47 = getgid */
	"obs_osigprocmask",			/* 48 = obsolete osigprocmask */
	"freebsd64_getlogin",			/* 49 = freebsd64_getlogin */
	"freebsd64_setlogin",			/* 50 = freebsd64_setlogin */
	"freebsd64_acct",			/* 51 = freebsd64_acct */
	"obs_osigpending",			/* 52 = obsolete osigpending */
	"freebsd64_sigaltstack",			/* 53 = freebsd64_sigaltstack */
	"freebsd64_ioctl",			/* 54 = freebsd64_ioctl */
	"reboot",			/* 55 = reboot */
	"freebsd64_revoke",			/* 56 = freebsd64_revoke */
	"freebsd64_symlink",			/* 57 = freebsd64_symlink */
	"freebsd64_readlink",			/* 58 = freebsd64_readlink */
	"freebsd64_execve",			/* 59 = freebsd64_execve */
	"umask",			/* 60 = umask */
	"freebsd64_chroot",			/* 61 = freebsd64_chroot */
	"obs_ofstat",			/* 62 = obsolete ofstat */
	"obs_ogetkerninfo",			/* 63 = obsolete ogetkerninfo */
	"obs_ogetpagesize",			/* 64 = obsolete ogetpagesize */
	"freebsd64_msync",			/* 65 = freebsd64_msync */
	"vfork",			/* 66 = vfork */
	"obs_vread",			/* 67 = obsolete vread */
	"obs_vwrite",			/* 68 = obsolete vwrite */
	"sbrk",			/* 69 = sbrk */
	"sstk",			/* 70 = sstk */
	"obs_ommap",			/* 71 = obsolete ommap */
	"compat11.vadvise",		/* 72 = freebsd11 vadvise */
	"freebsd64_munmap",			/* 73 = freebsd64_munmap */
	"freebsd64_mprotect",			/* 74 = freebsd64_mprotect */
	"freebsd64_madvise",			/* 75 = freebsd64_madvise */
	"obs_vhangup",			/* 76 = obsolete vhangup */
	"obs_vlimit",			/* 77 = obsolete vlimit */
	"freebsd64_mincore",			/* 78 = freebsd64_mincore */
	"freebsd64_getgroups",			/* 79 = freebsd64_getgroups */
	"freebsd64_setgroups",			/* 80 = freebsd64_setgroups */
	"getpgrp",			/* 81 = getpgrp */
	"setpgid",			/* 82 = setpgid */
	"freebsd64_setitimer",			/* 83 = freebsd64_setitimer */
	"obs_owait",			/* 84 = obsolete owait */
	"freebsd64_swapon",			/* 85 = freebsd64_swapon */
	"freebsd64_getitimer",			/* 86 = freebsd64_getitimer */
	"obs_ogethostname",			/* 87 = obsolete ogethostname */
	"obs_osethostname",			/* 88 = obsolete osethostname */
	"getdtablesize",			/* 89 = getdtablesize */
	"dup2",			/* 90 = dup2 */
	"#91",			/* 91 = getdopt */
	"freebsd64_fcntl",			/* 92 = freebsd64_fcntl */
	"freebsd64_select",			/* 93 = freebsd64_select */
	"#94",			/* 94 = setdopt */
	"fsync",			/* 95 = fsync */
	"setpriority",			/* 96 = setpriority */
	"socket",			/* 97 = socket */
	"freebsd64_connect",			/* 98 = freebsd64_connect */
	"obs_oaccept",			/* 99 = obsolete oaccept */
	"getpriority",			/* 100 = getpriority */
	"obs_osend",			/* 101 = obsolete osend */
	"obs_orecv",			/* 102 = obsolete orecv */
	"obs_osigreturn",			/* 103 = obsolete osigreturn */
	"freebsd64_bind",			/* 104 = freebsd64_bind */
	"freebsd64_setsockopt",			/* 105 = freebsd64_setsockopt */
	"listen",			/* 106 = listen */
	"obs_vtimes",			/* 107 = obsolete vtimes */
	"obs_osigvec",			/* 108 = obsolete osigvec */
	"obs_osigblock",			/* 109 = obsolete osigblock */
	"obs_osigsetmask",			/* 110 = obsolete osigsetmask */
	"obs_osigsuspend",			/* 111 = obsolete osigsuspend */
	"obs_osigstack",			/* 112 = obsolete osigstack */
	"obs_orecvmsg",			/* 113 = obsolete orecvmsg */
	"obs_osendmsg",			/* 114 = obsolete osendmsg */
	"obs_vtrace",			/* 115 = obsolete vtrace */
	"freebsd64_gettimeofday",			/* 116 = freebsd64_gettimeofday */
	"freebsd64_getrusage",			/* 117 = freebsd64_getrusage */
	"freebsd64_getsockopt",			/* 118 = freebsd64_getsockopt */
	"#119",			/* 119 = resuba */
	"freebsd64_readv",			/* 120 = freebsd64_readv */
	"freebsd64_writev",			/* 121 = freebsd64_writev */
	"freebsd64_settimeofday",			/* 122 = freebsd64_settimeofday */
	"fchown",			/* 123 = fchown */
	"fchmod",			/* 124 = fchmod */
	"obs_orecvfrom",			/* 125 = obsolete orecvfrom */
	"setreuid",			/* 126 = setreuid */
	"setregid",			/* 127 = setregid */
	"freebsd64_rename",			/* 128 = freebsd64_rename */
	"obs_otruncate",			/* 129 = obsolete otruncate */
	"obs_oftruncate",			/* 130 = obsolete oftruncate */
	"flock",			/* 131 = flock */
	"freebsd64_mkfifo",			/* 132 = freebsd64_mkfifo */
	"freebsd64_sendto",			/* 133 = freebsd64_sendto */
	"shutdown",			/* 134 = shutdown */
	"freebsd64_socketpair",			/* 135 = freebsd64_socketpair */
	"freebsd64_mkdir",			/* 136 = freebsd64_mkdir */
	"freebsd64_rmdir",			/* 137 = freebsd64_rmdir */
	"freebsd64_utimes",			/* 138 = freebsd64_utimes */
	"obs_4.2",			/* 139 = obsolete 4.2 sigreturn */
	"freebsd64_adjtime",			/* 140 = freebsd64_adjtime */
	"obs_ogetpeername",			/* 141 = obsolete ogetpeername */
	"obs_ogethostid",			/* 142 = obsolete ogethostid */
	"obs_osethostid",			/* 143 = obsolete osethostid */
	"obs_ogetrlimit",			/* 144 = obsolete ogetrlimit */
	"obs_osetrlimit",			/* 145 = obsolete osetrlimit */
	"obs_okillpg",			/* 146 = obsolete okillpg */
	"setsid",			/* 147 = setsid */
	"freebsd64_quotactl",			/* 148 = freebsd64_quotactl */
	"obs_oquota",			/* 149 = obsolete oquota */
	"obs_ogetsockname",			/* 150 = obsolete ogetsockname */
	"#151",			/* 151 = sem_lock */
	"#152",			/* 152 = sem_wakeup */
	"#153",			/* 153 = asyncdaemon */
	"freebsd64_nlm_syscall",			/* 154 = freebsd64_nlm_syscall */
	"freebsd64_nfssvc",			/* 155 = freebsd64_nfssvc */
	"obs_ogetdirentries",			/* 156 = obsolete ogetdirentries */
	"obs_freebsd4_statfs",			/* 157 = obsolete freebsd4_statfs */
	"obs_freebsd4_fstatfs",			/* 158 = obsolete freebsd4_fstatfs */
	"#159",			/* 159 = nosys */
	"freebsd64_lgetfh",			/* 160 = freebsd64_lgetfh */
	"freebsd64_getfh",			/* 161 = freebsd64_getfh */
	"obs_freebsd4_getdomainname",			/* 162 = obsolete freebsd4_getdomainname */
	"obs_freebsd4_setdomainname",			/* 163 = obsolete freebsd4_setdomainname */
	"obs_freebsd4_uname",			/* 164 = obsolete freebsd4_uname */
	"freebsd64_sysarch",			/* 165 = freebsd64_sysarch */
	"freebsd64_rtprio",			/* 166 = freebsd64_rtprio */
	"#167",			/* 167 = nosys */
	"#168",			/* 168 = nosys */
	"freebsd64_semsys",			/* 169 = freebsd64_semsys */
	"freebsd64_msgsys",			/* 170 = freebsd64_msgsys */
	"freebsd64_shmsys",			/* 171 = freebsd64_shmsys */
	"#172",			/* 172 = nosys */
	"obs_freebsd6_pread",			/* 173 = obsolete freebsd6_pread */
	"obs_freebsd6_pwrite",			/* 174 = obsolete freebsd6_pwrite */
	"setfib",			/* 175 = setfib */
	"freebsd64_ntp_adjtime",			/* 176 = freebsd64_ntp_adjtime */
	"#177",			/* 177 = sfork */
	"#178",			/* 178 = getdescriptor */
	"#179",			/* 179 = setdescriptor */
	"#180",			/* 180 = nosys */
	"setgid",			/* 181 = setgid */
	"setegid",			/* 182 = setegid */
	"seteuid",			/* 183 = seteuid */
	"obs_lfs_bmapv",			/* 184 = obsolete lfs_bmapv */
	"obs_lfs_markv",			/* 185 = obsolete lfs_markv */
	"obs_lfs_segclean",			/* 186 = obsolete lfs_segclean */
	"obs_lfs_segwait",			/* 187 = obsolete lfs_segwait */
	"compat11.freebsd64_stat",		/* 188 = freebsd11 freebsd64_stat */
	"compat11.freebsd64_fstat",		/* 189 = freebsd11 freebsd64_fstat */
	"compat11.freebsd64_lstat",		/* 190 = freebsd11 freebsd64_lstat */
	"freebsd64_pathconf",			/* 191 = freebsd64_pathconf */
	"fpathconf",			/* 192 = fpathconf */
	"#193",			/* 193 = nosys */
	"getrlimit",			/* 194 = getrlimit */
	"setrlimit",			/* 195 = setrlimit */
	"compat11.freebsd64_getdirentries",		/* 196 = freebsd11 freebsd64_getdirentries */
	"obs_freebsd6_mmap",			/* 197 = obsolete freebsd6_mmap */
	"__syscall",			/* 198 = __syscall */
	"obs_freebsd6_lseek",			/* 199 = obsolete freebsd6_lseek */
	"obs_freebsd6_truncate",			/* 200 = obsolete freebsd6_truncate */
	"obs_freebsd6_ftruncate",			/* 201 = obsolete freebsd6_ftruncate */
	"freebsd64___sysctl",			/* 202 = freebsd64___sysctl */
	"freebsd64_mlock",			/* 203 = freebsd64_mlock */
	"freebsd64_munlock",			/* 204 = freebsd64_munlock */
	"freebsd64_undelete",			/* 205 = freebsd64_undelete */
	"freebsd64_futimes",			/* 206 = freebsd64_futimes */
	"getpgid",			/* 207 = getpgid */
	"#208",			/* 208 = nosys */
	"freebsd64_poll",			/* 209 = freebsd64_poll */
	"lkmnosys",			/* 210 = lkmnosys */
	"lkmnosys",			/* 211 = lkmnosys */
	"lkmnosys",			/* 212 = lkmnosys */
	"lkmnosys",			/* 213 = lkmnosys */
	"lkmnosys",			/* 214 = lkmnosys */
	"lkmnosys",			/* 215 = lkmnosys */
	"lkmnosys",			/* 216 = lkmnosys */
	"lkmnosys",			/* 217 = lkmnosys */
	"lkmnosys",			/* 218 = lkmnosys */
	"lkmnosys",			/* 219 = lkmnosys */
	"obs_freebsd7___semctl",			/* 220 = obsolete freebsd7___semctl */
	"semget",			/* 221 = semget */
	"freebsd64_semop",			/* 222 = freebsd64_semop */
	"obs_semconfig",			/* 223 = obsolete semconfig */
	"obs_freebsd7_msgctl",			/* 224 = obsolete freebsd7_msgctl */
	"msgget",			/* 225 = msgget */
	"freebsd64_msgsnd",			/* 226 = freebsd64_msgsnd */
	"freebsd64_msgrcv",			/* 227 = freebsd64_msgrcv */
	"freebsd64_shmat",			/* 228 = freebsd64_shmat */
	"obs_freebsd7_shmctl",			/* 229 = obsolete freebsd7_shmctl */
	"freebsd64_shmdt",			/* 230 = freebsd64_shmdt */
	"shmget",			/* 231 = shmget */
	"freebsd64_clock_gettime",			/* 232 = freebsd64_clock_gettime */
	"freebsd64_clock_settime",			/* 233 = freebsd64_clock_settime */
	"freebsd64_clock_getres",			/* 234 = freebsd64_clock_getres */
	"freebsd64_ktimer_create",			/* 235 = freebsd64_ktimer_create */
	"ktimer_delete",			/* 236 = ktimer_delete */
	"freebsd64_ktimer_settime",			/* 237 = freebsd64_ktimer_settime */
	"freebsd64_ktimer_gettime",			/* 238 = freebsd64_ktimer_gettime */
	"ktimer_getoverrun",			/* 239 = ktimer_getoverrun */
	"freebsd64_nanosleep",			/* 240 = freebsd64_nanosleep */
	"freebsd64_ffclock_getcounter",			/* 241 = freebsd64_ffclock_getcounter */
	"freebsd64_ffclock_setestimate",			/* 242 = freebsd64_ffclock_setestimate */
	"freebsd64_ffclock_getestimate",			/* 243 = freebsd64_ffclock_getestimate */
	"freebsd64_clock_nanosleep",			/* 244 = freebsd64_clock_nanosleep */
	"#245",			/* 245 = nosys */
	"#246",			/* 246 = nosys */
	"freebsd64_clock_getcpuclockid2",			/* 247 = freebsd64_clock_getcpuclockid2 */
	"freebsd64_ntp_gettime",			/* 248 = freebsd64_ntp_gettime */
	"#249",			/* 249 = nosys */
	"freebsd64_minherit",			/* 250 = freebsd64_minherit */
	"rfork",			/* 251 = rfork */
	"obs_openbsd_poll",			/* 252 = obsolete openbsd_poll */
	"issetugid",			/* 253 = issetugid */
	"freebsd64_lchown",			/* 254 = freebsd64_lchown */
	"freebsd64_aio_read",			/* 255 = freebsd64_aio_read */
	"freebsd64_aio_write",			/* 256 = freebsd64_aio_write */
	"freebsd64_lio_listio",			/* 257 = freebsd64_lio_listio */
	"freebsd64_kbounce",			/* 258 = freebsd64_kbounce */
	"#259",			/* 259 = nosys */
	"#260",			/* 260 = nosys */
	"#261",			/* 261 = nosys */
	"#262",			/* 262 = nosys */
	"#263",			/* 263 = nosys */
	"#264",			/* 264 = nosys */
	"#265",			/* 265 = nosys */
	"#266",			/* 266 = nosys */
	"#267",			/* 267 = nosys */
	"#268",			/* 268 = nosys */
	"#269",			/* 269 = nosys */
	"#270",			/* 270 = nosys */
	"#271",			/* 271 = nosys */
	"compat11.freebsd64_getdents",		/* 272 = freebsd11 freebsd64_getdents */
	"#273",			/* 273 = nosys */
	"freebsd64_lchmod",			/* 274 = freebsd64_lchmod */
	"obs_netbsd_lchown",			/* 275 = obsolete netbsd_lchown */
	"freebsd64_lutimes",			/* 276 = freebsd64_lutimes */
	"obs_netbsd_msync",			/* 277 = obsolete netbsd_msync */
	"compat11.freebsd64_nstat",		/* 278 = freebsd11 freebsd64_nstat */
	"compat11.freebsd64_nfstat",		/* 279 = freebsd11 freebsd64_nfstat */
	"compat11.freebsd64_nlstat",		/* 280 = freebsd11 freebsd64_nlstat */
	"#281",			/* 281 = nosys */
	"#282",			/* 282 = nosys */
	"#283",			/* 283 = nosys */
	"#284",			/* 284 = nosys */
	"#285",			/* 285 = nosys */
	"#286",			/* 286 = nosys */
	"#287",			/* 287 = nosys */
	"#288",			/* 288 = nosys */
	"freebsd64_preadv",			/* 289 = freebsd64_preadv */
	"freebsd64_pwritev",			/* 290 = freebsd64_pwritev */
	"#291",			/* 291 = nosys */
	"#292",			/* 292 = nosys */
	"#293",			/* 293 = nosys */
	"#294",			/* 294 = nosys */
	"#295",			/* 295 = nosys */
	"#296",			/* 296 = nosys */
	"obs_freebsd4_fhstatfs",			/* 297 = obsolete freebsd4_fhstatfs */
	"freebsd64_fhopen",			/* 298 = freebsd64_fhopen */
	"compat11.freebsd64_fhstat",		/* 299 = freebsd11 freebsd64_fhstat */
	"modnext",			/* 300 = modnext */
	"freebsd64_modstat",			/* 301 = freebsd64_modstat */
	"modfnext",			/* 302 = modfnext */
	"freebsd64_modfind",			/* 303 = freebsd64_modfind */
	"freebsd64_kldload",			/* 304 = freebsd64_kldload */
	"kldunload",			/* 305 = kldunload */
	"freebsd64_kldfind",			/* 306 = freebsd64_kldfind */
	"kldnext",			/* 307 = kldnext */
	"freebsd64_kldstat",			/* 308 = freebsd64_kldstat */
	"kldfirstmod",			/* 309 = kldfirstmod */
	"getsid",			/* 310 = getsid */
	"setresuid",			/* 311 = setresuid */
	"setresgid",			/* 312 = setresgid */
	"obs_signanosleep",			/* 313 = obsolete signanosleep */
	"freebsd64_aio_return",			/* 314 = freebsd64_aio_return */
	"freebsd64_aio_suspend",			/* 315 = freebsd64_aio_suspend */
	"freebsd64_aio_cancel",			/* 316 = freebsd64_aio_cancel */
	"freebsd64_aio_error",			/* 317 = freebsd64_aio_error */
	"obs_freebsd6_aio_read",			/* 318 = obsolete freebsd6_aio_read */
	"obs_freebsd6_aio_write",			/* 319 = obsolete freebsd6_aio_write */
	"obs_freebsd6_lio_listio",			/* 320 = obsolete freebsd6_lio_listio */
	"yield",			/* 321 = yield */
	"obs_thr_sleep",			/* 322 = obsolete thr_sleep */
	"obs_thr_wakeup",			/* 323 = obsolete thr_wakeup */
	"mlockall",			/* 324 = mlockall */
	"munlockall",			/* 325 = munlockall */
	"freebsd64___getcwd",			/* 326 = freebsd64___getcwd */
	"freebsd64_sched_setparam",			/* 327 = freebsd64_sched_setparam */
	"freebsd64_sched_getparam",			/* 328 = freebsd64_sched_getparam */
	"freebsd64_sched_setscheduler",			/* 329 = freebsd64_sched_setscheduler */
	"sched_getscheduler",			/* 330 = sched_getscheduler */
	"sched_yield",			/* 331 = sched_yield */
	"sched_get_priority_max",			/* 332 = sched_get_priority_max */
	"sched_get_priority_min",			/* 333 = sched_get_priority_min */
	"freebsd64_sched_rr_get_interval",			/* 334 = freebsd64_sched_rr_get_interval */
	"freebsd64_utrace",			/* 335 = freebsd64_utrace */
	"obs_freebsd4_sendfile",			/* 336 = obsolete freebsd4_sendfile */
	"freebsd64_kldsym",			/* 337 = freebsd64_kldsym */
	"freebsd64_jail",			/* 338 = freebsd64_jail */
	"freebsd64_nnpfs_syscall",			/* 339 = freebsd64_nnpfs_syscall */
	"freebsd64_sigprocmask",			/* 340 = freebsd64_sigprocmask */
	"freebsd64_sigsuspend",			/* 341 = freebsd64_sigsuspend */
	"obs_freebsd4_sigaction",			/* 342 = obsolete freebsd4_sigaction */
	"freebsd64_sigpending",			/* 343 = freebsd64_sigpending */
	"obs_freebsd4_sigreturn",			/* 344 = obsolete freebsd4_sigreturn */
	"freebsd64_sigtimedwait",			/* 345 = freebsd64_sigtimedwait */
	"freebsd64_sigwaitinfo",			/* 346 = freebsd64_sigwaitinfo */
	"freebsd64___acl_get_file",			/* 347 = freebsd64___acl_get_file */
	"freebsd64___acl_set_file",			/* 348 = freebsd64___acl_set_file */
	"freebsd64___acl_get_fd",			/* 349 = freebsd64___acl_get_fd */
	"freebsd64___acl_set_fd",			/* 350 = freebsd64___acl_set_fd */
	"freebsd64___acl_delete_file",			/* 351 = freebsd64___acl_delete_file */
	"__acl_delete_fd",			/* 352 = __acl_delete_fd */
	"freebsd64___acl_aclcheck_file",			/* 353 = freebsd64___acl_aclcheck_file */
	"freebsd64___acl_aclcheck_fd",			/* 354 = freebsd64___acl_aclcheck_fd */
	"freebsd64_extattrctl",			/* 355 = freebsd64_extattrctl */
	"freebsd64_extattr_set_file",			/* 356 = freebsd64_extattr_set_file */
	"freebsd64_extattr_get_file",			/* 357 = freebsd64_extattr_get_file */
	"freebsd64_extattr_delete_file",			/* 358 = freebsd64_extattr_delete_file */
	"freebsd64_aio_waitcomplete",			/* 359 = freebsd64_aio_waitcomplete */
	"freebsd64_getresuid",			/* 360 = freebsd64_getresuid */
	"freebsd64_getresgid",			/* 361 = freebsd64_getresgid */
	"kqueue",			/* 362 = kqueue */
	"compat11.freebsd64_kevent",		/* 363 = freebsd11 freebsd64_kevent */
	"obs___cap_get_proc",			/* 364 = obsolete __cap_get_proc */
	"obs___cap_set_proc",			/* 365 = obsolete __cap_set_proc */
	"obs___cap_get_fd",			/* 366 = obsolete __cap_get_fd */
	"obs___cap_get_file",			/* 367 = obsolete __cap_get_file */
	"obs___cap_set_fd",			/* 368 = obsolete __cap_set_fd */
	"obs___cap_set_file",			/* 369 = obsolete __cap_set_file */
	"#370",			/* 370 = nosys */
	"freebsd64_extattr_set_fd",			/* 371 = freebsd64_extattr_set_fd */
	"freebsd64_extattr_get_fd",			/* 372 = freebsd64_extattr_get_fd */
	"freebsd64_extattr_delete_fd",			/* 373 = freebsd64_extattr_delete_fd */
	"__setugid",			/* 374 = __setugid */
	"obs_nfsclnt",			/* 375 = obsolete nfsclnt */
	"freebsd64_eaccess",			/* 376 = freebsd64_eaccess */
	"afs3_syscall",			/* 377 = afs3_syscall */
	"freebsd64_nmount",			/* 378 = freebsd64_nmount */
	"obs_kse_exit",			/* 379 = obsolete kse_exit */
	"obs_kse_wakeup",			/* 380 = obsolete kse_wakeup */
	"obs_kse_create",			/* 381 = obsolete kse_create */
	"obs_kse_thr_interrupt",			/* 382 = obsolete kse_thr_interrupt */
	"obs_kse_release",			/* 383 = obsolete kse_release */
	"freebsd64___mac_get_proc",			/* 384 = freebsd64___mac_get_proc */
	"freebsd64___mac_set_proc",			/* 385 = freebsd64___mac_set_proc */
	"freebsd64___mac_get_fd",			/* 386 = freebsd64___mac_get_fd */
	"freebsd64___mac_get_file",			/* 387 = freebsd64___mac_get_file */
	"freebsd64___mac_set_fd",			/* 388 = freebsd64___mac_set_fd */
	"freebsd64___mac_set_file",			/* 389 = freebsd64___mac_set_file */
	"freebsd64_kenv",			/* 390 = freebsd64_kenv */
	"freebsd64_lchflags",			/* 391 = freebsd64_lchflags */
	"freebsd64_uuidgen",			/* 392 = freebsd64_uuidgen */
	"freebsd64_sendfile",			/* 393 = freebsd64_sendfile */
	"freebsd64_mac_syscall",			/* 394 = freebsd64_mac_syscall */
	"compat11.freebsd64_getfsstat",		/* 395 = freebsd11 freebsd64_getfsstat */
	"compat11.freebsd64_statfs",		/* 396 = freebsd11 freebsd64_statfs */
	"compat11.freebsd64_fstatfs",		/* 397 = freebsd11 freebsd64_fstatfs */
	"compat11.freebsd64_fhstatfs",		/* 398 = freebsd11 freebsd64_fhstatfs */
	"#399",			/* 399 = nosys */
	"ksem_close",			/* 400 = ksem_close */
	"ksem_post",			/* 401 = ksem_post */
	"ksem_wait",			/* 402 = ksem_wait */
	"ksem_trywait",			/* 403 = ksem_trywait */
	"freebsd64_ksem_init",			/* 404 = freebsd64_ksem_init */
	"freebsd64_ksem_open",			/* 405 = freebsd64_ksem_open */
	"freebsd64_ksem_unlink",			/* 406 = freebsd64_ksem_unlink */
	"freebsd64_ksem_getvalue",			/* 407 = freebsd64_ksem_getvalue */
	"ksem_destroy",			/* 408 = ksem_destroy */
	"freebsd64___mac_get_pid",			/* 409 = freebsd64___mac_get_pid */
	"freebsd64___mac_get_link",			/* 410 = freebsd64___mac_get_link */
	"freebsd64___mac_set_link",			/* 411 = freebsd64___mac_set_link */
	"freebsd64_extattr_set_link",			/* 412 = freebsd64_extattr_set_link */
	"freebsd64_extattr_get_link",			/* 413 = freebsd64_extattr_get_link */
	"freebsd64_extattr_delete_link",			/* 414 = freebsd64_extattr_delete_link */
	"freebsd64___mac_execve",			/* 415 = freebsd64___mac_execve */
	"freebsd64_sigaction",			/* 416 = freebsd64_sigaction */
	"freebsd64_sigreturn",			/* 417 = freebsd64_sigreturn */
	"#418",			/* 418 = __xstat */
	"#419",			/* 419 = __xfstat */
	"#420",			/* 420 = __xlstat */
	"freebsd64_getcontext",			/* 421 = freebsd64_getcontext */
	"freebsd64_setcontext",			/* 422 = freebsd64_setcontext */
	"freebsd64_swapcontext",			/* 423 = freebsd64_swapcontext */
	"freebsd64_swapoff",			/* 424 = freebsd64_swapoff */
	"freebsd64___acl_get_link",			/* 425 = freebsd64___acl_get_link */
	"freebsd64___acl_set_link",			/* 426 = freebsd64___acl_set_link */
	"freebsd64___acl_delete_link",			/* 427 = freebsd64___acl_delete_link */
	"freebsd64___acl_aclcheck_link",			/* 428 = freebsd64___acl_aclcheck_link */
	"freebsd64_sigwait",			/* 429 = freebsd64_sigwait */
	"freebsd64_thr_create",			/* 430 = freebsd64_thr_create */
	"freebsd64_thr_exit",			/* 431 = freebsd64_thr_exit */
	"freebsd64_thr_self",			/* 432 = freebsd64_thr_self */
	"thr_kill",			/* 433 = thr_kill */
	"#434",			/* 434 = nosys */
	"#435",			/* 435 = nosys */
	"jail_attach",			/* 436 = jail_attach */
	"freebsd64_extattr_list_fd",			/* 437 = freebsd64_extattr_list_fd */
	"freebsd64_extattr_list_file",			/* 438 = freebsd64_extattr_list_file */
	"freebsd64_extattr_list_link",			/* 439 = freebsd64_extattr_list_link */
	"obs_kse_switchin",			/* 440 = obsolete kse_switchin */
	"freebsd64_ksem_timedwait",			/* 441 = freebsd64_ksem_timedwait */
	"freebsd64_thr_suspend",			/* 442 = freebsd64_thr_suspend */
	"thr_wake",			/* 443 = thr_wake */
	"kldunloadf",			/* 444 = kldunloadf */
	"freebsd64_audit",			/* 445 = freebsd64_audit */
	"freebsd64_auditon",			/* 446 = freebsd64_auditon */
	"freebsd64_getauid",			/* 447 = freebsd64_getauid */
	"freebsd64_setauid",			/* 448 = freebsd64_setauid */
	"freebsd64_getaudit",			/* 449 = freebsd64_getaudit */
	"freebsd64_setaudit",			/* 450 = freebsd64_setaudit */
	"freebsd64_getaudit_addr",			/* 451 = freebsd64_getaudit_addr */
	"freebsd64_setaudit_addr",			/* 452 = freebsd64_setaudit_addr */
	"freebsd64_auditctl",			/* 453 = freebsd64_auditctl */
	"freebsd64__umtx_op",			/* 454 = freebsd64__umtx_op */
	"freebsd64_thr_new",			/* 455 = freebsd64_thr_new */
	"freebsd64_sigqueue",			/* 456 = freebsd64_sigqueue */
	"freebsd64_kmq_open",			/* 457 = freebsd64_kmq_open */
	"freebsd64_kmq_setattr",			/* 458 = freebsd64_kmq_setattr */
	"freebsd64_kmq_timedreceive",			/* 459 = freebsd64_kmq_timedreceive */
	"freebsd64_kmq_timedsend",			/* 460 = freebsd64_kmq_timedsend */
	"freebsd64_kmq_notify",			/* 461 = freebsd64_kmq_notify */
	"freebsd64_kmq_unlink",			/* 462 = freebsd64_kmq_unlink */
	"freebsd64_abort2",			/* 463 = freebsd64_abort2 */
	"freebsd64_thr_set_name",			/* 464 = freebsd64_thr_set_name */
	"freebsd64_aio_fsync",			/* 465 = freebsd64_aio_fsync */
	"freebsd64_rtprio_thread",			/* 466 = freebsd64_rtprio_thread */
	"#467",			/* 467 = nosys */
	"#468",			/* 468 = nosys */
	"#469",			/* 469 = __getpath_fromfd */
	"#470",			/* 470 = __getpath_fromaddr */
	"sctp_peeloff",			/* 471 = sctp_peeloff */
	"freebsd64_sctp_generic_sendmsg",			/* 472 = freebsd64_sctp_generic_sendmsg */
	"freebsd64_sctp_generic_sendmsg_iov",			/* 473 = freebsd64_sctp_generic_sendmsg_iov */
	"freebsd64_sctp_generic_recvmsg",			/* 474 = freebsd64_sctp_generic_recvmsg */
	"freebsd64_pread",			/* 475 = freebsd64_pread */
	"freebsd64_pwrite",			/* 476 = freebsd64_pwrite */
	"freebsd64_mmap",			/* 477 = freebsd64_mmap */
	"lseek",			/* 478 = lseek */
	"freebsd64_truncate",			/* 479 = freebsd64_truncate */
	"ftruncate",			/* 480 = ftruncate */
	"thr_kill2",			/* 481 = thr_kill2 */
	"freebsd64_shm_open",			/* 482 = freebsd64_shm_open */
	"freebsd64_shm_unlink",			/* 483 = freebsd64_shm_unlink */
	"freebsd64_cpuset",			/* 484 = freebsd64_cpuset */
	"cpuset_setid",			/* 485 = cpuset_setid */
	"freebsd64_cpuset_getid",			/* 486 = freebsd64_cpuset_getid */
	"freebsd64_cpuset_getaffinity",			/* 487 = freebsd64_cpuset_getaffinity */
	"freebsd64_cpuset_setaffinity",			/* 488 = freebsd64_cpuset_setaffinity */
	"freebsd64_faccessat",			/* 489 = freebsd64_faccessat */
	"freebsd64_fchmodat",			/* 490 = freebsd64_fchmodat */
	"freebsd64_fchownat",			/* 491 = freebsd64_fchownat */
	"freebsd64_fexecve",			/* 492 = freebsd64_fexecve */
	"compat11.freebsd64_fstatat",		/* 493 = freebsd11 freebsd64_fstatat */
	"freebsd64_futimesat",			/* 494 = freebsd64_futimesat */
	"freebsd64_linkat",			/* 495 = freebsd64_linkat */
	"freebsd64_mkdirat",			/* 496 = freebsd64_mkdirat */
	"freebsd64_mkfifoat",			/* 497 = freebsd64_mkfifoat */
	"compat11.freebsd64_mknodat",		/* 498 = freebsd11 freebsd64_mknodat */
	"freebsd64_openat",			/* 499 = freebsd64_openat */
	"freebsd64_readlinkat",			/* 500 = freebsd64_readlinkat */
	"freebsd64_renameat",			/* 501 = freebsd64_renameat */
	"freebsd64_symlinkat",			/* 502 = freebsd64_symlinkat */
	"freebsd64_unlinkat",			/* 503 = freebsd64_unlinkat */
	"posix_openpt",			/* 504 = posix_openpt */
	"freebsd64_gssd_syscall",			/* 505 = freebsd64_gssd_syscall */
	"freebsd64_jail_get",			/* 506 = freebsd64_jail_get */
	"freebsd64_jail_set",			/* 507 = freebsd64_jail_set */
	"jail_remove",			/* 508 = jail_remove */
	"closefrom",			/* 509 = closefrom */
	"freebsd64___semctl",			/* 510 = freebsd64___semctl */
	"freebsd64_msgctl",			/* 511 = freebsd64_msgctl */
	"freebsd64_shmctl",			/* 512 = freebsd64_shmctl */
	"freebsd64_lpathconf",			/* 513 = freebsd64_lpathconf */
	"obs_cap_new",			/* 514 = obsolete cap_new */
	"freebsd64___cap_rights_get",			/* 515 = freebsd64___cap_rights_get */
	"cap_enter",			/* 516 = cap_enter */
	"freebsd64_cap_getmode",			/* 517 = freebsd64_cap_getmode */
	"freebsd64_pdfork",			/* 518 = freebsd64_pdfork */
	"pdkill",			/* 519 = pdkill */
	"freebsd64_pdgetpid",			/* 520 = freebsd64_pdgetpid */
	"#521",			/* 521 = pdwait4 */
	"freebsd64_pselect",			/* 522 = freebsd64_pselect */
	"freebsd64_getloginclass",			/* 523 = freebsd64_getloginclass */
	"freebsd64_setloginclass",			/* 524 = freebsd64_setloginclass */
	"freebsd64_rctl_get_racct",			/* 525 = freebsd64_rctl_get_racct */
	"freebsd64_rctl_get_rules",			/* 526 = freebsd64_rctl_get_rules */
	"freebsd64_rctl_get_limits",			/* 527 = freebsd64_rctl_get_limits */
	"freebsd64_rctl_add_rule",			/* 528 = freebsd64_rctl_add_rule */
	"freebsd64_rctl_remove_rule",			/* 529 = freebsd64_rctl_remove_rule */
	"posix_fallocate",			/* 530 = posix_fallocate */
	"posix_fadvise",			/* 531 = posix_fadvise */
	"freebsd64_wait6",			/* 532 = freebsd64_wait6 */
	"freebsd64_cap_rights_limit",			/* 533 = freebsd64_cap_rights_limit */
	"freebsd64_cap_ioctls_limit",			/* 534 = freebsd64_cap_ioctls_limit */
	"freebsd64_cap_ioctls_get",			/* 535 = freebsd64_cap_ioctls_get */
	"cap_fcntls_limit",			/* 536 = cap_fcntls_limit */
	"freebsd64_cap_fcntls_get",			/* 537 = freebsd64_cap_fcntls_get */
	"freebsd64_bindat",			/* 538 = freebsd64_bindat */
	"freebsd64_connectat",			/* 539 = freebsd64_connectat */
	"freebsd64_chflagsat",			/* 540 = freebsd64_chflagsat */
	"freebsd64_accept4",			/* 541 = freebsd64_accept4 */
	"freebsd64_pipe2",			/* 542 = freebsd64_pipe2 */
	"freebsd64_aio_mlock",			/* 543 = freebsd64_aio_mlock */
	"freebsd64_procctl",			/* 544 = freebsd64_procctl */
	"freebsd64_ppoll",			/* 545 = freebsd64_ppoll */
	"freebsd64_futimens",			/* 546 = freebsd64_futimens */
	"freebsd64_utimensat",			/* 547 = freebsd64_utimensat */
	"obs_numa_getaffinity",			/* 548 = obsolete numa_getaffinity */
	"obs_numa_setaffinity",			/* 549 = obsolete numa_setaffinity */
	"fdatasync",			/* 550 = fdatasync */
	"freebsd64_fstat",			/* 551 = freebsd64_fstat */
	"freebsd64_fstatat",			/* 552 = freebsd64_fstatat */
	"freebsd64_fhstat",			/* 553 = freebsd64_fhstat */
	"freebsd64_getdirentries",			/* 554 = freebsd64_getdirentries */
	"freebsd64_statfs",			/* 555 = freebsd64_statfs */
	"freebsd64_fstatfs",			/* 556 = freebsd64_fstatfs */
	"freebsd64_getfsstat",			/* 557 = freebsd64_getfsstat */
	"freebsd64_fhstatfs",			/* 558 = freebsd64_fhstatfs */
	"freebsd64_mknodat",			/* 559 = freebsd64_mknodat */
	"freebsd64_kevent",			/* 560 = freebsd64_kevent */
	"freebsd64_cpuset_getdomain",			/* 561 = freebsd64_cpuset_getdomain */
	"freebsd64_cpuset_setdomain",			/* 562 = freebsd64_cpuset_setdomain */
	"freebsd64_getrandom",			/* 563 = freebsd64_getrandom */
	"freebsd64_getfhat",			/* 564 = freebsd64_getfhat */
	"freebsd64_fhlink",			/* 565 = freebsd64_fhlink */
	"freebsd64_fhlinkat",			/* 566 = freebsd64_fhlinkat */
	"freebsd64_fhreadlink",			/* 567 = freebsd64_fhreadlink */
	"freebsd64_funlinkat",			/* 568 = freebsd64_funlinkat */
};
