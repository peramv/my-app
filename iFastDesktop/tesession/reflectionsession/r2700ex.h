// Machine generated IDispatch wrapper class(es) created with ClassWizard
/////////////////////////////////////////////////////////////////////////////
// Reflection2 wrapper class
namespace ReflectionDispatch
{

   class Reflection2 : public COleDispatchDriver
   {
   public:
      Reflection2() {}      // Calls COleDispatchDriver default constructor
      Reflection2(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
      Reflection2(const Reflection2& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
   public:

// Operations
      public:
      void AbortTransfer();
      void Break();
      void CancelTransfer();
      void Clear(long ClearWhat);
      void CloseAllConnections();
      long CompileScript(LPCTSTR ScriptName);
      void Connect(const VARIANT& ConnectionName);
      CString ConnectionSetting(LPCTSTR Setting);
      void Copy(long CopyWhat, const VARIANT& Format);
      void DDEExecute(long ConversationID, LPCTSTR Command);
      long DDEInitiate(LPCTSTR AppName, LPCTSTR TopicName);
      void DDEPoke(long ConversationID, LPCTSTR ItemName, LPCTSTR Value);
      CString DDEQueryServerTopics(LPCTSTR AppName, LPCTSTR TopicName);
      CString DDERequest(long ConversationID, LPCTSTR ItemName);
      void DDETerminate(long ConversationID);
      void DDETerminateAll();
      void Dial(LPCTSTR PhoneNumber, const VARIANT& Description, const VARIANT& InitString, const VARIANT& AnswerTimeout, const VARIANT& RetryTimes, const VARIANT& RetryInterval, const VARIANT& SpeakerMode, const VARIANT& SpeakerVolume, 
                const VARIANT& SpeakerOffAfterRedial, const VARIANT& IgnoreModemErrors);
      void Disconnect();
      void Display(LPCTSTR String, const VARIANT& Options);
      void DisplayFile(LPCTSTR Filename, const VARIANT& Options);
      void DropDTR();
      void EditScript(LPCTSTR ScriptName);
      CString EvaluateRCLExpression(LPCTSTR Expression, const VARIANT& Options);
      void ExecuteBuiltInFunction(LPCTSTR FunctionName);
      void ExecuteRCLCommand(LPCTSTR Command, const VARIANT& Options);
      BOOL FindText(LPCTSTR SearchFor, long StartRow, long StartColumn, const VARIANT& Options);
      void FlushPrinter();
      CString GetClipboardText();
      BOOL GetCommandGroupProfile(long CmdGroup);
      BOOL GetCommandProfile(LPCTSTR CmdName);
      CString GetText(long StartRow, long StartColumn, long EndRow, long EndColumn, const VARIANT& Options);
      long GetKeyMapCommandType(long Modifiers, LPCTSTR Key);
      CString GetKeyMapCommands(long Modifiers, LPCTSTR Key);
      CString GetOpenFilename(const VARIANT& FileFilter, const VARIANT& FilterIndex, const VARIANT& Title, const VARIANT& ButtonText);
      CString GetSaveAsFilename(const VARIANT& InitialFilename, const VARIANT& FileFilter, const VARIANT& FilterIndex, const VARIANT& Title, const VARIANT& ButtonText);
      long GetSerialStatistics(long WhichStatistic);
      void Hangup();
      void Help(const VARIANT& HelpTopic, const VARIANT& HelpFile);
      CString InputBox(LPCTSTR Prompt, const VARIANT& Title, const VARIANT& Default);
      void KermitReceiveFile(LPCTSTR LocalFile, LPCTSTR RemoteFile, const VARIANT& TransferType, const VARIANT& IfFileExists);
      void KermitSendFile(LPCTSTR LocalFile, LPCTSTR RemoteFile, const VARIANT& TransferType);
      void KermitStartServer();
      void KermitStopServer(const VARIANT& Logoff);
      void LockProfile(BOOL AllowUnlock, const VARIANT& Password);
      long MsgBox(LPCTSTR Message, const VARIANT& Type, const VARIANT& Caption);
      void NewSession(const VARIANT& SessionType, const VARIANT& SettingsFile);
      void OpenSettings(LPCTSTR Filename, const VARIANT& Type);
      CString PasswordBox(LPCTSTR Prompt, const VARIANT& Title, const VARIANT& Default);
      void Paste();
      void Print(long Range, const VARIANT& Copies);
      void PrintFile(LPCTSTR Filename);
      void PrintString(LPCTSTR String);
      void Quit();
      CString ReadChars(long Count, const VARIANT& Timeout, const VARIANT& Options);
      CString ReadLine(const VARIANT& Timeout, const VARIANT& Options, VARIANT* SawEndOfLine);
      CString ReadUntil(LPCTSTR UntilChars, const VARIANT& Timeout, const VARIANT& Options, VARIANT* WhichTerminator);
      void ResetTerminal(long ResetMode);
      void RestoreDefaults(long SettingType);
      void ResumeConnection(long ConnectionID);
      void RunScript(LPCTSTR ScriptName, const VARIANT& ScriptArguments);
      void SaveDisplayMemory(LPCTSTR Filename, const VARIANT& IfFileExists, const VARIANT& Options);
      void SaveSettings(LPCTSTR Filename, const VARIANT& Type, const VARIANT& IfFileExists);
      void SetClipboardText(LPCTSTR ClipboardText);
      void SetCommandGroupProfile(long CmdGroup, BOOL IsEnabled);
      void SetCommandProfile(LPCTSTR CmdName, BOOL IsEnabled);
      void SetKeyMap(long Modifiers, LPCTSTR Key, long CommandType, LPCTSTR Commands, const VARIANT& CommandArguments);
      void SetScanCodeName(long ScanType, long ScanCode, LPCTSTR ScanName);
      void SelectText(long StartRow, long StartColumn, long EndRow, long EndColumn, const VARIANT& SelectionType);
      void StartRecording();
      void StartTrace(LPCTSTR Filename, const VARIANT& IfFileExists, const VARIANT& TraceFormat);
      void StopRecording(LPCTSTR Filename, long Target, const VARIANT& IfFileExists);
      void StopScript();
      void StopTrace();
      long SuspendConnection();
      void Transmit(LPCTSTR String, const VARIANT& Options);
      void TransmitFile(LPCTSTR Filename, const VARIANT& PauseTime, const VARIANT& PromptChar, const VARIANT& Options);
      void TransmitTerminalKey(long KeyID);
      BOOL UnlockProfile(LPCTSTR Password);
      void Wait(const VARIANT& HowLong, const VARIANT& Options);
      void WaitForCall(const VARIANT& Description, const VARIANT& InitString);
      BOOL WaitForHostTrigger(const VARIANT& Timeout, const VARIANT& Options);
      BOOL WaitForSilence(const VARIANT& SilenceTime, const VARIANT& Timeout, const VARIANT& Options);
      BOOL WaitForString(LPCTSTR String, const VARIANT& Timeout, const VARIANT& Options);
      // method 'WaitForStrings' not emitted because of invalid return type or parameter type
      void WaitUntil(DATE DateTime, const VARIANT& Options);
      void WRQReceiveFile(LPCTSTR LocalFile, LPCTSTR RemoteFile, const VARIANT& TransferType, const VARIANT& IfFileExists, const VARIANT& Before, const VARIANT& Since, const VARIANT& Exclude);
      void WRQSendFile(LPCTSTR LocalFile, LPCTSTR RemoteFile, const VARIANT& TransferType, const VARIANT& IfFileExists, const VARIANT& Before, const VARIANT& Since, const VARIANT& Exclude, const VARIANT& Attributes);
      void WRQStartServer();
      void WRQStopServer();
      void XmodemReceiveFile(LPCTSTR LocalFile, const VARIANT& TransferType, const VARIANT& IfFileExists);
      void XmodemSendFile(LPCTSTR LocalFile, const VARIANT& TransferType);
      void ZmodemReceiveFile(LPCTSTR LocalFile, const VARIANT& RemoteFile, const VARIANT& TransferType, const VARIANT& IfFileExists);
      void ZmodemSendFile(LPCTSTR LocalFile, LPCTSTR RemoteFile, const VARIANT& TransferType);
      BOOL GetAllowScriptInterrupt();
      void SetAllowScriptInterrupt(BOOL bNewValue);
      long GetAnsiScreenColor();
      void SetAnsiScreenColor(long nNewValue);
      CString GetAnswerback();
      void SetAnswerback(LPCTSTR lpszNewValue);
      VARIANT GetApplication();
      void SetApplication(const VARIANT& newValue);
      BOOL GetAutoAnswerback();
      void SetAutoAnswerback(BOOL bNewValue);
      BOOL GetAutoFontSize();
      void SetAutoFontSize(BOOL bNewValue);
      BOOL GetAutoFormFeed();
      void SetAutoFormFeed(BOOL bNewValue);
      BOOL GetAutoLineFeed();
      void SetAutoLineFeed(BOOL bNewValue);
      BOOL GetAutoRepeat();
      void SetAutoRepeat(BOOL bNewValue);
      BOOL GetBell();
      void SetBell(BOOL bNewValue);
      BOOL GetBlinkCharacters();
      void SetBlinkCharacters(BOOL bNewValue);
      CString GetBlockTerminator();
      void SetBlockTerminator(LPCTSTR lpszNewValue);
      BOOL GetBoldCharacters();
      void SetBoldCharacters(BOOL bNewValue);
      BOOL GetBreakEnabled();
      void SetBreakEnabled(BOOL bNewValue);
      long GetBreakLength();
      void SetBreakLength(long nNewValue);
      BOOL GetBypassPrinterDriver();
      void SetBypassPrinterDriver(BOOL bNewValue);
      BOOL GetCapsLock();
      void SetCapsLock(BOOL bNewValue);
      CString GetCaption();
      void SetCaption(LPCTSTR lpszNewValue);
      BOOL GetClosePrinterManually();
      void SetClosePrinterManually(BOOL bNewValue);
      long GetCodePage();
      void SetCodePage(long nNewValue);
      long GetColumnsPerScroll();
      void SetColumnsPerScroll(long nNewValue);
      BOOL GetCompressBlankLines();
      void SetCompressBlankLines(BOOL bNewValue);
      BOOL GetConnected();
      void SetConnected(BOOL bNewValue);
      long GetConnectionID();
      void SetConnectionID(long nNewValue);
      long GetConnectionIndicator();
      void SetConnectionIndicator(long nNewValue);
      long GetConnectionError();
      void SetConnectionError(long nNewValue);
      CString GetConnectionErrorMessage();
      void SetConnectionErrorMessage(LPCTSTR lpszNewValue);
      CString GetConnectionSettings();
      void SetConnectionSettings(LPCTSTR lpszNewValue);
      CString GetConnectionType();
      void SetConnectionType(LPCTSTR lpszNewValue);
      BOOL GetConvertEOLToSeparator();
      void SetConvertEOLToSeparator(BOOL bNewValue);
      BOOL GetConvertMCSToNRC();
      void SetConvertMCSToNRC(BOOL bNewValue);
      BOOL GetConvertNRCToMCS();
      void SetConvertNRCToMCS(BOOL bNewValue);
      BOOL GetConvertSeparatorToEOL();
      void SetConvertSeparatorToEOL(BOOL bNewValue);
      BOOL GetCursorBlink();
      void SetCursorBlink(BOOL bNewValue);
      long GetCursorColumn();
      void SetCursorColumn(long nNewValue);
      long GetCursorRow();
      void SetCursorRow(long nNewValue);
      long GetCursorShape();
      void SetCursorShape(long nNewValue);
      BOOL GetCursorVisible();
      void SetCursorVisible(BOOL bNewValue);
      long GetDAResponse();
      void SetDAResponse(long nNewValue);
      BOOL GetDcd();
      void SetDcd(BOOL bNewValue);
      BOOL GetDDEServerEnable();
      void SetDDEServerEnable(BOOL bNewValue);
      CString GetDDEServerName();
      void SetDDEServerName(LPCTSTR lpszNewValue);
      long GetDDETimeout();
      void SetDDETimeout(long nNewValue);
      CString GetDefaultPrinter();
      void SetDefaultPrinter(LPCTSTR lpszNewValue);
      long GetDefaultScriptLanguage();
      void SetDefaultScriptLanguage(long nNewValue);
      BOOL GetDeleteTrailingSpaces();
      void SetDeleteTrailingSpaces(BOOL bNewValue);
      long GetDisplayColumns();
      void SetDisplayColumns(long nNewValue);
      long GetDisplayMemoryBlocks();
      void SetDisplayMemoryBlocks(long nNewValue);
      long GetDisplayMemoryTopRow();
      void SetDisplayMemoryTopRow(long nNewValue);
      long GetDisplayRows();
      void SetDisplayRows(long nNewValue);
      BOOL GetEndOfLineWrap();
      void SetEndOfLineWrap(BOOL bNewValue);
      BOOL GetEnqAck();
      void SetEnqAck(BOOL bNewValue);
      CString GetFontName();
      void SetFontName(LPCTSTR lpszNewValue);
      long GetFontSize();
      void SetFontSize(long nNewValue);
      BOOL GetForceAutoRepeat();
      void SetForceAutoRepeat(BOOL bNewValue);
      CString GetFullName();
      void SetFullName(LPCTSTR lpszNewValue);
      long GetHeight();
      void SetHeight(long nNewValue);
      BOOL GetHorizontalCoupling();
      void SetHorizontalCoupling(BOOL bNewValue);
      long GetHostCharacterSet();
      void SetHostCharacterSet(long nNewValue);
      long GetHostStatusLine();
      void SetHostStatusLine(long nNewValue);
      CString GetHostTriggerCharacter();
      void SetHostTriggerCharacter(LPCTSTR lpszNewValue);
      CString GetHostsFile();
      void SetHostsFile(LPCTSTR lpszNewValue);
      BOOL GetInsertMode();
      void SetInsertMode(BOOL bNewValue);
      BOOL GetInverseVideo();
      void SetInverseVideo(BOOL bNewValue);
      long GetJumpScrollSpeed();
      void SetJumpScrollSpeed(long nNewValue);
      BOOL GetKatakanaDisplay();
      void SetKatakanaDisplay(BOOL bNewValue);
      BOOL GetKermitAutomaticServer();
      void SetKermitAutomaticServer(BOOL bNewValue);
      long GetKermitChecksum();
      void SetKermitChecksum(long nNewValue);
      long GetKermitPacketSize();
      void SetKermitPacketSize(long nNewValue);
      CString GetKermitReceiveEndCharacter();
      void SetKermitReceiveEndCharacter(LPCTSTR lpszNewValue);
      CString GetKermitReceiveStartCharacter();
      void SetKermitReceiveStartCharacter(LPCTSTR lpszNewValue);
      CString GetKermitReceiveStartupCommand();
      void SetKermitReceiveStartupCommand(LPCTSTR lpszNewValue);
      CString GetKermitSendEndCharacter();
      void SetKermitSendEndCharacter(LPCTSTR lpszNewValue);
      CString GetKermitSendStartCharacter();
      void SetKermitSendStartCharacter(LPCTSTR lpszNewValue);
      CString GetKermitSendStartupCommand();
      void SetKermitSendStartupCommand(LPCTSTR lpszNewValue);
      CString GetKermitServerStartupCommand();
      void SetKermitServerStartupCommand(LPCTSTR lpszNewValue);
      long GetKermitTransferType();
      void SetKermitTransferType(long nNewValue);
      BOOL GetKermitTranslateCharacters();
      void SetKermitTranslateCharacters(BOOL bNewValue);
      BOOL GetKermitTranslateFilenames();
      void SetKermitTranslateFilenames(BOOL bNewValue);
      long GetKermitWindowSize();
      void SetKermitWindowSize(long nNewValue);
      BOOL GetKeyboardLocked();
      void SetKeyboardLocked(BOOL bNewValue);
      long GetLanguage();
      void SetLanguage(long nNewValue);
      long GetLeft();
      void SetLeft(long nNewValue);
      BOOL GetLocalEcho();
      void SetLocalEcho(BOOL bNewValue);
      BOOL GetMarginBell();
      void SetMarginBell(BOOL bNewValue);
      BOOL GetMultiplePageTerminal();
      void SetMultiplePageTerminal(BOOL bNewValue);
      CString GetName();
      void SetName(LPCTSTR lpszNewValue);
      long GetNationalReplacementSet();
      void SetNationalReplacementSet(long nNewValue);
      CString GetNativeOS();
      void SetNativeOS(LPCTSTR lpszNewValue);
      BOOL GetNewPageOnClear();
      void SetNewPageOnClear(BOOL bNewValue);
      BOOL GetNumLock();
      void SetNumLock(BOOL bNewValue);
      CString GetOLEServerName();
      void SetOLEServerName(LPCTSTR lpszNewValue);
      BOOL GetOnline();
      void SetOnline(BOOL bNewValue);
      long GetPPLActivityTimeout();
      void SetPPLActivityTimeout(long nNewValue);
      CString GetPPLStartupCommand();
      void SetPPLStartupCommand(LPCTSTR lpszNewValue);
      BOOL GetPageCoupling();
      void SetPageCoupling(BOOL bNewValue);
      VARIANT GetParent();
      void SetParent(const VARIANT& newValue);
      long GetPasteBufferSize();
      void SetPasteBufferSize(long nNewValue);
      long GetPasteDelay();
      void SetPasteDelay(long nNewValue);
      CString GetPath();
      void SetPath(LPCTSTR lpszNewValue);
      BOOL GetPreserveNRC();
      void SetPreserveNRC(BOOL bNewValue);
      long GetPrinterBottomMargin();
      void SetPrinterBottomMargin(long nNewValue);
      long GetPrinterColumns();
      void SetPrinterColumns(long nNewValue);
      CString GetPrintToFile();
      void SetPrintToFile(LPCTSTR lpszNewValue);
      CString GetPrinterFontName();
      void SetPrinterFontName(LPCTSTR lpszNewValue);
      BOOL GetPrinterInverseFont();
      void SetPrinterInverseFont(BOOL bNewValue);
      BOOL GetPrinterLogging();
      void SetPrinterLogging(BOOL bNewValue);
      BOOL GetPrinterPassThroughConversion();
      void SetPrinterPassThroughConversion(BOOL bNewValue);
      long GetPrinterRows();
      void SetPrinterRows(long nNewValue);
      long GetPrinterTimeout();
      void SetPrinterTimeout(long nNewValue);
      BOOL GetProcessDataComm();
      void SetProcessDataComm(BOOL bNewValue);
      BOOL GetReadCtrlZAsEOF();
      void SetReadCtrlZAsEOF(BOOL bNewValue);
      BOOL GetReadTabAsSpaces();
      void SetReadTabAsSpaces(BOOL bNewValue);
      BOOL GetReportErrors();
      void SetReportErrors(BOOL bNewValue);
      BOOL GetSaveFromScrollingRegion();
      void SetSaveFromScrollingRegion(BOOL bNewValue);
      BOOL GetSavePasswords();
      void SetSavePasswords(BOOL bNewValue);
      BOOL GetSaveWindowPosition();
      void SetSaveWindowPosition(BOOL bNewValue);
      long GetScreenTopRow();
      void SetScreenTopRow(long nNewValue);
      long GetScrollOptimization();
      void SetScrollOptimization(long nNewValue);
      long GetSelectionEndColumn();
      void SetSelectionEndColumn(long nNewValue);
      long GetSelectionEndRow();
      void SetSelectionEndRow(long nNewValue);
      long GetSelectionStartColumn();
      void SetSelectionStartColumn(long nNewValue);
      long GetSelectionStartRow();
      void SetSelectionStartRow(long nNewValue);
      long GetSelectionType();
      void SetSelectionType(long nNewValue);
      CString GetSerialNumber();
      void SetSerialNumber(LPCTSTR lpszNewValue);
      CString GetSettingsAuthor();
      void SetSettingsAuthor(LPCTSTR lpszNewValue);
      CString GetSettingsComments();
      void SetSettingsComments(LPCTSTR lpszNewValue);
      CString GetSettingsFile();
      void SetSettingsFile(LPCTSTR lpszNewValue);
      CString GetSettingsTitle();
      void SetSettingsTitle(LPCTSTR lpszNewValue);
      BOOL GetShowControlCharacters();
      void SetShowControlCharacters(BOOL bNewValue);
      BOOL GetShowTerminalFrame();
      void SetShowTerminalFrame(BOOL bNewValue);
      BOOL GetShowTerminalKeyboard();
      void SetShowTerminalKeyboard(BOOL bNewValue);
      BOOL GetShowToolbar();
      void SetShowToolbar(BOOL bNewValue);
      long GetSingleByteUPSS();
      void SetSingleByteUPSS(long nNewValue);
      BOOL GetSmoothScroll();
      void SetSmoothScroll(BOOL bNewValue);
      long GetSpacesPerTab();
      void SetSpacesPerTab(long nNewValue);
      long GetStartupAction();
      void SetStartupAction(long nNewValue);
      CString GetStartupConnection();
      void SetStartupConnection(LPCTSTR lpszNewValue);
      CString GetStatusBar();
      void SetStatusBar(LPCTSTR lpszNewValue);
      long GetTerminalClass();
      void SetTerminalClass(long nNewValue);
      long GetTerminalSound();
      void SetTerminalSound(long nNewValue);
      long GetTerminalType();
      void SetTerminalType(long nNewValue);
      long GetTextFileCharacterSet();
      void SetTextFileCharacterSet(long nNewValue);
      long GetTop();
      void SetTop(long nNewValue);
      long GetTransfer8Dot3FilenameCase();
      void SetTransfer8Dot3FilenameCase(long nNewValue);
      long GetTransferDefaultProtocol();
      void SetTransferDefaultProtocol(long nNewValue);
      CString GetTransferDownloadDirectory();
      void SetTransferDownloadDirectory(LPCTSTR lpszNewValue);
      long GetTransferIfFileExistsDefault();
      void SetTransferIfFileExistsDefault(long nNewValue);
      BOOL GetTransferReceiveAs8Dot3();
      void SetTransferReceiveAs8Dot3(BOOL bNewValue);
      long GetTransferReceiveTimeout();
      void SetTransferReceiveTimeout(long nNewValue);
      long GetTransferRetryLimit();
      void SetTransferRetryLimit(long nNewValue);
      BOOL GetTransferSpacesToUnderscores();
      void SetTransferSpacesToUnderscores(BOOL bNewValue);
      long GetTransferStartTimeout();
      void SetTransferStartTimeout(long nNewValue);
      BOOL GetTransferStatusWindow();
      void SetTransferStatusWindow(BOOL bNewValue);
      BOOL GetTransferUnderscoresToSpaces();
      void SetTransferUnderscoresToSpaces(BOOL bNewValue);
      BOOL GetTranslateCharacters();
      void SetTranslateCharacters(BOOL bNewValue);
      BOOL GetTranslatePrintedCharacters();
      void SetTranslatePrintedCharacters(BOOL bNewValue);
      BOOL GetTransmitXonXoff();
      void SetTransmitXonXoff(BOOL bNewValue);
      BOOL GetUnderlineCharacters();
      void SetUnderlineCharacters(BOOL bNewValue);
      BOOL GetUseAnsiColor();
      void SetUseAnsiColor(BOOL bNewValue);
      BOOL GetUseDefaultPrinterFont();
      void SetUseDefaultPrinterFont(BOOL bNewValue);
      BOOL GetUseNRC();
      void SetUseNRC(BOOL bNewValue);
      BOOL GetUserDefinedKeysLocked();
      void SetUserDefinedKeysLocked(BOOL bNewValue);
      CString GetUserDirectory();
      void SetUserDirectory(LPCTSTR lpszNewValue);
      BOOL GetUserFeaturesLocked();
      void SetUserFeaturesLocked(BOOL bNewValue);
      long GetVTBackspaceSends();
      void SetVTBackspaceSends(long nNewValue);
      long GetVTCursorKeyMode();
      void SetVTCursorKeyMode(long nNewValue);
      long GetVTKeypadMode();
      void SetVTKeypadMode(long nNewValue);
      long GetVersionMajor();
      void SetVersionMajor(long nNewValue);
      long GetVersionMinor();
      void SetVersionMinor(long nNewValue);
      CString GetVersionString();
      void SetVersionString(LPCTSTR lpszNewValue);
      BOOL GetVerticalCoupling();
      void SetVerticalCoupling(BOOL bNewValue);
      BOOL GetVisible();
      void SetVisible(BOOL bNewValue);
      BOOL GetWeakDCS();
      void SetWeakDCS(BOOL bNewValue);
      long GetWidth();
      void SetWidth(long nNewValue);
      long GetWindowState();
      void SetWindowState(long nNewValue);
      BOOL GetWriteCtrlZAsEOF();
      void SetWriteCtrlZAsEOF(BOOL bNewValue);
      BOOL GetWriteSpacesAsTab();
      void SetWriteSpacesAsTab(BOOL bNewValue);
      long GetWRQCompression();
      void SetWRQCompression(long nNewValue);
      CString GetWRQEndCharacter();
      void SetWRQEndCharacter(LPCTSTR lpszNewValue);
      CString GetWRQExtraCharacters();
      void SetWRQExtraCharacters(LPCTSTR lpszNewValue);
      long GetWRQFastFileTransfer();
      void SetWRQFastFileTransfer(long nNewValue);
      long GetWRQFrameSize();
      void SetWRQFrameSize(long nNewValue);
      CString GetWRQFrameTerminator();
      void SetWRQFrameTerminator(LPCTSTR lpszNewValue);
      CString GetWRQHostErrorMessage();
      void SetWRQHostErrorMessage(LPCTSTR lpszNewValue);
      long GetWRQHostRecordSize();
      void SetWRQHostRecordSize(long nNewValue);
      long GetWRQHostSystem();
      void SetWRQHostSystem(long nNewValue);
      BOOL GetWRQKeepFile();
      void SetWRQKeepFile(BOOL bNewValue);
      long GetWRQMPEFilenames();
      void SetWRQMPEFilenames(long nNewValue);
      BOOL GetWRQMPEStream();
      void SetWRQMPEStream(BOOL bNewValue);
      BOOL GetWRQPreserveCounts();
      void SetWRQPreserveCounts(BOOL bNewValue);
      BOOL GetWRQPreserveDate();
      void SetWRQPreserveDate(BOOL bNewValue);
      BOOL GetWRQQEditFormat();
      void SetWRQQEditFormat(BOOL bNewValue);
      BOOL GetWRQRemoveExtension();
      void SetWRQRemoveExtension(BOOL bNewValue);
      BOOL GetWRQSendSpooled();
      void SetWRQSendSpooled(BOOL bNewValue);
      BOOL GetWRQShowHidden();
      void SetWRQShowHidden(BOOL bNewValue);
      CString GetWRQStartCharacter();
      void SetWRQStartCharacter(LPCTSTR lpszNewValue);
      CString GetWRQStartupCommand();
      void SetWRQStartupCommand(LPCTSTR lpszNewValue);
      BOOL GetWRQSubmitBatch();
      void SetWRQSubmitBatch(BOOL bNewValue);
      BOOL GetWRQSubmitPrint();
      void SetWRQSubmitPrint(BOOL bNewValue);
      long GetWRQTransferLink();
      void SetWRQTransferLink(long nNewValue);
      long GetWRQTransferType();
      void SetWRQTransferType(long nNewValue);
      BOOL GetWRQTransferWithAttributes();
      void SetWRQTransferWithAttributes(BOOL bNewValue);
      BOOL GetWRQTranslateCCtl();
      void SetWRQTranslateCCtl(BOOL bNewValue);
      BOOL GetWRQUseBlockReads();
      void SetWRQUseBlockReads(BOOL bNewValue);
      BOOL GetWRQUseCTermFrameSize();
      void SetWRQUseCTermFrameSize(BOOL bNewValue);
      long GetWRQWindowSize();
      void SetWRQWindowSize(long nNewValue);
      long GetXmodemExtension();
      void SetXmodemExtension(long nNewValue);
      long GetXmodemTransferType();
      void SetXmodemTransferType(long nNewValue);
      BOOL GetXmodemTranslateCharacters();
      void SetXmodemTranslateCharacters(BOOL bNewValue);
      BOOL GetZmodemAutoDownload();
      void SetZmodemAutoDownload(BOOL bNewValue);
      BOOL GetZmodemDeleteCancelledReceives();
      void SetZmodemDeleteCancelledReceives(BOOL bNewValue);
      long GetZmodemPacketSize();
      void SetZmodemPacketSize(long nNewValue);
      CString GetZmodemReceiveStartupCommand();
      void SetZmodemReceiveStartupCommand(LPCTSTR lpszNewValue);
      CString GetZmodemSendStartupCommand();
      void SetZmodemSendStartupCommand(LPCTSTR lpszNewValue);
      long GetZmodemTransferType();
      void SetZmodemTransferType(long nNewValue);
      BOOL GetZmodemTranslateCharacters();
      void SetZmodemTranslateCharacters(BOOL bNewValue);
      BOOL GetZmodemTranslateFilenames();
      void SetZmodemTranslateFilenames(BOOL bNewValue);
      long GetCompensateFrameSpaces();
      void SetCompensateFrameSpaces(long nNewValue);
      BOOL GetGlobalCapsLock();
      void SetGlobalCapsLock(BOOL bNewValue);
      BOOL GetGlobalNumLock();
      void SetGlobalNumLock(BOOL bNewValue);
      BOOL GetGlobalScrollLock();
      void SetGlobalScrollLock(BOOL bNewValue);
      BOOL GetJISRomanG0();
      void SetJISRomanG0(BOOL bNewValue);
      BOOL GetOnDemandFonts();
      void SetOnDemandFonts(BOOL bNewValue);
      BOOL GetProportionalFonts();
      void SetProportionalFonts(BOOL bNewValue);
      void Activate();
      CString GetKeyMapCommandArgs(long Modifiers, LPCTSTR Key);
      void SetPropertyProfile(LPCTSTR PropertyName, long IsEnabled);
      void PlaySound(LPCTSTR SoundFile, const VARIANT& Asynchronous);
      BOOL PropertyIsModifiable(LPCTSTR PropertyName);
      long GetFileType(LPCTSTR Filename);
      void Shell(LPCTSTR Application, const VARIANT& CommandLine, const VARIANT& WindowState, const VARIANT& Wait);
      void CopyAboutBoxInfo();
      void ConnectTemplate(const VARIANT& ConnectionName, const VARIANT& Options);
      void OpenSettingsExtended(LPCTSTR Filename, const VARIANT& Type, const VARIANT& Options);
      BOOL WaitForIncomingData(const VARIANT& Timeout, const VARIANT& Options);
      void FlashWindow(const VARIANT& Rate);
      void SetColorMap(long Attribute, long Foreground, long Background);
      long ForegroundColor(long Attribute);
      long BackgroundColor(long Attribute);
      void SetColorRGB(long Color, long Red, long Green, long Blue);
      long GetColorRGB(long Color, long WhichValue);
      long CharacterAttributes(long Row, long Column);
      void SetAnsiColorRGB(long AnsiColor, long Red, long Green, long Blue);
      long GetAnsiColorRGB(long AnsiColor, long WhichValue);
      void FTPStartServer(const VARIANT& UserName, const VARIANT& Password, const VARIANT& HostName, const VARIANT& Options);
      void FTPStopServer();
      void FTPReceiveFile(LPCTSTR LocalFile, LPCTSTR RemoteFile, const VARIANT& TransferType, const VARIANT& IfFileExists, const VARIANT& Before, const VARIANT& Since, const VARIANT& Exclude);
      void FTPSendFile(LPCTSTR LocalFile, LPCTSTR RemoteFile, const VARIANT& TransferType, const VARIANT& IfFileExists, const VARIANT& Before, const VARIANT& Since, const VARIANT& Exclude);
      CString GetPropertyInformation(const VARIANT& Name, const VARIANT& Options);
      void StartRecordingSilently(const VARIANT& Options);
      void DestroyToolbar(LPCTSTR toolbarName);
      void SetMouseMap(long Modifiers, LPCTSTR Chord, long CommandType, LPCTSTR Commands, const VARIANT& CommandArguments);
      void StatusBox(LPCTSTR Text, const VARIANT& Options);
      void CloseStatusBox();
      CString GetFolderName(const VARIANT& Title, const VARIANT& Text, const VARIANT& StartInFolder);
      BOOL GetAllowJIS();
      void SetAllowJIS(BOOL bNewValue);
      CString GetCommandLineSwitches();
      void SetCommandLineSwitches(LPCTSTR lpszNewValue);
      BOOL GetDisplayEnabled();
      void SetDisplayEnabled(BOOL bNewValue);
      BOOL GetFlashWindowOnDisconnect();
      void SetFlashWindowOnDisconnect(BOOL bNewValue);
      BOOL GetForceC1Controls();
      void SetForceC1Controls(BOOL bNewValue);
      BOOL GetMinimizeCPUUsage();
      void SetMinimizeCPUUsage(BOOL bNewValue);
      long GetFoundTextRow();
      void SetFoundTextRow(long nNewValue);
      long GetFoundTextColumn();
      void SetFoundTextColumn(long nNewValue);
      BOOL GetPrinterPassEscape();
      void SetPrinterPassEscape(BOOL bNewValue);
      BOOL GetRecording();
      void SetRecording(BOOL bNewValue);
      CString GetRBVersionString();
      void SetRBVersionString(LPCTSTR lpszNewValue);
      CString GetScriptFolder();
      void SetScriptFolder(LPCTSTR lpszNewValue);
      CString GetSettingsExtension();
      void SetSettingsExtension(LPCTSTR lpszNewValue);
      BOOL GetShowMenuBar();
      void SetShowMenuBar(BOOL bNewValue);
      BOOL GetShowStatusBar();
      void SetShowStatusBar(BOOL bNewValue);
      BOOL GetShowVerticalScrollBar();
      void SetShowVerticalScrollBar(BOOL bNewValue);
      BOOL GetTransferDisconnectWhenDone();
      void SetTransferDisconnectWhenDone(BOOL bNewValue);
      long GetWindowHandle();
      void SetWindowHandle(long nNewValue);
      CString GetWordBoundaryInclusive();
      void SetWordBoundaryInclusive(LPCTSTR lpszNewValue);
      CString GetWordBoundaryExclusive();
      void SetWordBoundaryExclusive(LPCTSTR lpszNewValue);
      BOOL GetWRQShowRecordSize();
      void SetWRQShowRecordSize(BOOL bNewValue);
      BOOL GetAutoScroll();
      void SetAutoScroll(BOOL bNewValue);
      BOOL GetPrintANSIColorBackground();
      void SetPrintANSIColorBackground(BOOL bNewValue);
      BOOL GetRecognizeDEL();
      void SetRecognizeDEL(BOOL bNewValue);
      long GetReceivedCR();
      void SetReceivedCR(long nNewValue);
      BOOL GetWyseProtectMode();
      void SetWyseProtectMode(BOOL bNewValue);
      BOOL GetWyseBlockMode();
      void SetWyseBlockMode(BOOL bNewValue);
      long GetWyseAttributeMode();
      void SetWyseAttributeMode(long nNewValue);
      long GetWyseBlockTerminator();
      void SetWyseBlockTerminator(long nNewValue);
      BOOL GetWyseAcceptNulls();
      void SetWyseAcceptNulls(BOOL bNewValue);
      long GetWyseReturnKey();
      void SetWyseReturnKey(long nNewValue);
      long GetWyseEnterKey();
      void SetWyseEnterKey(long nNewValue);
      long GetWyseLabelLines();
      void SetWyseLabelLines(long nNewValue);
      long GetWyseStatusLineDisplay();
      void SetWyseStatusLineDisplay(long nNewValue);
      BOOL GetShowTitleBar();
      void SetShowTitleBar(BOOL bNewValue);
      long GetPrinterOrientation();
      void SetPrinterOrientation(long nNewValue);
      BOOL GetDigitalLA210PrinterEmulation();
      void SetDigitalLA210PrinterEmulation(BOOL bNewValue);
      BOOL GetConfirmExit();
      void SetConfirmExit(BOOL bNewValue);
      long GetSaveChanges();
      void SetSaveChanges(long nNewValue);
      BOOL GetToolbarIncludeLabels();
      void SetToolbarIncludeLabels(BOOL bNewValue);
      long GetFTPTransferType();
      void SetFTPTransferType(long nNewValue);
      CString GetFTPUserName();
      void SetFTPUserName(LPCTSTR lpszNewValue);
      CString GetFTPPassword();
      void SetFTPPassword(LPCTSTR lpszNewValue);
      CString GetFTPHostName();
      void SetFTPHostName(LPCTSTR lpszNewValue);
      BOOL GetFTPTranslateCharacters();
      void SetFTPTranslateCharacters(BOOL bNewValue);
      long GetPrinterMarginBottom();
      void SetPrinterMarginBottom(long nNewValue);
      long GetPrinterMarginLeft();
      void SetPrinterMarginLeft(long nNewValue);
      long GetPrinterMarginRight();
      void SetPrinterMarginRight(long nNewValue);
      long GetPrinterMarginTop();
      void SetPrinterMarginTop(long nNewValue);
      long GetHotspotRow();
      void SetHotspotRow(long nNewValue);
      long GetHotspotColumn();
      void SetHotspotColumn(long nNewValue);
      long GetHotspotLength();
      void SetHotspotLength(long nNewValue);
      long GetHotspotsModifiers();
      void SetHotspotsModifiers(long nNewValue);
      long GetHotspotsChord();
      void SetHotspotsChord(long nNewValue);
      BOOL GetHotspotsEnabled();
      void SetHotspotsEnabled(BOOL bNewValue);
      BOOL GetHotspotsVisible();
      void SetHotspotsVisible(BOOL bNewValue);
      CString GetHotspotText();
      void SetHotspotText(LPCTSTR lpszNewValue);
      BOOL GetWRQFastCompression();
      void SetWRQFastCompression(BOOL bNewValue);
      BOOL GetWidthChangeClear();
      void SetWidthChangeClear(BOOL bNewValue);
      long GetMouseRow();
      void SetMouseRow(long nNewValue);
      long GetMouseColumn();
      void SetMouseColumn(long nNewValue);
      BOOL GetUseModemDialerV5();
      void SetUseModemDialerV5(BOOL bNewValue);
      CString GetShortcutFolder();
      void SetShortcutFolder(LPCTSTR lpszNewValue);
      BOOL GetCreateShortcut();
      void SetCreateShortcut(BOOL bNewValue);
      CString GetTransferAutoDetectASCIIExtensionList();
      void SetTransferAutoDetectASCIIExtensionList(LPCTSTR lpszNewValue);
      CString GetTransferAutoDetectBinaryExtensionList();
      void SetTransferAutoDetectBinaryExtensionList(LPCTSTR lpszNewValue);
      CString GetTransferAutoDetectImageLabelsExtensionList();
      void SetTransferAutoDetectImageLabelsExtensionList(LPCTSTR lpszNewValue);
      CString GetTransferAutoDetectScanExtensionList();
      void SetTransferAutoDetectScanExtensionList(LPCTSTR lpszNewValue);
      long GetTransferAutoDetectDefaultType();
      void SetTransferAutoDetectDefaultType(long nNewValue);
      long GetHostForDefaultSettings();
      void SetHostForDefaultSettings(long nNewValue);
      CString GetSiteDefaults();
      void SetSiteDefaults(LPCTSTR lpszNewValue);
      BOOL GetPrinterFitFontToPage();
      void SetPrinterFitFontToPage(BOOL bNewValue);
      long GetWebSecurity();
      void SetWebSecurity(long nNewValue);
      long CheckEvent();
      long CheckEventNumber(long EventNumber);
      void ClearEvents();
      void DefineEvent(long EventNumber, long EventType, const VARIANT& String, const VARIANT& Row, const VARIANT& Column, const VARIANT& Key);
      void EnableOnEvent(long OnEventNumber, long EnableOrDisable);
      void RemoveEvent(long EventNumber);
      void RemoveOnEvent(long EventNumber);
      void ResetEvent(long EventNumber);
      long WaitEvent(const VARIANT& Timeout, const VARIANT& Options);
      BOOL WaitEventNumber(long EventNumber, const VARIANT& Timeout, const VARIANT& Options);
      BOOL WaitForEvent(long EventType, const VARIANT& Timeout, const VARIANT& String, const VARIANT& Row, const VARIANT& Column, const VARIANT& Key, const VARIANT& Options);
      void OnEvent(long EventNumber, long EventType, long CommandType, LPCTSTR Commands, long Enable, long AfterEvent, const VARIANT& String, const VARIANT& Row, const VARIANT& Column, const VARIANT& Key, const VARIANT& CommandArguments);
      CString GetPassword(const VARIANT& Prompt, const VARIANT& HostUserName, const VARIANT& HostName, const VARIANT& Options);
      CString GetLoginProperty(const VARIANT& Property_, const VARIANT& Prompt, const VARIANT& HostUserName, const VARIANT& HostName, const VARIANT& Options);
      void RunMacro(LPCTSTR MacroName, const VARIANT& MacroData);
      void StopMacro();
      void CommitLoginProperties(const VARIANT& Options);
      void StartRecordingExtended(const VARIANT& Options);
      void FTPSetCurrentHostDirectory(LPCTSTR HostDirectory);
      CString FTPGetCurrentHostDirectory();
      void CancelExitEvent();
      void RaiseControlEvent(const VARIANT& Param1, const VARIANT& Param2);
      void PrintScreen(long Range, const VARIANT& Copies);
      void RunExternalMacro(LPCTSTR Filename, LPCTSTR MacroName, const VARIANT& MacroData);
      void StopRecordingMacro(long Destination, const VARIANT& Name, const VARIANT& Description, const VARIANT& Options);
      CString GetTransferPreset();
      void SetTransferPreset(LPCTSTR lpszNewValue);
      BOOL GetFileTypeSticky();
      void SetFileTypeSticky(BOOL bNewValue);
      BOOL GetSaveColors();
      void SetSaveColors(BOOL bNewValue);
      BOOL GetSaveConnection();
      void SetSaveConnection(BOOL bNewValue);
      BOOL GetSaveHotspots();
      void SetSaveHotspots(BOOL bNewValue);
      BOOL GetSaveKeymap();
      void SetSaveKeymap(BOOL bNewValue);
      BOOL GetSaveMenus();
      void SetSaveMenus(BOOL bNewValue);
      BOOL GetSaveMouseMap();
      void SetSaveMouseMap(BOOL bNewValue);
      BOOL GetSaveToolbars();
      void SetSaveToolbars(BOOL bNewValue);
      long GetFileOpenType();
      void SetFileOpenType(long nNewValue);
      BOOL GetPrinterAutoRowSize();
      void SetPrinterAutoRowSize(BOOL bNewValue);
      BOOL GetPrinterColumnsTiedToDisplay();
      void SetPrinterColumnsTiedToDisplay(BOOL bNewValue);
      BOOL GetPrinterColumnsSetOrientation();
      void SetPrinterColumnsSetOrientation(BOOL bNewValue);
      CString GetPCRecordSeparator();
      void SetPCRecordSeparator(LPCTSTR lpszNewValue);
      CString GetHostRecordSeparator();
      void SetHostRecordSeparator(LPCTSTR lpszNewValue);
      BOOL GetUsePCRecordSeparator();
      void SetUsePCRecordSeparator(BOOL bNewValue);
      BOOL GetUseHostRecordSeparator();
      void SetUseHostRecordSeparator(BOOL bNewValue);
      CString GetPCUserName();
      void SetPCUserName(LPCTSTR lpszNewValue);
      BOOL GetAdmitOne();
      void SetAdmitOne(BOOL bNewValue);
      long GetEventDefined();
      void SetEventDefined(long nNewValue);
      BOOL GetFTPTranslateFilenames();
      void SetFTPTranslateFilenames(BOOL bNewValue);
      long GetWindowRows();
      void SetWindowRows(long nNewValue);
      long GetAllowLegacyComm();
      void SetAllowLegacyComm(long nNewValue);
      BOOL GetT27DC1ClearsEOL();
      void SetT27DC1ClearsEOL(BOOL bNewValue);
      long GetT27DisplayPages();
      void SetT27DisplayPages(long nNewValue);
      BOOL GetT27InsertKeyInsertsSpace();
      void SetT27InsertKeyInsertsSpace(BOOL bNewValue);
      BOOL GetT27CursorWrap();
      void SetT27CursorWrap(BOOL bNewValue);
      BOOL GetT27SPCFYKeySendsPageNo();
      void SetT27SPCFYKeySendsPageNo(BOOL bNewValue);
      long GetT27SPCFYKeySends();
      void SetT27SPCFYKeySends(long nNewValue);
      BOOL GetT27LineAtATimeXmit();
      void SetT27LineAtATimeXmit(BOOL bNewValue);
      long GetT27HostReturn();
      void SetT27HostReturn(long nNewValue);
      long GetT27HostLinefeed();
      void SetT27HostLinefeed(long nNewValue);
      long GetT27ReturnKey();
      void SetT27ReturnKey(long nNewValue);
      BOOL GetT27CLRClearsUnprotected();
      void SetT27CLRClearsUnprotected(BOOL bNewValue);
      CString GetMacroData();
      void SetMacroData(LPCTSTR lpszNewValue);
      BOOL GetAllowMacroInterrupt();
      void SetAllowMacroInterrupt(BOOL bNewValue);
      BOOL GetT27ETXDisplay();
      void SetT27ETXDisplay(BOOL bNewValue);
      BOOL GetT27ETXAdvance();
      void SetT27ETXAdvance(BOOL bNewValue);
      long GetT27DC2Function();
      void SetT27DC2Function(long nNewValue);
      long GetT27AlternativeUSChar();
      void SetT27AlternativeUSChar(long nNewValue);
      long GetT27AlternativeRSChar();
      void SetT27AlternativeRSChar(long nNewValue);
      BOOL GetT27FormXmitToCursor();
      void SetT27FormXmitToCursor(BOOL bNewValue);
      long GetT27ReturnKeyInForms();
      void SetT27ReturnKeyInForms(long nNewValue);
      BOOL GetT27SOHClearsScreen();
      void SetT27SOHClearsScreen(BOOL bNewValue);
      BOOL GetT27SOHExitsForms();
      void SetT27SOHExitsForms(BOOL bNewValue);
      BOOL GetDataStreamTranslation();
      void SetDataStreamTranslation(BOOL bNewValue);
      BOOL GetElfAtochemEmulation();
      void SetElfAtochemEmulation(BOOL bNewValue);
      BOOL GetFTPUseWRQFTP();
      void SetFTPUseWRQFTP(BOOL bNewValue);
      CString GetUserData();
      void SetUserData(LPCTSTR lpszNewValue);
      BOOL GetT27ShiftLock();
      void SetT27ShiftLock(BOOL bNewValue);
      BOOL GetDrawingOptimization();
      void SetDrawingOptimization(BOOL bNewValue);
      LPDISPATCH GetVBProject();
      void SetVBProject(LPDISPATCH newValue);
   };
/////////////////////////////////////////////////////////////////////////////
// EReflection2 wrapper class

   class EReflection2 : public COleDispatchDriver
   {
   public:
      EReflection2() {}      // Calls COleDispatchDriver default constructor
      EReflection2(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
      EReflection2(const EReflection2& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
   public:

// Operations
      public:
   };
/////////////////////////////////////////////////////////////////////////////
// _IReflectionControl wrapper class

   class _IReflectionControl : public COleDispatchDriver
   {
   public:
      _IReflectionControl() {}      // Calls COleDispatchDriver default constructor
      _IReflectionControl(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
      _IReflectionControl(const _IReflectionControl& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
   public:

// Operations
      public:
   };

// ==============================
// = Constants
// ==============================
   const short rcTrue          = -1    ;  // True
   const short rcFalse         = 0     ;  // False
   const short rcDefaultOptions = 0    ;  // Use default options
   const short rcNone          = 0     ;  // None
   const short rcEnabled       = -1    ;  // Property, command or group of commands is enabled
   const short rcDisabled      = 0     ;  // Property, command or group of commands is disabled
   const short rcPartiallyEnabled = -2 ;  // Group of commands is partially enabled/disabled
   const short rcDefault       = 2     ;  // Restore to default
   const short rcWebOpenAlways = 0     ;  // Always open downloaded settings files
   const short rcWebOpenNever  = 1     ;  // Never open downloaded settings files
   const short rcWebOpenAskUser = 2    ;  // Ask user if downloaded settings files should be opened
   const short rcLogoff        = -1    ;  // Logoff when shutting down the Kermit server program
   const short rcNoLogoff      = 0     ;  // Do not logoff when shutting down the Kermit server program
   const short rcNoTranslation = 1     ;  // Do not translate between PC and host character set
   const short rcNoDisplay     = 2     ;  // Do not show incoming data in Reflection;  //s display
   const short rcQuietDisplay  = 2     ;  // (null)
   const short rcAllowKeystrokes = 4   ;  // Allow keystrokes during wait
   const short rcIgnoreBlockMode = 8   ;  // Transmit data to the host, even in block mode
   const short rcIgnoreCase    = 16    ;  // Treat uppercase and lowercase letters the same when matching characters
   const short rcDecodePassword = 32   ;  // Decode (if necessary) a macro recorder encoded password before transmitting
   const short rcHexData       = 64    ;  // Decode hexadecimal sequence so that binary sequence will not be affected by Unicode translation.
   const short rcSelection     = 16    ;  // The current selection
   const short rcScreen        = 32    ;  // The current terminal screen
   const short rcAll           = 64    ;  // The current terminal screen and all previous terminal screens
   const short rcWrappedRegion = 256   ;  // Wrapped region in Reflection;  //s display
   const short rcRectRegion    = 512   ;  // Rectangular region in Reflection's display
   const short rcAsPlainText   = 1024  ;  // Copy to clipboard as plain text
   const short rcAsTableText   = 2048  ;  // Copy to clipboard as table text
   const short rcAsRichText    = 4096  ;  // Copy to clipboard as Rich Text Format
   const short rcAsBitmap      = 8192  ;  // Copy to clipboard as bitmap graphics
   const short rcNormalKey     = 0     ;  // No key modifier
   const short rcAltKey        = 1     ;  // Alt key modifier
   const short rcOptionKey     = 1     ;  // (null)
   const short rcAlt           = 1     ;  // (null)
   const short rcCtrlKey       = 2     ;  // Control key modifier
   const short rcCtrl          = 2     ;  // (null)
   const short rcShiftKey      = 4     ;  // Shift key modifier
   const short rcShift         = 4     ;  // (null)
   const short rcASCII         = 0     ;  // ASCII file transfer
   const short rcBinary        = 1     ;  // Binary file transfer
   const short rcLabels        = 2     ;  // Labels file transfer
   const short rcImage         = 2     ;  // Image file transfer
   const short rcAutoDetect    = 3     ;  // Auto-Detect file transfer
   const short rcScan          = 5     ;  // Scan file to determine file transfer type
   const short rcSettings      = 1     ;  // All Reflection settings
   const short rcCurrentProduct = 15   ;  // Reflection settings for current product
   const short rcKeymap        = 2     ;  // Reflection keyboard mapping settings
   const short rcToolbar       = 3     ;  // Reflection toolbar configuration settings
   const short rcColors        = 4     ;  // Reflection color configuration settings
   const short rcHotspots      = 5     ;  // Reflection hotspots configuration settings
   const short rcConnection    = 7     ;  // Reflection connection configuration settings
   const short rcMenumap       = 36    ;  // Reflection menu mapping settings
   const short rcProfile       = 6     ;  // Reflection profiled commands
   const short rcUnknown       = 14    ;  // Unknown file type
   const short rcAllDefaults   = 14    ;  // Restore all settings, including macros
   const short rcVBADefaults   = 16    ;  // Restore only macro settings
   const short rcCancel        = 4     ;  // Cancel operation if file exists
   const short rcAskUser       = 0     ;  // Prompt user with choice
   const short rcOverwrite     = 1     ;  // Overwrite existing file
   const short rcDelete        = 5     ;  // Delete existing file
   const short rcAppend        = 2     ;  // Append to existing file
   const short rcRename        = 6     ;  // Rename existing file
   const short rcUpdate        = 7     ;  // Update existing file
   const short rcSkip          = 8     ;  // Skip existing file
   const short rcResume        = 9     ;  // Resume cancelled transfer if file exists
   const short rcUseRemote     = 10    ;  // Use remote if file exists
   const short rcPurge         = 11    ;  // Purge if file exists
   const short rcDOSCharacterSet = 1   ;  // Use DOS character set
   const short rcWindowsCharacterSet = 0 ;  // Use Windows character set
   const short rcRLE           = 1     ;  // Use run length encoding for compression
   const short rcHuffman       = 2     ;  // Use Huffman encoding for compression
   const short rcNegotiate     = 1     ;  // Negotiate fast file transfer
   const short rcAlways        = 2     ;  // Always use fast file transfer
   const short rcNever         = 3     ;  // Never user fast file transfer
   const short rcHP1000        = 3     ;  // HP 1000 host system
   const short rcHP3000        = 4     ;  // HP 3000 host system
   const short rcVMS           = 5     ;  // OpenVMS host system
   const short rcOpenVMS       = 5     ;  // OpenVMS host system
   const short rcUNIX          = 6     ;  // Unix host system
   const short rcOther         = 7     ;  // Other host system
   const short rcUnisys        = 8     ;  // UNISYS A-Series host system
   const short rcMPE           = 1     ;  // MPE
   const short rcMPEOnly       = 2     ;  // MPEOnly
   const short rcPOSIX         = 3     ;  // POSIX
   const short rcAuto          = 4     ;  // Reflection will automatically determine the proper setting
   const short rcAnonymous     = 1     ;  // Anonymous Log In
   const short rcNoLogInDialog = 2     ;  // Do not display log in dialog
   const short rcSimple        = 0     ;  // Simple beep
   const short rcWindowsBeep   = 2     ;  // Standard Windows beep
   const short rcDOSBeep       = 1     ;  // Standard DOS beep
   const short rcNoBeep        = 4     ;  // Do not beep
   const short rcHP            = 1     ;  // HP terminal class
   const short rcDEC           = 2     ;  // DEC terminal class
   const short rcHP2392A       = 100   ;  // HP2392A terminal
   const short rcHP70092       = 101   ;  // HP70092 terminal
   const short rcHP70094       = 102   ;  // HP70094 terminal
   const short rcVT52          = 200   ;  // VT52 terminal
   const short rcVT102         = 203   ;  // VT102 terminal
   const short rcVT220_7       = 205   ;  // VT220 7-Bit terminal
   const short rcVT220_8       = 206   ;  // VT220 8-Bit terminal
   const short rcVT300_7       = 207   ;  // VT300 7-Bit terminal
   const short rcVT300_8       = 208   ;  // VT300 8-Bit terminal
   const short rcVT400_7       = 210   ;  // VT400 7-Bit terminal
   const short rcVT400_8       = 211   ;  // VT400 8-Bit terminal
   const short rcANSIBBS       = 218   ;  // ANSI (BBS) terminal
   const short rcANSIUNIX      = 219   ;  // ANSI (UNIX) terminal
   const short rcTek401X       = 220   ;  // Tektronix 401x terminal
   const short rcADDS          = 229   ;  // ADDS VP2 terminal
   const short rcWYSE50        = 230   ;  // Wyse 50+ terminal
   const short rcWYSE60        = 231   ;  // Wyse 60 terminal
   const short rcDG215         = 232   ;  // DG 215 terminal
   const short rcT27           = 233   ;  // Unisys T27 terminal
   const short rcWRQ           = 3     ;  // WRQ file transfer protocol
   const short rcXmodem        = 4     ;  // Xmodem file transfer protocol
   const short rcZmodem        = 5     ;  // Zmodem file transfer protocol
   const short rcKermit        = 6     ;  // Kermit file transfer protocol
   const short rcFTP           = 7     ;  // FTP file transfer protocol
   const short rcUseBitmap     = 1     ;  // Use off-screen bitmap for scrolling
   const short rcStandardScroll = 2    ;  // Use standard scrolling
   const short rcDECSupplemental = 100 ;  // DEC supplemental character set
   const short rcISOLatin1     = 101   ;  // ISO Latin 1 (ISO-8859-1), Western Europe
   const short rcISOLatin_1    = 101   ;  // ISO Latin 1 (ISO-8859-1), Western Europe
   const short rcPC437_English = 102   ;  // PC codepage 437
   const short rcPC850_Multilingual = 103 ;  // PC codepage 850
   const short rcHPRoman8      = 104   ;  // HP Roman 8 character set
   const short rcHPRoman9      = 157   ;  // HP Roman 9 character set
   const short rcPC852_Slavic  = 105   ;  // PC codepage 852, Eastern Europe
   const short rcPC855_Cyrillic = 106  ;  // PC codepage 855, Cyrillic
   const short rcPC857_Turkish = 107   ;  // PC codepage 857, Turkish
   const short rcPC860_Portuguese = 108 ;  // PC codepage 860, Portuguese
   const short rcPC861_Icelandic = 109 ;  // PC codepage 861, Icelandic
   const short rcPC863_CanadianFrench = 110 ;  // PC codepage 863, Canadian-French
   const short rcPC864_Arabic  = 111   ;  // PC codepage 864, Arabic
   const short rcPC865_Nordic  = 112   ;  // PC codepage 865, Norwegian
   const short rcPC866_Cyrillic = 113  ;  // PC codepage 866, Cyrillic
   const short rcPC869_ModernGreek = 114 ;  // PC codepage 869, Modern Greek
   const short rcISOLatin2     = 115   ;  // ISO Latin 2 (ISO-8859-2), Eastern Europe
   const short rcISOLatin_2    = 115   ;  // ISO Latin 2 (ISO-8859-2), Eastern Europe
   const short rcISOLatin5     = 116   ;  // ISO Cyrillic (ISO-8859-5)
   const short rcISOCyrillic   = 116   ;  // ISO Cyrillic (ISO-8859-5)
   const short rcISOLatin6     = 117   ;  // ISO Arabic (ISO-8859-6)
   const short rcISOArabic     = 117   ;  // ISO Arabic (ISO-8859-6)
   const short rcISOLatin7     = 118   ;  // ISO Greek (ISO-8859-7)
   const short rcISOGreek      = 118   ;  // ISO Greek (ISO-8859-7)
   const short rcISOLatin8     = 119   ;  // ISO Hebrew (ISO-8859-8)
   const short rcISOHebrew     = 119   ;  // ISO Hebrew (ISO-8859-8)
   const short rcISOLatin9     = 120   ;  // ISO Latin 5 (ISO-8859-9), Turkish
   const short rcISOLatin_5    = 120   ;  // ISO Latin 5 (ISO-8859-9), Turkish
   const short rcISOLatin_9    = 156   ;  // ISO Latin 9 (ISO-8859-15), Western Europe
   const short rcShiftJIS      = 121   ;  // Double byte, SHIFTJIS
   const short rcJIS1990       = 122   ;  // Double byte, JIS x0208-1990
   const short rcJIS1983       = 123   ;  // Double byte, JIS x0208-1983
   const short rcJIS1978       = 124   ;  // Double byte, JIS C6226-1978
   const short rcDECKanji1983  = 125   ;  // Double byte, new DEC Kanji
   const short rcDECKanji1978  = 126   ;  // Double byte, old DEC Kanji
   const short rcEUCKanji      = 127   ;  // Double byte, EUC Kanji
   const short rcBig5          = 128   ;  // Double byte, Big 5 (Taiwan)
   const short rcCCDC          = 129   ;  // Double byte, CCDC (Taiwan)
   const short rcGBChinese     = 130   ;  // Double byte, GB (PRC)
   const short rcKorean        = 131   ;  // Double byte, Korean KCS 5601
   const short rcHPGreek       = 132   ;  // HP Greek character set
   const short rcDECGreek      = 133   ;  // DEC Supplemental Greek character set
   const short rcPC437G_Greek  = 134   ;  // PC codepage 437, Greek
   const short rcYUASCII       = 135   ;  // YUASCII 7-bit character set
   const short rcJISKatakana   = 136   ;  // Single-byte Katakana character set
   const short rcNECN88        = 137   ;  // NEC Host (double-byte) character set
   const short rcPC862_Hebrew  = 138   ;  // PC codepage 862, Hebrew
   const short rcHPHebrew      = 139   ;  // HP Hebrew character set
   const short rcDECHebrew     = 140   ;  // DEC Hebrew character set
   const short rc7BitHebrew    = 141   ;  // 7-Bit Hebrew character set
   const short rcDECCyrillic   = 142   ;  // DEC Cyrillic character set
   const short rcHPTurkish     = 143   ;  // HP Turkish character set
   const short rcDECTurkish    = 144   ;  // DEC Turkish character set
   const short rcPC220_Spanish = 145   ;  // PC codepage 220, Spanish
   const short rcPC437T_Turkish = 146  ;  // PC codepage 437T, Turkish
   const short rcSBig5         = 147   ;  // SBig5 character set
   const short rcThai988TISO   = 148   ;  // Thai 988 TISO character set
   const short rcThaiTISO      = 149   ;  // Thai TISO character set
   const short rcThaiKU        = 150   ;  // Thai KU character set
   const short rcThaiPrime     = 151   ;  // Thai Prime character set
   const short rcDGInternational = 152 ;  // DG International character set
   const short rcWindows1250   = 153   ;  // Windows CP 1250 character set
   const short rcEastern_Europe_7bit = 135 ;  // Eastern Europe 7-bit character set
   const short rcLatinGreek7   = 154   ;  // Latin/Greek 7-bit character set
   const short rcNoDither      = 1     ;  // Disable image dithering
   const short rcPartialDither = 2     ;  // Do partial image dithering
   const short rcFullDither    = 3     ;  // Do full image dithering
   const short rcUnlimitedScroll = -1  ;  // Scroll rate based on data throughput
   const short rcScrollByPage  = -2    ;  // Scroll a page at a time
   const short rcScrollBy1     = 1     ;  // Scroll 1 line at a time
   const short rcScrollBy2     = 2     ;  // Scroll 2 lines at a time
   const short rcScrollBy4     = 4     ;  // Scroll 4 lines at a time
   const short rcScrollBy8     = 8     ;  // Scroll 8 lines at a time
   const short rcScrollBy16    = 16    ;  // Scroll 16 lines at a time
   const short rcScrollBy32    = 32    ;  // Scroll 32 lines at a time
   const short rcScrollBy64    = 64    ;  // Scroll 64 lines at a time
   const short rcScrollBy128   = 128   ;  // Scroll 128 lines at a time
   const short rcChecksum1Byte = 1     ;  // One byte checksum
   const short rcChecksum2Byte = 2     ;  // Two byte checksum
   const short rcCRC           = 3     ;  // Cyclic redundancy check
   const short rcVT100         = 201   ;  // VT100 terminal
   const short rcVT101         = 202   ;  // VT101 terminal
   const short rcVT220         = 204   ;  // VT220 terminal
   const short rcVT320         = 209   ;  // VT320 terminal
   const short rcVT420         = 212   ;  // VT420 terminal
   const short rcWRQID         = 213   ;  // WRQ terminal
   const short rcVT240         = 214   ;  // VT240 terminal
   const short rcVT241         = 215   ;  // VT241 terminal
   const short rcVT330         = 216   ;  // VT330 terminal
   const short rcVT340         = 217   ;  // VT340 terminal
   const short rcVT80          = 221   ;  // VT80 terminal
   const short rcVT100J        = 222   ;  // VT100J terminal
   const short rcVT102J        = 223   ;  // VT102J terminal
   const short rcVT220J        = 224   ;  // VT220J terminal
   const short rcVT240J        = 225   ;  // VT240J terminal
   const short rcVT282         = 226   ;  // VT282 terminal
   const short rcVT286         = 227   ;  // VT286 terminal
   const short rcVT382         = 228   ;  // VT382 terminal
   const short rcCompress      = 1     ;  // Prints vertically
   const short rcRotate        = 2     ;  // Prints horizontally
   const short rcExpand        = 3     ;  // Prints vertically with expanded characters
   const short rcUSASCII       = 0     ;  // United States ASCII character set
   const short rcBritish       = 1     ;  // British
   const short rcFrench        = 3     ;  // French
   const short rcGerman        = 4     ;  // German
   const short rcItalian       = 5     ;  // Italian
   const short rcNorwegian     = 6     ;  // Norwegian
   const short rcDanish        = 16    ;  // Danish
   const short rcSwedish       = 7     ;  // Swedish
   const short rcDutch         = 24    ;  // Dutch
   const short rcSwissGerman   = 9     ;  // Swiss German
   const short rcEuropeanSpanish = 22  ;  // European Spanish
   const short rcLatinSpanish  = 23    ;  // Latin Spanish
   const short rcPortuguese    = 12    ;  // Portuguese
   const short rcFinnish       = 17    ;  // Finnish
   const short rcCanadianEnglish = 21  ;  // Canadian English
   const short rcFlemish       = 25    ;  // Flemish
   const short rcCanadianFrench = 2    ;  // Canadian French
   const short rcSwissFrench   = 8     ;  // Swiss French
   const short rcEnglish       = 0     ;  // English
   const short rcJapanese      = 26    ;  // Japanese
   const short rcLanguageUnknown = 255 ;  // Language Unknown
   const short rc4k            = 4     ;  // 4k (primary status response)
   const short rc8k            = 8     ;  // 8k (primary status response)
   const short rc12k           = 12    ;  // 12k (primary status response)
   const short rc15k           = 15    ;  // 15k (primary status response)
   const short rcLine          = 1     ;  // In block mode, transfer data one line at a time
   const short rcPage          = 2     ;  // In block mode, transfer data one page at a time
   const short rcVB            = 1     ;  // Enable/disable Visual Basic macros and Reflection Basic scripts
   const short rcRB            = 1     ;  // Obsolete synonym for rcVB
   const short rcRCL           = 2     ;  // Enable/disable Reflection Command Language
   const short rcRBHost        = 3     ;  // Obsolete synonym for rcHost
   const short rcHost          = 3     ;  // Enable/disable host-initiated commands
   const short rcVBLocal       = 4     ;  // Enable/disable user-initiated macros
   const short rcRBLocal       = 4     ;  // Obsolete synonym for rcVBLocal
   const short rcOLEAutomation = 5     ;  // Enable/disable access to Reflection via OLE Automation
   const short rcRCLHost       = 6     ;  // Obsolete synonym for rcHost
   const short rcRCLLocal      = 7     ;  // Enable/disable user-initiated RCL commands
   const short rcSetup         = 8     ;  // Enable/disable access to all setup menus and dialogs
   const short rcFileTransfer  = 9     ;  // Enable/disable access to file transfer menus and dialogs
   const short rcHostDirectory = 10    ;  // Enable/disable access to file transfer host directory information
   const short rcTracing       = 11    ;  // Enable/disable tracing
   const short rcMenus         = 12    ;  // Enable/disable all of Reflection;  //s menus
   const short rcSavePasswords = 13    ;  // Enable/disable saving and recording of passwords
   const short rcFileTransferReceive = 14 ;  // Enable/disable ability to receive files from the host computer using file transfer
   const short rcFileTransferSend = 15 ;  // Enable/disable ability to send files to the host computer using file transfer
   const short rcSecondInstance = 16   ;  // Enable/Disable multiple instances of Reflection
   const short rcUnsecureConnections = 17 ;  // Enable/Disable unsecure connections
   const short rcMenuConversion = 18   ;  // Enable/Disable conversion of custom menus
   const short rcSpeakerOn     = 1     ;  // Modem speaker is always on
   const short rcSpeakerOff    = 2     ;  // Modem speaker is always off
   const short rcSpeakerDialing = 3    ;  // Modem speaker is on during dialing
   const short rcSpeakerLow    = 4     ;  // Modem speaker volume is low
   const short rcSpeakerMedium = 5     ;  // Modem speaker volume is medium
   const short rcSpeakerHigh   = 6     ;  // Modem speaker volume is high
   const short rcNotMapped     = 0     ;  // This key is not mapped
   const short rcVBCommand     = 9     ;  // This key invokes a Visual Basic command
   const short rcVBMacro       = 8     ;  // This key invokes a Visual Basic macro
   const short rcRBCommand     = 1     ;  // This key invokes a Reflection Basic command
   const short rcRBScript      = 2     ;  // This key invokes a Reflection Basic script
   const short rcBuiltInFunction = 3   ;  // This key executes a built-in function
   const short rcTransmitString = 4    ;  // This key transmits a string with character translation
   const short rcRCLCommand    = 6     ;  // This key executes an RCL command or script
   const short rcDefaultMap    = 7     ;  // Restore this key to its default mapping
   const short rcReflection1   = 1     ;  // Reflection 1 session
   const short rcReflection2   = 2     ;  // Reflection 2 session
   const short rcReflection4   = 4     ;  // Reflection 4 session
   const short rcReflectionIBM = 8     ;  // Reflection IBM session
   const short rcFTPClient     = 16    ;  // Reflection FTP client session
   const short rcReflectionX   = 32    ;  // Reflection X session
   const short rcConnectionWizard = 64 ;  // Reflection Connection Wizard session
   const short rcSoftReset     = 1     ;  // Perform a soft reset of the terminal
   const short rcHardReset     = 2     ;  // Perform a hard reset of the terminal
   const short rcSerialStats   = 3     ;  // Reset the serial connection statistics
   const short rcNormalScanCode = 0    ;  // Normal scan code
   const short rcExtendedScanCode = 1  ;  // Extended scan code
   const short rcExtendedE1ScanCode = 2 ;  // Extended E1 scan code
   const short rcTraceDefault  = 1     ;  // Trace incoming and outgoing datacomm
   const short rcTraceTimed    = 2     ;  // Trace incoming and outgoing datacomm with timing information
   const short rcTraceIncomingOnly = 3 ;  // Trace incoming datacomm only
   const short rcTraceEvents   = 4     ;  // Trace events
   const short rcRBSource      = 8     ;  // Reflection Basic source code
   const short rcVBSource      = 9     ;  // Visual Basic source code
   const short rcRCLSource     = 13    ;  // RCL source code
   const short rcMinimized     = 1     ;  // Minimized (iconic) window
   const short rcMaximized     = 2     ;  // Maximized (full-screen) window
   const short rcNormal        = 0     ;  // Normal (restored) window
   const short rcUser          = 1     ;  // User defined key set
   const short rcModes         = 2     ;  // Mode definition key set
   const short rcDeviceControl = 3     ;  // Device control key set
   const short rcDeviceModes   = 4     ;  // Device modes key set
   const short rcToDevices     = 5     ;  // Destination device key set
   const short rcEnhanceVideo  = 6     ;  // Video enhancements key set
   const short rcDefineField   = 7     ;  // Field Definition key set
   const short rc7BitLink      = 1     ;  // 7-bit transfer link
   const short rc8BitLink      = 2     ;  // 8-bit transfer link
   const short rcUserDefinedLink = 3   ;  // User-defined transfer link
   const short rcDCD           = 1     ;  // Use DCD modem status to indicate connection state
   const short rcDSR           = 2     ;  // Use DSR modem status to indicate connection state
   const short rcCTS           = 3     ;  // Use CTS modem status to indicate connection state
   const short rcNoConnect     = 1     ;  // On startup, load settings file but do not connect
   const short rcAutoConnect   = 54    ;  // On startup, automatically connect using saved settings
   const short rcConnectionDirectory = 3 ;  // On startup, show the Connection Directory dialog
   const short rcConnectionSetup = 4   ;  // On startup, show the Connection Setup dialog
   const short rcUseSavedConnection = 5 ;  // On startup, connect using a saved connection from the Connection Directory
   const short rcOpenSettings  = 6     ;  // On startup, show the Open Settings dialog
   const short rcNormalMode    = 1     ;  // Normal cursor keys mode
   const short rcNumericMode   = 2     ;  // Numeric keypad mode
   const short rcApplicationMode = 3   ;  // Application keypad/cursor keys mode
   const short rcBackspaceKey  = 1     ;  // Transmit a backspace to the host
   const short rcDeleteKey     = 2     ;  // Transmit a delete to the host
   const short rcAllFields     = 1     ;  // Transmit all fields to the host in format mode
   const short rcModifiedFields = 2    ;  // Transmit only modified fields to the host in format mode
   const short rcNoStatusLine  = 1     ;  // Don;  //t show the host status line
   const short rcIndicator     = 2     ;  // Show indicator status line
   const short rcHostWritable  = 3     ;  // Show host writable status line
   const short rcToPrinter     = 1     ;  // Images are sent to printer
   const short rcToHost        = 2     ;  // Images are set to host
   const short rcLevel1        = 1     ;  // Level 1 sixel device (aspect ration 2:1)
   const short rcLevel2        = 2     ;  // Level 2 sixel device (variable aspect ratio and horizontal grid size)
   const short rcLA210         = 3     ;  // LA210 (1:1 aspect ratio with a horizontal grid size of about 338 x 0.025 mm)
   const short rcUppercase     = 1     ;  // Host file names are created using all uppercase letters
   const short rcLowercase     = 2     ;  // Host file names are created using all lowercase letters
   const short rcPreserveCase  = 3     ;  // Host file names are created preserving letter case.
   const short rcXmodemCRC     = 1     ;  // Specifies 2-byte CRC and 128-byte packets
   const short rcXmodem1k      = 2     ;  // Specifies 2-byte CRC and 1024-byte packets
   const short rcReceiverOverruns = 1  ;  // Overrun errors
   const short rcParityErrors  = 2     ;  // Parity errors
   const short rcFramingErrors = 3     ;  // Framing errors
   const short rcReceiveBufferOverflow = 4 ;  // Overflow in receive buffer
   const short rcBreakDetect   = 5     ;  // Interruption in transmitting signal
   const short rcUnderline     = 1     ;  // Underline cursor shape
   const short rcBlock         = 4     ;  // Block cursor shape
   const short rcVerticalBar   = 5     ;  // Vertical bar cursor shape
   const short rcNoColor       = -1    ;  // No color
   const short rcWhite         = 0     ;  // White
   const short rcGrey          = 1     ;  // Grey
   const short rcRed           = 2     ;  // Red
   const short rcBlue          = 3     ;  // Blue
   const short rcGreen         = 4     ;  // Green
   const short rcYellow        = 5     ;  // Yellow
   const short rcCyan          = 6     ;  // Cyan
   const short rcMagenta       = 7     ;  // Magenta
   const short rcBlack         = 8     ;  // Black
   const short rcDkGrey        = 9     ;  // Dark Grey
   const short rcDkRed         = 10    ;  // Dark Red
   const short rcDkBlue        = 11    ;  // Dark Blue
   const short rcDkGreen       = 12    ;  // Dark Green
   const short rcDkYellow      = 13    ;  // Dark Yellow
   const short rcDkCyan        = 14    ;  // Dark Cyan
   const short rcDkMagenta     = 15    ;  // Dark Magenta
   const short rcAnsiWhite     = 23    ;  // ANSI White
   const short rcAnsiGrey      = 24    ;  // ANSI Grey
   const short rcAnsiRed       = 20    ;  // ANSI Red
   const short rcAnsiBlue      = 17    ;  // ANSI Blue
   const short rcAnsiGreen     = 18    ;  // ANSI Green
   const short rcAnsiBrown     = 22    ;  // ANSI Brown
   const short rcAnsiCyan      = 19    ;  // ANSI Cyan
   const short rcAnsiMagenta   = 21    ;  // ANSI Magenta
   const short rcAnsiBlack     = 16    ;  // ANSI Black
   const short rcAnsiLtWhite   = 31    ;  // ANSI Light White
   const short rcAnsiLtRed     = 28    ;  // ANSI Light Red
   const short rcAnsiLtBlue    = 25    ;  // ANSI Light Blue
   const short rcAnsiLtGreen   = 26    ;  // ANSI Light Green
   const short rcAnsiYellow    = 30    ;  // ANSI Yellow
   const short rcAnsiLtCyan    = 27    ;  // ANSI Light Cyan
   const short rcAnsiLtMagenta = 29    ;  // ANSI Light Magenta
   const short rcAttributeCharacter = 0 ;  // Wyse character attribute mode
   const short rcAttributeLine = 1     ;  // Wyse line attribute mode
   const short rcAttributePage = 2     ;  // Wyse page attribute mode
   const short rcUSCR          = 0     ;  // Wyse Block Terminator is US/CR
   const short rcCRETX         = 1     ;  // Wyse Block Terminator is CR/ETX
   const short rcWyseCR        = 0     ;  // Wyse return/enter keys send CR
   const short rcWyseCRLF      = 1     ;  // Wyse return/enter keys send CRLF
   const short rcWyseTAB       = 2     ;  // Wyse return/enter keys send tab
   const short rcNoCharacter   = -1    ;  // No character, past end of line
   const short rcPlainAttribute = 0    ;  // Plain character
   const short rcBlinkAttribute = 1    ;  // Blinking character
   const short rcInverseAttribute = 2  ;  // Inverse text character
   const short rcUnderlineAttribute = 4 ;  // Underlined character
   const short rcBoldAttribute = 8     ;  // Bold character
   const short rcHalfbrightAttribute = 8 ;  // Halfbright character
   const short rcFunctionKeys  = 16    ;  // HP Terminal Function Keys
   const short rcWyseStatusOff = 0     ;  // Wyse status line is off
   const short rcWyseStatusEdit = 1    ;  // Wyse status line is Edit
   const short rcWyseStatusStandard = 2 ;  // Wyse status line is Standard
   const short rcDefaultOrientation = 0 ;  // Print with printer default orientation
   const short rcPortraitOrientation = 1 ;  // Print in portrait orientation
   const short rcLandscapeOrientation = 2 ;  // Print in landscape orientation
   const short rcLeftButton    = 513   ;  // Left mouse button
   const short rcMiddleButton  = 516   ;  // Middle mouse button
   const short rcRightButton   = 514   ;  // Right mouse button
   const short rcLeftButton_DoubleClick = 521 ;  // Double-click of left mouse button
   const short rcMiddleButton_DoubleClick = 524 ;  // Double-click of middle mouse button
   const short rcRightButton_DoubleClick = 522 ;  // Double-click of right mouse button
   const short rcStatusBoxTitleBar = 1 ;  // Show the Title Bar in the StatusBox
   const short rcChangesNever  = 0     ;  // Never save changes when exiting Reflection
   const short rcChangesAlways = -1    ;  // Always save changes when exiting Reflection
   const short rcChangesAskUser = 2    ;  // Ask user whether to save changes when exiting Reflection
   const short rcPrintGraphColor = 0   ;  // Graphics image is printed in color
   const short rcPrintGraphMonochrome = 1 ;  // Graphic image is printed in monochrome
   const short rcPrintGraphicsHLS = 0  ;  // Graphic Color Image is printed in HLS
   const short rcPrintGraphicsRGB = 1  ;  // Graphic Color Image is printed in RGB
   const short rcEnable        = 1     ;  // Enable an Event
   const short rcDisable       = 0     ;  // Disable an Event
   const short rcEventDisable  = 2     ;  // Disable an Event after performing action
   const short rcEventReenable = 1     ;  // Re-enable an Event after performing action
   const short rcEventRemove   = 3     ;  // Remove an Event after performing action
   const short rcAllEvents     = 0     ;  // Applies to all events
   const short rcNextEvent     = 0     ;  // Use next available event number
   const short rcEvConnected   = 2     ;  // Event: connection established
   const short rcEvDisconnected = 3    ;  // Event: connection terminated
   const short rcReflectionStart = 13  ;  // Event: Reflection started
   const short rcReflectionExit = 14   ;  // Event: Reflection is exiting
   const short rcTerminalKeystroke = 12 ;  // Event: A terminal keystoke is sent
   const short rcLoadSettingsFile = 15 ;  // Event: A settings file is loading
   const short rcTime          = 11    ;  // Event: Time elapsed since event defined
   const short rcTimeOfDay     = 10    ;  // Event: A specific time of day
   const short rcSilence       = 0     ;  // Event: A period of no datacomm
   const short rcKbdEnabled    = 1     ;  // Event: Keyboard enabled for specified time
   const short rcBlockModeEnter = 16   ;  // Event: Terminal enters block mode
   const short rcBlockModeExit = 17    ;  // Event: Terminal exits block mode
   const short rcIsPassword    = 1     ;  // Login property is a password
   const short rcEnterPos      = 6     ;  // Event: Cursor enters a position
   const short rcExitPos       = 7     ;  // Event: Cursor exits a position
   const short rcDisplayString = 9     ;  // Event: String appears on screen
   const short rcCommString    = 8     ;  // Event: String received from host
   const short rcAnyRow        = 0     ;  // Event: can occur on any screen row
   const short rcAnyCol        = 0     ;  // Event: can occur on any screen column
   const short rcFileTransferDone = 19 ;  // Event: When a file transfer has finished
   const short rcT27SpecifyASCII = 0   ;  // T27 SPCFY key sends ASCII
   const short rcT27SpecifyHex = 1     ;  // T27 SPCFY key sends hex
   const short rcT27CRLF       = 0     ;  // T27 return is CRLF
   const short rcT27CR         = 1     ;  // T27 return is CR
   const short rcT27LF         = 0     ;  // T27 linefeed is LF
   const short rcT27CR_LF      = 1     ;  // T27 linefeed is CRLF
   const short rcT27DC2TogglesForms = 0 ;  // T27 DC2 toggles forms
   const short rcT27DC2AdvDCP  = 1     ;  // T27 DC2 advances DCP
   const short rcT27ReturnFormsExits = 0 ;  // T27 return key in forms exits field
   const short rcT27ReturnFormsNextLine = 1 ;  // T27 return key in forms goes to next line
   const short rcLegacyCommNever = 0   ;  // Never allow the use of thunking comm protocols
   const short rcLegacyCommAsNeeded = 1 ;  // Use thunking comm protocols if necessary
   const short rcLegacyCommOnly = 2    ;  // Only use thunking protocols (for troubleshooting)
   const short rcAnyTerminalKey = 0    ;  // Any terminal keystroke satisfies event
   const short rcSilently      = 1     ;  // Suppress recording toolbar
   const short rcWithPrompts   = 2     ;  // Ask about how to record each prompt
   const short rcMacro         = 1     ;  // Destination for StopRecordingMacro
   const short rcClipboard     = 2     ;  // Destination for StopRecordingMacro
   const short rcDiscard       = -1    ;  // Destination for StopRecordingMacro

// ==============================
// = ErrorValues
// ==============================
   const short rcErrReadOnlyProperty = 10000 ;  // Attempting to set the value of a read-only property
   const short rcErrInvalidBuiltInFunction = 10001 ;  // Unrecognized or invalid built-in function
   const short rcErrInvalidRCLExpression = 10002 ;  // Specified string is not a valid RCL expression
   const short rcErrInvalidRCLCommand = 10003 ;  // Specified string is not a valid RCL command
   const short rcErrInvalidTerminator = 10004 ;  // Invalid or empty string specified for read terminator
   const short rcErrTimeout    = 10005 ;  // Method timed out
   const short rcErrExpectOneDArray = 10006 ;  // Method requires a one-dimensional array
   const short rcErrExpectStringArray = 10007 ;  // Method requires a string array
   const short rcErrEmptyWaitForArray = 10008 ;  // At least one wait for string must be specified
   const short rcErrOperationFailed = 10009 ;  // The Reflection API call failed
   const short rcErrAbortedByUser = 10010 ;  // Operation cancelled by user
   const short rcErrPutPropertyFailed = 10011 ;  // Property put failed
   const short rcErrNotImplemented = 4080 ;  // Method or property is not implemented
   const short rcErrInvalidPropertyValue = 10012 ;  // Property value is invalid or out of range
   const short rcErrInvalidArgument = 10013 ;  // One or more arguments is invalid or out of range
   const short rcErrTypeMismatch = 10014 ;  // One or more arguments is of the wrong type
   const short rcErrBadTimeArgument = 10015 ;  // Invalid time argument
   const short rcErrBadDateArgument = 10016 ;  // Invalid date argument
   const short rcErrAlreadyInServerMode = 10017 ;  // Host file transfer program is already running in server mode
   const short rcErrInvalidTransferType = 10018 ;  // Invalid transfer type
   const short rcErrInvalidIfFileExists = 10019 ;  // Invalid if-file-exists option
   const short rcErrMissingHostFilename = 10020 ;  // Host file name must be specified
   const short rcErrMissingLocalFilename = 10021 ;  // Local file name must be specified
   const short rcErrOneXferAtATime = 10022 ;  // Only one file transfer is allowed at a time
   const short rcErrNotConnected = 10023 ;  // A connection is required to execute this method
   const short rcErrProfileLocked = 10024 ;  // Command profile is already locked
   const short rcErrNeedLockPassword = 10025 ;  // Password is required to lock the command profile
   const short rcErrNeedUnlockPassword = 10026 ;  // Password is required to unlock the command profile
   const short rcErrCantUnlockProfile = 10027 ;  // Command profile is permanently locked and cannot be unlocked
   const short rcErrTransferProtocol = 10028 ;  // Transfer protocol error
   const short rcErrTransferFailed = 10029 ;  // File transfer failed
   const short rcErrTransferComFailed = 10030 ;  // Communications error during transfer
   const short rcErrTransferTraceFailed = 10031 ;  // Tracing error during transfer
   const short rcErrNoHostResponse = 10032 ;  // No response from host transfer program
   const short rcErrHostTransferError = 10033 ;  // Transfer error occurred on host
   const short rcErrNoUpdateTransfer = 10034 ;  // No update transfer
   const short rcErrTransferLinkFailed = 10035 ;  // Communications error during transfer - unable to communicate with host
   const short rcErrCantStartTransfer = 10036 ;  // Unable to start file transfer
   const short rcErrIncompatibleHost = 10037 ;  // Incompatible host transfer program
   const short rcErrInvalidTerminalKey = 10038 ;  // Invalid terminal key constant
   const short rcErrLocalFileExists = 10039 ;  // Local file already exists
   const short rcErrLocalFileDoesNotExist = 10040 ;  // Local file does not exist
   const short rcErrCantReadFromFile = 10041 ;  // Can;  //t read from local file
   const short rcErrCantWriteToFile = 10042 ;  // Can;  //t write to local file
   const short rcErrCantOpenLocalFile = 10043 ;  // Can;  //t open local file for reading
   const short rcErrCantCreateLocalFile = 10044 ;  // Can;  //t create local file
   const short rcErrAccessDenied = 10045 ;  // Access to file denied
   const short rcErrOutOfDiskSpace = 10046 ;  // Out of disk space
   const short rcErrInvalidTraceType = 10047 ;  // Invalid trace type
   const short rcErrCommandDisabled = 10048 ;  // Command has been disabled
   const short rcErrAlreadyTracing = 10049 ;  // Trace is already enabled
   const short rcErrInvalidTarget = 10050 ;  // Invalid target script language
   const short rcErrFastTransferFailed = 10051 ;  // Fast file transfer failed
   const short rcErrInvalidKeyModifiers = 10052 ;  // Invalid key modifier(s)
   const short rcErrInvalidKeyName = 10053 ;  // Invalid key name
   const short rcErrInvalidCommandType = 10054 ;  // Invalid command type
   const short rcErrKeyReserved = 10055 ;  // Key is reserved and cannot be remapped
   const short rcErrInvalidScanType = 10056 ;  // Invalid scan code type
   const short rcErrInvalidScanCode = 10057 ;  // Invalid scan code value
   const short rcErrInvalidScanName = 10058 ;  // Invalid scan code name
   const short rcErrInvalidSessionType = 4220 ;  // Invalid session type
   const short rcErrProductNotFound = 10059 ;  // Could not find specified product
   const short rcErrDDEStringTooLong = 10060 ;  // DDE command or value string is too long
   const short rcErrDDENoResponse = 10061 ;  // No DDE servers responded
   const short rcErrDDEInvalidID = 10062 ;  // Invalid DDE conversation ID
   const short rcErrDDEConvLimit = 10063 ;  // Maximum number of DDE conversations established
   const short rcErrDDEServerTimeout = 10064 ;  // DDE server timed out
   const short rcErrDDEServerBusy = 10065 ;  // DDE server busy
   const short rcErrAlreadyConnected = 10066 ;  // A connection is currently active
   const short rcErrConnectionError = 10067 ;  // General connection error
   const short rcErrStringTooLarge = 10068 ;  // Method cannot return more than 64k of data
   const short rcErrReflectionBusy = 10069 ;  // Reflection is busy
   const short rcErrCantWriteConnectionDir = 10070 ;  // Cannot write to Connection Directory
   const short rcErrCantFindConnectionDir = 10071 ;  // Connection Directory could not be found or does not exist
   const short rcErrInvalidConnectionValue = 10072 ;  // Invalid connection setting value
   const short rcErrInvalidConnectionKeyword = 10073 ;  // Invalid connection setting keyword
   const short rcErrConnectionValueReadOnly = 10074 ;  // Connection setting cannot be changed
   const short rcErrConnectionTypeReadOnly = 10075 ;  // Connection type cannot be changed
   const short rcErrNoSelection = 10076 ;  // No selection exists
   const short rcErrNothingFound = 10077 ;  // No text found
   const short rcErrInvalidKeywordForType = 10078 ;  // Connection setting keyword is invalid for this connection type
   const short rcErrDisconnectedDuringWait = 10079 ;  // Disconnected from host while reading or waiting for text
   const short rcErrNeedNativeHost = 10080 ;  // A Native Mode version of the host file transfer program is required
   const short rcErrNeedNewerHost = 10081 ;  // A newer version of the host file transfer program is required
   const short rcErrCommandNotValidInAnsiMode = 10083 ;  // Command is not valid in ANSI mode
   const short rcErrCommandOnlyValidInAnsiMode = 10084 ;  // Command is only valid in ANSI mode
   const short rcErrCantOpenInternetSession = 10085 ;  // Unable to open internet session
   const short rcErrCantConnectToFTPHost = 10086 ;  // Unable to connect to FTP host
   const short rcErrCantLogInToFTPHost = 10087 ;  // Unable to log in to FTP host
   const short rcErrHostFileDoesntExist = 10088 ;  // File does not exist on FTP host
   const short rcErrCantOpenFileOnHost = 10090 ;  // Unable open file on FTP server
   const short rcErrFTPLogInCancelled = 10089 ;  // FTP log in cancelled
   const short rcErrCantUpdateFile = 10091 ;  // File could not be updated
   const short rcErrHostFileExists = 10092 ;  // Host file already exists
   const short rcErrMethodNotValid = 10093 ;  // Method is not valid for connection type
   const short rcErrNotInFTPServerMode = 10094 ;  // File transfer needs to be running in FTP server mode
   const short rcErrInvalidEventNumber = 4665 ;  // The specified event number is not valid
   const short rcErrAPIInvalidEvent = 4142 ;  // The specified event number is not valid
   const short rcErrMaxEventsDefined = 4667 ;  // The maximum number of events have already been defined
   const short rcErrMacroNoExist = 10095 ;  // The specified macro does not exist
   const short rcErrUnavailableWhenControl = 10096 ;  // This function not available when running Reflection as an ActiveX control
   const short rcErrUnavailableWhenEmbedded = 10097 ;  // This function not available when running Reflection as a document object
   const short rcErrCannotLoadLibrary = 10098 ;  // Returned by connect command
   const short rcErrDirectoryDoesNotExist = 10099 ;  // Directory does not exist
   const short rcErrInvalidMacroName = 10100 ;  // Macro name is invalid

// ==============================
// = ControlCodes
// ==============================
   const short rcNUL           = 0     ;  // NULL
   const short rcSOH           = 1     ;  // Start of header
   const short rcSTX           = 2     ;  // Start of text
   const short rcETX           = 3     ;  // End of text
   const short rcEOT           = 4     ;  // End of transmission
   const short rcENQ           = 5     ;  // Enquiry
   const short rcACK           = 6     ;  // Acknowledge
   const short rcBEL           = 7     ;  // Bell
   const short rcBS            = 8     ;  // Backspace
   const short rcHT            = 9     ;  // Horizontal tab
   const short rcLF            = 10    ;  // Linefeed
   const short rcVT            = 11    ;  // Vertical tab
   const short rcFF            = 12    ;  // Form feed
   const short rcCR            = 13    ;  // Carriage return
   const short rcSO            = 14    ;  // Shift out
   const short rcSI            = 15    ;  // Shift in
   const short rcDLE           = 16    ;  // Data link escape
   const short rcDC1           = 17    ;  // Device control 1 (XON)
   const short rcDC2           = 18    ;  // Device control 2
   const short rcDC3           = 19    ;  // Device control 3 (XOFF)
   const short rcDC4           = 20    ;  // Device control 4
   const short rcNAK           = 21    ;  // Negative acknowledge
   const short rcSYN           = 22    ;  // Synchronous idle
   const short rcETB           = 23    ;  // End of transmission block
   const short rcCAN           = 24    ;  // Cancel
   const short rcEM            = 25    ;  // End of medium
   const short rcSUB           = 26    ;  // Substitute
   const short rcESC           = 27    ;  // Escape
   const short rcFS            = 28    ;  // Field separator
   const short rcGS            = 29    ;  // Group separator
   const short rcRS            = 30    ;  // Record separator
   const short rcUS            = 31    ;  // Unit separator
   const short rcDEL           = 127   ;  // Delete
   const short rcIND           = 132   ;  // Index
   const short rcNEL           = 133   ;  // Next Line
   const short rcSSA           = 134   ;  // Start selected area
   const short rcESA           = 135   ;  // End selected area
   const short rcHTS           = 136   ;  // Horizontal tab set
   const short rcHTJ           = 137   ;  // Horizontal tab with justification
   const short rcVTS           = 138   ;  // Vertical tab set
   const short rcPLD           = 139   ;  // Partial line down
   const short rcPLU           = 140   ;  // Partial line up
   const short rcRI            = 141   ;  // Reverse index
   const short rcSS2           = 142   ;  // Single shift 2
   const short rcSS3           = 143   ;  // Single shift 3
   const short rcDCS           = 144   ;  // Device control string
   const short rcPU1           = 145   ;  // Private use 1
   const short rcPU2           = 146   ;  // Private use 2
   const short rcSTS           = 147   ;  // Set transmit state
   const short rcCCH           = 148   ;  // Cancel character
   const short rcMW            = 149   ;  // Message waiting
   const short rcSPA           = 150   ;  // Start protected area
   const short rcEPA           = 151   ;  // End protected area
   const short rcCSI           = 155   ;  // Control sequence introducer
   const short rcST            = 156   ;  // String terminator
   const short rcOSC           = 157   ;  // Operating system command
   const short rcPM            = 158   ;  // Privacy message
   const short rcAPC           = 159   ;  // Application program command

// ==============================
// = TerminalKeys
// ==============================
   const short rcHpBackSpaceKey = 600  ;  // BackSpace terminal key (HP emulation)
   const short rcHpBackTabKey  = 601   ;  // BackTab terminal key (HP emulation)
   const short rcHpBlinkVideoKey = 602 ;  // Blink video terminal key (HP emulation)
   const short rcHpBreakKey    = 603   ;  // Break terminal key (HP emulation)
   const short rcHpClearDisplayKey = 604 ;  // Clear display terminal key (HP emulation)
   const short rcHpClearLineKey = 605  ;  // Clear line terminal key (HP emulation)
   const short rcHpDefaultF1Key = 606  ;  // Default F1 terminal key (HP emulation)
   const short rcHpDefaultF2Key = 607  ;  // Default F2 terminal key (HP emulation)
   const short rcHpDefaultF3Key = 608  ;  // Default F3 terminal key (HP emulation)
   const short rcHpDefaultF4Key = 609  ;  // Default F4 terminal key (HP emulation)
   const short rcHpDefaultF5Key = 610  ;  // Default F5 terminal key (HP emulation)
   const short rcHpDefaultF6Key = 611  ;  // Default F6 terminal key (HP emulation)
   const short rcHpDefaultF7Key = 612  ;  // Default F7 terminal key (HP emulation)
   const short rcHpDefaultF8Key = 613  ;  // Default F8 terminal key (HP emulation)
   const short rcHpDefineFieldKeysKey = 614 ;  // Define field keys terminal key (HP emulation)
   const short rcHpDeleteKey   = 615   ;  // Delete terminal key (HP emulation)
   const short rcHpDeleteCharKey = 616 ;  // Delete character terminal key (HP emulation)
   const short rcHpDeleteCharWrapKey = 617 ;  // Delete character with wrap terminal key (HP emulation)
   const short rcHpDeleteLineKey = 618 ;  // Delete line terminal key (HP emulation)
   const short rcHpDeviceControlKey = 619 ;  // Device control terminal key (HP emulation)
   const short rcHpDeviceModesKey = 620 ;  // Device modes terminal key (HP emulation)
   const short rcHpDownKey     = 621   ;  // Cursor down terminal key (HP emulation)
   const short rcHpEnhanceFieldKeysKey = 622 ;  // Enhance field keys terminal key (HP emulation)
   const short rcHpEnterKey    = 623   ;  // Enter terminal key (HP emulation)
   const short rcHpEscKey      = 624   ;  // Escape terminal key (HP emulation)
   const short rcHpF1Key       = 625   ;  // F1 terminal key (HP emulation)
   const short rcHpF2Key       = 626   ;  // F2 terminal key (HP emulation)
   const short rcHpF3Key       = 627   ;  // F3 terminal key (HP emulation)
   const short rcHpF4Key       = 628   ;  // F4 terminal key (HP emulation)
   const short rcHpF5Key       = 629   ;  // F5 terminal key (HP emulation)
   const short rcHpF6Key       = 630   ;  // F6 terminal key (HP emulation)
   const short rcHpF7Key       = 631   ;  // F7 terminal key (HP emulation)
   const short rcHpF8Key       = 632   ;  // F8 terminal key (HP emulation)
   const short rcHpHalfBrightVideoKey = 633 ;  // Half-bright video terminal key (HP emulation)
   const short rcHpHideFunctionKeysKey = 634 ;  // Hide function keys terminal key (HP emulation)
   const short rcHpHomeDownKey = 635   ;  // Home down terminal key (HP emulation)
   const short rcHpHomeUpKey   = 636   ;  // Home up terminal key (HP emulation)
   const short rcHpInsertCharKey = 637 ;  // Insert character terminal key (HP emulation)
   const short rcHpInsertCharWrapKey = 638 ;  // Insert character with wrap terminal key (HP emulation)
   const short rcHpInsertLineKey = 639 ;  // Insert line terminal key (HP emulation)
   const short rcHpInverseVideoKey = 640 ;  // Inverse video terminal key (HP emulation)
   const short rcHpLeftKey     = 641   ;  // Cursor left terminal key (HP emulation)
   const short rcHpModesKey    = 642   ;  // Modes terminal key (HP emulation)
   const short rcHpMenuKey     = 643   ;  // Menu terminal key (HP emulation)
   const short rcHpNextPageKey = 644   ;  // Next page terminal key (HP emulation)
   const short rcHpPrevPageKey = 645   ;  // Previous page terminal key (HP emulation)
   const short rcHpPrintKey    = 646   ;  // Print terminal key (HP emulation)
   const short rcHpRecallUserKeysKey = 647 ;  // Recall user keys terminal key (HP emulation)
   const short rcHpReturnKey   = 648   ;  // Return terminal key (HP emulation)
   const short rcHpRightKey    = 649   ;  // Cursor right terminal key (HP emulation)
   const short rcHpSecurityVideoKey = 650 ;  // Security video terminal key (HP emulation)
   const short rcHpSetEnhancementKey = 651 ;  // Set enhancement terminal key (HP emulation)
   const short rcHpScrollDownKey = 652 ;  // Scroll down terminal key (HP emulation)
   const short rcHpScrollUpKey = 653   ;  // Scroll up terminal key (HP emulation)
   const short rcHpSelectKey   = 654   ;  // Select terminal key (HP emulation)
   const short rcHpStartUnprotectedKey = 655 ;  // Start unprotected field terminal key (HP emulation)
   const short rcHpStartXmitOnlyKey = 656 ;  // Start transmit-only field terminal key (HP emulation)
   const short rcHpStopKey     = 657   ;  // Stop terminal key (HP emulation)
   const short rcHpStopFieldKey = 658  ;  // Stop field terminal key (HP emulation)
   const short rcHpTabKey      = 659   ;  // Tab terminal key (HP emulation)
   const short rcHpToggleFormatModeKey = 660 ;  // Toggle format mode terminal key (HP emulation)
   const short rcHpUnderlineVideoKey = 661 ;  // Underline video terminal key (HP emulation)
   const short rcHpUpKey       = 662   ;  // Cursor up terminal key (HP emulation)
   const short rcHpUserKey     = 663   ;  // User terminal key (HP emulation)
   const short rcAnsiCenterKey = 700   ;  // Center terminal key (ANSI emulation)
   const short rcAnsiCtrlF1Key = 701   ;  // Control F1 terminal key (ANSI emulation)
   const short rcAnsiCtrlF2Key = 702   ;  // Control F2 terminal key (ANSI emulation)
   const short rcAnsiCtrlF3Key = 703   ;  // Control F3 terminal key (ANSI emulation)
   const short rcAnsiCtrlF4Key = 704   ;  // Control F4 terminal key (ANSI emulation)
   const short rcAnsiCtrlF5Key = 705   ;  // Control F5 terminal key (ANSI emulation)
   const short rcAnsiCtrlF6Key = 706   ;  // Control F6 terminal key (ANSI emulation)
   const short rcAnsiCtrlF7Key = 707   ;  // Control F7 terminal key (ANSI emulation)
   const short rcAnsiCtrlF8Key = 708   ;  // Control F8 terminal key (ANSI emulation)
   const short rcAnsiCtrlF9Key = 709   ;  // Control F9 terminal key (ANSI emulation)
   const short rcAnsiCtrlF10Key = 710  ;  // Control F10 terminal key (ANSI emulation)
   const short rcAnsiCtrlF11Key = 711  ;  // Control F11 terminal key (ANSI emulation)
   const short rcAnsiCtrlF12Key = 712  ;  // Control F12 terminal key (ANSI emulation)
   const short rcAnsiCtrlShiftF1Key = 713 ;  // Control shift F1 terminal key (ANSI emulation)
   const short rcAnsiCtrlShiftF2Key = 714 ;  // Control shift F2 terminal key (ANSI emulation)
   const short rcAnsiCtrlShiftF3Key = 715 ;  // Control shift F3 terminal key (ANSI emulation)
   const short rcAnsiCtrlShiftF4Key = 716 ;  // Control shift F4 terminal key (ANSI emulation)
   const short rcAnsiCtrlShiftF5Key = 717 ;  // Control shift F5 terminal key (ANSI emulation)
   const short rcAnsiCtrlShiftF6Key = 718 ;  // Control shift F6 terminal key (ANSI emulation)
   const short rcAnsiCtrlShiftF7Key = 719 ;  // Control shift F7 terminal key (ANSI emulation)
   const short rcAnsiCtrlShiftF8Key = 720 ;  // Control shift F8 terminal key (ANSI emulation)
   const short rcAnsiCtrlShiftF9Key = 721 ;  // Control shift F9 terminal key (ANSI emulation)
   const short rcAnsiCtrlShiftF10Key = 722 ;  // Control shift F10 terminal key (ANSI emulation)
   const short rcAnsiCtrlShiftF11Key = 723 ;  // Control shift F11 terminal key (ANSI emulation)
   const short rcAnsiCtrlShiftF12Key = 724 ;  // Control shift F12 terminal key (ANSI emulation)
   const short rcAnsiDeleteKey = 725   ;  // Delete terminal key (ANSI emulation)
   const short rcAnsiEndKey    = 726   ;  // End terminal key (ANSI emulation)
   const short rcAnsiF1Key     = 727   ;  // F1 terminal key (ANSI emulation)
   const short rcAnsiF2Key     = 728   ;  // F2 terminal key (ANSI emulation)
   const short rcAnsiF3Key     = 729   ;  // F3 terminal key (ANSI emulation)
   const short rcAnsiF4Key     = 730   ;  // F4 terminal key (ANSI emulation)
   const short rcAnsiF5Key     = 731   ;  // F5 terminal key (ANSI emulation)
   const short rcAnsiF6Key     = 732   ;  // F6 terminal key (ANSI emulation)
   const short rcAnsiF7Key     = 733   ;  // F7 terminal key (ANSI emulation)
   const short rcAnsiF8Key     = 734   ;  // F8 terminal key (ANSI emulation)
   const short rcAnsiF9Key     = 735   ;  // F9 terminal key (ANSI emulation)
   const short rcAnsiF10Key    = 736   ;  // F10 terminal key (ANSI emulation)
   const short rcAnsiF11Key    = 737   ;  // F11 terminal key (ANSI emulation)
   const short rcAnsiF12Key    = 738   ;  // F12 terminal key (ANSI emulation)
   const short rcAnsiHomeKey   = 739   ;  // Home terminal key (ANSI emulation)
   const short rcAnsiInsertKey = 740   ;  // Insert terminal key (ANSI emulation)
   const short rcAnsiPageDownKey = 741 ;  // Page down terminal key (ANSI emulation)
   const short rcAnsiPageUpKey = 742   ;  // Page up terminal key (ANSI emulation)
   const short rcAnsiShiftF1Key = 743  ;  // Shift F1 terminal key (ANSI emulation)
   const short rcAnsiShiftF2Key = 744  ;  // Shift F2 terminal key (ANSI emulation)
   const short rcAnsiShiftF3Key = 745  ;  // Shift F3 terminal key (ANSI emulation)
   const short rcAnsiShiftF4Key = 746  ;  // Shift F4 terminal key (ANSI emulation)
   const short rcAnsiShiftF5Key = 747  ;  // Shift F5 terminal key (ANSI emulation)
   const short rcAnsiShiftF6Key = 748  ;  // Shift F6 terminal key (ANSI emulation)
   const short rcAnsiShiftF7Key = 749  ;  // Shift F7 terminal key (ANSI emulation)
   const short rcAnsiShiftF8Key = 750  ;  // Shift F8 terminal key (ANSI emulation)
   const short rcAnsiShiftF9Key = 751  ;  // Shift F9 terminal key (ANSI emulation)
   const short rcAnsiShiftF10Key = 752 ;  // Shift F10 terminal key (ANSI emulation)
   const short rcAnsiShiftF11Key = 753 ;  // Shift F11 terminal key (ANSI emulation)
   const short rcAnsiShiftF12Key = 754 ;  // Shift F12 terminal key (ANSI emulation)
   const short rcVtComposeKey  = 800   ;  // Compose terminal key (VT emulation)
   const short rcVtF1Key       = 801   ;  // F1 terminal key (VT emulation)
   const short rcVtF2Key       = 802   ;  // F2 terminal key (VT emulation)
   const short rcVtF3Key       = 803   ;  // F3 terminal key (VT emulation)
   const short rcVtF4Key       = 804   ;  // F4 terminal key (VT emulation)
   const short rcVtF5Key       = 805   ;  // F5 terminal key (VT emulation)
   const short rcVtHoldScreenClearKey = 806 ;  // Hold screen clear terminal key (VT emulation)
   const short rcVtHoldScreenSetKey = 807 ;  // Hold screen set terminal key (VT emulation)
   const short rcVtPrintScreenKey = 808 ;  // Print screen terminal key (VT emulation)
   const short rcVtSendNullKey = 809   ;  // Send NULL terminal key (VT emulation)
   const short rcVtUdk6Key     = 810   ;  // UDK 6 terminal key (VT emulation)
   const short rcVtUdk7Key     = 811   ;  // UDK 7 terminal key (VT emulation)
   const short rcVtUdk8Key     = 812   ;  // UDK 8 terminal key (VT emulation)
   const short rcVtUdk9Key     = 813   ;  // UDK 9 terminal key (VT emulation)
   const short rcVtUdk10Key    = 814   ;  // UDK 10 terminal key (VT emulation)
   const short rcVtUdk11Key    = 815   ;  // UDK 11 terminal key (VT emulation)
   const short rcVtUdk12Key    = 816   ;  // UDK 12 terminal key (VT emulation)
   const short rcVtUdk13Key    = 817   ;  // UDK 13 terminal key (VT emulation)
   const short rcVtUdk14Key    = 818   ;  // UDK 14 terminal key (VT emulation)
   const short rcVtUdk15Key    = 819   ;  // UDK 15 terminal key (VT emulation)
   const short rcVtUdk16Key    = 820   ;  // UDK 16 terminal key (VT emulation)
   const short rcVtUdk17Key    = 821   ;  // UDK 17 terminal key (VT emulation)
   const short rcVtUdk18Key    = 822   ;  // UDK 18 terminal key (VT emulation)
   const short rcVtUdk19Key    = 823   ;  // UDK 19 terminal key (VT emulation)
   const short rcVtUdk20Key    = 824   ;  // UDK 20 terminal key (VT emulation)
   const short rcVtShiftDownKey = 825  ;  // Shift cursor down terminal key (VT emulation)
   const short rcVtShiftLeftKey = 826  ;  // Shift cursor left terminal key (VT emulation)
   const short rcVtShiftRightKey = 827 ;  // Shift cursor right terminal key (VT emulation)
   const short rcVtShiftUpKey  = 828   ;  // Shift cursor up terminal key (VT emulation)
   const short rcTekZoomKey    = 829   ;  // TEK zoom terminal key (Tek emulation)
   const short rcVt0Key        = 830   ;  // Keypad 0 terminal key (VT emulation)
   const short rcVt1Key        = 831   ;  // Keypad 1 terminal key (VT emulation)
   const short rcVt2Key        = 832   ;  // Keypad 2 terminal key (VT emulation)
   const short rcVt3Key        = 833   ;  // Keypad 3 terminal key (VT emulation)
   const short rcVt4Key        = 834   ;  // Keypad 4 terminal key (VT emulation)
   const short rcVt5Key        = 835   ;  // Keypad 5 terminal key (VT emulation)
   const short rcVt6Key        = 836   ;  // Keypad 6 terminal key (VT emulation)
   const short rcVt7Key        = 837   ;  // Keypad 7 terminal key (VT emulation)
   const short rcVt8Key        = 838   ;  // Keypad 8 terminal key (VT emulation)
   const short rcVt9Key        = 839   ;  // Keypad 9 terminal key (VT emulation)
   const short rcVtBackArrowKey = 840  ;  // Back arrow (delete) terminal key (VT emulation)
   const short rcVtBreakKey    = 841   ;  // Break terminal key (VT emulation)
   const short rcVtCommaKey    = 842   ;  // Keypad comma terminal key (VT emulation)
   const short rcVtDecimalKey  = 843   ;  // Keypad decimal terminal key (VT emulation)
   const short rcVtDisconnectKey = 844 ;  // Disconnect terminal key (VT emulation)
   const short rcVtDownKey     = 845   ;  // Cursor down terminal key (VT emulation)
   const short rcVtEnterKey    = 846   ;  // Enter terminal key (VT emulation)
   const short rcVtEscKey      = 847   ;  // Escape terminal key (VT emulation)
   const short rcVtF6Key       = 848   ;  // F6 terminal key (VT emulation)
   const short rcVtF7Key       = 849   ;  // F7 terminal key (VT emulation)
   const short rcVtF8Key       = 850   ;  // F8 terminal key (VT emulation)
   const short rcVtF9Key       = 851   ;  // F9 terminal key (VT emulation)
   const short rcVtF10Key      = 852   ;  // F10 terminal key (VT emulation)
   const short rcVtF11Key      = 853   ;  // F11 terminal key (VT emulation)
   const short rcVtF12Key      = 854   ;  // F12 terminal key (VT emulation)
   const short rcVtF13Key      = 855   ;  // F13 terminal key (VT emulation)
   const short rcVtF14Key      = 856   ;  // F14 terminal key (VT emulation)
   const short rcVtF15Key      = 857   ;  // F15 terminal key (VT emulation)
   const short rcVtF16Key      = 858   ;  // F16 terminal key (VT emulation)
   const short rcVtF17Key      = 859   ;  // F17 terminal key (VT emulation)
   const short rcVtF18Key      = 860   ;  // F18 terminal key (VT emulation)
   const short rcVtF19Key      = 861   ;  // F19 terminal key (VT emulation)
   const short rcVtF20Key      = 862   ;  // F20 terminal key (VT emulation)
   const short rcVtFindKey     = 863   ;  // Find terminal key (VT emulation)
   const short rcVtHoldScreenKey = 864 ;  // Hold screen terminal key (VT emulation)
   const short rcVtInsertHereKey = 865 ;  // Insert here terminal key (VT emulation)
   const short rcVtLeftKey     = 866   ;  // Cursor left terminal key (VT emulation)
   const short rcVtMinusKey    = 867   ;  // Keypad minus terminal key (VT emulation)
   const short rcVtNextScreenKey = 868 ;  // Next screen terminal key (VT emulation)
   const short rcVtNotBackArrowKey = 869 ;  // Not back arrow (backspace) terminal key (VT emulation)
   const short rcVtPF1Key      = 870   ;  // PF1 terminal key (VT emulation)
   const short rcVtPF2Key      = 871   ;  // PF2 terminal key (VT emulation)
   const short rcVtPF3Key      = 872   ;  // PF3 terminal key (VT emulation)
   const short rcVtPF4Key      = 873   ;  // PF4 terminal key (VT emulation)
   const short rcVtPrevScreenKey = 874 ;  // Prev screen terminal key (VT emulation)
   const short rcVtRemoveKey   = 875   ;  // Remove terminal key (VT emulation)
   const short rcVtReturnKey   = 876   ;  // Return terminal key (VT emulation)
   const short rcVtRightKey    = 877   ;  // Cursor right terminal key (VT emulation)
   const short rcVtScrollDownKey = 878 ;  // Scroll down terminal key (VT emulation)
   const short rcVtScrollUpKey = 879   ;  // Scroll up terminal key (VT emulation)
   const short rcVtSelectKey   = 880   ;  // Select terminal key (VT emulation)
   const short rcVtSendAnswerbackKey = 881 ;  // Send answerback terminal key (VT emulation)
   const short rcVtTabKey      = 882   ;  // Tab terminal key (VT emulation)
   const short rcVtUpKey       = 883   ;  // Cursor up terminal key (VT emulation)
   const short rcAddsF1Key     = 900   ;  // ADDS F1 terminal key
   const short rcAddsF2Key     = 901   ;  // ADDS F2 terminal key
   const short rcAddsF3Key     = 902   ;  // ADDS F3 terminal key
   const short rcAddsF4Key     = 903   ;  // ADDS F4 terminal key
   const short rcAddsF5Key     = 904   ;  // ADDS F5 terminal key
   const short rcAddsF6Key     = 905   ;  // ADDS F6 terminal key
   const short rcAddsF7Key     = 906   ;  // ADDS F7 terminal key
   const short rcAddsF8Key     = 907   ;  // ADDS F8 terminal key
   const short rcAddsF9Key     = 908   ;  // ADDS F9 terminal key
   const short rcAddsF10Key    = 909   ;  // ADDS F10 terminal key
   const short rcAddsF11Key    = 910   ;  // ADDS F11 terminal key
   const short rcAddsF12Key    = 911   ;  // ADDS F12 terminal key
   const short rcAddsShiftF1Key = 912  ;  // ADDS Shift F1 terminal Key
   const short rcAddsShiftF2Key = 913  ;  // ADDS Shift F2 terminal Key
   const short rcAddsShiftF3Key = 914  ;  // ADDS Shift F3 terminal Key
   const short rcAddsShiftF4Key = 915  ;  // ADDS Shift F4 terminal Key
   const short rcAddsShiftF5Key = 916  ;  // ADDS Shift F5 terminal Key
   const short rcAddsShiftF6Key = 917  ;  // ADDS Shift F6 terminal Key
   const short rcAddsShiftF7Key = 918  ;  // ADDS Shift F7 terminal Key
   const short rcAddsShiftF8Key = 919  ;  // ADDS Shift F8 terminal Key
   const short rcAddsShiftF9Key = 920  ;  // ADDS Shift F9 terminal Key
   const short rcAddsShiftF10Key = 921 ;  // ADDS Shift F10 terminal Key
   const short rcAddsShiftF11Key = 922 ;  // ADDS Shift F11 terminal Key
   const short rcAddsShiftF12Key = 923 ;  // ADDS Shift F12 terminal Key
   const short rcAddsUpKey     = 924   ;  // ADDS Up terminal Key
   const short rcAddsDownKey   = 925   ;  // ADDS Down terminal Key
   const short rcAddsLeftKey   = 926   ;  // ADDS Left terminal Key
   const short rcAddsShiftLeftKey = 928 ;  // ADDS Shift Left terminal Key
   const short rcAddsRightKey  = 927   ;  // ADDS Right terminal Key
   const short rcAddsShiftRightKey = 929 ;  // ADDS Shift Right terminal Key
   const short rcAddsHomeKey   = 930   ;  // ADDS Home terminal Key
   const short rcAddsShiftHomeKey = 931 ;  // ADDS Shift Home terminal Key
   const short rcAddsInsertKey = 932   ;  // ADDS Insert terminal Key
   const short rcAddsShiftInsertKey = 933 ;  // ADDS Shift Insert terminal Key
   const short rcAddsDeleteKey = 934   ;  // ADDS Delete terminal Key
   const short rcAddsCPDeleteKey = 935 ;  // ADDS CP Delete terminal Key
   const short rcAddsShiftCPDeleteKey = 936 ;  // ADDS Shift CP Delete terminal Key
   const short rcAddsEndKey    = 937   ;  // ADDS End terminal Key
   const short rcAddsShiftEndKey = 938 ;  // ADDS Shift End terminal Key
   const short rcAddsPageDownKey = 939 ;  // ADDS Page Down terminal Key
   const short rcAddsPageUpKey = 940   ;  // ADDS Page Up terminal Key
   const short rcAddsPrintScreenKey = 941 ;  // ADDS Print Screen terminal Key
   const short rcAddsShiftPrintScreenKey = 942 ;  // ADDS Shift Print Screen terminal Key
   const short rcAddsShiftTabKey = 943 ;  // ADDS Shift Tab terminal Key
   const short rcAddsEnterKey  = 944   ;  // ADDS Enter terminal Key
   const short rcWyseF1Key     = 1000  ;  // Wyse F1 terminal Key
   const short rcWyseF2Key     = 1001  ;  // Wyse F2 terminal Key
   const short rcWyseF3Key     = 1002  ;  // Wyse F3 terminal Key
   const short rcWyseF4Key     = 1003  ;  // Wyse F4 terminal Key
   const short rcWyseF5Key     = 1004  ;  // Wyse F5 terminal Key
   const short rcWyseF6Key     = 1005  ;  // Wyse F6 terminal Key
   const short rcWyseF7Key     = 1006  ;  // Wyse F7 terminal Key
   const short rcWyseF8Key     = 1007  ;  // Wyse F8 terminal Key
   const short rcWyseF9Key     = 1008  ;  // Wyse F9 terminal Key
   const short rcWyseF10Key    = 1009  ;  // Wyse F10 terminal Key
   const short rcWyseF11Key    = 1010  ;  // Wyse F11 terminal Key
   const short rcWyseF12Key    = 1011  ;  // Wyse F12 terminal Key
   const short rcWyseF13Key    = 1012  ;  // Wyse F13 terminal Key
   const short rcWyseF14Key    = 1013  ;  // Wyse F14 terminal Key
   const short rcWyseF15Key    = 1014  ;  // Wyse F15 terminal Key
   const short rcWyseF16Key    = 1015  ;  // Wyse F16 terminal Key
   const short rcWyseShiftF1Key = 1016 ;  // Wyse Shift F1 terminal Key
   const short rcWyseShiftF2Key = 1017 ;  // Wyse Shift F2 terminal Key
   const short rcWyseShiftF3Key = 1018 ;  // Wyse Shift F3 terminal Key
   const short rcWyseShiftF4Key = 1019 ;  // Wyse Shift F4 terminal Key
   const short rcWyseShiftF5Key = 1020 ;  // Wyse Shift F5 terminal Key
   const short rcWyseShiftF6Key = 1021 ;  // Wyse Shift F6 terminal Key
   const short rcWyseShiftF7Key = 1022 ;  // Wyse Shift F7 terminal Key
   const short rcWyseShiftF8Key = 1023 ;  // Wyse Shift F8 terminal Key
   const short rcWyseShiftF9Key = 1024 ;  // Wyse Shift F9 terminal Key
   const short rcWyseShiftF10Key = 1025 ;  // Wyse Shift F10 terminal Key
   const short rcWyseShiftF11Key = 1026 ;  // Wyse Shift F11 terminal Key
   const short rcWyseShiftF12Key = 1027 ;  // Wyse Shift F12 terminal Key
   const short rcWyseShiftF13Key = 1028 ;  // Wyse Shift F13 terminal Key
   const short rcWyseShiftF14Key = 1029 ;  // Wyse Shift F14 terminal Key
   const short rcWyseShiftF15Key = 1030 ;  // Wyse Shift F15 terminal Key
   const short rcWyseShiftF16Key = 1031 ;  // Wyse Shift F16 terminal Key
   const short rcWyseUpKey     = 1032  ;  // Wyse Up terminal Key
   const short rcWyseDownKey   = 1033  ;  // Wyse Down terminal Key
   const short rcWyseLeftKey   = 1034  ;  // Wyse Left terminal Key
   const short rcWyseInsertCharKey = 1035 ;  // Wyse Insert Char terminal Key
   const short rcWyseRightKey  = 1036  ;  // Wyse Right terminal Key
   const short rcWyseInsertLineKey = 1037 ;  // Wyse Insert Line terminal Key
   const short rcWyseSendDeleteKey = 1038 ;  // Wyse Send Delete terminal Key
   const short rcWyseDeleteCharKey = 1039 ;  // Wyse Delete Char terminal Key
   const short rcWyseDeleteLineKey = 1040 ;  // Wyse Delete Line terminal Key
   const short rcWyseClearLineKey = 1041 ;  // Wyse Clear Line terminal Key
   const short rcWyseClearPageKey = 1042 ;  // Wyse Clear Page terminal Key
   const short rcWyseHomeKey   = 1043  ;  // Wyse Home terminal Key
   const short rcWyseHomeCursorKey = 1044 ;  // Wyse Home Cursor terminal Key
   const short rcWyseInsertModeKey = 1045 ;  // Wyse Insert Mode terminal Key
   const short rcWyseReplaceModeKey = 1046 ;  // Wyse Replace Mode terminal Key
   const short rcWysePageDownKey = 1048 ;  // Wyse Page Down terminal Key
   const short rcWysePageUpKey = 1047  ;  // Wyse Page Up terminal Key
   const short rcWysePrintScreenKey = 1049 ;  // Wyse Print Screen terminal Key
   const short rcWyseSendKey   = 1050  ;  // Wyse Send terminal Key
   const short rcWyseBackTabKey = 1051 ;  // Wyse Back Tab terminal Key
   const short rcDGF1Key       = 1100  ;  // DG F1 terminal Key
   const short rcDGF2Key       = 1101  ;  // DG F2 terminal Key
   const short rcDGF3Key       = 1102  ;  // DG F3 terminal Key
   const short rcDGF4Key       = 1103  ;  // DG F4 terminal Key
   const short rcDGF5Key       = 1104  ;  // DG F5 terminal Key
   const short rcDGF6Key       = 1105  ;  // DG F6 terminal Key
   const short rcDGF7Key       = 1106  ;  // DG F7 terminal Key
   const short rcDGF8Key       = 1107  ;  // DG F8 terminal Key
   const short rcDGF9Key       = 1108  ;  // DG F9 terminal Key
   const short rcDGF10Key      = 1109  ;  // DG F10 terminal Key
   const short rcDGF11Key      = 1110  ;  // DG F11 terminal Key
   const short rcDGF12Key      = 1111  ;  // DG F12 terminal Key
   const short rcDGF13Key      = 1112  ;  // DG F13 terminal Key
   const short rcDGF14Key      = 1113  ;  // DG F14 terminal Key
   const short rcDGF15Key      = 1114  ;  // DG F15 terminal Key
   const short rcDGF16Key      = 1115  ;  // DG F16 terminal Key
   const short rcDGF17Key      = 1116  ;  // DG F17 terminal Key
   const short rcDGF18Key      = 1117  ;  // DG F18 terminal Key
   const short rcDGF19Key      = 1118  ;  // DG F19 terminal Key
   const short rcDGF20Key      = 1119  ;  // DG F20 terminal Key
   const short rcDGShiftF1Key  = 1120  ;  // DG Shift F1 terminal Key
   const short rcDGShiftF2Key  = 1121  ;  // DG Shift F2 terminal Key
   const short rcDGShiftF3Key  = 1122  ;  // DG Shift F3 terminal Key
   const short rcDGShiftF4Key  = 1123  ;  // DG Shift F4 terminal Key
   const short rcDGShiftF5Key  = 1124  ;  // DG Shift F5 terminal Key
   const short rcDGShiftF6Key  = 1125  ;  // DG Shift F6 terminal Key
   const short rcDGShiftF7Key  = 1126  ;  // DG Shift F7 terminal Key
   const short rcDGShiftF8Key  = 1127  ;  // DG Shift F8 terminal Key
   const short rcDGShiftF9Key  = 1128  ;  // DG Shift F9 terminal Key
   const short rcDGShiftF10Key = 1129  ;  // DG Shift F10 terminal Key
   const short rcDGShiftF11Key = 1130  ;  // DG Shift F11 terminal Key
   const short rcDGShiftF12Key = 1131  ;  // DG Shift F12 terminal Key
   const short rcDGShiftF13Key = 1132  ;  // DG Shift F13 terminal Key
   const short rcDGShiftF14Key = 1133  ;  // DG Shift F14 terminal Key
   const short rcDGShiftF15Key = 1134  ;  // DG Shift F15 terminal Key
   const short rcDGShiftF16Key = 1135  ;  // DG Shift F16 terminal Key
   const short rcDGShiftF17Key = 1136  ;  // DG Shift F17 terminal Key
   const short rcDGShiftF18Key = 1137  ;  // DG Shift F18 terminal Key
   const short rcDGShiftF19Key = 1138  ;  // DG Shift F19 terminal Key
   const short rcDGShiftF20Key = 1139  ;  // DG Shift F20 terminal Key
   const short rcDGCtrlF1Key   = 1140  ;  // DG Ctrl F1 terminal Key
   const short rcDGCtrlF2Key   = 1141  ;  // DG Ctrl F2 terminal Key
   const short rcDGCtrlF3Key   = 1142  ;  // DG Ctrl F3 terminal Key
   const short rcDGCtrlF4Key   = 1143  ;  // DG Ctrl F4 terminal Key
   const short rcDGCtrlF5Key   = 1144  ;  // DG Ctrl F5 terminal Key
   const short rcDGCtrlF6Key   = 1145  ;  // DG Ctrl F6 terminal Key
   const short rcDGCtrlF7Key   = 1146  ;  // DG Ctrl F7 terminal Key
   const short rcDGCtrlF8Key   = 1147  ;  // DG Ctrl F8 terminal Key
   const short rcDGCtrlF9Key   = 1148  ;  // DG Ctrl F9 terminal Key
   const short rcDGCtrlF10Key  = 1149  ;  // DG Ctrl F10 terminal Key
   const short rcDGCtrlF11Key  = 1150  ;  // DG Ctrl F11 terminal Key
   const short rcDGCtrlF12Key  = 1151  ;  // DG Ctrl F12 terminal Key
   const short rcDGCtrlF13Key  = 1152  ;  // DG Ctrl F13 terminal Key
   const short rcDGCtrlF14Key  = 1153  ;  // DG Ctrl F14 terminal Key
   const short rcDGCtrlF15Key  = 1154  ;  // DG Ctrl F15 terminal Key
   const short rcDGCtrlF16Key  = 1155  ;  // DG Ctrl F16 terminal Key
   const short rcDGCtrlF17Key  = 1156  ;  // DG Ctrl F17 terminal Key
   const short rcDGCtrlF18Key  = 1157  ;  // DG Ctrl F18 terminal Key
   const short rcDGCtrlF19Key  = 1158  ;  // DG Ctrl F19 terminal Key
   const short rcDGCtrlF20Key  = 1179  ;  // DG Ctrl F20 terminal Key
   const short rcDGCtrlShiftF1Key = 1140 ;  // DG Ctrl Shift F1 terminal Key
   const short rcDGCtrlShiftF2Key = 1161 ;  // DG Ctrl Shift F2 terminal Key
   const short rcDGCtrlShiftF3Key = 1162 ;  // DG Ctrl Shift F3 terminal Key
   const short rcDGCtrlShiftF4Key = 1163 ;  // DG Ctrl Shift F4 terminal Key
   const short rcDGCtrlShiftF5Key = 1164 ;  // DG Ctrl Shift F5 terminal Key
   const short rcDGCtrlShiftF6Key = 1165 ;  // DG Ctrl Shift F6 terminal Key
   const short rcDGCtrlShiftF7Key = 1166 ;  // DG Ctrl Shift F7 terminal Key
   const short rcDGCtrlShiftF8Key = 1167 ;  // DG Ctrl Shift F8 terminal Key
   const short rcDGCtrlShiftF9Key = 1168 ;  // DG Ctrl Shift F9 terminal Key
   const short rcDGCtrlShiftF10Key = 1169 ;  // DG Ctrl Shift F10 terminal Key
   const short rcDGCtrlShiftF11Key = 1170 ;  // DG Ctrl Shift F11 terminal Key
   const short rcDGCtrlShiftF12Key = 1171 ;  // DG Ctrl Shift F12 terminal Key
   const short rcDGCtrlShiftF13Key = 1172 ;  // DG Ctrl Shift F13 terminal Key
   const short rcDGCtrlShiftF14Key = 1173 ;  // DG Ctrl Shift F14 terminal Key
   const short rcDGCtrlShiftF15Key = 1174 ;  // DG Ctrl Shift F15 terminal Key
   const short rcDGCtrlShiftF16Key = 1175 ;  // DG Ctrl Shift F16 terminal Key
   const short rcDGCtrlShiftF17Key = 1176 ;  // DG Ctrl Shift F17 terminal Key
   const short rcDGCtrlShiftF18Key = 1177 ;  // DG Ctrl Shift F18 terminal Key
   const short rcDGCtrlShiftF19Key = 1178 ;  // DG Ctrl Shift F19 terminal Key
   const short rcDGCtrlShiftF20Key = 1179 ;  // DG Ctrl Shift F20 terminal Key
   const short rcDGEnterKey    = 1180  ;  // DG Enter terminal Key
   const short rcDGHomeKey     = 1181  ;  // DG Home terminal Key
   const short rcDGShiftHomeKey = 1182 ;  // DG Shift Home terminal Key
   const short rcDGUpKey       = 1183  ;  // DG Up terminal Key
   const short rcDGShiftUpKey  = 1184  ;  // DG Shift Up terminal Key
   const short rcDGDownKey     = 1185  ;  // DG Down terminal Key
   const short rcDGShiftDownKey = 1186 ;  // DG Shift Down terminal Key
   const short rcDGLeftKey     = 1187  ;  // DG Left terminal Key
   const short rcDGShiftLeftKey = 1188 ;  // DG Shift Left terminal Key
   const short rcDGRightKey    = 1189  ;  // DG Right terminal Key
   const short rcDGShiftRightKey = 1190 ;  // DG Shift Right terminal Key
   const short rcDGInsertKey   = 1191  ;  // DG Insert terminal Key
   const short rcDGShiftInsertKey = 1192 ;  // DG Shift Insert terminal Key
   const short rcDGDeleteKey   = 1193  ;  // DG Delete terminal Key
   const short rcDGCPDeleteKey = 1194  ;  // DG CP Delete terminal Key
   const short rcDGShiftTabKey = 1195  ;  // DG Shift Tab terminal Key
   const short rcDGC1Key       = 1196  ;  // DG C1 terminal Key
   const short rcDGC2Key       = 1197  ;  // DG C2 terminal Key
   const short rcDGC3Key       = 1198  ;  // DG C3 terminal Key
   const short rcDGC4Key       = 1199  ;  // DG C4 terminal Key
   const short rcDGErasePageKey = 1200 ;  // DG Erase Page terminal Key
   const short rcDGEraseEOLKey = 1201  ;  // DG Erase EOL terminal Key
   const short rcT27F1Key      = 1250  ;  // T27 F1 terminal Key
   const short rcT27F2Key      = 1251  ;  // T27 F2 terminal Key
   const short rcT27F3Key      = 1252  ;  // T27 F3 terminal Key
   const short rcT27F4Key      = 1253  ;  // T27 F4 terminal Key
   const short rcT27F5Key      = 1254  ;  // T27 F5 terminal Key
   const short rcT27F6Key      = 1255  ;  // T27 F6 terminal Key
   const short rcT27F7Key      = 1256  ;  // T27 F7 terminal Key
   const short rcT27F8Key      = 1257  ;  // T27 F8 terminal Key
   const short rcT27F9Key      = 1258  ;  // T27 F9 terminal Key
   const short rcT27F10Key     = 1259  ;  // T27 F10 terminal Key
   const short rcT27ShiftF1Key = 1260  ;  // T27 Shift F1 terminal Key
   const short rcT27ShiftF2Key = 1261  ;  // T27 Shift F2 terminal Key
   const short rcT27ShiftF3Key = 1262  ;  // T27 Shift F3 terminal Key
   const short rcT27ShiftF4Key = 1263  ;  // T27 Shift F4 terminal Key
   const short rcT27ShiftF5Key = 1264  ;  // T27 Shift F5 terminal Key
   const short rcT27ShiftF6Key = 1265  ;  // T27 Shift F6 terminal Key
   const short rcT27ShiftF7Key = 1266  ;  // T27 Shift F7 terminal Key
   const short rcT27ShiftF8Key = 1267  ;  // T27 Shift F8 terminal Key
   const short rcT27ShiftF9Key = 1268  ;  // T27 Shift F9 terminal Key
   const short rcT27ShiftF10Key = 1269 ;  // T27 Shift F10 terminal Key
   const short rcT27HomeKey    = 1270  ;  // T27 terminal Key
   const short rcT27ClearKey   = 1271  ;  // T27 terminal Key
   const short rcT27HelpKey    = 1272  ;  // T27 terminal Key
   const short rcT27PrintKey   = 1273  ;  // T27 terminal Key
   const short rcT27ShiftPrintKey = 1274 ;  // T27 terminal Key
   const short rcT27DeleteLineKey = 1275 ;  // T27 terminal Key
   const short rcT27DeleteCharKey = 1276 ;  // T27 terminal Key
   const short rcT27ClearEndOfLineKey = 1277 ;  // T27 terminal Key
   const short rcT27ClearEndOfPageKey = 1278 ;  // T27 terminal Key
   const short rcT27InsertCharKey = 1279 ;  // T27 terminal Key
   const short rcT27InsertLineKey = 1280 ;  // T27 terminal Key
   const short rcT27EnterKey   = 1281  ;  // T27 terminal Key
   const short rcT27CursorRightKey = 1282 ;  // T27 terminal Key
   const short rcT27CursorLeftKey = 1283 ;  // T27 terminal Key
   const short rcT27CursorDownKey = 1284 ;  // T27 terminal Key
   const short rcT27CursorUpKey = 1285 ;  // T27 terminal Key
   const short rcT27TransmitKey = 1286 ;  // T27 terminal Key
   const short rcT27LocalKey   = 1288  ;  // T27 terminal Key
   const short rcT27ReceiveKey = 1289  ;  // T27 terminal Key
   const short rcT27BackPageKey = 1290 ;  // T27 terminal Key
   const short rcT27NextPageKey = 1291 ;  // T27 terminal Key
   const short rcT27ETXKey     = 1292  ;  // T27 terminal Key
   const short rcT27GSDelimKey = 1293  ;  // T27 terminal Key
   const short rcT27DoubleZeroKey = 1294 ;  // T27 terminal Key
   const short rcT27BackTabKey = 1295  ;  // T27 terminal Key
   const short rcT27ControlKey = 1296  ;  // T27 terminal Key
   const short rcT27TabKey     = 1297  ;  // T27 terminal Key
   const short rcT27SpecifyKey = 1287  ;  // T27 terminal Key
   const short rcELFDeleteCharKey = 1300 ;  // ELF Delete Character Key
   const short rcELFInsertSpaceKey = 1301 ;  // ELF Insert Space Key
   const short rcELFHomeKey    = 1302  ;  // ELF Home Key
   const short rcELFEndKey     = 1303  ;  // ELF End Key
   const short rcELFShiftHomeKey = 1304 ;  // ELF Shift Home Key
   const short rcELFShiftEndKey = 1305 ;  // ELF Shift End Key
   const short rcELFBackspaceKey = 1306 ;  // ELF Backspace Key
   const short rcELFTransmitKey = 1307 ;  // ELF Transmit Key
   const short rcT27LineTransmitKey = 1298 ;  // T27 terminal Key

} // namespace ReflectionDispatch
