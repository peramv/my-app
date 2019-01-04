#pragma once
#include <ifastxparser\dstcprocesshandler.hpp>

class NASUProcessHandler : public DSTCProcessHandler
{
public:
   NASUProcessHandler( xp::ElementHandler *parentHandler, const DString &elementName, xercesc::AttributeList &attributes );

protected:
   virtual void writeCommitParms( AbstractProcess *wsProcess, BFDocument &out );

};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastxparser/NASUProcessHandler.hpp-arc  $
//
//   Rev 1.4   May 10 2004 18:23:24   PURDYECH
//PET910 - Xerces2 compatibility fixes
//
//   Rev 1.3   Oct 09 2002 23:56:32   PURDYECH
//PVCS Database Conversion
//
//   Rev 1.2   Oct 07 2002 17:01:16   SMITHDAV
//Changed xp::Document to BFDocument.
//
//   Rev 1.1   Aug 02 2002 17:13:38   SMITHDAV
//Major EBF to deal with post-commit data outputs using abstract document model and random access document implementation.
//
//   Rev 1.0   Jul 04 2002 15:24:10   SMITHDAV
//Initial revision.
 * 
 */

