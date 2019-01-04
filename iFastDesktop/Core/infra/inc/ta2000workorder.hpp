#ifndef TA2000WORKORDER_HPP
#define TA2000WORKORDER_HPP

#  pragma message( "including "__FILE__ )

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

/**@pkg DITABUSCORE */    

#ifndef INCLUDED_DSTRING_HPP
#include "dstring.hpp"
#define INCLUDED_DSTRING_HPP
#endif

#ifndef INCLUDED_OSTREAM
#include <ostream>
#define INCLUDED_OSTREAM
#endif

#ifndef COMMONPORT_H
#include "commonport.h"
#define COMMONPORT_H
#endif

// Forward declarations
class TA2000WorkOrderImpl;
class CBEBase;


// Import/Export resolution
#undef DITABUSCORE_LINKAGE
#ifdef DITABUSCORE_DLL
   #define DITABUSCORE_LINKAGE CLASS_EXPORT
#else
   #define DITABUSCORE_LINKAGE CLASS_IMPORT
#endif

class DITABUSCORE_LINKAGE TA2000WorkOrder
{
public:

   /**
    * Default constructor
    */
   TA2000WorkOrder();
   /**
    * Destructor
    * 
    * Deletes any "owned" CBE based classes
    * that were registered with us.
    */
   virtual ~TA2000WorkOrder();                   

   /**
    * Cycles through all registed CBEs, determining
    * if they are SPOT and calling their update
    * method with the appropriate Updater object.
    * After each CBE is done, the submit method
    * is called for each Updater.
    * 
    * @param bIgnoreDuplicate
    * @return 
    */
   SEVERITY update( const bool bIgnoreDuplicate = true );

   /**
    * Cycles through all registed CBEs, determining
    * if they are SPOT and calling their update
    * method with the appropriate Updater object.
    * 
    * @param bIgnoreDuplicate
    * @return 
    */
   SEVERITY updateNoCommit();

   /**
    * Cycles through all registed CBEs, calling the submit
    * method for each Updater.
    * 
    * @param bIgnoreDuplicate
    * @return 
    */
   SEVERITY commit( const bool bIgnoreDuplicate = true );            

   /**
    * Registers the CBE with the TA2000Workorder.
    * If the CBEBase * is already in the map or
    * the stringkey is already in the map, a
    * condition is added and we return.
    * 
    * @param pCBEBase
    * @param strKey
    * @param fOwnedByManager
    * @return 
    */
   bool registerCBE( CBEBase * pCBEBase, 
                     const DString& strKey, 
                     bool fOwnedByManager = true );
   
   /**
    * De-registers a CBE with the workorder
    * 
    * @param strKey
    * @return 
    */
   CBEBase * deregisterCBE( const DString& strKey );
   
   /**
    * Removes all references to CBEs from the
    * internal map.  Any "owned" CBEs are deleted.
    */
   void removeAllCBEs();

   /**
    * Attempts to find the stringkey in the map
    * and assign the supplied pointer to the
    * CBE found in the map.  If no key is found,
    * a condition is added, the pointer is NULLed
    * and we return FALSE;
    * 
    * @param strKey   - the key
    * @param pCBEBase - (out) the returned CBE
    * @return 
    */
   bool getCBE(const DString& strKey, CBEBase ** pCBEBase);  

   /**
    * Gets the CBE found at the index
    * 
    * @param nCBEIndex
    * @return 
    */
   CBEBase * getCBE( int nCBEIndex ) const;
   
   /**
    * Returns the number of CBEs in the workorder
    * 
    * @return 
    */
   int getCBECount() const;


   /**
    * Attempts to find the stringkey in the map
    * and removes the map entry.  If the mapped
    * CBE is "owned", we delete it also.  A
    * condition is added if the map key is not 
    * found.
    * 
    * @param strKey
    * @return 
    */
   bool removeCBE(const DString& strKey);

   /**
    * Refreshes the CBEs
    * 
    * @return 
    */
   SEVERITY refreshUpdatedCBOs();

   /**
    * Returns whether the workorder has CBEs
    * 
    * @return 
    */
   bool hasCBEs();

   /**
    * Dumps the contents of the CBEs to a stream
    * 
    * @param outStream
    */
   void dumpCBEs( i_ostream &outStream ) const;

   /**
    * Sets the batch number for financial updates
    * 
    * @param strBatchNumber
    * @return 
    */
   SEVERITY setFinancialBatchNumber( const DString& strBatchNumber );

   /**
    * Gets the batch number for financial updates
    * 
    * @param strBatchNumber
    */
   void getFinancialBatchNumber( DString& strBatchNumber ) const;

   /**
    * Sets the batch number for non-financial 
    * updates
    * 
    * @param strBatchNumber
    * @return 
    */
   SEVERITY setNonFinancialBatchNumber( const DString& strBatchNumber );

   /**
    * Gets the batch number for non-financial 
    * updates
    * 
    * @param strBatchNumber
    */
   void getNonFinancialBatchNumber( DString& strBatchNumber ) const;

	/**
	 * Set view limit to send data to the mainframe
	 *
	 * @return NO_CONDITION if view limit is greater than 0 and less than 32767.
	 *			  Otherwise return SEVERE_ERROR
	 */
	SEVERITY setViewLimit( unsigned long ulLimit );

   
private:

   TA2000WorkOrder( const TA2000WorkOrder &copy );
   TA2000WorkOrder& operator=( const TA2000WorkOrder& copy );

   TA2000WorkOrderImpl * _pWorkOrderImpl;
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
// $Log:   Y:/VCS/iFastAWD/inc/ta2000workorder.hpp-arc  $
//
//   Rev 1.0   28 Jan 2008 13:33:00   kovacsro
//Initial revision.
// 
//    Rev 1.4   Nov 01 2001 15:29:16   dt39990
// Added method setViewLimit() to set view 
// limit to send data to the mainframe
// 
// 
//    Rev 1.3   Nov 01 2001 15:18:18   dt39990
//  
// 
//    Rev 1.2   28 Nov 2000 13:44:00   dt14177
// cleanup
// 
//    Rev 1.1   Nov 11 1999 16:32:48   DT29758
// added unicode support and utilization of
// indexes for data object fields
// 
//    Rev 1.0.1.1   Jul 22 1999 13:36:14   DT22388
// Performed code clean-up and added #undefs
// for the substitution string i.e. $strParentImplClass$.
// Also, added #includes for test classes.
// 
// 
//    Rev 1.0.1.0   Jul 06 1999 13:40:34   DT22388
// Added new methods to complete the
// BatchWorkOrder and WorkOrder merge.
// 
//    Rev 1.0   Jun 21 1999 17:15:54   DT22388
//  
// 
//    Rev 1.0   29 Jul 1998 23:58:58   dt14596
// DLMG New Archives for TA2000NTDT
// 
//    Rev 1.10   Mar 25 1998 15:41:58   djoo
// Added method dumpCBEs.
// 
//    Rev 1.9   Mar 09 1998 09:53:36   djoo
// Modified the return for setNonFinancialBatchNumber
// and setFinancialBatchNumber.
// 
//    Rev 1.8   Mar 06 1998 16:24:28   djoo
// Added methods setFinancialBatchNumber, 
// getFinancialBatchNumber, setNonFinancialBatchNumber
// and getNonFinancialBatchNumber.
// 
//    Rev 1.7   Feb 09 1998 13:07:10   djoo
// Added method hasCBEs.
// 
#endif
