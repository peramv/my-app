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
// ^FILE   : PendingTradeDetails.hpp
// ^AUTHOR : Zijian Ying
// ^DATE   : 4/29/1999
//
// ^CLASS    : PendingTradeDetails
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************


#include <ifastcbo\mfcancbo.hpp>
#include <boost\utility.hpp>

class TradeAcctAllocList;
class TradeFromFundAllocList;
class PendingTradeBankInstructionsList;
class TransFeeList;
class TransFeeContext;
class TransactionUpdate;
class TradeSettlementLocationsList;

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class IFASTCBO_LINKAGE PendingTradeDetails : public MFCanBFCbo, private boost::noncopyable
{
public:
   PendingTradeDetails( BFAbstractCBO &parent );
   virtual ~PendingTradeDetails();

   SEVERITY getDetails( DString &AccountNum, 
                        DString& FundCode, 
                        DString& ClassCode,
                        DString& TransType, 
                        DString& TransNum, 
                        DString& TradeDate,
                        const DString& dstrTrack= I_("N"),
                        const DString& dstrPageName = NULL_STRING,
                        const DString& ignoreActiveBatch = I_("N"),
                        const DString& rebook = I_("N")
                  );
   void init( BFData &data);
   void getField( const BFFieldId& idField,
                  DString& strFieldValue,
                  const BFDataGroupId& idDataGroup,
                  bool formattedReturn = false ) const;
   SEVERITY getAccountAllocationList( TradeAcctAllocList*& pAccountAllocationList, 
                                      const BFDataGroupId& idDataGroup, 
                                      DString& AccountNum );
   SEVERITY getFromFundAllocationList(TradeFromFundAllocList *&pTradeFromFundAllocList, 
      const BFDataGroupId& idDataGroup, bool bCreate = true);
   SEVERITY getBankInstructionsList ( PendingTradeBankInstructionsList *&PendingTradeBankInstructionsList, 
                                      const BFDataGroupId &idDataGroup, 
                                      bool bCreate = true);
   SEVERITY getTransFeeList ( TransFeeList *&pTransFeeList, 
                              const BFDataGroupId &idDataGroup,
                              bool bCreate = true);
   SEVERITY getTransFeeContext ( TransFeeContext *&pTransFeeContext, 
                                 const BFDataGroupId &idDataGroup);
   bool isValidDateLag( const BFDataGroupId& idDataGroup );
   bool isMarginEligible (const BFDataGroupId& idDataGroup);
   bool isBankingAllowed (const BFDataGroupId &idDataGroup);
   bool PendingPACExist( const BFDataGroupId& idDataGroup );
   SEVERITY setConditions ( CONDITIONVECTOR *pCondVect, 
                            const BFDataGroupId& idDataGroup);
   SEVERITY getTransactionUpdate (TransactionUpdate *&pTransactionUpdate,
                                  const DString &recordType,
                                  const DString &caller,
                                  const DString &dstrEnableTradeAuthorization,
                                  const BFDataGroupId &idDataGroup,
                                  bool bInquireDataBase = true);
   SEVERITY getSettlementLocsList (TradeSettlementLocationsList *&pTradeSettlementLocationsList, 
                                   const BFDataGroupId &idDataGroup, 
                                   bool bCreate = true);
   bool amountInventoryAppl(const BFDataGroupId &idDataGroup);
private:
   SEVERITY clearingRelatedChanges();

   SEVERITY setSettlementLocationSubstList ( const BFFieldId &idFieldCode,
                                             const DString &dstrAccountNum,
                                             const BFDataGroupId &idDataGroup);

   SEVERITY setSettlementCodeSubstList ( const BFFieldId& idFieldCode,
                                         const DString &dstrAccountNum,
                                         const BFDataGroupId& idDataGroup);

   SEVERITY setGRRepayReasonSubstList(const BFDataGroupId &idDataGroup);
   SEVERITY initIsCancelModSEGTradeAllowed(const BFDataGroupId &idDataGroup);
   SEVERITY setSourceOfFundSubstList(const BFDataGroupId &idDataGroup); //P0186486_FN15_The Source of Funds

   bool isSEGFund ( const DString& fundCode);

   bool _AlreadyGotDetails;
   DString m_strAccountNum;
   TransFeeContext *_pTransFeeContext;
};

//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/PendingTradeDetails.hpp-arc  $
 * 
 *    Rev 1.28   May 04 2012 11:40:44   panatcha
 * P0186486_FN15_The Source of Funds
 * 
 *    Rev 1.27   Mar 05 2012 12:03:02   dchatcha
 * P0186484 FN05 - SEG Trade Processing.
 * 
 *    Rev 1.26   Apr 30 2010 01:16:32   dchatcha
 * PET0165541 FN01 QESI RESP Trading, display new fields of view 54.
 * 
 *    Rev 1.25   Aug 11 2009 15:13:22   jankovii
 * PET0164824 FN01 - Eiger iShares Orders and ETF Fields
 * 
 *    Rev 1.24   May 22 2009 16:04:02   jankovii
 * PET 159770 FN05 Auto Batching.
 * 
 *    Rev 1.23   Jul 08 2005 09:31:22   Yingbaol
 * PET1235,FN01:transaction cancellation rebook
 * 
 *    Rev 1.22   Jun 14 2005 15:41:16   Fengyong
 * #Incident 328435 - Add IgnoreActiveBatch field to 54 request
 * 
 *    Rev 1.21   Mar 10 2005 09:47:08   popescu
 * PET 1190/04, trade date aggregated order update
 * 
 *    Rev 1.20   Jan 20 2005 11:03:40   popescu
 * PTS 10038127, fixed internal error when user clicks on the 'Fees' button in trans  history screen
 * 
 *    Rev 1.19   Dec 13 2004 16:46:54   vadeanum
 * PET1117 FN21 - Settlement Instr setup.
 * 
 *    Rev 1.18   Dec 07 2004 21:20:24   popescu
 * PET 1117/06, pending trades/fees fixes, add-ons
 * 
 *    Rev 1.17   Nov 14 2004 14:51:04   purdyech
 * PET910 - .NET Conversion
 * 
 *    Rev 1.16   Nov 20 2003 09:14:00   linmay
 * added PendingPACExist( ) for PTS #10024070
 * 
 *    Rev 1.15   Oct 19 2003 16:44:50   popescu
 * CIBC, PET809, FN 13 banking work
 * 
 *    Rev 1.14   Sep 01 2003 21:32:36   popescu
 * PET 809, FN 02 CIBC Multi Fund Transfer
 * 
 *    Rev 1.13   Mar 21 2003 18:20:00   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.12   Feb 12 2003 16:37:10   KOVACSRO
 * Added isMarginEligible()
 * 
 *    Rev 1.11   Oct 09 2002 23:54:48   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.10   Aug 29 2002 12:53:10   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.9   22 May 2002 22:22:22   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.8   22 May 2002 18:20:18   PURDYECH
 * BFData Implementation
 */
