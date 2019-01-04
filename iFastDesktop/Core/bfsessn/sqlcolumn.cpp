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
//******************************************************************************
//
// ^FILE   : SQLColumn.cpp
// ^AUTHOR : Mark Tarantino
// ^DATE   : 27 Jan 1999
//
// ----------------------------------------------------------
//
// ^CLASS    : SQLColumn
//
// ^MEMBER VARIABLES :
//
//   ^^ DString      m_strValue - value of the data
//   ^^ Odbc::Type   m_tType    - data type
//   ^^ int          m_nCol     - column id
//
// ^CODING COMMENTS  :
//
//******************************************************************************
#include "win32\stdafx.h"

#include <srcprag.h>
#include "sqlcolumn.hpp"


//******************************************************************************
//              Public Methods
//******************************************************************************

SQLColumn::SQLColumn()
: m_strValue( I_( "" ) ), m_nCol( 0 ), m_tType( Odbc::sqlDefault )
{
}

SQLColumn::SQLColumn( const DString &strValue, int col, Odbc::Type type )
: m_strValue( strValue ), m_nCol( col ), m_tType( type )
{
}

SQLColumn::SQLColumn( const SQLColumn &copy )
{
   this->operator =( copy );
}

SQLColumn::~SQLColumn()
{
}

void SQLColumn::setValue( const DString &strValue )
{
   m_strValue = strValue;
}

void SQLColumn::setColumn( int col )
{
   m_nCol = col;
}

void SQLColumn::setType( Odbc::Type type )
{
   m_tType = type;
}

SQLColumn &SQLColumn::operator=( const SQLColumn &copy )
{
   if( this != &copy )
   {
      this->m_strValue = copy.m_strValue;
      this->m_nCol     = copy.m_nCol;
      this->m_tType    = copy.m_tType;
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
// $Log:   Y:/VCS/BF Core/bfsessn/sqlcolumn.cpp-arc  $
//
//   Rev 1.4   Oct 22 2004 08:58:54   PURDYECH
//PET910 - .NET Conversion Fixes
//
//   Rev 1.3   Apr 20 2004 10:47:40   PURDYECH
//PTS10024114 - Integrate changes from KC to deal with Double Locking in AWD.
// 
//    Rev 1.2   Oct 09 2002 17:41:06   PURDYECH
// New PVCS Database
// 
//    Rev 1.1   Sep 23 2002 14:40:58   PURDYECH
// made #include stdafx.h explicitly refer to win32 directory.
// 
//    Rev 1.0   28 May 2002 12:11:14   SMITHDAV
// Initial revision.
// 
//    Rev 1.0   Apr 16 1999 17:50:42   DMUM
//  
//
//    Rev 1.0   Feb 08 1999 10:49:10   DMUM
//
//
//




