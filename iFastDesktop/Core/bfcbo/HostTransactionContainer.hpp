#pragma once

//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by DST Systems, Inc.,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 1999 by DST Systems, Inc.
//
//
//******************************************************************************
//
// ^FILE   : HostTransactionContainer.hpp
// ^AUTHOR : Mihai Virgil Buzila & Serban Popescu
// ^DATE   : September 1999
//
// ^CLASS    : HostTransaction
// ^INHERITS FROM :
//
// ^CLASS DESCRIPTION :
//
//
//******************************************************************************

#include <bfcbo\bfcbo.hpp>
#include <bfcbo\jdata.hpp>
#include <bfdbrkr\bfrequest.hpp>
#include <bfutil\bfcritsec.hpp>
#include <dstring.hpp>

/**
 * This enum put here just for the purpose of NO_GROUP
 * its place is in the specific host data managers
 *
 * <pre>
 *@@  NO_GROUP   - the only value
 * </pre>
 */
enum TRXN_GROUP
{
   NO_GROUP
};


//CP20030128enum TRXN_TYPE
//CP20030128{
//CP20030128   NO_TRXN,
//CP20030128   NEW_SHAREHOLDER, //for new shareholder
//CP20030128   UPDATE_SHAREHOLDER, //for updating a shareholder (includes delete)
//CP20030128   NEW_ACCOUNT, //(...follow the above pattern)
//CP20030128   UPDATE_ACCOUNT,
//CP20030128   NEW_ENTITY,
//CP20030128   UPDATE_ENTITY,
//CP20030128   NEW_ENTITY_IDS,
//CP20030128   UPDATE_ENTITY_IDS,
//CP20030128   NEW_ACCOUNT_ENTITY,
//CP20030128   UPDATE_ACCOUNT_ENTITY,
//CP20030128   NEW_ADDRESS,
//CP20030128   UPDATE_ADDRESS,
//CP20030128   NEW_MAILING,
//CP20030128   UPDATE_MAILING,
//CP20030128   NEW_AS_PENSION,
//CP20030128   UPDATE_AS_PENSION,
//CP20030128   NEW_ESOP,
//CP20030128   UPDATE_ESOP,
//CP20030128   NEW_FEE_PARAM,
//CP20030128   UPDATE_FEE_PARAM,
//CP20030128   UPDATE_FEE_PARAM_SYS,
//CP20030128   UPDATE_SETTLEMENT,
//CP20030128   NEW_CATEGORY,
//CP20030128   UPDATE_CATEGORY,
//CP20030128
//CP20030128   //FAST TRANSACTIONS
//CP20030128   CLIENT_UPDATE,
//CP20030128   DEBIT_CARD_UPDATE,
//CP20030128   UNITHOLDER_UPDATE,
//CP20030128   PRODUCT_HOLDING_UPDATE,
//CP20030128   DEAL_UPDATE,
//CP20030128   SETTLEMENT_UPDATE,
//CP20030128   AGENT_COMMISSION_UPDATE,
//CP20030128   SUBSCRIPTION_UPDATE,
//CP20030128   UH_AGENT_UPDATE,
//CP20030128   COLLECTION_DETAILS_UPDATE,
//CP20030128   RSF_INSTRUCTION_UPDATE,
//CP20030128   INCOME_ALLOC_UPDATE,
//CP20030128   RIF_INSTRUCTION_UPDATE,
//CP20030128
//CP20030128   NOT_PERSISTENT, //this should always be the last item of the enum
//CP20030128};
//CP20030128

#undef BFBASE_LINKAGE
#ifdef BFBASE_DLL
   #define BFBASE_LINKAGE CLASS_EXPORT
#else
   #define BFBASE_LINKAGE CLASS_IMPORT
#endif

class BFBASE_LINKAGE TRXN_TYPE
{
public:
   TRXN_TYPE();
   explicit TRXN_TYPE( const I_CHAR* pszTrxnName );
   TRXN_TYPE( const TRXN_TYPE& rhs );
   ~TRXN_TYPE();

   TRXN_TYPE& operator=( const TRXN_TYPE& rhs );

   bool operator==( const TRXN_TYPE& rhs ) const
   { return( id_ == rhs.id_ ); }
   bool operator<( const TRXN_TYPE& rhs ) const 
   { return( id_ < rhs.id_ ); }
   bool operator!=( const TRXN_TYPE& rhs ) const 
   { return !((*this) == rhs); }

   int getId() const { return id_; }
   const DString& getName() const { return dstrName_; }

private:
   int id_;
   DString dstrName_;

   static BFCritSec s_cs_;
   static int s_idNext_;
};

extern BFBASE_LINKAGE TRXN_TYPE NO_TRXN;
extern BFBASE_LINKAGE TRXN_TYPE NOT_PERSISTENT;


/**
 * this is the transaction container that is used in keeping the transactions
 * after are build and until are commited to the host
 *
 * @author Mihai Virgil Buzila & Serban Popescu
 * </dd></dl><p><dl><dt><b>Date Created:</b></dt><dd> September 1999 </dd></dl>
 * @version 0.1
 */


class BFBASE_LINKAGE HostTransactionContainer
{
   friend class HostTransactionContainerIterator;

public:
   //constructor
   HostTransactionContainer();
   //destructor
   virtual ~HostTransactionContainer();

   /**
     * adds a transaction to the container
     * @param key         - the key
     * @param jdata       - JData pointer
     * @param objActivity - the activity
     * @param tranType    - transaction type
     * @param keyTypes    - the type of the key
     * @param trxnGroup   - what transaction group
     * @param trxnSubType - the transaction subtype
     */
   void addTransaction( const DString& key,
                        JData* jdata= NULL,
                        BF_OBJ_ACTIVITY objActivity = OBJ_ACTIVITY_NONE,
                        TRXN_TYPE tranType = NO_TRXN,
                        const DString& keyTypes = DString( NULL_STRING ),
                        long trxnGroup = NO_GROUP,
                        long trxnSubType = 0 );


   /**
     * gets a specific transaction from the container
     * @param dstrKey         - key built ( usually in trxnbuilder::buildTrxnKey ) for this trxn
     * @param objActivity - was defaulted in HTC::addTransaction see ^
     * @param trxnType    - was defaulted in HTC::addTransaction see ^
     * @param keyTypes    - was defaulted in HTC::addTransaction see ^
     * @param trxnGroup   - was defaulted in HTC::addTransaction see ^
     * @param trxnSubType - was defaulted in HTC::addTransaction see ^
     */
   HostTransactionContainerIterator getTransaction( const DString& dstrKey,
                                                    BF_OBJ_ACTIVITY objActivity = OBJ_ACTIVITY_NONE,
                                                    TRXN_TYPE trxnType = NO_TRXN,
                                                    const DString& keyTypes = DString( NULL_STRING ),
                                                    long trxnGroup = NO_GROUP,
                                                    long trxnSubType = 0 );
   /**
     * clears out the container
     */
   void clearContainer();
   /**
     * clears out the uncomited transactions
     */
   void clearUncommitedTransactions();

private:

   class HTC_Key
   {
   public:
      //used to group together transactions, specific for each host
      long        _trxnGroup;
      //identifies the transaction type at the host level
      TRXN_TYPE   _trxnType;
      //identifies the transaction subtype, specific for each host
      long        _trxnSubType;
      //used to define if an object is added/deleted
      BF_OBJ_ACTIVITY _objActivity;
      //used to identify the transaction based on the key string,
      //should hold information from which the containment rules
      //can be extracted
      DString     _strKey;
      //this doesn't count in ordering the transactions, it will
      //be and IDI string; the transaction builders intersted in replacing
      //temp values of database keys should register here
      DString     _keyTypes;

      HTC_Key( long trxnGroup,
               TRXN_TYPE tranType,
               long trxnSubType,
               BF_OBJ_ACTIVITY objActivity,
               const DString& strKey,
               const DString& keyTypes ) :
      _trxnGroup( trxnGroup ),
      _trxnType( tranType ),
      _trxnSubType( trxnSubType ),
      _objActivity( objActivity ),
      _strKey( strKey ),
      _keyTypes( keyTypes )
      {
      };
   };
   class less_HTC_Key
   {
   public:
      bool operator()( const HTC_Key& a, const HTC_Key& b )
      {
         if( a._trxnGroup != b._trxnGroup )
            return(a._trxnGroup < b._trxnGroup);
         else if( a._trxnSubType != b._trxnSubType )
            return(a._trxnSubType < b._trxnSubType);
         else if( a._trxnType != b._trxnType )
            return(a._trxnType < b._trxnType);
         else if( a._objActivity != b._objActivity )
            return(a._objActivity < b._objActivity);
         else
            return(a._strKey < b._strKey);
      }
   };

   typedef std::map < HTC_Key, JData*, less_HTC_Key >   TRXN_MAP;
   typedef TRXN_MAP::iterator                           TRXN_MAP_ITER;
   TRXN_MAP _trxnMap;
};

//the purpose of this class is to hide the key of the HostTransactionContainer object
//and to define filters for walking the HostTransactionContainer
/**
 * the purpose of this class is to hide the key of the HostTransactionContainer object
 * and to define filters for walking the HostTransactionContainer
 *
 * @author Serban Popescu
 * </dd></dl><p><dl><dt><b>Date Created:</b></dt><dd> September 1999 </dd></dl>
 * @version 0.1
 */
class BFBASE_LINKAGE HostTransactionContainerIterator
{

private:
   HostTransactionContainer::TRXN_MAP_ITER   _iter;
   HostTransactionContainer::TRXN_MAP*       _map;
   DString    _walkStrKey;
   long       _walkTrxnGroup;
   long       _walkTrxnSubType;
   long       _filter;
   //this is more powerfull then positioning on the next match
   //if the trxn group filter is set;
   //the caller will expect that elements that have the
   //<_trxnGroupToSkip> trxn group should be skipped
   long       _trxnGroupToSkip;
//filter flags
#define FILTER_HOST           0x0001
#define FILTER_STRKEY         0x0002
#define FILTER_TRXNGRP        0x0004
#define FILTER_TRXNSUBTYPE    0x0008
#define FILTER_SKIPTRXNGRP    0x0010

private:
   void filter()
   {
#if _DEBUG
      bool c1, c2, c3, c4;
#endif
      while( (_iter != _map->end()) && //end of the map
             //not matching the host filter, if set
             ( (
#if _DEBUG
               c1 =
#endif
               (FILTER_STRKEY & _filter) && (*_iter).first._strKey != _walkStrKey) ||
               //matching the trxn group to skip, if set; this goes before the trxn group filter,
               //so if both are set consider this one first
               (
#if _DEBUG
               c2 =
#endif
               (FILTER_SKIPTRXNGRP & _filter) && (*_iter).first._trxnGroup == _trxnGroupToSkip ) ||
               //not matching the trxn group filter, if set
               (
#if _DEBUG
               c3 =
#endif
               (FILTER_TRXNGRP & _filter) && (*_iter).first._trxnGroup != _walkTrxnGroup) ||
               //not matching the trxn sub type filter, if set
               (
#if _DEBUG
               c4 =
#endif
               (FILTER_TRXNSUBTYPE & _filter) && (*_iter).first._trxnSubType != _walkTrxnSubType)
             )
           )
      {
         //skip this element, it doesn't match the criteria set by the filters
         ++_iter;
      }
   };
public:
   typedef std::pair< HostTransactionContainer::HTC_Key, JData* > HTC_pair;

   /**
    * constructor
    * @param _hostTransactionContainer - which container
    */
   HostTransactionContainerIterator( HostTransactionContainer* _hostTransactionContainer )
   {
      _map = &_hostTransactionContainer->_trxnMap;
      _walkTrxnGroup = NO_GROUP;
      _walkTrxnSubType = 0;
      _trxnGroupToSkip = 0;
      _filter = 0x0000;
   };
   /**
    * destructor
    */
   ~HostTransactionContainerIterator()
   {
   };
   /**
    * copy constructor
    * @param htcIterator - iter reference
    */
   HostTransactionContainerIterator( const HostTransactionContainerIterator& htcIterator )
   {
      _iter = htcIterator._iter;
      _map = htcIterator._map;
   };
   /**
    * put the iterator on the begining of container
    * @param applyfilter - do we want to apply the filter
    * @param resetfilter - do we want to reset the filter
    */
   void begin( bool applyfilter = true, bool resetfilter = false )
   {
      if( resetfilter )
      {
         _filter = 0x0000;
      }
      _iter = _map->begin();
      if( applyfilter )
      {
         filter();
      }
   };
   /**
    * are we  on the end ?
    */
   bool end()
   {
      return(_iter == _map->end());
   };
   /**
    * deletes the item where we are posioned on
    */
   void erase()
   {
      _iter = _map->erase( _iter );
   };
   //this method will erase the entry in the map and also delte the pointer
   /**
    * erases the entry in the map and also deletes the pointer
    */
   void remove()
   {
      delete (*_iter).second;
      erase();
   };
   /**
    * advances the iterator
    */
   void operator++()
   {
      //move to the next position
      ++_iter;
      filter();
   };
   /**
    * returns a pair
    */
   HTC_pair pair()
   {
      return(std::make_pair( (*_iter).first, (*_iter).second ));
   };
   /**
    * inserts the pair
    */
   HostTransactionContainerIterator& operator=( const HTC_pair& pair )
   {
      _iter = _map->insert( pair ).first;
      return(*this);
   };
   /**
    * dereferentiates the iterator
    */
   JData* operator*()
   {
      return(*_iter).second;
   };
   /**
    * walks the map filtered on strKey
    * @param strKey - filter condition
    */
   void walkStrKey( DString& strKey )
   {
      _filter |= FILTER_STRKEY;
      _walkStrKey = strKey;
   };
   /**
    * walks the map within the transaction group
    * @param walkTrxnGroup - which group
    */
   void walkTrxnGroup( long walkTrxnGroup )
   {
      _filter |= FILTER_TRXNGRP;
      _walkTrxnGroup = walkTrxnGroup;
   };
   /**
    * walks the map within the items that have a transaction subtype
    * @param walkTrxnSubType - which transaction subtype
    */
   void walkTrxnSubType( long walkTrxnSubType )
   {
      _filter |= FILTER_TRXNSUBTYPE;
      _walkTrxnSubType = walkTrxnSubType;
   };
   /**
    * moves to transaction group trxnGroupToSkip
    * @param trxnGroupToSkip - to which transaction group to skip
    */
   void skipTrxnGroup( long trxnGroupToSkip )
   {
      _filter |= FILTER_SKIPTRXNGRP;
      _trxnGroupToSkip = trxnGroupToSkip;
   };
   /**
    * resets the filter
    */
   void resetFilter()
   {
      _filter = 0x0000;
   };
   //accessors for the key
   /**
    * returns the transaction group for the item on which we are positioned on
    */
   long trxnGroup()
   {
      return(*_iter).first._trxnGroup;
   };
   /**
    * returns the transaction type for the item on which we are positioned on
    */
   TRXN_TYPE trxnType()
   {
      return(*_iter).first._trxnType;
   };
   /**
    * returns the transaction subtype for the item on which we are positioned on
    */
   long trxnSubType()
   {
      return(*_iter).first._trxnSubType;
   };
   /**
    * returns the object activity for the item on which we are positioned on
    */
   BF_OBJ_ACTIVITY objActivity()
   {
      return(*_iter).first._objActivity;
   };
   /**
    * returns the strKey for the item on which we are positioned on
    */
   const DString& strKey()
   {
      return(*_iter).first._strKey;
   };
   /**
    * returns the keyTypes for the item on which we are positioned on
    */
   const DString& keyTypes()
   {
      return(*_iter).first._keyTypes;
   };
   //accessors for the right side

   BFData* getRequest()
   {
      return(**this)->_pdataRequest;
   };

   BFData* getResponse()
   {
      return(**this)->_pdataResponse;
   };

   void setCommited( bool commited )
   {
      (**this)->_blCommited = commited;
   };

   bool isCommited()
   {
      return(**this)->_blCommited;
   };

   const BFRequest& request()
   {
      return(**this)->_rbfRequest;
   };

   const DString& getRequestId()
   {
      return((**this)->_rbfRequest).getId();
   };

};


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF Core/bfcbo/HostTransactionContainer.hpp-arc  $
 * 
 *    Rev 1.22   Feb 07 2003 10:48:52   PURDYECH
 * Changed TRXN_TYPE from enum to class so that projects can define unique ones in the application classes.
 * 
 *    Rev 1.21   Jan 23 2003 11:22:52   PURDYECH
 * Added NEW_CATEGORY and UPDATE_CATEGORY for Robert
 * 
 *    Rev 1.20   Jan 17 2003 09:28:14   PURDYECH
 * Added UPDATE_FEE_PARAM_SYS
 * 
 *    Rev 1.19   Nov 27 2002 15:01:46   PURDYECH
 * Documentation Changes
 * 
 *    Rev 1.18   Oct 09 2002 17:40:14   PURDYECH
 * New PVCS Database
 * 
 *    Rev 1.17   Jun 12 2002 21:02:54   VASILEAD
 * Added UPDATE_SETTLEMENT
 * 
 *    Rev 1.16   22 May 2002 18:08:54   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.15   22 Mar 2002 15:11:56   PURDYECH
 * Removed compile-time "including..." message
 * Use #pragma once as include guard
 * Include files with lower-case only names
 * 
 *    Rev 1.14   Feb 22 2002 15:46:02   ROSIORUC
 * Modified order inside the enum TRXN_TYPE
 * 
 *    Rev 1.13   Feb 01 2002 15:28:40   YINGBAOL
 * Add FeeParam
 * 
 *    Rev 1.12   Oct 03 2001 18:39:32   OLTEANCR
 * added RSF_INSTRUCTION_UPDATE, INCOME_ALLOC_UPDATE,  RIF_INSTRUCTION_UPDATE;
 * 
 *    Rev 1.11   19 Sep 2001 14:52:06   KOVACSRO
 * Added ESOP.
 * 
 *    Rev 1.10   Sep 05 2001 11:45:18   IVESPAUL
 * DebitCard dealing.
 *
 *    Rev 1.9   Aug 23 2001 12:28:50   JANKAREN
 * Added As Pension Plan
 *
 *    Rev 1.8   03 May 2001 14:03:28   SMITHDAV
 * Session management restructuring.
 *
 *    Rev 1.7   Mar 07 2001 18:33:48   MCNABBGL
 * added getRequestId() to HTCIter
 *
 *    Rev 1.6   Mar 07 2001 16:05:00   MCNABBGL
 * added getTransaction method (based on key)
 *
 *    Rev 1.5   Feb 13 2001 15:46:12   MCNABBGL
 * changes for JData member access
 *
 *    Rev 1.4   Feb 06 2001 18:19:56   MCNABBGL
 * code formatting
 *
 *    Rev 1.3   Jan 16 2001 13:46:06   OLTEANCR
 * changed to use JData class instead IOData class
 *
 *    Rev 1.2   Aug 10 2000 09:03:04   DT24433
 * changed to not be a singleton - hosted by WorkSessionDetails now
 *
 *    Rev 1.1   Jul 21 2000 17:09:42   BUZILA
 * documentation added
 *
 *    Rev 1.0   Feb 15 2000 10:57:50   SMITHDAV
 * Initial revision.
//
//    Rev 1.16   Jan 14 2000 09:35:26   POPESCUS
// added a clear uncommited trxn method
//
//    Rev 1.15   Jan 07 2000 15:54:26   POPESCUS
// just checking in...
//
//    Rev 1.14   Jan 07 2000 07:48:40   BUZILA
// added clearContainer() method
//
//    Rev 1.13   Dec 19 1999 17:15:42   BUZILA
// added revision area
 *
 */

