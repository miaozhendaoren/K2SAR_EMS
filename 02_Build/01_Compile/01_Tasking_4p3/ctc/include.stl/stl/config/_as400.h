

// STLport configuration file
// It is internal STLport header - DO NOT include it directly

// AS/400 C++ config

# ifdef _REENTRANT
#  define _PTHREADS
# endif

#  define _STLP_NO_NEW_NEW_HEADER 1

#  define _STLP_NO_BOOL
#  define _STLP_LIMITED_DEFAULT_TEMPLATES

#  define _STLP_HAS_NO_NAMESPACES
#  define _STLP_NEED_TYPENAME
#  define _STLP_NEED_EXPLICIT
#  define _STLP_HAS_NO_EXCEPTIONS
#  define _STLP_NO_EXCEPTION_SPEC
#  define _STLP_NO_ARROW_OPERATOR // Unsupported more
#  define _STLP_NO_NEW_STYLE_CASTS

#  define _STLP_NEED_MUTABLE
#  define _STLP_NO_PARTIAL_SPECIALIZATION_SYNTAX
#  define _STLP_NO_BAD_ALLOC
#  define _STLP_NO_MEMBER_TEMPLATES
#  define _STLP_NO_MEMBER_TEMPLATE_CLASSES
#  define _STLP_NO_MEMBER_TEMPLATE_KEYWORD
#  define _STLP_NO_QUALIFIED_FRIENDS
#  define _STLP_NO_CLASS_PARTIAL_SPECIALIZATION
#  define _STLP_NO_FUNCTION_TMPL_PARTIAL_ORDER

#  define _STLP_NO_METHOD_SPECIALIZATION
#  define _STLP_NO_EXPLICIT_FUNCTION_TMPL_ARGS

// #  define _STLP_NO_EXCEPTION_HEADER

#  define _STLP_HAS_NO_NEW_C_HEADERS

#  define _STLP_STATIC_CONST_INIT_BUG
#  define _STLP_THROW_RETURN_BUG
#  define _STLP_LINK_TIME_INSTANTIATION
#  define _STLP_NO_TEMPLATE_CONVERSIONS /* support removed */

#  define _STLP_NON_TYPE_TMPL_PARAM_BUG 1
#  define _STLP_TRIVIAL_DESTRUCTOR_BUG  1

#  if defined(_LONG_LONG)
#    define _STLP_LONG_LONG long long
#  endif
#  if defined(_PTHREADS)
#    define _MULTI_THREADED
#  endif
// fbp : to fix __partition() problem
# define _STLP_NONTEMPL_BASE_MATCH_BUG 1
