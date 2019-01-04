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
// ^FILE   : InterestSegment.hpp
// ^AUTHOR :  
// ^DATE   : 
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : InterestSegment
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

class InterestSegmentList;

class IFASTBP_LINKAGE InterestSegmentProcess : public AbstractProcess
{
// Construction
public:
   /**
    * Default constructor
    */
   InterestSegmentProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand );
   virtual ~InterestSegmentProcess();

   virtual bool doMoreRecordsExist( GenericInterface *rpGICaller, const BFContainerId& idSearch );
   
protected:
   void *getPtrForContainer (const BFContainerId& idContainer,const BFDataGroupId& idDataGroup);
   virtual SEVERITY doInit();
   virtual bool doModelessChildComplete (const Command &cmd);
   virtual bool doModelessSetFocus(GenericInterface *rpGICaller);
   virtual E_COMMANDRETURN doProcess();

private:
   GenericInterface *_rpChildGI;
   InterestSegmentList *m_pInterestSegmentList;

   DString	m_strAcctNum,
			m_strIntInvestID;
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastbp/InterestSegmentProcess.hpp-arc  $
//
//   Rev 1.0   Dec 09 2011 19:34:28   wp040100
//Initial revision.
//
//
//
//
//
 */
