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
// ^FILE   : PSEEAPProcess.hpp
// ^AUTHOR :  
// ^DATE   : 
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : PSEEAPProcess
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

class PSEEAPList;

class IFASTBP_LINKAGE PSEEAPProcess : public AbstractProcess
{
// Construction
public:
   /**
    * Default constructor
    */

   PSEEAPProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand );
   virtual ~PSEEAPProcess();

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
	DString m_Caller,
	   m_TradeListKey,
	   m_AccountNum,
      m_transId;
   PSEEAPList *_pPSEEAPList;
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/PSEEAPProcess.hpp-arc  $
//
//   Rev 1.3   Apr 30 2010 15:31:40   popescu
//RES-QESI Trading - PSE/EAP work
//
//   Rev 1.2   Apr 29 2010 23:20:44   popescu
//RES-QESI Trading - PSE/EAP work
//
//   Rev 1.1   Apr 21 2010 17:19:36   popescu
//RESP-QESI Resp transfer screen
//
//   Rev 1.0   Apr 20 2010 00:59:34   popescu
//Initial revision.
//
 
*/