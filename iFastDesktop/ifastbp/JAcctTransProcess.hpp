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
//
// ^FILE   : TransactionHistoryProcess.hpp
// ^AUTHOR : Yongmei Feng
// ^DATE   : 03/11/1999
//
// ----------------------------------------------------------
//
// ^CLASS    : TransactionHistoryProcess
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :  This is the code for the Transaction Details dialog
//
//******************************************************************************



#include <bfproc\AbstractProcess.hpp>
///#endif

// Forward references
class TransactionList;
class TransactionDetails;
class FundDetailList;
class MgmtCoOptions;
class TranslationList;
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

class IFASTBP_LINKAGE AcctTransProcess : public AbstractProcess
{
// Construction
public:
   /**
    * Default constructor
    */
//CP20030319   AcctTransProcess();
   AcctTransProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand );
   virtual ~AcctTransProcess();
protected:
   virtual bool doGetData(
                         GenericInterface * rpGICaller,
                         BFData * 
                         ) const;
   /**
     * Set up the list and get parameters.
     * @returns SEVERITY noting any error/warning conditions
     */
   virtual SEVERITY doInit();
   virtual bool doMoreRecordsExist(
                                  GenericInterface *rpGICaller,
                                  const BFContainerId& idContainer 
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
                         );
/*	virtual void setCurrentListItem(
      const GenericInterface *rpGICaller,
      const BFContainerId& idList,
      const DString& strListItemKey
      );
  */

   void doGetField(
                  const GenericInterface *rpGICaller, 
                  const BFContainerId& idContainer, const BFFieldId& idField, 
                  const BFDataGroupId& idDataGroup, 
                  DString &strValueOut, 
                  bool bFormatted
                  ) const;

private:
   TransactionList *_pTransHistoryList;
   TransactionDetails *_pTransDetails;
   FundDetailList *_pFundDetailList;
   MgmtCoOptions * _pmgmtcooptions;
   TranslationList * _pTranslationList;
   MFAccount * _pMFAccount;
   GenericInterface *_rpChildGI;

   DString AccountNum;
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/JAcctTransProcess.hpp-arc  $
 * 
 *    Rev 1.12   Mar 21 2003 17:42:50   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.11   Oct 09 2002 23:53:20   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.10   Aug 29 2002 12:52:46   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.9   22 May 2002 18:20:46   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.8   19 Mar 2002 13:17:38   PURDYECH
 * Use #pragma once as include guard
 * Remove compile time "including..." message
 * 
 *    Rev 1.7   Dec 14 2000 15:53:54   FENGYONG
 * remove #3
 * 
 *    Rev 1.6   Aug 22 2000 16:57:26   FENGYONG
 * Fix French fundname and French Desc
 * 
 *    Rev 1.5   Jun 28 2000 12:01:30   VASILEAD
 * Adapted to the new views
 * 
 *    Rev 1.4   Jun 16 2000 10:35:46   VASILEAD
 * Reduced the number of transacions to be sent
 * 
 *    Rev 1.3   May 16 2000 14:32:40   YINGZ
 * support usedateflag
 * 
 *    Rev 1.2   Mar 24 2000 12:22:46   POPESCUS
 * Make things happen for Vision
// 
//    Rev 1.5   Mar 06 2000 15:50:52   FENGYONG
// Add currentdate
// 
//    Rev 1.4   Mar 01 2000 16:11:06   FENGYONG
// Add Currentdate
// 
//    Rev 1.3   Dec 16 1999 11:48:02   DT24433
// removed doOk/doCancel, unused headers
// 
//    Rev 1.2   Dec 15 1999 10:10:26   FENGYONG
// Add calculation of grossamt
// 
//    Rev 1.1   Nov 30 1999 11:01:56   FENGYONG
// Modified to adapt multipages
// 
//    Rev 1.0   Nov 22 1999 11:23:02   FENGYONG
// Initial revision.
 * 
 *    Rev 1.5   Sep 27 1999 13:55:54   YINGZ
 * add dosetfield
 * 
 *    Rev 1.4   Aug 31 1999 12:23:52   DT24433
 * changed dogetfield parms
 * 
 *    Rev 1.3   Jul 30 1999 14:04:32   YINGZ
 * grey pending when there is no pending
 * 
 *    Rev 1.2   Jul 22 1999 14:59:28   YINGZ
 * process amount and units in pending
 * 
 *    Rev 1.1   Jul 08 1999 10:04:02   SMITHDAV
 * Modify revision history commaent format to old
 * style comment -- I can't seem to get new style comments to work.
 *
 */

///#endif 
