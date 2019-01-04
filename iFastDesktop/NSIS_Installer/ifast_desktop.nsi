; Installation Script for iFAST Desktop
;--------------------------------------------------------------------------------------------------

; Require admin rights, since registry settings are added to machine hive
; and to register ona activex control
;--------------------------------------------------------------------------------------------------
RequestExecutionLevel admin

; Helper defines
;--------------------------------------------------------------------------------------------------
!define APP_NAME "iFAST/Desktop"
!define APP_DIRECTORY "iFAST"
!define COMPANY_NAME "International Financial Data Services"

!define PRODUCT_NAME "iFAST/Desktop"
!define PRODUCT_VERSION ${build}
!define PRODUCT_PUBLISHER "IFDS Group"
!define PRODUCT_WEB_SITE "http://www.ifdsgroup.com/"
!define PRODUCT_DIR_REGKEY "Software\Microsoft\Windows\CurrentVersion\App Paths\mfdstc.exe"
!define PRODUCT_UNINST_KEY "Software\Microsoft\Windows\CurrentVersion\Uninstall\${PRODUCT_NAME}"
!define PRODUCT_UNINST_ROOT_KEY "HKLM"

; MUI 1.67 compatible ------
;--------------------------------------------------------------------------------------------------
!include "MUI.nsh"

; MUI Settings
;--------------------------------------------------------------------------------------------------
!define MUI_ABORTWARNING
!define MUI_ICON "${NSISDIR}\Contrib\Graphics\Icons\modern-install.ico"
!define MUI_UNICON "${NSISDIR}\Contrib\Graphics\Icons\modern-uninstall.ico"

!define MUI_HEADERIMAGE
!define MUI_HEADERIMAGE_RIGHT
!define MUI_HEADERIMAGE_BITMAP "${NSISDIR}\Contrib\Graphics\Header\orange-r.bmp" 
!define MUI_HEADERIMAGE_UNBITMAP "${NSISDIR}\Contrib\Graphics\Header\orange-uninstall-r.bmp"

!define MUI_WELCOMEFINISHPAGE_BITMAP "${NSISDIR}\Contrib\Graphics\Wizard\orange.bmp" 
!define MUI_UNWELCOMEFINISHPAGE_BITMAP "${NSISDIR}\Contrib\Graphics\Wizard\orange-uninstall.bmp"

; Variables
;--------------------------------------------------------------------------------------------------
Var StartMenuGroup

; Installer pages
;--------------------------------------------------------------------------------------------------
; Welcome page
!insertmacro MUI_PAGE_WELCOME
; License page
!insertmacro MUI_PAGE_LICENSE "license.txt"
; Directory page
!insertmacro MUI_PAGE_DIRECTORY
; Start Menu page
!insertmacro MUI_PAGE_STARTMENU Application $StartMenuGroup
; Instfiles page
!insertmacro MUI_PAGE_INSTFILES
; Finish page
!define MUI_FINISHPAGE_NOAUTOCLOSE
!insertmacro MUI_PAGE_FINISH

; Uninstaller pages
;--------------------------------------------------------------------------------------------------
!insertmacro MUI_UNPAGE_WELCOME
!insertmacro MUI_UNPAGE_CONFIRM
!insertmacro MUI_UNPAGE_INSTFILES
!insertmacro MUI_UNPAGE_FINISH

; Language files
;--------------------------------------------------------------------------------------------------
!insertmacro MUI_LANGUAGE "English"

; MUI end ------
;--------------------------------------------------------------------------------------------------


; Defines
;--------------------------------------------------------------------------------------------------
!define RELEASE_FILES_PATH                      "..\shipset\win32"
!define ICON_RESOURCE_FILES_RELEASE_PATH        "..\shipset\win32"
!define CANADA_RESOURCE_FILES_RELEASE_PATH      "..\shipset\win32"
!define IFASTCSI_FOLDER_PATH                    "..\shipset\csi"
!define DATA_FILES_PATH                         "..\shipset\data"
!define CONFIG_FILES_PATH                       "..\data\config"


BrandingText "International Financial Data Services"


Name "${PRODUCT_NAME} ${PRODUCT_VERSION}"
OutFile "Setup.exe"
InstallDir "$PROGRAMFILES\${APP_DIRECTORY}"
InstallDirRegKey HKLM "${PRODUCT_DIR_REGKEY}" ""
ShowInstDetails show
ShowUnInstDetails show

;--------------------------------------------------------------------------------------------------
; Installer
;--------------------------------------------------------------------------------------------------

section "install"
        # Set installation folder
    setOutPath $INSTDIR

    # Files added here should be removed by the uninstaller (see section "uninstall")
		file "${RELEASE_FILES_PATH}\activemq-cpp.dll"
        file "${RELEASE_FILES_PATH}\bfawdi.dll"
        file "${RELEASE_FILES_PATH}\bfcbo.dll"
        file "${RELEASE_FILES_PATH}\BFConMgr.dll"
        file "${RELEASE_FILES_PATH}\bfdata.dll"
        file "${RELEASE_FILES_PATH}\BFDBrkr.dll"
        file "${RELEASE_FILES_PATH}\bfproc.dll"
        file "${RELEASE_FILES_PATH}\bfsessn.dll"
        file "${RELEASE_FILES_PATH}\BFUtil.dll"
        file "${RELEASE_FILES_PATH}\boost_thread.dll"
        file "${RELEASE_FILES_PATH}\boost_regex.dll"
        file "${RELEASE_FILES_PATH}\botan.dll"
        file "${RELEASE_FILES_PATH}\dbghelp.dll"
        file "${RELEASE_FILES_PATH}\diawd23U.dll"
        file "${RELEASE_FILES_PATH}\DIAWDIU.dll"
        file "${RELEASE_FILES_PATH}\DICOREU.dll"
        file "${RELEASE_FILES_PATH}\DIDBRKRU.dll"
        file "${RELEASE_FILES_PATH}\diviewu.dll"
        file "${RELEASE_FILES_PATH}\DPlatform.dll"
        file "${RELEASE_FILES_PATH}\ExtraEalSession.dll"
        file "${RELEASE_FILES_PATH}\icudt18l.dll"
        file "${RELEASE_FILES_PATH}\icuin18.dll"
        file "${RELEASE_FILES_PATH}\icuuc18.dll"
		file "${RELEASE_FILES_PATH}\icudt36.dll"
		file "${RELEASE_FILES_PATH}\icuin36.dll"
		file "${RELEASE_FILES_PATH}\icutest.dll"
		file "${RELEASE_FILES_PATH}\icuuc36.dll"
        file "${RELEASE_FILES_PATH}\ifastdataimpl.dll"
        file "${RELEASE_FILES_PATH}\ifastawd.dll"
        file "${RELEASE_FILES_PATH}\ifastbp.dll"
        file "${RELEASE_FILES_PATH}\ifastcbo.dll"
        file "${RELEASE_FILES_PATH}\ifastcsi.dll"
        file "${RELEASE_FILES_PATH}\ifastdbrkr.dll"
        file "${RELEASE_FILES_PATH}\ifastids.dll"
        file "${RELEASE_FILES_PATH}\ifdscore.dll"
        file "${RELEASE_FILES_PATH}\ifsupp.dll"
        file "${RELEASE_FILES_PATH}\KEASession.dll"
		file "${RELEASE_FILES_PATH}\libapr-1.dll"
        file "${RELEASE_FILES_PATH}\libsmq.dll"
        file "${RELEASE_FILES_PATH}\libsmqj.dll"
		file "${RELEASE_FILES_PATH}\io.dll"
		file "${RELEASE_FILES_PATH}\jio.dll"
		file "${RELEASE_FILES_PATH}\JMSCOMClient.dll"
		file "${RELEASE_FILES_PATH}\lwc.dll"
		file "${RELEASE_FILES_PATH}\mgram.dll"
		file "${RELEASE_FILES_PATH}\openssl.exe"
		file "${RELEASE_FILES_PATH}\psc_crypto0_9_8.dll"
		file "${RELEASE_FILES_PATH}\psc_ssl0_9_8.dll"
		file "${RELEASE_FILES_PATH}\psc_zlib_1_2_1_vc80.dll"
		file "${RELEASE_FILES_PATH}\spr.dll"
        file "${RELEASE_FILES_PATH}\MFC71.dll"
        file "${RELEASE_FILES_PATH}\MFC71u.dll"
        file "${RELEASE_FILES_PATH}\mfdstc.exe"
        file "${RELEASE_FILES_PATH}\mfdstc_config.exe"
        file "${RELEASE_FILES_PATH}\msvcp70.dll"
        file "${RELEASE_FILES_PATH}\msvcp71.dll"
		file "${RELEASE_FILES_PATH}\msvcp100.dll"
        file "${RELEASE_FILES_PATH}\msvcp110.dll"
        file "${RELEASE_FILES_PATH}\msvcr70.dll"
        file "${RELEASE_FILES_PATH}\msvcr71.dll"
		file "${RELEASE_FILES_PATH}\msvcr100.dll"
        file "${RELEASE_FILES_PATH}\msvcr110.dll"
        file "${RELEASE_FILES_PATH}\mfc110.dll"
        file "${RELEASE_FILES_PATH}\mfc110u.dll"
        file "${RELEASE_FILES_PATH}\msvcrt.dll"
        file "${RELEASE_FILES_PATH}\ReflectionSession.dll"
        file "${RELEASE_FILES_PATH}\uibase.dll"
        file "${RELEASE_FILES_PATH}\xerces-c_3_1.dll"
        file "${RELEASE_FILES_PATH}\MSCOMCT2.OCX"
		file "${RELEASE_FILES_PATH}\TransactionsMonitor.exe"	
      file "${RELEASE_FILES_PATH}\TransactionsMonitor2.exe"	

        file "${ICON_RESOURCE_FILES_RELEASE_PATH}\Road.ico"
        file "${ICON_RESOURCE_FILES_RELEASE_PATH}\RoadDoc.ico"

        file "${CANADA_RESOURCE_FILES_RELEASE_PATH}\canada_eng.dll"
        file "${CANADA_RESOURCE_FILES_RELEASE_PATH}\canada_fr.dll"
        file "${CANADA_RESOURCE_FILES_RELEASE_PATH}\lux_eng.dll"

        file "${IFASTCSI_FOLDER_PATH}\guicbie.edp"
        file "${IFASTCSI_FOLDER_PATH}\guicbie.r2w"
        file "${IFASTCSI_FOLDER_PATH}\ifast.ekm"
        file "${IFASTCSI_FOLDER_PATH}\ifast.etb"

        
        ###########################################################################################

        CreateDirectory "$INSTDIR\Data"
        
        setOutPath $INSTDIR\Data
        
;        file "${DATA_FILES_PATH}\bfbase.cnd"
;        file "${DATA_FILES_PATH}\bfconmgr.cnd"
;        file "${DATA_FILES_PATH}\BFDATA.cnd"
;        file "${DATA_FILES_PATH}\bfdbrkr.cnd"
;        file "${DATA_FILES_PATH}\bfutil.cnd"
;        file "${DATA_FILES_PATH}\bpbase.cnd"
        file "${DATA_FILES_PATH}\databroker.bin"
        file "${DATA_FILES_PATH}\Desktop.chm"
;        file "${DATA_FILES_PATH}\diawd23.cnd"
;        file "${DATA_FILES_PATH}\diawddb.cnd"
;        file "${DATA_FILES_PATH}\diawdi.cnd"
;        file "${DATA_FILES_PATH}\dicore.cnd"
;        file "${DATA_FILES_PATH}\didbrkr.cnd"
;        file "${DATA_FILES_PATH}\disessn.cnd"
;        file "${DATA_FILES_PATH}\diview.cnd"
;        file "${DATA_FILES_PATH}\gui.cnd"
        file "${DATA_FILES_PATH}\help.chm"
;        file "${DATA_FILES_PATH}\ifastawd.cnd"
;        file "${DATA_FILES_PATH}\ifastbp.cnd"
;        file "${DATA_FILES_PATH}\ifastcbo.cnd"
;        file "${DATA_FILES_PATH}\ifastdbrkr.cnd"
;        file "${DATA_FILES_PATH}\ifastgui.cnd"
        file "${DATA_FILES_PATH}\Search.avi"
        file "${DATA_FILES_PATH}\Setup Guide.chm"
;        file "${DATA_FILES_PATH}\srvbase.cnd"
        file "${DATA_FILES_PATH}\User Guide.chm"
;        file "${DATA_FILES_PATH}\vision.cnd"
;        file "${DATA_FILES_PATH}\xparser.cnd"
        

        ###########################################################################################

        CreateDirectory "$INSTDIR\Data\config"
        
        setOutPath $INSTDIR\Data\config

        file "${CONFIG_FILES_PATH}\fnd00001.htm"
        file "${CONFIG_FILES_PATH}\fnd00002.htm"
        file "${CONFIG_FILES_PATH}\fnd00003.htm"
        file "${CONFIG_FILES_PATH}\fnd00034.htm"
        file "${CONFIG_FILES_PATH}\fndAMGC.htm"
        file "${CONFIG_FILES_PATH}\fundlite.log"
        file "${CONFIG_FILES_PATH}\fyi2.htm"
        file "${CONFIG_FILES_PATH}\fyi.htm"
        file "${CONFIG_FILES_PATH}\fyiframe.htm"
        file "${CONFIG_FILES_PATH}\fyisampl.htm"
        file "${CONFIG_FILES_PATH}\fyit.html"
        file "${CONFIG_FILES_PATH}\fyiticker.htm"
        file "${CONFIG_FILES_PATH}\iFastGuiConfig.xml"
        file "${CONFIG_FILES_PATH}\session.grp"
        file "${CONFIG_FILES_PATH}\session.ini"
        file "${CONFIG_FILES_PATH}\session_no_awd.ini"
        file "${CONFIG_FILES_PATH}\session_portal.grp"
        file "${CONFIG_FILES_PATH}\AWDPortal.ini"
		file "${CONFIG_FILES_PATH}\CallCentre.ini"



        ###########################################################################################
        # Start Menu
        ###########################################################################################
        createDirectory "$SMPROGRAMS\${COMPANY_NAME}"
        # creeate application shortcut
        createShortCut "$SMPROGRAMS\${COMPANY_NAME}\${APP_NAME}.lnk" "$INSTDIR\mfdstc.exe" "" "$INSTDIR\Road.ico"

        # create a shortcut for the uninstaller
        createShortCut "$SMPROGRAMS\${COMPANY_NAME}\uninstall.lnk" "$INSTDIR\uninstall.exe"



        ###########################################################################################
        # Desktop
        ###########################################################################################

        # creeate desktop shortcut
        createShortCut "$DESKTOP\${PRODUCT_NAME}.lnk" "$INSTDIR\mfdstc.exe" "" "$INSTDIR\Road.ico"



        ###########################################################################################
        # Set Registry information
        ###########################################################################################
    WriteRegStr HKLM "Software\DST" "" ""

    WriteRegStr HKLM "Software\DST\DICORE" "mfdstc" "MFDSTC"
    WriteRegStr HKLM "Software\DST\DICORE" "mfdstc_uat" "MFDSTCUAT"

    WriteRegStr HKLM "Software\DST\HLLAPI\TCS" "HLLAPI_FUNCTION_CANCEL" "@d"
    WriteRegStr HKLM "Software\DST\HLLAPI\TCS" "HLLAPI_FUNCTION_COMPLETE" "@e"
    WriteRegStr HKLM "Software\DST\HLLAPI\TCS" "HLLAPI_HOTKEY_TEXT" "Attention"
    WriteRegStr HKLM "Software\DST\HLLAPI\TCS" "HLLAPI_VENDOR" "EXTRA"

    WriteRegDWORD HKLM "Software\DST\TESession\ExtraEal" "Capabilities" "4294967295"
    WriteRegStr HKLM "Software\DST\TESession\ExtraEal" "CreationImport" "CreateExtraEalSession"
    WriteRegStr HKLM "Software\DST\TESession\ExtraEal" "ModuleName" "ExtraEalSession.dll"
    WriteRegStr HKLM "Software\DST\TESession\ExtraEal" "ReleaseImport" "ReleaseExtraEalSession"

    WriteRegDWORD HKLM "Software\DST\TESession\KEA!" "Capabilities" "4294967295"
    WriteRegStr HKLM "Software\DST\TESession\KEA!" "CreationImport" "CreateKEASession"
    WriteRegStr HKLM "Software\DST\TESession\KEA!" "ModuleName" "KEASession.dll"
    WriteRegStr HKLM "Software\DST\TESession\KEA!" "ReleaseImport" "ReleaseKEASession"

    WriteRegDWORD HKLM "Software\DST\TESession\Reflection" "Capabilities" "4294967295"
    WriteRegStr HKLM "Software\DST\TESession\Reflection" "CreationImport" "CreateReflectionSession"
    WriteRegStr HKLM "Software\DST\TESession\Reflection" "ModuleName" "ReflectionSession.dll"
    WriteRegStr HKLM "Software\DST\TESession\Reflection" "ReleaseImport" "ReleaseReflectionSession"

    WriteRegDWORD HKLM "Software\DST\TESession\Stub" "Capabilities" "0"
    WriteRegStr HKLM "Software\DST\TESession\Stub" "CreationImport" "CreateStubSession"
    WriteRegStr HKLM "Software\DST\TESession\Stub" "ModuleName" "StubSession.dll"
    WriteRegStr HKLM "Software\DST\TESession\Stub" "ReleaseImport" "ReleaseStubSession"

    # Register activex control
        RegDLL "$INSTDIR\MSCOMCT2.OCX"

sectionEnd

Section -Post
  WriteUninstaller "$INSTDIR\uninstall.exe"
  WriteRegStr HKLM "${PRODUCT_DIR_REGKEY}" "" "$INSTDIR\mfdstc.exe"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "DisplayName" "$(^Name)"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "UninstallString" "$INSTDIR\uninstall.exe"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "DisplayIcon" "$INSTDIR\mfdstc.exe"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "DisplayVersion" "${PRODUCT_VERSION}"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "URLInfoAbout" "${PRODUCT_WEB_SITE}"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "Publisher" "${PRODUCT_PUBLISHER}"
SectionEnd



;--------------------------------------------------------------------------------------------------
; Uninstaller
;--------------------------------------------------------------------------------------------------

Function un.onUninstSuccess
  HideWindow
  MessageBox MB_ICONINFORMATION|MB_OK "$(^Name) was successfully removed from your computer."
FunctionEnd

Function un.onInit
  MessageBox MB_ICONQUESTION|MB_YESNO|MB_DEFBUTTON2 "Are you sure you want to completely remove $(^Name) and all of its components?" IDYES +2
  Abort
FunctionEnd

Section Uninstall
  # Remove files from the config directory
  Delete "$INSTDIR\Data\config\fnd00001.htm"
  Delete "$INSTDIR\Data\config\fnd00002.htm"
  Delete "$INSTDIR\Data\config\fnd00003.htm"
  Delete "$INSTDIR\Data\config\fnd00034.htm"
  Delete "$INSTDIR\Data\config\fndAMGC.htm"
  Delete "$INSTDIR\Data\config\fundlite.log"
  Delete "$INSTDIR\Data\config\fyi2.htm"
  Delete "$INSTDIR\Data\config\fyi.htm"
  Delete "$INSTDIR\Data\config\fyiframe.htm"
  Delete "$INSTDIR\Data\config\fyisampl.htm"
  Delete "$INSTDIR\Data\config\fyit.html"
  Delete "$INSTDIR\Data\config\fyiticker.htm"
  Delete "$INSTDIR\Data\config\iFastGuiConfig.xml"
  Delete "$INSTDIR\Data\config\session.grp"
  Delete "$INSTDIR\Data\config\session.ini"
  Delete "$INSTDIR\Data\config\session_no_awd.ini"
  Delete "$INSTDIR\Data\config\session_portal.grp"
  Delete "$INSTDIR\Data\config\AWDPortal.ini"
  Delete "$INSTDIR\Data\config\CallCentre.ini"

  # Remove the config directory
  RMDir "$INSTDIR\Data\config"

  # Remove files from the Data directory
;  Delete "$INSTDIR\Data\bfbase.cnd"
;  Delete "$INSTDIR\Data\bfconmgr.cnd"
;  Delete "$INSTDIR\Data\BFDATA.cnd"
;  Delete "$INSTDIR\Data\bfdbrkr.cnd"
;  Delete "$INSTDIR\Data\bfutil.cnd"
;  Delete "$INSTDIR\Data\bpbase.cnd"
  Delete "$INSTDIR\Data\databroker.bin"
  Delete "$INSTDIR\Data\Desktop.chm"
;  Delete "$INSTDIR\Data\diawd23.cnd"
;  Delete "$INSTDIR\Data\diawddb.cnd"
;  Delete "$INSTDIR\Data\diawdi.cnd"
;  Delete "$INSTDIR\Data\dicore.cnd"
;  Delete "$INSTDIR\Data\didbrkr.cnd"
;  Delete "$INSTDIR\Data\disessn.cnd"
;  Delete "$INSTDIR\Data\diview.cnd"
;  Delete "$INSTDIR\Data\gui.cnd"
  Delete "$INSTDIR\Data\help.chm"
;  Delete "$INSTDIR\Data\ifastawd.cnd"
;  Delete "$INSTDIR\Data\ifastbp.cnd"
;  Delete "$INSTDIR\Data\ifastcbo.cnd"
;  Delete "$INSTDIR\Data\ifastdbrkr.cnd"
;  Delete "$INSTDIR\Data\ifastgui.cnd"
  Delete "$INSTDIR\Data\Search.avi"
  Delete "$INSTDIR\Data\Setup Guide.chm"
;  Delete "$INSTDIR\Data\srvbase.cnd"
  Delete "$INSTDIR\Data\User Guide.chm"
;  Delete "$INSTDIR\Data\vision.cnd"
;  Delete "$INSTDIR\Data\xparser.cnd"

  # Remove the Data directory
  RMDir "$INSTDIR\Data"
  
  Delete "$INSTDIR\activemq-cpp.dll"
  Delete "$INSTDIR\bfawdi.dll"
  Delete "$INSTDIR\bfcbo.dll"
  Delete "$INSTDIR\BFConMgr.dll"
  Delete "$INSTDIR\bfdata.dll"
  Delete "$INSTDIR\BFDBrkr.dll"
  Delete "$INSTDIR\bfproc.dll"
  Delete "$INSTDIR\bfsessn.dll"
  Delete "$INSTDIR\BFUtil.dll"
  Delete "$INSTDIR\boost_thread.dll"
  Delete "$INSTDIR\boost_regex.dll"
  Delete "$INSTDIR\botan.dll"
  Delete "$INSTDIR\dbghelp.dll"
  Delete "$INSTDIR\diawd23U.dll"
  Delete "$INSTDIR\DIAWDIU.dll"
  Delete "$INSTDIR\DICOREU.dll"
  Delete "$INSTDIR\DIDBRKRU.dll"
  Delete "$INSTDIR\diviewu.dll"
  Delete "$INSTDIR\DPlatform.dll"
  Delete "$INSTDIR\ExtraEalSession.dll"
  Delete "$INSTDIR\icudt18l.dll"
  Delete "$INSTDIR\icuin18.dll"
  Delete "$INSTDIR\icuuc18.dll"
  Delete "$INSTDIR\icudt36.dll"
  Delete "$INSTDIR\icuin36.dll"
  Delete "$INSTDIR\icutest.dll"
  Delete "$INSTDIR\icuuc36.dll"
  Delete "$INSTDIR\ifastdataimpl.dll"
  Delete "$INSTDIR\ifastawd.dll"
  Delete "$INSTDIR\ifastbp.dll"
  Delete "$INSTDIR\ifastcbo.dll"
  Delete "$INSTDIR\ifastcsi.dll"
  Delete "$INSTDIR\ifastdbrkr.dll"
  Delete "$INSTDIR\ifastids.dll"
  Delete "$INSTDIR\ifdscore.dll"
  Delete "$INSTDIR\ifsupp.dll"
  Delete "$INSTDIR\KEASession.dll"
  Delete "$INSTDIR\libapr-1.dll"
  Delete "$INSTDIR\libsmq.dll"
  Delete "$INSTDIR\libsmqj.dll"
  Delete "$INSTDIR\io.dll"
  Delete "$INSTDIR\jio.dll"
  Delete "$INSTDIR\JMSCOMClient.dll"
  Delete "$INSTDIR\lwc.dll"
  Delete "$INSTDIR\mgram.dll"
  Delete "$INSTDIR\openssl.exe"
  Delete "$INSTDIR\psc_crypto0_9_8.dll"
  Delete "$INSTDIR\psc_ssl0_9_8.dll"
  Delete "$INSTDIR\psc_zlib_1_2_1_vc80.dll"
  Delete "$INSTDIR\spr.dll"
  Delete "$INSTDIR\MFC71.dll"
  Delete "$INSTDIR\MFC71u.dll"
  Delete "$INSTDIR\mfdstc.exe"
  Delete "$INSTDIR\mfdstc_config.exe"
  Delete "$INSTDIR\msvcp70.dll"
  Delete "$INSTDIR\msvcp71.dll"
  Delete "$INSTDIR\msvcp100.dll"
  Delete "$INSTDIR\msvcp110.dll"
  Delete "$INSTDIR\msvcr70.dll"
  Delete "$INSTDIR\msvcr71.dll"
  Delete "$INSTDIR\msvcr100.dll"
  Delete "$INSTDIR\msvcr110.dll"
  Delete "$INSTDIR\mfc110.dll"
  Delete "$INSTDIR\mfc110u.dll"
  Delete "$INSTDIR\msvcrt.dll"
  Delete "$INSTDIR\ReflectionSession.dll"
  Delete "$INSTDIR\uibase.dll"
  Delete "$INSTDIR\xerces-c_3_1.DLL"
  Delete "$INSTDIR\TransactionsMonitor.exe"
  Delete "$INSTDIR\TransactionsMonitor2.exe"
  
  Delete "$INSTDIR\Road.ico"
  Delete "$INSTDIR\RoadDoc.ico"

  Delete "$INSTDIR\canada_eng.dll"
  Delete "$INSTDIR\canada_fr.dll"
  Delete "$INSTDIR\lux_eng.dll"

  Delete "$INSTDIR\guicbie.edp"
  Delete "$INSTDIR\guicbie.r2w"
  Delete "$INSTDIR\ifast.ekm"
  Delete "$INSTDIR\ifast.etb"

  # Remove rest of the files
  Delete "$INSTDIR\${PRODUCT_NAME}.url"
  Delete "$INSTDIR\uninstall.exe"

  # Remove installation directory
  RMDir "$INSTDIR"

  # Remove shortcuts
  Delete "$SMPROGRAMS\${COMPANY_NAME}\uninstall.lnk"
  Delete "$SMPROGRAMS\${COMPANY_NAME}\${APP_NAME}.lnk"
  Delete "$DESKTOP\${PRODUCT_NAME}.lnk"

  # Remove the application directory from the start menu
  RMDir "$SMPROGRAMS\${COMPANY_NAME}"

  DeleteRegKey ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}"
  DeleteRegKey HKLM "${PRODUCT_DIR_REGKEY}"
  SetAutoClose true
SectionEnd