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
//    AUTHOR : Yingbao  Li
//    DATE   : Nov. 5, 2002
//
//
//    Copyright 2002 by International Financial Data Service.
//
//******************************************************************************
#include <bfproc/AbstractProcess.hpp>
#include <ifastbp/ifasthistoricalparameters.hpp>
///#endif

// Forward references
class AMSMstrList;
class AMSSearchCriteria;
// Import/Export resolution
#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif


class IFASTBP_LINKAGE AMSMstProcess : public AbstractProcess, public IFastHistoricalParameters
{
// Construction
public:
//CP20030319   AMSMstProcess();
   AMSMstProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand );
   virtual ~AMSMstProcess();
   SEVERITY performSearch( GenericInterface *rpGI, 
                           const BFContainerId& idSearch, E_SEARCHACTION eSearchAction );

protected:

   virtual void doGetField(
                          const GenericInterface *rpGICaller,
                          const BFContainerId& idContainer,
                          const BFFieldId& idField,
                          const BFDataGroupId& idDataGroup,
                          DString &strValueOut,
                          bool bFormatted
                          ) const;
   virtual SEVERITY doInit();
   virtual bool doModelessChildComplete(
                                       const Command &cmd
                                       );
   virtual bool doModelessSetFocus(
                                  GenericInterface *rpGICaller
                                  );

   virtual bool doSend(
                      GenericInterface *rpGICaller,
                      const I_CHAR *szMessage
                      ) ;
   virtual E_COMMANDRETURN doProcess();
   //virtual SEVERITY ok2( GenericInterface *rpGICaller );
   // virtual void *getPtrForContainer( const BFContainerId& idContainer, const BFDataGroupId& idDataGroup );
   virtual SEVERITY doSetField(
                              const GenericInterface *rpGICaller,
                              const BFContainerId& idContainer,
                              const BFFieldId& idField,
                              const BFDataGroupId& idDataGroup,
                              const DString& strValue,
                              bool bFormatted
                              );
   virtual bool doMoreRecordsExist(
                                  GenericInterface *rpGICaller, 
                                  const BFContainerId& idSearch );
   virtual bool doOk(
                    GenericInterface *rpGICaller
                    );
	void* getPtrForContainer( const BFContainerId& idContainer, const BFDataGroupId& idDataGroup );
	virtual void doPostOk( GenericInterface *rpGICaller, bool bSuccessFlag );
	virtual bool setCommitDataGroupAsHost()
	{
		return(true);
	};
   SEVERITY getHistoricalParameters( const BFContainerId& idContainer, HISTORICAL_VECTOR &vectorInput );

private:

    GenericInterface* _rpChildGI;
    DString _dstrFromScr;
	DString _dstrAmsCode;
	DString _dstrAmsType;
	DString _dstrEffectiveDate;

	DString _oldAmsCode;
	DString _oldAmsType;
	DString _oldEffectiveDate;

	AMSMstrList* _pAmsMstrList;
    AMSSearchCriteria* _pAMSSearchCriteria;

	// for Add Copy
    DString  _dstrOrgKey;
    DString  _dstrDestKey;

};


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* 


 */