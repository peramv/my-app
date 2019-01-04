// DPlatformException.h: interface for the DPlatformException class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_DPLATFORMEXCEPTION_H__INCLUDED_)
   #define _DPLATFORMEXCEPTION_H__INCLUDED_

   #include <dplatform\DPlatform.h>

   #pragma warning( disable : 4251 )
   #include <string>

class D_LINKAGE DPlatformException  
{
public:
   virtual const std::string getMessage() = 0;// {return "An unspecified platform library Exception occurred";}
};

#endif // !defined(_DPLATFORMEXCEPTION_H__INCLUDED_)
