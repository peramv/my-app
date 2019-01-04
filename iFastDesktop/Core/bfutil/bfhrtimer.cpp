#include "stdafx.h"
#include "bfhrtimer.hpp"

BFHRTimer::BFHRTimer()
: startTime_( getTimeValue() )
, pStopTime_( NULL )
{
}

BFHRTimer::BFHRTimer( const LARGE_INTEGER& startTime )
: startTime_( startTime )
, pStopTime_( NULL )
{
}

BFHRTimer::BFHRTimer( const BFHRTimer& rhs )
{
   *this = rhs;
}

BFHRTimer::~BFHRTimer()
{
   delete pStopTime_;
}


BFHRTimer& BFHRTimer::operator=( const BFHRTimer& rhs )
{
   if( this != &rhs )
   {
      startTime_.QuadPart = rhs.startTime_.QuadPart;
      if( NULL != rhs.pStopTime_ )
      {
         pStopTime_ = new LARGE_INTEGER;
         pStopTime_->QuadPart = rhs.pStopTime_->QuadPart;
      }
   }
   return( *this );
}


const LARGE_INTEGER& BFHRTimer::getTicksPerMillisecond()
{
   static LARGE_INTEGER ticksPerMilli = {0};
   if( 0 == ticksPerMilli.QuadPart )
   {
      LARGE_INTEGER freq;
      QueryPerformanceFrequency( &freq );
      ticksPerMilli.QuadPart = ( freq.QuadPart + 500 ) / 1000;
   }
   return( ticksPerMilli );
}

void BFHRTimer::reset()
{
   delete pStopTime_;
   pStopTime_ = NULL;
   startTime_ = getTimeValue();
}

void BFHRTimer::start()
{
   reset();
}

void BFHRTimer::stop()
{
   if( NULL == pStopTime_ )
   {
      pStopTime_ = new LARGE_INTEGER;
   }
   *pStopTime_ = getTimeValue();
}

unsigned long BFHRTimer::elapsed() const
{
   LARGE_INTEGER li;
   if( NULL != pStopTime_ )
   {
      li = *pStopTime_;
   }
   else
   {
      li = getTimeValue();
   }
   unsigned long ms = static_cast< unsigned long >( ( li.QuadPart - startTime_.QuadPart + ( getTicksPerMillisecond().QuadPart / 2 ) ) / getTicksPerMillisecond().QuadPart );
   return( ms );
}

LARGE_INTEGER BFHRTimer::getTimeValue()
{
   LARGE_INTEGER timeVal;
   QueryPerformanceCounter( &timeVal );
   return( timeVal );
}

//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF Core/bfutil/bfhrtimer.cpp-arc  $
//
//   Rev 1.2   Oct 22 2004 08:59:28   PURDYECH
//PET910 - .NET Conversion Fixes
// 
//    Rev 1.1   Oct 09 2002 17:41:14   PURDYECH
// New PVCS Database
// 
//    Rev 1.0   22 May 2002 16:29:44   PURDYECH
// Initial revision.
//
