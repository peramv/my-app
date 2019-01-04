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
// ^FILE   : AcctSettlementRuleProcess.hpp
// ^AUTHOR : Chatchai Daecha
// ^DATE   : Febuary 8, 2008  
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : AcctSettlementRuleProcess
//    This class manages the Account Level Settlement Rule process.
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

class AcctLvlSttlmntRuleList;

class IFASTBP_LINKAGE AcctLvlSttlmntRuleProcess : public AbstractProcess, public IFastHistoricalParameters
{
public:

    /**
    * Default constructor
    */
    AcctLvlSttlmntRuleProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand );
    virtual ~AcctLvlSttlmntRuleProcess(void);
    
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
                            
    virtual SEVERITY performSearch( GenericInterface *rpGI, const BFContainerId& idSearch, 
                                    E_SEARCHACTION eSearchAction );

    virtual bool doMoreRecordsExist(GenericInterface *rpGICaller,
                                    const BFContainerId& idSearch );

    virtual SEVERITY getHistoricalParameters( const BFContainerId& idContainer, 
                                              BFFieldId &recordIdField, DString& tableId, DString& dstrKeys);

    virtual SEVERITY getHistoricalParameters( const BFContainerId& idContainer, HISTORICAL_VECTOR &vectorInput );

    virtual SEVERITY doValidateAll(BFAbstractCBO *rpWSD, const BFDataGroupId& idDataGroup);

    virtual bool doOk( GenericInterface *rpGICaller );


private:

    GenericInterface*       _rpChildGI;
    AcctLvlSttlmntRuleList* _pAcctLvlSttlmntRuleList;
    MFAccount*              _pMFAccount;
    DString                 _accountNum;
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastbp/AcctSettlementRuleProcess.hpp-arc  $ */
//
//   Rev 1.1   Apr 16 2008 18:27:18   daechach
//PET2385 FN02&07 - Modified code regarding code review.
