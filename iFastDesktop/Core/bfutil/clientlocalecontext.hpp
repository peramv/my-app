#pragma once


#undef BFUTIL_LINKAGE
#ifdef BFUTIL_DLL
   #define BFUTIL_LINKAGE CLASS_EXPORT
#else
   #define BFUTIL_LINKAGE CLASS_IMPORT
#endif

#include <clientlocale.hpp>
#include <bfutil\bfexecutioncontext.hpp>

class BFUTIL_LINKAGE ClientLocaleContext : public BFExecutionContextImpl
{
public:
   static const ClientLocale& get();
   static void set( const ClientLocale& locale );

   const ClientLocale& getClientLocale() const;
   void setClientLocale( const ClientLocale& locale );

protected:
   virtual void notifyAttach();

private:
   ClientLocaleContext();
   virtual ~ClientLocaleContext();

   ClientLocale   locale_;
};

#ifndef _DEBUG
inline const ClientLocale& ClientLocaleContext::getClientLocale() const
{
   return(locale_);
}

inline void ClientLocaleContext::setClientLocale( const ClientLocale& locale )
{
   locale_ = locale;
   ::SetThreadLocale( locale_.getLCID() );
}
#endif
