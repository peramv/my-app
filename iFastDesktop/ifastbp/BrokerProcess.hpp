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


#include <bfproc\AbstractProcess.hpp>
///#endif

// Import/Export resolution
#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif

class BrokerList;
class FamilyCodeList;

class IFASTBP_LINKAGE BrokerProcess : public AbstractProcess
{
// Construction
public:
   BrokerProcess(GenericInterfaceContainer* pGIC, 
                 GenericInterface* pGIParent, const Command& rCommand);
   virtual ~BrokerProcess();

protected:
   virtual bool doModelessChildComplete(const Command &cmd);
   virtual E_COMMANDRETURN doProcess();
   virtual bool doRefresh(GenericInterface *rpGICaller, 
      const I_CHAR *szOriginalCommand);
   virtual SEVERITY doInit();
   virtual void doPostOk(GenericInterface *rpGICaller, 
      bool bSuccessFlag);
   virtual SEVERITY performSearch(GenericInterface *rpGICaller, 
      const BFContainerId& idSearch, E_SEARCHACTION eSearchAction);
   virtual bool doMoreRecordsExist(GenericInterface *rpGICaller, 
                                   const BFContainerId& idSearch );
private:
   GenericInterface *_rpChildGI;
   BrokerList *_pBrokerList;
   FundBrokerList *_pFundBrokerList;
   FamilyCodeList *_pFamilyCodeList;
   DString _dstrCaller;
   DString _dstrSearchCodeParameter;
};

///#endif 

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/BrokerProcess.hpp-arc  $
 * 
 *    Rev 1.9   Nov 08 2011 11:56:50   dchatcha
 * P0188902 FN02 - DYN Household Project
 * 
 *    Rev 1.8   Apr 06 2009 04:18:38   kitticha
 * IN#1588682 - Small Enhancement - Feature search screen for Fund Broker Search. - additional code changes for More button
 * 
 *    Rev 1.7   Mar 26 2009 01:44:42   kitticha
 * IN#1588682 - Small Enhancement - Feature search screen for Fund Broker Search. Code review.
 * 
 *    Rev 1.6   Jul 10 2003 22:19:40   popescu
 * check in for payment instruct, used mfcan_ip_param for some interporcess param passing
 * 
 *    Rev 1.5   Mar 21 2003 17:37:20   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.4   Oct 09 2002 23:53:06   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.3   22 May 2002 18:21:32   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.2   19 Mar 2002 13:15:22   PURDYECH
 * Use #pragma once as include guard
 * Remove compile time "including..." message
 * 
 *    Rev 1.1   Feb 15 2000 18:56:18   MCNABBGL
 * changed comment format
 * 
 *    Rev 1.0   Feb 15 2000 10:59:00   SMITHDAV
 * Initial revision.
// 
//    Rev 1.2   Jan 24 2000 18:11:30   POPESCUS
// some fixes
// 
//    Rev 1.1   Jan 22 2000 15:42:14   WINNIE
// To get search work

  */




