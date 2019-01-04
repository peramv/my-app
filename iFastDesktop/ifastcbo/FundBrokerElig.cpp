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
//    Copyright 1998 by DST Systems, Inc.
//
//
//******************************************************************************
//
// ^FILE   : FundBrokerElig.cpp
// ^AUTHOR : Serban Popescu 
// ^DATE   : November 2004
//
// ^CLASS    : FundBrokerElig
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "fundbrokerelig.hpp"
#include <ifastdataimpl\dse_dstc0321_req.hpp>
#include <ifastdataimpl\dse_dstc0321_vw.hpp>

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest FUND_BROKER_ELIGIBLE;
}

namespace
{
   //Trace literals
   const I_CHAR * const CLASSNAME = I_("FundBrokerElig");
}

namespace CND
{
}

//******************************************************************************
FundBrokerElig::FundBrokerElig  (BFAbstractCBO &parent) 
: MFCanBFCbo (parent)
{
   TRACE_CONSTRUCTOR  (CLASSNAME , NULL_STRING);
   setVersionable (false);
   setObjectAsList ();
}

//******************************************************************************
FundBrokerElig::~FundBrokerElig ()
{
   TRACE_DESTRUCTOR (CLASSNAME);
}

//******************************************************************************
SEVERITY FundBrokerElig::init ( const DString &fundBrokerCode,
                                const DString &fundCode, /*=NULL_STRING*/
                                const DString &dstrTrack, /*=I_("N")*/
                                const DString &dstrPageName /*=NULL_STRING*/
                              )
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("init")
                         );

//if both fund broker and fund code are null strings view returns all eligible combinations
//if fund broker is null string view returns all fund brokers eligible for the given fund code
//if fund is null string view returns all funds eligible for the given fund broker code
//if fund broker and fund code are not null strings view returns an exact match eligble combination, if any
   BFData queryData (ifds::DSTC0321_REQ);

   DString mgmtCoIdOut;

   queryData.setElementValue (ifds::FundBrokerCode, fundBrokerCode);
   queryData.setElementValue (ifds::FundCode, fundCode);
   queryData.setElementValue (ifds::CompanyId, getMgmtCoId (mgmtCoIdOut));
   queryData.setElementValue (ifds::Track, dstrTrack);
   queryData.setElementValue (ifds::Activity, dstrPageName);

   ReceiveData ( DSTC_REQUEST::FUND_BROKER_ELIGIBLE, 
                 queryData, 
                 ifds::DSTC0321_VW, 
                 DSTCRequestor (getSecurity ())
               );
   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
void FundBrokerElig::buildKey ( const DString &fundBrokerCode, 
                                const DString &fundCode, 
                                DString &strKey
                              )
{
   DString fundBrokerCode_ (fundBrokerCode),
      fundCode_ (fundCode);

   fundBrokerCode_.strip().upperCase();
   fundCode_.strip().upperCase();
   strKey = I_("FundBrokerCode=") + fundBrokerCode_;
   strKey += I_(";FundCode=") + fundCode_;
}

//******************************************************************************
void FundBrokerElig::getStrKey  (DString &strKey, const BFData *data)
{
   TRACE_METHOD (CLASSNAME, I_("getStrKey"));

   if (data)
   {
      buildKey ( data->getElementValue (ifds::FundBrokerCode), 
                 data->getElementValue (ifds::FundCode),
                 strKey
               );
   }
   else
   {
      BFCBO::getStrKey (strKey , NULL);
   }
}

//******************************************************************************
bool FundBrokerElig::isFundBrokerEligToTradeFund ( const DString &fundBrokerCode, 
                                                   const DString &fundCode, 
                                                   const BFDataGroupId &idDataGroup
                                                 )
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("isFundBrokerEligToTradeFund")
                         );

   DString strKey;
   BFObjIter bfIter (*this, idDataGroup);

   buildKey (fundBrokerCode, fundCode, strKey);
   return bfIter.positionByKey (strKey);
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/FundBrokerElig.cpp-arc  $
// 
//    Rev 1.1   Nov 18 2004 14:14:34   popescu
// PET 1117/06, corrected the view call constant
// 
//    Rev 1.0   Nov 18 2004 11:46:12   popescu
// Initial revision.
// 
// Initial revision.
*/