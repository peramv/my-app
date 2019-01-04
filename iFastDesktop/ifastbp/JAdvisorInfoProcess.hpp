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
class AdvisorList;
class JBrokerList;
class JBranchList;

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

class IFASTBP_LINKAGE AdvisorInfoProcess : public AbstractProcess
{
// Construction
public:
   /**
    * Default constructor
    */
//CP20030319   AdvisorInfoProcess();
   AdvisorInfoProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand );
   virtual ~AdvisorInfoProcess();

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

   virtual void setCurrentListItem(
                                  const GenericInterface *rpGICaller,
                                  const BFContainerId& idList,
                                  const DString& strListItemKey
                                  );
   /**
     * Implementation to support the ok method.  This method would be invoked
     * when the user completes the logon screen.  The logon process will 
     * attempt to logon and return accordingly.
     * @param rpGICaller - A reference pointer to the calling object.
     * @returns true if successful, call getErrors for errors if false
     */
   virtual void doPostOk(
                        GenericInterface *rpGICaller,
                        bool bSuccessFlag
                        );
private:

   AdvisorList *_pAdvisorList;
   JBrokerList * _pJBrokerList;
   JBranchList * _pJBranchList;
   GenericInterface *_rpChildGI;
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/JAdvisorInfoProcess.hpp-arc  $
 * 
 *    Rev 1.8   Mar 21 2003 17:42:58   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.7   Oct 09 2002 23:53:22   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.6   22 May 2002 18:20:48   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.5   19 Mar 2002 13:17:40   PURDYECH
 * Use #pragma once as include guard
 * Remove compile time "including..." message
 * 
 *    Rev 1.4   Jan 17 2002 14:57:52   FENGYONG
 * change name for api
 * 
 *    Rev 1.3   Sep 06 2000 11:47:00   YINGZ
 * get MgmtCoOptions from MgmtCo
 * 
 *    Rev 1.2   Mar 30 2000 15:44:56   FENGYONG
 * Add CurrentDate
 * 
 *    Rev 1.1   Mar 24 2000 12:22:46   POPESCUS
 * Make things happen for Vision
// 
//    Rev 1.2   Mar 21 2000 14:19:02   FENGYONG
// fix bug
// 
//    Rev 1.1   Feb 29 2000 15:28:38   FENGYONG
// Add Fileds
// 
//    Rev 1.0   Dec 18 2000 09:26:36   FENGYONG
// Initial revision.
 * 
 *
 */

