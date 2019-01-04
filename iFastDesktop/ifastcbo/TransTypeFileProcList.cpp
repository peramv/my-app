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
// ^FILE   : TransTypeFileProcList.cpp
// ^AUTHOR : Zijian Ying
// ^DATE   : 05/31/02
//
// ^CLASS    : TransTypeFileProcList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include "stdafx.h"
#include <bfutil\bfguard.hpp>
#include "transtypefileproclist.hpp"
#include <ifastdataimpl\dse_dstc0207_req.hpp>
#include <ifastdataimpl\dse_dstc0207_vw.hpp>

namespace
{
   //Trace literals
   const I_CHAR * const CLASSNAME = I_("TransTypeFileProcList");
}

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest TRANSTYPE_FILEPROC_LIST;
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId PayMethod;
   extern CLASS_IMPORT const BFTextFieldId TransType;
   extern CLASS_IMPORT const BFTextFieldId FileProcCode;
   extern CLASS_IMPORT const BFTextFieldId Currency;
}

//******************************************************************************
TransTypeFileProcList::TransTypeFileProcList(BFAbstractCBO &parent) 
: MFCanBFCbo(parent),
_usedTransTypes(NULL_STRING),
_transType(NULL_STRING)
{
   TRACE_CONSTRUCTOR(CLASSNAME, NULL_STRING);
   setObjectAsList();
}


//******************************************************************************
TransTypeFileProcList::~TransTypeFileProcList()
{
   TRACE_DESTRUCTOR(CLASSNAME);
}

//******************************************************************************
SEVERITY TransTypeFileProcList::init (const DString &transType)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("init"));

   if(_usedTransTypes.find(I_("[") + transType + I_("]")) == DString::npos)
   {
      BFGuard cs(_csTransTypeFileProcList);
   
      if (_usedTransTypes.find(I_("[") + transType + I_("]")) == DString::npos)
      {
         BFData requestData (ifds::DSTC0207_REQ);
         DString mgmtCoIdOut;

			_transType = transType;
         requestData.setElementValue (ifds::CompanyId, getMgmtCoId(mgmtCoIdOut));
         requestData.setElementValue (ifds::TransType, transType);
         requestData.setElementValue (ifds::Track, I_("N"));
         requestData.setElementValue (ifds::Activity, NULL_STRING);
         if (ReceiveData( DSTC_REQUEST::TRANSTYPE_FILEPROC_LIST, 
                          requestData, 
                          ifds::DSTC0207_VW, 
                          DSTCRequestor(getSecurity(), false)) <= WARNING)
         {
            _usedTransTypes += I_("[") + transType + I_("]");
         }
      }
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
DString TransTypeFileProcList::getFileProcSubList( const DString &transType, 
                                                   const DString &payMethod,
                                                   const DString &currency /*=NULL_STRING*/)
{
   DString fileProcSubList (NULL_STRING),
      transType_ (transType),
      payMethod_ (payMethod),
      currency_ (currency);

   if (!transType_.strip().empty())
   {
      transType_.upperCase();
      if (init (transType_) <= WARNING)
      {
         payMethod_.strip().upperCase();
         currency_.strip().upperCase();

         DString fileProcSubListKey (
               I_("TransType=") + transType_ + I_(";") + 
               I_("PayMethod=") + payMethod_ + I_(";"));
         BFObjIter iter ( *this, 
                          BF::HOST, 
                          true, //match substrings
                          BFObjIter::ITERTYPE::NON_DELETED, 
                          false, 
                          true);  
         std::set< DString > set;

         iter.begin (OBJ_TYPE_NONE, OBJ_ACTIVITY_NONE, fileProcSubListKey);
         while (!iter.end())
         {
            DString fileProcCode, 
               currencyList;
            bool considerFileProcCode = true;

            iter.getObject()->getField (ifds::FileProcCode, fileProcCode, BF::HOST, false);
            fileProcCode.strip();
            if (currency_ != NULL_STRING)
            {
               iter.getObject()->getField (ifds::Currency, currencyList, BF::HOST, false);
               considerFileProcCode = 
                  currencyList.find (currency_) != std::string::npos || 
                  currencyList == I_("*") || currencyList == I_("*,");
            }
            if (considerFileProcCode /*&& 
                  set.insert (fileProcCode).second != NULL*/) //uniqueness test
            {
               //fileProcSubList += fileProcCode + I_("=") + fileProcCode + I_(";");
               set.insert (fileProcCode);
            }
            ++iter;
         }
         std::set< DString >::reverse_iterator rit = set.rbegin();
         while (rit != set.rend())
         {            
            fileProcSubList += *rit + I_("=") + *rit + I_(";");
            rit++;
         }
      }
   }
   return fileProcSubList;
}

//******************************************************************************
DString TransTypeFileProcList::getCurrencySubList ( const DString &transType, 
                                                    const DString &payMethod,
                                                    const DString &fileProc /*=NULL_STRING*/)
{
   DString currencySubList (NULL_STRING),
      transType_ (transType),
      payMethod_ (payMethod),
      fileProc_ (fileProc);

   if (!transType_.strip().empty())
   {
      transType_.upperCase();
      if (init (transType_) <= WARNING)
      {
         payMethod_.strip().upperCase();
         fileProc_.strip().upperCase();

         DString currencySubListKey (
               I_("TransType=") + transType_ + I_(";") + 
               I_("PayMethod=") + payMethod_ + I_(";") + 
               (!fileProc_.empty() ? I_("FileProcCode=") + fileProc_ + I_(";") : I_(";"))),
               hostCurrencyList;
         BFObjIter iter ( *this, 
                          BF::HOST, 
                          true, //match substrings
                          BFObjIter::ITERTYPE::NON_DELETED, 
                          false, 
                          true);  
         std::set <DString> set;
         BFProperties * pProperties = 
            getFieldProperties (ifds::Currency, BF::HOST);

         pProperties->getAllSubstituteValues (hostCurrencyList);
         iter.begin (OBJ_TYPE_NONE, OBJ_ACTIVITY_NONE, currencySubListKey);
         while (!iter.end())
         {
            DString currencyList,
               currencyCode, 
               currencyDescription;

            iter.getObject()->getField (ifds::Currency, currencyList, BF::HOST, false);
            if (currencyList == I_("*") || currencyList == I_("*,"))
            {
               I_CHAR *temp = const_cast<I_CHAR*> (hostCurrencyList.c_str ());

               do
               {
                  temp = parseIdiString (temp, currencyCode, currencyDescription);
                  if (set.insert (currencyCode).second != NULL) //uniqueness test
                  {
                     currencySubList += currencyCode + I_("=") + currencyDescription + I_(";");
                  }
               } while (temp && temp != NULL_STRING && *temp);
            }
            else 
            {
               DString::size_type pos = 0, pos1;

               while ((pos1 = currencyList.find(I_(","), pos)) != DString::npos)
               {
                  currencyCode = currencyList.substr (pos, pos1 - pos);
                  currencyDescription = currencyCode;
                  pProperties->formatValue (ifds::Currency, currencyDescription, true);
                  if (set.insert (currencyCode).second != NULL) //uniqueness test
                  {
                     currencySubList += currencyCode + I_("=") + currencyDescription + I_(";");
                  }
                  pos = pos1 + 1;
               }
            }
            ++iter;
         }
      }
   }
   return currencySubList;
}

//******************************************************************************
DString TransTypeFileProcList::getPayMethodSubList( const DString &transType, 
                                                    const DString &fileProc,
                                                    const DString &currency /*=NULL_STRING*/)
{
   DString payMethodSubList (NULL_STRING),
      transType_ (transType),
      fileProc_ (fileProc),
      currency_ (currency);

   if (!transType_.strip().empty())
   {
      transType_.upperCase();
      if (init (transType_) <= WARNING)
      {
         fileProc_.strip().upperCase();
         currency_.strip().upperCase();

         DString transTypeSubListKey (I_("TransType=") + transType_+I_(";"));
         BFObjIter iter ( *this, 
                          BF::HOST, 
                          true, //match substrings
                          BFObjIter::ITERTYPE::NON_DELETED, 
                          false, 
                          true);  
         std::set< DString > set;

         iter.begin (OBJ_TYPE_NONE, OBJ_ACTIVITY_NONE, transTypeSubListKey);
         while (!iter.end())
         {
            DString payMethod, 
               currencyList,
               fileProcCode;

            iter.getObject()->getField (ifds::PayMethod, payMethod, BF::HOST, false);
            iter.getObject()->getField (ifds::FileProcCode, fileProcCode, BF::HOST, false);
            payMethod.strip();
            fileProcCode.strip();
            bool considerpayMethod = fileProcCode == fileProc_;
            if (considerpayMethod && !currency_.empty())
            {
               iter.getObject()->getField (ifds::Currency, currencyList, BF::HOST, false);
               considerpayMethod = 
                  currencyList.find (currency_) != std::string::npos || 
                  currencyList == I_("*") || currencyList == I_("*,");
            }
            if (considerpayMethod) //uniqueness test
            {
               set.insert (payMethod);
            }
            ++iter;
         }

         BFProperties * pProperties = 
            getFieldProperties (ifds::PayMethod, BF::HOST);
         DString payMehtodSubstListHost;
         pProperties->getAllSubstituteValues (payMehtodSubstListHost);
         
         std::set< DString >::reverse_iterator rit = set.rbegin();
         while (rit != set.rend())
         {            
            DString payMethodDescription (*rit);
            pProperties->formatValue (ifds::PayMethod, payMethodDescription, true);
            payMethodSubList += *rit + I_("=") + payMethodDescription + I_(";");
            rit++;
         }
      }
   }
   return payMethodSubList;
}

//******************************************************************************
DString TransTypeFileProcList::getPayMethodSubList2( const DString &transType, 
                                                    const DString &currency /*=NULL_STRING*/)
{
   DString payMethodSubList (NULL_STRING),
      transType_ (transType),
      currency_ (currency);

   if (!transType_.strip().empty())
   {
      transType_.upperCase();
      if (init (transType_) <= WARNING)
      {
         currency_.strip().upperCase();

         DString transTypeSubListKey (I_("TransType=") + transType_+I_(";"));
         BFObjIter iter ( *this, 
                          BF::HOST, 
                          true, //match substrings
                          BFObjIter::ITERTYPE::NON_DELETED, 
                          false, 
                          true);  
         std::set< DString > set;

         iter.begin (OBJ_TYPE_NONE, OBJ_ACTIVITY_NONE, transTypeSubListKey);
         while (!iter.end())
         {
            DString payMethod, 
               currencyList,
               fileProcCode;

            iter.getObject()->getField (ifds::PayMethod, payMethod, BF::HOST, false);
            payMethod.strip();
            
            bool considerpayMethod = set.find(payMethod) == set.end();
            if (considerpayMethod && !currency_.empty())
            {
               iter.getObject()->getField (ifds::Currency, currencyList, BF::HOST, false);
               considerpayMethod = 
                  currencyList.find (currency_) != std::string::npos || 
                  currencyList == I_("*") || currencyList == I_("*,");
            }
            if (considerpayMethod) //uniqueness test
            {
               set.insert (payMethod);
            }
            ++iter;
         }

         BFProperties * pProperties = 
            getFieldProperties (ifds::PayMethod, BF::HOST);
         DString payMehtodSubstListHost;
         pProperties->getAllSubstituteValues (payMehtodSubstListHost);
         
         std::set< DString >::reverse_iterator rit = set.rbegin();
         while (rit != set.rend())
         {            
            DString payMethodDescription (*rit);
            pProperties->formatValue (ifds::PayMethod, payMethodDescription, true);
            payMethodSubList += *rit + I_("=") + payMethodDescription + I_(";");
            rit++;
         }
      }
   }
   return payMethodSubList;
}

//******************************************************************************
void TransTypeFileProcList::buildKey ( const DString &transType, 
                                       const DString &payMethod, 
                                       const DString &fileProcCode,
                                       DString &strKey)
{
   DString transType_(transType),
      payMethod_(payMethod),
      fileProcCode_(fileProcCode);

   transType_.strip().upperCase();
   payMethod_.strip().upperCase();
   fileProcCode_.strip().upperCase();
   strKey = 
      I_(";TransType=") + transType_ + 
      I_(";PayMethod=") + payMethod_ + 
      I_(";FileProcCode=") + fileProcCode_ +
	  I_(";");
}

//******************************************************************************
void TransTypeFileProcList::getStrKey  ( DString &strKey, 
                                         const BFData *data)
{
   TRACE_METHOD (CLASSNAME, I_("getStrKey"));

   if (data)
   {
      DString genKey;

      BFCBO::getStrKey (genKey, NULL);
      buildKey (
		//if we use the trans type that comes from back-end for SSB the file processor
		//breaks, because for redemption they use the trans type 'RED' instead of 'PW'
            /*data->getElementValue (ifds::TradeType)*/ 
            _transType,
            data->getElementValue (ifds::PayMethod),
            data->getElementValue (ifds::FileProcCode),
            strKey);
      strKey = I_("Key=") + genKey + strKey;
   }
   else
   {
      BFCBO::getStrKey (strKey , NULL);
   }
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/TransTypeFileProcList.cpp-arc  $
// 
//    Rev 1.19   Apr 08 2011 04:17:44   kitticha
// PETP0179308_FN01_IN2487930_Desktop not support EFT Purchase Check paytype.
// 
//    Rev 1.18   Nov 06 2005 09:22:30   popescu
// Incident# 447373 - fixed file processor load for PAC/SWP
// 
//    Rev 1.17   Nov 14 2004 14:59:02   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.16   Oct 08 2004 19:47:18   HERNANDO
// PTS10034579 - Added original comparison.
// 
//    Rev 1.15   Oct 08 2004 14:32:26   HERNANDO
// PTS10034579 - Added a comma for a comparison.
// 
//    Rev 1.14   Sep 13 2004 14:37:12   popescu
// PET 1094 FN4 - Activest Bank File Interface, returned the file processor list in descending order
// 
//    Rev 1.13   Sep 13 2004 13:52:50   popescu
// PET 1094 FN4 - Activest Bank File Interface, changed the implementation to handle duplicates values
// 
//    Rev 1.12   Jan 27 2004 20:08:24   popescu
// PTS 10026408, removed not needed method, added at the previous iteration
// 
//    Rev 1.11   Jan 27 2004 20:04:10   popescu
// PTS 10026408, CITIBNK is not listed in Drop-down list for File Processor in setting up bank information, by Account - Income Distribution
// 
//    Rev 1.10   Sep 16 2003 11:10:44   ZHANGCEL
// Fix bug that related with 10021033, Using "RED" as the Transtype for Redemption rather than "PW" to make view 207 call.
// 
//    Rev 1.9   Aug 22 2003 12:05:02   popescu
// PTS 10021033, the cached list was not cleared before adding another value of file proc currencies. Added an object to the list and moved the processing of the back-end data in doCreateObject
// 
//    Rev 1.8   Jan 29 2003 11:47:12   KOVACSRO
// Fixed getFileProcSubList and getCurrencySubList for the case when TransType is empty.
// 
//    Rev 1.7   Oct 09 2002 23:55:14   PURDYECH
// PVCS Database Conversion
// 
//    Rev 1.6   Aug 29 2002 12:57:00   SMITHDAV
// ClientLocale and typed field changes.
// 
//    Rev 1.5   Jun 10 2002 10:12:46   YINGZ
// add getFileProcSubList
// 
//    Rev 1.4   Jun 04 2002 11:27:12   YINGZ
// done
// 
//    Rev 1.3   Jun 03 2002 10:11:24   YINGZ
// check in for check out
// 
//    Rev 1.2   May 31 2002 17:13:16   YINGZ
// for Robert
// 
//    Rev 1.1   May 31 2002 17:06:14   YINGZ
// for Robert
 * 
 *
*/