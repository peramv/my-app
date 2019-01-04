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
//    AUTHOR : Serban Popescu
//    DATE   : January 2003
//
//
//    Copyright 1997 by DST Systems, Inc.
//
//******************************************************************************


#include <bfproc\AbstractProcess.hpp>

// Forward references
class HistoricalInfoList;
// Import/Export resolution
#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif

/**
 *
 * @author Serban Popescu
 * </dd></dl><p><dl><dt><b>Date Created:</b></dt><dd> January 2003</dd></dl>
 * @version 0.1
 */

class IFASTBP_LINKAGE HistoricalInfoProcess : public AbstractProcess
{
// Construction
public:
   /**
    * Default constructor
    */
//CP20030319   HistoricalInfoProcess();
   HistoricalInfoProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand );
   virtual ~HistoricalInfoProcess();
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
   virtual bool doRefresh( GenericInterface *rpGICaller, 
                           const I_CHAR *szOriginalCommand )
   {
      return(true);
   }
   virtual SEVERITY performSearch( GenericInterface *rpGICaller, const BFContainerId& idSearch, 
      E_SEARCHACTION eSearchAction );
   virtual bool doMoreRecordsExist( GenericInterface *rpGICaller, const BFContainerId& idSearch );

   virtual void doGetField(
                          const GenericInterface *rpGICaller,
                          const BFContainerId& idContainer,
                          const BFFieldId& idField,
                          const BFDataGroupId& idDataGroup,
                          DString &strValueOut,
                          bool bFormatted
                          ) const;

   virtual bool doModelessSetFocus(
                                  GenericInterface *rpGICaller
                                  );
   virtual bool doModelessChildComplete(
                                       const Command &cmd
                                       );

private:

   HistoricalInfoList* _pHistoricalInfoList;
   GenericInterface *m_rpChildGI;
   DString m_dstrAccountNumber;
   DString m_dstrShareholderNumber;
   DString m_dstrBrokerCode, m_dstrBranchCode, m_dstrSalesRepCode;
   DString m_dstrHistoricalVectorPtr;

};


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/HistoricalInfoProcess.hpp-arc  $
//
//   Rev 1.10   Sep 15 2008 03:34:24   phiwponp
//IN 1394896    Inconsistence of Historical screen title under pending trade - clean code
//
//   Rev 1.9   Sep 10 2008 05:48:52   phiwponp
//IN 1394896  Inconsistence of Historical screen title under pending trade
//
//   Rev 1.8   Mar 04 2004 11:01:16   HERNANDO
//PET965 FN11 - Added doModelessSetFocus and doModelessChildComplete.
//
//   Rev 1.7   Feb 28 2004 16:01:06   HERNANDO
//PET965 FN11 - Additional historical enhancement.  Added two strings.
//
//   Rev 1.6   Oct 31 2003 16:06:34   HERNANDO
//PTS 10022670 - Support displaying Broker Code, Branch Code, and Sales Rep Code.
//
//   Rev 1.5   Oct 10 2003 16:17:32   HERNANDO
//PTS 10022670 - Added doGetField and dstrAccountNum.
//
//   Rev 1.4   Mar 21 2003 17:41:00   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.3   Feb 03 2003 11:53:30   popescu
//Changed to support the KeyString field of the 249 view
//
//   Rev 1.2   Jan 29 2003 14:58:04   popescu
//FIxes related to view layout change and error reporting
//
//   Rev 1.1   Jan 28 2003 16:56:34   popescu
//Fixes for the More button in the Historical Info dialog
//
//   Rev 1.0   Jan 28 2003 13:13:54   popescu
//Initial revision.
 * 
 *
 */
