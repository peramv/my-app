// Machine generated IDispatch wrapper class(es) created with ClassWizard

#include "stdafx.h"
#include "r2700ex.h"

#ifdef _DEBUG
   #define new DEBUG_NEW
   #undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

namespace ReflectionDispatch
{


/////////////////////////////////////////////////////////////////////////////
// Reflection2 properties

/////////////////////////////////////////////////////////////////////////////
// Reflection2 operations

   void Reflection2::AbortTransfer()
   {
      InvokeHelper(0x60020000, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
   }

   void Reflection2::Break()
   {
      InvokeHelper(0x60020001, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
   }

   void Reflection2::CancelTransfer()
   {
      InvokeHelper(0x60020002, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
   }

   void Reflection2::Clear(long ClearWhat)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x60020003, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
                   ClearWhat);
   }

   void Reflection2::CloseAllConnections()
   {
      InvokeHelper(0x60020004, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
   }

   long Reflection2::CompileScript(LPCTSTR ScriptName)
   {
      long result;
      static BYTE parms[] =
      VTS_BSTR;
      InvokeHelper(0x60020005, DISPATCH_METHOD, VT_I4, (void*)&result, parms,
                   ScriptName);
      return(result);
   }

   void Reflection2::Connect(const VARIANT& ConnectionName)
   {
      static BYTE parms[] =
      VTS_VARIANT;
      InvokeHelper(0x60020006, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
                   &ConnectionName);
   }

   CString Reflection2::ConnectionSetting(LPCTSTR Setting)
   {
      CString result;
      static BYTE parms[] =
      VTS_BSTR;
      InvokeHelper(0x60020007, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms,
                   Setting);
      return(result);
   }

   void Reflection2::Copy(long CopyWhat, const VARIANT& Format)
   {
      static BYTE parms[] =
      VTS_I4 VTS_VARIANT;
      InvokeHelper(0x60020008, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
                   CopyWhat, &Format);
   }

   void Reflection2::DDEExecute(long ConversationID, LPCTSTR Command)
   {
      static BYTE parms[] =
      VTS_I4 VTS_BSTR;
      InvokeHelper(0x60020009, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
                   ConversationID, Command);
   }

   long Reflection2::DDEInitiate(LPCTSTR AppName, LPCTSTR TopicName)
   {
      long result;
      static BYTE parms[] =
      VTS_BSTR VTS_BSTR;
      InvokeHelper(0x6002000a, DISPATCH_METHOD, VT_I4, (void*)&result, parms,
                   AppName, TopicName);
      return(result);
   }

   void Reflection2::DDEPoke(long ConversationID, LPCTSTR ItemName, LPCTSTR Value)
   {
      static BYTE parms[] =
      VTS_I4 VTS_BSTR VTS_BSTR;
      InvokeHelper(0x6002000b, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
                   ConversationID, ItemName, Value);
   }

   CString Reflection2::DDEQueryServerTopics(LPCTSTR AppName, LPCTSTR TopicName)
   {
      CString result;
      static BYTE parms[] =
      VTS_BSTR VTS_BSTR;
      InvokeHelper(0x6002000c, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms,
                   AppName, TopicName);
      return(result);
   }

   CString Reflection2::DDERequest(long ConversationID, LPCTSTR ItemName)
   {
      CString result;
      static BYTE parms[] =
      VTS_I4 VTS_BSTR;
      InvokeHelper(0x6002000d, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms,
                   ConversationID, ItemName);
      return(result);
   }

   void Reflection2::DDETerminate(long ConversationID)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x6002000e, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
                   ConversationID);
   }

   void Reflection2::DDETerminateAll()
   {
      InvokeHelper(0x6002000f, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
   }

   void Reflection2::Dial(LPCTSTR PhoneNumber, const VARIANT& Description, const VARIANT& InitString, const VARIANT& AnswerTimeout, const VARIANT& RetryTimes, const VARIANT& RetryInterval, const VARIANT& SpeakerMode, const VARIANT& SpeakerVolume, 
                          const VARIANT& SpeakerOffAfterRedial, const VARIANT& IgnoreModemErrors)
   {
      static BYTE parms[] =
      VTS_BSTR VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT;
      InvokeHelper(0x60020010, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
                   PhoneNumber, &Description, &InitString, &AnswerTimeout, &RetryTimes, &RetryInterval, &SpeakerMode, &SpeakerVolume, &SpeakerOffAfterRedial, &IgnoreModemErrors);
   }

   void Reflection2::Disconnect()
   {
      InvokeHelper(0x60020011, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
   }

   void Reflection2::Display(LPCTSTR String, const VARIANT& Options)
   {
      static BYTE parms[] =
      VTS_BSTR VTS_VARIANT;
      InvokeHelper(0x60020012, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
                   String, &Options);
   }

   void Reflection2::DisplayFile(LPCTSTR Filename, const VARIANT& Options)
   {
      static BYTE parms[] =
      VTS_BSTR VTS_VARIANT;
      InvokeHelper(0x60020013, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
                   Filename, &Options);
   }

   void Reflection2::DropDTR()
   {
      InvokeHelper(0x60020014, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
   }

   void Reflection2::EditScript(LPCTSTR ScriptName)
   {
      static BYTE parms[] =
      VTS_BSTR;
      InvokeHelper(0x60020015, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
                   ScriptName);
   }

   CString Reflection2::EvaluateRCLExpression(LPCTSTR Expression, const VARIANT& Options)
   {
      CString result;
      static BYTE parms[] =
      VTS_BSTR VTS_VARIANT;
      InvokeHelper(0x60020016, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms,
                   Expression, &Options);
      return(result);
   }

   void Reflection2::ExecuteBuiltInFunction(LPCTSTR FunctionName)
   {
      static BYTE parms[] =
      VTS_BSTR;
      InvokeHelper(0x60020017, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
                   FunctionName);
   }

   void Reflection2::ExecuteRCLCommand(LPCTSTR Command, const VARIANT& Options)
   {
      static BYTE parms[] =
      VTS_BSTR VTS_VARIANT;
      InvokeHelper(0x60020018, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
                   Command, &Options);
   }

   BOOL Reflection2::FindText(LPCTSTR SearchFor, long StartRow, long StartColumn, const VARIANT& Options)
   {
      BOOL result;
      static BYTE parms[] =
      VTS_BSTR VTS_I4 VTS_I4 VTS_VARIANT;
      InvokeHelper(0x60020019, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
                   SearchFor, StartRow, StartColumn, &Options);
      return(result);
   }

   void Reflection2::FlushPrinter()
   {
      InvokeHelper(0x6002001a, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
   }

   CString Reflection2::GetClipboardText()
   {
      CString result;
      InvokeHelper(0x6002001b, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
      return(result);
   }

   BOOL Reflection2::GetCommandGroupProfile(long CmdGroup)
   {
      BOOL result;
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x6002001c, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
                   CmdGroup);
      return(result);
   }

   BOOL Reflection2::GetCommandProfile(LPCTSTR CmdName)
   {
      BOOL result;
      static BYTE parms[] =
      VTS_BSTR;
      InvokeHelper(0x6002001d, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
                   CmdName);
      return(result);
   }

   CString Reflection2::GetText(long StartRow, long StartColumn, long EndRow, long EndColumn, const VARIANT& Options)
   {
      CString result;
      static BYTE parms[] =
      VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_VARIANT;
      InvokeHelper(0x6002001e, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms,
                   StartRow, StartColumn, EndRow, EndColumn, &Options);
      return(result);
   }

   long Reflection2::GetKeyMapCommandType(long Modifiers, LPCTSTR Key)
   {
      long result;
      static BYTE parms[] =
      VTS_I4 VTS_BSTR;
      InvokeHelper(0x6002001f, DISPATCH_METHOD, VT_I4, (void*)&result, parms,
                   Modifiers, Key);
      return(result);
   }

   CString Reflection2::GetKeyMapCommands(long Modifiers, LPCTSTR Key)
   {
      CString result;
      static BYTE parms[] =
      VTS_I4 VTS_BSTR;
      InvokeHelper(0x60020020, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms,
                   Modifiers, Key);
      return(result);
   }

   CString Reflection2::GetOpenFilename(const VARIANT& FileFilter, const VARIANT& FilterIndex, const VARIANT& Title, const VARIANT& ButtonText)
   {
      CString result;
      static BYTE parms[] =
      VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT;
      InvokeHelper(0x60020021, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms,
                   &FileFilter, &FilterIndex, &Title, &ButtonText);
      return(result);
   }

   CString Reflection2::GetSaveAsFilename(const VARIANT& InitialFilename, const VARIANT& FileFilter, const VARIANT& FilterIndex, const VARIANT& Title, const VARIANT& ButtonText)
   {
      CString result;
      static BYTE parms[] =
      VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT;
      InvokeHelper(0x60020022, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms,
                   &InitialFilename, &FileFilter, &FilterIndex, &Title, &ButtonText);
      return(result);
   }

   long Reflection2::GetSerialStatistics(long WhichStatistic)
   {
      long result;
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x60020023, DISPATCH_METHOD, VT_I4, (void*)&result, parms,
                   WhichStatistic);
      return(result);
   }

   void Reflection2::Hangup()
   {
      InvokeHelper(0x60020024, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
   }

   void Reflection2::Help(const VARIANT& HelpTopic, const VARIANT& HelpFile)
   {
      static BYTE parms[] =
      VTS_VARIANT VTS_VARIANT;
      InvokeHelper(0x60020025, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
                   &HelpTopic, &HelpFile);
   }

   CString Reflection2::InputBox(LPCTSTR Prompt, const VARIANT& Title, const VARIANT& Default)
   {
      CString result;
      static BYTE parms[] =
      VTS_BSTR VTS_VARIANT VTS_VARIANT;
      InvokeHelper(0x60020026, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms,
                   Prompt, &Title, &Default);
      return(result);
   }

   void Reflection2::KermitReceiveFile(LPCTSTR LocalFile, LPCTSTR RemoteFile, const VARIANT& TransferType, const VARIANT& IfFileExists)
   {
      static BYTE parms[] =
      VTS_BSTR VTS_BSTR VTS_VARIANT VTS_VARIANT;
      InvokeHelper(0x60020027, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
                   LocalFile, RemoteFile, &TransferType, &IfFileExists);
   }

   void Reflection2::KermitSendFile(LPCTSTR LocalFile, LPCTSTR RemoteFile, const VARIANT& TransferType)
   {
      static BYTE parms[] =
      VTS_BSTR VTS_BSTR VTS_VARIANT;
      InvokeHelper(0x60020028, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
                   LocalFile, RemoteFile, &TransferType);
   }

   void Reflection2::KermitStartServer()
   {
      InvokeHelper(0x60020029, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
   }

   void Reflection2::KermitStopServer(const VARIANT& Logoff)
   {
      static BYTE parms[] =
      VTS_VARIANT;
      InvokeHelper(0x6002002a, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
                   &Logoff);
   }

   void Reflection2::LockProfile(BOOL AllowUnlock, const VARIANT& Password)
   {
      static BYTE parms[] =
      VTS_BOOL VTS_VARIANT;
      InvokeHelper(0x6002002b, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
                   AllowUnlock, &Password);
   }

   long Reflection2::MsgBox(LPCTSTR Message, const VARIANT& Type, const VARIANT& Caption)
   {
      long result;
      static BYTE parms[] =
      VTS_BSTR VTS_VARIANT VTS_VARIANT;
      InvokeHelper(0x6002002c, DISPATCH_METHOD, VT_I4, (void*)&result, parms,
                   Message, &Type, &Caption);
      return(result);
   }

   void Reflection2::NewSession(const VARIANT& SessionType, const VARIANT& SettingsFile)
   {
      static BYTE parms[] =
      VTS_VARIANT VTS_VARIANT;
      InvokeHelper(0x6002002d, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
                   &SessionType, &SettingsFile);
   }

   void Reflection2::OpenSettings(LPCTSTR Filename, const VARIANT& Type)
   {
      static BYTE parms[] =
      VTS_BSTR VTS_VARIANT;
      InvokeHelper(0x6002002e, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
                   Filename, &Type);
   }

   CString Reflection2::PasswordBox(LPCTSTR Prompt, const VARIANT& Title, const VARIANT& Default)
   {
      CString result;
      static BYTE parms[] =
      VTS_BSTR VTS_VARIANT VTS_VARIANT;
      InvokeHelper(0x6002002f, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms,
                   Prompt, &Title, &Default);
      return(result);
   }

   void Reflection2::Paste()
   {
      InvokeHelper(0x60020030, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
   }

   void Reflection2::Print(long Range, const VARIANT& Copies)
   {
      static BYTE parms[] =
      VTS_I4 VTS_VARIANT;
      InvokeHelper(0x60020031, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
                   Range, &Copies);
   }

   void Reflection2::PrintFile(LPCTSTR Filename)
   {
      static BYTE parms[] =
      VTS_BSTR;
      InvokeHelper(0x60020032, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
                   Filename);
   }

   void Reflection2::PrintString(LPCTSTR String)
   {
      static BYTE parms[] =
      VTS_BSTR;
      InvokeHelper(0x60020033, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
                   String);
   }

   void Reflection2::Quit()
   {
      InvokeHelper(0x60020034, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
   }

   CString Reflection2::ReadChars(long Count, const VARIANT& Timeout, const VARIANT& Options)
   {
      CString result;
      static BYTE parms[] =
      VTS_I4 VTS_VARIANT VTS_VARIANT;
      InvokeHelper(0x60020035, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms,
                   Count, &Timeout, &Options);
      return(result);
   }

   CString Reflection2::ReadLine(const VARIANT& Timeout, const VARIANT& Options, VARIANT* SawEndOfLine)
   {
      CString result;
      static BYTE parms[] =
      VTS_VARIANT VTS_VARIANT VTS_PVARIANT;
      InvokeHelper(0x60020036, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms,
                   &Timeout, &Options, SawEndOfLine);
      return(result);
   }

   CString Reflection2::ReadUntil(LPCTSTR UntilChars, const VARIANT& Timeout, const VARIANT& Options, VARIANT* WhichTerminator)
   {
      CString result;
      static BYTE parms[] =
      VTS_BSTR VTS_VARIANT VTS_VARIANT VTS_PVARIANT;
      InvokeHelper(0x60020037, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms,
                   UntilChars, &Timeout, &Options, WhichTerminator);
      return(result);
   }

   void Reflection2::ResetTerminal(long ResetMode)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x60020038, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
                   ResetMode);
   }

   void Reflection2::RestoreDefaults(long SettingType)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x60020039, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
                   SettingType);
   }

   void Reflection2::ResumeConnection(long ConnectionID)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x6002003a, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
                   ConnectionID);
   }

   void Reflection2::RunScript(LPCTSTR ScriptName, const VARIANT& ScriptArguments)
   {
      static BYTE parms[] =
      VTS_BSTR VTS_VARIANT;
      InvokeHelper(0x6002003b, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
                   ScriptName, &ScriptArguments);
   }

   void Reflection2::SaveDisplayMemory(LPCTSTR Filename, const VARIANT& IfFileExists, const VARIANT& Options)
   {
      static BYTE parms[] =
      VTS_BSTR VTS_VARIANT VTS_VARIANT;
      InvokeHelper(0x6002003c, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
                   Filename, &IfFileExists, &Options);
   }

   void Reflection2::SaveSettings(LPCTSTR Filename, const VARIANT& Type, const VARIANT& IfFileExists)
   {
      static BYTE parms[] =
      VTS_BSTR VTS_VARIANT VTS_VARIANT;
      InvokeHelper(0x6002003d, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
                   Filename, &Type, &IfFileExists);
   }

   void Reflection2::SetClipboardText(LPCTSTR ClipboardText)
   {
      static BYTE parms[] =
      VTS_BSTR;
      InvokeHelper(0x6002003e, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
                   ClipboardText);
   }

   void Reflection2::SetCommandGroupProfile(long CmdGroup, BOOL IsEnabled)
   {
      static BYTE parms[] =
      VTS_I4 VTS_BOOL;
      InvokeHelper(0x6002003f, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
                   CmdGroup, IsEnabled);
   }

   void Reflection2::SetCommandProfile(LPCTSTR CmdName, BOOL IsEnabled)
   {
      static BYTE parms[] =
      VTS_BSTR VTS_BOOL;
      InvokeHelper(0x60020040, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
                   CmdName, IsEnabled);
   }

   void Reflection2::SetKeyMap(long Modifiers, LPCTSTR Key, long CommandType, LPCTSTR Commands, const VARIANT& CommandArguments)
   {
      static BYTE parms[] =
      VTS_I4 VTS_BSTR VTS_I4 VTS_BSTR VTS_VARIANT;
      InvokeHelper(0x60020041, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
                   Modifiers, Key, CommandType, Commands, &CommandArguments);
   }

   void Reflection2::SetScanCodeName(long ScanType, long ScanCode, LPCTSTR ScanName)
   {
      static BYTE parms[] =
      VTS_I4 VTS_I4 VTS_BSTR;
      InvokeHelper(0x60020042, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
                   ScanType, ScanCode, ScanName);
   }

   void Reflection2::SelectText(long StartRow, long StartColumn, long EndRow, long EndColumn, const VARIANT& SelectionType)
   {
      static BYTE parms[] =
      VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_VARIANT;
      InvokeHelper(0x60020043, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
                   StartRow, StartColumn, EndRow, EndColumn, &SelectionType);
   }

   void Reflection2::StartRecording()
   {
      InvokeHelper(0x60020044, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
   }

   void Reflection2::StartTrace(LPCTSTR Filename, const VARIANT& IfFileExists, const VARIANT& TraceFormat)
   {
      static BYTE parms[] =
      VTS_BSTR VTS_VARIANT VTS_VARIANT;
      InvokeHelper(0x60020045, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
                   Filename, &IfFileExists, &TraceFormat);
   }

   void Reflection2::StopRecording(LPCTSTR Filename, long Target, const VARIANT& IfFileExists)
   {
      static BYTE parms[] =
      VTS_BSTR VTS_I4 VTS_VARIANT;
      InvokeHelper(0x60020046, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
                   Filename, Target, &IfFileExists);
   }

   void Reflection2::StopScript()
   {
      InvokeHelper(0x60020047, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
   }

   void Reflection2::StopTrace()
   {
      InvokeHelper(0x60020048, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
   }

   long Reflection2::SuspendConnection()
   {
      long result;
      InvokeHelper(0x60020049, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::Transmit(LPCTSTR String, const VARIANT& Options)
   {
      static BYTE parms[] =
      VTS_BSTR VTS_VARIANT;
      InvokeHelper(0x6002004a, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
                   String, &Options);
   }

   void Reflection2::TransmitFile(LPCTSTR Filename, const VARIANT& PauseTime, const VARIANT& PromptChar, const VARIANT& Options)
   {
      static BYTE parms[] =
      VTS_BSTR VTS_VARIANT VTS_VARIANT VTS_VARIANT;
      InvokeHelper(0x6002004b, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
                   Filename, &PauseTime, &PromptChar, &Options);
   }

   void Reflection2::TransmitTerminalKey(long KeyID)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x6002004c, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
                   KeyID);
   }

   BOOL Reflection2::UnlockProfile(LPCTSTR Password)
   {
      BOOL result;
      static BYTE parms[] =
      VTS_BSTR;
      InvokeHelper(0x6002004d, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
                   Password);
      return(result);
   }

   void Reflection2::Wait(const VARIANT& HowLong, const VARIANT& Options)
   {
      static BYTE parms[] =
      VTS_VARIANT VTS_VARIANT;
      InvokeHelper(0x6002004e, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
                   &HowLong, &Options);
   }

   void Reflection2::WaitForCall(const VARIANT& Description, const VARIANT& InitString)
   {
      static BYTE parms[] =
      VTS_VARIANT VTS_VARIANT;
      InvokeHelper(0x6002004f, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
                   &Description, &InitString);
   }

   BOOL Reflection2::WaitForHostTrigger(const VARIANT& Timeout, const VARIANT& Options)
   {
      BOOL result;
      static BYTE parms[] =
      VTS_VARIANT VTS_VARIANT;
      InvokeHelper(0x60020050, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
                   &Timeout, &Options);
      return(result);
   }

   BOOL Reflection2::WaitForSilence(const VARIANT& SilenceTime, const VARIANT& Timeout, const VARIANT& Options)
   {
      BOOL result;
      static BYTE parms[] =
      VTS_VARIANT VTS_VARIANT VTS_VARIANT;
      InvokeHelper(0x60020051, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
                   &SilenceTime, &Timeout, &Options);
      return(result);
   }

   BOOL Reflection2::WaitForString(LPCTSTR String, const VARIANT& Timeout, const VARIANT& Options)
   {
      BOOL result;
      static BYTE parms[] =
      VTS_BSTR VTS_VARIANT VTS_VARIANT;
      InvokeHelper(0x60020052, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
                   String, &Timeout, &Options);
      return(result);
   }

   void Reflection2::WaitUntil(DATE DateTime, const VARIANT& Options)
   {
      static BYTE parms[] =
      VTS_DATE VTS_VARIANT;
      InvokeHelper(0x60020054, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
                   DateTime, &Options);
   }

   void Reflection2::WRQReceiveFile(LPCTSTR LocalFile, LPCTSTR RemoteFile, const VARIANT& TransferType, const VARIANT& IfFileExists, const VARIANT& Before, const VARIANT& Since, const VARIANT& Exclude)
   {
      static BYTE parms[] =
      VTS_BSTR VTS_BSTR VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT;
      InvokeHelper(0x60020055, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
                   LocalFile, RemoteFile, &TransferType, &IfFileExists, &Before, &Since, &Exclude);
   }

   void Reflection2::WRQSendFile(LPCTSTR LocalFile, LPCTSTR RemoteFile, const VARIANT& TransferType, const VARIANT& IfFileExists, const VARIANT& Before, const VARIANT& Since, const VARIANT& Exclude, const VARIANT& Attributes)
   {
      static BYTE parms[] =
      VTS_BSTR VTS_BSTR VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT;
      InvokeHelper(0x60020056, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
                   LocalFile, RemoteFile, &TransferType, &IfFileExists, &Before, &Since, &Exclude, &Attributes);
   }

   void Reflection2::WRQStartServer()
   {
      InvokeHelper(0x60020057, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
   }

   void Reflection2::WRQStopServer()
   {
      InvokeHelper(0x60020058, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
   }

   void Reflection2::XmodemReceiveFile(LPCTSTR LocalFile, const VARIANT& TransferType, const VARIANT& IfFileExists)
   {
      static BYTE parms[] =
      VTS_BSTR VTS_VARIANT VTS_VARIANT;
      InvokeHelper(0x60020059, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
                   LocalFile, &TransferType, &IfFileExists);
   }

   void Reflection2::XmodemSendFile(LPCTSTR LocalFile, const VARIANT& TransferType)
   {
      static BYTE parms[] =
      VTS_BSTR VTS_VARIANT;
      InvokeHelper(0x6002005a, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
                   LocalFile, &TransferType);
   }

   void Reflection2::ZmodemReceiveFile(LPCTSTR LocalFile, const VARIANT& RemoteFile, const VARIANT& TransferType, const VARIANT& IfFileExists)
   {
      static BYTE parms[] =
      VTS_BSTR VTS_VARIANT VTS_VARIANT VTS_VARIANT;
      InvokeHelper(0x6002005b, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
                   LocalFile, &RemoteFile, &TransferType, &IfFileExists);
   }

   void Reflection2::ZmodemSendFile(LPCTSTR LocalFile, LPCTSTR RemoteFile, const VARIANT& TransferType)
   {
      static BYTE parms[] =
      VTS_BSTR VTS_BSTR VTS_VARIANT;
      InvokeHelper(0x6002005c, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
                   LocalFile, RemoteFile, &TransferType);
   }

   BOOL Reflection2::GetAllowScriptInterrupt()
   {
      BOOL result;
      InvokeHelper(0x6002005d, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetAllowScriptInterrupt(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x6002005d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   long Reflection2::GetAnsiScreenColor()
   {
      long result;
      InvokeHelper(0x6002005f, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetAnsiScreenColor(long nNewValue)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x6002005f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   nNewValue);
   }

   CString Reflection2::GetAnswerback()
   {
      CString result;
      InvokeHelper(0x60020061, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetAnswerback(LPCTSTR lpszNewValue)
   {
      static BYTE parms[] =
      VTS_BSTR;
      InvokeHelper(0x60020061, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   lpszNewValue);
   }

   VARIANT Reflection2::GetApplication()
   {
      VARIANT result;
      InvokeHelper(0x60020063, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetApplication(const VARIANT& newValue)
   {
      static BYTE parms[] =
      VTS_VARIANT;
      InvokeHelper(0x60020063, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   &newValue);
   }

   BOOL Reflection2::GetAutoAnswerback()
   {
      BOOL result;
      InvokeHelper(0x60020065, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetAutoAnswerback(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x60020065, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   BOOL Reflection2::GetAutoFontSize()
   {
      BOOL result;
      InvokeHelper(0x60020067, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetAutoFontSize(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x60020067, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   BOOL Reflection2::GetAutoFormFeed()
   {
      BOOL result;
      InvokeHelper(0x60020069, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetAutoFormFeed(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x60020069, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   BOOL Reflection2::GetAutoLineFeed()
   {
      BOOL result;
      InvokeHelper(0x6002006b, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetAutoLineFeed(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x6002006b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   BOOL Reflection2::GetAutoRepeat()
   {
      BOOL result;
      InvokeHelper(0x6002006d, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetAutoRepeat(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x6002006d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   BOOL Reflection2::GetBell()
   {
      BOOL result;
      InvokeHelper(0x6002006f, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetBell(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x6002006f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   BOOL Reflection2::GetBlinkCharacters()
   {
      BOOL result;
      InvokeHelper(0x60020071, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetBlinkCharacters(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x60020071, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   CString Reflection2::GetBlockTerminator()
   {
      CString result;
      InvokeHelper(0x60020073, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetBlockTerminator(LPCTSTR lpszNewValue)
   {
      static BYTE parms[] =
      VTS_BSTR;
      InvokeHelper(0x60020073, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   lpszNewValue);
   }

   BOOL Reflection2::GetBoldCharacters()
   {
      BOOL result;
      InvokeHelper(0x60020075, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetBoldCharacters(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x60020075, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   BOOL Reflection2::GetBreakEnabled()
   {
      BOOL result;
      InvokeHelper(0x60020077, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetBreakEnabled(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x60020077, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   long Reflection2::GetBreakLength()
   {
      long result;
      InvokeHelper(0x60020079, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetBreakLength(long nNewValue)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x60020079, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   nNewValue);
   }

   BOOL Reflection2::GetBypassPrinterDriver()
   {
      BOOL result;
      InvokeHelper(0x6002007b, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetBypassPrinterDriver(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x6002007b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   BOOL Reflection2::GetCapsLock()
   {
      BOOL result;
      InvokeHelper(0x6002007d, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetCapsLock(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x6002007d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   CString Reflection2::GetCaption()
   {
      CString result;
      InvokeHelper(0x6002007f, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetCaption(LPCTSTR lpszNewValue)
   {
      static BYTE parms[] =
      VTS_BSTR;
      InvokeHelper(0x6002007f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   lpszNewValue);
   }

   BOOL Reflection2::GetClosePrinterManually()
   {
      BOOL result;
      InvokeHelper(0x60020081, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetClosePrinterManually(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x60020081, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   long Reflection2::GetCodePage()
   {
      long result;
      InvokeHelper(0x60020083, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetCodePage(long nNewValue)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x60020083, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   nNewValue);
   }

   long Reflection2::GetColumnsPerScroll()
   {
      long result;
      InvokeHelper(0x60020085, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetColumnsPerScroll(long nNewValue)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x60020085, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   nNewValue);
   }

   BOOL Reflection2::GetCompressBlankLines()
   {
      BOOL result;
      InvokeHelper(0x60020087, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetCompressBlankLines(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x60020087, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   BOOL Reflection2::GetConnected()
   {
      BOOL result;
      InvokeHelper(0x60020089, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetConnected(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x60020089, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   long Reflection2::GetConnectionID()
   {
      long result;
      InvokeHelper(0x6002008b, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetConnectionID(long nNewValue)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x6002008b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   nNewValue);
   }

   long Reflection2::GetConnectionIndicator()
   {
      long result;
      InvokeHelper(0x6002008d, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetConnectionIndicator(long nNewValue)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x6002008d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   nNewValue);
   }

   long Reflection2::GetConnectionError()
   {
      long result;
      InvokeHelper(0x6002008f, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetConnectionError(long nNewValue)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x6002008f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   nNewValue);
   }

   CString Reflection2::GetConnectionErrorMessage()
   {
      CString result;
      InvokeHelper(0x60020091, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetConnectionErrorMessage(LPCTSTR lpszNewValue)
   {
      static BYTE parms[] =
      VTS_BSTR;
      InvokeHelper(0x60020091, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   lpszNewValue);
   }

   CString Reflection2::GetConnectionSettings()
   {
      CString result;
      InvokeHelper(0x60020093, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetConnectionSettings(LPCTSTR lpszNewValue)
   {
      static BYTE parms[] =
      VTS_BSTR;
      InvokeHelper(0x60020093, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   lpszNewValue);
   }

   CString Reflection2::GetConnectionType()
   {
      CString result;
      InvokeHelper(0x60020095, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetConnectionType(LPCTSTR lpszNewValue)
   {
      static BYTE parms[] =
      VTS_BSTR;
      InvokeHelper(0x60020095, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   lpszNewValue);
   }

   BOOL Reflection2::GetConvertEOLToSeparator()
   {
      BOOL result;
      InvokeHelper(0x60020097, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetConvertEOLToSeparator(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x60020097, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   BOOL Reflection2::GetConvertMCSToNRC()
   {
      BOOL result;
      InvokeHelper(0x60020099, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetConvertMCSToNRC(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x60020099, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   BOOL Reflection2::GetConvertNRCToMCS()
   {
      BOOL result;
      InvokeHelper(0x6002009b, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetConvertNRCToMCS(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x6002009b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   BOOL Reflection2::GetConvertSeparatorToEOL()
   {
      BOOL result;
      InvokeHelper(0x6002009d, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetConvertSeparatorToEOL(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x6002009d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   BOOL Reflection2::GetCursorBlink()
   {
      BOOL result;
      InvokeHelper(0x6002009f, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetCursorBlink(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x6002009f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   long Reflection2::GetCursorColumn()
   {
      long result;
      InvokeHelper(0x600200a1, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetCursorColumn(long nNewValue)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x600200a1, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   nNewValue);
   }

   long Reflection2::GetCursorRow()
   {
      long result;
      InvokeHelper(0x600200a3, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetCursorRow(long nNewValue)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x600200a3, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   nNewValue);
   }

   long Reflection2::GetCursorShape()
   {
      long result;
      InvokeHelper(0x600200a5, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetCursorShape(long nNewValue)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x600200a5, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   nNewValue);
   }

   BOOL Reflection2::GetCursorVisible()
   {
      BOOL result;
      InvokeHelper(0x600200a7, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetCursorVisible(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x600200a7, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   long Reflection2::GetDAResponse()
   {
      long result;
      InvokeHelper(0x600200a9, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetDAResponse(long nNewValue)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x600200a9, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   nNewValue);
   }

   BOOL Reflection2::GetDcd()
   {
      BOOL result;
      InvokeHelper(0x600200ab, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetDcd(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x600200ab, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   BOOL Reflection2::GetDDEServerEnable()
   {
      BOOL result;
      InvokeHelper(0x600200ad, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetDDEServerEnable(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x600200ad, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   CString Reflection2::GetDDEServerName()
   {
      CString result;
      InvokeHelper(0x600200af, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetDDEServerName(LPCTSTR lpszNewValue)
   {
      static BYTE parms[] =
      VTS_BSTR;
      InvokeHelper(0x600200af, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   lpszNewValue);
   }

   long Reflection2::GetDDETimeout()
   {
      long result;
      InvokeHelper(0x600200b1, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetDDETimeout(long nNewValue)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x600200b1, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   nNewValue);
   }

   CString Reflection2::GetDefaultPrinter()
   {
      CString result;
      InvokeHelper(0x600200b3, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetDefaultPrinter(LPCTSTR lpszNewValue)
   {
      static BYTE parms[] =
      VTS_BSTR;
      InvokeHelper(0x600200b3, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   lpszNewValue);
   }

   long Reflection2::GetDefaultScriptLanguage()
   {
      long result;
      InvokeHelper(0x600200b5, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetDefaultScriptLanguage(long nNewValue)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x600200b5, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   nNewValue);
   }

   BOOL Reflection2::GetDeleteTrailingSpaces()
   {
      BOOL result;
      InvokeHelper(0x600200b7, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetDeleteTrailingSpaces(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x600200b7, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   long Reflection2::GetDisplayColumns()
   {
      long result;
      InvokeHelper(0x600200b9, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetDisplayColumns(long nNewValue)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x600200b9, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   nNewValue);
   }

   long Reflection2::GetDisplayMemoryBlocks()
   {
      long result;
      InvokeHelper(0x600200bb, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetDisplayMemoryBlocks(long nNewValue)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x600200bb, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   nNewValue);
   }

   long Reflection2::GetDisplayMemoryTopRow()
   {
      long result;
      InvokeHelper(0x600200bd, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetDisplayMemoryTopRow(long nNewValue)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x600200bd, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   nNewValue);
   }

   long Reflection2::GetDisplayRows()
   {
      long result;
      InvokeHelper(0x600200bf, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetDisplayRows(long nNewValue)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x600200bf, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   nNewValue);
   }

   BOOL Reflection2::GetEndOfLineWrap()
   {
      BOOL result;
      InvokeHelper(0x600200c1, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetEndOfLineWrap(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x600200c1, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   BOOL Reflection2::GetEnqAck()
   {
      BOOL result;
      InvokeHelper(0x600200c3, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetEnqAck(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x600200c3, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   CString Reflection2::GetFontName()
   {
      CString result;
      InvokeHelper(0x600200c5, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetFontName(LPCTSTR lpszNewValue)
   {
      static BYTE parms[] =
      VTS_BSTR;
      InvokeHelper(0x600200c5, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   lpszNewValue);
   }

   long Reflection2::GetFontSize()
   {
      long result;
      InvokeHelper(0x600200c7, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetFontSize(long nNewValue)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x600200c7, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   nNewValue);
   }

   BOOL Reflection2::GetForceAutoRepeat()
   {
      BOOL result;
      InvokeHelper(0x600200c9, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetForceAutoRepeat(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x600200c9, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   CString Reflection2::GetFullName()
   {
      CString result;
      InvokeHelper(0x600200cf, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetFullName(LPCTSTR lpszNewValue)
   {
      static BYTE parms[] =
      VTS_BSTR;
      InvokeHelper(0x600200cf, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   lpszNewValue);
   }

   long Reflection2::GetHeight()
   {
      long result;
      InvokeHelper(0x600200d1, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetHeight(long nNewValue)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x600200d1, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   nNewValue);
   }

   BOOL Reflection2::GetHorizontalCoupling()
   {
      BOOL result;
      InvokeHelper(0x600200d3, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetHorizontalCoupling(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x600200d3, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   long Reflection2::GetHostCharacterSet()
   {
      long result;
      InvokeHelper(0x600200d5, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetHostCharacterSet(long nNewValue)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x600200d5, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   nNewValue);
   }

   long Reflection2::GetHostStatusLine()
   {
      long result;
      InvokeHelper(0x600200d7, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetHostStatusLine(long nNewValue)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x600200d7, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   nNewValue);
   }

   CString Reflection2::GetHostTriggerCharacter()
   {
      CString result;
      InvokeHelper(0x600200d9, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetHostTriggerCharacter(LPCTSTR lpszNewValue)
   {
      static BYTE parms[] =
      VTS_BSTR;
      InvokeHelper(0x600200d9, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   lpszNewValue);
   }

   CString Reflection2::GetHostsFile()
   {
      CString result;
      InvokeHelper(0x600200db, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetHostsFile(LPCTSTR lpszNewValue)
   {
      static BYTE parms[] =
      VTS_BSTR;
      InvokeHelper(0x600200db, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   lpszNewValue);
   }

   BOOL Reflection2::GetInsertMode()
   {
      BOOL result;
      InvokeHelper(0x600200dd, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetInsertMode(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x600200dd, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   BOOL Reflection2::GetInverseVideo()
   {
      BOOL result;
      InvokeHelper(0x600200e1, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetInverseVideo(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x600200e1, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   long Reflection2::GetJumpScrollSpeed()
   {
      long result;
      InvokeHelper(0x600200e3, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetJumpScrollSpeed(long nNewValue)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x600200e3, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   nNewValue);
   }

   BOOL Reflection2::GetKatakanaDisplay()
   {
      BOOL result;
      InvokeHelper(0x600200e5, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetKatakanaDisplay(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x600200e5, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   BOOL Reflection2::GetKermitAutomaticServer()
   {
      BOOL result;
      InvokeHelper(0x600200e7, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetKermitAutomaticServer(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x600200e7, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   long Reflection2::GetKermitChecksum()
   {
      long result;
      InvokeHelper(0x600200e9, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetKermitChecksum(long nNewValue)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x600200e9, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   nNewValue);
   }

   long Reflection2::GetKermitPacketSize()
   {
      long result;
      InvokeHelper(0x600200eb, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetKermitPacketSize(long nNewValue)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x600200eb, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   nNewValue);
   }

   CString Reflection2::GetKermitReceiveEndCharacter()
   {
      CString result;
      InvokeHelper(0x600200ed, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetKermitReceiveEndCharacter(LPCTSTR lpszNewValue)
   {
      static BYTE parms[] =
      VTS_BSTR;
      InvokeHelper(0x600200ed, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   lpszNewValue);
   }

   CString Reflection2::GetKermitReceiveStartCharacter()
   {
      CString result;
      InvokeHelper(0x600200ef, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetKermitReceiveStartCharacter(LPCTSTR lpszNewValue)
   {
      static BYTE parms[] =
      VTS_BSTR;
      InvokeHelper(0x600200ef, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   lpszNewValue);
   }

   CString Reflection2::GetKermitReceiveStartupCommand()
   {
      CString result;
      InvokeHelper(0x600200f1, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetKermitReceiveStartupCommand(LPCTSTR lpszNewValue)
   {
      static BYTE parms[] =
      VTS_BSTR;
      InvokeHelper(0x600200f1, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   lpszNewValue);
   }

   CString Reflection2::GetKermitSendEndCharacter()
   {
      CString result;
      InvokeHelper(0x600200f3, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetKermitSendEndCharacter(LPCTSTR lpszNewValue)
   {
      static BYTE parms[] =
      VTS_BSTR;
      InvokeHelper(0x600200f3, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   lpszNewValue);
   }

   CString Reflection2::GetKermitSendStartCharacter()
   {
      CString result;
      InvokeHelper(0x600200f5, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetKermitSendStartCharacter(LPCTSTR lpszNewValue)
   {
      static BYTE parms[] =
      VTS_BSTR;
      InvokeHelper(0x600200f5, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   lpszNewValue);
   }

   CString Reflection2::GetKermitSendStartupCommand()
   {
      CString result;
      InvokeHelper(0x600200f7, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetKermitSendStartupCommand(LPCTSTR lpszNewValue)
   {
      static BYTE parms[] =
      VTS_BSTR;
      InvokeHelper(0x600200f7, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   lpszNewValue);
   }

   CString Reflection2::GetKermitServerStartupCommand()
   {
      CString result;
      InvokeHelper(0x600200f9, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetKermitServerStartupCommand(LPCTSTR lpszNewValue)
   {
      static BYTE parms[] =
      VTS_BSTR;
      InvokeHelper(0x600200f9, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   lpszNewValue);
   }

   long Reflection2::GetKermitTransferType()
   {
      long result;
      InvokeHelper(0x600200fb, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetKermitTransferType(long nNewValue)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x600200fb, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   nNewValue);
   }

   BOOL Reflection2::GetKermitTranslateCharacters()
   {
      BOOL result;
      InvokeHelper(0x600200fd, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetKermitTranslateCharacters(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x600200fd, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   BOOL Reflection2::GetKermitTranslateFilenames()
   {
      BOOL result;
      InvokeHelper(0x600200ff, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetKermitTranslateFilenames(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x600200ff, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   long Reflection2::GetKermitWindowSize()
   {
      long result;
      InvokeHelper(0x60020101, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetKermitWindowSize(long nNewValue)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x60020101, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   nNewValue);
   }

   BOOL Reflection2::GetKeyboardLocked()
   {
      BOOL result;
      InvokeHelper(0x60020103, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetKeyboardLocked(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x60020103, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   long Reflection2::GetLanguage()
   {
      long result;
      InvokeHelper(0x60020105, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetLanguage(long nNewValue)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x60020105, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   nNewValue);
   }

   long Reflection2::GetLeft()
   {
      long result;
      InvokeHelper(0x60020107, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetLeft(long nNewValue)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x60020107, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   nNewValue);
   }

   BOOL Reflection2::GetLocalEcho()
   {
      BOOL result;
      InvokeHelper(0x60020109, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetLocalEcho(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x60020109, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   BOOL Reflection2::GetMarginBell()
   {
      BOOL result;
      InvokeHelper(0x6002010b, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetMarginBell(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x6002010b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   BOOL Reflection2::GetMultiplePageTerminal()
   {
      BOOL result;
      InvokeHelper(0x6002010d, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetMultiplePageTerminal(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x6002010d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   CString Reflection2::GetName()
   {
      CString result;
      InvokeHelper(0x6002010f, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetName(LPCTSTR lpszNewValue)
   {
      static BYTE parms[] =
      VTS_BSTR;
      InvokeHelper(0x6002010f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   lpszNewValue);
   }

   long Reflection2::GetNationalReplacementSet()
   {
      long result;
      InvokeHelper(0x60020111, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetNationalReplacementSet(long nNewValue)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x60020111, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   nNewValue);
   }

   CString Reflection2::GetNativeOS()
   {
      CString result;
      InvokeHelper(0x60020113, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetNativeOS(LPCTSTR lpszNewValue)
   {
      static BYTE parms[] =
      VTS_BSTR;
      InvokeHelper(0x60020113, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   lpszNewValue);
   }

   BOOL Reflection2::GetNewPageOnClear()
   {
      BOOL result;
      InvokeHelper(0x60020115, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetNewPageOnClear(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x60020115, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   BOOL Reflection2::GetNumLock()
   {
      BOOL result;
      InvokeHelper(0x60020117, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetNumLock(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x60020117, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   CString Reflection2::GetOLEServerName()
   {
      CString result;
      InvokeHelper(0x60020119, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetOLEServerName(LPCTSTR lpszNewValue)
   {
      static BYTE parms[] =
      VTS_BSTR;
      InvokeHelper(0x60020119, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   lpszNewValue);
   }

   BOOL Reflection2::GetOnline()
   {
      BOOL result;
      InvokeHelper(0x6002011b, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetOnline(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x6002011b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   long Reflection2::GetPPLActivityTimeout()
   {
      long result;
      InvokeHelper(0x6002011d, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetPPLActivityTimeout(long nNewValue)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x6002011d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   nNewValue);
   }

   CString Reflection2::GetPPLStartupCommand()
   {
      CString result;
      InvokeHelper(0x6002011f, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetPPLStartupCommand(LPCTSTR lpszNewValue)
   {
      static BYTE parms[] =
      VTS_BSTR;
      InvokeHelper(0x6002011f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   lpszNewValue);
   }

   BOOL Reflection2::GetPageCoupling()
   {
      BOOL result;
      InvokeHelper(0x60020121, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetPageCoupling(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x60020121, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   VARIANT Reflection2::GetParent()
   {
      VARIANT result;
      InvokeHelper(0x60020123, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetParent(const VARIANT& newValue)
   {
      static BYTE parms[] =
      VTS_VARIANT;
      InvokeHelper(0x60020123, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   &newValue);
   }

   long Reflection2::GetPasteBufferSize()
   {
      long result;
      InvokeHelper(0x60020125, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetPasteBufferSize(long nNewValue)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x60020125, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   nNewValue);
   }

   long Reflection2::GetPasteDelay()
   {
      long result;
      InvokeHelper(0x60020127, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetPasteDelay(long nNewValue)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x60020127, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   nNewValue);
   }

   CString Reflection2::GetPath()
   {
      CString result;
      InvokeHelper(0x60020129, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetPath(LPCTSTR lpszNewValue)
   {
      static BYTE parms[] =
      VTS_BSTR;
      InvokeHelper(0x60020129, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   lpszNewValue);
   }

   BOOL Reflection2::GetPreserveNRC()
   {
      BOOL result;
      InvokeHelper(0x6002012b, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetPreserveNRC(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x6002012b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   long Reflection2::GetPrinterBottomMargin()
   {
      long result;
      InvokeHelper(0x6002012d, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetPrinterBottomMargin(long nNewValue)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x6002012d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   nNewValue);
   }

   long Reflection2::GetPrinterColumns()
   {
      long result;
      InvokeHelper(0x6002012f, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetPrinterColumns(long nNewValue)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x6002012f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   nNewValue);
   }

   CString Reflection2::GetPrintToFile()
   {
      CString result;
      InvokeHelper(0x60020131, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetPrintToFile(LPCTSTR lpszNewValue)
   {
      static BYTE parms[] =
      VTS_BSTR;
      InvokeHelper(0x60020131, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   lpszNewValue);
   }

   CString Reflection2::GetPrinterFontName()
   {
      CString result;
      InvokeHelper(0x60020133, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetPrinterFontName(LPCTSTR lpszNewValue)
   {
      static BYTE parms[] =
      VTS_BSTR;
      InvokeHelper(0x60020133, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   lpszNewValue);
   }

   BOOL Reflection2::GetPrinterInverseFont()
   {
      BOOL result;
      InvokeHelper(0x60020135, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetPrinterInverseFont(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x60020135, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   BOOL Reflection2::GetPrinterLogging()
   {
      BOOL result;
      InvokeHelper(0x60020137, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetPrinterLogging(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x60020137, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   BOOL Reflection2::GetPrinterPassThroughConversion()
   {
      BOOL result;
      InvokeHelper(0x60020139, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetPrinterPassThroughConversion(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x60020139, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   long Reflection2::GetPrinterRows()
   {
      long result;
      InvokeHelper(0x6002013b, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetPrinterRows(long nNewValue)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x6002013b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   nNewValue);
   }

   long Reflection2::GetPrinterTimeout()
   {
      long result;
      InvokeHelper(0x6002013d, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetPrinterTimeout(long nNewValue)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x6002013d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   nNewValue);
   }

   BOOL Reflection2::GetProcessDataComm()
   {
      BOOL result;
      InvokeHelper(0x6002013f, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetProcessDataComm(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x6002013f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   BOOL Reflection2::GetReadCtrlZAsEOF()
   {
      BOOL result;
      InvokeHelper(0x60020141, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetReadCtrlZAsEOF(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x60020141, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   BOOL Reflection2::GetReadTabAsSpaces()
   {
      BOOL result;
      InvokeHelper(0x60020143, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetReadTabAsSpaces(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x60020143, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   BOOL Reflection2::GetReportErrors()
   {
      BOOL result;
      InvokeHelper(0x60020145, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetReportErrors(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x60020145, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   BOOL Reflection2::GetSaveFromScrollingRegion()
   {
      BOOL result;
      InvokeHelper(0x60020147, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetSaveFromScrollingRegion(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x60020147, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   BOOL Reflection2::GetSavePasswords()
   {
      BOOL result;
      InvokeHelper(0x60020149, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetSavePasswords(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x60020149, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   BOOL Reflection2::GetSaveWindowPosition()
   {
      BOOL result;
      InvokeHelper(0x6002014b, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetSaveWindowPosition(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x6002014b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   long Reflection2::GetScreenTopRow()
   {
      long result;
      InvokeHelper(0x6002014d, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetScreenTopRow(long nNewValue)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x6002014d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   nNewValue);
   }

   long Reflection2::GetScrollOptimization()
   {
      long result;
      InvokeHelper(0x6002014f, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetScrollOptimization(long nNewValue)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x6002014f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   nNewValue);
   }

   long Reflection2::GetSelectionEndColumn()
   {
      long result;
      InvokeHelper(0x60020151, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetSelectionEndColumn(long nNewValue)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x60020151, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   nNewValue);
   }

   long Reflection2::GetSelectionEndRow()
   {
      long result;
      InvokeHelper(0x60020153, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetSelectionEndRow(long nNewValue)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x60020153, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   nNewValue);
   }

   long Reflection2::GetSelectionStartColumn()
   {
      long result;
      InvokeHelper(0x60020155, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetSelectionStartColumn(long nNewValue)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x60020155, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   nNewValue);
   }

   long Reflection2::GetSelectionStartRow()
   {
      long result;
      InvokeHelper(0x60020157, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetSelectionStartRow(long nNewValue)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x60020157, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   nNewValue);
   }

   long Reflection2::GetSelectionType()
   {
      long result;
      InvokeHelper(0x60020159, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetSelectionType(long nNewValue)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x60020159, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   nNewValue);
   }

   CString Reflection2::GetSerialNumber()
   {
      CString result;
      InvokeHelper(0x6002015b, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetSerialNumber(LPCTSTR lpszNewValue)
   {
      static BYTE parms[] =
      VTS_BSTR;
      InvokeHelper(0x6002015b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   lpszNewValue);
   }

   CString Reflection2::GetSettingsAuthor()
   {
      CString result;
      InvokeHelper(0x6002015d, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetSettingsAuthor(LPCTSTR lpszNewValue)
   {
      static BYTE parms[] =
      VTS_BSTR;
      InvokeHelper(0x6002015d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   lpszNewValue);
   }

   CString Reflection2::GetSettingsComments()
   {
      CString result;
      InvokeHelper(0x6002015f, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetSettingsComments(LPCTSTR lpszNewValue)
   {
      static BYTE parms[] =
      VTS_BSTR;
      InvokeHelper(0x6002015f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   lpszNewValue);
   }

   CString Reflection2::GetSettingsFile()
   {
      CString result;
      InvokeHelper(0x60020161, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetSettingsFile(LPCTSTR lpszNewValue)
   {
      static BYTE parms[] =
      VTS_BSTR;
      InvokeHelper(0x60020161, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   lpszNewValue);
   }

   CString Reflection2::GetSettingsTitle()
   {
      CString result;
      InvokeHelper(0x60020163, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetSettingsTitle(LPCTSTR lpszNewValue)
   {
      static BYTE parms[] =
      VTS_BSTR;
      InvokeHelper(0x60020163, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   lpszNewValue);
   }

   BOOL Reflection2::GetShowControlCharacters()
   {
      BOOL result;
      InvokeHelper(0x60020165, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetShowControlCharacters(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x60020165, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   BOOL Reflection2::GetShowTerminalFrame()
   {
      BOOL result;
      InvokeHelper(0x60020167, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetShowTerminalFrame(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x60020167, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   BOOL Reflection2::GetShowTerminalKeyboard()
   {
      BOOL result;
      InvokeHelper(0x60020169, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetShowTerminalKeyboard(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x60020169, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   BOOL Reflection2::GetShowToolbar()
   {
      BOOL result;
      InvokeHelper(0x6002016b, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetShowToolbar(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x6002016b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   long Reflection2::GetSingleByteUPSS()
   {
      long result;
      InvokeHelper(0x6002016d, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetSingleByteUPSS(long nNewValue)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x6002016d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   nNewValue);
   }

   BOOL Reflection2::GetSmoothScroll()
   {
      BOOL result;
      InvokeHelper(0x6002016f, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetSmoothScroll(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x6002016f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   long Reflection2::GetSpacesPerTab()
   {
      long result;
      InvokeHelper(0x60020171, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetSpacesPerTab(long nNewValue)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x60020171, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   nNewValue);
   }

   long Reflection2::GetStartupAction()
   {
      long result;
      InvokeHelper(0x60020173, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetStartupAction(long nNewValue)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x60020173, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   nNewValue);
   }

   CString Reflection2::GetStartupConnection()
   {
      CString result;
      InvokeHelper(0x60020175, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetStartupConnection(LPCTSTR lpszNewValue)
   {
      static BYTE parms[] =
      VTS_BSTR;
      InvokeHelper(0x60020175, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   lpszNewValue);
   }

   CString Reflection2::GetStatusBar()
   {
      CString result;
      InvokeHelper(0x60020177, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetStatusBar(LPCTSTR lpszNewValue)
   {
      static BYTE parms[] =
      VTS_BSTR;
      InvokeHelper(0x60020177, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   lpszNewValue);
   }

   long Reflection2::GetTerminalClass()
   {
      long result;
      InvokeHelper(0x60020179, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetTerminalClass(long nNewValue)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x60020179, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   nNewValue);
   }

   long Reflection2::GetTerminalSound()
   {
      long result;
      InvokeHelper(0x6002017b, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetTerminalSound(long nNewValue)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x6002017b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   nNewValue);
   }

   long Reflection2::GetTerminalType()
   {
      long result;
      InvokeHelper(0x6002017d, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetTerminalType(long nNewValue)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x6002017d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   nNewValue);
   }

   long Reflection2::GetTextFileCharacterSet()
   {
      long result;
      InvokeHelper(0x6002017f, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetTextFileCharacterSet(long nNewValue)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x6002017f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   nNewValue);
   }

   long Reflection2::GetTop()
   {
      long result;
      InvokeHelper(0x60020181, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetTop(long nNewValue)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x60020181, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   nNewValue);
   }

   long Reflection2::GetTransfer8Dot3FilenameCase()
   {
      long result;
      InvokeHelper(0x60020183, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetTransfer8Dot3FilenameCase(long nNewValue)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x60020183, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   nNewValue);
   }

   long Reflection2::GetTransferDefaultProtocol()
   {
      long result;
      InvokeHelper(0x60020185, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetTransferDefaultProtocol(long nNewValue)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x60020185, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   nNewValue);
   }

   CString Reflection2::GetTransferDownloadDirectory()
   {
      CString result;
      InvokeHelper(0x60020187, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetTransferDownloadDirectory(LPCTSTR lpszNewValue)
   {
      static BYTE parms[] =
      VTS_BSTR;
      InvokeHelper(0x60020187, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   lpszNewValue);
   }

   long Reflection2::GetTransferIfFileExistsDefault()
   {
      long result;
      InvokeHelper(0x60020189, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetTransferIfFileExistsDefault(long nNewValue)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x60020189, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   nNewValue);
   }

   BOOL Reflection2::GetTransferReceiveAs8Dot3()
   {
      BOOL result;
      InvokeHelper(0x6002018b, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetTransferReceiveAs8Dot3(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x6002018b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   long Reflection2::GetTransferReceiveTimeout()
   {
      long result;
      InvokeHelper(0x6002018d, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetTransferReceiveTimeout(long nNewValue)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x6002018d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   nNewValue);
   }

   long Reflection2::GetTransferRetryLimit()
   {
      long result;
      InvokeHelper(0x6002018f, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetTransferRetryLimit(long nNewValue)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x6002018f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   nNewValue);
   }

   BOOL Reflection2::GetTransferSpacesToUnderscores()
   {
      BOOL result;
      InvokeHelper(0x60020191, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetTransferSpacesToUnderscores(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x60020191, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   long Reflection2::GetTransferStartTimeout()
   {
      long result;
      InvokeHelper(0x60020193, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetTransferStartTimeout(long nNewValue)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x60020193, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   nNewValue);
   }

   BOOL Reflection2::GetTransferStatusWindow()
   {
      BOOL result;
      InvokeHelper(0x60020195, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetTransferStatusWindow(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x60020195, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   BOOL Reflection2::GetTransferUnderscoresToSpaces()
   {
      BOOL result;
      InvokeHelper(0x60020197, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetTransferUnderscoresToSpaces(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x60020197, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   BOOL Reflection2::GetTranslateCharacters()
   {
      BOOL result;
      InvokeHelper(0x60020199, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetTranslateCharacters(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x60020199, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   BOOL Reflection2::GetTranslatePrintedCharacters()
   {
      BOOL result;
      InvokeHelper(0x6002019b, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetTranslatePrintedCharacters(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x6002019b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   BOOL Reflection2::GetTransmitXonXoff()
   {
      BOOL result;
      InvokeHelper(0x6002019d, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetTransmitXonXoff(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x6002019d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   BOOL Reflection2::GetUnderlineCharacters()
   {
      BOOL result;
      InvokeHelper(0x6002019f, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetUnderlineCharacters(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x6002019f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   BOOL Reflection2::GetUseAnsiColor()
   {
      BOOL result;
      InvokeHelper(0x600201a1, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetUseAnsiColor(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x600201a1, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   BOOL Reflection2::GetUseDefaultPrinterFont()
   {
      BOOL result;
      InvokeHelper(0x600201a3, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetUseDefaultPrinterFont(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x600201a3, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   BOOL Reflection2::GetUseNRC()
   {
      BOOL result;
      InvokeHelper(0x600201a5, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetUseNRC(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x600201a5, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   BOOL Reflection2::GetUserDefinedKeysLocked()
   {
      BOOL result;
      InvokeHelper(0x600201a7, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetUserDefinedKeysLocked(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x600201a7, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   CString Reflection2::GetUserDirectory()
   {
      CString result;
      InvokeHelper(0x600201a9, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetUserDirectory(LPCTSTR lpszNewValue)
   {
      static BYTE parms[] =
      VTS_BSTR;
      InvokeHelper(0x600201a9, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   lpszNewValue);
   }

   BOOL Reflection2::GetUserFeaturesLocked()
   {
      BOOL result;
      InvokeHelper(0x600201ab, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetUserFeaturesLocked(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x600201ab, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   long Reflection2::GetVTBackspaceSends()
   {
      long result;
      InvokeHelper(0x600201ad, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetVTBackspaceSends(long nNewValue)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x600201ad, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   nNewValue);
   }

   long Reflection2::GetVTCursorKeyMode()
   {
      long result;
      InvokeHelper(0x600201af, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetVTCursorKeyMode(long nNewValue)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x600201af, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   nNewValue);
   }

   long Reflection2::GetVTKeypadMode()
   {
      long result;
      InvokeHelper(0x600201b1, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetVTKeypadMode(long nNewValue)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x600201b1, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   nNewValue);
   }

   long Reflection2::GetVersionMajor()
   {
      long result;
      InvokeHelper(0x600201b3, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetVersionMajor(long nNewValue)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x600201b3, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   nNewValue);
   }

   long Reflection2::GetVersionMinor()
   {
      long result;
      InvokeHelper(0x600201b5, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetVersionMinor(long nNewValue)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x600201b5, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   nNewValue);
   }

   CString Reflection2::GetVersionString()
   {
      CString result;
      InvokeHelper(0x600201b7, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetVersionString(LPCTSTR lpszNewValue)
   {
      static BYTE parms[] =
      VTS_BSTR;
      InvokeHelper(0x600201b7, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   lpszNewValue);
   }

   BOOL Reflection2::GetVerticalCoupling()
   {
      BOOL result;
      InvokeHelper(0x600201b9, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetVerticalCoupling(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x600201b9, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   BOOL Reflection2::GetVisible()
   {
      BOOL result;
      InvokeHelper(0x600201bb, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetVisible(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x600201bb, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   BOOL Reflection2::GetWeakDCS()
   {
      BOOL result;
      InvokeHelper(0x600201bd, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetWeakDCS(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x600201bd, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   long Reflection2::GetWidth()
   {
      long result;
      InvokeHelper(0x600201bf, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetWidth(long nNewValue)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x600201bf, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   nNewValue);
   }

   long Reflection2::GetWindowState()
   {
      long result;
      InvokeHelper(0x600201c1, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetWindowState(long nNewValue)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x600201c1, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   nNewValue);
   }

   BOOL Reflection2::GetWriteCtrlZAsEOF()
   {
      BOOL result;
      InvokeHelper(0x600201c3, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetWriteCtrlZAsEOF(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x600201c3, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   BOOL Reflection2::GetWriteSpacesAsTab()
   {
      BOOL result;
      InvokeHelper(0x600201c5, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetWriteSpacesAsTab(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x600201c5, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   long Reflection2::GetWRQCompression()
   {
      long result;
      InvokeHelper(0x600201c7, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetWRQCompression(long nNewValue)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x600201c7, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   nNewValue);
   }

   CString Reflection2::GetWRQEndCharacter()
   {
      CString result;
      InvokeHelper(0x600201c9, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetWRQEndCharacter(LPCTSTR lpszNewValue)
   {
      static BYTE parms[] =
      VTS_BSTR;
      InvokeHelper(0x600201c9, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   lpszNewValue);
   }

   CString Reflection2::GetWRQExtraCharacters()
   {
      CString result;
      InvokeHelper(0x600201cb, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetWRQExtraCharacters(LPCTSTR lpszNewValue)
   {
      static BYTE parms[] =
      VTS_BSTR;
      InvokeHelper(0x600201cb, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   lpszNewValue);
   }

   long Reflection2::GetWRQFastFileTransfer()
   {
      long result;
      InvokeHelper(0x600201cd, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetWRQFastFileTransfer(long nNewValue)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x600201cd, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   nNewValue);
   }

   long Reflection2::GetWRQFrameSize()
   {
      long result;
      InvokeHelper(0x600201cf, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetWRQFrameSize(long nNewValue)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x600201cf, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   nNewValue);
   }

   CString Reflection2::GetWRQFrameTerminator()
   {
      CString result;
      InvokeHelper(0x600201d1, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetWRQFrameTerminator(LPCTSTR lpszNewValue)
   {
      static BYTE parms[] =
      VTS_BSTR;
      InvokeHelper(0x600201d1, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   lpszNewValue);
   }

   CString Reflection2::GetWRQHostErrorMessage()
   {
      CString result;
      InvokeHelper(0x600201d3, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetWRQHostErrorMessage(LPCTSTR lpszNewValue)
   {
      static BYTE parms[] =
      VTS_BSTR;
      InvokeHelper(0x600201d3, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   lpszNewValue);
   }

   long Reflection2::GetWRQHostRecordSize()
   {
      long result;
      InvokeHelper(0x600201d5, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetWRQHostRecordSize(long nNewValue)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x600201d5, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   nNewValue);
   }

   long Reflection2::GetWRQHostSystem()
   {
      long result;
      InvokeHelper(0x600201d7, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetWRQHostSystem(long nNewValue)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x600201d7, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   nNewValue);
   }

   BOOL Reflection2::GetWRQKeepFile()
   {
      BOOL result;
      InvokeHelper(0x600201d9, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetWRQKeepFile(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x600201d9, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   long Reflection2::GetWRQMPEFilenames()
   {
      long result;
      InvokeHelper(0x600201db, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetWRQMPEFilenames(long nNewValue)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x600201db, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   nNewValue);
   }

   BOOL Reflection2::GetWRQMPEStream()
   {
      BOOL result;
      InvokeHelper(0x600201dd, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetWRQMPEStream(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x600201dd, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   BOOL Reflection2::GetWRQPreserveCounts()
   {
      BOOL result;
      InvokeHelper(0x600201df, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetWRQPreserveCounts(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x600201df, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   BOOL Reflection2::GetWRQPreserveDate()
   {
      BOOL result;
      InvokeHelper(0x600201e1, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetWRQPreserveDate(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x600201e1, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   BOOL Reflection2::GetWRQQEditFormat()
   {
      BOOL result;
      InvokeHelper(0x600201e3, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetWRQQEditFormat(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x600201e3, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   BOOL Reflection2::GetWRQRemoveExtension()
   {
      BOOL result;
      InvokeHelper(0x600201e5, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetWRQRemoveExtension(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x600201e5, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   BOOL Reflection2::GetWRQSendSpooled()
   {
      BOOL result;
      InvokeHelper(0x600201e7, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetWRQSendSpooled(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x600201e7, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   BOOL Reflection2::GetWRQShowHidden()
   {
      BOOL result;
      InvokeHelper(0x600201e9, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetWRQShowHidden(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x600201e9, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   CString Reflection2::GetWRQStartCharacter()
   {
      CString result;
      InvokeHelper(0x600201eb, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetWRQStartCharacter(LPCTSTR lpszNewValue)
   {
      static BYTE parms[] =
      VTS_BSTR;
      InvokeHelper(0x600201eb, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   lpszNewValue);
   }

   CString Reflection2::GetWRQStartupCommand()
   {
      CString result;
      InvokeHelper(0x600201ed, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetWRQStartupCommand(LPCTSTR lpszNewValue)
   {
      static BYTE parms[] =
      VTS_BSTR;
      InvokeHelper(0x600201ed, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   lpszNewValue);
   }

   BOOL Reflection2::GetWRQSubmitBatch()
   {
      BOOL result;
      InvokeHelper(0x600201ef, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetWRQSubmitBatch(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x600201ef, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   BOOL Reflection2::GetWRQSubmitPrint()
   {
      BOOL result;
      InvokeHelper(0x600201f1, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetWRQSubmitPrint(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x600201f1, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   long Reflection2::GetWRQTransferLink()
   {
      long result;
      InvokeHelper(0x600201f3, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetWRQTransferLink(long nNewValue)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x600201f3, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   nNewValue);
   }

   long Reflection2::GetWRQTransferType()
   {
      long result;
      InvokeHelper(0x600201f5, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetWRQTransferType(long nNewValue)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x600201f5, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   nNewValue);
   }

   BOOL Reflection2::GetWRQTransferWithAttributes()
   {
      BOOL result;
      InvokeHelper(0x600201f7, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetWRQTransferWithAttributes(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x600201f7, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   BOOL Reflection2::GetWRQTranslateCCtl()
   {
      BOOL result;
      InvokeHelper(0x600201f9, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetWRQTranslateCCtl(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x600201f9, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   BOOL Reflection2::GetWRQUseBlockReads()
   {
      BOOL result;
      InvokeHelper(0x600201fb, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetWRQUseBlockReads(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x600201fb, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   BOOL Reflection2::GetWRQUseCTermFrameSize()
   {
      BOOL result;
      InvokeHelper(0x600201fd, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetWRQUseCTermFrameSize(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x600201fd, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   long Reflection2::GetWRQWindowSize()
   {
      long result;
      InvokeHelper(0x600201ff, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetWRQWindowSize(long nNewValue)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x600201ff, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   nNewValue);
   }

   long Reflection2::GetXmodemExtension()
   {
      long result;
      InvokeHelper(0x60020201, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetXmodemExtension(long nNewValue)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x60020201, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   nNewValue);
   }

   long Reflection2::GetXmodemTransferType()
   {
      long result;
      InvokeHelper(0x60020203, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetXmodemTransferType(long nNewValue)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x60020203, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   nNewValue);
   }

   BOOL Reflection2::GetXmodemTranslateCharacters()
   {
      BOOL result;
      InvokeHelper(0x60020205, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetXmodemTranslateCharacters(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x60020205, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   BOOL Reflection2::GetZmodemAutoDownload()
   {
      BOOL result;
      InvokeHelper(0x60020207, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetZmodemAutoDownload(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x60020207, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   BOOL Reflection2::GetZmodemDeleteCancelledReceives()
   {
      BOOL result;
      InvokeHelper(0x60020209, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetZmodemDeleteCancelledReceives(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x60020209, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   long Reflection2::GetZmodemPacketSize()
   {
      long result;
      InvokeHelper(0x6002020b, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetZmodemPacketSize(long nNewValue)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x6002020b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   nNewValue);
   }

   CString Reflection2::GetZmodemReceiveStartupCommand()
   {
      CString result;
      InvokeHelper(0x6002020d, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetZmodemReceiveStartupCommand(LPCTSTR lpszNewValue)
   {
      static BYTE parms[] =
      VTS_BSTR;
      InvokeHelper(0x6002020d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   lpszNewValue);
   }

   CString Reflection2::GetZmodemSendStartupCommand()
   {
      CString result;
      InvokeHelper(0x6002020f, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetZmodemSendStartupCommand(LPCTSTR lpszNewValue)
   {
      static BYTE parms[] =
      VTS_BSTR;
      InvokeHelper(0x6002020f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   lpszNewValue);
   }

   long Reflection2::GetZmodemTransferType()
   {
      long result;
      InvokeHelper(0x60020211, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetZmodemTransferType(long nNewValue)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x60020211, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   nNewValue);
   }

   BOOL Reflection2::GetZmodemTranslateCharacters()
   {
      BOOL result;
      InvokeHelper(0x60020213, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetZmodemTranslateCharacters(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x60020213, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   BOOL Reflection2::GetZmodemTranslateFilenames()
   {
      BOOL result;
      InvokeHelper(0x60020215, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetZmodemTranslateFilenames(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x60020215, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   long Reflection2::GetCompensateFrameSpaces()
   {
      long result;
      InvokeHelper(0x60020217, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetCompensateFrameSpaces(long nNewValue)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x60020217, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   nNewValue);
   }

   BOOL Reflection2::GetGlobalCapsLock()
   {
      BOOL result;
      InvokeHelper(0x60020219, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetGlobalCapsLock(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x60020219, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   BOOL Reflection2::GetGlobalNumLock()
   {
      BOOL result;
      InvokeHelper(0x6002021b, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetGlobalNumLock(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x6002021b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   BOOL Reflection2::GetGlobalScrollLock()
   {
      BOOL result;
      InvokeHelper(0x6002021d, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetGlobalScrollLock(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x6002021d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   BOOL Reflection2::GetJISRomanG0()
   {
      BOOL result;
      InvokeHelper(0x6002021f, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetJISRomanG0(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x6002021f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   BOOL Reflection2::GetOnDemandFonts()
   {
      BOOL result;
      InvokeHelper(0x60020221, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetOnDemandFonts(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x60020221, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   BOOL Reflection2::GetProportionalFonts()
   {
      BOOL result;
      InvokeHelper(0x60020223, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetProportionalFonts(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x60020223, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   void Reflection2::Activate()
   {
      InvokeHelper(0x60020225, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
   }

   CString Reflection2::GetKeyMapCommandArgs(long Modifiers, LPCTSTR Key)
   {
      CString result;
      static BYTE parms[] =
      VTS_I4 VTS_BSTR;
      InvokeHelper(0x60020226, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms,
                   Modifiers, Key);
      return(result);
   }

   void Reflection2::SetPropertyProfile(LPCTSTR PropertyName, long IsEnabled)
   {
      static BYTE parms[] =
      VTS_BSTR VTS_I4;
      InvokeHelper(0x60020227, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
                   PropertyName, IsEnabled);
   }

   void Reflection2::PlaySound(LPCTSTR SoundFile, const VARIANT& Asynchronous)
   {
      static BYTE parms[] =
      VTS_BSTR VTS_VARIANT;
      InvokeHelper(0x60020228, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
                   SoundFile, &Asynchronous);
   }

   BOOL Reflection2::PropertyIsModifiable(LPCTSTR PropertyName)
   {
      BOOL result;
      static BYTE parms[] =
      VTS_BSTR;
      InvokeHelper(0x60020229, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
                   PropertyName);
      return(result);
   }

   long Reflection2::GetFileType(LPCTSTR Filename)
   {
      long result;
      static BYTE parms[] =
      VTS_BSTR;
      InvokeHelper(0x6002022a, DISPATCH_METHOD, VT_I4, (void*)&result, parms,
                   Filename);
      return(result);
   }

   void Reflection2::Shell(LPCTSTR Application, const VARIANT& CommandLine, const VARIANT& WindowState, const VARIANT& Wait)
   {
      static BYTE parms[] =
      VTS_BSTR VTS_VARIANT VTS_VARIANT VTS_VARIANT;
      InvokeHelper(0x6002022b, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
                   Application, &CommandLine, &WindowState, &Wait);
   }

   void Reflection2::CopyAboutBoxInfo()
   {
      InvokeHelper(0x6002022c, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
   }

   void Reflection2::ConnectTemplate(const VARIANT& ConnectionName, const VARIANT& Options)
   {
      static BYTE parms[] =
      VTS_VARIANT VTS_VARIANT;
      InvokeHelper(0x6002022d, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
                   &ConnectionName, &Options);
   }

   void Reflection2::OpenSettingsExtended(LPCTSTR Filename, const VARIANT& Type, const VARIANT& Options)
   {
      static BYTE parms[] =
      VTS_BSTR VTS_VARIANT VTS_VARIANT;
      InvokeHelper(0x6002022e, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
                   Filename, &Type, &Options);
   }

   BOOL Reflection2::WaitForIncomingData(const VARIANT& Timeout, const VARIANT& Options)
   {
      BOOL result;
      static BYTE parms[] =
      VTS_VARIANT VTS_VARIANT;
      InvokeHelper(0x6002022f, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
                   &Timeout, &Options);
      return(result);
   }

   void Reflection2::FlashWindow(const VARIANT& Rate)
   {
      static BYTE parms[] =
      VTS_VARIANT;
      InvokeHelper(0x60020230, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
                   &Rate);
   }

   void Reflection2::SetColorMap(long Attribute, long Foreground, long Background)
   {
      static BYTE parms[] =
      VTS_I4 VTS_I4 VTS_I4;
      InvokeHelper(0x60020231, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
                   Attribute, Foreground, Background);
   }

   long Reflection2::ForegroundColor(long Attribute)
   {
      long result;
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x60020232, DISPATCH_METHOD, VT_I4, (void*)&result, parms,
                   Attribute);
      return(result);
   }

   long Reflection2::BackgroundColor(long Attribute)
   {
      long result;
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x60020233, DISPATCH_METHOD, VT_I4, (void*)&result, parms,
                   Attribute);
      return(result);
   }

   void Reflection2::SetColorRGB(long Color, long Red, long Green, long Blue)
   {
      static BYTE parms[] =
      VTS_I4 VTS_I4 VTS_I4 VTS_I4;
      InvokeHelper(0x60020234, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
                   Color, Red, Green, Blue);
   }

   long Reflection2::GetColorRGB(long Color, long WhichValue)
   {
      long result;
      static BYTE parms[] =
      VTS_I4 VTS_I4;
      InvokeHelper(0x60020235, DISPATCH_METHOD, VT_I4, (void*)&result, parms,
                   Color, WhichValue);
      return(result);
   }

   long Reflection2::CharacterAttributes(long Row, long Column)
   {
      long result;
      static BYTE parms[] =
      VTS_I4 VTS_I4;
      InvokeHelper(0x60020236, DISPATCH_METHOD, VT_I4, (void*)&result, parms,
                   Row, Column);
      return(result);
   }

   void Reflection2::SetAnsiColorRGB(long AnsiColor, long Red, long Green, long Blue)
   {
      static BYTE parms[] =
      VTS_I4 VTS_I4 VTS_I4 VTS_I4;
      InvokeHelper(0x60020237, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
                   AnsiColor, Red, Green, Blue);
   }

   long Reflection2::GetAnsiColorRGB(long AnsiColor, long WhichValue)
   {
      long result;
      static BYTE parms[] =
      VTS_I4 VTS_I4;
      InvokeHelper(0x60020238, DISPATCH_METHOD, VT_I4, (void*)&result, parms,
                   AnsiColor, WhichValue);
      return(result);
   }

   void Reflection2::FTPStartServer(const VARIANT& UserName, const VARIANT& Password, const VARIANT& HostName, const VARIANT& Options)
   {
      static BYTE parms[] =
      VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT;
      InvokeHelper(0x60020239, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
                   &UserName, &Password, &HostName, &Options);
   }

   void Reflection2::FTPStopServer()
   {
      InvokeHelper(0x6002023a, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
   }

   void Reflection2::FTPReceiveFile(LPCTSTR LocalFile, LPCTSTR RemoteFile, const VARIANT& TransferType, const VARIANT& IfFileExists, const VARIANT& Before, const VARIANT& Since, const VARIANT& Exclude)
   {
      static BYTE parms[] =
      VTS_BSTR VTS_BSTR VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT;
      InvokeHelper(0x6002023b, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
                   LocalFile, RemoteFile, &TransferType, &IfFileExists, &Before, &Since, &Exclude);
   }

   void Reflection2::FTPSendFile(LPCTSTR LocalFile, LPCTSTR RemoteFile, const VARIANT& TransferType, const VARIANT& IfFileExists, const VARIANT& Before, const VARIANT& Since, const VARIANT& Exclude)
   {
      static BYTE parms[] =
      VTS_BSTR VTS_BSTR VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT;
      InvokeHelper(0x6002023c, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
                   LocalFile, RemoteFile, &TransferType, &IfFileExists, &Before, &Since, &Exclude);
   }

   CString Reflection2::GetPropertyInformation(const VARIANT& Name, const VARIANT& Options)
   {
      CString result;
      static BYTE parms[] =
      VTS_VARIANT VTS_VARIANT;
      InvokeHelper(0x6002023d, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms,
                   &Name, &Options);
      return(result);
   }

   void Reflection2::StartRecordingSilently(const VARIANT& Options)
   {
      static BYTE parms[] =
      VTS_VARIANT;
      InvokeHelper(0x6002023e, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
                   &Options);
   }

   void Reflection2::DestroyToolbar(LPCTSTR toolbarName)
   {
      static BYTE parms[] =
      VTS_BSTR;
      InvokeHelper(0x60020240, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
                   toolbarName);
   }

   void Reflection2::SetMouseMap(long Modifiers, LPCTSTR Chord, long CommandType, LPCTSTR Commands, const VARIANT& CommandArguments)
   {
      static BYTE parms[] =
      VTS_I4 VTS_BSTR VTS_I4 VTS_BSTR VTS_VARIANT;
      InvokeHelper(0x60020242, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
                   Modifiers, Chord, CommandType, Commands, &CommandArguments);
   }

   void Reflection2::StatusBox(LPCTSTR Text, const VARIANT& Options)
   {
      static BYTE parms[] =
      VTS_BSTR VTS_VARIANT;
      InvokeHelper(0x60020243, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
                   Text, &Options);
   }

   void Reflection2::CloseStatusBox()
   {
      InvokeHelper(0x60020244, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
   }

   CString Reflection2::GetFolderName(const VARIANT& Title, const VARIANT& Text, const VARIANT& StartInFolder)
   {
      CString result;
      static BYTE parms[] =
      VTS_VARIANT VTS_VARIANT VTS_VARIANT;
      InvokeHelper(0x60020245, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms,
                   &Title, &Text, &StartInFolder);
      return(result);
   }

   BOOL Reflection2::GetAllowJIS()
   {
      BOOL result;
      InvokeHelper(0x60020246, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetAllowJIS(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x60020246, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   CString Reflection2::GetCommandLineSwitches()
   {
      CString result;
      InvokeHelper(0x60020248, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetCommandLineSwitches(LPCTSTR lpszNewValue)
   {
      static BYTE parms[] =
      VTS_BSTR;
      InvokeHelper(0x60020248, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   lpszNewValue);
   }

   BOOL Reflection2::GetDisplayEnabled()
   {
      BOOL result;
      InvokeHelper(0x6002024a, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetDisplayEnabled(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x6002024a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   BOOL Reflection2::GetFlashWindowOnDisconnect()
   {
      BOOL result;
      InvokeHelper(0x6002024c, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetFlashWindowOnDisconnect(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x6002024c, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   BOOL Reflection2::GetForceC1Controls()
   {
      BOOL result;
      InvokeHelper(0x6002024e, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetForceC1Controls(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x6002024e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   BOOL Reflection2::GetMinimizeCPUUsage()
   {
      BOOL result;
      InvokeHelper(0x60020250, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetMinimizeCPUUsage(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x60020250, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   long Reflection2::GetFoundTextRow()
   {
      long result;
      InvokeHelper(0x60020252, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetFoundTextRow(long nNewValue)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x60020252, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   nNewValue);
   }

   long Reflection2::GetFoundTextColumn()
   {
      long result;
      InvokeHelper(0x60020254, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetFoundTextColumn(long nNewValue)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x60020254, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   nNewValue);
   }

   BOOL Reflection2::GetPrinterPassEscape()
   {
      BOOL result;
      InvokeHelper(0x60020256, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetPrinterPassEscape(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x60020256, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   BOOL Reflection2::GetRecording()
   {
      BOOL result;
      InvokeHelper(0x60020258, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetRecording(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x60020258, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   CString Reflection2::GetRBVersionString()
   {
      CString result;
      InvokeHelper(0x6002025a, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetRBVersionString(LPCTSTR lpszNewValue)
   {
      static BYTE parms[] =
      VTS_BSTR;
      InvokeHelper(0x6002025a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   lpszNewValue);
   }

   CString Reflection2::GetScriptFolder()
   {
      CString result;
      InvokeHelper(0x6002025c, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetScriptFolder(LPCTSTR lpszNewValue)
   {
      static BYTE parms[] =
      VTS_BSTR;
      InvokeHelper(0x6002025c, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   lpszNewValue);
   }

   CString Reflection2::GetSettingsExtension()
   {
      CString result;
      InvokeHelper(0x6002025e, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetSettingsExtension(LPCTSTR lpszNewValue)
   {
      static BYTE parms[] =
      VTS_BSTR;
      InvokeHelper(0x6002025e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   lpszNewValue);
   }

   BOOL Reflection2::GetShowMenuBar()
   {
      BOOL result;
      InvokeHelper(0x60020260, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetShowMenuBar(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x60020260, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   BOOL Reflection2::GetShowStatusBar()
   {
      BOOL result;
      InvokeHelper(0x60020262, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetShowStatusBar(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x60020262, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   BOOL Reflection2::GetShowVerticalScrollBar()
   {
      BOOL result;
      InvokeHelper(0x60020264, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetShowVerticalScrollBar(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x60020264, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   BOOL Reflection2::GetTransferDisconnectWhenDone()
   {
      BOOL result;
      InvokeHelper(0x60020266, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetTransferDisconnectWhenDone(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x60020266, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   long Reflection2::GetWindowHandle()
   {
      long result;
      InvokeHelper(0x60020268, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetWindowHandle(long nNewValue)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x60020268, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   nNewValue);
   }

   CString Reflection2::GetWordBoundaryInclusive()
   {
      CString result;
      InvokeHelper(0x6002026a, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetWordBoundaryInclusive(LPCTSTR lpszNewValue)
   {
      static BYTE parms[] =
      VTS_BSTR;
      InvokeHelper(0x6002026a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   lpszNewValue);
   }

   CString Reflection2::GetWordBoundaryExclusive()
   {
      CString result;
      InvokeHelper(0x6002026c, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetWordBoundaryExclusive(LPCTSTR lpszNewValue)
   {
      static BYTE parms[] =
      VTS_BSTR;
      InvokeHelper(0x6002026c, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   lpszNewValue);
   }

   BOOL Reflection2::GetWRQShowRecordSize()
   {
      BOOL result;
      InvokeHelper(0x6002026e, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetWRQShowRecordSize(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x6002026e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   BOOL Reflection2::GetAutoScroll()
   {
      BOOL result;
      InvokeHelper(0x60020270, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetAutoScroll(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x60020270, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   BOOL Reflection2::GetPrintANSIColorBackground()
   {
      BOOL result;
      InvokeHelper(0x60020272, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetPrintANSIColorBackground(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x60020272, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   BOOL Reflection2::GetRecognizeDEL()
   {
      BOOL result;
      InvokeHelper(0x60020274, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetRecognizeDEL(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x60020274, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   long Reflection2::GetReceivedCR()
   {
      long result;
      InvokeHelper(0x60020276, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetReceivedCR(long nNewValue)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x60020276, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   nNewValue);
   }

   BOOL Reflection2::GetWyseProtectMode()
   {
      BOOL result;
      InvokeHelper(0x60020278, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetWyseProtectMode(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x60020278, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   BOOL Reflection2::GetWyseBlockMode()
   {
      BOOL result;
      InvokeHelper(0x6002027a, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetWyseBlockMode(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x6002027a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   long Reflection2::GetWyseAttributeMode()
   {
      long result;
      InvokeHelper(0x6002027c, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetWyseAttributeMode(long nNewValue)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x6002027c, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   nNewValue);
   }

   long Reflection2::GetWyseBlockTerminator()
   {
      long result;
      InvokeHelper(0x6002027e, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetWyseBlockTerminator(long nNewValue)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x6002027e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   nNewValue);
   }

   BOOL Reflection2::GetWyseAcceptNulls()
   {
      BOOL result;
      InvokeHelper(0x60020280, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetWyseAcceptNulls(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x60020280, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   long Reflection2::GetWyseReturnKey()
   {
      long result;
      InvokeHelper(0x60020282, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetWyseReturnKey(long nNewValue)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x60020282, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   nNewValue);
   }

   long Reflection2::GetWyseEnterKey()
   {
      long result;
      InvokeHelper(0x60020284, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetWyseEnterKey(long nNewValue)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x60020284, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   nNewValue);
   }

   long Reflection2::GetWyseLabelLines()
   {
      long result;
      InvokeHelper(0x60020286, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetWyseLabelLines(long nNewValue)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x60020286, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   nNewValue);
   }

   long Reflection2::GetWyseStatusLineDisplay()
   {
      long result;
      InvokeHelper(0x60020288, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetWyseStatusLineDisplay(long nNewValue)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x60020288, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   nNewValue);
   }

   BOOL Reflection2::GetShowTitleBar()
   {
      BOOL result;
      InvokeHelper(0x6002028a, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetShowTitleBar(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x6002028a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   long Reflection2::GetPrinterOrientation()
   {
      long result;
      InvokeHelper(0x6002028c, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetPrinterOrientation(long nNewValue)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x6002028c, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   nNewValue);
   }

   BOOL Reflection2::GetDigitalLA210PrinterEmulation()
   {
      BOOL result;
      InvokeHelper(0x6002028e, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetDigitalLA210PrinterEmulation(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x6002028e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   BOOL Reflection2::GetConfirmExit()
   {
      BOOL result;
      InvokeHelper(0x60020290, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetConfirmExit(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x60020290, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   long Reflection2::GetSaveChanges()
   {
      long result;
      InvokeHelper(0x60020292, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetSaveChanges(long nNewValue)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x60020292, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   nNewValue);
   }

   BOOL Reflection2::GetToolbarIncludeLabels()
   {
      BOOL result;
      InvokeHelper(0x60020294, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetToolbarIncludeLabels(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x60020294, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   long Reflection2::GetFTPTransferType()
   {
      long result;
      InvokeHelper(0x60020298, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetFTPTransferType(long nNewValue)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x60020298, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   nNewValue);
   }

   CString Reflection2::GetFTPUserName()
   {
      CString result;
      InvokeHelper(0x6002029a, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetFTPUserName(LPCTSTR lpszNewValue)
   {
      static BYTE parms[] =
      VTS_BSTR;
      InvokeHelper(0x6002029a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   lpszNewValue);
   }

   CString Reflection2::GetFTPPassword()
   {
      CString result;
      InvokeHelper(0x6002029c, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetFTPPassword(LPCTSTR lpszNewValue)
   {
      static BYTE parms[] =
      VTS_BSTR;
      InvokeHelper(0x6002029c, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   lpszNewValue);
   }

   CString Reflection2::GetFTPHostName()
   {
      CString result;
      InvokeHelper(0x6002029e, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetFTPHostName(LPCTSTR lpszNewValue)
   {
      static BYTE parms[] =
      VTS_BSTR;
      InvokeHelper(0x6002029e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   lpszNewValue);
   }

   BOOL Reflection2::GetFTPTranslateCharacters()
   {
      BOOL result;
      InvokeHelper(0x600202a0, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetFTPTranslateCharacters(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x600202a0, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   long Reflection2::GetPrinterMarginBottom()
   {
      long result;
      InvokeHelper(0x600202a2, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetPrinterMarginBottom(long nNewValue)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x600202a2, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   nNewValue);
   }

   long Reflection2::GetPrinterMarginLeft()
   {
      long result;
      InvokeHelper(0x600202a4, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetPrinterMarginLeft(long nNewValue)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x600202a4, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   nNewValue);
   }

   long Reflection2::GetPrinterMarginRight()
   {
      long result;
      InvokeHelper(0x600202a6, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetPrinterMarginRight(long nNewValue)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x600202a6, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   nNewValue);
   }

   long Reflection2::GetPrinterMarginTop()
   {
      long result;
      InvokeHelper(0x600202a8, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetPrinterMarginTop(long nNewValue)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x600202a8, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   nNewValue);
   }

   long Reflection2::GetHotspotRow()
   {
      long result;
      InvokeHelper(0x600202aa, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetHotspotRow(long nNewValue)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x600202aa, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   nNewValue);
   }

   long Reflection2::GetHotspotColumn()
   {
      long result;
      InvokeHelper(0x600202ac, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetHotspotColumn(long nNewValue)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x600202ac, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   nNewValue);
   }

   long Reflection2::GetHotspotLength()
   {
      long result;
      InvokeHelper(0x600202ae, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetHotspotLength(long nNewValue)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x600202ae, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   nNewValue);
   }

   long Reflection2::GetHotspotsModifiers()
   {
      long result;
      InvokeHelper(0x600202b0, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetHotspotsModifiers(long nNewValue)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x600202b0, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   nNewValue);
   }

   long Reflection2::GetHotspotsChord()
   {
      long result;
      InvokeHelper(0x600202b2, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetHotspotsChord(long nNewValue)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x600202b2, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   nNewValue);
   }

   BOOL Reflection2::GetHotspotsEnabled()
   {
      BOOL result;
      InvokeHelper(0x600202b4, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetHotspotsEnabled(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x600202b4, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   BOOL Reflection2::GetHotspotsVisible()
   {
      BOOL result;
      InvokeHelper(0x600202b6, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetHotspotsVisible(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x600202b6, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   CString Reflection2::GetHotspotText()
   {
      CString result;
      InvokeHelper(0x600202b8, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetHotspotText(LPCTSTR lpszNewValue)
   {
      static BYTE parms[] =
      VTS_BSTR;
      InvokeHelper(0x600202b8, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   lpszNewValue);
   }

   BOOL Reflection2::GetWRQFastCompression()
   {
      BOOL result;
      InvokeHelper(0x600202ba, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetWRQFastCompression(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x600202ba, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   BOOL Reflection2::GetWidthChangeClear()
   {
      BOOL result;
      InvokeHelper(0x600202bc, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetWidthChangeClear(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x600202bc, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   long Reflection2::GetMouseRow()
   {
      long result;
      InvokeHelper(0x600202be, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetMouseRow(long nNewValue)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x600202be, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   nNewValue);
   }

   long Reflection2::GetMouseColumn()
   {
      long result;
      InvokeHelper(0x600202c0, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetMouseColumn(long nNewValue)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x600202c0, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   nNewValue);
   }

   BOOL Reflection2::GetUseModemDialerV5()
   {
      BOOL result;
      InvokeHelper(0x600202c2, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetUseModemDialerV5(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x600202c2, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   CString Reflection2::GetShortcutFolder()
   {
      CString result;
      InvokeHelper(0x600202c4, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetShortcutFolder(LPCTSTR lpszNewValue)
   {
      static BYTE parms[] =
      VTS_BSTR;
      InvokeHelper(0x600202c4, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   lpszNewValue);
   }

   BOOL Reflection2::GetCreateShortcut()
   {
      BOOL result;
      InvokeHelper(0x600202c6, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetCreateShortcut(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x600202c6, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   CString Reflection2::GetTransferAutoDetectASCIIExtensionList()
   {
      CString result;
      InvokeHelper(0x600202c8, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetTransferAutoDetectASCIIExtensionList(LPCTSTR lpszNewValue)
   {
      static BYTE parms[] =
      VTS_BSTR;
      InvokeHelper(0x600202c8, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   lpszNewValue);
   }

   CString Reflection2::GetTransferAutoDetectBinaryExtensionList()
   {
      CString result;
      InvokeHelper(0x600202ca, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetTransferAutoDetectBinaryExtensionList(LPCTSTR lpszNewValue)
   {
      static BYTE parms[] =
      VTS_BSTR;
      InvokeHelper(0x600202ca, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   lpszNewValue);
   }

   CString Reflection2::GetTransferAutoDetectImageLabelsExtensionList()
   {
      CString result;
      InvokeHelper(0x600202cc, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetTransferAutoDetectImageLabelsExtensionList(LPCTSTR lpszNewValue)
   {
      static BYTE parms[] =
      VTS_BSTR;
      InvokeHelper(0x600202cc, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   lpszNewValue);
   }

   CString Reflection2::GetTransferAutoDetectScanExtensionList()
   {
      CString result;
      InvokeHelper(0x600202ce, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetTransferAutoDetectScanExtensionList(LPCTSTR lpszNewValue)
   {
      static BYTE parms[] =
      VTS_BSTR;
      InvokeHelper(0x600202ce, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   lpszNewValue);
   }

   long Reflection2::GetTransferAutoDetectDefaultType()
   {
      long result;
      InvokeHelper(0x600202d0, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetTransferAutoDetectDefaultType(long nNewValue)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x600202d0, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   nNewValue);
   }

   long Reflection2::GetHostForDefaultSettings()
   {
      long result;
      InvokeHelper(0x600202d2, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetHostForDefaultSettings(long nNewValue)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x600202d2, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   nNewValue);
   }

   CString Reflection2::GetSiteDefaults()
   {
      CString result;
      InvokeHelper(0x600202d4, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetSiteDefaults(LPCTSTR lpszNewValue)
   {
      static BYTE parms[] =
      VTS_BSTR;
      InvokeHelper(0x600202d4, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   lpszNewValue);
   }

   BOOL Reflection2::GetPrinterFitFontToPage()
   {
      BOOL result;
      InvokeHelper(0x600202d6, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetPrinterFitFontToPage(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x600202d6, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   long Reflection2::GetWebSecurity()
   {
      long result;
      InvokeHelper(0x600202d8, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetWebSecurity(long nNewValue)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x600202d8, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   nNewValue);
   }

   long Reflection2::CheckEvent()
   {
      long result;
      InvokeHelper(0x600202da, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
      return(result);
   }

   long Reflection2::CheckEventNumber(long EventNumber)
   {
      long result;
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x600202db, DISPATCH_METHOD, VT_I4, (void*)&result, parms,
                   EventNumber);
      return(result);
   }

   void Reflection2::ClearEvents()
   {
      InvokeHelper(0x600202dc, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
   }

   void Reflection2::DefineEvent(long EventNumber, long EventType, const VARIANT& String, const VARIANT& Row, const VARIANT& Column, const VARIANT& Key)
   {
      static BYTE parms[] =
      VTS_I4 VTS_I4 VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT;
      InvokeHelper(0x600202dd, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
                   EventNumber, EventType, &String, &Row, &Column, &Key);
   }

   void Reflection2::EnableOnEvent(long OnEventNumber, long EnableOrDisable)
   {
      static BYTE parms[] =
      VTS_I4 VTS_I4;
      InvokeHelper(0x600202de, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
                   OnEventNumber, EnableOrDisable);
   }

   void Reflection2::RemoveEvent(long EventNumber)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x600202df, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
                   EventNumber);
   }

   void Reflection2::RemoveOnEvent(long EventNumber)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x600202e0, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
                   EventNumber);
   }

   void Reflection2::ResetEvent(long EventNumber)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x600202e1, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
                   EventNumber);
   }

   long Reflection2::WaitEvent(const VARIANT& Timeout, const VARIANT& Options)
   {
      long result;
      static BYTE parms[] =
      VTS_VARIANT VTS_VARIANT;
      InvokeHelper(0x600202e2, DISPATCH_METHOD, VT_I4, (void*)&result, parms,
                   &Timeout, &Options);
      return(result);
   }

   BOOL Reflection2::WaitEventNumber(long EventNumber, const VARIANT& Timeout, const VARIANT& Options)
   {
      BOOL result;
      static BYTE parms[] =
      VTS_I4 VTS_VARIANT VTS_VARIANT;
      InvokeHelper(0x600202e3, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
                   EventNumber, &Timeout, &Options);
      return(result);
   }

   BOOL Reflection2::WaitForEvent(long EventType, const VARIANT& Timeout, const VARIANT& String, const VARIANT& Row, const VARIANT& Column, const VARIANT& Key, const VARIANT& Options)
   {
      BOOL result;
      static BYTE parms[] =
      VTS_I4 VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT;
      InvokeHelper(0x600202e4, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
                   EventType, &Timeout, &String, &Row, &Column, &Key, &Options);
      return(result);
   }

   void Reflection2::OnEvent(long EventNumber, long EventType, long CommandType, LPCTSTR Commands, long Enable, long AfterEvent, const VARIANT& String, const VARIANT& Row, const VARIANT& Column, const VARIANT& Key, const VARIANT& CommandArguments)
   {
      static BYTE parms[] =
      VTS_I4 VTS_I4 VTS_I4 VTS_BSTR VTS_I4 VTS_I4 VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT;
      InvokeHelper(0x600202e5, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
                   EventNumber, EventType, CommandType, Commands, Enable, AfterEvent, &String, &Row, &Column, &Key, &CommandArguments);
   }

   CString Reflection2::GetPassword(const VARIANT& Prompt, const VARIANT& HostUserName, const VARIANT& HostName, const VARIANT& Options)
   {
      CString result;
      static BYTE parms[] =
      VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT;
      InvokeHelper(0x600202e6, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms,
                   &Prompt, &HostUserName, &HostName, &Options);
      return(result);
   }

   CString Reflection2::GetLoginProperty(const VARIANT& Property_, const VARIANT& Prompt, const VARIANT& HostUserName, const VARIANT& HostName, const VARIANT& Options)
   {
      CString result;
      static BYTE parms[] =
      VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT;
      InvokeHelper(0x600202e7, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms,
                   &Property_, &Prompt, &HostUserName, &HostName, &Options);
      return(result);
   }

   void Reflection2::RunMacro(LPCTSTR MacroName, const VARIANT& MacroData)
   {
      static BYTE parms[] =
      VTS_BSTR VTS_VARIANT;
      InvokeHelper(0x600202e8, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
                   MacroName, &MacroData);
   }

   void Reflection2::StopMacro()
   {
      InvokeHelper(0x600202e9, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
   }

   void Reflection2::CommitLoginProperties(const VARIANT& Options)
   {
      static BYTE parms[] =
      VTS_VARIANT;
      InvokeHelper(0x600202ea, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
                   &Options);
   }

   void Reflection2::StartRecordingExtended(const VARIANT& Options)
   {
      static BYTE parms[] =
      VTS_VARIANT;
      InvokeHelper(0x600202eb, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
                   &Options);
   }

   void Reflection2::FTPSetCurrentHostDirectory(LPCTSTR HostDirectory)
   {
      static BYTE parms[] =
      VTS_BSTR;
      InvokeHelper(0x600202ec, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
                   HostDirectory);
   }

   CString Reflection2::FTPGetCurrentHostDirectory()
   {
      CString result;
      InvokeHelper(0x600202ed, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::CancelExitEvent()
   {
      InvokeHelper(0x600202ee, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
   }

   void Reflection2::RaiseControlEvent(const VARIANT& Param1, const VARIANT& Param2)
   {
      static BYTE parms[] =
      VTS_VARIANT VTS_VARIANT;
      InvokeHelper(0x600202ef, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
                   &Param1, &Param2);
   }

   void Reflection2::PrintScreen(long Range, const VARIANT& Copies)
   {
      static BYTE parms[] =
      VTS_I4 VTS_VARIANT;
      InvokeHelper(0x600202f0, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
                   Range, &Copies);
   }

   void Reflection2::RunExternalMacro(LPCTSTR Filename, LPCTSTR MacroName, const VARIANT& MacroData)
   {
      static BYTE parms[] =
      VTS_BSTR VTS_BSTR VTS_VARIANT;
      InvokeHelper(0x600202f1, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
                   Filename, MacroName, &MacroData);
   }

   void Reflection2::StopRecordingMacro(long Destination, const VARIANT& Name, const VARIANT& Description, const VARIANT& Options)
   {
      static BYTE parms[] =
      VTS_I4 VTS_VARIANT VTS_VARIANT VTS_VARIANT;
      InvokeHelper(0x600202f2, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
                   Destination, &Name, &Description, &Options);
   }

   CString Reflection2::GetTransferPreset()
   {
      CString result;
      InvokeHelper(0x600202f3, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetTransferPreset(LPCTSTR lpszNewValue)
   {
      static BYTE parms[] =
      VTS_BSTR;
      InvokeHelper(0x600202f3, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   lpszNewValue);
   }

   BOOL Reflection2::GetFileTypeSticky()
   {
      BOOL result;
      InvokeHelper(0x600202f5, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetFileTypeSticky(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x600202f5, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   BOOL Reflection2::GetSaveColors()
   {
      BOOL result;
      InvokeHelper(0x600202f7, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetSaveColors(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x600202f7, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   BOOL Reflection2::GetSaveConnection()
   {
      BOOL result;
      InvokeHelper(0x600202f9, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetSaveConnection(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x600202f9, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   BOOL Reflection2::GetSaveHotspots()
   {
      BOOL result;
      InvokeHelper(0x600202fb, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetSaveHotspots(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x600202fb, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   BOOL Reflection2::GetSaveKeymap()
   {
      BOOL result;
      InvokeHelper(0x600202fd, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetSaveKeymap(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x600202fd, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   BOOL Reflection2::GetSaveMenus()
   {
      BOOL result;
      InvokeHelper(0x600202ff, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetSaveMenus(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x600202ff, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   BOOL Reflection2::GetSaveMouseMap()
   {
      BOOL result;
      InvokeHelper(0x60020301, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetSaveMouseMap(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x60020301, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   BOOL Reflection2::GetSaveToolbars()
   {
      BOOL result;
      InvokeHelper(0x60020303, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetSaveToolbars(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x60020303, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   long Reflection2::GetFileOpenType()
   {
      long result;
      InvokeHelper(0x60020305, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetFileOpenType(long nNewValue)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x60020305, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   nNewValue);
   }

   BOOL Reflection2::GetPrinterAutoRowSize()
   {
      BOOL result;
      InvokeHelper(0x60020307, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetPrinterAutoRowSize(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x60020307, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   BOOL Reflection2::GetPrinterColumnsTiedToDisplay()
   {
      BOOL result;
      InvokeHelper(0x60020309, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetPrinterColumnsTiedToDisplay(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x60020309, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   BOOL Reflection2::GetPrinterColumnsSetOrientation()
   {
      BOOL result;
      InvokeHelper(0x6002030b, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetPrinterColumnsSetOrientation(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x6002030b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   CString Reflection2::GetPCRecordSeparator()
   {
      CString result;
      InvokeHelper(0x6002030d, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetPCRecordSeparator(LPCTSTR lpszNewValue)
   {
      static BYTE parms[] =
      VTS_BSTR;
      InvokeHelper(0x6002030d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   lpszNewValue);
   }

   CString Reflection2::GetHostRecordSeparator()
   {
      CString result;
      InvokeHelper(0x6002030f, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetHostRecordSeparator(LPCTSTR lpszNewValue)
   {
      static BYTE parms[] =
      VTS_BSTR;
      InvokeHelper(0x6002030f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   lpszNewValue);
   }

   BOOL Reflection2::GetUsePCRecordSeparator()
   {
      BOOL result;
      InvokeHelper(0x60020311, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetUsePCRecordSeparator(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x60020311, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   BOOL Reflection2::GetUseHostRecordSeparator()
   {
      BOOL result;
      InvokeHelper(0x60020313, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetUseHostRecordSeparator(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x60020313, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   CString Reflection2::GetPCUserName()
   {
      CString result;
      InvokeHelper(0x60020315, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetPCUserName(LPCTSTR lpszNewValue)
   {
      static BYTE parms[] =
      VTS_BSTR;
      InvokeHelper(0x60020315, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   lpszNewValue);
   }

   BOOL Reflection2::GetAdmitOne()
   {
      BOOL result;
      InvokeHelper(0x60020317, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetAdmitOne(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x60020317, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   long Reflection2::GetEventDefined()
   {
      long result;
      InvokeHelper(0x60020319, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetEventDefined(long nNewValue)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x60020319, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   nNewValue);
   }

   BOOL Reflection2::GetFTPTranslateFilenames()
   {
      BOOL result;
      InvokeHelper(0x6002031b, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetFTPTranslateFilenames(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x6002031b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   long Reflection2::GetWindowRows()
   {
      long result;
      InvokeHelper(0x6002031d, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetWindowRows(long nNewValue)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x6002031d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   nNewValue);
   }

   long Reflection2::GetAllowLegacyComm()
   {
      long result;
      InvokeHelper(0x6002031f, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetAllowLegacyComm(long nNewValue)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x6002031f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   nNewValue);
   }

   BOOL Reflection2::GetT27DC1ClearsEOL()
   {
      BOOL result;
      InvokeHelper(0x60020321, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetT27DC1ClearsEOL(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x60020321, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   long Reflection2::GetT27DisplayPages()
   {
      long result;
      InvokeHelper(0x60020323, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetT27DisplayPages(long nNewValue)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x60020323, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   nNewValue);
   }

   BOOL Reflection2::GetT27InsertKeyInsertsSpace()
   {
      BOOL result;
      InvokeHelper(0x60020325, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetT27InsertKeyInsertsSpace(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x60020325, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   BOOL Reflection2::GetT27CursorWrap()
   {
      BOOL result;
      InvokeHelper(0x60020327, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetT27CursorWrap(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x60020327, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   BOOL Reflection2::GetT27SPCFYKeySendsPageNo()
   {
      BOOL result;
      InvokeHelper(0x60020329, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetT27SPCFYKeySendsPageNo(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x60020329, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   long Reflection2::GetT27SPCFYKeySends()
   {
      long result;
      InvokeHelper(0x6002032b, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetT27SPCFYKeySends(long nNewValue)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x6002032b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   nNewValue);
   }

   BOOL Reflection2::GetT27LineAtATimeXmit()
   {
      BOOL result;
      InvokeHelper(0x6002032d, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetT27LineAtATimeXmit(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x6002032d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   long Reflection2::GetT27HostReturn()
   {
      long result;
      InvokeHelper(0x6002032f, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetT27HostReturn(long nNewValue)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x6002032f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   nNewValue);
   }

   long Reflection2::GetT27HostLinefeed()
   {
      long result;
      InvokeHelper(0x60020331, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetT27HostLinefeed(long nNewValue)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x60020331, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   nNewValue);
   }

   long Reflection2::GetT27ReturnKey()
   {
      long result;
      InvokeHelper(0x60020333, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetT27ReturnKey(long nNewValue)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x60020333, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   nNewValue);
   }

   BOOL Reflection2::GetT27CLRClearsUnprotected()
   {
      BOOL result;
      InvokeHelper(0x60020335, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetT27CLRClearsUnprotected(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x60020335, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   CString Reflection2::GetMacroData()
   {
      CString result;
      InvokeHelper(0x60020337, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetMacroData(LPCTSTR lpszNewValue)
   {
      static BYTE parms[] =
      VTS_BSTR;
      InvokeHelper(0x60020337, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   lpszNewValue);
   }

   BOOL Reflection2::GetAllowMacroInterrupt()
   {
      BOOL result;
      InvokeHelper(0x60020339, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetAllowMacroInterrupt(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x60020339, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   BOOL Reflection2::GetT27ETXDisplay()
   {
      BOOL result;
      InvokeHelper(0x6002033b, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetT27ETXDisplay(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x6002033b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   BOOL Reflection2::GetT27ETXAdvance()
   {
      BOOL result;
      InvokeHelper(0x6002033d, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetT27ETXAdvance(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x6002033d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   long Reflection2::GetT27DC2Function()
   {
      long result;
      InvokeHelper(0x6002033f, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetT27DC2Function(long nNewValue)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x6002033f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   nNewValue);
   }

   long Reflection2::GetT27AlternativeUSChar()
   {
      long result;
      InvokeHelper(0x60020341, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetT27AlternativeUSChar(long nNewValue)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x60020341, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   nNewValue);
   }

   long Reflection2::GetT27AlternativeRSChar()
   {
      long result;
      InvokeHelper(0x60020343, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetT27AlternativeRSChar(long nNewValue)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x60020343, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   nNewValue);
   }

   BOOL Reflection2::GetT27FormXmitToCursor()
   {
      BOOL result;
      InvokeHelper(0x60020345, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetT27FormXmitToCursor(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x60020345, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   long Reflection2::GetT27ReturnKeyInForms()
   {
      long result;
      InvokeHelper(0x60020347, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetT27ReturnKeyInForms(long nNewValue)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x60020347, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   nNewValue);
   }

   BOOL Reflection2::GetT27SOHClearsScreen()
   {
      BOOL result;
      InvokeHelper(0x60020349, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetT27SOHClearsScreen(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x60020349, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   BOOL Reflection2::GetT27SOHExitsForms()
   {
      BOOL result;
      InvokeHelper(0x6002034b, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetT27SOHExitsForms(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x6002034b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   BOOL Reflection2::GetDataStreamTranslation()
   {
      BOOL result;
      InvokeHelper(0x6002034d, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetDataStreamTranslation(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x6002034d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   BOOL Reflection2::GetElfAtochemEmulation()
   {
      BOOL result;
      InvokeHelper(0x6002034f, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetElfAtochemEmulation(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x6002034f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   BOOL Reflection2::GetFTPUseWRQFTP()
   {
      BOOL result;
      InvokeHelper(0x60020351, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetFTPUseWRQFTP(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x60020351, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   CString Reflection2::GetUserData()
   {
      CString result;
      InvokeHelper(0x60020353, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetUserData(LPCTSTR lpszNewValue)
   {
      static BYTE parms[] =
      VTS_BSTR;
      InvokeHelper(0x60020353, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   lpszNewValue);
   }

   BOOL Reflection2::GetT27ShiftLock()
   {
      BOOL result;
      InvokeHelper(0x60020355, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetT27ShiftLock(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x60020355, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   BOOL Reflection2::GetDrawingOptimization()
   {
      BOOL result;
      InvokeHelper(0x60020357, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetDrawingOptimization(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x60020357, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   LPDISPATCH Reflection2::GetVBProject()
   {
      LPDISPATCH result;
      InvokeHelper(0x60020359, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
      return(result);
   }

   void Reflection2::SetVBProject(LPDISPATCH newValue)
   {
      static BYTE parms[] =
      VTS_DISPATCH;
      InvokeHelper(0x60020359, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   newValue);
   }


/////////////////////////////////////////////////////////////////////////////
// EReflection2 properties

/////////////////////////////////////////////////////////////////////////////
// EReflection2 operations


/////////////////////////////////////////////////////////////////////////////
// _IReflectionControl properties

/////////////////////////////////////////////////////////////////////////////
// _IReflectionControl operations

} // namespace ReflectionDispatch
