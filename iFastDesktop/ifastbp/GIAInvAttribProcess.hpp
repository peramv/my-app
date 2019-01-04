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
//    Copyright 2011 by DST Systems, Inc.
//
//******************************************************************************


#include <bfproc\abstractprocess.hpp>

// Forward references

#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif

class IFASTBP_LINKAGE GIAInvAttribProcess : public AbstractProcess
{
public:
   GIAInvAttribProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand );
   virtual ~GIAInvAttribProcess();
protected:
 	virtual SEVERITY doInit();
	virtual bool doModelessChildComplete (const Command &cmd);
	virtual E_COMMANDRETURN doProcess();
	void *getPtrForContainer (const BFContainerId& idContainer,const BFDataGroupId& idDataGroup);
	virtual bool doOk (GenericInterface *rpGICaller);
   virtual SEVERITY doValidateAll ( BFAbstractCBO *rpWSD, 
                                    const BFDataGroupId& idDataGroup);
   virtual bool doSend ( GenericInterface *rpGICaller,
                         const I_CHAR  *szMessage);

   virtual bool doRefresh( GenericInterface *rpGICaller,
                           const I_CHAR *szOriginalCommand );
   virtual void doPostOk ( GenericInterface *rpGICaller, 
                           bool bSuccessFlag );

	
private:
	GenericInterface *_rpChildGI;
	DString m_Caller,
	   m_TradeListKey,
      m_accountNum;
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/GIAInvAttribProcess.hpp-arc  $
//
//   Rev 1.1   Nov 27 2011 19:33:42   popescu
//INA Commission Work
//
//   Rev 1.3   Apr 30 2010 15:31:40   popescu
//RES-QESI Trading - PSE/EAP work
//

*/
