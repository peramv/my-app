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
//    Copyright 2001 by DST Canada, Inc.
//
//******************************************************************************
//
// ^FILE   : BankInstructionsProcess.hpp
// ^AUTHOR : Mihai Virgil Buzila
// ^DATE   : 02/09/2001
//
//******************************************************************************


#include <bfproc\AbstractProcess.hpp>
///#endif
#include <ifastbp\ifasthistoricalparameters.hpp>

// Import/Export resolution
#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif

class BankTransactionList;
class MFAccount;
class Shareholder;
class RRIFBankInstructionsList;
class SystematicBankInstructionsList;
class DistributionBankInstructionsList;
class SettlementTradeBankInstructionsList;
class MatSweepInstrBankList;
class ContractMatInstrBankList;
class AcctCommitBankList;
class ShareholderBankInstructionsList;

class IFASTBP_LINKAGE BankInstructionsProcess : public AbstractProcess, public IFastHistoricalParameters
{
// Construction
public:
   BankInstructionsProcess( GenericInterfaceContainer *pGIC, 
                            GenericInterface *pGIParent, 
                            const Command &rCommand);
   virtual ~BankInstructionsProcess();
   bool hasBankingInstr(const DString& dstrxAcctNumber = NULL_STRING ) const;

protected:
   virtual void doGetField ( const GenericInterface *rpGICaller,
                             const BFContainerId &idContainer, 
                             const BFFieldId &idField,
                             const BFDataGroupId &idDataGroup, 
                             DString &strValueOut,
                             bool bFormatted) const;
   virtual bool doModelessSetFocus (GenericInterface *rpGICaller);
   void setCurrentListItem ( const GenericInterface *rpGICaller, 
                             const BFContainerId &idList, 
                             const DString &strListItemKey);
   virtual bool doModelessChildComplete (const Command &cmd);
   virtual SEVERITY doInit();
   virtual bool doOk (GenericInterface *rpGI);
   virtual E_COMMANDRETURN doProcess();
   virtual SEVERITY doSetField ( const GenericInterface *rpGICaller,
                                 const BFContainerId &idContainer, 
                                 const BFFieldId &idField,
                                 const BFDataGroupId &idDataGroup, 
                                 const DString &strValue,
                                 bool bFormatted);
   virtual void *getPtrForContainer ( const BFContainerId& idContainer,
                                      const BFDataGroupId& idDataGroup);
   const BFProperties *doGetFieldAttributes ( const GenericInterface *rpGICaller, 
                                              const BFContainerId &idContainer, 
                                              const BFFieldId &idField, 
                                              const BFDataGroupId &idDataGroup);
   virtual SEVERITY doValidateAll ( BFAbstractCBO *rpWSD,
                                    const BFDataGroupId &idDataGroup);
   virtual bool doCancel (GenericInterface *rpGICaller);
   virtual void doPostOk ( GenericInterface *rpGICaller, 
                           bool bSuccessFlag);
   virtual SEVERITY getHistoricalParameters ( const BFContainerId &idContainer,
                                              BFFieldId &recordIdField, 
                                              DString &tableId, 
                                              DString &dstrKeys);
   virtual bool doSend ( GenericInterface *rpGICaller, 
                         const I_CHAR *szMessage);
   SEVERITY getHistoricalParameters ( const BFContainerId &idContainer, 
                                      HISTORICAL_VECTOR &vectorInput);

private:
template <class _X, class _Y, class _Z>
   SEVERITY cloneAndAttach ( const _X*, 
                             const _Y*, 
                             const _Z*, 
                             const BFContainerId &idContainer, 
                             const DString &keyToBeRemoved);
template <class _X, class _Y, class _Z>
   SEVERITY buildDummyBankInstructionsList ( _X *&ptrBankListOut, 
                                             const _Y *ptrBankObject, 
                                             const _Z *ptrObject);
   SEVERITY buildDummyRRIFBankInstructionsList();
   SEVERITY buildDummyDistributionBankInstructionsList();
   SEVERITY buildDummySystematicBankInstructionsList();
   SEVERITY buildDummySettlementTradeBankInstructionsList();
   SEVERITY buildDummyMatSweepInstrBankList();
   SEVERITY buildDummyContractMatInstrBankList();
   SEVERITY buildDummyAcctCommitBankList();

   void removeBankInstructionsList ( const BFContainerId &idContainer, 
                                     const I_CHAR *icharKey);
   void removedClonedBankLists ();
   SEVERITY processParameters();

   DString _accountNum,
      _shrNum,
      _fundCode,
      _classCode,
      _fundGroup,
      _fundSponsor,
      _bankInstrType,
      _brokerCode,
      _branchCode,
      _salesRepCode,
      _callerListKey,
      _callerSubListKey,
      _caller,
      _rrifListKey,
      _systematicListKey,
      _distributionListKey,
      _settlementListKey,
      _tradeListKey,
      _bankInstructionsListSelectionKey,
      _fundSponsorDesc,
      _distribGBCD,
      _distribVerifyStat,
      m_strUserAccessCode,
      _payInstructExists,
      _payToEntity,
	  _dstrCotAcctRid,
	  _dstrContractType,
	  _dstrContractTypeId;

   DString _matSweepInstrType;
   DString _matSweepInstrLevel;
   DString _matSweepInstrKey;
   DString _matSweepInstrDetailsKey;
   DString _matSweepInstrListKey;
   DString _acctCommitListKey;
   DString _conMatInstrListKey;
   DString _conConMatListKey;
   DString _TransNum;
   DString _TransId;
   DString _IntInvestId;
   DString _PrincipalAmount;
   DString _AccuredAmount;
   DString _RegAgent;

   GenericInterface *_rpChildGI;
   BFProperties *_propBankOptionsFieldsHeadingSet;
   MFAccount* _pMFAccount;
   Shareholder* _pShareholder;
   RRIFBankInstructionsList *_pDummyRRIFBankInstructionsList;
   SystematicBankInstructionsList *_pDummySystematicBankInstructionsList;
   MatSweepInstrBankList* _pDummyMatSweepInstrBankList;
   ContractMatInstrBankList* _pDummyContractMatInstrBankList;
   AcctCommitBankList* _pDummyAcctCommitBankList;
   DistributionBankInstructionsList *_pDummyDistributionBankInstructionsList;
   SettlementTradeBankInstructionsList *_pDummySettlementTradeBankInstructionsList;
};


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/BankInstructionsProcess.hpp-arc  $
 * 
 *    Rev 1.43   Apr 04 2012 11:10:54   wp040039
 * PETP0187485-Registration Agent  Banking
 * 
 *    Rev 1.42   Mar 08 2012 12:35:00   jankovii
 * Sync up: IN 2859411 - P0186477_FN02_Interest Instruction-Err displayed on split type 'Amount' instrctn
 * 
 *    Rev 1.41   Mar 02 2012 16:40:54   wp040100
 * P0186484 FN05 - Contract Maturity Instruction - Banking Screen Integration
 * 
 *    Rev 1.40   Feb 24 2012 18:39:56   if991250
 * Account Commitment
 * 
 *    Rev 1.39   Feb 21 2012 13:10:04   if991250
 * Trade Mat Sweep Instr Banks
 * 
 *    Rev 1.38   Feb 02 2012 15:06:52   if991250
 * Maturity/Interest Instructions banking
 * 
 *    Rev 1.37   Jul 05 2010 02:20:10   dchatcha
 * IN# 1984105 - Settlement from Broker trade will bring out shareholder default bank.
 * 
 *    Rev 1.36   Jan 13 2010 09:12:08   dchatcha
 * IN# 1971377 - R97_Static Data_File Processor&Bank are blank after deleting distribution option.
 * 
 *    Rev 1.35   Nov 02 2006 11:45:32   ZHANGCEL
 * PET2217 FN26 - Add a new parameter for Bank Instruction title display
 * 
 *    Rev 1.34   Oct 18 2006 15:53:08   popescu
 * PET 2217/26 STP Multiple Debit Accounts - fund sponsor banking
 * 
 *    Rev 1.33   Sep 10 2006 17:57:42   popescu
 * STP 2192/12
 * 
 *    Rev 1.32   Jul 31 2006 15:26:36   ZHANGCEL
 * PET2192 FN11 -- MgmtCo Banking related changes
 * 
 *    Rev 1.31   Nov 07 2004 14:05:54   popescu
 * PET 1117/06, synch changes
 * 
 *    Rev 1.30   Nov 04 2004 17:36:32   popescu
 * PET 1117/06, Trade processing
 * 
 *    Rev 1.29   Sep 21 2004 13:26:18   HERNANDO
 * PET1094 FN06 - Absatzmeldung Files enhancement.
 * 
 *    Rev 1.28   Apr 27 2004 16:02:12   popescu
 * PTS 10029582, 10029578 similar issue, the validation should be done prior to remove the cloned bank lists
 * 
 *    Rev 1.27   Mar 12 2004 13:30:12   popescu
 * PTS 10027880, synch-up release 55.1.0.0, ver 1.23.1.0
 * 
 *    Rev 1.26   Mar 10 2004 13:13:56   HERNANDO
 * PET965 FN11 - Added getHistoricalParameters.
 * 
 *    Rev 1.25   Feb 28 2004 16:11:58   HERNANDO
 * PET965 FN11 - Additional historical enhancement.
 * 
 *    Rev 1.24   Feb 11 2004 15:43:36   popescu
 * PET965.FN1 SSB Profile restriction, added a new method to remove cloned bank lists
 * 
 *    Rev 1.23   Oct 19 2003 18:35:00   popescu
 * CIBC PET 809, FN 13
 * t
 *    Rev 1.22   Oct 19 2003 16:43:20   popescu
 * CIBC, PET809, FN 13 banking work
 * 
 *    Rev 1.21   Aug 07 2003 18:35:42   popescu
 * added new param that will help set the UI selection on the desired bank
 * 
 *    Rev 1.20   Jun 10 2003 16:10:44   popescu
 * Changed the SettlementTrade bank instructions files to match new design for bank instructions that are not on host
 * 
 *    Rev 1.19   Jun 09 2003 17:39:52   popescu
 * Added support for fund and class search, still stopped at the Gui level, because it shouldn't be functional yet; do not know the id for the bank entity when seraching for bank using fund and class
 * 
 *    Rev 1.18   Jun 03 2003 20:58:38   popescu
 * Added the NotOnHost Banking Instructions CBO and List; dummy banks are derived from these objects for common processing
 * 
 *    Rev 1.17   Jun 01 2003 17:07:28   popescu
 * Systematic & Distribution banking work
 * 
 *    Rev 1.16   May 31 2003 20:29:08   popescu
 * RRIF work part ||
 * 
 *    Rev 1.15   May 31 2003 11:54:32   popescu
 * RRIF bank work
 * 
 *    Rev 1.14   May 27 2003 13:13:56   popescu
 * RRIF Banking work
 * 
 *    Rev 1.13   May 22 2003 14:11:26   popescu
 * Replaced name 'BankInstr' with 'BankInstructions'; 
 * simplified child lists getters for the Shareholder object
//
//   Rev 1.19   Mar 21 2003 17:36:28   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.18   Oct 09 2002 23:53:04   PURDYECH
//PVCS Database Conversion
//
//   Rev 1.17   Sep 11 2002 09:50:36   KOVACSRO
//Added m_strUserAccessCode
//
//   Rev 1.16   Aug 29 2002 12:51:52   SMITHDAV
//ClientLocale and typed field changes.
//
//   Rev 1.15   Jun 11 2002 21:27:02   HSUCHIN
//added support for settlement
//
//   Rev 1.14   Jun 07 2002 17:34:32   KOVACSRO
//doValidateAll()
//
//   Rev 1.13   Jun 03 2002 14:13:12   FENGYONG
//override "setCommitDataGroupAsHost" for NASU API
//
//   Rev 1.12   24 May 2002 15:15:30   KOVACSRO
//keeping FundCode.
//
//   Rev 1.11   22 May 2002 18:21:38   PURDYECH
//BFData Implementation
//
//   Rev 1.10   19 Mar 2002 13:15:14   PURDYECH
//Use #pragma once as include guard
//Remove compile time "including..." message
//
//   Rev 1.9   Sep 25 2001 10:42:50   YINGBAOL
//add rrIFkey
//
//   Rev 1.8   11 May 2001 16:33:08   YINGZ
//code sync
//
//   Rev 1.7   03 May 2001 14:03:48   SMITHDAV
//Session management restructuring.
//
//   Rev 1.6   Apr 03 2001 15:48:04   YINGBAOL
//add transactionBankList and it's logic
//
//   Rev 1.5   30 Mar 2001 17:09:20   BUZILAMI
//Systematic bank changes
//
//   Rev 1.4   28 Mar 2001 09:44:40   BUZILAMI
//fix
//
//   Rev 1.3   16 Mar 2001 16:31:48   BUZILAMI
//added m_dstEntityName member variable
//
//   Rev 1.2   07 Mar 2001 15:41:54   BUZILAMI
//Broker, Branch, SlsRep Bank Instructions changes
//
//   Rev 1.1   Feb 22 2001 15:24:34   BUZILAMI
//added search for bank using Broker, Branch and sales Rep
//
//   Rev 1.0   Feb 21 2001 16:01:20   BUZILAMI
//Initial revision.
//
 * 
 */
