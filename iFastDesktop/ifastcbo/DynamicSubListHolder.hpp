#define DISABLE_MACRO_REDEFINITION_WARNINGS 1

#pragma once

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
//    Copyright 1999 by DST Canada, Inc.
//
//
//******************************************************************************
//
// ^FILE   : DynamicSubListHolder.hpp
// ^AUTHOR : Zijian Ying
// ^DATE   : 05/31/02
//
// ^CLASS    : DynamicSubListHolder
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include <ifastcbo\mfcancbo.hpp>

#ifndef _MAP_
   #include <map>
#endif 

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif


class TransTypeFileProcList;
class BankAcctUseList;
class FundGroupSubList;
class BFAbstractCBO;

class IFASTCBO_LINKAGE DynamicSubListHolder : public MFCanBFCbo
{
public:
   DynamicSubListHolder( BFAbstractCBO &parent );
   virtual ~DynamicSubListHolder();

   DString getFileProcSubList (
      const DString &TransType, 
      const DString &PayMethod);
   DString getFileProcSubList (
      const DString &TransType, 
      const DString &PayMethod, 
      const DString &Currency);
   DString getCurrencySubList (
      const DString &TransType, 
      const DString &PayMethod);
   DString getCurrencySubList (
      const DString &TransType, 
      const DString &PayMethod, 
      const DString &FileProc);
   DString getBankAcctUseSubList (
      const DString &strBankType);
   DString getFundGroupSubList (
      const DString &strFundType);
   DString getPayMethodSubList( const DString &TransType, 
                                const DString &FileProc);
   DString getPayMethodSubList( const DString &TransType, 
                                const DString &FileProc,
                                const DString &Currency);

private:
   TransTypeFileProcList *m_pTransTypeFileProcList;
   BankAcctUseList *m_pBankAcctUseList;
   FundGroupSubList *m_pFundGroupList;
};

