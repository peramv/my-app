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

#include <bfproc\abstractprocess.hpp>
#include <ifastbp\ifasthistoricalparameters.hpp>

// Forward references
class FundMasterList;
class FundDetailList; 
class MFAccount;
class COANavig;
class Systematic;
class SystematicList;
class GroupList;
class MgmtCoOptions;
class AddressList;
class Shareholder;
class AccountEntityXref;
class AcqFeeInquiry;
class AutoAcctTransAllocationList;
class AutoTransAllocationList;
class SavingPlanMasterList;



// Import/Export resolution
#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif

/**
 * Class that manages the Systematic process.
 *
 * @author 
 * </dd></dl><p><dl><dt><b>Date Created:</b></dt><dd> 03/04/1999</dd></dl>
 * @version 0.1
 */

class IFASTBP_LINKAGE SystematicProcess : public AbstractProcess, public IFastHistoricalParameters
{
// Construction
public:
   /**
    * Default constructor
    */
//CP20030319   SystematicProcess();
   SystematicProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand );
   virtual ~SystematicProcess();

   virtual void setCurrentListItem(
                                  const GenericInterface *rpGICaller,
                                  const BFContainerId& idList,
                                  const DString& strListItemKey
                                  );

   virtual bool doOk(GenericInterface *rpGICaller);
   SEVERITY getHistoricalParameters(const BFContainerId& idContainer, 
      BFFieldId &recordIdField, DString& tableId, DString& dstrKeys);
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
   virtual void doGetField(
                          const GenericInterface *rpGICaller,
                          const BFContainerId& idContainer,
                          const BFFieldId& idField,
                          const BFDataGroupId& idDataGroup,
                          DString &strValueOut,
                          bool bFormatted
                          ) const;
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
   virtual SEVERITY doSetField(
                              const GenericInterface *rpGICaller,
                              const BFContainerId& idContainer,
                              const BFFieldId& idField,
                              const BFDataGroupId& idDataGroup,
                              const DString& strValue,
                              bool bFormatted
                              );

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
   virtual bool doModelessChildComplete(const Command &/*cmd*/);
   /**
     * Used to bring a modeless dialog (via parent process) to the top of the
     * window stack.
     * @param rpGICaller - A reference pointer to the calling object.
     * @returns true if successful, check conditions if false
     */
   virtual bool doModelessSetFocus(GenericInterface *rpGICaller);
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
   SEVERITY performSearch( GenericInterface *rpGI, const BFContainerId& idSearch, 
                           E_SEARCHACTION eSearchAction );

   void getEntityName( const BFDataGroupId& idDataGroup, DString& AcctNum, DString &EntityName);

   virtual void *getPtrForContainer(
                                   const BFContainerId& idContainer,
                                   const BFDataGroupId& idDataGroup
                                   );
   virtual bool doSend( GenericInterface *rpGICaller, const I_CHAR * szMessage );

   virtual SEVERITY doValidateAll( BFAbstractCBO *rpWSD,  const BFDataGroupId& idDataGroup   );

   void requestAcqFee(const BFDataGroupId& idDataGroup);
   SEVERITY getHistoricalParameters( const BFContainerId& idContainer, HISTORICAL_VECTOR &vectorInput );

private:
   GenericInterface*          _rpChildGI;
   SystematicList*            _pSystematicList;
   Systematic*                _pSystematic;                 //the current systematic record
   MFAccount*                 _pMFAccount;
   FundMasterList*            _pFundMasterList;
   FundDetailList*            _pFundDetailList;
   GroupList*                 _pGroupList;
   MgmtCoOptions*             _pMgmtCoOption;
   AcqFeeInquiry*             _pAcqFeeInquiry;
   SavingPlanMasterList*      _pSavingPlanMasterList;

   AutoAcctTransAllocationList*  _pAtAcctTransAllocationList;
   AutoTransAllocationList*  _pAutoTransAllocationList;

   AddressList*               _pAddressList;
   Shareholder*               _pShareholder;
   AccountEntityXref*         _pAccountEntityXref;

   DString                    _dstrAccountNum;
   DString                    _dstrShrNum;
   DString                    _dstrEntityName;
   DString                    _dstrListKey;
   DString                    _dstrTransType;

   // for Add/Copy
   DString                    _dstrOrgKey;
   DString                    _dstrDestKey;

   DString                    _dstrCaller;
   DString                    _dstrWorkType;
};


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/SystematicProcess.hpp-arc  $
 * 
 *    Rev 1.21   Nov 25 2010 13:56:58   jankovii
 * PET175778FN01 - Upstreaming Phase 2
 * 
 *    Rev 1.20   Mar 10 2004 13:21:00   HERNANDO
 * PET965 FN11 - Added getHistoricalParameters.
 * 
 *    Rev 1.19   Aug 18 2003 16:10:52   HERNANDO
 * Added keys to getHistoricalParameters.
 * 
 *    Rev 1.18   Mar 21 2003 17:48:54   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.17   Mar 05 2003 11:23:02   PURDYECH
 * IFastBaseProcess no longer exists.  Classes now derive from AbstractProcess (again) and the Protocol class IFastHistoricalParameters.
 * 
 *    Rev 1.16   Jan 29 2003 14:57:08   popescu
 * Added Historical button for Systematic
 * 
 *    Rev 1.15   Oct 09 2002 23:53:40   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.14   Aug 29 2002 12:53:48   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.13   Jun 03 2002 16:55:14   HSUCHIN
 * bug fix to doValidateAll to use BFAbstractCBO rather than BFCBO
 * 
 *    Rev 1.12   22 May 2002 18:19:40   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.11   19 Mar 2002 13:18:44   PURDYECH
 * Use #pragma once as include guard
 * Remove compile time "including..." message
 * 
 *    Rev 1.10   Aug 27 2001 09:47:12   YINGBAOL
 * fix paytype issue
 * 
 *    Rev 1.9   25 May 2001 15:07:24   YINGZ
 * just save a copy
 * 
 *    Rev 1.8   03 May 2001 14:05:00   SMITHDAV
 * Session management restructuring.
 * 
 *    Rev 1.7   Aug 02 2000 15:31:50   BUZILA
 * "locale" changes
 * 
 *    Rev 1.6   May 19 2000 17:12:06   HUANGSHA
 * Removed the Market Conditions for AT
 * 
 *    Rev 1.5   May 01 2000 09:41:40   YINGBAOL
 * automatic transfer added
 * 
 *    Rev 1.4   Apr 17 2000 17:15:34   YINGZ
 * add AddCopy function for systematic
 * 
 *    Rev 1.3   Apr 14 2000 12:04:22   YINGBAOL
 * add Automatic Transfer in systematic screen
 * 
 *    Rev 1.2   Apr 04 2000 10:46:14   YINGBAOL
 * M2 Sync.
 * 
 *    Rev 1.1   Feb 15 2000 18:56:50   MCNABBGL
 * changed comment format
 * 
 *    Rev 1.0   Feb 15 2000 10:59:24   SMITHDAV
 * Initial revision.
 * 
 *    Rev 1.19   Feb 09 2000 12:13:50   HUANGSHA
 * check in for release
 * 
 *    Rev 1.18   Feb 02 2000 18:09:58   BUZILA
 * changes
 * 
 *    Rev 1.17   Feb 02 2000 17:23:00   HUANGSHA
 * added getPrtForContainer()
 * 
 *    Rev 1.16   Jan 21 2000 14:40:00   BUZILA
 * took out doRefresh
 * 
 *    Rev 1.15   Jan 06 2000 14:57:16   HUANGSHA
 * COA changed
 * 
 *    Rev 1.14   Dec 23 1999 12:16:54   HUANGSHA
 * check in for Allocation testing
 * 
 *    Rev 1.13   Dec 21 1999 16:48:30   HUANGSHA
 * for testing
 * 
 *    Rev 1.12   Dec 16 1999 18:30:12   HUANGSHA
 * Check in for testing
 * 
 *    Rev 1.11   Dec 14 1999 15:35:14   HUANGSHA
 * check in for compiling
 * 
 *    Rev 1.10   Dec 01 1999 12:57:52   HUANGSHA
 * check in for 2nd release
 * 
 *    Rev 1.9   Nov 27 1999 16:25:00   HUANGSHA
 * check in
 * 
 *    Rev 1.8   Nov 25 1999 15:19:38   HUANGSHA
 * check in for the initial m2 release
 * 
 *    Rev 1.7   Nov 25 1999 10:26:28   HUANGSHA
 * check in for test
 * 
 *    Rev 1.6   Nov 24 1999 09:36:34   HUANGSHA
 * check in for test
 * 
 *    Rev 1.5   Nov 15 1999 14:43:32   HUANGSHA
 * temporary check in
 * 
 *    Rev 1.4   Nov 02 1999 14:18:36   DT24433
 * removed doOk and doCancel
 * 
 *    Rev 1.3   Aug 31 1999 12:08:34   DT24433
 * changed dogetfield parms
 * 
 *    Rev 1.2   Aug 03 1999 15:14:02   DT24433
 * container changes
 * 
 *    Rev 1.1   Jul 08 1999 10:03:58   SMITHDAV
 * Modify revision history commaent format to old
 * style comment -- I can't seem to get new style comments to work.
 *
 */
