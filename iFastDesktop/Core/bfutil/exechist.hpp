#pragma once

#ifndef SE_TEST
   #include <commonport.h>
   #include <dstring.hpp>
#else
   #define CLASS_EXPORT __declspec(dllexport)
   #define CLASS_IMPORT __declspec(dllimport)
   #define I_CHAR char
   #define DStringA std::string
   #define i_strcpy strcpy
   #define i_strlen strlen
   #define i_vsnprintf _vsnprintf
#endif
#include <stdio.h>


// standard linkage-specifier macro
#undef BFUTIL_LINKAGE
#ifdef BFUTIL_DLL
   #define BFUTIL_LINKAGE CLASS_EXPORT
#else
   #define BFUTIL_LINKAGE CLASS_IMPORT
#endif

#if defined(_DEBUG) && !defined(NBFRELSYM)
   #undef BFRELSYM
   #define BFRELSYM
#endif   

namespace exechist
{
   static const I_CHAR* getSourceFileName( const char* pszFile );
}


class BFUTIL_LINKAGE ExecutionHistory
{
public:
   ExecutionHistory( const I_CHAR* pszClass, const I_CHAR* pszFunction, const I_CHAR* pszFile, unsigned long ulLine );
   ExecutionHistory( const I_CHAR* pszFunction, const I_CHAR* pszFile, unsigned long ulLine );
   ~ExecutionHistory();

   enum Status {off, limited, full};

   static void setStatus( enum Status eStatus );
   static enum Status getStatus();

   static void init();
   static void finalize();
   static void dump( FILE* pFile );
   static I_CHAR* getSourceFileName( const I_CHAR* pszSourceFile );
   static DString getClassName( const char* pszClassName );

   void addMessage( const I_CHAR* pszMask, ... );
   void push( const I_CHAR* pszClass, 
              const I_CHAR* pszFunction, 
              const I_CHAR* pszFile, 
              unsigned long ulLine,
              const I_CHAR* pszMessage,
              bool bBreadcrumb );
private:
   unsigned int iGuard_;
   unsigned int iHist_;
   unsigned long iToken_;
   const I_CHAR* pszFile_;
};

#if defined(BFRELSYM)
   #include <stdlib.h>
   #include <typeinfo>	/* for EXECHISTI to work */
   
   namespace exechist {
      static DString getClassName( const char* pszClassName ) {
   	   return( ExecutionHistory::getClassName( pszClassName ) );
      }
   }

   #define EXECHIST( func ) ExecutionHistory l_execHist( (func), \
            exechist::getSourceFileName(__FILE__), __LINE__ )
   #define EXECHISTMSG( func, msg ) \
         ExecutionHistory l_execHist( (func),\
                                      exechist::getSourceFileName(__FILE__), __LINE__ ); \
         l_execHist.addMessage( msg )
   #define EXECHIST2( cls, mthd ) \
      ExecutionHistory l_execHist( (cls), \
                                   (mthd), \
                                   exechist::getSourceFileName(__FILE__), __LINE__ )
   #define EXECHISTI( mthd ) \
      ExecutionHistory l_execHist( exechist::getClassName(typeid(*this).name()).c_str(), \
                                   (mthd), \
                                   exechist::getSourceFileName(__FILE__), __LINE__ )
   #define EXECHIST2MSG( cls, mthd ) \
      ExecutionHistory l_execHist( (cls), \
                                   (mthd), \
                                   exechist::getSourceFileName(__FILE__), __LINE__ ); \
      l_execHist.addMessage( msg )
   #define EXECBREADCRUMB( msg ) \
      do { \
         l_execHist.push( NULL, NULL, exechist::getSourceFileName(__FILE__), __LINE__, NULL, true ); \
         l_execHist.addMessage msg; } \
      while( false )
#else
   #define EXECHIST( func )
   #define EXECHISTMSG( func, msg )
   #define EXECHIST2( cls, mthd )
   #define EXECHISTI( mthd )
   #define EXECHIST2MSG( cls, mthd, msg )
   #define EXECBREADCRUMB( msg )
#endif   

#if defined(BFRELSYM)
/**
 * EXECGUARD declares a variable on the stack and initializes it
 * with a well-known value.  The EXECTEST macro can be used subsequently
 * to make sure that the variable has the same value.  This is useful
 * for detecting stack-smash problems proactively.
 * 
 * @see #EXECTEST
 */
   #define EXECGUARD int l_iExecGuard = 0xbaadf00d
   #define EXECTEST do { if( 0xbaadf00d != l_iExecGuard ) { *(int*)0 = 0x00; } } while( false )
#else
   #define EXECGUARD
   #define EXECTEST
#endif

namespace exechist
{
   static const I_CHAR* getSourceFileName( const char* pszFile ) {
   	static I_CHAR* s_sourceFileName = NULL;
      if( NULL == s_sourceFileName ) {
	      s_sourceFileName = ExecutionHistory::getSourceFileName( DString(DStringA(pszFile)).c_str() );
      }
	   return( s_sourceFileName );
   }
}

