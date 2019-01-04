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
// ^FILE   : TaxExemptAuthorizationProcess.hpp
// ^AUTHOR : Celia Zhang
// ^DATE   : 07/15/2004
//
// ----------------------------------------------------------
//
// ^CLASS    : TaxExemptAuthorizationProcess
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :  
//
//******************************************************************************


#include <bfproc\AbstractProcess.hpp>

// Forward references
class TaxExemptAuthorizationList;
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
 * @author 
 * </dd></dl><p><dl><dt><b>Date Created:</b></dt><dd> 03/04/1999</dd></dl>
 * @version 0.1
 */

class IFASTBP_LINKAGE TaxExemptAuthorizationProcess : public AbstractProcess
{
// Construction
public:
   /**
    * Default constructor
    */
//CP20030319   TaxExemptAuthorizationProcess();
   TaxExemptAuthorizationProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand );
   virtual ~TaxExemptAuthorizationProcess();

protected:
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
   void doPostOk(
                GenericInterface *rpGICaller,
                bool bSuccessFlag
                );
    
   virtual void doGetField(
                          const GenericInterface *rpGICaller,
                          const BFContainerId& idContainer,
                          const BFFieldId& idField,
                          const BFDataGroupId& idDataGroup,
                          DString &strValueOut,
                          bool bFormatted
                          ) const;

   virtual const BFProperties *doGetFieldAttributes (
                           const GenericInterface *rpGICaller, 
                           const BFContainerId &idContainer, 
                           const BFFieldId &idField, 
                           const BFDataGroupId &idDataGroup);

   virtual bool doRegisterObserver ( const GenericInterface *rpGICaller,
                                     const BFContainerId &idContainer,
                                     const BFFieldId &idField,
                                     const BFDataGroupId &idDataGroup,
                                     BFObserver &rpObserver
                                   );

    virtual bool doMoreRecordsExist( GenericInterface *rpGICaller, const BFContainerId& idSearch );

	void *getPtrForContainer( const BFContainerId &idContainer,
                             const BFDataGroupId &idDataGroup );

	SEVERITY performSearch( GenericInterface *rpGI, const BFContainerId& idSearch, E_SEARCHACTION eSearchAction );

private:

   // Private member function

   // Private member data
   TaxExemptAuthorizationList *_pTaxExemptAuthorizationList;
   GenericInterface *_rpChildGI;
   MFAccount* _pMFAccount;
   DString strAccountNum;

   DString strKey;
};

///#endif 

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/TaxExemptAuthorizationProcess.hpp-arc  $
//
//   Rev 1.1   Nov 28 2005 09:40:36   jankovii
//PET1228_FN02_ EU Savings Directive Phase Two
//
//   Rev 1.0   Aug 06 2004 17:37:54   ZHANGCEL
//Initial revision.
 *
 */
