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
// ^FILE   : SysLvlSettlementInstr.cpp
// ^AUTHOR : 
// ^DATE   : 
//
//********************************************************************************
#include "stdafx.h"
#include "SysLvlSettlementInstr.hpp"
#include "SysLvlSettlementInstrList.hpp"
#include "MgmtCoOptions.hpp"
#include "mgmtco.hpp"

#include <ifastdataimpl\dse_dstc0267_vw.hpp>
#include <ifastdataimpl\dse_dstc0267_req.hpp>

namespace
{
   const I_CHAR * const CLASSNAME = I_( "SysLvlSettlementInstr" );
}

namespace CND
{
   extern const long ERR_DUPLICATE_SETTLE_LOCATION;
}

namespace UAF
{
   extern CLASS_IMPORT I_CHAR * const SETTLE_LOCATION_SYS_LVL;
}

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = 
{
//  Field DD Id,					State Flags,			Group Flags 
   { ifds::SettleLocationCode, BFCBO::REQUIRED, 0 }, 
   { ifds::SettleLocationDesc, BFCBO::REQUIRED, 0 },
   { ifds::SettleAccountNum,   BFCBO::REQUIRED, 0 },
   { ifds::Active,             BFCBO::REQUIRED, 0 },
   { ifds::ProcessDate,        BFCBO::NONE,     0 }, 
   { ifds::InUseAcct,          BFCBO::NONE,     0 }, 
   { ifds::InUseTrade,         BFCBO::NONE,     0 }, 
   { ifds::Username,           BFCBO::NONE,     0 }, 
   { ifds::ModDate,            BFCBO::NONE,     0 }, 
   { ifds::ModUser,            BFCBO::NONE,     0 }, 
   { ifds::InternalSettlementAccount, BFCBO::NONE, 0 },
};

static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );

//******************************************************************************

SysLvlSettlementInstr::SysLvlSettlementInstr( BFAbstractCBO &parent )
: MFCanBFCbo( parent )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   registerMemberData( NUM_FIELDS, (const CLASS_FIELD_INFO *)&classFieldInfo, 0, NULL );
}

//******************************************************************************

SysLvlSettlementInstr::~SysLvlSettlementInstr()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}  

//******************************************************************************

SEVERITY SysLvlSettlementInstr::init(const BFData& data)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );
   attachDataObject(const_cast<BFData&>(data), false);  

   DString dstrInUseAcct;
   dstrInUseAcct = data.getElementValue( ifds::InUseAcct );
   dstrInUseAcct.upperCase().stripAll();

   // Cannot rename existing codes.
   setFieldReadOnly( ifds::SettleLocationCode, BF::HOST, true );  

   // Cannot change status if Acct in use.
   if( dstrInUseAcct == I_("Y") )
   {
      setFieldReadOnly( ifds::Active, BF::HOST, true );
   }
   clearUpdatedFlags( BF::HOST );

	return GETCURRENTHIGHESTSEVERITY();
}

//*******************************************************************************

void SysLvlSettlementInstr::initNew(const BFDataGroupId& idDataGroup )
{
	setFieldNoValidate(ifds::SettleLocationCode, NULL_STRING, idDataGroup, false);
	setFieldNoValidate(ifds::SettleLocationDesc, NULL_STRING, idDataGroup, false);
}

//*********************************************************************************

SEVERITY SysLvlSettlementInstr::doValidateField( const BFFieldId& idField, const DString& strValue, 
												  const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("doValidateField" ));   
   if( idField == ifds::SettleLocationCode )
	{
		validateSettleLocation( strValue, idDataGroup );
	}
   return GETCURRENTHIGHESTSEVERITY();
}

//***************************************************************************************

SEVERITY SysLvlSettlementInstr::doApplyRelatedChanges( const BFFieldId& idField, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("doApplyRelatedChanges") );
   return GETCURRENTHIGHESTSEVERITY();
}

//************************************************************************************

SEVERITY SysLvlSettlementInstr::validateSettleLocation(const DString& strValue, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("validateSettleLocation") );
   DString dstrSettleLocation(strValue);
	dstrSettleLocation.strip().upperCase();

   if( !dstrSettleLocation.empty() )
   {
	   bool bExist = (dynamic_cast<SysLvlSettlementInstrList*>(getParent()) )->isDuplicateSettlementLocation( dstrSettleLocation, idDataGroup );
      if( bExist )
	   {
         ADDCONDITIONFROMFILE( CND::ERR_DUPLICATE_SETTLE_LOCATION );
		   return GETCURRENTHIGHESTSEVERITY();
	   }
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//********************************************************************************************

SEVERITY SysLvlSettlementInstr::doValidateAll( const BFDataGroupId& idDataGroup, long lValidateGroup )
{ 
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doValidateAll" ) );
   return(GETCURRENTHIGHESTSEVERITY());
}

//***********************************************
//R E V I S I O N   C O N T R O L   E N T R I E S
//***********************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastcbo/SysLvlSettlementInstr.cpp-arc  $
// 
//    Rev 1.1   Nov 14 2004 14:56:28   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.0   Oct 13 2004 13:01:24   VADEANUM
// Initial revision.
// 
//    Rev 1.1   Nov 24 2003 18:12:44   HERNANDO
// Next revision.
// 
//    Rev 1.0   Nov 20 2003 11:08:44   HERNANDO
// Initial revision.
// 
//