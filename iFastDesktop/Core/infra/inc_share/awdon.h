#ifndef _AWDON2_H
 #define _AWDON2_H

#define  AWD_LOGON_INVALID_OPID             100
#define  AWD_LOGON_INVALID_PSWD             101
#define  AWD_LOGON_PSWD_EXPIRED             105
#define  AWD_NEWPSWD_SAMEAS_OLD             108
#define  AWD_LOGON_USER_ALREADY_LOGGED_ON   110
#define  AWD_LOGON_USER_DISABLED            113
#define  SIZEOF_MIN_PSWD                    5

class AWDApplication;
class CAWDCommonResource;
class AWDMainFolder;

enum AWDLOGON_RC
{
   AWDLOGON_NO_ERROR, AWDLOGON_INVALID_PSWD, AWDLOGON_USER_ALREADY_LOGGED_ON,
   AWDLOGON_PSWD_EXPIRED, AWDLOGON_NEWPSWD_SAMEAS_OLD, AWDLOGON_INVALID_OPID,
   AWDLOGON_USER_DISABLED, AWDLOGON_INVALID_NEW_PSWD, AWDLOGON_OTHER_ERROR,
   AWDLOGON_NOGET_SERVICEDATFILE
}; /* end of enum */

class CAWDLogon
{
   public:
   /*------------------- Constructors ----------------------------------------*/
   __declspec(dllexport) CAWDLogon( BOOL usingGUI );
   __declspec(dllexport) CAWDLogon( CString& userid, CString& password, CString& newPassword, BOOL usingGUI );
   __declspec(dllexport) virtual ~CAWDLogon();

   /*------------------- Public methods --------------------------------------*/
   __declspec(dllexport) AWDLOGON_RC Logon( CString& strErrMsg );
   __declspec(dllexport) AWDLOGON_RC Logon( CString& sUserid, CString& sPswd, CString& sNewPswd, CString& sErrMsg );
   __declspec(dllexport) BOOL CreateMainFolder();
   __declspec(dllexport) BOOL DestroyMainFolderBeforeCreate();
   __declspec(dllexport) BOOL RefreshMainFolder();

   private:
   /*------------------- Private data ----------------------------------------*/
   AWDApplication* m_pApp;
   CAWDCommonResource* m_pComm;
   AWDMainFolder* m_mainFld;

   CString m_strUserid;
   CString m_strPswd;
   CString m_strNewPswd;

   BOOL m_bUsingGUI;
   BOOL m_bInternalCall;

   /*------------------- Private methods -------------------------------------*/
   void Initialize();

};  /* end of class CAWDLogon */

#endif
