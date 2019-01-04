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
// ^FILE   : heap.cpp
// ^AUTHOR : Larry Parnes
// ^DATE   : 06/19/98
//
//******************************************************************************
#define DICORE_DLL

#ifndef SRCPRAG_H
   #include "srcprag.h"
#endif
#ifndef HEAP_HPP
   #include "heap.hpp"
#endif


//******************************************************************************
//              Public Methods
//******************************************************************************

CHeap::CHeap (VOID)
{
   Init();
}


VOID CHeap::Init (VOID)
{
   hHeap = (HANDLE) NULL;
   nAllocs = 0;
}


PVOID CHeap::Alloc (DWORD dwBytes)
{
   PVOID pv = (PVOID) NULL;

   if( dwBytes > 0 )
   {

#if defined(_WIN32) && defined(USE_SEPARATE_HEAPS)

      if( !hHeap )
      {
         hHeap = HeapCreate(0, 0, 0);
      }

      if( hHeap && (pv = HeapAlloc(hHeap, HEAP_ZERO_MEMORY, dwBytes))
          != (PVOID) NULL )
      {
         nAllocs++;
      }

#else       // !defined(_WIN32) || !defined(USE_SEPARATE_HEAPS)

      pv = malloc((size_t) dwBytes);

#endif
   }

   return(pv);
}


BOOL CHeap::Free (PVOID pv)
{
   BOOL  bReturn = FALSE;

   if( nAllocs > 0 && pv )
   {
#if defined(_WIN32) && defined(USE_SEPARATE_HEAPS)

      if( HeapFree(hHeap, 0, pv) )
      {
         nAllocs--;
      }

#else       // !defined(_WIN32) || !defined(USE_SEPARATE_HEAPS)

      free(pv);
      nAllocs--;

#endif

      if( nAllocs == 0 )
      {
         bReturn = Destroy();
      }
   }

   return(bReturn);
}


BOOL CHeap::Destroy (VOID)
{
   BOOL  bReturn = TRUE;

#if defined(_WIN32) && defined(USE_SEPARATE_HEAPS)

   bReturn = (hHeap ? HeapDestroy(hHeap) : TRUE);

#endif

   Init();
   return(bReturn);
}


CHeap::~CHeap (VOID)
{
   Destroy();
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
// $Log:   //db3n5j11/d/scc/ifds/core/archives/ifdscore/heap.cpp-arc  $
// 
//    Rev 1.1   Oct 09 2002 17:42:02   PURDYECH
// New PVCS Database
// 
//    Rev 1.0   Jul 05 2002 10:14:16   SMITHDAV
// Initial revision.
// 
//    Rev 1.2   Jan 28 1999 14:02:58   DMUM
// Check in for VCPP 6.0
// 
//    Rev 1.1   Jan 28 1999 13:43:38   DMUM
// Check in for VCPP 6.0
//
//    Rev 1.0   Dec 09 1998 13:51:16   DMUM
//
//
//    Rev 1.5   Nov 09 1997 15:35:14   DTWK
// Add inclusion guards for faster compiles.
// Add guards so that class is flagged as exported only when compiling
// the output that actually exports the class.
//
//    Rev 1.4   Jul 07 1997 15:16:06   DTWK
// Add more commenting / bug fixes.
//
//    Rev 1.3   Jun 13 1997 13:20:28   DTWK
//
//
//

