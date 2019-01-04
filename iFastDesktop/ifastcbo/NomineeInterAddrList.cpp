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
//    Copyright 2000 by DST Canada Inc.
//
//
//******************************************************************************
//
// ^FILE   : NomineeInterAddrList.cpp
// ^AUTHOR : Robert Kovacs
// ^DATE   : 04/08/2000
//
// ^CLASS    : NomineeInterAddrList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "nomineeinteraddrlist.hpp"
#include "nomineeinteraddr.hpp"
#include <ifastdataimpl\dse_dstc0116_vw.hpp>
#include <ifastdataimpl\dse_dstc0116_req.hpp>

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest NOMINEE_INTER_ADDRESS;
}

namespace
{
   // Trace literals
   const I_CHAR * const CLASSNAME = I_("NomineeInterAddrList");
}

namespace CND
{
   extern const long ERR_BROKER_INTERMEDIARY_ADDRESS_NOT_FOUND;
}

//******************************************************************************
NomineeInterAddrList::NomineeInterAddrList (BFAbstractCBO &parent)
: MFCanBFCbo (parent)
{
   TRACE_CONSTRUCTOR (CLASSNAME, NULL_STRING);
   setObjectAsList ();
}

//******************************************************************************
NomineeInterAddrList::~NomineeInterAddrList (void)
{
   TRACE_DESTRUCTOR (CLASSNAME);
}

//******************************************************************************
SEVERITY NomineeInterAddrList::init (
         const DString &brokerInterCode,
         const DString &dstrTrack,
         const DString &dstrPageName)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("init"));

   BFData queryData (ifds::DSTC0116_REQ);

   DString mgmtCoIdOut;
   queryData.setElementValue (ifds::CompanyId, getMgmtCoId (mgmtCoIdOut));
   queryData.setElementValue (ifds::Track, dstrTrack);
   queryData.setElementValue (ifds::Activity, dstrPageName);
   queryData.setElementValue (ifds::BrokerCode, brokerInterCode); 
   ReceiveData (
         DSTC_REQUEST::NOMINEE_INTER_ADDRESS, 
         queryData, 
         ifds::DSTC0116_VW, 
         DSTCRequestor (getSecurity ()));
   return GETCURRENTHIGHESTSEVERITY ();
}

//*****************************************************************************
SEVERITY NomineeInterAddrList::doCreateObject (
         const BFData &data, 
         BFCBO *&pObjOut)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("doCreateObject"));

   pObjOut =  new NomineeInterAddr (*this);
   ((NomineeInterAddr*)pObjOut)->init (data);
   return GETCURRENTHIGHESTSEVERITY ();
}

//*******************************************************************************
bool NomineeInterAddrList::getNomineeAddressByTaxType (
         NomineeInterAddr *&pAddress, 
         const DString &taxType,
         const BFDataGroupId &idDataGroup)
{    
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("getNomineeAddressByTaxType"));

   pAddress = NULL;

   DString searchTaxTypeKey (I_("TaxType=") + taxType);
   BFObjIter iter (
      *this, 
      idDataGroup, 
      true, //match substrings
      BFObjIter::ITERTYPE::NON_DELETED, 
      false, 
      true);
   
   iter.begin (OBJ_TYPE_NONE, OBJ_ACTIVITY_NONE, searchTaxTypeKey);   
   if (!iter.end())
   {
      pAddress = dynamic_cast<NomineeInterAddr *> (iter.getObject ());
   }
   else
   {
//give callers the default address
      getDefault (pAddress, idDataGroup);
   }
	return !!pAddress;
}

//********************************************************************************
bool NomineeInterAddrList::getNomineeAddressByAddrCodeTaxType (
         NomineeInterAddr *&pAddress,
			const DString &regAddrCode,
			const DString &taxType,
         const BFDataGroupId &idDataGroup)

{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("getNomineeAddressByAddrCodeTaxType"));

//give callers the default address
   pAddress = NULL;

   DString searchKey;
   BFObjIter iter (
      *this, 
      idDataGroup, 
      true, //match substrings
      BFObjIter::ITERTYPE::NON_DELETED);

   buildKey (regAddrCode, taxType, searchKey); 
   if (iter.positionByKey (searchKey))
   {
      pAddress = dynamic_cast<NomineeInterAddr *> (iter.getObject ());
   }
   else
   {
//give callers the default address
      getDefault (pAddress, idDataGroup);
   }
	return !!pAddress;
}

//******************************************************************************
void NomineeInterAddrList::buildKey (
         const DString &regAddrCode, 
         const DString &taxType, 
         DString &strKey)
{
   DString regAddrCode_(regAddrCode),
      taxType_(taxType);

   regAddrCode_.strip().upperCase();
   taxType_.strip().upperCase();
   strKey = 
      I_(";AddressCode=") + regAddrCode_ + 
      I_(";TaxType=") + taxType_;
}

//******************************************************************************
void NomineeInterAddrList::getStrKey  (
         DString &strKey, 
         const BFData *data)
{
   TRACE_METHOD (CLASSNAME, I_("getStrKey"));

   if (data)
   {
      DString genKey;

      BFCBO::getStrKey (genKey, NULL);
      buildKey (
            data->getElementValue (ifds::RegAddrCode), 
            data->getElementValue (ifds::TaxType),
            strKey);
      strKey = I_("Key=") + genKey + strKey;
   }
   else
   {
      BFCBO::getStrKey (strKey , NULL);
   }
}

//******************************************************************************
SEVERITY NomineeInterAddrList::getDefault (
      NomineeInterAddr *&pNomineeAddress, 
      const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("getDefault"));
   pNomineeAddress = NULL;
   BFObjIter iter (*this, idDataGroup, true, BFObjIter::ITERTYPE::NON_DELETED);
   
   while (!iter.end())
   {
      DString defaultField;

      iter.getObject ()->getField (ifds::Default, defaultField, idDataGroup, false);
      if (defaultField == I_("Y"))
      {
         pNomineeAddress = dynamic_cast<NomineeInterAddr *> (iter.getObject ());
         break;
      }
      ++iter;
   }
   if (!pNomineeAddress)
   {
//should always have one default address 
      ADDCONDITIONFROMFILE (CND::ERR_BROKER_INTERMEDIARY_ADDRESS_NOT_FOUND);
   }
   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/NomineeInterAddrList.cpp-arc  $
 // 
 //    Rev 1.17   Nov 14 2004 14:50:48   purdyech
 // PET910 - .NET Conversion
 // 
 //    Rev 1.16   May 26 2004 17:25:20   popescu
 // PTS 10026123, when searching for nominee address by reg addrr code and by taxtype the iterator should be set to match substrings
 // 
 //    Rev 1.15   May 20 2004 14:17:06   popescu
 // PTS 10026123, address 01, for nominee and intermediary accounts by tax type and reg address code
 // 
 //    Rev 1.14   Nov 26 2003 16:26:52   YINGBAOL
 // PTS 10021623
 // 
 //    Rev 1.13   Apr 03 2003 16:21:46   YINGBAOL
 // fix TaxType issue
 // 
 //    Rev 1.12   Apr 03 2003 09:24:26   YINGBAOL
 // added getNomineeAddressByAddrCode and getNomineeAddressByTaxType
 // 
 //    Rev 1.11   Mar 21 2003 18:19:54   PURDYECH
 // BFDataGroupId/BFContainerId changeover
 // 
 //    Rev 1.10   Oct 09 2002 23:54:48   PURDYECH
 // PVCS Database Conversion
 // 
 //    Rev 1.9   Aug 29 2002 12:56:22   SMITHDAV
 // ClientLocale and typed field changes.
 // 
 //    Rev 1.8   22 May 2002 18:29:36   PURDYECH
 // BFData Implementation
 // 
 //    Rev 1.7   03 May 2001 14:06:54   SMITHDAV
 // Session management restructuring.
 // 
 //    Rev 1.6   Feb 19 2001 12:30:52   DINACORN
 // Add Revision Control Entries
 * 
 */
