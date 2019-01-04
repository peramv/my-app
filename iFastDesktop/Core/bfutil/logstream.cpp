#include "stdafx.h"
#include <bf/log/logstream.hpp>
#include <bf/log/log.hpp>
#include <bf/log/abstractlogtarget.hpp>
#include <assert.h>

#include <bfutil/bfguard.hpp>

bf::log::LogStream::LogStream( unsigned long fCategory, Log* pLog )
: pLog_( pLog )
, bInternal_( false )
, eReportingLevel_( e_critical )   // consider all logging information critical at start
, fCategories_( fCategory )
, numBase_( 10 )
{
   if( NULL == pLog_ ) {
      pLog_ = &bf::log::theLog;
   }
}

bf::log::LogStream::LogStream( Log* pLog )
: pLog_( pLog )
, bInternal_( true )
, eReportingLevel_( e_critical )   // consider all logging information critical at start
, fCategories_( 0 )
, numBase_( 10 )
{
   assert( NULL != pLog_ );
}

bf::log::LogStream::~LogStream()
{
   if( false == bInternal_ ) {
      // must flush this log stream to the attached targets
      pLog_->flushStream( this );
   }
}


void bf::log::LogStream::linestamp( void ) 
{
   // build the date/time information and the threadid info into a string buffer
   SYSTEMTIME st;
   GetLocalTime( &st );

   I_CHAR szBuf[ 128 ];
   i_sprintf( szBuf, I_( "%04d-%02d-%02d %02d:%02d:%02d.%03d (%04x)(%04x): " ),
              st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond, st.wMilliseconds, 
              GetCurrentThreadId() & 0x0000ffff,
              fCategories_ & 0x0000ffff );

   // append the 'linestamp' to the LogStreamBuffer.
   buf_ += szBuf;
}

void bf::log::LogStream::put( I_CHAR c ) { 
   if( pLog_->isOkToLog( eReportingLevel_, fCategories_ ) )
   {
      BFGuard g(cs_); 
      maybeLineStamp(); 
      buf_ += c; 
   }
   resetCategory();
}

void bf::log::LogStream::put( int i ) 
{ 
   if( pLog_->isOkToLog( eReportingLevel_, fCategories_ ) )
   {
      BFGuard g(cs_); 
      maybeLineStamp(); 
      I_CHAR szBuf[ 33 ]; 
      i_sprintf( szBuf, numBase_ == 10 ? I_( "%d" ) : I_( "%x" ), i ); 
      buf_ += szBuf; 
   }
   resetCategory();
   resetBase();
}

void bf::log::LogStream::put( unsigned int i ) 
{ 
   if( pLog_->isOkToLog( eReportingLevel_, fCategories_ ) )
   {
      BFGuard g(cs_); 
      maybeLineStamp(); 
      I_CHAR szBuf[ 33 ]; 
      i_sprintf( szBuf, numBase_ == 10 ? I_( "%u" ) : I_( "%x" ), i ); 
      buf_ += szBuf; 
   }
   resetCategory();
   resetBase();
}

void bf::log::LogStream::put( long l ) 
{ 
   if( pLog_->isOkToLog( eReportingLevel_, fCategories_ ) )
   {
      BFGuard g(cs_); 
      maybeLineStamp(); 
      I_CHAR szBuf[ 33 ]; 
      i_sprintf( szBuf, numBase_ == 10 ? I_( "%ld" ) : I_( "%x" ), l ); 
      buf_ += szBuf; 
   }
   resetCategory();
   resetBase();
}

void bf::log::LogStream::put( unsigned long l ) 
{ 
   if( pLog_->isOkToLog( eReportingLevel_, fCategories_ ) )
   {
      BFGuard g(cs_); 
      maybeLineStamp(); 
      I_CHAR szBuf[ 33 ]; 
      i_sprintf( szBuf, numBase_ == 10 ? I_( "%lu" ) : I_( "%x" ), l ); 
      buf_ += szBuf; 
   }
   resetCategory();
   resetBase();
}

void bf::log::LogStream::put( float f ) 
{ 
   if( pLog_->isOkToLog( eReportingLevel_, fCategories_ ) )
   {
      BFGuard g(cs_); 
      maybeLineStamp(); 
      I_CHAR szBuf[ 33 ]; 
      i_sprintf( szBuf, I_( "%f" ), f ); 
      buf_ += szBuf; 
   }
   resetCategory();
}

void bf::log::LogStream::put( double d ) 
{ 
   if( pLog_->isOkToLog( eReportingLevel_, fCategories_ ) )
   {
      BFGuard g(cs_); 
      maybeLineStamp(); 
      I_CHAR szBuf[ 33 ]; 
      i_sprintf( szBuf, I_( "%d" ), d ); 
      buf_ += szBuf; 
   }
   resetCategory();
}

void bf::log::LogStream::put( const I_CHAR* p ) 
{
   if( pLog_->isOkToLog( eReportingLevel_, fCategories_ ) )
   {
      BFGuard g(cs_); 
      for( ; 0x00 != *p; ++p )
      {
         maybeLineStamp();
         if( buf_.size() == buf_.capacity() )
         {
            if( buf_.size() < 16384 )
            {
               buf_.reserve( buf_.size() * 2 );
            }
            else
            {
               buf_.reserve( buf_.size() + 1024 );
            }
         }
         buf_ += *p;
      }
   }
   resetCategory();
}

void bf::log::LogStream::join( const LogStream* pLog )
{
   const DString& dstr = pLog->get();
   if( dstr.empty() ) return;

   BFGuard g(cs_);
   if( !buf_.empty() && buf_[ buf_.size() - 1 ] != 0x0a ) 
   {
      buf_ += I_( "\n" );
   }
   buf_ += pLog->get();
   if( !buf_.empty() && buf_[ buf_.size() - 1 ] != 0x0a ) 
   {
      buf_ += I_( "\n" );
   }
}


bf::log::LogStream& bf::log::LogStream::operator<<( I_CHAR c ) { 
   if( pLog_->getReportingThreshold() < LogStream::Level::e_silent ) {
      put( c ); 
   }
   return( *this );  
}
/**
 * inserter to allow ints to be written to the log
 * 
 * @param i      Integer to write
 * 
 * @return reference to this log
 */
bf::log::LogStream& bf::log::LogStream::operator<<( int i ) { 
   if( pLog_->getReportingThreshold() < LogStream::Level::e_silent ) {
      put( i );
   }
   return( *this ); 
}
/**
 * inserter to allow unsigned ints to be written to the log
 * 
 * @param i      Unsigned integer to write
 * 
 * @return reference to this log
 */
bf::log::LogStream& bf::log::LogStream::operator<<( unsigned int i ) { 
   if( pLog_->getReportingThreshold() < LogStream::Level::e_silent ) {
      put( i );
   }
   return( *this ); 
}
/**
 * inserter to allow long ints to be written to the log
 * 
 * @param l      Long integer to write
 * 
 * @return reference to this log
 */
bf::log::LogStream& bf::log::LogStream::operator<<( long l ) { 
   if( pLog_->getReportingThreshold() < LogStream::Level::e_silent ) {
      put( l );
   }
   return( *this ); 
}
/**
 * inserter to allow unsigned long ints to be written to the log
 * 
 * @param l      Unsigned long integer to write
 * 
 * @return reference to this log
 */
bf::log::LogStream& bf::log::LogStream::operator<<( unsigned long l ) { 
   if( pLog_->getReportingThreshold() < LogStream::Level::e_silent ) {
      put( l );
   }
   return( *this ); 
}


bf::log::LogStream& bf::log::LogStream::operator<<( const void* p ) { 
   if( pLog_->getReportingThreshold() < LogStream::Level::e_silent ) {
      put( reinterpret_cast<unsigned long>(p) );
   }
   return( *this ); 
}

/**
 * inserter to allow floats to be written to the log
 * 
 * @param f      Float to write
 * 
 * @return reference to this log
 */
bf::log::LogStream& bf::log::LogStream::operator<<( float f ) { 
   if( pLog_->getReportingThreshold() < LogStream::Level::e_silent ) {
      put( f );
   }
   return( *this ); 
}
/**
 * inserter to allow doubles to be written to the log
 * 
 * @param i      Doubles to write
 * 
 * @return reference to this log
 */
bf::log::LogStream& bf::log::LogStream::operator<<( double d ) { 
   if( pLog_->getReportingThreshold() < LogStream::Level::e_silent ) {
      put( d );
   }
   return( *this ); 
}
/**
 * inserter to allow c-style strings to be written to the log
 * 
 * @param p      Pointer to NULL-terminated string of characters
 * 
 * @return reference to this log
 */
bf::log::LogStream& bf::log::LogStream::operator<<( const I_CHAR* p ) { 
   if( pLog_->getReportingThreshold() < LogStream::Level::e_silent ) {
      put( p );
   }
   return( *this ); 
}
/**
 * inserter to allow DStrings to be written to the log
 * 
 * @param i      DString to write
 * 
 * @return reference to this log
 */
bf::log::LogStream& bf::log::LogStream::operator<<( const DString& str ) { 
   if( pLog_->getReportingThreshold() < LogStream::Level::e_silent ) {
      put( str );
   }
   return( *this ); 
}

void bf::log::LogStream::flush()
{
   if( false == bInternal_ )
   {
      pLog_->flushStream( this );
   }
}

//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF Core/bfutil/logstream.cpp-arc  $
// 
//    Rev 1.2   Jan 15 2004 08:40:52   PURDYECH
// Only display the bottom 16 bits of the thread and categories when stamping a line (i.e. only 4 hex digits each).  This regularizes the format of the timestamp
// 
//    Rev 1.1   Aug 14 2003 14:20:06   PURDYECH
// For stack-based LogStreams we now flush to the targets, instead of the associated log, when the LogStream is destroyed.
// 
//    Rev 1.0   Aug 12 2003 10:13:08   PURDYECH
// Initial Revision
//
