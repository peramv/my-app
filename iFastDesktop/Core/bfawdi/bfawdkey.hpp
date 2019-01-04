#pragma once

/** 
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

//CP20021120/**@pkg BFAWDI */    

#include <commonport.h>
#include <dstring.hpp>

#undef BFAWDI_LINKAGE
#ifdef BFAWDI_DLL
   #define BFAWDI_LINKAGE CLASS_EXPORT
#else
   #define BFAWDI_LINKAGE CLASS_IMPORT
#endif

/**
 * An BFAwdKey provides an abstract interface for a key (primary index) to an
 * AWD object on an AWD server.
 *
 * The three components of an AWD key may be queried using this class.  Since
 * the instantiation of this class is specific to the actual implementation for
 * AWD interaction, this class is designed to be a pure virtual class.  New
 * instances may only be aquired through the method AwdInterface::newBFAwdKey().
 */
class BFAWDI_LINKAGE BFAwdKey
{
   // Constructors and Destructor
public:
   /**
    * Default constructor
    */
   BFAwdKey();

   /**
    * Destrucor
    */
   virtual ~BFAwdKey();

   // Public methods
public:
   /**
    * Used to determine if this instance represents an AWD object on an
    * AWD Server.
    *
    * @return True if representing a real AWD object.
    */
   virtual bool isKey() const = 0;

   /**
    * Dynamically makes a copy of this object.
    *
    * <b>Note:</b>  The caller of this method is resonsible for deleting
    * the copy.
    *
    * @return Pointer to the copy.
    */
   virtual BFAwdKey *makeCopy() const = 0;

   /**
    * Returns the creation date-time component of the key.  The returned
    * value will have a format of CCYY-MM-DD-HH.MM.SS.TTTTTT.
    *
    * @return The date and time the AWD object was created.
    */
   virtual DString getCreateDateTime() const = 0;

   /**
    * Returns the record code component of the key.  The returned value will
    * be either 'C' for case, 'T' for transaction, or 'O' for source.
    *
    * @return The record code.
    */
   virtual DString getRecordCode() const = 0;

   /**
    * Returns the create node component of the key.
    *
    * @return The create node.
    */
   virtual DString getCreateNode() const = 0;

   /**
    * Comparison operator.  This method will determine if the two keys are
    * equal.  That is, if they reference the same AWD object on an AWD
    * server.
    *
    * @param key - BFAwdKey to compare with.
    *
    * @return True if the two keys reference the same AWD object.
    */
   virtual bool operator ==( const BFAwdKey &key ) const = 0;
};




//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
// $Log:   Y:/VCS/BF Core/bfawdi/bfawdkey.hpp-arc  $
//
//   Rev 1.2   Nov 27 2002 14:51:40   PURDYECH
//Documentation Cleanup
//
//   Rev 1.1   Oct 09 2002 17:39:54   PURDYECH
//New PVCS Database
//
//   Rev 1.0   28 May 2002 12:11:18   SMITHDAV
//Initial revision.
// 
//    Rev 1.7   23 Oct 2000 13:19:38   dt14177
// cleanup
// 
//    Rev 1.6   Apr 24 2000 10:38:30   DMUM
//  
//
//    Rev 1.5   Apr 09 1999 13:26:18   DMUM
// Sync up with 1.6.x
//
//    Rev 1.4   Mar 09 1999 12:54:52   DT20842
// Changes for internationalization
//
//    Rev 1.3   Jan 28 1999 14:05:22   DMUM
// Check in for VCPP 6.0
//
//    Rev 1.2   Dec 09 1998 13:39:00   DMUM
// Check in for DICORE
//
//    Rev 1.1   Sep 09 1998 08:00:04   DMUM
// Added == operator
//
//    Rev 1.0   29 Jul 1998 20:36:10   DT14596
// DLMG New Archives for TA2000NTDT
//
//    Rev 1.5   Dec 16 1997 15:58:28   dmum
// Made Enhancements
//
//    Rev 1.4   10 Nov 1997 15:01:30   dmum
// Added redundancy guards and export/import guards
//
//    Rev 1.3   07 Aug 1997 13:48:18   dmum
// changed inlcude statement
//
//    Rev 1.2   17 Jul 1997 11:26:40   dmum
// Added methods to extract the three components of an AWD key
//
//    Rev 1.1   13 Jun 1997 15:15:40   dmum
// Documented headers
//
//    Rev 1.0   Apr 25 1997 11:15:16   dmum
//
//
//
//
//
