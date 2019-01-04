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
//    Copyright 2004 by International Financial Data Services
//
//
//******************************************************************************
//
// ^FILE   : DSTCMFShareholderTrxnBuilder.cpp
// ^AUTHOR : Ram Singaram
// ^DATE   : October 1999
//
// ----------------------------------------------------------
//
// ^CLASS : DSTCMFShareholderTrxnBuilder
//
// ^MEMBER VARIABLES :  
//
// ^CODING COMMENTS  :
//
//******************************************************************************
#include "stdafx.h"
#include "ifasthosttransactioncontainer.hpp"

#include "dstcacctmailingtrxnbuilder.hpp"
#include "dstcaddresstrxnbuilder.hpp"
#include "dstcallocationtrxnbuilder.hpp"
#include "dstcbankinstructionstrxnbuilder.hpp"
#include "dstcdemographicstrxnbuilder.hpp"
#include "dstcmfshareholdertrxnbuilder.hpp"
#include "dstcshareholderremarkstrxnbuilder.hpp"
#include "dstcshrfundbrokertrxnbuilder.hpp"
#include "dstcshrfamilytrxnbuilder.hpp"
#include "dstcshrfundsponsoragrmnttrxnbuilder.hpp"
#include "mgmtco.hpp"
#include "shareholder.hpp"

#include <ifastdataimpl\dse_dstc0075_req.hpp>
#include <ifastdataimpl\dse_dstc0075_vw.hpp>

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest SHAREHOLDER_UPDATE;
}
namespace
{
   const I_CHAR* CLASSNAME = I_("DSTCMFShareholderTrxnBuilder");
   const I_CHAR* BUILDTRANSACTIONS = I_("buildTransactions");
}

namespace CND
{
   extern const I_CHAR* IFASTCBO_CONDITION;
}

namespace ifds
{
   extern CLASS_IMPORT const BFNumericFieldId ShrNum;
   extern CLASS_IMPORT const BFTextFieldId ShrNumCtrl;
}

namespace KEYTYPES
{
   extern CLASS_IMPORT I_CHAR * const SHRNUM;
}

void DSTCMFShareholderTrxnBuilder::buildTrxnKey(DString& strKey, Shareholder* mfShareholder)
{
   DString shrNum;

   //get the shareholder number off the shareholder
   mfShareholder->getField(ifds::ShrNum, shrNum, BF::HOST, true);
   shrNum.stripLeading('0');
   shrNum.strip();
   //build the key
   addIDITagValue(strKey, TRXNTAG::SHRTAG, shrNum);
}

//******************************************************************************
SEVERITY DSTCMFShareholderTrxnBuilder::buildTransactions(DSTCWorkSession &workSession,
                                                          BFAbstractCBO* pObj,
                                                          HostTransactionContainer* pTrCont, 
                                                          BF_OBJ_ACTIVITY objActivity /*= OBJ_ACTIVITY_NONE*/)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, BUILDTRANSACTIONS);
   SEVERITY severity = SEVERE_ERROR;
   Shareholder* mfShareholder = NULL;
   mfShareholder = dynamic_cast<Shareholder*>(pObj);

   //check if the shareholder itself is updated,
   //do not ask the children (call hasTransactionUpdates with false)
   if(mfShareholder != NULL && (objActivity == OBJ_ACTIVITY_ADDED || mfShareholder->hasTransactionUpdates(false)))
   {

      BFData *request = new BFData(ifds::DSTC0075_REQ);
      BFData *response = new BFData(ifds::DSTC0075_VW);
      //fill in the request update, only the part for which the MFShareholder is responsible
      mfShareholder->getData(*request, BF::HOST);


      DString strTrack,strAvtivity;
      mfShareholder->getTrackActivity(strTrack,strAvtivity);
      request->setElementValue(ifds::Track, strTrack, false, false);
      request->setElementValue(ifds::Activity, strAvtivity, false, false);

      DString mgmtCoId;
      workSession.getMgmtCo().getField(ifds::CompanyId, mgmtCoId, BF::HOST);
      request->setElementValue(ifds::CompanyId, mgmtCoId);

      //mfShareholder->getData(*request, BF::HOST);
      //set the RunMode field to the ShareholderUpdate trxn
      DSTCWorkSession::setRunMode(request, objActivity);

      DString strKey;

      //get the string key for the shareholder
      DSTCMFShareholderTrxnBuilder::buildTrxnKey(strKey, mfShareholder);
      //check first if this is a new shareholder or updated
      TRXN_TYPE trxnType = objActivity == OBJ_ACTIVITY_ADDED ? NEW_SHAREHOLDER : UPDATE_SHAREHOLDER;
      //add the transaction to the container; the right side of the XchgData

      DString keyTypes, shrNum;
      mfShareholder->getField(ifds::ShrNum, shrNum, BF::HOST, true);
      shrNum.stripLeading('0');
      shrNum.strip();

      addIDITagValue(keyTypes, KEYTYPES::SHRNUM, shrNum);

      DString shrNumCtrl;
      workSession.getOption(ifds::ShrNumCtrl, shrNumCtrl, BF::HOST);
      if(shrNumCtrl.strip().upperCase() == I_("M"))
         shrNumCtrl = I_("Y");
      else
         shrNumCtrl = I_("N");
      request->setElementValue(ifds::ShrNumManual, shrNumCtrl, false, false);

      JData *jdata = new JData(DSTC_REQUEST::SHAREHOLDER_UPDATE, request, response);
      pTrCont->addTransaction(strKey, jdata, objActivity, trxnType, keyTypes);
   }
   //call the transaction builders of the objects that are contained by the shareholder
   //build demographics transactions 
   //moved to account level for CIBC KYC
   //DSTCDemographicsTrxnBuilder::buildTransactions(workSession, mfShareholder, pTrCont, objActivity);

   //build the address trxns
   DSTCAddressTrxnBuilder::buildTransactions(workSession, mfShareholder, pTrCont, objActivity);

   //buld the accountmaling 
   DSTCAcctMailingTrxnBuilder::buildTransactions(workSession, mfShareholder, pTrCont, objActivity);

   //bank instructions builder
   DSTCBankInstructionsTrxnBuilder::buildTransactions(workSession, mfShareholder, pTrCont, objActivity);

   //build the shareholder default allocation instructions
   DSTCAllocationTrxnBuilder::buildTransactions(workSession, mfShareholder, pTrCont, objActivity);

   //build the shareholder remarks transactions
   DSTCShareholderRemarksTrxnBuilder::buildTransactions(workSession, mfShareholder, pTrCont, objActivity);

   DSTCShhrFamilyTrxnBuilder::buildTransactions(workSession, mfShareholder, pTrCont, objActivity);

	DSTCShrFundSponsorAgrmntTrxnBuilder::buildTransactions( workSession, mfShareholder, pTrCont, objActivity );

   DSTCShrFundBrokerTrxnBuilder::buildTransactions( workSession, mfShareholder, pTrCont, objActivity );
   
	return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/DSTCMFShareholderTrxnBuilder.cpp-arc  $
 * 
 *    Rev 1.20   Nov 28 2004 14:06:52   vadeanum
 * PET1117 FN08 - Shareholder Fund Broker support 
 * 
 *    Rev 1.19   Nov 14 2004 14:32:56   purdyech
 * PET910 - .NET Conversion
 * 
 *    Rev 1.18   Jul 27 2004 15:22:32   VADEANUM
 * PET1117 FN01 - Shareholder Static Data update support.
 * 
 *    Rev 1.17   Jul 11 2003 16:03:36   FENGYONG
 * move demographic from shareholder to MFAccount
 * 
 *    Rev 1.16   May 22 2003 15:00:46   popescu
 * name change 'left overs'
 * 
 *    Rev 1.15   May 22 2003 14:12:32   popescu
 * Replaced name 'BankInstr' with 'BankInstructions'; 
 * simplified child lists getters for the Shareholder object
 * 
 *    Rev 1.14   Mar 21 2003 18:05:58   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.13   Jan 13 2003 17:59:30   sanchez
 * Changes for Shareholer
 * 
 *    Rev 1.12   Oct 09 2002 23:54:20   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.11   Aug 29 2002 12:55:32   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.10   22 May 2002 18:27:56   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.9   Feb 25 2002 18:55:34   PURDYECH
 * Phase 1 of BFData Rollout - Base Component Compatibility
 * 
 *    Rev 1.8   Jul 19 2001 18:25:18   OLTEANCR
 *  setElementValue for ShrNumManual
 * 
 *    Rev 1.7   23 May 2001 14:39:30   SMITHDAV
 * Fill CompanyId to all request Data objects that are posted to the HTC.
 * 
 *    Rev 1.6   03 May 2001 14:06:20   SMITHDAV
 * Session management restructuring.
 * 
 *    Rev 1.5   09 Mar 2001 18:03:42   BUZILAMI
 * XchgData elimination fixes
 * 
 *    Rev 1.4   09 Feb 2001 15:01:32   SMITHDAV
 * Removed commented code; Removed unneeded includes; Some fixes.
 * 
 *    Rev 1.3   Jan 31 2001 16:10:58   YINGBAOL
 * set track and activity values for update transactions
 * 
 *    Rev 1.2   Jan 16 2001 13:53:36   OLTEANCR
 * 
 *    Rev 1.1   Dec 17 2000 20:23:10   OLTEANCR
 * changed to use a precompiled header
 * 
 *    Rev 1.0   Feb 15 2000 10:59:56   SMITHDAV
 * Initial revision.
// 
//    Rev 1.10   Feb 03 2000 10:52:00   BUZILA
// changed to call hasTransactionUpdates instead of  hasHostUpdates
// 
//    Rev 1.9   Feb 02 2000 10:33:58   BUZILA
// we should not send transactions for uncommited data
// 
//    Rev 1.8   Jan 20 2000 18:03:44   WINNIE
// Change default allocation builder for new structure
// 
//    Rev 1.7   Jan 07 2000 14:18:14   POPESCUS
// fixes
// 
//    Rev 1.6   Dec 24 1999 11:37:54   WINNIE
// misc
// 
//    Rev 1.5   Dec 12 1999 17:55:46   POPESCUS
// Delete the XchgData object and minor fixes
// 
*/