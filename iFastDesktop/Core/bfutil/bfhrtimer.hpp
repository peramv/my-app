#pragma once

// Import/Export resolution
#undef BFUTIL_LINKAGE
#ifdef BFUTIL_DLL
   #define BFUTIL_LINKAGE CLASS_EXPORT
#else
   #define BFUTIL_LINKAGE CLASS_IMPORT
#endif

/**
 * This class provides a high-resolution timer for the Win32 platform.
 * The timer has a resolution of one millisecond however it is possible
 * to achieve a much smaller resolution if required.
 * 
 * @author Chris Purdye
 */
class BFUTIL_LINKAGE BFHRTimer
{
public:
   BFHRTimer();
   BFHRTimer( const LARGE_INTEGER& startTime );
   BFHRTimer( const BFHRTimer& rhs );
   ~BFHRTimer();

   BFHRTimer& operator=( const BFHRTimer& hrs );

   /**
    * Start the timer.  The timer starts automatically when it is constructed
    * but this will also restart a running timer and start a previously 
    * stopped timer.
    */
   void start();

   /**
    * Stop a running timer.  All subsequent calls to {@link #elapsed() elapsed}
    * will return the same value until the timer is restarted.
    */
   void stop();

   /**
    * Return the number of milliseconds which have elapsed since the timer
    * was started.
    * 
    * @return The number of milliseconds which have elapsed since the time was
    *         started.  Since the timer actually has a much higher resolution
    *         than one millisecond this value will be rounded to the nearest millisecond.
    */
   unsigned long elapsed() const;

   /**
    * Reset the timer and restart it.
    */
   void reset();

   const LARGE_INTEGER& getStartTime() const { return(startTime_);}
   static LARGE_INTEGER getTimeValue();
   static const LARGE_INTEGER& getTicksPerMillisecond();
private:
   LARGE_INTEGER  startTime_;
   LARGE_INTEGER* pStopTime_;
};


//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF Core/bfutil/bfhrtimer.hpp-arc  $
//
//   Rev 1.2   Apr 16 2003 09:46:58   PURDYECH
//Doxygen documentation standard
//
//   Rev 1.1   Oct 09 2002 17:41:14   PURDYECH
//New PVCS Database
//
//   Rev 1.0   22 May 2002 16:30:36   PURDYECH
//Initial revision.
//
