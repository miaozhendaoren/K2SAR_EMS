

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

/*
 * Purpose of this file :
 *
 * To hold user-definable portion of STLport settings which may be overridden
 * on per-project basis.
 * Please note that if you use STLport iostreams (compiled library) then you have
 * to use consistent settings when you compile STLport library and your project. 
 * Those settings are defined in _site_config.h and have to be the same for a given
 * STLport installation.
 */

 
/*==========================================================
 * User-settable macros that control compilation:
 *              Features selection
 *==========================================================*/

/*
 * Use this switch for embedded systems where no iostreams are available
 * at all. STLport own iostreams will also get disabled automatically then.
 * You can either use STLport iostreams, or no iostreams.
 * If you want iostreams, you have to compile library in ../build/lib
 * and supply resulting library at link time.
 */
/*
#define _STLP_NO_IOSTREAMS 1
*/

/* 
 * Set _STLP_DEBUG to turn the "Debug Mode" on.
 * That gets you checked iterators/ranges in the manner
 * of "Safe STL". Very useful for debugging. Thread-safe.
 * Please do not forget to link proper STLport library flavor
 * (e.g libstlportstlg.so or libstlportstlg.a) when you set this flag
 * in STLport iostreams mode.
 */
/*
#define   _STLP_DEBUG 1
*/
/*
 * You can also choose the debug level:
 * STLport debug level: Default value
 *                      Check only what the STLport implementation concider as invalid. 
 *                      It also change the iterator invalidation schema.
 * Standard debug level: Check for all operations the standard concider as "undefined behavior"
 *                       even if STlport implement it correctly. It also invalidates iterators
 *                       more often.
 */
/*
#define   _STLP_DEBUG_LEVEL _STLP_STLPORT_DBG_LEVEL
#define   _STLP_DEBUG_LEVEL _STLP_STANDARD_DBG_LEVEL
*/

/* 
 * _STLP_NO_CUSTOM_IO : define this if you do not instantiate basic_xxx iostream 
 * classes with custom types (which is most likely the case). Custom means types
 * other than char, wchar_t, char_traits<> and allocator<> like
 * basic_ostream<my_char_type, my_traits<my_char_type> > or
 * basic_string<char, char_traits<char>, my_allocator >
 * When this option is on, most non-inline template functions definitions for iostreams
 * are not seen by the client which saves a lot of compile time for most compilers,
 * also object and executable size for some.
 * Default is off, just not to break compilation for those who do use those types.
 * That also guarantees that you still use optimized standard i/o when you compile
 * your program without optimization. Option does not affect STLport library build; you
 * may use the same binary library with and without this option, on per-project basis.
 */
/*
#define _STLP_NO_CUSTOM_IO
*/

/* 
 * _STLP_NO_RELOPS_NAMESPACE: if defined, don't put the relational
 * operator templates (>, <=. >=, !=) in namespace std::rel_ops, even
 * if the compiler supports namespaces.
 * Note : if the compiler do not support namespaces, those operators are not be provided by default,
 * to simulate hiding them into rel_ops. This was proved to resolve many compiler bugs with ambiguity.
 */
/*
#define _STLP_NO_RELOPS_NAMESPACE 1
*/

/*
 * If _STLP_USE_OWN_NAMESPACE is in effect, STLport by default will try
 * to rename std:: for the user to stlport::. If you do not want this feature, 
 * please define the following switch and then use stlport::
 */
/*
#define _STLP_DONT_REDEFINE_STD 1
*/

/*
 * _STLP_WHOLE_NATIVE_STD : only meaningful in _STLP_USE_OWN_NAMESPACE mode.
 * Normally, STLport only imports necessary components from native std:: namespace -
 * those not yet provided by STLport (<iostream>, <complex>, etc.) 
 * and their dependencies (<string>, <stdexcept>). 
 * You might want everything from std:: being available in std:: namespace when you
 * include corresponding STLport header (like STLport <map> provides std::map as well, etc.),
 * if you are going to use both stlport:: and std:: components in your code.
 * Otherwise this option is not recommended as it increases the size of your object files
 * and slows down compilation.
 */
/*
#define _STLP_WHOLE_NATIVE_STD
*/


/*
 * Use this option to catch uninitialized members in your classes.
 * When it is set, construct() and destroy() fill the class storage
 * with _STLP_SHRED_BYTE (see below).
 * Note : _STLP_DEBUG and _STLP_DEBUG_ALLOC don't set this option automatically.
 */
/*
#define _STLP_DEBUG_UNINITIALIZED 1
#define _STLP_DEBUG_ALLOC 1
*/

/*
 * Uncomment and provide a definition for the byte with which raw memory
 * will be filled if _STLP_DEBUG_ALLOC or _STLP_DEBUG_UNINITIALIZED is defined. 
 * Choose a value which is likely to cause a noticeable problem if dereferenced 
 * or otherwise abused. A good value may already be defined for your platform; see
 * stl/_config.h
 */
/*
#define _STLP_SHRED_BYTE 0xA3
*/

/*
 *  This option is for gcc users only and only affects systems where native linker
 *  does not let gcc to implement automatic instantiation of static template data members/
 *  It is being put in this file as there is no way to check if we are using GNU ld automatically,
 *  so it becomes user's responsibility.
 */
/*
#define _STLP_GCC_USES_GNU_LD
*/

/*==========================================================
 * Compatibility section
 *==========================================================*/

/*
 *  Define this macro to disable anachronistic constructs (like the ones used in HP STL and
 *  not included in final standard, etc. 
 */
/*
#define _STLP_NO_ANACHRONISMS 1
*/

/*
 *  Define this macro to disable STLport extensions (for example, to make sure your code will 
 *  compile with some other implementation )
 */
/*
#define _STLP_NO_EXTENSIONS 1
*/

/* 
 * You should define this macro if compiling with MFC - STLport <stl/_config.h>
 * then include <afx.h> instead of <windows.h> to get synchronisation primitives 
 */
/*
#define _STLP_USE_MFC 1
*/

/*
 * boris : this setting is here as we cannot detect precense of new Platform SDK automatically 
 * If you are using new PSDK with VC++ 6.0 or lower,
 * please define this to get correct prototypes for InterlockedXXX functions
 */
/*
#define _STLP_NEW_PLATFORM_SDK 1
*/

/*
 * For the same reason as the one above we are not able to detect easily use
 * of the compiler coming with the Platform SDK instead of the one coming with
 * a Microsoft Visual Studio release. This change native C/C++ library location
 * and implementation, please define this to get correct STLport configuration.
 */
/*
#define _STLP_USING_PLATFORM_SDK_COMPILER 1
*/

/*
 * Some compilers support the automatic linking feature. 
 * Uncomment the following if you prefer to specify the STLport library
 * to link with yourself.
 * For the moment, this feature is only supported and implemented within STLport
 * by the Microsoft compilers.
 */
/*
#define _STLP_DONT_USE_AUTO_LINK 1
*/

/*
 * When using automatic linking (see above), output a message that tells the 
 * user which lib is getting linked via 'pragma message(..)'.
 * This setting has no effect if automatic linking is not active.
 */
/*
#define _STLP_VERBOSE_AUTO_LINK 1
*/


/*
 * Use minimum set of default arguments on template classes that have more
 * than one - for example map<>, set<>.
 * This has effect only if _STLP_LIMITED_DEFAULT_TEMPLATES is on.
 * If _STLP_MINIMUM_DEFAULT_TEMPLATE_PARAMS is set, you'll be able to compile
 * set<T> with those compilers, but you'll have to use __set__<T, less<T>>
 *
 * Affects : map<>, multimap<>, set<>, multiset<>, hash_*<>, 
 * queue<>, priority_queue<>, stack<>, istream_iterator<>
 */
/*
#define _STLP_MINIMUM_DEFAULT_TEMPLATE_PARAMS 1
*/

/*
 * The agregation of strings using the + operator is an expensive operation
 * as it requires construction of temporary objects that need memory allocation
 * and deallocation. The problem can be even more important if you are adding
 * several strings together in a single expression. To avoid this problem STLport
 * implement expression template. With this technique addition of 2 string is not
 * a string anymore but a temporary object having a reference to each of the 
 * original strings involved in the expression. This object carry information
 * directly to the destination string to set its size correctly and only make
 * a single call to the allocator. This technique can be extended to addition of 
 * N elements where elements being basic_string, C string or character type.
 * The drawback can be longer compilation time and bigger executable size.
 * STLport rebuild: Yes
 */
/*
#define _STLP_USE_TEMPLATE_EXPRESSION 1
*/

/*
 * By default the STLport basic_string implementation use a little static buffer
 * (of 16 chars when writing this doc) to avoid systematically memory allocation
 * in case of little basic_string. The drawback of such a method is bigger 
 * basic_string size and some performance penalty for method like swap. If you
 * prefer systematical dynamic allocation turn on this macro.
 * STLport rebuild: Yes
 */
/*
#define _STLP_DONT_USE_SHORT_STRING_OPTIM 1
*/

/*
 * In theory a string implementation is not force to append a terminating character
 * to the internal buffer, this character is only mandatory when calling the c_str
 * method. This, of course, imply that there is no confusion between using &*begin()
 * or data method and the special c_str method. If you are not sure that there is
 * no such confusion in your code you should define the following macro.
 * Note 1: This macro has no effect on basic_string instanciated with no POD types
 *         (this is to avoid complicated instance management within the basic_string
            implementation).
 * Note 2: This feature goes against the C++ standard because we are forced to use a
 *         const_cast to assign the null terminated char in the c_str const method.
 * STLport rebuild: Yes
 */
/*
#define _STLP_FORCE_STRING_TERMINATION 1
*/

/*
 * To reduce the famous code bloat trouble due to the use of templates STLport grant
 * a specialization of the some containers for pointer types. So all instanciations
 * of those containers with a pointer type will use the same implementation based on
 * a container of void*. If you prefer systematical instanciation turn on this macro.
 * Remark: This feature is only implemented for compilers supporting partial template
 * specialization.
 * Limitation: The container pointer specialization do not support pointer to function
 * and pointer to class member method. So if you have instanciating any container with
 * such a type compilation will failed.
 */
/*
#define _STLP_USE_PTR_SPECIALIZATIONS 1
*/

/*
 * To achieve many different optimizations within the template implementations STLport
 * uses some type traits technique. With this macro you can ask STLport to use the famous
 * boost type traits rather than the internal one. The advantages are more compiler
 * integration and a better support. If you only define this macro once the STLport has been
 * built you just have to add the boost install path within your include path. If you want
 * to use this feature at STLport built time you will have to define the
 * STLP_BUILD_BOOST_PATH enrironment variable with the value of the boost library path.
 */
/*
#define _STLP_USE_BOOST_SUPPORT 1
*/

/*==========================================================*/
