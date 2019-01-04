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
//    Copyright 1999 by DST Systems, Inc.
//
//
//******************************************************************************
//
// ^FILE   : genericbfcbo.cpp
// ^AUTHOR : Chris Purdye
// ^DATE   : 
//
//******************************************************************************
#include <bfutil\RTRevisionDefines.hpp>
RT_SOURCE_REVISION( "$Archive:   //db3n5j11/d/scc/ifds/core/archives/bfcbo/genericbfcbo.cpp-arc  $", "$Revision:   1.2  $" )

#include "GenericBFCBO.hpp"

//******************************************************************************
GenericBFCBO::GenericBFCBO(BFAbstractCBO *parent) 
: BFCBO(parent),
_session( parent->getSession() )
{
}

//******************************************************************************
const BFSession &
GenericBFCBO::getSession() const
{
   return(_session);
}

//******************************************************************************
BFSession &
GenericBFCBO::getSession()
{
   return(_session);
}


//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   //db3n5j11/d/scc/ifds/core/archives/bfcbo/genericbfcbo.cpp-arc  $
// 
//    Rev 1.2   Oct 09 2002 17:40:12   PURDYECH
// New PVCS Database
// 
//    Rev 1.1   Aug 29 2002 12:51:08   SMITHDAV
// ClientLocale and typed field changes.
// 
//    Rev 1.0   22 May 2002 20:33:36   PURDYECH
// Initial revision.
//
