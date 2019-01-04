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
//    Copyright 1997 by DST Systems, Inc.
//
//******************************************************************************

//Forward declaration
class ManagementCompaniesList;

// Import/Export resolution
#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif

/**
 * Class that manages the Management Company process.
 *
 * @author Jerry Leenerts
 * </dd></dl><p><dl><dt><b>Date Created:</b></dt><dd> 02/08/99</dd></dl>
 * @version 0.1
 */

class IFASTBP_LINKAGE ManagementCompanyProcess : public AbstractProcess
{
// Construction
public:
   /**
    * Default constructor
    */
//CP20030319   ManagementCompanyProcess();
   ManagementCompanyProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand );
   virtual ~ManagementCompanyProcess();
protected:
   /**
     * Implementation overriding base functionality.  If we change to store data
     * in CBO, we may want to change to doOk.  This method would be invoked
     * when the user completes the logon screen.  The logon process will 
     * attempt to logon and return accordingly.
     * @param rpGICaller - A reference pointer to the calling object.
     * @returns true if successful, call getErrors for errors if false
     */
   virtual SEVERITY ok2(
                       GenericInterface *rpGI
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
                         )
   {
      return(false);
   }
   /**
     * This method is used (typically by an associated GUI component) to set the
     * current item in a list.  An exception will be thrown if the item is not 
     * found.
     * See note about lists in class document block.
     * @param rpGICaller - A reference pointer to the calling object.
     * @param idList - ID of list we are using.
     * @param strListItemKey - The key to the list item.  This item will be set
     * as the current item in the list.
     */
   virtual void setCurrentListItem(
                                  const GenericInterface *rpGICaller,
                                  const BFContainerId& idList,
                                  const DString& strListItemKey
                                  );

private:
   ManagementCompaniesList *_pMgmtCompaniesList;

   //sets the current company based on the SYSTMGMTS field in UserSessionProcess
   void setCurrentCompany(const GenericInterface *rpGICaller); 

   DString _dstCurrentCompanyId;

};


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/ManagementCompanyProcess.hpp-arc  $
 * 
 *    Rev 1.8   Mar 21 2003 17:44:44   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.7   Oct 09 2002 23:53:28   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.6   22 May 2002 18:20:26   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.5   19 Mar 2002 13:17:54   PURDYECH
 * Use #pragma once as include guard
 * Remove compile time "including..." message
 * 
 *    Rev 1.4   11 Jul 2001 13:50:12   SMITHDAV
 * Store current Management Co.
 * 
 *    Rev 1.3   05 Jun 2001 13:30:10   HSUCHIN
 * minor cleanup
 * 
 *    Rev 1.2   May 05 2000 16:48:50   YINGBAOL
 * fix
 * 
 *    Rev 1.1   Feb 15 2000 18:56:38   MCNABBGL
 * changed comment format
 * 
 *    Rev 1.0   Feb 15 2000 10:59:14   SMITHDAV
 * Initial revision.
 * 
 *    Rev 1.2   Oct 29 1999 10:52:38   DT24433
 * removed doCancel and changed doOk to ok2
 * 
 *    Rev 1.1   Jul 08 1999 10:03:50   SMITHDAV
 * Modify revision history commaent format to old
 * style comment -- I can't seem to get new style comments to work.
 *
 */
