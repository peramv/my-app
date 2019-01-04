// DcInputScreen.cpp: implementation of the DcInputScreen class.
//
//////////////////////////////////////////////////////////////////////

#include "DcInputScreen.h"
#include "DcInputField.h"
#include "CsiSession.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

DcInputScreen::DcInputScreen(const std::string &componentName)
:CsiScreen(componentName)
{

}

DcInputScreen::~DcInputScreen()
{

}

void 
DcInputScreen::init() const
{

   CsiSession &session = CsiSession::getInstance();
   TESession * terminal = session.getTerminal();

   const DcInputField *fields[128];
   for( int j =0; j<128; j++ )
      fields[j]=NULL;

   int maxIndex=0;
   CsiComponentIterator i(this);
   while( i.hasNext() )
   {

      const CsiComponent *comp = i.getNext();
      if( typeid(*comp) == typeid(DcInputField) )
      {
         const DcInputField *field = dynamic_cast<const DcInputField*>(comp);

         int index = field->getTabOrder()-1;
         if( index < 128 )
         {
            if( fields[index] == NULL )
               fields[index] = field;
//            else
//               throw ();

            if( index > maxIndex )
               maxIndex = index;
         }

      }

   }

   for( int j=0; j<=maxIndex; j++ )
   {
      if( fields[j] != NULL )
      {
//         if ( tes::EVENT_SUCCESS != terminal->cursorWait(15000, TEPosition(fields[j]->getRow(), fields[j]->getColumn()) ) )
//            throw DcInputFieldNotFound(fields[j]->getName(), fields[j]->getRow(), fields[j]->getColumn());
         terminal->sendKeyboardString( session.getParameter(fields[j]->getName(),"") );
      }

      if( j==maxIndex )
         break;
      terminal->sendKeyboardSpecial(TESession::Tab_Key);

   }

}
