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
//    AUTHOR : Serban Popescu
//    DATE   : 28/07/99
//
//
//    Copyright 1997 by DST Systems, Inc.
//
//******************************************************************************


#include <bfproc\AbstractProcess.hpp>
///#endif

// Forward references
class EntitySearchList;

// Import/Export resolution
#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif

/**
 * Class executes the search for entities!
 *
 * @author Serban Popescu
 * </dd></dl><p><dl><dt><b>Date Created:</b></dt><dd> 25/06/1999</dd></dl>
 * @version 0.1
 */

class IFASTBP_LINKAGE EntitySearchProcess : public AbstractProcess
{
// Construction
public:
   EntitySearchProcess ( GenericInterfaceContainer *pGIC, 
                         GenericInterface *pGIParent, 
                         const Command& rCommand);
   virtual ~EntitySearchProcess();
   static const int getEntitySearchCboType (const DString &usingCode);
   virtual bool doMoreRecordsExist( GenericInterface *rpGICaller, 
                                    const BFContainerId& idSearch );
   virtual SEVERITY performSearch (GenericInterface *rpGI, 
                                   const BFContainerId &idSearch, 
                                   E_SEARCHACTION eSearchAction );
protected:
   virtual SEVERITY doInit();
   bool doModelessChildComplete (const Command &cmd);
   virtual E_COMMANDRETURN doProcess();
   virtual void *getPtrForContainer( const BFContainerId& idContainer,
                                     const BFDataGroupId& idDataGroup);
   virtual bool doOk (GenericInterface *rpGICaller);
   virtual void doGetField (const GenericInterface *rpGICaller,
                            const BFContainerId &idContainer, 
                            const BFFieldId &idField, 
                            const BFDataGroupId& idDataGroup, 
                            DString &strValueOut, 
                            bool bFormatted) const;
private:
   EntitySearchList* _pEntitySearchList;

   DString _entityID,
      _searchCode,
      _firstValue,
      _secondValue,
      _entitySearch,
      _tradeSearch,
      _accountNum,
      _entityBackgroundSearch,
      _allEntity,
      _exactSearch,
      _noVerifySearchIfOneMatch,
      _fromScreen,
      _acctExsistencySearch,
      _showSameEntityMultipleTimes;
};


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/EntitySearchProcess.hpp-arc  $
 * 
 *    Rev 1.13   12 Jul 2007 18:41:08   popescu
 * GAP 6 - CIF - added two new search types on the main screen - by CIF and by AccessID
 * 
 *    Rev 1.12   Apr 14 2005 11:07:00   popescu
 * Incident #262507, Multiple a/c with same alternate a/c
 * 
 *    Rev 1.11   Mar 09 2005 14:37:34   yingbaol
 * PET1171,FN01: EUSD entity search support
 * 
 *    Rev 1.10   Dec 07 2004 02:45:00   popescu
 * PET 1117/56, verify search won't pop-up if alt acct/other ref # search returns one match
 * 
 *    Rev 1.9   Nov 05 2004 16:25:42   FENGYONG
 * PET1117 FN54 Fund Broker Static : Add AllEntityField and ExactSearch 
 * 
 *    Rev 1.8   Mar 21 2003 17:39:06   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.7   Feb 17 2003 18:11:44   popescu
 * WrapAccount field bug fix
 * 
 *    Rev 1.6   Oct 09 2002 23:53:12   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.5   22 May 2002 18:21:18   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.4   19 Mar 2002 13:16:58   PURDYECH
 * Use #pragma once as include guard
 * Remove compile time "including..." message
 * 
 *    Rev 1.3   Aug 16 2000 14:59:46   YINGBAOL
 * implement function "search for Trade"
 * 
 *    Rev 1.2   Mar 03 2000 12:11:06   POPESCUS
 * account search work
 * 
 *    Rev 1.1   Feb 15 2000 18:56:26   MCNABBGL
 * changed comment format
 * 
 *    Rev 1.0   Feb 15 2000 10:59:08   SMITHDAV
 * Initial revision.
// 
//    Rev 1.6   Jan 28 2000 12:27:04   POPESCUS
// fixes for more button
// 
//    Rev 1.5   Jan 14 2000 09:10:20   POPESCUS
// updated VerifySearch to the new control model
// 
//    Rev 1.4   Dec 15 1999 10:44:08   VASILEAD
// Implemented background search for Entity screen
// 
//    Rev 1.3   Oct 28 1999 19:04:46   DT24433
// changed from doOK to ok2
// 
//    Rev 1.2   Oct 18 1999 15:16:10   POPESCUS
// 
//    Rev 1.1   Oct 05 1999 09:46:56   HUANGSHA
// Set focus on the selected entity if search for the AltAccount + BrokerCode
// 
//    Rev 1.0   Jul 28 1999 13:16:48   POPESCUS
// Initial revision.
 */
