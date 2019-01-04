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
// ^FILE   : JPendingProcessProcess.hpp
// ^AUTHOR : Yongmei Feng
// ^DATE   : 09/05/2000
//
// ----------------------------------------------------------
//
// ^CLASS    : JPendingProcessProcess
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :  This is the code for the Transaction Details dialog
//
//******************************************************************************


#include <bfproc\AbstractProcess.hpp>
///#endif

// Forward references
class FundDetailList;
class TranslationList;
class PendingTradeList;
class MgmtCoOptions;
class AddressList;
class BFObjIter;

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

class IFASTBP_LINKAGE JPendingProcess : public AbstractProcess
{
// Construction
public:
   /**
    * Default constructor
    */
//CP20030319   JPendingProcess();
   JPendingProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand );
   virtual ~JPendingProcess();
protected:
   /**
     * Provide class specific implementation for some fields.
     * An exception will be thrown if the field cannot be found.
     * @param rpGICaller - A reference pointer to the calling object.
     * @param idContainer - ID of container we are using.
     * @param idField - ID of field we are getting.
     * @param strValue - A string reference where value is returned.
     * @param bFormatted - Flag where true means get data formatted.
     */
   virtual bool doGetData(
                         GenericInterface * rpGICaller,
                         BFData * 
                         ) const;
   /**
     * Set up the list and get parameters.
     * @returns SEVERITY noting any error/warning conditions
     */
   virtual SEVERITY doInit();
   /**
     * Implementation to support the modelessChildComplete method.
     * modelessChildComplete is used by the GenericInterfaceContainer to tell
     * the parent that the modeless child has been destroyed.
     * @param cmd - A reference to a command representing the object that has
     * been destroyed.
     * @returns true if this modeless object should end as well, false if not
     * done yet.  When returning true, the calling modelessChildComplete method
     * will call GenericInterfaceContainer::modelessDestroySelf to delete and
     * remove this object from the container
     */
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

   void* getPtrForContainer( const BFContainerId& idContainer, const BFDataGroupId& idDataGroup );

private:
   DString _AccountNum,_TransId,_ShareholderNum,_FundCode,_ClassCode,_NumEntry,_AllFundMode,_TransType,_TransNum,_TradeDate,_EntityId;
   DString _BrokerCode, _BranchCode, _SlsRepCode, _acctnum, _pPendingDetailsOnly;
   PendingTradeList *_pPendingTradeList;
   FundDetailList *_pFundDetailList;
   TranslationList *_pTranslationList;
   MgmtCoOptions * _pmgmtcooptions;
   AddressList *_pAddressList;
   GenericInterface *_rpChildGI;
};

///#endif 

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/JPendingProcess.hpp-arc  $
//
//   Rev 1.10   Mar 21 2003 17:44:14   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.9   Oct 09 2002 23:53:26   PURDYECH
//PVCS Database Conversion
//
//   Rev 1.8   Aug 29 2002 12:52:56   SMITHDAV
//ClientLocale and typed field changes.
//
//   Rev 1.7   22 May 2002 18:20:30   PURDYECH
//BFData Implementation
//
//   Rev 1.6   19 Mar 2002 13:17:50   PURDYECH
//Use #pragma once as include guard
//Remove compile time "including..." message
//
//   Rev 1.5   Mar 18 2001 18:18:00   VASILEAD
//Fixes for UAT release
//
//   Rev 1.4   Mar 12 2001 12:58:36   VASILEAD
//Modified for FUNDcom release
//
//   Rev 1.3   Dec 14 2000 15:53:58   FENGYONG
//remove #3
//
//   Rev 1.2   Oct 04 2000 13:50:40   FENGYONG
//Add EntityList to get firstname and lastname
//
//   Rev 1.1   Sep 13 2000 16:55:30   FENGYONG
//Add brokercode, branchcode,slsrep
//
//   Rev 1.0   Sep 07 2000 11:56:56   FENGYONG
//Initial revision.
 * 
 */
