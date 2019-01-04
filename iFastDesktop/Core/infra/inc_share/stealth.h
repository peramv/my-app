#include <awddef.h>
#include <awdapi.h>

#define DllExport	__declspec( dllexport )

class DllExport cStealth
{
public:
   cStealth() {};
   ~cStealth() {};

   static SHORT ClickContainerButton( HWND hwndCont, USHORT usButton,
                                     PVOID pReserved = NULL );

   static BOOL CloseImageWin( HWND hwndImage, PVOID pReserved = NULL );

   static HWND LoadComments( HWND hwndParent, HWND hwndOwner,
                             HWND hwndNotify, ULONG ulMsg,
                             PAWDOBJKEY pAwdObjKey,
                             USHORT usModal, PVOID pReserved = NULL );

   static PVOID LoadDocument( PVOID pvImageWindow, HWND hwndImage,
                              PAWDOBJ pAwdObj, UCHAR ucDocType,
                              PVOID pReserved = NULL );

   static HWND LoadHistory( HWND hwndParent, HWND hwndOwner, HWND hwndNotify,
                            ULONG ulMsg, PAWDOBJKEY pAwdObjKey, 
                            USHORT usModal, PVOID pReserved = NULL );

   static HWND LoadImageWin( HWND hwndParent, HWND hwndOwner,
                             PVOID* ppvImageWindow, UCHAR ucDocType,
                             USHORT usModal, PVOID pReserved = NULL );

   static HWND LoadSuspend( HWND hwndParent, HWND hwndOwner,
                            HWND hwndNotify, ULONG ulMsg, PAWDOBJ pAwdObj,
                            USHORT usModal, PVOID pReserved = NULL );

   static SHORT RefreshContainerItem( HWND hwndCont, PAWDOBJKEY pAwdObjKey,
                                      PVOID pReserved = NULL );

   static BOOL RetrieveAllLobs( PAWDOBJKEY pAwdObjKey,
                                PAWDLOBARRAY pAwdLobArray, 
                                PVOID pReserved = NULL);

   static SHORT UpdateObject(PAWDOBJ pAwdObj,
                             PAWDLOBARRAY pAwdLobArray,
                             PVOID pReserved = NULL);

   static VOID WriteLog( PSZ pszAppName, PSZ pszString, PVOID pReserved = NULL );
};
