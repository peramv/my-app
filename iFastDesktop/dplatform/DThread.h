// DThread.h: interface for the DThread class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_DTHREAD_H__INCLUDED_)
   #define _DTHREAD_H__INCLUDED_

   #include <dplatform\DPlatform.h>
   #include <dplatform\DPlatformException.h>

class D_LINKAGE DThread  
{
public:
   DThread();
   virtual ~DThread();

   void start();
   bool join(long ms=-1L);

protected:
   virtual void run() = 0;

private:
   HANDLE hThread;
   static void __cdecl startThread(void *threadObj);

};

class D_LINKAGE DThreadInitFailed : DPlatformException
{
public: 
   virtual const std::string getMessage() {return("DThread initialization failure.");}
};

class D_LINKAGE DThreadJoinFailed : DPlatformException
{
public: 
   virtual const std::string getMessage() {return("DThread join failure.");}
};


#endif // !defined(_DTHREAD_H__INCLUDED_)
