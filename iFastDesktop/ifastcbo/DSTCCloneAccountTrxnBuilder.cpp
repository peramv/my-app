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
// ^FILE   : DSTCCloneAccountTrxnBuilder.cpp
// ^AUTHOR : Serban Popescu
// ^DATE   : November 2006
//
// ----------------------------------------------------------
//
// ^CLASS : DSTCCloneAccountTrxnBuilder
//
// ^MEMBER VARIABLES :  
//
// ^CODING COMMENTS  :
//
//******************************************************************************
#include "stdafx.h"
#include "dstccloneaccounttrxnbuilder.hpp"

#include <ifastdataimpl\dse_dstc0377_req.hpp>
#include <ifastdataimpl\dse_dstc0377_vw.hpp>

#include "cloneaccount.hpp"
#include "mfaccount.hpp"
#include "ifasthosttransactioncontainer.hpp"
#include "mgmtco.hpp"

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest CLONE_ACCOUNT;
}
namespace
{
   const I_CHAR* CLASSNAME          = I_( "DSTCCloneAccountTrxnBuilder" );
   const I_CHAR* BUILDTRANSACTIONS  = I_( "buildTransactions" );
}

namespace CND
{
   extern const I_CHAR* IFASTCBO_CONDITION;
}

namespace ifds
{
}

namespace KEYTYPES
{
   extern CLASS_IMPORT I_CHAR * const SHRNUM;
   extern CLASS_IMPORT I_CHAR * const ACCOUNTNUM;
}

//******************************************************************************
void DSTCCloneAccountTrxnBuilder::buildTrxnKey (DString &strKey, CloneAccount *pCloneAccount)
{
   DString accountNum;

//get the account number off the account
   pCloneAccount->getField (ifds::AccountNum, accountNum, BF::HOST, true);
   accountNum.stripLeading ('0');
   accountNum.strip();
//build the key
   addIDITagValue (strKey, TRXNTAG::ACCTTAG, accountNum);
}

//******************************************************************************
SEVERITY DSTCCloneAccountTrxnBuilder::buildTransactions( DSTCWorkSession &workSession,
                                                         BFAbstractCBO *pObj, 
                                                         HostTransactionContainer* pTrCont, 
                                                         BF_OBJ_ACTIVITY objActivity /*= OBJ_ACTIVITY_NONE*/ )
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           BUILDTRANSACTIONS);
   CloneAccount* pCloneAccount  = dynamic_cast <CloneAccount  *> (pObj);
   
   if (pCloneAccount && pCloneAccount->hasTransactionUpdates (true))
   {
      BFData *request = new BFData (ifds::DSTC0377_REQ);
      BFData *response = new BFData (ifds::DSTC0377_VW);
//fill in the request update, only the part for which the CloneAccount is responsible
      pCloneAccount->getData (*request, BF::HOST);

      DString strTrack,
         strAvtivity,
         mgmtCoId;
      
      pCloneAccount->getTrackActivity (strTrack, strAvtivity);          
      workSession.getMgmtCo().getField (ifds::CompanyId, mgmtCoId, BF::HOST);

      request->setElementValue (ifds::Track, strTrack, false, false);
      request->setElementValue (ifds::Activity, strAvtivity, false, false);
      request->setElementValue (ifds::CompanyId, mgmtCoId);

      DString strKey,
         keyTypes,
         accountNum,
         shrNum;

//get the string key for the account
      DSTCCloneAccountTrxnBuilder::buildTrxnKey (strKey, pCloneAccount);
//get the shareholder number to be cloned off the clone account obbject
      pCloneAccount->getField (ifds::ShrNum, shrNum, BF::HOST, true);
//build the key
      shrNum.stripLeading ('0');
      shrNum.strip();
      addIDITagValue (keyTypes, KEYTYPES::SHRNUM, shrNum);

//get the account number off the account
      pCloneAccount->getField (ifds::AccountNum, accountNum, BF::HOST, true);
      accountNum.strip();
//build the key
      accountNum.stripLeading ('0');
      accountNum.strip();
      addIDITagValue (keyTypes, KEYTYPES::ACCOUNTNUM, accountNum);

      JData *jdata = new JData (DSTC_REQUEST::CLONE_ACCOUNT, request, response);
      pTrCont->addTransaction (strKey, jdata, objActivity, CLONE_ACCOUNT, keyTypes);
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/DSTCCloneAccountTrxnBuilder.cpp-arc  $
// 
//    Rev 1.0   Nov 08 2006 22:19:36   popescu
// Initial revision.
 * 

// 
*/