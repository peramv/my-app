#ifndef EVENTUPDATEORDER_HPP
#define EVENTUPDATEORDER_HPP

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


#ifndef INCLUDED_VECTOR
#include <vector>
#define INCLUDED_VETOR
#endif

#ifndef  CBEBASE_HPP
#include "cbebase.hpp"
#endif

#ifndef  DSTRING_HPP
#include "dstring.hpp"
#endif

#ifndef COMMONPORT_H
#include "commonport.h"
#endif

#ifndef CONDITIONMANAGER_HPP
#include "conditionmanager.hpp"
#endif

#ifndef DICBOCORE_H
#include "dicbocore_conditions.hpp"
#endif



// Import/Export resolution
#undef CBOBASE_LINKAGE
#ifdef DICBOCORE_DLL
    #define CBOBASE_LINKAGE CLASS_EXPORT
#else
    #define CBOBASE_LINKAGE CLASS_IMPORT
#endif

/**
 * The user interface (UI) layer can instantiate an
 * EventUpdateOrder object and then register one
 * or more CBEs that are ready for the update process.
 *   
 * After all CBEs have been registered,
 * the UI layer can tell the EventUpdateOrder object
 * to update and commit data contained in the CBEs.
 * During the update process, the EventUpdateOrder
 * object will iterate over its list of CBEs and tell
 * each CBE to build the update data for each
 * transaction.  CBEBase collaborates with the 
 * associated Updater object for storing the update
 * data.  After all update data has been collected,
 * the EventUpdateOrder object collaborates with the
 * Updater object(s) to submit the data to the host.  
 * 
 * @see Updater
 * @see CBEBase
 */
class CBOBASE_LINKAGE EventUpdateOrder
{

public:

    /**
     * This method is usually called after a call to
     * the updateNoCommit method has been made.
     * 
     * This method will cycle through all of the registered
     * Updater objects and tell each one to submit it's
     * data.  The submitData method will be called
     * on each Updater object.
     * 
     * This method will also call the notifyOnCommit
     * pass-through method for the registered CBE.
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
     * @return NO_CONDITION if successful
     * @see submitData
     * @see registerUpdater
     * @see updateNoCommit
     * @see registerCBE
     */
   virtual SEVERITY commit( const bool bIgnoreDuplicate = true );            

   /**
    * This method removes a CBE from the collection of
    * registered CBEs based on the specified key.
    * The CBEBase pointer that is returned can be
    * registered again if needed.
    * 
    * This method can be used for "re-work"
    * functionality when batching multiple
    * events.
    * 
    * This method will also call the notifyOnBackout
    * pass-through method for the registered CBE.
    * 
    * @param strKey An arbitrary string value to associate with
    *               the CBE.  This value must be unique to the
    *               current collection of CBEs in the EventUpdateOrder
    *               object. The value usually is a one word
    *               description of the event. e.g.("NEWACCOUNT1")
    * @return A CBEBase pointer
    * @see registerCBE
    */
   virtual CBEBase * deregisterCBE( const DString& strKey );

   /**
    * This method is a debug method that can be used
    * to write out all of the keys and the corresponding
    * CBE types that have been registered with an
    * EventUpdateOrder object.
    * 
    * @param outStream the output stream to write to
    *                  cout can be passed to dump to the console.
    * @see registerCBE
    */
   void dumpCBEs( i_ostream &outStream ) const;

   /** Constructor */
   EventUpdateOrder();

   /** Virtual Destructor */
   virtual ~EventUpdateOrder();                   

   /**
    * This method attempts to find the string key in the
    * collection of CBEs gets the corresponding CBEBase
    * pointer and assigns the supplied pointer
    * to the one found in the collection.
    * 
    * After a call to this method, the EventUpdateOrder
    * object still owns the CBEBase pointer and thus
    * will delete it.
    * 
    * If no key is found, a condition is added
    * and we return false;
    * 
    * @param strKey   An arbitrary string value to associate with
    *                 the CBE.  This value must be unique to the
    *                 current collection of CBEs in the EventUpdateOrder
    *                 object. The value usually is a one word
    *                 description of the event. e.g.("NEWACCOUNT1")
    * @param pCBEBase A pointer to a pointer to a CBEBase object
    * @return true if successful
    *         false if the CBE string key is not found
    * @see registerCBE
    */
   bool getCBE( const DString& strKey, CBEBase ** pCBEBase );

   /**
    * This method returns a CBEBase pointer based on
    * an index value that corresponds to a
    * registered CBE.
    * 
    * @param nCBEIndex an integer value that corresponds to a registered
    *                  CBE
    * @return A CBEBase pointer
    * @see registerCBE
    */
   CBEBase * getCBE( const int nCBEIndex ) const;

   /**
    * This method returns the number of CBEs that have
    * been registered with and EventUpdateOrder object.
    * 
    * @return an integer value of the number of CBEs that have
    *         been registered with and EventUpdateOrder object.
    * @see registerCBE
    */
   int getCBECount() const;

   /**
    * This method returns an Updater object pointer
    * based on the passed in string value.
    * An Updater object must be registered with the
    * EventUpdateOrder object before this method
    * can be called successfully.
    * 
    * @param strUpdaterId
    *               A unique string value that corresponds with a
    *               registered Updater object.
    * @return An Updater object pointer
    */
   Updater * getUpdaterPointer( const DString& strUpdaterId ) const;

   /**
    * This method checks to see if the current 
    * EventUpdateOrder object contains any
    * registered CBEs.
    * 
    * @return true if successful
    *         false if failure
    * @see registerCBE
    * @see deregisterCBE
    */
   bool hasCBEs();

   /**
    * Cycles through all registered CBEs and calls
    * the refresh method on each CBE.
    * 
    * @return NO_CONDITION if successful
    */
   SEVERITY refresh();

   /**
    * Register a CBEBase derived object with an
    * EventUpdateOrder object.
    * 
    * This method can be called multiple times since
    * an EventUpdateOrder object can hold one to many
    * CBEBase derived objects.  CBEs will be processed
    * in the order that they are registered.
    * 
    * @param pCBEBase  A CBEBase pointer to add to the CBE collection.
    * @param strKey    An arbitrary string value to associate with
    *                  the CBE.  This value must be unique to the
    *                  current collection of CBEs in the EventUpdateOrder
    *                  object. The value usually is a one word
    *                  description of the event. e.g.("NEWACCOUNT1")
    * @param fOwnedByManager
    *                  A boolean value to specify that an EventUpdateOrder
    *                  object owns the CBEBase pointer and thus will
    *                  take care of deleting the pointer upon
    *                  destruction of the EventUpdateOrder object.
    *                  
    *                  it defaults to true.
    * @param strUpdaterId
    *                  A unique string value that corresponds with a
    *                  registered Updater object. This value specifies
    *                  which Updater object you want this CBE to use
    *                  for updates to the host
    *                  
    *                  it defaults to null string
    * @param nPosition An integer value that specifies where you want the
    *                  CBE in the collection of CBEs. If you pass a
    *                  zero for the position the CBE will be put
    *                  at the front of the collection.  Any non zero
    *                  value will cause the CBE to be put at the end
    *                  of the collection.
    *                  
    *                  it defaults to 1
    * @return true if successful
    *         false if failure
    * @see deregisterCBE
    * @see removeAllCBEs
    * @see removeCBE
    * @see registerUpdater
    */
   virtual bool registerCBE( CBEBase * pCBEBase,
                             const DString& strKey,
                             bool fOwnedByManager = true,
                             const DString& strUpdaterId = I_(""),
                             const int nPosition = 1 );

   /**
    * Use this method to register an Updater object
    * with an EventUpdateOrder object.
    * 
    * You can have a CBE use a specific registered
    * Updater object by specifying the Updater you
    * want to use when calling the registerCBE method.
    * 
    * @param pUpdater A pointer to and Updater object that will be used
    *                 during the update process.
    * @param strUpdaterId
    *                 A unique string value that will correspond with a
    *                 registered Updater object.
    * @return 
    * @see getUpdaterPointer
    */
   bool registerUpdater( Updater * pUpdater, const DString& strUpdaterId );   
   
   /**
    * This method will clear the EventUpdateOrder object
    * of any registered CBEs. If the EventUpdateOrder
    * object owns the CBE pointers then he will delete
    * them.
    * 
    * This method will also make a call to the
    * notifyOnBackout method for each contained CBE.
    * 
    * This method also removes any registered Updater
    * objects.
    * 
    * @see registerCBE
    */
   void removeAllCBEs();

   /**
    * This method will remove an individual CBE from
    * the collection of registered CBEs.  If the
    * EventUpdateOrder object owns the CBE pointer
    * then he will delete it.
    * 
    * This method will also make a call to the
    * notifyOnBackout method for the contained CBE.
    * 
    * @param strKey An arbitrary string value to associate with
    *               the CBE.  This value must be unique to the
    *               current collection of CBEs in the EventUpdateOrder
    *               object. The value usually is a one word
    *               description of the event. e.g.("NEWACCOUNT1")
    * @return true if successful
    *         false if failure
    * @see registerCBE
    */
   bool removeCBE(const DString& strKey);

   /**
    * This method calls the updateNoCommit method
    * and the commit method. The data that is
    * extracted from the registered CBEs will be
    * sent to the host.
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
    * @return NO_CONDITION if successful
    * @see updateNoCommit
    * @see commit
    * @see registerCBE
    */
   virtual SEVERITY update( const bool bIgnoreDuplicate = true );            

   /**
    * This method kicks off the data gathering process.
    * Any data that is gathered from the registered
    * CBEs will not be sent to the host. The
    * commit method will need to be called to get
    * the data to the host. This allows for batching and re-working of
    * business transactions.
    * 
    * This method will make a call to the update method
    * that has been implemented in a derived class
    * from CBEBase/CBEBaseImpl.
    * 
    * This method will also call the notifyOnUpdate
    * pass-through method for the registered CBE.
    * 
    * @return NO_CONDITION if successful
    * @see commit
    * @see registerCBE
    */
   virtual SEVERITY updateNoCommit();
   

private://Methods

    /**
     * This method clears out the data
     * contained in all of the registerd Updater object
     * pointers.
     * 
     * @see _markAllCBESNotBuilt
     */
   void clearData();

   /**
    * copy constructor
    * 
    * @param copy
    */
   EventUpdateOrder( const EventUpdateOrder &copy );
   
   /**
    * operator equal
    * 
    * @param copy
    */
   EventUpdateOrder& operator=( const EventUpdateOrder &copy );
   
   /**
    * This method sets the boolean value to false
    * that specifies whether or not a CBE has been built.
    * A CBE is marked as built if it has been ran
    * through the updateNoCommit() method.
    * 
    * @see updateNoCommit
    */
   void _markAllCBESNotBuilt();


private://Attributes

   typedef struct
   {
      CBEBase     *pCBE;
      DString      strKey;
      bool        fOwnedByEventUpdateOrder;
      DString      strUpdaterId;
      bool        fBuilt;
   } MANAGED_OBJECT_INFO;

   typedef vector< MANAGED_OBJECT_INFO > managedObjectVector;
   managedObjectVector _vectorObjects;

   typedef struct
   {
      Updater     *pUpdater;
      DString      strUpdaterId;
   } ORDERED_UPDATERS;
   
   //This vector will be used for cross-referencing a cbe and its associated updater
   typedef vector< ORDERED_UPDATERS > updaterVector;
   updaterVector _vecUpdaters;
   bool _bBatchMode;


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
// $Log:   Y:/VCS/iFastAWD/inc/eventupdateorder.hpp-arc  $
//
//   Rev 1.0   28 Jan 2008 13:31:30   kovacsro
//Initial revision.
// 
//    Rev 1.7   28 Nov 2001 12:41:52   dt14177
// fixed linkage define
// 
//    Rev 1.6   Dec 29 2000 09:20:40   dt39990
// Added more documentation and 
// organized methods in alphabetical listing
// 
// 
//    Rev 1.5   25 Oct 2000 10:35:48   dt14177
// some cleanup - a lot of doc still needed
// 
//    Rev 1.4   Jan 04 2000 04:46:16   DT29758
//  
// 
//    Rev 1.3   Dec 29 1999 13:46:34   DT29758
// Modified comments to fit JavaDoc standard
// 
//    Rev 1.2   Dec 08 1999 12:22:56   DT29758
// added an attribute addressing batch
// processing mode
// 
//    Rev 1.1   Nov 11 1999 16:31:58   DT29758
// added unicode support and utilization of
// indexes for data object fields
// 
//    Rev 1.0.1.1   Jul 22 1999 13:35:56   DT22388
// Performed code clean-up and added #undefs
// for the substitution string i.e. $strParentImplClass$.
// Also, added #includes for test classes.
// 
// 
//    Rev 1.0.1.0   Jul 06 1999 13:24:12   DT22388
// Changed the managed_object_info
// to us a string to identify the unique updater
// instead of a pointer.
// 
//    Rev 1.0   Jun 21 1999 17:14:56   DT22388
//  
// 
//    Rev 1.1   Jan 14 1999 13:05:14   DT21815
// Changed #include file names to lower case.
// 
//    Rev 1.0   29 Jul 1998 23:57:20   dt14596
// DLMG New Archives for TA2000NTDT
// 
//    Rev 1.13   Mar 25 1998 15:41:46   djoo
// Added method dumpCBEs.
// 
//    Rev 1.12   Mar 09 1998 09:53:18   djoo
// Modified the return for setNonFinancialBatchNumber
// and setFinancialBatchNumber.
// 
//    Rev 1.11   Mar 06 1998 16:24:04   djoo
// Added methods setFinancialBatchNumber, 
// getFinancialBatchNumber, setNonFinancialBatchNumber
// and getNonFinancialBatchNumber.
// 
//    Rev 1.10   Mar 03 1998 12:13:40   djoo
// Removed static counter and method clearCBEUpdatedLabels.
// 
//    Rev 1.9   Feb 27 1998 13:36:42   djoo
// Added method clearCBEUpdatedLabels.
// 
//    Rev 1.8   Feb 09 1998 13:06:56   djoo
// Added method hasCBEs.
// 


