// DMutex.h: interface for the DMutex class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_DMUTEX_H__INCLUDED_)
   #define _DMUTEX_H__INCLUDED_

   #include <dplatform\DPlatform.h>
   #include <dplatform\DPlatformException.h>

class D_LINKAGE DMutex  
{
public:
   DMutex();
   virtual ~DMutex();

   bool wait(long ms=-1L) const;
   void release() const;
private:
   HANDLE hMutex;
};

class D_LINKAGE DMutexInitFailed : DPlatformException
{
public: 
   virtual const std::string getMessage() {return("DMutex initialization failure.");}
};

class D_LINKAGE DMutexWaitFailed : DPlatformException
{
public: 
   virtual const std::string getMessage() {return("DMutex wait failure.");}
};

class D_LINKAGE DMutexReleaseFailed : DPlatformException
{
public: 
   virtual const std::string getMessage() {return("DMutex release failure.");}
};

#endif // !defined(_DMUTEX_H__INCLUDED_)
