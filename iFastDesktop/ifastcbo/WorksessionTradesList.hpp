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
//    Copyright 2000 by DST Systems, Inc.
//
//
//******************************************************************************
//
// ^FILE   : WorksessionTradesList.hpp
// ^AUTHOR : Serban Popescu
// ^DATE   : September 2004
//
// ^CLASS    : WorksessionTradesList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include <ifastcbo\mfcancbo.hpp>
#include <boost\utility.hpp>

class PendingTradeDetails;
class TransactionDetails;
class ErrMsgRulesList;
class Trade;

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

//Forward declarations

class IFASTCBO_LINKAGE WorksessionTradesList : public MFCanBFCbo, private boost::noncopyable
{
public:
   static void buildKey ( const DString &accountNum,
                          const DString &transNum,
                          DString &strKey);
public:
   WorksessionTradesList( BFAbstractCBO &parent );
   virtual ~WorksessionTradesList();

   SEVERITY init ( const BFDataGroupId &idDataGroup, 
                   const DString &dstrTrack = I_("N"),
                   const DString &dstrPageName = NULL_STRING);
   SEVERITY fromPending2Trade ( PendingTradeDetails *pPendingTrade,
                                const BFDataGroupId &idDataGroup,
                                bool bReqRefresh,
                                DString &strNewKey,
                                bool bSameAccount = false,
                                bool bRebook = false,
                                bool bMultipleRebook = false,
                                bool bIsARollover = false,
                                const DString &rebookBatch = NULL_STRING,
                                bool bRefund = false);

   SEVERITY fromHistory2Trade ( TransactionDetails *pHistoryTrade,
                                const BFDataGroupId &idDataGroup,
                                bool bReqRefresh,
                                DString &strNewKey,
                                bool bSameAccount = false,
                                bool bRebook = false,
                                bool bMultipleRebook = false,
                                bool bIsARollover = false,
                                const DString &rebookBatch = NULL_STRING,
                                bool bRefund = false);

   void setManualTrades (bool bManualTrades);
   void setBatchName (const DString &batchName)
   {
      _batchName = batchName;
   }
   DString getBatchName () 
   {
      return _batchName;
   }
   bool getDuplicateTrade ()
   {
	   return m_bDuplicateTrade;
   }
   SEVERITY getErrMsgValue( DString dstrErrNum,       
	   const BFDataGroupId& idDataGroup, 
	   DString& dstrErrValue ) ;
   SEVERITY checkDuplicate ( Trade *pTrade, 
                             const BFDataGroupId &idDataGroup);
   virtual void getField ( const BFFieldId &idField, 
                           DString &fieldValue, 
                           const BFDataGroupId &idDataGroup, 
                           bool formattedReturn = false) const;
   bool isTradeAdded ( const DString &tradeKey,
                       const BFDataGroupId &idDataGroup);

protected:
   virtual SEVERITY doCreateObject (const BFData &data, BFCBO *&pObjOut);
   virtual SEVERITY doCreateNewObject (BFCBO *&pBase, DString &strKey, const BFDataGroupId &idDataGroup);
   virtual SEVERITY doValidateAll (const BFDataGroupId &idDataGroup, long lValidateGroup);
   virtual SEVERITY doApplyRelatedChanges ( const BFFieldId &idField, 
                                            const BFDataGroupId &idDataGroup);
   virtual void getStrKey (DString &strKey, const BFData *data = NULL);
   virtual void getStrKeyForNewItem (DString & strKey);
private:
   DString calculatePurchaseTotal (const BFDataGroupId &idDataGroup);
   Trade *makeTrade ( const DString &transType,
                      const BFDataGroupId &idDataGroup);
   SEVERITY fromPending2Trade ( PendingTradeDetails *pPendingTrade, 
                                BFData *data, 
                                const BFDataGroupId &idDataGroup);
   SEVERITY fromHistory2Trade ( TransactionDetails *pHistoryTrade, 
                                BFData *data, 
                                const BFDataGroupId &idDataGroup);

   DString _track,
           _pageName;
   bool _bRebook,
        _bIsARollover,
        _bManualTrades,
        _bFromHistory;
   bool _bRefund;
   DString _batchName;
   bool m_bDuplicateTrade;
   ErrMsgRulesList* _pErrMsgRulesList;
};

//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastcbo/WorksessionTradesList.hpp-arc  $
//
//   Rev 1.38   Sep 30 2009 06:51:12   dchatcha
//IN# 1595165 - Rebooking functionality where contr rcpt was issued not working properly.
//
//   Rev 1.37   May 27 2009 15:11:46   jankovii
//PET 159770 FN05 Auto Batching.
//
//   Rev 1.36   May 20 2009 11:04:34   jankovii
//PET 159770 FN05 Auto Batching.
//
//   Rev 1.35   17 Jul 2008 14:24:42   kovacsro
//PET5517 FN60C Cancellation of Contribution Receipts - Rebooking
//
//   Rev 1.34   17 Jul 2008 10:58:18   kovacsro
//PET5517 FN60C Cancellation of Contribution Receipts - Rebooking
//
//   Rev 1.33   Sep 06 2007 17:21:12   popescu
//GAP 18 - added manual management fee rebate to manual dividend screen
//
//   Rev 1.32   Sep 08 2005 12:59:26   popescu
//Incident# 398841 - activated rebook for rollovers
//
//   Rev 1.31   Aug 29 2005 10:42:56   popescu
//Incident 390388 - wire order number should be blanked out for multiple rebooks
//
//   Rev 1.30   Aug 11 2005 10:26:40   popescu
//PET 1235 - Reeebok, few changes
//
//   Rev 1.29   Jul 08 2005 09:34:36   Yingbaol
//PET1235,FN01:transaction cancellation rebook
//
//   Rev 1.28   May 30 2005 22:40:40   popescu
//Incident# 317930 - backed fix out
//
//   Rev 1.27   May 27 2005 16:59:36   Fengyong
//#Incident 317930 - Add init Exist function
//
//   Rev 1.26   Jan 07 2005 19:05:16   popescu
//PTS 10037553, fixed issues with modifying pending trades 
//
//   Rev 1.25   Jan 06 2005 13:57:52   popescu
//PTS 10037503, trade object set to be dirty immediate after being created
//
//   Rev 1.24   Dec 16 2004 19:06:38   popescu
//PET 1117/06, fixes for the case were account nums are invalid, or becomming invalid due to a change in Trade's context. Also, fixes for the order of keys when adding new trade
//
//   Rev 1.23   Dec 08 2004 17:50:18   popescu
//PET 1117/56, modify an aggregated order's pending trades list
//
//   Rev 1.22   Nov 30 2004 20:10:40   popescu
//PET 1117/06
//
//   Rev 1.21   Nov 30 2004 07:53:36   popescu
//PET 1117/06, made purchase total and OnBtnHistory active once again
//
//   Rev 1.20   Nov 22 2004 13:09:52   popescu
//PET 1117/56. fees processing
//
//   Rev 1.19   Nov 14 2004 14:59:32   purdyech
//PET910 - .NET Conversion
//
//   Rev 1.18   Nov 06 2004 00:43:28   popescu
//PET 1117/06, synch changes
//
//   Rev 1.4   Nov 04 2004 17:41:54   popescu
//PET 1117/06, Trade processing
//
//   Rev 1.3   Nov 02 2004 19:19:44   popescu
//PET 1117/06 Trade processing...
//
//   Rev 1.2   Oct 28 2004 18:24:02   popescu
//PET 1117/06
//
//   Rev 1.1   Oct 21 2004 06:29:40   popescu
//PET 1117/06 - Trade processing work in progress..
//
//   Rev 1.0   Oct 01 2004 19:30:10   popescu
//Initial revision.
//
//   Rev 1.17   Jul 22 2004 13:46:08   HERNANDO
//PTS 10032389 - Recovered doPreSetField.
//
//   Rev 1.16   May 17 2004 18:10:54   popescu
//PET 985, FN 01, LSIF Trade Entry
//
//   Rev 1.15   May 14 2004 17:38:20   popescu
//PET 905, fn 01, LSIF trade entry
//
//   Rev 1.14   Jan 13 2004 16:07:00   popescu
//PET 910, System Integration Testing, Rel_55.0.0.2
//Fix involved allows back dated trades when modifying a pending trade; issue occurred due to a previous fix where the WorksessionTradesList is now retrieved using an 'idDataGroup' not equal with BF::HOST.
//
//   Rev 1.13   May 27 2003 18:30:14   popescu
//due to several memory leaks found in some list getters at the DSTCWorkSession level caused by copy/paste, I've created a common template function to retrieve the dependent objects
//
//   Rev 1.12   Mar 21 2003 18:28:46   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.11   Oct 09 2002 23:55:16   PURDYECH
//PVCS Database Conversion
//
//   Rev 1.10   Aug 29 2002 12:54:04   SMITHDAV
//ClientLocale and typed field changes.
//
//   Rev 1.9   24 May 2002 15:04:52   KOVACSRO
//doPresetField changes.
//
//   Rev 1.8   22 May 2002 18:18:34   PURDYECH
//BFData Implementation
//
