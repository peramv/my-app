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
// ^FILE   : FundBrokerDefault.cpp
// ^AUTHOR : Serban Popescu 
// ^DATE   : November 2004
//
// ^CLASS    : FundBrokerDefault
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "fundbrokerdefault.hpp"
#include <ifastdataimpl\dse_dstc0325_req.hpp>
#include <ifastdataimpl\dse_dstc0325_vw.hpp>

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest FUND_BROKER_DEFAULT;
}

namespace
{
   //Trace literals
   const I_CHAR * const CLASSNAME = I_("FundBrokerDefault");
}

namespace CND
{
}

//******************************************************************************
FundBrokerDefault::FundBrokerDefault  (BFAbstractCBO &parent) 
: MFCanBFCbo (parent)
{
   TRACE_CONSTRUCTOR  (CLASSNAME , NULL_STRING);
}

//******************************************************************************
FundBrokerDefault::~FundBrokerDefault ()
{
   TRACE_DESTRUCTOR (CLASSNAME);
}

//******************************************************************************
SEVERITY FundBrokerDefault::init ( const DString &fundCode,
                                   const DString &accountNum,
                                   const DString &dstrTrack, 
                                   const DString &dstrPageName
                                 )
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("init")
                         );

   BFData queryData (ifds::DSTC0325_REQ);

   DString mgmtCoIdOut;
   queryData.setElementValue (ifds::FundCode, fundCode);
   queryData.setElementValue (ifds::AccountNum, accountNum);
   queryData.setElementValue (ifds::CompanyId, getMgmtCoId (mgmtCoIdOut));
   queryData.setElementValue (ifds::Track, dstrTrack);
   queryData.setElementValue (ifds::Activity, dstrPageName);

   ReceiveData ( DSTC_REQUEST::FUND_BROKER_DEFAULT, 
                 queryData, 
                 ifds::DSTC0325_VW, 
                 DSTCRequestor (getSecurity (), false)
               );
   return GETCURRENTHIGHESTSEVERITY ();
}

//*****************************************************************************
SEVERITY FundBrokerDefault::getDefaultFundBrokerCode ( DString &defaultFundBrokerCode, 
													   DString &dstrFdBrokerDefaultLevel,
                                                       const BFDataGroupId &idDataGroup
                                                     )
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("getDefaultFundBrokerCode")
                         );

   DString isDefault;
   
   getField (ifds::IsDefault, isDefault, idDataGroup, false);
   isDefault.strip().upperCase();
   if (isDefault == I_("Y")) //found a match
   {
      getField (ifds::FundBrokerCode, defaultFundBrokerCode, idDataGroup, false);
	  getField (ifds::FdBrokerDefaultlvl, dstrFdBrokerDefaultLevel, idDataGroup, false);
   }
   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/FundBrokerDefault.cpp-arc  $
// 
//    Rev 1.2   Jul 10 2012 18:18:28   wp040039
// PETP0201166- SSBG- Fund Broker validation
// 
//    Rev 1.1   Dec 08 2004 16:46:40   popescu
// PET 1117/56 fund broker defaul view 325, proved to be non-repeatable after all
// 
//    Rev 1.0   Nov 18 2004 11:46:20   popescu
// Initial revision.
// 
//    Rev 1.2   Nov 14 2004 14:51:46   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.1   Nov 04 2004 17:38:28   popescu
// PET 1117/06, Trade processing
// 
//    Rev 1.0   Oct 29 2004 20:27:36   popescu
// Initial revision.
*/