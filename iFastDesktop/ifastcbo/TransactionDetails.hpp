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
// ^FILE   : TransactionDetails.hpp
// ^AUTHOR : Zijian Ying
// ^DATE   : 3/22/1999
//
// ^CLASS    : TransactionDetails
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************


#include <ifastcbo\mfcancbo.hpp>
#include <boost\utility.hpp>

class BankInstructions;
class DeductionList;
class SplitCommissionList;
class TradeAcctAllocList;
class TradeFromFundAllocList;
class TransactionDetailsBankInstructionsList;
class TransactionLinkList;
class DateValidation;
class TransactionUpdate;
class TradeSettlementLocationsList;
class TradePayInstructList;
class EstateAllocationList;
class FundLmtOverrideList;

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class IFASTCBO_LINKAGE TransactionDetails : public MFCanBFCbo, private boost::noncopyable
{
public:
   TransactionDetails( BFAbstractCBO &parent );
   virtual ~TransactionDetails();

   SEVERITY getDetails( DString& TransId,
                        const DString& dstrTrack= I_("N"),
                        const DString& dstrPageName = NULL_STRING );

   SEVERITY init( BFData &data );

   DeductionList *getDeductionList() {return(pDeductionList_);};

   void getField( const BFFieldId& idField, DString& strFieldValue, 
      const BFDataGroupId& idDataGroup, bool formattedReturn = false ) const;
   SEVERITY getAccountAllocationList(TradeAcctAllocList*& pAccountAllocationList, 
      const BFDataGroupId& idDataGroup, DString& AccountNum );
   SEVERITY getFromFundAllocationList(TradeFromFundAllocList *&pTradeFromFundAllocList, 
      const BFDataGroupId& idDataGroup, bool bCreate = true);
   SEVERITY getBankInstructionsList(
      TransactionDetailsBankInstructionsList *&pTransactionDetailsBankInstructionsList, 
      const BFDataGroupId& idDataGroup, 
      bool bCreate = true,
      bool bCheckBankAllow = true );
   bool isBankingAllowed (const BFDataGroupId &idDataGroup);
   SEVERITY doValidateField ( const BFFieldId &idField, 
                                  const DString &strValue, 
                                  const BFDataGroupId &idDataGroup
                                );
   bool IsCancellationEnable ( const BFDataGroupId &idDataGroup ) const;
   bool isSWPSettleESGElig( const BFDataGroupId &idDataGroup);
   bool allowESGSettleForNominee ( const DString& dstrBroker, const BFDataGroupId &idDataGroup);
   bool allowESGSettleForIntermediary ( const BFDataGroupId &idDataGroup);

   SEVERITY TransactionDetails::getTransactionLinkList(
               TransactionLinkList *&pTransactionLinkList, 
               const BFDataGroupId& idDataGroup, bool bCreate = true);

   SEVERITY ValidateSettleDate (const BFDataGroupId &idDataGroup, const DString inputSettleDate );
   SEVERITY getDateValidation ( DateValidation *&pDateValidation, 
                                         const DString &validationType,
                                         const DString &tradeDate, 
                                         const BFDataGroupId &idDataGroup);
   SEVERITY getTransactionUpdate (TransactionUpdate *&pTransactionUpdate,
                                  const DString &recordType,
                                  const DString &caller,
                                  const DString &dstrEnableTradeAuthorization,
                                  const BFDataGroupId &idDataGroup,
                                  bool bInquireDataBase = true);
   SEVERITY getSettlementLocsList (TradeSettlementLocationsList *&pTradeSettlementLocationsList, 
                                   const BFDataGroupId &idDataGroup, 
                                   bool bCreate = true);

   SEVERITY getPayToEntity (DString &payToEntity, 
                            const BFDataGroupId &idDataGroup );
   SEVERITY getEstateAllocationList ( EstateAllocationList *&pEstateAllocationList, 
                                      const BFDataGroupId &idDataGroup, bool bReadOnly, bool bCreate = true);
   bool bIsRightToCancelRuleEnabled(const BFDataGroupId &idDataGroup);
   bool amountInventoryAppl(const BFDataGroupId &idDataGroup);

protected:
   bool isPayEntityBankAvailable( const BFDataGroupId &idDataGroup );
   SEVERITY getPayInstructList ( TradePayInstructList *&pTradePayInstructList, 
                                 const BFDataGroupId &idDataGroup);
   SEVERITY getEntityBankInstruction(BankInstructions *&pBankInstructions,
                                     const DString& payToEntity,
                                     const BFDataGroupId& idDataGroup);
   SEVERITY getEntityBankInstructionFromTrxnBank(BankInstructions *&pBankInstructions,
                                                 const BFDataGroupId& idDataGroup);

private:
   SEVERITY clearingRelatedChanges();

   SEVERITY setSettlementLocationSubstList ( const BFFieldId &idFieldCode,
                                             const DString &dstrAccountNum,
                                             const BFDataGroupId &idDataGroup );

   SEVERITY setSettlementCodeSubstList ( const BFFieldId& idFieldCode,
                                         const DString &dstrAccountNum,
                                         const BFDataGroupId& idDataGroup );

   SEVERITY setSourceOfFundSubstList(const BFDataGroupId &idDataGroup); //P0186486_FN15_The Source of Funds

   SEVERITY initIsCancelModSEGTradeAllowed(const BFDataGroupId &idDataGroup);
   SEVERITY getFundLmtOverrideList ( FundLmtOverrideList *&pFundLmtOverrideList, const BFDataGroupId &idDataGroup);

   bool isSEGFund ( const DString& fundCode);

   void getCurrency(const BFDataGroupId& idDataGroup, DString& currency) const;
   bool              _AlreadyGotDetails;
   DString           _TransId;
   DeductionList*    pDeductionList_;
};


//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/TransactionDetails.hpp-arc  $
 * 
 *    Rev 1.28   May 04 2012 11:37:18   panatcha
 * P0186486_FN15_The Source of Funds
 * 
 *    Rev 1.27   Mar 05 2012 12:13:56   dchatcha
 * P0186484 FN05 - SEG Trade Processing.
 * 
 *    Rev 1.26   Jul 05 2010 02:13:40   dchatcha
 * IN# 1984105 - Settlement from Broker trade will bring out shareholder default bank.
 * 
 *    Rev 1.25   Jan 20 2010 08:56:00   dchatcha
 * IN# 1976746 - Pay Instruction button enabled with Pay type X and error displayed.
 * 
 *    Rev 1.24   Aug 11 2009 15:14:26   jankovii
 * PET0164824 FN01 - Eiger iShares Orders and ETF Fields
 * 
 *    Rev 1.23   May 22 2009 16:04:46   jankovii
 * PET 159770 FN05 Auto Batching.
 * 
 *    Rev 1.22   May 22 2009 10:36:56   jankovii
 * PET 159770 FN05 Auto Batching.
 * 
 *    Rev 1.21   Mar 02 2006 17:33:24   ZHANGCEL
 * PET1334 - FN01 -- ESG Settlement enhancement
 * 
 *    Rev 1.20   Aug 04 2005 17:50:54   Fengyong
 * Incident 366368 - Add SettleDate validation
 * 
 *    Rev 1.19   Jul 08 2005 09:33:52   Yingbaol
 * PET1235,FN01:transaction cancellation rebook
 * 
 *    Rev 1.18   Mar 04 2005 17:03:50   Fengyong
 * PET1190 FN04 - TranCancel tempary check in for other coder
 * 
 *    Rev 1.17   Feb 03 2005 13:38:44   Fengyong
 * PET1117 FN66 - Trade reconcile API
 * 
 *    Rev 1.16   Dec 14 2004 10:45:38   vadeanum
 * PET1117 FN21 - Settlement Instr setup.
 * 
 *    Rev 1.15   Nov 14 2004 14:58:14   purdyech
 * PET910 - .NET Conversion
 * 
 *    Rev 1.14   Oct 19 2003 16:44:58   popescu
 * CIBC, PET809, FN 13 banking work
 * 
 *    Rev 1.13   Sep 01 2003 21:32:44   popescu
 * PET 809, FN 02 CIBC Multi Fund Transfer
 * 
 *    Rev 1.12   May 16 2003 17:17:06   popescu
 * TransactionDetails doesn't own split commission; it goes thru TradeFundAllocation
 * 
 *    Rev 1.11   Mar 21 2003 18:27:42   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.10   Oct 09 2002 23:55:12   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.9   Aug 29 2002 12:53:56   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.8   22 May 2002 22:22:28   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.7   22 May 2002 18:19:10   PURDYECH
 * BFData Implementation
 */
