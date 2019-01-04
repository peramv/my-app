#pragma once
#include <ifastxparser\dstcprocesshandler.hpp>

class AcctMailProcessHandler : public DSTCProcessHandler
{
public:
   AcctMailProcessHandler( xp::ElementHandler *parentHandler, const DString &elementName, xercesc::AttributeList &attributes );

protected:
   virtual void writeCommitParms( AbstractProcess *wsProcess, BFDocument &out );

};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastxparser/AcctMailProcessHandler.hpp-arc  $
//
//   Rev 1.0   Oct 24 2005 17:34:18   ZHANGCEL
//Initial revision.
 * 
 */

