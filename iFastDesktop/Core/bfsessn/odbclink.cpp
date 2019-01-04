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
// ^FILE   : ODBCLink.cpp
// ^AUTHOR : Mark Tarantino
// ^DATE   : 27 Jan 1999
//
// ----------------------------------------------------------
//
// ^CLASS    : ODBCLink
//
// ^MEMBER VARIABLES : none
//
// ^CODING COMMENTS  :
//
//******************************************************************************
#include "win32/stdafx.h"

#ifndef ODBCLINK_HPP
   #include "odbclink.hpp"
#endif

#ifndef DIODBC_H
   #include <diodbc.h>
#endif

#ifndef STRINGFUNCTIONS_HPP
   #include <stringfunctions.hpp>
#endif

#ifndef CONDITIONMANAGER_HPP
   #include <conditionmanager.hpp>
#endif

//******************************************************************************
//              Public Methods
//******************************************************************************

ODBCLink::ODBCLink()
: SQLDirect()
{
   TRACE_CONSTRUCTOR( I_( "ODBCLink" ), I_( "ODBCLink()" ) )
}

ODBCLink::ODBCLink( const DString &strSource )
: SQLDirect( strSource )
{
   TRACE_CONSTRUCTOR( I_( "ODBCLink" ), I_( "ODBCLink( const DString & )" ) )
}

ODBCLink::ODBCLink( const DString &strSource,
                    const DString &strUser,
                    const DString &strPassword )
: SQLDirect( strSource, strUser, strPassword )
{
   TRACE_CONSTRUCTOR( I_( "ODBCLink" ),
                      I_( "ODBCLink( const DString &, const DString &, const DString & )" ) )
}

ODBCLink::~ODBCLink()
{
   TRACE_DESTRUCTOR( I_( "ODBCLink" ) )
}

// Single Call to process Idi strings and add to DB
SEVERITY ODBCLink::addRow( const DString &strTable,
                           const DString &strIdiData )
{
   return(addRow( strTable, strIdiData, false ));
}

SEVERITY ODBCLink::addRow( const DString &strTable,
                           const DString &strIdiData,
                           const bool softColumnCheck  )
{
   MAKEFRAMEAUTOPROMOTE( DIODBC_CONDITION, I_( "ODBCLink::addRow()" ) )

   int index = 0;
   int count = 0;
   int position = 0;

   DString tag;
   DString value;
   DString pair;
   DString colomnList;
   DString valueList;

   Odbc::Type tType;

   while( ( position = strIdiData.find( ';', index ) ) != DString::npos )
   {
      count = position - index;
      pair = strIdiData.substr( index, count );
      index = position + 1;

      // Make sure there is an '='
      position = pair.find( '=' );

      if( DString::npos != position )
      {
         tag = pair.substr( 0, position );

         // Make sure the Tag is a column in the table
         tType = checkForColumnInTable( tag, strTable );

         if( ( Odbc::sqlUnknown == tType ) && softColumnCheck )
         {
            tType = Odbc::sqlChar;
         }

         if( Odbc::sqlUnknown != tType )
         {
            value = pair.substr( position + 1 );
            strip( value );

            // Make sure the value is not empty
            if( ! value.empty() )
            {
               // We have a tag = value !!!!!

               if( colomnList.size() > 0 )
               {
                  colomnList += I_( "," );
                  valueList += I_( "," );
               }

               // Set Column Name
               colomnList += tag;

               // Set Value
               if( Odbc::sqlChar == tType )
               {
                  valueList += '\'';
               }

               valueList += value;

               if( Odbc::sqlChar == tType )
               {
                  valueList += '\'';
               }
            }
         }
      }
   } // End While

   DString strSQL = I_( "INSERT INTO " );
   strSQL += strTable;
   strSQL += I_( " (" );
   strSQL += colomnList;
   strSQL += I_( ") VALUES (" );
   strSQL += valueList;
   strSQL += I_( ")" );

   executeSQL( strSQL );

   return(GETHIGHESTSEVERITY());
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
// $Log:   Y:/VCS/BF Core/bfsessn/odbclink.cpp-arc  $
//
//   Rev 1.2   Oct 22 2004 08:58:48   PURDYECH
//PET910 - .NET Conversion Fixes
// 
//    Rev 1.1   Oct 09 2002 17:41:06   PURDYECH
// New PVCS Database
// 
//    Rev 1.0   28 May 2002 12:11:14   SMITHDAV
// Initial revision.
// 
//    Rev 1.1   Jun 09 1999 16:21:26   DMUM
// Now supports soft column check to work with an
// ODBC Source that is a text file.
//
//    Rev 1.0   Apr 16 1999 17:50:34   DMUM
//
//
//    Rev 1.0   Feb 08 1999 10:49:08   DMUM
//
//
//
