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

class AccrualsList;
class AccrualsSearchCriteria;
class FundDetailList;
class FundMasterList;
class MFAccount;
class MFAccountHoldingList;

// Import/Export resolution
#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif

class IFASTBP_LINKAGE AccrualsProcess : public AbstractProcess
{

public:
//******************************************************************************
// Constructor
//******************************************************************************

//CP20030319   AccrualsProcess();
   AccrualsProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand );

//******************************************************************************
// Destructor
//******************************************************************************

   virtual ~AccrualsProcess();

protected:

//******************************************************************************
// Override for field which are defined in the Constructor as SUBCLASS_PROCESS.
// The following fields are processed.
// TOTAL_FIELD1
// TOTAL_FIELD2
// TOTAL_FIELD3
// TOTAL_FIELD4
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
// Initializes all the search criteria cbos and accrual list cbos.
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
// Functions which brings the Accrual dialog to focus and top of the window 
// stack.  It also notifies Accruals to refresh in case account information 
// has changed.
// @param   GenericInterface *rpGICaller - pointer to parent object.
// @return bool - true when successful, false otherwise.
//******************************************************************************

   virtual bool doModelessSetFocus( GenericInterface *rpGICaller );

//******************************************************************************
// Function called by accruals dialog which returns true/false depending on
// whether there exist more data in the database.
// @param   GenericInterface *rpGICaller - pointer to parent object.
//          in idSearch - Type of search is requested.
// @returns bool - true if there are more data
//                 false otherwise.
//******************************************************************************

   virtual bool doMoreRecordsExist( GenericInterface *rpGICaller, const BFContainerId& idSearch );

//******************************************************************************
// This functions starts the Accruals Dialog
// @returns E_COMMANDRETURN.
//******************************************************************************

   virtual E_COMMANDRETURN doProcess();

//******************************************************************************
// This function is called by the accruals dialog to initiate a new search.
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

private:

   AccrualsList *_pInterestAccrualDetailsList;        //Pointer Interest Accruals
   AccrualsList *_pMFAccrualsList;                    //Pointer to MF Accruals
   AccrualsList *_pMFRAccrualsList;                   //Pointer to MFR Accruals
   AccrualsList *_pInterestAccrualSummaryList;        //Pointer Interest Accruals Summary
   AccrualsList *_pMFAccrualsSummaryList;             //Pointer to MF Accruals Summary
   AccrualsList *_pMFRAccrualsSummaryList;            //Pointer to MFR Accruals Summary
   AccrualsSearchCriteria *_pInterestSearchCriteria;  //Pointer to IA Search CBO
   AccrualsSearchCriteria *_pMFSearchCriteria;        //Pointer to MF Search CBO
   AccrualsSearchCriteria *_pMFRSearchCriteria;       //Pointer to MFR Search CBO
   MFAccountHoldingList *_pMFAccountHoldingList;      //Pointer to Account Holdings
   FundMasterList *_pFundMasterList;                  //Pointer to Fund Master List
   FundDetailList *_pFundDetailList;                  //Pointer to Fund Details List
   MFAccount *_pMFAccount;                             //Pointer to MFAccount
   DString _dstrAccountNum;                           //Current Account Number
   GenericInterface *_rpChildGI;                      //Pointer to parent object.
};


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/AccrualsProcess.hpp-arc  $
//
//   Rev 1.8   Mar 21 2003 17:34:54   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.7   Oct 09 2002 23:53:00   PURDYECH
//PVCS Database Conversion
//
//   Rev 1.6   Aug 29 2002 12:51:34   SMITHDAV
//ClientLocale and typed field changes.
//
//   Rev 1.5   16 Apr 2002 14:48:00   HSUCHIN
//removed DString var which stored accrual totals
//
//   Rev 1.4   04 Apr 2002 14:52:38   HSUCHIN
//bug fix .. changed long to double
//
//   Rev 1.3   04 Apr 2002 13:47:48   HSUCHIN
//added member variables to store totals
//
//   Rev 1.2   19 Mar 2002 13:14:52   PURDYECH
//Use #pragma once as include guard
//Remove compile time "including..." message
//
//   Rev 1.1   12 Mar 2002 10:26:38   HSUCHIN
//added support for summary containers
//
//   Rev 1.0   21 Feb 2002 15:58:48   HSUCHIN
//Initial revision.
 */
