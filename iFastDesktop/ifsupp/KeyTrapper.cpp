#pragma warning(disable: 4001)      /* Single-line comment */

#include "stdafx.h"
#include <map>
#include <DString.hpp>
#include <typeinfo>
#include "AboutPropSheet.h"

#include "KeyTrapper.h"

static HINSTANCE s_hInstDll;
static HHOOK s_hHookKeyboard;

/**************************************************************** 
  WH_KEYBOARD hook procedure 
 ****************************************************************/ 

typedef int (*PFN_KEYBOARD_HOOK)(int nCode, WPARAM wParam, LPARAM lParam);

static PFN_KEYBOARD_HOOK s_pfnKeyboardHook = NULL;

static LRESULT WINAPI CALLBACK DiagnosticKeyboardHook(int nCode, WPARAM wParam, LPARAM lParam ) 
{
    if (nCode < 0)  // do not process message 
        return CallNextHookEx(s_hHookKeyboard, nCode, wParam, lParam); 

////    static FILE* pKeyFile = fopen("c:\\keyfile.log","a+");
   // lParam & 0x80000000: transition state, 0 if being pressed, 1 if being released
   // lParam & 0x40000000: previous state, 1 if down, 0 if up
   // lParam & 0x0000ffff: repeat count, number of times key has been repeated
//   fprintf(pKeyFile,"%08d, %08x, %08x\n", nCode, wParam, lParam);
//   fflush(pKeyFile);

   static bool bAltDown = false;
   static bool bCtrlDown = false;
   static bool bShiftDown = false;

   if(!((DWORD)lParam & 0x80000000) && (HC_ACTION==nCode)) {   
      if( VK_MENU == wParam ) { bAltDown = true; }
      if( VK_CONTROL == wParam ) { bCtrlDown = true; }
      if( VK_SHIFT == wParam ) { bShiftDown = true; }
   }
   if(((DWORD)lParam & 0x80000000) && (HC_ACTION==nCode)) {
      if( VK_MENU == wParam ) { bAltDown = false; }
      if( VK_CONTROL == wParam ) { bCtrlDown = false; }
      if( VK_SHIFT == wParam ) { bShiftDown = false; }
      if( 0x45 == wParam /* 'E' */ ) {
 //        fprintf(pKeyFile, "E released!\n");
         if( bAltDown && bCtrlDown && bShiftDown ) {
            ////fprintf(pKeyFile, "   and Alt, Ctrl, and Shift are still pressed!\n");
            AboutPropSheet::Display();
         }
      }
   }

   LRESULT lResult = CallNextHookEx(s_hHookKeyboard, nCode, wParam, lParam );
   return( lResult );
}


void RegisterKeyTrapperHooks( HINSTANCE hInstDll ) {
   s_hInstDll = hInstDll;

   s_hHookKeyboard = SetWindowsHookEx( 
         WH_KEYBOARD,
         DiagnosticKeyboardHook,
         hInstDll,
         GetCurrentThreadId() );
}
