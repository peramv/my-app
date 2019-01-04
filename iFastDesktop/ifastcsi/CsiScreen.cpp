// CsiScreen.cpp: implementation of the CsiScreen class.
//
//////////////////////////////////////////////////////////////////////

#include "CsiScreen.h"
#include "CsiIdentifier.h"
#include "CsiSession.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CsiScreen::CsiScreen(const std::string &componentName)
:CsiContainer(componentName)
{

}

CsiScreen::~CsiScreen()
{

}

void
CsiScreen::wait(long timeout) const
{
   CsiComponentIterator i(this);

   while( i.hasNext() )
   {
		CsiSession::getInstance().getTerminal()->silenceWait(3000, 500);


      const CsiComponent *comp = i.getNext();

      if( typeid(*comp) == typeid(CsiIdentifier) )
      {
         const CsiIdentifier *identifier = dynamic_cast<const CsiIdentifier*>(comp);

         identifier->wait(timeout);

      }

   }

} 

bool
CsiScreen::tryWait(long timeout) const
{
   CsiComponentIterator i(this);

   while( i.hasNext() )
   {

      const CsiComponent *comp = i.getNext();

      if( typeid(*comp) == typeid(CsiIdentifier) )
      {
         const CsiIdentifier *identifier = dynamic_cast<const CsiIdentifier*>(comp);

         if( !identifier->tryWait(timeout) )
            return(false);

      }

   }

   return(true);
} 