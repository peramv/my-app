#ifndef DATAPATH_H
#define DATAPATH_H

/*
 *    COPYRIGHT:
 *
 *    The computer systems, procedures, data bases and
 *    programs created and maintained by DST Systems, Inc.,
 *    are proprietary in nature and as such are confidential.
 *    Any unauthorized use or disclosure of such information
 *    may result in civil liabilities.
 *
 *    Copyright 1996-2000 by DST Systems, Inc.
 */

#ifndef INCLUDED_STRING
   #define INCLUDED_STRING
   #include <string>
#endif

#ifndef DSTRING_HPP
   #include <dstring.hpp>
#endif
extern "C" {
   DICORE_LINKAGE void SetGlobalDataPath( const DString& dataPath );
   DICORE_LINKAGE const DString& GetGlobalDataPath( const DString& dataPath );
   DICORE_LINKAGE void SetGlobalIniPath( const DString& iniPath );
   DICORE_LINKAGE const DString& GetGlobalIniPath( const DString& iniPath );
}


/**
 * Gets the path for the company default,
 * "DST"
 * 
 * @param path   - (in/out)
 * @param app    - the application name
 * @return - true, if the application name exists in the
 *         path or environment
 */
bool GetDataPath( DString &path, const DString &app );

/**
 * Gets the path for the application
 * 
 * @param path   - (in/out)
 * @param app    - the application name
 * @param company - the company name
 * @return - true, if the application name exists in the
 *         path or environment
 */
bool GetDataPath( DString &path, const DString &app, const DString &company );

/**
 * Gets the path for the company default,
 * "DST"; it looks at the INI path first, then
 * the data path
 * 
 * @param path   - (in/out)
 * @param app    - the application name
 * @param company - the company name
 * @return - true, if the application name exists in the
 *         path or environment
 */
bool GetIniPath( DString &path, const DString &app );

/**
 * Gets the path for the application;
 * it looks at the INI path first, then
 * the data path
 * 
 * @param path   - (in/out)
 * @param app    - the application name
 * @param company - the company name
 * @return - true, if the application name exists in the
 *         path or environment
 */
bool GetIniPath( DString &path, const DString &app, const DString &company );

/**
 * Returns a pointer to a string containing
 * the path delimiter
 * 
 * @return 
 */
const I_CHAR * GetPathDelemiter();

/**
 * Searches the registry for a key which
 * has the same name as the application
 * in "SOFTWARE\DST\DICORE"; it
 * then returns the value of the key
 * in the parameter location
 * 
 * @param strApp - (out) the name of the Configuration
 *               object associated with the application
 * @return true, if the application name is found in
 *         the registry
 */
bool FindApplication( DString &strApp );

/**
 * Returns the application name and path
 * 
 * @param strPath - (out) the path from where the application
 *                is run
 * @param strFile - (out) the name of the application
 */
void GetApplicationPathAndFile( DString &strPath, DString &strFile );

/**
 * Returns the application  path
 * 
 * @param strPath - (out) the path from where the application
 *                is run
 */
void GetApplicationPath( DString &strPath );

/**
 * Returns the application name 
 * 
 * @param strFile - (out) the name of the application
 */
void GetApplicationFile( DString &strFile );

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/core/ifdscore/datapath.h-arc  $
//
//   Rev 1.2   Aug 27 2009 08:59:10   purdyech
//Allow global override of IniPath and DataPath.  Used by XML configuration logic.
//
//   Rev 1.1   Oct 09 2002 17:41:54   PURDYECH
//New PVCS Database
//
//   Rev 1.0   Jul 05 2002 10:14:02   SMITHDAV
//Initial revision.
// 
//    Rev 1.8   12 Dec 2000 17:02:52   dt14177
// documentation
// 
//    Rev 1.7   07 Dec 2000 13:13:32   dt14177
// cleanup
// 
//    Rev 1.6   Jun 09 1999 09:51:36   DMUM
// If the DataPath is not found, config now uses the application path
//
//    Rev 1.5   Apr 27 1999 17:54:14   DMUM
// Changes for finding an application when setApplication()
// has not yet been found
//
//    Rev 1.4   22 Feb 1999 13:57:28   DT14177
// more UNICODE stuff
//
//    Rev 1.3   18 Feb 1999 10:38:02   DT14177
// UNICODE
//
//    Rev 1.2   Jan 28 1999 14:02:42   DMUM
// Check in for VCPP 6.0
//
//    Rev 1.1   Jan 28 1999 13:43:20   DMUM
// Check in for VCPP 6.0
//
//    Rev 1.0   Dec 09 1998 13:51:04   DMUM
//
//

#endif // DATAPATH_H

