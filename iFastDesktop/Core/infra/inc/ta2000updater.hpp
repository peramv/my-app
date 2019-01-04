#ifndef TA2000UPDATER_HPP
#define TA2000UPDATER_HPP

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

#ifndef COMMONPORT_H
#include "commonport.h"
#define COMMONPORT_H
#endif

#ifndef CONDITIONMANGER_HPP
#include "conditionmanager.hpp"
#endif

#ifndef UPDATER_HPP
#include "updater.hpp"
#endif


// Import/Export resolution
#undef DITABUSCORE_LINKAGE
#ifdef DITABUSCORE_DLL
   #define DITABUSCORE_LINKAGE CLASS_EXPORT
#else
   #define DITABUSCORE_LINKAGE CLASS_IMPORT
#endif

class DITABUSCORE_LINKAGE TA2000Updater : public Updater
{

public:
      // %BEGIN_INTERFACE%

   /**
    * constructor
    */
   TA2000Updater(const bool bIsSpotTransaction = false);

   /**
    * destructor
    */
   virtual ~TA2000Updater();

   /**
    * Adds a Data object to the updater
    * 
    * @param data      - object to add
    * @param strDataId - data object's name
    */
   virtual void addData( const Data & data,
                         const DString& strDataId = I_("") );
  
   /**
    * Dumps the string to the CBO dump file
    * specified by the environment variable
    * CBODUMPFILE
    * 
    * @param strView   - the data stream in a string
    * @param strDataId - the view name
    */
   virtual void addData( const DString& strView,
                         const DString& strDataId = I_("") );

   /**
    * Returns whether this updater is real-time
    * 
    * @return 
    */
   bool isSpotTransaction();

   /**
    * Clears the vector of all updates
    */
   virtual void clearData();

   /**
    * Sets the facility Id used by the host
    * 
    * @param strFacilityID
    */
   void setFacilityID(const DString &strFacilityID);
   
   /**
    * Gets the facility Id
    * 
    * @return 
    */
   DString& getFacilityID();

   /**
    * Sets the batch number used by the host
    * in the update
    * 
    * @param strBatchNumber
    * @return 
    */
   SEVERITY setBatchNumber(const DString &strBatchNumber);
   
   /**
    * Gets the batch number
    * 
    * @return 
    */
   DString& getBatchNumber();

	/**
	 * Set view limit to send data to the mainframe
	 *
	 * @return NO_CONDITION if view limit is greater than 0 and less than 32767.
	 *		     Otherwise return SEVERE_ERROR
	 */
	SEVERITY setViewLimit( unsigned long ulLimit );


      // %END_INTERFACE%

protected:

   /**
    * This method submits the update.
    * 
    * @param bIgnoreDuplicate
    * @return 
    */
   virtual bool submitData( const bool bIgnoreDuplicate = true );

private:
   TA2000Updater( const TA2000Updater &copy );
   TA2000Updater& operator=( const TA2000Updater &copy );

   void setDataTag( const DString& strNewTag );
   const DString getDataTag();
   virtual const int removeDataById( const DString& strRemoveTag );

   DString      _strFacilityID,
               _strViewName,
               _strBatchNumber,
               _strDataTag;

   bool _bIsSpotTransaction,
        _bIgnoreDuplicate;

   int _nNumberViews;

	unsigned long _ulLimit;

};


#endif


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
// $Log:   Y:/VCS/iFastAWD/inc/ta2000updater.hpp-arc  $
//
//   Rev 1.0   28 Jan 2008 13:32:58   kovacsro
//Initial revision.
// 
//    Rev 1.5   Nov 01 2001 15:18:16   dt39990
// Added method setViewLimit() to set view 
// limit to send data to the mainframe
// 
//    Rev 1.4   28 Nov 2000 12:32:20   dt14177
// cleanup
// 
//    Rev 1.3   Jul 18 2000 16:46:24   DT22388
// performed synch-up with infra 1.7
// renamed a method
// and made some methods
// virtual
// 
//    Rev 1.2   Apr 27 2000 17:54:36   DT22388
// Changed the addData() method that takes
// a Data object to iterate through a
// repeatable Data object and flatten
// the repeats into a string.
// 
// Made the submitData() method protected.
// 
// Added the corresponding test scenarios.
// 
//    Rev 1.1   Nov 11 1999 16:32:46   DT29758
// added unicode support and utilization of
// indexes for data object fields
// 
//    Rev 1.0.1.2   Sep 23 1999 16:11:50   DT22388
// Performed more code clean up.
// Made the ctor protected and made
// submitData() pure virtual.  Also
// removed the need for addDataSubClass()
// addDataSuperClass and submitDataSubClass()
// and submitDataSubClass().  Figured out
// that polymorphism works just fine for
// the addData() and the submitData() methods
