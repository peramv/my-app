// DSystem.cpp: implementation of the DSystem class.
//
//////////////////////////////////////////////////////////////////////

#include "DSystem.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

void 
DSystem::userMessage(const std::string &message, const std::string &appId)
{
   ::MessageBox(NULL, message.c_str(), appId.c_str(), MB_SYSTEMMODAL);
}

void 
DSystem::yeild()
{

   HCURSOR cursor = GetCursor();
   MSG msg;
   while( ::PeekMessage(&msg, NULL, 0L, 0L, PM_REMOVE) )
      if( msg.message == WM_PAINT )
      {
         ::TranslateMessage(&msg);
         ::DispatchMessage(&msg);
      }

   SetCursor(cursor);
}
