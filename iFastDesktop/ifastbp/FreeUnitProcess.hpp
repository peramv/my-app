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
//class FreeUnitList;
class FreeUnitList;
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
 * Class that manages the entity process.
 *
 * @author Chin Hsu
 * </dd></dl><p><dl><dt><b>Date Created:</b></dt><dd> 03/09/1999</dd></dl>
 * @version 0.1
 */

class IFASTBP_LINKAGE FreeUnitProcess : public AbstractProcess
{
// Construction
public:
   /**
    * Default constructor
    */
//CP20030319   FreeUnitProcess();
   FreeUnitProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand );
   virtual ~FreeUnitProcess();
   bool doMoreRecordsExist( GenericInterface *rpGICaller, const BFContainerId& idSearch );
   const DString& FreeUnitProcess::getFirstListItemKey( const GenericInterface *rpGICaller, const BFContainerId& idList );
   const DString& FreeUnitProcess::getNextListItemKey( const GenericInterface *rpGICaller, const BFContainerId& idList );
   SEVERITY doSetField( const GenericInterface *rpGICaller, 
                        const BFContainerId& idContainer,
                        const BFFieldId& idField, 
                        const BFDataGroupId& idDataGroup, 
                        const DString& strValue, 
                        bool bFormatted
                      );
protected:
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
     * Set up the list and get parameters.
     * @returns SEVERITY noting any error/warning conditions
     */
   virtual SEVERITY doInit();
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


   virtual void doGetField(
                          const GenericInterface *rpGICaller,
                          const BFContainerId& idContainer,
                          const BFFieldId& idField,
                          const BFDataGroupId& idDataGroup,
                          DString &strValueOut,
                          bool bFormatted
                          ) const;

   SEVERITY performSearch( GenericInterface *rpGI, const BFContainerId& idSearch, 
                           E_SEARCHACTION eSearchAction );

   void *getPtrForContainer( const BFContainerId& idContainer, const BFDataGroupId& idDataGroup );

private:
   FreeUnitList *_pFreeUnitList;
   FundDetailList *_pFundDetailList;
   GenericInterface *_rpChildGI;
   MFAccount *_pMFAccount;                             //Pointer to MFAccount
   FreeUnitList *_pFreeAmountList;

   DString AccountNumber;
   DString ListViewFilter;
   DString _FundCode;
   DString _ClassCode;
   DString m_DSCFeeLevel;
   DString _dstrPrcntFeeDipOpt;
   DString _prcntFeeHolding;
};


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/FreeUnitProcess.hpp-arc  $
 * 
 *    Rev 1.11   May 02 2005 13:25:00   hernando
 * PET1024 FN10 - Acct Level/Fund Level DSC Enhancement.
 * 
 *    Rev 1.10   Nov 05 2003 16:21:52   linmay
 * P843_FN251
 * 
 *    Rev 1.9   Mar 21 2003 17:40:06   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.8   Oct 09 2002 23:53:14   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.7   Aug 29 2002 12:52:28   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.6   22 May 2002 18:21:02   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.5   17 Apr 2002 18:18:00   HERNANDO
 * Added MFAccount *_pMFAccount.
 * 
 *    Rev 1.4   19 Mar 2002 13:17:04   PURDYECH
 * Use #pragma once as include guard
 * Remove compile time "including..." message
 * 
 *    Rev 1.3   Jun 07 2001 11:30:18   YINGBAOL
 * fix refresh issue
 * 
 *    Rev 1.2   Aug 02 2000 15:31:42   BUZILA
 * "locale" changes
 * 
 *    Rev 1.1   Feb 15 2000 18:56:28   MCNABBGL
 * changed comment format
 * 
 *    Rev 1.0   Feb 15 2000 10:59:08   SMITHDAV
 * Initial revision.
// 
//    Rev 1.5   Dec 08 1999 16:27:06   HSUCHIN
// changed doGetField and doSetField to include groupid
// 
//    Rev 1.4   Oct 29 1999 09:59:20   DT24433
// removed doOk/doCancel
 * 
 */
