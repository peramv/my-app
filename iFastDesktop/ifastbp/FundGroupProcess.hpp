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

class FundGroupSubList;
class FundSponsorsList;

class IFASTBP_LINKAGE FundGroupProcess : public AbstractProcess
{

public:

   FundGroupProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand );
   virtual ~FundGroupProcess();

protected:

   virtual E_COMMANDRETURN doProcess();
   virtual bool doRefresh (GenericInterface *rpGICaller, const I_CHAR *szOriginalCommand) {
      return(false);
   }
   virtual SEVERITY doInit();
   virtual void doPostOk(GenericInterface *rpGICaller, bool bSuccessFlag );

private:

   FundGroupSubList *m_pFundGroupSubList;
	FundSponsorsList *m_pFundSponsorsList;
   GenericInterface  *m_rpChildGI; 
	DString m_dstrSponsorGroup;
};


///#endif 

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/*
*/