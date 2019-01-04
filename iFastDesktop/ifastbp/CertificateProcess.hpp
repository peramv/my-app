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

// Forward references
class CertificateList;

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

class IFASTBP_LINKAGE CertificateProcess : public AbstractProcess
{
// Construction
public:
   /**
    * Default constructor
    */
//CP20030319   CertificateProcess();
   CertificateProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand );
   virtual ~CertificateProcess();
protected:

   void doGetField(
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
   const BFProperties *doGetFieldAttributes( const GenericInterface *rpGICaller, const BFContainerId& idContainer, const BFFieldId& idField, const BFDataGroupId& idDataGroup );
   SEVERITY doGetErrors( const GenericInterface *rpGICaller, const BFContainerId& idContainer, const BFFieldId& idField, const BFDataGroupId& idDataGroup, CONDITIONVECTOR &conditions ) const;


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
   GenericInterface *_rpChildGI;
   CertificateList  *_pCertificateList;
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/CertificateProcess.hpp-arc  $
 * 
 *    Rev 1.8   Mar 21 2003 17:37:44   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.7   Oct 09 2002 23:53:06   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.6   Aug 29 2002 12:52:00   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.5   22 May 2002 18:21:34   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.4   19 Mar 2002 13:15:22   PURDYECH
 * Use #pragma once as include guard
 * Remove compile time "including..." message
 * 
 *    Rev 1.3   Aug 02 2000 15:31:38   BUZILA
 * "locale" changes
 * 
 *    Rev 1.2   Jun 06 2000 08:39:44   BUZILA
 * finished M3 syncup
 * 
 *    Rev 1.1   Feb 15 2000 18:56:18   MCNABBGL
 * changed comment format
 * 
 *    Rev 1.0   Feb 15 2000 10:59:00   SMITHDAV
 * Initial revision.
 * 
 *    Rev 1.2   Oct 28 1999 17:55:14   DT24433
 * removed doOk/doCancel
 * 
 *    Rev 1.1   Jul 08 1999 10:03:32   SMITHDAV
 * Modify revision history commaent format to old
 * style comment -- I can't seem to get new style comments to work.
 *
 */

