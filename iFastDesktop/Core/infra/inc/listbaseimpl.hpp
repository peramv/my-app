#ifndef LISTBASEIMPL_HPP
#define LISTBASEIMPL_HPP

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

#ifndef  DATA_HPP
#include "data.hpp"
#endif

#ifndef  DSTRING_HPP
#include "dstring.hpp"
#endif

#ifndef  COMMONPORT_H
#include "commonport.h"
#endif

#ifndef  CONDITION_HPP
#include "condition.hpp"
#endif

/**@#-*/
using namespace std;
/**@#+*/

class ListIterator;

// Import/Export resolution
#undef CBOBASE_LINKAGE
#ifdef DICBOCORE_DLL
    #define CBOBASE_LINKAGE CLASS_EXPORT
#else
    #define CBOBASE_LINKAGE CLASS_IMPORT
#endif

/**
 * A base class for read only lists and updatable lists.
 * 
 * ListBaseImpl has a corresponding interface class
 * called ListBase. The ListBase methods are
 * just pass-through methods to the ListBaseImpl
 * methods.
 * 
 * The interface/implementation concept is known
 * as the "bridge" pattern or "handle/body" pattern
 * as found in the  Design Patterns(GOF95') book.
 * 
 * 
 * The ListBaseImpl class contains methods
 * used for retrieving read-only lists based on fixed and repeat Data objects
 * ListBaseImpl is a wrapper class for a repeat data object.
 * 
 * Derive a class from ListBaseImpl if you need to
 * represent a business list.(e.g. StateCountryListImpl)
 * 
 * The methods implemented within a ListBaseImpl derived class
 * should follow the concept of keeping data with its
 * representation.  As an example, "is" methods can
 * be written in a derived class to access an
 * individual repeat, grab one or more values,
 * and perform certain value checks
 * in order to answer a business question.
 * 
 * A derived class would do the following:
 * <pre><dir>
 * setViewData( pView0316Data ); //This set registers the data pointer with listbaseimpl
 * pDataBroker->receive( "VIEW0316", view0316Request, *pView0316Data );//call retriever view and fill our data object
 * Data *pView0316Data = getViewData();//Get the data object out of listbaseimpl
 * if( pView0316Data->getElementValue( "More_Records_Exist" ) == "Y" )//check a tag in the fixed data area for more records
 * </pre></dir>
 * 
 * It should be used for all read only lists and updatable lists.
 * UpdatableListBaseImpl derives from ListBaseImpl
 * 
 * @see Data
 * @see UpdatableListBaseImpl
 */
class CBOBASE_LINKAGE ListBaseImpl
{
   public:
      // %BEGIN_INTERFACE%

      /**
       * Retrieves a subset(range) of repeats based on the
       * passed in IDI string. The pair of iterators return
       * are the begin and end iterators.  
       * 
       * @param strValue An IDI string, example: Fund_Code=0000001;Account_Number=00000054961;
       * @return A pair of ListIterator objects. The first ListIterator
       *         points the beginning of the requested
       *         range(list items). The second ListIterator points
       *         to the end of the requested range(list items).
       */
      pair<ListIterator,ListIterator> equal_range( const DString& strValue ) const;

      /**
       * Get the fixed portion of the view return data.
       * The fixed portion contains the non-repeatable data.
       * Look at view0316 for an example. The group info is in
       * the fixed non-repeatable area.  It is OK if the fixed
       * data area does not exist.
       * Example Usage:
       * <pre><dir>
       * if( getFixedData( viewDataItem ) )
       * {
       *    string strMoreRecords;
       *    viewDataItem.getElementValue( "More_Records_Exist", strMoreRecords );
       * }
       * </pre></dir>
       * 
       * @param viewDataItem
       *               A reference to a data object that will be filled with the fixed data.
       * @return true if successful
       *         false if failure
       * @see Data
       */
      virtual bool getFixedData( Data & viewDataItem ) const;
      
      /**
       * Get the fixed portion of the view return data.
       * The fixed portion contains the non-repeatable data.
       * Look at view0316 for an example. The group info is in
       * the fixed non-repeatable area.  It is OK if the fixed
       * data area does not exist.
       * 
       * @return A Data object that will be filled with the fixed
       *         data.
       * @see Data
       */
      virtual const Data& getFixedData( void ) const;

      /**
       * Get a single view repeat by using a zero based
       * index number.  A Zero based index is an index that
       * starts at the value 0 and not 1.
       * 
       * @param nZeroBasedIndex
       *               An index number of the repeat, starting at zero.
       * @param viewDataItem
       *               A reference to a data object that will be filled with
       *               a single repeat's data.
       * @return true if successful
       *         false if failure.
       * @see Data
       */
      virtual bool getListItem( int nZeroBasedIndex, Data &viewDataItem ) const;

      /**
       * Get a single view repeat by using a zero based
       * index number.  A Zero based index is an index that
       * starts at the value 0 and not 1.
       * 
       * @param nZeroBasedIndex
       *               An index number of the repeat, starting at zero.
       * @return A Data object that will be filled with
       *         a single repeat's data.
       * @see Data
       */
      virtual const Data& getListItem( int nZeroBasedIndex ) const; 

      /**
       * Get a single view repeat by using a Data object for the request.
       * 
       * @param dataIDI A data object that will be flattend out
       *                into an IDI string, example: Fund_Code=0000001;Account_Number=00000054961;.
       * @param data    The return Data object to be filled with a single
       *                repeat
       * @return NO_CONDITION if successful
       * @see Data
       */
      virtual SEVERITY getListItem( const Data& dataIDI, Data& data )const;

      /**
       * Get a zero based index for a
       * view repeat for the passed IDI string.
       * The IDI string represents the search citeria.
       * 
       * @param strIDIString
       *               An IDI string, example: Fund_Code=0000001;Account_Number=00000054961;.
       * @return An integer value greater than or equal to zero if
       *         found
       *         A -1 if the item is not found
       * @see Data
       */
      virtual int getListItemNumber( const DString& strIDIString ) const; 

      /**
       * Get a single view repeat field value by
       * using a Data object for the request.
       * 
       * @param dataIDI    A data object that will be flattend out
       *                   into an IDI string, example: Fund_Code=0000001;Account_Number=00000054961;.
       * @param strDataTag The individual field you are looking for
       * @return a string value of an individual field
       *         a null string if not found
       * @see Data
       */
      virtual DString getListItemValue( const Data& dataIDI, const DString& strDataTag ) const;

      /**
       * Get number of view repeats in the contained
       * Data object
       * 
       * @return An unsigned long value greater than zero if repeats
       *         exist
       *         zero if there are no repeats in the contained
       *         Data object.
       * @see Data
       */
      virtual unsigned long getNumberOfItemsInList( void ) const; 

      /**
       * Determine if the setViewData method has been called
       * on an instance of the ListBase derived class.
       * 
       * @return true if the setViewData() method has been called.
       *         false if the setViewData() method has not been called.
       * @see setViewData
       */
      virtual bool isInitialized( void ) const;

      /** Constructor */
      ListBaseImpl();

      /** Destructor
       *  Deletes the pointer to the repeat Data object
       */
      virtual ~ListBaseImpl();

      /**
       * Assignment operarator
       * 
       * @param copy
       * @return 
       */
      ListBaseImpl& operator=( const ListBaseImpl& copy );

      /**
       * This method should be defined in a derived class.
       * The derived class implementation should make
       * a view call again or call the init() method again.
       * 
       * @return NO_CONDITION if successful
       */
      virtual SEVERITY refreshList();

      /**
       * Will set the protected variable in the implementation class
       * 
       * 
       * @param bool fIsInitialized
       */
      void setIsInitialized( bool fIsInitialized );

      
      // %END_INTERFACE%


   protected:

      /**
       * Called by all of the derived classes to get the data object that contains
       * the fixed data plus all of the repeat data.  This
       * method is used after making a call to the
       * setViewData() method.  Use this method when
       * dealing with "more record processing".  This
       * method will allow you to get the existing
       * repeat data object and append more repeats as
       * needed.
       * 
       * @return A Data object that may have fixed and repeat data,
       *         
       *         Returns null if the Data object pointer has not
       *         been set.
       * @see setViewData
       * @see Data
       */
      Data * getViewData( void ) const;

      /** Copy Constructor */
      ListBaseImpl( const ListBaseImpl &copy );

      /**
       * Called by all of the derived classes to set the data object that contains
       * the fixed data plus all of the repeat data.  This
       * method should be called from a derived classes 
       * init(). UpdatableListBaseImpl derived classes will need
       * to also call this method from their init() methods. 
       * 
       * @param pViewData A pointer to a data object used for the view call
       * @see getViewData
       * @see Data
       * @see UpdatableListBaseImpl
       */
      void setViewData( Data * pViewData );


// protected data
   protected:
      bool          _fIsInitialized;

// Private data
   private:
      Data         *_pViewData;
      Data         *_pRepeatRecord;
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
// $Log:   Y:/VCS/iFastAWD/inc/listbaseimpl.hpp-arc  $
//
//   Rev 1.0   28 Jan 2008 13:32:10   kovacsro
//Initial revision.
// 
//    Rev 1.8   28 Nov 2001 12:42:04   dt14177
// fixed linkage define
// 
//    Rev 1.7   Dec 27 2000 11:06:42   dt39990
// Added more documentation and 
// organized methods in alphabetical listing
// 
//    Rev 1.6   Aug 23 2000 08:52:36   DT29758
// moved variable _isInitialized from private to
// protected and added method setIsInitialized for setting of 
// protected variable
// 
//    Rev 1.5   Dec 31 1999 06:27:48   DT29758
// Minor Edits to Java-Doc comments
// 
//    Rev 1.3   Dec 06 1999 10:21:40   DT29758
// added ccdoc code tag directives for using 
// namespaces
// 
//    Rev 1.2   Dec 01 1999 10:52:42   DT29758
// added cc-doc style comments
// 
//    Rev 1.1   Nov 11 1999 16:32:06   DT29758
// added unicode support and utilization of
// indexes for data object fields
// 
//    Rev 1.0   Jun 21 1999 17:15:18   DT22388
//  
// 
//    Rev 1.2   Feb 25 1999 11:07:04   DT21815
// Added new methods: getValueByIDI,
// getDataObjectByIDI, and equal_range.
// 
// Added private methods: equal_range_by_idi
// and _buildIDI.
// 
//    Rev 1.1   Jan 14 1999 12:16:50   DT21815
// Changed #include file names to lower case.
// 
//    Rev 1.0   29 Jul 1998 23:58:34   dt14596
// DLMG New Archives for TA2000NTDT
// 
//    Rev 1.10   Feb 27 1998 13:28:52   djoo
// Added pseudo- virtual method refreshList().
// 
//    Rev 1.9   Nov 11 1997 15:31:10   djoo
//  
// 
//    Rev 1.8   03 Oct 1997 15:48:10   djbh
// Added an overloaded method for getFixedData
// that will return a const reference to a Data
// object
// 
//    Rev 1.7   26 Sep 1997 15:18:36   djbh
// Added an overloaded method getListItem that
// returns a const Data reference to help improve
// efficiency.
// 
//    Rev 1.6   17 Sep 1997 11:15:24   dmal
// removed repeatcnt from SetViewData method.
// 
//    Rev 1.5   02 Sep 1997 17:20:20   djbh
// Made changes to improve listbase efficiency
// with databroker
// 
//    Rev 1.4   16 Aug 1997 12:00:12   dmal
//  
//
//    Rev 1.3   11 Aug 1997 09:43:02   dlkt
// Added init method for initialization.
//
//    Rev 1.2   Jul 10 1997 17:41:30   DPQD
// Removed all occurrences of ErrorList
//
//    Rev 1.1   12 Jun 1997 09:18:38   dmal
// changed getComponet to getData and added
// getListItemNumber method. DJBH
//
//

#endif



