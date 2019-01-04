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
//    DATE   : July, 2004
//
//
//    Copyright 2000 by DST Systems, Inc.
//
//******************************************************************************

#include <bfproc\abstractprocess.hpp>

#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif

//Forward declarations
class MFAccount;
class PendingTradeList;
class SplitCommissionList;
class TransFee;
class WorksessionTradesList;

class IFASTBP_LINKAGE TradesProcess : public AbstractProcess
{
// Construction
public:
   TradesProcess ( GenericInterfaceContainer* pGIC, 
                   GenericInterface* pGIParent, 
                   const Command &rCommand);
   virtual ~TradesProcess();   
protected:
   virtual SEVERITY doInit();
   virtual E_COMMANDRETURN doProcess();
   virtual bool doOk (GenericInterface *rpGICaller);
   virtual bool doCancel (GenericInterface *rpGICaller);
   virtual void doPostOk ( GenericInterface *rpGICaller, 
                           bool bSuccessFlag);
   virtual SEVERITY deleteItemFromList ( const GenericInterface *rpGICaller,
                                         const BFContainerId& idList);
   virtual SEVERITY doSetField ( const GenericInterface *rpGICaller, 
                                 const BFContainerId &idContainer, 
                                 const BFFieldId &idField, 
                                 const BFDataGroupId &idDataGroup, 
                                 const DString &strValue, 
                                 bool bFormatted);
   virtual void doGetField ( const GenericInterface *rpGICaller,  
                             const BFContainerId &idContainer, 
                             const BFFieldId &idField, 
                             const BFDataGroupId &idDataGroup, 
                             DString &strValueOut, 
                             bool bFormtted) const;
   virtual SEVERITY doGetErrors ( const GenericInterface *rpGICaller,
                                  const BFContainerId &idContainer,
                                  const BFFieldId &idField,
                                  const BFDataGroupId &idDataGroup,
                                  CONDITIONVECTOR &conditions ) const;
   virtual const BFProperties *doGetFieldAttributes ( const GenericInterface *rpGICaller, 
                                                      const BFContainerId &idContainer, 
                                                      const BFFieldId &idField, 
                                                      const BFDataGroupId &idDataGroup);

   virtual bool doRegisterObserver ( const GenericInterface *rpGICaller,
                                     const BFContainerId &idContainer,
                                     const BFFieldId &idField,
                                     const BFDataGroupId &idDataGroup,
                                     BFObserver &rpObserver);
   virtual bool doSend ( GenericInterface *rpGICaller, 
                         const I_CHAR *szMessage);
   virtual bool doModelessChildComplete (const Command &cmd);
   virtual bool doModelessSetFocus (GenericInterface *rpGICaller);
   virtual const DString& getFirstListItemKey ( const GenericInterface *rpGICaller, 
                                                const BFContainerId &idList);
   virtual const DString& getNextListItemKey ( const GenericInterface *rpGICaller, 
                                               const BFContainerId &idList);
   virtual void *getPtrForContainer ( const BFContainerId &idContainer, 
                                      const BFDataGroupId &idDataGroup);
   virtual SEVERITY performSearch ( GenericInterface *rpGICaller,
                                    const BFContainerId &idSearch,
                                    E_SEARCHACTION eSearchAction );
   virtual void setCurrentListItem( const GenericInterface *rpGICaller,
                                    const BFContainerId& idList,
                                    const BFData* pKeyInfo);
private:
// Class used as key in conditions/properties map
   class TKey
   {
   public:
      DString _tradeKey;
      BFContainerId _idContainer;
      BFFieldId _idField;
      BFDataGroupId _idDataGroup;

      TKey (const DString &tradeKey, 
            const BFContainerId &idContainer, 
            const BFFieldId &idField,
            const BFDataGroupId &idDataGroup) :
      _tradeKey (tradeKey),
      _idContainer (idContainer),
      _idField (idField),
      _idDataGroup (idDataGroup)
      {}
   };

   // Class used for comparison of key in map
   class less_TKey
   {
   public:
      bool operator() (const TKey &a, const TKey &b) const
      {
         if (a._tradeKey != b._tradeKey)
         {
            return (a._tradeKey < b._tradeKey);
         }
         else if (a._idContainer != b._idContainer)
         {
            return (a._idContainer < b._idContainer);
         }
         else if (a._idField != b._idField)
         {
            return (a._idField < b._idField);
         }
         else
         {
            return (a._idDataGroup < b._idDataGroup);
         }
      }
   };

   typedef std::map <TKey, CONDITIONVECTOR*, less_TKey> CONDITIONS_MAP;
   typedef std::map <TKey, DString, less_TKey> VALUES_MAP;

   SEVERITY addTrade (const GenericInterface *rpGICaller);
   SEVERITY modifyTrade ( const GenericInterface *rpGICaller, 
                          const DString &accountNum,
                          bool bReqRefresh = false);
   void removeCurrentTradeDataFromMaps();
   void removeConditions (const TKey &tKey);
   bool isAccountSetAndValid ( const BFContainerId &idContainer,
                               const BFDataGroupId &idDataGroup);
   bool isOneSideTrade ();
   void setAccountSearchFieldFromAccount ( const BFContainerId &idContainer, 
                                           const BFFieldId &idField);
   SEVERITY processParameters ();
   SEVERITY findCorrespondingTransFee ( TransFee *&pTransFee, 
                                        const BFFieldId &idField) const;

//a map of conditions   
   CONDITIONS_MAP _conditionsMap;
//a map of values
   VALUES_MAP _valuesMap;

   GenericInterface *_rpChildGI;
   WorksessionTradesList *_pTradesList;
   PendingTradeList *_pPendingTrades;
   SplitCommissionList *_pSplitCommissionList;
   DString _accountNum,
      _aggregatedOrderTradeDate,
      _currentBusinessDate,
      _listKey,
      _caller,
      _isCancelHitOnVerifySearch,
      _track,
      _activity,
      _sameAccountTransType,
      _transNum,
      _reset,
      _rebookExist,
      _fromfund,
      _fromclass,
      _batch;
   bool _bIsARollover;
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/TradesProcess.hpp-arc  $
 * 
 *    Rev 1.51   Apr 14 2010 23:56:16   popescu
 * PET165541_FN01_QESI - RESP Gap_Dsk_Trading
 * 
 *    Rev 1.50   Nov 16 2009 13:53:44   popescu
 * Incident 1891982 - rebook
 * 
 *    Rev 1.49   Sep 30 2009 06:54:28   dchatcha
 * IN# 1595165 - Rebooking functionality where contr rcpt was issued not working properly.
 * 
 *    Rev 1.48   May 27 2009 15:13:46   jankovii
 * PET 159770 FN05 Auto Batching.
 * 
 *    Rev 1.47   Sep 06 2007 17:19:04   popescu
 * GAP 18 - added manual management fee rebate to manual dividend screen
 * 
 *    Rev 1.46   Feb 07 2006 11:29:44   AGUILAAM
 * IN 534395 - fixed rebook for management fee (AF91) where multiple trades are linked to one transnum; match exact trade with fund/class.
 * 
 *    Rev 1.45   Sep 08 2005 12:59:20   popescu
 * Incident# 398841 - activated rebook for rollovers
 * 
 *    Rev 1.44   Aug 29 2005 10:42:46   popescu
 * Incident 390388 - wire order number should be blanked out for multiple rebooks
 * 
 *    Rev 1.43   Aug 17 2005 11:45:52   popescu
 * PET 1235/01 rebook and cancelation - cleaned the code, 
 * 
 *    Rev 1.42   Jul 08 2005 09:38:16   Yingbaol
 * PET1235,FN01:cancellation rebook
 * 
 *    Rev 1.41   Jun 13 2005 18:46:16   popescu
 * Incident # 332227 - fixed trade entry crash  for allocated orders with composed of funds with and/or without split commissions.
 * 
 *    Rev 1.40   May 30 2005 22:53:40   popescu
 * Incident # 301110 - synch-up from 61
 * 
 *    Rev 1.39   May 30 2005 22:48:36   popescu
 * Incident # 301110 - reversed the old fix; updated the effective date on the trade entry screen for new trades only if user changes the default value of it. Otherwise is up to view 127 to determine the correct date. - synch-up from 61
 * 
 *    Rev 1.38   May 30 2005 22:47:02   popescu
 * Incident# 317930 - fixed TradeDate display issue for aggregated orders- backed old ifx out
 * 
 *    Rev 1.37   May 27 2005 17:04:06   Fengyong
 * #Incident 317930 - Add copyfromparent function
 * 
 *    Rev 1.36   Feb 18 2005 16:57:52   popescu
 * Incident #237786, fixed refresh data flickering issue, synch-up from Release 59.0.4
 * 
 *    Rev 1.35   Jan 29 2005 19:27:44   popescu
 * PET 1117. 66. added fields API
 * 
 *    Rev 1.34   Jan 21 2005 15:30:14   popescu
 * PET 1117/06, API pending trade mods
 * 
 *    Rev 1.33   Jan 13 2005 17:36:36   popescu
 * PET 1117/06, API further changes
 * 
 *    Rev 1.32   Dec 08 2004 17:49:54   popescu
 * PET 1117/56, modify an aggregated order's pending trades list
 * 
 *    Rev 1.31   Dec 01 2004 19:50:16   popescu
 * PET 1117/06, trades/fees processing, incorporate fees in trades transaction builder, and added method to copy fee values onto the trades fee fields for cycle processing
 * 
 *    Rev 1.30   Nov 22 2004 13:08:48   popescu
 * PET 1117/56. fees processing
 * 
 *    Rev 1.29   Nov 19 2004 14:19:50   popescu
 * PET 1117/06, fees processing
 * 
 *    Rev 1.28   Nov 15 2004 13:21:14   popescu
 * PET 1117/06, .NET synch changes
 * 
 *    Rev 1.27   Nov 07 2004 14:06:26   popescu
 * PET 1117/06, synch changes
//
//   Rev 1.4   Nov 04 2004 17:36:52   popescu
//PET 1117/06, Trade processing
//
//   Rev 1.3   Oct 27 2004 11:26:46   popescu
//PET 1117/06
//
//   Rev 1.2   Oct 21 2004 06:28:56   popescu
//PET 1117/06 - Trade processing work in progress..
//
//   Rev 1.1   Oct 01 2004 19:25:30   popescu
//PET 1117/06, SSB Germany Trade processing
//
//   Rev 1.0   Aug 13 2004 18:56:04   popescu
//Initial revision.
 * 
// 
*/
