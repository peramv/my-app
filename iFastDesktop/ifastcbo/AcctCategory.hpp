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
//    Copyright 1999 by DST Systems, Inc.
//
//
//******************************************************************************
//
// ^FILE   : AcctCategory.hpp
// ^AUTHOR : Robert Kovacs
// ^DATE   : January 21-2003
//
// ^CLASS    : AcctCategory
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************


#include <ifastcbo\mfcancbo.hpp>
#include <boost\utility.hpp>
///#endif

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class MFAccount;

class IFASTCBO_LINKAGE AcctCategory : public MFCanBFCbo, private boost::noncopyable
{
public:
   AcctCategory( BFAbstractCBO &parent );
   virtual ~AcctCategory();
   SEVERITY init( const BFData& data );
   SEVERITY initNew( const BFDataGroupId& idDataGroup );
   SEVERITY validateUserDelete( const BFDataGroupId& idDataGroup );

protected:
   SEVERITY doValidateField( const BFFieldId& idField, const DString& strValue, const BFDataGroupId& idDataGroup );
   SEVERITY doApplyRelatedChanges( const BFFieldId& idField, const BFDataGroupId& idDataGroup );
   SEVERITY buildPaymentRoutingSet(const BFDataGroupId &idDataGroup, DString &outdstrpymtLevelRoutingSet);//robs ACH
private:

   MFAccount* getParentAccount();
   SEVERITY overwriteAcctCategorySet();

   //validations
   SEVERITY validateAcctCategory(const DString& strValue, const BFDataGroupId& idDataGroup);
   SEVERITY validateModifyAcctCategory(const DString& strValue, const BFDataGroupId& idDataGroup);
   SEVERITY validateMarginAccount(const BFDataGroupId& idDataGroup);
   SEVERITY validateLoanAccount(const BFDataGroupId& idDataGroup);
   SEVERITY validateChqPrivAccount(const BFDataGroupId& idDataGroup);
   SEVERITY validateWRAPAccount(const BFDataGroupId& idDataGroup);
   SEVERITY validatePendingTrades();
   SEVERITY validateClientMonthlyStatement(const BFDataGroupId& idDataGroup);
   SEVERITY setDefaultPayment(const BFDataGroupId& idDataGroup);
   SEVERITY validateEPAApplicable(const BFDataGroupId& idDataGroup );

};
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/AcctCategory.hpp-arc  $
//
//   Rev 1.7   Dec 01 2010 06:25:56   dchatcha
//P0175716 FN02 - Client Name Redemption - EPA Auto Settlement.
//
//   Rev 1.6   Apr 06 2010 12:32:54   kitticha
//PET0169756_FN01_N131-103 Statement and Confirm.
//
//   Rev 1.5   Aug 16 2007 10:59:02   kovacsro
//PET2388FN01 - Swift Payment Mrthod Id
//
//   Rev 1.4   May 30 2007 10:34:10   jankovii
//Bankogk - Incident #847336 - add acct categories for MMF.
//
//   Rev 1.3   Mar 21 2003 17:55:52   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.2   Feb 12 2003 16:35:00   KOVACSRO
//Added validatePendingTrades()
//
//   Rev 1.1   Jan 25 2003 17:00:50   KOVACSRO
//Added validation methods.
//
//   Rev 1.0   Jan 21 2003 14:26:18   KOVACSRO
//Initial revision.

 */