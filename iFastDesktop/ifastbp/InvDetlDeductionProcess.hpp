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
//    AUTHOR : Amelia Aguila
//    DATE   : Januray 2005
//
//
//    Copyright 2004 by International Financial Data Services
//
//******************************************************************************

#include <bfproc\abstractprocess.hpp>

// Import/Export resolution
#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif


class InvDetlDeductionList;
class TransactionList;

class IFASTBP_LINKAGE InvDetlDeductionProcess : public AbstractProcess
{
// Construction
public:
   InvDetlDeductionProcess( GenericInterfaceContainer* pGIC, 
                            GenericInterface* pGIParent, 
								    const Command& rCommand );

   virtual ~InvDetlDeductionProcess();
protected:
   virtual SEVERITY doInit();

   virtual E_COMMANDRETURN doProcess();

   virtual bool doModelessChildComplete( const Command &cmd );  

   virtual SEVERITY performSearch( GenericInterface *rpGI, 
                                   const BFContainerId& idSearch, 
											  E_SEARCHACTION eSearchAction );
   
	virtual bool doMoreRecordsExist( GenericInterface *rpGICaller,
                                    const BFContainerId& idSearch );

   virtual bool doRefresh( GenericInterface *rpGICaller, 
                           const I_CHAR *szOriginalCommand )
   {
      return true;
   } 
   
	void *getPtrForContainer( const BFContainerId &idContainer,
                             const BFDataGroupId &idDataGroup );

   virtual bool doModelessSetFocus( GenericInterface *rpGICaller );

	bool doOk( GenericInterface *rpGICaller );

private:
   GenericInterface *_rpChildGI;
   
   SEVERITY processParameters();	

	InvDetlDeductionList* _pInvDetlDeductList;
   TransactionList* _pTransList;
	
   DString _dstrAccount;
	DString _dstrShareholder;
   DString _dstrTransId;

};



//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastbp/InvDetlDeductionProcess.hpp-arc  $
//
//   Rev 1.1   Feb 17 2005 13:15:12   aguilaam
//PET1198_FN01: LSIF Reason Code enhancement. 
//
//   Rev 1.0   Jan 28 2005 14:34:00   aguilaam
//Initial revision.
//

//
