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
//    Copyright 1997 by International Financial Data Services
//
//******************************************************************************
//
// ^FILE   : TransactionHistoryProcess.hpp
// ^AUTHOR : Zijian Ying
// ^DATE   : 03/04/1999
//
// ----------------------------------------------------------
//
// ^CLASS    : TransactionHistoryProcess
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :  This is the code for the Transaction Details dialog
//
//******************************************************************************


#include <bfproc\AbstractProcess.hpp>
///#endif

// Forward references
class COANavig;
class FundDetailList;
class PendingTradeList;
class TransactionList;
class TransactionExternalLinksList;
class TransDecimalsList;
class TradeAuthorization;

// Import/Export resolution
#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif

/**
 * Class that manages the entity process.
 *
 * @author 
 * </dd></dl><p><dl><dt><b>Date Created:</b></dt><dd> 03/04/1999</dd></dl>
 * @version 0.1
 */

class IFASTBP_LINKAGE TransHistoryProcess : public AbstractProcess
{
// Construction
public:
   /**
    * Default constructor
    */
//CP20030319   TransHistoryProcess();
   TransHistoryProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand );
   virtual ~TransHistoryProcess();
protected:
   /**
     * Provide class specific implementation for some fields.
     * An exception will be thrown if the field cannot be found.
     * @param rpGICaller - A reference pointer to the calling object.
     * @param idContainer - ID of container we are using.
     * @param idField - ID of field we are getting.
     * @param strValue - A string reference where value is returned.
     * @param bFormatted - Flag where true means get data formatted.
     */
   virtual void doGetField(
                          const GenericInterface *rpGICaller,
                          const BFContainerId& idContainer,
                          const BFFieldId& idField,
                          const BFDataGroupId& idDataGroup,
                          DString &strValueOut,
                          bool bFormatted
                          ) const;
   virtual bool doGetData(
                         GenericInterface * rpGICaller,
                         BFData * 
                         ) const;
   /**
     * Set up the list and get parameters.
     * @returns SEVERITY noting any error/warning conditions
     */
   virtual SEVERITY doInit();
   /**
     * Implementation to support the modelessChildComplete method.
     * modelessChildComplete is used by the GenericInterfaceContainer to tell
     * the parent that the modeless child has been destroyed.
     * @param cmd - A reference to a command representing the object that has
     * been destroyed.
     * @returns true if this modeless object should end as well, false if not
     * done yet.  When returning true, the calling modelessChildComplete method
     * will call GenericInterfaceContainer::modelessDestroySelf to delete and
     * remove this object from the container
     */
   virtual bool doModelessChildComplete(
                                       const Command &cmd
                                       );
   virtual bool doModelessSetFocus(
                                  GenericInterface *rpGICaller
                                  );
   virtual bool doMoreRecordsExist(
                                  GenericInterface *rpGICaller,
                                  const BFContainerId& idContainer
                                  );
   /**
     * Implementation to support the process method.
     * @returns an enum representing the return type
     */
   virtual E_COMMANDRETURN doProcess();
   /**
     * Implementation for the refresh method.  Not implemented yet.
     * @param rpGICaller - A reference pointer to the calling object.
     * @param szOriginalCommand - A string literal representing the original
     * command issuing the refresh (which may provide a hint on whether this
     * object needs to check for refresh).
     * @returns true if successful, call getErrors for errors if false
     */
   virtual bool doRefresh(
                         GenericInterface *rpGICaller,
                         const I_CHAR *szOriginalCommand
                         );
   virtual SEVERITY doSetField(
                              const GenericInterface *rpGICaller,
                              const BFContainerId& idContainer,
                              const BFFieldId& idField,
                              const BFDataGroupId& idDataGroup,
                              const DString& strValue,
                              bool bFormatted
                              );
   virtual void setCurrentListItem(
                                  const GenericInterface *rpGICaller,
                                  const BFContainerId& idList,
                                  const DString& strListItemKey
                                  );

   void * getPtrForContainer( const BFContainerId& idContainer, const BFDataGroupId& idDataGroup );
   SEVERITY getPendingTradeList(PendingTradeList *& pPendingTradeList, int nNumEntry = -1, bool bRefresh = false);

	virtual bool doSend( GenericInterface* rpGICaller, const I_CHAR * szMessage );

private:
   DString tmpClass;
   DString tmpFund;
   DString _AccountNum,_TransId,_ShareholderNum,_FundCode,_ClassCode,_NumEntry,_AllFundMode,
      _Pending,_TransType,_TransNum,_TradeDate,_EntityId, _InquiryOnly, _dstrDisableInvInfo;
   DString _hasPending, _ReqTransId, _ExtTransNum;
   COANavig *_pCOANavig;
   TransactionList *_pTransHistoryList;
   FundDetailList *_pFundDetailList;
   GenericInterface *_rpChildGI;
   TradeAuthorization *_pTradeAuthorization;
	DString _dstrPendingTrade,
      _CallPendigTradeDetails;
   DString DisableMsg;
   DString Reprint;
   DString TxnCancel;
   DString CallFrom;
   DString dstrFromSettlementScreen;
   SEVERITY performSearch( GenericInterface *rpGI, const BFContainerId& idSearch, 
                           E_SEARCHACTION  );

	TransactionExternalLinksList *_pTransactionExternalLinksList;
   TransDecimalsList* _pTransDecimalsList;

   DString 	_PendProcRecordType;
   DString 	_Authorization;
   DString 	_SettleBatch;
   DString  _caller;
   DString  _dstrWireOrder;
};

///#endif 



//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/TransHistoryProcess.hpp-arc  $
 * 
 *    Rev 1.26   Dec 09 2010 15:01:22   jankovii
 * IN 2339013 - P0175778: Uptreaming QA testing
 * 
 *    Rev 1.25   May 28 2009 06:38:16   wutipong
 * IN1608629 - Aimprod RTS error : Disable the settlement button on the trans history dialog only when the dialog is open from settlement dialog. -- Sync Up
 * 
 *    Rev 1.24   May 22 2009 10:28:04   jankovii
 * PET 159770 FN05 Auto Batching.
 * 
 *    Rev 1.23   Mar 02 2009 09:56:12   jankovii
 * PET0159508 FN03 ESG In Cash Transfer 
 * 
 *    Rev 1.22   Aug 29 2006 16:41:34   fengyong
 * PET2192 FN17 - Add from screen parameter
 * 
 *    Rev 1.21   Jul 20 2005 14:02:34   Yingbaol
 * PET1235,FN01:fix refresh issue
 * 
 *    Rev 1.20   May 30 2005 18:01:06   porteanm
 * PET OPC Confirm Reprint - Set Reprint/TxnCancel parameters.
 * 
 *    Rev 1.19   Apr 21 2005 16:33:02   hernando
 * Incident #278666 - Added DString ExtTransNum.  Synchronized with 1.16.1.0
 * 
 *    Rev 1.18   Mar 04 2005 17:08:48   Fengyong
 * PET1190 FN04 - TransCancel Tempery check in for other coder
 * 
 *    Rev 1.17   Mar 03 2005 14:33:12   aguilaam
 * PET1171_FN01: display view 330 details on Transaction Detail screen (history) EUSDSavings - others
 * 
 *    Rev 1.16   Feb 22 2005 16:28:38   hernando
 * PET1117 FN66-68 - Added DisableMsg parameter.
 * 
 *    Rev 1.15   Dec 21 2004 18:11:34   popescu
 * PET 1117/56, fixed call to pending trades details view 54 when dialog is launched.
 * 
 *    Rev 1.14   Sep 16 2004 09:35:28   VADEANUM
 * PET 1094 FN4 - Activest Bank File Interface.
 * 
 *    Rev 1.13   May 18 2004 11:33:16   HERNANDO
 * PET1046 FN01 - Added disableInvInfo parameter.
 * 
 *    Rev 1.12   Feb 16 2004 11:01:52   ZHANGCEL
 * PTS 10026640 : added a paramer for the pending trade checking
 * 
 *    Rev 1.11   Feb 04 2004 17:03:30   VADEANUM
 * PET 859 FN23 - ADL - Deductions Details.
 * 
 *    Rev 1.10   Mar 21 2003 17:49:44   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.9   Mar 03 2003 09:41:30   KOVACSRO
 * Added _InquiryOnly
 * 
 *    Rev 1.8   Oct 09 2002 23:53:42   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.7   Aug 29 2002 12:53:58   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.6   13 Jun 2002 14:40:44   YINGZ
 * add reqtransid to support settlement
 * 
 *    Rev 1.5   22 May 2002 18:19:14   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.4   19 Mar 2002 13:19:04   PURDYECH
 * Use #pragma once as include guard
 * Remove compile time "including..." message
 * 
 *    Rev 1.3   Jan 24 2001 12:56:54   KOVACSRO
 * Added getPtrForContainer() and getPendingTradesList()
 * 
 *    Rev 1.2   Aug 02 2000 15:31:52   BUZILA
 * "locale" changes
 * 
 *    Rev 1.1   Feb 15 2000 18:56:54   MCNABBGL
 * changed comment format
 * 
 *    Rev 1.0   Feb 15 2000 10:59:26   SMITHDAV
 * Initial revision.
 * 
 *    Rev 1.7   Dec 07 1999 14:20:02   YINGZ
 * add group to doset/get fiels
 * 
 *    Rev 1.6   Nov 02 1999 15:20:36   DT24433
 * removed doOk/doCancel
 * 
 *    Rev 1.5   Sep 27 1999 13:55:54   YINGZ
 * add dosetfield
 * 
 *    Rev 1.4   Aug 31 1999 12:23:52   DT24433
 * changed dogetfield parms
 * 
 *    Rev 1.3   Jul 30 1999 14:04:32   YINGZ
 * grey pending when there is no pending
 * 
 *    Rev 1.2   Jul 22 1999 14:59:28   YINGZ
 * process amount and units in pending
 * 
 *    Rev 1.1   Jul 08 1999 10:04:02   SMITHDAV
 * Modify revision history commaent format to old
 * style comment -- I can't seem to get new style comments to work.
 *
 */
