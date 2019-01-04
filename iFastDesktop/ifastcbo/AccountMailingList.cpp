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
//    Copyright 1999 by DST Canada Inc.
//
//
//******************************************************************************
//
// ^FILE   : AccountAddressInfo.cpp
// ^AUTHOR : Yingbao Li
// ^DATE   : Oct. 15, 99
//
// ^CLASS    : AccountAddressInfo 
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "accountmailinglist.hpp"
#include "accountmailinginfo.hpp"
#include "addresslist.hpp"
#include <ifastdataimpl\dse_dstc0113_req.hpp>
#include <ifastdataimpl\dse_dstc0113_vw.hpp>
#include <ifastdataimpl\dse_dstc0083_vw.hpp>
#include <ifastdataimpl\dse_dstc0043_vw.hpp>
#include "mgmtco.hpp"
#include "mgmtcooptions.hpp"
#include "shareholder.hpp"

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest ACCOUNT_MAILING;
}

namespace  
{
   const I_CHAR * const CLASSNAME = I_( "AccountMailingList" );  
   const I_CHAR * const IDI_CODE = I_( "CODE" );
   const I_CHAR * ACCOUNT_NUMBER_FIELD = I_( "AccountNum" );
}

namespace CND
{  // Conditions used

   extern const long ERR_ADDRESS_CODE_NOT_SETUP;
   extern const long ERR_ADDRESS_CODE_NOT_EFFECTIVE;
   extern const long WARN_ADDRESS_CODE_NOT_EFFECTIVE;   
   extern CLASS_IMPORT const long ERR_DATA_NOT_FOUND;
}
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

//*********************************************************************************
void AccountMailingList::buildKey( DString &strKey, const DString& AccountNum )
{
   //reset the key
   strKey = NULL_STRING;

   DString tempAccountNum( AccountNum );

   tempAccountNum.strip().stripLeading( '0' );
   //tempAccountNum.strip();
   addIDITagValue( strKey, ACCOUNT_NUMBER_FIELD, tempAccountNum );
}

//*********************************************************************************
AccountMailingList::AccountMailingList( BFAbstractCBO &parent )
: MFCanBFCbo( parent ),
_shrNum(NULL_STRING)
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   setObjectAsList();
}

//*********************************************************************************
AccountMailingList::~AccountMailingList()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//*********************************************************************************
SEVERITY AccountMailingList::initNew(const DString& shrNum, 
   const BFDataGroupId& idDataGroup /*== BF::HOST*/)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

   _shrNum = shrNum;
   return(GETCURRENTHIGHESTSEVERITY());
}

//*********************************************************************************
SEVERITY AccountMailingList::init(const DString& shrNum, 
   const DString& dstrTrack, const DString& dstrPageName)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

   _shrNum = shrNum;

   BFData requestData(ifds::DSTC0113_REQ);

   DString mgmtCoIdOut;
   requestData.setElementValue(ifds::CompanyId, getMgmtCoId(mgmtCoIdOut));
   requestData.setElementValue(ifds::ShrNum, _shrNum);
   requestData.setElementValue(ifds::Track, dstrTrack);
   requestData.setElementValue(ifds::Activity, dstrPageName);
   //call the back-end
   ReceiveData(DSTC_REQUEST::ACCOUNT_MAILING, requestData, ifds::DSTC0113_VW, 
      DSTCRequestor(getSecurity(),true));
   return(GETCURRENTHIGHESTSEVERITY());
}

//****************************************************************************
//key by account number
void AccountMailingList::getStrKey(DString &strKey, const BFData *data)  
{
   TRACE_METHOD( CLASSNAME, I_( "getStrKey" ) );

   if(data != NULL)
   {
      DString accountNum;

      accountNum = data->getElementValue(ifds::AccountNum);
      buildKey( strKey, accountNum );
   }
}

//*********************************************************************************
void AccountMailingList::getStrKeyForNewItem( DString &strKey )
{
   TRACE_METHOD( CLASSNAME, I_( "getStrKeyforNewItem" ) );

   buildKey( strKey, _strAccountNum );
}


//********************************************************************************
SEVERITY AccountMailingList::doCreateObject( const BFData& data, BFCBO *&pObjOut )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateObject" ) );
   pObjOut =  new AccountMailingInfo( *this );
   ((AccountMailingInfo*) pObjOut)->init( data, _shrNum );
   return(GETCURRENTHIGHESTSEVERITY());
}

//*********************************************************************************
SEVERITY AccountMailingList::doCreateNewObject( BFCBO *&pBase, DString &strKey, 
   const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateNewObject" ) );

   AccountMailingInfo* pAccountMailingInfo = new AccountMailingInfo( *this );

   pAccountMailingInfo->init(idDataGroup, _shrNum);
   //set the initial key on the acount mailing info
   pAccountMailingInfo->setInitialStrKey(strKey);
   pBase = pAccountMailingInfo;
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
void AccountMailingList::doCommitDataGroup( const BFDataGroupId& idDataGroup )
{
   BFObjIter bfIter( *this, idDataGroup, false, BFObjIter::ITERTYPE::ALL, false );
   bfIter.begin();
   while( !bfIter.end() )
   {
      if( bfIter.getKey().getDataGroupId() == idDataGroup )
      {
         DString newStrKey;

         bfIter.getObject()->getField( ifds::AccountNum, newStrKey, idDataGroup, false );
         ( dynamic_cast <AccountMailingInfo*> ( bfIter.getObject() ) )->setInitialStrKey( newStrKey );
         const BFObjectKey &oldKey = bfIter.getKey();
         if( oldKey.getStringKey() != newStrKey )
         {
            setObject( bfIter.getObject(), newStrKey, oldKey.getActivity(), idDataGroup, oldKey.getType() );
         }
      }
      ++bfIter;
   }
}

//*********************************************************************************
SEVERITY AccountMailingList::doValidateAll( const BFDataGroupId& idDataGroup, long lValidateGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doValidateAll" ) );

   Shareholder* pShareholder;
   if( getWorkSession().getShareholder( idDataGroup, _shrNum, pShareholder ) <= WARNING )
   {
      vecAddr.clear();
      AddressList* pAddressList = NULL;

      if( pShareholder->getAddressList( pAddressList, idDataGroup ) <= WARNING )
      {
         BFObjIter iterMailInfoList( *this, idDataGroup );

         while( !iterMailInfoList.end() )
         {
            AccountMailingInfo *pAccountMailingInfo = 
            dynamic_cast<AccountMailingInfo*>( iterMailInfoList.getObject() );

            if( pAccountMailingInfo != NULL && pAccountMailingInfo->isWorking() )
            {
               validateMailingCode( pAccountMailingInfo, ifds::RegAddr, idDataGroup );
               validateMailingCode( pAccountMailingInfo, ifds::DivConfAddr, idDataGroup );
               validateMailingCode( pAccountMailingInfo, ifds::DivChqAddr, idDataGroup );
               validateMailingCode( pAccountMailingInfo, ifds::TxnConfAddr, idDataGroup );
               validateMailingCode( pAccountMailingInfo, ifds::DupConfAddr, idDataGroup );
               validateMailingCode( pAccountMailingInfo, ifds::StmtAddr, idDataGroup );
               validateMailingCode( pAccountMailingInfo, ifds::DupStmtAddr, idDataGroup );
               validateMailingCode( pAccountMailingInfo, ifds::CertAddr, idDataGroup );
               validateMailingCode( pAccountMailingInfo, ifds::TaxAddr, idDataGroup );
               validateMailingCode( pAccountMailingInfo, ifds::LetAddr, idDataGroup );
               validateMailingCode( pAccountMailingInfo, ifds::BenAddr, idDataGroup );
               validateMailingCode( pAccountMailingInfo, ifds::NFCAddr, idDataGroup );
            }
            ++iterMailInfoList;
         }
      }
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//*********************************************************************************
SEVERITY AccountMailingList::validateMailingCode(BFCBO* pBase, const BFFieldId& idField, 
   const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateMailingCode" ) );

   Shareholder* pShareholder;

   if( getWorkSession().getShareholder( idDataGroup, _shrNum, pShareholder ) <= WARNING )
   {
      AddressList* pAddressList = NULL;

      if( pShareholder->getAddressList( pAddressList, idDataGroup ) <= WARNING )
      {
         DString strCode;
         pBase->getField( idField, strCode, idDataGroup, false );
         strCode.strip();
         if( strCode != NULL_STRING )
         {
            std::vector<DString>::iterator it = vecAddr.begin();

            while( it != vecAddr.end() )
            {
               if( *it == strCode )
               {
                  return(GETCURRENTHIGHESTSEVERITY());
               }
               it++;
            } 
            vecAddr.push_back( strCode );

            DString strTemp;
            bool bValid = false;

            if( pAddressList->IsValidateAddressCode( strCode, idDataGroup, bValid ) )
            {
               if( !bValid )
               {
                  addIDITagValue( strTemp, IDI_CODE, strCode.asInteger() );
                  ADDCONDITIONFROMFILEIDI( CND::WARN_ADDRESS_CODE_NOT_EFFECTIVE, strTemp );
               }
            }
            else
            {
               addIDITagValue( strTemp, IDI_CODE, strCode.asInteger() );
               ADDCONDITIONFROMFILEIDI( CND::ERR_ADDRESS_CODE_NOT_SETUP, strTemp);
            }
         }
      }
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//*********************************************************************************
void AccountMailingList::setNewAccountNumber( const DString& strAccount )
{
   TRACE_METHOD( CLASSNAME, I_( "setNewAccountNumber" ) );

   _strAccountNum = strAccount;
}

//*********************************************************************************
bool AccountMailingList::IsAddrCodeUsedByMailing(DString& strAddrCode, const BFDataGroupId& idDataGroup)
{
   bool bRet = false;

   BFObjIter iterMailinglist( *this, idDataGroup );
   DString  addrCode,addrCodekana,addrCodeKana;
   while( !iterMailinglist.end() ) // check if at least one fund has non zero balance
   {
      // in either settled units or unsettled units wstring
      AccountMailingInfo* _pInfo = dynamic_cast<AccountMailingInfo* >(iterMailinglist.getObject() );
      iterMailinglist.getObject()->getField(ifds::RegAddr,addrCode,idDataGroup);

      bRet = IsMailingTypeSameAsCode(_pInfo,strAddrCode,ifds::RegAddr,idDataGroup);
      bRet |= IsMailingTypeSameAsCode(_pInfo,strAddrCode,ifds::DivConfAddr,idDataGroup);
      bRet |= IsMailingTypeSameAsCode(_pInfo,strAddrCode,ifds::DivChqAddr,idDataGroup);
      bRet |= IsMailingTypeSameAsCode(_pInfo,strAddrCode,ifds::TxnConfAddr,idDataGroup);
      bRet |= IsMailingTypeSameAsCode(_pInfo,strAddrCode,ifds::DupConfAddr,idDataGroup);
      bRet |= IsMailingTypeSameAsCode(_pInfo,strAddrCode,ifds::StmtAddr,idDataGroup);
      bRet |= IsMailingTypeSameAsCode(_pInfo,strAddrCode,ifds::DupStmtAddr,idDataGroup);

      bRet |= IsMailingTypeSameAsCode(_pInfo,strAddrCode,ifds::TaxAddr,idDataGroup);
      bRet |= IsMailingTypeSameAsCode(_pInfo,strAddrCode,ifds::LetAddr,idDataGroup);
      bRet |= IsMailingTypeSameAsCode(_pInfo,strAddrCode,ifds::BenAddr,idDataGroup);
      bRet |= IsMailingTypeSameAsCode(_pInfo,strAddrCode,ifds::NFCAddr,idDataGroup);

      bRet |= IsMailingTypeSameAsCode(_pInfo,strAddrCode,ifds::CertAddr,idDataGroup);
      if( bRet == true ) break;


      ++iterMailinglist;
   }
   return(bRet);
}

//*********************************************************************************
bool AccountMailingList::IsMailingTypeSameAsCode(AccountMailingInfo* pMailInfo,DString& strCode, const BFFieldId& idMailType, const BFDataGroupId& idDataGroup)
{
   bool bRet = false;
   DString strAddrCode,addrCodekana, addrCodeKana;
   pMailInfo->getField(idMailType,strAddrCode, idDataGroup);  
   strAddrCode.strip();
//	addrCodeKana = I_("K") + strAddrCode;
//	addrCodekana = I_("k") + strAddrCode;
   if( (strCode == strAddrCode) || (strCode == addrCodeKana) || (strCode == addrCodekana ) )
   {
      bRet = true;

   }
   return(bRet);
}


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/AccountMailingList.cpp-arc  $
 * 
 *    Rev 1.15   Apr 26 2006 12:22:44   porteanm
 * Incident 605455 - Replaced error with warning  WARN_ADDRESS_CODE_NOT_EFFECTIVE.
 * 
 *    Rev 1.14   May 22 2003 14:11:46   popescu
 * Replaced name 'BankInstr' with 'BankInstructions'; 
 * simplified child lists getters for the Shareholder object
 * 
 *    Rev 1.13   Mar 21 2003 17:54:58   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.12   Oct 09 2002 23:53:54   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.11   Sep 25 2002 11:04:14   KOVACSRO
 * Bug fixed. Since we use the mailing info on the distribution screen, we need to wait for the response before popping up the screen - async receiving data is not a valid option.
 * 
 *    Rev 1.10   Aug 29 2002 12:54:54   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.9   22 May 2002 18:26:14   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.8   03 May 2001 14:05:54   SMITHDAV
 * Session management restructuring.
 * 
 *    Rev 1.7   Feb 14 2001 11:10:02   HSUCHIN
 *  async receive
 * 
 *    Rev 1.6   Jan 18 2001 16:03:26   YINGBAOL
 * add eTracker
 * 
 *    Rev 1.5   Dec 18 2000 14:24:00   HSUCHIN
 * minor optimization
 * 
 *    Rev 1.4   Dec 17 2000 20:22:22   OLTEANCR
 * changed to use a precompiled header
 * 
 *    Rev 1.3   15 Nov 2000 15:30:12   SMITHDAV
 * Use new ReceiveData and do some cleanup.
 * 
 *    Rev 1.2   Nov 02 2000 13:22:30   YINGBAOL
 * use new databroker
 * 
 *    Rev 1.1   Oct 30 2000 14:05:06   YINGBAOL
 * change sync.
 * 
 *    Rev 1.0   Feb 15 2000 10:59:48   SMITHDAV
 * Initial revision.
// 
//    Rev 1.21   Feb 01 2000 14:36:22   BUZILA
// added lValidateGroup parameter to doValidateAll method
// 
//    Rev 1.20   Jan 25 2000 18:04:20   YINGBAOL
// fix
// 
//    Rev 1.19   Jan 23 2000 16:59:34   POPESCUS
// fixes related to accessing the lists and rolling back a cloned account
// 
//    Rev 1.18   Jan 21 2000 16:44:30   YINGBAOL
// change the way access other list
// 
//    Rev 1.17   Jan 21 2000 11:11:44   POPESCUS
// the user can change the account number and the shareholder number
// 
//    Rev 1.16   Jan 20 2000 10:43:22   POPESCUS
// fixes for cloning an address mailing
// 
//    Rev 1.15   Jan 19 2000 10:46:54   POPESCUS
// probably, some fixes
// 
//    Rev 1.14   Jan 18 2000 18:18:08   POPESCUS
// check in for point release
// 
//    Rev 1.13   Jan 14 2000 15:29:08   YINGBAOL
// fix
// 
//    Rev 1.12   Jan 14 2000 15:07:50   YINGBAOL
// modify validation and setdefault values
// 
//    Rev 1.11   Jan 10 2000 13:59:18   POPESCUS
// fixes for NASU
// 
//    Rev 1.10   Jan 07 2000 17:12:20   YINGBAOL
// modify validation
// 
//    Rev 1.9   Jan 06 2000 13:37:06   YINGBAOL
// change
// 
//    Rev 1.8   Dec 30 1999 10:37:00   YINGBAOL
// more validation added
// 
//    Rev 1.7   Dec 21 1999 10:13:52   YINGBAOL
// add validation
// 
//    Rev 1.6   Dec 17 1999 18:01:02   YINGBAOL
// 
//    Rev 1.5   Dec 12 1999 16:25:06   POPESCUS
// Xchgdata issue; create and delete the object in the CBO
// 
//    Rev 1.4   Dec 09 1999 10:43:34   POPESCUS
// Fixed some memory leaks
// 
//    Rev 1.3   Dec 08 1999 11:48:58   POPESCUS
// modifications related to the ownership of the data object
// 
//    Rev 1.2   Dec 08 1999 09:48:22   YINGBAOL
// fix Nasu bug
*/


