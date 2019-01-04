#pragma once
#include <bfproc\AbstractProcess.hpp>

class FeeModelCopyToGroupProcess 
   :public AbstractProcess
{
public:
   FeeModelCopyToGroupProcess(GenericInterfaceContainer* pGIC,
      GenericInterface* pGIParent, 
      const Command& rCommand);
   virtual ~FeeModelCopyToGroupProcess(void);

protected:
   virtual void *getPtrForContainer( const BFContainerId& idContainer, const BFDataGroupId& idDataGroup );
   virtual bool doOk( GenericInterface *rpGICaller );

private:
   virtual SEVERITY doInit();
   virtual E_COMMANDRETURN doProcess();
   virtual bool doModelessSetFocus( GenericInterface *rpGICaller );
   virtual bool doModelessChildComplete( const Command &cmd );
   GenericInterface *_rpChildGI;

   DString _feeModelCode;
   DString _feeModelRecid;
   DString _feeModelDesc;
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastbp/FeeModelCopyToGroupProcess.h-arc  $
// 