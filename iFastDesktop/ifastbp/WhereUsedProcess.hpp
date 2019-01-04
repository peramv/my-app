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
//    AUTHOR : Mihai Virgil Buzila
//    DATE   : 16/04/99
//
//
//    Copyright 1997 by DST Systems, Inc.
//
//******************************************************************************


#include <bfproc\AbstractProcess.hpp>
///#endif

class AccountEntityXref;
class WhereUsedList;

// Import/Export resolution
#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif

class IFASTBP_LINKAGE WhereUsedProcess : public AbstractProcess
{
public:
//CP20030319   WhereUsedProcess();
   WhereUsedProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand );
   virtual ~WhereUsedProcess();
   virtual const DString& getFirstListItemKey( const GenericInterface *rpGICaller, const BFContainerId& idList );
   virtual const DString& getNextListItemKey( const GenericInterface *rpGICaller, const BFContainerId& idList );
   virtual bool doMoreRecordsExist( GenericInterface *rpGICaller, 
                                    const BFContainerId& idContainer );
   SEVERITY performSearch( GenericInterface *rpGICaller, const BFContainerId& idSearch, E_SEARCHACTION eSearchAction );

protected:
   virtual SEVERITY doInit();
   virtual bool doModelessChildComplete(
                                       const Command &cmd
                                       );
   virtual E_COMMANDRETURN doProcess();
   virtual bool doRefresh( GenericInterface *rpGICaller, const I_CHAR *szOriginalCommand )
   {
      return(true);
   };
   virtual  void doGetField(
                               const GenericInterface *rpGICaller,
                               const BFContainerId& idContainer,
                               const BFFieldId& idField,
                               const BFDataGroupId& idDataGroup,
                               DString &strValueOut,
                               bool bFormatted
                               ) const;


private:
   AccountEntityXref *_pAccountEntityXref;
   WhereUsedList *_pWhereUsedList;
   GenericInterface  *_rpChildGI;

   DString              _dstrEntityID;
   DString              _dstrEntityName;
   DString              _dstrEntityBirtyName;
};


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/WhereUsedProcess.hpp-arc  $
 * 
 *    Rev 1.6   May 17 2005 11:32:44   Fengyong
 * #Incident 272055 - Add more button to where used screen
 * 
 *    Rev 1.5   Apr 21 2005 13:20:46   yingbaol
 * Incident290503: add dogetField method
 * 
 *    Rev 1.4   Mar 21 2003 17:50:10   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.3   Oct 09 2002 23:53:44   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.2   19 Mar 2002 13:20:14   PURDYECH
 * Use #pragma once as include guard
 * Remove compile time "including..." message
 * 
 *    Rev 1.1   Feb 15 2000 18:57:06   MCNABBGL
 * changed comment format
 * 
 *    Rev 1.0   Feb 15 2000 10:59:28   SMITHDAV
 * Initial revision.
// 
//    Rev 1.7   Jan 14 2000 08:51:32   POPESCUS
// finally made those dialogs and processes work
// 
//    Rev 1.6   Dec 07 1999 14:20:02   YINGZ
// add group to doset/get fiels
// 
//    Rev 1.5   Nov 11 1999 17:54:00   VASILEAD
// Changed to the new AccountEntityXref list
// 
//    Rev 1.4   Oct 29 1999 14:30:44   DT24433
// removed doOk/doCancel
// 
//    Rev 1.3   Oct 27 1999 12:56:54   ZHANGCEL
// add new process WhereUsedList
// 
//    Rev 1.2   Aug 30 1999 18:46:10   DT24433
// changed dogetfield/dosetfield parms
// 
//    Rev 1.1   Jul 27 1999 16:03:38   BUZILA
// Increment M2
// 
//    Rev 1.0   Jul 22 1999 17:22:50   BUZILA
// Initial revision.
*/ 
