

/*
 *
 * Copyright (c) 1994
 * Hewlett-Packard Company
 *
 * Copyright (c) 1996,1997
 * Silicon Graphics Computer Systems, Inc.
 *
 * Copyright (c) 1997
 * Moscow Center for SPARC Technology
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

/* NOTE: This is an internal header file, included by other STL headers.
 *   You should not attempt to use it directly.
 */

#ifndef _STLP_INTERNAL_QUEUE_H
#define _STLP_INTERNAL_QUEUE_H

#ifndef _STLP_INTERNAL_DEQUE_H
#  include <stl/_deque.h>
#endif

#ifndef _STLP_INTERNAL_VECTOR_H
# include <stl/_vector.h>
#endif

#ifndef _STLP_INTERNAL_HEAP_H
#  include <stl/_heap.h>
#endif

#ifndef _STLP_INTERNAL_FUNCTION_BASE_H
#  include <stl/_function_base.h>
#endif

_STLP_BEGIN_NAMESPACE

# if ! defined ( _STLP_LIMITED_DEFAULT_TEMPLATES )
template <class _Tp, class _Sequence = deque<_Tp> >
# elif defined ( _STLP_MINIMUM_DEFAULT_TEMPLATE_PARAMS )
#  define _STLP_QUEUE_ARGS _Tp
template <class _Tp>
# else
template <class _Tp, class _Sequence>
# endif
class queue
{
# if defined ( _STLP_QUEUE_ARGS )
  typedef deque<_Tp> _Sequence;
  typedef queue<_Tp> _Self;
# else
  typedef queue<_Tp, _Sequence> _Self;
# endif
public:
  typedef typename _Sequence::value_type      value_type;
  typedef typename _Sequence::size_type       size_type;
  typedef          _Sequence                  container_type;

  typedef typename _Sequence::reference       reference;
  typedef typename _Sequence::const_reference const_reference;

protected:
  //c is a Standard name (23.2.3.1), do no make it STLport naming convention compliant.
  _Sequence c;
public:
  queue() : c() {}
  explicit queue(const _Sequence& __c) : c(__c) {}

#if !defined (_STLP_NO_MOVE_SEMANTIC)
  queue(__move_source<_Self> src) :
      c(src.get().c)
    { }
#endif

  bool empty() const { return c.empty(); }
  size_type size() const { return c.size(); }
  reference front() { return c.front(); }
  const_reference front() const { return c.front(); }
  reference back() { return c.back(); }
  const_reference back() const { return c.back(); }
  void push(const value_type& __x) { c.push_back(__x); }
  void pop() { c.pop_front(); }
  const _Sequence& _Get_s() const { return c; }

#if defined (_STLP_USE_PARTIAL_SPEC_WORKAROUND) && !defined (_STLP_FUNCTION_TMPL_PARTIAL_ORDER)
  void _M_swap_workaround(_Self& __x) {
    _Sequence __tmp = c;
    c = __x.c;
    __x.c = __tmp;
  }
#endif
};

#ifndef _STLP_QUEUE_ARGS
#  define _STLP_QUEUE_ARGS _Tp, _Sequence
#  define _STLP_QUEUE_HEADER_ARGS class _Tp, class _Sequence
#else
#  define _STLP_QUEUE_HEADER_ARGS class _Tp
#endif

template < _STLP_QUEUE_HEADER_ARGS >
inline bool _STLP_CALL
operator==(const queue<_STLP_QUEUE_ARGS >& __x, const queue<_STLP_QUEUE_ARGS >& __y) {
  return __x._Get_s() == __y._Get_s();
}

template < _STLP_QUEUE_HEADER_ARGS >
inline bool _STLP_CALL
operator<(const queue<_STLP_QUEUE_ARGS >& __x, const queue<_STLP_QUEUE_ARGS >& __y) {
  return __x._Get_s() < __y._Get_s();
}

_STLP_RELOPS_OPERATORS( template < _STLP_QUEUE_HEADER_ARGS >, queue<_STLP_QUEUE_ARGS > )

# if !(defined ( _STLP_LIMITED_DEFAULT_TEMPLATES ) || defined ( _STLP_TEMPLATE_PARAM_SUBTYPE_BUG ))
template <class _Tp, class _Sequence = vector<_Tp>,
          class _Compare = less<_STLP_HEADER_TYPENAME _Sequence::value_type> >
# elif defined ( _STLP_MINIMUM_DEFAULT_TEMPLATE_PARAMS )
template <class _Tp>
# else
template <class _Tp, class _Sequence, class _Compare>
# endif
class priority_queue
{
# ifdef _STLP_MINIMUM_DEFAULT_TEMPLATE_PARAMS
  typedef vector<_Tp> _Sequence;
  typedef less< typename vector<_Tp>::value_type> _Compare;
  typedef priority_queue<_Tp> _Self;
# else
  typedef priority_queue<_Tp, _Sequence, _Compare> _Self;
# endif
public:
  typedef typename _Sequence::value_type      value_type;
  typedef typename _Sequence::size_type       size_type;
  typedef          _Sequence                  container_type;

  typedef typename _Sequence::reference       reference;
  typedef typename _Sequence::const_reference const_reference;
protected:
  //c is a Standard name (23.2.3.2), do no make it STLport naming convention compliant.
  _Sequence c;
  _Compare comp;
public:
  priority_queue() : c() {}
  explicit priority_queue(const _Compare& __x) :  c(), comp(__x) {}
  priority_queue(const _Compare& __x, const _Sequence& __s)
    : c(__s), comp(__x)
    { make_heap(c.begin(), c.end(), comp); }

#if !defined (_STLP_NO_MOVE_SEMANTIC)
  priority_queue(__move_source<_Self> src) :
      c(src.get().c),
      comp(src.get().comp)
    { }
#endif

  template <class _InputIterator>
  priority_queue(_InputIterator __first, _InputIterator __last)
    : c(__first, __last) { make_heap(c.begin(), c.end(), comp); }

  template <class _InputIterator>
  priority_queue(_InputIterator __first,
                 _InputIterator __last, const _Compare& __x)
    : c(__first, __last), comp(__x)
    { make_heap(c.begin(), c.end(), comp); }

  template <class _InputIterator>
  priority_queue(_InputIterator __first, _InputIterator __last,
                 const _Compare& __x, const _Sequence& __s)
  : c(__s), comp(__x)
  {
    c.insert(c.end(), __first, __last);
    make_heap(c.begin(), c.end(), comp);
  }

  bool empty() const { return c.empty(); }
  size_type size() const { return c.size(); }
  const_reference top() const { return c.front(); }
  void push(const value_type& __x) {
    _STLP_TRY {
      c.push_back(__x);
      push_heap(c.begin(), c.end(), comp);
    }
    _STLP_UNWIND(c.clear())
  }
  void pop() {
    _STLP_TRY {
      pop_heap(c.begin(), c.end(), comp);
      c.pop_back();
    }
    _STLP_UNWIND(c.clear())
  }

  // To do: _Sequence must be swappable
  void swap( priority_queue& r )
    {
      _STLP_STD::swap( comp, r.comp );
      _STLP_STD::swap( c, r.c );
    }
#if defined (_STLP_USE_PARTIAL_SPEC_WORKAROUND) && !defined (_STLP_FUNCTION_TMPL_PARTIAL_ORDER)
  void _M_swap_workaround(_Self& __x) {
    _Sequence __tmp = c;
    c = __x.c;
    __x.c = __tmp;
  }
#endif
};

template <class _Tp, class _Sequence, class _Compare >
inline void swap( priority_queue<_Tp,_Sequence,_Compare>& l, priority_queue<_Tp,_Sequence,_Compare>& r )
{
  l.swap( r );
}

#if defined (_STLP_CLASS_PARTIAL_SPECIALIZATION) && !defined (_STLP_NO_MOVE_SEMANTIC)
_STLP_BEGIN_TR1_NAMESPACE

template <class _Tp, class _Sequence>
struct __has_trivial_move<queue<_Tp, _Sequence> > :
  public integral_constant<bool, __has_trivial_move<_Sequence>::value>
{ };

template <class _Tp, class _Sequence>
struct __has_move_constructor<queue<_Tp, _Sequence> > :
    public integral_constant<bool, __has_move_constructor<_Sequence>::value>
{ };

template <class _Tp, class _Sequence, class _Compare>
struct __has_trivial_move<priority_queue<_Tp, _Sequence, _Compare> > :
  public integral_constant<bool, __has_trivial_move<_Sequence>::value && __has_trivial_move<_Compare>::value>
{ };

template <class _Tp, class _Sequence, class _Compare>
struct __has_move_constructor<priority_queue<_Tp, _Sequence, _Compare> > :
    public integral_constant<bool, __has_move_constructor<_Sequence>::value && __has_move_constructor<_Compare>::value>
{ };

_STLP_END_NAMESPACE
#endif /* _STLP_CLASS_PARTIAL_SPECIALIZATION */

_STLP_END_NAMESPACE

#undef _STLP_QUEUE_ARGS
#undef _STLP_QUEUE_HEADER_ARGS
#undef comp

#endif /* _STLP_INTERNAL_QUEUE_H */

// Local Variables:
// mode:C++
// End:
