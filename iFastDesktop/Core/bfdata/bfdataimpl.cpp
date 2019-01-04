#include "stdafx.h"

#include "bfdataimpl.hpp"
#include "bfdataimpldefaults.hpp"

BFDataImplDefaults* BFDataImpl::s_pDefaults_ = NULL;

unsigned long BFDataImpl::getDefaultMarket()
{
   return( getDefaults()->getDefaultMarket() );
}

unsigned long BFDataImpl::getDefaultClient()
{
   return( getDefaults()->getDefaultClient() );
}

const DString& BFDataImpl::getDefaultLocale()
{
   return( getDefaults()->getDefaultLocale() );
}

BFDataImplDefaults* BFDataImpl::setDefaults( BFDataImplDefaults* pDefaults )
{
   BFDataImplDefaults* pOrig = s_pDefaults_;
   s_pDefaults_ = pDefaults;
   return( pOrig );
}

const BFDataImplDefaults* BFDataImpl::getDefaults()
{
   return(s_pDefaults_);
}


