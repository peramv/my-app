// AllocationsDlg.h : header file
//

#ifndef ALLOCATIONSHELPER_H
#define ALLOCATIONSHELPER_H
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
//******************************************************************************
//
// ^FILE   : AllocationsHelper.h
// ^AUTHOR : Yakov Prager
// ^DATE   : 09/26/99
//
// ^CLASSES  : Helper classes for Allocations and Transaction Allocations dlgs
// ^SUBCLASS : 
//
// ^CLASS DESCRIPTION : 
//
// -----------------------------------------------------------------------------
//
//******************************************************************************

struct AcctTax
{
   AcctTax( const DString &dstrAccountNum, const DString &dstrTaxType) 
   :  m_dstrAccountNum( dstrAccountNum ), m_dstrTaxType( dstrTaxType ) {}
   DString m_dstrAccountNum;
   DString m_dstrTaxType;
};


struct LessAcctTax
{
   bool operator() ( const AcctTax &first, const AcctTax &second ) const
   {
      if( first.m_dstrAccountNum < second.m_dstrAccountNum )
         return(true);
      else if( first.m_dstrAccountNum > second.m_dstrAccountNum )
         return(false);
      else
         return(first.m_dstrTaxType < second.m_dstrTaxType);
   }
};


struct Allocation
{
   int m_iListNum;
   const DString *m_pDstrKey;
   DString m_dstrType;
   DString m_dstrEffectiveDate;
   DString m_dstrAccountNum;
   DString m_dstrFund;
   DString m_dstrClass;
   DString m_dstrPercent;
   DString m_dstrAmount;
   DString m_dstrPACSWPId;
};


struct AllocationGroup
{
   int m_iListNum;
   const DString *m_pDstrKey;
   DString m_dstrType;
   DString m_dstrEffectiveDate;
   DString m_dstrUsage;
   DString m_dstrAccountNum;
   DString m_dstrTaxType;
   DString m_dstrPercent;
   DString m_dstrAmount;
   DString m_dstrCurrency;
   DString m_dstrPACSWPId;
   std::vector< Allocation > m_allocationArray;
};


#endif // ALLOCATIONSHELPER_H