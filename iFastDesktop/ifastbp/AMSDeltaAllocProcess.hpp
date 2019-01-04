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
//    DATE   : Jan. 10, 2018
//
//
//    Copyright 2002 by International Financial Data Service.
//
//******************************************************************************
#include <bfproc\AbstractProcess.hpp>

// Forward references
class AmsFundAllocList;
class FundAllocList;
class AMSDeltaAllocList;
class AMSMstrList;
class AmsMstrInfo;
class AMSAcctLvl;

// Import/Export resolution
#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif


class IFASTBP_LINKAGE AMSDeltaAllocProcess : public AbstractProcess
{
// Construction
public:
   AMSDeltaAllocProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand );
   virtual ~AMSDeltaAllocProcess();

protected:

   virtual SEVERITY doInit();
   virtual bool doModelessChildComplete(const Command &cmd);
   virtual bool doModelessSetFocus(GenericInterface *rpGICaller);
   virtual E_COMMANDRETURN doProcess();
   void* getPtrForContainer( const BFContainerId& idContainer, const BFDataGroupId& idDataGroup );
   virtual SEVERITY doValidateAll(BFAbstractCBO *rpWSD,const BFDataGroupId& idDataGroup);
   virtual void doGetField(const GenericInterface *rpGICaller,
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
   DString _dstrCurDeff;
   DString _dstrCurAmsCode;

   bool _bFoundAlloc;
   FundAllocList* _pFundAllocList;
   AMSDeltaAllocList* _pAMSDeltaAllocList;
   AMSMstrList* _pAmsMstrList;
   AmsMstrInfo* _pAmsMstrInfo;   
   AMSAcctLvl* _pAMSAcctLvl;
};
