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


#include <ifastcbo\Confirmation.hpp>
///#endif

// Forward references

// Import/Export resolution
#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif

class IFASTBP_LINKAGE ConfirmationProcess : public AbstractProcess
{
// Construction
public:
//CP20030319   ConfirmationProcess();
   ConfirmationProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand );
   virtual ~ConfirmationProcess();
protected:
   virtual bool doCancel(GenericInterface *rpGI);
   virtual void doGetField( const GenericInterface *rpGICaller,
                            const BFContainerId& idContainer,
                            const BFFieldId& idField,
                            const BFDataGroupId& idDataGroup,
                            DString &strValueOut,
                            bool bFormatted) const;
   virtual SEVERITY doInit();
   virtual bool doModelessChildComplete(const Command &cmd);
   virtual bool doModelessSetFocus(GenericInterface *rpGICaller);
   virtual E_COMMANDRETURN doProcess();
   virtual bool doRefresh( GenericInterface *rpGICaller, 
                           const I_CHAR *szOriginalCommand);
   virtual SEVERITY doSetField( const GenericInterface *rpGICaller,
                                const BFContainerId& idContainer,
                                const BFFieldId& idField,
                                const BFDataGroupId& idDataGroup,
                                const DString& strValue,
                                bool bFormatted);
   virtual SEVERITY ok2 (GenericInterface *rpGICaller);
   virtual bool doOk (GenericInterface *rpGICaller);

private:
   void refreshGlobals();

   GenericInterface *m_rpChildGI;
   Confirmation *m_pConfirmation;

   DString  m_dstrChoiceField,
      m_dstrCreatingShareholder,
      m_dstrAccountNum,
      m_dstrShrNum,
      m_dstrRemarksAvailable,
      m_dstrDisableRemarks,
      m_dstrFromRemarks,
      m_dstrAWDEvent,
      m_dstrCalledFrom,
      m_strNASUFlag,
      m_dstrDispRebook,
      m_dstrBulkCancel,
      m_dstrBatchNum,
      m_InvokedBrowserScreen,
      m_dstrHostAccountNum,
      m_dstrHostShareholderNum,
      m_dstrHostEntityId;
   DString m_CommitParentDataGroups;
};


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/ConfirmationProcess.hpp-arc  $
 * 
 *    Rev 1.26   Aug 10 2012 12:18:44   popescu
 * IN#3051211 - P0179630 FN01 - FATCA - Acct Ownership Allocation option is not refreshed
 * 
 *    Rev 1.25   Jan 14 2011 16:40:56   dchatcha
 * PET0165541 FN03 - QESI Phase3, refresh account detail screen after there is update from Govt Amendment screen.
 * 
 *    Rev 1.24   07 Apr 2008 09:38:30   kovacsro
 * IN#1166229 - refresh ObjectId & CRDA
 * 
 *    Rev 1.23   17 Jul 2007 15:18:50   popescu
 * GAP 6 CIF - AIM
 * 
 *    Rev 1.22   Jan 23 2006 13:58:08   zhengcon
 * Incident #521273 -- Auto Clone - Integration  - Add new LOB (Batch) field to confirmation
 * 
 *    Rev 1.21   Nov 24 2005 16:20:58   porteanm
 * PET1286 FN01 - Bulk Cancellation.
 * 
 *    Rev 1.20   Jul 15 2005 09:26:40   Yingbaol
 * PET1235,FN01: pass parameters 
 * 
 *    Rev 1.19   Jun 20 2005 18:40:50   porteanm
 * PET1024 FN40 - Guarantee Adjustments.
 * 
 *    Rev 1.18   Jun 16 2005 10:57:06   porteanm
 * PET1024 FN40 - Guarantee Adjustments.
 * 
 *    Rev 1.17   Apr 12 2005 10:27:44   porteanm
 * PET1190 FN14 - Wire order redemption against unsettled units.
 * 
 *    Rev 1.16   May 27 2004 17:18:52   HERNANDO
 * PET1017 FN01- Remarks-Confirmation change.   Allow Confirmation to view the Added Remark and allow copying it to the AWD object.
 * 
 *    Rev 1.15   Oct 03 2003 09:54:20   VADEANUM
 * PTS 10022545 - Record created when no Remark entered on the Remarks dialog - removed refAccount setting on this layer
 * PTS 10022399 - Wrong Account # assigned to Remark - replaced RefAccount with AccountNum in order to have the fieldid picked up in DSTCWorkSession::commit() after including the field in the transaction key.
 * 
 *    Rev 1.14   Sep 11 2003 10:30:22   HSUCHIN
 * bug fix to setting the refAccount to remarks during confirmation.
 * 
 *    Rev 1.13   Mar 21 2003 17:38:12   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.12   Mar 07 2003 11:55:42   PURDYECH
 * Cleanup obsolete code.
 * 
 *    Rev 1.11   Oct 09 2002 23:53:08   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.10   Aug 29 2002 12:52:02   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.9   22 May 2002 18:21:26   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.8   19 Mar 2002 13:15:28   PURDYECH
 * Use #pragma once as include guard
 * Remove compile time "including..." message
 * 
 *    Rev 1.7   12 Jun 2001 16:57:54   YINGZ
 * we do not need datagroupid parm when commit
 * 
 *    Rev 1.6   Jan 03 2001 10:47:12   ZHANGCEL
 * Added a new variable m_strNasuFlag
 * 
 *    Rev 1.5   Oct 11 2000 14:15:34   KOVACSRO
 * Added m_strCalledFrom.
 * 
 *    Rev 1.4   Sep 20 2000 17:39:14   HERNANDO
 * Added AWD Event; revised.
 * 
 *    Rev 1.3   Aug 02 2000 15:31:38   BUZILA
 * "locale" changes
 * 
 *    Rev 1.2   Apr 28 2000 18:20:02   BUZILA
 * M3
 * 
 *    Rev 1.1   Feb 15 2000 18:56:20   MCNABBGL
 * changed comment format
 * 
 *    Rev 1.0   Feb 15 2000 10:59:02   SMITHDAV
 * Initial revision.
 * 
 *    Rev 1.17   Jan 26 2000 19:43:10   VASILEAD
 * Fixes
 * 
 *    Rev 1.16   Jan 23 2000 18:27:50   POPESCUS
 * disable remarks when no global account num and shareholder num exist
 * 
 *    Rev 1.15   Jan 23 2000 16:58:34   POPESCUS
 * fixed the bug that freezes the app after errors in trxns and updated remarks in confirmation
 * 
 *    Rev 1.14   Jan 19 2000 09:36:22   HSUCHIN
 * Check in for Mihai
 * 
 *    Rev 1.13   Jan 18 2000 11:29:52   POPESCUS
 * fixed some of the settings of the global values (account & shareholder)
 * 
 *    Rev 1.12   Jan 16 2000 16:58:08   POPESCUS
 * prepared for refresh and cleaned up the code
 * 
 *    Rev 1.11   Jan 14 2000 09:35:06   POPESCUS
 * get the either the last active account number or the last active shareholder number
 * 
 *    Rev 1.10   07 Jan 2000 14:09:32   HSUCHIN
 * latest infra changes and remark updates
 * 
 *    Rev 1.9   23 Dec 1999 15:56:42   HSUCHIN
 * ??
 * 
 *    Rev 1.8   Dec 17 1999 17:58:46   DT24433
 * get DataGroupID parm
 * 
 *    Rev 1.7   Dec 17 1999 15:07:52   DT24433
 * added ok2
 * 
 *    Rev 1.6   Dec 08 1999 16:27:22   HSUCHIN
 * changed doGetField and doSetField to include groupid
 * 
 *    Rev 1.5   Oct 28 1999 18:17:18   DT24433
 * removed doOk/doCancel
 * 
 *    Rev 1.4   Aug 31 1999 10:36:12   DT24433
 * changed dogetfield/dosetfield parms
 * 
 *    Rev 1.3   Jul 27 1999 16:03:36   BUZILA
 * Increment M2
 * 
 *    Rev 1.2   Jul 26 1999 10:36:30   BUZILA
 * changed doGetField
 * 
 *    Rev 1.1   Jul 08 1999 10:03:38   SMITHDAV
 * Modify revision history commaent format to old
 * style comment -- I can't seem to get new style comments to work.
 *
 */
