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
// ^FILE   : FundMgmtSettlementInstr.cpp
// ^AUTHOR : 
// ^DATE   : 
//
//********************************************************************************
#include "stdafx.h"
#include "FundMgmtSettlementInstr.hpp"
#include "FundMgmtSettlementInstrList.hpp"
#include "SysLvlSettlementInstr.hpp"
#include "SysLvlSettlementInstrList.hpp"
#include "MgmtCoOptions.hpp"
#include "mgmtco.hpp"
#include "DSTCommonFunction.hpp"

#include <ifastdataimpl\dse_dstc0269_vw.hpp>
#include <ifastdataimpl\dse_dstc0269_req.hpp>

namespace
{
   const I_CHAR * const CLASSNAME = I_( "FundMgmtSettlementInstr" );
}

namespace CND
{
   extern const long ERR_DUPLICATE_SETTLE_LOCATION;
   extern const long ERR_MULTIPLE_DEFAULT_FND_MGMT_SETTLE_INSTR ;
   extern const long ERR_DUPLICATE_RECORD;

}

namespace UAF
{
   extern CLASS_IMPORT I_CHAR * const SETTLE_LOCATION_ACCT_LVL;
}

namespace ifds
{   
	extern CLASS_IMPORT const BFTextFieldId SettleAccountNum;
    extern CLASS_IMPORT const BFTextFieldId InternalSettlementAccount;
}

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = 
{
   // Field DD Id,				State Flags,	 Group Flags 
   { ifds::SettleLocationCode, BFCBO::REQUIRED,     0 },
   { ifds::SettleAccountNum,   BFCBO::NONE,         0 },
   { ifds::Default,            BFCBO::NONE,         0 },
   { ifds::InternalSettlementAccount, BFCBO::NONE,  0 },  
   // Admin/Date fields
   { ifds::ProcessDate,        BFCBO::NONE,     0 }, 
   { ifds::Username,           BFCBO::NONE,     0 }, 
   { ifds::ModDate,            BFCBO::NONE,     0 }, 
   { ifds::ModUser,            BFCBO::NONE,     0 }, 
};

static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );

//******************************************************************************
FundMgmtSettlementInstr::FundMgmtSettlementInstr( BFAbstractCBO &parent )
: MFCanBFCbo( parent )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   registerMemberData( NUM_FIELDS, (const CLASS_FIELD_INFO *)&classFieldInfo, 0, NULL );	
}

//******************************************************************************
FundMgmtSettlementInstr::~FundMgmtSettlementInstr()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}  

//******************************************************************************
SEVERITY FundMgmtSettlementInstr::init(const BFData& data, const DString& dstrSubstitution )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );
   attachDataObject(const_cast<BFData&>(data), false);  

   setFieldAllSubstituteValues( ifds::SettleLocationCode, BF::HOST, dstrSubstitution );
   clearUpdatedFlags( BF::HOST, false );

	DString dstrSettleLocCode;
	getField( ifds::SettleLocationCode, dstrSettleLocCode, BF::HOST, false );
	if ( !dstrSettleLocCode.strip().empty() )
   {
		setSettleAccountNum( dstrSettleLocCode, BF::HOST );
      setFieldReadOnly( ifds::SettleLocationCode, BF::HOST, true );
   }
			
	return GETCURRENTHIGHESTSEVERITY();
}

//*******************************************************************************
void FundMgmtSettlementInstr::initNew(const BFDataGroupId& idDataGroup, const DString& dstrSubstitution, const DString& dstrSettleLocationCode )
{
   setFieldAllSubstituteValues( ifds::SettleLocationCode, idDataGroup, dstrSubstitution );
   setField(ifds::Default, I_("N"), idDataGroup, false );
   clearUpdatedFlags( idDataGroup, false );
}

//*********************************************************************************
SEVERITY FundMgmtSettlementInstr::doValidateField( const BFFieldId& idField, 
																 const DString& dstrValue, 
												             const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("doValidateField" ));   

   if (idField == ifds::SettleLocationCode )
	{
      validateSettlementLocation( dstrValue, idDataGroup );
   }
   else if( idField == ifds::Default )
   {
      validateDefault( dstrValue, idDataGroup );
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//***************************************************************************************
SEVERITY FundMgmtSettlementInstr::doApplyRelatedChanges( const BFFieldId& idField, 
																		 const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("doApplyRelatedChanges") );		

	if (idField == ifds::SettleLocationCode )
	{
		DString dstrSettleLocCode;
		getField( ifds::SettleLocationCode, dstrSettleLocCode, idDataGroup, false );
		setSettleAccountNum( dstrSettleLocCode, idDataGroup );
	}
   
   return GETCURRENTHIGHESTSEVERITY();
}

//*******************************************************************************
SEVERITY FundMgmtSettlementInstr::doValidateAll( const BFDataGroupId& idDataGroup, 
															  long lValidateGroup )
{ 
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doValidateAll" ) );
   return(GETCURRENTHIGHESTSEVERITY());
}

//*******************************************************************************
SEVERITY FundMgmtSettlementInstr::validateSettlementLocation( const DString& dstrSettlementLocationCode, 
																			   const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("validateSettlementLocation") );

   DString dstrSettleLocationCode( dstrSettlementLocationCode );
   dstrSettleLocationCode.strip().upperCase();

   if( dstrSettleLocationCode.empty() )
   {
      return( NO_CONDITION );
   }

	bool bExist = (dynamic_cast<FundMgmtSettlementInstrList*>(getParent()) )->isDuplicateSettlementLocation( dstrSettleLocationCode, idDataGroup );
   if( bExist )
	{
		ADDCONDITIONFROMFILE( CND::ERR_DUPLICATE_RECORD  );
		return  GETCURRENTHIGHESTSEVERITY();
	}

   return GETCURRENTHIGHESTSEVERITY();
}

//*******************************************************************************
SEVERITY FundMgmtSettlementInstr::validateDefault( const DString& dstrDefaultCode, 
																 const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("validateDefault") );

   DString dstrDefault( dstrDefaultCode );
   dstrDefault.strip().upperCase();

   if( dstrDefault.empty() )
   {
      return( NO_CONDITION );
   }

	bool bExist = (dynamic_cast<FundMgmtSettlementInstrList*>(getParent()) )->isDuplicateDefault( dstrDefault, idDataGroup );
   if( bExist )
	{
      ADDCONDITIONFROMFILE( CND::ERR_MULTIPLE_DEFAULT_FND_MGMT_SETTLE_INSTR  );
		return  GETCURRENTHIGHESTSEVERITY();
	}

   return GETCURRENTHIGHESTSEVERITY();
}

//*******************************************************************************
SEVERITY FundMgmtSettlementInstr::setSettleAccountNum( const DString &dstrSettleLocCode, 
													   const BFDataGroupId& idDataGroup )
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("setSettleAccountNum") );

	DString dstrSettleAccountNum;

	SysLvlSettlementInstrList *pSysLvlSettlementInstrList = NULL;
	if ( getWorkSession().getSettlementLocationSysLvlList( pSysLvlSettlementInstrList, idDataGroup, true ) <= WARNING &&
		 NULL != pSysLvlSettlementInstrList )
	{
		SysLvlSettlementInstr *pSysLvlSettlementInstr = NULL;
		if ( pSysLvlSettlementInstrList->getSysLvlSettlementInstr(	dstrSettleLocCode, pSysLvlSettlementInstr, 
																	idDataGroup ) <= WARNING &&
			 NULL != pSysLvlSettlementInstr) 
		{ 
			pSysLvlSettlementInstr-> getField( ifds::SettleAccountNum, dstrSettleAccountNum, idDataGroup );
			setField(ifds::SettleAccountNum, dstrSettleAccountNum, idDataGroup);
            DString dstrInteralStlAccount;
            pSysLvlSettlementInstr-> getField( ifds::InternalSettlementAccount, dstrInteralStlAccount, idDataGroup );
            setField(ifds::InternalSettlementAccount, dstrInteralStlAccount, idDataGroup);
            setFieldUpdated(ifds::SettleAccountNum, idDataGroup, false);
            setFieldUpdated(ifds::InternalSettlementAccount, idDataGroup, false);
		} 
	}

	return GETCURRENTHIGHESTSEVERITY();
}

//***********************************************
//R E V I S I O N   C O N T R O L   E N T R I E S
//***********************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastcbo/FundMgmtSettlementInstr.cpp-arc  $
// 
//    Rev 1.3   Dec 01 2004 20:34:18   vadeanum
// PET1117_FN21: settlement instructions - the key should be read only
// 
//    Rev 1.2   Nov 30 2004 18:44:44   aguilaam
// PET1117_FN21:  settlement instructions.
// 
//    Rev 1.1   Nov 19 2004 17:32:58   aguilaam
// PET117_FN21: settlement instructions enhancement (temporary check-in for build)
// 
//    Rev 1.0.1.0   Nov 14 2004 14:42:50   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.0   Oct 13 2004 13:17:16   VADEANUM
// Initial revision.
// 
//    Rev 1.1   Nov 24 2003 18:11:04   HERNANDO
// Next revision.
// 
//    Rev 1.0   Nov 20 2003 11:08:40   HERNANDO
// Initial revision.
