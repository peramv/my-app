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


#include <bfproc\AbstractProcess.hpp>
#include <ifastbp\ifasthistoricalparameters.hpp>

// Forward references

class AccountContractList;
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

class ResetInstrList;
class ResetInstrCriteria;
class IFASTBP_LINKAGE ResetInstrProcess : public AbstractProcess, public IFastHistoricalParameters
{

public:
//******************************************************************************
// Constructor
//******************************************************************************

//CP20030319   ResetInstrProcess();
   ResetInstrProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand );

//******************************************************************************
// Destructor
//******************************************************************************

   virtual ~ResetInstrProcess();

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


   SEVERITY doSetField( const GenericInterface *rpGICaller,
                                        const BFContainerId& idContainer,
                                        const BFFieldId& fieldID,
                                        const BFDataGroupId& idDataGroup,
                                        const DString& strValue,
                                        bool bFormatted );

   bool setCommitDataGroupAsHost();
   SEVERITY getHistoricalParameters( const BFContainerId& idContainer, BFFieldId &recordIdField, DString& tableId, DString& dstrKeys );
   SEVERITY getHistoricalParameters( const BFContainerId& idContainer, HISTORICAL_VECTOR &vectorInput );

private:

   ResetInstrList* _pResetInstrList;        
   ResetInstrCriteria* _pResetInstrCriteria;
   MFAccountHoldingList* _pAccountHoldingList;   
   FundMasterList* _pFundMasterList;
   MFAccount *_pMFAccount;                            //Pointer to MFAccount   
   GenericInterface *_rpChildGI;                      //Pointer to parent object.
   DString _dstrAccountNum;
   DString _dstrParent;
   DString _OriKey;
};


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/ResetInstrProcess.hpp-arc  $
//
//   Rev 1.8   Mar 10 2004 13:19:44   HERNANDO
//PET965 FN11 - Added getHistoricalParameters.
//
//   Rev 1.7   Aug 18 2003 16:10:36   HERNANDO
//Added keys to getHistoricalParameters.
//
//   Rev 1.6   Jul 08 2003 15:02:10   HERNANDO
//PTS 10019155.
//
//   Rev 1.5   Mar 21 2003 17:47:00   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.4   Mar 05 2003 11:22:56   PURDYECH
//IFastBaseProcess no longer exists.  Classes now derive from AbstractProcess (again) and the Protocol class IFastHistoricalParameters.
//
//   Rev 1.3   Jan 29 2003 16:26:02   HSUCHIN
//added support for historical
//
//   Rev 1.2   Jan 27 2003 07:38:42   HSUCHIN
//added support for reversal
//
//   Rev 1.1   Jan 26 2003 16:02:24   HSUCHIN
//added more support
//
//   Rev 1.0   Jan 24 2003 16:10:38   HSUCHIN
//Initial Revision
 */
