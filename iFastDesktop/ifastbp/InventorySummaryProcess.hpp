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
//    Copyright 2003 by International Financial, Inc.
//
//******************************************************************************

#include <bfproc\abstractprocess.hpp>
#include <ifastbp/ifasthistoricalparameters.hpp>

// Forward references

class InventorySummaryProcess;
class MFAccount;
class MFAccountHoldingList;
class FundMasterList;

// Import/Export resolution
#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif

class IFASTBP_LINKAGE InventorySummaryProcess : public AbstractProcess
{

public:
//******************************************************************************
// Constructor
//******************************************************************************

//CP20030319   InventorySummaryProcess();
   InventorySummaryProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand );

//******************************************************************************
// Destructor
//******************************************************************************

   virtual ~InventorySummaryProcess();

   bool doSend(GenericInterface *rpGICaller, const I_CHAR *szMessage );

protected:

//******************************************************************************
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
// @param   GenericInterface *rpGICaller - pointer to parent object.
// @return bool - true when successful, false otherwise.
//******************************************************************************

   virtual bool doModelessSetFocus( GenericInterface *rpGICaller );

//******************************************************************************
// @param   GenericInterface *rpGICaller - pointer to parent object.
//          in idSearch - Type of search is requested.
// @returns bool - true if there are more data
//                 false otherwise.
//******************************************************************************

   virtual bool doMoreRecordsExist( GenericInterface *rpGICaller, const BFContainerId& idSearch );

//******************************************************************************
// This functions starts the Account Contract Dialog
// @returns E_COMMANDRETURN.
//******************************************************************************

   virtual E_COMMANDRETURN doProcess();

//******************************************************************************
// @param   GenericInterface *rpGICaller - pointer to parent object.
//          const BFContainerId& idSearch - Type of search is requested.
//          E_SEARCHACTION eSearchAction - SEARCH_START (new search)
//                                         SEARCH_NEXT_BLOCK ( get More )
//******************************************************************************

   virtual SEVERITY performSearch( GenericInterface *rpGI, const BFContainerId& idSearch, 
                                   E_SEARCHACTION eSearchAction );

//******************************************************************************
// Function which get the container pointer on demand.
// @param   const BFContainerId& idContainer - Id to the container.
//          const BFDataGroupId& idDataGroup - group id.
// @returns void.
//******************************************************************************

   void * getPtrForContainer( const BFContainerId& idContainer, const BFDataGroupId& idDataGroup );

   virtual SEVERITY doSetField( const GenericInterface *rpGICaller, 
                                const BFContainerId& idContainer, 
                                const BFFieldId& idField, 
                                const BFDataGroupId& idDataGroup, 
                                const DString& strValue, 
                                bool bFormatted );

   virtual const BFProperties *doGetFieldAttributes( const GenericInterface *rpGICaller, 
                                                     const BFContainerId& idContainer, 
                                                     const BFFieldId& idField, 
                                                     const BFDataGroupId& idDataGroup );

private:

   InventorySummaryList* _pInventorySummaryList;      //Pointer Inventory Summary List
   MFAccountHoldingList* _pAccountHoldingList;        //Pointer to AccountHolding List
   FundMasterList* _pFundMasterList; 
   MFAccount *_pMFAccount;                            //Pointer to MFAccount
   DString _dstrAccountNum;                           //Current Account Number
   DString _dstrFundCode;
   DString _dstrClassCode;
   GenericInterface *_rpChildGI;                      //Pointer to parent object.
};


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/InventorySummaryProcess.hpp-arc  $
//
//   Rev 1.2   Jun 08 2004 13:59:14   HERNANDO
//PET1046 FN01 - Storing Fund and Class codes.
//
//   Rev 1.1   May 19 2004 17:44:54   HERNANDO
//PET1046 FN01 - Added LSIF/Inventory Details.  Added doSend to allow clearing of the details container.
//
//   Rev 1.0   Feb 24 2004 10:28:06   ZHANGCEL
//Initial revision.
 */
