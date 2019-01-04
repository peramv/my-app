#pragma once

#include <bfutil\bfkernel.hpp>
#include <string>

// Import/Export resolution
#undef BFUTIL_LINKAGE
#ifdef BFUTIL_DLL
   #define BFUTIL_LINKAGE CLASS_EXPORT
#else
   #define BFUTIL_LINKAGE CLASS_IMPORT
#endif

namespace bfutil
{
   /**
    * Assign a name for a thread.  The name is only used by the Visual
    * Studio Debugger; it has no programmatic effect.  This function
    * is highly <i>non</i>-portable.
    * 
    * @param dwThreadID The TID of the thread to name.  Use -1 for the current thread.
    * @param pszThreadName
    *                   A pointer to a thread name.  The name should be 9 characters or less.
    *                   Note that the thread name must be ASCII ... no UNICODE spoken here.
    * 
    */
   extern BFUTIL_LINKAGE void setThreadName(DWORD dwThreadID, const char* pszThreadName);

   typedef std::string ( __stdcall *PTHRDNAMEFN )( DWORD );
}

class BFUTIL_LINKAGE BFThread : public BFKernel
{
public:
   //Put the thread at rest for a while (default 1 second)
   static void sleep( DWORD dwMilliseconds = 1000 );

   BFThread( bfutil::PTHRDNAMEFN pThreadNameFunc = NULL );
   virtual ~BFThread();

   //Get the thread ID
   DWORD getThreadID() const;

   //Get the thread's priority
   int getPriority() const;

   //Set the thread's priority
   void setPriority( int nPriority );

   //Suspend the thread
   void suspend();

   //Resume the thread
   bool resume();

   //Causes this thread to start
   void start( unsigned uStackSize = 0 );

   //Causes this thread to start in a suspended state
   void startSuspended( unsigned uStackSize = 0 );

protected:
   virtual void run() = 0;
   bfutil::PTHRDNAMEFN getThreadNameFunc() const { return pThreadNameFunc_; }

private:
   static unsigned _stdcall ThreadKicker( void *lpThreadParameter );

private:

   DWORD          tid_;             //the thread ID
   bfutil::PTHRDNAMEFN    pThreadNameFunc_;
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF Core/bfutil/BFThread.hpp-arc  $
//
//   Rev 1.5   May 01 2003 10:51:46   PURDYECH
//Added code to support thread naming.
//
//   Rev 1.4   Apr 28 2003 14:48:20   PURDYECH
//Added setThreadName 
//
//   Rev 1.3   Oct 09 2002 17:41:22   PURDYECH
//New PVCS Database
//
//   Rev 1.2   03 Oct 2001 15:10:02   SMITHDAV
//Syncronization changes and Job Queue changes
//
//   Rev 1.1   24 Jul 2001 19:52:06   PURDYECH
//Removed Debug console messages.
//
//   Rev 1.0   Jun 28 2001 09:47:02   PURDYECH
//Initial revision.
//
//   Rev 1.0   Jun 26 2001 12:03:56   PURDYECH
//Initial revision.
 * 
 *    Rev 1.3   Aug 23 2000 11:10:04   DT24433
 * Use Job::run method during run method
 * 
 *    Rev 1.2   Feb 16 2000 13:09:44   POPESCUS
 * Initial revision
 * 
 * 
 */

