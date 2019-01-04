#pragma once

#include <commonport.h>

#undef BFUTIL_LINKAGE
#ifdef BFUTIL_DLL
   #define BFUTIL_LINKAGE CLASS_EXPORT
#else
   #define BFUTIL_LINKAGE CLASS_IMPORT
#endif

namespace bf
{
   class AbstractPublisher;

   class AbstractSubscriber
   {
   public:
      virtual ~AbstractSubscriber() {}
      virtual void finish( AbstractPublisher* theFinishedPublisher ) = 0;
   protected:
      AbstractSubscriber() {}
   };
}
     


//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF Core/bfutil/subscriber.hpp-arc  $
//
//   Rev 1.0   Mar 14 2003 11:08:00   PURDYECH
//Initial Revision
//
