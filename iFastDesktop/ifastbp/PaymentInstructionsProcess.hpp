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
//    AUTHOR : Serban Popescu
//    DATE   : June 2003
//
//
//    Copyright 1997 by DST Systems, Inc.
//
//******************************************************************************

#include <bfproc\abstractprocess.hpp>
#include <ifastbp\ifasthistoricalparameters.hpp>


// Import/Export resolution
#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif

//Forward declarations
class PaymentInstructionsList;
class DistributorBankInstructionsList;
class BankInstructionsList;

class IFASTBP_LINKAGE PaymentInstructionsProcess : public AbstractProcess,
   public IFastHistoricalParameters
{
// Construction
public:
   PaymentInstructionsProcess(GenericInterfaceContainer* pGIC, 
      GenericInterface* pGIParent, const Command& rCommand);
   virtual ~PaymentInstructionsProcess();
protected:
   virtual SEVERITY doInit();
   virtual E_COMMANDRETURN doProcess();
   virtual bool doModelessChildComplete(const Command &cmd);
   virtual SEVERITY performSearch ( GenericInterface *rpGI, 
                                    const BFContainerId& idSearch, 
                                    E_SEARCHACTION eSearchAction);
   virtual bool doMoreRecordsExist ( GenericInterface *rpGICaller,
                                     const BFContainerId& idSearch);
   virtual bool doRefresh ( GenericInterface *rpGICaller, 
                            const I_CHAR *szOriginalCommand)
   {
      return true;
   }
   virtual void doGetField(const GenericInterface *rpGICaller,
      const BFContainerId& idContainer, const BFFieldId& idField,
      const BFDataGroupId& idDataGroup, DString &strValueOut,
      bool bFormatted) const;
   virtual SEVERITY doSetField(const GenericInterface *rpGICaller,
      const BFContainerId& idContainer, const BFFieldId& idField,
      const BFDataGroupId& idDataGroup, const DString& strValue,
      bool bFormatted);
   virtual SEVERITY doValidateAll(BFAbstractCBO *rpWSD,
      const BFDataGroupId &idDataGroup);
   void *getPtrForContainer(const BFContainerId &idContainer,
      const BFDataGroupId &idDataGroup);
   virtual bool doModelessSetFocus(GenericInterface *rpGICaller);
   virtual SEVERITY getHistoricalParameters(const BFContainerId& idContainer,
      BFFieldId &recordIdField, DString& tableId, DString& dstrKeys);
   SEVERITY getHistoricalParameters( const BFContainerId& idContainer, HISTORICAL_VECTOR &vectorInput );

private:
   GenericInterface *_rpChildGI;
   DString _dstrBrokerCode,
      _dstrBranchCode,
      _dstrSlsRepCode,
      _dstrPayToEntity,
      _dstrPaymentFor,
		_dstrSearchTypeMgmt;
		
   PaymentInstructionsList *_pPaymentInstructionsList;
   BankInstructionsList *_pBankInstructionsList;
   BankInstructionsList *_pDummyBankInstructionsList;
   bool isPaymentInstructionsListNotEmptyAfterFiltering();
   bool isBankingAllowed() const;
   SEVERITY processParameters();
};


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/PaymentInstructionsProcess.hpp-arc  $
//
//   Rev 1.10   Sep 10 2006 17:57:54   popescu
//STP 2192/12
//
//   Rev 1.9   Jul 27 2006 17:57:42   ZHANGCEL
//PET2192 FN11 - Commission Payments to MgmtCo related changes
//
//   Rev 1.8   Mar 10 2004 13:18:18   HERNANDO
//PET965 FN11 - Added getHistoricalParameters.
//
//   Rev 1.7   Aug 19 2003 10:24:04   HERNANDO
//Added keys to getHistoricalParameters.
//
//   Rev 1.6   Jul 31 2003 21:58:58   popescu
//Added support for PayType 'X' and support for Historical Info at the process level
//
//   Rev 1.5   Jul 26 2003 19:39:00   popescu
//the refresh of the banking list didn't work properly in some cases, 
//
//   Rev 1.4   Jul 25 2003 14:26:08   popescu
//Fix crash in payment instructions dialog, as result of filtering the payment instructions list, cleared the address fields when the checque option is selected for the payment method
//
//   Rev 1.3   Jul 23 2003 18:20:36   popescu
//Capitalized the parameters
//
//   Rev 1.2   Jul 09 2003 21:56:36   popescu
//Payment Instructiuons work, business rules implementation SSB_PET_821_FN17
//
//   Rev 1.1   Jul 02 2003 17:49:30   popescu
//work for payment instructions feature 
//
//   Rev 1.0   Jul 01 2003 18:12:14   popescu
//Initial revision.
//
//   Rev 1.0   Jun 27 2003 18:15:20   popescu
//Initial revision.
 *
 */
