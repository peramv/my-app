//*****************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by DST Canada, Inc.,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2001 by DST Canada, Inc.
//
//*****************************************************************************
//
// ^FILE   : SysIndexList.cpp
// ^AUTHOR : Mihai Virgil Buzila
// ^DATE   : 5/1/01
//
//-----------------------------------------------------------------------------
//
// ^CLASS  : SysIndexList
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS :
//
//*****************************************************************************
#include "stdafx.h"
#include <ifastdataimpl\dse_dstc0119_req.hpp>
#include <ifastdataimpl\dse_dstc0119_vw.hpp>
#include "mgmtcooptions.hpp"
#include "sysindex.hpp"
#include "sysindexlist.hpp"
#include "systematic.hpp"

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest SYS_INDEX;
}

namespace
{
   // Trace literals
   const I_CHAR * const CLASSNAME = I_( "SysIndexList" );
   const I_CHAR * const YES = I_("Y");
}


namespace ifds
{
   extern CLASS_IMPORT const BFDateFieldId StartDate;
   extern CLASS_IMPORT const BFDateFieldId StopDate;
   extern CLASS_IMPORT const BFDateFieldId CurrBusDate;
   extern CLASS_IMPORT const BFTextFieldId IndexExist;
   extern CLASS_IMPORT const BFDateFieldId LastProcessDate;
}

namespace CND
{  // Conditions used
   extern const long ERR_INDEX_DATE_RANGE_OVERLAP;
}

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = {
//  Field DD Id,            State Flags,             Group Flags    
   { ifds::DefaultIndexAmt,  BFCBO::NONE, 0 }, 
   { ifds::DefaultIndexType, BFCBO::NONE, 0 }, 
   { ifds::DefaultIndexFreq, BFCBO::NONE, 0 }, 
   { ifds::DefaultStartDate, BFCBO::NONE, 0 }, 
   { ifds::DefaultEndDate,   BFCBO::NONE, 0 }, 
};

static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );

//******************************************************************************
SysIndexList::SysIndexList( BFAbstractCBO &parent ) :
MFCanBFCbo( parent )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   setObjectAsList( );
}

//******************************************************************************
SysIndexList::~SysIndexList()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************
SEVERITY SysIndexList::init( const DString& dstrAccountNum,
                             const DString& dstrTransNum,
                             const DString& dstrTransType,
                             const DString& dstrTrack,
                             const DString& dstrPageName )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("init") );

   DString mgmtCoIdOut;
   BFData _requestData(ifds::DSTC0119_REQ);
   _requestData.setElementValue( ifds::CompanyId, getMgmtCoId( mgmtCoIdOut ) );
   _requestData.setElementValue( ifds::AccountNum, dstrAccountNum );
   _requestData.setElementValue( ifds::TransNum, dstrTransNum );
   _requestData.setElementValue( ifds::TransType, dstrTransType );
   _requestData.setElementValue( ifds::Track, dstrTrack );
   _requestData.setElementValue( ifds::Activity, dstrPageName );
   ReceiveData(DSTC_REQUEST::SYS_INDEX, _requestData, ifds::DSTC0119_VW, DSTCRequestor( getSecurity(), false) );

   return(GETCURRENTHIGHESTSEVERITY());
}

//********************************************************************************
SEVERITY SysIndexList::doCreateObject( const BFData& data, BFCBO *&pObjOut )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateObject" ) );

   pObjOut = new SysIndex ( *this );
   dynamic_cast< SysIndex * >( pObjOut )->init( data);

   return(GETCURRENTHIGHESTSEVERITY());
}

//********************************************************************************
SEVERITY SysIndexList::doCreateNewObject(BFCBO *& pBase, DString & strKey, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateNewObject" ) );

   pBase = new SysIndex ( *this );

   return(GETCURRENTHIGHESTSEVERITY());
}

//********************************************************************************
SEVERITY SysIndexList::doValidateAll( const BFDataGroupId& idDataGroup, long lValidateGroup ) 
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doValidateAll" ) );

   validateDateRanage ( idDataGroup );

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************

void SysIndexList::validateDateRanage (const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "ValidateCurrency_AcctUseCode" ) );

   DString dstrStartDate, dstrEndDate, dstrStartDate1, dstrEndDate1, dstrCurBusDate;
   Systematic *pSystematic = dynamic_cast <Systematic*> (getParent());
   BFObjIter iter( *this, idDataGroup, 0, BFObjIter::ITERTYPE::NON_DELETED);
   BFObjIter iter1( *this, idDataGroup, 0, BFObjIter::ITERTYPE::NON_DELETED);
   BFAbstractCBO *pBFCBO;
   BFAbstractCBO *pBFCBO1;
   bool bactive = false;
   if( !iter.end() )
      pSystematic->setField ( ifds::IndexExist, YES, idDataGroup );

   while( !iter.end() )
   {
      pBFCBO = iter.getObject();
      if( !iter.isDummy()  && pBFCBO )
      {
         pBFCBO->getField(ifds::StartDate, dstrStartDate, idDataGroup);
         pBFCBO->getField(ifds::EndDate, dstrEndDate, idDataGroup);

         if( DSTCommonFunctions::CompareDates( dstrStartDate, dstrEndDate ) // check only when date are valid
             == DSTCommonFunctions::FIRST_EARLIER )
         {
            // position to the next item
            iter1.positionByKey( iter.getStringKey() );
            if( !iter1.end() )++iter1;

            while( !iter1.end() )
            {
               pBFCBO1 = iter1.getObject();
               if( !iter1.isDummy()  && pBFCBO1 )
               {
                  pBFCBO1->getField(ifds::StartDate, dstrStartDate1, idDataGroup);
                  pBFCBO1->getField(ifds::EndDate, dstrEndDate1, idDataGroup);

                  if( DSTCommonFunctions::CompareDates( dstrStartDate1, dstrEndDate1 ) // check only when date are valid
                      == DSTCommonFunctions::FIRST_EARLIER )
                  {
                     if( DSTCommonFunctions::CompareDates( dstrStartDate1, dstrEndDate ) 
                         == DSTCommonFunctions::FIRST_EARLIER  &&
                         DSTCommonFunctions::CompareDates( dstrStartDate, dstrEndDate1 ) 
                         == DSTCommonFunctions::FIRST_EARLIER )
                     {
                        ADDCONDITIONFROMFILE( CND::ERR_INDEX_DATE_RANGE_OVERLAP );                        
                        return;
                     }
                  }
               }
               ++iter1;
            }
         }
      }
      if( !bactive )
      {
         getWorkSession().getMgmtCoOptions()->getField( ifds::CurrBusDate, dstrCurBusDate, idDataGroup, false );
         if( (DSTCommonFunctions::CompareDates( dstrStartDate, dstrCurBusDate ) == DSTCommonFunctions::FIRST_EARLIER) &&
             (DSTCommonFunctions::CompareDates( dstrCurBusDate, dstrEndDate ) == DSTCommonFunctions::FIRST_EARLIER) )
            bactive = true;
      }
      ++iter;
   }

   pSystematic->lockFrequency ( idDataGroup, bactive );
}

//******************************************************************************

bool SysIndexList::activeIndex (const BFDataGroupId& idDataGroup)
{
   BFObjIter iter( *this, BF::HOST, 0, BFObjIter::ITERTYPE::NON_DELETED);
   DString dstrStartDate, dstrEndDate, dstrLastProcessDate;   
   getParent()->getField( ifds::LastProcessDate, dstrLastProcessDate, idDataGroup, false );

   while( !iter.end() )
   {
      iter.getObject()->getField ( ifds::StartDate, dstrStartDate, idDataGroup, false );
      iter.getObject()->getField ( ifds::EndDate, dstrEndDate, idDataGroup, false );
      if( (DSTCommonFunctions::CompareDates( dstrStartDate, dstrLastProcessDate ) == DSTCommonFunctions::FIRST_EARLIER) &&
          (DSTCommonFunctions::CompareDates( dstrStartDate, dstrLastProcessDate ) == DSTCommonFunctions::EQUAL) &&
          (DSTCommonFunctions::CompareDates( dstrLastProcessDate, dstrEndDate ) == DSTCommonFunctions::FIRST_EARLIER) )
         return(true);
      ++iter;
   }       

   return(false);
}

//******************************************************************************

void SysIndexList::markReadOnly ( const BFDataGroupId& idDataGroup ) 
{
   BFObjIter iter( *this, BF::HOST, 0, BFObjIter::ITERTYPE::NON_DELETED);
   SysIndex *pSysIndex;
   while( !iter.end() )
   {
      pSysIndex = dynamic_cast <SysIndex*> (iter.getObject());
      pSysIndex->markReadOnly( idDataGroup );
      ++iter;
   }
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/SysIndexList.cpp-arc  $
// 
//    Rev 1.18   Nov 14 2004 14:56:26   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.17   Mar 21 2003 18:25:42   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.16   Oct 09 2002 23:55:04   PURDYECH
// PVCS Database Conversion
// 
//    Rev 1.15   Aug 29 2002 12:56:44   SMITHDAV
// ClientLocale and typed field changes.
// 
//    Rev 1.14   22 May 2002 18:29:56   PURDYECH
// BFData Implementation
// 
//    Rev 1.13   Feb 25 2002 18:55:52   PURDYECH
// Phase 1 of BFData Rollout - Base Component Compatibility
// 
//    Rev 1.12   07 Aug 2001 14:52:06   HSUCHIN
// bug fix to active index check.  The same day is now consider as an active index
// 
//    Rev 1.11   07 Aug 2001 14:44:22   HSUCHIN
// activeindex check now checks lastprocessdate rather than current business date
// 
//    Rev 1.10   02 Aug 2001 18:27:28   HSUCHIN
// added function to mark SysIndex readonly
// 
//    Rev 1.9   25 Jul 2001 09:10:00   HSUCHIN
// bug fix to turn on Systematic IndexExist flag
// 
//    Rev 1.8   18 Jul 2001 09:36:56   YINGZ
// use normal receive
// 
//    Rev 1.7   11 Jul 2001 15:09:58   HSUCHIN
// added activeIndex function
// 
//    Rev 1.6   06 Jun 2001 13:38:06   HSUCHIN
// code cleanup and additional business logic added
// 
//    Rev 1.5   01 Jun 2001 11:36:44   HSUCHIN
// bug fix in validateall
// 
//    Rev 1.4   31 May 2001 16:52:10   HSUCHIN
// changed init requirements
// 
//    Rev 1.3   31 May 2001 11:41:20   HSUCHIN
// view change and added conditions
// 
//    Rev 1.2   23 May 2001 12:32:18   HSUCHIN
// validation rules added
// 
//    Rev 1.1   11 May 2001 09:31:24   HSUCHIN
// Session management restructuring
// 
//    Rev 1.0   03 May 2001 13:44:54   BUZILAMI
// Initial revision.
 * 
*/

