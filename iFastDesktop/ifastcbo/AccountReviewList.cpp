//*****************************************************************************
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
//*****************************************************************************
//
// ^FILE   : AccountReviewList.cpp
// ^AUTHOR : 
// ^DATE   : 
//
//-----------------------------------------------------------------------------
//
// ^CLASS  : AccountReviewList
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS :
//
//*****************************************************************************
#include "stdafx.h"
#include "accountreviewlist.hpp"
#include "accountreview.hpp"
#include <ifastdataimpl\dse_dstc0204_vw.hpp>
#include <ifastdataimpl\dse_dstc0204_req.hpp>
#include <ifastdataimpl\dse_dstc0149_vw.hpp>
#include "MgmtCoOptions.hpp"
#include "DSTCommonFunction.hpp"
#include <bfutil\bfdate.hpp>

namespace
{
   // Trace literals
   const I_CHAR * const CLASSNAME = I_( "AccountReviewList" );
}

namespace CND
{
   extern const long ERR_ACCOUNTREVIEW_REVIEW_DATE_EARLIER;
   extern const long ERR_ACCOUNTREVIEW_SCHEDULED_DATE_EARLIER;
}

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest ACCOUNTREVIEW_LIST;
}

//******************************************************************************

AccountReviewList::AccountReviewList( BFAbstractCBO &parent ) 
: MFCanBFCbo( parent ), 
m_bOverrideScheduledDateFlag( false ),
m_iReviewMonths( 12 ),
m_requestData(ifds::DSTC0204_REQ)
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   setObjectAsList( );
}

//******************************************************************************

AccountReviewList::~AccountReviewList()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************

SEVERITY AccountReviewList::init()
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("init") );
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************

SEVERITY AccountReviewList::init( const DString& accountNum, 
                                  const DString& dstrTrack,
                                  const DString& dstrPageName )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("init") );

   DString mgmtCoIdOut;
   m_requestData.setElementValue( ifds::CompanyId, getMgmtCoId( mgmtCoIdOut ) );
   m_requestData.setElementValue( ifds::AccountNum, accountNum  );
   m_requestData.setElementValue( ifds::Track, dstrTrack );
   m_requestData.setElementValue( ifds::Activity, dstrPageName );

   ReceiveData(DSTC_REQUEST::ACCOUNTREVIEW_LIST, m_requestData, ifds::DSTC0204_VW, DSTCRequestor( getSecurity(), false) );

   // Get Account Review values from MgmtCoOption
   getAccountReviewSettings();

   // Set Read-only flag appropriately
   setReadOnlyFieldsBasedOnRules(BF::HOST);

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************

SEVERITY AccountReviewList::doCreateNewObject( BFCBO *& pBase, DString &strKey, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateNewObject" ) );
   AccountReview *pAccountReview = new AccountReview( *this );

   pAccountReview->init( idDataGroup );
   pBase = pAccountReview;
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************

SEVERITY AccountReviewList::doCreateObject( const BFData& data, BFCBO *&pObjOut )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateObject" ) );

   pObjOut = new AccountReview( *this );
   ( ( AccountReview* ) ( pObjOut ) )->init( data );

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************

SEVERITY AccountReviewList::getMore()
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getMore" ) );

   if( doMoreRecordsExist() )
   {
      ReceiveData(DSTC_REQUEST::ACCOUNTREVIEW_LIST, m_requestData, ifds::DSTC0204_VW, DSTCRequestor( getSecurity(), false) );
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************

void AccountReviewList::getAccountReviewSettings()
{
   DString dstrTemp;

   getWorkSession().getMgmtCoOptions()->getField(ifds::OverrideReviewDate, dstrTemp, BF::HOST, false );
   dstrTemp.stripAll().upperCase();
   m_bOverrideScheduledDateFlag = (dstrTemp == I_("Y"));

   getWorkSession().getMgmtCoOptions()->getField(ifds::ReviewMnths, dstrTemp, BF::HOST, false );
   dstrTemp.stripAll().upperCase();
   m_iReviewMonths = dstrTemp.asInteger();

}

//******************************************************************************

SEVERITY AccountReviewList::setReadOnlyFieldsBasedOnRules(const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "initializeFieldsBasedOnRules()" ) );

   DString dstrActualReviewDate;
   bool bReadOnlyStarted = false;

   // Set Read-Only flags according to position
   BFObjIter iter( *this, idDataGroup, 0, BFObjIter::ITERTYPE::NON_DELETED);
   if( iter.getNumberOfItemsInList() )
   {
      if( !iter.end() )
      {
         iter.getObject()->setFieldReadOnly( ifds::ActualReviewDate, idDataGroup, false );   
         iter.getObject()->getField( ifds::ActualReviewDate, dstrActualReviewDate, idDataGroup, false );
         if( !dstrActualReviewDate.empty() )
         {
            bReadOnlyStarted = true;
         }

         // Set Read-Only flag for Scheduled Date based on Scheduled Date Flag.
         if( m_bOverrideScheduledDateFlag )
         {
            iter.getObject()->setFieldReadOnly( ifds::SchedReviewDate, idDataGroup, false );
         }
      }
      // Set second item appropriately
      if( !iter.end() )
      {
         ++iter;
         if( !iter.end() )
         {
            iter.getObject()->setFieldReadOnly( ifds::ActualReviewDate, idDataGroup, bReadOnlyStarted );   
         }
      }
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************

SEVERITY AccountReviewList::validateActualReviewDate(BFAbstractCBO *pBFAbstractCBO, const DString& dstrValue, const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateActualReviewDate" ) );

   DString dstrCurrentSchedReviewDate, dstrLastActualReviewDate, dstrActualReviewDate, dstrSchedReviewDate;
   pBFAbstractCBO->getField( ifds::SchedReviewDate, dstrCurrentSchedReviewDate, idDataGroup, false );

   BFObjIter iter( *this, idDataGroup, 0, BFObjIter::ITERTYPE::NON_DELETED);
   while( !iter.end() )
   {
      iter.getObject()->getField ( ifds::SchedReviewDate, dstrSchedReviewDate, idDataGroup, false );
      if( dstrCurrentSchedReviewDate.compare( dstrSchedReviewDate ) == 0 )
      {
         ++iter;
         if( !iter.end() )
         {
            iter.getObject()->getField( ifds::ActualReviewDate, dstrLastActualReviewDate, idDataGroup, false );
            pBFAbstractCBO->getField( ifds::ActualReviewDate, dstrActualReviewDate, idDataGroup, false );
            if( DSTCommonFunctions::CompareDates ( dstrLastActualReviewDate, dstrActualReviewDate ) != DSTCommonFunctions::FIRST_EARLIER )
            {
               ADDCONDITIONFROMFILE( CND::ERR_ACCOUNTREVIEW_REVIEW_DATE_EARLIER );
               return(GETCURRENTHIGHESTSEVERITY());
            }
         }
      }
      if( !iter.end() )
      {
         ++iter;
      }
   }       
   return(NO_CONDITION);
}

//******************************************************************************

SEVERITY AccountReviewList::validateScheduledReviewDate(const DString& dstrValue, const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateScheduledReviewDate" ) );

   DString dstrLastSchedReviewDate, dstrSchedReviewDate;

   BFObjIter iter( *this, idDataGroup, 0, BFObjIter::ITERTYPE::NON_DELETED);
   if( !iter.end() )
   {
      iter.getObject()->getField( ifds::SchedReviewDate, dstrSchedReviewDate, idDataGroup, false );
      ++iter;
      if( !iter.end() )
      {
         iter.getObject()->getField( ifds::SchedReviewDate, dstrLastSchedReviewDate, idDataGroup, false );
         if( DSTCommonFunctions::CompareDates ( dstrLastSchedReviewDate, dstrSchedReviewDate ) != DSTCommonFunctions::FIRST_EARLIER )
         {
            ADDCONDITIONFROMFILE( CND::ERR_ACCOUNTREVIEW_SCHEDULED_DATE_EARLIER );
            return(GETCURRENTHIGHESTSEVERITY());
         }
      }
   }

   return(NO_CONDITION);
}

//******************************************************************************

SEVERITY AccountReviewList::applyScheduleReviewDateChange(BFAbstractCBO *pBFAbstractCBO, const BFFieldId& idField, const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "applyScheduleReviewDateChange" ) );

   DString dstrCurrentActualReviewDate, dstrActualReviewDate, dstrSchedReviewDate, dstrNewSchedReviewDate;
   pBFAbstractCBO->getField( ifds::ActualReviewDate, dstrCurrentActualReviewDate, idDataGroup, false );

   BFObjIter iter( *this, idDataGroup, 0, BFObjIter::ITERTYPE::NON_DELETED);
   BFAbstractCBO *pLastObj = iter.getObject();
   while( !iter.end() )
   {
      iter.getObject()->getField ( ifds::ActualReviewDate, dstrActualReviewDate, idDataGroup, false );
      if( dstrCurrentActualReviewDate.compare( dstrActualReviewDate ) == 0 )
      {
         if( iter.getObject() != pLastObj )
         {
            addMonthsToDate( dstrActualReviewDate, dstrNewSchedReviewDate, m_iReviewMonths );
            pLastObj->setField( ifds::SchedReviewDate, dstrNewSchedReviewDate, idDataGroup, false );
				pLastObj->clearUpdatedFlags (idDataGroup);
            return(GETCURRENTHIGHESTSEVERITY());
         }
      }
      pLastObj = iter.getObject();
      ++iter;
   }       
   return(NO_CONDITION);
}

//******************************************************************************

void AccountReviewList::addMonthsToDate(DString& dstrDateIn, DString& dstrDateOut, int iMonthIncrement)
{
   BFDate::DATE_FORMAT fmt = BFDate::inferFormat( dstrDateIn.c_str() );
   assert( fmt != BFDate::DF_NULL );
   BFDate dateIn( dstrDateIn.c_str(), fmt );
   dateIn.addMonths( iMonthIncrement );
   dstrDateOut = dateIn.get( fmt );
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/AccountReviewList.cpp-arc  $
// 
//    Rev 1.9   Dec 07 2005 15:41:28   AGUILAAM
// IN 485796 - update record with blank actual review date will not be sent by Desktop; will be updated on the View side.
// 
//    Rev 1.8   Mar 21 2003 17:55:08   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.7   Oct 09 2002 23:53:54   PURDYECH
// PVCS Database Conversion
// 
//    Rev 1.6   Aug 29 2002 12:54:54   SMITHDAV
// ClientLocale and typed field changes.
// 
//    Rev 1.5   Jul 05 2002 11:49:38   PURDYECH
// Infrastructure Fixup ... no more ICU!
// 
//    Rev 1.4   Jun 24 2002 18:11:48   HERNANDO
// Cleaned - setReadOnlyFieldsBasedOnRules.
// 
//    Rev 1.3   07 Jun 2002 17:40:32   HERNANDO
// Revised addMonthsToDate calculation.
// 
//    Rev 1.2   31 May 2002 14:23:48   HERNANDO
// Revised for Rel47.
// 
//    Rev 1.1   22 May 2002 18:26:14   PURDYECH
// BFData Implementation
// 
//    Rev 1.0   08 May 2002 18:58:42   HERNANDO
// Initial revision.
// 
 * 
*/