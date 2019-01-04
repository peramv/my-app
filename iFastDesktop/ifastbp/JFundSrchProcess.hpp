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
//
// ^FILE   : JFundSrchProcess.hpp
// ^AUTHOR : 
// ^DATE   : 03/09/1999
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : FundSrchProcess
//    This class manages the remarks information.
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************


#include <bfproc\AbstractProcess.hpp>
///#endif

// Forward references
class FundDetailList;
class MgmtCoOptions;
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

class IFASTBP_LINKAGE FundSrchProcess : public AbstractProcess
{
// Construction
public:
   /**
    * Default constructor
    */
//CP20030319   FundSrchProcess();
   FundSrchProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand );
   virtual ~FundSrchProcess();

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
private:

   FundDetailList *_pFundDetailList;
   MgmtCoOptions * _pmgmtcooptions;
   TranslationList *_pTranslationList;

   DString _strInitFundCode;
   DString _strInitClassCode;
   GenericInterface *_rpChildGI;
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/JFundSrchProcess.hpp-arc  $
 * 
 *    Rev 1.9   Mar 21 2003 17:44:08   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.8   Mar 09 2003 15:56:08   PURDYECH
 * Small fixes around DataGroupIds and ContainerIds.
 * 
 *    Rev 1.7   Oct 09 2002 23:53:26   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.6   22 May 2002 18:20:28   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.5   19 Mar 2002 13:17:50   PURDYECH
 * Use #pragma once as include guard
 * Remove compile time "including..." message
 * 
 *    Rev 1.4   Aug 22 2000 16:58:42   FENGYONG
 * Fix French Fundname
 * 
 *    Rev 1.3   Jul 26 2000 11:45:48   VASILEAD
 * Added AccessAllSlsRep field in logon transaction
 * 
 *    Rev 1.2   Mar 24 2000 12:22:50   POPESCUS
 * Make things happen for Vision
// 
//    Rev 1.1   Feb 29 2000 15:29:30   FENGYONG
// Add CurrentDate
// 
//    Rev 1.0   Nov 24 1999 09:26:36   FENGYONG
// Initial revision.
 * 
 *
 */

