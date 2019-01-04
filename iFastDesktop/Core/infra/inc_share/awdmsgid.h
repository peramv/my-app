#ifndef _AWDMSGID_H_
#define _AWDMSGID_H_

//***************************************************************************
//
// Message id definitions for AWD.
//    Note:  Please follow the format defined below for AWD messages when
//           creating new messages.  Macros have been defined to make life
//           easier.
//
//           MAKEAWDMSG     - platform independant version of OS/2 MPFROM2SHORT
//           GETAWDMSGFLAGS - platform independant version of OS/2 SHORT1FROMMP
//           GETAWDMSGID    - platform independant version of OS/2 SHORT2FROMMP
//
// Version 2.3.0
//
// Format of each message:
//
//   BIT31      BIT30-BIT27      BIT26-BIT21 BIT20-BIT16        BIT15-BIT0
//
//   0-private  1000-case        reserved    reserved for user  msgid -
//   1-public   0100-transaction                                started at 1
//              0010-source
//              0001-folder
//              1111-all
//              0000-none
//
//***************************************************************************
#include "bitflags.h"

// Combine l & h to form a 32 bit AWD message.
#define MAKEAWDMSG(h, l)   ((unsigned long)(((unsigned short)(l)) | ((unsigned long)(h))))

// Macros to extract standard types from an AWD message.
#define GETAWDMSGFLAGS(mr) ((unsigned long)(mr))
#define GETAWDMSGID(mr)    ((unsigned short)((unsigned long)mr))


// Flags defined so far.  Reserved area (bits 26-21) is for new AWD flags.
// User area (bits 20-16) is for user defined flags.

#define AWD_MF_PUBLIC         BIT_31      // Private is the default
#define AWD_MF_CASE           BIT_30
#define AWD_MF_TRANS          BIT_29
#define AWD_MF_SOURCE         BIT_28
#define AWD_MF_FOLDER         BIT_27
#define AWD_MF_ALL            AWD_MF_CASE | AWD_MF_TRANS | AWD_MF_SOURCE | AWD_MF_FOLDER

// Reserved Area for future flags.
//#define                     BIT_26
//#define                     BIT_25
//#define                     BIT_24
//#define                     BIT_23
//#define                     BIT_22
//#define                     BIT_21

// Awd message ids.
#define IDM_LOGON                  1
#define IDM_LOGOFF                 2

#define IDM_CSDOK                  3
#define IDM_CSDCANCEL              4

#define IDM_LOB_DONE               5
#define IDM_LOB_CANCEL             6
#define IDM_LOB_FUN_COMPLETE       7
#define IDM_LOB_UPDATE             8
#define IDM_LOB_PASS               9
#define IDM_LOB_FAIL               10
#define IDM_LOB_ERROR              11
#define IDM_SERVICE_MGR            12
#define IDM_OBJ_SUSPEND            13
#define IDM_OBJ_ACTIVE             14
#define IDM_OBJ_UPDATE             15
#define IDM_OBJ_CREATE             16
#define IDM_OBJ_LOCKED             17
#define IDM_OBJ_UNLOCKED           18
#define IDM_OBJ_DELETE             19
#define IDM_OBJ_RELATION_BREAK     20
#define IDM_CLONEOK                21
#define IDM_CLONECANCEL            22

#define IDM_IWD_START              23
#define IDM_IWD_READY              24
#define IDM_IWD_STOP               25
#define IDM_IWD_OPEN_DOCUMENT      26
#define IDM_IWD_OPEN_SOMDOCUMENT   27
#define IDM_IWD_NEW_DOCUMENT       28
#define IDM_IWD_EDIT_DOCUMENT      29
#define IDM_IWD_ADD_IMAGE_PAGE     30
#define IDM_IWD_DELETE_IMAGE_PAGE  31
#define IDM_IWD_SAVE_DOCUMENT      32
#define IDM_IWD_CLOSE_DOCUMENT     33
#define IDM_IWD_RESET              34
#define IDM_IWD_INVERT             35
#define IDM_IWD_PAGE_UP            36
#define IDM_IWD_PAGE_DOWN          37
#define IDM_IWD_ZOOM_IN            38
#define IDM_IWD_ZOOM_OUT           39
#define IDM_IWD_ROTATE_RIGHT       40
#define IDM_IWD_ROTATE_LEFT        41
#define IDM_IWD_QUERY_SETTINGS     42
#define IDM_IWD_MINIMIZE           43
#define IDM_IWD_RESTORE            44
#define IDM_IWD_SET_MODE           45
#define IDM_IWD_QUERY_MODE         46
#define IDM_IWD_QUERY_PAGE_NO      47
#define IDM_IWD_PING_SERVER        48
#define IDM_IWD_INSERT_AFTER       49
#define IDM_IWD_INSERT_BEFORE      50
#define IDM_IWD_INSERT_OVERLAY     51

#define IDM_OBJ_CREATE_RELATION    52
#define IDM_SRC_ANNOTATION_CHANGED 53
#define IDM_OBJ_ADD_CHILDREN       54

#define IDM_OBJ_BATCH_UNLOCK       55

#define IDM_IWD_FOREGROUND         56

#define IDM_CLONE_OPTIONS_OK       57
#define IDM_CLONE_OPTIONS_CANCEL   58

#define IDM_OBJ_EXTERN_CHANGE      59

#define IDM_IWD_TERMINATE          60
#define IDM_SRC_CLOSED_IN_IMGWN    61

#define IDM_OBJ_BATCH_LOCK         62

#define IDM_USER                   200

// Awd messages.
#define AWD_LOGGING_ON             MAKEAWDMSG( AWD_MF_PUBLIC, IDM_LOGON )
#define AWD_LOGGING_OFF            MAKEAWDMSG( AWD_MF_PUBLIC, IDM_LOGOFF )

#define AWD_CSD_CLOSE_OK           MAKEAWDMSG( AWD_MF_ALL, IDM_CSDOK )
#define AWD_CSD_CLOSE_CANCEL       MAKEAWDMSG( AWD_MF_ALL, IDM_CSDCANCEL )

#define AWD_LOB_DONE               MAKEAWDMSG( AWD_MF_CASE | AWD_MF_TRANS, IDM_LOB_DONE )
#define AWD_LOB_CANCEL             MAKEAWDMSG( AWD_MF_CASE | AWD_MF_TRANS, IDM_LOB_CANCEL )
#define AWD_LOB_FUN_COMPLETE       MAKEAWDMSG( AWD_MF_CASE | AWD_MF_TRANS, IDM_LOB_FUN_COMPLETE )
#define AWD_LOB_UPDATE             MAKEAWDMSG( AWD_MF_CASE | AWD_MF_TRANS, IDM_LOB_UPDATE )
#define AWD_LOB_PASS               MAKEAWDMSG( AWD_MF_CASE | AWD_MF_TRANS, IDM_LOB_PASS )
#define AWD_LOB_FAIL               MAKEAWDMSG( AWD_MF_CASE | AWD_MF_TRANS, IDM_LOB_FAIL )
#define AWD_LOB_ERROR              MAKEAWDMSG( AWD_MF_CASE | AWD_MF_TRANS, IDM_LOB_ERROR )

#define AWD_SERVICE_MANAGER        MAKEAWDMSG( AWD_MF_PUBLIC | AWD_MF_ALL, IDM_SERVICE_MGR )

#define AWD_OBJECT_SUSPENDED       MAKEAWDMSG( AWD_MF_PUBLIC | AWD_MF_CASE | AWD_MF_TRANS, IDM_OBJ_SUSPEND )
#define AWD_OBJECT_ACTIVATED       MAKEAWDMSG( AWD_MF_PUBLIC | AWD_MF_CASE | AWD_MF_TRANS, IDM_OBJ_ACTIVE )
#define AWD_OBJECT_UPDATED         MAKEAWDMSG( AWD_MF_PUBLIC | AWD_MF_CASE | AWD_MF_TRANS, IDM_OBJ_UPDATE )
#define AWD_OBJECT_CREATED         MAKEAWDMSG( AWD_MF_PUBLIC | AWD_MF_CASE | AWD_MF_TRANS, IDM_OBJ_CREATE )
#define AWD_OBJECT_DELETED         MAKEAWDMSG( AWD_MF_PUBLIC | AWD_MF_ALL, IDM_OBJ_DELETE )
#define AWD_OBJECT_RELATION_BROKEN MAKEAWDMSG( AWD_MF_PUBLIC | AWD_MF_CASE | AWD_MF_TRANS | AWD_MF_FOLDER, IDM_OBJ_RELATION_BREAK )

#define AWD_OBJECT_LOCKED          MAKEAWDMSG( AWD_MF_PUBLIC | AWD_MF_ALL, IDM_OBJ_LOCKED )
#define AWD_OBJECT_UNLOCKED        MAKEAWDMSG( AWD_MF_PUBLIC | AWD_MF_ALL, IDM_OBJ_UNLOCKED )
#define AWD_OBJECT_BATCH_LOCK      MAKEAWDMSG( AWD_MF_PUBLIC | AWD_MF_ALL, IDM_OBJ_BATCH_LOCK )
#define AWD_OBJECT_BATCH_UNLOCK    MAKEAWDMSG( AWD_MF_PUBLIC | AWD_MF_ALL, IDM_OBJ_BATCH_UNLOCK )

#define AWD_CLONE_CLOSE_OK         MAKEAWDMSG( AWD_MF_ALL, IDM_CLONEOK )
#define AWD_CLONE_CLOSE_CANCEL     MAKEAWDMSG( AWD_MF_ALL, IDM_CLONECANCEL )
#define AWD_CLONE_OPTIONS_CLOSE_OK MAKEAWDMSG( AWD_MF_ALL, IDM_CLONE_OPTIONS_OK )
#define AWD_CLONE_OPTIONS_CLOSE_CANCEL MAKEAWDMSG( AWD_MF_ALL, IDM_CLONE_OPTIONS_CANCEL )

#define AWD_OBJECT_ADD_CHILDREN    MAKEAWDMSG( AWD_MF_PUBLIC | AWD_MF_CASE | AWD_MF_TRANS | AWD_MF_SOURCE, IDM_OBJ_ADD_CHILDREN )
#define AWD_OBJECT_EXTERN_CHANGE   MAKEAWDMSG( AWD_MF_ALL, IDM_OBJ_EXTERN_CHANGE )

#define AWD_IWD_START              MAKEAWDMSG( AWD_MF_SOURCE, IDM_IWD_START )
#define AWD_IWD_READY              MAKEAWDMSG( AWD_MF_SOURCE, IDM_IWD_READY )
#define AWD_IWD_STOP               MAKEAWDMSG( AWD_MF_SOURCE, IDM_IWD_STOP )
#define AWD_IWD_OPEN_DOCUMENT      MAKEAWDMSG( AWD_MF_SOURCE, IDM_IWD_OPEN_DOCUMENT )
#define AWD_IWD_OPEN_SOMDOCUMENT   MAKEAWDMSG( AWD_MF_SOURCE, IDM_IWD_OPEN_SOMDOCUMENT )
#define AWD_IWD_NEW_DOCUMENT       MAKEAWDMSG( AWD_MF_SOURCE, IDM_IWD_NEW_DOCUMENT )
#define AWD_IWD_EDIT_DOCUMENT      MAKEAWDMSG( AWD_MF_SOURCE, IDM_IWD_EDIT_DOCUMENT )
#define AWD_IWD_ADD_IMAGE_PAGE     MAKEAWDMSG( AWD_MF_SOURCE, IDM_IWD_ADD_IMAGE_PAGE )
#define AWD_IWD_DELETE_IMAGE_PAGE  MAKEAWDMSG( AWD_MF_SOURCE, IDM_IWD_DELETE_IMAGE_PAGE )
#define AWD_IWD_SAVE_DOCUMENT      MAKEAWDMSG( AWD_MF_SOURCE, IDM_IWD_SAVE_DOCUMENT )
#define AWD_IWD_CLOSE_DOCUMENT     MAKEAWDMSG( AWD_MF_SOURCE, IDM_IWD_CLOSE_DOCUMENT )
#define AWD_IWD_RESET              MAKEAWDMSG( AWD_MF_SOURCE, IDM_IWD_RESET )
#define AWD_IWD_INVERT             MAKEAWDMSG( AWD_MF_SOURCE, IDM_IWD_INVERT )
#define AWD_IWD_PAGE_UP            MAKEAWDMSG( AWD_MF_SOURCE, IDM_IWD_PAGE_UP )
#define AWD_IWD_PAGE_DOWN          MAKEAWDMSG( AWD_MF_SOURCE, IDM_IWD_PAGE_DOWN )
#define AWD_IWD_ZOOM_IN            MAKEAWDMSG( AWD_MF_SOURCE, IDM_IWD_ZOOM_IN )
#define AWD_IWD_ZOOM_OUT           MAKEAWDMSG( AWD_MF_SOURCE, IDM_IWD_ZOOM_OUT )
#define AWD_IWD_ROTATE_RIGHT       MAKEAWDMSG( AWD_MF_SOURCE, IDM_IWD_ROTATE_RIGHT )
#define AWD_IWD_ROTATE_LEFT        MAKEAWDMSG( AWD_MF_SOURCE, IDM_IWD_ROTATE_LEFT )
#define AWD_IWD_QUERY_SETTINGS     MAKEAWDMSG( AWD_MF_SOURCE, IDM_IWD_QUERY_SETTINGS )
#define AWD_IWD_MINIMIZE           MAKEAWDMSG( AWD_MF_SOURCE, IDM_IWD_MINIMIZE )
#define AWD_IWD_RESTORE            MAKEAWDMSG( AWD_MF_SOURCE, IDM_IWD_RESTORE )
#define AWD_IWD_SET_MODE           MAKEAWDMSG( AWD_MF_SOURCE, IDM_IWD_SET_MODE )
#define AWD_IWD_QUERY_MODE         MAKEAWDMSG( AWD_MF_SOURCE, IDM_IWD_QUERY_MODE )
#define AWD_IWD_QUERY_PAGE_NO      MAKEAWDMSG( AWD_MF_SOURCE, IDM_IWD_QUERY_PAGE_NO )
#define AWD_IWD_PING_SERVER        MAKEAWDMSG( AWD_MF_SOURCE, IDM_IWD_PING_SERVER )
#define AWD_IWD_INSERT_AFTER       MAKEAWDMSG( AWD_MF_SOURCE, IDM_IWD_INSERT_AFTER )
#define AWD_IWD_INSERT_BEFORE      MAKEAWDMSG( AWD_MF_SOURCE, IDM_IWD_INSERT_BEFORE )
#define AWD_IWD_INSERT_OVERLAY     MAKEAWDMSG( AWD_MF_SOURCE, IDM_IWD_INSERT_OVERLAY )

#define AWD_IWD_TERMINATE          MAKEAWDMSG( AWD_MF_SOURCE, IDM_IWD_TERMINATE )
#define AWD_IWD_MINIMIZE           MAKEAWDMSG( AWD_MF_SOURCE, IDM_IWD_MINIMIZE )

#define AWD_IWD_FOREGROUND         MAKEAWDMSG( AWD_MF_SOURCE, IDM_IWD_FOREGROUND )

#define AWD_OBJECT_RELATION_CREATED MAKEAWDMSG( AWD_MF_PUBLIC | AWD_MF_CASE | AWD_MF_TRANS | AWD_MF_FOLDER, IDM_OBJ_CREATE_RELATION )
#define AWD_SRC_ANNOTATION_CHANGED MAKEAWDMSG( AWD_MF_PUBLIC | AWD_MF_SOURCE, IDM_SRC_ANNOTATION_CHANGED )
#define AWD_SRC_CLOSED_IN_IMGWN    MAKEAWDMSG( AWD_MF_PUBLIC | AWD_MF_SOURCE, IDM_SRC_CLOSED_IN_IMGWN )

#define AWD_USERMSG                MAKEAWDMSG( AWD_MF_PUBLIC | AWD_MF_ALL, IDM_USER )

#endif
