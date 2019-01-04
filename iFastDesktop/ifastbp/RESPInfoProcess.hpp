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
// ^FILE   : RESPInfoProcess.hpp
// ^AUTHOR : Dan Petolescu
// ^DATE   : 01/05/2000
//
// ----------------------------------------------------------
//
// ^CLASS    : RESPInfoProcess
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :  
//
//******************************************************************************


#include <bfproc\AbstractProcess.hpp>

// Forward references
class RESPInfoBeneficiaryList;
class RESPInfo;

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

class IFASTBP_LINKAGE RESPInfoProcess : public AbstractProcess
{
// Construction
public:
   /**
    * Default constructor
    */
//CP20030319   RESPInfoProcess();
   RESPInfoProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand );
   virtual ~RESPInfoProcess();

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
   // virtual bool doRefresh( GenericInterface *rpGICaller, const I_CHAR *szOriginalCommand );
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

private:
//   RESPInfoBeneficiaryList *_pRESPInfoBeneficiaryList;
   RESPInfo *_pRESPInfoBeneficiaryList; //added now
   RESPInfo *_pRESPInfo;
   GenericInterface *_rpChildGI;
   DString _strAccountNum; 
   DString _strShareholderNum;
   DString _strLastName;
   DString _strFirstName;

};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/RESPInfoProcess.hpp-arc  $
 * 
 *    Rev 1.7   Mar 21 2003 17:47:18   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.6   Oct 09 2002 23:53:34   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.5   22 May 2002 18:20:08   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.4   19 Mar 2002 13:18:12   PURDYECH
 * Use #pragma once as include guard
 * Remove compile time "including..." message
 * 
 *    Rev 1.3   Jun 07 2001 11:34:06   YINGBAOL
 * remove doRefresh
 * 
 *    Rev 1.2   Mar 22 2000 09:02:30   PETOLESC
 * Added Tax Rates and RESP dialogs.
// 
//    Rev 1.2   Mar 08 2000 10:50:28   PETOLESC
// Modified the title bar as requested by qa.
// 
//    Rev 1.1   Feb 16 2000 10:22:44   PETOLESC
// Added the list to MFAccount.
// 
//    Rev 1.0   Jan 17 2000 14:46:34   PETOLESC
// Initial revision.
 * 
 *
 */

///#endif 
