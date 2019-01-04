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
// ^FILE   : SQLDirect.cpp
// ^AUTHOR : Mark Tarantino
// ^DATE   : 27 Jan 1999
//
// ----------------------------------------------------------
//
// ^CLASS    : SQLDirect
//
// ^MEMBER VARIABLES :
//
//   ^^ SQLDirectImpl *m_pImpl - pointer to member implementation class
//
// ^CODING COMMENTS  :
//
//******************************************************************************
#include "win32/stdafx.h"

#include <srcprag.h>
#include <win32\sqldirectimpl.hpp>
#include "sqldirect.hpp"
#include "bfsessn.h"

//******************************************************************************
//              Public Methods
//******************************************************************************
SQLDirect::SQLDirect()
: m_pImpl( new SQLDirectImpl() )
{
}

SQLDirect::SQLDirect( const DString &strSource )
: m_pImpl( new SQLDirectImpl( strSource ) )
{
}

SQLDirect::SQLDirect( const DString &strSource,
                      const DString &strUser,
                      const DString &strPassword )
: m_pImpl( new SQLDirectImpl( strSource, strUser, strPassword ) )
{
}

SQLDirect::~SQLDirect()
{
   delete m_pImpl;
}

SEVERITY SQLDirect::executeSQL( const DString &strSQL )
{
   MAKEFRAMEAUTOPROMOTE( DISESSN_CONDITION, I_( "SQLDirect::executeSQL()" ) )

   m_pImpl->ExecuteSQL( strSQL );

   return(GETHIGHESTSEVERITY());
}

SEVERITY SQLDirect::connect( const DString &strSource )
{
   MAKEFRAMEAUTOPROMOTE( DISESSN_CONDITION, I_( "SQLDirect::connect()" ) )

   m_pImpl->Connect( strSource );

   return(GETHIGHESTSEVERITY());
}

SEVERITY SQLDirect::connect( const DString &strSource,
                             const DString &strUser,
                             const DString &strPassword )
{
   MAKEFRAMEAUTOPROMOTE( DISESSN_CONDITION, I_( "SQLDirect::connect()" ) )

   m_pImpl->Connect( strSource, strUser, strPassword );

   return(GETHIGHESTSEVERITY());
}

void SQLDirect::getError( DString &strError )
{
   m_pImpl->GetError( strError );
}

void SQLDirect::close()
{
   m_pImpl->Close();
}

SEVERITY SQLDirect::fetch()
{
   MAKEFRAMEAUTOPROMOTE( DISESSN_CONDITION, I_( "SQLDirect::fetch()" ) )

   m_pImpl->Fetch();

   return(GETHIGHESTSEVERITY());
}

int SQLDirect::getColumnID( const DString &strColumn )
{
   return(m_pImpl->GetColumnID( strColumn ));
}

Odbc::Type SQLDirect::getColumnType( int nCol )
{
   return(m_pImpl->GetColumnType( nCol ));
}

Odbc::Type SQLDirect::checkForColumnInTable( const DString &strColumn,
                                             const DString &strTable )
{
   return(m_pImpl->CheckForColumnInTable( strColumn, strTable ));
}

DString SQLDirect::getColumnData( int nCol )
{
   return(m_pImpl->GetCol( nCol ));
}

DString SQLDirect::getColumnData( const DString &strColumn )
{
   return(m_pImpl->GetCol( strColumn ));
}

DString SQLDirect::getColumnName( int nCol )
{
   return(m_pImpl->GetColumnName( nCol ));
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
// $Log:   Y:/VCS/BF Core/bfsessn/sqldirect.cpp-arc  $
//
//   Rev 1.3   Oct 22 2004 08:58:56   PURDYECH
//PET910 - .NET Conversion Fixes
//
//   Rev 1.2   Apr 20 2004 10:47:42   PURDYECH
//PTS10024114 - Integrate changes from KC to deal with Double Locking in AWD.
// 
//    Rev 1.1   Oct 09 2002 17:41:06   PURDYECH
// New PVCS Database
// 
//    Rev 1.0   28 May 2002 12:11:16   SMITHDAV
// Initial revision.
// 
//    Rev 1.2   13 Jan 2000 16:28:42   dt20842
// Added back in ODBC support
// 
//    Rev 1.1   Apr 22 1999 15:51:32   DMUM
// condition message changes
//
//    Rev 1.0   Apr 16 1999 17:50:50   DMUM
//
//
//    Rev 1.0   Feb 08 1999 10:49:10   DMUM
//
//
//

