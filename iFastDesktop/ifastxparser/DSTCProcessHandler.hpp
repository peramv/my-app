#pragma once
#include <xparser\processhandler.hpp>

#include <map>

class DSTCProcessHandler : public xp::ProcessHandler
{
public:
   DSTCProcessHandler( xp::ElementHandler *parentHandler, const DString &elementName, xercesc::AttributeList &attributes );

protected:
   virtual bool requiresWorkSession(); // make this const
   virtual void setProcessParms( AbstractProcess *process );
   void setProcessTrackParms( AbstractProcess *process );

private:

   class ETrackMap : public std::map< DString, DString >
   {
   public:
      ETrackMap();

   private:
      void addItem( const DString &processName, const DString &trackActivity );

   };

   static ETrackMap eTrackMap_;

};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastxparser/DSTCProcessHandler.hpp-arc  $
//
//   Rev 1.4   May 10 2004 19:28:14   SMITHDAV
//Add requiresWorksession() override.
//
//   Rev 1.2   Oct 09 2002 23:56:30   PURDYECH
//PVCS Database Conversion
//
//   Rev 1.1   Jul 04 2002 15:23:22   SMITHDAV
//NASU support and minor interface changes.
//
//   Rev 1.0   Jun 18 2002 09:50:18   SMITHDAV
//Initial revision.
 * 
 */

