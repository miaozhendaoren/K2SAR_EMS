
_BEGIN_STD_C
#if defined(__tricore__)

#define _JBTYPE  \
struct _jmp_buf { unsigned long return_address; unsigned long upper_ctx[16]; }
#define _JBLEN 1
#endif

#if defined(__arm__) || defined(__thumb__)
/*
 * All callee preserved registers:
 * v1 - v7, fp, ip, sp, lr, f4, f5, f6, f7
 */
#define _JBLEN 23
#endif

#ifdef __sparc__
/*
 * onsstack,sigmask,sp,pc,npc,psr,g1,o0,wbcnt (sigcontext).
 * All else recovered by under/over(flow) handling.
 */
#define	_JBLEN	13
#endif

/* necv70 was 9 as well. */

#ifdef __mc68000__
/*
 * onsstack,sigmask,sp,pc,psl,d2-d7,a2-a6,
 * fp2-fp7	for 68881.
 * All else recovered by under/over(flow) handling.
 */
#define	_JBLEN	34
#endif

#if defined(__mc68hc11__) || defined(__mc68hc12__) || defined(__mc68hc1x__)
/*
 * D, X, Y are not saved.
 * Only take into account the pseudo soft registers (max 32).
 */
#define _JBLEN  32
#endif

#if defined(__Z8001__) || defined(__Z8002__)
/* 16 regs + pc */
#define _JBLEN 20
#endif

#ifdef _AM29K
/*
 * onsstack,sigmask,sp,pc,npc,psr,g1,o0,wbcnt (sigcontext).
 * All else recovered by under/over(flow) handling.
 */
#define	_JBLEN	9
#endif

#if defined(__CYGWIN__) && !defined (_JBLEN)
#define _JBLEN (13 * 4)
#elif defined (__i386__)
#if defined(__unix__) || defined(__rtems__)
# define _JBLEN	9
#else
#include "setjmp-dj.h"
#endif
#endif

#ifdef __i960__
#define _JBLEN 35
#endif

#ifdef __M32R__
/* Only 8 words are currently needed.  10 gives us some slop if we need
   to expand.  */
#define _JBLEN 10
#endif

#ifdef __mips__
#ifdef __mips64
#define _JBTYPE long long
#endif
#ifdef __mips_soft_float
#define _JBLEN 11
#else
#define _JBLEN 23
#endif
#endif

#ifdef __m88000__
#define _JBLEN 21
#endif

#ifdef __H8300__
#define _JBLEN 5
typedef int jmp_buf[_JBLEN];
#endif

#ifdef __H8300H__
/* same as H8/300 but registers are twice as big */
#define _JBLEN 5
#define _JBTYPE long
#endif

#ifdef __H8300S__
/* same as H8/300 but registers are twice as big */
#define _JBLEN 5
#define _JBTYPE long
#endif

#ifdef __H8500__
#define _JBLEN 4
#endif

#ifdef  __sh__
#if __SH5__
#define _JBLEN 50
#define _JBTYPE long long
#else
#define _JBLEN 20
#endif /* __SH5__ */
#endif

#ifdef  __v800
#define _JBLEN 28
#endif

#ifdef __PPC__
#ifdef __ALTIVEC__
#define _JBLEN 64
#else
#define _JBLEN 32
#endif
#define _JBTYPE double
#endif

#ifdef __hppa__
/* %r30, %r2-%r18, %r27, pad, %fr12-%fr15.
   Note space exists for the FP registers, but they are not
   saved.  */
#define _JBLEN 28
#endif

#if defined(__mn10300__) || defined(__mn10200__)
#ifdef __AM33_2__
#define _JBLEN 26
#else
/* A guess */
#define _JBLEN 10
#endif
#endif

#ifdef __v850
/* I think our setjmp is saving 15 regs at the moment.  Gives us one word
   slop if we need to expand.  */
#define _JBLEN 16
#endif

#if defined(_C4x)
#define _JBLEN 10
#endif
#if defined(_C3x)
#define _JBLEN 9
#endif

#ifdef __TIC80__
#define _JBLEN 13
#endif

#ifdef __D10V__
#define _JBLEN 8
#endif

#ifdef __D30V__
#define _JBLEN ((64 /* GPR */ + (2*2) /* ACs */ + 18 /* CRs */) / 2)
#define _JBTYPE double
#endif

#ifdef __frv__
#define _JBLEN (68/2)  /* room for 68 32-bit regs */
#define _JBTYPE double
#endif

#ifdef __fr30__
#define _JBLEN 10
#endif

#ifdef __iq2000__
#define _JBLEN 32
#endif

#ifdef __mcore__
#define _JBLEN 16
#endif

#ifdef __MMIX__
/* Using a layout compatible with GCC's built-in.  */
#define _JBLEN 5
#define _JBTYPE unsigned long
#endif

#ifdef __xstormy16__
/* 4 GPRs plus SP plus PC. */
#define _JBLEN 8
#endif

#ifdef _JBLEN
#ifdef _JBTYPE
typedef	_JBTYPE jmp_buf[_JBLEN];
#else
typedef	int jmp_buf[_JBLEN];
#endif

_END_STD_C

#if defined(__CYGWIN__) || defined(__rtems__)
#include <signal.h>

#ifdef __cplusplus
extern "C" {
#endif

/* POSIX sigsetjmp/siglongjmp macros */
typedef int sigjmp_buf[_JBLEN+2];

#define _SAVEMASK	_JBLEN
#define _SIGMASK	(_JBLEN+1)

#ifdef __CYGWIN__
# define _CYGWIN_WORKING_SIGSETJMP
#endif

#define sigsetjmp(env, savemask) ((env)[_SAVEMASK] = savemask,\
               sigprocmask (SIG_SETMASK, 0, (sigset_t *) ((env) + _SIGMASK)),\
               setjmp (env))

#define siglongjmp(env, val) ((((env)[_SAVEMASK])?\
               sigprocmask (SIG_SETMASK, (sigset_t *) ((env) + _SIGMASK), 0):0),\
               longjmp (env, val))

#ifdef __cplusplus
}
#endif
#endif /* __CYGWIN__ or __rtems__ */
#endif
