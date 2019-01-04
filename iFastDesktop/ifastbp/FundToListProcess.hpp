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

class FundToList;
class FundMasterList;
class FundDetailList;
class FundSponsorsList;
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

class IFASTBP_LINKAGE FundToListProcess : public AbstractProcess
{
// Construction
public:
   /**
    * Default constructor
    */
//CP20030319   FundToListProcess();
   FundToListProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand );
   virtual ~FundToListProcess();
   const DString& getFirstListItemKey( const GenericInterface *rpGICaller, const BFContainerId& idList );
   const DString& getNextListItemKey( const GenericInterface *rpGICaller, const BFContainerId& idList );
   SEVERITY doSetField( const GenericInterface *rpGICaller, const BFContainerId& idContainer,
                        const BFFieldId& idField, const BFDataGroupId& idDataGroup, const DString& strValue, bool bFormatted );
   void doGetField( const GenericInterface *rpGICaller, const BFContainerId& idContainer, const BFFieldId& idField,
                    const BFDataGroupId& idDataGroup, DString &strValueOut, bool bFormatted ) const;


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
private:

   FundToList        *_pFundToList;
   FundDetailList    *_pFundDetailsList;
   FundMasterList    *_pFundMasterList;
   FundSponsorsList  *_pFundSponsorsList;
   TranslationList   *_pTranslationList;
   FeeInfoInquiry    *_pFeeInfoInquiry;

   DString _fromFundCode;
   DString _fromClassCode;
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/FundToListProcess.hpp-arc  $
//
//   Rev 1.6   Mar 21 2003 17:40:36   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.5   Oct 09 2002 23:53:16   PURDYECH
//PVCS Database Conversion
//
//   Rev 1.4   Aug 29 2002 12:52:34   SMITHDAV
//ClientLocale and typed field changes.
//
//   Rev 1.3   22 May 2002 18:20:58   PURDYECH
//BFData Implementation
//
//   Rev 1.2   19 Mar 2002 13:17:14   PURDYECH
//Use #pragma once as include guard
//Remove compile time "including..." message
//
//   Rev 1.1   Mar 21 2001 13:00:34   FENGYONG
//get fundtolist by fromfund,fromclass or sponsorcode
//
//   Rev 1.0   Dec 04 2000 13:11:32   VASILEAD
//Initial revision.
 *
 */

