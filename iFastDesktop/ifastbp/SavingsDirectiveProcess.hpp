#pragma once
//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by International Financial Data Services,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 1997 by International Financial Data Services
//
//******************************************************************************
//
// ^FILE   : SavingsDirectiveProcess.hpp
// ^AUTHOR : 
// ^DATE   : 15 Nov 2005
//
// ----------------------------------------------------------
//
// ^CLASS    : SavingsDirectiveProcess
//
//******************************************************************************


#include <bfproc\AbstractProcess.hpp>
///#endif

// Forward references
class SavingsDirective;

// Import/Export resolution
#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif


class IFASTBP_LINKAGE SavingsDirectiveProcess : public AbstractProcess
{
// Construction
public:
   /**
    * Default constructor
    */
   SavingsDirectiveProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand );
   virtual ~SavingsDirectiveProcess();
protected:
   virtual SEVERITY doInit();
	bool doModelessChildComplete( const Command &cmd ) ;
	bool doModelessSetFocus( GenericInterface *rpGICaller ) ;
	bool doSend(GenericInterface *rpGICaller, const I_CHAR *szMessage ) ;

	virtual bool doOk(GenericInterface *rpGICaller);

	/**
     * Implementation to support the process method.
     * @returns an enum representing the return type
     */
   virtual E_COMMANDRETURN doProcess();
   virtual SEVERITY doValidateAll( BFAbstractCBO *rpWSD, const BFDataGroupId& idDataGroup );
   virtual void *getPtrForContainer ( const BFContainerId &idContainer, 
                                      const BFDataGroupId &idDataGroup);
private:     
	SEVERITY processParameters();
	SavingsDirective *_pSavingsDirective;
	DString	_accountNum, 
				_transID,
				_fundCode,
				_classCode,
				_tis,
				_tisType,
				_cost,
				_costType,
				_eusdOverrideVer,
				_tradeDate;
	GenericInterface *_rpChildGI;
};


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/SavingsDirectiveProcess.hpp-arc  $
//
//   Rev 1.1   Jan 10 2006 16:27:06   AGUILAAM
//IN 513452 - refresh Savings Directive screen based on highlighted trade when EUSD button is clicked
//
//   Rev 1.0   Nov 29 2005 17:02:48   AGUILAAM
//Initial revision.
//
// */


