/*============================================================================*\
 *
 *      COPYRIGHT:
 *
 *      The computer systems, procedures, data bases and programs
 *      created and maintained by DST Systems, Inc., are proprietary
 *      in nature and as such are confidential.  Any unauthorized
 *      use or disclosure of such information may result in civil
 *      liabilities.
 *
 *      Copyright %xdate C$ by DST Systems, Inc.
 *      All Rights Reserved.
 *
 * $Workfile:   awddef.h  $
 *  $Modtime:   30 Oct 1997 14:50:48  $
 *   $Author:   kovacsro  $
 *  $Archive:   Y:/VCS/iFastAWD/inc_share/awddef.h-arc  $
 * $Revision:   1.0  $ $Date:   28 Jan 2008 13:33:54  $
 * Description:
 *
 *
\*============================================================================*/
#ifndef AWDDEF_H
#define AWDDEF_H

#define DllExport __declspec( dllexport )
#define DllImport __declspec( dllimport )

#define  AWD_CONTAINER         "AWD_Container"
#define  AWD_HISTORY           "AWD_History"
#define  AWD_QUALITY_WORK_STEP "AWD_Quality_Work_Step"
#define  AWD_QUALITY_HISTORY   "AWD_Quality_History"
#define  AWD_QUALITY_ERROR     "AWD_Quality_Error"
#define  AWD_SUSPEND           "AWD_Suspend"
#define  AWD_COMMENTS          "AWD_Comments"
#define  AWD_FAX_WS            "AWD_FAX_WS"
#define  AWD_QUALITY_WORK_STEP "AWD_Quality_Work_Step"
#define  AWD_QUALITY_HISTORY   "AWD_Quality_History"
#define  AWD_QUALITY_ERROR     "AWD_Quality_Error"
#define  AWD_CREATE_SOURCE     "AWD_Create_Source"
#define  AWD_CREATE_WRK_OBJ    "AWD_Create_Work_Obj"
#define  AWD_CREATE_FOLDER     "AWD_Create_Folder"
#define  AWD_WIN_POSITION      "Window Position"
#define  CSD_PROCESS           "CSD_Process"
#define  FAX_WS                "FAX_WorkStation"
#define  CONTAINER_VIEW        "Container View"
#define  PROCESS_VIEW          "Process View"
#define  LOOKUP_VIEW           "Lookup View"
#define  CREATE_VIEW           "Create View"
#define  FIND_VIEW             "Find View"
#define  AWD_CREATE_REL_FLAG   "Confirm create flag"
#define  AWD_BREAK_REL_FLAG    "Confirm break flag"
#define  AWD_PASS_FAIL_FLAG    "Confirm pass/fail flag"
#define  AWD_AUTOCREATE_FLAG    "Auto create objects"
#define  AWD_PROCIMMEDIATE_FLAG "Process work immediately"
#define  AWD_CONFIRM_LOGOFF_FLAG    "Confirm Logoff flag"
#define  AWD_ADD_COMMENTS_FLAG "Confirm add comments flag"
#define  MLE_FONT              "MLE Font information"
#define  AWD_AUTOFLAG          "AWD AutoFlag"
#define  SENDER_INFO           "Sender Information"
#define  AWD_EXTERNAL_PROGRAM  "AWD_EXT"
#define  AWD_HIST_PRINT        "PRINTER PORT"

#define      ICON_FLAGS     CV_ICON
#define      TREE_FLAGS     CV_TREE | CV_ICON | CA_TREELINE
#define      DETAIL_FLAGS   CV_DETAIL | CA_DETAILSVIEWTITLES

#define AWD_RESNAME           "AWD"
#define AWD_HIST              "AWD HIST"
#define DATA_PATH             "DATA_PATH"
#define BIN_PATH              "BIN_PATH"
#define FILES_PATH            "FILES_PATH"
#define PERSISTENT_PATH       "PERSISTENT_PATH"
#define INSTALL_PATH          "INSTALL_PATH"
#define CSD_PATH              "CSD PATH"

#define AWD_DEFAULT_BIN_PATH "C:\\AWDWIN\\BIN"
#define AWD_DEFAULT_DATA_PATH "C:\\AWDWIN\\DATA"
#define AWD_DEFAULT_INSTALL_PATH "C:\\AWDWIN"
#define AWD_FOLDER_PATH          "\\AWD"
#define AWD_DISTLIST_PATH        "\\AWDLIST.DAT"
#define AWD_PROFILE_NAME       "DST\\AWD\\"

#define CLONE_STATUS           "%d of %d items Cloned..."

#define FAX_LOG_FIRST_LINE     "Fax Request from User: %-56s"
#define FAX_LOG_SECOND_LINE    "To: %-74s"
#define FAX_LOG_THIRD_LINE     "To Fax Number: %-63s"
#define FAX_LOG_FOURTH_LINE    "Remarks: %-69s"


// Defined strings to use for WriteLog()

#define AWD_OUT_OF_MEMORY        "Memory allocation error - File: %s  Line: %d"
#define AWD_BAD_POINTER          "Bad pointer passed - File: %s  Line: %d"
#define AWD_BAD_CONTAINER        "Unable to create Conatiner - File: %s  Line: %d"
#define AWD_OBJECT_CREATED_LOG       "Created object, Key = %s"
#define AWD_OBJECT_NOT_CREATED   "Unable to create object, Key = %s"
#define AWD_BAD_DATA_FILES       "Unable to create data files - File: %s Line: %d"

#define DAM_VIEW_INITIATE        "Dam view initiated, Key = %s"
#define DAM_VIEW_FINISHED        "Dam view completed successfully. "
#define DAM_VIEW_ERROR           "Dam view error - View : %s RC = %s Msg : %s "

#define AWD_INITIATE             "Initiating, Key = %s"
#define AWD_TERMINATE            "Terminating"

#define AWD_INI                  "awd.ini"
#define AWD_INI_APP_DEFAULTFONT  "AWDDefaultFont"
#define AWD_INI_KEY_DEFAULTFONT  "DEFAULT"

#define AWD_DEFAULT_FILE        "%s\\defaults.dat"
#define AWD_OPERATOR_FILE       "%s\\operator.dat"
#define AWD_OPERATOR_INFO_FILE  "%s\\operinfo.dat"
#define AWD_FIELDS_FILE         "%s\\fields.dat"
#define AWD_LOOKUPS_FILE        "%s\\lookups.dat"
#define AWD_OLD_LOOKUPS_FILE    "%s\\lookups.old"
#define AWD_TRACE_FLAG          "Trace Flag"


#define COMMENTS_TITLE          "Insert Comments"
#define COMMENTS_EXTENSION      "*.CMT"
#define COMMENTS_OK_BUTTON      "Insert"
#define COMMENTS_LINE_COLUMN    "Line : %d  Column : %d"
#define COMMENTS_KEYSTROKE      "keystroke"
#define COMMENTS_CUT            "cut"
#define COMMENTS_COPY           "copy"
#define COMMENTS_PASTE          "paste"
#define COMMENTS_INSERT         "insert"
#define COMMENTS_UNDO           "~Undo"
#define COMMENTS_REDO           "Re~do"
#define COMMENTS_MENU           "%s %s\tAlt+Backspace"
#define COMMENTS_SEARCH_STRING  "Search string : '%s' not found."
#define COMMENTS_SEARCH         "Search"
#define COMMENTS_SAVEAS         "SaveAs"
#define COMMENTS_CMT            ".CMT"
#define COMMENTS_UPDATE_STATUS  "Updating object history."

#define PERSONAL_QUEUES 'P'
#define WORK_QUEUES     'Q'
#define ALL_QUEUES      'B'        // 'B' stands for BOTH sets of queues

// Defines for HELP files

#define  AWDPROCESS_HELP   "PROC"
#define  AWDLOOKUP_HELP   "LKUP"
#define  AWDCREATE_HELP   "CRET"
#define  AWDCSDTOOL_HELP   "TOOL"
#define  AWDSETTINGS_HELP   "SETT"

#define UM_ISIMAGEWINDOW    ( WM_USER + 1019 )

#define  AWD_CONTAINER_ID            "AWD0001"
#define  AWD_MESSAGE_ID              "AWD0002"
#define  AWD_CHANGE_QUEUE_ID         "AWD0003"
#define  AWD_COMMENTS_ID             "AWD0004"
#define  AWD_COMPLETE_ID             "AWD0005"
#define  AWD_CNTER_SETTINGS_ID       "AWD0006"
#define  AWD_CREATE_FOLDER_ID        "AWD0007"
#define  AWD_CREATE_SOURCE_ID        "AWD0008"
#define  AWD_CREATE_WORK_ID          "AWD0009"
#define  AWD_CSD_EXPAND_ID           "AWD0010"
#define  AWD_DEFAULT_VIEW_ID         "AWD0011"
#define  AWD_EXIT_ID                 "AWD0012"
#define  AWD_GOTO_ID                 "AWD0013"
#define  AWD_HISTORY_ID              "AWD0014"
#define  AWD_LIST_ID                 "AWD0015"
#define  AWD_PASSWORD_ID             "AWD0016"
#define  AWD_PRINT_ID                "AWD0017"
#define  AWD_REPLACE_ID              "AWD0018"
#define  AWD_SEARCH_ID               "AWD0019"
#define  AWD_SIGNON_ID               "AWD0020"
#define  AWD_SUSPEND_ID              "AWD0021"
#define  AWD_WAIT_ID                 "AWD0022"
#define  AWD_QUALITY_WORKSTEP_ID     "AWD0023"
#define  AWD_QUALITY_HISTORY_ID      "AWD0024"
#define  AWD_QUALITY_ERROR_ID        "AWD0025"
#define  AWD_FAX_ID                  "AWD0026"
#define  AWD_FAX_EDIT_ID             "AWD0027"
#define  AWD_DOCUMENT_FETCH_VALUE    "DOCUMENT FETCH"

#define WM_AWD_OBJECT_UPDATED        ( WM_USER + 2100 )
#define WM_AWD_LOGGING_OFF           ( WM_USER + 2101 )
#define WM_AWD_BROADCAST_SUSPEND     ( WM_USER + 2102 )
#define WM_AWD_BROADCAST_QUALITY_PASS ( WM_USER + 2103 )
#define WM_AWD_BROADCAST_QUALITY_FAIL ( WM_USER + 2104 )
#define WM_OBJECT_CLONED              ( WM_USER + 2105 )
#define WM_OBJECT_DELETED             ( WM_USER + 2106 )
#define WM_LOAD_DLG_HELP              ( WM_USER + 2107 )

/*----------------------------------------------------------------------------*\
|* AWD Options (W50 table)                                                    *|
\*----------------------------------------------------------------------------*/
#define CSD_OPTION_USE_ELAPSEDTIME           "CSD USE ACTIVE TIME"
#define CSD_OPTION_UPDATE_SUSPEND            "CSD UPDATE SUSPEND"
#define CSD_OPTVALUE_NO_UPDATE_SUSPEND       'N'
#define CSD_OPTVALUE_AUTO_UPDATE_SUSPEND     'Y'
#define CSD_OPTVALUE_PROMPT_UPDATE_SUSPEND   'P'
#define CSD_OPTION_AUTOFLAG_CLOSE             "AUTOFLAGCLOSE"
#define CSD_OPTION_LKUPDATE_RANGE             "LKUPDATE RANGE"
#define CSD_OPTION_LKUPDATE_TAG               "LKUPDATE TAG"
#define AWD_OPTION_PRODFACTOR                 "PRODUCTIVITY FACTOR"
#define AWD_OPTION_QUALFACTOR                 "QUALITY FACTOR"
#define AWD_OPTION_UTILFACTOR                 "UTILIZATION FACTOR"
#define AWD_OPTION_DATEPROFILE                "DATE PROFILE"
#define AWD_OPTION_JULIANPROFILE              "JULIAN PROFILE"
#define AWD_OPTION_TIMEPROFILE                "TIME PROFILE"
#define AWD_OPTION_DECIMALSYMBOL              "DECIMAL SYMBOL"
#define AWD_OPTION_DTM_HISTORY_VIEW           "DTM HISTORY VIEW"
#define AWD_OPTION_LOOKUP_AUTOLOCK            "LOOKUP AUTOLOCK"
#define AWD_OPTION_LOOKUP_SQL                 "LOOKUP SQL"
#define AWD_OPTION_RETAIN_SUSPEND_DAYS        "RETAIN SUSPEND DAYS"
#define AWD_OPTION_USE_ALL_WORK_STATUS        "USE ALL WORK STATUS"
#define AWD_OPTION_DEFAULT_DASD               "AAA DEFAULT DASD"

/*----------------------------------------------------------------------------*\
|* Service names:                                                             *|
\*----------------------------------------------------------------------------*/
#define AWD_SERVICE_CHANGE_QUEUE                "AWDChangeQueueService"
#define AWD_SERVICE_CLONE                       "AWDCSDCloneService"
#define AWD_SERVICE_CLONENOCSD                  "AWDCloneService"
#define AWD_SERVICE_COMMENTS                    "AWDCommentsService"
#define AWD_SERVICE_CSD                         "AWDCSDService"
#define AWD_SERVICE_FAX                         "AWDFaxService"
#define AWD_SERVICE_FIND_CHILDREN               "AWDFindChildrenService"
#define AWD_SERVICE_FIND_PARENT                 "AWDFindParentService"
#define AWD_SERVICE_FIND_PARENTS                "AWDFindParentsService"
#define AWD_SERVICE_HISTORY                     "AWDHistoryService"
#define AWD_SERVICE_IMAGE                       "AWDImageService"
#define AWD_SERVICE_INFO                        "AWDInfoService"
#define AWD_SERVICE_NUM_PAGES                   "AWDNumPagesService"
#define AWD_SERVICE_PRINT                       "AWDPrintService"
#define AWD_SERVICE_PROCESS                     "AWDProcessService"
#define AWD_SERVICE_QUALITY                     "AWDQualityService"
#define AWD_SERVICE_SOURCE_AND_DETAIL           "AWDSourceandDetailService"
#define AWD_SERVICE_SUSPEND                     "AWDSuspendService"

/*----------------------------------------------------------------------------*\
|* Needed by csd, csdtool, awdapi                                             *|
\*----------------------------------------------------------------------------*/
#define DLGC_COMBOBOX      0x1000  /* Combobox                                */

/*----------------------------------------------------------------------------*\
|* Registry keys:                                                             *|
\*----------------------------------------------------------------------------*/
#define KEY_AWDWINDOWPOS         "Software\\DST\\AWD\\WindowPos"
#define KEY_CSDWINDOWPOS         "Software\\DST\\AWD\\CSDProc\\AWDCSDWin"
#define AWD_ARRANGE_MODE         "Arrange Mode"
#define AWD_DEFAULT_ARRANGE_MODE "N"


/*----------------------------------------------------------------------------*\
|* Unique names for identification of a single instance app.                  *|
\*----------------------------------------------------------------------------*/
#define AWDLKUP_UNIQUE_NAME                     "LKUP23"


/*----------------------------------------------------------------------------*\
|* Debug Macros:                                                              *|
|* Using the following debug macros you can write code such as...             *|
|*                                                                            *|
|*    DBG(printf("Made it this far into the code");)                          *|
|*                                                                            *|
|* or                                                                         *|
|*    DBG( for( i = 0; i < 10; i++ ) )                                        *|
|*    DBG(    for( j = 0; j <= i; j++ ) )                                     *|
|*    DBG(      printf( "\n  x[%u][%u] = %u", i, j, x[i][j] );)               *|
|* or                                                                         *|
|*                                                                            *|
|*    IF_DBG(rc == NO_ERROR)                                                  *|
|*       DBG(printf("OK return code from function");)                         *|
|*    ELSEIF_DBG(rc == ERROR_TIMEOUT)                                         *|
|*       DBG(printf("timed out");)                                            *|
|*    ELSE_DBG                                                                *|
|*       DBG(printf("Error occured");)                                        *|
|*    ENDIF_DBG                                                               *|
|*                                                                            *|
\*----------------------------------------------------------------------------*/
#if defined( _DEBUG )
   #define DBG(a)    a
   #define IF_DBG(a)  if( a ) {
   #define ELSE_DBG  } else {
   #define ELSEIF_DBG(a)  } else if( a ) {
   #define ENDIF_DBG  }
#else
   #define DBG(a)
   #define IF_DBG(a)
   #define ELSE_DBG
   #define ELSEIF_DBG(a)
   #define ENDIF_DBG
#endif


#endif  /* AWDDEF_H */
/*============================================================================*\
 * $Log:   Y:/VCS/iFastAWD/inc_share/awddef.h-arc  $
//
//   Rev 1.0   28 Jan 2008 13:33:54   kovacsro
//Initial revision.
// 
//    Rev 1.0   Dec 16 1997 09:07:00   DDOS
//  
 * 
 *    Rev 1.21   Oct 31 1997 09:45:40   djth
 * Fix for ticket #855 (arrangement of main awd folder).
 *
 *    Rev 1.20   Aug 26 1997 12:30:58   DT17859A
 * change CSD USE ELAPSED TIME
 * to CSD USE ACTIVE TIME
 *
 *
 *    Rev 1.19   25 Jul 1997 17:26:12   DBRD
 * Added new window msg: WM_LOAD_DLG_HELP.
 *
 *    Rev 1.18   Jun 18 1997 10:01:24   DMRL
 * changed awdpm default directories to awdwin
 *
 *    Rev 1.17   Jun 18 1997 08:36:22   DT17859A
 * added some CSD W50 options
 *
 *    Rev 1.16   Jun 17 1997 14:24:58   DMRL
 * added options for use all work types and default dasd.
 *
 *    Rev 1.15   Jun 05 1997 11:25:16   DMRL
 * added system option #defines.
 *
 *    Rev 1.14   May 16 1997 12:38:00   DMRL
 * added #define for LOOKUP_AUTOLOCK
 *
 *    Rev 1.13   13 May 1997 17:17:06   DJTH
 * Added check for awd option "DTM HISTORY VIEW" before calling any of the
 * DTM history stuff.
 *
 *    Rev 1.12   09 May 1997 16:22:10   DBRD
 * Added KEY_CSDWINDOWPOS
 *
 *    Rev 1.11   08 Apr 1997 14:47:52   DBRD
 * improved the DBG() macros a bit.
 *
 *    Rev 1.10   08 Apr 1997 12:22:38   DBRD
 * added definition for DllImport.
 *
 *    Rev 1.9   01 Apr 1997 18:05:58   DBRD
 * added some defines for registry entries.
 *
 *    Rev 1.8   28 Feb 1997 16:12:26   DJTH
 * Added define for lookup's unique name.
 *
 *    Rev 1.7   Feb 28 1997 14:55:16   DMRL
 * fixed lost changes.
 *
 *    Rev 1.5   Feb 27 1997 14:57:36   DMRL
 * added #define for profile name.
 *
 *    Rev 1.4   Feb 21 1997 09:30:26   DMRL
 * changed the POSITION #define to WIN_POSITION #define
 * POSITION is a Windows type.
 *
 *    Rev 1.3   19 Feb 1997 13:18:30   DBRD
 * Added a registry key definition.
 *
 *    Rev 1.2   14 Feb 1997 16:30:34   DBRD
 * Added some debug macros and defined DllExport.
 *
 *    Rev 1.1   Jan 08 1997 15:27:52   DMRL
 * changed COMMENTS_PATH and LOOKUP_PATH
 * to FILES_PATH and PERSISTENT_PATH.
 *
 *    Rev 1.0   Sep 20 1996 10:57:46   DWBP
 * initial?
 *
 *    Rev 1.8   Aug 29 1996 08:42:30   DCUR
 * Added the AWD_SERVICE_CLONENOCSD
 * #define
 *
 *    Rev 1.7   Aug 12 1996 15:24:32   DJTH
 * Moved define for DLGC_COMBOBOX into awddef.h so everyone can get to it.
 *
 *    Rev 1.6   Jul 31 1996 08:59:04   DT17859A
 * changed AWD_OBJECT_CREATED
 * to AWD_OBJECT_CREATED_LOG
 * to eliminate conflict with awdmsgid.h
 * (used the same name)
 *
 *    Rev 1.5   11 Jul 1996 16:32:08   DBRD
 * Added some service names constants.
 *
 *    Rev 1.4   10 Jul 1996 16:22:00   DBRD
 * Added some CSD options constants.
 *
 *    Rev 1.3   01 Jul 1996 16:42:22   DBRD
 * Added some AWD Options constants.
\*============================================================================*/

