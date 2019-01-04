#ifndef DSTMEMORY_H
#define DSTMEMORY_H

#pragma message( "including "__FILE__ )

/*
 *    COPYRIGHT:
 *
 *    The computer systems, procedures, data bases and
 *    programs created and maintained by DST Systems, Inc.,
 *    are proprietary in nature and as such are confidential.
 *    Any unauthorized use or disclosure of such information
 *    may result in civil liabilities.
 *
 *    Copyright 1996-2000 by DST Systems, Inc.
 */

/**@pkg DITEST */

/** DSTMemoryState: Wrapper for OS-specific memory-leak checking code */

// This goes in the Win32 directory
// MFC dependency


#undef DITEST_LINKAGE
#ifdef DITEST_DLL
   #define DITEST_LINKAGE CLASS_EXPORT
#else
   #define DITEST_LINKAGE CLASS_IMPORT
#endif


#include <crtdbg.h>

class DITEST_LINKAGE DSTMemoryState
{

public:
   /**
   * Constructor
   *
   * @returns   this
   * @exception none
   */
   DSTMemoryState()
   {
      memset( this, 0, sizeof( *this ) );
   }

   /**
   * This method takes a snapshot of memory
   *
   * @returns   void
   * @exception none
   */
   void snapshot();

   /**
   * This method determines whether there is a significant
   * difference between two memory states
   *
   * @param     DSTMemoryState & - the first instance
   * @param     DSTMemoryState & - the second instance
   * @returns   bool
   * @exception none
   */
   bool difference( const DSTMemoryState & old,
                    const DSTMemoryState & pnew );

   /**
   * This method returns the total number of bytes allocated.
   *
   * @returns   long
   * @exception none
   */
   long getBytesAllocated();

private: // Attributes
   enum blockUsage
   {
      freeBlock,    // memory not used
      objectBlock,  // contains a CObject derived class object
      bitBlock,     // contains ::operator new data
      crtBlock,
      ignoredBlock,
      nBlockUseMax  // total number of usages
   };

   _CrtMemState m_memState;
   long m_lCounts[ nBlockUseMax ];
   long m_lSizes[ nBlockUseMax ];
   long m_lHighWaterCount;
   long m_lTotalCount;

private:
   void changeState();

};

//************************************************************************
//              Revision Control Entries
//************************************************************************
//
// Name:
//    %PM%
//    %PID%
//
// Description:
//    %PD%
//
// Design Parts:
//    %PIRP%
//
// Last Changed:
//    %PO%  -  %PRT%
//
// Changes:
//    %PLA%
//
//
// $Log:   Y:/VCS/iFastAWD/inc/dstmemory.h-arc  $
//
//   Rev 1.0   28 Jan 2008 13:31:26   kovacsro
//Initial revision.
//
//   Rev 1.4   Dec 07 2000 16:14:04   DT11159
//Renamed getTotalCount to getBytesAllocated.
//
//   Rev 1.3   Dec 07 2000 11:16:30   DT11159
//Added getTotalCount method.
//
//   Rev 1.2   30 Nov 2000 10:55:30   dt14177
//cleanup
//
//   Rev 1.1   Dec 23 1999 13:22:22   DT14177
//Fixed linkage macro
//

#endif // DSTMEMORY_H
