#pragma once
#include <bfproc\AbstractProcess.hpp>

class ValueVariationProcess 
   :public AbstractProcess
{
public:
   ValueVariationProcess(GenericInterfaceContainer* pGIC,
      GenericInterface* pGIParent, 
      const Command& rCommand);
   ~ValueVariationProcess(void);

private:
   virtual SEVERITY doInit();
   virtual E_COMMANDRETURN doProcess();
   virtual bool doModelessSetFocus( GenericInterface *rpGICaller );
   virtual bool doModelessChildComplete( const Command &cmd );
   virtual SEVERITY doValidateAll( BFAbstractCBO *rpWSD, const BFDataGroupId& idDataGroup );
   GenericInterface *_rpChildGI;
};