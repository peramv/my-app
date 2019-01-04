// CsiIdentifier.cpp: implementation of the CsiIdentifier class.
//
//////////////////////////////////////////////////////////////////////

#include "CsiSession.h"
#include "CsiIdentifier.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CsiIdentifier::CsiIdentifier(const std::string &componentName, int row, int column)
: CsiComponent(componentName), _idText(componentName), _row(row), _column(column)
{

}

CsiIdentifier::CsiIdentifier(const std::string &componentName, const std::string &idText, int row, int column,int r,int c)
: CsiComponent(componentName), _idText(idText), _row(row), _column(column), _rRightBtm(r),_cRightBtm(c)
{

}

CsiIdentifier::~CsiIdentifier()
{

}

void
CsiIdentifier::wait(long timeout) const 
{

   if( !tryWait(timeout) )
      throw CsiComponentWaitTimeout(getName());

}

bool CsiIdentifier:: isRect()  const
{
   if( _row < _rRightBtm && _column < _cRightBtm ) return(true);
   else return(false);

}


bool
CsiIdentifier::tryWait(long timeout)  const
{
   CsiSession &session = CsiSession::getInstance();
   TESession * terminal = session.getTerminal();

   long retCode;

   if( isRect() )
   {
      retCode = terminal->displayTextWait(timeout, _idText.c_str(), TEPosition(_row, _column),TEPosition(_rRightBtm,_cRightBtm) );
   }
   else
   {
      retCode = terminal->displayTextWait(timeout, _idText.c_str(), TEPosition(_row, _column));
   }
   if( tes::EVENT_TIMEOUT ==  retCode )
      return(false);

   if( tes::EVENT_SUCCESS !=  retCode )
      throw CsiComponentWaitFailure(getName());

   return(true);

}
