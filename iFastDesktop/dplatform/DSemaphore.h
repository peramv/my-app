// DSemaphore.h: interface for the DSemaphore class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_DSEMAPHORE_H__INCLUDED_)
   #define _DSEMAPHORE_H__INCLUDED_

   #include <dplatform\DPlatform.h>
   #include <dplatform\DPlatformException.h>

class D_LINKAGE DSemaphore  
{
public:
   DSemaphore(int maxCount=1);
   virtual ~DSemaphore();

   bool wait(long ms=-1L) const;
   void release(int releaseCount=1) const;
private:
   HANDLE hSemaphore;
};

class D_LINKAGE DSemaphoreInitFailed : DPlatformException
{
public: 
   virtual const std::string getMessage() {return("DSemaphore initialization failure.");}
};

class D_LINKAGE DSemaphoreWaitFailed : DPlatformException
{
public: 
   virtual const std::string getMessage() {return("DSemaphore wait failure.");}
};

class D_LINKAGE DSemaphoreReleaseFailed : DPlatformException
{
public: 
   virtual const std::string getMessage() {return("DSemaphore release failure.");}
};

#endif // !defined(_DSEMAPHORE_H__INCLUDED_)
