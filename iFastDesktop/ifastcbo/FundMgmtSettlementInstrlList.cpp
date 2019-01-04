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
// ^FILE   : FundMgmtSettlementInstrList.cpp
// ^AUTHOR : 
// ^DATE   : 
//
//********************************************************************************
#include "stdafx.h"
#include "FundMgmtSettlementInstrList.hpp"
#include "FundMgmtSettlementInstr.hpp"
#include "SysLvlSettlementInstrList.hpp"
#include "SysLvlSettlementInstr.hpp"
#include <ifastdataimpl\dse_dstc0269_vw.hpp>
#include <ifastdataimpl\dse_dstc0269_vwrepeat_record.hpp>
#include <ifastdataimpl\dse_dstc0269_req.hpp>

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest FUND_MGMT_SETTLEMENT_INSTR_LIST_INQ;
}

namespace
{
   const I_CHAR * const CLASSNAME = I_( "FundMgmtSettlementInstrList" );
}

namespace CND
{
   extern const long ERR_MISSING_DEFAULT_FND_MGMT_SETTL_INSTR;
   extern const long ERR_MULTIPLE_DEFAULT_FND_MGMT_SETTLE_INSTR ;

}

namespace ifds
{
	extern CLASS_IMPORT const BFTextFieldId Active;
	extern CLASS_IMPORT const BFTextFieldId FundMgmtSettleInstrHeadingSet;
	extern CLASS_IMPORT const BFTextFieldId SettleLocationAcctLvlHeading;
}
const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = 
{
   // Field DD Id,				State Flags,			    Group Flags 
	{ ifds::FundMgmtSettleInstrHeadingSet, BFCBO::NONE,     0 },   
	{ ifds::SettleLocationAcctLvlHeading, BFCBO::NONE,     0 },   
   { ifds::AccountNum,      BFCBO::NONE,     0 },
   { ifds::FundBrokerCode,  BFCBO::NONE,     0 },
};

static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );



//******************************************************************************
FundMgmtSettlementInstrList::FundMgmtSettlementInstrList( BFAbstractCBO &parent )
: MFCanBFCbo( parent ), 
m_requestData( ifds::DSTC0269_REQ ), 
m_dstrSettleLocationCodeSubstitution( NULL_STRING ),
m_dstrInitialSettleLocationCode( NULL_STRING )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );

	registerMemberData( NUM_FIELDS, (const CLASS_FIELD_INFO *)&classFieldInfo, 0, NULL );
   setObjectAsList( );

   // Determine Substitution String for Settle Location Code
   // Initialize substitution for Settle Location Code

   SysLvlSettlementInstrList *pSysLvlSettlementInstrList = NULL;
   getWorkSession().getSettlementLocationSysLvlList( pSysLvlSettlementInstrList, BF::HOST, true );
   while( pSysLvlSettlementInstrList && pSysLvlSettlementInstrList->doMoreRecordsExist() )
   {
      pSysLvlSettlementInstrList->getMore();
   }
   if( pSysLvlSettlementInstrList )
   {
      DString dstrSettleLocationCode, dstrSettleLocationDesc, dstrActive;
      BFObjIter bfObjIter( *pSysLvlSettlementInstrList, BF::HOST, BFObjIter::ITERTYPE::NON_DELETED );
      while( !bfObjIter.end() )
      {
         bfObjIter.getObject()->getField( ifds::SettleLocationCode, dstrSettleLocationCode, BF::HOST, false );
         bfObjIter.getObject()->getField( ifds::SettleLocationDesc, dstrSettleLocationDesc, BF::HOST, false );
         bfObjIter.getObject()->getField( ifds::Active, dstrActive, BF::HOST, false );
         dstrSettleLocationCode.stripLeading().stripTrailing();
         dstrSettleLocationDesc.stripLeading().stripTrailing();
         dstrActive.stripAll().upperCase();
         if( dstrActive == I_("Y") )
         {
            if( m_dstrInitialSettleLocationCode.empty() )
            {
               m_dstrInitialSettleLocationCode = dstrSettleLocationCode;
            }
            m_dstrSettleLocationCodeSubstitution += dstrSettleLocationCode + I_("=") + dstrSettleLocationDesc + I_(";");
         }
         ++bfObjIter;
      }
   }		
}

//******************************************************************************
FundMgmtSettlementInstrList::~FundMgmtSettlementInstrList()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************
SEVERITY FundMgmtSettlementInstrList::init( const DString& dstrAccountNum,
					                             const DString& dstrFundBrokerCode,
                                            const BFDataGroupId &idDataGroup )
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

	setFieldSubstituteValues (ifds::FundMgmtSettleInstrHeadingSet, BF::HOST, ifds::SettleLocationAcctLvlHeading );

   setFieldNoValidate( ifds::AccountNum,     dstrAccountNum,     idDataGroup );
   setFieldNoValidate( ifds::FundBrokerCode, dstrFundBrokerCode, idDataGroup );

	return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************

SEVERITY FundMgmtSettlementInstrList::init( const DString& dstrAccountNum,
											const DString& dstrFundBrokerCode,
											const DString& dstrTrack,
											const DString& dstrPageName )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

	setFieldNoValidate(ifds::AccountNum, dstrAccountNum, BF::HOST, false ); 
   setFieldNoValidate(ifds::FundBrokerCode, dstrFundBrokerCode, BF::HOST, false ); 
	setFieldSubstituteValues (ifds::FundMgmtSettleInstrHeadingSet, BF::HOST, ifds::SettleLocationAcctLvlHeading );

   m_requestData.setElementValue( ifds::NextKey, NULL_STRING );
   m_requestData.setElementValue( ifds::Track, dstrTrack );
   m_requestData.setElementValue( ifds::Activity, dstrPageName );
   m_requestData.setElementValue( ifds::AccountNum, dstrAccountNum );
   m_requestData.setElementValue( ifds::FundBrokerCode, dstrFundBrokerCode );


   DString mgmtCoIdOut;
   m_requestData.setElementValue( ifds::CompanyId, getMgmtCoId( mgmtCoIdOut ) );
   ReceiveData(DSTC_REQUEST::FUND_MGMT_SETTLEMENT_INSTR_LIST_INQ, m_requestData, ifds::DSTC0269_VW, DSTCRequestor(getSecurity()) );

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY FundMgmtSettlementInstrList::reInit()
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "reInit" ) );
   return(GETCURRENTHIGHESTSEVERITY());
}

//*************************************************************************************
SEVERITY FundMgmtSettlementInstrList::doCreateObject( const BFData& data, BFCBO*& pObjOut )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateObject" ) );
   
   pObjOut =  new FundMgmtSettlementInstr( *this );
   ( (FundMgmtSettlementInstr*) pObjOut)->init( data, m_dstrSettleLocationCodeSubstitution ) ;


   return( GETCURRENTHIGHESTSEVERITY() );
}

//**************************************************************************************
SEVERITY FundMgmtSettlementInstrList::doCreateNewObject( BFCBO *&pObjOut, DString &strKey, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateNewObject" ) );
   pObjOut =  new FundMgmtSettlementInstr( *this );
   ((FundMgmtSettlementInstr*) pObjOut)->initNew( idDataGroup, m_dstrSettleLocationCodeSubstitution, m_dstrInitialSettleLocationCode );
   return( GETCURRENTHIGHESTSEVERITY() );
}

//**************************************************************************************
SEVERITY FundMgmtSettlementInstrList::doValidateAll( const BFDataGroupId& idDataGroup, long lValidateGroup )
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
         iter.getObject()->getField( ifds::Default, dstrDefault, idDataGroup, false );
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
         ADDCONDITIONFROMFILE( CND::ERR_MISSING_DEFAULT_FND_MGMT_SETTL_INSTR );
      }
      else if( nFound > 1 )
      {
         ADDCONDITIONFROMFILE( CND::ERR_MULTIPLE_DEFAULT_FND_MGMT_SETTLE_INSTR  ); // This is backup.  Should be caught earlier.
      }
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//**********************************************************************************
void  FundMgmtSettlementInstrList::getStrKey( DString &strKey, const BFData *data  )
{
   BFCBO::getStrKey( strKey, NULL );
}

//**********************************************************************************
bool FundMgmtSettlementInstrList::isDuplicateSettlementLocation( DString &dstrSettleLocationCode, 
                                      const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("isDuplicateSettlementLocation") );

	short nFound = 0;
   DString dstrSettleLocationCodeTmp;

   // Check current list
   BFObjIter iter( *this, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED );
   while( !iter.end() && nFound < 2)
   {
      iter.getObject()->getField( ifds::SettleLocationCode, dstrSettleLocationCodeTmp, idDataGroup, false );
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
bool FundMgmtSettlementInstrList::isDuplicateDefault( DString &dstrDefault, 
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
         iter.getObject()->getField( ifds::Default, dstrDefaultTmp, idDataGroup, false );
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

//**************************************************************************************
SEVERITY FundMgmtSettlementInstrList::getSettlementLocationSubstList( DString& dstrSettleLocSubstList, 
                                                                      const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("setSettlementLocationSubstList") );

   BFObjIter fundMgmtSettlementInstrList( *this, 
				                              idDataGroup, 
				 									   true, 
														BFObjIter::ITERTYPE::NON_DELETED );
         
   fundMgmtSettlementInstrList.begin();  
			
	SysLvlSettlementInstrList *pSysLvlSettlementInstrList = NULL;
	if ( getWorkSession().getSettlementLocationSysLvlList( pSysLvlSettlementInstrList, 
			                                                 idDataGroup, 
																			 true ) <= WARNING &&
		  NULL != pSysLvlSettlementInstrList )
	{				
		while( !fundMgmtSettlementInstrList.end() )
		{
			FundMgmtSettlementInstr *pFundMgmtSettlementInstr = dynamic_cast<FundMgmtSettlementInstr*>( fundMgmtSettlementInstrList.getObject() );
			DString dstrSettleLocationCode;
			pFundMgmtSettlementInstr->getField( ifds::SettleLocationCode, dstrSettleLocationCode, idDataGroup );

			SysLvlSettlementInstr *pSysLvlSettlementInstr = NULL;
			if ( pSysLvlSettlementInstrList->getSysLvlSettlementInstr( dstrSettleLocationCode, 
	  		   			  										                 pSysLvlSettlementInstr, 
 																                    idDataGroup ) <= WARNING &&
				  NULL != pSysLvlSettlementInstr )
			{
					DString dstrSettleLocationDesc;
					pSysLvlSettlementInstr->getField( ifds::SettleLocationDesc, dstrSettleLocationDesc, idDataGroup );
									
					dstrSettleLocSubstList += dstrSettleLocationCode + I_("=") + dstrSettleLocationDesc + I_(";");				
					dstrSettleLocationCode = I_( "" );
			}		
			
			++fundMgmtSettlementInstrList;         			
		}
	}

   return(GETCURRENTHIGHESTSEVERITY());
}

//***********************************************
//R E V I S I O N   C O N T R O L   E N T R I E S
//***********************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastcbo/FundMgmtSettlementInstrlList.cpp-arc  $
// 
//    Rev 1.4   Dec 10 2004 17:20:18   vadeanum
// PET117_FN21: settlement instructions enhancement.
// 
//    Rev 1.3   Nov 30 2004 16:14:06   aguilaam
// PET1117_FN21: settlement instructions
// 
//    Rev 1.2   Nov 30 2004 11:38:16   aguilaam
// PET117_FN21: settlement instructions enhancement.
// 
//    Rev 1.1   Nov 19 2004 17:33:08   aguilaam
// PET117_FN21: settlement instructions enhancement (temporary check-in for build)
// 
//    Rev 1.0.1.0   Nov 14 2004 14:42:56   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.0   Oct 13 2004 13:17:36   VADEANUM
// Initial revision.
// 
//    Rev 1.2   Nov 27 2003 18:11:36   HERNANDO
// Changed checking in doValidateAll.
// 
//    Rev 1.1   Nov 24 2003 18:12:10   HERNANDO
// Next revision.
// 
//    Rev 1.0   Nov 20 2003 11:08:42   HERNANDO
// Initial revision.
