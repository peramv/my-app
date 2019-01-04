#include "stdafx.h"

#include "clientlocalecontext.hpp"
#include <configmanager.hpp>

static const DString keyClientLocaleContext( I_("ClientLocaleContext") );

const ClientLocale& ClientLocaleContext::get()
{
   BFExecutionContext* pContext = BFExecutionContext::get();

   ClientLocaleContext* pLocaleContext = dynamic_cast< ClientLocaleContext* >( pContext->getObject( keyClientLocaleContext ) );
   if( NULL == pLocaleContext )
   {
      pLocaleContext = new ClientLocaleContext();
      pContext->addObject( keyClientLocaleContext, pLocaleContext );
   }

   return( pLocaleContext->getClientLocale() );
}

void ClientLocaleContext::set( const ClientLocale& locale )
{
   BFExecutionContext* pContext = BFExecutionContext::get();

   ClientLocaleContext* pLocaleContext = dynamic_cast< ClientLocaleContext* >( pContext->getObject( keyClientLocaleContext ) );
   if( NULL == pLocaleContext )
   {
      pLocaleContext = new ClientLocaleContext();
      pContext->addObject( keyClientLocaleContext, pLocaleContext );
   }

   pLocaleContext->setClientLocale( locale );
}

ClientLocaleContext::ClientLocaleContext()
: locale_()
{
   DString dstrMarket = GetConfigValueAsString( ConfigManager::getApplication(), I_( "Market" ), I_( "Market" ) );
   locale_.setMarket( dstrMarket );
}

ClientLocaleContext::~ClientLocaleContext()
{
}

void ClientLocaleContext::notifyAttach()
{
   // we have just been attached to the current thread ... set our thread locale
   ::SetThreadLocale( locale_.getLCID() );
}


#ifdef _DEBUG
const ClientLocale& ClientLocaleContext::getClientLocale() const
{
   return(locale_);
}

void ClientLocaleContext::setClientLocale( const ClientLocale& locale )
{
   locale_ = locale;
   ::SetThreadLocale( locale_.getLCID() );
}
#endif

