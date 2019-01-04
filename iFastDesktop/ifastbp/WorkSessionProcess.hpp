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


#include <bfproc\AbstractProcess.hpp>
///#endif

class DSTCWorkSession;

// Import/Export resolution
#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif

/**
 * Class that provides encapsulation of tasks required to handle all aspects of
 * call/get work processing.
 *
 * This class is instantiated at the beginning of a call, "get work", or any
 * other complete set of work and its life time ends when the work is finished
 * (or cancelled).  It handles creating a sub-session to associate with the set
 * of work and obtaining a unique CBO session id from the CBM which will be 
 * used to manage CBO work in the repositories. 
 * !!!!!!!!!!!!!! The complete set of tasks which
 * this class will provide during and at the end of its existence are still to 
 * determined.
 *
 * @author Jerry Leenerts
 * </dd></dl><p><dl><dt><b>Date Created:</b></dt><dd> 12/14/98</dd></dl>
 * @version 0.1
 */

class IFASTBP_LINKAGE WorkSessionProcess : public AbstractProcess
{
// Construction
public:
   /**
    * Default constructor
    */
//CP20030319   WorkSessionProcess();
   WorkSessionProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand );
   virtual ~WorkSessionProcess();
protected:
   /**
     * Set up the work session id.
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
     * Implementation to override base functionality.  This method would be
     * invoked when the user is done with this work session.  The work session
     * will finish any work in process and return accordingly.
     * @param rpGICaller - A reference pointer to the calling object.
     * @returns true if successful, call getErrors for errors if false
     */
   virtual SEVERITY ok2(
                       GenericInterface *rpGI
                       );

   virtual bool doSend(GenericInterface *rpGICaller, const I_CHAR *szMessage);

private:
   DSTCWorkSession *_dstcWorkSession;
};


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/WorkSessionProcess.hpp-arc  $
 * 
 *    Rev 1.7   Mar 21 2003 17:50:16   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.6   Oct 09 2002 23:53:44   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.5   Apr 03 2002 18:41:36   HERNANDO
 * Added doSend to end/recreate Subsession.
 * 
 *    Rev 1.4   19 Mar 2002 13:20:16   PURDYECH
 * Use #pragma once as include guard
 * Remove compile time "including..." message
 * 
 *    Rev 1.3   03 May 2001 14:05:10   SMITHDAV
 * Session management restructuring.
 * 
 *    Rev 1.2   Mar 21 2000 10:40:38   DT24433
 * added doInit
 * 
 *    Rev 1.1   Feb 15 2000 18:57:08   MCNABBGL
 * changed comment format
 * 
 *    Rev 1.0   Feb 15 2000 10:59:28   SMITHDAV
 * Initial revision.
 * 
 *    Rev 1.2   Oct 29 1999 14:52:20   DT24433
 * changed doOk to ok2
 * 
 *    Rev 1.1   Jul 08 1999 10:04:06   SMITHDAV
 * Modify revision history commaent format to old
 * style comment -- I can't seem to get new style comments to work.
 *
 */
