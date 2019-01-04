//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by International Financial Data Services,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2004 by International Financial Data Services.
//
//
//******************************************************************************
//
// ^FILE   : SettlementInstrList.cpp
// ^AUTHOR : 
// ^DATE   : 
//
//********************************************************************************
#include "stdafx.h"
#include "SettlementInstr.hpp"
#include "SettlementInstrList.hpp"
#include "AcctSettlementInstrList.hpp"
#include "MFAccount.hpp"

#include <ifastdataimpl\dse_dstc0317_vw.hpp>
#include <ifastdataimpl\dse_dstc0317_vwrepeat_record.hpp>
#include <ifastdataimpl\dse_dstc0317_req.hpp>
#include <ifastdataimpl\dse_dstc0269_vw.hpp>
#include <ifastdataimpl\dse_dstc0269_vwrepeat_record.hpp>
#include <ifastdataimpl\dse_dstc0269_req.hpp>


namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest SETTLEMENT_INSTRUCTIONS_LIST_INQUIRY;
}

namespace
{
   const I_CHAR * const CLASSNAME = I_( "SettlementInstrList" );
}

namespace ifds
{   
	extern CLASS_IMPORT const BFDateFieldId EffectiveDate;
	extern CLASS_IMPORT const BFDateFieldId StopDate;
	extern CLASS_IMPORT const BFDateFieldId CurrBusDate;
}

namespace CND
{
   extern const long ERR_MISSING_DEFAULT_SETTLEMENT_INSTR;
   extern const long ERR_MULTIPLE_DEFAULT_SETTLEMENT_INSTR;
   extern const long ERR_DUPLICATE_RECORD;
}

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = 
{
   { ifds::AccountNum,      BFCBO::NONE,     0 },
   { ifds::FundBrokerCode,  BFCBO::NONE,     0 },
};

static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );

//******************************************************************************
SettlementInstrList::SettlementInstrList( BFAbstractCBO &parent )
: MFCanBFCbo( parent ),
m_requestData( ifds::DSTC0317_REQ )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
	
   registerMemberData( NUM_FIELDS, (const CLASS_FIELD_INFO *)&classFieldInfo, 0, NULL );	
   setObjectAsList( );  	
}

//******************************************************************************
SettlementInstrList::~SettlementInstrList()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************
SEVERITY SettlementInstrList::init( const BFDataGroupId& idDataGroup,
                                    const DString& dstrAccountNum,
                                    const DString& dstrFundBrokerCode )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );	

   setFieldNoValidate( ifds::AccountNum,     dstrAccountNum,     idDataGroup );
   setFieldNoValidate( ifds::FundBrokerCode, dstrFundBrokerCode, idDataGroup );

   return(GETCURRENTHIGHESTSEVERITY());
}


//******************************************************************************
SEVERITY SettlementInstrList::init(	const DString& dstrAccountNum,
                                    const DString& dstrFundBroker,
									         const BFDataGroupId& idDataGroup,
                                    const DString& dstrTrack,
                                    const DString& dstrPageName )
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );	

	setFieldNoValidate(ifds::AccountNum, dstrAccountNum, idDataGroup, false ); 
   setFieldNoValidate(ifds::FundBrokerCode, dstrFundBroker, idDataGroup, false ); 
   _accountNum = dstrAccountNum;

	// Set request fields
	m_requestData.setElementValue( ifds::NextKey, NULL_STRING );
	m_requestData.setElementValue( ifds::Track, dstrTrack );
	m_requestData.setElementValue( ifds::Activity, dstrPageName );
	m_requestData.setElementValue( ifds::AccountNum, dstrAccountNum );
   m_requestData.setElementValue( ifds::FundBrokerCode, dstrFundBroker );

	DString mgmtCoIdOut;
	m_requestData.setElementValue( ifds::CompanyId, getMgmtCoId( mgmtCoIdOut ) );
	ReceiveData(DSTC_REQUEST::SETTLEMENT_INSTRUCTIONS_LIST_INQUIRY, m_requestData, ifds::DSTC0317_VW, DSTCRequestor(getSecurity()));    
   return GETCURRENTHIGHESTSEVERITY();
}

//*************************************************************************************
SEVERITY SettlementInstrList::doCreateObject( const BFData& data, BFCBO*& pObjOut )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateObject" ) );
   	
	return( GETCURRENTHIGHESTSEVERITY() );
}

//**************************************************************************************
SEVERITY SettlementInstrList::doCreateNewObject( BFCBO *&pObjOut, DString &strKey, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateNewObject" ) );
   	
   
	return( GETCURRENTHIGHESTSEVERITY() );
}

//**************************************************************************************
SEVERITY SettlementInstrList::doValidateAll( const BFDataGroupId& idDataGroup, long lValidateGroup )
{ 
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doValidateAll" ) );

   // Check to ensure that one list item is marked default if a list exists.
	short nFound = 0;
   DString dstrDefault;

   // Check list
   bool bList = false;
   BFObjIter iter( *this, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED );
   while( !iter.end() && nFound < 2)
   {
      if( !iter.isDummy() )
      {
         bList = true;
         iter.getObject()->getField( ifds::DefaultSettlementInstr, dstrDefault, idDataGroup, false );
         dstrDefault.stripAll().upperCase();
         if( dstrDefault == I_("Y") ) 
         {
            ++nFound;
         }
      }
      ++iter;
   }
   if( bList )
   {
      if( nFound == 0 )
      {
         ADDCONDITIONFROMFILE( CND::ERR_MISSING_DEFAULT_SETTLEMENT_INSTR );
      }
      else if( nFound > 1 )
      {
         ADDCONDITIONFROMFILE( CND::ERR_MULTIPLE_DEFAULT_SETTLEMENT_INSTR ); // This is backup.  Should be caught earlier.      
	  }
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//**********************************************************************************
void  SettlementInstrList::getStrKey( DString &strKey, const BFData& data  )
{
}

//**********************************************************************************
SEVERITY SettlementInstrList::checkDuplicate ( const SettlementInstr *pSettlementInstrToCheck, const BFDataGroupId &idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_( "checkDuplicate" ) );  

	DString dstrSettlementInstrCodeToCheck;
	DString dstrEffectiveDateToCheck, dstrStopDateToCheck;
	
	pSettlementInstrToCheck->getField( ifds::SettlementInstrCode, dstrSettlementInstrCodeToCheck, idDataGroup );
	pSettlementInstrToCheck->getField( ifds::EffectiveDate, dstrEffectiveDateToCheck, idDataGroup );
	pSettlementInstrToCheck->getField( ifds::StopDate, dstrStopDateToCheck, idDataGroup );

	bool bHasDuplicate = false;
	
	//check first whether in the list (in memory) we have a duplicate
	BFObjIter iter( *this, idDataGroup, 0, BFObjIter::ITERTYPE::NON_DELETED );
	iter.begin();
	while (!iter.end())
	{
		SettlementInstr *pSettlementInstr = dynamic_cast<SettlementInstr*>(iter.getObject());
		// Don't check against itself
		if ( pSettlementInstr != pSettlementInstrToCheck )
		{
			DString dstrCurrentSettlementInstr;
			DString dstrCurrentEffectiveDate, dstrCurrentStopDate;

			pSettlementInstr->getField( ifds::SettlementInstrCode, dstrCurrentSettlementInstr, idDataGroup );
			pSettlementInstr->getField( ifds::EffectiveDate, dstrCurrentEffectiveDate, idDataGroup );
			pSettlementInstr->getField( ifds::StopDate, dstrCurrentStopDate, idDataGroup );

			dstrCurrentSettlementInstr.strip ();

			if ( dstrCurrentSettlementInstr  == dstrSettlementInstrCodeToCheck)
			{
				// check dates
				if( DSTCommonFunctions::dateRangesOverlap (dstrEffectiveDateToCheck, dstrStopDateToCheck,
														   dstrCurrentEffectiveDate, dstrCurrentStopDate))
				{
					bHasDuplicate = true;
					break;
				}
			}
		}
		++iter;
	}

	if ( bHasDuplicate )
	{
		ADDCONDITIONFROMFILE(CND::ERR_DUPLICATE_RECORD);
	}

	return GETCURRENTHIGHESTSEVERITY();
}
//**********************************************************************************
bool SettlementInstrList::isDuplicateSettlementLocation( DString &dstrSettleLocationCode, 
                                                             const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("isDuplicateSettlementLocation") );

	short nFound = 0;
   DString dstrSettleLocationCodeTmp;

   // Check current list
   BFObjIter iter( *this, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED );
   while( !iter.end() && nFound < 2)
   {
      iter.getObject()->getField( ifds::SettlementInstrCode, dstrSettleLocationCodeTmp, idDataGroup, false );
	  dstrSettleLocationCodeTmp.stripAll().upperCase();
      if( dstrSettleLocationCodeTmp == dstrSettleLocationCode ) 
      {
         ++nFound;
      }
      ++iter;
   }

   return( nFound > 1 );
}

//**********************************************************************************
bool SettlementInstrList::isDuplicateDefault( DString &dstrDefault, 
                                                  const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("isDuplicateDefault") );

   short nFound = 0;

   if( dstrDefault == I_("Y") )
   {
      DString dstrDefaultTmp;

      // Check current list
      BFObjIter iter( *this, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED );
      while( !iter.end() && nFound < 2)
      {
         iter.getObject()->getField( ifds::DefaultSettlementInstr, dstrDefaultTmp, idDataGroup, false );
		 dstrDefaultTmp.stripAll().upperCase();
         if( dstrDefaultTmp == dstrDefault ) 
         {
            ++nFound;
         }
         ++iter;
      }
   }

   return( nFound > 1 );
}

//******************************************************************************
SEVERITY SettlementInstrList::getSettlementCodeSubstList(DString& dstrSettleCodeSubstList, const BFDataGroupId& idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getSettlementCodeSubstList" ) );	

	BFObjIter settlementInstrListIter( *this, idDataGroup, true, BFObjIter::ITERTYPE::NON_DELETED );
	DString		dstrCurrBusDate;
	
	getWorkSession().getOption (ifds::CurrBusDate, dstrCurrBusDate, idDataGroup, false);
         
	settlementInstrListIter.begin();  
	while( !settlementInstrListIter.end() )
	{
		DString  dstrSettleInstrCode;
		DString	dstrEffectiveDate;
		DString	dstrStopDate;

		settlementInstrListIter.getObject()->getField( ifds::SettlementInstrCode, dstrSettleInstrCode, idDataGroup );
		settlementInstrListIter.getObject()->getField( ifds::EffectiveDate, dstrEffectiveDate, idDataGroup );
		settlementInstrListIter.getObject()->getField( ifds::StopDate, dstrStopDate, idDataGroup );

		if (DSTCommonFunctions::IsDateBetween (dstrEffectiveDate, dstrStopDate, dstrCurrBusDate))
		{
			dstrSettleCodeSubstList += dstrSettleInstrCode + I_("=") + dstrSettleInstrCode + I_(";");				
		}
		      
		++settlementInstrListIter;         
	}
	
	dstrSettleCodeSubstList += I_("N/A=N/A;");

	return(GETCURRENTHIGHESTSEVERITY());
}


//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastcbo/SettlementInstrList.cpp-arc  $
// 
//    Rev 1.5   May 04 2007 13:53:04   jankovii
// PET 2321 FN01 - MT54X Default Pay Type.
// 
//    Rev 1.4   Dec 10 2004 17:19:26   vadeanum
// PET117_FN21: settlement instructions enhancement.
// 
//    Rev 1.3   Nov 30 2004 11:23:08   aguilaam
// PET117_FN21: settlement instructions enhancement.
// 
//    Rev 1.2   Nov 26 2004 16:56:30   aguilaam
// PET1117_FN21: settlement instructions
// 
//    Rev 1.1   Nov 19 2004 17:33:16   aguilaam
// PET117_FN21: settlement instructions enhancement (temporary check-in for build)
// 
//    Rev 1.0.1.0   Nov 14 2004 14:54:04   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.0   Oct 13 2004 13:33:58   VADEANUM
// Initial revision.
//
