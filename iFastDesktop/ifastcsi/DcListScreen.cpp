// DcListScreen.cpp: implementation of the DcListScreen class.
//
//////////////////////////////////////////////////////////////////////

#include "DcListScreen.h"
#include "DcListColumn.h"
#include "CsiSession.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

DcListScreen::DcListScreen(const std::string &componentName, int topRow, int bottomRow)
:CsiScreen(componentName), _topRow(topRow), _bottomRow(bottomRow)
{

}

DcListScreen::~DcListScreen()
{

}

void 
DcListScreen::init() const
{

   CsiSession &session = CsiSession::getInstance();
   TESession * terminal = session.getTerminal();

   const DcListColumn *columns[64];
   for( int j =0; j<64; j++ )
      columns[j]=NULL;

   int columnCount=0;
   CsiComponentIterator i(this);
   while( i.hasNext() )
   {

      const CsiComponent *comp = i.getNext();
      if( typeid(*comp) == typeid(DcListColumn) )
         columns[columnCount++] = dynamic_cast<const DcListColumn*>(comp);
   }

   int currentRow = _topRow;
   while( true )
   {
      bool found = true;

      for( int currentColumn=0; currentColumn<columnCount; currentColumn++ )
      {
         const std::string &param = session.getParameter(columns[currentColumn]->getName());
         if( tes::EVENT_SUCCESS != terminal->displayTextWait( (currentRow==_topRow && currentColumn==0)?1000:200, 
                                                              param, 
                                                              TEPosition(currentRow,  columns[currentColumn]->getColumn())) )
         {
            found=false;
            break;
         }
      }

      if( found ) break;

      if( currentRow<=_bottomRow ) currentRow++;

      terminal->sendKeyboardSpecial(TESession::DOWN_Key);
      if( tes::EVENT_SUCCESS == terminal->displayTextWait(200, "End of list.", TEPosition(22, 1)) )
         throw DcListItemNotFound(getName());

   }

}