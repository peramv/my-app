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
class JAdvisorSumm;
class TranslationList;

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

class IFASTBP_LINKAGE AdvisorSummProcess : public AbstractProcess
{
// Construction
public:
   /**
    * Default constructor
    */
//CP20030319   AdvisorSummProcess();
   AdvisorSummProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand );
   virtual ~AdvisorSummProcess();

protected:
   /**
     * Set up the list and get parameters.
     * @returns SEVERITY noting any error/warning conditions
     */
   virtual SEVERITY doInit();

   virtual bool doGetData(
                         GenericInterface * rpGICaller,
                         BFData * 
                         ) const;
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
                         )
   {
      return(false);
   }
private:

   JAdvisorSumm *_pJAdvisorSumm;
   TranslationList *_pTranslationList;
   GenericInterface *_rpChildGI;
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/JAdvisorSummProcess.hpp-arc  $
 * 
 *    Rev 1.7   Mar 21 2003 17:43:06   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.6   Oct 09 2002 23:53:22   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.5   22 May 2002 18:20:34   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.4   19 Mar 2002 13:17:42   PURDYECH
 * Use #pragma once as include guard
 * Remove compile time "including..." message
 * 
 *    Rev 1.3   Aug 22 2000 16:58:34   FENGYONG
 * Fix French Fundname
 * 
 *    Rev 1.2   Jul 05 2000 13:45:06   VASILEAD
 * Added ShortName from TranslationList
 * 
 *    Rev 1.1   Mar 24 2000 12:22:46   POPESCUS
 * Make things happen for Vision
// 
//    Rev 1.0   Feb 25 2000 16:19:28   FENGYONG
// Initial revision.
// 
// Initial revision.
 * 
 *
 */

