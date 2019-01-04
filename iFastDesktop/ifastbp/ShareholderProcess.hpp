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
//    AUTHOR : Mihai Virgil Buzila, modified by Yakov Prager
//    DATE   : 16/04/99
//
//
//    Copyright 1997 by DST Systems, Inc.
//
//******************************************************************************


#include <bfproc\AbstractProcess.hpp>
#include <ifastbp\ifasthistoricalparameters.hpp>
///#endif

// Forward references
class Shareholder;
class MgmtCo;
class MFCommonBusinessManager;
class AccShrNumCheck;

// Import/Export resolution
#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif

/**
 * Class that manages the Shareholder process
 *
 * @author Yakov Prager
 * </dd></dl><p><dl><dt><b>Date Created:</b></dt><dd> 03/08/1999</dd></dl>
 * @version 0.1
 */

class IFASTBP_LINKAGE ShareholderProcess : public AbstractProcess,
   public IFastHistoricalParameters

{
// Construction
public:
//CP20030319   ShareholderProcess();
   ShareholderProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand );
   virtual ~ShareholderProcess();
   virtual SEVERITY fireCrossEdit(
                                 const GenericInterface *rpGICaller,
                                 const BFContainerId& idContainer,
                                 const BFFieldId& idCrossEdit,
                                 long lValidateGroup = 0
                                 );
protected:
   SEVERITY doGetErrors( const GenericInterface *rpGICaller, const BFContainerId& idContainer,
                         const BFFieldId& idField, const BFDataGroupId& idDataGroup, CONDITIONVECTOR &conditions ) const;
   virtual void doGetField(
                          const GenericInterface *rpGICaller,
                          const BFContainerId& idContainer,
                          const BFFieldId& idField,
                          const BFDataGroupId& idDataGroup,
                          DString &strValueOut,
                          bool bFormatted
                          ) const;
   virtual SEVERITY doInit();
   virtual bool doModelessChildComplete(
                                       const Command &cmd
                                       );
   virtual bool doModelessSetFocus(
                                  GenericInterface *rpGICaller
                                  );
   virtual E_COMMANDRETURN doProcess();
   virtual SEVERITY ok2( GenericInterface *rpGICaller );
   virtual void *getPtrForContainer( const BFContainerId& idContainer, const BFDataGroupId& idDataGroup );
   virtual SEVERITY doSetField(
                              const GenericInterface *rpGICaller,
                              const BFContainerId& idContainer,
                              const BFFieldId& idField,
                              const BFDataGroupId& idDataGroup,
                              const DString& strValue,
                              bool bFormatted
                              );
   virtual bool setCommitDataGroupAsHost()
   {
      return(false);
   }
   SEVERITY getHistoricalParameters( const BFContainerId& idContainer, HISTORICAL_VECTOR &vectorInput );

private:
   DString _shrNum;
   DString _dstrCreatingShareholder;
   GenericInterface* _rpChildGI;
   DString _dstrNewShrNum;
   bool m_bManualShr;
   bool m_bShrCreated;
   Condition* _pCondition;
};


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/ShareholderProcess.hpp-arc  $
 * 
 *    Rev 1.12   Mar 10 2004 10:23:34   HERNANDO
 * PET965 FN11 - Added getHistoricalParameters.
 * 
 *    Rev 1.11   Mar 21 2003 17:48:08   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.10   Oct 09 2002 23:53:36   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.9   Aug 29 2002 12:53:40   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.8   Jun 03 2002 14:13:12   FENGYONG
 * override "setCommitDataGroupAsHost" for NASU API
 * 
 *    Rev 1.7   22 May 2002 18:20:00   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.6   19 Mar 2002 13:18:28   PURDYECH
 * Use #pragma once as include guard
 * Remove compile time "including..." message
 * 
 *    Rev 1.5   11 May 2001 16:33:10   YINGZ
 * code sync
 * 
 *    Rev 1.4   Feb 28 2001 15:42:14   YINGZ
 * override fireCrossEdit to support validategroup
 * 
 *    Rev 1.3   Sep 22 2000 11:50:30   ZHANGCEL
 * Fixed the bug for manually entering a new shareholder number
 * 
 *    Rev 1.2   Aug 02 2000 15:31:50   BUZILA
 * "locale" changes
 * 
 *    Rev 1.1   Feb 15 2000 18:56:48   MCNABBGL
 * changed comment format
 * 
 *    Rev 1.0   Feb 15 2000 10:59:22   SMITHDAV
 * Initial revision.
 * 
 *    Rev 1.20   Jan 19 2000 15:32:00   POPESCUS
 * fixes in Shareholder
 * 
 *    Rev 1.19   Jan 17 2000 14:00:16   POPESCUS
 * support for refresh and misc
 * 
 *    Rev 1.18   Dec 09 1999 18:48:42   DT24433
 * removed Ok2 & doRefresh to allow base processing
 * 
 *    Rev 1.17   Nov 29 1999 11:26:50   POPESCUS
 * Fixes in NASU flow
 * 
 *    Rev 1.16   Nov 25 1999 17:08:52   POPESCUS
 * 
 *    Rev 1.15   Nov 23 1999 18:05:44   POPESCUS
 * NASU flow
 * 
 *    Rev 1.14   Nov 08 1999 15:50:10   ZHANGCEL
 * add mechanism for ShrNumCtrl and DefaultCtl
 * 
 *    Rev 1.13   Nov 02 1999 16:50:30   DT24433
 * removed doOk/doCancel
 * 
 *    Rev 1.12   Oct 27 1999 10:19:44   ZHANGCEL
 * add new process
 * 
 *    Rev 1.11   Sep 01 1999 12:39:50   DT24433
 * changed doGetField/doSetField parms
 * 
 *    Rev 1.10   Aug 26 1999 16:10:42   PRAGERYA
 * Implementing Search for Shareholder and Account Info
 * 
 *    Rev 1.9   Aug 08 1999 19:33:30   PRAGERYA
 * All in!
 * 
 *    Rev 1.8   Aug 04 1999 09:37:22   PRAGERYA
 * Implementing process
 * 
 *    Rev 1.7   Jul 30 1999 17:24:34   PRAGERYA
 * Coded to the level of Incr1
 * 
 *    Rev 1.6   Jul 27 1999 14:07:28   BUZILA
 * fix
 * 
 *    Rev 1.5   Jul 23 1999 15:45:24   YINGZ
 * 1
 * 
 *    Rev 1.4   Jul 23 1999 15:33:34   SMITHDAV
 * m21
 * 
 *    Rev 1.1   Jul 08 1999 10:03:56   SMITHDAV
 * Modify revision history commaent format to old
 * style comment -- I can't seem to get new style comments to work.
 *
 */
