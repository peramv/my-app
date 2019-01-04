#pragma once
#include <ifastxparser\dstcprocesshandler.hpp>

class AcctMailProdProcessHandler : public DSTCProcessHandler
{
public:
   AcctMailProdProcessHandler( xp::ElementHandler *parentHandler, const DString &elementName, xercesc::AttributeList &attributes );

protected:
   virtual void writeCommitParms( AbstractProcess *wsProcess, BFDocument &out );

};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastxparser/AcctMailProdProcessHandler.hpp-arc  $
//
//   Rev 1.0   Oct 24 2005 17:34:42   ZHANGCEL
//Initial revision.
 * 
 */

