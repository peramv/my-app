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
//    Copyright 1999 by DST Systems, Inc.
//
//
//******************************************************************************
//
// ^FILE   : DSTCAcctMailingTrxnBuilder.cpp
// ^AUTHOR : Winnie Shiu
// ^DATE   : December 1999
//
// ----------------------------------------------------------
//
// ^CLASS : DSTCAcctMailingTrxnBuilder
//
// ^MEMBER VARIABLES :  
//
// ^CODING COMMENTS  : Transaction builder for both Address and AccountMailingInfo objects
//
//******************************************************************************

#include "stdafx.h"
#include "ifasthosttransactioncontainer.hpp"
#include "dstcacctmailingtrxnbuilder.hpp"
#include "shareholder.hpp"
#include "mfaccount.hpp"
#include "accountmailinginfo.hpp"
#include "accountmailinglist.hpp"
#include "mgmtco.hpp"
#include <ifastdataimpl\dse_dstc0114_req.hpp>
#include <ifastdataimpl\dse_dstc0114_vw.hpp>

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest ACCTMAILING_UPDATE;
}

namespace
{
   const I_CHAR* CLASSNAME = I_( "DSTCAcctMailingTrxnBuilder" );
   const I_CHAR* BUILDTRANSACTIONS = I_( "buildTransactions" );
}

namespace CND
{
   extern const I_CHAR* IFASTCBO_CONDITION;
}

namespace ifds
{
   //extern CLASS_IMPORT const long ;
   extern CLASS_IMPORT const BFNumericFieldId ShrNum;
   extern CLASS_IMPORT const BFNumericFieldId AccountNum;

}

namespace KEYTYPES
{
   extern CLASS_IMPORT I_CHAR * const SHRNUM;
   extern CLASS_IMPORT I_CHAR * const ACCOUNTNUM;
}

//******************************************************************************
void DSTCAcctMailingTrxnBuilder::buildTrxnKey( DString& strKey, 
                                               Shareholder* pShareholder, 
                                               AccountMailingInfo* acctmailing )
{
   // Shareholder address & mailing Key consists of ShrNum only
   DString sAcctnum;
   DString shrNum;

   //get the address account number off the address and call addIDITagValue to build key
   acctmailing->getField( ifds::AccountNum, sAcctnum, BF::HOST, true );
   pShareholder->getField( ifds::ShrNum, shrNum, BF::HOST, true );
   sAcctnum.strip();
   shrNum.strip();
   addIDITagValue( strKey, TRXNTAG::SHRTAG, shrNum );
   addIDITagValue( strKey, TRXNTAG::ACCTMAILINGTAG, sAcctnum );
}

//******************************************************************************
SEVERITY DSTCAcctMailingTrxnBuilder::buildTransactions( DSTCWorkSession &workSession, 
                                                        BFAbstractCBO* pObj, 
                                                        HostTransactionContainer* pTrCont, 
                                                        BF_OBJ_ACTIVITY objActivity /*= OBJ_ACTIVITY_NONE*/ )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, BUILDTRANSACTIONS );
   Shareholder* pshareholder = dynamic_cast<Shareholder*>(pObj);

   if( pshareholder != NULL )
   {
      AccountMailingList* mailingList = NULL;
      DString shrnum;
      SEVERITY severity = SEVERE_ERROR;

      pshareholder->getField( ifds::ShrNum, shrnum, BF::HOST );
      shrnum.strip();

      //if no list do not go and get one from the database
      severity = pshareholder->getAccountMailingList( mailingList, BF::HOST, false );
      if( mailingList != NULL && severity <= WARNING )
      {
         //define an iterator on the address list
         BFObjIter iterMailingList( *mailingList, BF::HOST );
         int count = 0;

         while( !iterMailingList.end() )
         {
            AccountMailingInfo* acctMailing = dynamic_cast<AccountMailingInfo*>( iterMailingList.getObject() );
            BF_OBJ_ACTIVITY listObjActivity = iterMailingList.getKey().getActivity();

            if( acctMailing != NULL && (listObjActivity == OBJ_ACTIVITY_ADDED || acctMailing->hasTransactionUpdates( false ) ) )
            {
               DString strKey, transId = I_("00114");
               //get the string key for the account
               DSTCAcctMailingTrxnBuilder::buildTrxnKey( strKey, pshareholder, acctMailing );

               //fill in the request update
               //set the RunMode field to the account mailing trxn

               BFData *request = new BFData( ifds::DSTC0114_REQ );
               BFData* response = new BFData( ifds::DSTC0114_VW );

               acctMailing->getData( *request, BF::HOST );

               DSTCWorkSession::setRunMode( request, listObjActivity );

               //check first if this is a new account or updated
               TRXN_TYPE trxnType = listObjActivity == OBJ_ACTIVITY_ADDED ? NEW_MAILING : UPDATE_MAILING;

               DString keyTypes, accountNum;         

               acctMailing->getField( ifds::AccountNum, accountNum, BF::HOST, true );
               accountNum.strip();             

               DString strTrack,strAvtivity;
               mailingList->getTrackActivity(strTrack,strAvtivity);;

               DString mgmtCoId;
               workSession.getMgmtCo().getField(ifds::CompanyId, mgmtCoId, BF::HOST);
               request->setElementValue( ifds::CompanyId, mgmtCoId );

               request->setElementValue( ifds::AccountNum, accountNum, false, false );
               request->setElementValue( ifds::Track, strTrack, false, false );
               request->setElementValue( ifds::Activity, strAvtivity, false, false );

               //build the key
               addIDITagValue( keyTypes, KEYTYPES::SHRNUM, shrnum );
               addIDITagValue( keyTypes, KEYTYPES::ACCOUNTNUM, accountNum );

               //add the transaction to the container; the right side of the XchgData
               JData *jdata = new JData( DSTC_REQUEST::ACCTMAILING_UPDATE, request, response );
               pTrCont->addTransaction( strKey, jdata, listObjActivity, trxnType, keyTypes );
            }  // if address not equal to null and has been updated 
            ++iterMailingList;
         }  // while loop
      }  // AcctMailinglist not null
   }  // Shareholder not null
   return(GETCURRENTHIGHESTSEVERITY());
}


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/DSTCAcctMailingTrxnBuilder.cpp-arc  $
 * 
 *    Rev 1.13   Nov 14 2004 14:31:18   purdyech
 * PET910 - .NET Conversion
 * 
 *    Rev 1.12   Mar 21 2003 18:03:44   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.11   Oct 09 2002 23:54:14   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.10   Aug 29 2002 12:55:20   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.9   22 May 2002 18:26:50   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.8   Feb 25 2002 18:55:14   PURDYECH
 * Phase 1 of BFData Rollout - Base Component Compatibility
 * 
 *    Rev 1.7   23 May 2001 14:39:56   SMITHDAV
 * Fill CompanyId to all request Data objects that are posted to the HTC.
 * 
 *    Rev 1.6   03 May 2001 14:06:10   SMITHDAV
 * Session management restructuring.
 * 
 *    Rev 1.5   Feb 12 2001 14:55:12   YINGBAOL
 * fix key builder bug and some other bugs
 * 
 *    Rev 1.4   Jan 31 2001 16:10:52   YINGBAOL
 * set track and activity values for update transactions
 * 
 *    Rev 1.3   Jan 16 2001 14:00:50   OLTEANCR
 * modified buildTransaction(..)
 * 
 *    Rev 1.2   Jan 16 2001 13:53:26   OLTEANCR
 * 
 *    Rev 1.1   Dec 17 2000 20:22:58   OLTEANCR
 * changed to use a precompiled header
 * 
 *    Rev 1.0   Feb 15 2000 10:59:52   SMITHDAV
 * Initial revision.
// 
//    Rev 1.10   Feb 03 2000 10:51:54   BUZILA
// changed to call hasTransactionUpdates instead of  hasHostUpdates
// 
//    Rev 1.9   Feb 02 2000 10:33:52   BUZILA
// we should not send transactions for uncommited data
// 
//    Rev 1.8   Jan 20 2000 11:44:22   POPESCUS
// fix obj activity flag
// 
//    Rev 1.7   Jan 09 2000 13:18:34   POPESCUS
// added the group id to the lists
// 
//    Rev 1.6   Jan 07 2000 18:20:16   POPESCUS
// fixes in trxns
// 
//    Rev 1.5   Jan 07 2000 17:36:00   WINNIE
// fix deletion
// 
//    Rev 1.4   Dec 15 1999 11:47:32   POPESCUS
// do not get the list from the database if there is none in repository
// 
//    Rev 1.3   Dec 12 1999 18:45:34   POPESCUS
// some fixes
// 
//    Rev 1.2   Dec 12 1999 17:55:04   POPESCUS
// Delete the XchgData object and minor fixes
// 
//    Rev 1.1   Dec 10 1999 16:49:52   WINNIE
// remove test code
// 
//    Rev 1.0   Dec 10 1999 16:31:12   WINNIE
// Initial revision.

*/