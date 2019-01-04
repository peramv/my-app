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
// ^FILE   : AcctEntityValidation.cpp
// ^AUTHOR : Shashi Kant
// ^DATE   : August, 2012
//
// ^CLASS    : AcctEntityValidation
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include "stdafx.h"
#include "acctEntityvalidation.hpp"
#include "mfaccount.hpp"
#include <ifastdataimpl\dse_dstc0446_req.hpp>
#include <ifastdataimpl\dse_dstc0446_vw.hpp>
#include "mgmtco.hpp"

namespace CORFAX
{
   extern CLASS_IMPORT const DSTCHost HOST;

   const char *const CFX_TRANS = "CFXTRAN";
}

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest ACCT_ENTITY_VALIDATION;
}

namespace ifds
{

}

namespace
{
   const I_CHAR * const CLASSNAME                     = I_ ("AcctEntityValidation");
}

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = {
//  Field DD Id,              State Flags,      Group Flags 
   {ifds::WarnCode ,     BFCBO::NONE,             0},
};

static const int NUM_FIELDS = sizeof  (classFieldInfo) / sizeof  (BFCBO::CLASS_FIELD_INFO);



//******************************************************************************
AcctEntityValidation::AcctEntityValidation (BFAbstractCBO &parent)
: MFCanBFCbo (parent)
{
   TRACE_CONSTRUCTOR (CLASSNAME , NULL_STRING);
   registerMemberData (NUM_FIELDS,  (const CLASS_FIELD_INFO *)&classFieldInfo, 0, NULL);

   setObjectAsList ();
}

//******************************************************************************
AcctEntityValidation::~AcctEntityValidation ()
{
   TRACE_DESTRUCTOR (CLASSNAME);
}

//******************************************************************************
SEVERITY AcctEntityValidation::init (const DString &strAccountNum, 
									 const DString &strTaxType, 
									 const DString &strEntityId, 
									 const DString &strNationalID, 
									 const DString &strCOINationalID, 
									 const DString &dstrPassport, 
									 const DString &dstrCOIPassport)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_ ("init"));
   
   
   BFData queryData  (ifds::DSTC0446_REQ);

   DString mgmtCoIdOut;
   queryData.setElementValue (ifds::CompanyId, getMgmtCoId (mgmtCoIdOut));
   queryData.setElementValue (ifds::AccountNum, strAccountNum);
   queryData.setElementValue (ifds::TaxType, strTaxType);
   queryData.setElementValue (ifds::EntityId, strEntityId);
   queryData.setElementValue (ifds::NationalID, strNationalID);
   queryData.setElementValue (ifds::COINationalID, strCOINationalID);
   queryData.setElementValue (ifds::Passport, dstrPassport);
   queryData.setElementValue (ifds::COIPassport, dstrCOIPassport);
   
   ReceiveData  (DSTC_REQUEST::ACCT_ENTITY_VALIDATION, 
                 queryData, 
                 ifds::DSTC0446_VW,
                 DSTCRequestor  (getSecurity (), true));
	
   return GETCURRENTHIGHESTSEVERITY ();
}

//*************************************************************************
//              Revision Control Entries
//******************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastcbo/AcctEntityValidation.cpp-arc  $
// 
//    Rev 1.0   Aug 15 2012 13:53:04   wp040027
// Initial revision.
//

