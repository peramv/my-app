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
#include <bfproc\AbstractProcess.hpp>
#include <ifastbp/ifasthistoricalparameters.hpp>
///#endif

// Forward references
class AmsLmtOverrideList;
// Import/Export resolution
#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif


class IFASTBP_LINKAGE AmsLmtOverrideProcess : public AbstractProcess, public IFastHistoricalParameters
{
// Construction
public:
   AmsLmtOverrideProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand );
   virtual ~AmsLmtOverrideProcess();
   SEVERITY performSearch(GenericInterface *rpGI, 
      const BFContainerId& idSearch, E_SEARCHACTION eSearchAction);

protected:

   virtual SEVERITY doInit();
   virtual bool doModelessChildComplete(
                                       const Command &cmd
                                       );
   virtual bool doModelessSetFocus(
                                  GenericInterface *rpGICaller
                                  );

   virtual E_COMMANDRETURN doProcess();
	void* getPtrForContainer( const BFContainerId& idContainer, const BFDataGroupId& idDataGroup );
	virtual bool doMoreRecordsExist(
                                  GenericInterface *rpGICaller, 
                                  const BFContainerId& idSearch );
   virtual SEVERITY doValidateAll(
                                 BFAbstractCBO *rpWSD,
                                 const BFDataGroupId& idDataGroup
                                 );

   SEVERITY getHistoricalParameters( const BFContainerId& idContainer, HISTORICAL_VECTOR &vectorInput );

private:

    GenericInterface* _rpChildGI;
    DString _dstrEffectiveDate;
	DString _dstrAmsCode;
	DString _dstrAmsType;
	DString _dstrAmsRecId;
	DString _dstrAmsCodeSearch;
    DString _dstrFromScr;

	AmsLmtOverrideList* _pAmsLmtOverrideList;
};


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* 


 */