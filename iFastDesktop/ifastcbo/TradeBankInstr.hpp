#pragma once
//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by DST Canada, Inc.,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2002 by DST Canada Inc.
//
//
//******************************************************************************
//
// ^FILE   : TradeBankInstr.hpp
// ^AUTHOR : Robert Kovacs
// ^DATE   : 2/9/01
//
// ^CLASS    : TradeBankInstr
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include <ifastcbo\bankinstructions.hpp>
#include <boost\utility.hpp>

class Trade;

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class IFASTCBO_LINKAGE TradeBankInstr : public BankInstructions
{
public:
   TradeBankInstr( BFAbstractCBO &parent );
   ~TradeBankInstr();


   void initPendingTradeBank( const BFData& data, const Trade* pTrade, const DString& dstrAcctUseCode, 
                              const DString& dstSettleCurrency,const BFDataGroupId& idDataGroup );
   void initNewTradeBank(  const BFData& data, const bool noModelBank, DString& dstAcctNum, 
                           const Trade* pTrade,  const DString& dstrAcctUseCode, const BFDataGroupId& idDataGroup);
   void initLastEFT( const BFData& data, bool bBaseDelete = false );
   //void setFieldsSubsValuesForTrade( const BFDataGroupId& idDataGroup );

protected:
   void doInitWithDefaultValues( const BFDataGroupId& idDataGroup );
   SEVERITY doApplyRelatedChanges( const BFFieldId& idField, const BFDataGroupId& idDataGroup );
   SEVERITY doValidateField( const BFFieldId& idField, const DString& strValue, const BFDataGroupId& idDataGroup );
   bool doIsInternationalWire( const DString& strSettleCurr,  const DString& strCountry, const BFDataGroupId& idDataGroup);
   void setACHProcessorRequired( const BFDataGroupId& idDataGroup );

private:

   SEVERITY setFieldsFromTrade(const BFDataGroupId& idDataGroup);
   void commonInit(const DString& dstrAcctUseCode, const DString& dstSettleCurrency, const BFDataGroupId& idDataGroup );
   void initFieldsFromData( const BFDataGroupId& idDataGroup );
   const Trade* m_pTrade;
   BFData* m_pInitData;
   DString m_dstrAcctUseCode;
   DString m_dstSettleCurrency;
   DString m_dstrAccountNum;
   bool m_bNoModelBank;
};

///#endif

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/TradeBankInstr.hpp-arc  $
//
//   Rev 1.10   Nov 14 2004 14:57:42   purdyech
//PET910 - .NET Conversion
//
//   Rev 1.9   Mar 19 2004 09:58:42   WINNIE
//test label - no change
//
//   Rev 1.8   May 22 2003 14:13:38   popescu
//Replaced name 'BankInstr' with 'BankInstructions'; 
//simplified child lists getters for the Shareholder object
//
//   Rev 1.7   Mar 21 2003 18:26:58   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.6   Oct 09 2002 23:55:10   PURDYECH
//PVCS Database Conversion
//
//   Rev 1.5   Sep 09 2002 12:13:54   KOVACSRO
//Sync-up for PTS 10009768
//
//   Rev 1.4   Aug 29 2002 12:53:52   SMITHDAV
//ClientLocale and typed field changes.
//
//   Rev 1.3   Jun 21 2002 17:42:58   KOVACSRO
//Added initLastEFT
//
//   Rev 1.2   Jun 16 2002 16:59:34   KOVACSRO
//Added setACHProcessorRequired
//
//   Rev 1.1   Jun 15 2002 16:40:52   KOVACSRO
//keeping init data.
//
//   Rev 1.0   Jun 14 2002 16:46:30   KOVACSRO
//Initial revision.
//

 * 
*/