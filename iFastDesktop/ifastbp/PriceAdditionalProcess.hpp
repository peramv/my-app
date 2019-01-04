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
// ^FILE   : PriceAdditionalProcess.hpp
// ^AUTHOR : 
// ^DATE   : 03 May 2017
//
// ----------------------------------------------------------
//
// ^CLASS    : 
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :  
//
//******************************************************************************


#include <bfproc\AbstractProcess.hpp>
#include <ifastcbo\AlertMessageList.hpp>

// Forward references
class PriceAdditionalList;

// Import/Export resolution
#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
#define IFASTBP_LINKAGE CLASS_EXPORT
#else
#define IFASTBP_LINKAGE CLASS_IMPORT
#endif


class IFASTBP_LINKAGE PriceAdditionalProcess : public AbstractProcess
{
public:
	PriceAdditionalProcess(GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand);
	virtual ~PriceAdditionalProcess();

protected:
	virtual SEVERITY doInit();
	virtual E_COMMANDRETURN doProcess();

	virtual bool doRefresh(GenericInterface *rpGICaller, const I_CHAR *szOriginalCommand);
	virtual bool doModelessSetFocus(GenericInterface *rpGICaller);
	virtual bool doModelessChildComplete(const Command &cmd);
	virtual void doPostOk(GenericInterface *rpGICaller, bool bSuccessFlag);
	virtual bool doOk( GenericInterface *rpGICaller );

	virtual void *getPtrForContainer(const BFContainerId &idContainer, const BFDataGroupId &idDataGroup);

    virtual void doGetField(const GenericInterface *rpGICaller,
                            const BFContainerId& idContainer,
                            const BFFieldId& idField,
                            const BFDataGroupId& idDataGroup,
                            DString &strValueOut,
                            bool bFormatted) const;

private:
    GenericInterface *_rpChildGI;

    PriceAdditionalList *_pPriceAdditionalList;
    DString _tradeDate, _fundCode, _classCode;
    DString _priceCode, _unitValue, _chgFactor;
    DString _priceCode2, _unitValue2, _chgFactor2;
    DString _priceCode3, _unitValue3, _chgFactor3;
    DString _priceCode4, _unitValue4, _chgFactor4;
    DString _priceCode5, _unitValue5, _chgFactor5;
	DString _priceCode6, _unitValue6, _chgFactor6;
	DString _priceCode7, _unitValue7, _chgFactor7;
	DString _priceCode8, _unitValue8, _chgFactor8;
	DString _priceCode9, _unitValue9, _chgFactor9;
	DString _priceCode10, _unitValue10, _chgFactor10;
	DString _priceCode11, _unitValue11, _chgFactor11;
	DString _priceCode12, _unitValue12, _chgFactor12;
	DString _priceCode13, _unitValue13, _chgFactor13;
};


