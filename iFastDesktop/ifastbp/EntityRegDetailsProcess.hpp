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
//    Copyright 2000 by DST Systems, Inc.
//
//******************************************************************************
//
// ^FILE   : EntityRegDetailsProcess.hpp
// ^AUTHOR : 
// ^DATE   : 23 December 2013
//
// ----------------------------------------------------------
//
// ^CLASS    : EntityRegDetailsProcess
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :  
//
//******************************************************************************


#include <bfproc\AbstractProcess.hpp>
#include <ifastcbo\EntityRegDetailsList.hpp>
#include <ifastcbo\EntityRegJurisDetailsList.hpp>
#include <ifastbp\ifasthistoricalparameters.hpp>

// Forward references
class MFAccount;

// Import/Export resolution
#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
#define IFASTBP_LINKAGE CLASS_EXPORT
#else
#define IFASTBP_LINKAGE CLASS_IMPORT
#endif


class IFASTBP_LINKAGE EntityRegDetailsProcess : public AbstractProcess, public IFastHistoricalParameters
{

public:
	EntityRegDetailsProcess(GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand);
	virtual ~EntityRegDetailsProcess();

protected:

	virtual SEVERITY doInit();
	virtual E_COMMANDRETURN doProcess();

	virtual bool doRefresh(GenericInterface *rpGICaller, const I_CHAR *szOriginalCommand);
	virtual bool doModelessSetFocus(GenericInterface *rpGICaller);
	virtual bool doModelessChildComplete(const Command &cmd);
	virtual void doPostOk(GenericInterface *rpGICaller, bool bSuccessFlag);
	virtual bool doOk( GenericInterface *rpGICaller );

	virtual void doGetField(const GenericInterface *rpGICaller,
							const BFContainerId& idContainer,
							const BFFieldId& idField,
							const BFDataGroupId& idDataGroup,
							DString &strValueOut,
							bool bFormatted) const;

	virtual void *getPtrForContainer(const BFContainerId &idContainer, const BFDataGroupId &idDataGroup);

	virtual SEVERITY getHistoricalParameters(const BFContainerId& idContainer, 
		BFFieldId &recordIdField, DString& tableId, DString& dstrKey); 

	SEVERITY getHistoricalParameters(const BFContainerId& idContainer, HISTORICAL_VECTOR &vectorInput);

private:
	GenericInterface *_rpChildGI;
	DString _dstrAccountNum;
	DString _dstrEntityId;
	DString _dstrCaller;
};


