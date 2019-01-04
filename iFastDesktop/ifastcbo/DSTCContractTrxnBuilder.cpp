//*****************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by International Financial Data Services
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2005 by International Financial Data Services
//
//*****************************************************************************
//
// ^FILE   : DSTCContractTrxnBuilder.cpp
// ^AUTHOR : Celia Zhang
// ^DATE   : May 2000
//
// ----------------------------------------------------------
//
// ^CLASS : DSTCContractTrxnBuilder
//
// ^MEMBER VARIABLES :  
//
// ^CODING COMMENTS  :
//
//******************************************************************************
#include "stdafx.h"
#include "ifasthosttransactioncontainer.hpp"
#include "contractinfo.hpp"
#include "contractinfolist.hpp"
#include <ifastdataimpl\dse_dstc0161_req.hpp>
#include <ifastdataimpl\dse_dstc0161_reqrepeat_record.hpp>
#include <ifastdataimpl\dse_dstc0161_vw.hpp>
#include "dstccontracttrxnbuilder.hpp"
#include "mfaccount.hpp"
#include "mgmtco.hpp"

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest CONTRACT_UPDATE;
   extern CLASS_IMPORT const DSTCRequest MULTI_CONTRACT_UPDATE;
}

namespace
{
   const I_CHAR* CLASSNAME          = I_( "DSTCContractTrxnBuilder" );
   const I_CHAR* BUILDTRANSACTIONS  = I_( "buildTransactions" );
}

namespace CND
{
   extern const I_CHAR* IFASTCBO_CONDITION;
}

namespace DBR
{
   extern CLASS_IMPORT const BFNumericFieldId AccountNum;
   extern CLASS_IMPORT const BFNumericFieldId RepeatCount;
}

namespace KEYTYPES
{
   extern CLASS_IMPORT I_CHAR * const ACCOUNTNUM;
}

//******************************************************************************
void DSTCContractTrxnBuilder::buildTrxnKey( DString& strKey, MFAccount* pMFAccount)
{
   DString dstrAccountNum;

   pMFAccount->getField( ifds::AccountNum, dstrAccountNum, BF::HOST, true );
   dstrAccountNum.stripLeading( '0' );
   dstrAccountNum.strip();
   addIDITagValue( strKey, TRXNTAG::CONTRACTTAG, dstrAccountNum );
}

//******************************************************************************
SEVERITY DSTCContractTrxnBuilder::buildTransactions( DSTCWorkSession &workSession, 
                                                     BFAbstractCBO* pObj,
                                                     HostTransactionContainer* pTrCont, 
                                                     BF_OBJ_ACTIVITY objActivity /*= OBJ_ACTIVITY_NONE*/ )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, BUILDTRANSACTIONS );

   SEVERITY severity = SEVERE_ERROR;
   MFAccount* pMFAccount = dynamic_cast<MFAccount*>(pObj);
   ContractInfoList* pContractInfoList = NULL;
   ContractInfo* pContractInfo = NULL;
   BF_OBJ_ACTIVITY listObjActivity;

   //check if the ContractInfo itself is updated,
   //do not ask the children (call hasTransactionUpdates with false) and
   //if no list do not go and get one from the database

   if( pMFAccount != NULL )
   {
      bool bMultiContract = false;
      bool bMultiContr = false;
      severity = pMFAccount->getContractInfoList( pContractInfoList, BF::HOST, false);

      if( (pContractInfoList != NULL) && (severity <= WARNING ) && pContractInfoList->hasTransactionUpdates( ) )
      {
         //define an iterator on the ContractInfo list
         bMultiContract = pContractInfoList->setMultiContrPerm( bMultiContr ); 
         if( bMultiContract )
         {
            BFObjIter iterContractInfoList( *pContractInfoList, BF::HOST ); 
            iterContractInfoList.begin();
            //define an iterator on the HostTransactionContainer
            HostTransactionContainerIterator iterTrxnContList( pTrCont );
            //** Data* fixedArea = NULL;
            DString keyString;
            DSTCContractTrxnBuilder::buildTrxnKey( keyString, pMFAccount );
            //set the filter on the string key
            iterTrxnContList.walkStrKey( keyString );
            //the trxn hasn't been handled yet, no group and sub type set,
            iterTrxnContList.walkTrxnGroup( NO_GROUP );
            iterTrxnContList.walkTrxnSubType( 0 );
            //start walking the list
            iterTrxnContList.begin();
            BFData* request = NULL;
            BFData* response = NULL;
            if( iterTrxnContList.end() )    // Fixed Area does not exist, so create one
            {
               DString keyTypes, dstrAccountNum, strEffectiveDate;
               request = new BFData( ifds::DSTC0161_REQ );
               response = new BFData( ifds::DSTC0161_VW );
               DString strTrack,strAvtivity;
               pContractInfoList->getTrackActivity(strTrack,strAvtivity);;
               request->setElementValue( ifds::Track, strTrack, false, false );
               request->setElementValue( ifds::Activity, strAvtivity, false, false );
               DString mgmtCoId;
               workSession.getMgmtCo().getField(ifds::CompanyId, mgmtCoId, BF::HOST);
               request->setElementValue( ifds::CompanyId, mgmtCoId );
               pMFAccount->getField( ifds::AccountNum, dstrAccountNum, BF::HOST, true );
               dstrAccountNum.stripLeading( '0' );
               dstrAccountNum.strip();
               request->setElementValue( ifds::AccountNum, dstrAccountNum, false, false );

               addIDITagValue( keyTypes, KEYTYPES::ACCOUNTNUM, dstrAccountNum );   

               JData *jdata = new JData( DSTC_REQUEST::MULTI_CONTRACT_UPDATE, request, response );
               pTrCont->addTransaction( keyString, jdata, objActivity, NOT_PERSISTENT, keyTypes );
            }
            else
            {
               request = (*iterTrxnContList)->getRequestDataObject();
            }
            int count = 0;
            while( !iterContractInfoList.end() )
            {
//               if ( listObjActivity == OBJ_ACTIVITY_ADDED || iterContractInfoList.hasTransactionUpdates( ) 
//                    || listObjActivity == OBJ_ACTIVITY_DELETED )
               if( iterContractInfoList.hasTransactionUpdates() )
               {
                  pContractInfo = dynamic_cast< ContractInfo* >( iterContractInfoList.getObject() );
                  listObjActivity = iterContractInfoList.getKey().getActivity();
                  BFData dataRepeat( ifds::DSTC0161_REQRepeat_Record );
                  ++count;
                  request->setElementValue( ifds::RepeatCount, DString::asString( count ), false, false );
                  pContractInfo->getData( dataRepeat, BF::HOST );
                  DSTCWorkSession::setRunMode( &dataRepeat, listObjActivity );     
                  request->addRepeat( dataRepeat );

               }  // end -- iterContractInfoList.hasTransactionUpdates()
               ++iterContractInfoList;
            }  // end -- while (!iterContractInfoList.end())
         }  //if ( bMultiContract )    		 
      }  // end -- if( pContractInfoList != NULL && severity <= WARNING )   
   }  // end -- if( pMFAccount != NULL )

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/DSTCContractTrxnBuilder.cpp-arc  $
// 
//    Rev 1.23   Aug 17 2005 16:27:36   porteanm
// Incident 351033 - Removed single contract support, view 131.
// 
//    Rev 1.22   Nov 14 2004 14:31:52   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.21   Mar 21 2003 18:04:44   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.20   Oct 09 2002 23:54:18   PURDYECH
// PVCS Database Conversion
// 
//    Rev 1.19   Aug 29 2002 12:55:26   SMITHDAV
// ClientLocale and typed field changes.
// 
//    Rev 1.18   22 May 2002 18:27:20   PURDYECH
// BFData Implementation
// 
//    Rev 1.17   Feb 25 2002 18:55:24   PURDYECH
// Phase 1 of BFData Rollout - Base Component Compatibility
// 
//    Rev 1.16   24 Oct 2001 15:46:50   HSUCHIN
// removed assignment of PrevEffectiveDate from Effective date since BF::HOST version of Effective date has been changed (commited already).  Fixed builder logic so that non multiple contracts will be build now.
// 
//    Rev 1.15   Oct 19 2001 11:41:08   ZHANGCEL
// Rewrite the ContractTrxnBuilder
// 
//    Rev 1.14   Aug 10 2001 11:38:24   OLTEANCR
// set value for PrevEffectiveDate
// 
//    Rev 1.13   Jul 16 2001 19:14:32   OLTEANCR
// added logic for multicontract
// 
//    Rev 1.12   23 May 2001 14:39:54   SMITHDAV
// Fill CompanyId to all request Data objects that are posted to the HTC.
// 
//    Rev 1.11   03 May 2001 14:06:14   SMITHDAV
// Session management restructuring.
// 
//    Rev 1.10   Feb 02 2001 18:31:46   MCNABBGL
// scrubbed code
// 
//    Rev 1.9   Jan 31 2001 16:10:54   YINGBAOL
// set track and activity values for update transactions
// 
//    Rev 1.8   Jan 16 2001 14:02:28   OLTEANCR
// modified buildTransaction(..)
// 
//    Rev 1.7   Jan 16 2001 13:53:30   OLTEANCR
// 
//    Rev 1.6   Dec 17 2000 20:23:02   OLTEANCR
// changed to use a precompiled header
// 
//    Rev 1.5   Oct 17 2000 14:42:48   KOVACSRO
// updated pMFAccount->getContractInfoList().
// 
//    Rev 1.4   Aug 08 2000 16:12:50   ZHANGCEL
// Bug fixed
// 
//    Rev 1.3   Aug 02 2000 11:33:40   WINNIE
// new parameter for MFAccount.getContractInfoList to avoid creation of the object in transaction builder
// 
//    Rev 1.2   May 18 2000 15:45:08   ZHANGCEL
// Date culculate stuffs
 * 
 */
