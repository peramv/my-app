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
//    Copyright 2010, By International Financial Data Service
//
//
//******************************************************************************
//
// ^FILE   : GIInvestmentDetails.hpp
// ^AUTHOR : 
// ^DATE   : 
//
// ^CLASS    : GIInvestmentDetails
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include <ifastcbo\mfcancbo.hpp>

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class GIInvestmentDetailsDetailsList;
class GIInvestmentDetailsInterestList;

class IFASTCBO_LINKAGE GIInvestmentDetails : public MFCanBFCbo
{
public:
   GIInvestmentDetails( BFAbstractCBO &parent );
   virtual ~GIInvestmentDetails();
   SEVERITY init(const BFData& data);
   virtual SEVERITY doApplyRelatedChanges (const BFFieldId &idField, const BFDataGroupId &idDataGroup);
   SEVERITY calculate(const DString& dstrAccountNum, 
                      const DString& dstrEffDate, 
                      const DString& dstrGrossNet, 
                      const DString& dstrRedemOrder, 
                      const DString& dstrSuppressMVA, 
                      const DString& dstrSuppressAdmin,
                      const DString& dstrTradeAmount,
                      const BFDataGroupId &idDataGroup);
   virtual SEVERITY doValidateField( const BFFieldId &fieldId,
                                     const DString& strValue,
                                     const BFDataGroupId& idDataGroup );

   SEVERITY GIInvestmentDetails::calculateFees(const BFDataGroupId &idDataGroup);

protected:

private:
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/GIInvestmentDetails.hpp-arc  $
//
//   Rev 1.6   Apr 25 2012 18:14:52   if991250
//Money Out - sending SuppressMVA and Suppress Admin fee for investment inquiry and pending trade
//
//   Rev 1.5   Mar 20 2012 16:41:36   if991250
//IN 2885623 - GI Money Oout
//
//   Rev 1.4   Mar 12 2012 18:11:04   if991250
//GI Money Out
//
//   Rev 1.3   Mar 09 2012 17:45:40   if991250
//GIInvestmentDetails
//
//   Rev 1.2   Mar 08 2012 17:46:44   if991250
//GI Money Out
//
//   Rev 1.1   Mar 08 2012 09:57:50   if991250
//GI Money Out
//
//   Rev 1.0   Jan 26 2012 14:46:36   if991250
//Initial revision.
 * 
*/
