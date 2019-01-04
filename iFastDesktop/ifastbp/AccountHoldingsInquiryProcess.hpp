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
//    Copyright 1999 by DST Systems, Inc.
//
//******************************************************************************

#include <bfproc\abstractprocess.hpp>

// Forward references
class MFAccountHoldingList;
class MFAccount;
class AccountHoldingsByCurrencyList;
class FundClassHoldingsList;
class AccountDistributionList;

// Import/Export resolution
#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif

class IFASTBP_LINKAGE AccountHoldingsInquiryProcess : public AbstractProcess
{
// Construction
public:
   /**
    * Default constructor
    */
//CP20030319   AccountHoldingsInquiryProcess();
   AccountHoldingsInquiryProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand );
   virtual ~AccountHoldingsInquiryProcess();

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
                         )
   {
      return(false);
   };

   void *getPtrForContainer( const BFContainerId& idContainer, const BFDataGroupId& idDataGroup );

   void doGetField(
                  const GenericInterface *rpGICaller,
                  const BFContainerId& idContainer,
                  const BFFieldId& idField,
                  const BFDataGroupId& idDataGroup,
                  DString &strValueOut,
                  bool bFormatted
                  ) const;

private:

   MFAccountHoldingList *_pMFAccountHoldingList;
   MFAccount *_pMFAccount;
   AccountHoldingsByCurrencyList *_pAccountHoldingsByCurrencyList;
   FundClassHoldingsList *_pFundClassHoldingsList;
   AccountDistributionList *_pAccDistributionsList;

   DString  strAccountNumber;
   GenericInterface *_rpChildGI;
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/AccountHoldingsInquiryProcess.hpp-arc  $
//
//   Rev 1.6   Mar 21 2003 17:34:24   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.5   Oct 09 2002 23:52:58   PURDYECH
//PVCS Database Conversion
//
//   Rev 1.4   Aug 29 2002 12:51:28   SMITHDAV
//ClientLocale and typed field changes.
//
//   Rev 1.3   22 May 2002 18:22:04   PURDYECH
//BFData Implementation
//
//   Rev 1.2   19 Mar 2002 13:14:48   PURDYECH
//Use #pragma once as include guard
//Remove compile time "including..." message
//
//   Rev 1.1   Oct 30 2001 11:47:58   VASILEAD
//Added distribution information
//
//   Rev 1.0   Mar 05 2001 13:28:40   VASILEAD
//Initial revision.
 * 
 /    Rev 1.1   Nov 25 1999 11:52:46   FENGYONG
// Changed with MFAccount 
 * 
 *
 */

