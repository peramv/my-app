//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by International Financial Data Services,
//    are proprietary in nature and as such are confIdential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2010 by International Financial Data Services.
//
//
//******************************************************************************
//
// ^FILE   : AcctGuaranteeGuardOptList.cpp
// ^AUTHOR : 
// ^DATE   : Aug, 2010
//
// ^CLASS    : AcctGuaranteeGuardOptList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"

#include <ifastdataimpl\dse_dstc0412_vw.hpp>
#include <ifastdataimpl\dse_dstc0412_req.hpp>
#include <ifastdataimpl\dse_dstc0412_vwrepeat_record.hpp>

#include "AcctGuaranteeGuardOpt.hpp"
#include "AcctGuaranteeGuardOptList.hpp"
#include "mfaccount.hpp"

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest ACCT_GUARNT_GUARD_OPTN_INQUIRY;
}

namespace
{
   // Trace literals
   const I_CHAR * const CLASSNAME               = I_( "AcctGuaranteeGuardOptList" );
}

namespace ifds
{
   extern CLASS_IMPORT const BFNumericFieldId AccountNum;
}

namespace CND
{
}

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = 
{
   // Field DD Id,                     State Flags,          Group Flags 
   { ifds::AccountNum               , BFCBO::NONE,                0 },
};

static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );

//******************************************************************************
AcctGuaranteeGuardOptList::AcctGuaranteeGuardOptList( BFAbstractCBO &parent )
: MFCanBFCbo(parent)
, requestData412(NULL)
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );

   registerMemberData( NUM_FIELDS,
                       (const CLASS_FIELD_INFO *)&classFieldInfo,
                       0,
                       NULL );

   setObjectAsList( );
}

//******************************************************************************
AcctGuaranteeGuardOptList::~AcctGuaranteeGuardOptList(void)
{
   TRACE_DESTRUCTOR( CLASSNAME );

   if ( requestData412 != NULL )
   {
      delete requestData412;
      requestData412 = NULL;
   }
}

//******************************************************************************
SEVERITY AcctGuaranteeGuardOptList::initNew(const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("initNew") );

   DString dstrAccountNum;
   getParent()->getField(ifds::AccountNum, dstrAccountNum, idDataGroup, false);
   setFieldNoValidate(ifds::AccountNum, dstrAccountNum, idDataGroup, false, true, true);
   setObjectNew();

   return(GETCURRENTHIGHESTSEVERITY());
}

//********************************************************************************
SEVERITY AcctGuaranteeGuardOptList::init(const DString& accountNum,
                                       const BFDataGroupId& idDataGroup,
                                       const DString& dstrTrack,
                                       const DString& dstrPageName )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, 
                          CLASSNAME, 
                          I_("init"));

   setFieldNoValidate(ifds::AccountNum, accountNum, idDataGroup, false, true, true);

   DString mgmtCoIdOut;
   requestData412 = new BFData(ifds::DSTC0412_REQ);

   requestData412->setElementValue (ifds::CompanyId, getMgmtCoId (mgmtCoIdOut));
   requestData412->setElementValue (ifds::Track, dstrTrack);
   requestData412->setElementValue (ifds::Activity, dstrPageName);
   requestData412->setElementValue (ifds::AccountNum, accountNum);

   BFData* responseData = new BFData (ifds::DSTC0412_VW);
   ReceiveData( DSTC_REQUEST::ACCT_GUARNT_GUARD_OPTN_INQUIRY,
                *requestData412, 
                *responseData, 
                DSTCRequestor (getSecurity(), true));

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY AcctGuaranteeGuardOptList::doCreateObject( const BFData& data, BFCBO *&pObjOut )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateObject" ) );

   pObjOut =  new AcctGuaranteeGuardOpt( *this );
   ((AcctGuaranteeGuardOpt*) pObjOut )->init( data );

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY AcctGuaranteeGuardOptList::doCreateNewObject (BFCBO *& pBase, 
                                                       DString &strKey, 
                                                       const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateNewObject" ) );

   pBase =  new AcctGuaranteeGuardOpt( *this );

   ((AcctGuaranteeGuardOpt*)pBase)->initNew( idDataGroup );

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY AcctGuaranteeGuardOptList::getMore()
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getMore" ) );

   if( doMoreRecordsExist() )
   {
      ReceiveData(DSTC_REQUEST::ACCT_GUARNT_GUARD_OPTN_INQUIRY, 
                  *requestData412, 
                  ifds::DSTC0412_VW, 
                  DSTCRequestor( getSecurity(), false ) );
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastcbo/AcctGuaranteeGuardOptList.cpp-arc  $
// 
//    Rev 1.0   Sep 17 2010 03:42:10   kitticha
// Initial revision.
// 
//
