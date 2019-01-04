//===========================================================================
//  
//  File: ATMAPI32.H
// 
//  Desc: Windows ATMAPI32 Communications Library DLL core definitions.
//  
//  This document contains confidential/proprietary information. Not for
//  distribution outside the company.
//
//  Copyright (c) 1996 by Attachmate Corporation.
//  All rights reserved worldwide.
// 
// 
//  $LOG$
//
// ===========================================================================

//******************************************************************************
//                              Module Header
//******************************************************************************
//
// File:       ATMAPI32.H
//
//******************************************************************************

#ifdef __cplusplus
extern "C"{
#endif

// Flags for ATMGetSessionStatus
#define ATM_ISCONFIGURED    1
#define ATM_ISOPENED        2
#define ATM_ISPOWERED       3
#define ATM_ISEMULATED      14
#define ATM_ISCONNECTED     15
#define ATM_ISFILETRANSFER  16


// Flags for ATMGetSessions()
// Flags to create a list of sessions of a type
#define ATM_GETCONFIGURED       1
#define ATM_GETOPENED           2
#define ATM_GETPOWERED          3  
#define ATM_GETEMULATED         11
#define ATM_GETEMULATEDPOWERED  12   // Emulated and Powered


//Size of Session string that gets returned in ATMGetSessions() sans Array
#define ATM_SESSIONLEN  sizeof("A SESSION1,")


// Flags to return number of sessions of a type                                                           
#define ATM_GETCONFIGUREDCOUNT      4
#define ATM_GETOPENEDCOUNT          5
#define ATM_GETPOWEREDCOUNT         6  
#define ATM_GETEMULATEDCOUNT        14
#define ATM_GETEMULATEDPOWEREDCOUNT 15   //Emulated and Powered


// Option flags for ATMRowColumn
#define ATM_GETROW          0
#define ATM_GETCOLUMN       1  


// Flags for field functions.
#define ATM_THISFIELD                    0
#define ATM_NEXTFIELD                    1
#define ATM_PREVIOUSFIELD                2
#define ATM_NEXTPROTECTEDFIELD           3
#define ATM_NEXTUNPROTECTEDFIELD         4
#define ATM_PREVIOUSPROTECTEDFIELD       5
#define ATM_PREVIOUSUNPROTECTEDFIELD     6


//Flags for ATMStartHostNotify
#define ATM_NOTIFYCURSOR          1
#define ATM_NOTIFYOIA             2
#define ATM_NOTIFYPS              4
#define ATM_NOTIFYBEEPS           8
#define ATM_NOTIFYBASECOLOR      16
#define ATM_NOTIFYMODEL          32
#define ATM_NOTIFYPOWER          64
#define ATM_NOTIFYALL           127


//Flags for ATMStartKeystrokeIntercept
#define ATM_AIDKEYS 1
#define ATM_ALLKEYS 2


//Connectivity types for use with the ATMRegisterClient function
#define ATM_EXTRA 1
#define ATM_RALLY 2
#define ATM_KEA   3
#define ATM_IRMA  4
#define ATM_ICON  5


#define ATM_3270  1  // duplicate ATM_EXTRA
#define ATM_5250  2  // duplicate ATM_RALLY
#define IRM_3270  4  // duplicate ATM_IRMA
#define INFO_CON  5  // duplicate ATM_ICON


//Constants for ATMFieldInfo function.
#define ATM_ISFIELDPROTECTED                1
#define ATM_ISFIELDNUMERIC                  2
#define ATM_ISFIELDSELECTORPENDETECTABLE    3
#define ATM_ISFIELDBOLD                     4
#define ATM_ISFIELDHIDDEN                   5
#define ATM_ISFIELDMODIFIED                 6


// ATMSeachSession option flags
#define ATM_SEARCHALL     1
#define ATM_SEARCHFROM    2
#define ATM_SEARCHAT      3
#define ATM_SEARCHBACK    4


// Following is the definitions for HLL WIN Parameters
#define ATM_ATTRIB                               1
#define ATM_AUTORESET                            2
#define ATM_CONNECTTYPE                          3
#define ATM_EAB                                  4
#define ATM_PAUSE                                5
#define ATM_SEARCHORG                            6
#define ATM_SEARCHDIRECTION                      7
#define ATM_TIMEOUT                              8
#define ATM_TRACE                                9
#define ATM_WAIT                                 10
#define ATM_XLATE                                11
#define ATM_ESCAPE                               12


//ATMFileTransferDlg flags
#define ATM_FTRECEIVEDLG                       100
#define ATM_FTSENDDLG                          200
#define ATM_FTTSO                                1
#define ATM_FTCMS                                2
#define ATM_FTCICS                               4


// Parameters for ATMGetConnectionStatus 
#define ATM_XSTATUS         1
#define ATM_CONNECTION      2
#define ATM_ERROR           3


// Return codes for ATMGetConnectionStatus 
#define ATM_INVALIDNUM      1
#define ATM_NUMONLY         2
#define ATM_PROTFIELD       3
#define ATM_PASTEOF         4
#define ATM_BUSY            5
#define ATM_INVALIDFUNC     6
#define ATM_UNAUTHORIZED    7
#define ATM_SYSTEM          8
#define ATM_INVALIDCHAR     9


// Flags for Online and Screen Ownership : Group 1
#define ATM_APPOWNED        1
#define ATM_SSCP            2
#define ATM_UNOWNED         3
#define ATM_NONE            4
#define ATM_UNKNOWN         5


// Flags for Input Inhibited : Group 8 - byte 1
#define ATM_PROGCHECK       1
#define ATM_COMMCHECK       2
#define ATM_MACHINECHECK    3


// EAL Function Prototypes

int  WINAPI ATMAllowUpdates(HWND);
int  WINAPI ATMBlockUpdates(HWND);
int  WINAPI ATMConnectSession (HWND,LPSTR);
int  WINAPI ATMDisconnectSession (HWND);
int  WINAPI ATMGetATMAPIVersion(LPSTR,WORD);
int  WINAPI ATMGetConnectionStatus(HWND hWnd, WORD wMask);
int  WINAPI ATMGetCursorLocation (HWND);
int  WINAPI ATMGetEmulatorPath(HWND,LPSTR,WORD);
int  WINAPI ATMGetEmulatorVersion (HWND,LPSTR,WORD);
int  WINAPI ATMGetError(HWND,LPSTR,WORD);
int  WINAPI ATMGetFieldInfo(HWND hWnd,int nRow,int nColumn,WORD wMask);
int  WINAPI ATMGetFieldLength(HWND,int,int,WORD);
int  WINAPI ATMGetFieldPosition(HWND,int, int,WORD);
int  WINAPI ATMGetParameter(HWND,WORD);
int  WINAPI ATMGetSessionHandle(HWND,LPSTR);
int  WINAPI ATMGetSessions(HWND,LPSTR,WORD,WORD);
int  WINAPI ATMGetSessionSize(HWND);
int  WINAPI ATMGetSessionStatus (HWND,LPSTR,WORD);
int  WINAPI ATMGetString (HWND,int,int,LPSTR,WORD);
int  WINAPI ATMGetStringFromField(HWND,int,int,LPSTR,WORD);
int  WINAPI ATMListSessions(HWND,LPSTR,WORD,LPSTR,WORD);   
int  WINAPI ATMLockKeyboard(HWND);
int  WINAPI ATMPause(HWND,WORD);
int  WINAPI ATMReceiveFile(HWND,LPSTR,WORD);
BOOL WINAPI ATMRegisterClient (HWND, WORD);  
int  WINAPI ATMResetSystem(HWND);
int  WINAPI ATMRowColumn(HWND,WORD,WORD);
int  WINAPI ATMRunEmulatorMacro(HWND, LPSTR,LPSTR);
int  WINAPI ATMSearchField(HWND,int,int,LPSTR);
int  WINAPI ATMSearchSession (HWND,int,int,LPSTR,WORD);
int  WINAPI ATMSendAndWait(HWND hWnd,int nRow, int nColumn, LPSTR lpszString, LPSTR lpszWaitString, int nTime);
int  WINAPI ATMSendFile(HWND,LPSTR,WORD);
int  WINAPI ATMSendKey (HWND,LPSTR);
int  WINAPI ATMSendString(HWND,int,int,LPSTR);
int  WINAPI ATMSendStringToField(HWND,int,int,LPSTR);
int  WINAPI ATMSessionOff(HWND);
int  WINAPI ATMSessionOn(HWND);
int  WINAPI ATMSetCursorLocation(HWND,int,int);
int  WINAPI ATMSetParameter(HWND,WORD,WORD,LPSTR);
BOOL WINAPI ATMShowLastError(HWND);
int  WINAPI ATMStartSession(HWND,LPSTR,LPSTR);
int  WINAPI ATMStopSession(HWND);
int  WINAPI ATMUnlockKeyboard(HWND);
BOOL WINAPI ATMUnregisterClient (HWND);
int  WINAPI ATMWait (HWND);
int  WINAPI ATMWaitForCursor(HWND hWnd,int nRow, int nColumn,int nTime);
int  WINAPI ATMWaitForCursorMove(HWND hWnd, int wTimeOut);
int  WINAPI ATMWaitForHostConnect(HWND hWnd, WORD wTimeOut);
int  WINAPI ATMWaitForHostDisconnect(HWND hWnd, WORD wTimeOut);
int  WINAPI ATMWaitForKey(HWND hWnd, LPSTR lpszKeystroke, WORD nTime);
int  WINAPI ATMWaitForString(HWND,int,int,LPSTR,int);
int  WINAPI ATMWaitHostQuiet(HWND hWnd, WORD wSettleTime, WORD wTimeOut);



// These functions are available ONLY on the KEA product platform
int WINAPI ATMAddWait(HWND hWnd, int nTable, int nEventID);
int WINAPI ATMAddWaitForCursor(HWND hWnd, int nTable, int nEventID, int nRow, int nColumn);
int WINAPI ATMAddWaitForCursorMove(HWND hWnd, int nTable, int nEventID);
int WINAPI ATMAddWaitForString(HWND hWnd, int nTable, int nEventID,int nRow, int nColumn, LPSTR lpString);
int WINAPI ATMAddWaitForStringNotAt(HWND hWnd, int nTable, int nEventID,int nRow, int nColumn, LPSTR lpString);
int WINAPI ATMAddWaitHostQuiet(HWND hWnd, int nTable, int nEventID,int nIdleMilliseconds);
int WINAPI ATMAddWaitForHostConnect(HWND hWnd, int nTable, int nEventID);
int WINAPI ATMAddWaitForHostDisconnect(HWND hWnd, int nTable, int nEventID);
int WINAPI ATMAddWaitForKey(HWND hWnd, int nTable, int nEventID,LPSTR lpszKeystroke);
int WINAPI ATMClearEventTable(HWND hWnd, int nTable);
int WINAPI ATMDeleteEvent(HWND hWnd, int nTable, int nEventID);
int WINAPI ATMExecute (HWND hWnd, LPSTR lpszMacroCode, WORD wTimeOut);
int WINAPI ATMHoldHost(HWND hWnd);
int WINAPI ATMResumeHost(HWND hWnd);
int WINAPI ATMWaitForEvent(HWND hWnd, int nTable, int nTimeout);

// These functions are available ONLY on the EXTRA product platform
int  WINAPI ATMCloseConfiguration(HWND);
int  WINAPI ATMGetConfiguration(HWND,LPSTR,WORD);
int  WINAPI ATMGetEXTRAPath(HWND,LPSTR,WORD);
int  WINAPI ATMGetEXTRAVersion (HWND,LPSTR,WORD);
int  WINAPI ATMGetLayoutName(HWND,LPSTR,WORD);
int  WINAPI ATMOpenConfiguration(HWND,LPSTR);
int  WINAPI ATMOpenLayout(HWND,LPSTR);
int  WINAPI ATMRunEXTRAMacro(HWND, LPSTR,LPSTR);


#ifdef __cplusplus
}
#endif
