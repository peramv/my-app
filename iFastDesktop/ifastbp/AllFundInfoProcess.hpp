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


#include <bfproc\AbstractProcess.hpp>
///#endif

// Forward references
class FundMasterList;
class FundDetailList;
class FundSponsorsList;
class MgmtCoOptions;
class TranslationList;
class FeeInfoInquiry;

// Import/Export resolution
#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif

/**
 * Class that manages the Historical Market Value process.
 *
 * @author Yakov Prager
 * </dd></dl><p><dl><dt><b>Date Created:</b></dt><dd> 03/09/1999</dd></dl>
 * @version 0.1
 */

class IFASTBP_LINKAGE AllFundInfoProcess : public AbstractProcess
{
// Construction
public:
   /**
    * Default constructor
    */
//CP20030319   AllFundInfoProcess();
   AllFundInfoProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand );
   virtual ~AllFundInfoProcess();

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
   }
   void doGetField( const GenericInterface *rpGICaller, const BFContainerId& idContainer, const BFFieldId& idField,
                    const BFDataGroupId& idDataGroup, DString &strValueOut, bool bFormatted ) const;
private:

   FundDetailList  *_pFundDetailsList;
   FundMasterList  *_pFundMasterList;
   FundSponsorsList *_pFundSponsorsList;
   MgmtCoOptions   *_pmgmtcooptions;
   TranslationList *_pTranslationList;
   FeeInfoInquiry  *_pFeeInfoInquiry;
   DString _strInitFundCode;
   DString _strInitClassCode;
   GenericInterface *_rpChildGI;
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/AllFundInfoProcess.hpp-arc  $
//
//   Rev 1.7   Mar 21 2003 17:35:34   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.6   Oct 09 2002 23:53:02   PURDYECH
//PVCS Database Conversion
//
//   Rev 1.5   Aug 29 2002 12:51:44   SMITHDAV
//ClientLocale and typed field changes.
//
//   Rev 1.4   22 May 2002 18:21:54   PURDYECH
//BFData Implementation
//
//   Rev 1.3   19 Mar 2002 13:15:04   PURDYECH
//Use #pragma once as include guard
//Remove compile time "including..." message
//
//   Rev 1.2   May 08 2001 10:29:38   FENGYONG
//Add #107 for redemFee
//
//   Rev 1.1   Nov 27 2000 11:37:10   VASILEAD
//Added AllFundInfo support to provide with fund information for the global object in ECOMM
//
//   Rev 1.0   Nov 20 2000 17:54:04   VASILEAD
//Initial revision.
 * 
 */

