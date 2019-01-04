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


#include <bfproc\AbstractProcess.hpp>
///#endif

// Import/Export resolution
#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif

/**
 * Class that manages the search process, which defines the search criterias
 * and builds a list of accounts.
 *
 * @author Serban Popescu
 * </dd></dl><p><dl><dt><b>Date Created:</b></dt><dd> 03/08/1999</dd></dl>
 * @version 0.1
 */

class IFASTBP_LINKAGE SearchProcess : public AbstractProcess
{
// Construction
public:
   /**
    * Default constructor
    */
//CP20030319   SearchProcess();
   SearchProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand );
   virtual ~SearchProcess();
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
   DString _searchCriteria;
   DString _searchUsing;
   DString _firstValue;
   DString _secondValue;
   DString _thirdValue;
   DString _backgroundSearch;
   DString _allEntity;
   DString _exactSearch;
   DString _noVerifySearchIfOneMatch;
   DString _showSameEntityMultipleTimes;
   DString _whereUsedCode;
};


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/SearchProcess.hpp-arc  $
 * 
 *    Rev 1.11   Apr 27 2012 09:52:12   if991250
 * CPF - Account Setup & Settlement 
 * 
 *    Rev 1.10   Apr 14 2005 11:07:04   popescu
 * Incident #262507, Multiple a/c with same alternate a/c
 * 
 *    Rev 1.9   Dec 07 2004 02:45:04   popescu
 * PET 1117/56, verify search won't pop-up if alt acct/other ref # search returns one match
 * 
 *    Rev 1.8   Nov 05 2004 16:25:38   FENGYONG
 * PET1117 FN54 Fund Broker Static : Add AllEntityField and ExactSearch 
 * 
 *    Rev 1.7   Aug 10 2004 11:13:48   FENGYONG
 * PET117 FN5 - Client Condition Fee
 * 
 *    Rev 1.6   Mar 21 2003 17:47:48   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.5   Oct 09 2002 23:53:36   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.4   22 May 2002 18:19:58   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.3   19 Mar 2002 13:18:26   PURDYECH
 * Use #pragma once as include guard
 * Remove compile time "including..." message
 * 
 *    Rev 1.2   07 Mar 2001 15:41:56   BUZILAMI
 * Broker, Branch, SlsRep Bank Instructions changes
 * 
 *    Rev 1.1   Feb 15 2000 18:56:46   MCNABBGL
 * changed comment format
 * 
 *    Rev 1.0   Feb 15 2000 10:59:22   SMITHDAV
 * Initial revision.
 * 
 *    Rev 1.6   Dec 15 1999 10:44:16   VASILEAD
 * Implemented background search for Entity screen
 * 
 *    Rev 1.5   Oct 29 1999 12:17:54   DT24433
 * removed doOk/doCancel
 * 
 *    Rev 1.4   Oct 18 1999 09:48:10   POPESCUS
 * New search criterias
 * 
 *    Rev 1.3   Jul 28 1999 13:16:06   POPESCUS
 * Added a new process for entity search
 * 
 *    Rev 1.2   Jul 23 1999 10:20:40   POPESCUS
 * Added a new process that will fill the dstc front end combos
 * 
 *    Rev 1.1   Jul 08 1999 10:03:56   SMITHDAV
 * Modify revision history commaent format to old
 * style comment -- I can't seem to get new style comments to work.
 *
 */
