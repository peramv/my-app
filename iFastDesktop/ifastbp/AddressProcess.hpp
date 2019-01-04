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

// Forward references

// Import/Export resolution
#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif

#include "iFastHistoricalParameters.hpp"

/**
 * Class that manages the address book process, which defines the a list of addresses
 *
 * @author Serban Popescu
 * </dd></dl><p><dl><dt><b>Date Created:</b></dt><dd> 03/30/1999</dd></dl>
 * @version 0.1
 */
class AccountEntityXref;
class AccountMailingList;
class AddressList;
class AddressEntityList;
class EntityList;
class Entity;
class WorkSessionEntityList;
class ProvinceList;
//class AccountAddressInfoList;
//class ShareholderAddressInfo;
//class Address;
//class AccountAddressInfo;
class Shareholder;

class IFASTBP_LINKAGE AddressProcess : public AbstractProcess, public IFastHistoricalParameters
{
// Construction
public:
   /**
    * Default constructor
    */
//CP20030319   AddressProcess();
   AddressProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand );
   virtual ~AddressProcess();

   void refreshUnclaimedFields( const BFDataGroupId &idDataGroup );
   void refreshRegAddrForNominee( const BFDataGroupId &idDataGroup );
   void getMailOptionSubstitutionByDocKey(const DString &strDocKey, 
                                          BFFieldId &fieldID);

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

   virtual const DString& getKeyForNewListItem(
                                              const GenericInterface *rpGICaller,
                                              const BFContainerId& idList
                                              );

   virtual  bool doRefresh(
                          GenericInterface *rpGICaller,
                          const I_CHAR *szOriginalCommand
                          );

   virtual void doPostOk( GenericInterface *rpGICaller, bool bSuccessFlag );

   virtual SEVERITY doValidateAll(
                                 BFAbstractCBO *rpWSD,
                                 const BFDataGroupId& idDataGroup
                                 );

   void *getPtrForContainer(
                           const BFContainerId& idContainer, const BFDataGroupId& idDataGroup
                           );
   bool doModelessSetFocus( GenericInterface *rpGICaller );
   bool doModelessChildComplete( const Command &cmd );
   void setCurrentListItem(const GenericInterface *rpGICaller, const BFContainerId& idList,const DString& strListItemKey);
   const DString& getFirstListItemKey( const GenericInterface *rpGICaller, const BFContainerId& idList );
   const DString& getNextListItemKey( const GenericInterface *rpGICaller, const BFContainerId& idList );
   SEVERITY setFreshList( GenericInterface *rpGI );
   void doGetField( const GenericInterface *rpGICaller, 
                    const BFContainerId& idContainer, const BFFieldId& idField, 
                    const BFDataGroupId& idDataGroup, 
                    DString &strValueOut, 
                    bool bFormatted ) const;

   virtual SEVERITY doGetErrors ( const GenericInterface *rpGICaller,
                                  const BFContainerId &idContainer,
                                  const BFFieldId &idField,
                                  const BFDataGroupId &idDataGroup,
                                  CONDITIONVECTOR &conditions ) const;

   virtual const BFProperties *doGetFieldAttributes ( const GenericInterface *rpGICaller, 
                                                      const BFContainerId &idContainer, 
                                                      const BFFieldId &idField, 
                                                      const BFDataGroupId &idDataGroup);

   virtual SEVERITY doSetField( const GenericInterface* rpGICaller,
                                const BFContainerId& idContainer,
                                const BFFieldId &fieldID,
                                const BFDataGroupId& idDataGroup,
                                const DString &strValue,
                                bool bFormatted );	

   virtual bool setCommitDataGroupAsHost()
   {
      return false;
   }
   virtual bool doOk (GenericInterface* rpGICaller);
   virtual SEVERITY getHistoricalParameters(
      const BFContainerId &idContainer, 
      BFFieldId &recordIdField, 
      DString &tableId, 
      DString &dstrKeys);

   SEVERITY getHistoricalParameters( const BFContainerId& idContainer, HISTORICAL_VECTOR &vectorInput );

private:
   GenericInterface *_rpChildGI;
   AccountEntityXref *_pAccountEntityXref; //logical singleton
   AddressList* _pAddressList;
   AccountMailingList* _pAccountMailingList;
   AddressEntityList *_pAddressEntityList;	
   WorkSessionEntityList *_pWorkSessionEntityList;
   ProvinceList *_pProvinceList;
   
   DString _strKey;
   DString _searchShareholder;
   DString _accountNum; 
   DString _shrNum;
   DString _addrCode;
   DString _strFromSearch;
   DString _strNASUFlag;
   DString _FromSettlement;
   DString _InquiryOnly;
   
   DString m_dstrEntityId;
   DString m_dstrFromEntity;    
   DString m_dstrEntityType;
   DString m_dstrSeqNum;

   DString m_dstrRetMailTab;
   DString m_dstrFromEntityAlone;
};
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/AddressProcess.hpp-arc  $
 * 
 *    Rev 1.23   Jan 25 2010 22:45:24   dchatcha
 * IN# 1983880 - Rel 97 Static Data - Status of Nom (01 Reg address) is set to Unverified.
 * 
 *    Rev 1.22   Sep 22 2008 08:45:28   wongsakw
 * PET5517 FN71 Unclaimed Property
 * 
 *    Rev 1.21   Mar 16 2005 09:52:22   porteanm
 * PET 1171 FN01 - EUSD Entity Address Update support.
 * 
 *    Rev 1.20   Mar 15 2005 10:46:04   porteanm
 * PET 1171 FN01 - EUSD Entity Address Update support - work in progress.
 * 
 *    Rev 1.19   Mar 11 2005 15:01:42   porteanm
 * PET 1171 FN01 - EUSD Entity Address Update - work in progress.
 * 
 *    Rev 1.18   Mar 08 2005 10:20:48   porteanm
 * PET 1171 FN01 - EUSD Entity Address Update support - work in progress.
 * 
 *    Rev 1.17   Feb 25 2005 13:20:14   porteanm
 * PET 1171 FN01 - EUSD Entity Address Search.
 * 
 *    Rev 1.16   Mar 10 2004 11:32:06   HERNANDO
 * PET965 FN11 - Added getHistoricalParameters.
 * 
 *    Rev 1.15   Mar 03 2004 16:21:14   popescu
 * PTS 10027578, refresh the account information after updating the mailing address info and demographics info; changed the name of the refreshMe method, to be consistent with the shareholder object
 * 
 *    Rev 1.14   Mar 02 2004 16:22:52   HERNANDO
 * PET965 FN11 - Added Historical functionality; added getHistoricalParameters.
 * 
 *    Rev 1.13   Mar 21 2003 17:35:18   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.12   Mar 03 2003 11:59:50   KOVACSRO
 * Added InquiryOnly
 * 
 *    Rev 1.11   Oct 09 2002 23:53:00   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.10   Aug 29 2002 12:51:42   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.9   Jun 11 2002 11:43:28   YINGBAOL
 * lauch address list dialoge for settlement
 * 
 *    Rev 1.8   Jun 03 2002 16:55:10   HSUCHIN
 * bug fix to doValidateAll to use BFAbstractCBO rather than BFCBO
 * 
 *    Rev 1.7   Jun 03 2002 14:13:10   FENGYONG
 * override "setCommitDataGroupAsHost" for NASU API
 * 
 *    Rev 1.6   22 May 2002 18:21:50   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.5   19 Mar 2002 13:15:00   PURDYECH
 * Use #pragma once as include guard
 * Remove compile time "including..." message
 * 
 *    Rev 1.4   Jun 04 2001 15:00:06   YINGBAOL
 * add doRefresh method
 * 
 *    Rev 1.3   Aug 02 2000 15:31:38   BUZILA
 * "locale" changes
 * 
 *    Rev 1.2   Jul 17 2000 17:00:30   KOVACSRO
 * Added RegAddress not updatable for Acc. Des. = 2 OR 3
 * 
 *    Rev 1.1   Feb 15 2000 18:56:12   MCNABBGL
 * changed comment format
 * 
 *    Rev 1.0   Feb 15 2000 10:58:56   SMITHDAV
 * Initial revision.
 * 
 *    Rev 1.17   Jan 31 2000 18:14:04   YINGBAOL
 * override validate all
 * 
 *    Rev 1.16   Jan 26 2000 16:23:48   POPESCUS
 * removed refresh
 * 
 *    Rev 1.15   Jan 25 2000 18:05:22   YINGBAOL
 * fix
 * 
 *    Rev 1.14   Jan 23 2000 16:59:34   POPESCUS
 * fixes related to accessing the lists and rolling back a cloned account
 * 
 *    Rev 1.13   Jan 19 2000 14:31:30   YINGBAOL
 * getnewitemkey
 * 
 *    Rev 1.12   Jan 06 2000 12:52:14   POPESCUS
 * fixes for validation
 * 
 *    Rev 1.11   Dec 02 1999 17:56:58   POPESCUS
 * Fixed crashes in search
 * 
 *    Rev 1.10   Nov 30 1999 15:24:50   YINGBAOL
 * add nasu
 * 
 *    Rev 1.9   Nov 25 1999 12:03:20   YINGBAOL
 * check in for M2 release
 * 
 *    Rev 1.8   Nov 24 1999 14:13:54   YINGBAOL
 * check in sync
 * 
 *    Rev 1.7   Nov 18 1999 16:14:04   YINGBAOL
 * split view 43 sync
 * 
 *    Rev 1.6   Nov 02 1999 15:48:52   YINGBAOL
 * add lgroupId to getPtrForContainer
 * 
 *    Rev 1.5   Oct 29 1999 09:40:00   YINGBAOL
 * 
 *    Rev 1.4   Aug 25 1999 14:25:02   YINGBAOL
 * check in for jerry
 * 
 *    Rev 1.3   Aug 18 1999 11:51:14   YINGBAOL
 * No change.
 * 
 *    Rev 1.2   Jul 27 1999 16:32:48   VASILEAD
 * The address selected on entities screen is also selected on address book screen
 * 
 *    Rev 1.1   Jul 08 1999 10:03:26   SMITHDAV
 * Modify revision history commaent format to old
 * style comment -- I can't seem to get new style comments to work.
 *
 */
