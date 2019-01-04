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
#include <ifastbp\ifasthistoricalparameters.hpp>

///#endif

// Forward references
class EntityList;
class EntityIdsList;

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

//Forward declaration
class AccountEntityXref;
class Entity;

class IFASTBP_LINKAGE EntityProcess : public AbstractProcess,
   public IFastHistoricalParameters

{
// Construction
public:
   /**
    * Default constructor
    */
//CP20030319   EntityProcess();
   EntityProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand );
   virtual ~EntityProcess();
   const DString& getFirstListItemKey( const GenericInterface *rpGICaller, const BFContainerId& idList );
   const DString& getNextListItemKey( const GenericInterface *rpGICaller, const BFContainerId& idList );
   SEVERITY performSearch( GenericInterface *rpGICaller, const BFContainerId& idSearch, E_SEARCHACTION eSearchAction );
   const DString& getKeyForNewListItem( const GenericInterface *rpGICaller, const BFContainerId& idList );
   SEVERITY deleteItemFromList( const GenericInterface *rpGICaller, const BFContainerId& idList );
   SEVERITY setData( GenericInterface *rpGICaller, const BFContainerId& idContainer, const BFData *rpData );

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
   SEVERITY doSetField(
                      const GenericInterface *rpGICaller, 
                      const BFContainerId& idContainer,
                      const BFFieldId& idField, 
                      const BFDataGroupId& idDataGroup, 
                      const DString& strValueOut, 
                      bool bFormatted
                      );
   void doGetField(
                  const GenericInterface *rpGICaller, 
                  const BFContainerId& idContainer, 
                  const BFFieldId& idField,
                  const BFDataGroupId& idDataGroup, 
                  DString &strValueOut, 
                  bool bFormatted
                  ) const;
   SEVERITY doGetErrors( const GenericInterface *rpGICaller, const BFContainerId& idContainer,
                         const BFFieldId& idField, const BFDataGroupId& idDataGroup, CONDITIONVECTOR &conditions ) const;
   const BFProperties *doGetFieldAttributes( const GenericInterface *rpGICaller, const BFContainerId& idContainer, const BFFieldId& idField, const BFDataGroupId& idDataGroup );
   /**
     * Set up the list and get parameters.
     * @returns SEVERITY noting any error/warning conditions
     */
   virtual SEVERITY doInit();
   virtual bool doModelessChildComplete( const Command &cmd );
   virtual bool doModelessSetFocus( GenericInterface *rpGICaller );
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
/*   virtual bool doRefresh(
      GenericInterface *rpGICaller,
      const I_CHAR *szOriginalCommand
      )
   {
      return false;
   }*/
/*   void setCurrentListItem(const GenericInterface *rpGICaller, const BFContainerId& idList,const DString& strListItemKey);
   const DString&  getFirstListItemKey( const GenericInterface *rpGICaller,const BFContainerId& idList);
   const DString&  getNextListItemKey( const GenericInterface *rpGICaller,const BFContainerId& idList); */

   virtual bool doRefresh(
                         GenericInterface *rpGICaller,
                         const I_CHAR *szOriginalCommand
                         );

   bool doOk( GenericInterface *rpGICaller );

   void * getPtrForContainer(const BFContainerId& idContainer, const BFDataGroupId& idDataGroup);
   virtual bool doSend( GenericInterface* rpGICaller,const I_CHAR* szMessage );

   virtual bool setCommitDataGroupAsHost()
   {
      return(false); 
   }
   virtual void doPostOk( GenericInterface *rpGICaller, bool bSuccessFlag );
   SEVERITY getHistoricalParameters( const BFContainerId& idContainer, HISTORICAL_VECTOR &vectorInput );
   virtual void setCurrentListItem(const GenericInterface *rpGICaller,
                                       const BFContainerId& idList, 
                                       const DString& strListItemKey);

private:
   DString _accNum;
   DString _entityId;
   DString _dstrCreatingAccount;
   DString _dstrCreatingShareholder;
   DString selectionKey;
   DString strKey;
   AccountEntityXref *_pAccountEntityXref;
   EntityIdsList *_pEntityIdsList;
   GenericInterface *_rpChildGI;
   bool flg_no_account;
   bool flg_copy_entity;
   DString _dstrOrgKey;
   DString _dstrDestKey;
   DString _modelAcctNum;

   DString _originalDeathDate;
   DString _originalDeathOfNotifDate;

   std::set < DString > setEntityIds;
   std::set < DString > setEntityOwnerIds;
};


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/EntityProcess.hpp-arc  $
 * 
 *    Rev 1.18   Jan 12 2009 11:13:32   jankovii
 * IN 1549377 Estate and Death of Notification acct category can only be added by the system
 * 
 *    Rev 1.17   Jun 03 2004 15:35:56   popescu
 * PTS 10030936, refreshed Shareholder if entity account owner or nominee account owner gets updated
 * 
 *    Rev 1.16   Apr 23 2004 17:32:56   HERNANDO
 * PET1027 FN02 - Added setEntityIDs.
 * 
 *    Rev 1.15   Feb 28 2004 16:06:16   HERNANDO
 * PET965 FN11 - Additional historical enhancement.
 * 
 *    Rev 1.14   Mar 21 2003 17:38:58   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.13   Oct 09 2002 23:53:10   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.12   Aug 29 2002 12:52:18   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.11   Jul 12 2002 15:19:24   FENGYONG
 * Add doPostOk
 * 
 *    Rev 1.10   Jun 03 2002 14:13:12   FENGYONG
 * override "setCommitDataGroupAsHost" for NASU API
 * 
 *    Rev 1.9   22 May 2002 18:21:16   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.8   19 Mar 2002 13:16:56   PURDYECH
 * Use #pragma once as include guard
 * Remove compile time "including..." message
 * 
 *    Rev 1.7   06 Dec 2001 16:21:18   KOVACSRO
 * Added doOk.
 * 
 *    Rev 1.6   Sep 12 2001 10:47:46   ZHANGCEL
 * Added a new member data: modelAcctNum
 * 
 *    Rev 1.5   Jun 04 2001 15:00:06   YINGBAOL
 * add doRefresh method
 * 
 *    Rev 1.4   Dec 20 2000 09:59:36   ZHANGCEL
 * Added three variables for the CopyEntity requirement
 * 
 *    Rev 1.3   Oct 19 2000 14:36:06   VASILEAD
 * Added setData
 * 
 *    Rev 1.2   Aug 02 2000 15:31:40   BUZILA
 * "locale" changes
 * 
 *    Rev 1.1   Feb 15 2000 18:56:26   MCNABBGL
 * changed comment format
 * 
 *    Rev 1.0   Feb 15 2000 10:59:06   SMITHDAV
 * Initial revision.
 * 
 *    Rev 1.16   Jan 23 2000 16:44:48   VASILEAD
 * Reset functionality
 * 
 *    Rev 1.15   Jan 21 2000 10:33:30   VASILEAD
 * implemented doGetFieldAttributes
 * 
 *    Rev 1.14   Jan 13 2000 17:39:38   VASILEAD
 * Added support for catching errors
 * 
 *    Rev 1.13   Dec 21 1999 10:42:14   VASILEAD
 * Added Entity list iteration based on the string keys and not on the ObjectKey, added background search support
 * 
 *    Rev 1.12   Dec 15 1999 10:44:12   VASILEAD
 * Implemented background search for Entity screen
 * 
 *    Rev 1.11   Dec 10 1999 11:58:42   VASILEAD
 * Added refresh support
 * 
 *    Rev 1.10   Nov 23 1999 18:05:42   POPESCUS
 * NASU flow
 * 
 *    Rev 1.9   Nov 21 1999 13:36:02   VASILEAD
 * Added support for creating a new entity
 * 
 *    Rev 1.8   Nov 20 1999 13:14:38   VASILEAD
 * Worked on entity - account relationship
 * 
 *    Rev 1.7   Nov 02 1999 14:03:56   BUZILA
 * removed doOk and doCancel methods
 * 
 *    Rev 1.6   27 Oct 1999 13:22:30   ZARKHINE
 * Nested List Functionality added
 * 
 *    Rev 1.5   Aug 31 1999 14:25:58   DT24433
 * changed doGetField parms
 * 
 *    Rev 1.4   Aug 31 1999 14:42:50   YINGBAOL
 * addSubstituleList
 * 
 *    Rev 1.3   Jul 28 1999 12:04:36   BUZILA
 * added to EntityProcess the getField(...) method 
 * 
 *    Rev 1.2   Jul 27 1999 15:03:20   BUZILA
 * First M2 revision
 * 
 *    Rev 1.1   Jul 08 1999 10:03:42   SMITHDAV
 * Modify revision history commaent format to old
 * style comment -- I can't seem to get new style comments to work.
 *
 */
