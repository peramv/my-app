// ExtraEalSession.cpp: implementation of the ExtraEalSession class.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"

#include "ExtraEalSession.h"
#include <3rdparty\atmapi\inc\atmapi32.h>

extern "C"
{
   __declspec( dllexport ) TESession *
   CreateExtraEalSession( HWND hWnd, const char *param, const char *host )
   {
      ExtraEalSession *session = new ExtraEalSession( hWnd );
      if( NULL==session ) return(NULL);
      if( !session->init(param, host) )
      {
         delete session;
         return(NULL);
      }
      return(session);
   }

   __declspec( dllexport ) void
   ReleaseExtraEalSession(ExtraEalSession *session)
   {
      delete session;
   }

}

BOOL CALLBACK EnumExtraProc( HWND hwnd, LPARAM lParam )
{

   
   CHAR pClassName[26];
   ::GetClassName( hwnd, pClassName, 26 );
   if ( 0 == ::strcmp( pClassName, "Afx:400000:202b:10011:6:0" ) ) {

      *(HWND*)lParam = hwnd;
      return FALSE;
   }

   return TRUE;
}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

/**
 *
 */
ExtraEalSession::ExtraEalSession( HWND hWnd )
: _hWnd( hWnd )
//: _hWnd(HWND_DESKTOP)
//: _hWnd((HWND)65548)
, _hSessionWnd(NULL)
, _hPSWnd(NULL)
, _connected(false)
, _visible(false)
, _cancel(false)
{

}

/**
 *
 */
ExtraEalSession::~ExtraEalSession()
{
   try {
      setConnected(false);
      ::ATMStopSession( _hWnd );
      ::ATMDisconnectSession( _hWnd );
//      ::ATMUnregisterClient( _hWnd );
   }
   catch( ... ) {}
}

/**
 *
 */
bool
ExtraEalSession::init(const char *param, const char *host)
{
   long rc = 0;

   rc = ::ATMRegisterClient( _hWnd, ATM_EXTRA );
   if ( rc != 1 ) {
	   return false;
   }

   rc = ::ATMConnectSession( _hWnd, const_cast<char *>(param) );
   if ( rc != 1 ) {
	   return false;
   }

//   rc = ::ATMOpenConfiguration( _hWnd, const_cast<char *>(param) );
//   if ( rc != 1 ) {
//      return false;
//   }

//   rc = ::ATMSetParameter( _hWnd, ATM_XLATE, 2, "@" ); 
//   if ( rc < 1 ) {
//      return false;
//   }

   rc = ::ATMSetParameter( _hWnd, ATM_ATTRIB, 1, "" ); 
   if ( rc < 1 ) {
	   return false;
   }

   rc = ::ATMStartSession( _hWnd, const_cast<char *>(param), "H" );
   if ( rc != 1 ) {
	   return false;
   }

   rc = ::ATMSessionOff( _hWnd );
   if ( rc != 1 ) {
	   return false;
   }
   _connected = false;

   rc = ::ATMHoldHost( _hWnd );
   if ( rc != 1 ) {
	   return false;
   }

   rc = ::ATMGetSessionHandle( _hWnd, const_cast<char *>(param) );
   if ( rc <= 0 ) {
	   return false;
   }


   _hSessionWnd = (HWND)rc;

   LONG lStyle = GetWindowLong( _hSessionWnd, GWL_STYLE );
   if( lStyle & WS_SYSMENU )
   {
      SetWindowLong( _hSessionWnd, GWL_STYLE, lStyle & (~WS_SYSMENU) );
   }
   BringWindowToTop( _hSessionWnd );

   EnumChildWindows( _hSessionWnd, EnumExtraProc, (long)&_hPSWnd );
   if ( _hPSWnd == NULL ) {
      return false;
   }


   return( true );
}

/**
 *
 */
bool
ExtraEalSession::getVisible()
{
   return _visible;
}

/**
 *
 */
void
ExtraEalSession::setVisible(bool set)
{
   if ( set && !_visible ) {
      ::ShowWindow(_hSessionWnd, SW_SHOW);
   }
   else if ( !set && _visible ) {
      ::ShowWindow(_hSessionWnd, SW_HIDE);
   }
   _visible = set;
}

/**
 *
 */
bool
ExtraEalSession::getConnected()
{
   return _connected;
}

/**
 *
 */
void
ExtraEalSession::setConnected(bool set)
{
   long rc = 0;
   if( set && !_connected ) 
   {
      rc = ::ATMSessionOn( _hWnd );
   }
   else if( !set && _connected )
   {
      rc = ::ATMSessionOff( _hWnd );
   }

   if ( rc == 1 ) { 
      _connected = set;
   }

}

/**
 *
 */
void 
ExtraEalSession::sendKeyboardString(const std::string &input)
{
   ::ATMResumeHost( _hWnd );
   long rc = ::ATMSendString ( _hWnd, 0, 0, const_cast<char *>(input.c_str()) );
   ::ATMHoldHost( _hWnd );
}

/**
 *
 */
void 
ExtraEalSession::sendKeyboardSpecial(keys key)
{
   long rc=0;
   ::ATMResumeHost( _hWnd );
   switch( key )
   {
      case F1_Key:
//         rc = ::ATMSendString( _hWnd, 0, 0, "\x1B" "[17~" );
         ::PostMessage(_hPSWnd, WM_KEYDOWN, VK_F1, 0x003B0001);
         ::PostMessage(_hPSWnd, WM_KEYUP,   VK_F1, 0xC03B0001);
         ::Sleep( 200 );
         break;
      case F2_Key:
//         rc = ::ATMSendString( _hWnd, 0, 0, "\x1B" "[18~" );
         ::PostMessage(_hPSWnd, WM_KEYDOWN, VK_F2, 0x003C0001);
         ::PostMessage(_hPSWnd, WM_KEYUP,   VK_F2, 0xC03C0001);
         ::Sleep( 200 );
         break;
      case F3_Key:
//         rc = ::ATMSendString( _hWnd, 0, 0, "\x1B" "[19~" );
         ::PostMessage(_hPSWnd, WM_KEYDOWN, VK_F3, 0x003D0001);
         ::PostMessage(_hPSWnd, WM_KEYUP,   VK_F3, 0xC03D0001);
         ::Sleep( 200 );
         break;
      case F4_Key:
//         rc = ::ATMSendKey ( _hWnd, "@4");
//         rc = ::ATMSendString( _hWnd, 0, 0, "\x1B" "[20~" );
//         rc = ::ATMSendString( _hWnd, 0, 0, "<Esc>[20~" );
         ::PostMessage(_hPSWnd, WM_KEYDOWN, VK_F4, 0x003E0001);
         ::PostMessage(_hPSWnd, WM_KEYUP,   VK_F4, 0xC03E0001);
         ::Sleep( 200 );
//         silenceWait( 1000, 200 );

         break;
      case F5_Key:
//         rc = ::ATMSendString( _hWnd, 0, 0, "\x1B" "[21~" );
         ::PostMessage(_hPSWnd, WM_KEYDOWN, VK_F5, 0x003F0001);
         ::PostMessage(_hPSWnd, WM_KEYUP,   VK_F5, 0xC03F0001);
         ::Sleep( 200 );
         break;
      case F6_Key:
//         rc = ::ATMSendString( _hWnd, 0, 0, "\x1B" "[23~" );
         ::PostMessage(_hPSWnd, WM_KEYDOWN, VK_F6, 0x00400001);
         ::PostMessage(_hPSWnd, WM_KEYUP,   VK_F6, 0xC0400001);
         ::Sleep( 200 );
         break;
      case F7_Key:
//         rc = ::ATMSendString( _hWnd, 0, 0, "\x1B" "[24~" );
         ::PostMessage(_hPSWnd, WM_KEYDOWN, VK_F7, 0x00410001);
         ::PostMessage(_hPSWnd, WM_KEYUP,   VK_F7, 0xC0410001);
         ::Sleep( 200 );
         break;
      case F8_Key:
//         rc = ::ATMSendString( _hWnd, 0, 0, "\x1B" "[25~" );
         ::PostMessage(_hPSWnd, WM_KEYDOWN, VK_F8, 0x00420001);
         ::PostMessage(_hPSWnd, WM_KEYUP,   VK_F8, 0xC0420001);
         ::Sleep( 200 );
         break;
      case F9_Key:
//         rc = ::ATMSendString( _hWnd, 0, 0, "\x1B" "[26~" );
         ::PostMessage(_hPSWnd, WM_KEYDOWN, VK_F9, 0x00430001);
         ::PostMessage(_hPSWnd, WM_KEYUP,   VK_F9, 0xC0430001);
         ::Sleep( 200 );
         break;
      case F10_Key:
//         rc = ::ATMSendString( _hWnd, 0, 0, "\x1B" "[31~" );
         ::PostMessage(_hPSWnd, WM_KEYDOWN, VK_F10, 0x00440001);
         ::PostMessage(_hPSWnd, WM_KEYUP,   VK_F10, 0xC0440001);
         ::Sleep( 200 );
         break;
      case F11_Key:
//         rc = ::ATMSendString( _hWnd, 0, 0, "\x1B" "[32~" );
         ::PostMessage(_hPSWnd, WM_KEYDOWN, VK_F11, 0x00570001);
         ::PostMessage(_hPSWnd, WM_KEYUP,   VK_F11, 0xC0570001);
         ::Sleep( 200 );
         break;
      case F12_Key:
//         rc = ::ATMSendString( _hWnd, 0, 0, "\x1B" "[33~" );
         ::PostMessage(_hPSWnd, WM_KEYDOWN, VK_F12, 0x00580001);
         ::PostMessage(_hPSWnd, WM_KEYUP,   VK_F12, 0xC0580001);
         ::Sleep( 200 );
         break;
      case Tab_Key:
         rc = ::ATMSendKey ( _hWnd, "@T");
         break;
      case Return_Key:
         rc = ::ATMSendKey ( _hWnd, "@E");
         break;
      case BS_Key:
         rc = ::ATMSendKey ( _hWnd, "@\\");
         break;
      case INSERT_Key:
//         rc = ::ATMSendString( _hWnd, 0, 0, "\x1B" "[2~" );
         ::PostMessage(_hPSWnd, WM_KEYDOWN, VK_INSERT, 0x01520001);
         ::PostMessage(_hPSWnd, WM_KEYUP,   VK_INSERT, 0xC1520001);
         ::Sleep( 200 );
         break;
      case DELETE_Key:
//         rc = ::ATMSendString( _hWnd, 0, 0, "\x1B" "[3~" );
         ::PostMessage(_hPSWnd, WM_KEYDOWN, VK_DELETE, 0x01530001);
         ::PostMessage(_hPSWnd, WM_KEYUP,   VK_DELETE, 0xC1530001);
         ::Sleep( 200 );
         break;
      case HOME_Key:
//         rc = ::ATMSendString( _hWnd, 0, 0, "\x1B" "[1~" );
         ::PostMessage(_hPSWnd, WM_KEYDOWN, VK_HOME, 0x01470001);
         ::PostMessage(_hPSWnd, WM_KEYUP,   VK_HOME, 0xC1470001);
         ::Sleep( 200 );
         break;
      case END_Key:
//         rc = ::ATMSendString( _hWnd, 0, 0, "\x1B" "[4~" );
         ::PostMessage(_hPSWnd, WM_KEYDOWN, VK_END, 0x014F0001);
         ::PostMessage(_hPSWnd, WM_KEYUP,   VK_END, 0xC14F0001);
         ::Sleep( 200 );
         break;
      case PGUP_Key:
//         rc = ::ATMSendString( _hWnd, 0, 0, "\x1B" "[5~" );
         ::PostMessage(_hPSWnd, WM_KEYDOWN, VK_PRIOR, 0x01490001);
         ::PostMessage(_hPSWnd, WM_KEYUP,   VK_PRIOR, 0xC1490001);
         ::Sleep( 200 );
         break;
      case PGDN_Key:
//         rc = ::ATMSendString( _hWnd, 0, 0, "\x1B" "[6~" );
         ::PostMessage(_hPSWnd, WM_KEYDOWN, VK_NEXT, 0x01510001);
         ::PostMessage(_hPSWnd, WM_KEYUP,   VK_NEXT, 0xC1510001);
         ::Sleep( 200 );
         break;
      case UP_Key:
         rc = ::ATMSendKey ( _hWnd, "@U");
         break;
      case DOWN_Key:
         rc = ::ATMSendKey ( _hWnd, "@V");
         break;
      case LEFT_Key:
         rc = ::ATMSendKey ( _hWnd, "@L");
         break;
      case RIGHT_Key:
         rc = ::ATMSendKey ( _hWnd, "@Z");
         break;
      default:
         return;
         break;
   }
   ::ATMHoldHost( _hWnd );

}

/**
 * Note: This does not conform to the TESession contract. It waits on the entre screen  for the text to appear.
 *       It should only pick-up on new text stream from the host.
 */
long 
ExtraEalSession::streamTextWait(long timeout, const std::string &text)
{
   if( ::ATMWaitForString ( _hWnd, 0, 0, const_cast<char *>(text.c_str()), transformTimeout(timeout) ) > 0  ) {
      return(tes::EVENT_TIMEOUT);
   }
   return(tes::EVENT_SUCCESS);
}

/**
 *
 */
long 
ExtraEalSession::displayTextWait(long timeout, const std::string &text, TEPosition &position)
{
   return ExtraEalText( text, *this ).wait( timeout, position );
/*
   std::string buffer;

   // *** this is a cheesy hack 
   // line characters are reduced to /xff character is EXTRA when interpreted by the api.
   // Reflection use a set of escape characters which is what we uses in the scripts.
   // here we convert all escape characters to /xff so that EXTRA api will find then
   // if the text changed we do a short wait since this mod can cause an other wise unique
   // search to have duplicates. ( i.e. the it may trip on the top of the border instead of
   // the bottom )
   std::string modtext(text);

   bool changed = false;
   for ( int i=0; i < modtext.size(); i++  ) 
   {
      if ( modtext[i] < '\x20' ) 
      {
         modtext[i] = '\xff';
         changed = true;
      } 
   }

//   if ( changed ) {
//      silenceWait( 10000, 1500 );
//   }
   // *** end of cheesy hack


   {
      long rc = ::ATMGetParameter( _hWnd, ATM_ATTRIB ); 
      if ( rc < 1 ) {
	      return false;
      }
   }

   bool found = false;
   if( position.row == tes::POSITION_ANY )
   {
      for( int row=1; row<=24; row++ )
      {
         getDisplayText( TEPosition(row, position.column), modtext.size(), buffer);
         if( 0 == modtext.compare(buffer) )
         {
            found = true;
            break;
         }
      }
   }
   else if( position.column == tes::POSITION_ANY )
   {
      for( int col=1; col<=81-modtext.size(); col++ )
      {
         getDisplayText( TEPosition(position.row, col), modtext.size(), buffer);
         if( 0 == modtext.compare(buffer) )
         {
            found = true;
            break;
         }
      }
   }
   else
   {
      getDisplayText( position, modtext.size(), buffer);
      if( 0 == modtext.compare(buffer) )
         found = true;
   }

   if( !found )
   {
      if( timeout==0L )
      {
         return(tes::EVENT_TIMEOUT);
      }
      
      int row = position.row==tes::POSITION_ANY?0:position.row;
      int column = position.column==tes::POSITION_ANY?0:position.column;

      ::ATMResumeHost( _hWnd );
      long rc = ::ATMWaitForString ( _hWnd, row, column, const_cast<char *>(modtext.c_str()), transformTimeout(timeout) );
      ::ATMHoldHost( _hWnd );

      if( rc < 0 ) {
         return(tes::EVENT_TIMEOUT);
      }
   }

   return(tes::EVENT_SUCCESS);
*/
}

/**
 *
 */
long
ExtraEalSession::displayTextWait(long timeout, const std::string &text, TEPosition &startPos, TEPosition &endPos)
{
   return ExtraEalText( text, *this ).wait( timeout, startPos, endPos );
/*
   std::string modtext(text);

   bool changed = false;
   for ( int i=0; i < modtext.size(); i++  ) 
   {
      if ( modtext[i] < '\x20' ) 
      {
         modtext[i] = '\xff';
         changed = true;
      } 
   }


   TEPosition  pos(startPos);
   while( findDisplayTextInternal(modtext, pos ) )
   {
      if( pos.row >= startPos.row && pos.row <= endPos.row && pos.column >= startPos.column && pos.column <= endPos.column )
         return(tes::EVENT_SUCCESS);
      pos.row++; 
      if( pos.row > endPos.row )
         break;
   }

   if( timeout==0L )
   {
      return(tes::EVENT_TIMEOUT);
   }

   long lTime0=GetTickCount();
   long lTime = 0;   //current time - begin time
   while( (tes::TIMEOUT_INFINITE == timeout) ||  lTime < timeout )
   {
      for( int row = startPos.row; row<= endPos.row;row++ )
      {

         ::ATMResumeHost( _hWnd );
         long rc = ::ATMWaitForString ( _hWnd, row, 0, const_cast<char *>(modtext.c_str()), 2 );
         ::ATMHoldHost( _hWnd );

         if( rc < 0 ) {
            return(tes::EVENT_TIMEOUT);
         }

         pos.row = startPos.row; pos.column = 1;
         if( findDisplayTextInternal(modtext, pos ) )
         {
            if( pos.row >= startPos.row && pos.row <= endPos.row && pos.column >= startPos.column && pos.column <= endPos.column )
               return(tes::EVENT_SUCCESS);
         }
         lTime = GetTickCount() - lTime0;
      }
   }
   return(tes::EVENT_TIMEOUT);
*/
}

/**
 *
 */
long 
ExtraEalSession::cursorWait(long timeout, TEPosition &position)
{

   TEPosition cursorPosition;
   getCursorPosition(cursorPosition);

   if( isCursorAt( position ) ) {
      return(tes::EVENT_SUCCESS);
   }

   if( timeout==0L )
   {
      return(tes::EVENT_TIMEOUT);
   }


   int row = position.row==tes::POSITION_ANY?0:position.row;
   int column = position.column==tes::POSITION_ANY?0:position.column;

   ::ATMResumeHost( _hWnd );
   long rc = ATMWaitForCursor ( _hWnd, row, column, transformTimeout(timeout) );
   ::ATMHoldHost( _hWnd );

   if ( 1 == rc ) {
      return(tes::EVENT_SUCCESS);
   }

/*
   long time0=GetTickCount();

   while( 1 )
   {
      if ( 1 == ATMWaitForCursor ( _hWnd, row, column, 2 ) ) {
         return(tes::EVENT_SUCCESS);
      }
      if( isCursorAt( position ) ) {
         return(tes::EVENT_SUCCESS);
      }
      if( (tes::TIMEOUT_INFINITE != timeout) &&  (GetTickCount()-time0) >= timeout )
         break;
   } */

   return(tes::EVENT_TIMEOUT);
}

/**
 *
 */
long 
ExtraEalSession::silenceWait(long timeout, long duration)
{
   ::ATMResumeHost( _hWnd );
   long rc = ATMWaitHostQuiet ( _hWnd, (WORD)duration, (WORD)transformTimeout(timeout) );
   ::ATMHoldHost( _hWnd );

   if ( 1 != rc )
   {
      return(tes::EVENT_TIMEOUT);
   }

   return(tes::EVENT_SUCCESS);
}

/**
 *
 */
long
ExtraEalSession::doneWait(long timeout)
{
/*
   ::ATMResumeHost( _hWnd );
   ::Sleep( 200 );
   long rc = ATMWaitForKey( _hWnd, "@1", transformTimeout(timeout) );
   ::ATMHoldHost( _hWnd );

   if ( 1 ==  rc )
   {
      return(tes::EVENT_SUCCESS);
   }
*/

   _cancel = false;

   long time0=GetTickCount();

   while( 1 )
   {

      ::ATMResumeHost( _hWnd );
      ::Sleep( 200 );
      long rc = ATMWaitForKey( _hWnd, "@1", 2 );
      ::ATMHoldHost( _hWnd );

      if ( 1 ==  rc )
      {
         return(tes::EVENT_SUCCESS);
      }

      if( _cancel )
      {
         _cancel = false;
         return(tes::EVENT_CANCEL);
      }
      if( (tes::TIMEOUT_INFINITE != timeout) &&  ((long)GetTickCount()-time0) >= timeout )
         break;
   } 

   return(tes::EVENT_TIMEOUT);

}

/**
 *
 */
TEPosition &
ExtraEalSession::getCursorPosition(TEPosition &position)
{
   long loc = ATMGetCursorLocation ( _hWnd );
   
   position.row = ATMRowColumn ( _hWnd, (WORD)loc, ATM_GETROW );
   position.column = ATMRowColumn ( _hWnd, (WORD)loc, ATM_GETCOLUMN );

   return(position);
}

/**
 *
 */
bool
ExtraEalSession::isCursorAt(TEPosition &position)
{

   TEPosition cursorPosition;
   getCursorPosition(cursorPosition);

   if( (position.row==tes::POSITION_ANY || position.row==cursorPosition.row) &&
      (position.column==tes::POSITION_ANY || position.column==cursorPosition.column) ) {
      return(true);
   }

   return(false);

}

/**
 *
 */
TESelection &
ExtraEalSession::getCurrentSelection(TESelection &selection)
{
/*   selection.startPosition.row = rsession.GetSelectionStartRow()+1;
   selection.startPosition.column = rsession.GetSelectionStartColumn()+1;
   selection.endPosition.row = rsession.GetSelectionEndRow()+1;
   selection.endPosition.column = rsession.GetSelectionEndColumn()+1;*/
   return(selection);
}

/**
 *
 */
std::string &
ExtraEalSession::getDisplayText(const TEPosition &position, int length, std::string &buffer) const
{
   char *cBuff = new char[length+1];
   long rc = ATMGetString ( _hWnd, 
                            position.row, 
                            position.column, 
                            cBuff, 
                            length );

   buffer = cBuff;
   delete[] cBuff;
   return(buffer);

}

/**
 *
 */
bool
ExtraEalSession::findDisplayText(const std::string &text, TEPosition &position)
{

   return ExtraEalText( text, *this ).find( position );
/*
   std::string modtext(text);
   
   bool changed = false;
   for ( int i=0; i < modtext.size(); i++  ) 
   {
      if ( modtext[i] < '\x20' ) 
      {
         modtext[i] = '\xff';
         changed = true;
      } 
   }

   return findDisplayTextInternal( modtext, position );
*/
}

/**
 *
 */
void
ExtraEalSession::invokeCancel()
{
   _cancel = true;
}

/*
bool 
ExtraEalSession::findDisplayTextInternal(const std::string &modtext, TEPosition &position)
{
   long rc = ATMSearchSession( _hWnd, position.row, position.column, const_cast<char *>(modtext.c_str()), ATM_SEARCHFROM );

   if ( rc > 0 ) {
      position.row = ATMRowColumn ( _hWnd, rc, ATM_GETROW );
      position.column = ATMRowColumn ( _hWnd, rc, ATM_GETCOLUMN );
      return(true);
   }

   return(false);
}
*/

/**
 *
 */
long 
ExtraEalSession::transformTimeout( long timeout ) const
{
   if ( timeout == tes::TIMEOUT_INFINITE ) {
      return 32767;
   }

   return timeout/500;
}

const int ExtraEalText::BORDER_NO = 0;
const int ExtraEalText::BORDER_TL = 1;
const int ExtraEalText::BORDER_TR = 2;
const int ExtraEalText::BORDER_BL = 3;
const int ExtraEalText::BORDER_BR = 4;

ExtraEalText::ExtraEalText( const std::string &origText, const ExtraEalSession &session )
: _text(origText)
, _border( BORDER_NO )
, _session( session )
{

   if ( _text.size() > 0 ) {
      if ( _text[0] == '\x0e' ) {
         _border = BORDER_BL;
      }
   }

   for ( unsigned int i=0; i < _text.size(); i++  ) {
      if ( _text[i] < '\x20' ) {
         _text[i] = '\xff';
      } 
   }

}

bool 
ExtraEalText::find( TEPosition &position ) const
{
   while ( 1 ) {
      long rc = ::ATMSearchSession( _session._hWnd, position.row, position.column, const_cast<char *>(_text.c_str()), ATM_SEARCHFROM );

      if ( rc <= 0 ) {
         return(false);
      }

      TEPosition foundPos( ATMRowColumn ( _session._hWnd, (WORD)rc, ATM_GETROW ), ATMRowColumn ( _session._hWnd, (WORD)rc, ATM_GETCOLUMN ) );
      if ( verifyText( foundPos ) ) {
         position = foundPos;
         return(true);
      }

      ++position;
   }

}

bool 
ExtraEalText::find( TEPosition &position, TEPosition &endPos ) const
{
   TEPosition startPos(position);
   while( find(position) )
   {
      if( position.row >= startPos.row && 
          position.row <= endPos.row && 
          position.column >= startPos.column && 
          position.column <= endPos.column ) {
         return(true);
      }

      ++position; 
      if( position.row > endPos.row ) {
         break;
      }
   }
   return(false);
}

long
ExtraEalText::wait(long timeout, TEPosition &position) const
{
   {
      long rc = ::ATMGetParameter( _session._hWnd, ATM_ATTRIB ); 
      if ( rc < 1 ) {
	      return false;
      }
   }

   bool found = false;
   std::string buffer;

   if( position.row == tes::POSITION_ANY )
   {
      for( int row=1; row<=24; row++ )
      {
         _session.getDisplayText( TEPosition(row, position.column), _text.size(), buffer);
         if( 0 == _text.compare(buffer) )
         {
            found = true;
            break;
         }
      }
   }
   else if( position.column == tes::POSITION_ANY )
   {
      for( unsigned int col=1; col<=81-_text.size(); col++ )
      {
         _session.getDisplayText( TEPosition(position.row, col), _text.size(), buffer);
         if( 0 == _text.compare(buffer) )
         {
            found = true;
            break;
         }
      }
   }
   else
   {
      _session.getDisplayText( position, _text.size(), buffer);
      if( 0 == _text.compare(buffer) )
         found = true;
   }

   if( !found )
   {
      if( timeout==0L )
      {
         return(tes::EVENT_TIMEOUT);
      }
      
      int row = position.row==tes::POSITION_ANY?0:position.row;
      int column = position.column==tes::POSITION_ANY?0:position.column;

      ::ATMResumeHost( _session._hWnd );
      long rc = ::ATMWaitForString ( _session._hWnd, row, column, const_cast<char *>(_text.c_str()), _session.transformTimeout(timeout) );
      ::ATMHoldHost( _session._hWnd );

      if( rc < 0 ) {
         return(tes::EVENT_TIMEOUT);
      }
   }

   return(tes::EVENT_SUCCESS);
}

long
ExtraEalText::wait(long timeout, TEPosition &startPos, TEPosition &endPos) const
{
   {
      TEPosition  position(startPos);
      if ( find( position, endPos ) ) {
         return(tes::EVENT_SUCCESS);
      }
   }
//   while( find(pos ) )
//   {
//      if( pos.row >= startPos.row && pos.row <= endPos.row && pos.column >= startPos.column && pos.column <= endPos.column )
//         return(tes::EVENT_SUCCESS);
//      ++pos; 
//      if( pos.row > endPos.row )
//         break;
//   }

   if( timeout==0L )
   {
      return(tes::EVENT_TIMEOUT);
   }

   long lTime0=GetTickCount();
   long lTime = 0;   //current time - begin time
   while( (tes::TIMEOUT_INFINITE == timeout) ||  lTime < timeout )
   {
      for( int row = startPos.row; row<= endPos.row;row++ )
      {

         ::ATMResumeHost( _session._hWnd );
         long rc = ::ATMWaitForString ( _session._hWnd, row, 0, const_cast<char *>(_text.c_str()), 2 );
         ::ATMHoldHost( _session._hWnd );

         if( rc < 0 ) {
            return(tes::EVENT_TIMEOUT);
         }

         TEPosition  position(startPos);
         if ( find( position, endPos ) ) {
            return(tes::EVENT_SUCCESS);
         }
//         pos.row = startPos.row; pos.column = 1;
//         while( find(pos ) )
//         {
//            if( pos.row >= startPos.row && pos.row <= endPos.row && pos.column >= startPos.column && pos.column <= endPos.column )
//               return(tes::EVENT_SUCCESS);
//            ++pos; 
//            if( pos.row > endPos.row )
//               break;
//         }
         lTime = GetTickCount()-lTime0;
      }
   }
   return(tes::EVENT_TIMEOUT);
}

bool 
ExtraEalText::verifyText( TEPosition &position ) const
{
   std::string buffer;
   bool result = true;
   if ( _border == BORDER_TL ) {
      result = (_session.getDisplayText( TEPosition( position.row+1, position.column ), 1, buffer)[0] == '\xff' );
   }
   else if ( _border == BORDER_TR ) {
      result = (_session.getDisplayText( TEPosition( position.row+1, position.column+_text.size()-1 ), 1, buffer)[0] == '\xff' );
   }
   else if ( _border == BORDER_BL ) {
      result = (_session.getDisplayText( TEPosition( position.row-1, position.column ), 1, buffer)[0] == '\xff' );
   }
   else if ( _border == BORDER_BR ) {
      result = (_session.getDisplayText( TEPosition( position.row-1, position.column+_text.size()-1 ), 1, buffer)[0] == '\xff' );
   }

   return result;
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/tesession/extraealsession/ExtraEalSession.cpp-arc  $
// 
//    Rev 1.3   Nov 19 2004 09:23:24   PURDYECH
// PET910 - .NET Conversion
// 
//    Rev 1.2   Nov 24 2003 15:55:52   HSUCHIN
// PTS 10020087 - Enhanced to pass host information to TeSession
 */

