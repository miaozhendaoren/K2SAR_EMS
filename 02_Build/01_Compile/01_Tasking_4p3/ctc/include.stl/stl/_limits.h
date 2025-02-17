

/*
 * Copyright (c) 1997
 * Silicon Graphics Computer Systems, Inc.
 *
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
 *
 */

/* NOTE: This may be not portable code. Parts of numeric_limits<> are
 * inherently machine-dependent.  At present this file is suitable
 * for the MIPS, SPARC, Alpha and ia32 architectures.
 */

#ifndef _STLP_INTERNAL_LIMITS
#define _STLP_INTERNAL_LIMITS

#ifndef _STLP_CLIMITS
#  include <climits>
#endif

#ifndef _STLP_CFLOAT
#  include <cfloat>
#endif

#if defined (_STLP_HAS_WCHAR_T) && !defined (_STLP_INTERNAL_CWCHAR)
#  include <stl/_cwchar.h>
#endif

_STLP_BEGIN_NAMESPACE

enum float_round_style {
  round_indeterminate       = -1,
  round_toward_zero         =  0,
  round_to_nearest          =  1,
  round_toward_infinity     =  2,
  round_toward_neg_infinity =  3
};

enum float_denorm_style {
  denorm_indeterminate = -1,
  denorm_absent        =  0,
  denorm_present       =  1
};

_STLP_MOVE_TO_PRIV_NAMESPACE

// Base class for all specializations of numeric_limits.
template <class __number>
class _Numeric_limits_base {
public:

  static __number (_STLP_CALL min)() _STLP_NOTHROW { return __number(); }
  static __number (_STLP_CALL max)() _STLP_NOTHROW { return __number(); }

  _STLP_STATIC_CONSTANT(int, digits = 0);
  _STLP_STATIC_CONSTANT(int, digits10 = 0);
  _STLP_STATIC_CONSTANT(int, radix = 0);
  _STLP_STATIC_CONSTANT(int, min_exponent = 0);
  _STLP_STATIC_CONSTANT(int, min_exponent10 = 0);
  _STLP_STATIC_CONSTANT(int, max_exponent = 0);
  _STLP_STATIC_CONSTANT(int, max_exponent10 = 0);

  _STLP_STATIC_CONSTANT(float_denorm_style, has_denorm = denorm_absent);
  _STLP_STATIC_CONSTANT(float_round_style, round_style = round_toward_zero);

  _STLP_STATIC_CONSTANT(bool, is_specialized = false);
  _STLP_STATIC_CONSTANT(bool, is_signed  = false);
  _STLP_STATIC_CONSTANT(bool, is_integer = false);
  _STLP_STATIC_CONSTANT(bool, is_exact = false);
  _STLP_STATIC_CONSTANT(bool, has_infinity = false);
  _STLP_STATIC_CONSTANT(bool, has_quiet_NaN = false);
  _STLP_STATIC_CONSTANT(bool, has_signaling_NaN = false);
  _STLP_STATIC_CONSTANT(bool, has_denorm_loss = false);
  _STLP_STATIC_CONSTANT(bool, is_iec559 = false);
  _STLP_STATIC_CONSTANT(bool, is_bounded = false);
  _STLP_STATIC_CONSTANT(bool, is_modulo = false);
  _STLP_STATIC_CONSTANT(bool, traps = false);
  _STLP_STATIC_CONSTANT(bool, tinyness_before = false);

  static __number _STLP_CALL epsilon() _STLP_NOTHROW     { return __number(); }
  static __number _STLP_CALL round_error() _STLP_NOTHROW { return __number(); }

  static __number _STLP_CALL infinity() _STLP_NOTHROW      { return __number(); }
  static __number _STLP_CALL quiet_NaN() _STLP_NOTHROW     { return __number(); }
  static __number _STLP_CALL signaling_NaN() _STLP_NOTHROW { return __number(); }
  static __number _STLP_CALL denorm_min() _STLP_NOTHROW    { return __number(); }
};

// Base class for integers.

#ifdef _STLP_LIMITED_DEFAULT_TEMPLATES
#  ifdef _STLP_LONG_LONG
#    define _STLP_LIMITS_MIN_TYPE _STLP_LONG_LONG
#    define _STLP_LIMITS_MAX_TYPE unsigned _STLP_LONG_LONG
#  else
#    define _STLP_LIMITS_MIN_TYPE long
#    define _STLP_LIMITS_MAX_TYPE unsigned long
#  endif
#else
#  define _STLP_LIMITS_MIN_TYPE _Int
#  define _STLP_LIMITS_MAX_TYPE _Int
#endif /* _STLP_LIMITED_DEFAULT_TEMPLATES */

template <class _Int,
          _STLP_LIMITS_MIN_TYPE __imin,
          _STLP_LIMITS_MAX_TYPE __imax,
          int __idigits, bool __ismod>
class _Integer_limits : public _Numeric_limits_base<_Int> {
public:

  static _Int (_STLP_CALL min) () _STLP_NOTHROW { return (_Int)__imin; }
  static _Int (_STLP_CALL max) () _STLP_NOTHROW { return (_Int)__imax; }

  _STLP_STATIC_CONSTANT(int, digits = (__idigits < 0) ? ((int)((sizeof(_Int) * (CHAR_BIT))) - ((__imin == 0) ? 0 : 1)) : (__idigits));
  _STLP_STATIC_CONSTANT(int, digits10 = (digits * 301UL) / 1000);
  _STLP_STATIC_CONSTANT(int, radix = 2);
  _STLP_STATIC_CONSTANT(bool, is_specialized = true);
  _STLP_STATIC_CONSTANT(bool, is_signed = (__imin != 0));
  _STLP_STATIC_CONSTANT(bool, is_integer = true);
  _STLP_STATIC_CONSTANT(bool, is_exact = true);
  _STLP_STATIC_CONSTANT(bool, is_bounded = true);
  _STLP_STATIC_CONSTANT(bool, is_modulo = __ismod);
};

// Base class for floating-point numbers.
template <class __number,
         int __Digits, int __Digits10,
         int __MinExp, int __MaxExp,
         int __MinExp10, int __MaxExp10,
         bool __IsIEC559,
         float_denorm_style __DenormStyle,
         float_round_style __RoundStyle>
class _Floating_limits : public _Numeric_limits_base<__number> {
public:

  _STLP_STATIC_CONSTANT(int, digits = __Digits);
  _STLP_STATIC_CONSTANT(int, digits10 = __Digits10);
  _STLP_STATIC_CONSTANT(int, radix = FLT_RADIX);
  _STLP_STATIC_CONSTANT(int, min_exponent = __MinExp);
  _STLP_STATIC_CONSTANT(int, max_exponent = __MaxExp);
  _STLP_STATIC_CONSTANT(int, min_exponent10 = __MinExp10);
  _STLP_STATIC_CONSTANT(int, max_exponent10 = __MaxExp10);

  _STLP_STATIC_CONSTANT(float_denorm_style, has_denorm = __DenormStyle);
  _STLP_STATIC_CONSTANT(float_round_style, round_style = __RoundStyle);

  _STLP_STATIC_CONSTANT(bool, is_specialized = true);
  _STLP_STATIC_CONSTANT(bool, is_signed = true);

  _STLP_STATIC_CONSTANT(bool, has_infinity = true);
#if (!defined (_STLP_MSVC) || (_STLP_MSVC > 1300)) && \
    (!defined (__BORLANDC__) || (__BORLANDC__ >= 0x590)) && \
    (!defined (_CRAY) || defined (_CRAYIEEE))
  _STLP_STATIC_CONSTANT(bool, has_quiet_NaN = true);
  _STLP_STATIC_CONSTANT(bool, has_signaling_NaN = true);
#else
  _STLP_STATIC_CONSTANT(bool, has_quiet_NaN = false);
  _STLP_STATIC_CONSTANT(bool, has_signaling_NaN = false);
#endif

  _STLP_STATIC_CONSTANT(bool, is_iec559 = __IsIEC559 && has_infinity && has_quiet_NaN && has_signaling_NaN && (has_denorm == denorm_present));
  _STLP_STATIC_CONSTANT(bool, has_denorm_loss =  false);
  _STLP_STATIC_CONSTANT(bool, is_bounded = true);
  _STLP_STATIC_CONSTANT(bool, traps = true);
  _STLP_STATIC_CONSTANT(bool, tinyness_before = false);
};

_STLP_MOVE_TO_STD_NAMESPACE

// Class numeric_limits

// The unspecialized class.

template<class _Tp>
class numeric_limits : public _STLP_PRIV _Numeric_limits_base<_Tp> {};

// Specializations for all built-in integral types.

#if !defined (_STLP_NO_BOOL)
_STLP_TEMPLATE_NULL
class numeric_limits<bool>
  : public _STLP_PRIV _Integer_limits<bool, false, true, 1, false>
{};
#endif /* _STLP_NO_BOOL */

_STLP_TEMPLATE_NULL
class numeric_limits<char>
  : public _STLP_PRIV _Integer_limits<char, CHAR_MIN, CHAR_MAX, -1, true>
{};

#if !defined (_STLP_NO_SIGNED_BUILTINS)
_STLP_TEMPLATE_NULL
class numeric_limits<signed char>
  : public _STLP_PRIV _Integer_limits<signed char, SCHAR_MIN, SCHAR_MAX, -1, true>
{};
#endif

_STLP_TEMPLATE_NULL
class numeric_limits<unsigned char>
  : public _STLP_PRIV _Integer_limits<unsigned char, 0, UCHAR_MAX, -1, true>
{};

#if !(defined (_STLP_NO_WCHAR_T) || defined (_STLP_WCHAR_T_IS_USHORT))

_STLP_TEMPLATE_NULL
class numeric_limits<wchar_t>
  : public _STLP_PRIV _Integer_limits<wchar_t, WCHAR_MIN, WCHAR_MAX, -1, true>
{};

#endif

_STLP_TEMPLATE_NULL
class numeric_limits<short>
  : public _STLP_PRIV _Integer_limits<short, SHRT_MIN, SHRT_MAX, -1, true>
{};

_STLP_TEMPLATE_NULL
class numeric_limits<unsigned short>
  : public _STLP_PRIV _Integer_limits<unsigned short, 0, USHRT_MAX, -1, true>
{};

#if defined (__xlC__) && (__xlC__ == 0x500)
#  undef INT_MIN
#  define INT_MIN -2147483648
#endif

_STLP_TEMPLATE_NULL
class numeric_limits<int>
  : public _STLP_PRIV _Integer_limits<int, INT_MIN, INT_MAX, -1, true>
{};

_STLP_TEMPLATE_NULL
class numeric_limits<unsigned int>
  : public _STLP_PRIV _Integer_limits<unsigned int, 0, UINT_MAX, -1, true>
{};

_STLP_TEMPLATE_NULL
class numeric_limits<long>
  : public _STLP_PRIV _Integer_limits<long, LONG_MIN, LONG_MAX, -1, true>
{};

_STLP_TEMPLATE_NULL
class numeric_limits<unsigned long>
  : public _STLP_PRIV _Integer_limits<unsigned long, 0, ULONG_MAX, -1, true>
{};

#if defined (_STLP_LONG_LONG)

#  if defined (_STLP_MSVC) || defined (__BORLANDC__)
#    define LONGLONG_MAX     0x7fffffffffffffffi64
#    define LONGLONG_MIN     (-LONGLONG_MAX-1i64)
#    define ULONGLONG_MAX    0xffffffffffffffffUi64
#  else
#    ifndef LONGLONG_MAX
#      define LONGLONG_MAX   0x7fffffffffffffffLL
#    endif
#    ifndef LONGLONG_MIN
#      define LONGLONG_MIN   (-LONGLONG_MAX-1LL)
#    endif
#    ifndef ULONGLONG_MAX
#      define ULONGLONG_MAX  0xffffffffffffffffULL
#    endif
#  endif

#  if !defined (__GNUC__) || (__GNUC__ == 2 && __GNUC_MINOR__ <= 96) || (__GNUC__ == 3 && __GNUC_MINOR__ >= 1) || (__GNUC__ > 3)

_STLP_TEMPLATE_NULL
class numeric_limits<_STLP_LONG_LONG>
  : public _STLP_PRIV _Integer_limits<_STLP_LONG_LONG, LONGLONG_MIN, LONGLONG_MAX, -1, true>
{};

_STLP_TEMPLATE_NULL
class numeric_limits<unsigned _STLP_LONG_LONG>
  : public _STLP_PRIV _Integer_limits<unsigned _STLP_LONG_LONG, 0, ULONGLONG_MAX, -1, true>
{};
#  else /* gcc 2.97 (after 2000-11-01), 2.98, 3.0 */
/*
 newest gcc has new mangling scheme, that has problem
 with generating name [instantiated] of template specialization like
 _Integer_limits<_STLP_LONG_LONG, LONGLONG_MIN, LONGLONG_MAX, -1, true>
                                  ~~~~~~~~~~~~  ~~~~~~~~~~~~
 Below is code that solve this problem.
   - ptr
 */
_STLP_TEMPLATE_NULL
class numeric_limits<_STLP_LONG_LONG>
  : public _STLP_PRIV _Numeric_limits_base<_STLP_LONG_LONG> {
public:

  static _STLP_LONG_LONG (_STLP_CALL min) () _STLP_NOTHROW { return LONGLONG_MIN; }
  static _STLP_LONG_LONG (_STLP_CALL max) () _STLP_NOTHROW { return LONGLONG_MAX; }

  _STLP_STATIC_CONSTANT(int, digits = ((int)((sizeof(_STLP_LONG_LONG) * (CHAR_BIT))) - 1));
  _STLP_STATIC_CONSTANT(int, digits10 = (digits * 301UL) / 1000);
  _STLP_STATIC_CONSTANT(int, radix = 2);
  _STLP_STATIC_CONSTANT(bool, is_specialized = true);
  _STLP_STATIC_CONSTANT(bool, is_signed = true);
  _STLP_STATIC_CONSTANT(bool, is_integer = true);
  _STLP_STATIC_CONSTANT(bool, is_exact = true);
  _STLP_STATIC_CONSTANT(bool, is_bounded = true);
  _STLP_STATIC_CONSTANT(bool, is_modulo = true);
};

_STLP_TEMPLATE_NULL
class numeric_limits<unsigned _STLP_LONG_LONG>
  : public _STLP_PRIV _Numeric_limits_base<unsigned _STLP_LONG_LONG> {
public:

  static unsigned _STLP_LONG_LONG (_STLP_CALL min) () _STLP_NOTHROW { return 0ULL; }
  static unsigned _STLP_LONG_LONG (_STLP_CALL max) () _STLP_NOTHROW { return ULONGLONG_MAX; }

  _STLP_STATIC_CONSTANT(int, digits = ((int)((sizeof(unsigned _STLP_LONG_LONG) * (CHAR_BIT)))));
  _STLP_STATIC_CONSTANT(int, digits10 = (digits * 301UL) / 1000);
  _STLP_STATIC_CONSTANT(int, radix = 2);
  _STLP_STATIC_CONSTANT(bool, is_specialized = true);
  _STLP_STATIC_CONSTANT(bool, is_signed = false);
  _STLP_STATIC_CONSTANT(bool, is_integer = true);
  _STLP_STATIC_CONSTANT(bool, is_exact = true);
  _STLP_STATIC_CONSTANT(bool, is_bounded = true);
  _STLP_STATIC_CONSTANT(bool, is_modulo = true);
};

#  endif /* __GNUC__ > 2000-11-01 */

#endif /* _STLP_LONG_LONG */

_STLP_MOVE_TO_PRIV_NAMESPACE

template <class _F, int _N>
struct _Lim
{
};

#  if defined (__GNUC__) || defined (__BORLANDC__) || (defined(__SUNPRO_CC) && (__SUNPRO_CC >= 0x590))
#    define _STLP_ADDITIONAL_OPEN_BRACKET {
#    define _STLP_ADDITIONAL_CLOSE_BRACKET }
#  else
#    define _STLP_ADDITIONAL_OPEN_BRACKET
#    define _STLP_ADDITIONAL_CLOSE_BRACKET
#  endif

template <class _F>
struct _Lim<_F,16>
{
  union _access
  {
    unsigned char b[sizeof(_F)];
    _F    f;
  };

  static _F inf() _STLP_NOTHROW
  {
#  if defined (_STLP_BIG_ENDIAN)
    _access tmp = { _STLP_ADDITIONAL_OPEN_BRACKET 0x7c, 0 _STLP_ADDITIONAL_CLOSE_BRACKET };
#  else /* _STLP_LITTLE_ENDIAN */
    _access tmp = { _STLP_ADDITIONAL_OPEN_BRACKET 0, 0x7c _STLP_ADDITIONAL_CLOSE_BRACKET };
#  endif
    return tmp.f;
  }

  static _F qnan() _STLP_NOTHROW
  {
#  if defined (_STLP_BIG_ENDIAN)
    _access tmp = { _STLP_ADDITIONAL_OPEN_BRACKET 0x7e, 0 _STLP_ADDITIONAL_CLOSE_BRACKET };
#  else /* _STLP_LITTLE_ENDIAN */
    _access tmp = { _STLP_ADDITIONAL_OPEN_BRACKET 0, 0x7e _STLP_ADDITIONAL_CLOSE_BRACKET };
#  endif
    return tmp.f;
  }

  static _F snan() _STLP_NOTHROW
  {
#  if defined (_STLP_BIG_ENDIAN)
    _access tmp = { _STLP_ADDITIONAL_OPEN_BRACKET 0x7d, 0 _STLP_ADDITIONAL_CLOSE_BRACKET };
#  else /* _STLP_LITTLE_ENDIAN */
    _access tmp = { _STLP_ADDITIONAL_OPEN_BRACKET 0, 0x7d _STLP_ADDITIONAL_CLOSE_BRACKET };
#  endif
    return tmp.f;
  }

  static _F denorm_min() _STLP_NOTHROW
  {
#  if defined (_STLP_BIG_ENDIAN)
    _access tmp = { _STLP_ADDITIONAL_OPEN_BRACKET 0, 0x1 _STLP_ADDITIONAL_CLOSE_BRACKET };
#  else /* _STLP_LITTLE_ENDIAN */
    _access tmp = { _STLP_ADDITIONAL_OPEN_BRACKET 0x1, 0 _STLP_ADDITIONAL_CLOSE_BRACKET };
#  endif
    return tmp.f;
  }
};

template <class _F>
struct _Lim<_F,32>
{
  union _access
  {
    unsigned char b[sizeof(_F)];
    _F    f;
  };

  static _F inf() _STLP_NOTHROW
  {
#  if defined (_STLP_BIG_ENDIAN)
    _access tmp = { _STLP_ADDITIONAL_OPEN_BRACKET 0x7f, 0x80, 0, 0 _STLP_ADDITIONAL_CLOSE_BRACKET };
#  else /* _STLP_LITTLE_ENDIAN */
    _access tmp = { _STLP_ADDITIONAL_OPEN_BRACKET 0, 0, 0x80, 0x7f _STLP_ADDITIONAL_CLOSE_BRACKET };
#  endif
    return tmp.f;
  }

  static _F qnan() _STLP_NOTHROW
  {
#  if defined (_STLP_BIG_ENDIAN)
    _access tmp = { _STLP_ADDITIONAL_OPEN_BRACKET 0x7f, 0xc0, 0, 0 _STLP_ADDITIONAL_CLOSE_BRACKET };
#  else /* _STLP_LITTLE_ENDIAN */
    _access tmp = { _STLP_ADDITIONAL_OPEN_BRACKET 0, 0, 0xc0, 0x7f _STLP_ADDITIONAL_CLOSE_BRACKET };
#  endif
    return tmp.f;
  }

  static _F snan() _STLP_NOTHROW
  {
#  if defined (_STLP_BIG_ENDIAN)
    _access tmp = { _STLP_ADDITIONAL_OPEN_BRACKET 0x7f, 0xa0, 0, 0 _STLP_ADDITIONAL_CLOSE_BRACKET };
#  else /* _STLP_LITTLE_ENDIAN */
    _access tmp = { _STLP_ADDITIONAL_OPEN_BRACKET 0, 0, 0xa0, 0x7f _STLP_ADDITIONAL_CLOSE_BRACKET };
#  endif
    return tmp.f;
  }

  static _F denorm_min() _STLP_NOTHROW
  {
#  if defined (_STLP_BIG_ENDIAN)
    _access tmp = { _STLP_ADDITIONAL_OPEN_BRACKET 0, 0, 0, 0x1 _STLP_ADDITIONAL_CLOSE_BRACKET };
#  else /* _STLP_LITTLE_ENDIAN */
    _access tmp = { _STLP_ADDITIONAL_OPEN_BRACKET 0x1, 0, 0, 0 _STLP_ADDITIONAL_CLOSE_BRACKET };
#  endif
    return tmp.f;
  }
};

template <class _F>
struct _Lim<_F,64>
{
  union _access
  {
    unsigned char b[sizeof(_F)];
    _F    f;
  };

  static _F inf() _STLP_NOTHROW
  {
#  if defined (_STLP_BIG_ENDIAN)
    _access tmp = { _STLP_ADDITIONAL_OPEN_BRACKET 0x7f, 0xf0, 0, 0, 0, 0, 0, 0 _STLP_ADDITIONAL_CLOSE_BRACKET };
#  else /* _STLP_LITTLE_ENDIAN */
    _access tmp = { _STLP_ADDITIONAL_OPEN_BRACKET 0, 0, 0, 0, 0, 0, 0xf0, 0x7f _STLP_ADDITIONAL_CLOSE_BRACKET };
#  endif
    return tmp.f;
  }

  static _F qnan() _STLP_NOTHROW
  {
#  if defined (_STLP_BIG_ENDIAN)
    _access tmp = { _STLP_ADDITIONAL_OPEN_BRACKET 0x7f, 0xf8, 0, 0, 0, 0, 0, 0 _STLP_ADDITIONAL_CLOSE_BRACKET };
#  else /* _STLP_LITTLE_ENDIAN */
    _access tmp = { _STLP_ADDITIONAL_OPEN_BRACKET 0, 0, 0, 0, 0, 0, 0xf8, 0x7f _STLP_ADDITIONAL_CLOSE_BRACKET };
#  endif
    return tmp.f;
  }

  static _F snan() _STLP_NOTHROW
  {
#  if defined (_STLP_BIG_ENDIAN)
    _access tmp = { _STLP_ADDITIONAL_OPEN_BRACKET 0x7f, 0xf4, 0, 0, 0, 0, 0, 0 _STLP_ADDITIONAL_CLOSE_BRACKET };
#  else /* _STLP_LITTLE_ENDIAN */
    _access tmp = { _STLP_ADDITIONAL_OPEN_BRACKET 0, 0, 0, 0, 0, 0, 0xf4, 0x7f _STLP_ADDITIONAL_CLOSE_BRACKET };
#  endif
    return tmp.f;
  }

  static _F denorm_min() _STLP_NOTHROW
  {
#  if defined (_STLP_BIG_ENDIAN)
    _access tmp = { _STLP_ADDITIONAL_OPEN_BRACKET 0, 0, 0, 0, 0, 0, 0, 0x1 _STLP_ADDITIONAL_CLOSE_BRACKET };
#  else /* _STLP_LITTLE_ENDIAN */
    _access tmp = { _STLP_ADDITIONAL_OPEN_BRACKET 0x1, 0, 0, 0, 0, 0, 0, 0 _STLP_ADDITIONAL_CLOSE_BRACKET };
#  endif
    return tmp.f;
  }
};

template <class _F>
struct _Lim<_F,80>
{
  union _access
  {
    unsigned char b[sizeof(_F)];
    _F    f;
  };

  static _F inf() _STLP_NOTHROW
  {
#  if defined (_STLP_BIG_ENDIAN)
    _access tmp = { _STLP_ADDITIONAL_OPEN_BRACKET 0x7f, 0xff, 0, 0, 0, 0, 0, 0, 0, 0 _STLP_ADDITIONAL_CLOSE_BRACKET };
#  else /* _STLP_LITTLE_ENDIAN */
#   if defined(__i386__) || defined(__ia64__) || defined(__x86_64__) || defined(_M_IX86) || defined(_M_IA64) || defined(_M_AMD64)
    /* For historical reasons, this format has no implicit/hidden bit: the explicit bit
       was used in the Intel 8087 to suppress the normalization of subnormal numbers in
       certain cases.
     */
    _access tmp = { _STLP_ADDITIONAL_OPEN_BRACKET 0, 0, 0, 0, 0, 0, 0, 0x80, 0xff, 0x7f _STLP_ADDITIONAL_CLOSE_BRACKET };
#   else
    _access tmp = { _STLP_ADDITIONAL_OPEN_BRACKET 0, 0, 0, 0, 0, 0, 0, 0, 0xff, 0x7f _STLP_ADDITIONAL_CLOSE_BRACKET };
#   endif
#  endif
    return tmp.f;
  }

  static _F qnan() _STLP_NOTHROW
  {
#  if defined (_STLP_BIG_ENDIAN)
    _access tmp = { _STLP_ADDITIONAL_OPEN_BRACKET 0x7f, 0xff, 0x80, 0, 0, 0, 0, 0, 0, 0 _STLP_ADDITIONAL_CLOSE_BRACKET };
#  else /* _STLP_LITTLE_ENDIAN */
    _access tmp = { _STLP_ADDITIONAL_OPEN_BRACKET 0, 0, 0, 0, 0, 0, 0, 0x80, 0xff, 0x7f _STLP_ADDITIONAL_CLOSE_BRACKET };
#  endif
    return tmp.f;
  }

  static _F snan() _STLP_NOTHROW
  {
#  if defined (_STLP_BIG_ENDIAN)
    _access tmp = { _STLP_ADDITIONAL_OPEN_BRACKET 0x7f, 0xff, 0x40, 0, 0, 0, 0, 0, 0, 0 _STLP_ADDITIONAL_CLOSE_BRACKET };
#  else /* _STLP_LITTLE_ENDIAN */
    _access tmp = { _STLP_ADDITIONAL_OPEN_BRACKET 0, 0, 0, 0, 0, 0, 0, 0x40, 0xff, 0x7f _STLP_ADDITIONAL_CLOSE_BRACKET };
#  endif
    return tmp.f;
  }

  static _F denorm_min() _STLP_NOTHROW
  {
#  if defined (_STLP_BIG_ENDIAN)
    _access tmp = { _STLP_ADDITIONAL_OPEN_BRACKET 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x1 _STLP_ADDITIONAL_CLOSE_BRACKET };
#  else /* _STLP_LITTLE_ENDIAN */
    _access tmp = { _STLP_ADDITIONAL_OPEN_BRACKET 0x1, 0, 0, 0, 0, 0, 0, 0, 0, 0 _STLP_ADDITIONAL_CLOSE_BRACKET };
#  endif
    return tmp.f;
  }
};

template <class _F>
struct _Lim<_F,96>
{
  union _access
  {
    unsigned char b[sizeof(_F)];
    _F    f;
  };

  static _F inf() _STLP_NOTHROW
  {
#  if defined (_STLP_BIG_ENDIAN)
    _access tmp = { _STLP_ADDITIONAL_OPEN_BRACKET 0x7f, 0xff, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 _STLP_ADDITIONAL_CLOSE_BRACKET };
#  else /* _STLP_LITTLE_ENDIAN */
#   if defined(__i386__) || defined(__ia64__) || defined(__x86_64__) || defined(_M_IX86) || defined(_M_IA64) || defined(_M_AMD64)
    /* This is same format as 80-bits above, just take into account alignment (padded
       by empty bytes).
       For historical reasons, this format has no implicit/hidden bit: the explicit bit
       was used in the Intel 8087 to suppress the normalization of subnormal numbers in
       certain cases.
     */
    _access tmp = { _STLP_ADDITIONAL_OPEN_BRACKET 0, 0, 0, 0, 0, 0, 0, 0x80, 0xff, 0x7f, 0, 0 _STLP_ADDITIONAL_CLOSE_BRACKET };
#   else
    _access tmp = { _STLP_ADDITIONAL_OPEN_BRACKET 0, 0, 0, 0, 0, 0, 0, 0, 0xff, 0x7f, 0, 0 _STLP_ADDITIONAL_CLOSE_BRACKET };
#   endif
#  endif
    return tmp.f;
  }

  static _F qnan() _STLP_NOTHROW
  {
#  if defined (_STLP_BIG_ENDIAN)
    _access tmp = { _STLP_ADDITIONAL_OPEN_BRACKET 0x7f, 0xff, 0, 0, 0xc0, 0, 0, 0, 0, 0, 0, 0 _STLP_ADDITIONAL_CLOSE_BRACKET };
#  else /* _STLP_LITTLE_ENDIAN */
    _access tmp = { _STLP_ADDITIONAL_OPEN_BRACKET 0, 0, 0, 0, 0, 0, 0, 0xc0, 0xff, 0x7f, 0, 0 _STLP_ADDITIONAL_CLOSE_BRACKET };
#  endif
    return tmp.f;
  }

  static _F snan() _STLP_NOTHROW
  {
#  if defined (_STLP_BIG_ENDIAN)
    _access tmp = { _STLP_ADDITIONAL_OPEN_BRACKET 0x7f, 0xff, 0, 0, 0xa0, 0, 0, 0, 0, 0, 0, 0 _STLP_ADDITIONAL_CLOSE_BRACKET };
#  else /* _STLP_LITTLE_ENDIAN */
    _access tmp = { _STLP_ADDITIONAL_OPEN_BRACKET 0, 0, 0, 0, 0, 0, 0, 0xa0, 0xff, 0x7f, 0, 0 _STLP_ADDITIONAL_CLOSE_BRACKET };
#  endif
    return tmp.f;
  }

  static _F denorm_min() _STLP_NOTHROW
  {
#  if defined (_STLP_BIG_ENDIAN)
    _access tmp = { _STLP_ADDITIONAL_OPEN_BRACKET 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x1 _STLP_ADDITIONAL_CLOSE_BRACKET };
#  else /* _STLP_LITTLE_ENDIAN */
    _access tmp = { _STLP_ADDITIONAL_OPEN_BRACKET 0x1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 _STLP_ADDITIONAL_CLOSE_BRACKET };
#  endif
    return tmp.f;
  }
};

template <class _F>
struct _Lim<_F,128>
{
  union _access
  {
    unsigned char b[sizeof(_F)];
    _F             f;
  };

  static _F inf() _STLP_NOTHROW
  {
#  if defined (_STLP_BIG_ENDIAN)
    _access tmp = { _STLP_ADDITIONAL_OPEN_BRACKET 0x7f, 0xff, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 _STLP_ADDITIONAL_CLOSE_BRACKET };
#  else /* _STLP_LITTLE_ENDIAN */
    _access tmp = { _STLP_ADDITIONAL_OPEN_BRACKET 0, 0, 0, 0, 0, 0, 0, 0, 0xff, 0x7f, 0, 0, 0, 0, 0, 0 _STLP_ADDITIONAL_CLOSE_BRACKET };
#  endif
    return tmp.f;
  }

  static _F qnan() _STLP_NOTHROW
  {
#  if defined (_STLP_BIG_ENDIAN)
    _access tmp = { _STLP_ADDITIONAL_OPEN_BRACKET 0x7f, 0xff, 0, 0, 0, 0, 0xc0, 0, 0, 0, 0, 0, 0, 0, 0, 0 _STLP_ADDITIONAL_CLOSE_BRACKET };
#  else /* _STLP_LITTLE_ENDIAN */
    _access tmp = { _STLP_ADDITIONAL_OPEN_BRACKET 0, 0, 0, 0, 0, 0, 0, 0xc0, 0xff, 0x7f, 0, 0, 0, 0, 0, 0 _STLP_ADDITIONAL_CLOSE_BRACKET };
#  endif
    return tmp.f;
  }

  static _F snan() _STLP_NOTHROW
  {
#  if defined (_STLP_BIG_ENDIAN)
    _access tmp = { _STLP_ADDITIONAL_OPEN_BRACKET 0x7f, 0xff, 0, 0, 0, 0, 0xa0, 0, 0, 0, 0, 0, 0, 0, 0, 0 _STLP_ADDITIONAL_CLOSE_BRACKET };
#  else /* _STLP_LITTLE_ENDIAN */
    _access tmp = { _STLP_ADDITIONAL_OPEN_BRACKET 0, 0, 0, 0, 0, 0, 0, 0xa0, 0xff, 0x7f, 0, 0, 0, 0, 0, 0 _STLP_ADDITIONAL_CLOSE_BRACKET };
#  endif
    return tmp.f;
  }

  static _F denorm_min() _STLP_NOTHROW
  {
#  if defined (_STLP_BIG_ENDIAN)
    _access tmp = { _STLP_ADDITIONAL_OPEN_BRACKET 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x1, 0, 0 _STLP_ADDITIONAL_CLOSE_BRACKET };
#  else /* _STLP_LITTLE_ENDIAN */
    _access tmp = { _STLP_ADDITIONAL_OPEN_BRACKET 0x1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 _STLP_ADDITIONAL_CLOSE_BRACKET };
#  endif
    return tmp.f;
  }
};

#undef _STLP_ADDITIONAL_OPEN_BRACKET
#undef _STLP_ADDITIONAL_CLOSE_BRACKET

#if defined (__TASKING__)
/* TASKING C compilers do not support denormalized floating point numbers. */
#  define _STLP_FLT_DENORM_STYLE denorm_absent
#  define _STLP_DBL_DENORM_STYLE denorm_absent
#  define _STLP_LDBL_DENORM_STYLE denorm_absent
#elif defined (__GNUC__)
#  if defined (__FLT_DENORM_MIN__)
#    define _STLP_FLT_DENORM_MIN __FLT_DENORM_MIN__
#  else
#    define _STLP_FLT_DENORM_STYLE denorm_absent
#  endif
#  if defined (__DBL_DENORM_MIN__)
#    define _STLP_DBL_DENORM_MIN __DBL_DENORM_MIN__
#  else
#    define _STLP_DBL_DENORM_STYLE denorm_absent
#  endif
#  if defined (__LDBL_DENORM_MIN__)
#    define _STLP_LDBL_DENORM_MIN __LDBL_DENORM_MIN__
#  else
#    define _STLP_LDBL_DENORM_STYLE denorm_absent
#  endif
#endif

/* If compiler do not expose thanks to some macro its status regarding
 * denormalized floating point numbers, we consider that denormalization
 * is present. Unit tests will tell us if compiler do not support them. */
#if !defined (_STLP_FLT_DENORM_STYLE)
#  define _STLP_FLT_DENORM_STYLE denorm_present
#endif

#if !defined (_STLP_DBL_DENORM_STYLE)
#  define _STLP_DBL_DENORM_STYLE denorm_present
#endif

#if !defined (_STLP_LDBL_DENORM_STYLE)
#  define _STLP_LDBL_DENORM_STYLE denorm_present
#endif

_STLP_MOVE_TO_STD_NAMESPACE

_STLP_TEMPLATE_NULL
class numeric_limits<float> :
    public _STLP_PRIV _Floating_limits<float,
                                       FLT_MANT_DIG,   // Binary digits of precision
                                       FLT_DIG,        // Decimal digits of precision
                                       FLT_MIN_EXP,    // Minimum exponent
                                       FLT_MAX_EXP,    // Maximum exponent
                                       FLT_MIN_10_EXP, // Minimum base 10 exponent
                                       FLT_MAX_10_EXP, // Maximum base 10 exponent
                                       true,
                                       _STLP_FLT_DENORM_STYLE,
                                       round_to_nearest>
{
  public:
    static float (_STLP_CALL min) () _STLP_NOTHROW { return FLT_MIN; }
    static float _STLP_CALL denorm_min() _STLP_NOTHROW
      {
#if defined (_STLP_FLT_DENORM_MIN)
        return _STLP_FLT_DENORM_MIN;
#else
        return _STLP_FLT_DENORM_STYLE ? _STLP_PRIV _Lim<float,sizeof(float)<<3>::denorm_min() : FLT_MIN;
#endif
      }
    static float (_STLP_CALL max) () _STLP_NOTHROW
      { return FLT_MAX; }
    static float _STLP_CALL epsilon() _STLP_NOTHROW
      { return FLT_EPSILON; }
    static float _STLP_CALL round_error() _STLP_NOTHROW
      { return 0.5f; } // Units: ulps.
    static float _STLP_CALL infinity() _STLP_NOTHROW
      { return _STLP_PRIV _Lim<float,sizeof(float)<<3>::inf(); }
    static float _STLP_CALL quiet_NaN() _STLP_NOTHROW 
      { return _STLP_PRIV _Lim<float,sizeof(float)<<3>::qnan(); }
    static float _STLP_CALL signaling_NaN() _STLP_NOTHROW
      { return _STLP_PRIV _Lim<float,sizeof(float)<<3>::snan(); }
};

#undef _STLP_FLT_DENORM_MIN
#undef _STLP_FLT_DNORM_STYLE

_STLP_TEMPLATE_NULL
class numeric_limits<double> :
    public _STLP_PRIV _Floating_limits<double,
                                       DBL_MANT_DIG,   // Binary digits of precision
                                       DBL_DIG,        // Decimal digits of precision
                                       DBL_MIN_EXP,    // Minimum exponent
                                       DBL_MAX_EXP,    // Maximum exponent
                                       DBL_MIN_10_EXP, // Minimum base 10 exponent
                                       DBL_MAX_10_EXP, // Maximum base 10 exponent
                                       true,
                                       _STLP_DBL_DENORM_STYLE,
                                       round_to_nearest>
{
  public:
    static double (_STLP_CALL min)() _STLP_NOTHROW
      { return DBL_MIN; }
    static double _STLP_CALL denorm_min() _STLP_NOTHROW
      {
#if defined (_STLP_DBL_DENORM_MIN)
        return _STLP_DBL_DENORM_MIN;
#else
        return _STLP_DBL_DENORM_STYLE ? _STLP_PRIV _Lim<double,sizeof(double)<<3>::denorm_min() : DBL_MIN;
#endif
      }
    static double (_STLP_CALL max)() _STLP_NOTHROW
      { return DBL_MAX; }
    static double _STLP_CALL epsilon() _STLP_NOTHROW
      { return DBL_EPSILON; }
    static double _STLP_CALL round_error() _STLP_NOTHROW
      { return 0.5; } // Units: ulps.
    static double _STLP_CALL infinity() _STLP_NOTHROW
      { return _STLP_PRIV _Lim<double,sizeof(double)<<3>::inf(); }
    static double _STLP_CALL quiet_NaN() _STLP_NOTHROW
      { return _STLP_PRIV _Lim<double,sizeof(double)<<3>::qnan(); }
    static double _STLP_CALL signaling_NaN() _STLP_NOTHROW
      { return _STLP_PRIV _Lim<double,sizeof(double)<<3>::snan(); }
};

#if !defined (_STLP_NO_LONG_DOUBLE)

_STLP_TEMPLATE_NULL
class numeric_limits<long double> :
    public _STLP_PRIV _Floating_limits<long double,
                                       LDBL_MANT_DIG,  // Binary digits of precision
                                       LDBL_DIG,       // Decimal digits of precision
                                       LDBL_MIN_EXP,   // Minimum exponent
                                       LDBL_MAX_EXP,   // Maximum exponent
                                       LDBL_MIN_10_EXP,// Minimum base 10 exponent
                                       LDBL_MAX_10_EXP,// Maximum base 10 exponent
                                       false,          // do not conform to iec559
                                       _STLP_LDBL_DENORM_STYLE,
                                       round_to_nearest>
{
  public:
    static long double (_STLP_CALL min) () _STLP_NOTHROW
      { return LDBL_MIN; }
    static long double _STLP_CALL denorm_min() _STLP_NOTHROW
      {
#if defined (_STLP_LDBL_DENORM_MIN)
        return _STLP_LDBL_DENORM_MIN;
#else
        return _STLP_LDBL_DENORM_STYLE ? _STLP_PRIV _Lim<long double,sizeof(long double)<<3>::denorm_min() : LDBL_MIN;
#endif
      }
    _STLP_STATIC_CONSTANT(bool, is_iec559 = false);
    static long double (_STLP_CALL max) () _STLP_NOTHROW
      { return LDBL_MAX; }
    static long double _STLP_CALL epsilon() _STLP_NOTHROW
      { return LDBL_EPSILON; }
    static long double _STLP_CALL round_error() _STLP_NOTHROW
      { return 0.5l; }
    static long double _STLP_CALL infinity() _STLP_NOTHROW
      {
        return _STLP_PRIV _Lim<long double,sizeof(long double)<<3>::inf();
      }
    static long double _STLP_CALL quiet_NaN() _STLP_NOTHROW
      { return _STLP_PRIV _Lim<long double,sizeof(long double)<<3>::qnan(); }
    static long double _STLP_CALL signaling_NaN() _STLP_NOTHROW
      { return _STLP_PRIV _Lim<long double,sizeof(long double)<<3>::snan(); }
};

#endif

// We write special values (Inf and NaN) as bit patterns and
// cast the the appropriate floating-point types.
_STLP_END_NAMESPACE

#if !defined (_STLP_LINK_TIME_INSTANTIATION)
#  include <stl/_limits.c>
#endif

#endif

// Local Variables:
// mode:C++
// End:
