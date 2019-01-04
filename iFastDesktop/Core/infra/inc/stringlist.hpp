#ifndef STRINGLIST_HPP
#define STRINGLIST_HPP

/*
 *    COPYRIGHT:
 *
 *    The computer systems, procedures, data bases and
 *    programs created and maintained by DST Systems, Inc.,
 *    are proprietary in nature and as such are confidential.
 *    Any unauthorized use or disclosure of such information
 *    may result in civil liabilities.
 *
 *    Copyright 1999-2000 by DST Systems, Inc.
 */

/**@pkg DICBOCORE */

#ifndef  DSTRING_HPP
#include "dstring.hpp"
#endif


#ifndef COMMONPORT_H
#include "commonport.h"
#endif

#ifndef MUTEXSEMAPHORE_HPP
#include "mutexsemaphore.hpp"
#endif

/**@#-*/
using namespace std;
/**@#+*/

// Import/Export resolution
#undef CBOBASE_LINKAGE
#ifdef DICBOCORE_DLL
    #define CBOBASE_LINKAGE CLASS_EXPORT
#else
    #define CBOBASE_LINKAGE CLASS_IMPORT
#endif


/**
 * This class provides management of a linear collection of strings.
 *
 * This class manages the values for a number of strings.  The number
 * of strings that are contained in the list must be passed to the
 * constructor.  The "sets" and "gets" operate on zero-based index
 * values.
 *
 * The class provides minimal range checking for the zero-based DString
 * number in the "set" and "get" methods. */
class CBOBASE_LINKAGE StringList
{
   // Public Methods
   public:

      /**
       * Retrieve the string value of the nth string.
       * @param nString Zero based index of the string to retrieve.
       * @returns string value. 
       */
      const DString& getValue( int nString ) const;

      /**
       * Retrieve the DString value of the nth DString.
       * @param nString Zero based index of the DString to retrieve.
       * @param strValue Reference to the DString object that will contain the retrieved value.
       * @returns Nothing.     
       */
      void getValue( int nString, DString& strValue ) const;

      /** Assignment operator */
      StringList& operator=( const StringList& copy );
      
      /**
       * Call this method to turn on or off multithreading safeguards.
       *
       * @param multiThread  - True to enable, false to disable
       */
      static void safeGuardMultiThread( const bool multiThread = true );

      /**
       * Change the DString value of the nth DString.
       * @param nString Zero based index of the DString to change.
       * @param strValue New DString value.
       * @returns true if successful / false if failure. 
       */
      bool setValue( int nString, const DString& strValue );

      /**
       * Constructor
       * @param nStrings Number of strings to store in list  
       */
      StringList( int nStrings );

      /** Copy constructor */
      StringList( const StringList& copy );

      /** Destructor */
      ~StringList();



   // Private Data
   private:
      int               _nStrings;          // How many strings
      DString         *  _pStrings;          // Pointer to array of strings
      MutexSemaphore    _mutex;             // Thread safety

      static bool       _bMultiThread;      // Safegaurd for multithreading
};




//************************************************************************
//              Revision Control Entries
//************************************************************************
//
// Name:
//    %PM%
//    %PID%
//
// Description:
//    %PD%
//
// Design Parts:
//    %PIRP%
//
// Last Changed:
//    %PO%  -  %PRT%
//
// Changes:
//    %PLA%
//
//
// $Log:   Y:/VCS/iFastAWD/inc/stringlist.hpp-arc  $
//
//   Rev 1.0   28 Jan 2008 13:32:50   kovacsro
//Initial revision.
// 
//    Rev 1.10   28 Nov 2001 12:42:08   dt14177
// fixed linkage define
// 
//    Rev 1.9   Dec 26 2000 15:47:50   dt39990
// Organized methods in alphabetical listing
// 
//    Rev 1.8   28 Nov 2000 10:43:26   dt14177
// cleanup
// 
//    Rev 1.7   28 Nov 2000 10:39:12   dt14177
// cleanup
// 
//    Rev 1.6   Apr 04 2000 09:30:18   dtwk
// Syncup with 1.7 threading fixes
// 
//    Rev 1.5   Jan 05 2000 07:22:32   DT29758
// Java-doc modification
// 
//    Rev 1.3   Jan 04 2000 04:46:28   DT29758
//  
// 
//    Rev 1.2   Dec 29 1999 13:46:40   DT29758
// Modified comments to fit JavaDoc standard
// 
//    Rev 1.1   Nov 11 1999 16:32:42   DT29758
// added unicode support and utilization of
// indexes for data object fields
// 
//    Rev 1.0   Jun 21 1999 17:15:40   DT22388
//  
// 
//    Rev 1.2   Mar 17 1999 14:50:06   DT21815
// Added ccdoc comments/documentation.
// 
//    Rev 1.1   Jan 14 1999 11:18:12   DT21815
// Changed #include file names to lower case.
// 
//    Rev 1.0   29 Jul 1998 23:58:50   dt14596
// DLMG New Archives for TA2000NTDT
// 
//    Rev 1.2   Apr 10 1998 09:59:36   djoo
// Modified redundant include guard for
// string.
// 
//    Rev 1.1   Nov 11 1997 08:49:00   djoo
// Added Redundant Include Guards and import/export protection.
// 
//    Rev 1.0   16 Jul 1997 15:26:18   dmal
//  
//
//



#endif


