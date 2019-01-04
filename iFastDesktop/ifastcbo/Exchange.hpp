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
//    Copyright 2000 by International Financial Data Services
//
//******************************************************************************
//
// ^FILE   : Exchange.hpp
// ^AUTHOR : Serban Popescu
// ^DATE   : September, 2004
//
// ^CLASS    : Exchange
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include <ifastcbo\transfer.hpp>

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

//Forward declarations

class IFASTCBO_LINKAGE Exchange : public Transfer
{
public:
   Exchange (BFAbstractCBO &parent);
   virtual ~Exchange();
   virtual bool isAccountCloningAllowed (const BFDataGroupId &idDataGroup);
   virtual bool isGIAAttribAllowed (const BFDataGroupId &idDataGroup);
protected:
   virtual SEVERITY doInit (const BFDataGroupId &idDataGroup);
   virtual SEVERITY doInit (const BFData &data);
   virtual SEVERITY preInitWithDefaultValues (const BFDataGroupId &idDataGrousp);
   virtual void doInitWithDefaultValues (const BFDataGroupId &idDataGroup);
   virtual SEVERITY doApplyRelatedChanges ( const BFFieldId &idField, 
                                            const BFDataGroupId &idDataGroup );
   virtual SEVERITY doValidateField ( const BFFieldId &idField, 
                                      const DString &strValue, 
                                      const BFDataGroupId &idDataGroup); 

//validation methods
   virtual SEVERITY validateAccount ( MFAccount *pMFAccount, 
                                      const BFDataGroupId &idDataGroup);
   //account validation
   virtual SEVERITY canAccountTrade ( MFAccount *pMFAccount, 
                                      const BFDataGroupId &idDataGroup);	
   virtual SEVERITY validateAccountTo ( MFAccount *pMFAccount, 
                                        const BFDataGroupId &idDataGroup);
   virtual SEVERITY canAccountToTrade ( MFAccount *pMFAccount, 
                                        const BFDataGroupId &idDataGroup);
   virtual SEVERITY validateFundClass ( const DString &fundCode, 
                                        const DString &classCode, 
                                        const DString &accountNum, 
                                        const BFDataGroupId &idDataGroup);
   virtual SEVERITY validateToFundClass ( const DString &fundCode, 
                                          const DString &classCode, 
                                          const DString &accountNum, 
                                          const BFDataGroupId &idDataGroup);
   virtual SEVERITY validateFromToFundClass ( const DString &fromCode,
                                              const DString &fromClass,
                                              const DString &toCode,
                                              const DString &toClass,
                                              const BFDataGroupId &idDataGroup);
   virtual bool isEscrowTaxTypeRIFTransferApplicable (const BFDataGroupId &idDataGroup);
   virtual SEVERITY validateMasterActAMS(const BFDataGroupId &idDataGroup);
   virtual SEVERITY validateAmountAmtType (const BFDataGroupId& idDataGroup);
   virtual SEVERITY validateMinFromFundAmount ( const DString &accountNum,
                                                const DString &fundCode,
                                                const DString &classCode,
                                                const DString &amtType,
                                                const DString &amount,
                                                const DString &broker,
                                                const DString &branch,
                                                const DString &slsrep,
                                                const DString &depositType, //in1419539
                                                const BFDataGroupId &idDataGroup);
   virtual SEVERITY validateMinToFundAmount ( const DString &accountNum,
                                              const DString &fundCode,
                                              const DString &classCode,
                                              const DString &amtType,
                                              const DString &amount,
                                              const DString &broker,
                                              const DString &branch,
                                              const DString &slsrep,
                                              const DString &depositType, //in1419539
                                              const BFDataGroupId &idDataGroup);
   virtual SEVERITY validateOrderType ( const DString &orderType, 
                                        const BFDataGroupId &idDataGroup);
   virtual SEVERITY getAtCostTIKStatus ( const BFDataGroupId& idDataGroup, 
                                         const DString& dstrFundCodeIn, 
                                         const DString& dstrClassCodeIn,
                                         bool  blInAllocation,
                                         bool &blIsAtCostTIK);
   virtual SEVERITY validateTIKRedCodes ( const DString &redCode,
                                          const BFDataGroupId& idDataGroup);
   virtual bool isWireSupported (const BFDataGroupId &idDataGroup);
   virtual SEVERITY setDefaultOrderType (const BFDataGroupId &idDataGroup);
   virtual SEVERITY validateToSoftCapCheck (const BFDataGroupId &idDataGroup);
   virtual SEVERITY validateClosedCountryForPendingTrades (const BFDataGroupId &idDataGroup);

   virtual bool areRESPBenefAllocationsAllowed (const BFDataGroupId &idDataGroup);
   virtual bool isRESPTransferAllowed (const BFDataGroupId &idDataGroup);

   virtual SEVERITY validateRESPtoRESPTransfer(const DString& strDepType,
                                                const DString& strRedCode, 
                                                const DString& strTaxTypeFrom, 
                                                const DString& strTaxTypeTo, 
                                                const BFDataGroupId& idDataGroup);
   virtual SEVERITY validateLinkedEntity(const DString& strValue, const BFDataGroupId &idDataGroup);

   SEVERITY validateMoneyMktFund (const BFDataGroupId &idDataGroup);

   virtual SEVERITY validatePerfFeeFromToClassesWithFund ( const BFDataGroupId &idDataGroup);
   virtual SEVERITY validatePerfFeeFXRate ( const BFDataGroupId &idDataGroup);
   virtual SEVERITY PFCrystalisationRelatedChanges (const BFDataGroupId &idDataGroup);
   SEVERITY giAttribRelatedChanges (const BFDataGroupId &idDataGroup);
   virtual SEVERITY toFundClassRelatedChanges ( const DString &fundCode, 
                                                const DString &classCode, 
                                                const BFDataGroupId &idDataGroup);

   SEVERITY validateGIAToDIFExchange (const BFDataGroupId &idDataGroup);
   virtual SEVERITY RDRAdviceRelatedChanges (const BFDataGroupId &idDataGroup);
   virtual bool allowToFndClsBeParentAMS(const BFDataGroupId& idDataGroup);
   virtual bool isRDSPTransferAllowed (const BFDataGroupId &idDataGroup);

private:
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/Exchange.hpp-arc  $
//
//   Rev 1.28   Jul 26 2012 10:46:38   wp040027
//P0198518 - RDR Functionality
//
//   Rev 1.27   Apr 04 2012 14:42:46   jankovii
//IN 2898233 - R12.3-P0186477-Enable manual tax calculation of money out transactions for NR
//
//   Rev 1.26   Mar 23 2012 15:56:46   wp040133
//IN:
//WO:750919
//PF Crystalisation error for various erorrs
//For Some reason the changes were not reflected after check-in.So did a re-checkin
//
//   Rev 1.25   Mar 23 2012 15:50:28   wp040133
//IN:
//WO:750919
//PF Crystalisation error for various erorrs
//
//   Rev 1.24   Mar 15 2012 17:58:00   if991250
//IN 2879297: Money Out
//
//   Rev 1.23   Jan 20 2012 15:47:52   wp040027
//P0188394_Performance Fees - Order Entry
//
//   Rev 1.22   Dec 08 2011 21:45:16   wp040032
//P0183989 - Money Market Non Receipt
//
//   Rev 1.21   Aug 02 2010 07:56:32   dchatcha
//IN# 2196483 - QESI phase 1 - PET165541 - cannot process exchanges.
//
//   Rev 1.20   May 13 2010 15:27:28   jankovii
//PET165541_FN01_QESI - RESP Gap_Dsk_TRADING 
//
//   Rev 1.19   Mar 08 2010 13:17:38   jankovii
//PET165541_FN01_QESI - RESP Gap_Dsk_TRADING 
//
//   Rev 1.18   Jun 26 2009 06:17:32   kitticha
//IN#1738640 - R94 - Country Schedule - Cannot modify TX even when FundFrom and FundTo are same
//
//   Rev 1.17   15 Jun 2009 08:35:46   popescu
//PET157837 FN02 - Country Schedule Daily Non Resident Schedule A - revised the code
//
//   Rev 1.16   Jun 09 2009 05:44:10   kitticha
//PET157837 FN02 - Country Schedule Daily Non Resident Schedule A
//
//   Rev 1.15   01 Oct 2008 11:53:38   popescu
//Check in for incident 1419539
//
//   Rev 1.14   01 Aug 2007 15:59:10   popescu
//Incident # 956780 - mgfeerebate should always be direct
//
//   Rev 1.13   23 Jul 2007 16:49:38   popescu
//PET 2360 - FN 20 - GAP 20 Soft cap functionality
//
//   Rev 1.12   May 09 2007 16:21:12   jankovii
//MT54X PET2321 FN03 -Participant Transfer.
//
//   Rev 1.11   Mar 30 2007 14:06:22   jankovii
//PET 2292 FN01 - Switch Settlement.
//
//   Rev 1.9   Mar 26 2007 11:08:28   jankovii
//PET 2292 FN01 - Switch Settlement.
//
//   Rev 1.8   Nov 09 2006 00:07:48   popescu
//PET 2281/Fn01 - cloning account - TA  synch-up from rel 73
//
//   Rev 1.7   Oct 30 2006 17:02:26   jankovii
//PET 2185 FN04 - Trade restrictions.
//
//   Rev 1.6   Feb 20 2005 11:50:42   porteanm
//Incident 244225/WO 19920 - Missing escrow account validation for Exchange.
//
//   Rev 1.5   Dec 07 2004 01:37:34   popescu
//PET 1117/56 trades processing/modify trade
//
//   Rev 1.4   Nov 30 2004 20:09:56   popescu
//PET 1117/06
//
//   Rev 1.3   Nov 29 2004 20:30:14   popescu
//PET 1117/06/56 fees/trades processing
//
//   Rev 1.2   Nov 14 2004 14:36:58   purdyech
//PET910 - .NET Conversion
//
//   Rev 1.1   Nov 06 2004 00:40:48   popescu
//PET 1117/06, synch changes
//
//   Rev 1.2   Nov 04 2004 17:37:26   popescu
//PET 1117/06, Trade processing
//
//   Rev 1.1   Nov 02 2004 19:19:24   popescu
//PET 1117/06 Trade processing...
//
//   Rev 1.0   Oct 29 2004 20:27:40   popescu
//Initial revision.
//
//   Rev 1.0   Oct 01 2004 19:30:06   popescu
//Initial revision.
 * 
 *    Rev 1.206   Sep 15 2004 15:35:34   popescu
// 
*/