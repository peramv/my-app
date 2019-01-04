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

#include <bf/log/bflog.hpp>
#include <bf/log/logstream.hpp>

namespace bf {
namespace log {

class AbstractLogTarget;

class BFUTIL_LINKAGE Log
{
public:
   static void attachThreads();
   static void detachThreads();

   friend Log& __cdecl ldebug( Log& );
   friend Log& __cdecl ltrace( Log& );
   friend Log& __cdecl information( Log& );
   friend Log& __cdecl warning( Log& );
   friend Log& __cdecl notify( Log& );
   friend Log& __cdecl severe( Log& );
   friend Log& __cdecl critical( Log& );

   friend void __cdecl swsetcat( Log&, unsigned long );

   Log();
   virtual ~Log();

   /**
    * Add a target to this log.  The concrete log target should be a heap 
    * object (i.e. constructed with new).  Unless the target is removed
    * from this log with the removeTarget function the log will destroy
    * the target when the log is destroyed.
    * 
    * @param strTarget A unique name for this target.
    * @param pTarget   A pointer to the heap-constructed concrete log target.
    * 
    * @see #removeTarget
    * @see AbstractLogTarget
    */
   void addTarget( const DString& strTarget, AbstractLogTarget* pTarget );
   /**
    * Remove a target from this log.  The target must have been previously
    * added to this log with the addTarget function.  removeTarget will
    * return a pointer to the concrete log target which was removed; it
    * is the responsibility of the programmer to destroy this object.
    * 
    * @param strTarget The unique name which identifies the concrete log target to remove.
    * 
    * @return Pointer to the concrete log target.  NULL is returned if the concrete 
    *         log target is not found
    * @see #addTarget
    * @see AbstractLogTarget
    */
   AbstractLogTarget* removeTarget( const DString& strTarget );

   /**
    * Suspend the specified concrete log target.  Suspending a concrete
    * log target will cause no data to be written to the log target when
    * when the flush or endlf operators are called.
    * 
    * A call to restartTarget will reverse this operation.
    * 
    * @param strTarget The unique name of the log target to suspend.
    * 
    * @see #restartTarget
    */
   void suspendTarget( const DString& strTarget );

   /**
    * Allow a concrete log target which was previously suspended by a
    * call to suspendTarget to resume writing data.
    * 
    * @param strTarget Unique name of the concrete log target to restart.
    * 
    * @see #suspendTarget
    */
   void restartTarget( const DString& strTarget );

   /**
    * Determine if the specified concrete log target exists for this
    * log.
    * 
    * @param strTarget Unique name of concrete log target.
    * 
    * @return true if the concrete log target exists already.
    */
   bool hasTarget( const DString& strTarget ) const;

   AbstractLogTarget* getTarget( const DString& strTarget );

   /**
    * inserter to allow no-argument functions to be streamed
    * into this log (e.g. bf::log::endl)
    * 
    * @param _F     function to call
    * 
    * @return reference to this log
    */
   Log& operator<<( Log& (__cdecl *_F)(Log&)) {
      return((*_F)(*this)); 
   }

   /**
    * inserter to allow I_CHARs to be written to the log
    * 
    * @param c      Character to write
    * 
    * @return reference to this log
    */
   Log& operator<<( I_CHAR c ) { 
      if( getReportingThreshold() < LogStream::Level::e_silent ) {
         stream().put( c ); 
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
   Log& operator<<( int i ) { 
      if( getReportingThreshold() < LogStream::Level::e_silent ) {
         stream().put( i );
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
   Log& operator<<( unsigned int i ) { 
      if( getReportingThreshold() < LogStream::Level::e_silent ) {
         stream().put( i );
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
   Log& operator<<( long l ) { 
      if( getReportingThreshold() < LogStream::Level::e_silent ) {
         stream().put( l );
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
   Log& operator<<( unsigned long l ) { 
      if( getReportingThreshold() < LogStream::Level::e_silent ) {
         stream().put( l );
      }
      return( *this ); 
   }

   Log& operator<<( const void* p ) { 
      if( getReportingThreshold() < LogStream::Level::e_silent ) {
         stream().put( reinterpret_cast<unsigned long>(p) );
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
   Log& operator<<( float f ) { 
      if( getReportingThreshold() < LogStream::Level::e_silent ) {
         stream().put( f );
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
   Log& operator<<( double d ) { 
      if( getReportingThreshold() < LogStream::Level::e_silent ) {
         stream().put( d );
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
   Log& operator<<( const I_CHAR* p ) { 
      if( getReportingThreshold() < LogStream::Level::e_silent ) {
         stream().put( p );
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
   Log& operator<<( const DString& str ) { 
      if( getReportingThreshold() < LogStream::Level::e_silent ) {
         stream().put( str );
      }
      return( *this ); 
   }

   /**
    * Get the LogStream for the current thread.  It is not possible to
    * get the LogStream for a different thread.
    * 
    * @return Reference to the LogStream for the current thread.  If the current
    *         thread has no LogStream for this log then a LogStream will be
    *         created for this thread.
    * @see LogStream
    */
   inline LogStream& stream()
   {
      BFGuard g( csStreams_ );
      unsigned long ulTID = ::GetCurrentThreadId();
      STREAM_MAP::iterator it = mapStreams_.find( ulTID );
      if( mapStreams_.end() != it )
      {
         return( *(*it).second );
      }
      LogStream* pStream = new bf::log::LogStream( this );
      mapStreams_[ ulTID ] = pStream;
      return( *pStream );
   }

   /**
    * Attach a LogStream object to this log for the current thread.
    */
   void attachThread() { stream(); }
   /**
    * Remove and destroy the LogStream object for the current thread from
    * this log.
    */
   void detachThread()
   {
      BFGuard g( csStreams_ );
      STREAM_MAP::iterator itStream = mapStreams_.find( ::GetCurrentThreadId() );
      if( mapStreams_.end() != itStream ) {
         delete (*itStream).second;
         mapStreams_.erase( itStream );
      }
   }

   /**
    * Set the Reporting Threshold for this log.  
    * 
    * Each LogStream which is attached to this log has a 'Reporting Level'
    * which defined by using one of the streaming operators notify, 
    * informational, warning, severe, and critical.  When data is
    * streamed into the LogStream for a thread the LogStream's reporting
    * level is compared with the Reporting Threshold for the log itself.
    * If the LogStream's reporting level is less than the log's 
    * Reporting Threshold then the data is not appended to the LogStream.
    * 
    * @param eReportingThreshold
    *               The new Reporting Threshold to set.
    * 
    * @see bf::log::LogStream::Level
    */
   inline void setReportingThreshold( enum LogStream::Level eReportingThreshold ) 
   {
      BFGuard g( csReporting_ );
      eReportingThreshold_ = eReportingThreshold;
   }
   /**
    * Get the current Reporting Threshold for this log.
    * 
    * @return 
    */
   inline enum LogStream::Level getReportingThreshold() const
   {
      BFGuard g( csReporting_ );
      return(eReportingThreshold_);
   }

   inline void setReportingCategory( enum Category eCategory, bool bSet ) {
      BFGuard g( csReporting_ );
      if( bSet ) fReportingCategories_ |= eCategory;
      else fReportingCategories_ &= ~eCategory;
   }
   inline void setReportingCategory( unsigned int fCat ) {
      BFGuard g( csReporting_ );
      fReportingCategories_ = fCat;
   }
   inline bool isReportingFor( enum Category eCategory ) const { 
      BFGuard g( csReporting_ );
      return( ( fReportingCategories_ & eCategory ) == eCategory );
   }

   bool isOkToLog( enum LogStream::Level eLevel, unsigned long fCat ) const;

   void join( const LogStream* pLogStream );

   void flushAll();     // flush all targets
   void flushStream( LogStream* pLogStream );

   void setbase( unsigned int numBase ) {
      stream().setbase( numBase );
   }

private:
   mutable BFCritSec csReporting_;
   void setReportingLevel( enum LogStream::Level eCurr );
   void setCategory( unsigned long fCat );

   // simple map of log targets
   typedef std::map< DString, AbstractLogTarget* > TARGET_MAP;
   TARGET_MAP mapTargets_;
   mutable BFCritSec csTargets_;       // guard the map of log targets

   // simple map of log streams (one per thread)
   typedef std::map< unsigned long, LogStream* > STREAM_MAP;
   STREAM_MAP mapStreams_;
   mutable BFCritSec csStreams_;       // guard the map of the streams

   enum LogStream::Level eReportingThreshold_;     // minimum reporting level to record
   unsigned long fReportingCategories_;            // bit array of categories to report on

};

inline Log& __cdecl endl( Log& l )
{
   l << I_( "\n" );
   return( l );
}

inline Log& __cdecl endlf( Log& l )
{
   l << I_( "\n" );
   l.flushAll();
   return( l );
}

inline Log& __cdecl flush( Log& l )
{
   l.flushAll();
   return( l );
}

inline Log& __cdecl hex( Log& l )
{
   l.setbase(16);
   return( l );
}

inline Log& __cdecl dec( Log& l )
{
   l.setbase(10);
   return( l );
}

/*==========================================================================
 *------------------------ Reporting Level functions -----------------------
 *==========================================================================*/
inline Log& __cdecl ldebug( Log& l ) 
{
   l.setReportingLevel( LogStream::Level::e_debug );
   return( l );
}

inline Log& __cdecl ltrace( Log& l ) 
{
   l.setReportingLevel( LogStream::Level::e_trace );
   return( l );
}

inline Log& __cdecl notify( Log& l ) 
{
   l.setReportingLevel( LogStream::Level::e_notify );
   return( l );
}

inline Log& __cdecl information( Log& l ) 
{
   l.setReportingLevel( LogStream::Level::e_information );
   return( l );
}

inline Log& __cdecl warning( Log& l ) 
{
   l.setReportingLevel( LogStream::Level::e_warning );
   return( l );
}

inline Log& __cdecl severe( Log& l ) 
{
   l.setReportingLevel( LogStream::Level::e_severe );
   return( l );
}

inline Log& __cdecl critical( Log& l ) 
{
   l.setReportingLevel( LogStream::Level::e_critical );
   return( l );
}

/*==========================================================================
 *---------------------- Reporting Category functions ----------------------
 *==========================================================================*/
// these functions work on a thread basis.
template<class _Tm>
struct logmanip
{
   logmanip(void (__cdecl *_F)(Log&, _Tm), _Tm _A)
   : _Pf(_F), _arg(_A) {}
   void (__cdecl *_Pf)(Log&, _Tm);
   _Tm _arg;
};

template<class _Tm> inline
Log& _cdecl operator<<( Log& _L, const logmanip<_Tm>& _M)
{(*_M._Pf)(_L, _M._arg);
   return(_L);}

BFUTIL_LINKAGE logmanip< unsigned long > __cdecl setcat( unsigned long );

extern BFUTIL_LINKAGE Log theLog;


}  // namespace log
}  // namespace bf

//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/core/bf/log/log.hpp-arc  $
//
//   Rev 1.1   Feb 20 2009 14:33:58   purdyech
//ZTS Revision 6
//
//   Rev 1.0   Aug 12 2003 10:14:08   PURDYECH
//Initial revision.
//
