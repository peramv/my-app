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

// Import/Export resolution
#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif

namespace BROWSERLAUNCH
{
   const BFFieldId UPDATE_STATUS(3000);

   extern IFASTBP_LINKAGE const I_CHAR * const CONFIRMATION;
}

/**
 * Implementation class for Browser launch process.
 *
 * The BrowserLaunchProcess class represents the processing for id caller.
 *
 */

class IFASTBP_LINKAGE BrowserLaunchProcess : public AbstractProcess
{
// Construction
public:
   /**
    * Default constructor
    */
   BrowserLaunchProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand );
   virtual ~BrowserLaunchProcess();
   bool confirm( GenericInterface * rpGICaller );

protected:
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
     * Override to set focus to child dialog.
     * Used to bring a modeless dialog (via parent process) to the top of the
     * window stack.
     * @param rpGICaller - A reference pointer to the calling object.
     * @returns true if successful, check conditions if false
     */
   virtual bool doModelessSetFocus(
                                  GenericInterface *rpGICaller
                                  );
   virtual E_COMMANDRETURN doProcess();
   bool doSend( GenericInterface * rpGICaller, const I_CHAR * szMessage );
   virtual SEVERITY doInit();
   void processParameters();
	SEVERITY doSetField(
                      const GenericInterface *rpGICaller,
                      const BFContainerId& idContainer,
                      const BFFieldId& idField,
                      const BFDataGroupId& idDataGroup,
                      const DString& strValue,
                      bool bFormatted
                      );
   virtual void doPostOk ( GenericInterface *rpGICaller, 
                           bool bSuccessFlag);
   
private:
   GenericInterface *_rpChildGI;   
   DString m_pageName, 
         m_fromScreen,
         m_urlParams,
         m_acctNum;
   DString _bupdateStatus;
};


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/BrowserLaunchProcess.hpp-arc  $
//
//   Rev 1.8   Sep 16 2011 11:36:18   dchatcha
//P0181953 FN01 - TFSA Amendment - Remove specific interprocess parameter passing.
//
//   Rev 1.7   Jul 11 2011 07:38:20   dchatcha
//P0181953 FN01 - TFSA Amendment- integration test.
//
//   Rev 1.6   Dec 14 2010 00:34:08   dchatcha
//PET0165541 FN03 - QESI Phase3, refresh account detail screen after there is update from Tax jurisdiction history screen.
//
//   Rev 1.5   06 Dec 2007 15:19:58   popescu
//Incident 1088629 - read the ACL set-up for the web pages URL instead of the using the xml configuration file.
//
//   Rev 1.4   Dec 19 2006 16:56:28   fengyong
//PET2282 FN01 - Add Clone Account web page
//
//   Rev 1.3   Dec 06 2006 14:56:50   fengyong
//Incident #763433 - refresh account detail after ok on fund limitation page
//
//   Rev 1.2   Jun 19 2006 11:20:42   fengyong
//Handle parameters by configuration file setting
//
//   Rev 1.1   Jun 08 2006 13:53:56   fengyong
//initial - for prompt group
//
//   Rev 1.0   Jun 08 2006 13:48:02   fengyong
//Initial revision.
 *
 */
