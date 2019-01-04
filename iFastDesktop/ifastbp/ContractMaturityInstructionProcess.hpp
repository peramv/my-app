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
// ^FILE   : ContractMaturityInstructionProcess.hpp
// ^AUTHOR :  
// ^DATE   : 
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : ContractMaturityInstructionProcess
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include <bfproc\AbstractProcess.hpp>
#include <ifastbp\ifasthistoricalparameters.hpp>

// Import/Export resolution
#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif

class Shareholder;
class AddressList;
class ContractMaturityInstructionList;

class IFASTBP_LINKAGE ContractMaturityInstructionProcess : public AbstractProcess
{
// Construction
public:
   /**
    * Default constructor
    */
   ContractMaturityInstructionProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand );
   virtual ~ContractMaturityInstructionProcess();

   virtual bool doMoreRecordsExist( GenericInterface *rpGICaller, const BFContainerId& idSearch );
   
protected:
   void *getPtrForContainer (const BFContainerId& idContainer,const BFDataGroupId& idDataGroup);
   
	bool doModelessChildComplete (const Command &cmd);
	bool doModelessSetFocus(GenericInterface *rpGICaller);

	bool doRefresh(GenericInterface *rpGICaller, const I_CHAR *szOriginalCommand);

	E_COMMANDRETURN doProcess();

	SEVERITY doInit();

	SEVERITY doValidateAll( BFAbstractCBO *rpWSD,const BFDataGroupId& idDataGroup );

	SEVERITY performSearch (GenericInterface *rpGICaller, 
							const BFContainerId& idSearch, 
							E_SEARCHACTION eSearchAction);

	SEVERITY doSetField (	const GenericInterface *rpGICaller,
                            const BFContainerId &idContainer, 
                            const BFFieldId &idField,
                            const BFDataGroupId &idDataGroup, 
                            const DString &strValue,
                            bool bFormatted );

	void	doGetField (	const GenericInterface *rpGICaller,
							const BFContainerId& idContainer,
							const BFFieldId& idField,
							const BFDataGroupId& idDataGroup,
							DString &strValueOut,
							bool bFormatted
							) const;

private:
   GenericInterface					*_rpChildGI;

   MFAccount						*m_pMFAccount;

   ContractMaturityInstructionList	*m_pContractMatInstrList;

   AddressList						*m_pAddressList;
   Shareholder						*m_pShareholder;

   DString	m_strAcctNum,
			m_dstrCotAcctRid,
			m_strContractType,
			m_strContractTypeId,
			m_dstrPolicyYear,
			m_dstrPolicyTerm,
			m_dstrMaturityDate;
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastbp/ContractMaturityInstructionProcess.hpp-arc  $
//
//   Rev 1.1   Mar 16 2012 17:44:02   wp040100
//P0186484 FN05 - Contract Maturity Instruction Changes
//
//   Rev 1.0   Feb 21 2012 15:30:04   wp040100
//Initial revision.
//
//
 */
