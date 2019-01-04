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

// Import/Export resolution
#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif

// Forward references
class MFAccountList;
class EntityList;
class EntityIdsList;
class MFAccountHoldingList;
class TransactionList;
class PendingTradeList;
class AddressList;
class FundDetailList;
class COANavig;
class UserAccessList;
class Shareholder;
class Address;
class AccountEntityXref;
class MFAccount;
/**
 * Class that manages the entity process.
 *
 * @author 
 * </dd></dl><p><dl><dt><b>Date Created:</b></dt><dd> 03/04/1999</dd></dl>
 * @version 0.1
 */

class IFASTBP_LINKAGE AccountDetailsProcess : public AbstractProcess
{
// Construction
public:
   /**
    * Default constructor
    */
   AccountDetailsProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand );
   virtual ~AccountDetailsProcess();

   const DString& getFirstListItemKey (const GenericInterface *rpGICaller, const BFContainerId &idList);
   const DString& getNextListItemKey (const GenericInterface *rpGICaller, const BFContainerId &idList);
   void setCurrentListItem( const GenericInterface *rpGICaller,
                            const BFContainerId& idList,
                            const DString& strListItemKey);
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
   virtual void doGetField( const GenericInterface *rpGICaller,
                            const BFContainerId& idContainer,
                            const BFFieldId& idField,
                            const BFDataGroupId& idDataGroup,
                            DString &strValueOut,
                            bool bFormatted) const;
   /**
     * This method is used to implement subclass overrides for setField.  The business
     * process must determine where to locate the field.
     * Override this method and set appropriate flags via addFieldDetails,
     * if the derived class must process setField differently than this
     * base class does.
     * @param rpGICaller - A reference pointer to the calling object.
     * @param idContainer - ID of container we are using.
     * @param idField - ID of field we are getting.
     * @param idDataGroup - group ID to use for CBO processing
     * @param strValue - A string reference for the value of the field to be
     * set.
     * @param bFormatted - Flag where true means incoming data is formatted.
     * @returns SEVERITY indicating any errors/warnings encountered.
     */
   virtual SEVERITY doSetField( const GenericInterface *rpGICaller,
                                const BFContainerId& idContainer,
                                const BFFieldId& idField,
                                const BFDataGroupId& idDataGroup,
                                const DString& strValue,
                                bool bFormatted);
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
     * Implementation for the refresh method.  
     * @param rpGICaller - A reference pointer to the calling object.
     * @param szOriginalCommand - A string literal representing the original
     * command issuing the refresh (which may provide a hint on whether this
     * object needs to check for refresh).
     * @returns true if successful, call getErrors for errors if false
     */
   virtual bool doRefresh( GenericInterface *rpGICaller,
                           const I_CHAR *szOriginalCommand);


   void *getPtrForContainer( const BFContainerId& idContainer, const BFDataGroupId& idDataGroup );
   const BFProperties * doGetFieldAttributes( const GenericInterface *rpGICaller, 
                                              const BFContainerId& idContainer, 
                                              const BFFieldId& idField, 
                                              const BFDataGroupId& idDataGroup);
   bool doSend ( GenericInterface * rpGICaller, 
                const I_CHAR * szMessage );
private:
   void getCOAFieldWithInquiryPermission( const GenericInterface *rpGICaller,
                                          const BFContainerId& idList, 
                                          const BFFieldId& idField, 
                                          const I_CHAR* userAccessFunctionCode, 
                                          DString& strValue ) const;

   void getMFAcctField( const GenericInterface *rpGICaller,
                        const BFFieldId& idField,
                        DString &strValueOut,
                        bool bFormatted) const;
   SEVERITY getCurrentMFAccount(MFAccount*& pMFAccount, const BFDataGroupId& idDataGroup);
   SEVERITY getFundDetailList(FundDetailList*& pFundDetailList);
   DString _strEmpty;         // Used only to return an empty string reference
   //MFAccountList *_pMFAccountList;
   AccountEntityXref *_pAccountEntityXref;
   //EntityList *_pEntityList;
   EntityIdsList *_pEntityIdsList;
   Shareholder   *_pShareholder;
   Address*            _pShareHolderAddress;
   MFAccountHoldingList *_pMFAccountHoldingList;
   TransactionList *_pTransactionsList;
   TransactionList *_pAllTransactionsListForOneAccount;
   bool flagAllFunds;
   PendingTradeList *_pPendingTradesList;
   AddressList *_pAddressList;
   FundDetailList *_pFundDetailList;
   COANavig *_pCOANavig;
   UserAccessList* _pUserAccessList;
   DString AccountNumber;
   DString EntityId;
   GenericInterface *_rpChildGI;
   DString HomePhone;
   DString _dstrAltAccountParam;
   DString _dstrBrokerCodeParam;
   DString _dstrShrNum;
   DString EntityIdPos;
   DString _initialEntityId;
   DString _searchCode;
   bool flg_entity_finished;
   DString _newAccountNumber;
   int nNoOfPendingTrades;
   BFObjIter* _pIterAccountEntityXrefOut;
   DString _strCurrentFundCode;
   DString _strCurrentClassCode;
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/AccDetailsProcess.hpp-arc  $
 * 
 *    Rev 1.24   Feb 17 2012 10:04:18   popescu
 * refresh portfolio - temporary backed the code out.
 * 
 *    Rev 1.23   Feb 08 2012 20:32:36   dchatcha
 * IN# 2837678 - REL12.2-PET0186484- New INA Contract Information screen issues as on 6 Feb 2012
 * 
 *    Rev 1.22   Nov 10 2010 04:00:08   dchatcha
 * PET0165541 FN03 - QESI Phase3 - Removed not necessary pieces of code.
 * 
 *    Rev 1.21   Oct 29 2010 06:19:36   kitticha
 * PET0165541 FN03 - QESI Phase3.
 * 
 *    Rev 1.20   07 May 2009 11:19:24   popescu
 * Incident 1667442 - duplicate accounts displayed in Desktop
 * 
 *    Rev 1.19   22 Aug 2007 13:37:20   popescu
 * GAP 6 - search by CIF should return all the entities linked by CIF
 * 
 *    Rev 1.18   Nov 17 2004 15:46:26   popescu
 * PET 910. - NET changes
 * 
 *    Rev 1.16   Aug 11 2004 18:39:58   FENGYONG
 * PET 1117 FN05 Syncup after get files resource 
 * 
 *    Rev 1.15   May 11 2004 14:26:24   FENGYONG
 * PET1046 FN1 - transfer-switch -Rel57
 * 
 *    Rev 1.14   Oct 23 2003 17:48:12   FENGYONG
 * Add field DTAType and getFieldAttribute
 * 
 *    Rev 1.13   Mar 21 2003 17:33:44   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.12   Oct 09 2002 23:52:56   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.11   Aug 29 2002 12:51:22   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.10   22 May 2002 18:22:08   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.9   19 Mar 2002 13:14:40   PURDYECH
 * Use #pragma once as include guard
 * Remove compile time "including..." message
 * 
 *    Rev 1.8   23 Nov 2001 11:16:10   KOVACSRO
 * Added currentFundCode and currentClassCode.
 * 
 *    Rev 1.7   19 Nov 2001 11:12:02   KOVACSRO
 * added getCurrentMFAccount() and getFundDetailList().
 * 
 *    Rev 1.6   Jan 17 2001 10:16:50   KOVACSRO
 * Added a member variable nNoOfPendingTrades.
 * 
 *    Rev 1.5   Oct 26 2000 12:28:28   KOVACSRO
 * Added 'doRefresh'.
 * 
 *    Rev 1.4   Aug 02 2000 15:31:36   BUZILA
 * "locale" changes
 * 
 *    Rev 1.3   Jul 19 2000 10:47:12   WINNIE
 * Filter Contract, RESP, Gurantee Attribute on account defail screen according to the taxtype, system features and permission
 * 
 *    Rev 1.2   Apr 04 2000 16:48:06   DT24433
 * changed to use GI's hasPermission
 * 
 *    Rev 1.1   Feb 15 2000 18:56:08   MCNABBGL
 * changed comment format
 * 
 *    Rev 1.0   Feb 15 2000 10:58:54   SMITHDAV
 * Initial revision.
 * 
 *    Rev 1.16   Dec 29 1999 18:11:34   BUZILA
 * changed COA flags
 * 
 *    Rev 1.15   Dec 23 1999 11:29:08   POPESCUS
 * NASU process and the new confirmation model
 * 
 *    Rev 1.14   Dec 10 1999 11:58:42   VASILEAD
 * Added refresh support
 * 
 *    Rev 1.13   Dec 06 1999 16:35:04   VASILEAD
 * Biult the keys at the CBO level
 * 
 *    Rev 1.12   Dec 01 1999 19:54:28   VASILEAD
 * Stuff
 * 
 *    Rev 1.11   Nov 30 1999 18:24:50   POPESCUS
 * changes related to the NASU flow
 * 
 *    Rev 1.10   Nov 21 1999 13:34:50   VASILEAD
 * added new features
 * 
 *    Rev 1.9   Nov 09 1999 16:53:40   VASILEAD
 * Changed to AccountEntityXref
 * 
 *    Rev 1.8   Nov 02 1999 16:03:06   PRAGERYA
 * getPtrForContainer parameter list changed
 * 
 *    Rev 1.7   Nov 02 1999 10:28:38   YINGBAOL
 * move address from mfaccount to shareholder
 * 
 *    Rev 1.6   Oct 28 1999 17:16:16   DT24433
 * removed doOk/doCancel
 * 
 *    Rev 1.5   Oct 05 1999 09:47:42   HUANGSHA
 * Set focus on the selected entity on detail screen if search for the AltAccount + BrokerCode
 * 
 *    Rev 1.4   Sep 21 1999 14:20:26   VASILEAD
 * Added functionality for All funds check box in Details screen
 * 
 *    Rev 1.3   Sep 17 1999 07:13:40   DT24433
 * changed for new parm to getGroupID and now using getReadOnlyGroupID
 * 
 *    Rev 1.2   Aug 31 1999 11:00:00   DT24433
 * changed dogetfield/dosetfield parms
 * 
 *    Rev 1.1   Jul 08 1999 10:03:22   SMITHDAV
 * Modify revision history commaent format to old
 * style comment -- I can't seem to get new style comments to work.
 *
 */
