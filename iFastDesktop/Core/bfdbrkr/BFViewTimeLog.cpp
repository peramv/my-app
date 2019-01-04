//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by DST Systems, Inc.,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 1999 by DST Systems, Inc.
//
//
//******************************************************************************
//
// ^FILE   :  BFViewTimeLog.cpp
// ^AUTHOR :  Chris Purdye
// ^DATE   :  September 2001
//
// ----------------------------------------------------------
#define NOMINMAX
#include <SrcPrag.h>

#include "BFViewTimeLog.hpp"
#include <configmanager.hpp>
#include <bfutil\BFGuard.hpp>
#include <iomanip>


typedef std::deque< const ViewTimeEntry* > VIEWTIMEENTRY_DECK;
typedef VIEWTIMEENTRY_DECK::iterator VIEWTIMEENTRY_DECK_ITER; 
typedef VIEWTIMEENTRY_DECK::reverse_iterator VIEWTIMEENTRY_DECK_RITER; 

static BFCritSec      s_csDeck;

static VIEWTIMEENTRY_DECK& getViewTimeDeck()
{
   static VIEWTIMEENTRY_DECK s_VTE;
   return( s_VTE );
}

const ViewTimeEntry* ViewTimeEntry::getViewTimeEntry( const ViewTimeEntry* p ) {
   BFGuard g(s_csDeck);
   if( p == NULL ) {
      // get first entry
      VIEWTIMEENTRY_DECK_RITER it = getViewTimeDeck().rbegin();
      if( it != getViewTimeDeck().rend() ) {
         return *it;
      }
      return( NULL );
   }
   for( VIEWTIMEENTRY_DECK_RITER it = getViewTimeDeck().rbegin(); it != getViewTimeDeck().rend(); ++it ) {
      if( *it == p ) {
         ++it;
         if( it != getViewTimeDeck().rend() ) {
            return( *it );
         }
         return( NULL );
      }
   }
   return( NULL );
}

static size_t s_sizeViewTimeEntryDeck = 200;

void ViewTimeEntry::recordViewTimeEntry( const DStringA& viewName, 
                                         const DStringA& msgId,
                                         unsigned long sendTime,
                                         unsigned long receiveTime,
                                         unsigned long unitOfWorkTime,
                                         unsigned long networkTime,
                                         unsigned long oeInvocationTime,
                                         unsigned long viewTime,
                                         unsigned long preViewTime,
                                         unsigned long postViewTime)
{
   ViewTimeEntry* p = new ViewTimeEntry( viewName, msgId, 
                                         sendTime,
                                         receiveTime,
                                         unitOfWorkTime,
                                         networkTime,
                                         oeInvocationTime,
                                         viewTime,
                                         preViewTime,
                                         postViewTime);
   VIEWTIMEENTRY_DECK& deck = getViewTimeDeck();
   BFGuard g(s_csDeck);
   while( deck.size() > s_sizeViewTimeEntryDeck ) {
      VIEWTIMEENTRY_DECK_ITER it = deck.begin();
      if( it != deck.end() ) {
         const ViewTimeEntry* pPop = (*it);
         delete pPop;
         deck.pop_front();
      }     
   }
   deck.push_back(p);
   return;
}



BFCritSec      BFViewTimeLog::s_csViewTimeLog_;
BFViewTimeLog *BFViewTimeLog::s_pInstance_ = NULL;
bool           BFViewTimeLog::s_bActive_ = false;


BFViewTimeLog &BFViewTimeLog::getInstance() 
{
   if( NULL == s_pInstance_ )
   {
      DString dstrPath; 
      unsigned int maxUserSize = 0;
	   const unsigned int maxSize = 1024 *512;

      // determine if we are active or not
      if( s_bActive_ = GetConfigValueAsBool( I_("Support"), I_("ViewTimeLog_Enable") ) ) {
         // get the logfile path and maximum filesize
         dstrPath = GetConfigValueAsString( I_("Support"), I_("ViewTimeLog_Path") );
         if( dstrPath.empty() ) {
            // path not specified ... turn 'active' off
            s_bActive_ = false;
         }
         else {
            if( dstrPath[ dstrPath.length() - 1 ] != '\\' )
            {
               dstrPath += '\\';
            }

            maxUserSize = GetConfigValueAsInteger( I_("Support"), I_("ViewTimeLog_Size") );
            maxUserSize = std::max( maxSize, maxUserSize );
         }
      }
      s_pInstance_ = new BFViewTimeLog( dstrPath, maxUserSize );
   }


   return( *s_pInstance_ );
}

void BFViewTimeLog::killInstance()
{
   delete s_pInstance_;
   s_pInstance_ = NULL;
}

void BFViewTimeLog::enable( bool b ) {
   s_bActive_ = b;
}

BFViewTimeLog::BFViewTimeLog( const DString &dstrPath, int maxSize )
: dstrPath_( dstrPath )
, maxSize_( maxSize )
{
   if( !maxSize_ ) {
      maxSize_ = 65536;
   }
}

BFViewTimeLog::~BFViewTimeLog()
{
}

void BFViewTimeLog::log( const DString &viewName, int requestTime )
{
   if( false == s_bActive_ ) {
      return;
   }

   BFGuard g( s_csViewTimeLog_ );

   // open the log file
   std::ofstream of;
   openFile( of );

   // write to the file 
   // date time viewname time(msec)
   SYSTEMTIME st;
   GetSystemTime( &st );
   of << std::setfill('0') << std::setw( 4 ) << st.wYear << "-" << std::setw(2) << st.wMonth << "-" << std::setw(2) << st.wDay;
   of << "  " << std::setw(2) << st.wHour << ":" << std::setw(2) << st.wMinute << ":" << std::setw(2) << st.wSecond << "." << std::setw(3) << st.wMilliseconds;
   of << "  " << viewName.asA().c_str();
   of << "  " << requestTime;
   of << std::endl;
}

void BFViewTimeLog::log( const DStringA& viewName, 
                         const DStringA& msgId,
                         unsigned long sendTime,
                         unsigned long receiveTime,
                         unsigned long unitOfWorkTime,
                         unsigned long networkTime,
                         unsigned long viewTime,
                         const char* pszNote )
{
   ViewTimeEntry::recordViewTimeEntry(viewName, msgId, sendTime,receiveTime,unitOfWorkTime,networkTime, -1, viewTime, -1, -1);

   if( false == s_bActive_ ) {
      return;
   }

   BFGuard g( s_csViewTimeLog_ );

   // open the log file
   std::ofstream of;
   openFile( of );

   // write to the file 
   // date time viewname time(msec)
   SYSTEMTIME st;
   GetSystemTime( &st );
   of << std::setfill('0') << std::setw( 4 ) << st.wYear << "-" << std::setw(2) << st.wMonth << "-" << std::setw(2) << st.wDay;
   of << "  " << std::setw(2) << st.wHour << ":" << std::setw(2) << st.wMinute << ":" << std::setw(2) << st.wSecond << "." << std::setw(3) << st.wMilliseconds;
   of << "  " << viewName.c_str();
   of << " [" << msgId.c_str() << "]";
   of << " Snd " << sendTime;
   of << ", Rcv " << receiveTime;
   of << ", UoW " << unitOfWorkTime;
   of << ", Net " << networkTime;
   of << ", Vw " << viewTime;
   if( NULL != pszNote ) {
      of << ", " << pszNote;
   }
   of << std::endl;
}

void BFViewTimeLog::log( const DStringA& viewName, 
                         const DStringA& msgId,
                         unsigned long sendTime,
                         unsigned long receiveTime,
                         unsigned long unitOfWorkTime,
                         unsigned long networkTime,
                         unsigned long oeInvocationTime,
                         unsigned long viewTime,
                         unsigned long preViewTime,
                         unsigned long postViewTime,
                         const char* pszNote )
{
   ViewTimeEntry::recordViewTimeEntry(viewName, msgId, sendTime,receiveTime,unitOfWorkTime,networkTime,oeInvocationTime, viewTime, preViewTime, postViewTime);

   if( false == s_bActive_ )
   {
      return;
   }

   BFGuard g( s_csViewTimeLog_ );

   // open the log file
   std::ofstream of;
   openFile( of );

   // write to the file 
   // date time viewname time(msec)
   SYSTEMTIME st;
   GetSystemTime( &st );
   of << std::setfill('0') << std::setw( 4 ) << st.wYear << "-" << std::setw(2) << st.wMonth << "-" << std::setw(2) << st.wDay;
   of << "  " << std::setw(2) << st.wHour << ":" << std::setw(2) << st.wMinute << ":" << std::setw(2) << st.wSecond << "." << std::setw(3) << st.wMilliseconds;
   of << "  " << viewName.c_str();
   of << " [" << msgId.c_str() << "]";
   of << " Snd " << sendTime;
   of << ", Rcv " << receiveTime;
   of << ", UoW " << unitOfWorkTime;
   of << ", Net " << networkTime;
   of << ", OEInvoke " << oeInvocationTime;
   of << ", Post " << postViewTime;
   if( NULL != pszNote ) {
      of << ", " << pszNote;
   }
   of << std::endl;
}

int BFViewTimeLog::getFileSize( int iFile )
{
   DString dstrFileName = dstrPath_ + DString(I_( "vwtlog.00" ) ) + ::asString( iFile );
   WIN32_FIND_DATA ffd;
   HANDLE h = FindFirstFile( dstrFileName.asA().c_str(), &ffd );
   if( INVALID_HANDLE_VALUE != h )
      FindClose( h );
   return( ffd.nFileSizeLow );
}

bool BFViewTimeLog::rolloverFile( int iFile /* = 3 */)
{
   if( 1 == iFile )
      return( true );

   DString dstrFileNameCurr = dstrPath_ + DString(I_( "vwtlog.00" ) ) + ::asString( iFile - 1 );
   DString dstrFileNameNew = dstrPath_ + DString(I_( "vwtlog.00" ) ) + ::asString( iFile );

   DeleteFile( dstrFileNameNew.asA().c_str() );
   MoveFile( dstrFileNameCurr.asA().c_str(), dstrFileNameNew.asA().c_str() );

   return( rolloverFile( --iFile ) );
}

std::ofstream& BFViewTimeLog::openFile( std::ofstream &of )
{
   // make sure that the '.001' file is not too big
   if( getFileSize( 1 ) > maxSize_ ) {
      rolloverFile();
   }

   DString dstrFileName = dstrPath_ + DString(I_( "vwtlog.001" ) );
   of.open( dstrFileName.asA().c_str(), std::ios::app );
   return( of );
}
