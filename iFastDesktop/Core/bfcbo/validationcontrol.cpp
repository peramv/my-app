#include <bfutil\rtrevisiondefines.hpp>
RT_SOURCE_REVISION( "$Archive:   Y:/VCS/BF Core/bfcbo/validationcontrol.cpp-arc  $$", "$Revision:   1.1  $" )

#pragma warning( disable: 4275 )
#include "validationcontrol.hpp"
#include <bfutil\bfguard.hpp>

static const DString keyValidationControl( I_( "ValidationControl" ) );

ValidationControl& ValidationControl::get()
{
   BFExecutionContext* pContext = BFExecutionContext::get();

   ValidationControl* pValidationControl = dynamic_cast< ValidationControl* >( pContext->getObject( keyValidationControl ) );
   if( NULL == pValidationControl )
   {
      pValidationControl = new ValidationControl();
      pContext->addObject( keyValidationControl, pValidationControl );
   }

   return( *pValidationControl );
}

ValidationControl::ValidationControl()
: cProcesses_( 0 )
{}

ValidationControl::~ValidationControl()
{
}

void ValidationControl::setValidateOnly()
{
   BFGuard g( cs_ );
   ++cProcesses_;
}

void ValidationControl::unsetValidateOnly()
{
   BFGuard g( cs_ );
   if( cProcesses_ > 0 ) --cProcesses_;
}

bool ValidationControl::isValidateOnly() const
{
   BFGuard g( cs_ );
   return( cProcesses_ > 0 );
}

//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF Core/bfcbo/validationcontrol.cpp-arc  $
// 
//    Rev 1.1   Sep 27 2004 09:40:44   PURDYECH
// Clean up compiler warnings so that there are no complaints about silly things (like truncated debug names...)
// 
//    Rev 1.0   May 26 2003 14:22:12   PURDYECH
// Initial revision.
//
