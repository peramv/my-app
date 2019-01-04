//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by DST Systems, Inc.,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 1997 by DST Systems, Inc.
//
//******************************************************************************
//
// ^FILE   : BFAwdLookupCriteria.cpp
// ^AUTHOR : Michael McGarry
// ^DATE   : 4 Jan 1999
//
// ----------------------------------------------------------
//
// ^CLASS    : BFAwdLookupCriteria
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************
#define BFAWDI_DLL

#include <srcprag.h>
#include "bfawdlookupcriteria.hpp"

namespace
{
   const int FIELD_LENGTH = 4;
   const int VALUE_LENGTH = 75;
}

//******************************************************************************
//              Public Methods
//******************************************************************************

BFAwdLookupCriteria::BFAwdLookupCriteria( const DString &field,
                                          const Comparison compare,
                                          const DString &value )
: m_field( field ),
m_value( value ),
m_compare( compare ),
m_order( NO_ORDER )
{
}

BFAwdLookupCriteria::BFAwdLookupCriteria( const DString &field,
                                          const Order order )
: m_field( field ),
m_value( I_("") ),
m_compare( UNDEFINED ),
m_order( order )
{
}

BFAwdLookupCriteria::BFAwdLookupCriteria()
: m_field( I_("") ),
m_value( I_("") ),
m_compare( UNDEFINED ),
m_order( NO_ORDER )
{
}

BFAwdLookupCriteria::BFAwdLookupCriteria( const BFAwdLookupCriteria &copy )
{
   this->operator =( copy );
}


BFAwdLookupCriteria::~BFAwdLookupCriteria()
{
}

bool BFAwdLookupCriteria::isValid() const
{
   bool valid = ( EQUAL_TO <= m_compare ) && ( NOT_EQUAL >= m_compare );
   valid &= m_value.size() && ( VALUE_LENGTH >= m_value.size() );

   if( ! valid )
   {
      valid = isOrderBy();
   }

   valid &= m_field.size() && ( FIELD_LENGTH >= m_field.size() );

   return(valid);
}

BFAwdLookupCriteria &BFAwdLookupCriteria::operator=( const BFAwdLookupCriteria &copy )
{
   if( this != &copy )
   {
      this->m_field = copy.m_field;
      this->m_value = copy.m_value;
      this->m_compare = copy.m_compare;
      this->m_order = copy.m_order;
   }

   return(*this);
}


//******************************************************************************
//              Protected Methods
//******************************************************************************



//******************************************************************************
//              Private Methods
//******************************************************************************


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
// $Log:   //db3n5j11/d/scc/ifds/core/archives/bfawdi/bfawdlookupcriteria.cpp-arc  $
// 
//    Rev 1.1   Oct 09 2002 17:39:54   PURDYECH
// New PVCS Database
// 
//    Rev 1.0   28 May 2002 12:11:08   SMITHDAV
// Initial revision.
// 
//    Rev 1.2   May 18 1999 08:49:54   DMUM
//  
//
//    Rev 1.1   Apr 14 1999 12:29:24   DMUM
// Sunc up with 1.6.x
//
//    Rev 1.1   Apr 09 1999 13:49:06   DMUM
// Sync up with 1.6.x
//
//    Rev 1.0.1.0   Mar 31 1999 13:19:22   DMUM
//
//
//    Rev 1.0   Jan 20 1999 09:09:32   DMUM
//
//
//

