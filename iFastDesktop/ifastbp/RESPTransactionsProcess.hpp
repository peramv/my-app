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
//******************************************************************************
//
// ^FILE   : RESPTransactionsProcess.hpp
// ^AUTHOR : Dan Petolescu
// ^DATE   : 01/20/2000
//
// ----------------------------------------------------------
//
// ^CLASS    : RESPTransactionsProcess
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :  
//
//******************************************************************************


#include <bfproc\AbstractProcess.hpp>

// Forward references
class RESPTransactionsList;

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

class IFASTBP_LINKAGE RESPTransactionsProcess : public AbstractProcess
{
// Construction
public:
   /**
    * Default constructor
    */
//CP20030319   RESPTransactionsProcess();
   RESPTransactionsProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand );
   virtual ~RESPTransactionsProcess();

protected:
   /**
     * Implementation to support the cancel method.
     * @param rpGICaller - A reference pointer to the calling object.
     * @returns true if successful, call getErrors for errors if false
     */
   virtual bool doCancel( GenericInterface *rpGI );
   /**
     * Set up the list and get parameters.
     * @returns SEVERITY noting any error/warning conditions
     */
   virtual SEVERITY doInit();
   /**
     * Implementation to support the ok method.  This method would be invoked
     * when the user completes the logon screen.  The logon process will 
     * attempt to logon and return accordingly.
     * @param rpGICaller - A reference pointer to the calling object.
     * @returns true if successful, call getErrors for errors if false
     */
   virtual bool doOk( GenericInterface *rpGI );
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
   virtual bool doModelessSetFocus( GenericInterface *rpGICaller );
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
   virtual bool doMoreRecordsExist( GenericInterface *rpGICaller, const BFContainerId& idContainer );
   virtual SEVERITY performSearch( GenericInterface *rpGI, const BFContainerId& idSearch, E_SEARCHACTION  );
   virtual void *getPtrForContainer ( const BFContainerId& idContainer,
                                      const BFDataGroupId& idDataGroup);
   bool  doRefresh( GenericInterface *rpGICaller,
                    const I_CHAR *szOriginalCommand );
   virtual void doPostOk (GenericInterface *rpGICaller, bool bSuccessFlag);

private:
   SEVERITY removeTransactionList (GenericInterface *rpGICaller,
                                   const DString& historyPending);
   RESPTransactionsList *_pRESPTransactionsList;
   GenericInterface *_rpChildGI;
   DString _strAccountNum, 
      _strHistoryPending,
      _strTransId,
	  _strCaller,
	  _strTradeDate;
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/RESPTransactionsProcess.hpp-arc  $
 * 
 *    Rev 1.13   Aug 11 2010 19:44:44   jankovii
 * PET165541 FN03 SOC14 & SOC6
 * 
 *    Rev 1.12   Aug 06 2010 14:00:42   jankovii
 * PET165541 FN03 SOC14 & SOC6
 * 
 *    Rev 1.11   May 13 2010 01:31:34   popescu
 * RESP-QESI fixes
 * 
 *    Rev 1.10   May 11 2010 08:19:12   popescu
 * QESI - RESP Fixes
 * 
 *    Rev 1.9   Apr 01 2010 16:23:20   popescu
 * PET165541_FN01_QESI - RESP Gap_Dsk_Trading - RESP Trading History Dialog
 * 
 *    Rev 1.8   Apr 01 2010 00:47:10   popescu
 * PET165541_FN01_QESI - RESP Gap_Dsk_Trading - RESP Trading History Dialog
 * 
 *    Rev 1.7   25 Nov 2008 16:39:28   popescu
 * Incident  1496411 - fixed the more button in the RESP screen
 * 
 *    Rev 1.6   Mar 21 2003 17:47:26   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.5   Oct 09 2002 23:53:34   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.4   22 May 2002 18:20:04   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.3   19 Mar 2002 13:18:14   PURDYECH
 * Use #pragma once as include guard
 * Remove compile time "including..." message
 * 
 *    Rev 1.2   Mar 22 2000 09:02:38   PETOLESC
 * Added Tax Rates and RESP dialogs.
// 
//    Rev 1.3   Mar 02 2000 12:00:06   PETOLESC
// Corrected qa issues.
// 
//    Rev 1.2   Feb 16 2000 10:06:48   PETOLESC
// Included the list in MFAccount.
// 
//    Rev 1.1   Feb 07 2000 11:02:30   PETOLESC
// Minor corrections and code cleaning.
 * 
 *
 */

///#endif 
