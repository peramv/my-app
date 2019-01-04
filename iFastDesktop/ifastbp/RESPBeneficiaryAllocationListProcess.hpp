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
// ^FILE   : RESPBeneficiaryAllocationListProcess.hpp
// ^AUTHOR :  
// ^DATE   : 
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : RESPBeneficiaryAllocationListProcess
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

class RegDocumentList;

class IFASTBP_LINKAGE RESPBeneficiaryAllocationListProcess : public AbstractProcess
{
// Construction
public:
   /**
    * Default constructor
    */

   RESPBeneficiaryAllocationListProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand );
   virtual ~RESPBeneficiaryAllocationListProcess();

 	virtual SEVERITY doInit();
	virtual bool doModelessChildComplete (const Command &cmd);
	virtual bool doModelessSetFocus(GenericInterface *rpGICaller);
	virtual E_COMMANDRETURN doProcess();
	void *getPtrForContainer (const BFContainerId& idContainer,const BFDataGroupId& idDataGroup);
   virtual bool setCommitDataGroupAsHost();
	virtual bool doOk (GenericInterface *rpGICaller);
   virtual SEVERITY doValidateAll ( BFAbstractCBO *rpWSD, const BFDataGroupId& idDataGroup);

private:
	GenericInterface *_rpChildGI;
	DString m_Caller,
			m_RESPTransListKey,
			m_TradeListKey,
			m_AccountNum,
			m_DecimalDigits,
			m_HistoryPending,
			m_disableScreen,
			m_TransId,
			m_HRDCPending;
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/RESPBeneficiaryAllocationListProcess.hpp-arc  $
//
//   Rev 1.6   Oct 27 2010 10:22:54   jankovii
//IN 2305655 - FN03 QESI - RESP Beneficiary Allocation History Button
//
//   Rev 1.5   Jun 21 2010 17:19:54   popescu
//Incident 2162449 - REL Pre99 Bene Alloc button grayed out on RESP Transaction History Screen
//
//   Rev 1.4   Apr 23 2010 18:50:44   popescu
//PET165541_FN01_QESI - RESP Gap_Dsk_Trading - fixed RESP Transfer fixed session 115 
//
//   Rev 1.3   Mar 31 2010 00:24:14   popescu
//PET165541_FN01_QESI - RESP Gap_Dsk_Trading - bene allocation updates
//
//   Rev 1.2   Mar 29 2010 23:06:20   popescu
//PET165541_FN01_QESI - RESP Gap_Dsk_Trading
 * 
 *    Rev 1.15   Mar 29 2010 10:49:40   jankovii
 * PET165541_FN01_QESI - RESP Gap_Dsk_Trading
 * 
*/