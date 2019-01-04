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

#include <bfproc\AbstractProcess.hpp>
///#endif

// Forward references
class MFAccount;
class Shareholder;
class SystematicList;
class SysAllocationList;
class FundDetailList;
class RRIF_LIF_LRIF_InfoList;
class WorksessionTradesList;
//class ShrAllocTypeList;
//class AcctAllocList;
//class FundAllocList;
class AutoAcctTransAllocationList;
class AutoTransAllocationList;

// Import/Export resolution
#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif

/**
 * Class that manages the Allocations process.
 *
 * @author Yakov Prager
 * </dd></dl><p><dl><dt><b>Date Created:</b></dt><dd> 03/09/1999</dd></dl>
 * @version 0.1
 */

class IFASTBP_LINKAGE AllocationsProcess : public AbstractProcess
{
// Construction
public:
   /**
    * Default constructor
    */
//CP20030319   AllocationsProcess();
   AllocationsProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand );
   virtual ~AllocationsProcess();
   bool hasFrontEndLoadCommission();

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

   SEVERITY doSetField(
                      const GenericInterface *rpGICaller, 
                      const BFContainerId& idContainer, 
                      const BFFieldId& idField, 
                      const BFDataGroupId& idDataGroup, 
                      const DString& strValue, 
                      bool bFormatted
                      );
   SEVERITY doGetErrors( const GenericInterface *rpGICaller, const BFContainerId& idContainer,
                         const BFFieldId& idField, const BFDataGroupId& idDataGroup, CONDITIONVECTOR &conditions ) const;
   const BFProperties * doGetFieldAttributes( const GenericInterface *rpGICaller, const BFContainerId& idContainer, const BFFieldId& idField, const BFDataGroupId& idDataGroup );

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
   virtual bool doModelessChildComplete( const Command &cmd );
   /**
      * Used to bring a modeless dialog (via parent process) to the top of the
      * window stack.
      * @param rpGICaller - A reference pointer to the calling object.
      * @returns true if successful, check conditions if false
      */
   virtual bool doModelessSetFocus( GenericInterface *rpGICaller );
   /**
      * This method implements the base functionality for refresh processing.
      * Basically, this method will check all containers to see if update
      * level has changed. If so, refresh will be invoked on associated child
      * GUI's.
      * This should be overridden if the derived class needs something else.
      * @param rpGICaller - A reference pointer to the calling object.
      * @param szOriginalCommand - A string literal representing the original
      * command issuing the refresh (which may provide a hint on whether this
      * object needs to check for refresh).
      * @returns true if successful, check conditions if false
      */
   virtual bool doRefresh( GenericInterface *rpGICaller,
                           const I_CHAR *szOriginalCommand );
   /**
     * Implementation to support the process method.
     * @returns an enum representing the return type
     */
   virtual E_COMMANDRETURN doProcess();
   /**
      * This method may be overridden if the derived process needs a chance to
      * process prior to the normal ok (ok2) processing.
      * @param rpGICaller - A reference pointer to the calling GenericInterface.
      * @return true if successful causing ok processing to continue or false to 
      * halt ok processing.
      */
   virtual bool doOk( GenericInterface *rpGICaller );
   /**
      * This method is used to implement subclass overrides for validateAll
      * during ok2 processing.  The method implementation must not use a 
      * MAKEFRAME, or should make sure all conditions are promoted to its frame
      * prior to returning.
      * @param rpWSD - WorkSessionDetails pointer
      * @param idDataGroup - group ID to use for CBO processing
      * @returns SEVERITY indicating any errors/warnings encountered.
      */
   virtual SEVERITY doValidateAll( BFAbstractCBO *rpWSD, const BFDataGroupId& idDataGroup );
   virtual void doPostOk ( GenericInterface *rpGICaller, 
                           bool bSuccessFlag
                         );
   /**
      * This method is used (typically by a GUI object) to delete the current
      * item from a list.
      * An exception will be thrown if the list or item could not be found.
      * See note about lists in class document block.
      * @param rpGICaller - A reference pointer to the calling object.
      * @param idList - ID of list we are using.
      * @returns highest SEVERITY encountered, check conditions.
      */
   virtual SEVERITY deleteItemFromList( const GenericInterface *rpGICaller, const BFContainerId& idList );

   void *getPtrForContainer( const BFContainerId& idContainer, const BFDataGroupId& idDataGroup );

   virtual void setCurrentListItem ( const GenericInterface *rpGICaller,
                                     const BFContainerId& idList,
                                     const DString& strListItemKey
                                   );

private:
   SEVERITY resetContainers();

   MFAccount *_pMFAccount;                            // Not owned by this class!
   Shareholder *_pShareholder;                        // Not owned by this class!
   //ShrAllocTypeList *_pShrAllocationsList;
   SystematicList *_pSystematicList;                  // Not owned by this class!
   SysAllocationList *_pSysAllocationList;            // Not owned by this class!
   FundDetailList *_pFundDetailList;

   RRIF_LIF_LRIF_InfoList  *_pRRIF_LIF_LRIF_InfoList;

   WorksessionTradesList *_pTradesList;                          // Not owned by this class!

   //FundAllocList *_pFundAllocationList;        
   //AcctAllocList *_pAccountAllocationList;        

   AutoAcctTransAllocationList*  _pAtAcctTransList;
   AutoTransAllocationList* _pAtFundTransList;

   //AcctAllocList *_pDefAcctAllocList;
   //FundAllocList *_pDefFundAllocList;

   DString _dstrAccountNum;
   DString _dstrShare;
   DString _dstrPendingOrTransHist;
   DString _dstrTransCode;
   DString _dstrTransNum; 
   DString _dstrTradeDate;
   DString _dstrSettleCurrency;
   DString _dstrTransactionAmount;
   DString _strTransType;
   DString _strAllocationListKey;

   GenericInterface *_rpChildGI;
   DString _dstrAllocationType;
   DString _mainListKey;
};


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/AllocationsProcess.hpp-arc  $
 * 
 *    Rev 1.25   Nov 07 2004 14:05:42   popescu
 * PET 1117/06, synch changes
 * 
 *    Rev 1.24   Aug 17 2003 12:46:36   popescu
 * set the selection on the allocation list based on the alocation item selected in Trade dialog
 * 
 *    Rev 1.23   Mar 21 2003 17:35:42   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.22   Oct 09 2002 23:53:02   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.21   Aug 29 2002 12:51:46   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.20   Aug 06 2002 09:54:04   KOVACSRO
 * Release 48. Converted RRIF allocs.
 * 
 *    Rev 1.19   Jul 18 2002 17:17:24   KOVACSRO
 * Added _strTransType.
 * 
 *    Rev 1.18   Jun 03 2002 16:55:10   HSUCHIN
 * bug fix to doValidateAll to use BFAbstractCBO rather than BFCBO
 * 
 *    Rev 1.17   22 May 2002 22:22:20   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.16   08 May 2002 16:36:02   KOVACSRO
 * Removed trade allocations. Using base class pointers.
 * 
 *    Rev 1.15   29 Apr 2002 15:54:32   KOVACSRO
 * Added new trade allocations.
 * 
 *    Rev 1.14   22 Apr 2002 09:58:34   KOVACSRO
 * Rel.47 : new design for Allocations.
 * 
 *    Rev 1.13   19 Mar 2002 13:15:06   PURDYECH
 * Use #pragma once as include guard
 * Remove compile time "including..." message
 * 
 *    Rev 1.12   13 Jun 2001 09:42:34   KOVACSRO
 * added doSetField, doGetErrors, doGetAttributes.
 * 
 *    Rev 1.11   03 May 2001 14:03:44   SMITHDAV
 * Session management restructuring.
 * 
 *    Rev 1.10   01 Mar 2001 16:47:00   KOVACSRO
 * Added a pointer to TradeAllocationList
 * 
 *    Rev 1.9   22 Feb 2001 14:36:18   KOVACSRO
 * Changed TradeAllocation into FundAllocation.
 * 
 *    Rev 1.8   Feb 06 2001 14:48:12   KOVACSRO
 * Changed TradesList into WorksessionTradesList.
 * 
 *    Rev 1.7   Aug 02 2000 15:31:38   BUZILA
 * "locale" changes
 * 
 *    Rev 1.6   May 01 2000 09:40:48   YINGBAOL
 * add validation and other logic
 * 
 *    Rev 1.5   Apr 17 2000 14:44:54   HUANGSHA
 * Added the routine SetCurrentListItem
 * 
 *    Rev 1.4   Apr 10 2000 12:31:40   HUANGSHA
 * Added TradeAllocations processing routines
 * 
 *    Rev 1.3   Mar 24 2000 10:07:46   YINGBAOL
 * change
 * 
 *    Rev 1.2   Mar 20 2000 16:45:42   HSUCHIN
 * check in for Yingbao
 * 
 *    Rev 1.1   Feb 15 2000 18:56:14   MCNABBGL
 * changed comment format
 * 
 *    Rev 1.0   Feb 15 2000 10:58:56   SMITHDAV
 * Initial revision.
// 
//    Rev 1.18   Feb 03 2000 12:01:58   PRAGERYA
// Some fixes
// 
//    Rev 1.17   Feb 01 2000 13:02:48   PRAGERYA
// For Winnie
// 
//    Rev 1.16   Jan 31 2000 12:06:38   PRAGERYA
// For Release
// 
//    Rev 1.15   Jan 27 2000 12:13:08   PRAGERYA
// Some fixes
// 
//    Rev 1.14   Dec 24 1999 17:10:54   PRAGERYA
// For internal release
// 
//    Rev 1.13   Dec 09 1999 10:52:18   PRAGERYA
// Another check-in for Jerry
// 
//    Rev 1.12   Dec 07 1999 11:43:38   PRAGERYA
// Check in for Jerry
// 
//    Rev 1.11   Dec 01 1999 14:37:22   PRAGERYA
// Check-in for release
// 
//    Rev 1.10   Nov 25 1999 15:36:48   PRAGERYA
// Shameful check-in for Release; very little things are functional
// 
//    Rev 1.9   Nov 18 1999 16:55:42   PRAGERYA
// This is the version developed on the premises that (1) Total amount is updatable, and (2) Pending transaction allocations are updatable. 
// According to Mike Metzger's clarifications, both of these assumtions are wrong. Pending transactions are not updatable just like Transaction History ones. Total Amount is also not updatable. If it is zero, the Fund Amount edit box should be disabled, and the value in it set to zero.
// 
//    Rev 1.8   Nov 18 1999 13:48:14   PRAGERYA
// Coding for Allocations, incr2
// 
//    Rev 1.7   Nov 15 1999 15:57:22   PRAGERYA
// Incr2 partial functionality
// 
//    Rev 1.6   Nov 01 1999 18:10:10   DT24433
// removed doOk/doCancel
// 
//    Rev 1.5   Oct 28 1999 13:01:38   PRAGERYA
// doGetField added
// 
//    Rev 1.4   Sep 24 1999 20:17:12   PRAGERYA
// Default allocations started
// 
//    Rev 1.3   Sep 24 1999 10:11:58   PRAGERYA
// "Milestone" check in
// 
//    Rev 1.2   Sep 20 1999 14:53:28   PRAGERYA
// From now on, we show only allocations for the current account
// 
//    Rev 1.1   Sep 20 1999 10:53:50   PRAGERYA
// This is the implementation made on the premise that we need to show allocations for ALL accounts pertaining to the current shareholder. All the further revisions are made on the premise that we need to show only allocations pertaining to the currently active account.
// 
//    Rev 1.0   Sep 19 1999 13:40:06   PRAGERYA
// Initial revision.
 * 
 *    Rev 1.1   Jul 08 1999 10:03:46   SMITHDAV
 * Modify revision history commaent format to old
 * style comment -- I can't seem to get new style comments to work.
 *
 */
