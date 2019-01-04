#ifndef AWDSTRCT_H
#define AWDSTRCT_H

#pragma pack( 1 )

#define QUEUE_LEN 8
#define UNIT_LEN 10
#define STATUS_LEN 10
#define WRK_LEN 10
#define OBJID_LEN 12

//ษอออออออออออออออออออป
//บ AWD object fields บ
//ศอออออออออออออออออออผ

#define AWD_CRDATTIM_FIELD    "CRDA"
#define AWD_RECORDCD_FIELD    "RECO"
#define AWD_CRNODE_FIELD      "CRNO"
#define AWD_OWNERNODE_FIELD   "OWNE"

#define AWD_LOCKSTAT_FIELD    "LOCK"

//ษอออออออออออออออออป
//บ AWD work fields บ
//ศอออออออออออออออออผ

#define AWD_QUEUE_FIELD       "QUEU"
#define AWD_STATUS_FIELD      "STAT"
#define AWD_UNIT_FIELD        "UNIT"
#define AWD_WRKTYPE_FIELD     "WRKT"
#define AWD_PRIORITY_FIELD    "PRTY"
#define AWD_INCREASE_FIELD    "INCR"
#define AWD_VI_FIELD          "VIFL"
#define AWD_SUSP_FIELD        "SUSP"
#define AWD_AMOUNT_TYPE_FIELD "AMTT"
#define AWD_AMOUNT_FIELD      "AMTV"

//ษอออออออออออออออออออป
//บ AWD source fields บ
//ศอออออออออออออออออออผ

#define AWD_ARCHIVE_BOX_FIELD    "ARCB"
#define AWD_ARCHIVE_PAGE_FIELD   "ARCP"
#define AWD_CREATE_STATION_FIELD "CRST"
#define AWD_CREATE_USERID_FIELD  "CRUS"
#define AWD_OBJTYPE_FIELD        "OBJT"
#define AWD_RECV_DATE_FIELD      "RCDA"
#define AWD_OBJECTFMT_FIELD      "OBJF"
#define AWD_OPTSTAT_FIELD        "OPTS"
#define AWD_OBJECTID_FIELD       "OBJI"
#define AWD_REVISEFLAG_FIELD     "REVI"
#define AWD_SECLEVEL_FIELD       "SECL"
#define AWD_MAILTYPE_FIELD       "MAIL"

//ษอออออออออออออออออออป
//บ AWD folder fields บ
//ศอออออออออออออออออออผ

#define AWD_FLDTYPE_FIELD        "FOLD"

/* awd work object structure */

typedef struct _awdwrkobj
   {
   char  unitcd[10];
   char  wrktype[10];
   char  statcd[10];
   char  queuecd[8];
   char  prty[3];
   char  increase[3];
   char  viflag;
   char  suspflag;
   char  amounttype;
   char  amount[17];                   /* 13.4 */
   } AWDWRKOBJ, *PAWDWRKOBJ;

/* awd source object structure */

typedef struct _awdsrcobJ
   {
   char  crstation[8];
   char  cruserid[8];
   char  rcdattim[26];
   char  objectfmt;
   char  mailtype;
   char  archivbox[7];
   char  archivpage[5];
   char  optstat;
   char  objectid[12];
   char  unitcd[10];
   char  objtype[10];
   char  reviseflag;
   char  seclevel[3];
   } AWDSRCOBJ, *PAWDSRCOBJ;

/* awd folder object structure */

typedef struct _awdfldobj
   {
   char crstation[8];
   char cruserid[8];
   char unitcd[10];
   char fldtype[10];
   } AWDFLDOBJ, *PAWDFLDOBJ;

/* awd object key structure */

#define AWDFAXFLAG
typedef struct _awdobjkey
   {
   char crdattim[ 26 ];
   char recordcd;
   char crnode[ 2 ];
   }  AWDOBJKEY,*PAWDOBJKEY;

typedef struct _awdlobcall
   {
   char exthost[8];
   char extparm[8];
   char extdll[8];
   char extproc[33];
   } AWDLOBCALL,*PAWDLOBCALL;

typedef struct _awdobj
   {
   char comment;                      /* y,n if object has comments */
   char relation;                     /* 1,2,3... relationship stuff */
   char item_selected;                /* selected for work */
   char relatrecordtype[3];            // actual awd relation code to parent
   char relatcrdattim[26];             // relationship date time

   AWDOBJKEY awdobjkey;                /* key information */

   char  ownernode[ 2 ];               /* owner node information */

   union
      {
      AWDSRCOBJ awdsrcobj;             /* source object information */
      AWDWRKOBJ awdwrkobj;             /* work object information */
      AWDFLDOBJ awdfldobj;             // folder object information
      }  awddata;

   char existflag;                     // user can see object exists
   char viewflag;                      // user can view object
   char updateflag;                    // user can update object
   char wrkselflag;                    // user can work select object
   char lockstat[8];                   // userid who locked record
   char csdscreen[12];                 // csd screen id for object
   char icobjectid[12];                // icon id for object
   char autoflags[30];                 // auto flags of object

   AWDLOBCALL AwdLobCall[4];

   char inxfld01[ 10 ];
   char inxfld02[ 21 ];
   char inxfld03[ 25 ];
   char inxfld04[ 30 ];
   } AWDOBJ, *PAWDOBJ;

/* awd lob data structure */

typedef struct _awd_lob_data
   {
   char   seqnbr[ 3 ];
   char   dataname[ 4 ];
   char   datavalue[ 75 ];
   unsigned short datalength;
   }  AWDLOBDATA,*PAWDLOBDATA;

typedef struct _awd_lob_data_old
  {
   char   seqnbr[ 3 ];
   char   dataname[ 4 ];
   char   datavalue[ 75 ];
   }  AWDLOBDATAOLD,*PAWDLOBDATAOLD;


/* awd lob array structure */

typedef struct _awd_lob_array
   {
   unsigned short usCount;
   PAWDLOBDATA pAwdLobData;
   }  AWDLOBARRAY, *PAWDLOBARRAY;

struct XXLIST_DEF
{
    char *data;
    struct XXLIST_DEF *next;
    struct XXLIST_DEF *prev;
};
typedef struct XXLIST_DEF XXLIST;

struct XLIST_DEF
{
    int datasize;
    int koffset;
    int keylen;
    int variable;
    long int count;
    XXLIST *head, *tail, *cur;
};
typedef struct XLIST_DEF XLIST;
typedef struct XLIST_DEF * PXLIST;

typedef struct _awdfld
   {
   unsigned char dataname[ 4 ];
   unsigned char fldformat;
   unsigned char fldlength[ 3 ];
   unsigned char decimals[ 3 ];
   unsigned char fldmask[ 75 ];
   unsigned char fldclass[ 10 ];
   unsigned char reqflag;
   unsigned char fldtype;            // 1-AWD Field           2-Single LOB Field
                             // 3-AWD Derived Field   4-Remote Field
                             // 5-Group Field

   unsigned char preproc[ 33 ];
   unsigned char predll[ 8 ];
   unsigned char postproc[ 33 ];
   unsigned char postdll[ 8 ];
   unsigned char validproc[ 33 ];
   unsigned char validdll[ 8 ];
   unsigned char listproc[ 33 ];
   unsigned char listdll[ 8 ];
   unsigned char uniqueness;
   unsigned char groupflag;
   unsigned char groupname[ 4 ];
   unsigned char groupseq;
   unsigned char v14name[ 10 ];
   unsigned char v21name[ 10 ];
   unsigned char inxflag;
   unsigned char inxfldname[ 10 ];
   unsigned char csdflags[5];
   unsigned char mediumname[ 20 ];
   unsigned char helptext[ 78 ];
   } AWDFLD, * PAWDFLD;

typedef struct _keydata
{
  unsigned char  crdattim[ 26 ];          // Create date and time
  unsigned char  recordcd[ 01 ];          // Record code ex: c,f,o,t - case,folder,etc...
  unsigned char  crnode[ 02 ];            // Create node
} KEYDATA, *PKEYDATA;

typedef struct _awddata
{
  KEYDATA  KeyData;               // Key data information
  XLIST    *pxlData;              // Pointer to linked list of the data
} AWDDATA, *PAWDDATA;


/********************************************************/
/**  Define structure for edit field mask and options  **/
/********************************************************/

typedef struct _editmask
{
  char     *pszEditMask;
  BOOL      fContainsSpecialchars;
  BOOL      fStripSpecialchars;
  unsigned short    usFirstchar;
  unsigned short    usMaskLength;
  unsigned short    usDecimals;
  unsigned long     ulFieldType;         // TEXT, DATE, CURRENCY, TIME
  BOOL      fFloatingSign;
  unsigned long     ulReserved1;
  unsigned long     ulReserved2;
  unsigned short    usReserved1;
  unsigned short    usReserved2;
} EDITMASK, *PEDITMASK;


typedef struct _currencyinfo
{
  short     DollarLength;       // number of digits to the left of the decimal
  short     Precision;          // number of digits to the right of the decimal
  char      szSign[5];          // string that represents the currency sign
  char      szThousands;        // character used to seperate thousands
  char      szDecimal;          // character used to seperate decimal portion
  BOOL      fSignOnLeft;        // TRUE if they want the sign on the left; FALSE = right
  BOOL      fFloatingSign;      // TRUE if they want the sign to float ( left side only )
  BOOL      fSignSeperator;     // TRUE if they want a one SPACE ( " " ) seperation between
                                // the sign and the value ( either side )
} CURRENCYINFO, *PCURRENCYINFO;


// this is in csdapi.h and awdcsd.xh - these are duplicates and couse problems for 
// those using the CSD exits

#ifdef _NEVER_USE_SEE_AWDCSD_XH
typedef struct _csdpmdata
{
   unsigned long  x;
   unsigned long  y;
   unsigned long  cx;
   unsigned long  cy;
   unsigned long  ulClass;
   unsigned long  ulStyle;
   unsigned short usId;
} CSDPMDATA, *PCSDPMDATA;


typedef struct _csdfld
 {
   EDITMASK   editmask;       // this must remain first so that the editmask
                              // functions can reach it by typecasting as an
                              // EDITMASK instead of a CSDFLD...rjf 4/20/93
   CSDPMDATA  csdPMData;
   void***    pfnPrevious;    // this is used by the CSD Tool to track the
                              // previous function when subclassing
   unsigned char      dataname[ 4 ];
   BOOL       usefldmask;
   unsigned char      fldmask[ 75 ];
   unsigned char      reqflag;
   BOOL       usepreproc;
   unsigned char      preproc[ 33 ];
   unsigned char      predll[ 8 ];
   BOOL       usepostproc;
   unsigned char      postproc[ 33 ];
   unsigned char      postdll[ 8 ];
   BOOL       usevalidproc;              // If set then use the dynamic ext
   unsigned char      validproc[ 33 ];           // If a value in here and usevalidproc
   unsigned char      validdll[ 8 ];             //   not set then use this ELSE dont call any
   BOOL       uselistproc;
   unsigned char      listproc[ 33 ];
   unsigned char      listdll[ 8 ];
   unsigned char      mediumname[ 20 ];
   unsigned char      helptext[ 78 ];
} CSDFLD, *PCSDFLD;

/*----------------------------------------------------------------------------*\
|* CSDUSERBUTTONATTR is a struture that is only used if the control on
|* the csd is a User 'Magic' Button.  It is overlayed on the listproc
|* field of the CSDFLD structure.
\*----------------------------------------------------------------------------*/
typedef struct _csduserbuttonattr
   {
   char  junk[29];
   long  style;
   } CSDUSERBUTTONATTR, *PCSDUSERBUTTONATTR;

typedef struct _csdpage
   {
   CSDPMDATA  csdPMData;
   unsigned char      szTitle[ 50 ];
   unsigned char      okproc[ 33 ];
   unsigned char      okdll[ 8 ];
   unsigned char      cancelproc[ 33 ];
   unsigned char      canceldll[ 8 ];
   unsigned char      initproc[ 33 ];
   unsigned char      initdll[ 8 ];
   unsigned short     usPageNumber;
   unsigned short     usNumControls;
   } CSDPAGE, *PCSDPAGE;

typedef struct _csdscreen
   {
   unsigned short   usVersion;
   unsigned short   usNumPages;
   unsigned short   usCsdType;
   } CSDSCREEN, *PCSDSCREEN;

// CSD User 'Magic' Button Exit.
//

#ifndef SOM_AWDBase_xh
   #ifdef __cplusplus
      class  AWDBase;
   #else
      #define AWDBase void
   #endif /* end of C++ */
#endif

typedef struct _csd_userbutton_exit
{
   HWND     hwndCSD;                   /* handle to CSD                       */
   AWDBase* pAwdObj;                   /* ptr to AWD Object (SOM)             */
} CSD_USERBUTTON_EXIT, *PCSD_USERBUTTON_EXIT;

#endif //_NEVER_USE_SEE_AWDCSD_XH


/* Data to pass to dialogs so they have all the info they need to display */

typedef struct _awddlgdata
{
  PAWDOBJKEY pawdobjkey;            /* key information */
  PAWDWRKOBJ pawdwrkobj;            /* info for a work object */
  PAWDSRCOBJ pawdsrcobj;            /* info for a source object */
  char       icontext[ 200 ];       /* Icon text */
} AWDDLGDATA, *PAWDDLGDATA;

/* what awdloaddlg passes to all dialogs loaded by it */

typedef struct _dlginit
   {
   unsigned short   usSize;                    // size of dlginit
   PVOID    pvStuff;                   // pointer to whatever, usually key
   }  DLGINIT, *PDLGINIT;


/* what awdloaddlg passes to all dialogs loaded by it */

#pragma pack()
#endif  // AWDSTRCT_H
