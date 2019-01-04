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
class MFAccountHoldingList;
class MFAccountList;
class MFAccount;
class TranslationList;
class FundMasterList;
class FundSponsorsList;
class AccountDistributionList;
class PendingTradeList;
class Demographics;

// Import/Export resolution
#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif

typedef std::map< DString, DString, std::less<DString> > FUND_SORT;
typedef std::map< DString, DString, std::less<DString> >::iterator FUND_SORT_ITER;
/**
 * Class that manages the Historical Market Value process.
 *
 * @author Yakov Prager
 * </dd></dl><p><dl><dt><b>Date Created:</b></dt><dd> 03/09/1999</dd></dl>
 * @version 0.1
 */

class IFASTBP_LINKAGE AcctDetlProcess : public AbstractProcess
{
// Construction
public:
   /**
    * Default constructor
    */
//CP20030319   AcctDetlProcess();
   AcctDetlProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand );
   virtual ~AcctDetlProcess();
   const DString& getFirstListItemKey( const GenericInterface *rpGICaller, const BFContainerId& idList );
   const DString& getNextListItemKey( const GenericInterface *rpGICaller, const BFContainerId& idList );
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

   virtual void setCurrentListItem(
                                  const GenericInterface *rpGICaller,
                                  const BFContainerId& idList,
                                  const DString& strListItemKey
                                  );

   void doGetField(
                  const GenericInterface *rpGICaller, 
                  const BFContainerId& idContainer, const BFFieldId& idField, 
                  const BFDataGroupId& idDataGroup, 
                  DString &strValueOut, 
                  bool bFormatted
                  ) const;

   void sortFundByShortName( GenericInterface *pGI, 
                             const BFContainerId& idContainer, const BFFieldId& fundCode, 
                             const BFFieldId& classCode, const BFContainerId& idTranslationList, 
                             DString& language, FUND_SORT* resultMap );

private:

   MFAccountHoldingList *_pMFAccountHoldingList;
   MFAccountList *_pMFAccountList;
   MFAccount *_pMFAccount;
   TranslationList * _pTranslationList;
   FundMasterList  *_pFundMasterList;
   FundSponsorsList *_pFundSponsorsList;
   AccountDistributionList *rpAccDistributionList;
   PendingTradeList * _pPendingTradeList;
   Demographics * _pDemographics;

   DString _strInitFundCode, language;
   DString  strAccountNumber;
   DString _strInitClassCode;
   GenericInterface *_rpChildGI;

   FUND_SORT holdingfundNameSort;
   FUND_SORT_ITER holdingiter;
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/JAcctDetlProcess.hpp-arc  $
 * 
 *    Rev 1.16   Mar 21 2003 17:42:44   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.15   Mar 09 2003 15:55:50   PURDYECH
 * Small fixes around DataGroupIds and ContainerIds.
 * 
 *    Rev 1.14   Oct 09 2002 23:53:20   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.13   Aug 29 2002 12:52:46   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.12   22 May 2002 18:20:46   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.11   19 Mar 2002 13:17:38   PURDYECH
 * Use #pragma once as include guard
 * Remove compile time "including..." message
 * 
 *    Rev 1.10   May 08 2001 10:33:48   FENGYONG
 * Add sorting by fundname  and dogetfield
 * 
 *    Rev 1.9   Mar 29 2001 12:12:58   FENGYONG
 * Add managementstyle
 * 
 *    Rev 1.8   Feb 13 2001 17:16:32   FENGYONG
 * Add pending tradelist for trading page
 * 
 *    Rev 1.7   Dec 15 2000 16:54:22   FENGYONG
 * remove #3
 * 
 *    Rev 1.6   Dec 01 2000 16:57:40   FENGYONG
 * Add acctdistribution list
 * 
 *    Rev 1.5   Nov 28 2000 14:44:16   FENGYONG
 * Add fundsponser
 * 
 *    Rev 1.4   Aug 22 2000 16:56:30   FENGYONG
 * Fix French Fundname and French desc
 * 
 *    Rev 1.3   Jul 05 2000 13:45:08   VASILEAD
 * Added ShortName from FundMasterList
 * 
 *    Rev 1.2   Mar 24 2000 12:22:46   POPESCUS
 * Make things happen for Vision
// 
//    Rev 1.2   Mar 06 2000 15:50:22   FENGYONG
// Add Firstname & Lastname
// 
//    Rev 1.1   Nov 25 1999 11:52:46   FENGYONG
// Changed with MFAccount 
 * 
 *
 */

