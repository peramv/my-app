#pragma once
//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by International Financial, Inc.,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2002 by International Financial, Inc.
//
//******************************************************************************

#include <bfproc\AbstractProcess.hpp>

// Forward references
class MFAccount;
class PensionInfo;

// Import/Export resolution
#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif

class IFASTBP_LINKAGE PensionInfoProcess : public AbstractProcess
{

public:
//******************************************************************************
// Constructor
//******************************************************************************

//CP20030319   PensionInfoProcess();
   PensionInfoProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand );

//******************************************************************************
// Destructor
//******************************************************************************

   virtual ~PensionInfoProcess();

protected:

//******************************************************************************
// Override for field which are defined in the Constructor as SUBCLASS_PROCESS.
// The following fields are processed.
// PORTION_CURRENT_MARKET_VALUE
// @param   const GenericInterface *rpGICaller - pointer to parent object.
//          const BFContainerId& idContainer - container id.
//          const BFFieldId& idField - field requested.
//          const BFDataGroupId& idDataGroup - group id.
//          DString &strValueOut - Field value returned.
//          bool bFormatted - boolean indicating value to be formatted or not.
// @returns void.
//******************************************************************************

   virtual void doGetField( const GenericInterface *rpGICaller,
                            const BFContainerId& idContainer,
                            const BFFieldId& idField,
                            const BFDataGroupId& idDataGroup,
                            DString &strValueOut,
                            bool bFormatted ) const;


//******************************************************************************
// Initializes pension info cbo.
// @returns SEVERITY.
//******************************************************************************

   virtual SEVERITY doInit();

//******************************************************************************
// Function which tells the generic interface container that the modeless child
// has been destroyed.
// @param   const Command &cmd - cmd indicating the child is destroyed.
// @returns bool - true when successful.
//******************************************************************************

   virtual bool doModelessChildComplete( const Command &cmd );

//******************************************************************************
// Functions which brings the Pension Info dialog to focus and top of the window 
// stack.  It also notifies Pension Info to refresh in case account information 
// has changed.
// @param   GenericInterface *rpGICaller - pointer to parent object.
// @return bool - true when successful, false otherwise.
//******************************************************************************

   virtual bool doModelessSetFocus( GenericInterface *rpGICaller );

//******************************************************************************
// This functions starts the Pension Info Dialog
// @returns E_COMMANDRETURN.
//******************************************************************************

   virtual E_COMMANDRETURN doProcess();

//******************************************************************************
// Function which get the container pointer on demand.
// @param   const BFContainerId& idContainer - Id to the container.
//          const BFDataGroupId& idDataGroup - group id.
// @returns void.
//******************************************************************************

   void * getPtrForContainer( const BFContainerId& idContainer, const BFDataGroupId& idDataGroup );   

   virtual SEVERITY doValidateAll( BFAbstractCBO *rpWSD, const BFDataGroupId& idDataGroup );

   bool doOk(GenericInterface *rpGICaller);
   
   virtual bool doCancel(GenericInterface *rpGICaller);
private:

   MFAccount *_pMFAccount;                             //Pointer to MFAccount
   PensionInfo *_pPensionInfo;                        //Pointer to Pension Info
   DString _dstrAccountNum;                           //Current Account Number
   DString _dstrCreatingAcct;
   DString _dstrCreatingShr;
   GenericInterface *_rpChildGI;                      //Pointer to parent object.
};


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/PensionInfoProcess.hpp-arc  $
//
//   Rev 1.5   Jan 27 2012 02:20:24   wutipong
//IN2774749 Pension Information screens become invalid when the screen is opened the second time with an account whose does not have pention information setup.
//
//   Rev 1.4   Mar 21 2003 17:45:48   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.3   Oct 09 2002 23:53:32   PURDYECH
//PVCS Database Conversion
//
//   Rev 1.2   Aug 29 2002 12:53:10   SMITHDAV
//ClientLocale and typed field changes.
//
//   Rev 1.1   Aug 08 2002 15:09:00   HSUCHIN
//added doOk override
//
//   Rev 1.0   Jun 02 2002 17:59:10   HSUCHIN
//Initial revision.
 */
