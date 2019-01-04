#include <windows.h>
#include <process.h>

#define D_CALLBACK __stdcall

#ifdef D_LIBRARY
   #ifdef D_DLL
      #define D_LINKAGE __declspec(dllexport) 
   #else
      #define D_LINKAGE
   #endif
#else
   #define D_LINKAGE __declspec(dllimport) 
#endif 