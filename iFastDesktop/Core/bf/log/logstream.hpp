#pragma once

#undef BFUTIL_LINKAGE
#ifdef BFUTIL_DLL
   #define BFUTIL_LINKAGE CLASS_EXPORT
#else
   #define BFUTIL_LINKAGE CLASS_IMPORT
#endif

#include <windows.h>
#include <map>
#include <dstring.hpp>
#include <bfutil/bfcritsec.hpp>
#include <bfutil/bfguard.hpp>
#include <bfutil/bfifds.hpp>
#include <assert.h>

#include <bf/log/bflog.hpp>

namespace bf {
namespace log {

class Log;

class BFUTIL_LINKAGE LogStream
{
public:

   friend Log;

   friend LogStream& __cdecl ldebug( LogStream& );
   friend LogStream& __cdecl ltrace( LogStream& );
   friend LogStream& __cdecl information( LogStream& );
   friend LogStream& __cdecl warning( LogStream& );
   friend LogStream& __cdecl notify( LogStream& );
   friend LogStream& __cdecl severe( LogStream& );
   friend LogStream& __cdecl critical( LogStream& );

   enum Level
   {
      e_debug = 0, e_trace, e_notify, e_information, e_warning, e_severe, e_critical, e_silent
   };

   LogStream( unsigned long fCategory, Log* pLog = NULL );
   ~LogStream();

private:
   LogStream( Log* pLog );      // used only by Log
public:

   void put( I_CHAR c );
   void put( int i );
   void put( unsigned int i );
   void put( long l );
   void put( unsigned long l );
   void put( float f ) ;
   void put( double d );
   void put( const I_CHAR* p );
   void put( const DString& str ) { put( str.c_str() ); }

   DString get() const { 
      BFGuard g( cs_ );
      DString dstr;
      {
         dstr.reserve( buf_.size() + 1 );
         dstr += buf_;     // += will not reset the reserve() method's allocation
      }
      if( dstr.size() != 0 && 0x0a != dstr[ dstr.size() - 1 ] )
      {
         dstr += I_( "\n" );
      }
      return(dstr); 
   }
   void reset( int cbReserve = 128 ) 
   { 
      BFGuard g( cs_ );
      buf_ = I_(""); 
      if( 0 < cbReserve )
         buf_.reserve( cbReserve );
   }
   // if external logstream then flush to internal log stream
   void flush();

   inline BFCritSec& getCS() const { return(cs_);}

   void setReportingLevel( enum Level eLevel ) { assert( e_silent != eLevel ); eReportingLevel_ = eLevel; }
   void setCategory( unsigned long fCat ) { fCategories_ |= fCat;}

   void join( const LogStream* pLog );

   inline void resetCategory() { if( true == bInternal_ ) fCategories_ = 0; }
   inline void resetBase() { numBase_ = 10; }

   void setbase( unsigned int numBase ) {
       numBase_ = numBase_;
       switch( numBase_ ) { 
          case 10:
          case 16:
             break;
          default:
             numBase_ = 10;
       }
   }

private:
   Log* pLog_;                // containing log object
   bool bInternal_;

   DString buf_;
   enum Level eReportingLevel_;     // current reporting level for this stream
   unsigned long fCategories_;      // current reporting categories for this stream

   unsigned int numBase_;

   mutable BFCritSec cs_;

   inline void maybeLineStamp() 
   {
      if( buf_.size() == 0 || 0x0a == buf_[ buf_.size() - 1 ] )
      {
         linestamp();
      }
   }
   void linestamp();

public:
   LogStream& operator<<( LogStream& (__cdecl *_F)(LogStream&)) {
      return((*_F)(*this)); 
   }
   /**
    * inserter to allow I_CHARs to be written to the log
    * 
    * @param c      Character to write
    * 
    * @return reference to this log
    */
   LogStream& operator<<( I_CHAR c );
   /**
    * inserter to allow ints to be written to the log
    * 
    * @param i      Integer to write
    * 
    * @return reference to this log
    */
   LogStream& operator<<( int i );
   /**
    * inserter to allow unsigned ints to be written to the log
    * 
    * @param i      Unsigned integer to write
    * 
    * @return reference to this log
    */
   LogStream& operator<<( unsigned int i );
   /**
    * inserter to allow long ints to be written to the log
    * 
    * @param l      Long integer to write
    * 
    * @return reference to this log
    */
   LogStream& operator<<( long l );
   /**
    * inserter to allow unsigned long ints to be written to the log
    * 
    * @param l      Unsigned long integer to write
    * 
    * @return reference to this log
    */
   LogStream& operator<<( unsigned long l );

   LogStream& operator<<( const void* p );
   /**
    * inserter to allow floats to be written to the log
    * 
    * @param f      Float to write
    * 
    * @return reference to this log
    */
   LogStream& operator<<( float f );
   /**
    * inserter to allow doubles to be written to the log
    * 
    * @param i      Doubles to write
    * 
    * @return reference to this log
    */
   LogStream& operator<<( double d );
   /**
    * inserter to allow c-style strings to be written to the log
    * 
    * @param p      Pointer to NULL-terminated string of characters
    * 
    * @return reference to this log
    */
   LogStream& operator<<( const I_CHAR* p );
   /**
    * inserter to allow DStrings to be written to the log
    * 
    * @param i      DString to write
    * 
    * @return reference to this log
    */
   LogStream& operator<<( const DString& str );

};


inline LogStream& __cdecl endl( LogStream& l )
{
   l << I_( "\n" );
   return( l );
}

inline LogStream& __cdecl endlf( LogStream& l )
{
   l << I_( "\n" );
   l.flush();
   return( l );
}

inline LogStream& __cdecl flush( LogStream& l )
{
   l.flush();
   return( l );
}

inline LogStream& __cdecl hex( LogStream& l )
{
   l.setbase(16);
   return( l );
}

inline LogStream& __cdecl dec( LogStream& l )
{
   l.setbase(10);
   return( l );
}

/*==========================================================================
 *------------------------ Reporting Level functions -----------------------
 *==========================================================================*/
inline LogStream& __cdecl ldebug( LogStream& l ) 
{
   l.setReportingLevel( LogStream::Level::e_debug );
   return( l );
}

inline LogStream& __cdecl ltrace( LogStream& l ) 
{
   l.setReportingLevel( LogStream::Level::e_trace );
   return( l );
}

inline LogStream& __cdecl notify( LogStream& l ) 
{
   l.setReportingLevel( LogStream::Level::e_notify );
   return( l );
}

inline LogStream& __cdecl information( LogStream& l ) 
{
   l.setReportingLevel( LogStream::Level::e_information );
   return( l );
}

inline LogStream& __cdecl warning( LogStream& l ) 
{
   l.setReportingLevel( LogStream::Level::e_warning );
   return( l );
}

inline LogStream& __cdecl severe( LogStream& l ) 
{
   l.setReportingLevel( LogStream::Level::e_severe );
   return( l );
}

inline LogStream& __cdecl critical( LogStream& l ) 
{
   l.setReportingLevel( LogStream::Level::e_critical );
   return( l );
}

}  // namespace log
}  // namespace bf

//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/core/bf/log/logstream.hpp-arc  $
//
//   Rev 1.1   Feb 20 2009 14:43:26   purdyech
//ZTS Revision 6
//
//   Rev 1.0   Aug 12 2003 10:14:10   PURDYECH
//Initial revision.
//
