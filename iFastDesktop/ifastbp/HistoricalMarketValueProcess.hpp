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
class HistoricalMarketValueList;
class FundDetailList;
class MFAccount;

// Import/Export resolution
#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif

/**
 * Class that manages the Historical Market Value process.
 *
 * @author Yakov Prager
 * </dd></dl><p><dl><dt><b>Date Created:</b></dt><dd> 03/09/1999</dd></dl>
 * @version 0.1
 */

class IFASTBP_LINKAGE HistoricalMarketValueProcess : public AbstractProcess
{
// Construction
public:
   /**
    * Default constructor
    */
//CP20030319   HistoricalMarketValueProcess();
   HistoricalMarketValueProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand );
   virtual ~HistoricalMarketValueProcess();

protected:
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
                         );
   ///**
   //  * This is an override of the virtual function from AbstractProcess. For
   //  * MFAccountHoldingList, we need a specialized behavior: only interest 
   //  * accrual funds should be returned by the iterator.
   //  * This method is used to get the key to the first item in a list.  This 
   //  * will also set the first item as the current item in the list.
   //  * An exception will be thrown if the list cannot be found.
   //  * See note about lists in class document block.
   //  * @param rpGICaller - A reference pointer to the calling object.
   // * @param idList - ID of list we are using.
   //  * @returns the key to the first list item.  This will be an empty string
   //  * if the list is empty.
   //  */
   //virtual const DString& getFirstListItemKey(
   //   const GenericInterface *rpGICaller,
   //   int idList
   //   );
   ///**
   //  * This is an override of the virtual function from AbstractProcess. For
   //  * MFAccountHoldingList, we need a specialized behavior: only interest 
   //  * accrual funds should be returned by the iterator.
   //  * This method is used to get the key to the next item in a list.  This 
   //  * will also set the first item as the current item in the list.
   //  * An exception will be thrown if the list cannot be found.
   //  * See note about lists in class document block.
   //  * @param rpGICaller - A reference pointer to the calling object.
   //  * @param idList - ID of list we are using.
   //  * @returns the key to the next list item.  This will be an empty string
   //  * if at the end of the list.
   //  */
   //virtual const DString& getNextListItemKey(
   //   const GenericInterface *rpGICaller,
   //   int idList
   //   );
   virtual SEVERITY performSearch( GenericInterface *rpGI, const BFContainerId& idSearch, 
                                   E_SEARCHACTION eSearchAction );
   /*virtual bool doMoreRecordsExist( GenericInterface *rpGICaller, const BFContainerId& idSearch );*/
   SEVERITY doSetField(
                      const GenericInterface *rpGICaller, 
                      const BFContainerId& idContainer, 
                      const BFFieldId& idField, 
                      const BFDataGroupId& idDataGroup, 
                      const DString& strValue, 
                      bool bFormatted
                      );
   void doGetField(
                  const GenericInterface *rpGICaller,  
                  const BFContainerId& idContainer, 
                  const BFFieldId& idField, 
                  const BFDataGroupId& idDataGroup, 
                  DString &strValueOut, 
                  bool bFormtted
                  ) const;
private:
   bool  isFixedPartField(const BFFieldId& idField ) const;
   HistoricalMarketValueList *_pHistoricalMarketValueList;
   FundDetailList *_pFundDetailList;// Not owned by this class!
   MFAccount *_pMFAccount;// Not owned by this class!
   DString _strInitFundCode;
   DString _strInitClassCode;
   GenericInterface *_rpChildGI;
};


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/HistoricalMarketValueProcess.hpp-arc  $
 * 
 *    Rev 1.12   Mar 21 2003 17:41:14   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.11   Feb 17 2003 14:23:48   popescu
 * Added a field for th calculation of the total market value by FundGroup
 * 
 *    Rev 1.10   Oct 09 2002 23:53:18   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.9   Sep 30 2002 11:00:58   PURDYECH
 * BFFieldId no longer has operator long(), so explicit getId() calls are needed in places.
 * 
 *    Rev 1.8   Aug 29 2002 12:52:40   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.7   22 May 2002 18:20:52   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.6   19 Mar 2002 13:17:26   PURDYECH
 * Use #pragma once as include guard
 * Remove compile time "including..." message
 * 
 *    Rev 1.5   Feb 05 2002 10:41:00   YINGBAOL
 * add  isFixedPartField(const long lidField)
 * 
 *    Rev 1.4   28 Dec 2001 14:54:14   KOVACSRO
 * Added doGetField and doSetField; removed _pHistoricalMarketValue.
 * 
 *    Rev 1.3   Jun 07 2001 11:31:38   YINGBAOL
 * fix reFresh
 * 
 *    Rev 1.2   Jul 07 2000 10:20:58   ZHANGCEL
 * Changed for C2 improvment
 * 
 *    Rev 1.1   Feb 15 2000 18:56:32   MCNABBGL
 * changed comment format
 * 
 *    Rev 1.0   Feb 15 2000 10:59:12   SMITHDAV
 * Initial revision.
 * 
 *    Rev 1.2   Nov 02 1999 11:19:06   DT24433
 * removed doOk/doCancel
 * 
 *    Rev 1.1   Jul 08 1999 10:03:46   SMITHDAV
 * Modify revision history commaent format to old
 * style comment -- I can't seem to get new style comments to work.
 *
 */
