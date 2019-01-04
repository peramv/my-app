#ifndef CBEBASE_HPP
#define CBEBASE_HPP

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


#ifndef  DSTRING_HPP
#include "dstring.hpp"
#endif

#ifndef COMMONPORT_H
#include "commonport.h"
#endif

#ifndef CONDITIONMANAGER_HPP
#include "conditionmanager.hpp"   
#endif

// Forward declarations
class CBEBaseImpl;
class Updater;
class Data;
class CBOBase;

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
 * A base (CBE - Common Business Event) class for
 * handling common business transactions.
 * 
 * CBEBase is the interface class for the
 * CBEBaseImpl implementation class.
 * 
 * All the method contained in CBEBase are pass-through
 * method to methods of the same name implemented in
 * CBEBaseImpl.
 * 
 * The CBEBaseImpl class contains methods
 * used for field management and business data
 * gathering.
 * 
 * An instance of this class should contain either
 * a CBOBase pointer or an UpdatableListBase pointer
 * but not both.
 * 
 * CBEBaseImpl also will contain a collection of Data
 * objects that may or may not be filled with data for
 * an update.
 * 
 * Derived classes from CBEBase will need to either
 * set in a CBO or a Updatablelistbase derived class
 * upon initialization of the event. Also, in the
 * initialization step, the CBEBase derived class will
 * need to register one or more Data objects that
 * may be used for updates.
 * 
 * In the update process, CBEBase will iterate over
 * each of the registered Data objects and fill them
 * with data from the contained CBO or UpdatableList
 * data.  Before data gathering for an update can occur,
 * CBEBaseImpl will ask the contained CBO or UpdatableList
 * object if an update for the associated data object
 * should be built. CBEBaseImpl will then ask the
 * contained CBO or UpdatableList if it is in a valid
 * state.  And as the final step, CBEBase will get the
 * data from the contained CBO or UpdatableListBase
 * object.
 * 
 * The interface/implementation concept is known
 * as the "bridge" pattern or "handle/body" pattern
 * as found in the  Design Patterns(GOF95') book.
 * 
 * @see CBEBaseImpl
 */
class CBOBASE_LINKAGE CBEBase
{
   // public data structures and definitions
   public:
      enum VALIDATION_MODE { IMMEDIATE,
                             POSTPONED };


      enum ORIGIN
      {
         TELEPHONE_TRANSACTION,
         BACK_OFFICE_TRANSACTION
      };


   public:
      /** Constructor */
      CBEBase();

      /** virtual Destructor */
      virtual ~CBEBase();

      /**
       * This method calls the containd CBO's method of the same name
       * which takes a "snapshot" of of a contained CBO
       * instanceFieldInfo for a potential rollback.
       * This method makes a full and complete copy of
       * anything related to instance fields. Any previous
       * checkpoint will be cleared.
       * 
       * @return true if successful / false on failure
       * @see rollbackFieldsToCheckpoint()
       */
      bool checkpointFields( void );

      /**
       * Retrieves a details object( the contained CBO )
       * of a business event
       * 
       * @return A CBOBase reference
       */
      const CBOBase& getDetails() const;

      /**
       * This method calls the contained CBO's method of the
       * same name which populates a string with the
       * requested field's value if found.
       * 
       * @param strFieldTag
       *                 A unique string tag indentifier for the registered field
       *                 used to index into the instancefieldinfo.
       *                 The string tag indentifier for a field is set up in
       *                 the CLASS_FIELD_INFO.
       * @param strValue The user supplied string to hold the field value
       * @return NO_CONDITION if successful
       * @see CLASS_FIELD_INFO
       * @see setField
       */
      virtual SEVERITY getField( const DString& strFieldTag,
                                 DString& strValue ) const;

      /**
       * Retrieve the number of Data objects
       * that have been registered with CBEBaseImpl
       * 
       * A Data object can be registered with CBEBaseImpl
       * by making a call to registerView from the init
       * method of a class that is derived from CBEBaseImpl.
       * 
       * @return an integer value of the number of Data objects
       *         registered with CBEBaseImpl
       * @see registerView
       */
      int getNumberTransactionDataObjects( void ) const;

      /**
       * This method is called by an EventUpdateOrder object.
       * 
       * It gets the number of update stages in a business event.
       * A transaction stage is an integer value that specifies
       * the order in which data will be gathered and
       * thus sent to the host.
       * For example. a Data object marked as a stage 1 update
       * will be filled with data and thus submitted before any
       * Data objects that are marked as stage 2 updates.
       * All data goes to the host at the same time, but
       * the stage 1 data will go before the stage 2 data.
       * 
       * You can specify a transaction stage for each
       * Data object that you register with CBEBaseImpl.
       * The registerView method will store off the
       * corresponding stage number with the passed in
       * Data object.
       * 
       * @return an integer value of the number of stages associated
       *         with the current business event
       * @see registerView
       */
      int getNumTransactionStages( void ) const;

      /**
       * Retrieve a single Data object
       * that has been registered with CBEBaseImpl
       * 
       * A Data object can be registered with CBEBaseImpl
       * by making a call to registerView from the init
       * method of a class that is derived from CBEBaseImpl.
       * 
       * @param index   an integer value of the contained Data object
       * @param outData a Data reference to be filled with data
       * @return true if successful
       *         false if failure
       * @see registerView
       */
      bool getTransactionDataObject( int index, Data& outData  ) const;

      /**
       * This method calls the contained CBO's method of the same name
       * which returns the contained CBO's validation mode IMMEDIATE or POSTPONED.
       * Validation mode can be set for all instances of an object(class level)
       * or on a instance by instance basis(object level).
       * If the validation mode is immediate, error conditions
       * will be returned immediately from a call to setField.
       * 
       * If the validation mode is postponed, all conditions will
       * be ignored at the time of a setField call.
       * This means the user intends to collect all conditions
       * at a later time by making a call to the validateAll()
       * method.
       * The methods that check for validation mode are:
       * setObject
       * _authorizedSetObject
       * setField
       * 
       * @return An enumeration of the validation mode of the object
       *         (0 = IMMEDIATE or 1 = POSTPONED)
       * @see VALIDATION_MODE
       * @see setObject
       * @see _authorizedSetObject
       * @see setField
       */
      VALIDATION_MODE getValidationMode( void ) const;

      /**
       * This method calls the contained CBO's method of the same name
       * which checks to see if an instance field is marked with INST_FLD_READ_ONLY.
       * If a instance field is marked as INST_FLD_READ_ONLY
       * then the field cannot be set from the user interface
       * without generating a "field read only" error message.
       * A read only field can be set by using one of the _authorizedSet
       * methods from within a derived class.
       * 
       * Fields can initially start out with INST_FLD_READ_ONLY marked
       * based on the field entry in the CLASS_FIELD_INFO.
       * (Use CLASS_FLD_READ_ONLY in the CLASS_FIELD_INFO field entry.
       * 
       * The INST_FLD_READ_ONLY flag can be turned off and on
       * many times during the lifetime of an object.
       * 
       * @param strFieldTag
       *               A unique string tag indentifier for the registered field
       *               used to index into the instancefieldinfo.
       *               The string tag indentifier for a field is set up in
       *               the CLASS_FIELD_INFO.
       * @return true if field is marked with INST_FLD_READ_ONLY
       *         false if field is not marked as INST_FLD_READ_ONLY
       * @see CLASS_FIELD_INFO
       * @see FIELD_FLAG
       * @see setFieldFlag
       * @see clearFieldFlag
       * @see isFieldFlagSet
       */
      bool isFieldReadOnly( const DString& strFieldTag ) const;

      /**
       * This method calls the contained CBO's method of the same name
       * which checks to see if field has been updated
       * (determined by checking the INST_FLD_UPDATED field flag ).
       * 
       * If an instance field is marked as INST_FLD_UPDATED
       * then the field has been changed from it's original value.
       * 
       * Fields initially start out with the INST_FLD_UPDATED
       * flag turned off.
       * 
       * The methods that will cause this flag to get turn on
       * are:
       * 
       * setField <-- only if all validations pass or in postponed validation mode
       * applyActiveGroup
       * 
       * The INST_FLD_UPDATED flag can be turned off and on
       * many times during the lifetime of an object.
       * 
       * @param strFieldTag
       *               A unique string tag indentifier for the registered field
       *               used to index into the instancefieldinfo.
       *               The string tag indentifier for a field is set up in
       *               the CLASS_FIELD_INFO.
       * @return true if field is marked with INST_FLD_UPDATED
       *         false if field is not marked as INST_FLD_UPDATED
       * @see setField
       * @see applyActiveGroup
       * @see setFieldFlag
       * @see clearFieldFlag
       * @see isFieldFlagSet
       */
      bool isFieldUpdated( const DString& strFieldTag ) const;

      /**
       * This method checks to see if atleast one Data object
       * has been registered with CBEBaseImpl.
       * 
       * A Data object can be registered with CBEBaseImpl
       * by making a call to registerView from the init
       * method of a class that is derived from CBEBaseImpl.
       * 
       * @return true if a Data object has been registered
       *         false if not
       * @see registerView
       */
      bool isInitialized( void ) const;

      /**
       * This a method specific to TA2000.
       * It is called by TA2000WorkOrder.
       * 
       * A SPOT transaction is considered a
       * financial transaction which uses
       * the J360p0 COBOL subroutine for updates
       * to the host.  A non-financial transaction
       * will use the H260p0 COBOL subroutine
       * for updates to the host. The J360p0 is
       * the new updater routine. The H260p0 is
       * the old updater routine. 
       * 
       * @return true if the business event uses the new updater
       *         routine
       *         false if the business event uses the old updater
       *         routine
       */
      bool isSPOTTransaction() const;

      /**
       * This method calls the contained CBO's method of the same name
       * which should be implemented in a CBOBaseImpl
       * derived class.
       * 
       * This method is part of rework functionality
       * implemented in EventUpdateOrder.
       * 
       * If an event(CBE) is removed from an
       * EventUpdateOrder notification can be sent
       * to any contained CBOs associated with the
       * event.
       * 
       * @return NO_CONDITION if successful
       * @see notifyOnCommit
       * @see notifyOnUpdate
       * @see EventUpdateOrder
       * @see Updater
       * @see CBEBaseImpl
       */
      SEVERITY notifyOnBackout();
      
      /**
       * This method calls the contained CBO's method of the same name
       * which should be implemented in a CBOBaseImpl
       * derived class.
       * 
       * This method is part of rework functionality
       * implemented in EventUpdateOrder.
       * 
       * If the business data contained within a CBE
       * is committed(sent to the host) from an
       * EventUpdateOrder, notification can be sent
       * to any contained CBOs associated with the
       * common business event.
       * 
       * @see notifyOnUpdate
       * @see notifyOnBackout
       * @see EventUpdateOrder
       * @see Updater
       * @see CBEBaseImpl
       */
      void notifyOnCommit();
      
      /**
       * This method calls the contained CBO's method of the same name
       * which should be implemented in a CBOBaseImpl
       * derived class.
       * 
       * This method is part of rework functionality
       * implemented in EventUpdateOrder.
       * 
       * If the business data contained within a CBE
       * has been collected in an Updater object
       * but not committed(sent to the host) from an
       * EventUpdateOrder, notification can be sent
       * to any contained CBOs associated with the
       * common business event.
       * 
       * @return NO_CONDITION if successful
       * @see notifyOnCommit
       * @see notifyOnBackout
       * @see EventUpdateOrder
       * @see Updater
       * @see CBEBaseImpl
       */
      SEVERITY notifyOnUpdate();
      
      /** Assignment operator */
      CBEBase& operator=( const CBEBase& copy );

      /**
       * This method calls the contained CBO's method of the same name
       * which should be implemented in a CBOBaseImpl
       * derived class.
       * 
       * CBOBaseImpl will only increment the updateLevel
       * of the current object.
       * 
       * This method is usually overridden in the derived
       * class to implement code that will grab the latest
       * data for the instancefieldinfo.  The refresh is
       * usually called after updates to the host have
       * occurred.
       * 
       * @return NO_CONDITION if successful
       * @see getUpdateLevel
       */
      SEVERITY refresh( void );

      /**
       * This method calls the contained CBO's method of the same name
       * which resets the specified field to its default value(if one exists)
       * and resets its corresponding object state flags to
       * the original values.
       * 
       * The reset is based on the values contained in
       * the CLASS_FIELD_INFO.
       * 
       * @param strFieldTag
       *               A unique string tag indentifier for the registered field
       *               used to index into the instancefieldinfo.
       *               The string tag indentifier for a field is set up in
       *               the CLASS_FIELD_INFO.
       * @return true for successs
       *         false for failure
       * @see CLASS_FIELD_INFO
       * @see setField
       * @see getField
       */
      bool resetField( const DString &strFieldTag);

      /**
       * This method calls the contained CBO's method of the same name
       * which attempts to roll back the instancefieldinfo to the previous "snapshot"
       * taken by calling the checkpointFields method.
       * This removes the current instancefieldinfo
       * from existance.
       * 
       * @return true for successs
       *         false for failure
       * @see checkpointFields
       */
      bool rollbackFieldsToCheckpoint( void );

      /**
       * This method calls the contained CBO's method of the same name
       * which sets the specified instance field with the
       * supplied string value. This method will call
       * another setField overload to actually perform
       * the validations and storage. It needs to figure
       * out the subclass id we are currently working with
       * first.
       * 
       * @param strFieldTag
       *                 A unique string tag indentifier for the registered field
       *                 used to index into the instancefieldinfo.
       *                 The string tag indentifier for a field is set up in
       *                 the CLASS_FIELD_INFO.
       * @param strValue A string value that will be validated and stored
       * @return NO_CONDITION if successful
       * @see getField
       * @see validate
       * @see resetField
       */
      virtual SEVERITY setField( const DString& strFieldTag,
                                 const DString& strValue );
      /**
       * This method calls the contained CBO's method of the same name
       * which sets the object's validation mode to IMMEDIATE or POSTPONED.
       * Validation mode can be set for all instances of an object(class level)
       * or on a instance by instance basis(object level).
       * 
       * If an objects's validation mode is set to IMMEDIATE,
       * then any "set" method that is called on this object
       * will generate a condition and return it immediately
       * to the user if the data being set is invalid.
       * 
       * If an objects's validation mode is set to POSTPONED,
       * then any data can be set into the object whether the
       * data is invalid or not.  The validateAll method or
       * the validate method should be called at a later
       * time to kick off any validations needed. The
       * only field validations performed by CBOBaseImpl
       * are the read only and required checks.
       * 
       * The methods that check the validation mode are:
       * setObject
       * _authorizedSetObject
       * setField
       * 
       * @param validationMode
       *               An enumeration stating which mode is needed for
       *               this object.  Valid values are IMMEDIATE or POSTPONED
       * @see VALIDATION_MODE
       * @see getValidationMode
       * @see setObject
       * @see _authorizedSetObject
       * @see setField
       * @see validateAll
       * @see validate
       */
      void setValidationMode( VALIDATION_MODE validationMode );

      /**
       * A Pure virtual method
       * This method must be implemented in a derived class.
       * This method is called by an EventUpdateOrder object.
       * 
       * Use this method as a place to call an isAuthorized
       * implementation or perform any other security checks
       * needed.
       * 
       * Also place a  call to the CBEBaseImpl commitUpdate method
       * to kick of the data gathering and update process.
       * 
       * @param updater A Updater object to hold the Data that is
       *                gathered and to be used for updating the host
       * @param nUpdateStage
       *                A update stage is an integer value that specifies
       *                the order in which data will be gathered and
       *                thus sent to the host.
       *                For example. a Data object marked as a stage 1 update
       *                will be filled with data and thus submitted before any
       *                Data objects that are marked as stage 2 updates.
       *                All data goes to the host at the same time, but
       *                the stage 1 data will go before the stage 2 data.
       *                
       *                
       *                It defaults to a value of 1.
       * @return NO_CONDITION if successful
       * @see commitUpdate
       * @see isAuthorized
       */
      virtual SEVERITY update( Updater &updater, int nStage ) = 0;

      /**
       * This method calls the contained CBO's method of the same name
       * which attempts to validate the entire object and
       * return a severity designating the state of
       * this object.
       * 
       * Contained(aggregate) objects are also validated.
       * 
       * This method will check ALL fields and objects
       * adding conditions for each invalid item.
       * If an item (field or object) is not in a
       * valid state, an attempt to validate it will occur.
       * 
       * This method will be called by the CBOBase
       * validateAll method or it can be called directly
       * from a derived class.
       * 
       * @return NO_CONDITION if successful
       * @see performIsValidForUpdateEdits
       * @see setValidationMode
       * @see setField
       * @see setObject
       * @see _authorizedSetObject
       */
      virtual SEVERITY validateAll( void );
      
      /**
       * This method calls the contained CBO's method of the same name
       * which attempts to cross-validate two or more
       * fields.  It will kick off a cross-field validator
       * that is defined in the derived class.
       * 
       * Call this method after setting values for
       * a related group of fields.
       * 
       * Or let validateAll/validate kick off the
       * cross-field validator for you.
       * 
       * @param strFieldTag
       *               A unique string tag indentifier for the registered field
       *               used to index into the instancefieldinfo.
       *               The string tag indentifier for a field is set up in
       *               the CLASS_FIELD_INFO.
       * @return NO_CONDTION if successful
       * @see setField
       * @see setData
       */
      virtual SEVERITY validateField( const DString& strFieldTag );


   protected:
      enum PROTECTED_CREATION
      {
         PROTECTED_CREATE
      };


   protected:
      CBEBase( PROTECTED_CREATION protected_creation );


   protected:
      CBEBaseImpl * _pImpl;

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
// $Log:   Y:/VCS/iFastAWD/inc/cbebase.hpp-arc  $
//
//   Rev 1.0   28 Jan 2008 13:30:10   kovacsro
//Initial revision.
// 
//    Rev 1.5   28 Nov 2001 12:41:30   dt14177
// fixed linkage define
// 
//    Rev 1.4   Dec 28 2000 18:15:40   dt39990
// Added more documentation and 
// organized methods in alphabetical listing
// 
// 
// 
//    Rev 1.3   Dec 31 1999 06:27:32   DT29758
// Minor Edits to Java-Doc comments
// 
//    Rev 1.1   Nov 11 1999 16:31:08   DT29758
// added unicode support and utilization of
// indexes for data object fields
// 
//    Rev 1.0   Jun 21 1999 17:06:50   DT22388
//  
// 
//    Rev 1.3   Jan 14 1999 13:04:50   DT21815
// Changed #include file names to lower case.
// 
//    Rev 1.2   Jan 07 1999 09:18:54   DMAL
// added the methods, notifyonbackout, notifiyonupdate,
// and notifyoncommit.  All code changes were 
// made for the 3.4.0.0 code sync up.
//
//    Rev 1.1   Jul 30 1998 14:22:34   djoo
// Made getNumTransactionStages const.
//
//    Rev 1.0   29 Jul 1998 23:58:08   dt14596
// DLMG New Archives for TA2000NTDT
//
//    Rev 1.15   Mar 25 1998 11:28:04   djoo
// Added method resetField.
//
//    Rev 1.14   Mar 03 1998 12:22:14   djoo
// Removed method clearUpdatedLabels.
// Renamed refreshUpdatedCBOs to refresh.
//
//    Rev 1.13   Feb 27 1998 13:32:28   djoo
// Added method clearUpdatedLabels.
//
//    Rev 1.12   Feb 19 1998 11:08:40   djoo
// Added methods isFieldReadOnly and getDetails.
//
//    Rev 1.11   Feb 09 1998 12:13:02   djoo
// Added support for refreshing CBOs.
// Added method refreshUpdatedCBOs.
//
//    Rev 1.10   Jan 17 1998 11:29:06   djoo
// Added support for stages during transactions.
// Added method getNumTransactionStages.
//
//    Rev 1.9   Dec 09 1997 08:41:50   djoo
// Added methods isFieldUpdated, checkpointFields & rollbackFieldsToCheckpoint.
//
//    Rev 1.8   Dec 01 1997 16:44:40   djoo
// Added ORIGIN enum.
//
//    Rev 1.7   Nov 20 1997 13:43:58   djoo
// Added validateField method that passes thru to defaultCBO (details).
//
//    Rev 1.6   Nov 11 1997 08:10:22   djoo
// Added redundant include guards, dll import/export protection and removed extraneous
// code dealing with the vector of cbos.
//
//    Rev 1.5   Sep 04 1997 12:41:58   djoo
// Added assert macros and enhancements for retrieving data objects.
//
//    Rev 1.4   Sep 02 1997 16:06:20   djoo
// Intermediate Check-in for CBO8. (Condition Manager enhancements)
//
//    Rev 1.3   Aug 26 1997 12:50:14   djoo
// Initial SEVERITY enhancements.
//
//    Rev 1.2   16 Aug 1997 12:01:32   dmal
// added work order enhancement.
//
//


#endif


