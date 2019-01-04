#pragma once

//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by International Financial Data Services,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2004 by International Financial Data Services.
//
//
//******************************************************************************
//
// ^FILE   : GIInvestmentDetailsList.hpp
// ^AUTHOR : 
// ^DATE   : 
//
// ^CLASS    : GIInvestmentDetailsList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include <ifastcbo\mfcancbo.hpp>
#include <boost\utility.hpp>

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class InvestmentHistory;

class IFASTCBO_LINKAGE GIInvestmentDetailsList : public MFCanBFCbo, private boost::noncopyable
{
public:
   GIInvestmentDetailsList( BFAbstractCBO &parent );
   virtual ~GIInvestmentDetailsList();

	SEVERITY init (const DString& dstrAccountNum, 
					   const DString& dstrTransId, 
					   const DString& dstrFund,
					   const DString& dstrClass,
					   const DString& dstrInvNum,
					   const DString& dstrInvStatus,
					   const DString& dstrSearchBy,
                  const DString& dstrTradeDate,
                  const DString& dstrAmountType,
                  bool  isNew,
					   const BFDataGroupId& idDataGroup,
                  const DString& dstrSuppressMVA,
                  const DString& dstrSuppressAdmin,
                  const DString& dstrTradeAmt,
                  const DString& dstrGrossNet);

   SEVERITY init (const BFDataGroupId& idDataGroup);
   SEVERITY initCalc(
                     const DString dstrAccountNum, 
                     const DString& dstrTransId,       
                     const DString& dstrFundFrom,      
                     const DString& dstrClassFrom,     
                     const DString& dstrEffDate,     
                     const DString& dstrGrossNet,    
                     const DString& dstrRedemOrder,  
                     const DString& dstrSelInvAmtType, 
                     const DString& dstrSelInvAmount,  
                     const DString& dstrSuppressMVA, 
                     const DString& dstrSuppressAdmin,
                     const DString& dstrInvHisInvestId,
                     const DString& dstrInvSummId,
                     const DString& dstrTradeAmount);
	SEVERITY getMore();

	bool isAnyStatusBlank (const BFDataGroupId &idDataGroup);

	SEVERITY setDummyFlag (const BFDataGroupId &idDataGroup);
   SEVERITY calculateTotals(GIInvestmentDetailsList& totalsList, const BFDataGroupId &idDataGroup);
   SEVERITY recalculateAll(const BFDataGroupId& idDataGroup);
   void changeAmtType( const DString& dstrAmtType, const BFDataGroupId &idDataGroup);
   void setIsTotalsCBO(bool isTotalsCBO) {m_isTotalsCBO = isTotalsCBO;};   
protected:
	virtual SEVERITY doCreateObject( const BFData& data, BFCBO*& pObjOut );
    SEVERITY doValidateAll( const BFDataGroupId& idDataGroup, long lValidateGroup );
	virtual SEVERITY doApplyRelatedChanges ( const BFFieldId &idField, 
											 const BFDataGroupId &idDataGroup);
	SEVERITY doValidateField ( const BFFieldId &idField, 
							   const DString &strValue, 
							   const BFDataGroupId &idDataGroup);

private:
	BFData  m_requestData;
   bool m_isTotalsCBO;
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/GIInvestmentDetailsList.hpp-arc  $
//
//   Rev 1.9   May 01 2012 09:23:56   if991250
//GI Money Out - clearing the calculated amounts when the Investment row is unselected.
//
//   Rev 1.8   Apr 26 2012 11:06:50   if991250
//Sending GrossNet and TradeAmount to vw 421 in inquiry modes
//
//   Rev 1.7   Apr 25 2012 18:16:30   if991250
//Money Out - sending SuppressMVA and Suppress Admin fee for investment inquiry and pending trade
//
//   Rev 1.6   Mar 20 2012 16:42:52   if991250
//IN 2885623 - GI Money Oout
//
//   Rev 1.5   Mar 09 2012 17:46:22   if991250
//GIInvestmentDetails
//
//   Rev 1.4   Mar 08 2012 17:47:14   if991250
//GI Money Out
//
//   Rev 1.3   Mar 08 2012 15:14:02   if991250
//Account Commitment
//
//   Rev 1.2   Mar 08 2012 09:58:10   if991250
//GI Money Out
//
//   Rev 1.1   Jan 26 2012 14:48:50   if991250
//Added GIInvestmentDetails (cpp and hpp)
//
//   Rev 1.0   Jan 16 2012 15:27:52   if991250
//Initial revision.
// 
*/
