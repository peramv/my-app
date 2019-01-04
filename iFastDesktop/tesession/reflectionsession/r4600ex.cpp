// Machine generated IDispatch wrapper class(es) created with ClassWizard

#include "stdafx.h"
#include "r4600ex.h"

#ifdef _DEBUG
   #define new DEBUG_NEW
   #undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


namespace ReflectionDispatch
{

/////////////////////////////////////////////////////////////////////////////
// Application properties

/////////////////////////////////////////////////////////////////////////////
// Application operations

   void Application::AbortTransfer()
   {
      InvokeHelper(0x60020000, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
   }

   void Application::Break()
   {
      InvokeHelper(0x60020001, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
   }

   void Application::CancelTransfer()
   {
      InvokeHelper(0x60020002, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
   }

   void Application::Clear(long ClearWhat)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x60020003, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
                   ClearWhat);
   }

   void Application::CloseAllConnections()
   {
      InvokeHelper(0x60020004, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
   }

   long Application::CompileScript(LPCTSTR ScriptName)
   {
      long result;
      static BYTE parms[] =
      VTS_BSTR;
      InvokeHelper(0x60020005, DISPATCH_METHOD, VT_I4, (void*)&result, parms,
                   ScriptName);
      return(result);
   }

   void Application::Connect(const VARIANT& ConnectionName)
   {
      static BYTE parms[] =
      VTS_VARIANT;
      InvokeHelper(0x60020006, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
                   &ConnectionName);
   }

   CString Application::ConnectionSetting(LPCTSTR Setting)
   {
      CString result;
      static BYTE parms[] =
      VTS_BSTR;
      InvokeHelper(0x60020007, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms,
                   Setting);
      return(result);
   }

   void Application::Copy(long CopyWhat, const VARIANT& Format)
   {
      static BYTE parms[] =
      VTS_I4 VTS_VARIANT;
      InvokeHelper(0x60020008, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
                   CopyWhat, &Format);
   }

   void Application::DDEExecute(long ConversationID, LPCTSTR Command)
   {
      static BYTE parms[] =
      VTS_I4 VTS_BSTR;
      InvokeHelper(0x60020009, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
                   ConversationID, Command);
   }

   long Application::DDEInitiate(LPCTSTR AppName, LPCTSTR TopicName)
   {
      long result;
      static BYTE parms[] =
      VTS_BSTR VTS_BSTR;
      InvokeHelper(0x6002000a, DISPATCH_METHOD, VT_I4, (void*)&result, parms,
                   AppName, TopicName);
      return(result);
   }

   void Application::DDEPoke(long ConversationID, LPCTSTR ItemName, LPCTSTR Value)
   {
      static BYTE parms[] =
      VTS_I4 VTS_BSTR VTS_BSTR;
      InvokeHelper(0x6002000b, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
                   ConversationID, ItemName, Value);
   }

   CString Application::DDEQueryServerTopics(LPCTSTR AppName, LPCTSTR TopicName)
   {
      CString result;
      static BYTE parms[] =
      VTS_BSTR VTS_BSTR;
      InvokeHelper(0x6002000c, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms,
                   AppName, TopicName);
      return(result);
   }

   CString Application::DDERequest(long ConversationID, LPCTSTR ItemName)
   {
      CString result;
      static BYTE parms[] =
      VTS_I4 VTS_BSTR;
      InvokeHelper(0x6002000d, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms,
                   ConversationID, ItemName);
      return(result);
   }

   void Application::DDETerminate(long ConversationID)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x6002000e, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
                   ConversationID);
   }

   void Application::DDETerminateAll()
   {
      InvokeHelper(0x6002000f, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
   }

   void Application::Dial(LPCTSTR PhoneNumber, const VARIANT& Description, const VARIANT& InitString, const VARIANT& AnswerTimeout, const VARIANT& RetryTimes, const VARIANT& RetryInterval, const VARIANT& SpeakerMode, const VARIANT& SpeakerVolume, 
                          const VARIANT& SpeakerOffAfterRedial, const VARIANT& IgnoreModemErrors)
   {
      static BYTE parms[] =
      VTS_BSTR VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT;
      InvokeHelper(0x60020010, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
                   PhoneNumber, &Description, &InitString, &AnswerTimeout, &RetryTimes, &RetryInterval, &SpeakerMode, &SpeakerVolume, &SpeakerOffAfterRedial, &IgnoreModemErrors);
   }

   void Application::Disconnect()
   {
      InvokeHelper(0x60020011, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
   }

   void Application::Display(LPCTSTR String, const VARIANT& Options)
   {
      static BYTE parms[] =
      VTS_BSTR VTS_VARIANT;
      InvokeHelper(0x60020012, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
                   String, &Options);
   }

   void Application::DisplayFile(LPCTSTR Filename, const VARIANT& Options)
   {
      static BYTE parms[] =
      VTS_BSTR VTS_VARIANT;
      InvokeHelper(0x60020013, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
                   Filename, &Options);
   }

   void Application::DropDTR()
   {
      InvokeHelper(0x60020014, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
   }

   void Application::EditScript(LPCTSTR ScriptName)
   {
      static BYTE parms[] =
      VTS_BSTR;
      InvokeHelper(0x60020015, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
                   ScriptName);
   }

   CString Application::EvaluateRCLExpression(LPCTSTR Expression, const VARIANT& Options)
   {
      CString result;
      static BYTE parms[] =
      VTS_BSTR VTS_VARIANT;
      InvokeHelper(0x60020016, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms,
                   Expression, &Options);
      return(result);
   }

   void Application::ExecuteBuiltInFunction(LPCTSTR FunctionName)
   {
      static BYTE parms[] =
      VTS_BSTR;
      InvokeHelper(0x60020017, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
                   FunctionName);
   }

   void Application::ExecuteRCLCommand(LPCTSTR Command, const VARIANT& Options)
   {
      static BYTE parms[] =
      VTS_BSTR VTS_VARIANT;
      InvokeHelper(0x60020018, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
                   Command, &Options);
   }

   BOOL Application::FindText(LPCTSTR SearchFor, long StartRow, long StartColumn, const VARIANT& Options)
   {
      BOOL result;
      static BYTE parms[] =
      VTS_BSTR VTS_I4 VTS_I4 VTS_VARIANT;
      InvokeHelper(0x60020019, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
                   SearchFor, StartRow, StartColumn, &Options);
      return(result);
   }

   void Application::FlushPrinter()
   {
      InvokeHelper(0x6002001a, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
   }

   CString Application::GetClipboardText()
   {
      CString result;
      InvokeHelper(0x6002001b, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
      return(result);
   }

   BOOL Application::GetCommandGroupProfile(long CmdGroup)
   {
      BOOL result;
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x6002001c, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
                   CmdGroup);
      return(result);
   }

   BOOL Application::GetCommandProfile(LPCTSTR CmdName)
   {
      BOOL result;
      static BYTE parms[] =
      VTS_BSTR;
      InvokeHelper(0x6002001d, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
                   CmdName);
      return(result);
   }

   CString Application::GetText(long StartRow, long StartColumn, long EndRow, long EndColumn, const VARIANT& Options)
   {
      CString result;
      static BYTE parms[] =
      VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_VARIANT;
      InvokeHelper(0x6002001e, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms,
                   StartRow, StartColumn, EndRow, EndColumn, &Options);
      return(result);
   }

   long Application::GetKeyMapCommandType(long Modifiers, LPCTSTR Key)
   {
      long result;
      static BYTE parms[] =
      VTS_I4 VTS_BSTR;
      InvokeHelper(0x6002001f, DISPATCH_METHOD, VT_I4, (void*)&result, parms,
                   Modifiers, Key);
      return(result);
   }

   CString Application::GetKeyMapCommands(long Modifiers, LPCTSTR Key)
   {
      CString result;
      static BYTE parms[] =
      VTS_I4 VTS_BSTR;
      InvokeHelper(0x60020020, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms,
                   Modifiers, Key);
      return(result);
   }

   CString Application::GetOpenFilename(const VARIANT& FileFilter, const VARIANT& FilterIndex, const VARIANT& Title, const VARIANT& ButtonText)
   {
      CString result;
      static BYTE parms[] =
      VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT;
      InvokeHelper(0x60020021, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms,
                   &FileFilter, &FilterIndex, &Title, &ButtonText);
      return(result);
   }

   CString Application::GetSaveAsFilename(const VARIANT& InitialFilename, const VARIANT& FileFilter, const VARIANT& FilterIndex, const VARIANT& Title, const VARIANT& ButtonText)
   {
      CString result;
      static BYTE parms[] =
      VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT;
      InvokeHelper(0x60020022, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms,
                   &InitialFilename, &FileFilter, &FilterIndex, &Title, &ButtonText);
      return(result);
   }

   long Application::GetSerialStatistics(long WhichStatistic)
   {
      long result;
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x60020023, DISPATCH_METHOD, VT_I4, (void*)&result, parms,
                   WhichStatistic);
      return(result);
   }

   void Application::Hangup()
   {
      InvokeHelper(0x60020024, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
   }

   void Application::Help(const VARIANT& HelpTopic, const VARIANT& HelpFile)
   {
      static BYTE parms[] =
      VTS_VARIANT VTS_VARIANT;
      InvokeHelper(0x60020025, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
                   &HelpTopic, &HelpFile);
   }

   CString Application::InputBox(LPCTSTR Prompt, const VARIANT& Title, const VARIANT& Default)
   {
      CString result;
      static BYTE parms[] =
      VTS_BSTR VTS_VARIANT VTS_VARIANT;
      InvokeHelper(0x60020026, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms,
                   Prompt, &Title, &Default);
      return(result);
   }

   void Application::KermitReceiveFile(LPCTSTR LocalFile, LPCTSTR RemoteFile, const VARIANT& TransferType, const VARIANT& IfFileExists)
   {
      static BYTE parms[] =
      VTS_BSTR VTS_BSTR VTS_VARIANT VTS_VARIANT;
      InvokeHelper(0x60020027, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
                   LocalFile, RemoteFile, &TransferType, &IfFileExists);
   }

   void Application::KermitSendFile(LPCTSTR LocalFile, LPCTSTR RemoteFile, const VARIANT& TransferType)
   {
      static BYTE parms[] =
      VTS_BSTR VTS_BSTR VTS_VARIANT;
      InvokeHelper(0x60020028, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
                   LocalFile, RemoteFile, &TransferType);
   }

   void Application::KermitStartServer()
   {
      InvokeHelper(0x60020029, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
   }

   void Application::KermitStopServer(const VARIANT& Logoff)
   {
      static BYTE parms[] =
      VTS_VARIANT;
      InvokeHelper(0x6002002a, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
                   &Logoff);
   }

   void Application::LockProfile(BOOL AllowUnlock, const VARIANT& Password)
   {
      static BYTE parms[] =
      VTS_BOOL VTS_VARIANT;
      InvokeHelper(0x6002002b, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
                   AllowUnlock, &Password);
   }

   long Application::MsgBox(LPCTSTR Message, const VARIANT& Type, const VARIANT& Caption)
   {
      long result;
      static BYTE parms[] =
      VTS_BSTR VTS_VARIANT VTS_VARIANT;
      InvokeHelper(0x6002002c, DISPATCH_METHOD, VT_I4, (void*)&result, parms,
                   Message, &Type, &Caption);
      return(result);
   }

   void Application::NewSession(const VARIANT& SessionType, const VARIANT& SettingsFile)
   {
      static BYTE parms[] =
      VTS_VARIANT VTS_VARIANT;
      InvokeHelper(0x6002002d, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
                   &SessionType, &SettingsFile);
   }

   void Application::OpenSettings(LPCTSTR Filename, const VARIANT& Type)
   {
      static BYTE parms[] =
      VTS_BSTR VTS_VARIANT;
      InvokeHelper(0x6002002e, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
                   Filename, &Type);
   }

   CString Application::PasswordBox(LPCTSTR Prompt, const VARIANT& Title, const VARIANT& Default)
   {
      CString result;
      static BYTE parms[] =
      VTS_BSTR VTS_VARIANT VTS_VARIANT;
      InvokeHelper(0x6002002f, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms,
                   Prompt, &Title, &Default);
      return(result);
   }

   void Application::Paste()
   {
      InvokeHelper(0x60020030, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
   }

   void Application::Print(long Range, const VARIANT& Copies)
   {
      static BYTE parms[] =
      VTS_I4 VTS_VARIANT;
      InvokeHelper(0x60020031, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
                   Range, &Copies);
   }

   void Application::PrintFile(LPCTSTR Filename)
   {
      static BYTE parms[] =
      VTS_BSTR;
      InvokeHelper(0x60020032, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
                   Filename);
   }

   void Application::PrintString(LPCTSTR String)
   {
      static BYTE parms[] =
      VTS_BSTR;
      InvokeHelper(0x60020033, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
                   String);
   }

   void Application::Quit()
   {
      InvokeHelper(0x60020034, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
   }

   CString Application::ReadChars(long Count, const VARIANT& Timeout, const VARIANT& Options)
   {
      CString result;
      static BYTE parms[] =
      VTS_I4 VTS_VARIANT VTS_VARIANT;
      InvokeHelper(0x60020035, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms,
                   Count, &Timeout, &Options);
      return(result);
   }

   CString Application::ReadLine(const VARIANT& Timeout, const VARIANT& Options, VARIANT* SawEndOfLine)
   {
      CString result;
      static BYTE parms[] =
      VTS_VARIANT VTS_VARIANT VTS_PVARIANT;
      InvokeHelper(0x60020036, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms,
                   &Timeout, &Options, SawEndOfLine);
      return(result);
   }

   CString Application::ReadUntil(LPCTSTR UntilChars, const VARIANT& Timeout, const VARIANT& Options, VARIANT* WhichTerminator)
   {
      CString result;
      static BYTE parms[] =
      VTS_BSTR VTS_VARIANT VTS_VARIANT VTS_PVARIANT;
      InvokeHelper(0x60020037, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms,
                   UntilChars, &Timeout, &Options, WhichTerminator);
      return(result);
   }

   void Application::ResetTerminal(long ResetMode)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x60020038, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
                   ResetMode);
   }

   void Application::RestoreDefaults(long SettingType)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x60020039, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
                   SettingType);
   }

   void Application::ResumeConnection(long ConnectionID)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x6002003a, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
                   ConnectionID);
   }

   void Application::RunScript(LPCTSTR ScriptName, const VARIANT& ScriptArguments)
   {
      static BYTE parms[] =
      VTS_BSTR VTS_VARIANT;
      InvokeHelper(0x6002003b, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
                   ScriptName, &ScriptArguments);
   }

   void Application::SaveDisplayMemory(LPCTSTR Filename, const VARIANT& IfFileExists, const VARIANT& Options)
   {
      static BYTE parms[] =
      VTS_BSTR VTS_VARIANT VTS_VARIANT;
      InvokeHelper(0x6002003c, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
                   Filename, &IfFileExists, &Options);
   }

   void Application::SaveSettings(LPCTSTR Filename, const VARIANT& Type, const VARIANT& IfFileExists)
   {
      static BYTE parms[] =
      VTS_BSTR VTS_VARIANT VTS_VARIANT;
      InvokeHelper(0x6002003d, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
                   Filename, &Type, &IfFileExists);
   }

   void Application::SetClipboardText(LPCTSTR ClipboardText)
   {
      static BYTE parms[] =
      VTS_BSTR;
      InvokeHelper(0x6002003e, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
                   ClipboardText);
   }

   void Application::SetCommandGroupProfile(long CmdGroup, BOOL IsEnabled)
   {
      static BYTE parms[] =
      VTS_I4 VTS_BOOL;
      InvokeHelper(0x6002003f, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
                   CmdGroup, IsEnabled);
   }

   void Application::SetCommandProfile(LPCTSTR CmdName, BOOL IsEnabled)
   {
      static BYTE parms[] =
      VTS_BSTR VTS_BOOL;
      InvokeHelper(0x60020040, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
                   CmdName, IsEnabled);
   }

   void Application::SetKeyMap(long Modifiers, LPCTSTR Key, long CommandType, LPCTSTR Commands, const VARIANT& CommandArguments)
   {
      static BYTE parms[] =
      VTS_I4 VTS_BSTR VTS_I4 VTS_BSTR VTS_VARIANT;
      InvokeHelper(0x60020041, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
                   Modifiers, Key, CommandType, Commands, &CommandArguments);
   }

   void Application::SetScanCodeName(long ScanType, long ScanCode, LPCTSTR ScanName)
   {
      static BYTE parms[] =
      VTS_I4 VTS_I4 VTS_BSTR;
      InvokeHelper(0x60020042, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
                   ScanType, ScanCode, ScanName);
   }

   void Application::SelectText(long StartRow, long StartColumn, long EndRow, long EndColumn, const VARIANT& SelectionType)
   {
      static BYTE parms[] =
      VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_VARIANT;
      InvokeHelper(0x60020043, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
                   StartRow, StartColumn, EndRow, EndColumn, &SelectionType);
   }

   void Application::StartRecording()
   {
      InvokeHelper(0x60020044, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
   }

   void Application::StartTrace(LPCTSTR Filename, const VARIANT& IfFileExists, const VARIANT& TraceFormat)
   {
      static BYTE parms[] =
      VTS_BSTR VTS_VARIANT VTS_VARIANT;
      InvokeHelper(0x60020045, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
                   Filename, &IfFileExists, &TraceFormat);
   }

   void Application::StopRecording(LPCTSTR Filename, long Target, const VARIANT& IfFileExists)
   {
      static BYTE parms[] =
      VTS_BSTR VTS_I4 VTS_VARIANT;
      InvokeHelper(0x60020046, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
                   Filename, Target, &IfFileExists);
   }

   void Application::StopScript()
   {
      InvokeHelper(0x60020047, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
   }

   void Application::StopTrace()
   {
      InvokeHelper(0x60020048, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
   }

   long Application::SuspendConnection()
   {
      long result;
      InvokeHelper(0x60020049, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
      return(result);
   }

   void Application::Transmit(LPCTSTR String, const VARIANT& Options)
   {
      static BYTE parms[] =
      VTS_BSTR VTS_VARIANT;
      InvokeHelper(0x6002004a, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
                   String, &Options);
   }

   void Application::TransmitFile(LPCTSTR Filename, const VARIANT& PauseTime, const VARIANT& PromptChar, const VARIANT& Options)
   {
      static BYTE parms[] =
      VTS_BSTR VTS_VARIANT VTS_VARIANT VTS_VARIANT;
      InvokeHelper(0x6002004b, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
                   Filename, &PauseTime, &PromptChar, &Options);
   }

   void Application::TransmitTerminalKey(long KeyID)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x6002004c, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
                   KeyID);
   }

   BOOL Application::UnlockProfile(LPCTSTR Password)
   {
      BOOL result;
      static BYTE parms[] =
      VTS_BSTR;
      InvokeHelper(0x6002004d, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
                   Password);
      return(result);
   }

   void Application::Wait(const VARIANT& HowLong, const VARIANT& Options)
   {
      static BYTE parms[] =
      VTS_VARIANT VTS_VARIANT;
      InvokeHelper(0x6002004e, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
                   &HowLong, &Options);
   }

   void Application::WaitForCall(const VARIANT& Description, const VARIANT& InitString)
   {
      static BYTE parms[] =
      VTS_VARIANT VTS_VARIANT;
      InvokeHelper(0x6002004f, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
                   &Description, &InitString);
   }

   BOOL Application::WaitForHostTrigger(const VARIANT& Timeout, const VARIANT& Options)
   {
      BOOL result;
      static BYTE parms[] =
      VTS_VARIANT VTS_VARIANT;
      InvokeHelper(0x60020050, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
                   &Timeout, &Options);
      return(result);
   }

   BOOL Application::WaitForSilence(const VARIANT& SilenceTime, const VARIANT& Timeout, const VARIANT& Options)
   {
      BOOL result;
      static BYTE parms[] =
      VTS_VARIANT VTS_VARIANT VTS_VARIANT;
      InvokeHelper(0x60020051, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
                   &SilenceTime, &Timeout, &Options);
      return(result);
   }

   BOOL Application::WaitForString(LPCTSTR String, const VARIANT& Timeout, const VARIANT& Options)
   {
      BOOL result;
      static BYTE parms[] =
      VTS_BSTR VTS_VARIANT VTS_VARIANT;
      InvokeHelper(0x60020052, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
                   String, &Timeout, &Options);
      return(result);
   }

   void Application::WaitUntil(DATE DateTime, const VARIANT& Options)
   {
      static BYTE parms[] =
      VTS_DATE VTS_VARIANT;
      InvokeHelper(0x60020054, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
                   DateTime, &Options);
   }

   void Application::WRQReceiveFile(LPCTSTR LocalFile, LPCTSTR RemoteFile, const VARIANT& TransferType, const VARIANT& IfFileExists, const VARIANT& Before, const VARIANT& Since, const VARIANT& Exclude)
   {
      static BYTE parms[] =
      VTS_BSTR VTS_BSTR VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT;
      InvokeHelper(0x60020055, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
                   LocalFile, RemoteFile, &TransferType, &IfFileExists, &Before, &Since, &Exclude);
   }

   void Application::WRQSendFile(LPCTSTR LocalFile, LPCTSTR RemoteFile, const VARIANT& TransferType, const VARIANT& IfFileExists, const VARIANT& Before, const VARIANT& Since, const VARIANT& Exclude, const VARIANT& Attributes)
   {
      static BYTE parms[] =
      VTS_BSTR VTS_BSTR VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT;
      InvokeHelper(0x60020056, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
                   LocalFile, RemoteFile, &TransferType, &IfFileExists, &Before, &Since, &Exclude, &Attributes);
   }

   void Application::WRQStartServer()
   {
      InvokeHelper(0x60020057, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
   }

   void Application::WRQStopServer()
   {
      InvokeHelper(0x60020058, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
   }

   void Application::XmodemReceiveFile(LPCTSTR LocalFile, const VARIANT& TransferType, const VARIANT& IfFileExists)
   {
      static BYTE parms[] =
      VTS_BSTR VTS_VARIANT VTS_VARIANT;
      InvokeHelper(0x60020059, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
                   LocalFile, &TransferType, &IfFileExists);
   }

   void Application::XmodemSendFile(LPCTSTR LocalFile, const VARIANT& TransferType)
   {
      static BYTE parms[] =
      VTS_BSTR VTS_VARIANT;
      InvokeHelper(0x6002005a, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
                   LocalFile, &TransferType);
   }

   void Application::ZmodemReceiveFile(LPCTSTR LocalFile, LPCTSTR RemoteFile, const VARIANT& TransferType, const VARIANT& IfFileExists)
   {
      static BYTE parms[] =
      VTS_BSTR VTS_BSTR VTS_VARIANT VTS_VARIANT;
      InvokeHelper(0x6002005b, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
                   LocalFile, RemoteFile, &TransferType, &IfFileExists);
   }

   void Application::ZmodemSendFile(LPCTSTR LocalFile, LPCTSTR RemoteFile, const VARIANT& TransferType)
   {
      static BYTE parms[] =
      VTS_BSTR VTS_BSTR VTS_VARIANT;
      InvokeHelper(0x6002005c, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
                   LocalFile, RemoteFile, &TransferType);
   }

   BOOL Application::GetAllowScriptInterrupt()
   {
      BOOL result;
      InvokeHelper(0x6002005d, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Application::SetAllowScriptInterrupt(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x6002005d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   long Application::GetAnsiScreenColor()
   {
      long result;
      InvokeHelper(0x6002005f, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
      return(result);
   }

   void Application::SetAnsiScreenColor(long nNewValue)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x6002005f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   nNewValue);
   }

   CString Application::GetAnswerback()
   {
      CString result;
      InvokeHelper(0x60020061, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
      return(result);
   }

   void Application::SetAnswerback(LPCTSTR lpszNewValue)
   {
      static BYTE parms[] =
      VTS_BSTR;
      InvokeHelper(0x60020061, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   lpszNewValue);
   }

   VARIANT Application::GetApplication()
   {
      VARIANT result;
      InvokeHelper(0x60020063, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
      return(result);
   }

   void Application::SetApplication(const VARIANT& newValue)
   {
      static BYTE parms[] =
      VTS_VARIANT;
      InvokeHelper(0x60020063, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   &newValue);
   }

   BOOL Application::GetAutoAnswerback()
   {
      BOOL result;
      InvokeHelper(0x60020065, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Application::SetAutoAnswerback(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x60020065, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   BOOL Application::GetAutoFontSize()
   {
      BOOL result;
      InvokeHelper(0x60020067, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Application::SetAutoFontSize(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x60020067, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   BOOL Application::GetAutoFormFeed()
   {
      BOOL result;
      InvokeHelper(0x60020069, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Application::SetAutoFormFeed(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x60020069, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   BOOL Application::GetAutoLineFeed()
   {
      BOOL result;
      InvokeHelper(0x6002006b, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Application::SetAutoLineFeed(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x6002006b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   BOOL Application::GetAutoRepeat()
   {
      BOOL result;
      InvokeHelper(0x6002006d, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Application::SetAutoRepeat(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x6002006d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   BOOL Application::GetBell()
   {
      BOOL result;
      InvokeHelper(0x6002006f, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Application::SetBell(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x6002006f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   BOOL Application::GetBlinkCharacters()
   {
      BOOL result;
      InvokeHelper(0x60020071, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Application::SetBlinkCharacters(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x60020071, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   CString Application::GetBlockTerminator()
   {
      CString result;
      InvokeHelper(0x60020073, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
      return(result);
   }

   void Application::SetBlockTerminator(LPCTSTR lpszNewValue)
   {
      static BYTE parms[] =
      VTS_BSTR;
      InvokeHelper(0x60020073, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   lpszNewValue);
   }

   BOOL Application::GetBoldCharacters()
   {
      BOOL result;
      InvokeHelper(0x60020075, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Application::SetBoldCharacters(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x60020075, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   BOOL Application::GetBreakEnabled()
   {
      BOOL result;
      InvokeHelper(0x60020077, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Application::SetBreakEnabled(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x60020077, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   long Application::GetBreakLength()
   {
      long result;
      InvokeHelper(0x60020079, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
      return(result);
   }

   void Application::SetBreakLength(long nNewValue)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x60020079, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   nNewValue);
   }

   BOOL Application::GetBypassPrinterDriver()
   {
      BOOL result;
      InvokeHelper(0x6002007b, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Application::SetBypassPrinterDriver(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x6002007b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   BOOL Application::GetCapsLock()
   {
      BOOL result;
      InvokeHelper(0x6002007d, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Application::SetCapsLock(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x6002007d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   CString Application::GetCaption()
   {
      CString result;
      InvokeHelper(0x6002007f, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
      return(result);
   }

   void Application::SetCaption(LPCTSTR lpszNewValue)
   {
      static BYTE parms[] =
      VTS_BSTR;
      InvokeHelper(0x6002007f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   lpszNewValue);
   }

   BOOL Application::GetClosePrinterManually()
   {
      BOOL result;
      InvokeHelper(0x60020081, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Application::SetClosePrinterManually(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x60020081, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   long Application::GetCodePage()
   {
      long result;
      InvokeHelper(0x60020083, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
      return(result);
   }

   void Application::SetCodePage(long nNewValue)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x60020083, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   nNewValue);
   }

   long Application::GetColumnsPerScroll()
   {
      long result;
      InvokeHelper(0x60020085, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
      return(result);
   }

   void Application::SetColumnsPerScroll(long nNewValue)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x60020085, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   nNewValue);
   }

   BOOL Application::GetCompressBlankLines()
   {
      BOOL result;
      InvokeHelper(0x60020087, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Application::SetCompressBlankLines(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x60020087, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   BOOL Application::GetConnected()
   {
      BOOL result;
      InvokeHelper(0x60020089, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Application::SetConnected(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x60020089, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   long Application::GetConnectionID()
   {
      long result;
      InvokeHelper(0x6002008b, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
      return(result);
   }

   void Application::SetConnectionID(long nNewValue)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x6002008b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   nNewValue);
   }

   long Application::GetConnectionIndicator()
   {
      long result;
      InvokeHelper(0x6002008d, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
      return(result);
   }

   void Application::SetConnectionIndicator(long nNewValue)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x6002008d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   nNewValue);
   }

   long Application::GetConnectionError()
   {
      long result;
      InvokeHelper(0x6002008f, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
      return(result);
   }

   void Application::SetConnectionError(long nNewValue)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x6002008f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   nNewValue);
   }

   CString Application::GetConnectionErrorMessage()
   {
      CString result;
      InvokeHelper(0x60020091, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
      return(result);
   }

   void Application::SetConnectionErrorMessage(LPCTSTR lpszNewValue)
   {
      static BYTE parms[] =
      VTS_BSTR;
      InvokeHelper(0x60020091, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   lpszNewValue);
   }

   CString Application::GetConnectionSettings()
   {
      CString result;
      InvokeHelper(0x60020093, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
      return(result);
   }

   void Application::SetConnectionSettings(LPCTSTR lpszNewValue)
   {
      static BYTE parms[] =
      VTS_BSTR;
      InvokeHelper(0x60020093, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   lpszNewValue);
   }

   CString Application::GetConnectionType()
   {
      CString result;
      InvokeHelper(0x60020095, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
      return(result);
   }

   void Application::SetConnectionType(LPCTSTR lpszNewValue)
   {
      static BYTE parms[] =
      VTS_BSTR;
      InvokeHelper(0x60020095, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   lpszNewValue);
   }

   BOOL Application::GetConvertEOLToSeparator()
   {
      BOOL result;
      InvokeHelper(0x60020097, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Application::SetConvertEOLToSeparator(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x60020097, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   BOOL Application::GetConvertMCSToNRC()
   {
      BOOL result;
      InvokeHelper(0x60020099, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Application::SetConvertMCSToNRC(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x60020099, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   BOOL Application::GetConvertNRCToMCS()
   {
      BOOL result;
      InvokeHelper(0x6002009b, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Application::SetConvertNRCToMCS(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x6002009b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   BOOL Application::GetConvertSeparatorToEOL()
   {
      BOOL result;
      InvokeHelper(0x6002009d, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Application::SetConvertSeparatorToEOL(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x6002009d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   BOOL Application::GetCopyGraphicsBackground()
   {
      BOOL result;
      InvokeHelper(0x6002009f, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Application::SetCopyGraphicsBackground(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x6002009f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   BOOL Application::GetCopyGraphicsVGAColors()
   {
      BOOL result;
      InvokeHelper(0x600200a1, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Application::SetCopyGraphicsVGAColors(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x600200a1, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   BOOL Application::GetCursorBlink()
   {
      BOOL result;
      InvokeHelper(0x600200a3, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Application::SetCursorBlink(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x600200a3, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   long Application::GetCursorColumn()
   {
      long result;
      InvokeHelper(0x600200a5, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
      return(result);
   }

   void Application::SetCursorColumn(long nNewValue)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x600200a5, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   nNewValue);
   }

   long Application::GetCursorRow()
   {
      long result;
      InvokeHelper(0x600200a7, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
      return(result);
   }

   void Application::SetCursorRow(long nNewValue)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x600200a7, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   nNewValue);
   }

   long Application::GetCursorShape()
   {
      long result;
      InvokeHelper(0x600200a9, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
      return(result);
   }

   void Application::SetCursorShape(long nNewValue)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x600200a9, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   nNewValue);
   }

   BOOL Application::GetCursorVisible()
   {
      BOOL result;
      InvokeHelper(0x600200ab, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Application::SetCursorVisible(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x600200ab, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   long Application::GetDAResponse()
   {
      long result;
      InvokeHelper(0x600200ad, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
      return(result);
   }

   void Application::SetDAResponse(long nNewValue)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x600200ad, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   nNewValue);
   }

   BOOL Application::GetDcd()
   {
      BOOL result;
      InvokeHelper(0x600200af, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Application::SetDcd(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x600200af, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   BOOL Application::GetDDEServerEnable()
   {
      BOOL result;
      InvokeHelper(0x600200b1, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Application::SetDDEServerEnable(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x600200b1, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   CString Application::GetDDEServerName()
   {
      CString result;
      InvokeHelper(0x600200b3, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
      return(result);
   }

   void Application::SetDDEServerName(LPCTSTR lpszNewValue)
   {
      static BYTE parms[] =
      VTS_BSTR;
      InvokeHelper(0x600200b3, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   lpszNewValue);
   }

   long Application::GetDDETimeout()
   {
      long result;
      InvokeHelper(0x600200b5, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
      return(result);
   }

   void Application::SetDDETimeout(long nNewValue)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x600200b5, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   nNewValue);
   }

   CString Application::GetDefaultPrinter()
   {
      CString result;
      InvokeHelper(0x600200b7, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
      return(result);
   }

   void Application::SetDefaultPrinter(LPCTSTR lpszNewValue)
   {
      static BYTE parms[] =
      VTS_BSTR;
      InvokeHelper(0x600200b7, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   lpszNewValue);
   }

   long Application::GetDefaultScriptLanguage()
   {
      long result;
      InvokeHelper(0x600200b9, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
      return(result);
   }

   void Application::SetDefaultScriptLanguage(long nNewValue)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x600200b9, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   nNewValue);
   }

   BOOL Application::GetDeleteTrailingSpaces()
   {
      BOOL result;
      InvokeHelper(0x600200bb, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Application::SetDeleteTrailingSpaces(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x600200bb, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   long Application::GetDisplayColumns()
   {
      long result;
      InvokeHelper(0x600200bd, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
      return(result);
   }

   void Application::SetDisplayColumns(long nNewValue)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x600200bd, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   nNewValue);
   }

   long Application::GetDisplayMemoryBlocks()
   {
      long result;
      InvokeHelper(0x600200bf, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
      return(result);
   }

   void Application::SetDisplayMemoryBlocks(long nNewValue)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x600200bf, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   nNewValue);
   }

   long Application::GetDisplayMemoryTopRow()
   {
      long result;
      InvokeHelper(0x600200c1, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
      return(result);
   }

   void Application::SetDisplayMemoryTopRow(long nNewValue)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x600200c1, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   nNewValue);
   }

   long Application::GetDisplayRows()
   {
      long result;
      InvokeHelper(0x600200c3, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
      return(result);
   }

   void Application::SetDisplayRows(long nNewValue)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x600200c3, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   nNewValue);
   }

   BOOL Application::GetEndOfLineWrap()
   {
      BOOL result;
      InvokeHelper(0x600200c5, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Application::SetEndOfLineWrap(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x600200c5, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   BOOL Application::GetEnqAck()
   {
      BOOL result;
      InvokeHelper(0x600200c7, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Application::SetEnqAck(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x600200c7, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   CString Application::GetFontName()
   {
      CString result;
      InvokeHelper(0x600200c9, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
      return(result);
   }

   void Application::SetFontName(LPCTSTR lpszNewValue)
   {
      static BYTE parms[] =
      VTS_BSTR;
      InvokeHelper(0x600200c9, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   lpszNewValue);
   }

   long Application::GetFontSize()
   {
      long result;
      InvokeHelper(0x600200cb, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
      return(result);
   }

   void Application::SetFontSize(long nNewValue)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x600200cb, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   nNewValue);
   }

   BOOL Application::GetForceAutoRepeat()
   {
      BOOL result;
      InvokeHelper(0x600200cd, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Application::SetForceAutoRepeat(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x600200cd, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   CString Application::GetFullName()
   {
      CString result;
      InvokeHelper(0x600200d3, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
      return(result);
   }

   void Application::SetFullName(LPCTSTR lpszNewValue)
   {
      static BYTE parms[] =
      VTS_BSTR;
      InvokeHelper(0x600200d3, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   lpszNewValue);
   }

   long Application::GetGraphicsDestination()
   {
      long result;
      InvokeHelper(0x600200d5, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
      return(result);
   }

   void Application::SetGraphicsDestination(long nNewValue)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x600200d5, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   nNewValue);
   }

   BOOL Application::GetGraphicsFixScreen()
   {
      BOOL result;
      InvokeHelper(0x600200d7, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Application::SetGraphicsFixScreen(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x600200d7, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   long Application::GetGraphicsLevel()
   {
      long result;
      InvokeHelper(0x600200d9, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
      return(result);
   }

   void Application::SetGraphicsLevel(long nNewValue)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x600200d9, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   nNewValue);
   }

   BOOL Application::GetGraphicsOutputCursor()
   {
      BOOL result;
      InvokeHelper(0x600200db, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Application::SetGraphicsOutputCursor(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x600200db, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   long Application::GetGraphicsPrintMode()
   {
      long result;
      InvokeHelper(0x600200dd, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
      return(result);
   }

   void Application::SetGraphicsPrintMode(long nNewValue)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x600200dd, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   nNewValue);
   }

   BOOL Application::GetGraphicsScrolling()
   {
      BOOL result;
      InvokeHelper(0x600200df, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Application::SetGraphicsScrolling(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x600200df, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   long Application::GetGraphicsTerminalType()
   {
      long result;
      InvokeHelper(0x600200e1, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
      return(result);
   }

   void Application::SetGraphicsTerminalType(long nNewValue)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x600200e1, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   nNewValue);
   }

   long Application::GetHeight()
   {
      long result;
      InvokeHelper(0x600200e3, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
      return(result);
   }

   void Application::SetHeight(long nNewValue)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x600200e3, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   nNewValue);
   }

   BOOL Application::GetHorizontalCoupling()
   {
      BOOL result;
      InvokeHelper(0x600200e5, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Application::SetHorizontalCoupling(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x600200e5, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   long Application::GetHostCharacterSet()
   {
      long result;
      InvokeHelper(0x600200e7, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
      return(result);
   }

   void Application::SetHostCharacterSet(long nNewValue)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x600200e7, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   nNewValue);
   }

   BOOL Application::GetHostColorChanges()
   {
      BOOL result;
      InvokeHelper(0x600200e9, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Application::SetHostColorChanges(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x600200e9, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   long Application::GetHostStatusLine()
   {
      long result;
      InvokeHelper(0x600200eb, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
      return(result);
   }

   void Application::SetHostStatusLine(long nNewValue)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x600200eb, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   nNewValue);
   }

   CString Application::GetHostTriggerCharacter()
   {
      CString result;
      InvokeHelper(0x600200ed, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
      return(result);
   }

   void Application::SetHostTriggerCharacter(LPCTSTR lpszNewValue)
   {
      static BYTE parms[] =
      VTS_BSTR;
      InvokeHelper(0x600200ed, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   lpszNewValue);
   }

   CString Application::GetHostsFile()
   {
      CString result;
      InvokeHelper(0x600200ef, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
      return(result);
   }

   void Application::SetHostsFile(LPCTSTR lpszNewValue)
   {
      static BYTE parms[] =
      VTS_BSTR;
      InvokeHelper(0x600200ef, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   lpszNewValue);
   }

   BOOL Application::GetImageCurrentColors()
   {
      BOOL result;
      InvokeHelper(0x600200f1, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Application::SetImageCurrentColors(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x600200f1, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   long Application::GetImageDither()
   {
      long result;
      InvokeHelper(0x600200f3, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
      return(result);
   }

   void Application::SetImageDither(long nNewValue)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x600200f3, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   nNewValue);
   }

   BOOL Application::GetImageFleshtones()
   {
      BOOL result;
      InvokeHelper(0x600200f5, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Application::SetImageFleshtones(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x600200f5, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   BOOL Application::GetInsertMode()
   {
      BOOL result;
      InvokeHelper(0x600200f7, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Application::SetInsertMode(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x600200f7, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   BOOL Application::GetInverseVideo()
   {
      BOOL result;
      InvokeHelper(0x600200fb, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Application::SetInverseVideo(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x600200fb, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   long Application::GetJumpScrollSpeed()
   {
      long result;
      InvokeHelper(0x600200fd, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
      return(result);
   }

   void Application::SetJumpScrollSpeed(long nNewValue)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x600200fd, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   nNewValue);
   }

   BOOL Application::GetKatakanaDisplay()
   {
      BOOL result;
      InvokeHelper(0x600200ff, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Application::SetKatakanaDisplay(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x600200ff, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   BOOL Application::GetKermitAutomaticServer()
   {
      BOOL result;
      InvokeHelper(0x60020101, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Application::SetKermitAutomaticServer(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x60020101, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   long Application::GetKermitChecksum()
   {
      long result;
      InvokeHelper(0x60020103, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
      return(result);
   }

   void Application::SetKermitChecksum(long nNewValue)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x60020103, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   nNewValue);
   }

   long Application::GetKermitPacketSize()
   {
      long result;
      InvokeHelper(0x60020105, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
      return(result);
   }

   void Application::SetKermitPacketSize(long nNewValue)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x60020105, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   nNewValue);
   }

   CString Application::GetKermitReceiveEndCharacter()
   {
      CString result;
      InvokeHelper(0x60020107, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
      return(result);
   }

   void Application::SetKermitReceiveEndCharacter(LPCTSTR lpszNewValue)
   {
      static BYTE parms[] =
      VTS_BSTR;
      InvokeHelper(0x60020107, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   lpszNewValue);
   }

   CString Application::GetKermitReceiveStartCharacter()
   {
      CString result;
      InvokeHelper(0x60020109, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
      return(result);
   }

   void Application::SetKermitReceiveStartCharacter(LPCTSTR lpszNewValue)
   {
      static BYTE parms[] =
      VTS_BSTR;
      InvokeHelper(0x60020109, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   lpszNewValue);
   }

   CString Application::GetKermitReceiveStartupCommand()
   {
      CString result;
      InvokeHelper(0x6002010b, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
      return(result);
   }

   void Application::SetKermitReceiveStartupCommand(LPCTSTR lpszNewValue)
   {
      static BYTE parms[] =
      VTS_BSTR;
      InvokeHelper(0x6002010b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   lpszNewValue);
   }

   CString Application::GetKermitSendEndCharacter()
   {
      CString result;
      InvokeHelper(0x6002010d, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
      return(result);
   }

   void Application::SetKermitSendEndCharacter(LPCTSTR lpszNewValue)
   {
      static BYTE parms[] =
      VTS_BSTR;
      InvokeHelper(0x6002010d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   lpszNewValue);
   }

   CString Application::GetKermitSendStartCharacter()
   {
      CString result;
      InvokeHelper(0x6002010f, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
      return(result);
   }

   void Application::SetKermitSendStartCharacter(LPCTSTR lpszNewValue)
   {
      static BYTE parms[] =
      VTS_BSTR;
      InvokeHelper(0x6002010f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   lpszNewValue);
   }

   CString Application::GetKermitSendStartupCommand()
   {
      CString result;
      InvokeHelper(0x60020111, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
      return(result);
   }

   void Application::SetKermitSendStartupCommand(LPCTSTR lpszNewValue)
   {
      static BYTE parms[] =
      VTS_BSTR;
      InvokeHelper(0x60020111, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   lpszNewValue);
   }

   CString Application::GetKermitServerStartupCommand()
   {
      CString result;
      InvokeHelper(0x60020113, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
      return(result);
   }

   void Application::SetKermitServerStartupCommand(LPCTSTR lpszNewValue)
   {
      static BYTE parms[] =
      VTS_BSTR;
      InvokeHelper(0x60020113, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   lpszNewValue);
   }

   long Application::GetKermitTransferType()
   {
      long result;
      InvokeHelper(0x60020115, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
      return(result);
   }

   void Application::SetKermitTransferType(long nNewValue)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x60020115, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   nNewValue);
   }

   BOOL Application::GetKermitTranslateCharacters()
   {
      BOOL result;
      InvokeHelper(0x60020117, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Application::SetKermitTranslateCharacters(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x60020117, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   BOOL Application::GetKermitTranslateFilenames()
   {
      BOOL result;
      InvokeHelper(0x60020119, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Application::SetKermitTranslateFilenames(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x60020119, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   long Application::GetKermitWindowSize()
   {
      long result;
      InvokeHelper(0x6002011b, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
      return(result);
   }

   void Application::SetKermitWindowSize(long nNewValue)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x6002011b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   nNewValue);
   }

   BOOL Application::GetKeyboardLocked()
   {
      BOOL result;
      InvokeHelper(0x6002011d, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Application::SetKeyboardLocked(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x6002011d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   long Application::GetLanguage()
   {
      long result;
      InvokeHelper(0x6002011f, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
      return(result);
   }

   void Application::SetLanguage(long nNewValue)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x6002011f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   nNewValue);
   }

   long Application::GetLeft()
   {
      long result;
      InvokeHelper(0x60020121, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
      return(result);
   }

   void Application::SetLeft(long nNewValue)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x60020121, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   nNewValue);
   }

   BOOL Application::GetLocalEcho()
   {
      BOOL result;
      InvokeHelper(0x60020123, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Application::SetLocalEcho(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x60020123, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   BOOL Application::GetMacrographReports()
   {
      BOOL result;
      InvokeHelper(0x60020125, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Application::SetMacrographReports(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x60020125, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   BOOL Application::GetMaintainUnscaledImage()
   {
      BOOL result;
      InvokeHelper(0x60020127, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Application::SetMaintainUnscaledImage(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x60020127, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   BOOL Application::GetMarginBell()
   {
      BOOL result;
      InvokeHelper(0x60020129, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Application::SetMarginBell(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x60020129, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   BOOL Application::GetMultiplePageTerminal()
   {
      BOOL result;
      InvokeHelper(0x6002012b, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Application::SetMultiplePageTerminal(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x6002012b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   CString Application::GetName()
   {
      CString result;
      InvokeHelper(0x6002012d, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
      return(result);
   }

   void Application::SetName(LPCTSTR lpszNewValue)
   {
      static BYTE parms[] =
      VTS_BSTR;
      InvokeHelper(0x6002012d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   lpszNewValue);
   }

   long Application::GetNationalReplacementSet()
   {
      long result;
      InvokeHelper(0x6002012f, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
      return(result);
   }

   void Application::SetNationalReplacementSet(long nNewValue)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x6002012f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   nNewValue);
   }

   CString Application::GetNativeOS()
   {
      CString result;
      InvokeHelper(0x60020131, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
      return(result);
   }

   void Application::SetNativeOS(LPCTSTR lpszNewValue)
   {
      static BYTE parms[] =
      VTS_BSTR;
      InvokeHelper(0x60020131, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   lpszNewValue);
   }

   BOOL Application::GetNewPageOnClear()
   {
      BOOL result;
      InvokeHelper(0x60020133, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Application::SetNewPageOnClear(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x60020133, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   BOOL Application::GetNumLock()
   {
      BOOL result;
      InvokeHelper(0x60020135, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Application::SetNumLock(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x60020135, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   CString Application::GetOLEServerName()
   {
      CString result;
      InvokeHelper(0x60020137, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
      return(result);
   }

   void Application::SetOLEServerName(LPCTSTR lpszNewValue)
   {
      static BYTE parms[] =
      VTS_BSTR;
      InvokeHelper(0x60020137, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   lpszNewValue);
   }

   BOOL Application::GetOnline()
   {
      BOOL result;
      InvokeHelper(0x60020139, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Application::SetOnline(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x60020139, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   long Application::GetPPLActivityTimeout()
   {
      long result;
      InvokeHelper(0x6002013b, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
      return(result);
   }

   void Application::SetPPLActivityTimeout(long nNewValue)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x6002013b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   nNewValue);
   }

   CString Application::GetPPLStartupCommand()
   {
      CString result;
      InvokeHelper(0x6002013d, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
      return(result);
   }

   void Application::SetPPLStartupCommand(LPCTSTR lpszNewValue)
   {
      static BYTE parms[] =
      VTS_BSTR;
      InvokeHelper(0x6002013d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   lpszNewValue);
   }

   BOOL Application::GetPageCoupling()
   {
      BOOL result;
      InvokeHelper(0x6002013f, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Application::SetPageCoupling(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x6002013f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   VARIANT Application::GetParent()
   {
      VARIANT result;
      InvokeHelper(0x60020141, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
      return(result);
   }

   void Application::SetParent(const VARIANT& newValue)
   {
      static BYTE parms[] =
      VTS_VARIANT;
      InvokeHelper(0x60020141, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   &newValue);
   }

   long Application::GetPasteBufferSize()
   {
      long result;
      InvokeHelper(0x60020143, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
      return(result);
   }

   void Application::SetPasteBufferSize(long nNewValue)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x60020143, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   nNewValue);
   }

   long Application::GetPasteDelay()
   {
      long result;
      InvokeHelper(0x60020145, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
      return(result);
   }

   void Application::SetPasteDelay(long nNewValue)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x60020145, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   nNewValue);
   }

   CString Application::GetPath()
   {
      CString result;
      InvokeHelper(0x60020147, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
      return(result);
   }

   void Application::SetPath(LPCTSTR lpszNewValue)
   {
      static BYTE parms[] =
      VTS_BSTR;
      InvokeHelper(0x60020147, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   lpszNewValue);
   }

   BOOL Application::GetPreserveNRC()
   {
      BOOL result;
      InvokeHelper(0x60020149, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Application::SetPreserveNRC(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x60020149, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   long Application::GetPrinterBottomMargin()
   {
      long result;
      InvokeHelper(0x6002014b, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
      return(result);
   }

   void Application::SetPrinterBottomMargin(long nNewValue)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x6002014b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   nNewValue);
   }

   long Application::GetPrinterColumns()
   {
      long result;
      InvokeHelper(0x6002014d, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
      return(result);
   }

   void Application::SetPrinterColumns(long nNewValue)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x6002014d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   nNewValue);
   }

   CString Application::GetPrintToFile()
   {
      CString result;
      InvokeHelper(0x6002014f, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
      return(result);
   }

   void Application::SetPrintToFile(LPCTSTR lpszNewValue)
   {
      static BYTE parms[] =
      VTS_BSTR;
      InvokeHelper(0x6002014f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   lpszNewValue);
   }

   CString Application::GetPrinterFontName()
   {
      CString result;
      InvokeHelper(0x60020151, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
      return(result);
   }

   void Application::SetPrinterFontName(LPCTSTR lpszNewValue)
   {
      static BYTE parms[] =
      VTS_BSTR;
      InvokeHelper(0x60020151, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   lpszNewValue);
   }

   BOOL Application::GetPrinterInverseFont()
   {
      BOOL result;
      InvokeHelper(0x60020153, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Application::SetPrinterInverseFont(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x60020153, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   BOOL Application::GetPrinterLogging()
   {
      BOOL result;
      InvokeHelper(0x60020155, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Application::SetPrinterLogging(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x60020155, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   BOOL Application::GetPrinterPassThroughConversion()
   {
      BOOL result;
      InvokeHelper(0x60020157, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Application::SetPrinterPassThroughConversion(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x60020157, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   long Application::GetPrinterRows()
   {
      long result;
      InvokeHelper(0x60020159, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
      return(result);
   }

   void Application::SetPrinterRows(long nNewValue)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x60020159, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   nNewValue);
   }

   long Application::GetPrinterTimeout()
   {
      long result;
      InvokeHelper(0x6002015b, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
      return(result);
   }

   void Application::SetPrinterTimeout(long nNewValue)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x6002015b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   nNewValue);
   }

   BOOL Application::GetProcessDataComm()
   {
      BOOL result;
      InvokeHelper(0x6002015d, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Application::SetProcessDataComm(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x6002015d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   BOOL Application::GetReadCtrlZAsEOF()
   {
      BOOL result;
      InvokeHelper(0x6002015f, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Application::SetReadCtrlZAsEOF(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x6002015f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   BOOL Application::GetReadTabAsSpaces()
   {
      BOOL result;
      InvokeHelper(0x60020161, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Application::SetReadTabAsSpaces(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x60020161, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   BOOL Application::GetReGISAlwaysGraphics()
   {
      BOOL result;
      InvokeHelper(0x60020163, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Application::SetReGISAlwaysGraphics(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x60020163, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   BOOL Application::GetReportErrors()
   {
      BOOL result;
      InvokeHelper(0x60020165, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Application::SetReportErrors(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x60020165, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   BOOL Application::GetRestoreTextColors()
   {
      BOOL result;
      InvokeHelper(0x60020167, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Application::SetRestoreTextColors(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x60020167, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   BOOL Application::GetSaveFromScrollingRegion()
   {
      BOOL result;
      InvokeHelper(0x60020169, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Application::SetSaveFromScrollingRegion(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x60020169, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   BOOL Application::GetSavePasswords()
   {
      BOOL result;
      InvokeHelper(0x6002016b, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Application::SetSavePasswords(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x6002016b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   BOOL Application::GetSaveWindowPosition()
   {
      BOOL result;
      InvokeHelper(0x6002016d, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Application::SetSaveWindowPosition(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x6002016d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   long Application::GetScreenTopRow()
   {
      long result;
      InvokeHelper(0x6002016f, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
      return(result);
   }

   void Application::SetScreenTopRow(long nNewValue)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x6002016f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   nNewValue);
   }

   long Application::GetScrollOptimization()
   {
      long result;
      InvokeHelper(0x60020171, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
      return(result);
   }

   void Application::SetScrollOptimization(long nNewValue)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x60020171, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   nNewValue);
   }

   long Application::GetSelectionEndColumn()
   {
      long result;
      InvokeHelper(0x60020173, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
      return(result);
   }

   void Application::SetSelectionEndColumn(long nNewValue)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x60020173, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   nNewValue);
   }

   long Application::GetSelectionEndRow()
   {
      long result;
      InvokeHelper(0x60020175, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
      return(result);
   }

   void Application::SetSelectionEndRow(long nNewValue)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x60020175, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   nNewValue);
   }

   long Application::GetSelectionStartColumn()
   {
      long result;
      InvokeHelper(0x60020177, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
      return(result);
   }

   void Application::SetSelectionStartColumn(long nNewValue)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x60020177, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   nNewValue);
   }

   long Application::GetSelectionStartRow()
   {
      long result;
      InvokeHelper(0x60020179, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
      return(result);
   }

   void Application::SetSelectionStartRow(long nNewValue)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x60020179, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   nNewValue);
   }

   long Application::GetSelectionType()
   {
      long result;
      InvokeHelper(0x6002017b, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
      return(result);
   }

   void Application::SetSelectionType(long nNewValue)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x6002017b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   nNewValue);
   }

   CString Application::GetSerialNumber()
   {
      CString result;
      InvokeHelper(0x6002017d, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
      return(result);
   }

   void Application::SetSerialNumber(LPCTSTR lpszNewValue)
   {
      static BYTE parms[] =
      VTS_BSTR;
      InvokeHelper(0x6002017d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   lpszNewValue);
   }

   CString Application::GetSettingsAuthor()
   {
      CString result;
      InvokeHelper(0x6002017f, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
      return(result);
   }

   void Application::SetSettingsAuthor(LPCTSTR lpszNewValue)
   {
      static BYTE parms[] =
      VTS_BSTR;
      InvokeHelper(0x6002017f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   lpszNewValue);
   }

   CString Application::GetSettingsComments()
   {
      CString result;
      InvokeHelper(0x60020181, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
      return(result);
   }

   void Application::SetSettingsComments(LPCTSTR lpszNewValue)
   {
      static BYTE parms[] =
      VTS_BSTR;
      InvokeHelper(0x60020181, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   lpszNewValue);
   }

   CString Application::GetSettingsFile()
   {
      CString result;
      InvokeHelper(0x60020183, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
      return(result);
   }

   void Application::SetSettingsFile(LPCTSTR lpszNewValue)
   {
      static BYTE parms[] =
      VTS_BSTR;
      InvokeHelper(0x60020183, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   lpszNewValue);
   }

   CString Application::GetSettingsTitle()
   {
      CString result;
      InvokeHelper(0x60020185, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
      return(result);
   }

   void Application::SetSettingsTitle(LPCTSTR lpszNewValue)
   {
      static BYTE parms[] =
      VTS_BSTR;
      InvokeHelper(0x60020185, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   lpszNewValue);
   }

   BOOL Application::GetShowControlCharacters()
   {
      BOOL result;
      InvokeHelper(0x60020187, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Application::SetShowControlCharacters(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x60020187, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   BOOL Application::GetShowTerminalFrame()
   {
      BOOL result;
      InvokeHelper(0x60020189, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Application::SetShowTerminalFrame(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x60020189, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   BOOL Application::GetShowTerminalKeyboard()
   {
      BOOL result;
      InvokeHelper(0x6002018b, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Application::SetShowTerminalKeyboard(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x6002018b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   BOOL Application::GetShowToolbar()
   {
      BOOL result;
      InvokeHelper(0x6002018d, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Application::SetShowToolbar(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x6002018d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   long Application::GetSingleByteUPSS()
   {
      long result;
      InvokeHelper(0x6002018f, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
      return(result);
   }

   void Application::SetSingleByteUPSS(long nNewValue)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x6002018f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   nNewValue);
   }

   BOOL Application::GetSmoothScroll()
   {
      BOOL result;
      InvokeHelper(0x60020191, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Application::SetSmoothScroll(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x60020191, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   long Application::GetSpacesPerTab()
   {
      long result;
      InvokeHelper(0x60020193, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
      return(result);
   }

   void Application::SetSpacesPerTab(long nNewValue)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x60020193, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   nNewValue);
   }

   long Application::GetStartupAction()
   {
      long result;
      InvokeHelper(0x60020195, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
      return(result);
   }

   void Application::SetStartupAction(long nNewValue)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x60020195, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   nNewValue);
   }

   CString Application::GetStartupConnection()
   {
      CString result;
      InvokeHelper(0x60020197, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
      return(result);
   }

   void Application::SetStartupConnection(LPCTSTR lpszNewValue)
   {
      static BYTE parms[] =
      VTS_BSTR;
      InvokeHelper(0x60020197, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   lpszNewValue);
   }

   CString Application::GetStatusBar()
   {
      CString result;
      InvokeHelper(0x60020199, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
      return(result);
   }

   void Application::SetStatusBar(LPCTSTR lpszNewValue)
   {
      static BYTE parms[] =
      VTS_BSTR;
      InvokeHelper(0x60020199, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   lpszNewValue);
   }

   long Application::GetTerminalClass()
   {
      long result;
      InvokeHelper(0x6002019b, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
      return(result);
   }

   void Application::SetTerminalClass(long nNewValue)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x6002019b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   nNewValue);
   }

   long Application::GetTerminalSound()
   {
      long result;
      InvokeHelper(0x6002019d, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
      return(result);
   }

   void Application::SetTerminalSound(long nNewValue)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x6002019d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   nNewValue);
   }

   long Application::GetTerminalType()
   {
      long result;
      InvokeHelper(0x6002019f, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
      return(result);
   }

   void Application::SetTerminalType(long nNewValue)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x6002019f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   nNewValue);
   }

   long Application::GetTextFileCharacterSet()
   {
      long result;
      InvokeHelper(0x600201a1, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
      return(result);
   }

   void Application::SetTextFileCharacterSet(long nNewValue)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x600201a1, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   nNewValue);
   }

   long Application::GetTop()
   {
      long result;
      InvokeHelper(0x600201a3, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
      return(result);
   }

   void Application::SetTop(long nNewValue)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x600201a3, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   nNewValue);
   }

   long Application::GetTransfer8Dot3FilenameCase()
   {
      long result;
      InvokeHelper(0x600201a5, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
      return(result);
   }

   void Application::SetTransfer8Dot3FilenameCase(long nNewValue)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x600201a5, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   nNewValue);
   }

   long Application::GetTransferDefaultProtocol()
   {
      long result;
      InvokeHelper(0x600201a7, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
      return(result);
   }

   void Application::SetTransferDefaultProtocol(long nNewValue)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x600201a7, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   nNewValue);
   }

   CString Application::GetTransferDownloadDirectory()
   {
      CString result;
      InvokeHelper(0x600201a9, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
      return(result);
   }

   void Application::SetTransferDownloadDirectory(LPCTSTR lpszNewValue)
   {
      static BYTE parms[] =
      VTS_BSTR;
      InvokeHelper(0x600201a9, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   lpszNewValue);
   }

   long Application::GetTransferIfFileExistsDefault()
   {
      long result;
      InvokeHelper(0x600201ab, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
      return(result);
   }

   void Application::SetTransferIfFileExistsDefault(long nNewValue)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x600201ab, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   nNewValue);
   }

   BOOL Application::GetTransferReceiveAs8Dot3()
   {
      BOOL result;
      InvokeHelper(0x600201ad, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Application::SetTransferReceiveAs8Dot3(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x600201ad, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   long Application::GetTransferReceiveTimeout()
   {
      long result;
      InvokeHelper(0x600201af, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
      return(result);
   }

   void Application::SetTransferReceiveTimeout(long nNewValue)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x600201af, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   nNewValue);
   }

   long Application::GetTransferRetryLimit()
   {
      long result;
      InvokeHelper(0x600201b1, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
      return(result);
   }

   void Application::SetTransferRetryLimit(long nNewValue)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x600201b1, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   nNewValue);
   }

   BOOL Application::GetTransferSpacesToUnderscores()
   {
      BOOL result;
      InvokeHelper(0x600201b3, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Application::SetTransferSpacesToUnderscores(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x600201b3, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   long Application::GetTransferStartTimeout()
   {
      long result;
      InvokeHelper(0x600201b5, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
      return(result);
   }

   void Application::SetTransferStartTimeout(long nNewValue)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x600201b5, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   nNewValue);
   }

   BOOL Application::GetTransferStatusWindow()
   {
      BOOL result;
      InvokeHelper(0x600201b7, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Application::SetTransferStatusWindow(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x600201b7, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   BOOL Application::GetTransferUnderscoresToSpaces()
   {
      BOOL result;
      InvokeHelper(0x600201b9, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Application::SetTransferUnderscoresToSpaces(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x600201b9, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   BOOL Application::GetTranslateCharacters()
   {
      BOOL result;
      InvokeHelper(0x600201bb, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Application::SetTranslateCharacters(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x600201bb, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   BOOL Application::GetTranslatePrintedCharacters()
   {
      BOOL result;
      InvokeHelper(0x600201bd, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Application::SetTranslatePrintedCharacters(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x600201bd, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   BOOL Application::GetTransmitXonXoff()
   {
      BOOL result;
      InvokeHelper(0x600201bf, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Application::SetTransmitXonXoff(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x600201bf, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   BOOL Application::GetUnderlineCharacters()
   {
      BOOL result;
      InvokeHelper(0x600201c1, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Application::SetUnderlineCharacters(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x600201c1, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   BOOL Application::GetUseAnsiColor()
   {
      BOOL result;
      InvokeHelper(0x600201c3, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Application::SetUseAnsiColor(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x600201c3, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   BOOL Application::GetUseDefaultPrinterFont()
   {
      BOOL result;
      InvokeHelper(0x600201c5, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Application::SetUseDefaultPrinterFont(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x600201c5, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   BOOL Application::GetUseNRC()
   {
      BOOL result;
      InvokeHelper(0x600201c7, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Application::SetUseNRC(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x600201c7, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   BOOL Application::GetUserDefinedKeysLocked()
   {
      BOOL result;
      InvokeHelper(0x600201c9, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Application::SetUserDefinedKeysLocked(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x600201c9, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   CString Application::GetUserDirectory()
   {
      CString result;
      InvokeHelper(0x600201cb, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
      return(result);
   }

   void Application::SetUserDirectory(LPCTSTR lpszNewValue)
   {
      static BYTE parms[] =
      VTS_BSTR;
      InvokeHelper(0x600201cb, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   lpszNewValue);
   }

   BOOL Application::GetUserFeaturesLocked()
   {
      BOOL result;
      InvokeHelper(0x600201cd, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Application::SetUserFeaturesLocked(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x600201cd, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   long Application::GetVTBackspaceSends()
   {
      long result;
      InvokeHelper(0x600201cf, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
      return(result);
   }

   void Application::SetVTBackspaceSends(long nNewValue)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x600201cf, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   nNewValue);
   }

   long Application::GetVTCursorKeyMode()
   {
      long result;
      InvokeHelper(0x600201d1, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
      return(result);
   }

   void Application::SetVTCursorKeyMode(long nNewValue)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x600201d1, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   nNewValue);
   }

   long Application::GetVTKeypadMode()
   {
      long result;
      InvokeHelper(0x600201d3, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
      return(result);
   }

   void Application::SetVTKeypadMode(long nNewValue)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x600201d3, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   nNewValue);
   }

   BOOL Application::GetVTTek()
   {
      BOOL result;
      InvokeHelper(0x600201d5, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Application::SetVTTek(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x600201d5, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   long Application::GetVersionMajor()
   {
      long result;
      InvokeHelper(0x600201d7, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
      return(result);
   }

   void Application::SetVersionMajor(long nNewValue)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x600201d7, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   nNewValue);
   }

   long Application::GetVersionMinor()
   {
      long result;
      InvokeHelper(0x600201d9, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
      return(result);
   }

   void Application::SetVersionMinor(long nNewValue)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x600201d9, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   nNewValue);
   }

   CString Application::GetVersionString()
   {
      CString result;
      InvokeHelper(0x600201db, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
      return(result);
   }

   void Application::SetVersionString(LPCTSTR lpszNewValue)
   {
      static BYTE parms[] =
      VTS_BSTR;
      InvokeHelper(0x600201db, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   lpszNewValue);
   }

   BOOL Application::GetVerticalCoupling()
   {
      BOOL result;
      InvokeHelper(0x600201dd, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Application::SetVerticalCoupling(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x600201dd, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   BOOL Application::GetVisible()
   {
      BOOL result;
      InvokeHelper(0x600201df, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Application::SetVisible(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x600201df, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   BOOL Application::GetWeakDCS()
   {
      BOOL result;
      InvokeHelper(0x600201e1, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Application::SetWeakDCS(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x600201e1, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   long Application::GetWidth()
   {
      long result;
      InvokeHelper(0x600201e3, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
      return(result);
   }

   void Application::SetWidth(long nNewValue)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x600201e3, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   nNewValue);
   }

   long Application::GetWindowState()
   {
      long result;
      InvokeHelper(0x600201e5, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
      return(result);
   }

   void Application::SetWindowState(long nNewValue)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x600201e5, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   nNewValue);
   }

   BOOL Application::GetWriteCtrlZAsEOF()
   {
      BOOL result;
      InvokeHelper(0x600201e7, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Application::SetWriteCtrlZAsEOF(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x600201e7, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   BOOL Application::GetWriteSpacesAsTab()
   {
      BOOL result;
      InvokeHelper(0x600201e9, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Application::SetWriteSpacesAsTab(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x600201e9, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   long Application::GetWRQCompression()
   {
      long result;
      InvokeHelper(0x600201eb, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
      return(result);
   }

   void Application::SetWRQCompression(long nNewValue)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x600201eb, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   nNewValue);
   }

   CString Application::GetWRQEndCharacter()
   {
      CString result;
      InvokeHelper(0x600201ed, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
      return(result);
   }

   void Application::SetWRQEndCharacter(LPCTSTR lpszNewValue)
   {
      static BYTE parms[] =
      VTS_BSTR;
      InvokeHelper(0x600201ed, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   lpszNewValue);
   }

   CString Application::GetWRQExtraCharacters()
   {
      CString result;
      InvokeHelper(0x600201ef, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
      return(result);
   }

   void Application::SetWRQExtraCharacters(LPCTSTR lpszNewValue)
   {
      static BYTE parms[] =
      VTS_BSTR;
      InvokeHelper(0x600201ef, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   lpszNewValue);
   }

   long Application::GetWRQFastFileTransfer()
   {
      long result;
      InvokeHelper(0x600201f1, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
      return(result);
   }

   void Application::SetWRQFastFileTransfer(long nNewValue)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x600201f1, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   nNewValue);
   }

   long Application::GetWRQFrameSize()
   {
      long result;
      InvokeHelper(0x600201f3, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
      return(result);
   }

   void Application::SetWRQFrameSize(long nNewValue)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x600201f3, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   nNewValue);
   }

   CString Application::GetWRQFrameTerminator()
   {
      CString result;
      InvokeHelper(0x600201f5, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
      return(result);
   }

   void Application::SetWRQFrameTerminator(LPCTSTR lpszNewValue)
   {
      static BYTE parms[] =
      VTS_BSTR;
      InvokeHelper(0x600201f5, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   lpszNewValue);
   }

   CString Application::GetWRQHostErrorMessage()
   {
      CString result;
      InvokeHelper(0x600201f7, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
      return(result);
   }

   void Application::SetWRQHostErrorMessage(LPCTSTR lpszNewValue)
   {
      static BYTE parms[] =
      VTS_BSTR;
      InvokeHelper(0x600201f7, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   lpszNewValue);
   }

   long Application::GetWRQHostRecordSize()
   {
      long result;
      InvokeHelper(0x600201f9, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
      return(result);
   }

   void Application::SetWRQHostRecordSize(long nNewValue)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x600201f9, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   nNewValue);
   }

   long Application::GetWRQHostSystem()
   {
      long result;
      InvokeHelper(0x600201fb, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
      return(result);
   }

   void Application::SetWRQHostSystem(long nNewValue)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x600201fb, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   nNewValue);
   }

   BOOL Application::GetWRQKeepFile()
   {
      BOOL result;
      InvokeHelper(0x600201fd, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Application::SetWRQKeepFile(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x600201fd, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   long Application::GetWRQMPEFilenames()
   {
      long result;
      InvokeHelper(0x600201ff, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
      return(result);
   }

   void Application::SetWRQMPEFilenames(long nNewValue)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x600201ff, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   nNewValue);
   }

   BOOL Application::GetWRQMPEStream()
   {
      BOOL result;
      InvokeHelper(0x60020201, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Application::SetWRQMPEStream(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x60020201, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   BOOL Application::GetWRQPreserveCounts()
   {
      BOOL result;
      InvokeHelper(0x60020203, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Application::SetWRQPreserveCounts(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x60020203, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   BOOL Application::GetWRQPreserveDate()
   {
      BOOL result;
      InvokeHelper(0x60020205, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Application::SetWRQPreserveDate(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x60020205, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   BOOL Application::GetWRQQEditFormat()
   {
      BOOL result;
      InvokeHelper(0x60020207, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Application::SetWRQQEditFormat(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x60020207, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   BOOL Application::GetWRQRemoveExtension()
   {
      BOOL result;
      InvokeHelper(0x60020209, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Application::SetWRQRemoveExtension(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x60020209, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   BOOL Application::GetWRQSendSpooled()
   {
      BOOL result;
      InvokeHelper(0x6002020b, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Application::SetWRQSendSpooled(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x6002020b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   BOOL Application::GetWRQShowHidden()
   {
      BOOL result;
      InvokeHelper(0x6002020d, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Application::SetWRQShowHidden(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x6002020d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   CString Application::GetWRQStartCharacter()
   {
      CString result;
      InvokeHelper(0x6002020f, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
      return(result);
   }

   void Application::SetWRQStartCharacter(LPCTSTR lpszNewValue)
   {
      static BYTE parms[] =
      VTS_BSTR;
      InvokeHelper(0x6002020f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   lpszNewValue);
   }

   CString Application::GetWRQStartupCommand()
   {
      CString result;
      InvokeHelper(0x60020211, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
      return(result);
   }

   void Application::SetWRQStartupCommand(LPCTSTR lpszNewValue)
   {
      static BYTE parms[] =
      VTS_BSTR;
      InvokeHelper(0x60020211, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   lpszNewValue);
   }

   BOOL Application::GetWRQSubmitBatch()
   {
      BOOL result;
      InvokeHelper(0x60020213, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Application::SetWRQSubmitBatch(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x60020213, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   BOOL Application::GetWRQSubmitPrint()
   {
      BOOL result;
      InvokeHelper(0x60020215, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Application::SetWRQSubmitPrint(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x60020215, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   long Application::GetWRQTransferLink()
   {
      long result;
      InvokeHelper(0x60020217, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
      return(result);
   }

   void Application::SetWRQTransferLink(long nNewValue)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x60020217, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   nNewValue);
   }

   long Application::GetWRQTransferType()
   {
      long result;
      InvokeHelper(0x60020219, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
      return(result);
   }

   void Application::SetWRQTransferType(long nNewValue)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x60020219, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   nNewValue);
   }

   BOOL Application::GetWRQTransferWithAttributes()
   {
      BOOL result;
      InvokeHelper(0x6002021b, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Application::SetWRQTransferWithAttributes(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x6002021b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   BOOL Application::GetWRQTranslateCCtl()
   {
      BOOL result;
      InvokeHelper(0x6002021d, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Application::SetWRQTranslateCCtl(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x6002021d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   BOOL Application::GetWRQUseBlockReads()
   {
      BOOL result;
      InvokeHelper(0x6002021f, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Application::SetWRQUseBlockReads(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x6002021f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   BOOL Application::GetWRQUseCTermFrameSize()
   {
      BOOL result;
      InvokeHelper(0x60020221, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Application::SetWRQUseCTermFrameSize(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x60020221, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   long Application::GetWRQWindowSize()
   {
      long result;
      InvokeHelper(0x60020223, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
      return(result);
   }

   void Application::SetWRQWindowSize(long nNewValue)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x60020223, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   nNewValue);
   }

   long Application::GetXmodemExtension()
   {
      long result;
      InvokeHelper(0x60020225, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
      return(result);
   }

   void Application::SetXmodemExtension(long nNewValue)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x60020225, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   nNewValue);
   }

   long Application::GetXmodemTransferType()
   {
      long result;
      InvokeHelper(0x60020227, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
      return(result);
   }

   void Application::SetXmodemTransferType(long nNewValue)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x60020227, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   nNewValue);
   }

   BOOL Application::GetXmodemTranslateCharacters()
   {
      BOOL result;
      InvokeHelper(0x60020229, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Application::SetXmodemTranslateCharacters(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x60020229, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   BOOL Application::GetZmodemAutoDownload()
   {
      BOOL result;
      InvokeHelper(0x6002022b, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Application::SetZmodemAutoDownload(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x6002022b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   BOOL Application::GetZmodemDeleteCancelledReceives()
   {
      BOOL result;
      InvokeHelper(0x6002022d, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Application::SetZmodemDeleteCancelledReceives(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x6002022d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   long Application::GetZmodemPacketSize()
   {
      long result;
      InvokeHelper(0x6002022f, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
      return(result);
   }

   void Application::SetZmodemPacketSize(long nNewValue)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x6002022f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   nNewValue);
   }

   CString Application::GetZmodemReceiveStartupCommand()
   {
      CString result;
      InvokeHelper(0x60020231, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
      return(result);
   }

   void Application::SetZmodemReceiveStartupCommand(LPCTSTR lpszNewValue)
   {
      static BYTE parms[] =
      VTS_BSTR;
      InvokeHelper(0x60020231, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   lpszNewValue);
   }

   CString Application::GetZmodemSendStartupCommand()
   {
      CString result;
      InvokeHelper(0x60020233, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
      return(result);
   }

   void Application::SetZmodemSendStartupCommand(LPCTSTR lpszNewValue)
   {
      static BYTE parms[] =
      VTS_BSTR;
      InvokeHelper(0x60020233, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   lpszNewValue);
   }

   long Application::GetZmodemTransferType()
   {
      long result;
      InvokeHelper(0x60020235, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
      return(result);
   }

   void Application::SetZmodemTransferType(long nNewValue)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x60020235, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   nNewValue);
   }

   BOOL Application::GetZmodemTranslateCharacters()
   {
      BOOL result;
      InvokeHelper(0x60020237, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Application::SetZmodemTranslateCharacters(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x60020237, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   BOOL Application::GetZmodemTranslateFilenames()
   {
      BOOL result;
      InvokeHelper(0x60020239, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Application::SetZmodemTranslateFilenames(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x60020239, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   long Application::GetCompensateFrameSpaces()
   {
      long result;
      InvokeHelper(0x6002023b, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
      return(result);
   }

   void Application::SetCompensateFrameSpaces(long nNewValue)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x6002023b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   nNewValue);
   }

   BOOL Application::GetGlobalCapsLock()
   {
      BOOL result;
      InvokeHelper(0x6002023d, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Application::SetGlobalCapsLock(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x6002023d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   BOOL Application::GetGlobalNumLock()
   {
      BOOL result;
      InvokeHelper(0x6002023f, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Application::SetGlobalNumLock(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x6002023f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   BOOL Application::GetGlobalScrollLock()
   {
      BOOL result;
      InvokeHelper(0x60020241, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Application::SetGlobalScrollLock(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x60020241, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   BOOL Application::GetJISRomanG0()
   {
      BOOL result;
      InvokeHelper(0x60020243, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Application::SetJISRomanG0(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x60020243, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   BOOL Application::GetOnDemandFonts()
   {
      BOOL result;
      InvokeHelper(0x60020245, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Application::SetOnDemandFonts(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x60020245, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   BOOL Application::GetProportionalFonts()
   {
      BOOL result;
      InvokeHelper(0x60020247, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Application::SetProportionalFonts(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x60020247, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   void Application::Activate()
   {
      InvokeHelper(0x60020249, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
   }

   CString Application::GetKeyMapCommandArgs(long Modifiers, LPCTSTR Key)
   {
      CString result;
      static BYTE parms[] =
      VTS_I4 VTS_BSTR;
      InvokeHelper(0x6002024a, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms,
                   Modifiers, Key);
      return(result);
   }

   void Application::SetPropertyProfile(LPCTSTR PropertyName, long IsEnabled)
   {
      static BYTE parms[] =
      VTS_BSTR VTS_I4;
      InvokeHelper(0x6002024b, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
                   PropertyName, IsEnabled);
   }

   void Application::PlaySound(LPCTSTR SoundFile, const VARIANT& Asynchronous)
   {
      static BYTE parms[] =
      VTS_BSTR VTS_VARIANT;
      InvokeHelper(0x6002024c, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
                   SoundFile, &Asynchronous);
   }

   BOOL Application::PropertyIsModifiable(LPCTSTR PropertyName)
   {
      BOOL result;
      static BYTE parms[] =
      VTS_BSTR;
      InvokeHelper(0x6002024d, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
                   PropertyName);
      return(result);
   }

   long Application::GetFileType(LPCTSTR Filename)
   {
      long result;
      static BYTE parms[] =
      VTS_BSTR;
      InvokeHelper(0x6002024e, DISPATCH_METHOD, VT_I4, (void*)&result, parms,
                   Filename);
      return(result);
   }

   void Application::Shell(LPCTSTR Application, const VARIANT& CommandLine, const VARIANT& WindowState, const VARIANT& Wait)
   {
      static BYTE parms[] =
      VTS_BSTR VTS_VARIANT VTS_VARIANT VTS_VARIANT;
      InvokeHelper(0x6002024f, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
                   Application, &CommandLine, &WindowState, &Wait);
   }

   void Application::CopyAboutBoxInfo()
   {
      InvokeHelper(0x60020250, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
   }

   void Application::ConnectTemplate(const VARIANT& ConnectionName, const VARIANT& Options)
   {
      static BYTE parms[] =
      VTS_VARIANT VTS_VARIANT;
      InvokeHelper(0x60020251, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
                   &ConnectionName, &Options);
   }

   void Application::OpenSettingsExtended(LPCTSTR Filename, const VARIANT& Type, const VARIANT& Options)
   {
      static BYTE parms[] =
      VTS_BSTR VTS_VARIANT VTS_VARIANT;
      InvokeHelper(0x60020252, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
                   Filename, &Type, &Options);
   }

   BOOL Application::WaitForIncomingData(const VARIANT& Timeout, const VARIANT& Options)
   {
      BOOL result;
      static BYTE parms[] =
      VTS_VARIANT VTS_VARIANT;
      InvokeHelper(0x60020253, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
                   &Timeout, &Options);
      return(result);
   }

   void Application::FlashWindow(const VARIANT& Rate)
   {
      static BYTE parms[] =
      VTS_VARIANT;
      InvokeHelper(0x60020254, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
                   &Rate);
   }

   void Application::SetColorMap(long Attribute, long Foreground, long Background)
   {
      static BYTE parms[] =
      VTS_I4 VTS_I4 VTS_I4;
      InvokeHelper(0x60020255, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
                   Attribute, Foreground, Background);
   }

   long Application::ForegroundColor(long Attribute)
   {
      long result;
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x60020256, DISPATCH_METHOD, VT_I4, (void*)&result, parms,
                   Attribute);
      return(result);
   }

   long Application::BackgroundColor(long Attribute)
   {
      long result;
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x60020257, DISPATCH_METHOD, VT_I4, (void*)&result, parms,
                   Attribute);
      return(result);
   }

   void Application::SetColorRGB(long Color, long Red, long Green, long Blue)
   {
      static BYTE parms[] =
      VTS_I4 VTS_I4 VTS_I4 VTS_I4;
      InvokeHelper(0x60020258, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
                   Color, Red, Green, Blue);
   }

   long Application::GetColorRGB(long Color, long WhichValue)
   {
      long result;
      static BYTE parms[] =
      VTS_I4 VTS_I4;
      InvokeHelper(0x60020259, DISPATCH_METHOD, VT_I4, (void*)&result, parms,
                   Color, WhichValue);
      return(result);
   }

   long Application::CharacterAttributes(long Row, long Column)
   {
      long result;
      static BYTE parms[] =
      VTS_I4 VTS_I4;
      InvokeHelper(0x6002025a, DISPATCH_METHOD, VT_I4, (void*)&result, parms,
                   Row, Column);
      return(result);
   }

   void Application::SetAnsiColorRGB(long AnsiColor, long Red, long Green, long Blue)
   {
      static BYTE parms[] =
      VTS_I4 VTS_I4 VTS_I4 VTS_I4;
      InvokeHelper(0x6002025b, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
                   AnsiColor, Red, Green, Blue);
   }

   long Application::GetAnsiColorRGB(long AnsiColor, long WhichValue)
   {
      long result;
      static BYTE parms[] =
      VTS_I4 VTS_I4;
      InvokeHelper(0x6002025c, DISPATCH_METHOD, VT_I4, (void*)&result, parms,
                   AnsiColor, WhichValue);
      return(result);
   }

   void Application::FTPStartServer(const VARIANT& UserName, const VARIANT& Password, const VARIANT& HostName, const VARIANT& Options)
   {
      static BYTE parms[] =
      VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT;
      InvokeHelper(0x6002025d, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
                   &UserName, &Password, &HostName, &Options);
   }

   void Application::FTPStopServer()
   {
      InvokeHelper(0x6002025e, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
   }

   void Application::FTPReceiveFile(LPCTSTR LocalFile, LPCTSTR RemoteFile, const VARIANT& TransferType, const VARIANT& IfFileExists, const VARIANT& Before, const VARIANT& Since, const VARIANT& Exclude)
   {
      static BYTE parms[] =
      VTS_BSTR VTS_BSTR VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT;
      InvokeHelper(0x6002025f, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
                   LocalFile, RemoteFile, &TransferType, &IfFileExists, &Before, &Since, &Exclude);
   }

   void Application::FTPSendFile(LPCTSTR LocalFile, LPCTSTR RemoteFile, const VARIANT& TransferType, const VARIANT& IfFileExists, const VARIANT& Before, const VARIANT& Since, const VARIANT& Exclude)
   {
      static BYTE parms[] =
      VTS_BSTR VTS_BSTR VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT;
      InvokeHelper(0x60020260, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
                   LocalFile, RemoteFile, &TransferType, &IfFileExists, &Before, &Since, &Exclude);
   }

   CString Application::GetPropertyInformation(const VARIANT& Name, const VARIANT& Options)
   {
      CString result;
      static BYTE parms[] =
      VTS_VARIANT VTS_VARIANT;
      InvokeHelper(0x60020261, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms,
                   &Name, &Options);
      return(result);
   }

   void Application::StartRecordingSilently(const VARIANT& Options)
   {
      static BYTE parms[] =
      VTS_VARIANT;
      InvokeHelper(0x60020262, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
                   &Options);
   }

   void Application::DestroyToolbar(LPCTSTR toolbarName)
   {
      static BYTE parms[] =
      VTS_BSTR;
      InvokeHelper(0x60020264, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
                   toolbarName);
   }

   void Application::SetMouseMap(long Modifiers, LPCTSTR Chord, long CommandType, LPCTSTR Commands, const VARIANT& CommandArguments)
   {
      static BYTE parms[] =
      VTS_I4 VTS_BSTR VTS_I4 VTS_BSTR VTS_VARIANT;
      InvokeHelper(0x60020266, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
                   Modifiers, Chord, CommandType, Commands, &CommandArguments);
   }

   void Application::StatusBox(LPCTSTR Text, const VARIANT& Options)
   {
      static BYTE parms[] =
      VTS_BSTR VTS_VARIANT;
      InvokeHelper(0x60020267, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
                   Text, &Options);
   }

   void Application::CloseStatusBox()
   {
      InvokeHelper(0x60020268, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
   }

   CString Application::GetFolderName(const VARIANT& Title, const VARIANT& Text, const VARIANT& StartInFolder)
   {
      CString result;
      static BYTE parms[] =
      VTS_VARIANT VTS_VARIANT VTS_VARIANT;
      InvokeHelper(0x60020269, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms,
                   &Title, &Text, &StartInFolder);
      return(result);
   }

   BOOL Application::GetAllowJIS()
   {
      BOOL result;
      InvokeHelper(0x6002026a, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Application::SetAllowJIS(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x6002026a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   CString Application::GetCommandLineSwitches()
   {
      CString result;
      InvokeHelper(0x6002026c, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
      return(result);
   }

   void Application::SetCommandLineSwitches(LPCTSTR lpszNewValue)
   {
      static BYTE parms[] =
      VTS_BSTR;
      InvokeHelper(0x6002026c, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   lpszNewValue);
   }

   BOOL Application::GetDisplayEnabled()
   {
      BOOL result;
      InvokeHelper(0x6002026e, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Application::SetDisplayEnabled(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x6002026e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   BOOL Application::GetFlashWindowOnDisconnect()
   {
      BOOL result;
      InvokeHelper(0x60020270, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Application::SetFlashWindowOnDisconnect(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x60020270, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   BOOL Application::GetForceC1Controls()
   {
      BOOL result;
      InvokeHelper(0x60020272, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Application::SetForceC1Controls(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x60020272, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   BOOL Application::GetMinimizeCPUUsage()
   {
      BOOL result;
      InvokeHelper(0x60020274, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Application::SetMinimizeCPUUsage(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x60020274, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   long Application::GetFoundTextRow()
   {
      long result;
      InvokeHelper(0x60020276, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
      return(result);
   }

   void Application::SetFoundTextRow(long nNewValue)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x60020276, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   nNewValue);
   }

   long Application::GetFoundTextColumn()
   {
      long result;
      InvokeHelper(0x60020278, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
      return(result);
   }

   void Application::SetFoundTextColumn(long nNewValue)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x60020278, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   nNewValue);
   }

   BOOL Application::GetPrinterPassEscape()
   {
      BOOL result;
      InvokeHelper(0x6002027a, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Application::SetPrinterPassEscape(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x6002027a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   BOOL Application::GetRecording()
   {
      BOOL result;
      InvokeHelper(0x6002027c, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Application::SetRecording(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x6002027c, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   CString Application::GetRBVersionString()
   {
      CString result;
      InvokeHelper(0x6002027e, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
      return(result);
   }

   void Application::SetRBVersionString(LPCTSTR lpszNewValue)
   {
      static BYTE parms[] =
      VTS_BSTR;
      InvokeHelper(0x6002027e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   lpszNewValue);
   }

   CString Application::GetScriptFolder()
   {
      CString result;
      InvokeHelper(0x60020280, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
      return(result);
   }

   void Application::SetScriptFolder(LPCTSTR lpszNewValue)
   {
      static BYTE parms[] =
      VTS_BSTR;
      InvokeHelper(0x60020280, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   lpszNewValue);
   }

   CString Application::GetSettingsExtension()
   {
      CString result;
      InvokeHelper(0x60020282, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
      return(result);
   }

   void Application::SetSettingsExtension(LPCTSTR lpszNewValue)
   {
      static BYTE parms[] =
      VTS_BSTR;
      InvokeHelper(0x60020282, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   lpszNewValue);
   }

   BOOL Application::GetShowMenuBar()
   {
      BOOL result;
      InvokeHelper(0x60020284, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Application::SetShowMenuBar(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x60020284, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   BOOL Application::GetShowStatusBar()
   {
      BOOL result;
      InvokeHelper(0x60020286, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Application::SetShowStatusBar(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x60020286, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   BOOL Application::GetShowVerticalScrollBar()
   {
      BOOL result;
      InvokeHelper(0x60020288, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Application::SetShowVerticalScrollBar(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x60020288, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   BOOL Application::GetTransferDisconnectWhenDone()
   {
      BOOL result;
      InvokeHelper(0x6002028a, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Application::SetTransferDisconnectWhenDone(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x6002028a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   long Application::GetWindowHandle()
   {
      long result;
      InvokeHelper(0x6002028c, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
      return(result);
   }

   void Application::SetWindowHandle(long nNewValue)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x6002028c, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   nNewValue);
   }

   CString Application::GetWordBoundaryInclusive()
   {
      CString result;
      InvokeHelper(0x6002028e, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
      return(result);
   }

   void Application::SetWordBoundaryInclusive(LPCTSTR lpszNewValue)
   {
      static BYTE parms[] =
      VTS_BSTR;
      InvokeHelper(0x6002028e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   lpszNewValue);
   }

   CString Application::GetWordBoundaryExclusive()
   {
      CString result;
      InvokeHelper(0x60020290, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
      return(result);
   }

   void Application::SetWordBoundaryExclusive(LPCTSTR lpszNewValue)
   {
      static BYTE parms[] =
      VTS_BSTR;
      InvokeHelper(0x60020290, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   lpszNewValue);
   }

   BOOL Application::GetWRQShowRecordSize()
   {
      BOOL result;
      InvokeHelper(0x60020292, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Application::SetWRQShowRecordSize(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x60020292, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   BOOL Application::GetAutoScroll()
   {
      BOOL result;
      InvokeHelper(0x60020294, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Application::SetAutoScroll(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x60020294, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   BOOL Application::GetPrintANSIColorBackground()
   {
      BOOL result;
      InvokeHelper(0x60020296, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Application::SetPrintANSIColorBackground(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x60020296, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   BOOL Application::GetRecognizeDEL()
   {
      BOOL result;
      InvokeHelper(0x60020298, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Application::SetRecognizeDEL(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x60020298, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   long Application::GetReceivedCR()
   {
      long result;
      InvokeHelper(0x6002029a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
      return(result);
   }

   void Application::SetReceivedCR(long nNewValue)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x6002029a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   nNewValue);
   }

   BOOL Application::GetWyseProtectMode()
   {
      BOOL result;
      InvokeHelper(0x6002029c, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Application::SetWyseProtectMode(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x6002029c, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   BOOL Application::GetWyseBlockMode()
   {
      BOOL result;
      InvokeHelper(0x6002029e, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Application::SetWyseBlockMode(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x6002029e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   long Application::GetWyseAttributeMode()
   {
      long result;
      InvokeHelper(0x600202a0, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
      return(result);
   }

   void Application::SetWyseAttributeMode(long nNewValue)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x600202a0, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   nNewValue);
   }

   long Application::GetWyseBlockTerminator()
   {
      long result;
      InvokeHelper(0x600202a2, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
      return(result);
   }

   void Application::SetWyseBlockTerminator(long nNewValue)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x600202a2, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   nNewValue);
   }

   BOOL Application::GetWyseAcceptNulls()
   {
      BOOL result;
      InvokeHelper(0x600202a4, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Application::SetWyseAcceptNulls(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x600202a4, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   long Application::GetWyseReturnKey()
   {
      long result;
      InvokeHelper(0x600202a6, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
      return(result);
   }

   void Application::SetWyseReturnKey(long nNewValue)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x600202a6, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   nNewValue);
   }

   long Application::GetWyseEnterKey()
   {
      long result;
      InvokeHelper(0x600202a8, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
      return(result);
   }

   void Application::SetWyseEnterKey(long nNewValue)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x600202a8, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   nNewValue);
   }

   long Application::GetWyseLabelLines()
   {
      long result;
      InvokeHelper(0x600202aa, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
      return(result);
   }

   void Application::SetWyseLabelLines(long nNewValue)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x600202aa, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   nNewValue);
   }

   long Application::GetWyseStatusLineDisplay()
   {
      long result;
      InvokeHelper(0x600202ac, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
      return(result);
   }

   void Application::SetWyseStatusLineDisplay(long nNewValue)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x600202ac, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   nNewValue);
   }

   BOOL Application::GetReGISMoveMouse()
   {
      BOOL result;
      InvokeHelper(0x600202ae, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Application::SetReGISMoveMouse(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x600202ae, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   BOOL Application::GetShowTitleBar()
   {
      BOOL result;
      InvokeHelper(0x600202b0, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Application::SetShowTitleBar(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x600202b0, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   long Application::GetPrinterOrientation()
   {
      long result;
      InvokeHelper(0x600202b2, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
      return(result);
   }

   void Application::SetPrinterOrientation(long nNewValue)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x600202b2, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   nNewValue);
   }

   BOOL Application::GetDigitalLA210PrinterEmulation()
   {
      BOOL result;
      InvokeHelper(0x600202b4, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Application::SetDigitalLA210PrinterEmulation(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x600202b4, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   BOOL Application::GetConfirmExit()
   {
      BOOL result;
      InvokeHelper(0x600202b6, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Application::SetConfirmExit(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x600202b6, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   long Application::GetSaveChanges()
   {
      long result;
      InvokeHelper(0x600202b8, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
      return(result);
   }

   void Application::SetSaveChanges(long nNewValue)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x600202b8, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   nNewValue);
   }

   BOOL Application::GetToolbarIncludeLabels()
   {
      BOOL result;
      InvokeHelper(0x600202ba, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Application::SetToolbarIncludeLabels(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x600202ba, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   BOOL Application::GetToolbarFlatLook()
   {
      BOOL result;
      InvokeHelper(0x600202bc, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Application::SetToolbarFlatLook(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x600202bc, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   long Application::GetFTPTransferType()
   {
      long result;
      InvokeHelper(0x600202be, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
      return(result);
   }

   void Application::SetFTPTransferType(long nNewValue)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x600202be, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   nNewValue);
   }

   CString Application::GetFTPUserName()
   {
      CString result;
      InvokeHelper(0x600202c0, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
      return(result);
   }

   void Application::SetFTPUserName(LPCTSTR lpszNewValue)
   {
      static BYTE parms[] =
      VTS_BSTR;
      InvokeHelper(0x600202c0, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   lpszNewValue);
   }

   CString Application::GetFTPPassword()
   {
      CString result;
      InvokeHelper(0x600202c2, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
      return(result);
   }

   void Application::SetFTPPassword(LPCTSTR lpszNewValue)
   {
      static BYTE parms[] =
      VTS_BSTR;
      InvokeHelper(0x600202c2, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   lpszNewValue);
   }

   CString Application::GetFTPHostName()
   {
      CString result;
      InvokeHelper(0x600202c4, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
      return(result);
   }

   void Application::SetFTPHostName(LPCTSTR lpszNewValue)
   {
      static BYTE parms[] =
      VTS_BSTR;
      InvokeHelper(0x600202c4, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   lpszNewValue);
   }

   BOOL Application::GetFTPTranslateCharacters()
   {
      BOOL result;
      InvokeHelper(0x600202c6, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Application::SetFTPTranslateCharacters(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x600202c6, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   long Application::GetPrinterMarginBottom()
   {
      long result;
      InvokeHelper(0x600202c8, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
      return(result);
   }

   void Application::SetPrinterMarginBottom(long nNewValue)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x600202c8, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   nNewValue);
   }

   long Application::GetPrinterMarginLeft()
   {
      long result;
      InvokeHelper(0x600202ca, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
      return(result);
   }

   void Application::SetPrinterMarginLeft(long nNewValue)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x600202ca, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   nNewValue);
   }

   long Application::GetPrinterMarginRight()
   {
      long result;
      InvokeHelper(0x600202cc, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
      return(result);
   }

   void Application::SetPrinterMarginRight(long nNewValue)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x600202cc, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   nNewValue);
   }

   long Application::GetPrinterMarginTop()
   {
      long result;
      InvokeHelper(0x600202ce, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
      return(result);
   }

   void Application::SetPrinterMarginTop(long nNewValue)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x600202ce, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   nNewValue);
   }

   long Application::GetHotspotRow()
   {
      long result;
      InvokeHelper(0x600202d0, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
      return(result);
   }

   void Application::SetHotspotRow(long nNewValue)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x600202d0, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   nNewValue);
   }

   long Application::GetHotspotColumn()
   {
      long result;
      InvokeHelper(0x600202d2, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
      return(result);
   }

   void Application::SetHotspotColumn(long nNewValue)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x600202d2, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   nNewValue);
   }

   long Application::GetHotspotLength()
   {
      long result;
      InvokeHelper(0x600202d4, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
      return(result);
   }

   void Application::SetHotspotLength(long nNewValue)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x600202d4, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   nNewValue);
   }

   long Application::GetHotspotsModifiers()
   {
      long result;
      InvokeHelper(0x600202d6, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
      return(result);
   }

   void Application::SetHotspotsModifiers(long nNewValue)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x600202d6, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   nNewValue);
   }

   long Application::GetHotspotsChord()
   {
      long result;
      InvokeHelper(0x600202d8, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
      return(result);
   }

   void Application::SetHotspotsChord(long nNewValue)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x600202d8, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   nNewValue);
   }

   BOOL Application::GetHotspotsEnabled()
   {
      BOOL result;
      InvokeHelper(0x600202da, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Application::SetHotspotsEnabled(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x600202da, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   BOOL Application::GetHotspotsVisible()
   {
      BOOL result;
      InvokeHelper(0x600202dc, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Application::SetHotspotsVisible(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x600202dc, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   CString Application::GetHotspotText()
   {
      CString result;
      InvokeHelper(0x600202de, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
      return(result);
   }

   void Application::SetHotspotText(LPCTSTR lpszNewValue)
   {
      static BYTE parms[] =
      VTS_BSTR;
      InvokeHelper(0x600202de, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   lpszNewValue);
   }

   BOOL Application::GetWRQFastCompression()
   {
      BOOL result;
      InvokeHelper(0x600202e0, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Application::SetWRQFastCompression(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x600202e0, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   BOOL Application::GetWidthChangeClear()
   {
      BOOL result;
      InvokeHelper(0x600202e2, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Application::SetWidthChangeClear(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x600202e2, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   long Application::GetMouseRow()
   {
      long result;
      InvokeHelper(0x600202e4, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
      return(result);
   }

   void Application::SetMouseRow(long nNewValue)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x600202e4, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   nNewValue);
   }

   long Application::GetMouseColumn()
   {
      long result;
      InvokeHelper(0x600202e6, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
      return(result);
   }

   void Application::SetMouseColumn(long nNewValue)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x600202e6, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   nNewValue);
   }

   BOOL Application::GetUseModemDialerV5()
   {
      BOOL result;
      InvokeHelper(0x600202e8, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Application::SetUseModemDialerV5(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x600202e8, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   CString Application::GetShortcutFolder()
   {
      CString result;
      InvokeHelper(0x600202ea, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
      return(result);
   }

   void Application::SetShortcutFolder(LPCTSTR lpszNewValue)
   {
      static BYTE parms[] =
      VTS_BSTR;
      InvokeHelper(0x600202ea, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   lpszNewValue);
   }

   BOOL Application::GetCreateShortcut()
   {
      BOOL result;
      InvokeHelper(0x600202ec, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Application::SetCreateShortcut(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x600202ec, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   BOOL Application::GetVT640Compatible()
   {
      BOOL result;
      InvokeHelper(0x600202ee, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Application::SetVT640Compatible(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x600202ee, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   CString Application::GetTransferAutoDetectASCIIExtensionList()
   {
      CString result;
      InvokeHelper(0x600202f0, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
      return(result);
   }

   void Application::SetTransferAutoDetectASCIIExtensionList(LPCTSTR lpszNewValue)
   {
      static BYTE parms[] =
      VTS_BSTR;
      InvokeHelper(0x600202f0, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   lpszNewValue);
   }

   CString Application::GetTransferAutoDetectBinaryExtensionList()
   {
      CString result;
      InvokeHelper(0x600202f2, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
      return(result);
   }

   void Application::SetTransferAutoDetectBinaryExtensionList(LPCTSTR lpszNewValue)
   {
      static BYTE parms[] =
      VTS_BSTR;
      InvokeHelper(0x600202f2, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   lpszNewValue);
   }

   CString Application::GetTransferAutoDetectImageLabelsExtensionList()
   {
      CString result;
      InvokeHelper(0x600202f4, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
      return(result);
   }

   void Application::SetTransferAutoDetectImageLabelsExtensionList(LPCTSTR lpszNewValue)
   {
      static BYTE parms[] =
      VTS_BSTR;
      InvokeHelper(0x600202f4, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   lpszNewValue);
   }

   CString Application::GetTransferAutoDetectScanExtensionList()
   {
      CString result;
      InvokeHelper(0x600202f6, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
      return(result);
   }

   void Application::SetTransferAutoDetectScanExtensionList(LPCTSTR lpszNewValue)
   {
      static BYTE parms[] =
      VTS_BSTR;
      InvokeHelper(0x600202f6, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   lpszNewValue);
   }

   long Application::GetTransferAutoDetectDefaultType()
   {
      long result;
      InvokeHelper(0x600202f8, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
      return(result);
   }

   void Application::SetTransferAutoDetectDefaultType(long nNewValue)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x600202f8, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   nNewValue);
   }

   long Application::GetHostForDefaultSettings()
   {
      long result;
      InvokeHelper(0x600202fa, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
      return(result);
   }

   void Application::SetHostForDefaultSettings(long nNewValue)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x600202fa, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   nNewValue);
   }

   CString Application::GetSiteDefaults()
   {
      CString result;
      InvokeHelper(0x600202fc, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
      return(result);
   }

   void Application::SetSiteDefaults(LPCTSTR lpszNewValue)
   {
      static BYTE parms[] =
      VTS_BSTR;
      InvokeHelper(0x600202fc, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   lpszNewValue);
   }

   BOOL Application::GetPrinterFitFontToPage()
   {
      BOOL result;
      InvokeHelper(0x600202fe, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
      return(result);
   }

   void Application::SetPrinterFitFontToPage(BOOL bNewValue)
   {
      static BYTE parms[] =
      VTS_BOOL;
      InvokeHelper(0x600202fe, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   bNewValue);
   }

   long Application::GetWebSecurity()
   {
      long result;
      InvokeHelper(0x60020300, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
      return(result);
   }

   void Application::SetWebSecurity(long nNewValue)
   {
      static BYTE parms[] =
      VTS_I4;
      InvokeHelper(0x60020300, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
                   nNewValue);
   }

} // namespace ReflectionDispatch