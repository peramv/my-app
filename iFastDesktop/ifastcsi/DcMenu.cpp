// DcMenu.cpp: implementation of the DcMenu class.
//
//////////////////////////////////////////////////////////////////////

#include "DcMenu.h"
#include "DcMenuItem.h"
#include "CsiIdentifier.h"
#include "CsiSession.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

DcMenu::DcMenu(const std::string &componentName, int itemColumn,int Column2)
:CsiScreen(componentName), _itemColumn(itemColumn),_itemColumn2(Column2)
{

}

DcMenu::~DcMenu()
{

}

void 
DcMenu::select(const std::string &componentName) const
{
   if( isRect() )
   {
      if( !trySelect1(componentName) )
         throw DcMenuItemNotIdentified(componentName);
   }
   else
   {
      if( !trySelect(componentName) )
         throw DcMenuItemNotIdentified(componentName);
   }
}

bool
DcMenu::isRect()  const
{
   if( _itemColumn < _itemColumn2 )  return(true);
   else return(false);
}

bool 
DcMenu::isInRect(TEPosition pos,TEPosition leftTop,TEPosition rightBtm ) const
{
   if( pos.column >= leftTop.column && pos.column <= rightBtm.column && pos.row >= leftTop.row && pos.row <= rightBtm.row ) return(true);
   else return(false);
}


bool
DcMenu::trySelect1(const std::string &componentName) const
{
   TEPosition leftTop,rightBtm;

   CsiSession &session = CsiSession::getInstance();
   TESession * terminal = session.getTerminal();


   // find the "Menu Header" identifier
   const CsiIdentifier *identifier = dynamic_cast<const CsiIdentifier*> (getComponent("Menu Header"));

   TEPosition headerPosition;
   while( 1 )
   {
      if( !terminal->findDisplayText(identifier->getIdText() , headerPosition) )
         return(false); // not found
      identifier->getRect(leftTop.row,leftTop.column,rightBtm.row,rightBtm.column);
      if( isInRect(headerPosition,leftTop,rightBtm ) )break;  //found
      ++headerPosition;
   }


   // find the "Menu Trailer" identifier
   identifier = dynamic_cast<const CsiIdentifier*> (getComponent("Menu Trailer"));

   TEPosition trailerPosition (headerPosition);
   while( 1 )
   {
      if( !terminal->findDisplayText(identifier->getIdText() , trailerPosition) )
         return(false); // not found
      identifier->getRect(leftTop.row,leftTop.column,rightBtm.row,rightBtm.column);
      if( isInRect(trailerPosition,leftTop,rightBtm ) ) break;  //found
      ++trailerPosition;
   }

   // look for a More menu Item as the lat item
   bool hasMore = false;
   TEPosition morePosition;
   leftTop.row = trailerPosition.row-3; leftTop.column = _itemColumn;
   rightBtm.row = trailerPosition.row; rightBtm.column = _itemColumn2; 
   while( 1 )
   {
      if( !terminal->findDisplayText("More",morePosition ) )break; //not found
      if( isInRect(morePosition,leftTop,rightBtm ) )
      {
         hasMore = true; break;
      } //found
      ++morePosition ;
   }

   if( tes::EVENT_SUCCESS == terminal->displayTextWait(1000, "More", TEPosition(trailerPosition.row-1,  _itemColumn)) )
      hasMore = true;

   for( int currentRow = headerPosition.row+1; currentRow<=trailerPosition.row-1; currentRow++ )
   {
      if( currentRow == trailerPosition.row-1 && hasMore )
      {
         const DcMenu *moreMenu = dynamic_cast<const DcMenu*> (getComponent("More Menu"));

         terminal->sendKeyboardSpecial(TESession::Return_Key);
         moreMenu->wait(15000);
         if( moreMenu->trySelect1(componentName) )
         {
            return(true);
         }
         else
         {
            terminal->sendKeyboardSpecial(TESession::F4_Key);
            wait(15000); // wait for this menu screen...
            return(false);
         }
      }

      if( tes::EVENT_SUCCESS == terminal->displayTextWait(1000, componentName, TEPosition(currentRow,  trailerPosition.column),TEPosition(currentRow,trailerPosition.column+10)) )
      {
         terminal->sendKeyboardSpecial(TESession::Return_Key);
         return(true);
      }


      terminal->sendKeyboardSpecial(TESession::DOWN_Key);

   }

   return(false); // not found
}




bool
DcMenu::trySelect(const std::string &componentName) const
{

//   const CsiComponent *comp = getComponent(componentName);

//   if ( typeid(*comp) != typeid(DcMenuItem) )
//      return;

//   const DcMenuItem *menuItem = dynamic_cast<const DcMenuItem*>(comp);

   CsiSession &session = CsiSession::getInstance();
   TESession * terminal = session.getTerminal();


   // find the "Menu Header" identifier
   const CsiIdentifier *identifier = dynamic_cast<const CsiIdentifier*> (getComponent("Menu Header"));

   TEPosition headerPosition;
   while( 1 )
   {
      if( !terminal->findDisplayText(identifier->getIdText() , headerPosition) )
         return(false); // not found

      if( ( identifier->getRow() == tes::POSITION_ANY    || headerPosition.row == identifier->getRow()       ) && 
          ( identifier->getColumn() == tes::POSITION_ANY || headerPosition.column == identifier->getColumn() ) )
         break; // found 

      ++headerPosition;
   }


   // find the "Menu Trailer" identifier
   identifier = dynamic_cast<const CsiIdentifier*> (getComponent("Menu Trailer"));

   TEPosition trailerPosition (headerPosition);
   while( 1 )
   {
      if( !terminal->findDisplayText(identifier->getIdText() , trailerPosition) )
         return(false); // not found

      if( ( identifier->getRow() == tes::POSITION_ANY    || trailerPosition.row == identifier->getRow()       ) && 
          ( identifier->getColumn() == tes::POSITION_ANY || trailerPosition.column == identifier->getColumn() ) )
         break; // found 

      ++trailerPosition;
   }

   // look for a More menu Item as the lat item
   bool hasMore = false;
   if( tes::EVENT_SUCCESS == terminal->displayTextWait(1000, "More", TEPosition(trailerPosition.row-1,  _itemColumn)) )
      hasMore = true;

   for( int currentRow = headerPosition.row+1; currentRow<=trailerPosition.row-1; currentRow++ )
   {
      if( currentRow == trailerPosition.row-1 && hasMore )
      {
         const DcMenu *moreMenu = dynamic_cast<const DcMenu*> (getComponent("More Menu"));

         terminal->sendKeyboardSpecial(TESession::Return_Key);
         moreMenu->wait(15000);
         if( moreMenu->trySelect(componentName) )
         {
            return(true);
         }
         else
         {
            terminal->sendKeyboardSpecial(TESession::F4_Key);
            wait(15000); // wait for this menu screen...
            return(false);
         }
      }

      if( tes::EVENT_SUCCESS == terminal->displayTextWait(0, componentName, TEPosition(currentRow,  _itemColumn)) )
      {
         terminal->sendKeyboardSpecial(TESession::Return_Key);
         return(true);
      }


      terminal->sendKeyboardSpecial(TESession::DOWN_Key);

   }

   return(false); // not found
}
