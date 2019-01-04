// CsiException.h: interface for the CsiException class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_CSIEXCEPTION_H__INCLUDED_)
   #define _CSIEXCEPTION_H__INCLUDED_

   #include <ifastcsi\xplatform.h>

class CsiException  
{
public:
   virtual const std::string getMessage() = 0;// {return "An unspecified Csi library Exception occurred";}
};

#endif // !defined(_CSIEXCEPTION_H__INCLUDED_)
