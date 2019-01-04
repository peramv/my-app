/*
 *   COMPONENT_NAME: somk
 *
 *   ORIGINS: 27
 *
 *
 *   10H9767, 10H9769  (C) COPYRIGHT International Business Machines Corp. 1992,1994
 *   All Rights Reserved
 *   Licensed Materials - Property of IBM
 *   US Government Users Restricted Rights - Use, duplication or
 *   disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
  Last change:  KAS  12 Oct 94    3:44 pm
 */
/* %Z% %I% %W% %G% %U% [%H% %T%] */

/*
 */

/*
 *    SOMLTYPE.H
 *    Assure definitions for SOMEXTERN, SOMLINK, and SOMDLINK
 *
 *    These variables are used to control the register linkage conventions
 *    for all SOM functions, methods, and external data references.  
 *
 *    All SOM functions and external data references are preceeded with a
 *    SOMEXTERN macro (SOM methods do not have external names).
 *
 *    All SOM functions and methods are prototyped with a SOMLINK keyword.
 *
 *    All SOM external data references are defined with a SOMDLINK keyword.
 *
 *    Users may supply (at their own risk) appropriate definitions for
 *    other compilers using "-DSOMEXTERN=x", "-DSOMLINK=y" or "-DSOMDLINK=z"
 *    arguments on the compiler's command line.  Any such definition is not
 *    disturbed by the following code.
 *  
 *    assumptions: 
 *      (1) __cplusplus is defined when compiling C++ code anywhere
 *      (2) __IBMCPP__ is defined by CSet/2 on OS/2 when compiling C++ code
 *      (3) _CL386 may be defined if not using an IBM compiler
 *      (4) neither _CL386 nor __IBMCPP__ are defined on AIX
 *
 *    assumption (2) is not properly stated.
 *
 *      (new 2) __IBMCPP__ is defined by IBM C++ compilers for all platforms,
 *              including _WIN32, therefore, you must check which system is
 *              targeted in these blocks.
 *
 *      _WIN32 also means that a new macro is present.  This macro is
 *      called WIN32_DLLIMPORT.  It is used to deal with the with the
 *      MSVC __declspec(dllimport) syntax (or equivalent syntax for other
 *      vendors) required for global data imported from DLLs.  It appears
 *      on the ClassData structure definitions in .h and .xh bindings,
 *      most of the time.  It does not appear in some situations.  For
 *      example, consider class Foo.  If the .h was included by Foo's
 *      implementation file, or if the macro SOM_DONT_IMPORT_Foo_Class
 *      is defined, then the ClassData struct does not have WIN32_DLLIMPORT
 *      in the data declaration.  Examine binding files for more detail.
 *      You may override this macro from the command line at your own
 *      risk.
 */

/* set up the use of import syntax on WINDOWS NT/95 platforms */
#if defined(_WIN32) && !defined(WIN32_DLLIMPORT)
    /* Microsoft compiler defines */
    #if (_MSC_VER >= 900)
      #define WIN32_DLLIMPORT __declspec(dllimport)
    #elif (defined(__IBMC__) || defined(__IBMCPP__)) && defined(__WINDOWS__)
      /* IBM compiler defines */
      #define WIN32_DLLIMPORT __declspec(dllimport)
    #endif

    /* DEFAULT: no defines from above means define it to NULL/nothing */
    #if !defined(WIN32_DLLIMPORT)
      #define WIN32_DLLIMPORT
    #endif
#endif

/* TORO57113: defined WIN32_DLLEXPORT as well */
#if defined(_WIN32) && !defined(WIN32_DLLEXPORT)
    /* Microsoft compiler defines */
    #if (_MSC_VER >= 900)
      #define WIN32_DLLEXPORT __declspec(dllexport)
    #elif (defined(__IBMC__) || defined(__IBMCPP__)) && defined(__WINDOWS__)
      /* IBM compiler defines */
      #define WIN32_DLLEXPORT __declspec(dllexport)
    #endif

    /* DEFAULT: no defines from above means define it to NULL/nothing */
    #if !defined(WIN32_DLLEXPORT)
      #define WIN32_DLLEXPORT
    #endif
#endif

#ifndef SOMEXTERN
  #ifdef __cplusplus
    #define SOMEXTERN extern "C"
    #ifdef __STR__
      #undef __STR__
    #endif
  #else
    #define SOMEXTERN extern
  #endif
#endif

#ifndef SOMLINK
  #if defined(_CL386)
    #define SOMLINK _syscall
  #elif defined(__OS2__)
    #if defined(__IBMCPP__) || defined(__IBMC__)  /* 15369 */
      #define SOMLINK _System
    #elif defined(__BCPLUSPLUS__) || (__BORLANDC__)
      #define SOMLINK _syscall
    #elif defined(__HIGHC__)
      #define SOMLINK _DCC(_DEFAULT_CALLING_CONVENTION &   \
			   ~_SHORT_STRUCTS_IN_REGS & ~_OVERLOADED)
    #else
      #define SOMLINK
    #endif
  #elif defined(__WINDOWS__)   /* 15369 */
    #define SOMLINK __stdcall  
  #elif defined(_MSDOS) || defined(__MSDOS__) || defined(__SC__)
    #if defined(_WDOS) || defined(__SOMEMIT__)
      #ifdef __SC__
	#define SOMLINK
      #endif
    #else
      #define SOMLINK __loadds
      #define WIN16_SOMLINK __loadds
      #ifndef _WIN16
  #define _WIN16
      #endif
    #endif
  #elif defined(_WIN32)
    #define SOMLINK __stdcall
  #else
    #define SOMLINK
  #endif
#endif

#ifndef SOMDLINK
  #if defined(_CL386)
    #define SOMDLINK
  #elif defined(__OS2__)
    #define SOMDLINK
  #elif defined(_MSDOS) || defined(__MSDOS__) || defined(__SC__)
    #if (defined(_WDOS) || defined(__SOMEMIT__)) && defined(__SC__)
      #define SOMDLINK
    #else
      #define SOMDLINK __far
    #endif
  #else
    /* this is also the WIN32 define */ 
    #define SOMDLINK
  #endif
#endif

