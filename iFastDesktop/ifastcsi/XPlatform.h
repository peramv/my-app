#if !defined(XPLATFORM_H__INCLUDED_)
   #define XPLATFORM_H__INCLUDED_

   #ifdef _MSC_VER
// Disable the following compiler warnings
// 4786 identifier truncated to 255 characters
      #pragma warning( disable : 4786 )
      #pragma warning( disable : 4251 )

      #include <dplatform\DPlatform.h>
      #include <dplatform\DSystem.h>
      #include <dplatform\DPlatformException.h>
      #include <dplatform\DThread.h>
      #include <dplatform\DMutex.h>
      #include <dplatform\DSemaphore.h>
      #include <dplatform\DEvent.h>

   #endif

#endif // !defined(XPLATFORM_H__INCLUDED_)
