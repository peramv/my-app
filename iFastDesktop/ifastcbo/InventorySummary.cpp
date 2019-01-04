//********************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by DST Systems, Inc.,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2003 By International Financial Data Services.
//
//
//********************************************************************************
//
// ^FILE   : InventorySummary.cpp
// ^AUTHOR : 
// ^DATE   : 
//
//********************************************************************************
#include "stdafx.h"
#include "InventorySummary.hpp"
#include "InventorySummaryList.hpp"
#include "InventoryDetailsList.hpp"
#include "MgmtCoOptions.hpp"
#include "mgmtco.hpp"
#include "MFAccount.hpp"

#include <ifastdataimpl\dse_dstc0287_vw.hpp>
#include <ifastdataimpl\dse_dstc0287_req.hpp>

namespace
{
   const I_CHAR * const CLASSNAME               = I_( "InventorySummary" );
   const I_CHAR * const INVENTORYDETAILSLIST      = I_( "InventoryDetailsList" );
}

namespace CND
{
}

namespace ifds
{
 extern CLASS_IMPORT const BFTextFieldId DisplayRolloverQualificationDate;
}

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = 
{
//  Field DD Id,                 State Flags,                  Group Flags 
   { ifds::TransType,            BFCBO::NONE,                     0 }, 
   { ifds::PartnerShip,          BFCBO::NONE,                     0 }, 
   { ifds::OrigEffectiveDate,    BFCBO::NONE,                     0 }, 
   { ifds::MaturityDate,         BFCBO::NONE,                     0 }, 
   { ifds::RollQualDate,         BFCBO::NONE,                     0 }, 
   { ifds::OriginalTotalUnits,   BFCBO::NONE,                     0 }, 
   { ifds::UsedUnits,            BFCBO::NONE,                     0 }, 
   { ifds::Units,                BFCBO::NONE,                     0 }, 
   { ifds::Rate,                 BFCBO::NONE,                     0 }, 
   { ifds::CommRate,             BFCBO::NONE,                     0 }, 
   { ifds::FromFund,             BFCBO::NONE,                     0 }, 
   { ifds::FromClass,            BFCBO::NONE,                     0 }, 
   { ifds::DisplayRolloverQualificationDate,
								 BFCBO::CALCULATED_FIELD,         0 },
};

static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );

const BFCBO::CLASS_OBJECT_INFO classObjectInfo[] = 
{
   // Object Label,                 State Flags,      Group Flags 
   { I_( "InventorySummaryList" ),    BFCBO::NONE,     0},
};

static const int NUM_OBJECTS = sizeof( classObjectInfo ) / sizeof( BFCBO::CLASS_OBJECT_INFO );

//******************************************************************************

InventorySummary::InventorySummary( BFAbstractCBO &parent )
: MFCanBFCbo( parent )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   registerMemberData( NUM_FIELDS, (const CLASS_FIELD_INFO *)&classFieldInfo, NUM_OBJECTS, (const CLASS_OBJECT_INFO *)&classObjectInfo );
}

//******************************************************************************

InventorySummary::~InventorySummary()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}  

//******************************************************************************

SEVERITY InventorySummary::init(const BFData& data)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );
   attachDataObject(const_cast<BFData&>(data), false);  
   clearUpdatedFlags( BF::HOST );

   setFieldReadOnly( ifds::RollQualDate, BF::HOST, true );

   DString dstrAccountNum, dstrDisplayRolloverQualificationDate;
   getParent()->getParent()->getField(ifds::AccountNum, dstrAccountNum, BF::HOST ); 
   MFAccount *pMFAccount = NULL;
   if( getWorkSession().getMFAccount ( BF::HOST, dstrAccountNum, pMFAccount) <= WARNING &&
	   pMFAccount)
   {
	   dstrDisplayRolloverQualificationDate = pMFAccount->isAccountOmnibus(dstrAccountNum, BF::HOST ) ?	
											  I_("N") : I_("Y");
   }
   setFieldNoValidate( ifds::DisplayRolloverQualificationDate, dstrDisplayRolloverQualificationDate, 
					   BF::HOST, true, true );

   return GETCURRENTHIGHESTSEVERITY();
}

//*******************************************************************************

void InventorySummary::initNew(const BFDataGroupId& idDataGroup )
{
   setFieldReadOnly( ifds::RollQualDate, idDataGroup, true );
   DString dstrAccountNum, dstrDisplayRolloverQualificationDate;
   getParent()->getParent()->getField(ifds::AccountNum, dstrAccountNum, idDataGroup ); 
   MFAccount *pMFAccount = NULL;
   if( getWorkSession().getMFAccount (idDataGroup, dstrAccountNum, pMFAccount) <= WARNING &&
	   pMFAccount)
   {
	   dstrDisplayRolloverQualificationDate = pMFAccount->isAccountOmnibus(dstrAccountNum, idDataGroup) ?	
											  I_("N") : I_("Y");
   }
   setFieldNoValidate( ifds::DisplayRolloverQualificationDate, dstrDisplayRolloverQualificationDate, 
					   idDataGroup, true, true );
}

//*********************************************************************************

SEVERITY InventorySummary::doValidateField( const BFFieldId& idField, const DString& strValue, 
                                            const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("doValidateField" ));   
   return GETCURRENTHIGHESTSEVERITY();
}

//***************************************************************************************

SEVERITY InventorySummary::doApplyRelatedChanges( const BFFieldId& idField, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("doApplyRelatedChanges") );
   return GETCURRENTHIGHESTSEVERITY();
}

//********************************************************************************************

SEVERITY InventorySummary::getInventoryDetailsList( InventoryDetailsList *&pInventoryDetailsList, const BFDataGroupId& idDataGroup, const DString &dstrInvSummId, bool bCreate )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("getInventoryDetailsList") );
   DString dstrKey( I_("INVENTORY_DETAILS_LIST ") );
   dstrKey += dstrInvSummId;
   
   pInventoryDetailsList = NULL;
   pInventoryDetailsList = dynamic_cast<InventoryDetailsList*>(getObject( dstrKey, idDataGroup ) );
   if( pInventoryDetailsList || !bCreate )
   {
      return(GETCURRENTHIGHESTSEVERITY());
   }


   pInventoryDetailsList = new InventoryDetailsList( *this );
   if( isNew() )
   {
//      pInventoryDetailsList->initNew( idDataGroup);
      setObject( pInventoryDetailsList, dstrKey, OBJ_ACTIVITY_NONE, idDataGroup );
   }
   else
   {
      if( pInventoryDetailsList->init( dstrInvSummId, I_("N"), NULL_STRING ) <= WARNING )
      {
         setObject( pInventoryDetailsList, dstrKey, OBJ_ACTIVITY_NONE, BF::HOST );
      }
      else
      {
         delete pInventoryDetailsList;
         pInventoryDetailsList = NULL;
      }
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//*******************************************************************************

SEVERITY InventorySummary::doValidateAll( const BFDataGroupId& idDataGroup, long lValidateGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doValidateAll" ) );
   return(GETCURRENTHIGHESTSEVERITY());
}


//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastcbo/InventorySummary.cpp-arc  $
// 
//    Rev 1.2   May 29 2008 05:57:48   daechach
// PET0006862 Fn02 - Roll Over Qualification Period Enhancement
// 
//    Rev 1.1   Nov 14 2004 14:48:42   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.0   May 19 2004 17:40:32   HERNANDO
// Initial revision.
//