#pragma once
#include <xparser\roothandler.hpp>

class DSTCPackageHandler : public xp::RootHandler
{
public:
   DSTCPackageHandler( const DString &elementName, xercesc::AttributeList &attributes );
   DSTCPackageHandler( const DString &elementName );

protected:
   virtual void writeParms( AbstractProcess *userSessionProcess, BFDocument &out );
   virtual void logoff( AbstractProcess *userSessionProcess );

private:
   bool _logoffOnExit;
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastxparser/DSTCPackageHandler.hpp-arc  $
//
//   Rev 1.7   May 27 2004 16:29:52   SMITHDAV
//Changes to InterProcessData to move "global data" to the session level.
//
//   Rev 1.6   May 10 2004 18:22:50   PURDYECH
//PET910 - Xerces2 compatibility fixes
//
//   Rev 1.5   Oct 09 2002 23:56:30   PURDYECH
//PVCS Database Conversion
//
//   Rev 1.4   Oct 07 2002 17:01:08   SMITHDAV
//Changed xp::Document to BFDocument.
//
//   Rev 1.3   Aug 02 2002 17:13:14   SMITHDAV
//Major EBF to deal with post-commit data outputs using abstract document model and random access document implementation.
//
//   Rev 1.2   07 Jun 2002 17:08:56   SMITHDAV
//Add support for root level attributes to turn on statistics writing and verbose conditions.
//
//   Rev 1.1   14 May 2002 16:42:50   SMITHDAV
//put xparser code namespace xp.
//
//   Rev 1.0   02 Apr 2002 14:00:44   SMITHDAV
//Initial revision.
 * 
 */

