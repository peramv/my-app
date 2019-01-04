#ifndef FLAGITEMLIST_HPP
#define FLAGITEMLIST_HPP

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


#ifndef INCLUDED_STRING
#include <string>
#define INCLUDED_STRING
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
 * This class provides management of bit flags.
 *
 * This class provides the management of any number of
 * bit flags (binary values) for any number of items, as well
 * as an overall "group" bit flag for the object as a whole.
 *
 * Example:
 * 
 * Suppose that we're writing a system for a hospital.  Each
 * on-duty nurse cares for a number of patients.  For each
 * patient under the nurse's care, we need to track the status
 * for each of the following: (a) requires surgery? (y/n),
 * (b) restricted diet? (y/n), (c) visitors allowed? (y/n).
 * Each status is a binary value (yes or no).  Instead of having
 * to code collections of boolean variables in our nurse class,
 * we can use this class to efficiently track these flags for us.
 *
 * For the nurse class, we can use FlagItemList as follows:
 *   Each patient will be an item, and each patient status will be 
 *   a flag.
 *
 * The FlagItemList class could be used as follows in implementing
 * the Nurse class.  The use of "enum" is not required, but in many 
 * cases the * enum provides a nice balance of type safety and 
 * generic use (maps directly to int).
 * <pre><dir>
 *
 * class Nurse
 * {
 *   public:
 *      enum PATIENT_STATUS
 *      {
 *         REQUIRES_SURGERY,
 *         RESTRICTED_DIET,
 *         VISITORS_ALLOWED,
 *         MAX_PATIENT_STATUS
 *      };
 *
 *      Nurse( int NumberPatients ) :
 *         m_NumberPatients( NumberPatients ),
 *         m_PatientFlags( MAX_PATIENT_STATUS, m_NumberPatients )
 *      {
 *      }
 *
 *      bool getPatientStatus( int patientNumber,
 *                             PATIENT_STATUS status )
 *      {
 *         return m_PatientFlags.isFlagSet( status, patientNumber );
 *      }
 *
 *      void setPatientStatus( int patientNumber,
 *                             PATIENT_STATUS status,
 *                             bool statusApplies )
 *      {
 *         if ( statusApplies )
 *         {
 *            m_PatientFlags.setFlag( status, patientNumber );
 *         }
 *         else
 *         {
 *            m_PatientFlags.clearFlag( status, patientNumber );
 *         }
 *      }
 *
 *   private:
 *     int m_NumberPatients;
 *     FlagItemList m_PatientFlags;
 * };                                    
 */
class CBOBASE_LINKAGE FlagItemList
{
   // Public Methods
   public:

      /** Turns off (clears) the nth flag of the nth item.
       *  @param nFlag - Zero based index of the flag to clear.
       *  @param nItem - Zero-based index of the item whose flag 
       *                 will be cleared.
       *  @returns Boolean indicating whether the flag was
       *           successfully cleared. 
       */
      bool clearFlag( int nFlag, int nItem );

      /** Turns off (clears) the specified group bit flag(s).
       *  @param ulGroupFlag Group bit flag(s) to clear.
       *  @returns Boolean indicating whether the group bit flag(s)
       *           was successfully cleared. 
       */
      bool clearGroupFlag( unsigned long ulGroupFlag );

      /** Constructor
       *  @param nFlags - Number of bit flags to manage
       *  @param nItems - Number of items that require individual 
       *                  bit flag management
       *  @param ulGroupFlag Initial group bit flag 
       */
      FlagItemList( int nFlags = 0,
                    int nItems = 0,
                    unsigned long ulGroupFlag = 0x0000 );
                    
      /** Copy constructor */
      FlagItemList( const FlagItemList& copy );

      /** Destructor */
      ~FlagItemList();

      /** Assignment operator */
      FlagItemList& operator=( const FlagItemList& copy );

      /** Retrieves the group bit flags.
       *  @param ulGroupFlag - Unsigned long (by reference) to hold 
       *                       retrieved group bit flags. 
       *  @returns Nothing. 
       */
      void getGroupFlag( unsigned long &ulGroupFlag );

      /** Determines if the nth flag of the nth item is turned on 
       *    or off.
       *  @param nFlag Zero based index of the flag to examine.
       *  @param nItem Zero-based index of the item to examine.
       *  @returns Boolean indicating whether the flag is turned 
       *           on or off.  
       */
      bool isFlagSet( int nFlag, int nItem ) const;

      /** Turns on (sets) the nth flag of the nth item.
       *  @param nFlag - Zero based index of the flag to set.
       *  @param nItem - Zero-based index of the item whose flag 
       *                 will be set.
       *  @returns Boolean indicating whether the flag was 
       *           successfully set. 
       */
      bool isGroupFlagSet( unsigned long ulGroupFlag ) const;

      /** Turns on (sets) the specified group bit flag(s).
       *  @param ulGroupFlag - Group bit flag(s) to set.
       *  @returns Boolean indicating whether the group bit flag(s) 
       *           was successfully set. 
       */
      bool setFlag( int nFlag, int nItem );

      /** Determines if the specified group bit flag(s) is set.
       *  @param ulGroupFlag - Group bit flag(s) to examine.
       *  @returns Boolean indicating whether the group bit flag(s) 
       *           is turned on or off. 
       */
      bool setGroupFlag( unsigned long ulGroupFlag );


   // Private Data
   private:
      int                   _nFlags;           // How many bit flags
      int                   _nItems;           // How many items
      int                   _nItemFlagBytes;   // # bytes req'd for a item's flags
      int                   _nFlagBytes;       // # bytes req'd in total
      I_UCHAR  *            _pFlags;           // Pointer to buffer of flags
      unsigned long         _ulGroupFlag;      // Group bit flags
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
// $Log:   Y:/VCS/iFastAWD/inc/flagitemlist.hpp-arc  $
//
//   Rev 1.0   28 Jan 2008 13:31:30   kovacsro
//Initial revision.
// 
//    Rev 1.7   28 Nov 2001 12:41:54   dt14177
// fixed linkage define
// 
//    Rev 1.6   Dec 26 2000 15:46:08   dt39990
// Organized methods in alphabetical listing
// 
//    Rev 1.5   25 Oct 2000 10:51:08   dt14177
// cleanup
// 
//    Rev 1.4   Jan 04 2000 04:46:18   DT29758
//  
// 
//    Rev 1.3   Dec 30 1999 08:04:34   DT29758
// Modified comments to Java-Doc style
// 
//    Rev 1.2   Dec 29 1999 13:46:36   DT29758
// Modified comments to fit JavaDoc standard
// 
//    Rev 1.1   Nov 11 1999 16:32:00   DT29758
// added unicode support and utilization of
// indexes for data object fields
// 
//    Rev 1.0   Jun 21 1999 17:15:00   DT22388
//  
// 
//    Rev 1.2   Mar 17 1999 13:18:52   DT21815
// Added ccdoc comments/documentation.
// 
//    Rev 1.1   Jan 14 1999 11:16:40   DT21815
// Changed #include file names to lower case.
// 
//    Rev 1.0   29 Jul 1998 23:58:26   dt14596
// DLMG New Archives for TA2000NTDT
// 
//    Rev 1.5   Apr 10 1998 10:00:12   djoo
// Modified redundant include guard for 
// string.
// 
//    Rev 1.4   Mar 10 1998 13:05:44   DT21815
// Removed static array of bit masks (moved into source).
// Added header comment block and revision comment block.
//
//



#endif

