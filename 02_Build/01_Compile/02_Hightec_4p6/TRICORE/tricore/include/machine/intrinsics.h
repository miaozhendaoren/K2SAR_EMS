/*
 * intrinsics.h -- C interface for TriCore special machine instructions.
 *
 * Copyright (C) 1999-2003 HighTec EDV-Systeme GmbH.
 *
 */

#ifndef __intrinsics_h
#define __intrinsics_h

/* Note: you must use a numerical constant here (not an integer variable),
   otherwise the assembler will issue an error message.  */
#define _bisr(intlvl) __bisr(intlvl)
#define __bisr(intlvl) asm volatile ("bisr "#intlvl : : : "memory")

/* Note: The parameter "regaddr" in the _mfcr and _mtcr macros may either
   be specified as a 16-bit constant or as a symbolic name (e.g., $psw).  */
#define _mfcr(regaddr) __mfcr(regaddr)
#define __mfcr(regaddr) \
  ({ int res; asm volatile ("mfcr %0,"#regaddr : "=d" (res) : : "memory"); res; })
#define _mtcr(regaddr,val) __mtcr(regaddr,val)
#define __mtcr(regaddr,val) \
  { int newval = (val); asm volatile ("mtcr "#regaddr",%0" : : "d" (newval) : "memory"); }

/* Note: you must use a numerical constant here (not an integer variable),
   otherwise the assembler will issue an error message.  */
#define _syscall(svcno) __syscall(svcno)
#define __syscall(svcno) asm volatile ("syscall "#svcno : : : "memory")

#define _disable() asm volatile ("disable" : : : "memory")
#define _enable() asm volatile ("enable" : : : "memory")
#define _debug() asm volatile ("debug" : : : "memory")
#define _isync() asm volatile ("isync" : : : "memory")
#define _dsync() asm volatile ("dsync" : : : "memory")
#define _rstv() asm volatile ("rstv" : : : "memory")
#define _rslcx() asm volatile ("rslcx" : : : "memory")
#define _svlcx() asm volatile ("svlcx" : : : "memory")
#define _nop() asm volatile ("nop")

#endif /* __intrinsics_h */
