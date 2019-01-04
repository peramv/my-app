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
// ^FILE   : TradeSettleLocationsProcess.hpp
// ^AUTHOR :  
// ^DATE   : 
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : TradeSettleLocationsProcess
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


class IFASTBP_LINKAGE TradeSettleLocationsProcess : public AbstractProcess
{
// Construction
public:
   /**
    * Default constructor
    */
	TradeSettleLocationsProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand );
	virtual ~TradeSettleLocationsProcess();

	virtual SEVERITY doInit();
	virtual bool doModelessChildComplete (const Command &cmd);
	virtual bool doModelessSetFocus(GenericInterface *rpGICaller);
	virtual E_COMMANDRETURN doProcess();
	void *getPtrForContainer (const BFContainerId& idContainer,const BFDataGroupId& idDataGroup);

	virtual bool doOk (GenericInterface *rpGICaller);

private:
	GenericInterface *_rpChildGI;
	DString m_Caller;
	DString m_TransListKey;
	DString m_TradeListKey;
	DString m_AccountNum;
	DString m_RecordType;
	DString m_DecimalDigits;
};

/* $Log:: 
 */
