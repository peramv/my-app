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
//    Copyright 2009 by International Financial Data Services.
//
//******************************************************************************
//
// ^FILE   : DSTCInvestorAuthorizationTrxnBuilder.cpp
// ^AUTHOR : Serban Popescu
// ^DATE   : June 2009
//
// ----------------------------------------------------------
//
// ^CLASS : DSTCInvestorAuthorizationTrxnBuilder
//
// ^MEMBER VARIABLES :  
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include "stdafx.h"

#include "ifasthosttransactioncontainer.hpp"

#include "DSTCInvestorAuthorizationTrxnBuilder.hpp"
#include "dstclisttrxnbuilder.hpp"
#include "InvestorAuthorizationList.hpp"
#include "InvestorAuthorization.hpp"

#include "MFAccount.hpp"

#include <ifastdataimpl\dse_dstc0396_req.hpp>
#include <ifastdataimpl\dse_dstc0396_reqrepeat_record.hpp>
#include <ifastdataimpl\dse_dstc0396_vw.hpp>

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest INVESTOR_AUTHORIZATION_UPDATE;
}

namespace
{
   const I_CHAR* CLASSNAME          = I_( "DSTCInvestorAuthorizationTrxnBuilder" );
   const I_CHAR* BUILDTRANSACTIONS  = I_( "buildTransactions" );
}

namespace KEYTYPES
{
   extern CLASS_IMPORT I_CHAR * const ACCOUNTNUM;
}

namespace ifds
{
   extern CLASS_IMPORT const BFNumericFieldId AccountNum;
}

//******************************************************************************
void DSTCInvestorAuthorizationTrxnBuilder::buildTrxnKey (DString& dstrKey) 
{
}

//******************************************************************************
SEVERITY DSTCInvestorAuthorizationTrxnBuilder::buildTransactions( DSTCWorkSession &workSession,
                                                                  BFAbstractCBO *pObj, 
                                                                  HostTransactionContainer *pTrCont, 
                                                                  BF_OBJ_ACTIVITY objActivity /*= OBJ_ACTIVITY_NONE*/)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, BUILDTRANSACTIONS);

   MFAccount* pMFaccount = dynamic_cast<MFAccount*>(pObj);

   if (pMFaccount)
   {
      DString dstAccountNum, 
         dstTrnKey, 
         dstKeyTypes;

      pMFaccount->getField (ifds::AccountNum, dstAccountNum, BF::HOST, true);

      addIDITagValue (dstTrnKey, TRXNTAG::AMSACCTLVLTAG, dstAccountNum.stripLeading('0').strip());
      addIDITagValue (dstKeyTypes, KEYTYPES::ACCOUNTNUM, dstAccountNum);

      InvestorAuthorizationList *pInvestorAuthorizationList = NULL;
      if (pMFaccount->getInvestorAuthorizationList(pInvestorAuthorizationList, BF::HOST) <= WARNING && 
          pInvestorAuthorizationList)
      {
         std::vector<BFFieldId> fields;
         fields.push_back(ifds::AccountNum);

         DSTCListTrxnBuilder <InvestorAuthorization*> investorAuthorizationListTrxnBuilder;
         TRXNINFO investorAuthorizationInfo( I_("InvestorAuthorizationList"), 
                                             DSTC_REQUEST::INVESTOR_AUTHORIZATION_UPDATE,
                                             ifds::DSTC0396_REQ,
                                             ifds::DSTC0396_REQRepeat_Record,
                                             ifds::DSTC0396_VW,
                                             fields);
         investorAuthorizationListTrxnBuilder.buildTransactions( workSession, 
                                                                 pTrCont, 
                                                                 pInvestorAuthorizationList, 
                                                                 investorAuthorizationInfo,
                                                                 OBJ_ACTIVITY_NONE,
                                                                 dstKeyTypes);

      }
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/DSTCInvestorAuthorizationTrxnBuilder.cpp-arc  $
// 
//    Rev 1.1   Jul 09 2009 15:52:50   dchatcha
// PET156681 FN14 H36 Investor Authorization.
// 
//    Rev 1.0   29 Jun 2009 16:27:14   popescu
// Initial revision.
// 
*/
