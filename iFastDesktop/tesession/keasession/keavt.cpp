// Machine generated IDispatch wrapper class(es) created with ClassWizard


#include "stdafx.h"
#include "keavt.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


namespace KEADispatch
{

/////////////////////////////////////////////////////////////////////////////
// Area properties

short Area::GetPage()
{
   short result;
   GetProperty(0x1, VT_I2, (void*)&result);
   return result;
}

void Area::SetPage(short propVal)
{
   SetProperty(0x1, VT_I2, propVal);
}

short Area::GetTop()
{
   short result;
   GetProperty(0x2, VT_I2, (void*)&result);
   return result;
}

void Area::SetTop(short propVal)
{
   SetProperty(0x2, VT_I2, propVal);
}

short Area::GetLeft()
{
   short result;
   GetProperty(0x3, VT_I2, (void*)&result);
   return result;
}

void Area::SetLeft(short propVal)
{
   SetProperty(0x3, VT_I2, propVal);
}

short Area::GetBottom()
{
   short result;
   GetProperty(0x4, VT_I2, (void*)&result);
   return result;
}

void Area::SetBottom(short propVal)
{
   SetProperty(0x4, VT_I2, propVal);
}

short Area::GetRight()
{
   short result;
   GetProperty(0x5, VT_I2, (void*)&result);
   return result;
}

void Area::SetRight(short propVal)
{
   SetProperty(0x5, VT_I2, propVal);
}

short Area::GetType()
{
   short result;
   GetProperty(0x6, VT_I2, (void*)&result);
   return result;
}

void Area::SetType(short propVal)
{
   SetProperty(0x6, VT_I2, propVal);
}

CString Area::GetValue()
{
   CString result;
   GetProperty(0x7, VT_BSTR, (void*)&result);
   return result;
}

LPDISPATCH Area::GetApplication()
{
   LPDISPATCH result;
   GetProperty(0xc, VT_DISPATCH, (void*)&result);
   return result;
}

LPDISPATCH Area::GetParent()
{
   LPDISPATCH result;
   GetProperty(0xd, VT_DISPATCH, (void*)&result);
   return result;
}

/////////////////////////////////////////////////////////////////////////////
// Area operations

LPDISPATCH Area::WaitUntilChanged(const VARIANT& Idle)
{
   LPDISPATCH result;
   static BYTE parms[] =
      VTS_VARIANT;
   InvokeHelper(0x8, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
      &Idle);
   return result;
}

void Area::Select()
{
   InvokeHelper(0x9, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void Area::Copy()
{
   InvokeHelper(0xa, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void Area::Paste()
{
   InvokeHelper(0xb, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}


/////////////////////////////////////////////////////////////////////////////
// Buttons properties

long Buttons::GetCount()
{
   long result;
   GetProperty(0x1, VT_I4, (void*)&result);
   return result;
}

LPDISPATCH Buttons::GetApplication()
{
   LPDISPATCH result;
   GetProperty(0x7, VT_DISPATCH, (void*)&result);
   return result;
}

LPDISPATCH Buttons::GetParent()
{
   LPDISPATCH result;
   GetProperty(0x8, VT_DISPATCH, (void*)&result);
   return result;
}

/////////////////////////////////////////////////////////////////////////////
// Buttons operations

LPDISPATCH Buttons::Add(short ActionType, LPCTSTR ActionName, LPCTSTR Caption)
{
   LPDISPATCH result;
   static BYTE parms[] =
      VTS_I2 VTS_BSTR VTS_BSTR;
   InvokeHelper(0x2, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
      ActionType, ActionName, Caption);
   return result;
}

LPDISPATCH Buttons::Item(short Index)
{
   LPDISPATCH result;
   static BYTE parms[] =
      VTS_I2;
   InvokeHelper(0x3, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
      Index);
   return result;
}

void Buttons::Remove(short Index)
{
   static BYTE parms[] =
      VTS_I2;
   InvokeHelper(0x4, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
       Index);
}

void Buttons::RemoveAll()
{
   InvokeHelper(0x5, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}


/////////////////////////////////////////////////////////////////////////////
// Connectivity properties

CString Connectivity::GetType()
{
   CString result;
   GetProperty(0x1, VT_BSTR, (void*)&result);
   return result;
}

LPDISPATCH Connectivity::GetOptions()
{
   LPDISPATCH result;
   GetProperty(0x2, VT_DISPATCH, (void*)&result);
   return result;
}

LPDISPATCH Connectivity::GetApplication()
{
   LPDISPATCH result;
   GetProperty(0x3, VT_DISPATCH, (void*)&result);
   return result;
}

LPDISPATCH Connectivity::GetParent()
{
   LPDISPATCH result;
   GetProperty(0x4, VT_DISPATCH, (void*)&result);
   return result;
}

/////////////////////////////////////////////////////////////////////////////
// Connectivity operations


/////////////////////////////////////////////////////////////////////////////
// Field properties

short Field::GetPage()
{
   short result;
   GetProperty(0x1, VT_I2, (void*)&result);
   return result;
}

void Field::SetPage(short propVal)
{
   SetProperty(0x1, VT_I2, propVal);
}

short Field::GetTop()
{
   short result;
   GetProperty(0x2, VT_I2, (void*)&result);
   return result;
}

void Field::SetTop(short propVal)
{
   SetProperty(0x2, VT_I2, propVal);
}

short Field::GetLeft()
{
   short result;
   GetProperty(0x3, VT_I2, (void*)&result);
   return result;
}

void Field::SetLeft(short propVal)
{
   SetProperty(0x3, VT_I2, propVal);
}

short Field::GetBottom()
{
   short result;
   GetProperty(0x4, VT_I2, (void*)&result);
   return result;
}

void Field::SetBottom(short propVal)
{
   SetProperty(0x4, VT_I2, propVal);
}

short Field::GetRight()
{
   short result;
   GetProperty(0x5, VT_I2, (void*)&result);
   return result;
}

void Field::SetRight(short propVal)
{
   SetProperty(0x5, VT_I2, propVal);
}

short Field::GetType()
{
   short result;
   GetProperty(0x6, VT_I2, (void*)&result);
   return result;
}

void Field::SetType(short propVal)
{
   SetProperty(0x6, VT_I2, propVal);
}

CString Field::GetValue()
{
   CString result;
   GetProperty(0x7, VT_BSTR, (void*)&result);
   return result;
}

LPDISPATCH Field::GetApplication()
{
   LPDISPATCH result;
   GetProperty(0xc, VT_DISPATCH, (void*)&result);
   return result;
}

LPDISPATCH Field::GetParent()
{
   LPDISPATCH result;
   GetProperty(0xd, VT_DISPATCH, (void*)&result);
   return result;
}

short Field::GetBold()
{
   short result;
   GetProperty(0x64, VT_I2, (void*)&result);
   return result;
}

short Field::GetBlink()
{
   short result;
   GetProperty(0x65, VT_I2, (void*)&result);
   return result;
}

/////////////////////////////////////////////////////////////////////////////
// Field operations

LPDISPATCH Field::WaitUntilChanged(const VARIANT& Idle)
{
   LPDISPATCH result;
   static BYTE parms[] =
      VTS_VARIANT;
   InvokeHelper(0x8, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
      &Idle);
   return result;
}

void Field::Select()
{
   InvokeHelper(0x9, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void Field::Copy()
{
   InvokeHelper(0xa, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void Field::Paste()
{
   InvokeHelper(0xb, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}


/////////////////////////////////////////////////////////////////////////////
// FileTransferResult properties

CString FileTransferResult::GetName()
{
   CString result;
   GetProperty(0x1, VT_BSTR, (void*)&result);
   return result;
}

CString FileTransferResult::GetRemoteName()
{
   CString result;
   GetProperty(0x2, VT_BSTR, (void*)&result);
   return result;
}

long FileTransferResult::GetSize()
{
   long result;
   GetProperty(0x3, VT_I4, (void*)&result);
   return result;
}

long FileTransferResult::GetTime()
{
   long result;
   GetProperty(0x4, VT_I4, (void*)&result);
   return result;
}

short FileTransferResult::GetErrors()
{
   short result;
   GetProperty(0x5, VT_I2, (void*)&result);
   return result;
}

short FileTransferResult::GetTimeouts()
{
   short result;
   GetProperty(0x6, VT_I2, (void*)&result);
   return result;
}

short FileTransferResult::GetEndState()
{
   short result;
   GetProperty(0x7, VT_I2, (void*)&result);
   return result;
}

/////////////////////////////////////////////////////////////////////////////
// FileTransferResult operations


/////////////////////////////////////////////////////////////////////////////
// Screen properties

short Screen::GetPage()
{
   short result;
   GetProperty(0x1, VT_I2, (void*)&result);
   return result;
}

short Screen::GetRow()
{
   short result;
   GetProperty(0x2, VT_I2, (void*)&result);
   return result;
}

short Screen::GetCol()
{
   short result;
   GetProperty(0x3, VT_I2, (void*)&result);
   return result;
}

short Screen::GetPages()
{
   short result;
   GetProperty(0x4, VT_I2, (void*)&result);
   return result;
}

short Screen::GetRows()
{
   short result;
   GetProperty(0x5, VT_I2, (void*)&result);
   return result;
}

short Screen::GetCols()
{
   short result;
   GetProperty(0x6, VT_I2, (void*)&result);
   return result;
}

CString Screen::GetHostName()
{
   CString result;
   GetProperty(0x7, VT_BSTR, (void*)&result);
   return result;
}

BOOL Screen::GetLocal()
{
   BOOL result;
   GetProperty(0xd, VT_BOOL, (void*)&result);
   return result;
}

void Screen::SetLocal(BOOL propVal)
{
   SetProperty(0xd, VT_BOOL, propVal);
}

BOOL Screen::GetSynchronous()
{
   BOOL result;
   GetProperty(0x16, VT_BOOL, (void*)&result);
   return result;
}

void Screen::SetSynchronous(BOOL propVal)
{
   SetProperty(0x16, VT_BOOL, propVal);
}

LPDISPATCH Screen::GetHostOptions()
{
   LPDISPATCH result;
   GetProperty(0x17, VT_DISPATCH, (void*)&result);
   return result;
}

LPDISPATCH Screen::GetSelection()
{
   LPDISPATCH result;
   GetProperty(0x1a, VT_DISPATCH, (void*)&result);
   return result;
}

LPDISPATCH Screen::GetApplication()
{
   LPDISPATCH result;
   GetProperty(0x1c, VT_DISPATCH, (void*)&result);
   return result;
}

LPDISPATCH Screen::GetParent()
{
   LPDISPATCH result;
   GetProperty(0x1d, VT_DISPATCH, (void*)&result);
   return result;
}

/////////////////////////////////////////////////////////////////////////////
// Screen operations

void Screen::PutString(LPCTSTR Text)
{
   static BYTE parms[] =
      VTS_BSTR;
   InvokeHelper(0x8, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
       Text);
}

void Screen::SendKeys(LPCTSTR Text)
{
   static BYTE parms[] =
      VTS_BSTR;
   InvokeHelper(0x9, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
       Text);
}

LPDISPATCH Screen::Area(short Row, short Col, short EndRow, short EndCol, const VARIANT& Page, const VARIANT& Type)
{
   LPDISPATCH result;
   static BYTE parms[] =
      VTS_I2 VTS_I2 VTS_I2 VTS_I2 VTS_VARIANT VTS_VARIANT;
   InvokeHelper(0xa, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
      Row, Col, EndRow, EndCol, &Page, &Type);
   return result;
}

CString Screen::GetString(short Row, short Col, short Len, const VARIANT& Page)
{
   CString result;
   static BYTE parms[] =
      VTS_I2 VTS_I2 VTS_I2 VTS_VARIANT;
   InvokeHelper(0xb, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms,
      Row, Col, Len, &Page);
   return result;
}

void Screen::Clear()
{
   InvokeHelper(0xc, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void Screen::SendInput(LPCTSTR Text)
{
   static BYTE parms[] =
      VTS_BSTR;
   InvokeHelper(0xe, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
       Text);
}

LPDISPATCH Screen::WaitHostQuiet(long Time)
{
   LPDISPATCH result;
   static BYTE parms[] =
      VTS_I4;
   InvokeHelper(0xf, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
      Time);
   return result;
}

LPDISPATCH Screen::WaitForStream(LPCTSTR Text, const VARIANT& Idle, const VARIANT& Timeout, const VARIANT& Options)
{
   LPDISPATCH result;
   static BYTE parms[] =
      VTS_BSTR VTS_VARIANT VTS_VARIANT VTS_VARIANT;
   InvokeHelper(0x10, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
      Text, &Idle, &Timeout, &Options);
   return result;
}

LPDISPATCH Screen::WaitForString(LPCTSTR Text, const VARIANT& Row, const VARIANT& Col, const VARIANT& Page, const VARIANT& Idle, const VARIANT& Timeout, const VARIANT& Options)
{
   LPDISPATCH result;
   static BYTE parms[] =
      VTS_BSTR VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT;
   InvokeHelper(0x11, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
      Text, &Row, &Col, &Page, &Idle, &Timeout, &Options);
   return result;
}

LPDISPATCH Screen::Search(LPCTSTR Text, const VARIANT& Row, const VARIANT& Col, const VARIANT& Page, const VARIANT& Occurrence)
{
   LPDISPATCH result;
   static BYTE parms[] =
      VTS_BSTR VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT;
   InvokeHelper(0x12, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
      Text, &Row, &Col, &Page, &Occurrence);
   return result;
}

LPDISPATCH Screen::WaitForCursor(const VARIANT& Row, const VARIANT& Col, const VARIANT& Page)
{
   LPDISPATCH result;
   static BYTE parms[] =
      VTS_VARIANT VTS_VARIANT VTS_VARIANT;
   InvokeHelper(0x13, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
      &Row, &Col, &Page);
   return result;
}

LPDISPATCH Screen::WaitForCursorMove()
{
   LPDISPATCH result;
   InvokeHelper(0x14, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
   return result;
}

LPDISPATCH Screen::WaitForKeys(const VARIANT& Process)
{
   LPDISPATCH result;
   static BYTE parms[] =
      VTS_VARIANT;
   InvokeHelper(0x15, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
      &Process);
   return result;
}

void Screen::Copy()
{
   InvokeHelper(0x18, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void Screen::Paste()
{
   InvokeHelper(0x19, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

LPDISPATCH Screen::SelectAll()
{
   LPDISPATCH result;
   InvokeHelper(0x1b, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
   return result;
}

LPDISPATCH Screen::Select(short StartRow, short StartCol, short EndRow, short EndCol, const VARIANT& Page)
{
   LPDISPATCH result;
   static BYTE parms[] =
      VTS_I2 VTS_I2 VTS_I2 VTS_I2 VTS_VARIANT;
   InvokeHelper(0x1e, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
      StartRow, StartCol, EndRow, EndCol, &Page);
   return result;
}

VARIANT Screen::CopyPS(short Row, short Col, short Len, const VARIANT& Page, const VARIANT& Type)
{
   VARIANT result;
   static BYTE parms[] =
      VTS_I2 VTS_I2 VTS_I2 VTS_VARIANT VTS_VARIANT;
   InvokeHelper(0x1f, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
      Row, Col, Len, &Page, &Type);
   return result;
}

void Screen::GetInfo(short* Row, short* Col, short* Page, short* DisplayTop, short* DisplayLeft, short* DisplayBottom, short* DisplayRight, short* Rows, short* Cols, short* Pages)
{
   static BYTE parms[] =
      VTS_PI2 VTS_PI2 VTS_PI2 VTS_PI2 VTS_PI2 VTS_PI2 VTS_PI2 VTS_PI2 VTS_PI2 VTS_PI2;
   InvokeHelper(0x20, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
       Row, Col, Page, DisplayTop, DisplayLeft, DisplayBottom, DisplayRight, Rows, Cols, Pages);
}

void Screen::CancelSelection()
{
   InvokeHelper(0x21, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

LPDISPATCH Screen::GetDisplayArea()
{
   LPDISPATCH result;
   InvokeHelper(0x22, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
   return result;
}

LPDISPATCH Screen::GetField(short Attribute, short Row, short Col, const VARIANT& Page)
{
   LPDISPATCH result;
   static BYTE parms[] =
      VTS_I2 VTS_I2 VTS_I2 VTS_VARIANT;
   InvokeHelper(0x23, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
      Attribute, Row, Col, &Page);
   return result;
}

LPDISPATCH Screen::GetFields(short Attribute)
{
   LPDISPATCH result;
   static BYTE parms[] =
      VTS_I2;
   InvokeHelper(0x24, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
      Attribute);
   return result;
}


/////////////////////////////////////////////////////////////////////////////
// KeyWait properties

LPDISPATCH KeyWait::GetApplication()
{
   LPDISPATCH result;
   GetProperty(0x6, VT_DISPATCH, (void*)&result);
   return result;
}

LPDISPATCH KeyWait::GetParent()
{
   LPDISPATCH result;
   GetProperty(0x7, VT_DISPATCH, (void*)&result);
   return result;
}

BOOL KeyWait::GetChanged()
{
   BOOL result;
   GetProperty(0xa, VT_BOOL, (void*)&result);
   return result;
}

BOOL KeyWait::GetEnabled()
{
   BOOL result;
   GetProperty(0xe, VT_BOOL, (void*)&result);
   return result;
}

void KeyWait::SetEnabled(BOOL propVal)
{
   SetProperty(0xe, VT_BOOL, propVal);
}

CString KeyWait::GetName()
{
   CString result;
   GetProperty(0x64, VT_BSTR, (void*)&result);
   return result;
}

/////////////////////////////////////////////////////////////////////////////
// KeyWait operations

BOOL KeyWait::Wait(const VARIANT& Timeout)
{
   BOOL result;
   static BYTE parms[] =
      VTS_VARIANT;
   InvokeHelper(0x1, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
      &Timeout);
   return result;
}

void KeyWait::Clear()
{
   InvokeHelper(0x2, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

short KeyWait::_StartWait(LPDISPATCH pServer, long DispidNewEvent)
{
   short result;
   static BYTE parms[] =
      VTS_DISPATCH VTS_I4;
   InvokeHelper(0x3, DISPATCH_METHOD, VT_I2, (void*)&result, parms,
      pServer, DispidNewEvent);
   return result;
}

void KeyWait::_StopWait()
{
   InvokeHelper(0x4, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

long KeyWait::_GetBase(long SessionID)
{
   long result;
   static BYTE parms[] =
      VTS_I4;
   InvokeHelper(0x5, DISPATCH_METHOD, VT_I4, (void*)&result, parms,
      SessionID);
   return result;
}

void KeyWait::StartNotify(long hWnd, long wMsg, long wParam, long lParam, long wMsgFail, long wParamFail, long lParamFail)
{
   static BYTE parms[] =
      VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4;
   InvokeHelper(0x8, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
       hWnd, wMsg, wParam, lParam, wMsgFail, wParamFail, lParamFail);
}

void KeyWait::StopNotify()
{
   InvokeHelper(0x9, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void KeyWait::StartCallback(LPDISPATCH pDispatch)
{
   static BYTE parms[] =
      VTS_DISPATCH;
   InvokeHelper(0xb, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
       pDispatch);
}

void KeyWait::StopCallback()
{
   InvokeHelper(0xc, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void KeyWait::Reset()
{
   InvokeHelper(0xd, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}


/////////////////////////////////////////////////////////////////////////////
// MatchWait properties

LPDISPATCH MatchWait::GetApplication()
{
   LPDISPATCH result;
   GetProperty(0x6, VT_DISPATCH, (void*)&result);
   return result;
}

LPDISPATCH MatchWait::GetParent()
{
   LPDISPATCH result;
   GetProperty(0x7, VT_DISPATCH, (void*)&result);
   return result;
}

BOOL MatchWait::GetChanged()
{
   BOOL result;
   GetProperty(0xa, VT_BOOL, (void*)&result);
   return result;
}

BOOL MatchWait::GetEnabled()
{
   BOOL result;
   GetProperty(0xe, VT_BOOL, (void*)&result);
   return result;
}

void MatchWait::SetEnabled(BOOL propVal)
{
   SetProperty(0xe, VT_BOOL, propVal);
}

CString MatchWait::GetString()
{
   CString result;
   GetProperty(0x64, VT_BSTR, (void*)&result);
   return result;
}

short MatchWait::GetRow()
{
   short result;
   GetProperty(0x65, VT_I2, (void*)&result);
   return result;
}

short MatchWait::GetCol()
{
   short result;
   GetProperty(0x66, VT_I2, (void*)&result);
   return result;
}

short MatchWait::GetPage()
{
   short result;
   GetProperty(0x67, VT_I2, (void*)&result);
   return result;
}

/////////////////////////////////////////////////////////////////////////////
// MatchWait operations

BOOL MatchWait::Wait(const VARIANT& Timeout)
{
   BOOL result;
   static BYTE parms[] =
      VTS_VARIANT;
   InvokeHelper(0x1, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
      &Timeout);
   return result;
}

void MatchWait::Clear()
{
   InvokeHelper(0x2, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

short MatchWait::_StartWait(LPDISPATCH pServer, long DispidNewEvent)
{
   short result;
   static BYTE parms[] =
      VTS_DISPATCH VTS_I4;
   InvokeHelper(0x3, DISPATCH_METHOD, VT_I2, (void*)&result, parms,
      pServer, DispidNewEvent);
   return result;
}

void MatchWait::_StopWait()
{
   InvokeHelper(0x4, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

long MatchWait::_GetBase(long SessionID)
{
   long result;
   static BYTE parms[] =
      VTS_I4;
   InvokeHelper(0x5, DISPATCH_METHOD, VT_I4, (void*)&result, parms,
      SessionID);
   return result;
}

void MatchWait::StartNotify(long hWnd, long wMsg, long wParam, long lParam, long wMsgFail, long wParamFail, long lParamFail)
{
   static BYTE parms[] =
      VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4;
   InvokeHelper(0x8, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
       hWnd, wMsg, wParam, lParam, wMsgFail, wParamFail, lParamFail);
}

void MatchWait::StopNotify()
{
   InvokeHelper(0x9, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void MatchWait::StartCallback(LPDISPATCH pDispatch)
{
   static BYTE parms[] =
      VTS_DISPATCH;
   InvokeHelper(0xb, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
       pDispatch);
}

void MatchWait::StopCallback()
{
   InvokeHelper(0xc, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void MatchWait::Reset()
{
   InvokeHelper(0xd, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}


/////////////////////////////////////////////////////////////////////////////
// DisconnectWait properties

LPDISPATCH DisconnectWait::GetApplication()
{
   LPDISPATCH result;
   GetProperty(0x6, VT_DISPATCH, (void*)&result);
   return result;
}

LPDISPATCH DisconnectWait::GetParent()
{
   LPDISPATCH result;
   GetProperty(0x7, VT_DISPATCH, (void*)&result);
   return result;
}

BOOL DisconnectWait::GetChanged()
{
   BOOL result;
   GetProperty(0xa, VT_BOOL, (void*)&result);
   return result;
}

BOOL DisconnectWait::GetEnabled()
{
   BOOL result;
   GetProperty(0xe, VT_BOOL, (void*)&result);
   return result;
}

void DisconnectWait::SetEnabled(BOOL propVal)
{
   SetProperty(0xe, VT_BOOL, propVal);
}

BOOL DisconnectWait::GetConnected()
{
   BOOL result;
   GetProperty(0x64, VT_BOOL, (void*)&result);
   return result;
}

/////////////////////////////////////////////////////////////////////////////
// DisconnectWait operations

BOOL DisconnectWait::Wait(const VARIANT& Timeout)
{
   BOOL result;
   static BYTE parms[] =
      VTS_VARIANT;
   InvokeHelper(0x1, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
      &Timeout);
   return result;
}

void DisconnectWait::Clear()
{
   InvokeHelper(0x2, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

short DisconnectWait::_StartWait(LPDISPATCH pServer, long DispidNewEvent)
{
   short result;
   static BYTE parms[] =
      VTS_DISPATCH VTS_I4;
   InvokeHelper(0x3, DISPATCH_METHOD, VT_I2, (void*)&result, parms,
      pServer, DispidNewEvent);
   return result;
}

void DisconnectWait::_StopWait()
{
   InvokeHelper(0x4, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

long DisconnectWait::_GetBase(long SessionID)
{
   long result;
   static BYTE parms[] =
      VTS_I4;
   InvokeHelper(0x5, DISPATCH_METHOD, VT_I4, (void*)&result, parms,
      SessionID);
   return result;
}

void DisconnectWait::StartNotify(long hWnd, long wMsg, long wParam, long lParam, long wMsgFail, long wParamFail, long lParamFail)
{
   static BYTE parms[] =
      VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4;
   InvokeHelper(0x8, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
       hWnd, wMsg, wParam, lParam, wMsgFail, wParamFail, lParamFail);
}

void DisconnectWait::StopNotify()
{
   InvokeHelper(0x9, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void DisconnectWait::StartCallback(LPDISPATCH pDispatch)
{
   static BYTE parms[] =
      VTS_DISPATCH;
   InvokeHelper(0xb, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
       pDispatch);
}

void DisconnectWait::StopCallback()
{
   InvokeHelper(0xc, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void DisconnectWait::Reset()
{
   InvokeHelper(0xd, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}


/////////////////////////////////////////////////////////////////////////////
// Session properties

LPDISPATCH Session::GetScreen()
{
   LPDISPATCH result;
   GetProperty(0x1, VT_DISPATCH, (void*)&result);
   return result;
}

LPDISPATCH Session::GetButtons()
{
   LPDISPATCH result;
   GetProperty(0x2, VT_DISPATCH, (void*)&result);
   return result;
}

CString Session::GetFullName()
{
   CString result;
   GetProperty(0x3, VT_BSTR, (void*)&result);
   return result;
}

CString Session::GetName()
{
   CString result;
   GetProperty(0x4, VT_BSTR, (void*)&result);
   return result;
}

CString Session::GetTitle()
{
   CString result;
   GetProperty(0x5, VT_BSTR, (void*)&result);
   return result;
}

CString Session::GetPath()
{
   CString result;
   GetProperty(0x6, VT_BSTR, (void*)&result);
   return result;
}

BOOL Session::GetVisible()
{
   BOOL result;
   GetProperty(0x7, VT_BOOL, (void*)&result);
   return result;
}

void Session::SetVisible(BOOL propVal)
{
   SetProperty(0x7, VT_BOOL, propVal);
}

BOOL Session::GetHistory()
{
   BOOL result;
   GetProperty(0x8, VT_BOOL, (void*)&result);
   return result;
}

void Session::SetHistory(BOOL propVal)
{
   SetProperty(0x8, VT_BOOL, propVal);
}

BOOL Session::GetCapture()
{
   BOOL result;
   GetProperty(0x9, VT_BOOL, (void*)&result);
   return result;
}

void Session::SetCapture(BOOL propVal)
{
   SetProperty(0x9, VT_BOOL, propVal);
}

LPDISPATCH Session::GetFont()
{
   LPDISPATCH result;
   GetProperty(0xa, VT_DISPATCH, (void*)&result);
   return result;
}

BOOL Session::GetMenu()
{
   BOOL result;
   GetProperty(0xb, VT_BOOL, (void*)&result);
   return result;
}

void Session::SetMenu(BOOL propVal)
{
   SetProperty(0xb, VT_BOOL, propVal);
}

BOOL Session::GetSaved()
{
   BOOL result;
   GetProperty(0x10, VT_BOOL, (void*)&result);
   return result;
}

CString Session::GetCaption()
{
   CString result;
   GetProperty(0x14, VT_BSTR, (void*)&result);
   return result;
}

void Session::SetCaption(LPCTSTR propVal)
{
   SetProperty(0x14, VT_BSTR, propVal);
}

CString Session::GetStatusBar()
{
   CString result;
   GetProperty(0x15, VT_BSTR, (void*)&result);
   return result;
}

short Session::GetType()
{
   short result;
   GetProperty(0x16, VT_I2, (void*)&result);
   return result;
}

short Session::GetWindowState()
{
   short result;
   GetProperty(0x17, VT_I2, (void*)&result);
   return result;
}

void Session::SetWindowState(short propVal)
{
   SetProperty(0x17, VT_I2, propVal);
}

LPDISPATCH Session::GetCursor()
{
   LPDISPATCH result;
   GetProperty(0x18, VT_DISPATCH, (void*)&result);
   return result;
}

LPDISPATCH Session::GetFileTransferScheme()
{
   LPDISPATCH result;
   GetProperty(0x19, VT_DISPATCH, (void*)&result);
   return result;
}

LPDISPATCH Session::GetConnectivity()
{
   LPDISPATCH result;
   GetProperty(0x1a, VT_DISPATCH, (void*)&result);
   return result;
}

LPDISPATCH Session::GetApplication()
{
   LPDISPATCH result;
   GetProperty(0x1b, VT_DISPATCH, (void*)&result);
   return result;
}

LPDISPATCH Session::GetParent()
{
   LPDISPATCH result;
   GetProperty(0x1c, VT_DISPATCH, (void*)&result);
   return result;
}

BOOL Session::GetConnected()
{
   BOOL result;
   GetProperty(0x1d, VT_BOOL, (void*)&result);
   return result;
}

void Session::SetConnected(BOOL propVal)
{
   SetProperty(0x1d, VT_BOOL, propVal);
}

short Session::GetLeft()
{
   short result;
   GetProperty(0x24, VT_I2, (void*)&result);
   return result;
}

void Session::SetLeft(short propVal)
{
   SetProperty(0x24, VT_I2, propVal);
}

short Session::GetTop()
{
   short result;
   GetProperty(0x25, VT_I2, (void*)&result);
   return result;
}

void Session::SetTop(short propVal)
{
   SetProperty(0x25, VT_I2, propVal);
}

short Session::GetWidth()
{
   short result;
   GetProperty(0x26, VT_I2, (void*)&result);
   return result;
}

void Session::SetWidth(short propVal)
{
   SetProperty(0x26, VT_I2, propVal);
}

short Session::GetHeight()
{
   short result;
   GetProperty(0x27, VT_I2, (void*)&result);
   return result;
}

void Session::SetHeight(short propVal)
{
   SetProperty(0x27, VT_I2, propVal);
}

long Session::GetHWnd()
{
   long result;
   GetProperty(0x28, VT_I4, (void*)&result);
   return result;
}

/////////////////////////////////////////////////////////////////////////////
// Session operations

void Session::Activate()
{
   InvokeHelper(0xc, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void Session::Close()
{
   InvokeHelper(0xd, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void Session::Save()
{
   InvokeHelper(0xe, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void Session::SaveAs(LPCTSTR Name)
{
   static BYTE parms[] =
      VTS_BSTR;
   InvokeHelper(0xf, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
       Name);
}

void Session::PrintDisplay(short Extent, BOOL Graphics)
{
   static BYTE parms[] =
      VTS_I2 VTS_BOOL;
   InvokeHelper(0x11, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
       Extent, Graphics);
}

void Session::ClearHistory()
{
   InvokeHelper(0x12, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void Session::Restart()
{
   InvokeHelper(0x13, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

LPDISPATCH Session::ReceiveFile(const VARIANT& Files, const VARIANT& Path)
{
   LPDISPATCH result;
   static BYTE parms[] =
      VTS_VARIANT VTS_VARIANT;
   InvokeHelper(0x1e, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
      &Files, &Path);
   return result;
}

LPDISPATCH Session::SendFile(const VARIANT& Files, const VARIANT& HostName)
{
   LPDISPATCH result;
   static BYTE parms[] =
      VTS_VARIANT VTS_VARIANT;
   InvokeHelper(0x1f, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
      &Files, &HostName);
   return result;
}

void Session::ClearComm()
{
   InvokeHelper(0x20, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void Session::Connect(const VARIANT& Name)
{
   static BYTE parms[] =
      VTS_VARIANT;
   InvokeHelper(0x21, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
       &Name);
}

void Session::Disconnect()
{
   InvokeHelper(0x22, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

LPDISPATCH Session::WaitForDisconnect()
{
   LPDISPATCH result;
   InvokeHelper(0x23, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
   return result;
}

LPDISPATCH Session::RunMacro(LPCTSTR File)
{
   LPDISPATCH result;
   static BYTE parms[] =
      VTS_BSTR;
   InvokeHelper(0x29, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
      File);
   return result;
}

LPDISPATCH Session::Execute(LPCTSTR Command)
{
   LPDISPATCH result;
   static BYTE parms[] =
      VTS_BSTR;
   InvokeHelper(0x2a, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
      Command);
   return result;
}

CString Session::GetDirectory(short FileTypeRequested)
{
   CString result;
   static BYTE parms[] =
      VTS_I2;
   InvokeHelper(0x2b, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms,
      FileTypeRequested);
   return result;
}


/////////////////////////////////////////////////////////////////////////////
// Sessions properties

long Sessions::GetCount()
{
   long result;
   GetProperty(0x1, VT_I4, (void*)&result);
   return result;
}

LPDISPATCH Sessions::GetApplication()
{
   LPDISPATCH result;
   GetProperty(0x6, VT_DISPATCH, (void*)&result);
   return result;
}

LPDISPATCH Sessions::GetParent()
{
   LPDISPATCH result;
   GetProperty(0x7, VT_DISPATCH, (void*)&result);
   return result;
}

/////////////////////////////////////////////////////////////////////////////
// Sessions operations

LPDISPATCH Sessions::Item(short Index)
{
   LPDISPATCH result;
   static BYTE parms[] =
      VTS_I2;
   InvokeHelper(0x2, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
      Index);
   return result;
}

void Sessions::CloseAll()
{
   InvokeHelper(0x4, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void Sessions::RestartAll()
{
   InvokeHelper(0x5, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}


/////////////////////////////////////////////////////////////////////////////
// System properties

LPDISPATCH System::GetWaits()
{
   LPDISPATCH result;
   GetProperty(0x4, VT_DISPATCH, (void*)&result);
   return result;
}

CString System::GetName()
{
   CString result;
   GetProperty(0x6, VT_BSTR, (void*)&result);
   return result;
}

CString System::GetVersion()
{
   CString result;
   GetProperty(0x7, VT_BSTR, (void*)&result);
   return result;
}

LPDISPATCH System::GetApplication()
{
   LPDISPATCH result;
   GetProperty(0x8, VT_DISPATCH, (void*)&result);
   return result;
}

LPDISPATCH System::GetParent()
{
   LPDISPATCH result;
   GetProperty(0x9, VT_DISPATCH, (void*)&result);
   return result;
}

LPDISPATCH System::GetSessions()
{
   LPDISPATCH result;
   GetProperty(0xa, VT_DISPATCH, (void*)&result);
   return result;
}

LPDISPATCH System::GetActiveSession()
{
   LPDISPATCH result;
   GetProperty(0xc, VT_DISPATCH, (void*)&result);
   return result;
}

CString System::GetFullName()
{
   CString result;
   GetProperty(0xd, VT_BSTR, (void*)&result);
   return result;
}

/////////////////////////////////////////////////////////////////////////////
// System operations

long System::_RegisterClient(LPDISPATCH pApplication)
{
   long result;
   static BYTE parms[] =
      VTS_DISPATCH;
   InvokeHelper(0x1, DISPATCH_METHOD, VT_I4, (void*)&result, parms,
      pApplication);
   return result;
}

void System::_DeregisterClient(long SessionID)
{
   static BYTE parms[] =
      VTS_I4;
   InvokeHelper(0x2, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
       SessionID);
}

void System::_ServerWait(long SessionID, LPDISPATCH ClientWait, LPCTSTR IID_Client, long DispidStartWait, long DispidStopWait, long DefaultTimeout)
{
   static BYTE parms[] =
      VTS_I4 VTS_DISPATCH VTS_BSTR VTS_I4 VTS_I4 VTS_I4;
   InvokeHelper(0x3, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
       SessionID, ClientWait, IID_Client, DispidStartWait, DispidStopWait, DefaultTimeout);
}

void System::Quit()
{
   InvokeHelper(0x5, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void System::_ActiveClient(long SessionID)
{
   static BYTE parms[] =
      VTS_I4;
   InvokeHelper(0xb, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
       SessionID);
}

CString System::GetDirectory(short ProductTypeWanted, short DirectoryTypeWanted)
{
   CString result;
   static BYTE parms[] =
      VTS_I2 VTS_I2;
   InvokeHelper(0xe, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms,
      ProductTypeWanted, DirectoryTypeWanted);
   return result;
}


/////////////////////////////////////////////////////////////////////////////
// Wait properties

LPDISPATCH Wait::GetApplication()
{
   LPDISPATCH result;
   GetProperty(0x6, VT_DISPATCH, (void*)&result);
   return result;
}

LPDISPATCH Wait::GetParent()
{
   LPDISPATCH result;
   GetProperty(0x7, VT_DISPATCH, (void*)&result);
   return result;
}

BOOL Wait::GetChanged()
{
   BOOL result;
   GetProperty(0xa, VT_BOOL, (void*)&result);
   return result;
}

BOOL Wait::GetEnabled()
{
   BOOL result;
   GetProperty(0xe, VT_BOOL, (void*)&result);
   return result;
}

void Wait::SetEnabled(BOOL propVal)
{
   SetProperty(0xe, VT_BOOL, propVal);
}

/////////////////////////////////////////////////////////////////////////////
// Wait operations

BOOL Wait::Wait_(const VARIANT& Timeout)
{
   BOOL result;
   static BYTE parms[] =
      VTS_VARIANT;
   InvokeHelper(0x1, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
      &Timeout);
   return result;
}

void Wait::Clear()
{
   InvokeHelper(0x2, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

short Wait::_StartWait(LPDISPATCH pServer, long DispidNewEvent)
{
   short result;
   static BYTE parms[] =
      VTS_DISPATCH VTS_I4;
   InvokeHelper(0x3, DISPATCH_METHOD, VT_I2, (void*)&result, parms,
      pServer, DispidNewEvent);
   return result;
}

void Wait::_StopWait()
{
   InvokeHelper(0x4, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

long Wait::_GetBase(long SessionID)
{
   long result;
   static BYTE parms[] =
      VTS_I4;
   InvokeHelper(0x5, DISPATCH_METHOD, VT_I4, (void*)&result, parms,
      SessionID);
   return result;
}

void Wait::StartNotify(long hWnd, long wMsg, long wParam, long lParam, long wMsgFail, long wParamFail, long lParamFail)
{
   static BYTE parms[] =
      VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4;
   InvokeHelper(0x8, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
       hWnd, wMsg, wParam, lParam, wMsgFail, wParamFail, lParamFail);
}

void Wait::StopNotify()
{
   InvokeHelper(0x9, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void Wait::StartCallback(LPDISPATCH pDispatch)
{
   static BYTE parms[] =
      VTS_DISPATCH;
   InvokeHelper(0xb, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
       pDispatch);
}

void Wait::StopCallback()
{
   InvokeHelper(0xc, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void Wait::Reset()
{
   InvokeHelper(0xd, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}


/////////////////////////////////////////////////////////////////////////////
// Waits properties

short Waits::GetCount()
{
   short result;
   GetProperty(0x1, VT_I2, (void*)&result);
   return result;
}

long Waits::GetChanged()
{
   long result;
   GetProperty(0x8, VT_I4, (void*)&result);
   return result;
}

BOOL Waits::GetEnabled()
{
   BOOL result;
   GetProperty(0xf, VT_BOOL, (void*)&result);
   return result;
}

void Waits::SetEnabled(BOOL propVal)
{
   SetProperty(0xf, VT_BOOL, propVal);
}

/////////////////////////////////////////////////////////////////////////////
// Waits operations

long Waits::Add(LPDISPATCH Wait)
{
   long result;
   static BYTE parms[] =
      VTS_DISPATCH;
   InvokeHelper(0x2, DISPATCH_METHOD, VT_I4, (void*)&result, parms,
      Wait);
   return result;
}

LPDISPATCH Waits::Item(long ID)
{
   LPDISPATCH result;
   static BYTE parms[] =
      VTS_I4;
   InvokeHelper(0x3, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
      ID);
   return result;
}

void Waits::Remove(long ID)
{
   static BYTE parms[] =
      VTS_I4;
   InvokeHelper(0x5, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
       ID);
}

void Waits::RemoveAll()
{
   InvokeHelper(0x6, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

long Waits::Wait(const VARIANT& Timeout)
{
   long result;
   static BYTE parms[] =
      VTS_VARIANT;
   InvokeHelper(0x7, DISPATCH_METHOD, VT_I4, (void*)&result, parms,
      &Timeout);
   return result;
}

void Waits::Clear()
{
   InvokeHelper(0x9, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void Waits::Reset()
{
   InvokeHelper(0xa, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void Waits::StartNotify(long hWnd, long wMsg, long wParam, long lParam, long wMsgFail, long wParamFail, long lParamFail)
{
   static BYTE parms[] =
      VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4;
   InvokeHelper(0xb, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
       hWnd, wMsg, wParam, lParam, wMsgFail, wParamFail, lParamFail);
}

void Waits::StopNotify()
{
   InvokeHelper(0xc, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void Waits::StartCallback(LPDISPATCH pDispatch)
{
   static BYTE parms[] =
      VTS_DISPATCH;
   InvokeHelper(0xd, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
       pDispatch);
}

void Waits::StopCallback()
{
   InvokeHelper(0xe, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

short Waits::_StartWait(LPDISPATCH pServer, long DispidNewEvent)
{
   short result;
   static BYTE parms[] =
      VTS_DISPATCH VTS_I4;
   InvokeHelper(0x10, DISPATCH_METHOD, VT_I2, (void*)&result, parms,
      pServer, DispidNewEvent);
   return result;
}

void Waits::_StopWait()
{
   InvokeHelper(0x11, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

long Waits::_GetBase(long SessionID)
{
   long result;
   static BYTE parms[] =
      VTS_I4;
   InvokeHelper(0x12, DISPATCH_METHOD, VT_I4, (void*)&result, parms,
      SessionID);
   return result;
}

short Waits::_Add(LPDISPATCH pWait)
{
   short result;
   static BYTE parms[] =
      VTS_DISPATCH;
   InvokeHelper(0x13, DISPATCH_METHOD, VT_I2, (void*)&result, parms,
      pWait);
   return result;
}

short Waits::_Remove(LPDISPATCH pWait)
{
   short result;
   static BYTE parms[] =
      VTS_DISPATCH;
   InvokeHelper(0x14, DISPATCH_METHOD, VT_I2, (void*)&result, parms,
      pWait);
   return result;
}

void Waits::_ClearAll()
{
   InvokeHelper(0x15, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void Waits::_ResetAll()
{
   InvokeHelper(0x16, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void Waits::_StartNotify(long hWnd, long wMsg, long wParam, long lParam, long wMsgFail, long wParamFail, long lParamFail)
{
   static BYTE parms[] =
      VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4;
   InvokeHelper(0x17, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
       hWnd, wMsg, wParam, lParam, wMsgFail, wParamFail, lParamFail);
}

void Waits::_StopNotify()
{
   InvokeHelper(0x18, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void Waits::_StartCallback(LPDISPATCH pDispatch)
{
   static BYTE parms[] =
      VTS_DISPATCH;
   InvokeHelper(0x19, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
       pDispatch);
}

void Waits::_StopCallback()
{
   InvokeHelper(0x1a, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void Waits::_SetEnabled(BOOL Enabled)
{
   static BYTE parms[] =
      VTS_BOOL;
   InvokeHelper(0x1b, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
       Enabled);
}


/////////////////////////////////////////////////////////////////////////////
// AreaWait properties

LPDISPATCH AreaWait::GetApplication()
{
   LPDISPATCH result;
   GetProperty(0x6, VT_DISPATCH, (void*)&result);
   return result;
}

LPDISPATCH AreaWait::GetParent()
{
   LPDISPATCH result;
   GetProperty(0x7, VT_DISPATCH, (void*)&result);
   return result;
}

BOOL AreaWait::GetChanged()
{
   BOOL result;
   GetProperty(0xa, VT_BOOL, (void*)&result);
   return result;
}

BOOL AreaWait::GetEnabled()
{
   BOOL result;
   GetProperty(0xe, VT_BOOL, (void*)&result);
   return result;
}

void AreaWait::SetEnabled(BOOL propVal)
{
   SetProperty(0xe, VT_BOOL, propVal);
}

LPDISPATCH AreaWait::GetArea()
{
   LPDISPATCH result;
   GetProperty(0x64, VT_DISPATCH, (void*)&result);
   return result;
}

/////////////////////////////////////////////////////////////////////////////
// AreaWait operations

BOOL AreaWait::Wait(const VARIANT& Timeout)
{
   BOOL result;
   static BYTE parms[] =
      VTS_VARIANT;
   InvokeHelper(0x1, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
      &Timeout);
   return result;
}

void AreaWait::Clear()
{
   InvokeHelper(0x2, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

short AreaWait::_StartWait(LPDISPATCH pServer, long DispidNewEvent)
{
   short result;
   static BYTE parms[] =
      VTS_DISPATCH VTS_I4;
   InvokeHelper(0x3, DISPATCH_METHOD, VT_I2, (void*)&result, parms,
      pServer, DispidNewEvent);
   return result;
}

void AreaWait::_StopWait()
{
   InvokeHelper(0x4, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

long AreaWait::_GetBase(long SessionID)
{
   long result;
   static BYTE parms[] =
      VTS_I4;
   InvokeHelper(0x5, DISPATCH_METHOD, VT_I4, (void*)&result, parms,
      SessionID);
   return result;
}

void AreaWait::StartNotify(long hWnd, long wMsg, long wParam, long lParam, long wMsgFail, long wParamFail, long lParamFail)
{
   static BYTE parms[] =
      VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4;
   InvokeHelper(0x8, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
       hWnd, wMsg, wParam, lParam, wMsgFail, wParamFail, lParamFail);
}

void AreaWait::StopNotify()
{
   InvokeHelper(0x9, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void AreaWait::StartCallback(LPDISPATCH pDispatch)
{
   static BYTE parms[] =
      VTS_DISPATCH;
   InvokeHelper(0xb, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
       pDispatch);
}

void AreaWait::StopCallback()
{
   InvokeHelper(0xc, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void AreaWait::Reset()
{
   InvokeHelper(0xd, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}


/////////////////////////////////////////////////////////////////////////////
// Button properties

CString Button::GetCaption()
{
   CString result;
   GetProperty(0x1, VT_BSTR, (void*)&result);
   return result;
}

void Button::SetCaption(LPCTSTR propVal)
{
   SetProperty(0x1, VT_BSTR, propVal);
}

LPDISPATCH Button::GetParent()
{
   LPDISPATCH result;
   GetProperty(0x3, VT_DISPATCH, (void*)&result);
   return result;
}

CString Button::GetActionName()
{
   CString result;
   GetProperty(0x4, VT_BSTR, (void*)&result);
   return result;
}

void Button::SetActionName(LPCTSTR propVal)
{
   SetProperty(0x4, VT_BSTR, propVal);
}

short Button::GetActionType()
{
   short result;
   GetProperty(0x5, VT_I2, (void*)&result);
   return result;
}

void Button::SetActionType(short propVal)
{
   SetProperty(0x5, VT_I2, propVal);
}

LPDISPATCH Button::GetApplication()
{
   LPDISPATCH result;
   GetProperty(0x6, VT_DISPATCH, (void*)&result);
   return result;
}

/////////////////////////////////////////////////////////////////////////////
// Button operations

void Button::Invoke()
{
   InvokeHelper(0x2, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}


/////////////////////////////////////////////////////////////////////////////
// SerialOptions properties

CString SerialOptions::GetHostName()
{
   CString result;
   GetProperty(0x1, VT_BSTR, (void*)&result);
   return result;
}

LPDISPATCH SerialOptions::GetApplication()
{
   LPDISPATCH result;
   GetProperty(0x2, VT_DISPATCH, (void*)&result);
   return result;
}

LPDISPATCH SerialOptions::GetParent()
{
   LPDISPATCH result;
   GetProperty(0x3, VT_DISPATCH, (void*)&result);
   return result;
}

/////////////////////////////////////////////////////////////////////////////
// SerialOptions operations


/////////////////////////////////////////////////////////////////////////////
// Cursor properties

BOOL Cursor::GetBlink()
{
   BOOL result;
   GetProperty(0x1, VT_BOOL, (void*)&result);
   return result;
}

void Cursor::SetBlink(BOOL propVal)
{
   SetProperty(0x1, VT_BOOL, propVal);
}

BOOL Cursor::GetBlock()
{
   BOOL result;
   GetProperty(0x2, VT_BOOL, (void*)&result);
   return result;
}

void Cursor::SetBlock(BOOL propVal)
{
   SetProperty(0x2, VT_BOOL, propVal);
}

BOOL Cursor::GetVisible()
{
   BOOL result;
   GetProperty(0x3, VT_BOOL, (void*)&result);
   return result;
}

void Cursor::SetVisible(BOOL propVal)
{
   SetProperty(0x3, VT_BOOL, propVal);
}

/////////////////////////////////////////////////////////////////////////////
// Cursor operations


/////////////////////////////////////////////////////////////////////////////
// CursorWait properties

LPDISPATCH CursorWait::GetApplication()
{
   LPDISPATCH result;
   GetProperty(0x6, VT_DISPATCH, (void*)&result);
   return result;
}

LPDISPATCH CursorWait::GetParent()
{
   LPDISPATCH result;
   GetProperty(0x7, VT_DISPATCH, (void*)&result);
   return result;
}

BOOL CursorWait::GetChanged()
{
   BOOL result;
   GetProperty(0xa, VT_BOOL, (void*)&result);
   return result;
}

BOOL CursorWait::GetEnabled()
{
   BOOL result;
   GetProperty(0xe, VT_BOOL, (void*)&result);
   return result;
}

void CursorWait::SetEnabled(BOOL propVal)
{
   SetProperty(0xe, VT_BOOL, propVal);
}

short CursorWait::GetRow()
{
   short result;
   GetProperty(0x64, VT_I2, (void*)&result);
   return result;
}

short CursorWait::GetCol()
{
   short result;
   GetProperty(0x65, VT_I2, (void*)&result);
   return result;
}

short CursorWait::GetPage()
{
   short result;
   GetProperty(0x66, VT_I2, (void*)&result);
   return result;
}

/////////////////////////////////////////////////////////////////////////////
// CursorWait operations

BOOL CursorWait::Wait(const VARIANT& Timeout)
{
   BOOL result;
   static BYTE parms[] =
      VTS_VARIANT;
   InvokeHelper(0x1, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
      &Timeout);
   return result;
}

void CursorWait::Clear()
{
   InvokeHelper(0x2, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

short CursorWait::_StartWait(LPDISPATCH pServer, long DispidNewEvent)
{
   short result;
   static BYTE parms[] =
      VTS_DISPATCH VTS_I4;
   InvokeHelper(0x3, DISPATCH_METHOD, VT_I2, (void*)&result, parms,
      pServer, DispidNewEvent);
   return result;
}

void CursorWait::_StopWait()
{
   InvokeHelper(0x4, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

long CursorWait::_GetBase(long SessionID)
{
   long result;
   static BYTE parms[] =
      VTS_I4;
   InvokeHelper(0x5, DISPATCH_METHOD, VT_I4, (void*)&result, parms,
      SessionID);
   return result;
}

void CursorWait::StartNotify(long hWnd, long wMsg, long wParam, long lParam, long wMsgFail, long wParamFail, long lParamFail)
{
   static BYTE parms[] =
      VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4;
   InvokeHelper(0x8, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
       hWnd, wMsg, wParam, lParam, wMsgFail, wParamFail, lParamFail);
}

void CursorWait::StopNotify()
{
   InvokeHelper(0x9, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void CursorWait::StartCallback(LPDISPATCH pDispatch)
{
   static BYTE parms[] =
      VTS_DISPATCH;
   InvokeHelper(0xb, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
       pDispatch);
}

void CursorWait::StopCallback()
{
   InvokeHelper(0xc, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void CursorWait::Reset()
{
   InvokeHelper(0xd, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}


/////////////////////////////////////////////////////////////////////////////
// Fields properties

long Fields::GetCount()
{
   long result;
   GetProperty(0x1, VT_I4, (void*)&result);
   return result;
}

LPDISPATCH Fields::GetApplication()
{
   LPDISPATCH result;
   GetProperty(0x3, VT_DISPATCH, (void*)&result);
   return result;
}

LPDISPATCH Fields::GetParent()
{
   LPDISPATCH result;
   GetProperty(0x4, VT_DISPATCH, (void*)&result);
   return result;
}

/////////////////////////////////////////////////////////////////////////////
// Fields operations

LPDISPATCH Fields::Item(long Index)
{
   LPDISPATCH result;
   static BYTE parms[] =
      VTS_I4;
   InvokeHelper(0x2, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
      Index);
   return result;
}


/////////////////////////////////////////////////////////////////////////////
// FileTransferWait properties

LPDISPATCH FileTransferWait::GetApplication()
{
   LPDISPATCH result;
   GetProperty(0x6, VT_DISPATCH, (void*)&result);
   return result;
}

LPDISPATCH FileTransferWait::GetParent()
{
   LPDISPATCH result;
   GetProperty(0x7, VT_DISPATCH, (void*)&result);
   return result;
}

BOOL FileTransferWait::GetChanged()
{
   BOOL result;
   GetProperty(0xa, VT_BOOL, (void*)&result);
   return result;
}

BOOL FileTransferWait::GetEnabled()
{
   BOOL result;
   GetProperty(0xe, VT_BOOL, (void*)&result);
   return result;
}

void FileTransferWait::SetEnabled(BOOL propVal)
{
   SetProperty(0xe, VT_BOOL, propVal);
}

short FileTransferWait::GetFileEnd()
{
   short result;
   GetProperty(0x64, VT_I2, (void*)&result);
   return result;
}

long FileTransferWait::GetCount()
{
   long result;
   GetProperty(0x65, VT_I4, (void*)&result);
   return result;
}

/////////////////////////////////////////////////////////////////////////////
// FileTransferWait operations

BOOL FileTransferWait::Wait(const VARIANT& Timeout)
{
   BOOL result;
   static BYTE parms[] =
      VTS_VARIANT;
   InvokeHelper(0x1, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
      &Timeout);
   return result;
}

void FileTransferWait::Clear()
{
   InvokeHelper(0x2, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

short FileTransferWait::_StartWait(LPDISPATCH pServer, long DispidNewEvent)
{
   short result;
   static BYTE parms[] =
      VTS_DISPATCH VTS_I4;
   InvokeHelper(0x3, DISPATCH_METHOD, VT_I2, (void*)&result, parms,
      pServer, DispidNewEvent);
   return result;
}

void FileTransferWait::_StopWait()
{
   InvokeHelper(0x4, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

long FileTransferWait::_GetBase(long SessionID)
{
   long result;
   static BYTE parms[] =
      VTS_I4;
   InvokeHelper(0x5, DISPATCH_METHOD, VT_I4, (void*)&result, parms,
      SessionID);
   return result;
}

void FileTransferWait::StartNotify(long hWnd, long wMsg, long wParam, long lParam, long wMsgFail, long wParamFail, long lParamFail)
{
   static BYTE parms[] =
      VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4;
   InvokeHelper(0x8, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
       hWnd, wMsg, wParam, lParam, wMsgFail, wParamFail, lParamFail);
}

void FileTransferWait::StopNotify()
{
   InvokeHelper(0x9, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void FileTransferWait::StartCallback(LPDISPATCH pDispatch)
{
   static BYTE parms[] =
      VTS_DISPATCH;
   InvokeHelper(0xb, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
       pDispatch);
}

void FileTransferWait::StopCallback()
{
   InvokeHelper(0xc, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void FileTransferWait::Reset()
{
   InvokeHelper(0xd, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

LPDISPATCH FileTransferWait::Item(long Index)
{
   LPDISPATCH result;
   static BYTE parms[] =
      VTS_I4;
   InvokeHelper(0x66, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
      Index);
   return result;
}


/////////////////////////////////////////////////////////////////////////////
// FileTransferScheme properties

short FileTransferScheme::GetProtocol()
{
   short result;
   GetProperty(0x1, VT_I2, (void*)&result);
   return result;
}

void FileTransferScheme::SetProtocol(short propVal)
{
   SetProperty(0x1, VT_I2, propVal);
}

short FileTransferScheme::GetDuplicateName()
{
   short result;
   GetProperty(0x2, VT_I2, (void*)&result);
   return result;
}

void FileTransferScheme::SetDuplicateName(short propVal)
{
   SetProperty(0x2, VT_I2, propVal);
}

BOOL FileTransferScheme::GetCrashRecovery()
{
   BOOL result;
   GetProperty(0x3, VT_BOOL, (void*)&result);
   return result;
}

void FileTransferScheme::SetCrashRecovery(BOOL propVal)
{
   SetProperty(0x3, VT_BOOL, propVal);
}

BOOL FileTransferScheme::GetSendFullPath()
{
   BOOL result;
   GetProperty(0x4, VT_BOOL, (void*)&result);
   return result;
}

void FileTransferScheme::SetSendFullPath(BOOL propVal)
{
   SetProperty(0x4, VT_BOOL, propVal);
}

BOOL FileTransferScheme::GetUsePath()
{
   BOOL result;
   GetProperty(0x5, VT_BOOL, (void*)&result);
   return result;
}

void FileTransferScheme::SetUsePath(BOOL propVal)
{
   SetProperty(0x5, VT_BOOL, propVal);
}

BOOL FileTransferScheme::GetCreatePath()
{
   BOOL result;
   GetProperty(0x6, VT_BOOL, (void*)&result);
   return result;
}

void FileTransferScheme::SetCreatePath(BOOL propVal)
{
   SetProperty(0x6, VT_BOOL, propVal);
}

BOOL FileTransferScheme::GetRecurseSubdirectories()
{
   BOOL result;
   GetProperty(0x7, VT_BOOL, (void*)&result);
   return result;
}

void FileTransferScheme::SetRecurseSubdirectories(BOOL propVal)
{
   SetProperty(0x7, VT_BOOL, propVal);
}

CString FileTransferScheme::GetReceiveTo()
{
   CString result;
   GetProperty(0x8, VT_BSTR, (void*)&result);
   return result;
}

void FileTransferScheme::SetReceiveTo(LPCTSTR propVal)
{
   SetProperty(0x8, VT_BSTR, propVal);
}

short FileTransferScheme::GetFileType()
{
   short result;
   GetProperty(0x9, VT_I2, (void*)&result);
   return result;
}

void FileTransferScheme::SetFileType(short propVal)
{
   SetProperty(0x9, VT_I2, propVal);
}

BOOL FileTransferScheme::GetScanUnknownType()
{
   BOOL result;
   GetProperty(0xa, VT_BOOL, (void*)&result);
   return result;
}

void FileTransferScheme::SetScanUnknownType(BOOL propVal)
{
   SetProperty(0xa, VT_BOOL, propVal);
}

CString FileTransferScheme::GetTextFiles()
{
   CString result;
   GetProperty(0xb, VT_BSTR, (void*)&result);
   return result;
}

void FileTransferScheme::SetTextFiles(LPCTSTR propVal)
{
   SetProperty(0xb, VT_BSTR, propVal);
}

LPDISPATCH FileTransferScheme::GetApplication()
{
   LPDISPATCH result;
   GetProperty(0xc, VT_DISPATCH, (void*)&result);
   return result;
}

LPDISPATCH FileTransferScheme::GetParent()
{
   LPDISPATCH result;
   GetProperty(0xd, VT_DISPATCH, (void*)&result);
   return result;
}

BOOL FileTransferScheme::GetQuiet()
{
   BOOL result;
   GetProperty(0xe, VT_BOOL, (void*)&result);
   return result;
}

void FileTransferScheme::SetQuiet(BOOL propVal)
{
   SetProperty(0xe, VT_BOOL, propVal);
}

/////////////////////////////////////////////////////////////////////////////
// FileTransferScheme operations


/////////////////////////////////////////////////////////////////////////////
// Font properties

BOOL Font::GetAutoSize()
{
   BOOL result;
   GetProperty(0x3, VT_BOOL, (void*)&result);
   return result;
}

void Font::SetAutoSize(BOOL propVal)
{
   SetProperty(0x3, VT_BOOL, propVal);
}

short Font::GetSize()
{
   short result;
   GetProperty(0x4, VT_I2, (void*)&result);
   return result;
}

void Font::SetSize(short propVal)
{
   SetProperty(0x4, VT_I2, propVal);
}

LPDISPATCH Font::GetApplication()
{
   LPDISPATCH result;
   GetProperty(0x5, VT_DISPATCH, (void*)&result);
   return result;
}

LPDISPATCH Font::GetParent()
{
   LPDISPATCH result;
   GetProperty(0x6, VT_DISPATCH, (void*)&result);
   return result;
}

/////////////////////////////////////////////////////////////////////////////
// Font operations

BOOL Font::NextLarger()
{
   BOOL result;
   InvokeHelper(0x1, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
   return result;
}

BOOL Font::NextSmaller()
{
   BOOL result;
   InvokeHelper(0x2, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
   return result;
}


/////////////////////////////////////////////////////////////////////////////
// HostOptions properties

CString HostOptions::GetTerminalMode()
{
   CString result;
   GetProperty(0x1, VT_BSTR, (void*)&result);
   return result;
}

void HostOptions::SetTerminalMode(LPCTSTR propVal)
{
   SetProperty(0x1, VT_BSTR, propVal);
}

CString HostOptions::GetDAResponse()
{
   CString result;
   GetProperty(0x2, VT_BSTR, (void*)&result);
   return result;
}

void HostOptions::SetDAResponse(LPCTSTR propVal)
{
   SetProperty(0x2, VT_BSTR, propVal);
}

CString HostOptions::GetCustomPrimaryDA()
{
   CString result;
   GetProperty(0x3, VT_BSTR, (void*)&result);
   return result;
}

void HostOptions::SetCustomPrimaryDA(LPCTSTR propVal)
{
   SetProperty(0x3, VT_BSTR, propVal);
}

CString HostOptions::GetCustomSecondaryDA()
{
   CString result;
   GetProperty(0x4, VT_BSTR, (void*)&result);
   return result;
}

void HostOptions::SetCustomSecondaryDA(LPCTSTR propVal)
{
   SetProperty(0x4, VT_BSTR, propVal);
}

CString HostOptions::GetAnswerBack()
{
   CString result;
   GetProperty(0x5, VT_BSTR, (void*)&result);
   return result;
}

void HostOptions::SetAnswerBack(LPCTSTR propVal)
{
   SetProperty(0x5, VT_BSTR, propVal);
}

CString HostOptions::GetCharacterSetMode()
{
   CString result;
   GetProperty(0x6, VT_BSTR, (void*)&result);
   return result;
}

void HostOptions::SetCharacterSetMode(LPCTSTR propVal)
{
   SetProperty(0x6, VT_BSTR, propVal);
}

CString HostOptions::GetUserPreferredCharacterSet()
{
   CString result;
   GetProperty(0x7, VT_BSTR, (void*)&result);
   return result;
}

void HostOptions::SetUserPreferredCharacterSet(LPCTSTR propVal)
{
   SetProperty(0x7, VT_BSTR, propVal);
}

short HostOptions::GetNationalCharacterSet()
{
   short result;
   GetProperty(0x8, VT_I2, (void*)&result);
   return result;
}

void HostOptions::SetNationalCharacterSet(short propVal)
{
   SetProperty(0x8, VT_I2, propVal);
}

BOOL HostOptions::GetLocalEcho()
{
   BOOL result;
   GetProperty(0x9, VT_BOOL, (void*)&result);
   return result;
}

void HostOptions::SetLocalEcho(BOOL propVal)
{
   SetProperty(0x9, VT_BOOL, propVal);
}

BOOL HostOptions::GetLockUserKeys()
{
   BOOL result;
   GetProperty(0xa, VT_BOOL, (void*)&result);
   return result;
}

void HostOptions::SetLockUserKeys(BOOL propVal)
{
   SetProperty(0xa, VT_BOOL, propVal);
}

BOOL HostOptions::GetLockUserFeatures()
{
   BOOL result;
   GetProperty(0xb, VT_BOOL, (void*)&result);
   return result;
}

void HostOptions::SetLockUserFeatures(BOOL propVal)
{
   SetProperty(0xb, VT_BOOL, propVal);
}

BOOL HostOptions::GetColumns80()
{
   BOOL result;
   GetProperty(0xc, VT_BOOL, (void*)&result);
   return result;
}

void HostOptions::SetColumns80(BOOL propVal)
{
   SetProperty(0xc, VT_BOOL, propVal);
}

CString HostOptions::GetLines()
{
   CString result;
   GetProperty(0xd, VT_BSTR, (void*)&result);
   return result;
}

void HostOptions::SetLines(LPCTSTR propVal)
{
   SetProperty(0xd, VT_BSTR, propVal);
}

short HostOptions::GetScroll()
{
   short result;
   GetProperty(0xe, VT_I2, (void*)&result);
   return result;
}

void HostOptions::SetScroll(short propVal)
{
   SetProperty(0xe, VT_I2, propVal);
}

short HostOptions::GetStatusDisplay()
{
   short result;
   GetProperty(0xf, VT_I2, (void*)&result);
   return result;
}

void HostOptions::SetStatusDisplay(short propVal)
{
   SetProperty(0xf, VT_I2, propVal);
}

BOOL HostOptions::GetHorizontalCoupling()
{
   BOOL result;
   GetProperty(0x10, VT_BOOL, (void*)&result);
   return result;
}

void HostOptions::SetHorizontalCoupling(BOOL propVal)
{
   SetProperty(0x10, VT_BOOL, propVal);
}

BOOL HostOptions::GetVerticalCoupling()
{
   BOOL result;
   GetProperty(0x11, VT_BOOL, (void*)&result);
   return result;
}

void HostOptions::SetVerticalCoupling(BOOL propVal)
{
   SetProperty(0x11, VT_BOOL, propVal);
}

BOOL HostOptions::GetPageCoupling()
{
   BOOL result;
   GetProperty(0x12, VT_BOOL, (void*)&result);
   return result;
}

void HostOptions::SetPageCoupling(BOOL propVal)
{
   SetProperty(0x12, VT_BOOL, propVal);
}

BOOL HostOptions::GetNewLine()
{
   BOOL result;
   GetProperty(0x13, VT_BOOL, (void*)&result);
   return result;
}

void HostOptions::SetNewLine(BOOL propVal)
{
   SetProperty(0x13, VT_BOOL, propVal);
}

BOOL HostOptions::GetAutoWrap()
{
   BOOL result;
   GetProperty(0x14, VT_BOOL, (void*)&result);
   return result;
}

void HostOptions::SetAutoWrap(BOOL propVal)
{
   SetProperty(0x14, VT_BOOL, propVal);
}

BOOL HostOptions::GetDisplayControls()
{
   BOOL result;
   GetProperty(0x15, VT_BOOL, (void*)&result);
   return result;
}

void HostOptions::SetDisplayControls(BOOL propVal)
{
   SetProperty(0x15, VT_BOOL, propVal);
}

BOOL HostOptions::GetInverseScreen()
{
   BOOL result;
   GetProperty(0x16, VT_BOOL, (void*)&result);
   return result;
}

void HostOptions::SetInverseScreen(BOOL propVal)
{
   SetProperty(0x16, VT_BOOL, propVal);
}

short HostOptions::GetKeyboardLayout()
{
   short result;
   GetProperty(0x17, VT_I2, (void*)&result);
   return result;
}

void HostOptions::SetKeyboardLayout(short propVal)
{
   SetProperty(0x17, VT_I2, propVal);
}

BOOL HostOptions::GetEditpadVTLike()
{
   BOOL result;
   GetProperty(0x18, VT_BOOL, (void*)&result);
   return result;
}

void HostOptions::SetEditpadVTLike(BOOL propVal)
{
   SetProperty(0x18, VT_BOOL, propVal);
}

BOOL HostOptions::GetKeypadModeApplication()
{
   BOOL result;
   GetProperty(0x19, VT_BOOL, (void*)&result);
   return result;
}

void HostOptions::SetKeypadModeApplication(BOOL propVal)
{
   SetProperty(0x19, VT_BOOL, propVal);
}

BOOL HostOptions::GetCursorKeyModeApplication()
{
   BOOL result;
   GetProperty(0x1a, VT_BOOL, (void*)&result);
   return result;
}

void HostOptions::SetCursorKeyModeApplication(BOOL propVal)
{
   SetProperty(0x1a, VT_BOOL, propVal);
}

BOOL HostOptions::GetBackspaceDoesDelete()
{
   BOOL result;
   GetProperty(0x1b, VT_BOOL, (void*)&result);
   return result;
}

void HostOptions::SetBackspaceDoesDelete(BOOL propVal)
{
   SetProperty(0x1b, VT_BOOL, propVal);
}

short HostOptions::GetF1Key()
{
   short result;
   GetProperty(0x1c, VT_I2, (void*)&result);
   return result;
}

void HostOptions::SetF1Key(short propVal)
{
   SetProperty(0x1c, VT_I2, propVal);
}

short HostOptions::GetF2Key()
{
   short result;
   GetProperty(0x1d, VT_I2, (void*)&result);
   return result;
}

void HostOptions::SetF2Key(short propVal)
{
   SetProperty(0x1d, VT_I2, propVal);
}

short HostOptions::GetF3Key()
{
   short result;
   GetProperty(0x1e, VT_I2, (void*)&result);
   return result;
}

void HostOptions::SetF3Key(short propVal)
{
   SetProperty(0x1e, VT_I2, propVal);
}

short HostOptions::GetF4Key()
{
   short result;
   GetProperty(0x1f, VT_I2, (void*)&result);
   return result;
}

void HostOptions::SetF4Key(short propVal)
{
   SetProperty(0x1f, VT_I2, propVal);
}

short HostOptions::GetF5Key()
{
   short result;
   GetProperty(0x20, VT_I2, (void*)&result);
   return result;
}

void HostOptions::SetF5Key(short propVal)
{
   SetProperty(0x20, VT_I2, propVal);
}

BOOL HostOptions::GetMarginBell()
{
   BOOL result;
   GetProperty(0x21, VT_BOOL, (void*)&result);
   return result;
}

void HostOptions::SetMarginBell(BOOL propVal)
{
   SetProperty(0x21, VT_BOOL, propVal);
}

BOOL HostOptions::GetWarningBell()
{
   BOOL result;
   GetProperty(0x22, VT_BOOL, (void*)&result);
   return result;
}

void HostOptions::SetWarningBell(BOOL propVal)
{
   SetProperty(0x22, VT_BOOL, propVal);
}

BOOL HostOptions::GetGraphicsDisplayList()
{
   BOOL result;
   GetProperty(0x23, VT_BOOL, (void*)&result);
   return result;
}

void HostOptions::SetGraphicsDisplayList(BOOL propVal)
{
   SetProperty(0x23, VT_BOOL, propVal);
}

BOOL HostOptions::GetGraphicsBitmap()
{
   BOOL result;
   GetProperty(0x24, VT_BOOL, (void*)&result);
   return result;
}

void HostOptions::SetGraphicsBitmap(BOOL propVal)
{
   SetProperty(0x24, VT_BOOL, propVal);
}

BOOL HostOptions::GetGraphicsCursor()
{
   BOOL result;
   GetProperty(0x25, VT_BOOL, (void*)&result);
   return result;
}

void HostOptions::SetGraphicsCursor(BOOL propVal)
{
   SetProperty(0x25, VT_BOOL, propVal);
}

BOOL HostOptions::GetGraphicsMacroReport()
{
   BOOL result;
   GetProperty(0x26, VT_BOOL, (void*)&result);
   return result;
}

void HostOptions::SetGraphicsMacroReport(BOOL propVal)
{
   SetProperty(0x26, VT_BOOL, propVal);
}

BOOL HostOptions::GetSixelScrolling()
{
   BOOL result;
   GetProperty(0x27, VT_BOOL, (void*)&result);
   return result;
}

void HostOptions::SetSixelScrolling(BOOL propVal)
{
   SetProperty(0x27, VT_BOOL, propVal);
}

BOOL HostOptions::GetStyledLines()
{
   BOOL result;
   GetProperty(0x28, VT_BOOL, (void*)&result);
   return result;
}

void HostOptions::SetStyledLines(BOOL propVal)
{
   SetProperty(0x28, VT_BOOL, propVal);
}

BOOL HostOptions::GetSixelIgnorePrintRequests()
{
   BOOL result;
   GetProperty(0x29, VT_BOOL, (void*)&result);
   return result;
}

void HostOptions::SetSixelIgnorePrintRequests(BOOL propVal)
{
   SetProperty(0x29, VT_BOOL, propVal);
}

BOOL HostOptions::GetSixelBackgroundPrinting()
{
   BOOL result;
   GetProperty(0x2a, VT_BOOL, (void*)&result);
   return result;
}

void HostOptions::SetSixelBackgroundPrinting(BOOL propVal)
{
   SetProperty(0x2a, VT_BOOL, propVal);
}

BOOL HostOptions::GetSixelColorPrinting()
{
   BOOL result;
   GetProperty(0x2b, VT_BOOL, (void*)&result);
   return result;
}

void HostOptions::SetSixelColorPrinting(BOOL propVal)
{
   SetProperty(0x2b, VT_BOOL, propVal);
}

short HostOptions::GetSixelGraphicsLevel()
{
   short result;
   GetProperty(0x2c, VT_I2, (void*)&result);
   return result;
}

void HostOptions::SetSixelGraphicsLevel(short propVal)
{
   SetProperty(0x2c, VT_I2, propVal);
}

short HostOptions::GetSixelPrintOption()
{
   short result;
   GetProperty(0x2d, VT_I2, (void*)&result);
   return result;
}

void HostOptions::SetSixelPrintOption(short propVal)
{
   SetProperty(0x2d, VT_I2, propVal);
}

short HostOptions::GetSixelColorSpecification()
{
   short result;
   GetProperty(0x2e, VT_I2, (void*)&result);
   return result;
}

void HostOptions::SetSixelColorSpecification(short propVal)
{
   SetProperty(0x2e, VT_I2, propVal);
}

BOOL HostOptions::GetTektronixCRAddsLF()
{
   BOOL result;
   GetProperty(0x2f, VT_BOOL, (void*)&result);
   return result;
}

void HostOptions::SetTektronixCRAddsLF(BOOL propVal)
{
   SetProperty(0x2f, VT_BOOL, propVal);
}

BOOL HostOptions::GetTektronixLFAddsCR()
{
   BOOL result;
   GetProperty(0x30, VT_BOOL, (void*)&result);
   return result;
}

void HostOptions::SetTektronixLFAddsCR(BOOL propVal)
{
   SetProperty(0x30, VT_BOOL, propVal);
}

BOOL HostOptions::GetTektronixBSDoesDEL()
{
   BOOL result;
   GetProperty(0x31, VT_BOOL, (void*)&result);
   return result;
}

void HostOptions::SetTektronixBSDoesDEL(BOOL propVal)
{
   SetProperty(0x31, VT_BOOL, propVal);
}

BOOL HostOptions::GetTektronixDELIgnored()
{
   BOOL result;
   GetProperty(0x32, VT_BOOL, (void*)&result);
   return result;
}

void HostOptions::SetTektronixDELIgnored(BOOL propVal)
{
   SetProperty(0x32, VT_BOOL, propVal);
}

short HostOptions::GetTektronixGINTerminator()
{
   short result;
   GetProperty(0x33, VT_I2, (void*)&result);
   return result;
}

void HostOptions::SetTektronixGINTerminator(short propVal)
{
   SetProperty(0x33, VT_I2, propVal);
}

BOOL HostOptions::GetTektronixVT640Compatible()
{
   BOOL result;
   GetProperty(0x34, VT_BOOL, (void*)&result);
   return result;
}

void HostOptions::SetTektronixVT640Compatible(BOOL propVal)
{
   SetProperty(0x34, VT_BOOL, propVal);
}

BOOL HostOptions::GetTektronixEnlargedCharacters()
{
   BOOL result;
   GetProperty(0x35, VT_BOOL, (void*)&result);
   return result;
}

void HostOptions::SetTektronixEnlargedCharacters(BOOL propVal)
{
   SetProperty(0x35, VT_BOOL, propVal);
}

BOOL HostOptions::GetTektronixVectorFont()
{
   BOOL result;
   GetProperty(0x36, VT_BOOL, (void*)&result);
   return result;
}

void HostOptions::SetTektronixVectorFont(BOOL propVal)
{
   SetProperty(0x36, VT_BOOL, propVal);
}

short HostOptions::GetTektronixCharacterSet()
{
   short result;
   GetProperty(0x37, VT_I2, (void*)&result);
   return result;
}

void HostOptions::SetTektronixCharacterSet(short propVal)
{
   SetProperty(0x37, VT_I2, propVal);
}

short HostOptions::GetTektronixLineStyleMap()
{
   short result;
   GetProperty(0x38, VT_I2, (void*)&result);
   return result;
}

void HostOptions::SetTektronixLineStyleMap(short propVal)
{
   SetProperty(0x38, VT_I2, propVal);
}

short HostOptions::GetTektronixMarginControl()
{
   short result;
   GetProperty(0x39, VT_I2, (void*)&result);
   return result;
}

void HostOptions::SetTektronixMarginControl(short propVal)
{
   SetProperty(0x39, VT_I2, propVal);
}

BOOL HostOptions::GetTektronixAutoPrint()
{
   BOOL result;
   GetProperty(0x3a, VT_BOOL, (void*)&result);
   return result;
}

void HostOptions::SetTektronixAutoPrint(BOOL propVal)
{
   SetProperty(0x3a, VT_BOOL, propVal);
}

short HostOptions::GetTektronixDisplay()
{
   short result;
   GetProperty(0x3b, VT_I2, (void*)&result);
   return result;
}

void HostOptions::SetTektronixDisplay(short propVal)
{
   SetProperty(0x3b, VT_I2, propVal);
}

short HostOptions::GetEditMode()
{
   short result;
   GetProperty(0x3c, VT_I2, (void*)&result);
   return result;
}

void HostOptions::SetEditMode(short propVal)
{
   SetProperty(0x3c, VT_I2, propVal);
}

short HostOptions::GetEditFunctionKeys()
{
   short result;
   GetProperty(0x3d, VT_I2, (void*)&result);
   return result;
}

void HostOptions::SetEditFunctionKeys(short propVal)
{
   SetProperty(0x3d, VT_I2, propVal);
}

CString HostOptions::GetEditEOLChars()
{
   CString result;
   GetProperty(0x3e, VT_BSTR, (void*)&result);
   return result;
}

void HostOptions::SetEditEOLChars(LPCTSTR propVal)
{
   SetProperty(0x3e, VT_BSTR, propVal);
}

CString HostOptions::GetEditEOBChars()
{
   CString result;
   GetProperty(0x3f, VT_BSTR, (void*)&result);
   return result;
}

void HostOptions::SetEditEOBChars(LPCTSTR propVal)
{
   SetProperty(0x3f, VT_BSTR, propVal);
}

BOOL HostOptions::GetEditTransferTermination()
{
   BOOL result;
   GetProperty(0x40, VT_BOOL, (void*)&result);
   return result;
}

void HostOptions::SetEditTransferTermination(BOOL propVal)
{
   SetProperty(0x40, VT_BOOL, propVal);
}

BOOL HostOptions::GetEditSpaceCompression()
{
   BOOL result;
   GetProperty(0x41, VT_BOOL, (void*)&result);
   return result;
}

void HostOptions::SetEditSpaceCompression(BOOL propVal)
{
   SetProperty(0x41, VT_BOOL, propVal);
}

BOOL HostOptions::GetEditLineTransmit()
{
   BOOL result;
   GetProperty(0x42, VT_BOOL, (void*)&result);
   return result;
}

void HostOptions::SetEditLineTransmit(BOOL propVal)
{
   SetProperty(0x42, VT_BOOL, propVal);
}

BOOL HostOptions::GetEditNewLineScrolling()
{
   BOOL result;
   GetProperty(0x43, VT_BOOL, (void*)&result);
   return result;
}

void HostOptions::SetEditNewLineScrolling(BOOL propVal)
{
   SetProperty(0x43, VT_BOOL, propVal);
}

BOOL HostOptions::GetEditEraseAll()
{
   BOOL result;
   GetProperty(0x44, VT_BOOL, (void*)&result);
   return result;
}

void HostOptions::SetEditEraseAll(BOOL propVal)
{
   SetProperty(0x44, VT_BOOL, propVal);
}

BOOL HostOptions::GetEditKeyImmediate()
{
   BOOL result;
   GetProperty(0x45, VT_BOOL, (void*)&result);
   return result;
}

void HostOptions::SetEditKeyImmediate(BOOL propVal)
{
   SetProperty(0x45, VT_BOOL, propVal);
}

BOOL HostOptions::GetEditTransmitImmediate()
{
   BOOL result;
   GetProperty(0x46, VT_BOOL, (void*)&result);
   return result;
}

void HostOptions::SetEditTransmitImmediate(BOOL propVal)
{
   SetProperty(0x46, VT_BOOL, propVal);
}

BOOL HostOptions::GetEditVT131Transfer()
{
   BOOL result;
   GetProperty(0x47, VT_BOOL, (void*)&result);
   return result;
}

void HostOptions::SetEditVT131Transfer(BOOL propVal)
{
   SetProperty(0x47, VT_BOOL, propVal);
}

BOOL HostOptions::GetEditGuardedAreaAll()
{
   BOOL result;
   GetProperty(0x48, VT_BOOL, (void*)&result);
   return result;
}

void HostOptions::SetEditGuardedAreaAll(BOOL propVal)
{
   SetProperty(0x48, VT_BOOL, propVal);
}

BOOL HostOptions::GetEditSelectedAreaAll()
{
   BOOL result;
   GetProperty(0x49, VT_BOOL, (void*)&result);
   return result;
}

void HostOptions::SetEditSelectedAreaAll(BOOL propVal)
{
   SetProperty(0x49, VT_BOOL, propVal);
}

BOOL HostOptions::GetEditMultipleArea()
{
   BOOL result;
   GetProperty(0x4a, VT_BOOL, (void*)&result);
   return result;
}

void HostOptions::SetEditMultipleArea(BOOL propVal)
{
   SetProperty(0x4a, VT_BOOL, propVal);
}

short HostOptions::GetPrintMode()
{
   short result;
   GetProperty(0x4b, VT_I2, (void*)&result);
   return result;
}

void HostOptions::SetPrintMode(short propVal)
{
   SetProperty(0x4b, VT_I2, propVal);
}

short HostOptions::GetPrintCloseIdle()
{
   short result;
   GetProperty(0x4c, VT_I2, (void*)&result);
   return result;
}

void HostOptions::SetPrintCloseIdle(short propVal)
{
   SetProperty(0x4c, VT_I2, propVal);
}

short HostOptions::GetPrintExtent()
{
   short result;
   GetProperty(0x4d, VT_I2, (void*)&result);
   return result;
}

void HostOptions::SetPrintExtent(short propVal)
{
   SetProperty(0x4d, VT_I2, propVal);
}

BOOL HostOptions::GetPrintTerminator()
{
   BOOL result;
   GetProperty(0x4e, VT_BOOL, (void*)&result);
   return result;
}

void HostOptions::SetPrintTerminator(BOOL propVal)
{
   SetProperty(0x4e, VT_BOOL, propVal);
}

BOOL HostOptions::GetPrintEmulateANSI()
{
   BOOL result;
   GetProperty(0x4f, VT_BOOL, (void*)&result);
   return result;
}

void HostOptions::SetPrintEmulateANSI(BOOL propVal)
{
   SetProperty(0x4f, VT_BOOL, propVal);
}

BOOL HostOptions::GetPrintBackground()
{
   BOOL result;
   GetProperty(0x50, VT_BOOL, (void*)&result);
   return result;
}

void HostOptions::SetPrintBackground(BOOL propVal)
{
   SetProperty(0x50, VT_BOOL, propVal);
}

BOOL HostOptions::GetPrintColors()
{
   BOOL result;
   GetProperty(0x51, VT_BOOL, (void*)&result);
   return result;
}

void HostOptions::SetPrintColors(BOOL propVal)
{
   SetProperty(0x51, VT_BOOL, propVal);
}

BOOL HostOptions::GetPrintReverseBlackWhite()
{
   BOOL result;
   GetProperty(0x52, VT_BOOL, (void*)&result);
   return result;
}

void HostOptions::SetPrintReverseBlackWhite(BOOL propVal)
{
   SetProperty(0x52, VT_BOOL, propVal);
}

BOOL HostOptions::GetPrintUseBitmap()
{
   BOOL result;
   GetProperty(0x53, VT_BOOL, (void*)&result);
   return result;
}

void HostOptions::SetPrintUseBitmap(BOOL propVal)
{
   SetProperty(0x53, VT_BOOL, propVal);
}

BOOL HostOptions::GetPrintAutoFontSelect()
{
   BOOL result;
   GetProperty(0x54, VT_BOOL, (void*)&result);
   return result;
}

void HostOptions::SetPrintAutoFontSelect(BOOL propVal)
{
   SetProperty(0x54, VT_BOOL, propVal);
}

CString HostOptions::GetPrintFont()
{
   CString result;
   GetProperty(0x55, VT_BSTR, (void*)&result);
   return result;
}

void HostOptions::SetPrintFont(LPCTSTR propVal)
{
   SetProperty(0x55, VT_BSTR, propVal);
}

CString HostOptions::GetPrintFontStyle()
{
   CString result;
   GetProperty(0x56, VT_BSTR, (void*)&result);
   return result;
}

void HostOptions::SetPrintFontStyle(LPCTSTR propVal)
{
   SetProperty(0x56, VT_BSTR, propVal);
}

CString HostOptions::GetPrintFontSize()
{
   CString result;
   GetProperty(0x57, VT_BSTR, (void*)&result);
   return result;
}

void HostOptions::SetPrintFontSize(LPCTSTR propVal)
{
   SetProperty(0x57, VT_BSTR, propVal);
}

LPDISPATCH HostOptions::GetApplication()
{
   LPDISPATCH result;
   GetProperty(0x58, VT_DISPATCH, (void*)&result);
   return result;
}

LPDISPATCH HostOptions::GetParent()
{
   LPDISPATCH result;
   GetProperty(0x59, VT_DISPATCH, (void*)&result);
   return result;
}

BOOL HostOptions::GetInhibitHandshake()
{
   BOOL result;
   GetProperty(0x5a, VT_BOOL, (void*)&result);
   return result;
}

void HostOptions::SetInhibitHandshake(BOOL propVal)
{
   SetProperty(0x5a, VT_BOOL, propVal);
}

BOOL HostOptions::GetInhibitDC2()
{
   BOOL result;
   GetProperty(0x5b, VT_BOOL, (void*)&result);
   return result;
}

void HostOptions::SetInhibitDC2(BOOL propVal)
{
   SetProperty(0x5b, VT_BOOL, propVal);
}

BOOL HostOptions::GetEnqAck()
{
   BOOL result;
   GetProperty(0x5c, VT_BOOL, (void*)&result);
   return result;
}

void HostOptions::SetEnqAck(BOOL propVal)
{
   SetProperty(0x5c, VT_BOOL, propVal);
}

BOOL HostOptions::GetUseHostPrompt()
{
   BOOL result;
   GetProperty(0x5d, VT_BOOL, (void*)&result);
   return result;
}

void HostOptions::SetUseHostPrompt(BOOL propVal)
{
   SetProperty(0x5d, VT_BOOL, propVal);
}

CString HostOptions::GetPrompt()
{
   CString result;
   GetProperty(0x5e, VT_BSTR, (void*)&result);
   return result;
}

void HostOptions::SetPrompt(LPCTSTR propVal)
{
   SetProperty(0x5e, VT_BSTR, propVal);
}

short HostOptions::GetTransmissionModes()
{
   short result;
   GetProperty(0x5f, VT_I2, (void*)&result);
   return result;
}

void HostOptions::SetTransmissionModes(short propVal)
{
   SetProperty(0x5f, VT_I2, propVal);
}

short HostOptions::GetTransferTrigger()
{
   short result;
   GetProperty(0x60, VT_I2, (void*)&result);
   return result;
}

void HostOptions::SetTransferTrigger(short propVal)
{
   SetProperty(0x60, VT_I2, propVal);
}

short HostOptions::GetTransferStartColumn()
{
   short result;
   GetProperty(0x61, VT_I2, (void*)&result);
   return result;
}

void HostOptions::SetTransferStartColumn(short propVal)
{
   SetProperty(0x61, VT_I2, propVal);
}

BOOL HostOptions::GetTransferTransmitFunctions()
{
   BOOL result;
   GetProperty(0x62, VT_BOOL, (void*)&result);
   return result;
}

void HostOptions::SetTransferTransmitFunctions(BOOL propVal)
{
   SetProperty(0x62, VT_BOOL, propVal);
}

CString HostOptions::GetTransferTerminator()
{
   CString result;
   GetProperty(0x63, VT_BSTR, (void*)&result);
   return result;
}

void HostOptions::SetTransferTerminator(LPCTSTR propVal)
{
   SetProperty(0x63, VT_BSTR, propVal);
}

short HostOptions::GetTransferBlockUnit()
{
   short result;
   GetProperty(0x64, VT_I2, (void*)&result);
   return result;
}

void HostOptions::SetTransferBlockUnit(short propVal)
{
   SetProperty(0x64, VT_I2, propVal);
}

short HostOptions::GetMemorySize()
{
   short result;
   GetProperty(0x65, VT_I2, (void*)&result);
   return result;
}

void HostOptions::SetMemorySize(short propVal)
{
   SetProperty(0x65, VT_I2, propVal);
}

BOOL HostOptions::GetMessageBell()
{
   BOOL result;
   GetProperty(0x66, VT_BOOL, (void*)&result);
   return result;
}

void HostOptions::SetMessageBell(BOOL propVal)
{
   SetProperty(0x66, VT_BOOL, propVal);
}

BOOL HostOptions::GetDisplayFunctions()
{
   BOOL result;
   GetProperty(0x67, VT_BOOL, (void*)&result);
   return result;
}

void HostOptions::SetDisplayFunctions(BOOL propVal)
{
   SetProperty(0x67, VT_BOOL, propVal);
}

BOOL HostOptions::GetLockMemory()
{
   BOOL result;
   GetProperty(0x68, VT_BOOL, (void*)&result);
   return result;
}

void HostOptions::SetLockMemory(BOOL propVal)
{
   SetProperty(0x68, VT_BOOL, propVal);
}

short HostOptions::GetLeftMargin()
{
   short result;
   GetProperty(0x69, VT_I2, (void*)&result);
   return result;
}

void HostOptions::SetLeftMargin(short propVal)
{
   SetProperty(0x69, VT_I2, propVal);
}

short HostOptions::GetRightMargin()
{
   short result;
   GetProperty(0x6a, VT_I2, (void*)&result);
   return result;
}

void HostOptions::SetRightMargin(short propVal)
{
   SetProperty(0x6a, VT_I2, propVal);
}

BOOL HostOptions::GetTabsGenerateSpaces()
{
   BOOL result;
   GetProperty(0x6b, VT_BOOL, (void*)&result);
   return result;
}

void HostOptions::SetTabsGenerateSpaces(BOOL propVal)
{
   SetProperty(0x6b, VT_BOOL, propVal);
}

CString HostOptions::GetTabColumns()
{
   CString result;
   GetProperty(0x6c, VT_BSTR, (void*)&result);
   return result;
}

void HostOptions::SetTabColumns(LPCTSTR propVal)
{
   SetProperty(0x6c, VT_BSTR, propVal);
}

short HostOptions::GetReturnKey()
{
   short result;
   GetProperty(0x6d, VT_I2, (void*)&result);
   return result;
}

void HostOptions::SetReturnKey(short propVal)
{
   SetProperty(0x6d, VT_I2, propVal);
}

short HostOptions::GetCREffect()
{
   short result;
   GetProperty(0x6e, VT_I2, (void*)&result);
   return result;
}

void HostOptions::SetCREffect(short propVal)
{
   SetProperty(0x6e, VT_I2, propVal);
}

short HostOptions::GetNumericPadEnter()
{
   short result;
   GetProperty(0x6f, VT_I2, (void*)&result);
   return result;
}

void HostOptions::SetNumericPadEnter(short propVal)
{
   SetProperty(0x6f, VT_I2, propVal);
}

BOOL HostOptions::GetTypeahead()
{
   BOOL result;
   GetProperty(0x70, VT_BOOL, (void*)&result);
   return result;
}

void HostOptions::SetTypeahead(BOOL propVal)
{
   SetProperty(0x70, VT_BOOL, propVal);
}

BOOL HostOptions::GetCapsLock()
{
   BOOL result;
   GetProperty(0x71, VT_BOOL, (void*)&result);
   return result;
}

void HostOptions::SetCapsLock(BOOL propVal)
{
   SetProperty(0x71, VT_BOOL, propVal);
}

BOOL HostOptions::GetSpaceOverwrite()
{
   BOOL result;
   GetProperty(0x72, VT_BOOL, (void*)&result);
   return result;
}

void HostOptions::SetSpaceOverwrite(BOOL propVal)
{
   SetProperty(0x72, VT_BOOL, propVal);
}

short HostOptions::GetPrintLog()
{
   short result;
   GetProperty(0x73, VT_I2, (void*)&result);
   return result;
}

void HostOptions::SetPrintLog(short propVal)
{
   SetProperty(0x73, VT_I2, propVal);
}

short HostOptions::GetPrintPrint()
{
   short result;
   GetProperty(0x74, VT_I2, (void*)&result);
   return result;
}

void HostOptions::SetPrintPrint(short propVal)
{
   SetProperty(0x74, VT_I2, propVal);
}

BOOL HostOptions::GetFormFormatMode()
{
   BOOL result;
   GetProperty(0x75, VT_BOOL, (void*)&result);
   return result;
}

void HostOptions::SetFormFormatMode(BOOL propVal)
{
   SetProperty(0x75, VT_BOOL, propVal);
}

short HostOptions::GetFormTransmitFields()
{
   short result;
   GetProperty(0x76, VT_I2, (void*)&result);
   return result;
}

void HostOptions::SetFormTransmitFields(short propVal)
{
   SetProperty(0x76, VT_I2, propVal);
}

CString HostOptions::GetFormFieldSeparator()
{
   CString result;
   GetProperty(0x77, VT_BSTR, (void*)&result);
   return result;
}

void HostOptions::SetFormFieldSeparator(LPCTSTR propVal)
{
   SetProperty(0x77, VT_BSTR, propVal);
}

short HostOptions::GetFormBufferSize()
{
   short result;
   GetProperty(0x78, VT_I2, (void*)&result);
   return result;
}

void HostOptions::SetFormBufferSize(short propVal)
{
   SetProperty(0x78, VT_I2, propVal);
}

short HostOptions::GetFormDecimalType()
{
   short result;
   GetProperty(0x79, VT_I2, (void*)&result);
   return result;
}

void HostOptions::SetFormDecimalType(short propVal)
{
   SetProperty(0x79, VT_I2, propVal);
}

short HostOptions::GetFormDecimalDigits()
{
   short result;
   GetProperty(0x7a, VT_I2, (void*)&result);
   return result;
}

void HostOptions::SetFormDecimalDigits(short propVal)
{
   SetProperty(0x7a, VT_I2, propVal);
}

BOOL HostOptions::GetTektronixOverwrite()
{
   BOOL result;
   GetProperty(0x7b, VT_BOOL, (void*)&result);
   return result;
}

void HostOptions::SetTektronixOverwrite(BOOL propVal)
{
   SetProperty(0x7b, VT_BOOL, propVal);
}

/////////////////////////////////////////////////////////////////////////////
// HostOptions operations


/////////////////////////////////////////////////////////////////////////////
// MacroWait properties

LPDISPATCH MacroWait::GetApplication()
{
   LPDISPATCH result;
   GetProperty(0x6, VT_DISPATCH, (void*)&result);
   return result;
}

LPDISPATCH MacroWait::GetParent()
{
   LPDISPATCH result;
   GetProperty(0x7, VT_DISPATCH, (void*)&result);
   return result;
}

BOOL MacroWait::GetChanged()
{
   BOOL result;
   GetProperty(0xa, VT_BOOL, (void*)&result);
   return result;
}

BOOL MacroWait::GetEnabled()
{
   BOOL result;
   GetProperty(0xe, VT_BOOL, (void*)&result);
   return result;
}

void MacroWait::SetEnabled(BOOL propVal)
{
   SetProperty(0xe, VT_BOOL, propVal);
}

short MacroWait::GetMacroEnd()
{
   short result;
   GetProperty(0x64, VT_I2, (void*)&result);
   return result;
}

/////////////////////////////////////////////////////////////////////////////
// MacroWait operations

BOOL MacroWait::Wait(const VARIANT& Timeout)
{
   BOOL result;
   static BYTE parms[] =
      VTS_VARIANT;
   InvokeHelper(0x1, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
      &Timeout);
   return result;
}

void MacroWait::Clear()
{
   InvokeHelper(0x2, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

short MacroWait::_StartWait(LPDISPATCH pServer, long DispidNewEvent)
{
   short result;
   static BYTE parms[] =
      VTS_DISPATCH VTS_I4;
   InvokeHelper(0x3, DISPATCH_METHOD, VT_I2, (void*)&result, parms,
      pServer, DispidNewEvent);
   return result;
}

void MacroWait::_StopWait()
{
   InvokeHelper(0x4, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

long MacroWait::_GetBase(long SessionID)
{
   long result;
   static BYTE parms[] =
      VTS_I4;
   InvokeHelper(0x5, DISPATCH_METHOD, VT_I4, (void*)&result, parms,
      SessionID);
   return result;
}

void MacroWait::StartNotify(long hWnd, long wMsg, long wParam, long lParam, long wMsgFail, long wParamFail, long lParamFail)
{
   static BYTE parms[] =
      VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4;
   InvokeHelper(0x8, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
       hWnd, wMsg, wParam, lParam, wMsgFail, wParamFail, lParamFail);
}

void MacroWait::StopNotify()
{
   InvokeHelper(0x9, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void MacroWait::StartCallback(LPDISPATCH pDispatch)
{
   static BYTE parms[] =
      VTS_DISPATCH;
   InvokeHelper(0xb, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
       pDispatch);
}

void MacroWait::StopCallback()
{
   InvokeHelper(0xc, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void MacroWait::Reset()
{
   InvokeHelper(0xd, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}


/////////////////////////////////////////////////////////////////////////////
// _Application properties

/////////////////////////////////////////////////////////////////////////////
// _Application operations

LPDISPATCH _Application::_Waits(LPDISPATCH pServer, BOOL Enabled)
{
   LPDISPATCH result;
   static BYTE parms[] =
      VTS_DISPATCH VTS_BOOL;
   InvokeHelper(0x1, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
      pServer, Enabled);
   return result;
}

LPDISPATCH _Application::_Session()
{
   LPDISPATCH result;
   InvokeHelper(0x2, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
   return result;
}

LPDISPATCH _Application::_Restart()
{
   LPDISPATCH result;
   InvokeHelper(0x3, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
   return result;
}

LPDISPATCH _Application::_Close()
{
   LPDISPATCH result;
   InvokeHelper(0x4, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
   return result;
}


/////////////////////////////////////////////////////////////////////////////
// _ServerWait properties

LPDISPATCH _ServerWait::GetParent()
{
   LPDISPATCH result;
   GetProperty(0x7, VT_DISPATCH, (void*)&result);
   return result;
}

/////////////////////////////////////////////////////////////////////////////
// _ServerWait operations

BOOL _ServerWait::Wait(const VARIANT& Timeout)
{
   BOOL result;
   static BYTE parms[] =
      VTS_VARIANT;
   InvokeHelper(0x1, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
      &Timeout);
   return result;
}

long _ServerWait::_GetServerBase()
{
   long result;
   InvokeHelper(0x3e8, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
   return result;
}

void _ServerWait::_NewEvent(long iSession, short iClient)
{
   static BYTE parms[] =
      VTS_I4 VTS_I2;
   InvokeHelper(0x3e9, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
       iSession, iClient);
}


/////////////////////////////////////////////////////////////////////////////
// _ServerWaits properties

short _ServerWaits::GetCount()
{
   short result;
   GetProperty(0x1, VT_I2, (void*)&result);
   return result;
}

long _ServerWaits::GetChanged()
{
   long result;
   GetProperty(0x8, VT_I4, (void*)&result);
   return result;
}

BOOL _ServerWaits::GetEnabled()
{
   BOOL result;
   GetProperty(0xf, VT_BOOL, (void*)&result);
   return result;
}

void _ServerWaits::SetEnabled(BOOL propVal)
{
   SetProperty(0xf, VT_BOOL, propVal);
}

/////////////////////////////////////////////////////////////////////////////
// _ServerWaits operations

long _ServerWaits::Add(LPDISPATCH Wait)
{
   long result;
   static BYTE parms[] =
      VTS_DISPATCH;
   InvokeHelper(0x2, DISPATCH_METHOD, VT_I4, (void*)&result, parms,
      Wait);
   return result;
}

LPDISPATCH _ServerWaits::Item(long ID)
{
   LPDISPATCH result;
   static BYTE parms[] =
      VTS_I4;
   InvokeHelper(0x3, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
      ID);
   return result;
}

void _ServerWaits::Remove(long ID)
{
   static BYTE parms[] =
      VTS_I4;
   InvokeHelper(0x5, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
       ID);
}

void _ServerWaits::RemoveAll()
{
   InvokeHelper(0x6, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

long _ServerWaits::Wait(const VARIANT& Timeout)
{
   long result;
   static BYTE parms[] =
      VTS_VARIANT;
   InvokeHelper(0x7, DISPATCH_METHOD, VT_I4, (void*)&result, parms,
      &Timeout);
   return result;
}

void _ServerWaits::Clear()
{
   InvokeHelper(0x9, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void _ServerWaits::Reset()
{
   InvokeHelper(0xa, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void _ServerWaits::StartNotify(long hWnd, long wMsg, long wParam, long lParam, long wMsgFail, long wParamFail, long lParamFail)
{
   static BYTE parms[] =
      VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4;
   InvokeHelper(0xb, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
       hWnd, wMsg, wParam, lParam, wMsgFail, wParamFail, lParamFail);
}

void _ServerWaits::StopNotify()
{
   InvokeHelper(0xc, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void _ServerWaits::StartCallback(LPDISPATCH pDispatch)
{
   static BYTE parms[] =
      VTS_DISPATCH;
   InvokeHelper(0xd, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
       pDispatch);
}

void _ServerWaits::StopCallback()
{
   InvokeHelper(0xe, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

long _ServerWaits::_GetServerBase()
{
   long result;
   InvokeHelper(0x3e8, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
   return result;
}

void _ServerWaits::_NewEvent(long iSession, short iClient)
{
   static BYTE parms[] =
      VTS_I4 VTS_I2;
   InvokeHelper(0x3e9, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
       iSession, iClient);
}

} // namespace KeaDispatch