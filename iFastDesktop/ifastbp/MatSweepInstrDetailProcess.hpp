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

class IFASTBP_LINKAGE MatSweepInstrDetailProcess : public AbstractProcess
{
public:
   MatSweepInstrDetailProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand );
   virtual ~MatSweepInstrDetailProcess();
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

	
private:
	GenericInterface *_rpChildGI;
	DString		m_Caller,
				m_MatSweepInstrListKey,
				m_MatSweepInstrDetailListKey,
				m_accountNum,
				m_strInstrType;
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log::   

*/
