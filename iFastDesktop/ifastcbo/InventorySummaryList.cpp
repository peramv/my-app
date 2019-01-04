//*****************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by International Financial,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2003 by International Financial
//
//*****************************************************************************
//
// ^FILE   : InventorySummaryList.cpp
// ^AUTHOR : Celia Zhang
// ^DATE   : Feb 12, 2004
//
//-----------------------------------------------------------------------------
//
// ^CLASS  : InventorySummaryList
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS :
//
//*****************************************************************************

#include "stdafx.h"
#include "InventorySummaryList.hpp"
#include "InventorySummary.hpp"
#include "InventoryDetailsList.hpp"
#include <ifastdataimpl\dse_dstc0287_req.hpp>
#include <ifastdataimpl\dse_dstc0287_vw.hpp>
#include <ifastdataimpl/dse_dstc0287_vwrepeat_record.hpp> // TotalCBFreeUnits

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest INVENTORY_SUMMARY_LIST;   
}

namespace
{
   const I_CHAR * const CLASSNAME = I_( "InventorySummaryList" );
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId SortBy;
   extern CLASS_IMPORT const BFTextFieldId SortOrder;
   extern CLASS_IMPORT const BFTextFieldId InvSummSortBy;
   extern CLASS_IMPORT const BFIntegerFieldId SortByColumn;
   extern CLASS_IMPORT const BFTextFieldId InventorySummHeading;
}

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = {
//   Field DD Id,                   State Flags,              Group Flags 
   { ifds::SortBy,                  BFCBO::NOT_ON_HOST,           0 }, 
   { ifds::SortOrder,               BFCBO::NOT_ON_HOST,           0 },
   { ifds::SortByColumn,            BFCBO::NOT_ON_HOST,           0 },
   { ifds::InventorySummHeading,    BFCBO::NOT_ON_HOST,           0 },
};

static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );

//******************************************************************************
// Constructor
// @param   BFBase - pointer to the parent BFBase
//******************************************************************************

InventorySummaryList::InventorySummaryList( BFAbstractCBO &parent ) 
: MFCanBFCbo( parent ),  
_pRequestData ( 0 ),
m_dstrSortBy(I_("MD")),
m_dstrSortOrder(I_("D")),
m_dstrAccountNumber(NULL_STRING),
m_dstrFundCode(NULL_STRING),
m_dstrClassCode(NULL_STRING),
m_dstrActiveOnly(NULL_STRING)
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   setObjectAsList( );
   registerMemberData( NUM_FIELDS,
                       (const CLASS_FIELD_INFO *)&classFieldInfo,
                       0,
                       NULL );
}

//******************************************************************************
// Destructor
//******************************************************************************

InventorySummaryList::~InventorySummaryList()
{
   TRACE_DESTRUCTOR( CLASSNAME );
   if( _pRequestData )
      delete _pRequestData;
	/*if( _pResponseData )
      delete _pResponseData;*/
}

//******************************************************************************
// Initalize CBO and executes view call
// @param   const DString& dstrAccountNumber - Account Number ( Required )
// @param   const DString& dstrFundCode - Fund Code 
// @param   const DString& dstrClassCode - Class Code 
// @param   const DString& dstrTrack - Tracking flag ( used by eAdvisor )
// @param   const DString& dstrPageName - Page Name value ( used by eAdvisor )
// @return  SEVERITY - NO_CONDITION/WARNING/SEVERE_ERROR based view call.
//******************************************************************************

SEVERITY InventorySummaryList::init( const DString& dstrAccountNumber, 
                                     const DString& dstrFundCode,
                                     const DString& dstrClassCode,
                                     const DString& dstrActiveOnly,
                                     const DString& dstrTrack,
                                     const DString& dstrPageName )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );
   
   DString strInvSummSortBySubstList;
   BFProperties *pBFPropertiesHost = getFieldProperties( ifds::InvSummSortBy, BF::HOST );
   pBFPropertiesHost->getAllSubstituteValues (strInvSummSortBySubstList);

   setFieldAllSubstituteValues (ifds::SortBy, BF::HOST, strInvSummSortBySubstList);
   setFieldNoValidate(ifds::SortBy, m_dstrSortBy, BF::HOST, false, true, false, false);
   
   m_dstrAccountNumber = dstrAccountNumber;
   m_dstrFundCode = dstrFundCode;
   m_dstrClassCode = dstrClassCode;
   m_dstrActiveOnly = dstrActiveOnly;   

   DString mgmtCoIdOut;
   _pRequestData = new BFData(ifds::DSTC0287_REQ);
   _pRequestData->setElementValue( ifds::CompanyId, getMgmtCoId( mgmtCoIdOut ) );
   _pRequestData->setElementValue( ifds::AccountNum,  dstrAccountNumber  );   
   _pRequestData->setElementValue( ifds::FundCode,  dstrFundCode );   
   _pRequestData->setElementValue( ifds::ClassCode,  dstrClassCode );   
   _pRequestData->setElementValue( ifds::ActiveOnly, dstrActiveOnly );
   _pRequestData->setElementValue( ifds::SortBy, m_dstrSortBy);
   _pRequestData->setElementValue( ifds::SortOrder, m_dstrSortOrder);
   
   _pRequestData->setElementValue( ifds::Track, dstrTrack );
   _pRequestData->setElementValue( ifds::Activity, dstrPageName );
   _pRequestData->setElementValue( ifds::NextKey, NULL_STRING );

   // Execute view call.
   SEVERITY sevRtn = NO_CONDITION;
   sevRtn = ReceiveData(DSTC_REQUEST::INVENTORY_SUMMARY_LIST, 
                        *_pRequestData, 
                        ifds::DSTC0287_VW, 
                        DSTCRequestor( getSecurity(), 
                        false) );

   getField( ifds::UnitsTotal, m_dstrUnitsTotal, BF::HOST, false);
   getField( ifds::TotalCBFFreeUnits, m_dstrTotalCBFreeUnits, BF::HOST, false);

   setFieldNoValidate (ifds::SortBy, m_dstrSortBy, BF::HOST, false, true, false, false );
   setFieldNoValidate (ifds::SortOrder, m_dstrSortOrder, BF::HOST, false, true, false, false );
   if(m_dstrSortBy == I_("MD"))
   {
      setFieldNoValidate (ifds::SortByColumn, I_("5"), BF::HOST, false, true, false, false );
   }
   else
   {
      setFieldNoValidate (ifds::SortByColumn, I_("4"), BF::HOST, false, true, false, false );
   }
   
	return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
// getMore retrieves more data.
// @return SEVERITY - NO_CONDITION/WARNING/SEVERE_ERROR based view call.
//******************************************************************************

SEVERITY InventorySummaryList::getMore( )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getMore" ) );
   
   ReceiveData(DSTC_REQUEST::INVENTORY_SUMMARY_LIST, 
               *_pRequestData, 
               ifds::DSTC0287_VW, 
               DSTCRequestor( getSecurity(), 
               false) );

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY InventorySummaryList::doCreateObject( const BFData& data, BFCBO*& pObjOut )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateObject" ) );
   pObjOut =  new InventorySummary( *this );
   ((InventorySummary*) pObjOut)->init( data);
   return( GETCURRENTHIGHESTSEVERITY() );
}

//**************************************************************************************
SEVERITY InventorySummaryList::doCreateNewObject( BFCBO *&pObjOut, DString &strKey, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateNewObject" ) );
   pObjOut =  new InventorySummary( *this );
   ((InventorySummary*) pObjOut)->initNew( idDataGroup );
   return( GETCURRENTHIGHESTSEVERITY() );
}

//**************************************************************************************
SEVERITY InventorySummaryList::doApplyRelatedChanges( const BFFieldId& idField,
                                                      const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doApplyRelatedChanges" ) );
   
   if( idField == ifds::SortBy || idField == ifds::SortOrder )
   {
      DString mgmtCoIdOut;
      
      if(_pRequestData)
      {
         delete _pRequestData;
         _pRequestData = NULL;
      }

      getField (ifds::SortBy, m_dstrSortBy, idDataGroup, false );
      getField (ifds::SortOrder, m_dstrSortOrder, idDataGroup, false );
      m_dstrSortBy.strip().upperCase();
      m_dstrSortOrder.strip().upperCase();

      BFObjIter invSummIter( *this, idDataGroup, true, BFObjIter::ITERTYPE::NON_DELETED );

      if( invSummIter.begin() )
      {
         while( !invSummIter.end() )
         {
            invSummIter.removeObjectFromMap( true );
         }
      }

      _pRequestData = new BFData(ifds::DSTC0287_REQ);
      _pRequestData->setElementValue( ifds::CompanyId, getMgmtCoId( mgmtCoIdOut ) );
      _pRequestData->setElementValue( ifds::AccountNum,  m_dstrAccountNumber  );   
      _pRequestData->setElementValue( ifds::FundCode,  m_dstrFundCode );   
      _pRequestData->setElementValue( ifds::ClassCode,  m_dstrClassCode );   
      _pRequestData->setElementValue( ifds::ActiveOnly, m_dstrActiveOnly );
      _pRequestData->setElementValue( ifds::SortBy, m_dstrSortBy);
      _pRequestData->setElementValue( ifds::SortOrder, m_dstrSortOrder);

      _pRequestData->setElementValue( ifds::Track, I_("N") );
      _pRequestData->setElementValue( ifds::Activity, NULL_STRING );
      _pRequestData->setElementValue( ifds::NextKey, NULL_STRING );
      
      ReceiveData(DSTC_REQUEST::INVENTORY_SUMMARY_LIST, 
                  *_pRequestData, 
                  ifds::DSTC0287_VW,
                  DSTCRequestor( getSecurity(), 
                  false) );

      getField( ifds::UnitsTotal, m_dstrUnitsTotal, BF::HOST, false);
      getField( ifds::TotalCBFFreeUnits, m_dstrTotalCBFreeUnits, BF::HOST, false);

      if(m_dstrSortBy == I_("MD"))
      {
         setFieldNoValidate (ifds::SortByColumn, I_("5"), BF::HOST, false, true, false, false );
      }
      else
      {
         setFieldNoValidate (ifds::SortByColumn, I_("4"), BF::HOST, false, true, false, false );
      }
   }

   return(GETCURRENTHIGHESTSEVERITY());   
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/InventorySummaryList.cpp-arc  $
// 
//    Rev 1.6   Nov 14 2004 14:48:44   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.5   May 25 2004 20:11:22   HERNANDO
// PET1046 FN01 - Changed use of TotalCBFreeUnits.
// 
//    Rev 1.4   May 19 2004 17:46:08   HERNANDO
// PET1046 FN01 - Added LSIF/Inventory Details support; made use of InventorySummary.
// 
//    Rev 1.3   Mar 10 2004 17:50:02   ZHANGCEL
// PET 1001 - FN01: Fix crash when click F11
// 
//    Rev 1.1   Feb 26 2004 17:16:34   ZHANGCEL
// PET1001 - FN01 Added logic to cope with the UnitsTatol issue
// 
//    Rev 1.0   Feb 24 2004 10:40:44   ZHANGCEL
// Initial revision.
//
*/
