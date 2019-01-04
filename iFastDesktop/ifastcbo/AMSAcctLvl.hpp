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
//    Copyright 2007, By International Financial Data Service`
//
//
//******************************************************************************
//
// ^FILE   : AMSAcctLvl.hpp
// ^AUTHOR : Monica Porteanu
// ^DATE   : June 19, 2007
//
// ^CLASS    : AMSAcctLvl
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

class AmsMstrInfo;
class AbstractAlloc;
class DefFundAllocList;
class AMSDeltaAllocList;

class IFASTCBO_LINKAGE AMSAcctLvl : public MFCanBFCbo
{
public:
   AMSAcctLvl( BFAbstractCBO &parent );
   virtual ~AMSAcctLvl();

   SEVERITY init(const BFData&   data );
   SEVERITY initNew(const BFDataGroupId& idDataGroup );
   SEVERITY getAMSAcctLvlAllocation ( DefFundAllocList *&pFundAllocList, 
                                      const BFDataGroupId& idDataGroup,
                                      bool bCreate = true);
   SEVERITY getAMSDeltaAllocList(AMSDeltaAllocList *&pAMSDeltaAllocList,const BFDataGroupId& idDataGroup, bool bCreate = true);
   SEVERITY initAMSDeltaAllocList(DefFundAllocList *pAMSFundAllocList, AMSDeltaAllocList *&pAMSDeltaAllocList, const BFDataGroupId& idDataGroup);

protected:
   virtual SEVERITY doValidateField( const BFFieldId& idField, const DString& strValue, const BFDataGroupId& idDataGroup );
   virtual SEVERITY doValidateAll( const BFDataGroupId& idDataGroup, long lValidateGroup );
   virtual SEVERITY doApplyRelatedChanges( const BFFieldId& idField, const BFDataGroupId& idDataGroup );
   virtual void doInitWithDefaultValues( const BFDataGroupId& idDataGroup );


private:
   SEVERITY validateAMSCode( const DString& strValue, const BFDataGroupId& idDataGroup );
   SEVERITY validateAMSRestrictionForBrokers( const DString& dstrAMSCode, MFAccount* pMFAccount, const BFDataGroupId& idDataGroup );
   SEVERITY validateAMSRestrictions( AmsMstrInfo* pAmsMstrInfo, 
                                     MFAccount* pMFAccount, 
                                     const BFDataGroupId& idDataGroup);
   SEVERITY validateAMSType( const DString& dstrAMSType, const BFDataGroupId& idDataGroup );
   SEVERITY validateNextRebDate(const DString& strValue, const BFDataGroupId& idDataGroup );
   SEVERITY validateThresholdPrcnt(const DString& strValue, const BFDataGroupId& idDataGroup );
   SEVERITY validateSchedSetupFreqID(const DString& strValue, const BFDataGroupId& idDataGroup );
   SEVERITY validateEffectiveDate(const DString& strValue, const BFDataGroupId& idDataGroup );
   SEVERITY validateStopDate(const DString& strValue, const BFDataGroupId& idDataGroup );
   bool isBusinessDate( const DString& strValue, const BFDataGroupId& idDataGroup );
   bool isLastBusDayOfWeek ( const DString& strValue, const BFDataGroupId& idDataGroup );

   void applyDefaultRBChanges(const BFDataGroupId& idDataGroup);
   void CalculateNextRebDate(const BFDataGroupId& idDataGroup);
   SEVERITY setAMSTypeSubstitutionList( const BFDataGroupId& idDataGroup, DString& firstCode );  // as copied from MFAccount
   SEVERITY setAMSFrequencySubstSet( const BFDataGroupId& idDataGroup );
   SEVERITY getAMSMasterInfo (AmsMstrInfo *&pAmsMstrInfo, const BFDataGroupId& idDataGroup);
   SEVERITY commonInit( const BFDataGroupId& idDataGroup );

   SEVERITY getAcctAlloc( AbstractAlloc *&pAcctAlloc, const BFDataGroupId& idDataGroup );
   bool isAmsCodeGlobal( const DString &dstrAMSCode, const BFDataGroupId& idDataGroup );
   SEVERITY validateAccountClosedCountry ( const BFDataGroupId &idDataGroup );
   //IN2818924 - DSK_AMS Validation for CDIC
   bool isAmsFundAllocAppliedBankruptcy( DString& fundCode,
                                         DString& classCode,
                                         const BFDataGroupId& idDataGroup );

   SEVERITY validateAMSCodeWithUnderSameShr(const DString& strValue,
                                            MFAccount* pMFAccount,
                                            const BFDataGroupId&  idDataGroup);

   SEVERITY validateAgainstStopStatus ( const BFDataGroupId &idDataGroup);   	 
private:
   bool bRecalcRebDate;

};

//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastcbo/AMSAcctLvl.hpp-arc  $
//
//   Rev 1.18   Jan 31 2012 07:35:56   panatcha
//IN2818924 - DSK_AMS Validation for CDIC
//
//   Rev 1.17   Jun 09 2009 05:37:30   kitticha
//PET157837 FN02 - Country Schedule Daily Non Resident Schedule A
//
//   Rev 1.16   12 Feb 2008 16:22:00   kovacsro
//IN#1101605 - added isAMSGlobal
//
//   Rev 1.15   19 Oct 2007 16:17:04   kovacsro
//IN#1038318 - added rej erros / hard edit to prevent users from entering future dated Stop dates on AMS and modifying Effective Date for RB/RO default allocations on Allocation screen
//
//   Rev 1.14   21 Sep 2007 16:24:56   popescu
//Incident 1015469 -  added bCreate to the allocations method
//
//   Rev 1.13   21 Sep 2007 14:32:04   popescu
//Incident 10002765 Added AMS setup edit for institutional accounts
//Checks AMS limitation rules for StopPurchase/StopRedemption/Transfer out and Tarsnfer In
//
//   Rev 1.12   14 Sep 2007 10:59:22   popescu
//Incident 1003183 (GAP2360/02) - fixed AMS allocations
//
//   Rev 1.11   Sep 11 2007 09:02:04   smithdav
//IN 979244 - Non exchangable funds edit.
//
//   Rev 1.10   Sep 07 2007 14:26:52   smithdav
//IN 982733 - set Account level Alloc fields from AMSAcct.
//
//   Rev 1.9   Aug 17 2007 10:30:02   smithdav
//IN #973657
//
//   Rev 1.8   Aug 16 2007 18:05:24   smithdav
//IN #978244
//
//   Rev 1.7   Aug 10 2007 17:08:16   smithdav
//PET 2360 FN02 - fix BrokerAMS edit bug.
//
//   Rev 1.6   Aug 03 2007 09:34:54   smithdav
//PET 2360 FN02
//
//   Rev 1.5   Jul 27 2007 11:34:28   smithdav
//PET2360 FN02 - Add NextReb date edits. Add som fiield inits.
//
//   Rev 1.4   Jul 19 2007 14:23:36   smithdav
//PET2360 FN02 - Fix NextRebalanceDate recalc.
//
//   Rev 1.3   Jul 18 2007 09:35:32   smithdav
//PET2360 FN02
//
//   Rev 1.2   Jun 28 2007 15:48:52   porteanm
//PET 2360 FN02 - AMS - work in progress.
//
//   Rev 1.1   Jun 22 2007 14:18:22   porteanm
//PET 2360 FN02 - AMS - work in progress.
//
//   Rev 1.0   Jun 20 2007 11:42:48   porteanm
//Initial revision.
//
