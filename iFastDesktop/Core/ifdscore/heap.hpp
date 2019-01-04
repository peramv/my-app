#pragma once

//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by DST Systems, Inc.,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 1997 by DST Systems, Inc.
//
//******************************************************************************
//
// ^FILE   : heap.hpp
// ^AUTHOR : Larry Parnes
// ^DATE   : 06/19/97
//
// ^CLASS  : CHeap
// ^PARENT : None
//
// ^CLASS DESCRIPTION : An abstract base class for the interface of heaps.
//
//******************************************************************************

#ifndef DIPORT_H
   #include <diport.h>
#endif

#undef DICORE_LINKAGE
#ifdef DICORE_DLL
   #define DICORE_LINKAGE CLASS_EXPORT
#else
   #define DICORE_LINKAGE CLASS_IMPORT
#endif

class DICORE_LINKAGE CHeap
{
public:
   CHeap (VOID);
   virtual ~CHeap (VOID);
   virtual PVOID Alloc (DWORD dwBytes);
   virtual BOOL Free (PVOID pv);
   virtual BOOL Destroy (VOID);

private:
   VOID Init (VOID);

   HANDLE   hHeap;
   ULONG nAllocs;
};

