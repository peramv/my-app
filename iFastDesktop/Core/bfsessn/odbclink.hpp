#pragma once

/* 
 *    COPYRIGHT:
 *
 *    The computer systems, procedures, data bases and
 *    programs created and maintained by DST Systems, Inc.,
 *    are proprietary in nature and as such are confidential.
 *    Any unauthorized use or disclosure of such information
 *    may result in civil liabilities.
 *
 *    Copyright 1997-2000 by DST Systems, Inc.
 */

#ifndef DIODBC_HPP
   #include <diodbc.hpp>
#endif

#ifndef SQLDIRECT_HPP
   #include <bfsessn\sqldirect.hpp>
#endif

/**
 * This class represents a link to an ODBC data source
 */
class ODBCLink : public SQLDirect
{
public:
   /**
    * Default Constructor
    */
   ODBCLink();

   /**
    * Contructor.  Establishes a link with a data source.
    *
    * @param strSource - The name of the data source to link with.
    *
    * @exception ConditionException if connect fails.
    */
   ODBCLink( const DString &strSource );

   /**
    * Contructor.  Establishes a link with a secured data source.
    *
    * @param strSource - The name of the data source to link with.
    * @param strUser - User ID to use for the link.
    * @param strPassword - Password to use for the link.
    *
    * @exception ConditionException if connect fails.
    */
   ODBCLink( const DString &strSource,
             const DString &strUser,
             const DString &strPassword );

   /**
    * Destructor.
    */
   virtual ~ODBCLink();

   // Implementation
public:
   /**
    * Adds a single row to a table in the data source.
    *
    * @param strTable - Table in which the row is to be added
    * @param strIdiData - The data to add: column=value;...
    *
    * @return The highest SEVERITY found.
    */
   SEVERITY addRow( const DString &strTable,
                    const DString &strIdiData );

   /**
    * Adds a single row to a table in the data source.
    *
    * @param strTable - Table in which the row is to be added
    * @param strIdiData - The data to add: column=value;...
    * @param softColumnCheck - If true, then the columns are not verified.
    *                          If false, only data for columns that have
    *                          been verified will be passed.
    *
    * @return The highest SEVERITY found.
    */
   SEVERITY addRow( const DString &strTable,
                    const DString &strIdiData,
                    const bool softColumnCheck );
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
// $Log:   //db3n5j11/d/scc/ifds/core/archives/bfsessn/odbclink.hpp-arc  $
//
//   Rev 1.1   Oct 09 2002 17:41:06   PURDYECH
//New PVCS Database
//
//   Rev 1.0   28 May 2002 12:11:24   SMITHDAV
//Initial revision.
// 
//    Rev 1.4   22 Nov 2000 11:13:40   dt14177
// cleanup
// 
//    Rev 1.3   Apr 24 2000 10:38:40   DMUM
//  
//
//    Rev 1.2   Jun 09 1999 16:21:34   DMUM
// Now supports soft column check to work with an
// ODBC Source that is a text file.
//
//    Rev 1.1   Apr 19 1999 12:59:12   DTWK
//
//
//    Rev 1.0   Apr 16 1999 17:50:38   DMUM
//
//
//    Rev 1.0   Feb 08 1999 10:51:40   DMUM
//
//
//


