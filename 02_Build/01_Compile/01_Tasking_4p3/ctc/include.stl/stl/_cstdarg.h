

/*
 * Copyright (c) 1999
 * Boris Fomitchev
 *
 * This material is provided "as is", with absolutely no warranty expressed
 * or implied. Any use is at your own risk.
 *
 * Permission to use or copy this software for any purpose is hereby granted
 * without fee, provided the above notices are retained on all copies.
 * Permission to modify the code and to distribute modified code is granted,
 * provided the above notices are retained, and a notice that the code was
 * modified is included with the above copyright notice.
 */

#ifndef _STLP_INTERNAL_CSTDARG
#define _STLP_INTERNAL_CSTDARG

#if defined (_STLP_USE_NEW_C_HEADERS)
#  if defined (_STLP_HAS_INCLUDE_NEXT)
#    include_next <cstdarg>
#  else
#    include _STLP_NATIVE_CPP_C_HEADER(cstdarg)
#  endif
#else
#  include <stdarg.h>
#endif

#ifdef _STLP_IMPORT_VENDOR_CSTD
_STLP_BEGIN_NAMESPACE
using _STLP_VENDOR_CSTD::va_list;
_STLP_END_NAMESPACE
#endif /* _STLP_IMPORT_VENDOR_CSTD */

#endif
