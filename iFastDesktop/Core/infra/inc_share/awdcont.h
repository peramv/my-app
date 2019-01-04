#ifndef AWDCONT_H
#define AWDCONT_H

#ifndef __AFXWIN_H__
   #error include 'stdafx.h' before including this file for PCH
#endif

#include <awdtree.xh>

// Shared Memory definitions for single instance applications.
#define AWD_PROCESS_NAME      "PROCESS.EXE"
#define AWD_CREATCNR_NAME     "CREATCNR.EXE"
#define AWD_PQUE_NAME         "AWDPQUE.EXE"

#ifndef DllExport
#define DllExport   __declspec( dllexport )
#endif

// Unique id to be set into the window word of the frame to allow the apis
// to identify awd containers.
//
#define AWD_CONTAINER_IDENTIFIER   7787

enum CONT_MODE
{
   PROCESS, PERSONALQUEUE, LOOKUP, CREATE, FINDPARENTS, FINDCHILDREN, CMD_LINE_LOOKUP
};

DllExport HWND AWDLoadContainer( CONT_MODE cnrMode, AWDTree* tree, AWDBase * pAwdObj );

#endif  // AWDCONT_H


