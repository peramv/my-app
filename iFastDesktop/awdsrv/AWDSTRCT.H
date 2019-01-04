#ifndef AWDSTRCT_H
#define AWDSTRCT_H

#include "AWDCNV.H"

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
#define  AWD_COMMENT_FLAG     "COMF"

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
   CHAR  unitcd[10];
   CHAR  wrktype[10];
   CHAR  statcd[10];
   CHAR  queuecd[8];
   CHAR  prty[3];
   CHAR  increase[3];
   CHAR  viflag;
   CHAR  suspflag;
   CHAR  amounttype;
   CHAR  amount[17];                   /* 13.4 */
   } AWDWRKOBJ, *PAWDWRKOBJ;

/* awd source object structure */

typedef struct _awdsrcobJ
        {
   CHAR  crstation[8];
   CHAR  cruserid[8];
   CHAR  rcdattim[26];
   CHAR  objectfmt;
   CHAR  mailtype;
   CHAR  archivbox[7];
   CHAR  archivpage[5];
   CHAR  optstat;
   CHAR  objectid[12];
   CHAR  unitcd[10];
   CHAR  objtype[10];
   CHAR  reviseflag;
   CHAR  seclevel[3];
   } AWDSRCOBJ, *PAWDSRCOBJ;


/* awd folder object structure */

typedef struct _awdfldobj
   {
   CHAR crstation[8];
   CHAR cruserid[8];
   CHAR unitcd[10];
   CHAR fldtype[10];
   } AWDFLDOBJ, *PAWDFLDOBJ;

/* awd object key structure */

#define AWDFAXFLAG
typedef struct _awdobjkey
   {
   CHAR crdattim[ 26 ];
   CHAR recordcd;
   CHAR crnode[ 2 ];
        }  AWDOBJKEY,*PAWDOBJKEY;

typedef struct _awdlobcall
   {
   CHAR exthost[8];
   CHAR extparm[8];
   CHAR extdll[8];
   CHAR extproc[33];
   } AWDLOBCALL,*PAWDLOBCALL;

typedef struct _awdobj
   {
   CHAR comment;                      /* y,n if object has comments */
   CHAR relation;                     /* 1,2,3... relationship stuff */
   CHAR item_selected;                /* selected for work */
   CHAR relatrecordtype[3];            // actual awd relation code to parent
   CHAR relatcrdattim[26];             // relationship date time

   AWDOBJKEY awdobjkey;                /* key information */

   CHAR  ownernode[ 2 ];               /* owner node information */

   union
      {
      AWDSRCOBJ awdsrcobj;             /* source object information */
      AWDWRKOBJ awdwrkobj;             /* work object information */
      AWDFLDOBJ awdfldobj;             // folder object information
      }  awddata;

   CHAR existflag;                     // user can see object exists
   CHAR viewflag;                      // user can view object
   CHAR updateflag;                    // user can update object
   CHAR wrkselflag;                    // user can work select object
   CHAR lockstat[8];                   // userid who locked record
        CHAR csdscreen[12];                 // csd screen id for object
   CHAR icobjectid[12];                // icon id for object
   CHAR autoflags[30];                 // auto flags of object

   AWDLOBCALL AwdLobCall[4];

   CHAR inxfld01[ 10 ];
   CHAR inxfld02[ 21 ];
   CHAR inxfld03[ 25 ];
   CHAR inxfld04[ 30 ];
   } AWDOBJ, *PAWDOBJ;

/* awd lob data structure */

typedef struct _awd_lob_data
{
   CHAR   seqnbr[ 3 ];
   CHAR   dataname[ 4 ];
   CHAR   datavalue[ 75 ];
   USHORT datalength;
}  AWDLOBDATA,*PAWDLOBDATA;


typedef struct AWD_AWDLOBDATA
 {
 char  seqnbr[3];
 char  dataname[4];
 char  datavalue[75];
 unsigned short  datalength;
 } AWD_AWDLOBDATA;
typedef struct AWD_AWDLOBDATA* AWD_PAWDLOBDATA;


typedef struct _awd_lob_data_old
  {
   CHAR   seqnbr[ 3 ];
   CHAR   dataname[ 4 ];
   CHAR   datavalue[ 75 ];
   }  AWDLOBDATAOLD,*PAWDLOBDATAOLD;


/* awd lob array structure */

typedef struct _awd_lob_array
{
    USHORT usCount;
    PAWDLOBDATA pAwdLobData;
}  AWDLOBARRAY, *PAWDLOBARRAY;


typedef struct AWD_AWDLOBARRAY
 {
 unsigned short  usCount;
 AWD_PAWDLOBDATA pAwdLobData;
 } AWD_AWDLOBARRAY;
typedef struct AWD_AWDLOBARRAY* AWD_PAWDLOBARRAY;


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

/* awd object format structure */

typedef struct _awdobjectfmt
   {
   CHAR  objectfmt;
   CHAR  objectdesc[80];
   CHAR  createDLL[8];
   CHAR  viewDLL[8];
   CHAR  editDLL[8];
   CHAR  printDLL[8];
   CHAR  faxDLL[8];
   CHAR  convertDLL[8];
   }  AWDOBJECTFMT, *PAWDOBJECTFMT;

/* awd container source object structure */

typedef struct _cnrsrcobj
  {
	  void *  pvDocInfo;
     void  * pvAppInstance;
     PAWDOBJ pAwdObj;
     char    pszDLL[9];
     HMODULE hModule;
  } CNRSRCOBJ, * PCNRSRCOBJ;


typedef struct _awdfld
   {
   UCHAR dataname[ 4 ];
   UCHAR fldformat;
   UCHAR fldlength[ 3 ];
   UCHAR decimals[ 3 ];
   UCHAR fldmask[ 75 ];
   UCHAR fldclass[ 10 ];
   UCHAR reqflag;
   UCHAR fldtype;            // 1-AWD Field           2-Single LOB Field
                             // 3-AWD Derived Field   4-Remote Field
                             // 5-Group Field

   UCHAR preproc[ 33 ];
   UCHAR predll[ 8 ];
   UCHAR postproc[ 33 ];
   UCHAR postdll[ 8 ];
   UCHAR validproc[ 33 ];
   UCHAR validdll[ 8 ];
   UCHAR listproc[ 33 ];
   UCHAR listdll[ 8 ];
   UCHAR uniqueness;
   UCHAR groupflag;
   UCHAR groupname[ 4 ];
   UCHAR groupseq;
   UCHAR v14name[ 10 ];
   UCHAR v21name[ 10 ];
   UCHAR inxflag;
   UCHAR inxfldname[ 10 ];
   UCHAR csdflags[5];
   UCHAR mediumname[ 20 ];
   UCHAR helptext[ 78 ];
   } AWDFLD, * PAWDFLD;

typedef struct _keydata
{
  UCHAR  crdattim[ 26 ];          // Create date and time
  UCHAR  recordcd[ 01 ];          // Record code ex: c,f,o,t - case,folder,etc...
  UCHAR  crnode[ 02 ];            // Create node
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
  CHAR     *pszEditMask;
//  BOOL      fContainsSpecialChars;
  ULONG     fContainsSpecialChars;
//  BOOL      fStripSpecialChars;
  ULONG     fStripSpecialChars;
  USHORT    usFirstChar;
  USHORT    usMaskLength;
  USHORT    usDecimals;
  ULONG     ulFieldType;         // TEXT, DATE, CURRENCY, TIME
//  BOOL      fFloatingSign;
  ULONG     fFloatingSign;
  ULONG     ulReserved1;
  ULONG     ulReserved2;
  USHORT    usReserved1;
  USHORT    usReserved2;
} EDITMASK, *PEDITMASK;


typedef struct _currencyinfo
{
  SHORT     DollarLength;       // number of digits to the left of the decimal
  SHORT     Precision;          // number of digits to the right of the decimal
  CHAR      szSign[5];          // string that represents the currency sign
  CHAR      szThousands;        // character used to seperate thousands
  CHAR      szDecimal;          // character used to seperate decimal portion
  BOOL      fSignOnLeft;        // TRUE if they want the sign on the left; FALSE = right
  BOOL      fFloatingSign;      // TRUE if they want the sign to float ( left side only )
  BOOL      fSignSeperator;     // TRUE if they want a one SPACE ( " " ) seperation between
                                // the sign and the value ( either side )
} CURRENCYINFO, *PCURRENCYINFO;


typedef struct _csdpmdata
{
   ULONG  x;
   ULONG  y;
   ULONG  cx;
   ULONG  cy;
   ULONG  ulClass;
   ULONG  ulStyle;
   USHORT usId;
} CSDPMDATA, *PCSDPMDATA;


typedef struct _csdfld
 {
   EDITMASK   editmask;       // this must remain first so that the editmask
                              // functions can reach it by typecasting as an
                              // EDITMASK instead of a CSDFLD...rjf 4/20/93
   CSDPMDATA  csdPMData;
   PFNWP      pfnPrevious;    // this is used by the CSD Tool to track the
                              // previous function when subclassing
   UCHAR      dataname[ 4 ];
   OBOOL       usefldmask;
   UCHAR      fldmask[ 75 ];
   UCHAR      reqflag;
   OBOOL       usepreproc;
   UCHAR      preproc[ 33 ];
   UCHAR      predll[ 8 ];
   OBOOL       usepostproc;
   UCHAR      postproc[ 33 ];
   UCHAR      postdll[ 8 ];
   OBOOL       usevalidproc;              // If set then use the dynamic ext
   UCHAR      validproc[ 33 ];           // If a value in here and usevalidproc
   UCHAR      validdll[ 8 ];             //   not set then use this ELSE dont call any
   OBOOL       uselistproc;
   UCHAR      listproc[ 33 ];
   UCHAR      listdll[ 8 ];
   UCHAR      mediumname[ 20 ];
   UCHAR      helptext[ 78 ];
} CSDFLD, *PCSDFLD;

typedef struct _csdpage
   {
   CSDPMDATA  csdPMData;
   UCHAR      szTitle[ 50 ];
   UCHAR      okproc[ 33 ];
   UCHAR      okdll[ 8 ];
   UCHAR      cancelproc[ 33 ];
   UCHAR      canceldll[ 8 ];
   UCHAR      initproc[ 33 ];
   UCHAR      initdll[ 8 ];
   USHORT     usPageNumber;
   USHORT     usNumControls;
   } CSDPAGE, *PCSDPAGE;

typedef struct _csdscreen
   {
   USHORT   usVersion;
   USHORT   usNumPages;
   USHORT   usCsdType;
   } CSDSCREEN, *PCSDSCREEN;

/* Data to pass to dialogs so they have all the info they need to display */

typedef struct _awddlgdata
{
  PAWDOBJKEY pawdobjkey;            /* key information */
  PAWDWRKOBJ pawdwrkobj;            /* info for a work object */
  PAWDSRCOBJ pawdsrcobj;            /* info for a source object */
  CHAR       icontext[ 200 ];       /* Icon text */
} AWDDLGDATA, *PAWDDLGDATA;

/* what awdloaddlg passes to all dialogs loaded by it */

typedef struct _dlginit
   {
   USHORT   usSize;                    // size of dlginit
   PVOID    pvStuff;                   // pointer to whatever, usually key
   }  DLGINIT, *PDLGINIT;


/* what awdloaddlg passes to all dialogs loaded by it */

#pragma pack()
#endif  // AWDSTRCT_H

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/awdsrv/AWDSTRCT.H-arc  $
//
//   Rev 1.0   Oct 31 2005 15:05:28   yingbaol
//Initial revision.
 * 
 *

 */








