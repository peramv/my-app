// DEvent.h: interface for the DEvent class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_DEVENT_H__INCLUDED_)
   #define _DEVENT_H__INCLUDED_

   #include <dplatform\DPlatform.h>
   #include <dplatform\DPlatformException.h>

class D_LINKAGE DEvent  
{
public:
   DEvent(bool manualReset = false);
   virtual ~DEvent();

   bool wait(long ms=-1L) const;
   void set() const;
private:
   HANDLE hEvent;
};

class D_LINKAGE DEventInitFailed : DPlatformException
{
public: 
   virtual const std::string getMessage() {return("DEvent initialization failure.");}
};

class D_LINKAGE DEventWaitFailed : DPlatformException
{
public: 
   virtual const std::string getMessage() {return("DEvent wait failure.");}
};

class D_LINKAGE DEventSetFailed : DPlatformException
{
public: 
   virtual const std::string getMessage() {return("DEvent set failure.");}
};

#endif // !defined(_DEVENT_H__INCLUDED_)
