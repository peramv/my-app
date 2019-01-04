#if !defined(_KEAVT_H__INCLUDED_)
#define _KEAVT_H__INCLUDED_
// Machine generated IDispatch wrapper class(es) created with ClassWizard
/////////////////////////////////////////////////////////////////////////////
namespace KEADispatch
{

// Area wrapper class

class Area : public COleDispatchDriver
{
public:
   Area() {}      // Calls COleDispatchDriver default constructor
   Area(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
   Area(const Area& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:
   short GetPage();
   void SetPage(short);
   short GetTop();
   void SetTop(short);
   short GetLeft();
   void SetLeft(short);
   short GetBottom();
   void SetBottom(short);
   short GetRight();
   void SetRight(short);
   short GetType();
   void SetType(short);
   CString GetValue();
   LPDISPATCH GetApplication();
   LPDISPATCH GetParent();

// Operations
public:
   LPDISPATCH WaitUntilChanged(const VARIANT& Idle);
   void Select();
   void Copy();
   void Paste();
};
/////////////////////////////////////////////////////////////////////////////
// Buttons wrapper class

class Buttons : public COleDispatchDriver
{
public:
   Buttons() {}      // Calls COleDispatchDriver default constructor
   Buttons(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
   Buttons(const Buttons& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:
   long GetCount();
   LPDISPATCH GetApplication();
   LPDISPATCH GetParent();

// Operations
public:
   LPDISPATCH Add(short ActionType, LPCTSTR ActionName, LPCTSTR Caption);
   LPDISPATCH Item(short Index);
   void Remove(short Index);
   void RemoveAll();
};
/////////////////////////////////////////////////////////////////////////////
// Connectivity wrapper class

class Connectivity : public COleDispatchDriver
{
public:
   Connectivity() {}      // Calls COleDispatchDriver default constructor
   Connectivity(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
   Connectivity(const Connectivity& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:
   CString GetType();
   LPDISPATCH GetOptions();
   LPDISPATCH GetApplication();
   LPDISPATCH GetParent();

// Operations
public:
};
/////////////////////////////////////////////////////////////////////////////
// Field wrapper class

class Field : public COleDispatchDriver
{
public:
   Field() {}      // Calls COleDispatchDriver default constructor
   Field(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
   Field(const Field& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:
   short GetPage();
   void SetPage(short);
   short GetTop();
   void SetTop(short);
   short GetLeft();
   void SetLeft(short);
   short GetBottom();
   void SetBottom(short);
   short GetRight();
   void SetRight(short);
   short GetType();
   void SetType(short);
   CString GetValue();
   LPDISPATCH GetApplication();
   LPDISPATCH GetParent();
   short GetBold();
   short GetBlink();

// Operations
public:
   LPDISPATCH WaitUntilChanged(const VARIANT& Idle);
   void Select();
   void Copy();
   void Paste();
};
/////////////////////////////////////////////////////////////////////////////
// FileTransferResult wrapper class

class FileTransferResult : public COleDispatchDriver
{
public:
   FileTransferResult() {}      // Calls COleDispatchDriver default constructor
   FileTransferResult(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
   FileTransferResult(const FileTransferResult& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:
   CString GetName();
   CString GetRemoteName();
   long GetSize();
   long GetTime();
   short GetErrors();
   short GetTimeouts();
   short GetEndState();

// Operations
public:
};
/////////////////////////////////////////////////////////////////////////////
// Screen wrapper class

class Screen : public COleDispatchDriver
{
public:
   Screen() {}      // Calls COleDispatchDriver default constructor
   Screen(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
   Screen(const Screen& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:
   short GetPage();
   short GetRow();
   short GetCol();
   short GetPages();
   short GetRows();
   short GetCols();
   CString GetHostName();
   BOOL GetLocal();
   void SetLocal(BOOL);
   BOOL GetSynchronous();
   void SetSynchronous(BOOL);
   LPDISPATCH GetHostOptions();
   LPDISPATCH GetSelection();
   LPDISPATCH GetApplication();
   LPDISPATCH GetParent();

// Operations
public:
   void PutString(LPCTSTR Text);
   void SendKeys(LPCTSTR Text);
   LPDISPATCH Area(short Row, short Col, short EndRow, short EndCol, const VARIANT& Page, const VARIANT& Type);
   CString GetString(short Row, short Col, short Len, const VARIANT& Page);
   void Clear();
   void SendInput(LPCTSTR Text);
   LPDISPATCH WaitHostQuiet(long Time);
   LPDISPATCH WaitForStream(LPCTSTR Text, const VARIANT& Idle, const VARIANT& Timeout, const VARIANT& Options);
   LPDISPATCH WaitForString(LPCTSTR Text, const VARIANT& Row, const VARIANT& Col, const VARIANT& Page, const VARIANT& Idle, const VARIANT& Timeout, const VARIANT& Options);
   LPDISPATCH Search(LPCTSTR Text, const VARIANT& Row, const VARIANT& Col, const VARIANT& Page, const VARIANT& Occurrence);
   LPDISPATCH WaitForCursor(const VARIANT& Row, const VARIANT& Col, const VARIANT& Page);
   LPDISPATCH WaitForCursorMove();
   LPDISPATCH WaitForKeys(const VARIANT& Process);
   void Copy();
   void Paste();
   LPDISPATCH SelectAll();
   LPDISPATCH Select(short StartRow, short StartCol, short EndRow, short EndCol, const VARIANT& Page);
   VARIANT CopyPS(short Row, short Col, short Len, const VARIANT& Page, const VARIANT& Type);
   void GetInfo(short* Row, short* Col, short* Page, short* DisplayTop, short* DisplayLeft, short* DisplayBottom, short* DisplayRight, short* Rows, short* Cols, short* Pages);
   void CancelSelection();
   LPDISPATCH GetDisplayArea();
   LPDISPATCH GetField(short Attribute, short Row, short Col, const VARIANT& Page);
   LPDISPATCH GetFields(short Attribute);
};
/////////////////////////////////////////////////////////////////////////////
// KeyWait wrapper class

class KeyWait : public COleDispatchDriver
{
public:
   KeyWait() {}      // Calls COleDispatchDriver default constructor
   KeyWait(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
   KeyWait(const KeyWait& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:
   LPDISPATCH GetApplication();
   LPDISPATCH GetParent();
   BOOL GetChanged();
   BOOL GetEnabled();
   void SetEnabled(BOOL);
   CString GetName();

// Operations
public:
   BOOL Wait(const VARIANT& Timeout);
   void Clear();
   short _StartWait(LPDISPATCH pServer, long DispidNewEvent);
   void _StopWait();
   long _GetBase(long SessionID);
   void StartNotify(long hWnd, long wMsg, long wParam, long lParam, long wMsgFail, long wParamFail, long lParamFail);
   void StopNotify();
   void StartCallback(LPDISPATCH pDispatch);
   void StopCallback();
   void Reset();
};
/////////////////////////////////////////////////////////////////////////////
// MatchWait wrapper class

class MatchWait : public COleDispatchDriver
{
public:
   MatchWait() {}      // Calls COleDispatchDriver default constructor
   MatchWait(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
   MatchWait(const MatchWait& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:
   LPDISPATCH GetApplication();
   LPDISPATCH GetParent();
   BOOL GetChanged();
   BOOL GetEnabled();
   void SetEnabled(BOOL);
   CString GetString();
   short GetRow();
   short GetCol();
   short GetPage();

// Operations
public:
   BOOL Wait(const VARIANT& Timeout);
   void Clear();
   short _StartWait(LPDISPATCH pServer, long DispidNewEvent);
   void _StopWait();
   long _GetBase(long SessionID);
   void StartNotify(long hWnd, long wMsg, long wParam, long lParam, long wMsgFail, long wParamFail, long lParamFail);
   void StopNotify();
   void StartCallback(LPDISPATCH pDispatch);
   void StopCallback();
   void Reset();
};
/////////////////////////////////////////////////////////////////////////////
// DisconnectWait wrapper class

class DisconnectWait : public COleDispatchDriver
{
public:
   DisconnectWait() {}      // Calls COleDispatchDriver default constructor
   DisconnectWait(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
   DisconnectWait(const DisconnectWait& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:
   LPDISPATCH GetApplication();
   LPDISPATCH GetParent();
   BOOL GetChanged();
   BOOL GetEnabled();
   void SetEnabled(BOOL);
   BOOL GetConnected();

// Operations
public:
   BOOL Wait(const VARIANT& Timeout);
   void Clear();
   short _StartWait(LPDISPATCH pServer, long DispidNewEvent);
   void _StopWait();
   long _GetBase(long SessionID);
   void StartNotify(long hWnd, long wMsg, long wParam, long lParam, long wMsgFail, long wParamFail, long lParamFail);
   void StopNotify();
   void StartCallback(LPDISPATCH pDispatch);
   void StopCallback();
   void Reset();
};
/////////////////////////////////////////////////////////////////////////////
// Session wrapper class

class Session : public COleDispatchDriver
{
public:
   Session() {}      // Calls COleDispatchDriver default constructor
   Session(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
   Session(const Session& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:
   LPDISPATCH GetScreen();
   LPDISPATCH GetButtons();
   CString GetFullName();
   CString GetName();
   CString GetTitle();
   CString GetPath();
   BOOL GetVisible();
   void SetVisible(BOOL);
   BOOL GetHistory();
   void SetHistory(BOOL);
   BOOL GetCapture();
   void SetCapture(BOOL);
   LPDISPATCH GetFont();
   BOOL GetMenu();
   void SetMenu(BOOL);
   BOOL GetSaved();
   CString GetCaption();
   void SetCaption(LPCTSTR);
   CString GetStatusBar();
   short GetType();
   short GetWindowState();
   void SetWindowState(short);
   LPDISPATCH GetCursor();
   LPDISPATCH GetFileTransferScheme();
   LPDISPATCH GetConnectivity();
   LPDISPATCH GetApplication();
   LPDISPATCH GetParent();
   BOOL GetConnected();
   void SetConnected(BOOL);
   short GetLeft();
   void SetLeft(short);
   short GetTop();
   void SetTop(short);
   short GetWidth();
   void SetWidth(short);
   short GetHeight();
   void SetHeight(short);
   long GetHWnd();

// Operations
public:
   void Activate();
   void Close();
   void Save();
   void SaveAs(LPCTSTR Name);
   void PrintDisplay(short Extent, BOOL Graphics);
   void ClearHistory();
   void Restart();
   LPDISPATCH ReceiveFile(const VARIANT& Files, const VARIANT& Path);
   LPDISPATCH SendFile(const VARIANT& Files, const VARIANT& HostName);
   void ClearComm();
   void Connect(const VARIANT& Name);
   void Disconnect();
   LPDISPATCH WaitForDisconnect();
   LPDISPATCH RunMacro(LPCTSTR File);
   LPDISPATCH Execute(LPCTSTR Command);
   CString GetDirectory(short FileTypeRequested);
};
/////////////////////////////////////////////////////////////////////////////
// Sessions wrapper class

class Sessions : public COleDispatchDriver
{
public:
   Sessions() {}      // Calls COleDispatchDriver default constructor
   Sessions(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
   Sessions(const Sessions& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:
   long GetCount();
   LPDISPATCH GetApplication();
   LPDISPATCH GetParent();

// Operations
public:
   LPDISPATCH Item(short Index);
   void CloseAll();
   void RestartAll();
};
/////////////////////////////////////////////////////////////////////////////
// System wrapper class

class System : public COleDispatchDriver
{
public:
   System() {}      // Calls COleDispatchDriver default constructor
   System(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
   System(const System& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:
   LPDISPATCH GetWaits();
   CString GetName();
   CString GetVersion();
   LPDISPATCH GetApplication();
   LPDISPATCH GetParent();
   LPDISPATCH GetSessions();
   LPDISPATCH GetActiveSession();
   CString GetFullName();

// Operations
public:
   long _RegisterClient(LPDISPATCH pApplication);
   void _DeregisterClient(long SessionID);
   void _ServerWait(long SessionID, LPDISPATCH ClientWait, LPCTSTR IID_Client, long DispidStartWait, long DispidStopWait, long DefaultTimeout);
   void Quit();
   void _ActiveClient(long SessionID);
   CString GetDirectory(short ProductTypeWanted, short DirectoryTypeWanted);
};
/////////////////////////////////////////////////////////////////////////////
// Wait wrapper class

class Wait : public COleDispatchDriver
{
public:
   Wait() {}      // Calls COleDispatchDriver default constructor
   Wait(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
   Wait(const Wait& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:
   LPDISPATCH GetApplication();
   LPDISPATCH GetParent();
   BOOL GetChanged();
   BOOL GetEnabled();
   void SetEnabled(BOOL);

// Operations
public:
   BOOL Wait_(const VARIANT& Timeout);
   void Clear();
   short _StartWait(LPDISPATCH pServer, long DispidNewEvent);
   void _StopWait();
   long _GetBase(long SessionID);
   void StartNotify(long hWnd, long wMsg, long wParam, long lParam, long wMsgFail, long wParamFail, long lParamFail);
   void StopNotify();
   void StartCallback(LPDISPATCH pDispatch);
   void StopCallback();
   void Reset();
};
/////////////////////////////////////////////////////////////////////////////
// Waits wrapper class

class Waits : public COleDispatchDriver
{
public:
   Waits() {}      // Calls COleDispatchDriver default constructor
   Waits(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
   Waits(const Waits& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:
   short GetCount();
   long GetChanged();
   BOOL GetEnabled();
   void SetEnabled(BOOL);

// Operations
public:
   long Add(LPDISPATCH Wait);
   LPDISPATCH Item(long ID);
   void Remove(long ID);
   void RemoveAll();
   long Wait(const VARIANT& Timeout);
   void Clear();
   void Reset();
   void StartNotify(long hWnd, long wMsg, long wParam, long lParam, long wMsgFail, long wParamFail, long lParamFail);
   void StopNotify();
   void StartCallback(LPDISPATCH pDispatch);
   void StopCallback();
   short _StartWait(LPDISPATCH pServer, long DispidNewEvent);
   void _StopWait();
   long _GetBase(long SessionID);
   short _Add(LPDISPATCH pWait);
   short _Remove(LPDISPATCH pWait);
   void _ClearAll();
   void _ResetAll();
   void _StartNotify(long hWnd, long wMsg, long wParam, long lParam, long wMsgFail, long wParamFail, long lParamFail);
   void _StopNotify();
   void _StartCallback(LPDISPATCH pDispatch);
   void _StopCallback();
   void _SetEnabled(BOOL Enabled);
};
/////////////////////////////////////////////////////////////////////////////
// AreaWait wrapper class

class AreaWait : public COleDispatchDriver
{
public:
   AreaWait() {}      // Calls COleDispatchDriver default constructor
   AreaWait(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
   AreaWait(const AreaWait& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:
   LPDISPATCH GetApplication();
   LPDISPATCH GetParent();
   BOOL GetChanged();
   BOOL GetEnabled();
   void SetEnabled(BOOL);
   LPDISPATCH GetArea();

// Operations
public:
   BOOL Wait(const VARIANT& Timeout);
   void Clear();
   short _StartWait(LPDISPATCH pServer, long DispidNewEvent);
   void _StopWait();
   long _GetBase(long SessionID);
   void StartNotify(long hWnd, long wMsg, long wParam, long lParam, long wMsgFail, long wParamFail, long lParamFail);
   void StopNotify();
   void StartCallback(LPDISPATCH pDispatch);
   void StopCallback();
   void Reset();
};
/////////////////////////////////////////////////////////////////////////////
// Button wrapper class

class Button : public COleDispatchDriver
{
public:
   Button() {}      // Calls COleDispatchDriver default constructor
   Button(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
   Button(const Button& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:
   CString GetCaption();
   void SetCaption(LPCTSTR);
   LPDISPATCH GetParent();
   CString GetActionName();
   void SetActionName(LPCTSTR);
   short GetActionType();
   void SetActionType(short);
   LPDISPATCH GetApplication();

// Operations
public:
   void Invoke();
};
/////////////////////////////////////////////////////////////////////////////
// SerialOptions wrapper class

class SerialOptions : public COleDispatchDriver
{
public:
   SerialOptions() {}      // Calls COleDispatchDriver default constructor
   SerialOptions(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
   SerialOptions(const SerialOptions& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:
   CString GetHostName();
   LPDISPATCH GetApplication();
   LPDISPATCH GetParent();

// Operations
public:
};
/////////////////////////////////////////////////////////////////////////////
// Cursor wrapper class

class Cursor : public COleDispatchDriver
{
public:
   Cursor() {}      // Calls COleDispatchDriver default constructor
   Cursor(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
   Cursor(const Cursor& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:
   BOOL GetBlink();
   void SetBlink(BOOL);
   BOOL GetBlock();
   void SetBlock(BOOL);
   BOOL GetVisible();
   void SetVisible(BOOL);

// Operations
public:
};
/////////////////////////////////////////////////////////////////////////////
// CursorWait wrapper class

class CursorWait : public COleDispatchDriver
{
public:
   CursorWait() {}      // Calls COleDispatchDriver default constructor
   CursorWait(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
   CursorWait(const CursorWait& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:
   LPDISPATCH GetApplication();
   LPDISPATCH GetParent();
   BOOL GetChanged();
   BOOL GetEnabled();
   void SetEnabled(BOOL);
   short GetRow();
   short GetCol();
   short GetPage();

// Operations
public:
   BOOL Wait(const VARIANT& Timeout);
   void Clear();
   short _StartWait(LPDISPATCH pServer, long DispidNewEvent);
   void _StopWait();
   long _GetBase(long SessionID);
   void StartNotify(long hWnd, long wMsg, long wParam, long lParam, long wMsgFail, long wParamFail, long lParamFail);
   void StopNotify();
   void StartCallback(LPDISPATCH pDispatch);
   void StopCallback();
   void Reset();
};
/////////////////////////////////////////////////////////////////////////////
// Fields wrapper class

class Fields : public COleDispatchDriver
{
public:
   Fields() {}      // Calls COleDispatchDriver default constructor
   Fields(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
   Fields(const Fields& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:
   long GetCount();
   LPDISPATCH GetApplication();
   LPDISPATCH GetParent();

// Operations
public:
   LPDISPATCH Item(long Index);
};
/////////////////////////////////////////////////////////////////////////////
// FileTransferWait wrapper class

class FileTransferWait : public COleDispatchDriver
{
public:
   FileTransferWait() {}      // Calls COleDispatchDriver default constructor
   FileTransferWait(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
   FileTransferWait(const FileTransferWait& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:
   LPDISPATCH GetApplication();
   LPDISPATCH GetParent();
   BOOL GetChanged();
   BOOL GetEnabled();
   void SetEnabled(BOOL);
   short GetFileEnd();
   long GetCount();

// Operations
public:
   BOOL Wait(const VARIANT& Timeout);
   void Clear();
   short _StartWait(LPDISPATCH pServer, long DispidNewEvent);
   void _StopWait();
   long _GetBase(long SessionID);
   void StartNotify(long hWnd, long wMsg, long wParam, long lParam, long wMsgFail, long wParamFail, long lParamFail);
   void StopNotify();
   void StartCallback(LPDISPATCH pDispatch);
   void StopCallback();
   void Reset();
   LPDISPATCH Item(long Index);
};
/////////////////////////////////////////////////////////////////////////////
// FileTransferScheme wrapper class

class FileTransferScheme : public COleDispatchDriver
{
public:
   FileTransferScheme() {}      // Calls COleDispatchDriver default constructor
   FileTransferScheme(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
   FileTransferScheme(const FileTransferScheme& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:
   short GetProtocol();
   void SetProtocol(short);
   short GetDuplicateName();
   void SetDuplicateName(short);
   BOOL GetCrashRecovery();
   void SetCrashRecovery(BOOL);
   BOOL GetSendFullPath();
   void SetSendFullPath(BOOL);
   BOOL GetUsePath();
   void SetUsePath(BOOL);
   BOOL GetCreatePath();
   void SetCreatePath(BOOL);
   BOOL GetRecurseSubdirectories();
   void SetRecurseSubdirectories(BOOL);
   CString GetReceiveTo();
   void SetReceiveTo(LPCTSTR);
   short GetFileType();
   void SetFileType(short);
   BOOL GetScanUnknownType();
   void SetScanUnknownType(BOOL);
   CString GetTextFiles();
   void SetTextFiles(LPCTSTR);
   LPDISPATCH GetApplication();
   LPDISPATCH GetParent();
   BOOL GetQuiet();
   void SetQuiet(BOOL);

// Operations
public:
};
/////////////////////////////////////////////////////////////////////////////
// Font wrapper class

class Font : public COleDispatchDriver
{
public:
   Font() {}      // Calls COleDispatchDriver default constructor
   Font(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
   Font(const Font& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:
   BOOL GetAutoSize();
   void SetAutoSize(BOOL);
   short GetSize();
   void SetSize(short);
   LPDISPATCH GetApplication();
   LPDISPATCH GetParent();

// Operations
public:
   BOOL NextLarger();
   BOOL NextSmaller();
};
/////////////////////////////////////////////////////////////////////////////
// HostOptions wrapper class

class HostOptions : public COleDispatchDriver
{
public:
   HostOptions() {}      // Calls COleDispatchDriver default constructor
   HostOptions(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
   HostOptions(const HostOptions& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:
   CString GetTerminalMode();
   void SetTerminalMode(LPCTSTR);
   CString GetDAResponse();
   void SetDAResponse(LPCTSTR);
   CString GetCustomPrimaryDA();
   void SetCustomPrimaryDA(LPCTSTR);
   CString GetCustomSecondaryDA();
   void SetCustomSecondaryDA(LPCTSTR);
   CString GetAnswerBack();
   void SetAnswerBack(LPCTSTR);
   CString GetCharacterSetMode();
   void SetCharacterSetMode(LPCTSTR);
   CString GetUserPreferredCharacterSet();
   void SetUserPreferredCharacterSet(LPCTSTR);
   short GetNationalCharacterSet();
   void SetNationalCharacterSet(short);
   BOOL GetLocalEcho();
   void SetLocalEcho(BOOL);
   BOOL GetLockUserKeys();
   void SetLockUserKeys(BOOL);
   BOOL GetLockUserFeatures();
   void SetLockUserFeatures(BOOL);
   BOOL GetColumns80();
   void SetColumns80(BOOL);
   CString GetLines();
   void SetLines(LPCTSTR);
   short GetScroll();
   void SetScroll(short);
   short GetStatusDisplay();
   void SetStatusDisplay(short);
   BOOL GetHorizontalCoupling();
   void SetHorizontalCoupling(BOOL);
   BOOL GetVerticalCoupling();
   void SetVerticalCoupling(BOOL);
   BOOL GetPageCoupling();
   void SetPageCoupling(BOOL);
   BOOL GetNewLine();
   void SetNewLine(BOOL);
   BOOL GetAutoWrap();
   void SetAutoWrap(BOOL);
   BOOL GetDisplayControls();
   void SetDisplayControls(BOOL);
   BOOL GetInverseScreen();
   void SetInverseScreen(BOOL);
   short GetKeyboardLayout();
   void SetKeyboardLayout(short);
   BOOL GetEditpadVTLike();
   void SetEditpadVTLike(BOOL);
   BOOL GetKeypadModeApplication();
   void SetKeypadModeApplication(BOOL);
   BOOL GetCursorKeyModeApplication();
   void SetCursorKeyModeApplication(BOOL);
   BOOL GetBackspaceDoesDelete();
   void SetBackspaceDoesDelete(BOOL);
   short GetF1Key();
   void SetF1Key(short);
   short GetF2Key();
   void SetF2Key(short);
   short GetF3Key();
   void SetF3Key(short);
   short GetF4Key();
   void SetF4Key(short);
   short GetF5Key();
   void SetF5Key(short);
   BOOL GetMarginBell();
   void SetMarginBell(BOOL);
   BOOL GetWarningBell();
   void SetWarningBell(BOOL);
   BOOL GetGraphicsDisplayList();
   void SetGraphicsDisplayList(BOOL);
   BOOL GetGraphicsBitmap();
   void SetGraphicsBitmap(BOOL);
   BOOL GetGraphicsCursor();
   void SetGraphicsCursor(BOOL);
   BOOL GetGraphicsMacroReport();
   void SetGraphicsMacroReport(BOOL);
   BOOL GetSixelScrolling();
   void SetSixelScrolling(BOOL);
   BOOL GetStyledLines();
   void SetStyledLines(BOOL);
   BOOL GetSixelIgnorePrintRequests();
   void SetSixelIgnorePrintRequests(BOOL);
   BOOL GetSixelBackgroundPrinting();
   void SetSixelBackgroundPrinting(BOOL);
   BOOL GetSixelColorPrinting();
   void SetSixelColorPrinting(BOOL);
   short GetSixelGraphicsLevel();
   void SetSixelGraphicsLevel(short);
   short GetSixelPrintOption();
   void SetSixelPrintOption(short);
   short GetSixelColorSpecification();
   void SetSixelColorSpecification(short);
   BOOL GetTektronixCRAddsLF();
   void SetTektronixCRAddsLF(BOOL);
   BOOL GetTektronixLFAddsCR();
   void SetTektronixLFAddsCR(BOOL);
   BOOL GetTektronixBSDoesDEL();
   void SetTektronixBSDoesDEL(BOOL);
   BOOL GetTektronixDELIgnored();
   void SetTektronixDELIgnored(BOOL);
   short GetTektronixGINTerminator();
   void SetTektronixGINTerminator(short);
   BOOL GetTektronixVT640Compatible();
   void SetTektronixVT640Compatible(BOOL);
   BOOL GetTektronixEnlargedCharacters();
   void SetTektronixEnlargedCharacters(BOOL);
   BOOL GetTektronixVectorFont();
   void SetTektronixVectorFont(BOOL);
   short GetTektronixCharacterSet();
   void SetTektronixCharacterSet(short);
   short GetTektronixLineStyleMap();
   void SetTektronixLineStyleMap(short);
   short GetTektronixMarginControl();
   void SetTektronixMarginControl(short);
   BOOL GetTektronixAutoPrint();
   void SetTektronixAutoPrint(BOOL);
   short GetTektronixDisplay();
   void SetTektronixDisplay(short);
   short GetEditMode();
   void SetEditMode(short);
   short GetEditFunctionKeys();
   void SetEditFunctionKeys(short);
   CString GetEditEOLChars();
   void SetEditEOLChars(LPCTSTR);
   CString GetEditEOBChars();
   void SetEditEOBChars(LPCTSTR);
   BOOL GetEditTransferTermination();
   void SetEditTransferTermination(BOOL);
   BOOL GetEditSpaceCompression();
   void SetEditSpaceCompression(BOOL);
   BOOL GetEditLineTransmit();
   void SetEditLineTransmit(BOOL);
   BOOL GetEditNewLineScrolling();
   void SetEditNewLineScrolling(BOOL);
   BOOL GetEditEraseAll();
   void SetEditEraseAll(BOOL);
   BOOL GetEditKeyImmediate();
   void SetEditKeyImmediate(BOOL);
   BOOL GetEditTransmitImmediate();
   void SetEditTransmitImmediate(BOOL);
   BOOL GetEditVT131Transfer();
   void SetEditVT131Transfer(BOOL);
   BOOL GetEditGuardedAreaAll();
   void SetEditGuardedAreaAll(BOOL);
   BOOL GetEditSelectedAreaAll();
   void SetEditSelectedAreaAll(BOOL);
   BOOL GetEditMultipleArea();
   void SetEditMultipleArea(BOOL);
   short GetPrintMode();
   void SetPrintMode(short);
   short GetPrintCloseIdle();
   void SetPrintCloseIdle(short);
   short GetPrintExtent();
   void SetPrintExtent(short);
   BOOL GetPrintTerminator();
   void SetPrintTerminator(BOOL);
   BOOL GetPrintEmulateANSI();
   void SetPrintEmulateANSI(BOOL);
   BOOL GetPrintBackground();
   void SetPrintBackground(BOOL);
   BOOL GetPrintColors();
   void SetPrintColors(BOOL);
   BOOL GetPrintReverseBlackWhite();
   void SetPrintReverseBlackWhite(BOOL);
   BOOL GetPrintUseBitmap();
   void SetPrintUseBitmap(BOOL);
   BOOL GetPrintAutoFontSelect();
   void SetPrintAutoFontSelect(BOOL);
   CString GetPrintFont();
   void SetPrintFont(LPCTSTR);
   CString GetPrintFontStyle();
   void SetPrintFontStyle(LPCTSTR);
   CString GetPrintFontSize();
   void SetPrintFontSize(LPCTSTR);
   LPDISPATCH GetApplication();
   LPDISPATCH GetParent();
   BOOL GetInhibitHandshake();
   void SetInhibitHandshake(BOOL);
   BOOL GetInhibitDC2();
   void SetInhibitDC2(BOOL);
   BOOL GetEnqAck();
   void SetEnqAck(BOOL);
   BOOL GetUseHostPrompt();
   void SetUseHostPrompt(BOOL);
   CString GetPrompt();
   void SetPrompt(LPCTSTR);
   short GetTransmissionModes();
   void SetTransmissionModes(short);
   short GetTransferTrigger();
   void SetTransferTrigger(short);
   short GetTransferStartColumn();
   void SetTransferStartColumn(short);
   BOOL GetTransferTransmitFunctions();
   void SetTransferTransmitFunctions(BOOL);
   CString GetTransferTerminator();
   void SetTransferTerminator(LPCTSTR);
   short GetTransferBlockUnit();
   void SetTransferBlockUnit(short);
   short GetMemorySize();
   void SetMemorySize(short);
   BOOL GetMessageBell();
   void SetMessageBell(BOOL);
   BOOL GetDisplayFunctions();
   void SetDisplayFunctions(BOOL);
   BOOL GetLockMemory();
   void SetLockMemory(BOOL);
   short GetLeftMargin();
   void SetLeftMargin(short);
   short GetRightMargin();
   void SetRightMargin(short);
   BOOL GetTabsGenerateSpaces();
   void SetTabsGenerateSpaces(BOOL);
   CString GetTabColumns();
   void SetTabColumns(LPCTSTR);
   short GetReturnKey();
   void SetReturnKey(short);
   short GetCREffect();
   void SetCREffect(short);
   short GetNumericPadEnter();
   void SetNumericPadEnter(short);
   BOOL GetTypeahead();
   void SetTypeahead(BOOL);
   BOOL GetCapsLock();
   void SetCapsLock(BOOL);
   BOOL GetSpaceOverwrite();
   void SetSpaceOverwrite(BOOL);
   short GetPrintLog();
   void SetPrintLog(short);
   short GetPrintPrint();
   void SetPrintPrint(short);
   BOOL GetFormFormatMode();
   void SetFormFormatMode(BOOL);
   short GetFormTransmitFields();
   void SetFormTransmitFields(short);
   CString GetFormFieldSeparator();
   void SetFormFieldSeparator(LPCTSTR);
   short GetFormBufferSize();
   void SetFormBufferSize(short);
   short GetFormDecimalType();
   void SetFormDecimalType(short);
   short GetFormDecimalDigits();
   void SetFormDecimalDigits(short);
   BOOL GetTektronixOverwrite();
   void SetTektronixOverwrite(BOOL);

// Operations
public:
};
/////////////////////////////////////////////////////////////////////////////
// MacroWait wrapper class

class MacroWait : public COleDispatchDriver
{
public:
   MacroWait() {}      // Calls COleDispatchDriver default constructor
   MacroWait(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
   MacroWait(const MacroWait& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:
   LPDISPATCH GetApplication();
   LPDISPATCH GetParent();
   BOOL GetChanged();
   BOOL GetEnabled();
   void SetEnabled(BOOL);
   short GetMacroEnd();

// Operations
public:
   BOOL Wait(const VARIANT& Timeout);
   void Clear();
   short _StartWait(LPDISPATCH pServer, long DispidNewEvent);
   void _StopWait();
   long _GetBase(long SessionID);
   void StartNotify(long hWnd, long wMsg, long wParam, long lParam, long wMsgFail, long wParamFail, long lParamFail);
   void StopNotify();
   void StartCallback(LPDISPATCH pDispatch);
   void StopCallback();
   void Reset();
};
/////////////////////////////////////////////////////////////////////////////
// _Application wrapper class

class _Application : public COleDispatchDriver
{
public:
   _Application() {}      // Calls COleDispatchDriver default constructor
   _Application(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
   _Application(const _Application& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
   LPDISPATCH _Waits(LPDISPATCH pServer, BOOL Enabled);
   LPDISPATCH _Session();
   LPDISPATCH _Restart();
   LPDISPATCH _Close();
};
/////////////////////////////////////////////////////////////////////////////
// _ServerWait wrapper class

class _ServerWait : public COleDispatchDriver
{
public:
   _ServerWait() {}      // Calls COleDispatchDriver default constructor
   _ServerWait(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
   _ServerWait(const _ServerWait& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:
   LPDISPATCH GetParent();

// Operations
public:
   BOOL Wait(const VARIANT& Timeout);
   long _GetServerBase();
   void _NewEvent(long iSession, short iClient);
};
/////////////////////////////////////////////////////////////////////////////
// _ServerWaits wrapper class

class _ServerWaits : public COleDispatchDriver
{
public:
   _ServerWaits() {}      // Calls COleDispatchDriver default constructor
   _ServerWaits(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
   _ServerWaits(const _ServerWaits& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:
   short GetCount();
   long GetChanged();
   BOOL GetEnabled();
   void SetEnabled(BOOL);

// Operations
public:
   long Add(LPDISPATCH Wait);
   LPDISPATCH Item(long ID);
   void Remove(long ID);
   void RemoveAll();
   long Wait(const VARIANT& Timeout);
   void Clear();
   void Reset();
   void StartNotify(long hWnd, long wMsg, long wParam, long lParam, long wMsgFail, long wParamFail, long lParamFail);
   void StopNotify();
   void StartCallback(LPDISPATCH pDispatch);
   void StopCallback();
   long _GetServerBase();
   void _NewEvent(long iSession, short iClient);
};

} // namespace KeaDispatch

#endif // !defined(_KEAVT_H__INCLUDED_)
