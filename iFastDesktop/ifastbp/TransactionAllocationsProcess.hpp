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
class TradeAcctAllocList;
//class Shareholder;

// Import/Export resolution
#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif

/**
 * Class that manages the Transaction Allocations process.
 *
 * @author Yakov Prager
 * </dd></dl><p><dl><dt><b>Date Created:</b></dt><dd> 03/09/1999</dd></dl>
 * @version 0.1
 */

class IFASTBP_LINKAGE TransactionAllocationsProcess : public AbstractProcess
{
// Construction
public:
   /**
    * Default constructor
    */
//CP20030319   TransactionAllocationsProcess();
   TransactionAllocationsProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand );
   virtual ~TransactionAllocationsProcess();
   virtual void *getPtrForContainer(
                                   const BFContainerId& idContainer,
                                   const BFDataGroupId& idDataGroup
                                   );

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
   /**
      * Used to bring a modeless dialog (via parent process) to the top of the
      * window stack.
      * @param rpGICaller - A reference pointer to the calling object.
      * @returns true if successful, check conditions if false
      */
   virtual bool doModelessSetFocus(
                                  GenericInterface *rpGICaller
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
                         )
   {
      return(false);
   }

private:
   MFAccount *_pMFAccount;// Not owned by this class!
   DString _dstrAccountNum;
   DString _dstrPendingOrTransHist;
   DString _dstrTransCode;
   DString _dstrTransNum; 
   DString _dstrTradeDate;
   DString _dstrSettleCurrency;
   DString _dstrPendingListKey;
   TradeAcctAllocList *_pAccountAllocationList;
   GenericInterface *_rpChildGI;
};


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/TransactionAllocationsProcess.hpp-arc  $
 * 
 *    Rev 1.12   Sep 01 2003 21:21:16   popescu
 * PET 809 FN 02, CIBC Multi fund enhancement
 * 
 *    Rev 1.11   Mar 21 2003 17:49:26   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.10   Oct 09 2002 23:53:40   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.9   Aug 29 2002 12:53:56   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.8   22 May 2002 18:19:08   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.7   29 Apr 2002 16:09:10   KOVACSRO
 * new trade allocations.
 * 
 *    Rev 1.6   19 Mar 2002 13:19:00   PURDYECH
 * Use #pragma once as include guard
 * Remove compile time "including..." message
 * 
 *    Rev 1.5   Mar 23 2001 12:34:26   HSUCHIN
 * changed to use the list key from transaction history
 * 
 *    Rev 1.4   Mar 18 2001 11:08:48   YINGZ
 * change field names
 * 
 *    Rev 1.3   Aug 02 2000 15:31:52   BUZILA
 * "locale" changes
 * 
 *    Rev 1.2   Jun 05 2000 10:00:18   HUANGSHA
 * added param SettleCurrencyCode
 * 
 *    Rev 1.1   Feb 15 2000 18:56:52   MCNABBGL
 * changed comment format
 * 
 *    Rev 1.0   Feb 15 2000 10:59:26   SMITHDAV
 * Initial revision.
// 
//    Rev 1.4   Dec 24 1999 17:11:34   PRAGERYA
// For internal release
// 
//    Rev 1.3   Nov 18 1999 13:48:14   PRAGERYA
// Coding for Allocations, incr2
// 
//    Rev 1.2   Nov 02 1999 16:35:30   DT24433
// removed doOk/doCancel
 * 
*/
