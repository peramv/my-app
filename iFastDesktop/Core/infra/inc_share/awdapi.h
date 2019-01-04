#ifndef AWDAPI_H
#define AWDAPI_H

#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
#include <string.h>

#define VC_EXTRALEAN        // Exclude rarely-used stuff from Windows headers
#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions

#ifndef AWDSTRCT_H
   #include <awdstrct.h>
#endif

/*------------------------------ CONSTANTS ---------------------------------*/
#define NOT_MODAL                            0
#define APP_MODAL                            1

#ifndef EXPENTRY
  #define EXPENTRY                           APIENTRY
#endif

#define PHWND                                HWND*
#define PSHORT                               short*

// SIZE_OFs
#define SIZEOF_AWD_DATE                      10
#define SIZEOF_AWD_TIME                      15
#define SIZEOF_AWD_STAMP                     26
#define SIZEOF_AWD_DATETIME                  26
#define SIZEOF_AWD_OPERID                    8
#define SIZEOF_AWD_STRING                    133   // Same size for admin apis
#define SIZEOF_AWD_USERID                    8
#define SIZEOF_AWD_PASSWORD                  8
#define SIZEOF_AWD_FLDNAMETYPE               6
#define SIZEOF_AWD_DATANAME                  4
#define SIZEOF_AWD_OBJECTID                  12
#define SIZEOF_AWD_DATAVALUE                 75
#define SIZEOF_AWD_COMPARATOR                2
#define SIZEOF_AWD_DOCID                     12
#define SIZEOF_AWD_PATH                      CCHMAXPATH
#define SIZEOF_AWD_COUNTRY                   3
#define SIZEOF_AWD_CREATENODE                2
#define SIZEOF_AWD_OPTIONNAME                20
#define SIZEOF_AWD_OPTIONVALUE               75
#define SIZEOF_AWD_SEQUENCENUM               3
#define SIZEOF_AWD_QUEUE                     8
#define SIZEOF_AWD_STATUS                    10
#define SIZEOF_AWD_UNITCD                    10
#define SIZEOF_AWD_WORKTYPE                  10
#define SIZEOF_AWD_SOURCETYPE                10
#define SIZEOF_AWD_FOLDERTYPE                10
#define SIZEOF_AWD_SUSPENDREASON             75
#define SIZEOF_AWD_RECORDCD                  1
#define SIZEOF_AWD_VIEWNAME                  8
#define SIZEOF_AWD_VERSION                   5

#define SIZEOF_AWDOPER_STATUS                1
#define SIZEOF_AWDOPER_CLASSIFY              20
#define SIZEOF_AWDOPER_LASTNAME              20
#define SIZEOF_AWDOPER_FIRSTNAME             20
#define SIZEOF_AWDOPER_GROUPCD               10
#define SIZEOF_AWDOPER_PQFLAG                1
#define SIZEOF_AWDOPER_PHONE                 15
#define SIZEOF_AWDOPER_WORKSELECT            1
#define SIZEOF_AWDOPER_FAXNUM                25
#define SIZEOF_AWDOPER_FAXDEPT               50
#define SIZEOF_AWDOPER_FAXLISTID             10
#define SIZEOF_AWDOPER_SECURITYLEV           3

// Awd buttons
#define AWD_HELP                             ID_CONTEXT_HELP
#define AWD_OK                               IDOK
#define AWD_CANCEL                           ID_APP_EXIT
#define AWDAPI_HELP                          AWD_HELP
#define AWDAPI_OK                            AWD_OK
#define AWDAPI_CANCEL                        AWD_CANCEL

// Awd object types
#define AWDAPI_SOURCE                        100
#define AWDAPI_TRANSACTION                   101
#define AWDAPI_CASE                          102
#define AWDAPI_FOLDER                        103
#define AWDAPI_WORK                          104

// Lookup comparators.
#define AWDAPI_EQUAL                         "= "
#define AWDAPI_NOT_EQUAL                     "<>"
#define AWDAPI_GREATERTHAN                   "> "
#define AWDAPI_GREATERTHAN_EQUAL             ">="
#define AWDAPI_LESSTHAN                      "< "
#define AWDAPI_LESSTHAN_EQUAL                "<="
#define AWDAPI_LIKE                          "= "

// View return codes
#define AWDRC_RELATIONSHIP_EXISTS            19

// Csd load options
#define CSD_LOAD_CREATE_WORK                 0
#define CSD_LOAD_DISPLAY_WORK                1
#define CSD_LOAD_UPDATE_WORK                 2
#define CSD_LOAD_CREATE_SOURCE               3
#define CSD_LOAD_DISPLAY_SOURCE              4
#define CSD_LOAD_UPDATE_SOURCE               5
#define CSD_LOAD_CREATE_FOLDER               6
#define CSD_LOAD_DISPLAY_FOLDER              7
#define CSD_LOAD_UPDATE_FOLDER               8
#define CSD_LOAD_CREATE_WORK_BATCH           9
#define CSD_LOAD_CREATE_SOURCE_BATCH         10
#define CSD_LOAD_UPDATE_WORK_INVISIBLE       11
#define CSD_LOAD_CLONE_WORK                  12
#define CSD_LOAD_LOOKUP                      13

// Container item popup menu items
#define AWD_CONT_MENUITEM_PRINT              106
#define AWD_CONT_MENUITEM_FAX                107
#define AWD_CONT_MENUITEM_CLONE              108
#define AWD_CONT_MENUITEM_QUALITY            110
#define AWD_CONT_MENUITEM_SUSPEND            112
#define AWD_CONT_MENUITEM_DETAIL             113
#define AWD_CONT_MENUITEM_COMMENTS           114
#define AWD_CONT_MENUITEM_HISTORY            115
#define AWD_CONT_MENUITEM_SOURCE             116
#define AWD_CONT_MENUITEM_PROCESS            119
#define AWD_CONT_MENUITEM_PARENT             134
#define AWD_CONT_MENUITEM_CHILDREN           135
#define AWD_CONT_MENUITEM_CHANGEQ            142
#define AWD_CONT_MENUITEM_EXPAND             143
#define AWD_CONT_MENUITEM_CLONE_SOURCE       146
#define AWD_CONT_MENUITEM_SOURCE_AND_DETAIL  147
#define AWD_CONT_MENUITEM_DELETE             148
#define AWD_CONT_MENUITEM_CASEPRT            149

// Container API User Messages
#define UM_AWD_CONT_GETWORK                  WM_USER + 665

// Container return Codes
#ifndef NO_ERROR
  #define NO_ERROR                            0
#endif
#define AWD_ERROR                            -1
#define AWD_INVALID_PARENT_KEY               -2
#define AWD_INVALID_CHILD_KEY                -3
#define AWD_KEY_NOT_FOUND                    -4
#define AWD_PARENT_KEY_NOT_FOUND             -5
#define AWD_CHILD_KEY_NOT_FOUND              -6
#define AWD_RELATIONSHIP_NOT_CREATED         -7
#define AWD_RELATIONSHIP_EXISTS              -8
#define AWD_INVALID_CONTAINER                -9
#define AWD_INVALID_RELATIONSHIP             -10
#define AWD_RELATIONSHIP_NOT_DELETED         -11
#define AWD_INVALID_KEY                      -12
#define AWD_INVALID_OBJECT                   -13
#define AWD_RELATIONSHIP_NOT_EXISTS          -14
#define AWD_MEMSIZE                          -15
#define AWDAPI_NONE                          -16
#define AWD_UNABLE_TO_LOCK                   -17
#define AWD_INVALID_SIZE                     -18
#define AWD_LOB_NOTFOUND                     -19
#define AWD_INVALID_DATANAME                 -20
#define AWD_INVALID_FLD_FOR_OBJTYPE          -21
#define AWD_INVALID_DATAVALUE                -22
#define AWD_VALIDPROC_LOADFAIL               -23
#define AWD_VALIDPROC_NOTFOUND               -24
#define AWD_OBJ_NOTLOCKED_BYCONTAINER        -25
#define AWD_NO_CONTAINERS_FOUND              -26
#define AWD_MENUITEM_NOT_AVAILABLE           -27
#define AWD_INVALID_OBJECT_TYPE              -28
#define AWD_OBJECT_LOCKED_TO_USER            -29
#define AWD_OBJECT_LOCKED_TO_OTHER_USER      -30
#define AWD_USER_ALREADY_LOGGEDON            -31
#define AWD_USER_NOT_LOGGEDON                -32



// Error codes returned from AwdApiGetLastError
//
#define AWD_ERROR_INVALID_APP                      -50
#define AWD_ERROR_NO_MEMORY                        -51
#define AWD_ERROR_BAD_PARAM                        -52
#define AWD_ERROR_RESLIB_NOT_LOADED                -53
#define AWD_ERROR_INVALID_HELPER                   -54
#define AWD_ERROR_INTERNAL_FUNCTION_CALL_FAILED    -55
#define AWD_ERROR_NO_WINDOWS_OPENED                -56
#define AWD_ERROR_WINDOW_NOT_FOUND                 -57
#define AWD_ERROR_IMGWND_NOT_READY                 -58
#define AWD_ERROR_INVALID_DATA_FORALL              -59
#define AWD_ERROR_INVALID_WINDOW_HANDLE            -60
#define AWD_ERROR_SERVICE_UNAVAILABLE              -61
#define AWD_ERROR_INVALID_CSD                      -62
#define AWD_ERROR_VIEW_FAILURE                     -63
#define AWD_ERROR_COMM_FAILURE                     -64
#define AWD_ERROR_INVALID_OBJTYPE                  -65
#define AWD_ERROR_SYSTEM_OPTION                    -66
#define AWD_ERROR_IMGWND_START_FAILURE             -67
#define AWD_ERROR_OPENDOC_FAILURE                  -68
#define AWD_ERROR_INVALID_DICT                     -69
#define AWD_ERROR_INVALID_TREE                     -70
#define AWD_ERROR_INVALID_FIELD                    -71
#define AWD_ERROR_CANNOT_LOAD_CONT                 -72
#define AWD_ERROR_CANNOT_ACCESS_SMEMORY            -73
#define AWD_ERROR_WAITING_FOR_DATA                 -74
#define AWD_ERROR_CONTAINER_NOT_FOUND              -75
#define AWD_ERROR_INVALID_CONTMODE                 -76
#define AWD_ERROR_INVALID_MSGQ                     -77
#define AWD_ERROR_NO_SECURITY_ACCESS               -78
#define AWD_ERROR_CANNOT_LOCK_OBJECT               -79
#define AWD_ERROR_RECORDCD_REQUIRED                -80
#define AWD_ERROR_INVALID_USERID                   -81
#define AWD_ERROR_CANNOT_OPEN_CONTAINER            -82
#define AWD_ERROR_TOO_MANY_PROCESS_CONTS           -83
#define AWD_ERROR_OBJECT_NOT_LOCKED                -84
#define AWD_ERROR_MFC_ERROR                        -85



// OPTIONS: Awd container deletion, queryitem, access, expand, etc.
#define AWD_ITEM                             30    // deletion & query & select
#define AWD_PARENT                           31    // query & expand
#define AWD_ALLITEMS                         32    // deletion only
#define AWD_ALLCHILDREN                      33    // deletion & query
#define AWD_ALLSIBLINGS                      34    // query only
#define AWD_BREAK_RELATION                   35    // deletion only
#define AWD_GETNUM_CHILDREN                  36    // query only
#define AWD_GETNUM_DESCENDANTS               37    // query only
#define AWD_GETNUM_SIBLINGS                  38    // query only
#define AWD_GETNUM_ITEM                      39    // query only
#define AWD_SELECTEDITEM                     40    // query only
#define AWD_FIRSTCHILD                       41    // query & select
#define AWD_NEXTITEM                         42    // query & select
#define AWD_NEXTIMMEDIATEITEM                43    // query & select
#define AWD_ALLDECENDANTS                    44    // query only
#define AWD_REFRESH_ICONTEXT                 45    // access item
#define AWD_QUERY_ICONTEXT                   46    // access item
#define AWD_SET_ICONTEXT                     47    // access item
#define AWD_CONTRACT_ITEM                    48    // access item
#define AWD_CONTAINER_MODE                   49    // access cont
#define AWD_LOCK_OBJECT                      50    // access item
#define AWD_UNLOCK_OBJECT                    51    // access item
#define AWD_EXPAND_ITEM                      52    // access item
#define AWD_QUERY_CONTAINER_MODE             53    // access cont
#define AWD_SET_CONTAINER_VIEW               54    // access cont
#define AWD_QUERY_CONTAINER_VIEW             55    // access cont
#define AWD_CHILD                            58    // expand only
#define AWD_BOTH                             59    // expand only
#define AWD_UNRELATED                        60    // non-error return code
#define AWD_SIBLING                          61    // non-error return code
#define AWD_NEXTUNRELATED                    62    // select only
#define AWD_NEXTWORKSELECTED                 63    // select only
#define AWD_SELECT_ITEM                      64    // select only
#define AWD_DETERMINE_SEARCH                 65    // lookup only
#define AWD_USE_SQL                          66    // lookup only
#define AWD_USE_RECORD_AT_A_TIME             67    // lookup only
#define AWD_UPDATE_ITEM                      68    // refresh item
#define AWD_QUERY_LOCKFLAG                   69    // access item
#define AWD_LOCKFLAG_SET                     70    // non-error return code
#define AWD_CONTINUE_VIEW                    70    // non-error return code
#define AWD_CLICK_CONTAINER_OKBUTTON         71    // click contbutt
#define AWD_MORE_RECORDS                     72    // non-error return code
#define AWD_ALL_RECORDS                      73    // non-error return code
#define AWD_DBLCLK_ITEM                      74    // access item
#define AWD_SELECT_CONT_MENUITEM             75    // access item
#define AWDAPI_ALL                           76    // query & access item
#define AWD_GETNUM_ALL                       77    // query
#define AWD_ROOT                             78    // insert only


// Awd container views
#define AWD_TREE                             CV_TREE
#define AWD_ICON                             CV_ICON
#define AWD_DETAIL                           CV_DETAIL

// Awd container modes
#define AWD_CONT_PROCESS                     0
#define AWD_CONT_PERSONAL_QUEUE              1
#define AWD_CONT_LOOKUP                      2
#define AWD_CONT_CASE                        3
#define AWD_CONT_CREATE                      4
#define AWD_CONT_CHILD                       5
#define AWD_CONT_PARENT                      6
#define AWD_CONT_CREATE_WORK                 7
#define AWD_CONT_CREATE_SOURCE               8
#define AWD_CONT_CREATE_FOLDER               9
#define AWD_CONT_ALL                         10
#define AWD_CONT_EXE                         11
#define AWD_CONT_GENERIC                     12

// XLIST insert options
#define X_SORTED                             0
#define X_TOP                                1
#define X_END                                2

/*------------------------------ STRUCTURES --------------------------------*/
// Structure used to for data need to load a CSD
typedef struct _loadcsd
{
   HWND hwndParent;              // required by all
   HWND hwndOwner;               // required by all
   HWND hwndNotify;              // required by all
   ULONG ulOkMsg;                // required by all
   ULONG ulCancelMsg;            // required by all
   HWND hwndImage;               // required by all except CSD_LOOKUP
   PVOID pvImageWindow;          // required by all except CSD_LOOKUP
   PAWDOBJ pAwdObj;              // required by all except CSD_LOOKUP
   PXLIST pxlDocs;
   PAWDLOBARRAY pAwdLobArray;    // required by CSD_CREATE_WORKOBJ,
                                 //             CSD_CREATE_SRCOBJ,
                                 //             CSD_CREATE_FLDOBJ,
                                 //             CSD_CLONE_WORKOBJ,
                                 //             CSD_CREATE_SRC_OBJBATCH
                                 //             CSD_CREATE_WORK_OBJBATCH
   PSZ pszFileName;              // required by CSD_CREATE_SOURCE only
   PAWDOBJ pParentAwdObj;        // required by CSD_CLONE_WORKOBJ only
   PUCHAR pucKey;                // required by CSD_CREATE_SRC_OBJBATCH,
                                 //             CSD_CREATE_WORK_OBJBATCH
   PSZ pszCsdName;               // required by CSD_LOOKUP only
}  LOADCSD, *PLOADCSD;

// Used to return drive data
typedef struct
{
  CHAR cDrive;                   // drive letter
  CHAR cType;                    // drive type 'O'ptical or 'D'asd
} DRIVE_DATA, *PDRIVE_DATA;

// Originally in awdview.h
//
#ifndef AWDVIEW_H
  typedef struct _search_criteria
  {
     UCHAR dataname[4];
     UCHAR wildcard;
     UCHAR comparator[2];
     UCHAR datavalue[75];
  } SEARCH_CRITERIA;
#endif


/*------------------------------- MACROS -----------------------------------*/

#define AwdApiTrimSpaces( psz ) \
   {                                                      \
      long i;                                             \
      for(i = strlen(psz)-1; i>=0; --i)                   \
         if ( psz[i] == ' ' )                             \
            psz[i]=0x00;                                  \
         else if ( psz[i] != 0x00 )                       \
            i=-1;                                         \
   }  /* end of AwdApiTrimSpaces() macro */

#define AwdApiMemSpace(psz, l)   memset( psz, ' ', l );
#define AwdApiMemZero(psz, l)    memset( psz, '0', l );
#define AwdApiMemNull(psz, l)    memset( psz, 0x00, l );

#define AwdApiConvertCountry( ulCountry, szCountry )            \
     if ( ((unsigned long)ulCountry) < 1000 )                   \
        sprintf( szCountry,"%3.3u", (unsigned long)ulCountry ); \
     else                                                       \
        strcpy( szCountry, "001" )

/*------------------------------ PROTOTYPES --------------------------------*/
#ifdef __cplusplus
   extern "C"  {
#endif  // __cplusplus
                             // ***** Dll Initialization
                             //
// We have to prototype this accoring to the documentation.
//
//ÛÛÿ04-14-97ÿ11:39ÿÛÛBOOL WINAPI _CRT_INIT(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpReserved);
//ÛÛÿ04-14-97ÿ11:38ÿÛÛBOOL WINAPI AwdApiDllMain( HINSTANCE hInstance,
//ÛÛÿ04-14-97ÿ11:38ÿÛÛ                           DWORD ul_reason_for_call, LPVOID lpReserved );

                             // ***** Container APIs
                             //
BOOL EXPENTRY AwdApiCloseContainer( HWND hwndCont, PVOID pReserved );
HWND EXPENTRY AwdApiOpenContainer( HWND hwndParent,
                              USHORT usMode, PVOID pReserved );

SHORT EXPENTRY AwdApiDeleteItem( HWND hwndCont,
                            PAWDOBJKEY pAwdObjKey,
                            USHORT usItem, PVOID pReserved );

SHORT EXPENTRY AwdApiCreateRelationship( HWND hwndCont,
                                    PAWDOBJKEY pParentKey,
                                    PAWDOBJKEY pChildKey, PVOID pReserved );

USHORT EXPENTRY AwdApiQueryContainerTitle( HWND hwndCont, USHORT usSize,
                                      PSZ pszTitle, PVOID pReserved );


SHORT EXPENTRY AwdApiQueryContainerMode( HWND hwndCont, PVOID pReserved );


BOOL EXPENTRY AwdApiGetAutoFlag( PVOID pReserved );
BOOL EXPENTRY AwdApiSetAutoFlag( BOOL flAutoFlag, PVOID pReserved );

USHORT EXPENTRY AwdApiQueryIconText( HWND hwndCont, PAWDOBJKEY pAwdObjKey,
                                USHORT usSize, PSZ pszText, PVOID pReserved );

BOOL EXPENTRY AwdApiContractContainerItem( HWND hwndCont,
                                      PAWDOBJKEY pAwdObjKey,
                                      PVOID pReserved );

HWND  EXPENTRY AwdApiQueryContainerHandle( HWND hwndDlg, PVOID pReserved );
HWND* EXPENTRY AwdApiFindContainer( PUSHORT pusTotal,
                                    USHORT usMode, PVOID pReserved );

SHORT EXPENTRY AwdApiQueryItem( HWND hwndCont,
                           PAWDOBJKEY pStartKey, PAWDOBJ pAwdObj,
                           USHORT usSize, USHORT usItem,
                           PUSHORT pusIndex, PVOID pReserved );

SHORT EXPENTRY AwdApiInsertItemKey( HWND hwndCont, PAWDOBJKEY pParentKey,
                               PAWDOBJKEY pAwdObjKey, BOOL fUpdateCount,
                               BOOL fLockFlag, PVOID pReserved );

SHORT EXPENTRY AwdApiInsertItem( HWND hwndCont, PAWDOBJKEY pParentKey,
                            PAWDOBJ pAwdObj, BOOL fUpdateCount,
                            BOOL fLockFlag, PVOID pReserved );

BOOL EXPENTRY AwdApiExpandContainerItem( HWND hwndCont, PAWDOBJKEY pAwdObjKey,
                                    USHORT usDirection, PVOID pReserved );

SHORT EXPENTRY AwdApiSelectItem( HWND hwndCont, PAWDOBJKEY pAwdObjKey,
                            USHORT usItem, USHORT usIndex, PVOID pReserved );

HWND EXPENTRY AwdApiLocateContainer( PAWDOBJ pAwdObj,
                                PSHORT psReturnCd, PVOID pReserved );

SHORT EXPENTRY AwdApiDoubleClickContainerItem( HWND hwndCont, PAWDOBJKEY pAwdObjKey,
                                          PVOID pReserved );

SHORT EXPENTRY AwdApiSelectMenuItemContainer( HWND hwndCont,
                                              PAWDOBJKEY pAwdObjKey,
                                              USHORT usMenuItem,
                                              PVOID pReserved );

                             // ***** Csd Stuff
                             //
HWND EXPENTRY AwdApiLoadCsd( PLOADCSD pLoadCsd, USHORT usCsdMode, PVOID pReserved );
PUCHAR* EXPENTRY AwdApiFieldsOnCsd( PAWDOBJ pAwdObj, USHORT usObjType,
                               PUSHORT pusTotal, PVOID pReserved );
BOOL EXPENTRY AwdApiCsdVerify( PAWDOBJ pAwdObj,
                               PAWDLOBARRAY pAwdLobArray, PVOID pReserved );

                             // ***** Miscellaneous APIs
                             //
BOOL EXPENTRY AwdApiLookup( HWND hwndNotify, ULONG ulMsg,
                            BOOL fContainer, CHAR cObjectType,
                            SEARCH_CRITERIA* pSearchCriteria,
                            USHORT usCount,
                            USHORT usSearchType, PVOID pReserved );

                             // ***** Object APIs
                             //
BOOL  EXPENTRY AwdApiCreateObject( PAWDOBJ pAwdObj, PAWDLOBARRAY pAwdLobArray,
                              USHORT usObjectType, BOOL fCreateLocked,
                              PCHAR pSource, UCHAR ucDrive, PVOID pReserved );

BOOL  EXPENTRY AwdApiLockObject( HWND hwndCont, PAWDOBJ pAwdObj,
                            BOOL bLock, PVOID pReserved );

SHORT EXPENTRY AwdApiRetrieveObject( PAWDOBJ pAwdObj,
                                     PAWDOBJKEY pAwdObjKey, PVOID pReserved );

PAWDOBJ EXPENTRY AwdApiRetrieveParents( PAWDOBJKEY pAwdObjKey, BOOL fContinue,
                                        PSHORT psReturnCd, PVOID pReserved );
#ifdef __cplusplus
   }  /* end of code block */
#endif  // __cplusplus

#endif
