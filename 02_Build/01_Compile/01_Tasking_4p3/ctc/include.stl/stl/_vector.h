

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

#ifndef _STLP_INTERNAL_VECTOR_H
#define _STLP_INTERNAL_VECTOR_H

#ifndef _STLP_INTERNAL_ALGOBASE_H
#  include <stl/_algobase.h>
#endif

#ifndef _STLP_INTERNAL_ALLOC_H
#  include <stl/_alloc.h>
#endif

#ifndef _STLP_INTERNAL_ITERATOR_H
#  include <stl/_iterator.h>
#endif

#ifndef _STLP_INTERNAL_UNINITIALIZED_H
#  include <stl/_uninitialized.h>
#endif

#ifndef _STLP_TYPE_TRAITS
#  include <type_traits>
#endif

_STLP_BEGIN_NAMESPACE

// The vector base class serves one purpose, its constructor and
// destructor allocate (but don't initialize) storage.  This makes
// exception safety easier.

_STLP_MOVE_TO_PRIV_NAMESPACE

template <class _Tp, class _Alloc>
class _Vector_base
{
  public:
    typedef _Vector_base<_Tp, _Alloc> _Self;
    _STLP_FORCE_ALLOCATORS(_Tp, _Alloc)
    typedef _Alloc allocator_type;
    typedef _Tp* pointer;
    typedef _STLP_alloc_proxy<pointer, _Tp, allocator_type> _AllocProxy;

    _Vector_base(const _Alloc& __a) 
        : _M_start(0),
          _M_finish(0),
          _M_end_of_storage(__a, 0)
      { }

    _Vector_base(size_t __n, const _Alloc& __a) :
        _M_start(0),
        _M_finish(0),
        _M_end_of_storage(__a, 0)
      {
        _M_start = _M_end_of_storage.allocate(__n);
        _M_finish = _M_start;
        _M_end_of_storage._M_data = _M_start + __n;
        _STLP_MPWFIX_TRY _STLP_MPWFIX_CATCH
      }

#if !defined (_STLP_NO_MOVE_SEMANTIC)
    _Vector_base( __move_source<_Self> src ) :
        _M_start(src.get()._M_start),
        _M_finish(src.get()._M_finish),
        _M_end_of_storage(__move_source<_AllocProxy>(src.get()._M_end_of_storage))
      {
        //Set the source as empty:
        src.get()._M_finish = src.get()._M_end_of_storage._M_data = src.get()._M_start = 0;
      }
#endif

    ~_Vector_base()
      {
        if (_M_start != _STLP_DEFAULT_CONSTRUCTED(pointer)) {
          _M_end_of_storage.deallocate(_M_start, _M_end_of_storage._M_data - _M_start);
        }
      }

  protected:
    void _STLP_FUNCTION_THROWS _M_throw_length_error() const;
    void _STLP_FUNCTION_THROWS _M_throw_out_of_range() const;

    pointer _M_start;
    pointer _M_finish;
    _AllocProxy _M_end_of_storage;
};

#if defined (_STLP_USE_PTR_SPECIALIZATIONS)
#  define vector _STLP_PTR_IMPL_NAME(vector)
#elif defined (_STLP_DEBUG)
#  define vector _STLP_NON_DBG_NAME(vector)
#else
_STLP_MOVE_TO_STD_NAMESPACE
#endif

template <class _Tp, _STLP_DFL_TMPL_PARAM(_Alloc, allocator<_Tp>) >
class vector :
    protected _STLP_PRIV _Vector_base<_Tp, _Alloc>
{
  private:
    typedef _STLP_PRIV _Vector_base<_Tp, _Alloc> _Base;
    typedef vector<_Tp, _Alloc> _Self;
  public:
    _STLP_FORCE_ALLOCATORS(_Tp, _Alloc)
    typedef typename _Base::allocator_type allocator_type;

    typedef _Tp value_type;
    typedef value_type* pointer;
    typedef const value_type* const_pointer;
    typedef value_type* iterator;
    typedef const value_type* const_iterator;

    typedef value_type& reference;
    typedef const value_type& const_reference;
    typedef size_t size_type;
    typedef ptrdiff_t difference_type;
    typedef random_access_iterator_tag _Iterator_category;

    _STLP_DECLARE_RANDOM_ACCESS_REVERSE_ITERATORS;

    allocator_type get_allocator() const
      { return (const allocator_type&)this->_M_end_of_storage; }

  private:
#if defined (_STLP_NO_MOVE_SEMANTIC)
    typedef false_type _Movable;
#endif

    // handles insertions on overflow
    void _M_insert_overflow( pointer __pos, const _Tp& __x, const false_type& /* trivial move */,
                             size_type __fill_len, bool __atend = false);
    void _M_insert_overflow( pointer __pos, const _Tp& __x, const true_type& /* trivial move */,
                             size_type __fill_len, bool __atend = false);
    void _M_range_check(size_type __n) const
      {
        if (__n >= size_type(this->_M_finish - this->_M_start)) {
          this->_M_throw_out_of_range();
        }
      }

    size_type _M_compute_next_size( size_type __n )
      {
        const size_type __size = size();
        if (__n > max_size() - __size) {
          this->_M_throw_length_error();
        }
        size_type __len = __size + (max)(__n, __size);
        if (__len > max_size() || __len < __size) {
          __len = max_size(); // overflow
        }
        return __len;
      }

  public:
    iterator begin()
      { return this->_M_start; }
    const_iterator begin() const
      { return this->_M_start; }
    iterator end()
      { return this->_M_finish; }
    const_iterator end() const
      { return this->_M_finish; }

    reverse_iterator rbegin()
      { return reverse_iterator(end()); }
    const_reverse_iterator rbegin() const
      { return const_reverse_iterator(end()); }
    reverse_iterator rend()
      { return reverse_iterator(begin()); }
    const_reverse_iterator rend() const
      { return const_reverse_iterator(begin()); }

    size_type size() const
      { return size_type(this->_M_finish - this->_M_start); }
    size_type max_size() const
      {
        size_type __vector_max_size = size_type(-1) / sizeof(_Tp);
        typename allocator_type::size_type __alloc_max_size = this->_M_end_of_storage.max_size();
        return (__alloc_max_size < __vector_max_size)?__alloc_max_size:__vector_max_size;
      }

    size_type capacity() const
      { return size_type(this->_M_end_of_storage._M_data - this->_M_start); }
    bool empty() const
      { return this->_M_start == this->_M_finish; }

    reference operator[]( size_type __n )
      { return *(begin() + __n); }
    const_reference operator[]( size_type __n ) const
      { return *(begin() + __n); }

    reference front()
      { return *begin(); }
    const_reference front() const
      { return *begin(); }
    reference back()
      { return *(end() - 1); }
    const_reference back() const
      { return *(end() - 1); }

    reference at( size_type __n )
      { _M_range_check(__n); return (*this)[__n]; }
    const_reference at(size_type __n) const
      { _M_range_check(__n); return (*this)[__n]; }

    explicit vector(const allocator_type& __a = allocator_type()) :
        _STLP_PRIV _Vector_base<_Tp, _Alloc>(__a)
      { }

  private:
    //We always call _M_initialize with only 1 parameter. Default parameter
    //is used to allow explicit instanciation of vector with types with no
    //default constructor.
    void _M_initialize( size_type __n, const _Tp& __val = _STLP_DEFAULT_CONSTRUCTED(_Tp) )
      { this->_M_finish = _STLP_PRIV __uninitialized_init(this->_M_start, __n, __val); }

  public:
    explicit vector(size_type __n) :
        _STLP_PRIV _Vector_base<_Tp, _Alloc>( __n, allocator_type() )
      { _M_initialize(__n); }
    vector( size_type __n, const _Tp& __val, const allocator_type& __a = allocator_type() ) :
        _STLP_PRIV _Vector_base<_Tp, _Alloc>(__n, __a)
      { this->_M_finish = _STLP_PRIV __uninitialized_fill_n(this->_M_start, __n, __val); }

    vector(const _Self& __x) :
        _STLP_PRIV _Vector_base<_Tp, _Alloc>(__x.size(), __x.get_allocator())
      {
        typedef typename has_trivial_copy_constructor<_Tp>::type _TrivialUCopy;
        this->_M_finish = _STLP_PRIV __ucopy_ptrs(__x.begin(), __x.end(), this->_M_start, _TrivialUCopy());
      }

#if !defined (_STLP_NO_MOVE_SEMANTIC)
  vector(__move_source<_Self> src) :
        _STLP_PRIV _Vector_base<_Tp, _Alloc>(__move_source<_Base>(src.get()))
      { }
#endif

  private:
    template <class _Integer>
    void _M_initialize_aux( _Integer __n, _Integer __val, const true_type& /*_IsIntegral*/ )
      {
        size_type __real_n = ((__n + sizeof(_Integer) * 8 - 1) & ~(sizeof(_Integer) * 8 - 1));
        this->_M_start = this->_M_end_of_storage.allocate(__real_n);
        this->_M_end_of_storage._M_data = this->_M_start + __real_n;
        this->_M_finish = _STLP_PRIV __uninitialized_fill_n(this->_M_start, __n, __val);
      }

    template <class _InputIterator>
    void _M_initialize_aux( _InputIterator __first, _InputIterator __last,
                            const false_type& /*_IsIntegral*/ )
      { _M_range_initialize(__first, __last, _STLP_ITERATOR_CATEGORY(__first, _InputIterator)); }

  public:
    // Check whether it's an integral type.  If so, it's not an iterator.
    template <class _InputIterator>
    vector( _InputIterator __first, _InputIterator __last,
            const allocator_type& __a _STLP_ALLOCATOR_TYPE_DFL ) :
        _STLP_PRIV _Vector_base<_Tp, _Alloc>(__a)
      {
        typedef typename is_integral<_InputIterator>::type _Integral;
        _M_initialize_aux(__first, __last, _Integral());
      }

#  if defined (_STLP_NEEDS_EXTRA_TEMPLATE_CONSTRUCTORS)
    template <class _InputIterator>
    vector( _InputIterator __first, _InputIterator __last) :
        _STLP_PRIV _Vector_base<_Tp, _Alloc>(allocator_type())
      {
        typedef typename is_integral<_InputIterator>::type _Integral;
        _M_initialize_aux(__first, __last, _Integral());
      }
#  endif /* _STLP_NEEDS_EXTRA_TEMPLATE_CONSTRUCTORS */

    //As the vector container is a back insert oriented container it
    //seems rather logical to destroy elements in reverse order.
    ~vector() { _STLP_STD::_Destroy_Range(rbegin(), rend()); }

    _Self& operator=(const _Self& __x);

    void reserve(size_type __n);

    // assign(), a generalized assignment member function.  Two
    // versions: one that takes a count, and one that takes a range.
    // The range version is a member template, so we dispatch on whether
    // or not the type is an integer.

    void assign(size_type __n, const _Tp& __val) { _M_fill_assign(__n, __val); }
    void _M_fill_assign(size_type __n, const _Tp& __val);

    template <class _ForwardIter>
    void _M_assign_aux( _ForwardIter __first, _ForwardIter __last, const forward_iterator_tag & )
      {
        const size_type __len = _STLP_STD::distance(__first, __last);
        if (__len > capacity()) {
          size_type __n = __len;
          iterator __tmp = _M_allocate_and_copy(__n, __first, __last);
          _M_clear();
          _M_set(__tmp, __tmp + __len, __tmp + __n);
        } else if (size() >= __len) {
          iterator __new_finish = copy(__first, __last, this->_M_start);
          _STLP_STD::_Destroy_Range(__new_finish, this->_M_finish);
          this->_M_finish = __new_finish;
        } else {
          _ForwardIter __mid = __first;
          _STLP_STD::advance(__mid, size());
          _STLP_STD::copy(__first, __mid, this->_M_start);
          this->_M_finish = _STLP_STD::uninitialized_copy(__mid, __last, this->_M_finish);
        }
      }

    template <class _InputIter>
    void _M_assign_aux( _InputIter __first, _InputIter __last, const input_iterator_tag& )
      {
        iterator __cur = begin();
        for ( ; __first != __last && __cur != end(); ++__cur, ++__first) {
          *__cur = *__first;
        }
        if ( __first == __last ) {
          erase(__cur, end());
        } else {
          insert(end(), __first, __last);
        }
      }

    template <class _Integer>
    void _M_assign_dispatch( _Integer __n, _Integer __val, const true_type& /*_IsIntegral*/ )
      { _M_fill_assign(__n, __val); }

    template <class _InputIter>
    void _M_assign_dispatch( _InputIter __first, _InputIter __last,
                             const false_type& /*_IsIntegral*/)
      { _M_assign_aux(__first, __last, _STLP_ITERATOR_CATEGORY(__first, _InputIter)); }

    template <class _InputIterator>
    void assign(_InputIterator __first, _InputIterator __last)
      { _M_assign_dispatch(__first, __last, typename is_integral<_InputIterator>::type() ); }

    void push_back(const _Tp& __x)
      {
        if (this->_M_finish != this->_M_end_of_storage._M_data) {
          _Copy_Construct(this->_M_finish, __x);
          ++this->_M_finish;
        } else if ( &__x >= this->_M_start && &__x < this->_M_finish ) { // inside moved
          _Tp __x_copy( __x );
          _M_insert_overflow( this->_M_finish, __x_copy, typename __has_trivial_move<_Tp>::type(), 1, true );
        } else {
          _M_insert_overflow( this->_M_finish, __x, typename  __has_trivial_move<_Tp>::type(), 1, true );
        }
      }

    iterator insert(iterator __pos, const _Tp& __x);

    void swap(_Self& __x)
      {
        _STLP_STD::swap(this->_M_start, __x._M_start);
        _STLP_STD::swap(this->_M_finish, __x._M_finish);
        // this->_M_end_of_storage.swap(__x._M_end_of_storage);
        _STLP_STD::swap(this->_M_end_of_storage,__x._M_end_of_storage);
      }
#if defined (_STLP_USE_PARTIAL_SPEC_WORKAROUND) && !defined (_STLP_FUNCTION_TMPL_PARTIAL_ORDER)
    void _M_swap_workaround(_Self& __x)
      { swap(__x); }
#endif

  private:
    void _M_fill_insert_aux( iterator __pos, size_type __n, const _Tp& __x, const true_type& /*_Movable*/);
    void _M_fill_insert_aux( iterator __pos, size_type __n, const _Tp& __x, const false_type& /*_Movable*/);
    void _M_fill_insert( iterator __pos, size_type __n, const _Tp& __x );

    template <class _ForwardIterator>
    void _M_range_insert_realloc( iterator __pos,
                                  _ForwardIterator __first, _ForwardIterator __last,
                                  size_type __n, const false_type& /* trivial move */ )
      {
        size_type __len = _M_compute_next_size(__n);
        pointer __new_start = this->_M_end_of_storage.allocate(__len);
        pointer __new_finish = __new_start;
        pointer old = this->_M_start;
        _STLP_TRY {
          for ( ; old != __pos; ++__new_finish, ++old ) {
            _Move_Construct( __new_finish, *old );
          }
          // handle insertion
          for ( ; __first != __last; ++__first, ++__new_finish ) {
            _Copy_Construct( __new_finish, *__first );
          }
          for ( ; old != this->_M_finish; ++__new_finish, ++old ) {
            _Move_Construct( __new_finish, *old );
          }
        }
        _STLP_UNWIND((_STLP_STD::_Destroy_Range(__new_start,__new_finish),
                      this->_M_end_of_storage.deallocate(__new_start,__len)))
        _M_clear();
        _M_set(__new_start, __new_finish, __new_start + __len);
      }

    template <class _ForwardIterator>
    void _M_range_insert_realloc( iterator __pos,
                                  _ForwardIterator __first, _ForwardIterator __last,
                                  size_type __n, const true_type& /* trivial move */ )
      {
        size_type __len = _M_compute_next_size(__n);
        pointer __new_start = this->_M_end_of_storage.allocate(__len);
        pointer __new_finish = __STATIC_CAST(pointer, _STLP_PRIV __ucopy_trivial( this->_M_start, __pos, __new_start ) );
        // handle insertion ToDo: spec for _ForwardIterator, in construct
        for ( ; __first != __last; ++__first, ++__new_finish ) {
          _Copy_Construct<_Tp>( __new_finish, *__first );
        }
        __new_finish = __STATIC_CAST(pointer, _STLP_PRIV __ucopy_trivial( __pos, this->_M_finish, __new_finish ) ); // copy remainder
        _M_clear_after_move();
        _M_set(__new_start, __new_finish, __new_start + __len);
      }

    template <class _ForwardIterator>
    void _M_range_insert_aux( iterator __pos,
                              _ForwardIterator __first, _ForwardIterator __last,
                              size_type __n, const true_type& /*_Movable*/)
      {
        _STLP_PRIV __copy_trivial( __pos, this->_M_finish, __pos + __n );
        this->_M_finish += __n;
        for ( ; __first != __last; ++__first, ++__pos ) {
          _Copy_Construct<_Tp>( __pos, *__first );
        }
      }

    template <class _ForwardIterator>
    void _M_range_insert_aux( iterator __pos,
                              _ForwardIterator __first, _ForwardIterator __last,
                              size_type __n, const false_type& /*_Movable*/)
      {
        iterator src = this->_M_finish - 1;
        iterator dst = src + __n;
        for ( ; src >= __pos; --dst, --src ) {
          _STLP_STD::_Move_Construct(dst, *src);
          _STLP_STD::_Destroy_Moved(src);
        }
        this->_M_finish += __n;
        for ( ; __first != __last; ++__first, ++__pos ) {
          _Copy_Construct( __pos, *__first );
        }
      }

    template <class _Integer>
    void _M_insert_dispatch( iterator __pos, _Integer __n, _Integer __val, const true_type&)
      { _M_fill_insert(__pos, (size_type) __n, (_Tp) __val); }

    template <class _InputIterator>
    void _M_insert_dispatch( iterator __pos, _InputIterator __first, _InputIterator __last,
                             const false_type& )
      { _M_range_insert(__pos, __first, __last, _STLP_ITERATOR_CATEGORY(__first, _InputIterator)); }

  public:
    // Check whether it's an integral type.  If so, it's not an iterator.
    template <class _InputIterator>
    void insert( iterator __pos, _InputIterator __first, _InputIterator __last )
      {
        typedef typename is_integral<_InputIterator>::type _Integral;
        _M_insert_dispatch(__pos, __first, __last, _Integral());
      }

  private:
    template <class _InputIterator>
    void _M_range_insert( iterator __pos, _InputIterator __first, _InputIterator __last,
                          const input_iterator_tag &)
      {
        for ( ; __first != __last; ++__first) {
          __pos = insert(__pos, *__first);
          ++__pos;
        }
      }

    template <class _ForwardIterator>
    void _M_range_insert( iterator __pos, _ForwardIterator __first, _ForwardIterator __last,
                          const forward_iterator_tag& )
     {
       /* This method do not check self referencing.
        * Standard forbids it, checked by the debug mode.
        */
       if (__first != __last) {
         size_type __n = _STLP_STD::distance(__first, __last);

         if (size_type(this->_M_end_of_storage._M_data - this->_M_finish) >= __n) {
           _M_range_insert_aux(__pos, __first, __last, __n, typename __has_trivial_move<_Tp>::type() );
         } else {
           _M_range_insert_realloc(__pos, __first, __last, __n, typename __has_trivial_move<_Tp>::type() );
         }
       }
    }

  public:
    void insert (iterator __pos, size_type __n, const _Tp& __x)
      { _M_fill_insert(__pos, __n, __x); }

    void pop_back()
      {
        --this->_M_finish;
        _STLP_STD::_Destroy(this->_M_finish);
      }

  private:
    iterator _M_erase(iterator __pos, const false_type& /*_Movable*/)
      {
        _STLP_STD::_Destroy(__pos);

        iterator __dst = __pos, __src = __dst + 1;
        iterator __end = end();
        for (; __src != __end; ++__dst, ++__src) {
          _STLP_STD::_Move_Construct(__dst, *__src);
          _STLP_STD::_Destroy_Moved(__src);
        }
        this->_M_finish = __dst;
        return __pos;
      }

    iterator _M_erase(iterator __pos, const true_type& /*_Movable*/)
      {
        _STLP_STD::_Destroy(__pos);

        if (__pos + 1 != end()) {
          _STLP_PRIV __copy_trivial( __pos + 1, this->_M_finish, __pos );
        }
        --this->_M_finish;
        return __pos;
      }

    iterator _M_erase(iterator __first, iterator __last, const false_type& /*_Movable*/)
      {
        iterator __dst = __first, __src = __last;
        iterator __end = end();
        for (; __dst != __last && __src != __end; ++__dst, ++__src) {
          _STLP_STD::_Destroy(__dst);
          _STLP_STD::_Move_Construct(__dst, *__src);
        }
        if (__dst != __last) {
          //There is more elements to erase than element to move:
          _STLP_STD::_Destroy_Range(__dst, __last);
          _STLP_STD::_Destroy_Moved_Range(__last, __end);
        } else {
          //There is more element to move than element to erase:
          for (; __src != __end; ++__dst, ++__src) {
            _STLP_STD::_Destroy_Moved(__dst);
            _STLP_STD::_Move_Construct(__dst, *__src);
          }
          _STLP_STD::_Destroy_Moved_Range(__dst, __end);
        }
        this->_M_finish = __dst;
        return __first;
      }

    iterator _M_erase(iterator __first, iterator __last, const true_type& /*_Movable*/)
      {
        _STLP_STD::_Destroy_Range(__first, __last);
        this->_M_finish = __STATIC_CAST(pointer, _STLP_PRIV __copy_trivial( __last, this->_M_finish, __first ) );
        return __first;
      }

  public:
    iterator erase(iterator __pos)
      {
        return _M_erase(__pos, integral_constant<bool, __has_trivial_move<_Tp>::value>() );
      }

    iterator erase(iterator __first, iterator __last)
      {
        return __first == __last ? __first : _M_erase(__first, __last, integral_constant<bool, __has_trivial_move<_Tp>::value>() );
      }

#if !defined (_STLP_DONT_SUP_DFLT_PARAM)
    void resize( size_type __new_size, const _Tp& __x = _STLP_DEFAULT_CONSTRUCTED(_Tp) )
      {
#else
    void resize( size_type __new_size, const _Tp& __x )
      {
#endif /*_STLP_DONT_SUP_DFLT_PARAM*/
         if ( __new_size < size() ) {
           erase(begin() + __new_size, end());
         } else {
           insert(end(), __new_size - size(), __x);
         }
      }

#if defined (_STLP_DONT_SUP_DFLT_PARAM)
    void resize(size_type __new_size)
      { resize(__new_size, _STLP_DEFAULT_CONSTRUCTED(_Tp)); }
#endif /*_STLP_DONT_SUP_DFLT_PARAM*/

    void clear()
      { erase(begin(), end()); }

  private:
    void _M_clear()
      {
        _STLP_STD::_Destroy_Range(rbegin(), rend());
        this->_M_end_of_storage.deallocate(this->_M_start, this->_M_end_of_storage._M_data - this->_M_start);
      }

    void _M_clear_after_move()
      {
        _STLP_STD::_Destroy_Moved_Range(rbegin(), rend());
        this->_M_end_of_storage.deallocate(this->_M_start, this->_M_end_of_storage._M_data - this->_M_start);
      }

    void _M_set( pointer __s, pointer __f, pointer __e )
      {
        this->_M_start = __s;
        this->_M_finish = __f;
        this->_M_end_of_storage._M_data = __e;
      }

    template <class _ForwardIterator>
    pointer _M_allocate_and_copy( size_type& __n,
                                  _ForwardIterator __first, _ForwardIterator __last )
      {
        pointer __result = this->_M_end_of_storage.allocate(__n);
        _STLP_TRY {
          uninitialized_copy(__first, __last, __result);
          return __result;
        }
        _STLP_UNWIND(this->_M_end_of_storage.deallocate(__result, __n))
        _STLP_RET_AFTER_THROW(__result)
      }

    template <class _InputIterator>
    void _M_range_initialize( _InputIterator __first, _InputIterator __last,
                              const input_iterator_tag& )
      {
        for ( ; __first != __last; ++__first) {
          push_back(*__first);
        }
      }
    // This function is only called by the constructor.
    template <class _ForwardIterator>
    void _M_range_initialize( _ForwardIterator __first, _ForwardIterator __last,
                              const forward_iterator_tag& )
      {
        size_type __n = _STLP_STD::distance(__first, __last);
        this->_M_start = this->_M_end_of_storage.allocate(__n);
        this->_M_end_of_storage._M_data = this->_M_start + __n;
        this->_M_finish = uninitialized_copy(__first, __last, this->_M_start);
      }
};

#if defined (vector)
_STLP_MOVE_TO_STD_NAMESPACE
#  if defined (_STLP_CLASS_PARTIAL_SPECIALIZATION) && !defined (_STLP_NO_MOVE_SEMANTIC)
_STLP_BEGIN_TR1_NAMESPACE

template <class _Tp, class _Alloc>
struct __has_trivial_move<_STLP_PRIV vector<_Tp, _Alloc> > :
  public integral_constant<bool, is_trivial<_Alloc>::value> /* true_type */
{ };

template <class _Tp, class _Alloc>
struct __has_move_constructor<_STLP_PRIV vector<_Tp, _Alloc> > :
    public true_type
{ };

_STLP_END_NAMESPACE
#  endif /* _STLP_CLASS_PARTIAL_SPECIALIZATION */

#  undef vector
#else // vector
#  if defined (_STLP_CLASS_PARTIAL_SPECIALIZATION) && !defined (_STLP_NO_MOVE_SEMANTIC)
_STLP_BEGIN_TR1_NAMESPACE

template <class _Tp, class _Alloc>
struct __has_trivial_move<vector<_Tp, _Alloc> > :
  public integral_constant<bool, is_trivial<_Alloc>::value> /* true_type */
{ };

template <class _Tp, class _Alloc>
struct __has_move_constructor<vector<_Tp, _Alloc> > :
    public true_type
{ };

_STLP_END_NAMESPACE
#  endif /* _STLP_CLASS_PARTIAL_SPECIALIZATION */
#endif // vector

_STLP_END_NAMESPACE

#if !defined (_STLP_LINK_TIME_INSTANTIATION)
#  include <stl/_vector.c>
#endif

#if defined (_STLP_USE_PTR_SPECIALIZATIONS)
#  include <stl/pointers/_vector.h>
#endif

//We define the bool specialization before the debug interfave
//to benefit of the debug version of vector even for the bool
//specialization.
#if !defined (_STLP_NO_BOOL) || !defined (_STLP_NO_EXTENSIONS)
#  if !defined (_STLP_INTERNAL_BVECTOR_H)
#    include <stl/_bvector.h>
#  endif
#endif

#if defined (_STLP_DEBUG)
#  include <stl/debug/_vector.h>
#endif

_STLP_BEGIN_NAMESPACE

#if !defined (_STLP_NO_BOOL) && !defined (_STLP_NO_EXTENSIONS)
// This typedef is non-standard.  It is provided for backward compatibility.
typedef vector<bool, allocator<bool> > bit_vector;
#endif

#define _STLP_TEMPLATE_HEADER template <class _Tp, class _Alloc>
#define _STLP_TEMPLATE_CONTAINER vector<_Tp, _Alloc>
#include <stl/_relops_cont.h>
#undef _STLP_TEMPLATE_CONTAINER
#undef _STLP_TEMPLATE_HEADER

_STLP_END_NAMESPACE

#endif /* _STLP_VECTOR_H */

// Local Variables:
// mode:C++
// End:
