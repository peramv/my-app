// DSystem.h: interface for the DSystem class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_DSYSTEM_H__INCLUDED_)
   #define _DSYSTEM_H__INCLUDED_

   #include <dplatform\DPlatform.h>
   #include <dplatform\DPlatformException.h>

   #include <string>

class D_LINKAGE DSystem  
{
public:
   static void userMessage(const std::string &message, const std::string &appId);
   static void yeild();

private:
   DSystem() {}

};

#endif // !defined(_DSYSTEM_H__INCLUDED_)
