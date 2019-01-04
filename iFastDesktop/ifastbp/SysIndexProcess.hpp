#pragma once



//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by DST Canada, Inc.,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2001 by DST Canada, Inc.
//
//******************************************************************************
//
// ^FILE   : SysIndexProcess.hpp
// ^AUTHOR : Mihai Virgil Buzila
// ^DATE   : 05/01/2001
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

class MFAccount;
class MFCommonBusinessManager;
class AccountDistributionList;
class SysIndexList;

class IFASTBP_LINKAGE SysIndexProcess : public AbstractProcess
{
// Construction
public:
   /**
    * Default constructor
    */
//CP20030319   SysIndexProcess();
   SysIndexProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand );
   virtual ~SysIndexProcess();

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

   virtual void *getPtrForContainer(
                                   const BFContainerId& idContainer,
                                   const BFDataGroupId& idDataGroup
                                   );

   virtual SEVERITY doValidateAll(
                                 BFAbstractCBO *rpWSD,
                                 const BFDataGroupId& idDataGroup
                                 );

   virtual SEVERITY deleteItemFromList(
                                      const GenericInterface *rpGICaller,
                                      const BFContainerId& idList
                                      );

private:

   GenericInterface   * m_rpChildGI;
   DString m_dstAcctNum;
   DString m_dstPACSWPId;
   SysIndexList *_pSysIndexList;
};


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/SysIndexProcess.hpp-arc  $
//
//   Rev 1.8   Mar 21 2003 17:48:40   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.7   Oct 09 2002 23:53:38   PURDYECH
//PVCS Database Conversion
//
//   Rev 1.6   Jun 03 2002 16:55:12   HSUCHIN
//bug fix to doValidateAll to use BFAbstractCBO rather than BFCBO
//
//   Rev 1.5   22 May 2002 18:19:44   PURDYECH
//BFData Implementation
//
//   Rev 1.4   19 Mar 2002 13:18:40   PURDYECH
//Use #pragma once as include guard
//Remove compile time "including..." message
//
//   Rev 1.3   01 Aug 2001 17:38:30   HSUCHIN
//clean up of unused functions
//
//   Rev 1.2   05 Jul 2001 17:43:40   HSUCHIN
//force validateall to validate only SysIndexList
//
//   Rev 1.1   06 Jun 2001 13:38:04   HSUCHIN
//code cleanup and additional business logic added
//
//   Rev 1.0   03 May 2001 13:42:14   BUZILAMI
//Initial revision.
 * 
 */
