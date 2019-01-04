// ReflectionSession.cpp: implementation of the ReflectionSession class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "ReflectionSession.h"

extern "C"
{
   __declspec( dllexport ) TESession *
   CreateReflectionSession( HWND hWnd, const char *param, const char *host )
   {
      // Initialize OLE 2.0 libraries
      CoInitialize(NULL);

      ReflectionSession *session = new ReflectionSession();
      if( NULL==session ) return(NULL);
      if( !session->init(param, host) )
      {
         delete session;
         return(NULL);
      }
      return(session);
   }

   __declspec( dllexport ) void
   ReleaseReflectionSession(ReflectionSession *session)
   {
      delete session;
      CoUninitialize();
   }

}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ReflectionSession::ReflectionSession()
:cancel(false)
{

}

ReflectionSession::~ReflectionSession()
{
   try {
      rsession.EnableOnEvent(1L, ReflectionDispatch::rcDisable);
      rsession.Quit();
      rsession.ReleaseDispatch();
   }
   catch( ... ) {}
}

bool
ReflectionSession::init(const char *param, const char *host)
{

   COleException error;

   CLSID clsid;
   SCODE sc = AfxGetClassIDFromString("Reflection2.Session", &clsid);
   if( FAILED(sc) )
   {
      return(false);
   }

   LPCLASSFACTORY lpcf;
   sc = CoGetClassObject(clsid, CLSCTX_LOCAL_SERVER , NULL, IID_IClassFactory, (LPVOID *)&lpcf);
   if( FAILED(sc) )
   {
      return(false);
   }

   LPUNKNOWN lpUnknown = NULL;
   sc = lpcf->CreateInstance(NULL, IID_IUnknown, (LPVOID *)&lpUnknown);
   if( FAILED(sc) )
   {
      lpcf->Release();
      return(false);
   }

   // query for IDispatch interface
   LPDISPATCH lpDispatch;
   lpUnknown->QueryInterface(IID_IDispatch, (LPVOID *)&lpDispatch);
   if( lpDispatch == NULL )
   {
      lpUnknown->Release();
      lpcf->Release();
      return(false);
   }

   rsession.AttachDispatch(lpDispatch);

   int refCount;
#if 0
   LPPERSISTFILE lpPersistFile = NULL;
   lpUnknown->QueryInterface(IID_IPersistFile, (LPVOID *)&lpPersistFile);
   if( lpPersistFile == NULL )
   {
      lpUnknown->Release();
      lpcf->Release();
      return(false);
   }

   sc = lpPersistFile->Load((LPCOLESTR) L"C:\\R2Win\\User\\cfxint.r2w", STGM_READ);
   if( FAILED(sc) )
   {
      lpPersistFile->Release();
      lpcf->Release();
      return(false);
   }

   refCount = lpPersistFile->Release();
#endif
   refCount = lpUnknown->Release();

   refCount = lpcf->Release();

   rsession.SetProcessDataComm(FALSE);

   
   rsession.OpenSettings(param, COleVariant((short)1) );
   //It seems like reflection has already connected when the host is properly defined in the r2w file
   //at this point, we have to disconnect before we can change the host name.
   rsession.Disconnect();
   //Override connection settings to use DNS host from parameter passed in.
   rsession.SetConnectionSettings (( std::string("Host ") + host ).c_str());    

   rsession.SetConfirmExit(FALSE);
   rsession.EnableOnEvent(1L, ReflectionDispatch::rcEnable);
   HWND hwndWin =(HWND) rsession.GetWindowHandle();
   if( hwndWin )
   {
      LONG lStyle = GetWindowLong(hwndWin,GWL_STYLE);
      if( lStyle & WS_SYSMENU )
      {
         SetWindowLong(hwndWin, GWL_STYLE, lStyle & (~WS_SYSMENU)  );
      }
      BringWindowToTop(hwndWin);
   }

   return(true);
}

bool
ReflectionSession::getVisible()
{
   return(TRUE==rsession.GetVisible());
}

void
ReflectionSession::setVisible(bool set)
{
   rsession.SetVisible(set? TRUE: FALSE);
}

bool
ReflectionSession::getConnected()
{
   return(TRUE==rsession.GetConnected());
}

void
ReflectionSession::setConnected(bool set)
{
   if( set && FALSE==rsession.GetConnected() )
   {
      rsession.Connect(COleVariant());
   }
   else if( !set && TRUE==rsession.GetConnected() )
   {
      rsession.Disconnect();
   }
}

void 
ReflectionSession::sendKeyboardString(const std::string &input)
{
   rsession.Transmit(input.c_str(), COleVariant(ReflectionDispatch::rcIgnoreBlockMode));
}

void 
ReflectionSession::sendKeyboardSpecial(keys key)
{
   long keyMapType;
   CString keyMapCommand;
   switch( key )
   {
      case F1_Key: 
         keyMapType = rsession.GetKeyMapCommandType(ReflectionDispatch::rcNormalKey, "F1");
         keyMapCommand = rsession.GetKeyMapCommands(ReflectionDispatch::rcNormalKey, "F1");
         break;
      case F2_Key:
         keyMapType = rsession.GetKeyMapCommandType(ReflectionDispatch::rcNormalKey, "F2");
         keyMapCommand = rsession.GetKeyMapCommands(ReflectionDispatch::rcNormalKey, "F2");
         break;
      case F3_Key:
         keyMapType = rsession.GetKeyMapCommandType(ReflectionDispatch::rcNormalKey, "F3");
         keyMapCommand = rsession.GetKeyMapCommands(ReflectionDispatch::rcNormalKey, "F3");
         break;
      case F4_Key:
         keyMapType = rsession.GetKeyMapCommandType(ReflectionDispatch::rcNormalKey, "F4");
         keyMapCommand = rsession.GetKeyMapCommands(ReflectionDispatch::rcNormalKey, "F4");
         break;
      case F5_Key:
         keyMapType = rsession.GetKeyMapCommandType(ReflectionDispatch::rcNormalKey, "F5");
         keyMapCommand = rsession.GetKeyMapCommands(ReflectionDispatch::rcNormalKey, "F5");
         break;
      case F6_Key:
         keyMapType = rsession.GetKeyMapCommandType(ReflectionDispatch::rcNormalKey, "F6");
         keyMapCommand = rsession.GetKeyMapCommands(ReflectionDispatch::rcNormalKey, "F6");
         break;
      case F7_Key:
         keyMapType = rsession.GetKeyMapCommandType(ReflectionDispatch::rcNormalKey, "F7");
         keyMapCommand = rsession.GetKeyMapCommands(ReflectionDispatch::rcNormalKey, "F7");
         break;
      case F8_Key:
         keyMapType = rsession.GetKeyMapCommandType(ReflectionDispatch::rcNormalKey, "F8");
         keyMapCommand = rsession.GetKeyMapCommands(ReflectionDispatch::rcNormalKey, "F8");
         break;
      case F9_Key:
         keyMapType = rsession.GetKeyMapCommandType(ReflectionDispatch::rcNormalKey, "F9");
         keyMapCommand = rsession.GetKeyMapCommands(ReflectionDispatch::rcNormalKey, "F9");
         break;
      case F10_Key:
         keyMapType = rsession.GetKeyMapCommandType(ReflectionDispatch::rcNormalKey, "F10");
         keyMapCommand = rsession.GetKeyMapCommands(ReflectionDispatch::rcNormalKey, "F10");
         break;
      case F11_Key:
         keyMapType = rsession.GetKeyMapCommandType(ReflectionDispatch::rcNormalKey, "F11");
         keyMapCommand = rsession.GetKeyMapCommands(ReflectionDispatch::rcNormalKey, "F11");
         break;
      case F12_Key:
         keyMapType = rsession.GetKeyMapCommandType(ReflectionDispatch::rcNormalKey, "F12");
         keyMapCommand = rsession.GetKeyMapCommands(ReflectionDispatch::rcNormalKey, "F12");
         break;
      case Tab_Key:
         keyMapType = rsession.GetKeyMapCommandType(ReflectionDispatch::rcNormalKey, "Tab");
         keyMapCommand = rsession.GetKeyMapCommands(ReflectionDispatch::rcNormalKey, "Tab");
         break;
      case Return_Key:
         keyMapType = rsession.GetKeyMapCommandType(ReflectionDispatch::rcNormalKey, "Return");
         keyMapCommand = rsession.GetKeyMapCommands(ReflectionDispatch::rcNormalKey, "Return");
         break;
      case BS_Key:
         keyMapType = rsession.GetKeyMapCommandType(ReflectionDispatch::rcNormalKey, "Backspace");
         keyMapCommand = rsession.GetKeyMapCommands(ReflectionDispatch::rcNormalKey, "Backspace");
         break;
      case INSERT_Key:
         keyMapType = rsession.GetKeyMapCommandType(ReflectionDispatch::rcNormalKey, "CpIns");
         keyMapCommand = rsession.GetKeyMapCommands(ReflectionDispatch::rcNormalKey, "CpIns");
         break;
      case DELETE_Key:
         keyMapType = rsession.GetKeyMapCommandType(ReflectionDispatch::rcNormalKey, "CpDel");
         keyMapCommand = rsession.GetKeyMapCommands(ReflectionDispatch::rcNormalKey, "CpDel");
         break;
      case HOME_Key:
         keyMapType = rsession.GetKeyMapCommandType(ReflectionDispatch::rcNormalKey, "CpHome");
         keyMapCommand = rsession.GetKeyMapCommands(ReflectionDispatch::rcNormalKey, "CpHome");
         break;
      case END_Key:
         keyMapType = rsession.GetKeyMapCommandType(ReflectionDispatch::rcNormalKey, "CpEnd");
         keyMapCommand = rsession.GetKeyMapCommands(ReflectionDispatch::rcNormalKey, "CpEnd");
         break;
      case PGUP_Key:
         keyMapType = rsession.GetKeyMapCommandType(ReflectionDispatch::rcNormalKey, "CpPgUp");
         keyMapCommand = rsession.GetKeyMapCommands(ReflectionDispatch::rcNormalKey, "CpPgUp");
         break;
      case PGDN_Key:
         keyMapType = rsession.GetKeyMapCommandType(ReflectionDispatch::rcNormalKey, "CpPgDn");
         keyMapCommand = rsession.GetKeyMapCommands(ReflectionDispatch::rcNormalKey, "CpPgDn");
         break;
      case UP_Key:
         keyMapType = rsession.GetKeyMapCommandType(ReflectionDispatch::rcNormalKey, "CpUp");
         keyMapCommand = rsession.GetKeyMapCommands(ReflectionDispatch::rcNormalKey, "CpUp");
         break;
      case DOWN_Key:
         keyMapType = rsession.GetKeyMapCommandType(ReflectionDispatch::rcNormalKey, "CpDown");
         keyMapCommand = rsession.GetKeyMapCommands(ReflectionDispatch::rcNormalKey, "CpDown");
         break;
      case LEFT_Key:
         keyMapType = rsession.GetKeyMapCommandType(ReflectionDispatch::rcNormalKey, "CpLeft");
         keyMapCommand = rsession.GetKeyMapCommands(ReflectionDispatch::rcNormalKey, "CpLeft");
         break;
      case RIGHT_Key:
         keyMapType = rsession.GetKeyMapCommandType(ReflectionDispatch::rcNormalKey, "CpRight");
         keyMapCommand = rsession.GetKeyMapCommands(ReflectionDispatch::rcNormalKey, "CpRight");
         break;
      default:
         return;
         break;
   }

   switch( keyMapType )
   {
      case ReflectionDispatch::rcTransmitString:
         rsession.Transmit(keyMapCommand, COleVariant(ReflectionDispatch::rcIgnoreBlockMode));
         break;
      case ReflectionDispatch::rcBuiltInFunction:
         rsession.ExecuteBuiltInFunction(keyMapCommand);
         break;
      default:
         return;
   }
}

long 
ReflectionSession::streamTextWait(long timeout, const std::string &text)
{
   std::string strTimeout;
   if( FALSE == rsession.WaitForString(text.c_str(), 
                                       COleVariant(formatTimeoutString(timeout, strTimeout).c_str()), 
                                       COleVariant()) )
      return(tes::EVENT_TIMEOUT);
   return(tes::EVENT_SUCCESS);
}



long 
ReflectionSession::displayTextWait(long timeout, const std::string &text, TEPosition &position)
{
   std::string strTimeout;
   std::string buffer;

   bool found = false;

   if( position.row == tes::POSITION_ANY )
   {
      for( int row=1; row<=24; row++ )
      {
         getDisplayText(TESelection(TEPosition(row, position.column), TEPosition(row, position.column+text.size()-1)), buffer);
         if( 0 == text.compare(buffer) )
         {
            found = true;
            break;
         }
      }
   }
   else if( position.column == tes::POSITION_ANY )
   {
      for( int col=1; col<=(int)(81-text.size()); col++ )
      {
         getDisplayText(TESelection(TEPosition(position.row, col), TEPosition(position.row, col+text.size()-1)), buffer);
         if( 0 == text.compare(buffer) )
         {
            found = true;
            break;
         }
      }
   }
   else
   {
      getDisplayText(TESelection(position, TEPosition(position.row, position.column+text.size()-1)), buffer);
      if( 0 == text.compare(buffer) )
         found = true;
   }

   if( !found )
   {
      if( timeout==0L )
      {
         return(tes::EVENT_TIMEOUT);
      }

      if( FALSE == rsession.WaitForEvent(ReflectionDispatch::rcDisplayString,
                                         COleVariant(formatTimeoutString(timeout, strTimeout).c_str()),
                                         COleVariant(text.c_str()),
                                         COleVariant((short) (position.row == tes::POSITION_ANY?ReflectionDispatch::rcAnyRow:position.row) ),
                                         COleVariant((short) (position.column == tes::POSITION_ANY?ReflectionDispatch::rcAnyCol:position.column)),
                                         COleVariant(),
//                                          COleVariant() ) )
                                         COleVariant(ReflectionDispatch::rcAllowKeystrokes) ) )
      {
         return(tes::EVENT_TIMEOUT);
      }
   }

   return(tes::EVENT_SUCCESS);
}

/*
long 
ReflectionSession::displayTextWait(long timeout, const std::string &text, TEPosition &startPos, TEPosition &endPos)
{
   std::string strTimeout;
  
   int row, column;
   long count = 0;
   bool found = false;

   {
      // We need to do this in a loop in case their is more than one occurance. The first
      // occurance may be before the endPos but outside the desired rectangle. The loop
      // should take care of this.
      TEPosition  pos(startPos);
      while( findDisplayText(text, pos ) )
      {
         if(pos.row >= startPos.row && pos.row <= endPos.row && pos.column >= startPos.column && pos.column <= endPos.column )
            return    tes::EVENT_SUCCESS;

         // Increment pos so we don't get this occurance again
         // TEPosition implements the ++ operator -- I think it works.
         pos++; 
         if ( pos > endPos )
             break;
      }
      if (timeout==0L)
      {
         return tes::EVENT_TIMEOUT;
      }
   }

   // Here we use the system clock to manage the timeout. Remaining time can be calcualted by "timeout - (GetTickCount()-time0)".
   // We loop until the given timeout has expired. And always wait for the proper remaining time.
   long time0=GetTickCount();

   while(GetTickCount()-time0 < timeout)
   {
      if ( TRUE == rsession.WaitForEvent(ReflectionDispatch::rcDisplayString,
                                        COleVariant(formatTimeoutString(timeout-(GetTickCount()-time0), strTimeout).c_str()),
                                        COleVariant(text.c_str()),
                                        COleVariant((short) (ReflectionDispatch::rcAnyRow:row)),
                                        COleVariant((short) (ReflectionDispatch::rcAnyCol:column)),
                                        COleVariant(),
//                                         COleVariant() ) )
                                        COleVariant(ReflectionDispatch::rcAllowKeystrokes)) )
      {
         // The WaitForEvent should set the FoundTextRow and FoundTextColumn properties of rsession
         // on a successful find. We can use these to confirm they are in the rectangle
         pos.row = rsession.GetFoundTextRow()+1;
         pos.column = rsession.GetFoundTextColumn()+1;

         if(pos.row >= startPos.row && pos.row <= endPos.row && pos.column >= startPos.column && pos.column <= endPos.column )
            return tes::EVENT_SUCCESS;

      }

   }
   return tes::EVENT_TIMEOUT;
}

*/











long ReflectionSession::  // yingbao  support rect searching
displayTextWait(long timeout, const std::string &text, TEPosition &startPos, TEPosition &endPos)
{
   std::string strTimeout;
   int row, column;
   long DeltaTime;
   TEPosition  pos(startPos);
   while( findDisplayText(text, pos ) )
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

   column = tes::POSITION_ANY;
   DeltaTime = 1000;  //1 sencond
   long lTime0=GetTickCount();
   long lTime = 0;   //current time - begin time
   while( lTime  < timeout )
   {
      for( row = startPos.row; row<= endPos.row;row++ )
      {
         rsession.WaitForEvent(ReflectionDispatch::rcDisplayString,
                               COleVariant(formatTimeoutString(DeltaTime, strTimeout).c_str()),
                               COleVariant(text.c_str()),
                               COleVariant((short) (row == tes::POSITION_ANY?ReflectionDispatch::rcAnyRow:row) ),
                               COleVariant((short) (column == tes::POSITION_ANY?ReflectionDispatch::rcAnyCol:column)),
                               COleVariant(),
                               //                                          COleVariant() ) )
                               COleVariant(ReflectionDispatch::rcAllowKeystrokes) ); 

         pos.row = startPos.row; pos.column = 1;
         if( findDisplayText(text, pos ) )
         {
            if( pos.row >= startPos.row && pos.row <= endPos.row && pos.column >= startPos.column && pos.column <= endPos.column )
               return(tes::EVENT_SUCCESS);
         }
         lTime = GetTickCount() - lTime0;
      }
   }
   return(tes::EVENT_TIMEOUT);
}




long 
ReflectionSession::cursorWait(long timeout, TEPosition &position)
{
   std::string strTimeout;

   TEPosition cursorPosition;
   getCursorPosition(cursorPosition);

   if( (position.row==tes::POSITION_ANY || position.row==cursorPosition.row) &&
       (position.column==tes::POSITION_ANY || position.column==cursorPosition.column) )
      return(tes::EVENT_SUCCESS);

   if( timeout==0L )
   {
      return(tes::EVENT_TIMEOUT);
   }

   long time0=GetTickCount();

   while( 1 )
   {
      if( FALSE != rsession.WaitForEvent(ReflectionDispatch::rcEnterPos, 
                                         COleVariant("00:00:01.00"), 
                                         COleVariant(), 
                                         COleVariant((short) (position.row == tes::POSITION_ANY?ReflectionDispatch::rcAnyRow:position.row) ),
                                         COleVariant((short) (position.column == tes::POSITION_ANY?ReflectionDispatch::rcAnyCol:position.column)),
                                         COleVariant(), 
//                                          COleVariant() ) )
                                         COleVariant(ReflectionDispatch::rcAllowKeystrokes) ) )
      {
         return(tes::EVENT_SUCCESS);
      }

      getCursorPosition(cursorPosition);
      if( (position.row==tes::POSITION_ANY || position.row==cursorPosition.row) &&
          (position.column==tes::POSITION_ANY || position.column==cursorPosition.column) )
         return(tes::EVENT_SUCCESS);


      if( (tes::TIMEOUT_INFINITE != timeout) &&  ((long)GetTickCount()-time0) >= timeout )
         break;

   }

   return(tes::EVENT_TIMEOUT);
}

long 
ReflectionSession::silenceWait(long timeout, long duration)
{
   std::string strTimeout;
   std::string strDuration;

   if( FALSE == rsession.WaitForEvent(ReflectionDispatch::rcSilence, 
                                      COleVariant(formatTimeoutString(timeout, strTimeout).c_str()), 
                                      COleVariant(formatTimeoutString(duration, strDuration).c_str()), 
                                      COleVariant(),
                                      COleVariant(),
                                      COleVariant(), 
//                                       COleVariant() ) )
                                      COleVariant(ReflectionDispatch::rcAllowKeystrokes) ) )
   {
      return(tes::EVENT_TIMEOUT);
   }

   return(tes::EVENT_SUCCESS);
}

long
ReflectionSession::doneWait(long timeout)
{

   cancel = false;

   long time0=GetTickCount();

   while( 1 )
   {
      if( FALSE != rsession.WaitForEvent(ReflectionDispatch::rcTerminalKeystroke, 
                                         COleVariant("00:00:01.00"), 
                                         COleVariant(), 
                                         COleVariant(), 
                                         COleVariant(), 
                                         COleVariant(ReflectionDispatch::rcVtEscKey), 
                                         COleVariant(ReflectionDispatch::rcAllowKeystrokes)) )
      {
         return(tes::EVENT_SUCCESS);
      }

      if( cancel )
      {
         cancel = false;
         return(tes::EVENT_CANCEL);
      }
      if( (tes::TIMEOUT_INFINITE != timeout) &&  ((long)GetTickCount()-time0) >= timeout )
         break;
   }

   return(tes::EVENT_TIMEOUT);
}

/*
long 
ReflectionSession::setStreamTextWait(const std::string &text)
{
   rsession.DefineEvent(ReflectionDispatch::rcNextEvent, 
                        ReflectionDispatch::rcCommString, 
                        COleVariant(text.c_str()), 
                        COleVariant(), 
                        COleVariant(), 
                        COleVariant());
   return(rsession.GetEventDefined());
}

long 
ReflectionSession::setDisplayTextWait(const std::string &text, TEPosition &position)
{
   rsession.DefineEvent(ReflectionDispatch::rcNextEvent, 
                        ReflectionDispatch::rcDisplayString, 
                        COleVariant(text.c_str()), 
                        COleVariant((short) (position.row == tes::POSITION_ANY?ReflectionDispatch::rcAnyRow:position.row) ),
                        COleVariant((short) (position.column == tes::POSITION_ANY?ReflectionDispatch::rcAnyCol:position.column)),
                        COleVariant());
   return(rsession.GetEventDefined());
}

long 
ReflectionSession::setCursorWait(TEPosition &position)
{
   rsession.DefineEvent(ReflectionDispatch::rcNextEvent, 
                        ReflectionDispatch::rcEnterPos, 
                        COleVariant(), 
                        COleVariant((short) (position.row == tes::POSITION_ANY?ReflectionDispatch::rcAnyRow:position.row) ),
                        COleVariant((short) (position.column == tes::POSITION_ANY?ReflectionDispatch::rcAnyCol:position.column)),
                        COleVariant());
   return(rsession.GetEventDefined());
}

long 
ReflectionSession::setSilenceWait(long duration)
{
   std::string strDuration;

   rsession.DefineEvent(ReflectionDispatch::rcNextEvent, 
                        ReflectionDispatch::rcSilence, 
                        COleVariant(formatTimeoutString(duration, strDuration).c_str()), 
                        COleVariant(),
                        COleVariant(),
                        COleVariant());
   return(rsession.GetEventDefined());
}

long
ReflectionSession::setDoneWait()
{
   rsession.DefineEvent(ReflectionDispatch::rcNextEvent, 
                        ReflectionDispatch::rcTerminalKeystroke, 
                        COleVariant(), 
                        COleVariant(), 
                        COleVariant(), 
                        COleVariant(ReflectionDispatch::rcVtEscKey));
   return(rsession.GetEventDefined());
}

long 
ReflectionSession::wait(long timeout)
{
   std::string strTimeout;
   long event = rsession.WaitEvent(COleVariant(formatTimeoutString(timeout, strTimeout).c_str()), 
//                                    COleVariant());
                                   COleVariant(ReflectionDispatch::rcAllowKeystrokes));

   rsession.ClearEvents();

   if( event==0 )
      return(tes::EVENT_TIMEOUT);
   return(event);
}
*/

TEPosition &
ReflectionSession::getCursorPosition(TEPosition &position)
{
   position.row = rsession.GetCursorRow()+1;
   position.column = rsession.GetCursorColumn()+1;
   return(position);
}

TESelection &
ReflectionSession::getCurrentSelection(TESelection &selection)
{
   selection.startPosition.row = rsession.GetSelectionStartRow()+1;
   selection.startPosition.column = rsession.GetSelectionStartColumn()+1;
   selection.endPosition.row = rsession.GetSelectionEndRow()+1;
   selection.endPosition.column = rsession.GetSelectionEndColumn()+1;
   return(selection);
}

std::string &
ReflectionSession::getDisplayText(const TESelection &selection, std::string &buffer)
{
   CString result = rsession.GetText(selection.startPosition.row-1, 
                                     selection.startPosition.column-1, 
                                     selection.endPosition.row-1, 
                                     selection.endPosition.column-1, 
                                     COleVariant(ReflectionDispatch::rcNoTranslation));

   buffer = result.GetBuffer(0);
   result.ReleaseBuffer();

   return(buffer);
}

bool
ReflectionSession::findDisplayText(const std::string &text, TEPosition &position)
{
   if( TRUE == rsession.FindText(text.c_str(), rsession.GetScreenTopRow()+position.row-1, position.column-1, COleVariant()) )
   {
      position.row = rsession.GetFoundTextRow()+1;
      position.column = rsession.GetFoundTextColumn()+1;
      return(true);
   }
   return(false);
}

void
ReflectionSession::invokeCancel()
{
   cancel = true;
}

std::string &
ReflectionSession::formatTimeoutString(long timeout, std::string &buffer)
{

   if( timeout == 0L )
   {
      buffer = "00:00:00.10";
      return(buffer);
   }

   if( timeout == tes::TIMEOUT_INFINITE )
   {
      buffer = "";
      return(buffer);
   }

   int f = 0;
   int s = 0;
   int m = 0;
   int h = 0;
   char nStr[12];

   timeout /= 10;

   f = timeout % 100;
   timeout /= 100;

   s = timeout % 60;
   timeout /= 60;

   m = timeout % 60;
   timeout /= 60;

   h = timeout;

   wsprintf(nStr, "%02d:%02d:%02d.%02d", h, m, s, f);

   buffer = nStr;
//   buffer = std::string(itoa(h, nStr, 10)) + 
//      std::string(":") + 
//      std::string(itoa(m, nStr, 10)) + 
//      std::string(":") + 
//      std::string(itoa(s, nStr, 10)) + 
//      std::string(":00");

   return(buffer);
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/tesession/reflectionsession/ReflectionSession.cpp-arc  $
 * 
 *    Rev 1.5   Nov 19 2004 09:21:46   PURDYECH
 * PET910 - .NET Conversion
 * 
 *    Rev 1.4   Nov 24 2003 15:58:40   HSUCHIN
 * PTS 10020087 - Enhanced to take host information and connect to reflections based on host passed in.
 */


