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
//    AUTHOR : Thanisorn Sangkrajang
//    DATE   : Jul. 23, 2017
//
//
//    Copyright 2002 by International Financial Data Service.
//
//******************************************************************************
#include <bfproc\AbstractProcess.hpp>


// Forward references
class AMSHypoAllocList;
class AmsFundAllocList;
class FundAllocList;
// Import/Export resolution
#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif


class IFASTBP_LINKAGE AMSHypoAllocProcess : public AbstractProcess
{
// Construction
public:
   AMSHypoAllocProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand );
   virtual ~AMSHypoAllocProcess();
   /*SEVERITY performSearch(GenericInterface *rpGI, 
      const BFContainerId& idSearch, E_SEARCHACTION eSearchAction);*/

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

   virtual SEVERITY doValidateAll(
                                 BFAbstractCBO *rpWSD,
                                 const BFDataGroupId& idDataGroup
                                 );

   virtual void doGetField(
                          const GenericInterface *rpGICaller,
                          const BFContainerId& idContainer,
                          const BFFieldId& idField,
                          const BFDataGroupId& idDataGroup,
                          DString &strValueOut,
                          bool bFormatted
                          ) const;

private:

    GenericInterface* _rpChildGI;
    DString _dstrEffectiveDate;
	DString _dstrAmsCode;
	DString _dstrAmsType;
	DString _dstrAccountNum;

	bool _bFoundAlloc;
	AMSHypoAllocList* _pAMSHypoAllocList;
	FundAllocList*	  _pFundAllocList;
};


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* 


 */