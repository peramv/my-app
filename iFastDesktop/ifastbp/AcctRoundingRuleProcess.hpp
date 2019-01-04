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
//    Copyright 2008 by International Financial.
//
//******************************************************************************

//******************************************************************************
//
// ^FILE   : AcctRoundingRuleProcess.hpp
// ^AUTHOR : 
// ^DATE   :  
//
// -----------------------------------------------------------------------------
//
// ^CLASS  : AcctRoundingRuleProcess
//			 This class manages the Account Rounding Rule process.
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include <bfproc/abstractprocess.hpp>
#include <ifastbp/ifasthistoricalparameters.hpp>

// Import/Export resolution
#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif

class AcctRoundingRuleList;

class IFASTBP_LINKAGE AcctRoundingRuleProcess : public AbstractProcess, public IFastHistoricalParameters
{
public:

    /**
    * Default constructor
    */
    AcctRoundingRuleProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand );
    virtual ~AcctRoundingRuleProcess(void);
    
protected:

    virtual SEVERITY doInit();
    virtual E_COMMANDRETURN doProcess();

    virtual  bool doRefresh(
                            GenericInterface *rpGICaller,
                            const I_CHAR *szOriginalCommand
                            );


    void *getPtrForContainer(
                            const BFContainerId& idContainer, const BFDataGroupId& idDataGroup
                            );

    virtual bool doModelessSetFocus( GenericInterface *rpGICaller );
    virtual bool doModelessChildComplete( const Command &cmd );
    virtual void doGetField(
                            const GenericInterface *rpGICaller,
                            const BFContainerId& idContainer,
                            const BFFieldId& idField,
                            const BFDataGroupId& idDataGroup,
                            DString &strValueOut,
                            bool bFormatted
                            ) const;

    virtual SEVERITY doSetField(
                                const GenericInterface *rpGICaller,
                                const BFContainerId& idContainer,
                                const BFFieldId& idField,
                                const BFDataGroupId& idDataGroup,
                                const DString& strValue,
                                bool  bFormatted
                                );
                            
    virtual SEVERITY performSearch( GenericInterface *rpGI, const BFContainerId& idSearch, E_SEARCHACTION eSearchAction );

    virtual bool doMoreRecordsExist(GenericInterface *rpGICaller, const BFContainerId& idSearch );   

    virtual SEVERITY doValidateAll(BFAbstractCBO *rpWSD, const BFDataGroupId& idDataGroup);

    virtual bool doOk( GenericInterface *rpGICaller );

	virtual SEVERITY getHistoricalParameters( const BFContainerId& idContainer, BFFieldId &recordIdField, DString& tableId, DString& dstrKeys);

    virtual SEVERITY getHistoricalParameters( const BFContainerId& idContainer, HISTORICAL_VECTOR &vectorInput );


private:

    GenericInterface*        _rpChildGI;
    AcctRoundingRuleList*	 _pAcctRoundingRuleList;
    MFAccount*               _pMFAccount;
    DString                  _accountNum;
	DString					 _dstrNewAccount;
	DString					 _dstrNewShareholder;
};
