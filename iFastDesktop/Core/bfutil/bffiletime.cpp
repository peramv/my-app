#include "stdafx.h"
#include "bffiletime.hpp"

LONGLONG operator-( const BFFileTime& lhs, const BFFileTime& rhs )
{
   return( BFFileTime( lhs ) -= rhs );
}


