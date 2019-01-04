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
//
// ^FILE   : ProgressiveIntRate.hpp
// ^AUTHOR :  
// ^DATE   : 
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : ProgressiveIntRate
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include <bfproc\AbstractProcess.hpp>

// Import/Export resolution
#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif

class ProgressiveIntRateList;

class IFASTBP_LINKAGE ProgressiveIntRateProcess : public AbstractProcess
{
// Construction
public:
   /**
    * Default constructor
    */
   ProgressiveIntRateProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand );
   virtual ~ProgressiveIntRateProcess();

   virtual bool doMoreRecordsExist( GenericInterface *rpGICaller, const BFContainerId& idSearch );
   
protected:
   void *getPtrForContainer (const BFContainerId& idContainer,const BFDataGroupId& idDataGroup);
   virtual SEVERITY doInit();
   virtual bool doModelessChildComplete (const Command &cmd);
   virtual bool doModelessSetFocus(GenericInterface *rpGICaller);
   virtual E_COMMANDRETURN doProcess();
   //virtual bool doRefresh(GenericInterface *rpGICaller, const I_CHAR *szOriginalCommand);

private:
   GenericInterface *_rpChildGI;
   ProgressiveIntRateList *m_pProgressiveIntRateList;

   DString	m_strAcctNum,
			m_strIntInvestID;
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastbp/ProgressiveIntRateProcess.hpp-arc  $
//
//   Rev 1.1   Dec 01 2011 18:02:58   wp040100
//P0186477/FN03 - GIA - Investment History Changes
//
//   Rev 1.0   Nov 27 2011 21:16:52   wp040100
//Initial revision.
//
//
//
 */
