#pragma once
#include <xparser\cbohandler.hpp>

class TradeCBOHandler : public xp::CBOHandler
{
public:
   TradeCBOHandler( xp::ElementHandler *parentHandler, const DString &elementName, xercesc::AttributeList &attributes );

protected:

   virtual SEVERITY doValidate( xp::CBOAction action, 
                                AbstractProcess *process, 
                                const BFContainerId& idContainer );

   virtual void writeFields( xp::CBOAction action, 
                             AbstractProcess *process, 
                             const BFContainerId& idContainer,
                             BFDocument &out );

   virtual void writeCommitFields( xp::CBOAction action, 
                                   AbstractProcess *wsProcess, 
                                   BFDocument &out );

private:
   DString transNum_;
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastxparser/TradeCBOHandler.hpp-arc  $
//
//   Rev 1.6   Jan 27 2005 16:09:38   smithdav
//Made enum name changes related to base changes.
//
//   Rev 1.5   May 10 2004 18:23:44   PURDYECH
//PET910 - Xerces2 compatibility fixes
//
//   Rev 1.4   Mar 21 2003 18:48:38   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.3   Oct 09 2002 23:56:32   PURDYECH
//PVCS Database Conversion
//
//   Rev 1.2   Oct 07 2002 17:01:18   SMITHDAV
//Changed xp::Document to BFDocument.
//
//   Rev 1.1   Aug 02 2002 17:13:38   SMITHDAV
//Major EBF to deal with post-commit data outputs using abstract document model and random access document implementation.
//
//   Rev 1.0   07 Jun 2002 10:56:52   SMITHDAV
//Initial revision.
 * 
 */

