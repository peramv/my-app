#ifndef UPDATER_HPP
#define UPDATER_HPP

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


#ifndef INCLUDED_STRING
#include <string>
#define INCLUDED_STRING
#endif

#ifndef INCLUDED_VECTOR
#include <vector>
#define INCLUDED_VECTOR
#endif

#ifndef  DSTRING_HPP
#include "dstring.hpp"
#endif

#ifndef COMMONPORT_H
#include "commonport.h"
#endif


/**@#-*/
//forward declares
class Data;
/**@#+*/


// Import/Export resolution
#undef CBOBASE_LINKAGE
#ifdef DICBOCORE_DLL
    #define CBOBASE_LINKAGE CLASS_EXPORT
#else
    #define CBOBASE_LINKAGE CLASS_IMPORT
#endif

/**
 * Updater knows how to hold and order data,
 * but does not know how to prepare the data
 * for submitting to the host.
 * 
 * Therefore, developers should derive a class from
 * Updater and implement a submitData()
 * method that performs the final formatting of the
 * data.  The addData() methods in Updater can also be
 * overridden to perform any host specific formatting.
 * 
 * One or more Updater objects can be held by an
 * EventUpdateOrder object.  EventUpdateOrder is
 * responsible for moving data from the CBE
 * Data object(s) to the contained Updater
 * string(s).
 * 
 * @see EventUpdateOrder
 * @see CBEBase
 */
class CBOBASE_LINKAGE Updater
{

   public:

       /**
        * This method will store off the string value in
        * a collection of data for updates and attach
        * the specified string key value.
        * 
        * This method is usually called from CBEBaseImpl or
        * a CBEBaseImpl derived class.
        * 
        * @param strData   a string value of data that will be sent to the host
        * @param strDataId An identifier to store with the data
        */
      virtual void addData( const DString & strData,
                            const DString & strDataId = I_("") );

      /**
       * This method takes a Data object and flattens it
       * out into a string value and stores it in a
       * colleciton of data for updates.
       * 
       * This method is usually called from CBEBaseImpl or
       * a CBEBaseImpl derived class.
       * 
       * @param data      A Data object that has been filled with business
       *                  data for updates.
       * @param strDataId An identifier to store with the data
       */
      virtual void addData( const Data & data,
                            const DString & strDataId = I_("") );
      
      /**
       * Clears all of the stored data from the Updater
       * object.
       */
      virtual void clearData();

      /**
       * This method gets the string data at the specified
       * index.
       * 
       * @param index  An integer value of and index into the collection
       *               of string data
       * @return 
       */
      virtual const DString getData( const int index ) const;
      
      /**
       * This method gets the current string data ID
       * 
       * @return A string value of the current string data ID
       */
      virtual const DString getDataId();

      /**
       * This method returns the size of the string
       * at the passed index.
       * 
       * @param nIndex An integer value of and index into the collection
       *               of string data
       * @return An integer value of the size of the string
       *         at the passed-in index
       */
      virtual const int getDataLength( const int nIndex ) const;
      
      /**
       * This method removes a string data from the collection
       * based on the string valued ID passed in.
       * 
       * @param strDataId
       * @return An integer value of the number of string data
       *         structs that were removed
       */
      virtual const int removeDataById( 
                                     const DString & strDataId );

      /**
       * Set the current string data ID
       * 
       * @param strDataId An identifier that is stored with the data
       */
      virtual void setDataId( const DString & strDataId );
      
      /**
       * This method should be implemented in a derived
       * class.
       * 
       * The derived class method implementation should
       * format the data as needed for the corresponding
       * host.
       * 
       * @param bIgnoreDuplicate
       *               A boolean value that specifies whether or not the
       *               user cares about a duplicate transaction condition
       *               message.
       *               
       *               If the data that is submitted to the host creates
       *               a duplicate record condition and this value is
       *               false then we will hold on to the data until the
       *               user calls commit passing a true to ignore the
       *               condition message.
       * @return true if successful
       *         false if failure
       */
      virtual bool submitData( const bool bIgnoreDuplicate=true ) 
                                                             = 0;
      
      /**
       * This method will perform the actual call to
       * the Submiter object which will make the
       * actual call to a TA2000DataBroker object
       * to send the data to the host.
       * 
       * @param strData    A string value of the data that will be sent to
       *                   the host
       * @param returnData A Data object that will be filled with the
       *                   return data from the host.
       * @param strDataId  The name of the updater view
       * @return true if successful
       *         false if failure
       */
      virtual bool submitData( const DString & strData, 
                               Data & returnData, 
                            const DString & strDataId = I_("") );

      /**
       * Destructor
       */
      virtual ~Updater();


   protected: //methods
      
      Updater();

      
   private: // methods


      Updater( const Updater &copy );
      Updater & operator=( const Updater &copy );

   private: // attributes

      struct UpdaterStruct
      {
         DString strData;
         DString strDataId;
      };

      typedef std::vector< UpdaterStruct > UPDATER_STRUCT_VEC;

      DString _strDataId;

      UPDATER_STRUCT_VEC _vecUpdaterStructs;
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
// $Log:   Y:/VCS/iFastAWD/inc/updater.hpp-arc  $
//
//   Rev 1.0   28 Jan 2008 13:33:16   kovacsro
//Initial revision.
// 
//    Rev 1.8   28 Nov 2001 12:42:26   dt14177
// fixed linkage define
// 
//    Rev 1.7   Dec 27 2000 17:13:32   dt39990
// Added more documentation and 
// organized methods in alphabetical listing
// 
// 
// 
//    Rev 1.6   29 Nov 2000 14:08:22   dt14177
// fixed std namespace compile problems
// 
//    Rev 1.5   29 Nov 2000 10:57:24   dt14177
// cleanup
// 
//    Rev 1.4   Jul 18 2000 16:46:26   DT22388
// performed synch-up with infra 1.7
// renamed a method
// and made some methods
// virtual
// 
//    Rev 1.3   Jan 04 2000 04:46:32   DT29758
//  
// 
//    Rev 1.2   Dec 29 1999 13:46:44   DT29758
// Modified comments to fit JavaDoc standard
// 
//    Rev 1.1   Nov 11 1999 16:32:52   DT29758
// added unicode support and utilization of
// indexes for data object fields
// 
//    Rev 1.0.1.2   Sep 23 1999 16:08:32   DT22388
// Performed more code clean up.
// Made the ctor protected and made
// submitData() pure virtual.  Also
// removed the need for addDataSubClass()
// addDataSuperClass and submitDataSubClass()
// and submitDataSubClass().  Figured out
// that polymorphism works just fine for
// the addData() and the submitData() methods
#endif // UPDATER_HPP
