#ifndef CBOINSTANCEOBJECTINFO_HPP
#define CBOINSTANCEOBJECTINFO_HPP

/** 
 *    COPYRIGHT:
 *
 *    The computer systems, procedures, data bases and
 *    programs created and maintained by DST Systems, Inc.,
 *    are proprietary in nature and as such are confidential.
 *    Any unauthorized use or disclosure of such information
 *    may result in civil liabilities.
 *
 *    Copyright 1999 by DST Systems, Inc.
 */

/**@pkg DICBOCORE */    


#ifndef INCLUDED_VECTOR
#include <vector>
#define INCLUDED_VECTOR
#endif

#ifndef FLAGITEMLIST_HPP
#include "flagitemlist.hpp"
#endif

#ifndef CBOBASE_HPP
#include "cbobase.hpp"
#endif

#ifndef COMMONPORT_H
#include "commonport.h"
#endif

// Import/Export resolution
#undef CBOBASE_LINKAGE
#ifdef DICBOCORE_DLL
    #define CBOBASE_LINKAGE CLASS_EXPORT
#else
    #define CBOBASE_LINKAGE CLASS_IMPORT
#endif

/**@#-*/
using namespace std;
/**@#+*/

// Forward declare Data object;
class Data;


/**
 * This class provides management of CBO objects and their flags.
 *
 * Objects are accessed by their zero-based index.  Additionally,
 * any number of flags can be associated with each object.  These
 * flags are user-defined and can have any values.
 *
 * This class is a specialization of FlagItemList in which each "item"
 * is a CBO object.
 *
 * The concept of "ownership" in this class (isOwnedObject, makeUnowned,
 * and makeOwned) reflects whether or not an instance of this class
 * should delete the CBO objects on destruction.  Ownership status can
 * vary from one managed CBO object to another.
 * <BR><BR> */
class CBOBASE_LINKAGE CBOInstanceObjectInfo : public FlagItemList
{
   public:

      /** Constructor
       * @param nObject Number of CBO objects to manage
       * @param ulGroupFlag Initial group bit flags 
       */
      CBOInstanceObjectInfo( int nObjects,
                             unsigned long ulGroupFlag = 0x0000 );

      /** Copy constructor */
      CBOInstanceObjectInfo( const CBOInstanceObjectInfo& copy );

      /** Destructor */
      ~CBOInstanceObjectInfo();

      /** Assignment operator */
      CBOInstanceObjectInfo& operator=( const CBOInstanceObjectInfo& copy );

      /** Retrieve the nth CBO object.
       *  @param nPosition Zero based index of the object to retrieve.
       *  @returns const pointer to CBO object.  
       */
      const CBOBase * getConstObject( int nPosition ) const;

      /** Retrieve the nth CBO object.
       *  @param nPosition Zero based index of the object to retrieve.
       *  @returns Pointer to CBO object. 
       */
      CBOBase * getObject( int nPosition );

      /** Determines if the nth CBO object is owned by us.
       *  @param nPosition Zero based index of the CBO object to examine.
       *  @returns boolean indicating whether we own the specified CBO object.  
       */
      bool isOwnedObject( int nPosition ) const;

      /** Takes ownership of the specified CBO object.
       *  @param nPosition Zero based index of the CBO object that we will now own.
       *  @returns true if successful / false if failure.  
       */
      bool makeOwned( int nPosition );

      /** Removes our ownership of the specified CBO object.
       *  @param nPosition Zero based index of the CBO object that we're relinquishing our ownership.
       *  @returns true if successful / false if failure.  
       */
      bool makeUnowned( int nPosition );

      /** Change the CBO object value of the nth object.
       *  @param nPosition Zero based index of the object to change.
       *  @param pObject Pointer to new CBO object.
       *  @param fObjectIsOwned Boolean indicating whether the passed object will be owned by us.
       *  @returns true if successful / false if failure.  
       */
      bool setObject( int nPosition, CBOBase * pObject, bool fObjectIsOwned );


   private:
      CBOInstanceObjectInfo();

   private:
      int                           _nObjects;
      vector< CBOBase * >           _vecCBO;
      vector< bool >                _vecCBOOwnedFlags;
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
// $Log:   Y:/VCS/iFastAWD/inc/cboinstanceobjectinfo.hpp-arc  $
//
//   Rev 1.0   28 Jan 2008 13:30:16   kovacsro
//Initial revision.
// 
//    Rev 1.4   28 Nov 2001 12:41:50   dt14177
// fixed linkage define
// 
//    Rev 1.3   Dec 26 2000 15:38:52   dt39990
// Organized methods in alphabetical listing
// 
//    Rev 1.2   Jan 04 2000 04:46:14   DT29758
//  
// 
//    Rev 1.1   Dec 30 1999 08:04:24   DT29758
// Modified comments to Java-Doc style
// 
//    Rev 1.0   Jun 21 1999 17:07:14   DT22388
//  
// 
//    Rev 1.2   Mar 17 1999 15:04:16   DT21815
// Added ccdoc comments/documentation.
// 
//    Rev 1.1   Jan 14 1999 11:50:42   DT21815
// Changed #include file names to lower case.
// 
//    Rev 1.0   29 Jul 1998 23:58:12   dt14596
// DLMG New Archives for TA2000NTDT
// 
//    Rev 1.7   Mar 10 1998 14:44:08   DT21815
// Added comment header block and comment revision block.
//
//


#endif

