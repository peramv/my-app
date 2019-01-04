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
// FILE   : RDSPTransfersProcess.hpp
// AUTHOR :  
// DATE   : 
//
// -----------------------------------------------------------------------------
//
// CLASS  : RDSPTransfersProcess
//
// MEMBER VARIABLES :
//
// CODING COMMENTS  :
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

class RDSPTransfer;

class IFASTBP_LINKAGE RDSPTransfersProcess : public AbstractProcess
{
// Construction
public:
	/**
	* Default constructor
	*/

	RDSPTransfersProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand );
	virtual ~RDSPTransfersProcess();

	virtual SEVERITY doInit();
	virtual bool doModelessChildComplete (const Command &cmd);
	virtual bool doModelessSetFocus(GenericInterface *rpGICaller);
	virtual E_COMMANDRETURN doProcess();
	void *getPtrForContainer (const BFContainerId& idContainer,const BFDataGroupId& idDataGroup);
	virtual bool doOk (GenericInterface *rpGICaller);
	virtual void doPostOk ( GenericInterface *rpGICaller, bool bSuccessFlag);
	virtual SEVERITY doValidateAll ( BFAbstractCBO *rpWSD, const BFDataGroupId& idDataGroup);

protected:

	virtual SEVERITY doSetField (const GenericInterface *rpGICaller, 
								 const BFContainerId &idContainer, 
								 const BFFieldId &idField, 
								 const BFDataGroupId &idDataGroup, 
								 const DString &strValue, 
								 bool bFormatted);

	virtual void doGetField (const GenericInterface *rpGICaller,  
							 const BFContainerId &idContainer, 
							 const BFFieldId &idField, 
							 const BFDataGroupId &idDataGroup, 
							 DString &strValueOut, 
							 bool bFormtted) const;

	virtual const BFProperties *doGetFieldAttributes (const GenericInterface *rpGICaller, 
													  const BFContainerId &idContainer, 
													  const BFFieldId &idField, 
													  const BFDataGroupId &idDataGroup);

	virtual SEVERITY doGetErrors ( const GenericInterface *rpGICaller,
								   const BFContainerId &idContainer,
								   const BFFieldId &idField,
								   const BFDataGroupId &idDataGroup,
								   CONDITIONVECTOR &conditions) const;

private:
	GenericInterface *_rpChildGI;

	RDSPTransfer* _pRDSPTransfer;

	DString m_Caller,
			m_RDSPTransListKey,
			m_TradeListKey,
			m_AccountNum,
			m_DecimalDigits,	  
			m_TransType,
			m_DepositType,
			m_RedCode;
	
};
