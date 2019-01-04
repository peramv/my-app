#pragma once
#include <ifastxparser\dstcprocesshandler.hpp>

class NASUChildProcessHandler : public DSTCProcessHandler
{
public:
   NASUChildProcessHandler( xp::ElementHandler *parentHandler, const DString &elementName, xercesc::AttributeList &attributes );

protected:
   virtual void setProcessParms( AbstractProcess *process );
   virtual void getProcessParms( AbstractProcess *process );

};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastxparser/NASUChildProcessHandler.hpp-arc  $
//
//   Rev 1.5   May 10 2004 18:23:20   PURDYECH
//PET910 - Xerces2 compatibility fixes
//
//   Rev 1.4   Oct 09 2002 23:56:32   PURDYECH
//PVCS Database Conversion
//
//   Rev 1.3   Jul 04 2002 15:23:24   SMITHDAV
//NASU support and minor interface changes.
//
//   Rev 1.2   Jul 03 2002 10:54:12   SMITHDAV
//Write specific implementation.
//
//   Rev 1.1   Jun 14 2002 17:59:36   SMITHDAV
//Restored activity tracking code.
//
//   Rev 1.0   07 Jun 2002 10:56:52   SMITHDAV
//Initial revision.
 * 
 */

