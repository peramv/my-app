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
// ^FILE   : DSTCAddressTrxnBuilder.cpp
// ^AUTHOR : Winnie Shiu
// ^DATE   : December 1999
//
// ----------------------------------------------------------
//
// ^CLASS : DSTCAddressTrxnBuilder
//
// ^MEMBER VARIABLES :  
//
// ^CODING COMMENTS  : Transaction builder for both Address and AccountMailingInfo objects
//
//******************************************************************************
#include "stdafx.h"
#include "ifasthosttransactioncontainer.hpp"
#include "dstcaddresstrxnbuilder.hpp"
#include "dstcmfshareholdertrxnbuilder.hpp"
#include "shareholder.hpp"
#include "address.hpp"
#include "addresslist.hpp"
#include "mgmtco.hpp"
#include <ifastdataimpl\dse_dstc0072_req.hpp>
#include <ifastdataimpl\dse_dstc0072_vw.hpp>
#include <ifastdataimpl\dse_dstc0072_reqrepeat_record.hpp>
#include <ifastdataimpl\dse_dstc0043_vwrepeat_record.hpp>
#include <ifastdataimpl\dse_dstc0042_vw.hpp>

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest ADDRESSBOOK_UPDATE;
}

namespace
{
   const I_CHAR* CLASSNAME = I_( "DSTCAddressTrxnBuilder" );
   const I_CHAR* BUILDTRANSACTIONS = I_( "buildTransactions" );
   const I_CHAR* BUILDADDRESSREPEAT = I_( "buildAddressRepeat");
}

namespace CND
{
   extern const I_CHAR* IFASTCBO_CONDITION;
}

namespace ifds
{
   extern CLASS_IMPORT const BFNumericFieldId ShrNum;
}

namespace KEYTYPES
{
   extern CLASS_IMPORT I_CHAR * const SHRNUM;
}

//******************************************************************************
void DSTCAddressTrxnBuilder::buildTrxnKey( DString& strKey, Shareholder* pshareholder )
{
   // Shareholder address & mailing Key consists of ShrNum only
   DString sShrnum;

   //get the address shareholder number off the address and call addIDITagValue to build key
   pshareholder->getField( ifds::ShrNum, sShrnum, BF::HOST, true );
   sShrnum.strip();
   addIDITagValue( strKey, TRXNTAG::SHRTAG, sShrnum );
   addIDITagValue( strKey, TRXNTAG::ADDRESSTAG, sShrnum );
}

//******************************************************************************
SEVERITY DSTCAddressTrxnBuilder::buildTransactions( DSTCWorkSession &workSession, 
                                                    BFAbstractCBO* pObj, 
                                                    HostTransactionContainer* pTrCont, 
                                                    BF_OBJ_ACTIVITY objActivity /*= OBJ_ACTIVITY_NONE*/ )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, BUILDTRANSACTIONS );
   Shareholder* pshareholder = dynamic_cast<Shareholder*>(pObj);

   if( pshareholder != NULL )
   {
      AddressList* addressList = NULL;
      SEVERITY severity = SEVERE_ERROR;
      int count = 0;

      //if no list do not go and get one from the database
      severity = pshareholder->getAddressList( addressList, BF::HOST, true, false );
      if( addressList != NULL && severity <= WARNING )
      {
         //define an iterator on the address list, to walk only the deletes
         BFObjIter iterDeletesAddressList( *addressList, BF::HOST, false, BFObjIter::ITERTYPE::DELETED );
         //set the number of repeates to zero

         while( !iterDeletesAddressList.end() )
         {
            Address* address = dynamic_cast<Address*>( iterDeletesAddressList.getObject() );
            BF_OBJ_ACTIVITY listObjActivity = iterDeletesAddressList.getKey().getActivity();

            //we should build the deletes first
            if( address != NULL && listObjActivity == OBJ_ACTIVITY_DELETED )
            {
               if( ( severity = buildAddressRepeat( workSession, pshareholder, address, addressList,
                                                    pTrCont, count, listObjActivity ) ) > WARNING )
               {
                  break;
               }

            }// if address not equal to null and has been deleted
            ++iterDeletesAddressList;
         }
         if( severity <= WARNING )
         {
            //define an iterator on the address list, to walk only the non-deletes
            BFObjIter iterAddressList( *addressList, BF::HOST, false, BFObjIter::ITERTYPE::NON_DELETED );

            while( !iterAddressList.end() )
            {
               Address* address = dynamic_cast<Address*>( iterAddressList.getObject() );
               BF_OBJ_ACTIVITY listObjActivity = iterAddressList.getKey().getActivity();

               //we should build the updates and the adds first
               if( address != NULL && ( listObjActivity == OBJ_ACTIVITY_ADDED || address->hasTransactionUpdates( false ) ) )
               {
                  if( ( severity = buildAddressRepeat( workSession, pshareholder, address, addressList,
                                                       pTrCont, count, listObjActivity ) ) > WARNING )
                  {
                     break;
                  }

               }// if address not equal to null and has been updated or added
               ++iterAddressList;
            }
         }
      }  // Addresslist not null
   }  // Shareholder not null
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY DSTCAddressTrxnBuilder::buildAddressRepeat( DSTCWorkSession &workSession, 
                                                     Shareholder *pshareholder, 
                                                     Address *address, 
                                                     AddressList *addressList, 
                                                     HostTransactionContainer *pTrCont, 
                                                     int &count /*no of repeats*/, 
                                                     BF_OBJ_ACTIVITY listObjActivity )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, BUILDADDRESSREPEAT );

   DString strKey, shrnum, dstrName2;
   SEVERITY severity = SEVERE_ERROR;

   DSTCAddressTrxnBuilder::buildTrxnKey( strKey, pshareholder );
   //get the shareholder number
   pshareholder->getField( ifds::ShrNum, shrnum, BF::HOST );
   pshareholder->getField( ifds::Name2, dstrName2, BF::HOST );
   //define an iterator on the HostTransactionContainer
   HostTransactionContainerIterator iterTrxnContList( pTrCont );

   // get the key for this address
   // look for the address record in the HostTransactionContainer
   iterTrxnContList.walkStrKey( strKey );
   //the trxn hasn't been handled yet, no group and sub type set,
   iterTrxnContList.walkTrxnGroup( NO_GROUP );
   iterTrxnContList.walkTrxnSubType( 0 );
   iterTrxnContList.begin();

   // If begin is pointing to the end (i.e. no object with the keyString value )
   // then update fix area : build key and add transaction
   BFData* pDataReq = NULL;
   BFData* pDataRes = NULL;


   if( iterTrxnContList.end() )
   {
      pDataReq = new BFData( ifds::DSTC0072_REQ );
      pDataRes = new BFData( ifds::DSTC0072_VW );

      DString strTrack,strActivity;
      addressList->getTrackActivity(strTrack,strActivity);
      pDataReq->setElementValue( ifds::Track, strTrack, false, false );
      pDataReq->setElementValue( ifds::Activity, strActivity, false, false );

      DString mgmtCoId;
      workSession.getMgmtCo().getField(ifds::CompanyId, mgmtCoId, BF::HOST);
      pDataReq->setElementValue( ifds::CompanyId, mgmtCoId );

      pDataReq->setElementValue( ifds::ShrNum, shrnum, false, false );
      pDataReq->setElementValue( ifds::Name2, dstrName2, false, false );
      shrnum.stripLeading( '0' ).strip();

      DSTCWorkSession::setRunMode( pDataReq, listObjActivity );

      DString keyTypes;
      addIDITagValue( keyTypes, KEYTYPES::SHRNUM, shrnum );

      TRXN_TYPE trxnType = listObjActivity == OBJ_ACTIVITY_ADDED ? NEW_ADDRESS : UPDATE_ADDRESS;

      JData *jdata = new JData( DSTC_REQUEST::ADDRESSBOOK_UPDATE, pDataReq, pDataRes );
      pTrCont->addTransaction( strKey, jdata, listObjActivity, trxnType, keyTypes );

   }
   else
   {
      pDataReq = (*iterTrxnContList)->getRequestDataObject();
   }

   //************************ Kanji Address **************************************
   //create a repeat for the request and filled in
   BFData repeat( ifds::DSTC0072_REQRepeat_Record );

   address->getData( repeat, BF::HOST );
   //set the RunMode field to the address trxn
   DSTCWorkSession::setRunMode( &repeat, listObjActivity );     
   count++; // set repeat count
   pDataReq->setElementValue( ifds::RepeatCount, DString::asString( count ), false, false );

   //add the repeat to the retrieved request(req)

   pDataReq->addRepeat( repeat );

   //******************************************************************************
   //************************ Kana Address **************************************
   //create a repeat for the request and filled in
   DString strMarket = DSTCommonFunctions::getMarket();

   if (strMarket == MARKET_IDS::JAPAN)
   {
      DString kaddrline1, kaddrline2, kaddrline3, kaddrline4, kaddrline5;
      DString kaddressVer, kaddressRid, addresscode;

      address->getField ( ifds::kAddrLine1, kaddrline1, BF::HOST );
      address->getField ( ifds::kAddrLine2, kaddrline2, BF::HOST );
      address->getField ( ifds::kAddrLine3, kaddrline3, BF::HOST );
      address->getField ( ifds::kAddrLine4, kaddrline4, BF::HOST );
      address->getField ( ifds::kAddrLine5, kaddrline5, BF::HOST );
      address->getField ( ifds::KAddrFileVer, kaddressVer, BF::HOST );
      address->getField ( ifds::KAddrFileRid, kaddressRid, BF::HOST );
      address->getField ( ifds::AddrCode, addresscode, BF::HOST );
      addresscode = I_( "K" ) + addresscode;
      // if all kana lines are empty and AddressfileRid == 0, then no action required
      if( (kaddrline1 != NULL_STRING ||
           kaddrline2 != NULL_STRING ||
           kaddrline3 != NULL_STRING ||
           kaddrline4 != NULL_STRING ||
           kaddrline5 != NULL_STRING || kaddressRid != I_( "0" ) ) ||
          ( kaddressRid != I_( "0" ) && listObjActivity == OBJ_ACTIVITY_DELETED ) )
      {
         BFData repeat( ifds::DSTC0072_REQRepeat_Record );

         count++; // set repeat count
         pDataReq->setElementValue( ifds::RepeatCount, DString::asString( count ), false, false );

         address->getData( repeat, BF::HOST );

         // if KaddressRid == 0, then set RunMode to 'Add',
         //but the record is not deleted
         if( kaddressRid == I_( "0" ) && listObjActivity != OBJ_ACTIVITY_DELETED )
         {
            //set the RunMode field to the address trxn
            DSTCWorkSession::setRunMode( &repeat, OBJ_ACTIVITY_ADDED );     
            repeat.setElementValue( ifds::Confirm, I_( "Y" ), false, false );
         }
         else
         {
            // if at all address lines are empty, then perform delete action
            if( ( kaddrline1 == NULL_STRING &&
                  kaddrline2 == NULL_STRING &&
                  kaddrline3 == NULL_STRING &&
                  kaddrline4 == NULL_STRING &&
                  kaddrline5 == NULL_STRING ) || listObjActivity == OBJ_ACTIVITY_DELETED )
            {
               //set the RunMode field to the address trxn
               DSTCWorkSession::setRunMode( &repeat, OBJ_ACTIVITY_DELETED ); 
            }
            else // if KaddressRid not equal to 0 and at least one address line is filled, then perform record update 
            {
               //set the RunMode field to the address trxn
               DSTCWorkSession::setRunMode( &repeat, OBJ_ACTIVITY_NONE ); 
            }
         }
         repeat.setElementValue( ifds::AddrCode, addresscode, false, false );
         repeat.setElementValue( ifds::AddrLine1, kaddrline1, false, false );
         repeat.setElementValue( ifds::AddrLine2, kaddrline2, false, false );
         repeat.setElementValue( ifds::AddrLine3, kaddrline3, false, false );
         repeat.setElementValue( ifds::AddrLine4, kaddrline4, false, false );
         repeat.setElementValue( ifds::AddrLine5, kaddrline5, false, false );
         repeat.setElementValue( ifds::AddressFileVer, kaddressVer, false, false );
         repeat.setElementValue( ifds::AddressFileRid, kaddressRid, false, false );

         //add the repeat to the retrieved request(req)
         pDataReq->addRepeat( repeat );
      }
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/DSTCAddressTrxnBuilder.cpp-arc  $
 * 
 *    Rev 1.17   Nov 14 2004 14:31:24   purdyech
 * PET910 - .NET Conversion
 * 
 *    Rev 1.16   May 20 2004 14:16:58   popescu
 * PTS 10026123, address 01, for nominee and intermediary accounts by tax type and reg address code
 * 
 *    Rev 1.15   Mar 21 2003 18:03:56   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.14   Oct 09 2002 23:54:16   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.13   Aug 29 2002 12:55:20   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.12   22 May 2002 18:27:02   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.11   Mar 07 2002 19:39:10   HERNANDO
 * PTS 10007183 - Fixed missing Name2.  Copy Name2 from Shareholder.
 * 
 *    Rev 1.10   Feb 25 2002 18:55:16   PURDYECH
 * Phase 1 of BFData Rollout - Base Component Compatibility
 * 
 *    Rev 1.9   23 May 2001 14:39:54   SMITHDAV
 * Fill CompanyId to all request Data objects that are posted to the HTC.
 * 
 *    Rev 1.8   03 May 2001 14:06:12   SMITHDAV
 * Session management restructuring.
 * 
 *    Rev 1.7   09 Mar 2001 18:03:46   BUZILAMI
 * XchgData elimination fixes
 * 
 *    Rev 1.6   09 Feb 2001 15:01:10   SMITHDAV
 * Removed commented code; Removed unneeded includes; Some fixes.
 * 
 *    Rev 1.5   Jan 31 2001 16:10:54   YINGBAOL
 * set track and activity values for update transactions
 * 
 *    Rev 1.4   Jan 16 2001 14:01:16   OLTEANCR
 * modified buildTransaction(..)
 * 
 *    Rev 1.3   Jan 16 2001 13:53:26   OLTEANCR
 * 
 *    Rev 1.2   Dec 17 2000 20:22:58   OLTEANCR
 * changed to use a precompiled header
 * 
 *    Rev 1.1   May 09 2000 14:27:08   BUZILA
 * using OBJ_NONE
 * 
 *    Rev 1.0   Feb 15 2000 10:59:52   SMITHDAV
 * Initial revision.
// 
//    Rev 1.13   Feb 03 2000 10:51:54   BUZILA
// changed to call hasTransactionUpdates instead of  hasHostUpdates
// 
//    Rev 1.12   Feb 02 2000 10:33:52   BUZILA
// we should not send transactions for uncommited data
// 
//    Rev 1.11   Jan 31 2000 13:39:18   POPESCUS
// fixes for the sending the deletes first and then the adds and updates
// 
//    Rev 1.10   Jan 26 2000 14:19:44   WINNIE
// fix delete logic to delete the Kana address
// 
//    Rev 1.9   Jan 11 2000 08:40:30   POPESCUS
// small change related to setting the sahreholder number on the address update fixed area
// 
//    Rev 1.8   Jan 09 2000 13:18:36   POPESCUS
// added the group id to the lists
// 
//    Rev 1.7   Jan 07 2000 18:20:18   POPESCUS
// fixes in trxns
// 
//    Rev 1.6   Jan 07 2000 17:36:02   WINNIE
// fix deletion
// 
//    Rev 1.5   Jan 06 2000 12:02:54   POPESCUS
// fix related to filter more the HTC 
// 
//    Rev 1.4   Dec 17 1999 10:15:24   WINNIE
// Assign address code for the Kana address with a leading 'K'.
// 
//    Rev 1.3   Dec 15 1999 11:47:34   POPESCUS
// do not get the list from the database if there is none in repository
// 
//    Rev 1.2   Dec 13 1999 16:54:18   WINNIE
// Add logic to update kana address
// 
//    Rev 1.1   Dec 12 1999 17:55:06   POPESCUS
// Delete the XchgData object and minor fixes
// 
*/