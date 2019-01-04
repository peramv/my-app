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
// ^FILE   :  BFAbstractRequestor.cpp
// ^AUTHOR :  David Smith
// ^DATE   :  September 2000
//
// ----------------------------------------------------------
#include <srcprag.h>
#include <bfdata\bfdata.hpp>
#include <bfdata\bfdatafielditer.hpp>
#include "dbrkrlogger.hpp"
#include <conditionmanager.hpp>
#include "bfabstractrequestor.hpp"
#include "bfrequest.hpp"
#include "bfwritebuffer.hpp"
#include "bfreadbuffer.hpp"
#include <bfutil\txnstats.hpp>
#include <bfutil\bfhrtimer.hpp>

#include "bfviewtimelog.hpp"

class ViewTimeTxnStatElement : public TxnStatElement
{
public:
   ViewTimeTxnStatElement( const DString& name,
                           unsigned long  elapsed,
                           unsigned long  assignTime )
   : _name( name )
   , _elapsed( elapsed )
   , _assignTime( assignTime )
   {
   }

   virtual const DString& getName() const
   {
      return(_name);
   }

   virtual DString getAsIDIString() const
   {
      DString dstrIDI;
      dstrIDI =  I_( "ViewName=" );
      dstrIDI += getName();
      dstrIDI += I_( ";ViewTime=" );
      dstrIDI += DString::asString( _elapsed );
      dstrIDI += I_( ";ViewAssignTime=" );
      dstrIDI += DString::asString( _assignTime );
      dstrIDI += I_( ";" );
      return( dstrIDI );
   }

   virtual void writeXML( BFDocument& out )
   {
      ElementWriter ew( out, I_("View") );
      ElementWriter::write( out, I_("Name"),        getName() );
      ElementWriter::write( out, I_("ElapsedTime"), DString::asString( _elapsed ) );
      ElementWriter::write( out, I_("AssignTime"),  DString::asString( _assignTime ) );
   }

private:
   DString        _name;
   unsigned long  _elapsed;
   unsigned long  _assignTime;
};


namespace
{
   const I_CHAR *const CLASSNAME = I_( "AbstractRequestor" );
   const I_CHAR *const RECEIVE = I_( "receive" );
   const I_CHAR *const PARSE_BUFFER_COMPONENT  = I_( "parseBufferComponent" );
   const I_CHAR *const PARSE_BUFFER  = I_( "parseBuffer" );
}

namespace CND
{
   extern const I_CHAR *BFDBRKR_CONDITION;
   extern const long MISSMATCHING_VIEW_LAYOUT;
}

//******************************************************************************
BFAbstractRequestor::BFAbstractRequestor()
: _assignTime( -1 )
, arLogger_( new DbrkrLogger() )
{
}

//******************************************************************************
BFAbstractRequestor::BFAbstractRequestor( const BFAbstractRequestor& rhs )
: _assignTime( -1 )
, arLogger_( new DbrkrLogger() )
{
}

//******************************************************************************
BFAbstractRequestor::~BFAbstractRequestor()
{
}

//******************************************************************************
SEVERITY
BFAbstractRequestor::receive( const BFRequest &request, 
                              BFData &queryData, 
                              BFData &receivedData, 
                              bool *outMoreAvailable /*= NULL*/ )
{
   MAKEFRAMEAUTOPROMOTE2( CND::BFDBRKR_CONDITION, CLASSNAME, RECEIVE );

   // allocate the request record (implemented by deriving class)
   BFWriteBuffer *requestBuffer = NULL;
   BFReadBuffer *responseBuffer = NULL;
   arLogger_->setFileName( queryData.getName() );
   if( NULL != outMoreAvailable )
   {
      *outMoreAvailable = false;
   }

   try
   {
      arLogger_->logData ( I_("*********************** REQUEST ") + queryData.getName() + I_(" ************************\n"));
      logCallingTime();
      requestBuffer = createRequestBuffer(request);
      // build the request record
      formatBuffer( queryData, requestBuffer );

      // do the recieve call (implemented by deriving class)
      SEVERITY severity = receiveBuffer( request, requestBuffer, &responseBuffer, &queryData );

      if( WARNING < severity || NULL == responseBuffer )
      {
         delete requestBuffer;
         requestBuffer = NULL;
         return(GETCURRENTHIGHESTSEVERITY());
      }
      arLogger_->logData ( requestBuffer, responseBuffer, queryData.getName());
      delete requestBuffer;
      requestBuffer = NULL;

      arLogger_->logData ( I_("\n*********************** RESPONSE ") + receivedData.getName() + I_(" ***********************\n"));
      // parse the response record
      parseBuffer( responseBuffer, receivedData );

      TxnStats* pTxnStats = TxnStats::get();
      if( pTxnStats->isEnabled() )
      {
         ViewTimeTxnStatElement* pElem = new ViewTimeTxnStatElement( request.getId() , getRequestTime(), getAssignTime() );
         pTxnStats->addElement( I_( "ViewLog" ), pElem );
      }
      BFViewTimeLog::getInstance().log( request.getId(), getRequestTime() );

      delete responseBuffer;
      responseBuffer = NULL;
   }
   catch( ConditionException &ce )
   {
      delete requestBuffer;
      delete responseBuffer;
      SETCONDITIONFROMEXCEPTION(ce);
   }
   catch( ... )
   {
      delete requestBuffer;
      delete responseBuffer;
      // throw unknown excetion
      throw;
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
unsigned long BFAbstractRequestor::getAssignTime() const
{
   return( _assignTime );
}


//******************************************************************************
void
BFAbstractRequestor::formatBuffer(const BFData &queryData, BFWriteBuffer *requestBuffer ) const
{
   requestBuffer->writeStart();
   {
      requestBuffer->writeStartFixed();
      arLogger_->logData ( I_("**FIXED SECTION**\n" ));
      BFConstDataFieldIter dataIter( queryData );
      for( ;dataIter; ++dataIter )
      {
         requestBuffer->writeField( queryData, dataIter().getId() );
         arLogger_->logData ( queryData, dataIter().getId() );
      }

      requestBuffer->writeEndFixed();
   }

   if( 0 != queryData.getRepeatId() )
   {
      unsigned long cRepeats = queryData.getRepeatCount();
      DString dstrRepeat;
      if( cRepeats )
      {
         requestBuffer->writeStartRepeatSection();

         for( unsigned long repeatIndex = 0; repeatIndex < cRepeats; ++repeatIndex )
         {
            requestBuffer->writeStartRepeat();

            dstrRepeat.convertIntToString( repeatIndex + 1 );
            arLogger_->logData ( I_("\n**REPEAT COUNT ") + dstrRepeat + I_(" **\n" ));
            BFConstDataFieldIter dataIter( queryData.getRepeat( repeatIndex ) );
            for( ;dataIter; ++dataIter )
            {
               requestBuffer->writeField( queryData.getRepeat( repeatIndex ), dataIter().getId() );
               arLogger_->logData ( queryData.getRepeat( repeatIndex ), dataIter().getId() );
            }
            requestBuffer->writeEndRepeat();
         }

         requestBuffer->writeEndRepeatSection();
      }
   }

   requestBuffer->writeEnd();
}


//******************************************************************************
void BFAbstractRequestor::parseBuffer(BFReadBuffer *responseBuffer, BFData &receivedData ) const
{
   MAKEFRAMEAUTOPROMOTE2( CND::BFDBRKR_CONDITION, CLASSNAME, PARSE_BUFFER_COMPONENT );
   BFHRTimer t;
   responseBuffer->readStart();

   responseBuffer->readStartFixed();
   arLogger_->logData ( I_("** FIXED SECTION **\n" ));
   // parse fixed portion
   parseBufferComponent(responseBuffer, receivedData );
   responseBuffer->readEndFixed();

   const BFDataId& idRepeat = receivedData.getRepeatId();

   if(idRepeat.getId() == 0 && !responseBuffer->isAtEnd())
   {
      const BFDataId& id = receivedData.getId();
      DString idiStr;
      addIDITagValue(idiStr, I_("VIEW_ID"), id.getName());

      ADDCONDITIONFROMFILEIDI(CND::MISSMATCHING_VIEW_LAYOUT, idiStr);
      return;
   }
   if( responseBuffer->readStartRepeatSection() )
   {
      if( !receivedData.exists( DEFAULT_REPEAT_RECORD ) )
      { // not repeatable but parsing repeat section
         assert(0);
         throw;
      }


      BFData repeatData( idRepeat );
      DString dstrRepeat;
      int iRepeat = 0;
      while( responseBuffer->readStartRepeat() )
      {
         dstrRepeat.convertIntToString( ++iRepeat );
         arLogger_->logData ( I_("\n** REPEAT COUNT ") + dstrRepeat + I_(" **\n" ));
         // parse repeat
         parseBufferComponent(responseBuffer, repeatData );

         receivedData.addRepeat(repeatData);
         repeatData.resetValue();      // done by following code more creatively

         responseBuffer->readEndRepeat();
      }

      responseBuffer->readEndRepeatSection();
   }

   responseBuffer->readEnd();

   _assignTime = t.elapsed() + ( ( _assignTime == -1 ) ? 0 : _assignTime );

}


//******************************************************************************
void BFAbstractRequestor::parseBufferComponent(BFReadBuffer *responseBuffer, BFData &data ) const
{
   MAKEFRAMEAUTOPROMOTE2( CND::BFDBRKR_CONDITION, CLASSNAME, PARSE_BUFFER_COMPONENT );
   DString elementValue;
   BFDataFieldIter dIter( data );
   for( ;dIter; ++dIter )
   {
      const BFDataField& df = dIter();
      const BFDataFieldProperties* fieldProp = df.getProperties();
      if(responseBuffer->isAtEnd())
      {
         const BFDataId& id = data.getId();
         DString idiStr;
         addIDITagValue(idiStr, I_("VIEW_ID"), id.getName());

         ADDCONDITIONFROMFILEIDI(CND::MISSMATCHING_VIEW_LAYOUT, idiStr);
      }
      else if(responseBuffer->readField(*fieldProp, elementValue) )
      {
         data.setElementValue( df.getId(), elementValue, false, false );
         arLogger_->logData ( df.getId().getName(), elementValue );
      }
      else
      {
         arLogger_->logData ( df.getId().getName(), I_("**NULL**") );
      }
   }
}

//******************************************************************************
void BFAbstractRequestor::logData ( const DString &fieldName, const DString &fieldValue )
{
   arLogger_->logData ( fieldName, fieldValue );
}

//******************************************************************************
void BFAbstractRequestor::logData ( const DString &dstrOutput )
{
   arLogger_->logData ( dstrOutput );
}

//******************************************************************************
void BFAbstractRequestor::logData ( const BFWriteBuffer* pRequestBuffer, const BFReadBuffer* pResponseBuffer, const DString& dstrLabel )
{
   arLogger_->logData ( pRequestBuffer, pResponseBuffer, dstrLabel );
}

//******************************************************************************
//RevisionControlEntries
//******************************************************************************
//
/*$Log:   Y:/VCS/BF iFAST/core/bfdbrkr/BFAbstractRequestor.cpp-arc  $
//
//   Rev 1.24   May 16 2012 18:08:34   dchatcha
//P0186479 FN10 -Gap 14G - Block Service Unit Transfers, helper key to track view calling time.
//
//   Rev 1.23   Oct 21 2009 10:44:12   purdyech
//LDAP Authorization Support
//
//   Rev 1.22   Mar 27 2009 10:15:02   purdyech
//Added more JMSProperties to ZTS request messages.
//
//   Rev 1.21   Mar 05 2004 13:27:28   SMITHDAV
//Make changes to support new ElementWriter semantics.
// 
//    Rev 1.20   Apr 10 2003 10:50:38   PURDYECH
// Use BFFieldId::getName() instead of BFDataFieldProperties::getName() to get field names
// 
//    Rev 1.19   Oct 09 2002 17:40:36   PURDYECH
// New PVCS Database
// 
//    Rev 1.18   Sep 19 2002 09:28:12   IVESPAUL
// Adapted the transaction stats to write results using XML ElementWriter.  Moved ElementAttribute and ElementWriter to BFUtil.
//
//    Rev 1.17   Sep 09 2002 13:36:12   PURDYECH
// Added dtor and copy ctor.
// Removed redundant and obsolete code.
//
//    Rev 1.16   Aug 29 2002 12:49:26   PURDYECH
// ClientLocale and Field corrections
//
//    Rev 1.15   May 28 2002 12:15:38   PURDYECH
// BFData Implementation - Phase II
//
//    Rev 1.14   22 May 2002 17:56:06   PURDYECH
// BFData Implementation
//
//    Rev 1.13   22 Mar 2002 15:17:08   PURDYECH
// BFData integration
//
//    Rev 1.12   26 Oct 2001 12:09:58   HSUCHIN
// minor fix to support error response.
//
//    Rev 1.11   26 Oct 2001 11:03:30   HSUCHIN
// added support to log raw transaction request/response
//
//    Rev 1.10   26 Sep 2001 10:25:16   PURDYECH
// Added ViewTimeLogging through BFViewTimeLog
//
//    Rev 1.9   18 Sep 2001 15:20:46   PURDYECH
// Get STUB_DATA working again.
//
//    Rev 1.8   10 Aug 2001 11:28:46   PURDYECH
// Added code to reset the fields of the re-used Repeat data object in BFAbstractRequestor::parseBuffer
//
//    Rev 1.7   07 Aug 2001 11:24:44   PURDYECH
// Added code to get timing data for the assignment of incoming data to a Data object.
//
//    Rev 1.6   24 Jul 2001 14:43:50   HSUCHIN
// added method logData so that dervived classes can log data
//
//    Rev 1.5   19 Jul 2001 11:57:52   HSUCHIN
// added logic to log NULL data object
//
//    Rev 1.4   09 Jul 2001 15:44:10   SMITHDAV
// Fix double delete of logger when an exception  is caught.
//
//    Rev 1.3   03 Jul 2001 15:45:20   HSUCHIN
// bug fix again relating to format buffer
//
//    Rev 1.2   03 Jul 2001 14:09:22   YINGZ
// bug fix
//
//    Rev 1.1   28 Jun 2001 14:22:16   HSUCHIN
// added logging capabilities
//
//    Rev 1.6   14 Jun 2001 15:00:52   HSUCHIN
// added logging capabilities.
//
//    Rev 1.5   10 May 2001 11:15:08   SMITHDAV
// Sync-up from 1.3.1.0.
//
//    Rev 1.4   03 May 2001 14:03:06   SMITHDAV
// Session management restructuring.
//
//    Rev 1.3   09 Feb 2001 14:32:02   SMITHDAV
// Cleaned-up exception processing...
//
//    Rev 1.2   Nov 06 2000 15:42:18   YINGBAOL
// fix setElementValue issue
 *
 */
