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
//    Copyright 2002 by DST Canada, Inc.
//
//
//******************************************************************************
//
// ^FILE   : TradeFundAlloc.hpp
// ^AUTHOR : Robert Kovacs
// ^DATE   : 08/04/02
//
// ^CLASS    : TradeFundAlloc
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION : default fund allocation 
//
//******************************************************************************

#ifndef FUNDALLOC_HPP
   #include <ifastcbo\FundAlloc.hpp>
#endif 

class AcqFeeInquiry;
class MFAccountHoldingList;

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class IFASTCBO_LINKAGE TradeFundAlloc : public FundAlloc
{
public:
   // X-structors
   TradeFundAlloc( BFAbstractCBO &parent );
   virtual ~TradeFundAlloc( void );
   SEVERITY initNew( const BFDataGroupId& idDataGroup,
                     const DString& dstrTrack = I_("N"),
                     const DString& dstrPageName = NULL_STRING );
   SEVERITY initExisting(const BFData &data);
   SEVERITY initDefault(BFAbstractCBO* pDefaultAlloc, const BFDataGroupId& idDataGroup);
   SEVERITY getSplitCommissionList ( SplitCommissionList *&rpSplitCommissionList, 
                                     const BFDataGroupId &idDataGroup, 
                                     bool bCreate = true,
                                     bool bGetDefault = false);
   SEVERITY copyDataFromParent(const BFDataGroupId& idDataGroup);
   SEVERITY refreshSplitCommFlag (const BFDataGroupId& idDataGroup);
   void   changeFieldsForRebook();
   bool hasPurchExchgFrontEndLoadCommission(const BFDataGroupId& idDataGroup);
   bool isFELFundClass(const BFDataGroupId& idDataGroup);
   SEVERITY getAcqFeeDefault (AcqFeeInquiry *&pAcqFeeInquiry, const BFDataGroupId &idDataGroup);
   SEVERITY setFeeRate(const DString& dstrFeeRate, const BFDataGroupId& idDataGroup);
   SEVERITY isBaseCommissionApplicableAndGetSFACRate ( bool &baseCommApplicable,
                                                       DString &strSFACRate,
                                                       const BFDataGroupId &idDataGroup, 
                                                       const DString dstrAllocFundCode  = NULL_STRING, 
                                                       const DString dstrAllocClassCode = NULL_STRING);

protected:

   SEVERITY doApplyRelatedChanges( const BFFieldId& idField, const BFDataGroupId& idDataGroup );
   SEVERITY doValidateField( const BFFieldId& idField, const DString& strValue, const BFDataGroupId& idDataGroup );
   void doInitWithDefaultValues( const BFDataGroupId& idDataGroup );
   bool isSegFundValidationReq(){return true;};
   virtual SEVERITY doValidateAll ( const BFDataGroupId& idDataGroup, long lValidateGroup );

   virtual SEVERITY validateFundClassAccNumDate ( const BFDataGroupId& idDataGroup );  
   virtual SEVERITY getSeqFundValidation( SeqFundValidation *&pSeqFundValidation,
                                          const BFDataGroupId& idDataGroup);

   SEVERITY calculateAquisitionFeeCommission(const BFDataGroupId &idDataGroup);
   SEVERITY updateTransFeeAcqFeeRate(const DString& dstrFeeRate, const BFDataGroupId& idDataGroup);
private :

   //validations
   SEVERITY validateFundCode( const DString& strValue, const BFDataGroupId& idDataGroup ) ;
   SEVERITY validateClassCode( const DString& strValue, const BFDataGroupId& idDataGroup ) ;
   SEVERITY validateFundClass( const BFDataGroupId& idDataGroup ) ;
   SEVERITY validateSoftCapCheck( const BFDataGroupId& idDataGroup ) ;
   SEVERITY validateAcctNumFundClass( const BFDataGroupId& idDataGroup ) ;
   SEVERITY validateAmount( const DString& strValue, const BFDataGroupId& idDataGroup );
   SEVERITY validateCrossAmount(const BFDataGroupId& idDataGroup);
   SEVERITY validateFundClassPercent(const BFDataGroupId& idDataGroup);
   SEVERITY validateFundAllocation (const BFDataGroupId& idDataGroup);
   SEVERITY getMaxFeeRate(SplitCommissionList *&rpSplitCommissionList,const BFDataGroupId& idDataGroup);
   SEVERITY updateCommissionDefault(const BFDataGroupId& idDataGroup);

   //handy methods
   SEVERITY fetchSplitCommisionListUsingParentCBO(SplitCommissionList *&rpSplitCommissionList, 
      const BFDataGroupId& idDataGroup);
	SEVERITY setAmountField( const BFDataGroupId& idDataGroup );
   bool splitCommActive ( const BFDataGroupId& idDataGroup );  
   bool _bInitialSplitComm;

};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/TradeFundAlloc.hpp-arc  $
//
//   Rev 1.27   Jul 31 2012 14:25:56   wp040027
//IN# 3006862-CPF-Enable Fee in PAC/Corrected default Fee in PAC and Trade screen/Max Fee Validation
//
//   Rev 1.26   Apr 16 2012 23:22:32   popescu
//2901148 - Gurantee Flag Override
//
//   Rev 1.25   Apr 11 2012 12:20:08   dchatcha
//IN# 2914672 - P0186479 Issues on Guarantee Override field on Trade Entry screen
//
//   Rev 1.24   Apr 11 2006 09:24:16   jankovii
//PET 1334 Alternative Product.
//
//   Rev 1.23   Jul 08 2005 09:33:26   Yingbaol
//PET1235,FN01:transaction cancellation rebook
//
//   Rev 1.22   Jun 15 2005 15:50:04   porteanm
//PET1024 FN40 - Guarantee Adjustments.
//
//   Rev 1.21   Feb 22 2005 17:38:06   popescu
//Incident# 247079, move the code to dovalidateall
//
//   Rev 1.20   Jan 18 2005 19:42:18   popescu
//PTS 10038609, acquisition does not get refreshed if split comm changes to default
//
//   Rev 1.19   Jan 12 2005 17:18:34   popescu
//PTS 10037811, fixed pending trade issue with split commissions, also cleaned-up the fel/acq fee methods
//
//   Rev 1.18   Nov 29 2004 20:30:54   popescu
//PET 1117/06/56 fees/trades processing
//
//   Rev 1.17   Nov 27 2004 21:19:18   popescu
//PET 1117/06, trades processing
//
//   Rev 1.16   Nov 14 2004 14:57:58   purdyech
//PET910 - .NET Conversion
//
//   Rev 1.15   Nov 06 2004 00:43:16   popescu
//PET 1117/06, synch changes
//
//   Rev 1.14   Mar 01 2004 10:14:44   HERNANDO
//PET965 FN02 - Added forward reference.
//
//   Rev 1.13   Feb 27 2004 11:08:32   AGUILAAM
//PET965_FN02: Added trade amount validation against account holdings (return error or warning)
//
//   Rev 1.12   Dec 08 2003 15:28:50   popescu
//PTS 10023645, split commission re-work
//
//   Rev 1.11   Oct 14 2003 10:43:38   VADEANUM
//PTS 10021935 - Allocation screen Percent Total is 200 - added 
//setAmountField as Read Only or not, removed set100Percent().
//
//   Rev 1.10   Aug 25 2003 18:40:00   WINNIE
//Non close account full redemption code enhancement : If full redemption is indicated, set the percentage to 100% (for processing purpose) and set the allocpercentage to read only. Same logic applies to new object recreation. Modify doInitwithdefaultValue to invoke this the new method
//
//   Rev 1.9   Jun 02 2003 18:20:12   popescu
//removed setSplitRate total since is not used anymore. The amount on a split commission should be set by using the Amount field of the SplitCommission list
//
//   Rev 1.8   May 15 2003 15:03:48   popescu
//fixes for a crash in PendingTrades, split comm
//
//   Rev 1.7   Apr 29 2003 17:14:52   popescu
//PTS 10016204
//
//   Rev 1.6   Mar 21 2003 18:27:10   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.5   Nov 12 2002 11:28:50   KOVACSRO
//Added isSegFundValidationReq() to clarify which allocations require this validation.
//
//   Rev 1.4   Oct 09 2002 23:55:10   PURDYECH
//PVCS Database Conversion
//
//   Rev 1.3   Aug 29 2002 12:53:54   SMITHDAV
//ClientLocale and typed field changes.
//
//   Rev 1.2   Aug 19 2002 17:04:12   KOVACSRO
//Added validateFundClassPercent()
//
//   Rev 1.1   22 May 2002 18:19:40   PURDYECH
//BFData Implementation
//
//   Rev 1.0   29 Apr 2002 16:56:24   KOVACSRO
//Initial revision.
 * 
 *
*/