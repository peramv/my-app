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
//    DATE   : 06/04/99
//
//
//    Copyright 1999 by DST Systems, Inc.
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

class AccShrNumCheck;
/**
 * Class that manages the the account information
 *
 * @author Serban Popescu
 * </dd></dl><p><dl><dt><b>Date Created:</b></dt><dd> 03/08/1999</dd></dl>
 * @version 0.1
 */

class IFASTBP_LINKAGE AccInfoProcess : public AbstractProcess
{
// Construction
public:
//CP20030319   AccInfoProcess();
   AccInfoProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand );
   virtual ~AccInfoProcess();
protected:
   SEVERITY doGetErrors( const GenericInterface *rpGICaller, const BFContainerId& idContainer,
                         const BFFieldId& idField, const BFDataGroupId& idDataGroup, CONDITIONVECTOR &conditions ) const;
   virtual void doGetField(
                          const GenericInterface *rpGICaller, 
                          const BFContainerId& idContainer, 
                          const BFFieldId& idField, 
                          const BFDataGroupId& idDataGroup, 
                          DString &strValueOut, 
                          bool bFormtted
                          ) const;
   virtual SEVERITY doInit();
   virtual bool doModelessChildComplete( const Command &cmd );
   virtual bool doModelessSetFocus( GenericInterface *rpGICaller );
   virtual E_COMMANDRETURN doProcess();
   virtual void *getPtrForContainer( const BFContainerId& idContainer, const BFDataGroupId& idDataGroup );
   virtual SEVERITY ok2( GenericInterface *rpGICaller );
   virtual bool doCancel( GenericInterface * rpGICaller );
   virtual SEVERITY doSetField(
                              const GenericInterface *rpGICaller,
                              const BFContainerId& idContainer,
                              const BFFieldId& idField,
                              const BFDataGroupId& idDataGroup,
                              const DString& strValue,
                              bool bFormatted
                              );

   //virtual bool setCommitDataGroupAsHost()
   //{
   //   return(false);
   //}  
private:
   GenericInterface *_rpChildGI;
   //data
   DString _accountNum;
   DString _shareholderNum;
   DString _creatingAccount;
   DString _creatingShareholder;
   DString _entityId;
   DString _CancelAfterAccountInfo;
   DString _fromScreen;
   DString _modelAccountNum;
   
   bool m_bManualAccNum;
   bool m_bAccCreated;
   AccShrNumCheck *_pAcctShrNumCheck;
   Condition* _pCondition;
	DString _LaunchCOA;
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/AccInfoProcess.hpp-arc  $
 * 
 *    Rev 1.18   Feb 17 2012 10:04:36   popescu
 * refresh portfolio - temporary backed the code out.
 * 
 *    Rev 1.17   Feb 08 2012 20:29:14   dchatcha
 * IN# 2837678 - REL12.2-PET0186484- New INA Contract Information screen issues as on 6 Feb 2012
 * 
 *    Rev 1.16   Feb 07 2012 18:06:22   dchatcha
 * IN# 2837678 - REL12.2-PET0186484- New INA Contract Information screen issues as on 6 Feb 2012
 * 
 *    Rev 1.15   Jan 26 2006 12:04:36   popescu
 * Disable the COA button on the AccInfo screen if this is invoked from the  COA dialog
 * 
 *    Rev 1.14   Jul 06 2005 10:55:04   ZHANGCEL
 * PET1141 - FN05 -- NSCC Broker enhancement
 * 
 *    Rev 1.13   Mar 21 2003 17:33:52   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.12   Jan 09 2003 11:06:36   FENGYONG
 * comment out override of setcommitdatagroup
 * 
 *    Rev 1.11   Oct 09 2002 23:52:56   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.10   Aug 29 2002 12:51:24   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.9   Jul 26 2002 15:28:28   YINGBAOL
 * fix PTS10009161
 * 
 *    Rev 1.8   Jun 03 2002 14:13:10   FENGYONG
 * override "setCommitDataGroupAsHost" for NASU API
 * 
 *    Rev 1.7   22 May 2002 18:22:10   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.6   19 Mar 2002 13:14:42   PURDYECH
 * Use #pragma once as include guard
 * Remove compile time "including..." message
 * 
 *    Rev 1.5   11 May 2001 16:32:38   YINGZ
 * code sync
 * 
 *    Rev 1.4   Sep 23 2000 15:27:52   DINACORN
 * Create new data member
 * 
 *    Rev 1.3   Aug 02 2000 15:31:36   BUZILA
 * "locale" changes
 * 
 *    Rev 1.2   Feb 15 2000 18:56:08   MCNABBGL
 * changed comment format
 * 
 *    Rev 1.1   Feb 15 2000 12:50:12   POPESCUS
 * fix compiling issues
 * 
 *    Rev 1.0   Feb 15 2000 10:58:54   SMITHDAV
 * Initial revision.
*/ 
//    Rev 1.25   Jan 23 2000 18:48:46   POPESCUS
// changes related to creating a slsrep on the fly
// 
//    Rev 1.24   Jan 12 2000 09:03:16   POPESCUS
// changes related to cloning an account and fixing some validation, adding subst sets
// 
//    Rev 1.23   Jan 11 2000 08:41:40   POPESCUS
// fixes and validation
// 
//    Rev 1.22   Jan 09 2000 19:11:24   POPESCUS
// bug fixes?
// 
//    Rev 1.21   Jan 07 2000 15:55:46   POPESCUS
// just checking in...
// 
//    Rev 1.20   Jan 06 2000 09:58:36   POPESCUS
// cleanup code and remove some unused methods
// 
//    Rev 1.19   Dec 24 1999 15:18:28   VASILEAD
// Fixed transactions
// 
//    Rev 1.18   Dec 24 1999 10:29:54   VASILEAD
// Fixed NASU flow
// 
//    Rev 1.17   Dec 21 1999 14:15:00   POPESCUS
// cleanup the code, validations and misc
// 
//    Rev 1.16   Dec 20 1999 16:14:18   POPESCUS
// Code review, validations removed commented code, misc
// 
//    Rev 1.15   Dec 14 1999 09:49:26   ZHANGCEL
// Add View87 request
// 
//    Rev 1.14   Dec 03 1999 18:21:20   ZHANGCEL
// debug
// 
//    Rev 1.13   Nov 30 1999 18:24:52   POPESCUS
// changes related to the NASU flow
// 
//    Rev 1.12   Nov 30 1999 13:58:28   ZHANGCEL
// New AccountInfo implementation
// 
//    Rev 1.11   Nov 29 1999 11:04:30   ZHANGCEL
// Debug
// 
//    Rev 1.10   Nov 29 1999 10:10:28   ZHANGCEL
// Implemente View requirst use new function
// 
//    Rev 1.9   Nov 25 1999 14:08:56   POPESCUS
// get the account number for mfcommonbm and cleanup
// 
//    Rev 1.8   Nov 25 1999 10:19:32   ZHANGCEL
// modify
// 
//    Rev 1.7   Nov 24 1999 10:06:04   POPESCUS
// again NASU
// 
//    Rev 1.6   Nov 23 1999 18:05:40   POPESCUS
// NASU flow
// 
//    Rev 1.5   Nov 01 1999 16:00:14   DT24433
// removed doOk/doCancel
// 
//    Rev 1.4   Sep 01 1999 12:39:50   DT24433
// changed doGetField/doSetField parms
// 
//    Rev 1.3   Aug 08 1999 19:33:24   PRAGERYA
// All in!
// 
//    Rev 1.2   Aug 04 1999 09:37:20   PRAGERYA
// Implementing process
// 
//    Rev 1.1   Jul 27 1999 16:03:30   BUZILA
// Increment M2
// 
//    Rev 1.0   Jul 22 1999 17:22:48   BUZILA
// Initial revision.
// 
