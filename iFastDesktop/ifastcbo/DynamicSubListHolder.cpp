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
// ^FILE   : DynamicSubListHolder.cpp
// ^AUTHOR : Zijian Ying
// ^DATE   : 05/31/02
//
// ^CLASS    : DynamicSubListHolder
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include "stdafx.h"
#include "DynamicSubListHolder.hpp"
#include "TransTypeFileProcList.hpp"
#include "BankAcctUseList.hpp"
#include "FundGroupSubList.hpp"


namespace
{
   //Trace literals
   const I_CHAR * const CLASSNAME = I_("DynamicSubListHolder");
}

//******************************************************************************
DynamicSubListHolder::DynamicSubListHolder (BFAbstractCBO &parent) 
: MFCanBFCbo (parent)
, m_pBankAcctUseList (NULL)
, m_pTransTypeFileProcList (NULL)
, m_pFundGroupList (NULL)
{
   TRACE_CONSTRUCTOR (CLASSNAME, NULL_STRING);
   
   m_pTransTypeFileProcList = new TransTypeFileProcList (*this);
   if  (!m_pTransTypeFileProcList)
   {
      setObject (m_pTransTypeFileProcList, 
         I_("TransTypeFileProcList"));
   }
   setVersionable( false );

}

//******************************************************************************
DynamicSubListHolder::~DynamicSubListHolder (void)
{
   TRACE_DESTRUCTOR (CLASSNAME);
}

//******************************************************************************
DString DynamicSubListHolder::getFileProcSubList (
   const DString &TransType, 
   const DString &PayMethod)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("getFileProcSubList"));

   return m_pTransTypeFileProcList->getFileProcSubList (TransType, PayMethod);
}

//******************************************************************************
DString DynamicSubListHolder::getFileProcSubList (
   const DString &TransType, 
   const DString &PayMethod, 
   const DString &Currency)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("getFileProcSubList"));

   return m_pTransTypeFileProcList->getFileProcSubList (TransType, PayMethod, Currency);
}

//******************************************************************************
DString DynamicSubListHolder::getCurrencySubList (
   const DString &TransType, 
   const DString &PayMethod)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("getCurrencySubList"));

   return m_pTransTypeFileProcList->getCurrencySubList (TransType, PayMethod);
}

//******************************************************************************
DString DynamicSubListHolder::getCurrencySubList  (
   const DString &TransType, 
   const DString &PayMethod, 
   const DString &FileProc)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("getCurrencySubList"));

   return m_pTransTypeFileProcList->getCurrencySubList (TransType, PayMethod, FileProc);
}

//******************************************************************************
DString DynamicSubListHolder::getPayMethodSubList( const DString &TransType, 
                                                   const DString &FileProc)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("getPayMethodSubList"));

   if(FileProc.empty())
	   return m_pTransTypeFileProcList->getPayMethodSubList2(TransType);
   else
	   return m_pTransTypeFileProcList->getPayMethodSubList (TransType, FileProc);
}


//******************************************************************************
DString DynamicSubListHolder::getPayMethodSubList( const DString &TransType, 
                                                   const DString &FileProc,
                                                   const DString &Currency)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("getPayMethodSubList"));

   if(FileProc.empty())
	   return m_pTransTypeFileProcList->getPayMethodSubList2(TransType, Currency);
   else
	   return m_pTransTypeFileProcList->getPayMethodSubList (TransType, FileProc, Currency);
}

//******************************************************************************
DString DynamicSubListHolder::getBankAcctUseSubList (const DString& strBankType)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("getBankAcctUseSubList"));

   if (!m_pBankAcctUseList)
   {
      m_pBankAcctUseList = new BankAcctUseList (*this);
      setObject (m_pBankAcctUseList, I_("BankAcctUseList"));
   }
   return m_pBankAcctUseList->getAcctUseSubstList (strBankType);
}

//******************************************************************************
DString DynamicSubListHolder::getFundGroupSubList (const DString& strFundType)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("getFundGroupSubList"));

   if (!m_pFundGroupList)
   {
      m_pFundGroupList = new FundGroupSubList (*this);
      setObject (m_pFundGroupList, I_("FundGroupSubList"));
   }
   return m_pFundGroupList->getFundGroupSubList (strFundType);
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/DynamicSubListHolder.cpp-arc  $
// 
//    Rev 1.13   Apr 08 2011 04:09:36   kitticha
// PETP0179308_FN01_IN2487930_Desktop not support EFT Purchase Check paytype.
// 
//    Rev 1.12   Dec 10 2004 14:34:54   hernando
// PET1117 - Recovered version feature.
// 
//    Rev 1.11   Nov 24 2004 10:17:50   yingbaol
// PET1117:temperary take out version features
// 
//    Rev 1.10   Nov 18 2004 13:28:00   YINGBAOL
// PET1117: Perfermance Tunning
// 
//    Rev 1.9   Nov 14 2004 14:36:26   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.8   Aug 10 2004 11:23:44   FENGYONG
// PET 1117 FN 5 - Client condition Fee
// 
//    Rev 1.7   Jan 27 2004 20:04:06   popescu
// PTS 10026408, CITIBNK is not listed in Drop-down list for File Processor in setting up bank information, by Account - Income Distribution
// 
//    Rev 1.6   Jan 12 2003 18:52:14   KOVACSRO
// Added getFundGroupSubList.
// 
//    Rev 1.5   Oct 09 2002 23:54:24   PURDYECH
// PVCS Database Conversion
// 
//    Rev 1.4   Aug 29 2002 12:55:42   SMITHDAV
// ClientLocale and typed field changes.
// 
//    Rev 1.3   Jul 05 2002 11:57:52   KOVACSRO
// Added getBankAcctUseSubList
// 
//    Rev 1.2   Jun 10 2002 10:12:46   YINGZ
// add getFileProcSubList
// 
//    Rev 1.1   May 31 2002 17:06:12   YINGZ
// for Robert
 * 
 *
*/