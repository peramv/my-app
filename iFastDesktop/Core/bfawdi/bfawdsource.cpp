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
// ^FILE   : BFAwdSource.cpp
// ^AUTHOR : Michael McGarry
// ^DATE   : 21 Jul 1999
//
// ----------------------------------------------------------
//
// ^CLASS    : BFAwdSource
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#define BFAWDI_DLL

#include <srcprag.h>
#include "bfawdsource.hpp"


//******************************************************************************
//              Public Methods
//******************************************************************************

BFAwdSource::BFAwdSource()
: m_format( BFAwdSource::NO_FORMAT )
{
}


BFAwdSource::~BFAwdSource()
{
}

const BFAwdKey *BFAwdSource::getKey() const
{
   return(m_data.getKey());
}

const BFAwdData &BFAwdSource::getData() const
{
   return(m_data);
}

const DString &BFAwdSource::getSourceType() const
{
   return(m_data.getObjt());
}

const DString &BFAwdSource::getLobValue( const DString &name ) const
{
   return(m_data.getLobValue( name ));
}

//******************************************************************************
//              Protected Methods
//******************************************************************************


//******************************************************************************
//              Private Methods
//******************************************************************************


// These two methods are purposely not implemented.
//
// BFAwdSource::BFAwdSource( const BFAwdSource &copy )
// {
//    this->operator =( copy );
// }
//
// const BFAwdSource &BFAwdSource::operator=( const BFAwdSource &copy )
// {
//    if ( this == &copy )
//    {
//       return *this;
//    }
//
//    return *this;
// }


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
// $Log:   //db3n5j11/d/scc/ifds/core/archives/bfawdi/bfawdsource.cpp-arc  $
// 
//    Rev 1.1   Oct 09 2002 17:39:56   PURDYECH
// New PVCS Database
// 
//    Rev 1.0   28 May 2002 12:11:10   SMITHDAV
// Initial revision.
// 
//    Rev 1.1   Aug 26 1999 12:58:42   DMUM
// Sync up with 1.7 & 1.6
// Now supports Sources and the starting and stoping of a source.
//
//    Rev 1.0   Aug 04 1999 09:45:02   DMUM
//
//
//

