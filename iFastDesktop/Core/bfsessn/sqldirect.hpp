#pragma once

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
//    Copyright 1997, 1998, 1999, 2000 by DST Systems, Inc.
//
//******************************************************************************

#ifndef DIODBC_HPP
   #include <diodbc.hpp>
#endif

#ifndef SQLCOLUMN_HPP
   #include <bfsessn\sqlcolumn.hpp>
#endif

#ifndef CONDITIONMANAGER_HPP
   #include <conditionmanager.hpp>
#endif

#ifndef SQLDIRECTIMPL_HPP
class SQLDirectImpl;
#endif

/**
 * Interface class (portable) for a kernal of ODBC functionality
 */
class SQLDirect
{
public:
   /**
    * Default Constructor
    */
   SQLDirect();

   /**
    * Contructor.  Establishes a link with a data source.
    *
    * @param strSource - The name of the data source to link with.
    *
    * @exception ConditionException if connect fails.
    */
   SQLDirect( const DString &strSource );

   /**
    * Contructor.  Establishes a link with a secured data source.
    *
    * @param strSource - The name of the data source to link with.
    * @param strUser - User ID to use for the link.
    * @param strPassword - Password to use for the link.
    *
    * @exception ConditionException if connect fails.
    */
   SQLDirect( const DString &strSource,
              const DString &strUser,
              const DString &strPassword );

   /**
    * Destructor.
    */
   virtual ~SQLDirect();

public:
   /**
    * Sends the SQL statement to the data source.  The current cursor is
    * closed and reopened awaiting a new result set.
    *
    * @param strSQL - SQL statement
    *
    * @return The highest SEVERITY encountered.
    */
   virtual SEVERITY executeSQL( const DString &strSQL );

   /**
    * Establishes a connection to an ODBC data source
    *
    * @param strSource - Data source to connect with.
    *
    * @return SEVERITY - The severity will be INFORMATIONAL if the
    *                    connection is successful and there was a message.
    *
    * @exception ConditionException if connection fails
    */
   virtual SEVERITY connect( const DString &strSource );

   /**
    * Establishes a connection to an ODBC data source with security.
    *
    * @param strSource - Data source to connect with.
    * @param strUser - User ID to use for the connection.
    * @param strPassword - Password to use for the connection.
    *
    * @return SEVERITY - The severity will be INFORMATIONAL if the
    *                    connection is successful and there was a message.
    *
    * @exception ConditionException if connection fails
    */
   virtual SEVERITY connect( const DString &strSource,
                             const DString &strUser,
                             const DString &strPassword );

   /**
    * The will get the last error or message from the data source and or
    * its driver.  For the most part, these messaged will be set as
    * condition objects as the error or informational massage occurs.  In
    * the case of Connecting, this method is called internally before
    * throwing the ConditionException.
    *
    * @param strError - DString object to receive the error message.
    */
   virtual void getError( DString &strError );

   /**
    * This only closes the current cursor and then opens a new one.  The
    * connection is only closed when the destructor is called.
    */
   void close();

   /**
    * This will get the next row in the cursor (result set).
    *
    * @return The highest SEVERITY found.
    */
   SEVERITY fetch();

   /**
    * If the column exists in the current cursor (result set) this will
    * return the id of the column, else it will return a -1.
    *
    * @param strColumn - The name of column to find.
    *
    * @return ID of the column (-1 if not found).
    */
   int getColumnID( const DString &strColumn );

   /**
    * This will return the column type for the current cursor (result set).
    * If the column ID is invalid, then ODBC::sqlUnkown is returned.
    *
    * @param nCol - Column ID.
    *
    * @return The column type.
    */
   Odbc::Type getColumnType( int nCol );

   /**
    * If the column exists in the table, then the column type will be
    * returned.  If the column type is not supported or the column does not
    * exist in the table, then this will return ODBC::sqlUnkown.
    *
    * @param strColumn - Column to find.
    * @param strTable - Table to look in.
    *
    * @return The cloumn type.
    */
   Odbc::Type checkForColumnInTable( const DString &strColumn,
                                     const DString &strTable );

   /**
    * This will return the data value for the column IDed in the current
    * cursor (result set) for the current row.
    *
    * @param nCol - Column ID.
    *
    * @return Data value.
    */
   DString getColumnData( int nCol );

   /**
    * This will return the data value for the column named in the current
    * cursor (result set) for the current row.
    *
    * @param strColumn - Column name.
    *
    * @return Data value.
    */
   DString getColumnData( const DString &strColumn );

   /**
    * This will return the name of the column IDed in the current cursor
    * (result set).
    *
    * @param nCol - Column ID.
    *
    * @return The column name.
    */
   DString getColumnName( int nCol );

private:
   SQLDirectImpl *m_pImpl;
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
// $Log:   //db3n5j11/d/scc/ifds/core/archives/bfsessn/sqldirect.hpp-arc  $
//
//   Rev 1.1   Oct 09 2002 17:41:08   PURDYECH
//New PVCS Database
//
//   Rev 1.0   28 May 2002 12:11:24   SMITHDAV
//Initial revision.
// 
//    Rev 1.2   Apr 24 2000 10:38:44   DMUM
//  
//
//    Rev 1.1   Apr 19 1999 12:59:16   DTWK
//
//
//    Rev 1.0   Apr 16 1999 17:50:56   DMUM
//
//
//    Rev 1.0   Feb 08 1999 10:51:44   DMUM
//
//
//


