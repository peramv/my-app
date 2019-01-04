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
#include <bfproc\abstractprocess.hpp>

// Forward references
class AccountSearchList;
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

class IFASTBP_LINKAGE AccountSearchProcess : public AbstractProcess
{
// Construction
public:
   /**
    * Default constructor
    */
//CP20030319   AccountSearchProcess();
   AccountSearchProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand );
   virtual ~AccountSearchProcess();

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
   };

   virtual void setCurrentListItem(
                                  const GenericInterface *rpGICaller,
                                  const BFContainerId& idList,
                                  const DString& strListItemKey
                                  );

   void doGetField(
                  const GenericInterface *rpGICaller,  
                  const BFContainerId& idContainer, 
                  const BFFieldId& idField, 
                  const BFDataGroupId& idDataGroup, 
                  DString &strValueOut, 
                  bool bFormtted
                  ) const;
private:
   AccountSearchList* _pAccountSearchList;
   GenericInterface *_rpChildGI;

//	MFAccount *_pMFAccount;
   DString _SrchAltAcct, _SrchBrokerCode, _OneAcctOnly;
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/AccountSearchProcess.hpp-arc  $
//
//   Rev 1.5   Mar 21 2003 17:34:46   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.4   Oct 09 2002 23:52:58   PURDYECH
//PVCS Database Conversion
//
//   Rev 1.3   Aug 29 2002 12:51:32   SMITHDAV
//ClientLocale and typed field changes.
//
//   Rev 1.2   22 May 2002 18:21:56   PURDYECH
//BFData Implementation
//
//   Rev 1.1   19 Mar 2002 13:14:50   PURDYECH
//Use #pragma once as include guard
//Remove compile time "including..." message
//
//   Rev 1.0   Jan 25 2002 11:57:48   FENGYONG
//Initial revision.
 * 
 */

