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
//    Copyright 1997 by DST Systems, Inc.
//
//
//******************************************************************************
//
// ^FILE   : DuplicateTradeCheck.hpp
// ^AUTHOR : Robert Kovacs
// ^DATE   : July, 2001
//
// ^CLASS    : DuplicateTradeCheck
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include <ifastcbo\mfcancbo.hpp>
#include <boost\utility.hpp>
#include <srcprag.h>

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class IFASTCBO_LINKAGE DuplicateTradeCheck : public MFCanBFCbo, private boost::noncopyable
{
public:

   DuplicateTradeCheck( BFAbstractCBO &parent );
   virtual ~DuplicateTradeCheck();
   SEVERITY init( const DString&  strAccountNum, 
                  const DString&  strFundCode, const DString&  strClassCode, const DString&  strTransType,
                  const DString&  AmountType, const DString&  Amount, 
                  const DString&  strEffectiveDate,
				  const DString&  strIndc, const DString& strSettleCurrency,
				  const DString& strSettleDate, const DString& strToFundCode, 
				  const DString& strToClassCode, const DString& strToAccount,
				  const DString&  strRecId = NULL_STRING);

   bool isChanged(const DString&  strAccountNum, const DString&  strFundCode, 
                  const DString&  strClassCode, const DString&  strTransType,
                  const DString&  AmountType , const DString&  Amount, 
                  const DString&  strEffectiveDate, const DString&  strRecId = NULL_STRING );

   bool isDuplicate();

   SEVERITY refresh(const DString&  strAccountNum, 
                    const DString&  strFundCode, const DString&  strClassCode, const DString&  strTransType,
                    const DString&  AmountType, const DString&  Amount, 
					const DString&  strEffectiveDate, 
					const DString&  strIndc, const DString& strSettleCurrency,
					const DString& strSettleDate, const DString& strToFundCode, 
					const DString& strToClassCode, const DString& strToAccount,
					const DString&  strRecId = NULL_STRING);
private:

   DString m_AccountNum;
   DString m_FundCode;
   DString m_ClassCode;
   DString m_TransType;
   DString m_Amount;
   DString m_AmountType;
   DString m_EffectiveDate;
   DString m_RecId;
   DString m_Indc;
   DString m_SettleCurrency;
   DString m_SettleDate;
   DString m_ToFundCode;
   DString m_ToClassCode;
   DString m_ToAccount;
};
///#endif
