//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by DST Systems, Inc.,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 1997 by DST Systems, Inc.
//
//
//******************************************************************************
//
// ^FILE   : RDRAdvice.cpp
// ^AUTHOR : Shashi Kant
// ^DATE   : July, 2012
//
// ^CLASS    : RDRAdvice
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include "stdafx.h"
#include "rdradvice.hpp"
#include "mfaccount.hpp"
#include <ifastdataimpl\dse_dstc0442_req.hpp>
#include <ifastdataimpl\dse_dstc0442_vw.hpp>
#include "mgmtco.hpp"

namespace CORFAX
{
   extern CLASS_IMPORT const DSTCHost HOST;

   const char *const CFX_TRANS = "CFXTRAN";
}

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest RDR_ADVICE;
}

namespace ifds
{

}

namespace
{
   const I_CHAR * const CLASSNAME                     = I_ ("RDRAdvice");
}

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = {
//  Field DD Id,              State Flags,      Group Flags 
   {ifds::RDRApplic,     BFCBO::NONE,             0},
   {ifds::RDRDefault,    BFCBO::NONE,             0},
};

static const int NUM_FIELDS = sizeof  (classFieldInfo) / sizeof  (BFCBO::CLASS_FIELD_INFO);



//******************************************************************************
RDRAdvice::RDRAdvice (BFAbstractCBO &parent)
: MFCanBFCbo (parent)
{
   TRACE_CONSTRUCTOR (CLASSNAME , NULL_STRING);
   registerMemberData (NUM_FIELDS,  (const CLASS_FIELD_INFO *)&classFieldInfo, 0, NULL);

   setObjectAsList ();
}

//******************************************************************************
RDRAdvice::~RDRAdvice ()
{
   TRACE_DESTRUCTOR (CLASSNAME);
}

//******************************************************************************
SEVERITY RDRAdvice::init (const DString &strAccountNum, 
                                 const DString &strFundCode, 
                                 const DString &strClassCode, 
                                 const DString &strTransType, 
                                 const DString &strEffectiveDate, 
                                 const DString &dstrBrokerCode, 
                                 const DString &dstrBranchCode,
								 const DString &dstrSalesRepCode)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_ ("init"));
   
   
   BFData queryData  (ifds::DSTC0442_REQ);

   DString mgmtCoIdOut;
   queryData.setElementValue (ifds::CompanyId, getMgmtCoId (mgmtCoIdOut));
   queryData.setElementValue (ifds::AccountNum, strAccountNum);
   queryData.setElementValue (ifds::FundCode, strFundCode);
   queryData.setElementValue (ifds::ClassCode, strClassCode);
   queryData.setElementValue (ifds::TransType, strTransType);
   queryData.setElementValue (ifds::EffectiveDate, strEffectiveDate, false, false);
   queryData.setElementValue (ifds::BrokerCode, dstrBrokerCode);
   queryData.setElementValue (ifds::BranchCode, dstrBranchCode);
   queryData.setElementValue (ifds::SalesRepCode, dstrSalesRepCode);

   ReceiveData  (DSTC_REQUEST::RDR_ADVICE, 
                 queryData, 
                 ifds::DSTC0442_VW,
                 DSTCRequestor  (getSecurity (), true));
	
   return GETCURRENTHIGHESTSEVERITY ();
}

//*************************************************************************
//              Revision Control Entries
//******************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastcbo/RDRAdvice.cpp-arc  $
// 
//    Rev 1.0   Jul 24 2012 13:45:28   wp040027
// Initial revision.
// 

