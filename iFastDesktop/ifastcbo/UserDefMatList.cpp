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
// ^FILE   : UserDefMatList.cpp
// ^CLASS  : UserDefMatList
//
//*****************************************************************************
#include "stdafx.h"
#include "UserDefMatList.hpp"
#include "UserDefMat.hpp"
#include <ifastdataimpl\dse_dstc0340_vw.hpp>
#include <ifastdataimpl\dse_dstc0340_req.hpp>

namespace
{
   const I_CHAR * const CLASSNAME = I_( "UserDefMatList" );
}

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest USER_DEF_MAT_LIST;
}

namespace ifds
{
   extern CLASS_IMPORT const BFDateFieldId LegalMaturityDate;
   extern CLASS_IMPORT const BFNumericFieldId AccountNum;
   extern CLASS_IMPORT const BFTextFieldId ContractType;
}

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = 
{
   { ifds::LegalMaturityDate, BFCBO::CALCULATED_FIELD, 0 },
   { ifds::AccountNum, BFCBO::CALCULATED_FIELD, 0 },
   { ifds::ContractType, BFCBO::CALCULATED_FIELD, 0 },
};
static const int NUM_FIELDS = sizeof(classFieldInfo) / sizeof(BFCBO::CLASS_FIELD_INFO);

//******************************************************************************

UserDefMatList::UserDefMatList( BFAbstractCBO &parent ) 
: MFCanBFCbo( parent ), 
m_requestData(ifds::DSTC0340_REQ)
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   setObjectAsList( );
   registerMemberData(NUM_FIELDS,
                       (const CLASS_FIELD_INFO *)&classFieldInfo,
                       0,
                       NULL);
}

//******************************************************************************

UserDefMatList::~UserDefMatList()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************

SEVERITY UserDefMatList::initNew ( const DString& AccountNum, 
                                   const DString& ContractType,
                                   const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("init") );
   // Set fields
   m_AccountNum = AccountNum;
   m_ContractType = ContractType;
   setFieldNoValidate(ifds::AccountNum, AccountNum, idDataGroup, false );
   setFieldNoValidate(ifds::ContractType, ContractType, idDataGroup, false );

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************

SEVERITY UserDefMatList::init( const DString& AccountNum, 
                               const BFDataGroupId& idDataGroup,
                               const DString& LegalMaturityDate,
                               const DString& ContractType,
                               const DString& dstrTrack,
                               const DString& dstrPageName )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("init") );

   // Set fields
   m_AccountNum = AccountNum;
   m_ContractType = ContractType;
   m_LegalMaturityDate = LegalMaturityDate;
   setFieldNoValidate(ifds::LegalMaturityDate, LegalMaturityDate, idDataGroup, false );
   setFieldNoValidate(ifds::AccountNum, AccountNum, idDataGroup, false );
   setFieldNoValidate(ifds::ContractType, ContractType, idDataGroup, false );

   DString mgmtCoIdOut;
   m_requestData.setElementValue( ifds::CompanyId, getMgmtCoId( mgmtCoIdOut ) );
   m_requestData.setElementValue( ifds::AccountNum, AccountNum  );
   m_requestData.setElementValue( ifds::Track, dstrTrack );
   m_requestData.setElementValue( ifds::Activity, dstrPageName );

   ReceiveData( DSTC_REQUEST::USER_DEF_MAT_LIST, m_requestData, ifds::DSTC0340_VW, DSTCRequestor( getSecurity(), false /*Partial*/) );

   setFieldNoValidate(ifds::LegalMaturityDate, LegalMaturityDate, idDataGroup, false );
   setFieldNoValidate(ifds::AccountNum, AccountNum, idDataGroup, false );
   setFieldNoValidate(ifds::ContractType, ContractType, idDataGroup, false );

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************

SEVERITY UserDefMatList::doCreateNewObject( BFCBO *& pBase, DString &strKey, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateNewObject" ) );

   UserDefMat *pUserDefMat = new UserDefMat( *this );
   pUserDefMat->init( idDataGroup );
   pBase = pUserDefMat;
   pUserDefMat->setNonDummyFlag();
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************

SEVERITY UserDefMatList::doCreateObject( const BFData& data, BFCBO *&pObjOut )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateObject" ) );

   DString dstContractType;
   data.getElementValue( ifds::ContractType, dstContractType);

   dstContractType.strip();
   
   if(m_ContractType == dstContractType)
   {
      pObjOut = new UserDefMat( *this );
      ( ( UserDefMat* ) ( pObjOut ) )->init( data, m_ContractType );
      pObjOut->setNonDummyFlag();
   }
   else
      pObjOut = NULL;

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************

SEVERITY UserDefMatList::getMore()
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getMore" ) );

   if( doMoreRecordsExist() )
   {
      ReceiveData(DSTC_REQUEST::USER_DEF_MAT_LIST, m_requestData, ifds::DSTC0340_VW, DSTCRequestor( getSecurity(), false) );
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************

void UserDefMatList::doReset( const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, CLASSNAME, I_("doReset") );

   // Set fields
   setFieldNoValidate(ifds::LegalMaturityDate, m_LegalMaturityDate, BF::HOST, false );
   setFieldNoValidate(ifds::AccountNum, m_AccountNum, BF::HOST, false );
   setFieldNoValidate(ifds::ContractType, m_ContractType, BF::HOST, false );
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
// $Log:   Y:/VCS/BF iFAST/ifastcbo/UserDefMatList.cpp-arc  $
// 
//    Rev 1.7   Jun 18 2012 17:35:12   if991250
// IN2937065: new CMD Based on: User Defined Mat - Transfer
// 
//    Rev 1.6   Mar 29 2012 15:48:38   if991250
// IN 2858958: user def mat dates
// 
//    Rev 1.5   Jul 08 2005 16:10:58   hernando
// Incident 344960 - Added ContractType to initNew sig.
// 
//    Rev 1.4   Jun 22 2005 13:11:48   popescu
// Incident #339563 - fixed NASU flow crash on the UserDefMat screen
// 
//    Rev 1.3   May 15 2005 16:40:12   hernando
// Inc 305633 - Added ContractType in init call.
// 
//    Rev 1.2   Apr 18 2005 17:21:08   hernando
// PET1024 FN02 - Added doReset to retain list values.
// 
//    Rev 1.1   Apr 14 2005 10:09:58   hernando
// PET1024 FN02 - Added Contract Type support.
// 
//    Rev 1.0   Mar 20 2005 17:12:50   hernando
// Initial revision.
