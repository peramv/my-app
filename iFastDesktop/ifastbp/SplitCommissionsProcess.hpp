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
//******************************************************************************


#include <bfproc\abstractprocess.hpp>

// Forward references
class MFAccount;
class Trade;
class Systematic;
class TradeFundAllocList;
class TransactionList;
class SplitCommissionList;
class SysAllocationList;
class AutoTransAllocationList;
class MatchTransferList;

// Import/Export resolution
#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif

class IFASTBP_LINKAGE SplitCommissionsProcess : public AbstractProcess
{
// Construction
public:
   SplitCommissionsProcess (GenericInterfaceContainer* pGIC, 
      GenericInterface* pGIParent, const Command& rCommand);
   virtual ~SplitCommissionsProcess();

protected:
   virtual void doGetField(const GenericInterface *rpGICaller,
      const BFContainerId& idContainer,
      const BFFieldId& idField,
      const BFDataGroupId& idDataGroup,
      DString &strValueOut,
      bool bFormatted) const;
   virtual SEVERITY doInit();
   virtual bool doModelessChildComplete(const Command &cmd);
   //virtual bool doModelessSetFocus(GenericInterface *rpGICaller);
   //bool doOk( GenericInterface *rpGICaller );
   virtual E_COMMANDRETURN doProcess();
   void *getPtrForContainer(const BFContainerId& idContainer, 
      const BFDataGroupId& idDataGroup);
   const DString& getNextListItemKey( const GenericInterface *rpGICaller, 
      const BFContainerId& idList );
   const DString& getFirstListItemKey( const GenericInterface *rpGICaller, 
      const BFContainerId& idList );
   void  setCurrentListItem(const GenericInterface *rpGICaller, 
      const BFContainerId& idList, const DString& strListItemKey );
   SEVERITY doValidateAll(BFAbstractCBO *rpWSD, const BFDataGroupId& idDataGroup);
   virtual void doPostOk( GenericInterface *rpGICaller, bool bSuccessFlag );
private:
   template <class _X>
      void setSplitCommissionListPtr(const _X*, BFCBO* pParentList, 
         const DString& strListItemKey);
template <class _X> 
   void setTradeFundAllocListPtr(const _X*, BFCBO* pMainList);
   GenericInterface *_rpChildGI;
   MFAccount *_pMFAccount;
   SplitCommissionList *_pSplitCommissionList;
   TradeFundAllocList *_pFundAllocationList;
   TransactionList *_pTransactionList;
   SysAllocationList *_pSysAllocationList;
   AutoTransAllocationList *_pAutoTransAllocationList;
   MatchTransferList *_pMatchTransferList;
   Trade *_pTrade;
   Systematic *_pSystematic;
   DString _dstrAccountNum,
      _dstrCaller, 
      _dstrMainListKey,
      _dstrTransactionNumber,
      _dstrTransactionTypeDesc,
      _dstrMatchTransactionId,
      _dstrCurrentKeyInParentList,
      _dstrAllocationListKey,
      _dstrSplitCommListKey,
	  _dstrFeeType;
}; 


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/SplitCommissionsProcess.hpp-arc  $
//
//   Rev 1.31   Mar 04 2011 12:04:40   jankovii
//PET181943 FN01 - XMLPhase 2
//
//   Rev 1.30   Nov 27 2004 21:21:12   popescu
//PET 1117/06, trades processing
//
//   Rev 1.29   Nov 07 2004 14:06:24   popescu
//PET 1117/06, synch changes
//
//   Rev 1.28   Nov 04 2004 17:36:38   popescu
//PET 1117/06, Trade processing
//
//   Rev 1.27   May 16 2003 17:22:52   popescu
//move the ownership of split commission at the trade fund alloc level
//
//   Rev 1.26   May 15 2003 11:39:06   popescu
//Fix system crash in TransactioAllocationDialog with split commission
//
//   Rev 1.25   May 14 2003 11:15:46   popescu
//added extra param to the process layer, which is used to pass the key string of the current selected item in the allocations list, in order to set selection on it in split commission dialog
//
//   Rev 1.24   May 13 2003 10:05:02   popescu
//Split commission re-work
//
//   Rev 1.23   Apr 05 2003 16:11:00   popescu
//Moved setting the Fee field inTrade & Systematic into the SplitCommisionProcess
//
//   Rev 1.22   Apr 04 2003 15:58:58   popescu
//split commsion work for Systematic
//
//   Rev 1.21   Mar 21 2003 17:48:24   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.20   Oct 09 2002 23:53:38   PURDYECH
//PVCS Database Conversion
//
//   Rev 1.19   Aug 29 2002 12:53:42   SMITHDAV
//ClientLocale and typed field changes.
//
//   Rev 1.18   Jun 03 2002 16:55:12   HSUCHIN
//bug fix to doValidateAll to use BFAbstractCBO rather than BFCBO
//
//   Rev 1.17   22 May 2002 18:19:42   PURDYECH
//BFData Implementation
//
//   Rev 1.16   29 Apr 2002 16:05:52   KOVACSRO
//Added new trade allocations.
//
//   Rev 1.15   19 Mar 2002 13:18:34   PURDYECH
//Use #pragma once as include guard
//Remove compile time "including..." message
//
//   Rev 1.14   08 Feb 2002 10:36:08   HSUCHIN
//added DString variable dstrInquiry to support inquiry mode from trade dialog
//
//   Rev 1.13   07 Oct 2001 16:30:48   HSUCHIN
//undo last changes
//
//   Rev 1.11   Aug 16 2001 13:23:56   ZHANGCEL
//Added content for MatchTransfer
//
//   Rev 1.10   11 May 2001 16:33:10   YINGZ
//code sync
//
//   Rev 1.9   03 Apr 2001 20:23:28   HSUCHIN
//added extra keys to store list information from trade
//
//   Rev 1.8   01 Apr 2001 09:50:34   HSUCHIN
//added ATSysAllocation hook up (doesn't work yet)
//
//   Rev 1.7   Mar 21 2001 13:30:10   HSUCHIN
//more improvements and bug fix
//
//   Rev 1.6   Mar 20 2001 15:40:44   HSUCHIN
//minor code cleanup
//
//   Rev 1.5   Mar 18 2001 17:51:44   HSUCHIN
//check in for winnie
//
//   Rev 1.4   Mar 18 2001 11:52:06   HSUCHIN
//additioanl features and support
//
//   Rev 1.3   Mar 13 2001 09:15:40   HSUCHIN
//Check in for Zijian
//
//   Rev 1.2   Mar 09 2001 13:11:20   HSUCHIN
//bug fix and check in for inquiry test
//
//   Rev 1.1   Mar 08 2001 15:25:54   HSUCHIN
//check in for Ulli
//
// 
 *
 */
