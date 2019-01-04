#ifndef INSTANCEFIELDINFO_HPP
#define INSTANCEFIELDINFO_HPP

/** 
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


#ifndef  FLAGITEMLIST_HPP
#include "flagitemlist.hpp"
#endif

#ifndef STRINGLIST_HPP
#include "stringlist.hpp"
#endif

#ifndef COMMONPORT_H
#include "commonport.h"
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
 * This class provides management of field values, masks, and flags.
 *
 * Each field has a mask (which can be empty) and a set of flags that
 * pertain to that field.  Fields and masks are accessed by their
 * zero-based index.  Additionally, any number of flags can be
 * associated with each field.  These flags are user-defined and can
 * have any values.
 *
 * This class is a specialization of FlagItemList in which each "item"
 * is a field. */
class CBOBASE_LINKAGE InstanceFieldInfo : public FlagItemList
{
   // Public Methods
   public:

      /** Retrieve the DString mask of the nth field.
       *  @param nField Zero based index of the field whose mask is being retrieved.
       *  @return String mask. 
       */
      const DString& getMask( int nField ) const;

      /** Retrieve the DString mask of the nth field.
       *  @param nField Zero based index of the field whose mask is being retrieved.
       *  @param strMask String (by reference) that will contain the requested mask.
       *  @return Nothing.  
       */
      void getMask( int nField, DString& strMask ) const;

      /** Retrieve the DString value of the nth field.
       * @param nField Zero based index of the field whose value is being retrieved.
       * @return String value.
       */
      const DString& getValue( int nField ) const;

      /** Retrieve the DString value of the nth field.
       * @param nField Zero based index of the field whose value is being retrieved.
       * @param strValue String (by reference) that will contain the requested value.
       * @return Nothing.  
       */
      void getValue( int nField, DString& strValue ) const;

      /** Constructor
       *  @param nFlags Number of flags to store for each field
       *  @param nFields Number of fields to manage
       *  @param ulGroupFlag Initial group flag (bit flags)  
       */
      InstanceFieldInfo( int nFlags = 0,
                         int nFields = 0,
                         unsigned long ulGroupFlag = 0x0000 );

      /** Copy constructor
       *  @param copy Instance to clone 
       */
      InstanceFieldInfo( const InstanceFieldInfo& copy );

      /** Destructor */
      ~InstanceFieldInfo();

      /** Assignment operator */
      InstanceFieldInfo& operator=( const InstanceFieldInfo& copy );

      /** Change the mask of the nth field.
       *  @param nField Zero based index of the field whose mask is to change.
       *  @param strMask New DString mask.
       *  @returns true if successful / false if failure.
       */
      bool setMask( int nField, const DString& strMask );
 
      /** Change the DString value of the nth field.
       *  @param nField Zero based index of the field whose value is to change.
       *  @param strValue New DString value.
       *  @returns true if successful / false if failure. 
       */
      bool setValue( int nField, const DString& strValue );


   // Private Data
   private:
      int                  _nFields;          // How many fields
      StringList           _fieldStringList;
      StringList           _maskStringList;

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
// $Log:   Y:/VCS/iFastAWD/inc/instancefieldinfo.hpp-arc  $
//
//   Rev 1.0   28 Jan 2008 13:31:56   kovacsro
//Initial revision.
// 
//    Rev 1.7   28 Nov 2001 12:41:56   dt14177
// fixed linkage define
// 
//    Rev 1.6   Dec 26 2000 15:47:08   dt39990
// Organized methods in alphabetical listing
// 
//    Rev 1.5   Jan 05 2000 07:09:30   DT29758
// Java-doc Modifications
// 
//    Rev 1.3   Jan 04 2000 04:46:20   DT29758
//  
// 
//    Rev 1.2   Dec 30 1999 08:04:38   DT29758
// Modified comments to Java-Doc style
// 
//    Rev 1.1   Nov 11 1999 16:32:02   DT29758
// added unicode support and utilization of
// indexes for data object fields
// 
//    Rev 1.0   Jun 21 1999 17:15:10   DT22388
//  
// 
//    Rev 1.2   Mar 17 1999 14:50:32   DT21815
// Added ccdoc comments/documentation.
// 
//    Rev 1.1   Jan 14 1999 11:15:36   DT21815
// Changed #include file names to lower case.
// 
//    Rev 1.0   29 Jul 1998 23:58:32   dt14596
// DLMG New Archives for TA2000NTDT
// 
//    Rev 1.3   Nov 11 1997 08:43:10   djoo
// Added Redundant Include Guards and import/export protection.
// 
//    Rev 1.2   Jul 16 1997 15:16:54   DPQD
// Added capability of storing field masks.  Changed data
// members to use new class 'StringList' for storing field values
// and field masks.
//
//    Rev 1.1   Jul 10 1997 17:36:36   DPQD
// Made to inherit from FlagItemList.
//
// Removed methods that have been pushed up to FlagItemList
//
//


#endif

