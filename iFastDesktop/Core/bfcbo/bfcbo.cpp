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
// ^FILE   : BFCBO.cpp
// ^AUTHOR : Mike Metzger + other dudes  ( Replaces old BFBASE, ListBase, CBEBase )
// ^DATE   : May 1999
//
// ----------------------------------------------------------
//
// ^CLASS : BFCBO
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************
#include <bfutil\rtrevisiondefines.hpp>
RT_SOURCE_REVISION( "$Archive:   Y:/VCS/BF iFAST/core/bfcbo/bfcbo.cpp-arc  $$", "$Revision:   1.60  $" )

#include "bfcbo.hpp"
#include "bfobjiter.hpp"
#include "bfconstobjiter.hpp"
#include <bfdata\bfdatafielditer.hpp>
#include <bfdata\bffieldid.hpp>
#include <conditionmanager.hpp>
#include <idistring.hpp>
#include <mathstring.hpp>
#include <bfdata\bfdatafieldfactory.hpp>
#include <bfdbrkr\bfdatabroker.hpp>
#include <bfdbrkr\bfrequest.hpp>
#include <bfdbrkr\bfrequestor.hpp>
#include <bfdbrkr\asyncrequestor.hpp>
#include "bfsession.hpp"
#include "genericbfcbo.hpp"
#include <typeinfo>
#include <boost\smart_ptr.hpp>

#include <bfutil\bfguard.hpp>
#include <bfutil\txnstats.hpp>

#include <bfdata\bfdataexception.hpp>
#include <bfutil\clientlocalecontext.hpp>

#include <bf/log/logstream.hpp>
#include <bfutil\elementwriter.hpp>

class BFSecurity;

#include <ios>
#include <set>

class BFCBOGuard
{
public:
   BFCBOGuard( BFCritSec* pSem )
   : _guard( NULL )
   {
      if( BFCBO::areThreadsAllowed() )
      {
         _guard = new BFGuard( *pSem );
      }
   }
   BFCBOGuard( BFCritSec& sem )
   : _guard( NULL )
   {
      if( BFCBO::areThreadsAllowed() )
      {
         _guard = new BFGuard( sem );
      }
   }
   ~BFCBOGuard()
   {
      delete _guard;
   }

private:
   BFGuard* _guard;
};

BFCBO::BFCBOEvent::BFCBOEvent( bool bManualReset /*=false*/, bool bInitialState /*=false*/ )
: _pEvent( NULL )
{
   if( BFCBO::areThreadsAllowed() )
   {
      _pEvent = new BFEvent( bManualReset, bInitialState );
   }
}

BFCBO::BFCBOEvent::~BFCBOEvent()
{
   delete _pEvent;
}

void BFCBO::BFCBOEvent::set()
{
   if( _pEvent != NULL )
   {
      _pEvent->set();
   }
}

void BFCBO::BFCBOEvent::reset()
{
   if( _pEvent != NULL )
   {
      _pEvent->reset();
   }
}

void BFCBO::BFCBOEvent::wait( DWORD dwMilliseconds )
{
   if( _pEvent != NULL )
   {
      _pEvent->wait( dwMilliseconds );
   }
}

namespace
{
   const DString TYPE_ATTR_TAG_NAME = I_( "type" );
}

BFCBO::BFCBOTypeAttribute::BFCBOTypeAttribute( const BFDataFieldProperties* pProp )
: _type( I_( "unknown" ) )
{
   if( pProp->isText() ) {
      _type = I_( "text" );
   } else if( pProp->isDate() ) {
      _type = I_( "date" );
   } else if( pProp->isTime() ) {
      _type = I_( "time" );
   } else if( pProp->isNumeric() ) {
      _type = I_( "numeric" );
   }
}

ElementAttribute *BFCBO::BFCBOTypeAttribute::clone() const
{
   return(new BFCBOTypeAttribute(*this));
}

const DString &BFCBO::BFCBOTypeAttribute::getTagName() const
{
   return(TYPE_ATTR_TAG_NAME);
}

const DString &BFCBO::BFCBOTypeAttribute::getValue() const
{
   return(_type);
}

bool BFCBO::BFCBOTypeAttribute::hasDefaultValue() const
{
   return(false);
}

namespace
{
   // Trace literals
   const I_CHAR * const CLASSNAME = I_( "BFCBO" );

   const I_CHAR * const INIT                       = I_( "init" );
   const I_CHAR * const DELETEOBJECT               = I_( "deleteObject" );
   const I_CHAR * const INITDEFAULTS               = I_( "initDefaults" );
   const I_CHAR * const DODELETEOBJECT             = I_( "doDeleteObject" );
   const I_CHAR * const ERASEDATAOBJECTCONTAINERS  = I_( "eraseDataObjectContainers" );
   const I_CHAR * const ERASEOBJECTCONTAINER       = I_( "eraseObjectContainer" );
   const I_CHAR * const IDI_TAG                    = I_( "TAG" );
   const I_CHAR * const STUB_MODE                  = I_( "STUB_MODE" );
   const I_CHAR * const OFF                        = I_( "OFF" );
   const I_CHAR * const OFFLINE                    = I_( "OFFLINE" );
   const I_CHAR * const COLLECT                    = I_( "COLLECT" );
   BFAbstractCBO* NULL_POINTER = NULL;

}

namespace CND
{  // Conditions used
   extern const I_CHAR* BFBASE_CONDITION;

   extern const long ERR_FIELD_REQUIRED;
   extern const long ERR_FIELD_REQUIRED_GUI;
   extern const long ERR_OBJ_REQUIRED;
   extern const long ERR_OBJ_REQUIRED_IN_LIST;
   extern const long ERR_FIELD_VALUE_NOT_VALID_GUI;
   extern const long ERR_FIELD_VALUE_NOT_VALID;
}


BFCBO::BFPropertyRepository          BFCBO::m_bfProprRepository;

bool BFCBO::s_bAllowThreads = true;


void BFCBO::allowThreads( bool bAllow )
{
   s_bAllowThreads = bAllow;
}

bool BFCBO::areThreadsAllowed()
{
   return( s_bAllowThreads );
}

class BFCBO::FieldInfo
{
private:
   BFDataGroupId     idDataGroup_;       // Data group (typically a business process/dialog) that set/owns the value 
   long              flagsState_;       // Bit flags that represent current state (FIELD_FLAGS)
   long              flagsGroup_;       // Group bit flags
   DString*          pStrValue_;          // Field value
   BFProperties*     pFieldProperties_;   // Field properties
   CONDITIONVECTOR*  pvConditions_;
   BFObservable*     pBFObservable_;
   bool              bOwnFieldProperties_;
   bool              bOwnBFObservable_;
public:
   BFCBO::FieldInfo(const BFDataGroupId& idDataGroup = BF::HOST, long stateFlags = 0, long groupFlags = 0 ) 
   : idDataGroup_( idDataGroup )
   , flagsState_(stateFlags)
   , flagsGroup_(groupFlags)
   , pStrValue_(NULL)
   , pFieldProperties_( NULL )
   , pvConditions_( NULL )
   , pBFObservable_(NULL)
   , bOwnFieldProperties_(false)
   , bOwnBFObservable_( false )
   {}

   BFCBO::FieldInfo( const FieldInfo& rhs );
   BFCBO::FieldInfo& operator=( const FieldInfo& rhs );

   const BFDataGroupId& getDataGroupId() const { return(idDataGroup_);}
   void setDataGroupId( const BFDataGroupId& idDataGroup ) { idDataGroup_ = idDataGroup;}

   DString* getStrValue() const { return(pStrValue_);}
   void resetStrValue() { delete pStrValue_; pStrValue_ = NULL;}
   void setStrValue( DString* pValue ) { assert( NULL != pStrValue_ ); *pStrValue_ = *pValue;}
   void setStrValue( const I_CHAR* pszValue ) { assert( NULL != pStrValue_ ); *pStrValue_ = pszValue;}

   void setValue(const DString* value)
   {
      if( value == NULL )
      {
         if( pStrValue_ != NULL )
            *pStrValue_ = NULL_STRING;
      }
      else
      {
         if( pStrValue_ == NULL )
            pStrValue_ = new DString(*value);
         else
            *pStrValue_ = *value;
      }

   }
   bool checkStateFlag( long f ) const { return( ( flagsState_ & f ) != 0 );}
   void setStateFlag( long nValue ) { flagsState_ |= nValue;};
   void clearStateFlag( long nValue ) { flagsState_ &= ~nValue;};

   long getGroupFlags() const { return(flagsGroup_);}
   void setGroupFlags( long nValues ) { flagsGroup_ = nValues;};
   bool checkGroupFlag( long f ) const { return( ( flagsGroup_ & f ) != 0 );}

   BFObservable* getObservable() const { return(pBFObservable_);}
   void makeObservable() {
      if( NULL == pBFObservable_ )
      {
         pBFObservable_ = new BFObservable();
         bOwnBFObservable_ = true;
      }
   }
   void clearObservable() { 
      if( bOwnBFObservable_ )
      {
         delete pBFObservable_;
         pBFObservable_ = NULL;
      }
   }
   void takeObservable( FieldInfo* pLoser )
   {
      clearObservable();
      pBFObservable_ = pLoser->pBFObservable_;
      bOwnBFObservable_ = true;
      pLoser->bOwnBFObservable_ = false;
   }

   BFProperties* getFieldProperties() const { return(pFieldProperties_);}
   void clearFieldProperties()
   {
      // placeholder method
   }
   void takeFieldProperties( FieldInfo* pLoser )
   {
      clearFieldProperties();
      pFieldProperties_ = pLoser->pFieldProperties_;
      bOwnFieldProperties_ = true;
      pLoser->bOwnFieldProperties_ = false;
   }
   void initFieldProperties( const BFFieldId& idField )
   {
      // Add false == bOwnFieldProperties_ check so that if FieldInfo pointer does not
      // already own the FieldProperty, create a new one so that rollback will function properly
      // in the situation where the field properties have been changed.
      if( NULL == pFieldProperties_ || false == bOwnFieldProperties_ )
      {
         const BFDataFieldProperties* pProp = BFDataFieldProperties::get( idField );
         pFieldProperties_ = new BFProperties( pProp );
         bOwnFieldProperties_ = true;
      }
   }

   CONDITIONVECTOR* getConditionVector() const { return(pvConditions_);}
   // <KLUDGE>
   // Until we get a CONDITIONVECTOR which copies itself, etc, we must allow this
   // CP 20020114
   void setConditionVector( CONDITIONVECTOR* pvConditions ) { pvConditions_ = pvConditions;}
   // </KLUDGE>
   void addCondition( Condition* pCondition ) {
      if( NULL == pvConditions_ ) pvConditions_ = new CONDITIONVECTOR;
      pvConditions_->push_back( pCondition );
   }
   void clearConditionVector()
   {
      if( pvConditions_ != NULL )
      {
         CONDITIONVECTOR::iterator iter = pvConditions_->begin();
         while( iter != pvConditions_->end() )
         {
            delete *iter;
            iter = pvConditions_->erase(iter);
         }
         delete pvConditions_;
         pvConditions_ = NULL;
      }
   }

   void makeLike( FieldInfo* pFrom, const DString& strValue )
   {
      flagsGroup_ = pFrom->flagsGroup_;
      flagsState_ = pFrom->flagsState_;
      setValue( &strValue );
      pFieldProperties_ = pFrom->getFieldProperties();
      bOwnFieldProperties_ = false;
      pBFObservable_ = pFrom->getObservable();
      bOwnBFObservable_ = false;
   }

   void setTo( FieldInfo* pFrom )
   {
      if( pFrom->getStrValue() != NULL )
      {
         setValue( pFrom->getStrValue() );
      }

      if( pFrom->getObservable() != getObservable() )
      {
         takeObservable( pFrom );
      }

      if( pFrom->getFieldProperties() != getFieldProperties() )
      {
         takeFieldProperties( pFrom );
      }

      flagsGroup_ = pFrom->flagsGroup_;
      flagsState_ = pFrom->flagsState_;
      clearConditionVector();
   }


   ~FieldInfo()
   {
      delete pStrValue_;

      clearConditionVector();

      if( bOwnFieldProperties_ )
         delete pFieldProperties_;
      if( bOwnBFObservable_ )
         delete pBFObservable_;
   }
};

class BFCBO::GROUP_INFO                     // Host (committed) field info 
{
public:
   GROUP_INFO( const BFDataGroupId& idParentDataGroup, long lUpdateLevel )
   : idParentDataGroup_( idParentDataGroup )
   , updateLevel_( lUpdateLevel )
   , objLastValidationError_( NO_SEVERITY )
   , objChildrenLastValidationError_( NO_SEVERITY ) 
   , pvConditions_( NULL )
   {}; 
   ~GROUP_INFO()
   {
      clearConditions();
   }

   const BFDataGroupId& getParentDataGroupId() const { return(idParentDataGroup_);}


   SEVERITY getLastValidationError() const { return(objLastValidationError_);}
   void setLastValidationError( SEVERITY s ) { objLastValidationError_ = s;}

   SEVERITY getLastChildValidationError() const { return(objChildrenLastValidationError_);}
   void setLastChildValidationError( SEVERITY s ) { objChildrenLastValidationError_ = s;}

   const CONDITIONVECTOR* getConditions() const { return(pvConditions_);}
   CONDITIONVECTOR* getConditions() { return(pvConditions_);}

   void addCondition( Condition* pCondition )
   {
      if( NULL == pvConditions_ ) pvConditions_ = new CONDITIONVECTOR;
      pvConditions_->push_back( pCondition );
   }

   void clearConditions()
   {
      if( NULL != pvConditions_ )
      {
         CONDITIONVECTOR::iterator iter = pvConditions_->begin();
         while( iter != pvConditions_->end() )
         {
            delete *iter;
            iter = pvConditions_->erase( iter );
         }
         pvConditions_ = NULL;
      }
   }

private:
   const BFDataGroupId idParentDataGroup_;// Parent Metagroup Id 
   long updateLevel_;      // Update Level for this Metagroup
   SEVERITY objLastValidationError_;
   SEVERITY objChildrenLastValidationError_;
   CONDITIONVECTOR* pvConditions_;
};

/******************************************************************************
 * public methods
/******************************************************************************/

//******************************************************************************
BFProperties * BFCBO::BFPropertyRepository::get( const BFFieldId& idField, const BFFieldId& basedOnFieldId )
{
   BFGuard g( csPropertyMap_ );

   BF_PROPERTIES_MAP_ITER bfPropertiesMapIter = m_map.find( idField );
   BFProperties * pBFProperties = NULL;
   if( bfPropertiesMapIter != m_map.end( ) )
   {
      return( ( *bfPropertiesMapIter ).second );
   }
   else
   {
      const BFDataFieldProperties* pProp = BFDataFieldProperties::get( idField );
      pBFProperties = new BFProperties( pProp );
      m_map.insert( BF_PROPERTIES_MAP::value_type( idField, pBFProperties ));
      if( basedOnFieldId != ifds::NullFieldId )
      {
         BFProperties * pBasedOnProperties = get( basedOnFieldId );
         if( pBasedOnProperties )
            pBFProperties->initUnformattedSubstValues( *pBasedOnProperties->getAllSubstituteValues( ));
      }
   }

   return(pBFProperties);
}

//******************************************************************************
BFCBO::BFPropertyRepository::~BFPropertyRepository()
{
   clean();
}

//******************************************************************************
void BFCBO::BFPropertyRepository::clean()
{
   BFGuard g( csPropertyMap_ );

   BF_PROPERTIES_MAP_ITER iter = m_map.begin();
   while( iter != m_map.end() )
   {
      delete (*iter).second;
      ++iter;
   }
   m_map.clear();
}

void BFCBO::cleanBFPropertyRepository()
{
    m_bfProprRepository.clean();
};

//******************************************************************************
BFCBO::BFCBO( BFAbstractCBO* parent, VALIDATION_MODE validationMode )
: BFAbstractCBO( parent, validationMode )
, _iNextKey( 1 )
, _dataMapKey( 0 )
, _lBFStatus( 0 )
, _BFObservable( 0 )
, _objLastValidationError( NO_CONDITION )
, _objChildrenLastValidationError( NO_CONDITION )
, _moreRecordsAvailable( false )
, _asyncRequestor(NULL)
, _receivingData( true, true )
, _lastrequestCondition( NULL )
, _baseLock()
, _setCondition ( false )
, m_RequestSeverity(NO_CONDITION)
, bInDoPopulateField_( false )
, bVersionable_( true )
,_asyncRetrieveDone (false)
{
   TRACE_CONSTRUCTOR( CLASSNAME, I_( "( VALIDATION_MODE )" ));

   GROUP_INFO * grpinfo = new GROUP_INFO( BF::HOST,0 );
   _dataGroupMap.insert( METAGROUP_MAP::value_type( BF::HOST, grpinfo ));
}

//******************************************************************************
BFCBO::BFCBO( VALIDATION_MODE validationMode )
: BFAbstractCBO( NULL, validationMode )
, _iNextKey( 1 )
, _dataMapKey( 0 )
, _lBFStatus( 0 )
, _BFObservable( 0 )
, _objLastValidationError( NO_CONDITION )
, _objChildrenLastValidationError( NO_CONDITION )
, _moreRecordsAvailable( false )
, _asyncRequestor(NULL)
, _receivingData( true, true )
, _lastrequestCondition( NULL )
, _baseLock()
, _setCondition ( false )
, m_RequestSeverity(NO_CONDITION)
, bInDoPopulateField_( false )
, bVersionable_( true )
{
   TRACE_CONSTRUCTOR( CLASSNAME, I_( "( VALIDATION_MODE )" ));

   GROUP_INFO * grpinfo = new GROUP_INFO( BF::HOST,0 );
   _dataGroupMap.insert( METAGROUP_MAP::value_type( BF::HOST, grpinfo ));
}

//******************************************************************************
BFCBO::~BFCBO( )
{
   TRACE_DESTRUCTOR( CLASSNAME );
//   _receivingData.wait(INFINITE);
   FIELD_MAP_ITER  iter    = _fieldMap.begin( );
   FIELD_MAP_ITER  iterEnd = _fieldMap.end( );

   while( iter != iterEnd )
   {
      delete ( *iter ).second;
      ++iter;
   }

   if( _BFObservable )
   {
      notifyObservers( ifds::NullFieldId, BF::HOST, NON_FIELD_NOTIFICATIONS, E_EVENT_CBO_DESTROYED, I_( "" ));
      delete _BFObservable;
      _BFObservable = NULL;
   }

   METAGROUP_MAP_ITER it;
   for( it = _dataGroupMap.begin( ); it != _dataGroupMap.end( ); ++it )
      delete ( *it ).second;
   _dataGroupMap.clear( );

   m_crossEditGroupToFieldMap.clear( );
   m_crossEditFieldToGroupMap.clear( );

   delete _asyncRequestor;
   _asyncRequestor = NULL;
   delete _lastrequestCondition;
   _lastrequestCondition = NULL;
   eraseDataObjectContainers( );
   eraseObjectContainer( );
   eraseIteratorsVector( );
}

//******************************************************************************
SEVERITY BFCBO::clearField( const BFFieldId& idField, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::BFBASE_CONDITION,
                          CLASSNAME,
                          I_( "clearField( const BFFieldId &, const BFDataGroupId & )" ) );
   FieldInfo * pFieldInfo = prepareFieldInfoPointer( idField, isVersionable() ? idDataGroup : BF::HOST );

   if( pFieldInfo && pFieldInfo->getStrValue() && *( pFieldInfo->getStrValue() ) != NULL_STRING )
   {
      pFieldInfo->setStrValue( NULL_STRING );
      pFieldInfo->setStateFlag( UPDATED );
      if( getFieldProperties( idField, isVersionable() ? idDataGroup : BF::HOST )->isRequired( ) )
         pFieldInfo->clearStateFlag( VALID );
      else
         pFieldInfo->setStateFlag( VALID );
   }
   return(GETCURRENTHIGHESTSEVERITY( ));
}

//******************************************************************************
void BFCBO::clearUpdatedFlags( const BFDataGroupId& idDataGroup, bool inclSubObj /*= false*/ )
{
   FIELD_MAP_ITER fIter = _fieldMap.begin( );
   FIELD_MAP_ITER fIterEnd = _fieldMap.end( );

   //clear the fields update flag
   while( fIter != fIterEnd )
   {
      FieldInfo* pFI = ( *fIter ).second;
      if( NULL != pFI &&
          pFI->getDataGroupId() == idDataGroup &&
          pFI->checkStateFlag( UPDATED ) )
      {
         pFI->clearStateFlag( UPDATED );
      }
      ++fIter;
   }
   //clear the objects update flag
   if( inclSubObj )
   {
      BFAbstractCBO::OBJECT_MAP_ITER oIter = _objectMap.begin( );
      BFAbstractCBO::OBJECT_MAP_ITER oIterEnd = _objectMap.end( );

      while( oIter != oIterEnd )
      {
         if( ( *oIter ).second &&
             ( *oIter ).second->getInstance() )
         {
            //enter recursion
            ( *oIter ).second->getInstance()->clearUpdatedFlags( idDataGroup, inclSubObj );
         }
         ++oIter;
      }
   }
}

//******************************************************************************
SEVERITY BFCBO::commitAndValidateDataGroup( const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::BFBASE_CONDITION,
                          CLASSNAME,
                          I_( "commitAndValidateDataGroup( const BFDataGroupId & )" ) );

   deleteNonUpdatedAddedElements( idDataGroup );

   if( validateAll( idDataGroup ) > WARNING )
      return(GETCURRENTHIGHESTSEVERITY( ));

   commitDataGroup( idDataGroup );

   return(GETCURRENTHIGHESTSEVERITY( ));
}

//******************************************************************************
SEVERITY BFCBO::commitDataGroup( const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::BFBASE_CONDITION,
                          CLASSNAME,
                          I_( "commitDataGroup( const BFDataGroupId & )" ) );

   // 0 = HOST - not valid, it is the committed data group
   assert( idDataGroup != BF::HOST );

   deleteNonUpdatedAddedElements( idDataGroup, false );

   doCommitDataGroup( idDataGroup );

   //TODO - add in Metagroup logic

   METAGROUP_MAP_ITER groupIter;

   findDataGroup( groupIter, idDataGroup );

   BFDataGroupId idParentGroup = ( *groupIter ).second->getParentDataGroupId();


   for( groupIter = _dataGroupMap.begin( ); groupIter != _dataGroupMap.end( ); groupIter++ )
   {
      if( ( *groupIter ).second->getParentDataGroupId() == idDataGroup )
      {
         eraseDataGroupFields(( *groupIter ).first );
      }
   }

   eraseOrphanGroups( );



   FIELD_MAP_ITER  fieldIter      = _fieldMap.lower_bound( BFFieldKey( idDataGroup, ifds::NullFieldId ));
   FIELD_MAP_ITER  fieldIterEnd   = _fieldMap.upper_bound( BFFieldKey( idDataGroup, ifds::MaxFieldId ));

   FIELD_MAP_ITER  iter;


   while( fieldIter != fieldIterEnd )
   {
      FieldInfo* pFrom = ( *fieldIter ).second;
      if( pFrom->getDataGroupId() == idDataGroup )
      {
         iter = _fieldMap.find( BFFieldKey( idParentGroup, ( *fieldIter ).first.getFieldId() ) );

         //ensure that the field id is valid
         if( iter == _fieldMap.end( ) )
         {
            pFrom->setDataGroupId( idParentGroup );
            _fieldMap.insert( FIELD_MAP::value_type( BFFieldKey( idParentGroup, ( *fieldIter ).first.getFieldId() ), pFrom ) );
         }
         else
         {
            FieldInfo* pTo = ( *iter ).second;
            pTo->setTo( pFrom );

            delete pFrom;
         }

         //TODO - determine state flag update criteria
         //increment before erasing
         fieldIter = _fieldMap.erase( fieldIter  );
      }
      else
      {
         assert( 0 );
         ++fieldIter;
      }
   }

   findDataGroup( groupIter, idDataGroup );

   if( groupIter  != _dataGroupMap.end( ) )
   {
      delete ( *groupIter ).second;
      _dataGroupMap.erase( groupIter );
   }

   findDataGroup( groupIter, idParentGroup );


   BFAbstractCBO::OBJECT_MAP_ITER objIter = _objectMap.begin( );
   BFAbstractCBO::OBJECT_MAP_ITER hstObjIter;

   bool haveObjMapChanges = false;

   while( objIter != _objectMap.end( ) )
   {
      const BFObjectKey& rObjKey = (*objIter).first;
      BFAbstractCBO::OBJECT_INFO* pObjInfo = (*objIter).second;

      if( pObjInfo->getInstance() != NULL )
         pObjInfo->getInstance()->commitDataGroup( idDataGroup );

      if( rObjKey.getDataGroupId() == idDataGroup )
      {
         hstObjIter = _objectMap.begin( );
         bool bObjectDeleted = false;

         const DString * pKey = NULL;
         DString toUpdStrKey = I_( "" );

         if( pObjInfo->getInstance() )
            pKey  = pObjInfo->getInstance()->getInitialStrKey( );

         if( pKey != NULL )
            toUpdStrKey = *pKey;

         while( hstObjIter != _objectMap.end( ) )
         {
            const BFObjectKey& rHstObjKey = (*hstObjIter).first;
            BFAbstractCBO::OBJECT_INFO* pHstObjInfo = (*hstObjIter).second;

            if( rHstObjKey.getDataGroupId() == idParentGroup &&
                rHstObjKey.getType() == rObjKey.getType() )
            {
               if( rHstObjKey.getActivity() == OBJ_ACTIVITY_ADDED &&
                   rObjKey.getActivity() == OBJ_ACTIVITY_DELETED &&
                   pHstObjInfo->ownsInstance() &&
                   rHstObjKey.getStringKey() == rObjKey.getStringKey() )
               {
                  BFAbstractCBO* pObjInst = pObjInfo->getInstance();
                  
                  delete pObjInst;
				  delete pObjInfo;
//Back-out fix for 562038 - BPServer memory leaks (see below commented out line)
//Crash occurs when a record is deleted and re-added on modal processes, which update
//lists created by the modeless parents (that belong to them). The idea should be that 
//modal processes (dialogs) should edit their own CBO's. For that when querying for a 
//list instead of using getObject Desktop/BPServer should be using 
//::findObject (const BFObjectKey & objKey, bool lookIntoParents) - 
//passing 'false' for the last param which is 'true' by default

//				  delete pHstObjInfo->getInstance();
				  delete pHstObjInfo;
                  _objectMap.erase( hstObjIter );
                  bObjectDeleted = true;
                  break;
               }
               else
               {
                  BFAbstractCBO* pHstInst = pHstObjInfo->getInstance();
                  const DString* hstInitStrKey = pHstInst ? pHstInst->getInitialStrKey( ) : NULL;

                  if( toUpdStrKey == NULL_STRING && (rHstObjKey.getStringKey() == rObjKey.getStringKey() )  ||
                      toUpdStrKey != NULL_STRING && pHstInst && hstInitStrKey && *hstInitStrKey == toUpdStrKey )
                  {
                     if( !pObjInfo->getInstance() )
                        pObjInfo->setInstance( pHstInst );

                     if( pHstObjInfo->ownsInstance() )
                     {
                        pObjInfo->setOwnInstance( true ); //taking the ownership

                        if( pHstInst && pHstInst != pObjInfo->getInstance() )
                           delete pHstInst;
                     }

                     delete pHstObjInfo;
                     _objectMap.erase( hstObjIter );
                     break;
                  }
               }
            }
            ++hstObjIter;
         }

         if( !bObjectDeleted )
         {
            if( toUpdStrKey == NULL_STRING )
               toUpdStrKey = rObjKey.getStringKey();

            BFObjectKey lObjKey( toUpdStrKey,
                                 idParentGroup,
                                 rObjKey.getActivity(),
                                 rObjKey.getType() );
            if( lObjKey.getActivity() ==  OBJ_ACTIVITY_ADDED || lObjKey.getActivity() ==  OBJ_ACTIVITY_DELETED )
               notifyObservers( ifds::NullFieldId, idParentGroup, NON_FIELD_NOTIFICATIONS, E_EVENT_CBO_OBJITER_UPDATE, I_( "" ));

            _objectMap.insert( BFAbstractCBO::OBJECT_MAP::value_type( lObjKey, pObjInfo ));
         }
         objIter = _objectMap.erase( objIter );

         haveObjMapChanges = true;
      }
      else
         ++objIter ;
   }

   if( haveObjMapChanges )
      notifyObservers( ifds::NullFieldId, idParentGroup, NON_FIELD_NOTIFICATIONS, E_EVENT_CBO_OBJITER_UPDATE, I_( "" ));
   return(GETCURRENTHIGHESTSEVERITY( ));
}

//******************************************************************************
SEVERITY BFCBO::deleteNonUpdatedAddedElements( const BFDataGroupId& idDataGroup, bool inclSubObj )
{
   BFAbstractCBO::OBJECT_MAP_ITER objIter = _objectMap.begin( );

   bool hasChanges = false;
   while( objIter != _objectMap.end( ) )
   {
      BFAbstractCBO::OBJECT_INFO* pObjInfo = (*objIter).second;
      if( pObjInfo->getInstance() )
      {
         if( isDummy( objIter ) && ( *objIter ).first.getDataGroupId() == idDataGroup )
         {
            if( pObjInfo->ownsInstance() )
            {
               delete pObjInfo->getInstance();
               hasChanges = true;
            }
			delete pObjInfo;
            objIter = _objectMap.erase( objIter );
            continue;
         }
         if( inclSubObj )
            pObjInfo->getInstance()->deleteNonUpdatedAddedElements( idDataGroup );
      }
      ++objIter;
   }
   if( hasChanges )
      notifyObservers( ifds::NullFieldId, idDataGroup, NON_FIELD_NOTIFICATIONS, E_EVENT_CBO_OBJITER_UPDATE, I_( "" ));

   return(NO_CONDITION);       // should be changed to void!
}

//******************************************************************************
SEVERITY BFCBO::deleteObject( const DString& strKey, const BFDataGroupId& idDataGroup, bool bRemoveFromMap /*=false*/, bool bForce /*=false*/ )  
{
   MAKEFRAMEAUTOPROMOTE2( CND::BFBASE_CONDITION,
                          CLASSNAME,
                          I_( "deleteObject( const DString &, const BFDataGroupId &, bool, bool )" ) );

   BFObjIter bfIter( *this, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED );
   bfIter.positionByKey( strKey );
   if( !bfIter.end( ) )
   {
      BFAbstractCBO::OBJECT_MAP_ITER objIter = _objectMap.find( bfIter.getKey( ));
      deleteObject( objIter, idDataGroup, bRemoveFromMap, bForce );
   }
   else
      assert( 0 ); //non existing object

   return(GETCURRENTHIGHESTSEVERITY( ));
}

//******************************************************************************
bool BFCBO::existsFieldInfo( const BFFieldId& idField )
{
   FIELD_MAP_ITER  _fieldIter = _fieldMap.find( BFFieldKey( BF::HOST, idField ));
   if( _fieldIter != _fieldMap.end( ) )
      return(true);
   else
      return(false);

}

//******************************************************************************
SEVERITY BFCBO::getAllErrors( const BFDataGroupId& idDataGroup, CONDITIONVECTOR & cndVec, bool bRecurse /* = false */ ) const
{
   CONDITIONVECTOR * cndVec1 = NULL;
   SEVERITY sevRtn    = NO_CONDITION;
   SEVERITY maxSevRtn = NO_CONDITION;

   sevRtn = const_cast< BFCBO* >(this)->getErrorState( idDataGroup );
   maxSevRtn = sevRtn;

   if( sevRtn > NO_CONDITION )
   {
      cndVec1 = const_cast< BFCBO* >(this)->getErrors( idDataGroup );
      if( cndVec1 != NULL )
      {
         CONDITIONVECTOR::iterator cndVecIter = cndVec1->begin( );
         while( cndVecIter != cndVec1->end( ) )
         {
            cndVec.push_back( *cndVecIter );
            ++cndVecIter;
         }
      }
   }

   FIELD_MAP_CONST_ITER  _fieldIter      = _fieldMap.lower_bound( BFFieldKey( idDataGroup, ifds::NullFieldId ));
   FIELD_MAP_CONST_ITER  _fieldIterEnd   = _fieldMap.upper_bound( BFFieldKey( idDataGroup, ifds::MaxFieldId ));

   while( _fieldIter != _fieldIterEnd )
   {
      sevRtn = getErrors(( *_fieldIter ).first.getFieldId(), idDataGroup, cndVec );
      maxSevRtn = maxSevRtn > sevRtn ? maxSevRtn : sevRtn ;
      ++_fieldIter;
   }

   // walk the contained objects if recursion is requested
   if( true == bRecurse )
   {
      BFObjIter bfIter( *(const_cast< BFCBO* >(this)), idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED );
      while( !bfIter.end( ) )
      {
         BFAbstractCBO* pObj = bfIter.getObject( );
         if( pObj )
         {
            sevRtn = pObj->getAllErrors( idDataGroup, cndVec, bRecurse );
            maxSevRtn = maxSevRtn >= sevRtn ? maxSevRtn : sevRtn;
         }
         ++bfIter;
      }
   }

   return(maxSevRtn);
}

//******************************************************************************
void BFCBO::getCrossEditFields( const BFFieldId& idField, std::vector<BFFieldId> & lFieldIdVector )
{
   CROSS_EDIT_MAP_ITER iter = m_crossEditGroupToFieldMap.find( idField );
   while( iter != m_crossEditGroupToFieldMap.end( ) && ( *iter ).first == idField )
   {
      lFieldIdVector.push_back(( *iter ).second );
      ++iter;
   }

}

//******************************************************************************
SEVERITY BFCBO::getData(  BFData& data,
                          const BFDataGroupId& idDataGroup,
                          bool fAppendNewTags,
                          bool fUseDataObjectOnly )
{
   MAKEFRAMEAUTOPROMOTE2( CND::BFBASE_CONDITION,
                          CLASSNAME,
                          I_( "getData( BFData &, const BFDataGroupId &, bool, bool )" ) );
   BFDataFieldIter dIter( data );
   DString fieldValue;

   for( ;dIter; ++dIter )
   {
      const BFDataField& df = dIter();
      getField( df.getId(), fieldValue, idDataGroup );
      if( fieldValue != NULL_STRING || fieldExists( df.getId() ) )
         data.setElementValue( df.getId(), fieldValue, fAppendNewTags, false );
   }
   return(GETCURRENTHIGHESTSEVERITY( ));
}

//******************************************************************************
CONDITIONVECTOR * BFCBO::getErrors( const BFDataGroupId& idDataGroup ) const
{
   CONDITIONVECTOR * cndVec = NULL;

   METAGROUP_MAP_ITER  groupIter;
   const_cast< BFCBO* >(this)->findDataGroup( groupIter, idDataGroup );
   if( groupIter != _dataGroupMap.end( ) )
   {
      GROUP_INFO* grpInfo = ( *groupIter ).second;
      cndVec = grpInfo->getConditions();
   }
   return(cndVec);
}

//******************************************************************************
SEVERITY BFCBO::getErrors( const BFFieldId& idField, const BFDataGroupId& idDataGroup, CONDITIONVECTOR & cndVec ) const
{
   CONDITIONVECTOR * cndVec1 = NULL;
   SEVERITY sevRtn = NO_CONDITION;
   SEVERITY maxSevRtn = NO_CONDITION;

   FIELD_MAP_CONST_ITER  fieldIter;
   fieldIter = _fieldMap.find( BFFieldKey( idDataGroup, idField ));
   if( fieldIter != _fieldMap.end( ) )
   {
      FieldInfo * pFieldInfo = ( *fieldIter ).second;
      if( pFieldInfo->getConditionVector() != NULL )
      {
         CONDITIONVECTOR::iterator iter = pFieldInfo->getConditionVector()->begin( );
         for( ; iter != pFieldInfo->getConditionVector()->end( ); ++iter )
         {
            Condition* pCondition = (*iter);
            sevRtn = pCondition->getSeverity();
            maxSevRtn = maxSevRtn > sevRtn ? maxSevRtn : sevRtn;
            cndVec.push_back( pCondition );
         }
      }
   }

   std::pair<CROSS_EDIT_MAP_CONST_ITER, CROSS_EDIT_MAP_CONST_ITER> crossMapPair;
   crossMapPair = m_crossEditFieldToGroupMap.equal_range( idField );

   CROSS_EDIT_MAP_CONST_ITER ceIterBegin  = crossMapPair.first;
   while( ceIterBegin != crossMapPair.second )
   {
      sevRtn = getErrors(( *ceIterBegin ).second, idDataGroup, cndVec );
      maxSevRtn = maxSevRtn > sevRtn ? maxSevRtn : sevRtn;
      ++ceIterBegin;
   }
   return(maxSevRtn);
}

//******************************************************************************
SEVERITY BFCBO::getErrorState( const BFFieldId& idField, const BFDataGroupId& idDataGroup ) const
{
   SEVERITY sevRtn = NO_CONDITION;
   SEVERITY maxSevRtn = NO_CONDITION;

   FIELD_MAP_CONST_ITER  fieldIter;
   fieldIter = _fieldMap.find( BFFieldKey( idDataGroup, idField ));
   if( fieldIter != _fieldMap.end( ) )
   {
      FieldInfo *pFieldInfo = ( *fieldIter ).second;
      if( pFieldInfo->getConditionVector() != NULL )
      {
         CONDITIONVECTOR::iterator iter = pFieldInfo->getConditionVector()->begin( );
         while( iter != pFieldInfo->getConditionVector()->end( ) )
         {
            sevRtn = ( *iter )->getSeverity( );
            maxSevRtn = maxSevRtn > sevRtn ? maxSevRtn : sevRtn;
            ++iter;
         }
      }
   }
   std::pair<CROSS_EDIT_MAP_CONST_ITER, CROSS_EDIT_MAP_CONST_ITER> crossMapPair;
   crossMapPair = m_crossEditFieldToGroupMap.equal_range( idField );

   CROSS_EDIT_MAP_CONST_ITER ceIter  = crossMapPair.first;
   while( ceIter != crossMapPair.second )
   {
      sevRtn = getErrorState(( *ceIter ).second, idDataGroup );
      maxSevRtn = maxSevRtn > sevRtn ? maxSevRtn : sevRtn;
      ++ceIter;
   }

   return(maxSevRtn);
}

//******************************************************************************
SEVERITY BFCBO::getErrorState( const BFDataGroupId& idDataGroup ) const
{
   SEVERITY sevRtn    = NO_CONDITION;
   SEVERITY maxSevRtn = NO_CONDITION;

   METAGROUP_MAP_ITER  groupIter;

   const_cast< BFCBO* >(this)->findDataGroup( groupIter, idDataGroup );

   if( groupIter != _dataGroupMap.end( ) )
   {
      GROUP_INFO * grpInfo = ( *groupIter ).second;
      const CONDITIONVECTOR * cndVec = grpInfo->getConditions();
      if( cndVec != NULL )
      {
         CONDITIONVECTOR::const_iterator iter = cndVec->begin( );
         while( iter != cndVec->end( ) )
         {
            sevRtn = ( *iter )->getSeverity( );
            maxSevRtn = maxSevRtn > sevRtn ? maxSevRtn : sevRtn;
            ++iter;
         }
      }
   }
   return(maxSevRtn);
}

//******************************************************************************
void BFCBO::getField( const BFFieldId& idField,
                      DString& strValue,
                      const BFDataGroupId& idDataGroup,
                      bool formattedReturn ) const
{
   EXECHISTI( I_( "getField( const BFFieldId &, DString &, const BFDataGroupId &, bool )" ) );

   FIELD_MAP_ITER       _fieldIter;
   METAGROUP_MAP_ITER   groupIter;

   _receivingData.wait(INFINITE);
   BFCBOGuard g( _baseLock );

   if( _setCondition ) 
   {
      const_cast< BFCBO*>(this)->addBFCondition();
   }

   FieldInfo * pFieldInfo = getFieldInfoPointer( idField, isVersionable() ? idDataGroup : BF::HOST );

   if( pFieldInfo != NULL )
   {
      if( pFieldInfo->checkStateFlag( PRIVATE_USE ) )
      {
         strValue = NULL_STRING;
         return;
      }
      else if( pFieldInfo->getStrValue() != NULL )
      {
         strValue = *( pFieldInfo->getStrValue() );
         if( formattedReturn )
         {
            ( const_cast < BFCBO* >( this ))->formatField( idField, strValue, isVersionable() ? idDataGroup : BF::HOST );
         }
         strValue.stripTrailing( );
         return;
      }
   }

   strValue = NULL_STRING;

   if( isNew() )
      return;


   // we want to apply our custom formatting to the field, but getFieldBeforeImage uses the default formatting from 
   // the data dictionary.
   if( getFieldBeforeImage( idField, strValue, false ) )
   {
      strValue.stripTrailing( );
      if( formattedReturn )
      {
         formatField( idField, strValue, isVersionable() ? idDataGroup : BF::HOST );
      }
      // we strip trailing spaces after format Field again, since formatField pads in spaces.
      // This may be a temp fix.
      //strValue.stripTrailing( );
      return;
   }

   // <HACK>
   // This code is not thread safe!  However, the only time it is used (I think) is when the CBO is Global Side.  Hopefully it
   // won't get called concurrently :)  CP 21Nov2002 (at the request of PMI) 
   // 
   if( false == bInDoPopulateField_ )
   {
      bInDoPopulateField_ = true;
      (const_cast< BFCBO*>(this))->doPopulateField( idField, strValue, formattedReturn );
   }
   bInDoPopulateField_ = false;
   // </HACK>
}

//******************************************************************************
bool BFCBO::getFieldBeforeImage( const BFFieldId& idField, DString&  strValue, bool formattedReturn ) const
{
//   EXECHIST2( 
//      CLASSNAME,
//      I_( "getFieldBeforeImage( const BFFieldId &, DString &, bool )" ) );

   strValue = I_( "" );

   //traverse data vector until data.doesExist = true or end
   DATA_VECTOR_ITER  dataIter    = const_cast<BFCBO *>( this )->_vecData.begin( );
   DATA_VECTOR_ITER  dataIterEnd = const_cast<BFCBO *>( this )->_vecData.end( );

   while( dataIter != dataIterEnd )
   {
      if( ( *dataIter )->exists( idField ) )
      {
         unsigned long ulFlags = 0;
         if( formattedReturn )
         {
            ulFlags = BFDataField::USE_MASK | BFDataField::USE_SUBSTITUTES;
         }
         ( *dataIter )->getElementValue( idField, strValue, ulFlags );
         return(true);
      }
      ++dataIter;
   }

   return(false);
}

//******************************************************************************
BFProperties * BFCBO::getFieldProperties( const BFFieldId& idField, const BFDataGroupId& idDataGroup )
{
   FieldInfo * pFieldInfo = getFieldInfoPointer( idField, isVersionable() ? idDataGroup : BF::HOST, true );
   if( pFieldInfo && pFieldInfo->getFieldProperties() != NULL )
   {
      return( pFieldInfo->getFieldProperties() );
   }
   return( m_bfProprRepository.get( idField ) );
}

//******************************************************************************
void BFCBO::getKey( BFObjectKey &objKey, const BFData *data, bool newObject )
{
   TRACE_METHOD( CLASSNAME, I_( "getKey" ));

   DString dstrKey = objKey.getStringKey();
   if( newObject == true )
   {
      getStrKeyForNewItem( dstrKey );
   }
   else
   {
      getStrKey( dstrKey, data );
   }

   objKey.setStringKey( dstrKey );
}

//******************************************************************************
SEVERITY BFCBO::getMaxValidationSeverityForChildren( const BFDataGroupId& idDataGroup  ) const
{
   SEVERITY sevRtn = NO_SEVERITY;
   if( idDataGroup == BF::HOST )
      sevRtn = _objChildrenLastValidationError;
   else
   {
      METAGROUP_MAP_CONST_ITER groupIter = _dataGroupMap.find( idDataGroup );

      if( groupIter != _dataGroupMap.end( ) )
         sevRtn = ( *groupIter ).second->getLastChildValidationError();
   }
   return(sevRtn);
}

//******************************************************************************
SEVERITY BFCBO::getMaxValidationSeverityForObject( const BFDataGroupId& idDataGroup ) const
{
   SEVERITY sevRtn = NO_SEVERITY;
   if( idDataGroup == BF::HOST )
      sevRtn = _objLastValidationError;
   else
   {
      METAGROUP_MAP_CONST_ITER groupIter = _dataGroupMap.find( idDataGroup );

      if( groupIter != _dataGroupMap.end( ) )
         sevRtn = ( *groupIter ).second->getLastValidationError();
   }
   return(sevRtn);
}

//******************************************************************************
SEVERITY BFCBO::getMaxValidationSeverityForObjectAndChildren( const BFDataGroupId& idDataGroup )const
{
   SEVERITY sevRtnObj    = NO_SEVERITY;
   SEVERITY sevRtnChild  = NO_SEVERITY;
   if( idDataGroup == BF::HOST )
   {
      sevRtnObj     = _objLastValidationError;
      sevRtnChild   = _objChildrenLastValidationError;
   }
   else
   {
      METAGROUP_MAP_CONST_ITER groupIter = _dataGroupMap.find( idDataGroup );

      if( groupIter != _dataGroupMap.end( ) )
      {
         sevRtnObj     = ( *groupIter ).second->getLastValidationError();
         sevRtnChild   = ( *groupIter ).second->getLastChildValidationError();
      }
   }

   return(sevRtnChild > sevRtnObj ? sevRtnChild : sevRtnObj);
}

//******************************************************************************
BFCBO * BFCBO::getNewListItem( BFObjectKey &objKey )
{
   EXECHISTI( I_( "getNewListItem( BFObjectKey & )" ) );
   BFCBO * pObj;

   getKey( objKey, NULL, true );
   objKey.setActivity( OBJ_ACTIVITY_ADDED );
   DString dstrKey = objKey.getStringKey();
   doCreateNewObject( pObj, dstrKey, objKey.getDataGroupId() );
   objKey.setStringKey( dstrKey );
   pObj->setObjectNew( );
   setObject( objKey, pObj );
   pObj->initWithDefaultValues( objKey.getDataGroupId() );
   if( !pObj->getNonDummyFlag() )
      pObj->clearUpdatedFlags( objKey.getDataGroupId() );
   return(pObj);
}

//******************************************************************************
SEVERITY BFCBO::getNonFieldErrors( const BFDataGroupId& idDataGroup, 
                                   CONDITIONVECTOR &lCndVector, 
                                   long lValidateGroup, 
                                   bool inclSubObj )
{

   SEVERITY sevRtn = NO_CONDITION;
   SEVERITY maxSevRtn = NO_CONDITION;

   METAGROUP_MAP_ITER  groupIter;
   findDataGroup( groupIter, idDataGroup );
   if( groupIter != _dataGroupMap.end( ) )
   {
      const CONDITIONVECTOR * cndVec = ( *groupIter ).second->getConditions();
      if( cndVec != NULL )
      {
         CONDITIONVECTOR::const_iterator iter = cndVec->begin( );
         bool bAddCondition ;
         while( iter != cndVec->end( ) )
         {
            bAddCondition = true;
            sevRtn = ( *iter )->getSeverity( );
            //don't add the same condition twice ..
            int condCode = ( *iter )->getCode();
            CONDITIONVECTOR::iterator iter1 = lCndVector.begin( );
            while( iter1 != lCndVector.end( ) )
            {
               int existentCondCode = ( *iter1 )->getCode();
               if( existentCondCode == condCode )
               {
                  bAddCondition = false;
                  break;
               }
               ++iter1;
            }
            if( bAddCondition )
            {
               lCndVector.push_back( *iter );
               maxSevRtn = maxSevRtn >= sevRtn ? maxSevRtn : sevRtn;
            }
            ++iter;
         }
      }
   }
   BFObjIter bfIter( *this, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED );
   while( !bfIter.end( ) )
   {
      if( !lValidateGroup || bfIter.getGroupFlags( ) & lValidateGroup )
      {
         BFAbstractCBO* pObj = bfIter.getObject( );
         if( pObj )
         {
            sevRtn = pObj->getNonFieldErrors( idDataGroup, lCndVector, lValidateGroup, inclSubObj );
            maxSevRtn = maxSevRtn >= sevRtn ? maxSevRtn : sevRtn;
         }
      }
      ++bfIter;
   }
   return(maxSevRtn);
}

//******************************************************************************
bool BFCBO::getNotApplicable( const BFFieldId& idField, const BFDataGroupId& idDataGroup )
{
   EXECHISTI(I_( "getNotApplicable( const BFFieldId &, const BFDataGroupId & )" ) );
   bool retVal = false;
   FieldInfo * pFieldInfo = getFieldInfoPointer( idField, idDataGroup );
   if( pFieldInfo != NULL )
      retVal = pFieldInfo->checkStateFlag( PRIVATE_USE );

   return(retVal);
}

//******************************************************************************
BFAbstractCBO* BFCBO::getObject( const DString&   strKey,
                                 const BFDataGroupId& idDataGroup,
                                 BF_OBJ_TYPE      type,
                                 BF_OBJ_ACTIVITY  activity ) const
{
   EXECHISTI( I_( "getObject( const DString &, const BFDataGroupId &, BF_OBJ_TYPE, BF_OBJ_ACTIVITY )" ) );
   _receivingData.wait(INFINITE);
   BFCBOGuard g( _baseLock );

   if( _setCondition )
      addBFCondition();

   BFObjectKey objKey( strKey, isVersionable() ? idDataGroup : BF::HOST, activity, type );

   if( strKey != NULL_STRING )
   {
      return(findObject( objKey ));
   }
   else
   {
      return(NULL);
   }
}

//******************************************************************************
BFAbstractCBO* BFCBO::getObject( DString&        strKey,
                                 const BFDataGroupId& idDataGroup,
                                 BF_OBJ_TYPE     type,
                                 BF_OBJ_ACTIVITY activity ) const
{
   EXECHISTI( I_( "getObject( DString &, const BFDataGroupId &, BF_OBJ_TYPE, BF_OBJ_ACTIVITY )" ) );
   _receivingData.wait(INFINITE);
   BFCBOGuard g( _baseLock );

   if( _setCondition )
   {
      addBFCondition();
   }

   BFObjectKey objKey( strKey, isVersionable() ? idDataGroup : BF::HOST, activity, type );
   if( strKey != NULL_STRING )
   {
      return(findObject( objKey ));
   }
   else
   {
      BFCBO * pObject;
      // cast away the const-ness of this.  This is cheesy and will be fixed
      // in nextgen cbo - Chris Purdye 27Aug2002
      pObject = const_cast< BFCBO* >( this )->getNewListItem( objKey );
      strKey = objKey.getStringKey();
      return(pObject);
   }
}

//******************************************************************************
BFObservable * BFCBO::getObservable( const BFFieldId& idField, 
                                     const BFDataGroupId& idDataGroup,
                                     E_EVENT_GROUP eEventCateg, 
                                     E_EVENT eEventId ) const
{
//   EXECHIST2( 
//      CLASSNAME,
//      I_( "getObservable( const BFFieldId &, const BFDataGroupId &, E_EVENT_GROUP, E_EVENT )" ) );
   BFObservable * retPtr = NULL;

   if( eEventCateg == FIELD_NOTIFICATIONS )
   {
      FieldInfo * pFieldInfo = const_cast< BFCBO* >(this)->prepareFieldInfoPointer( idField, idDataGroup );

      if( pFieldInfo )
      {
         if( pFieldInfo->getObservable() == NULL )
         {
            pFieldInfo->makeObservable();
         }
         retPtr = pFieldInfo->getObservable();
      }

   }
   else
   {
      if( _BFObservable == NULL )
      {
         const_cast< BFCBO* >(this)->_BFObservable = new BFObservable( );
      }

      retPtr = _BFObservable;
   }

   return(retPtr);
}

//******************************************************************************
const BFDataGroupId& BFCBO::getParentDataGroup( const BFDataGroupId& idDataGroup )
{
//   EXECHIST2( 
//      CLASSNAME,
//      I_( "getParentDataGroup( const BFDataGroupId & )" ) );
   METAGROUP_MAP_ITER  groupIter;

   findDataGroup( groupIter, idDataGroup );

   if( groupIter == _dataGroupMap.end( ) ) {
      return( BF::NullDataGroupId );
   }
   else
   {
      return( *groupIter ).second->getParentDataGroupId();
   }
}

//******************************************************************************
const BFCBO * BFCBO::getParent( ) const
{
   EXECHISTI( I_( "getParent()" ) );
   const BFCBO *p = dynamic_cast< const BFCBO* >( BFAbstractCBO::getParent() );
   return(p);
}

//******************************************************************************
BFCBO * BFCBO::getParent( )
{
   EXECHISTI( I_( "getParent()" ) );
   BFCBO *p = dynamic_cast< BFCBO* >( BFAbstractCBO::getParent() );
   return(p);
}

//******************************************************************************
const BFAbstractCBO* BFCBO::getTopLevelAncestor( ) const
{
//   EXECHIST2( 
//      CLASSNAME,
//      I_( "getTopLevelAncestor(  )" ) );
   if( NULL == getParent() || getParent()->isSession() )
   {
      return(this);
   }

   return(getParent()->getTopLevelAncestor( ));
}

//******************************************************************************
BFAbstractCBO* BFCBO::getTopLevelAncestor( )
{
//   EXECHIST2( 
//      CLASSNAME,
//      I_( "getTopLevelAncestor(  )" ) );
   if( NULL == getParent() || getParent()->isSession() )
      return(this);

   return(getParent()->getTopLevelAncestor( ));
}

//******************************************************************************
bool BFCBO::isSession() const
{
   return(false);
}


//******************************************************************************
bool BFCBO::hasHostUpdates( bool inclSubObj ) const
{
   EXECHISTI( I_( "hasHostUpdates( bool )" ) );
   bool updated = false;

   //check the fields if are updated with a non HOST datagroup
   for( FIELD_MAP_CONST_ITER fieldIter = _fieldMap.begin( );
      fieldIter != _fieldMap.end( ); ++fieldIter )
   {
      const BFFieldKey& rKey = (*fieldIter).first;
      FieldInfo* pFI = (*fieldIter).second;
      if( ( pFI->checkStateFlag( UPDATED ) ) && 
          ( rKey.getDataGroupId() == BF::HOST ) )
      {
         updated = true;
         break;
      }
   }
   //if doesn't have nonHost updates
   //check for uncommitted deletes
   //adds should have updated fields in order to be non dummy

   BFAbstractCBO::OBJECT_MAP_CONST_ITER objIter;
   if( !updated )
   {
      for( objIter = _objectMap.begin( ); objIter != _objectMap.end( ); ++objIter )
      {
         const BFObjectKey& rObjKey = (*objIter).first;
         if( ( rObjKey.getActivity() == OBJ_ACTIVITY_DELETED || rObjKey.getActivity() == OBJ_ACTIVITY_ADDED ) &&
             ( rObjKey.getDataGroupId() == BF::HOST ) )
         {
            updated = true;
            break;
         }
      }
   }

   //if not already updated,
   //check the children objects if are updated
   if( !updated && inclSubObj )
   {
      for( objIter = _objectMap.begin( ); objIter != _objectMap.end( ); ++objIter )
      {
         const BFAbstractCBO::OBJECT_INFO* pObjInfo = (*objIter).second;
         if( pObjInfo->getInstance() && pObjInfo->getInstance()->hasHostUpdates( ) )
         {
            updated = true;
            break;
         }
      }
   }
   return(updated);
}

//******************************************************************************
bool BFCBO::hasNonDummyEntries( const BFDataGroupId& idDataGroup ) const
{
   EXECHISTI( I_( "hasNonDummyEntries( const BFDataGroupId & )" ) );
   bool retVal = false;
//to do change to BFObjIter
   if( !isList( ) )
   {
      retVal = true;
   }
   else
   {
      BFAbstractCBO::OBJECT_MAP_CONST_ITER objIter;
      for( objIter = _objectMap.begin( ); objIter != _objectMap.end( ); ++objIter )
      {
         const BFObjectKey& rKey = (*objIter).first;
         if( isContainedDataGroup(rKey.getDataGroupId(), idDataGroup ) && //idDataGroup should see the change
             rKey.getActivity() != OBJ_ACTIVITY_DELETED &&                  //should not be deleted
             !isDummy( objIter ) )                                                     //should not be dummy
         {
            retVal = true;
            break;
         }
      }
   }
   return(retVal);
}

//******************************************************************************
bool BFCBO::hasNonHostUpdates( ) const
{
   EXECHISTI( I_( "hasNonHostUpdates(  )" ) );
   bool updated = false;

   //check the fields if are updated with a non HOST datagroup
   for( FIELD_MAP_CONST_ITER fieldIter = _fieldMap.begin( );
      fieldIter != _fieldMap.end( ); ++fieldIter )
   {
      const BFFieldKey& rKey = (*fieldIter).first;
      FieldInfo* pFI = (*fieldIter).second;
      if( ( pFI->checkStateFlag( UPDATED ) ) && 
          ( rKey.getDataGroupId() != BF::HOST ) )
      {
         updated = true;
         break;
      }
   }
   //if doesn't have nonHost updates
   //check for uncommitted deletes
   //adds should have updated fields in order to be non dummy

   BFAbstractCBO::OBJECT_MAP_CONST_ITER objIter;
   if( !updated )
      for( objIter = _objectMap.begin( ); objIter != _objectMap.end( ); ++objIter )
      {
         const BFObjectKey& rKey = (*objIter).first;
         if( rKey.getActivity() == OBJ_ACTIVITY_DELETED && rKey.getDataGroupId() != BF::HOST )
         {
            updated = true;
            break;
         }
      }

   //if not already updated,
   //check the children objects if are updated
   if( !updated )
   {
      for( objIter = _objectMap.begin( ); objIter != _objectMap.end( ); ++objIter )
      {
         OBJECT_INFO* pOI = (*objIter).second;
         if( pOI->getInstance() && pOI->getInstance()->hasNonHostUpdates( ) )
         {
            updated = true;
            break;
         }
      }
   }
   return(updated);
}

//******************************************************************************
bool BFCBO::hasTransactionUpdates( bool inclSubObj ) const
{
   EXECHISTI( I_( "hasTransactionUpdates( bool )" ) );
   bool updated = false;

   //check the fields if are updated with a non HOST datagroup
   for( FIELD_MAP_CONST_ITER fieldIter = _fieldMap.begin( );
      fieldIter != _fieldMap.end( ); ++fieldIter )
   {
      const BFFieldKey& rKey = (*fieldIter).first;
      FieldInfo* pFI = (*fieldIter).second;
      if( pFI->checkStateFlag( UPDATED ) &&
          !( pFI->checkStateFlag( CALCULATED_FIELD ) ) &&
          rKey.getDataGroupId() == BF::HOST )
      {
         updated = true;
         break;
      }
   }

   //if doesn't have nonHost updates
   //check for uncommitted deletes
   //adds should have updated fields in order to be non dummy
   BFAbstractCBO::OBJECT_MAP_CONST_ITER objIter;
   if( !updated )
      for( objIter = _objectMap.begin( ); objIter != _objectMap.end( ); ++objIter )
      {
         const BFObjectKey& rKey = (*objIter).first;
         if( (rKey.getActivity() == OBJ_ACTIVITY_DELETED || rKey.getActivity() == OBJ_ACTIVITY_ADDED )
             && rKey.getDataGroupId() == BF::HOST )
         {
            updated = true;
            break;
         }
      }

   //if not already updated,
   //check the children objects if are updated
   if( !updated && inclSubObj )
   {
      for( objIter = _objectMap.begin( ); objIter != _objectMap.end( ); ++objIter )
      {
         OBJECT_INFO* pOI = (*objIter).second;
         if( pOI->getInstance() && pOI->getInstance()->hasTransactionUpdates( ) )
         {
            updated = true;
            break;
         }
      }
   }
   return(updated);
}

//******************************************************************************
bool BFCBO::hasUpdatedFields( const BFDataGroupId& idDataGroup ) const
{
   EXECHISTI( I_( "hasUpdatedFields( const BFDataGroupId & )" ) );
   bool retVal = false;

   for( FIELD_MAP_CONST_ITER fieldIter = _fieldMap.begin( ); fieldIter != _fieldMap.end( ); ++fieldIter )
   {
      FieldInfo* pFI = (*fieldIter).second;
      bool b1 = pFI->checkStateFlag( UPDATED );
      bool b2 = isContainedDataGroup( idDataGroup, (*fieldIter).first.getDataGroupId() );
      if( b1 && b2 )
      {
         retVal = true;
         break;
      }
   }
   return(retVal);
}

//******************************************************************************
void BFCBO::initWithDefaultValues( const BFDataGroupId& idDataGroup )
{
   EXECHISTI( I_( "initWithDefaultValues( const BFDataGroupId & )" ) );

   doInitWithDefaultValues( idDataGroup );

   FIELD_MAP_ITER iter = _fieldMap.begin( );
   FieldInfo * pFieldInfo;
   DString locale;
   while( iter != _fieldMap.end() && ( *iter ).first.getDataGroupId() == BF::HOST )
   {
      const BFFieldId& idField = ( *iter ).first.getFieldId();
      pFieldInfo = ( *iter ).second;
      if( pFieldInfo && ( !pFieldInfo->getStrValue() || *( pFieldInfo->getStrValue() ) == NULL_STRING ) )
      {
         const BFDataFieldProperties* pProp = BFDataFieldProperties::get( idField );
         DString lDefVal = pProp->getDefaultValue( ClientLocaleContext::get() );
         lDefVal.strip( );
         pFieldInfo->setValue( &lDefVal );
         if( pFieldInfo->checkStateFlag( REQUIRED ) && lDefVal == NULL_STRING )
            pFieldInfo->clearStateFlag( VALID );
         else
            pFieldInfo->setStateFlag( VALID );
      }
      pFieldInfo->clearStateFlag( UPDATED );
      ++iter;
   }
}

//******************************************************************************
bool BFCBO::isContainedDataGroup( const BFDataGroupId& idContainerDataGroup, const BFDataGroupId& idDataGroup ) const
{
   EXECHISTI( I_( "isContainedDataGroup( const BFDataGroupId &, const BFDataGroupId & )" ) );
   bool retVal = false;

   if( idContainerDataGroup == BF::HOST )                               // BF::HOST DataGroup contains of all groups
      retVal = true;
   else if( idContainerDataGroup == idDataGroup )                      // a DataGroup contains himself
      retVal = true;
   else
      retVal = isParentDataGroup( idContainerDataGroup, idDataGroup );  // a parent contains his soons

   return(retVal);
}

//******************************************************************************
bool BFCBO::isParentDataGroup( const BFDataGroupId& idParentDataGroup, const BFDataGroupId& idDataGroup ) const
{
   return( idParentDataGroup.isAncestorOf( idDataGroup ) );
}

//******************************************************************************
bool BFCBO::isUpdated( bool inclSubObj ) const
{
   EXECHISTI( I_( "isUpdated( bool )" ) );
   bool updated = false;

   BFAbstractCBO::OBJECT_MAP_CONST_ITER objIter;

   updated = hasUpdatedFields( BF::HOST );
   //if not already updated,
   //check the the object map for deletions, adds have to have updated fields in order to be non dummy

   if( !updated )
   {
      for( objIter = _objectMap.begin( ); objIter != _objectMap.end( ); ++objIter )
      {
         const BFObjectKey& rKey = (*objIter).first;
         if( rKey.getActivity() == OBJ_ACTIVITY_DELETED ||
             rKey.getActivity() == OBJ_ACTIVITY_ADDED   && !isDummy( objIter ) )
         {
            updated = true;
            break;
         }
      }

   }
   //if not already updated,
   //check the children objects if are updated

   if( !updated && inclSubObj )
   {
      for( objIter = _objectMap.begin( );
         objIter != _objectMap.end( ); ++objIter )
      {
         OBJECT_INFO* pOI = (*objIter).second;
         if( pOI->getInstance() && pOI->getInstance()->isUpdated( inclSubObj ) )
         {
            updated = true;
            break;
         }
      }
   }

   return(updated);
}

//******************************************************************************
bool BFCBO::isUpdatedForDataGroup( const BFDataGroupId& idDataGroup, bool inclSubObj ) const
{
   EXECHISTI( I_( "isUpdatedForDataGroup( const BFDataGroupId &, bool )" ) );
   bool retVal = false;

   retVal = hasUpdatedFields( idDataGroup ); //check the fields if are updated

   //if not already updated,
   //check we have some changes in objectMap ( adds/deletes ):
   BFAbstractCBO::OBJECT_MAP_CONST_ITER objIter;
   if( !retVal )
   {
      for( objIter = _objectMap.begin( ); objIter != _objectMap.end( ); ++objIter )
      {
         const BFObjectKey& rKey = (*objIter).first;
         if( isContainedDataGroup( idDataGroup, rKey.getDataGroupId() ) && //idDataGroup should see the change
             ( rKey.getActivity() == OBJ_ACTIVITY_DELETED ||
               rKey.getActivity() == OBJ_ACTIVITY_ADDED   && !isDummy( objIter )  ) )
         {
            retVal = true;
            break;
         }
      }
   }

   BFObjIter iter( *(const_cast< BFCBO* >(this)), idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED );
   if( !retVal && inclSubObj )
   {
      while( !iter.end( ) )
      {
         BFAbstractCBO* pCBO = iter.getObject();
         if( ( NULL != pCBO ) && pCBO->isUpdatedForDataGroup( idDataGroup, inclSubObj ) )
         {
            retVal = true;
            break;
         }
         ++iter;
      }
   }

   return(retVal);
}

//******************************************************************************
void BFCBO::notifyObservers( const BFFieldId& idField, const BFDataGroupId& idDataGroup, E_EVENT_GROUP eEventCateg, E_EVENT eEventId, const DString&  hint )
{
   EXECHISTI( I_( "notifyObservers( const BFFieldId &, const BFDataGroupId &, E_EVENT_GROUP, E_EVENT, const DString & )" ) );
   if( eEventCateg == FIELD_NOTIFICATIONS )
   {
      FieldInfo * pFieldInfo = getFieldInfoPointer( idField, idDataGroup, false );
      if( ( NULL != pFieldInfo ) && ( pFieldInfo->getObservable() != NULL ) )
         pFieldInfo->getObservable()->notifyObservers( eEventCateg, eEventId, hint );
   }
   else
   {
      if( _BFObservable != NULL )
         _BFObservable->notifyObservers( eEventCateg, eEventId, hint );
   }
}

//==========================================================================
//---------------------- i_ostream Manipulator Helpers ---------------------
//==========================================================================
static int _ios_userIndex = -1;   // index to ostream xalloc array

//******************************************************************************
// set the BFCBO specific i_ostream manipulator flags
static void _setf( i_ostream &_strm, long f )
{
   if( _ios_userIndex == -1 )
   {
      _ios_userIndex = _strm.xalloc();
   }
   if( _ios_userIndex >= 0 )
   {
      long &bfbase_flags = _strm.iword(_ios_userIndex);
      bfbase_flags |= f;
   }
   return;
}

//******************************************************************************
// unset the BFCBO specific i_ostream manipulator flags
static void _unsetf( i_ostream &_strm, long f )
{
   if( _ios_userIndex == -1 )
   {
      _ios_userIndex = _strm.xalloc();
   }
   if( _ios_userIndex == -1 )
   {
      _ios_userIndex = _strm.xalloc();
   }
   if( _ios_userIndex >= 0 )
   {
      long &bfbase_flags = _strm.iword(_ios_userIndex);
      bfbase_flags &= ~(f);
   }
   return;
}

//==========================================================================
//------------------------- i_ostream Manipulators -------------------------
//==========================================================================
// cause operator<<( i_ostream &, const BFCBO & ) to recurse
i_ostream& __cdecl recurse_objects( i_ostream &_strm ) {
   _setf(_strm, BFCBO::OStream_Flags::_recurse_objects);
   return(_strm);
}

//******************************************************************************
// stop operator<<( i_ostream &, const BFCBO & ) from recursing
i_ostream& __cdecl norecurse_objects( i_ostream &_strm ) {
   _unsetf(_strm, BFCBO::OStream_Flags::_recurse_objects);
   return(_strm);
}

//******************************************************************************
// cause operator<<( i_ostream &, const BFCBO & ) to write all fields
i_ostream& __cdecl allfields( i_ostream &_strm ) {
   _setf(_strm, BFCBO::OStream_Flags::_allfields);
   return(_strm);
}

//******************************************************************************
// stop operator<<( i_ostream &, const BFCBO & ) from writing all fields
i_ostream& __cdecl noallfields( i_ostream &_strm ) {
   _unsetf(_strm, BFCBO::OStream_Flags::_allfields);
   return(_strm);
}

//******************************************************************************
// cause operator<<( i_ostream &, const BFCBO & ) to write raw data
i_ostream& __cdecl rawdata( i_ostream &_strm ) {
   _setf(_strm, BFCBO::OStream_Flags::_rawdata);
   return(_strm);
}

//******************************************************************************
// stop operator<<( i_ostream &, const BFCBO & ) from writing raw data
i_ostream& __cdecl norawdata( i_ostream &_strm ) {
   _unsetf(_strm, BFCBO::OStream_Flags::_rawdata);
   return(_strm);
}

//******************************************************************************
// unset all BFCBO-specific manipulator flags
i_ostream& __cdecl resetbfbaseio( i_ostream &_strm )
{
   _unsetf( _strm, 0xffff );
   return(_strm);
}

//******************************************************************************
i_ostream &operator<< ( i_ostream &stream, const BFCBO &base )
{
   //stream out contents
   BFCBO::FIELD_MAP_CONST_ITER  iter    = base._fieldMap.begin( );
   BFCBO::FIELD_MAP_CONST_ITER  iterEnd = base._fieldMap.end( );

   try
   {
      const type_info &ti = typeid(base);
      DString dstrName;
      dstrName = ti.name();
      stream << I_( "Object " ) << &base << I_( " of type " ) << dstrName << std::endl;

   }
   catch( std::__non_rtti_object& )
   {
      stream << I_( "Object " ) << &base << I_( " is not compiled with RTTI" ) << std::endl;
   }
   catch( std::bad_typeid& )
   {
   }


   stream << I_( "Field Info..." ) << std::endl << std::endl;
   DString fieldLabel;
   while( iter != iterEnd )
   {
      stream << I_( "GroupId: " )
      << ( (*iter).first.getDataGroupId().getId() )
      << I_( " FieldId: " );

      const BFDataFieldProperties* pProps = BFDataFieldProperties::get( ( *iter ).first.getFieldId() );
      if( NULL != pProps || ( fieldLabel = pProps->getLabel( ClientLocaleContext::get() ) ) == I_( "" ) )
      {
         stream << ( *iter ).first.getFieldId().getId();
      }
      else
      {
         stream << fieldLabel;
      }

      BFCBO::FieldInfo* pFI = (*iter).second;
      //display flag values
      stream << I_( "  [" ) << ( pFI->checkStateFlag( BFCBO::VALID ) ? I_("V") : I_("-") );

      stream << I_( "  [" ) << ( pFI->checkStateFlag( BFCBO::UPDATED ) ? I_("u") : I_("-") );

      stream << I_( "  [" ) << ( pFI->checkStateFlag( BFCBO::READ_ONLY ) ? I_("r") : I_("-") );
      stream << I_( "]" );

      if( NULL != pFI->getStrValue() )
      {
         stream << I_( "  " ) << *pFI->getStrValue();
      }
      else
      {
         stream << I_( "  <NULL> " );
      }

      stream << std::endl;
      ++iter;
   }

   return(stream);
}

//******************************************************************************
DString BFCBO::serialize( const BFDataGroupId& idDataGroup, bool bIncludeType /* = false */ ) const
{
   DString strXML;
   BasicDocument d( strXML );
   serializeCBO( d, idDataGroup, bIncludeType );
   return(strXML);
}

//******************************************************************************
void BFCBO::serializeCBO( BasicDocument& doc, const BFDataGroupId& idDataGroup, bool bIncludeType ) const
{
   const type_info &ti = typeid( *this );
   DString dstrCBOName = ( DStringA )const_cast< char* >( ti.name());
   dstrCBOName = serializeCBOName( dstrCBOName );
   ElementWriter ew( doc, dstrCBOName );

   serializeFields( doc, idDataGroup, bIncludeType );

   BFConstObjIter iter( *this, idDataGroup, false, BFConstObjIter::ITERTYPE::NON_DELETED );
   for( ; !iter.end(); ++iter )
   {
      // write the fields to the XML.  What exactly does this mean, anyway?  
      // _fieldMap contains all fields which are defined in the the CLASS_FIELD_INFO for
      // the CBO.  Is this good enough?  No as we don't always define all fields in 
      // CLASS_FIELD_INFO.  So we need to go through the data objects for the field
      //
      // 
      const BFCBO* pObj = dynamic_cast< const BFCBO* >( iter.getObject() );
      assert( NULL != pObj );
      // need to check for GenericBFCBO? 
      pObj->serializeCBO( doc, idDataGroup, bIncludeType );
   }

}

//******************************************************************************
void BFCBO::serializeFields( BasicDocument& doc, const BFDataGroupId& idDataGroup, bool bIncludeType ) const
{
   FieldValuePairsMap mapFieldValues;
   getAllFields( mapFieldValues, idDataGroup );

   // mapFieldValues now contains valid name/value pairs for every field in the CBO
   FieldValuePairsMap::iterator it = mapFieldValues.begin();
   FieldValuePairsMap::iterator itEnd = mapFieldValues.end();
   for( ; it != itEnd; ++it )
   {
      serializeField( doc, (*it).first, (*it).second, bIncludeType );
   }
}

//******************************************************************************
DString BFCBO::serializeCBOName( const DString& dstrCBOName ) const
{
   return( right( dstrCBOName, dstrCBOName.size() - 6 ) );
}

//******************************************************************************
DString BFCBO::serializeFieldName( const DString& dstrFieldName ) const
{
   return( dstrFieldName );
}

//******************************************************************************
DString BFCBO::serializeFieldValue( const BFFieldId& idField, const DString& dstrValue ) const
{
   return( dstrValue );
}

//******************************************************************************
void BFCBO::getAllFields( FieldValuePairsMap& fvp, const BFDataGroupId& idDataGroup ) const
{
   const ClientLocale& cl = ClientLocaleContext::get();

   DATA_VECTOR::const_iterator itData = _vecData.begin( );
   DATA_VECTOR::const_iterator itDataEnd = _vecData.end( );
   for( ; itData != itDataEnd; ++itData )
   {
      const BFData& rData = *(*itData);
      BFConstDataFieldIter itField( rData, true );
      for( ; itField; ++itField )
      {
         const BFDataField& df = itField();
         const BFFieldId& id = df.getId();
         fvp[ id ] = df.get( true, cl, NULL );
      }
   }

   // now to get the FIELD_MAP values we have to resort to some trickery.  First off
   // we need to build a list of unique fieldids which are in the field map.  This is
   // readily available so we'll build it
   std::set< BFFieldId > setUniqueFields;
   FIELD_MAP::const_iterator itField = _fieldMap.begin();
   FIELD_MAP::const_iterator itFieldEnd = _fieldMap.end();
   for( ; itField != itFieldEnd; ++itField )
   {
      const BFFieldKey& rKey = (*itField).first;
      setUniqueFields.insert( rKey.getFieldId() );
   }

   DString dstrValue;
   std::set< BFFieldId >::iterator itUniqueField = setUniqueFields.begin();
   for( ; itUniqueField != setUniqueFields.end(); ++itUniqueField )
   {
      const BFFieldId& idUniqueField = *itUniqueField;
      // BFCBO can determine which is the appropriate value based on the datagroup
      getField( idUniqueField, dstrValue, idDataGroup, true );
      fvp[ idUniqueField ] = dstrValue;
   }
}

//******************************************************************************
void BFCBO::serializeField( BasicDocument& doc, const BFFieldId& idField, const DString& dstrValue, bool bIncludeType ) const
{
   if( bIncludeType ) 
   {
      ElementWriter::write( doc, 
                            serializeFieldName( idField.getName() ), 
                            BFCBOTypeAttribute( BFDataFieldProperties::get( idField ) ), 
                            serializeFieldValue( idField, dstrValue ) );
   }
   else
   {
      ElementWriter::write( doc, serializeFieldName( idField.getName() ), serializeFieldValue( idField, dstrValue ) );
   }
}

//******************************************************************************
SEVERITY BFCBO::ReceiveData( const BFRequest &request,
                             BFData &queryData,
                             long responseDataSetId,
                             BFRequestor &requestor,
                             bool bInsertLast )
{
   BFData *responseData = new BFData(responseDataSetId);

   SEVERITY severity = ReceiveData (request, queryData, *responseData, requestor, bInsertLast);
   if( severity > WARNING ) 
   {
      delete responseData;
   }

   return(severity);

}

static DString getClassName( const char* pszClassName ) 
{
   if( NULL == pszClassName ) {
	  return( DString( I_("NoClass") ) );
   } 
   else if( strlen( pszClassName ) > 6 ) {
	  if( 0 == strncmp( pszClassName, "class ", 6 ) ) {
        return( DString( DStringA( pszClassName + 6 ) ) );
	  }
   }
   return( DString( DStringA( pszClassName ) ) );
}


//******************************************************************************
SEVERITY BFCBO::ReceiveData( const BFRequest &request,
                             BFData &queryData,
                             BFData &receivedData,
                             BFRequestor &requestor,
                             bool bInsertLast )
{
   MAKEFRAMEAUTOPROMOTE2( CND::BFBASE_CONDITION,
                          CLASSNAME,
                          I_( "ReceiveData( const BFRequest &, BFData &, BFData &, BFRequestor &, bool )" ) );

   SEVERITY sevRtn = SEVERE_ERROR;
   bf::log::LogStream ls( bf::log::cbo );
   ls << bf::log::information;

   DString dstrClassName = getClassName(typeid(*this).name());
   BFHRTimer tTotal;
   sevRtn = BFDataBroker::getInstance( )->receive( request, queryData, receivedData, requestor, &_moreRecordsAvailable );
   BFHRTimer tCBO;

   if( sevRtn > m_RequestSeverity )
   {
      m_RequestSeverity = sevRtn;
   }

   if( sevRtn > WARNING )
   {
      return(sevRtn);
   }

   attachDataObject( receivedData, true, bInsertLast );
   createObjectForEachRepeat( receivedData );
   ls << I_("Object creation for ") << dstrClassName << I_(" took ") << tTotal.elapsed() << I_(" ms.");
   ls << I_("  [CBO creation took ") << tCBO.elapsed() << I_(" ms.]");
   ls << bf::log::endlf;

   return(GETCURRENTHIGHESTSEVERITY( ));
}

//******************************************************************************
void BFCBO::AsyncReceiveData( const BFRequest &request,
                              BFData &queryData,
                              long responseDataSetId,
                              BFRequestor &requestor,
                              int callBackOption)
{
   EXECHISTI( I_( "AsyncReceiveData( const BFRequest &, BFData &, long, BFRequestor &, int )" ) );
   BFData *responseData = new BFData(responseDataSetId);
   AsyncReceiveData (request, queryData, *responseData, requestor, callBackOption);
}

//******************************************************************************
void BFCBO::AsyncReceiveData( const BFRequest &request,
                              BFData &queryData,
                              BFData &receivedData,
                              BFRequestor &requestor,
                              int callBackOption)
{
   EXECHISTI( I_( "AsyncReceiveData( const BFRequest &, BFData &, BFData &, BFRequestor &, int )" ) );
//### for DEMO - begin
   I_CHAR *rpEnv = NULL;
   rpEnv = i_getenv( STUB_MODE );    // Can return NULL pointer if no variable
   if( rpEnv && i_strcmp( rpEnv, OFF ) )
   {  //COLLECT or OFFLINE
      ReceiveData( request,queryData, receivedData, requestor );
      _asyncRetrieveDone = true; //no asynch here - flag set to true since data is collected already.
      return;
   }
//### for DEMO - end

   if( areThreadsAllowed() )
   {
      delete _asyncRequestor;
      _asyncRequestor = NULL;

      // TODO: put event into un-signalled state
      _asyncRequestor = new AsyncRequestor(requestor, this, callBackOption);
      _receivingData.reset();
      BFDataBroker::getInstance( )->receive( request, queryData, receivedData, *_asyncRequestor, NULL );
   }
   else
   {
      ReceiveData( request, queryData, receivedData, requestor );
      return;
   }

}

//******************************************************************************
void BFCBO::notifyResponse( SEVERITY severity, 
                            const Condition *condition, 
                            BFData *receivedData, 
                            bool moreAvailable, 
                            int callBackOption)
{
   EXECHISTI( I_( "notifyResponse( SEVERITY, const Condition *, BFData *, bool, int )" ) );
   BFCBOGuard g( _baseLock );
   _receivingData.set();
   donotifyResponse( severity, condition, receivedData, moreAvailable, callBackOption);
   _asyncRetrieveDone = severity > WARNING || !moreAvailable;
}

//******************************************************************************

void BFCBO::donotifyResponse( SEVERITY severity, 
                              const Condition *condition, 
                              BFData *receivedData, 
                              bool moreAvailable, 
                              int callBackOption)
{
   EXECHISTI( I_( "donotifyResponse( SEVERITY, const Condition *, BFData *, bool, int )" ) );
   if( WARNING >= severity )
   {
      _moreRecordsAvailable = moreAvailable;
      attachDataObject( *receivedData, true, true );
      createObjectForEachRepeat( *receivedData );
   }
   else
   {
      delete receivedData;
      receivedData=NULL;
      // TODO: set last request condition state.
      if( _lastrequestCondition != NULL )
         delete _lastrequestCondition;

      _lastrequestCondition = new Condition (*condition);
      _setCondition = true;
   }
   if( severity > m_RequestSeverity )
      m_RequestSeverity   = severity;
   // TODO: put event into signalled state
}

//******************************************************************************
bool BFCBO::isAsyncRetrieveDone ()
{
   return _asyncRetrieveDone;
}

//******************************************************************************

bool BFCBO::dataReady ()
{
   _receivingData.wait(INFINITE);
   return(true);
}

//******************************************************************************
SEVERITY BFCBO::refresh( bool bNewObject )
{
   EXECHISTI( I_( "refresh( bool )" ) );
   if( needsRefresh( BF::HOST ) )
   {
      doPreClearFields( );
      clearFieldMap( );
      eraseDataObjectContainers( );
      reInit( );
   }

   BFAbstractCBO::OBJECT_MAP_ITER  objIter      = _objectMap.begin( );
   BFAbstractCBO::OBJECT_MAP_ITER  objIterEnd   = _objectMap.end( );

   while( objIter != objIterEnd )
   {
      if( ( *objIter ).second && ( *objIter ).second->getInstance() )
      {
         if( ( *objIter ).second->getInstance()->hasHostUpdates( ) )
         {
            if( ( *objIter ).second->ownsInstance() )
               delete ( *objIter ).second->getInstance();
            if( isList() )
            {
			   delete ( *objIter ).second;
               objIter = _objectMap.erase( objIter );
               continue;
            }
            else
               ( *objIter ).second->setInstance( NULL );
         }
      }
      ++objIter;
   }
   return(NO_SEVERITY);
}

//******************************************************************************
bool BFCBO::registerObserver( const BFFieldId& idField, 
                              const BFDataGroupId& idDataGroup, 
                              BFObserver * pObserver, 
                              E_EVENT_GROUP eEventCateg, 
                              E_EVENT eEventId ) const
{
   EXECHISTI( I_( "registerObserver( const BFFieldId &, const BFDataGroupId &, BFObserver *, E_EVENT_GROUP, E_EVENT )" ) );
   _receivingData.wait (INFINITE);
   BFCBOGuard g( _baseLock );
   if( _setCondition )
      const_cast< BFCBO* >(this)->addBFCondition();
   BFObservable * bfObservable = getObservable( idField, idDataGroup, eEventCateg, eEventId );
   if( pObserver != NULL && bfObservable )
   {
      pObserver->registerObserver( bfObservable->getId( ), eEventCateg, eEventId );
      return(true);
   }
   else
      return(false);
}

//******************************************************************************
SEVERITY BFCBO::reset( const BFDataGroupId& idDataGroup, bool inclSubObj )
{
   MAKEFRAMEAUTOPROMOTE2( CND::BFBASE_CONDITION,
                          CLASSNAME,
                          I_( "reset( const BFDataGroupId &, bool )" ) );

   // BF::HOST is not valid ... it is the committed data group
   assert( idDataGroup != BF::HOST );

   if( idDataGroup != BF::HOST)
   {
      eraseDataGroupFields( idDataGroup );
      eraseOrphanGroups( );
   }

   if( inclSubObj )
   {
      BFAbstractCBO::OBJECT_MAP_ITER iter = _objectMap.begin( );
      bool hasChanges = false;
      while( iter != _objectMap.end( ) )
      {
         const BFObjectKey& rKey = (*iter).first;
         OBJECT_INFO* pOI = (*iter).second;
         if( pOI->getInstance() != NULL )
         {
            pOI->getInstance()->reset( idDataGroup );
         }
         if( rKey.getDataGroupId() == idDataGroup )
         {
#ifdef CP1_TODO
            if( pOI->ownsInstance() )
            {
               delete pOI->getInstance();
            }
#endif
            delete pOI;
            iter = _objectMap.erase( iter );
            hasChanges = true;
         }
         else
            ++iter;
      }
      if( hasChanges ) 
      {
         notifyObservers( ifds::NullFieldId, idDataGroup, NON_FIELD_NOTIFICATIONS, E_EVENT_CBO_OBJITER_UPDATE, I_( "" ));
      }
   }

   doReset( idDataGroup );

   if( isNew() )
   {
      initWithDefaultValues( idDataGroup );
   }

   return(GETCURRENTHIGHESTSEVERITY( ));
}

//******************************************************************************
SEVERITY BFCBO::rollbackDataGroup( const BFDataGroupId& idDataGroup, bool inclSubObj )
{
   MAKEFRAMEAUTOPROMOTE2( CND::BFBASE_CONDITION,
                          CLASSNAME,
                          I_( "rollbackDataGroup( const BFDataGroupId &, bool )" ) );

   // BF::HOST is not valid ... it is the committed data group
   assert( idDataGroup != BF::HOST );

   if( idDataGroup != BF::HOST )
   {
      eraseDataGroupFields( idDataGroup );
      eraseOrphanGroups( );
   }

   if( inclSubObj )
   {
      BFAbstractCBO::OBJECT_MAP_ITER iter = _objectMap.begin( );
      bool hasChanges = false;
      while( iter != _objectMap.end( ) )
      {
         const BFObjectKey& rKey = (*iter).first;
         OBJECT_INFO* pOI = (*iter).second;
         if( pOI->getInstance() != NULL )
         {
            pOI->getInstance()->rollbackDataGroup( idDataGroup );
         }
         if( rKey.getDataGroupId() == idDataGroup )
         {
#ifdef CP1_TODO
            if( pOI->ownsInstance() )
            {
               delete pOI->getInstance();
            }
#endif
            delete pOI;
            iter = _objectMap.erase( iter );
            hasChanges = true;
         }
         else
         {
            ++iter;
         }
      }
      if( hasChanges )
      {
         notifyObservers( ifds::NullFieldId, idDataGroup, NON_FIELD_NOTIFICATIONS, E_EVENT_CBO_OBJITER_UPDATE, I_( "" ));
      }
   }

   return(GETCURRENTHIGHESTSEVERITY( ));
}

//******************************************************************************
void BFCBO::setAllFieldsValid( const BFDataGroupId& idDataGroup )
{
   EXECHISTI( I_( "setAllFieldsValid( const BFDataGroupId & )" ) );

   FIELD_MAP_ITER  iter      = _fieldMap.lower_bound( BFFieldKey( idDataGroup, ifds::NullFieldId ));
   FIELD_MAP_ITER  iterEnd   = _fieldMap.upper_bound( BFFieldKey( idDataGroup, ifds::MaxFieldId ));

   for( ; iter != iterEnd; ++iter )
   {
      ( *iter ).second->setStateFlag( VALID );
   }
}

//******************************************************************************
SEVERITY BFCBO::setData( const BFData &data, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::BFBASE_CONDITION,
                          CLASSNAME,
                          I_( "setData( const BFData &, const BFDataGroupId & )" ) );

   for( FIELD_MAP_ITER fIter = _fieldMap.begin( ); fIter != _fieldMap.end( ); fIter++ )
   {
      const BFFieldKey& rKey = (*fIter).first;
      const BFFieldId& idField = rKey.getFieldId();
      const BFDataGroupId& idFieldDataGroup = rKey.getDataGroupId();

      DString fieldValue;
      if( data.exists( idField ) && idFieldDataGroup == BF::HOST )
      {
         data.getElementValue( idField, fieldValue );
         setField( idField, fieldValue, idDataGroup, true );
      }
   }
   return(GETCURRENTHIGHESTSEVERITY( ));
}

//******************************************************************************
SEVERITY BFCBO::setDataNoValidate( const BFData &data, const BFDataGroupId& idDataGroup, bool bValid )
{
   MAKEFRAMEAUTOPROMOTE2( CND::BFBASE_CONDITION,
                          CLASSNAME,
                          I_( "setDataNoValidate( const BFData &, const BFDataGroupId &, bool )" ) );

   for( FIELD_MAP_ITER fIter = _fieldMap.begin( ); fIter != _fieldMap.end( ); fIter++ )
   {
      const BFFieldKey& rKey = (*fIter).first;
      const BFFieldId& idField = ( *fIter ).first.getFieldId();
      const BFDataGroupId& idFieldDataGroup = ( *fIter ).first.getDataGroupId();

      DString fieldValue;
      if( data.exists( idField ) && idDataGroup == idFieldDataGroup )
      {
         data.getElementValue( idField, fieldValue );
         setFieldNoValidate( idField, fieldValue, idDataGroup, true, bValid );
      }
   }
   return(GETCURRENTHIGHESTSEVERITY( ));
}

//******************************************************************************
SEVERITY BFCBO::setField( const BFFieldId& idField,
                          const DString& strValue,
                          const BFDataGroupId& idDataGroup,
                          bool  lFormatted,
                          bool  lSideEffect,
                          bool  bCheckCurrentValue)
{
   MAKEFRAMEAUTOPROMOTE2( CND::BFBASE_CONDITION,
                          CLASSNAME,
                          I_( "setField( const BFFieldId &, const DString &, const BFDataGroupId &, bool, bool, bool )" ) );
   SEVERITY  sevRtn;

   DString newValue = strValue;
   DString oldValue;

   doPreSetField( idField, newValue, isVersionable() ? idDataGroup : BF::HOST, lFormatted );


   if( bCheckCurrentValue ) {
      BFCBO::getField( idField, oldValue, isVersionable() ? idDataGroup : BF::HOST, false );
   }

   if( lFormatted )
   {
      unformatField( idField, newValue, isVersionable() ? idDataGroup : BF::HOST );
   }

   bool doingSetField = true;
   if( bCheckCurrentValue ) {
      doingSetField = oldValue != newValue;
   }

   if (doingSetField) //we want to do setFieldNoValidate only if it is changed ( we don't want to change flags )
   {
      FieldInfo * pFieldInfo = prepareFieldInfoPointer( idField, isVersionable() ? idDataGroup : BF::HOST );

      // Determine if the field which is being set is in the CLASSFIELDINFO struct for the
      // concrete BFCBO class.  If it is *NOT* in that struct then the set will have no effect.
      // Serban wants to know if he forgot to put a field in the CLASSFIELDINFO struct
      // Let's see if this works...  CP20040528
      assert( NULL != pFieldInfo );

      if (pFieldInfo != NULL)
      {
         if( !pFieldInfo->checkStateFlag( PRIVATE_USE ) )
         {
            pFieldInfo->setValue( &newValue );
            pFieldInfo->setStateFlag( UPDATED );
            pFieldInfo->clearStateFlag( VALID );
            if (pFieldInfo->checkStateFlag (APPEND_VALUE_TO_SUBST))
            {
               BFProperties * pBFProperties = prepareFieldProperties (idField, idDataGroup);
               
               if (pBFProperties)
               {
                  pBFProperties->appendValueToSubst (strValue);
               }
            }
            if (lSideEffect)
            {
               notifyObservers (idField, isVersionable() ? idDataGroup : BF::HOST, FIELD_NOTIFICATIONS, E_EVENT_VALUE_CHANGE, I_(""));
            }
         }
      }
      setCrossEditInvalid (idField, isVersionable() ? idDataGroup : BF::HOST);
   }


   if( BFAbstractCBO::IMMEDIATE == getObjectValidationMode() )
   {
      sevRtn = validateField( idField, newValue, isVersionable() ? idDataGroup : BF::HOST );
      if( sevRtn <= WARNING ) {
         processCrossEdits( idField, isVersionable() ? idDataGroup : BF::HOST );
      }

      if( doingSetField && sevRtn <= WARNING ) {
         doApplyRelatedChanges( idField, isVersionable() ? idDataGroup : BF::HOST );
      }
   }
   else
   {
      //TODO - deferred validation - set field state to invalid
   }

   return(GETCURRENTHIGHESTSEVERITY( ));
}

//******************************************************************************
void BFCBO::setFieldAllSubstituteValues( const BFFieldId& idField, const BFDataGroupId& idDataGroup, const DString& strValues )
{
   EXECHISTI( I_( "setFieldAllSubstituteValues( const BFFieldId &, const BFDataGroupId &, const DString & )" ) );
   prepareFieldProperties( idField, idDataGroup )->setAllSubstituteValues( strValues );
   notifyObservers( idField, idDataGroup, FIELD_NOTIFICATIONS, E_EVENT_PROPERTY_CHANGE, I_( "" ));
}
//******************************************************************************
void BFCBO::setFieldAllSubstituteValues( const BFFieldId& idField, const BFDataGroupId& idDataGroup, const BFFieldId& useFieldId )
{
   EXECHISTI( I_( "setFieldAllSubstituteValues( const BFFieldId &, const BFDataGroupId &, const BFFieldId & )" ) );
   BFProperties * pBFProperties = prepareFieldProperties( idField, idDataGroup );
   BFProperties * pUseBFProperties = getFieldProperties( useFieldId, idDataGroup );
   DString subst = NULL_STRING;
   if( pUseBFProperties )
   {
      pUseBFProperties->getAllSubstituteValues( subst );
   }

   if( pBFProperties && idField != useFieldId )
   {
      pBFProperties->setAllSubstituteValues( subst );
      notifyObservers( idField, idDataGroup, FIELD_NOTIFICATIONS, E_EVENT_PROPERTY_CHANGE, I_( "" ));
   }
}

//******************************************************************************
void BFCBO::setFieldReadOnly( const BFFieldId& idField, const BFDataGroupId& idDataGroup, bool readonly )
{
   prepareFieldProperties( idField, isVersionable() ? idDataGroup : BF::HOST )->setReadOnly( readonly );

   FieldInfo * pFieldInfo = prepareFieldInfoPointer( idField, isVersionable() ? idDataGroup : BF::HOST );
   if( pFieldInfo != NULL )
   {
      if( readonly )
      {
         pFieldInfo->setStateFlag( BFCBO::STATE_FLAGS::READ_ONLY ); 
      }
      else
      {
         pFieldInfo->clearStateFlag( BFCBO::STATE_FLAGS::READ_ONLY );
      }
   }

   notifyObservers( idField, isVersionable() ? idDataGroup : BF::HOST, FIELD_NOTIFICATIONS, E_EVENT_PROPERTY_CHANGE, I_( "" ));
}

//******************************************************************************
void BFCBO::setFieldRequired( const BFFieldId& idField, const BFDataGroupId& idDataGroup, bool required )
{
   prepareFieldProperties( idField, isVersionable() ? idDataGroup : BF::HOST )->setRequired( required );

   FieldInfo * pFieldInfo = prepareFieldInfoPointer( idField, isVersionable() ? idDataGroup : BF::HOST );
   if( pFieldInfo != NULL )
   {
      if( required )
      {
         pFieldInfo->setStateFlag( BFCBO::STATE_FLAGS::REQUIRED ); 
      }
      else
      {
         pFieldInfo->clearStateFlag( BFCBO::STATE_FLAGS::REQUIRED );
      }
   }
   notifyObservers( idField, isVersionable() ? idDataGroup : BF::HOST, FIELD_NOTIFICATIONS, E_EVENT_PROPERTY_CHANGE, I_( "" ));
}

//******************************************************************************
void BFCBO::setFieldUpdated( const BFFieldId& idField, const BFDataGroupId& idDataGroup, bool bUpdated )
{
   FieldInfo * pFieldInfo = prepareFieldInfoPointer( idField, isVersionable() ? idDataGroup : BF::HOST );
   if( pFieldInfo != NULL )
   {
      if( bUpdated )
      {
         pFieldInfo->setStateFlag( BFCBO::STATE_FLAGS::UPDATED ); 
      }
      else
      {
         pFieldInfo->clearStateFlag( BFCBO::STATE_FLAGS::UPDATED );
      }
   }
   notifyObservers( idField, isVersionable() ? idDataGroup : BF::HOST, FIELD_NOTIFICATIONS, E_EVENT_PROPERTY_CHANGE, I_( "" ));
}

//******************************************************************************
void BFCBO::setFieldValid( const BFFieldId& idField, const BFDataGroupId& idDataGroup, bool bValid )
{
   FieldInfo * pFieldInfo = prepareFieldInfoPointer( idField, isVersionable() ? idDataGroup : BF::HOST );
   if( pFieldInfo != NULL )
   {
      if( bValid )
      {
         pFieldInfo->setStateFlag( BFCBO::STATE_FLAGS::VALID ); 
      }
      else
      {
         pFieldInfo->clearStateFlag( BFCBO::STATE_FLAGS::VALID );
      }
   }
   notifyObservers( idField, isVersionable() ? idDataGroup : BF::HOST, FIELD_NOTIFICATIONS, E_EVENT_PROPERTY_CHANGE, I_( "" ));
}

//******************************************************************************
void BFCBO::setFieldSubstituteValues( const BFFieldId& idField, const BFDataGroupId& idDataGroup, const BFFieldId& useFieldId )
{
   BFProperties * pBFProperties, *pUseBFProperties;
   pBFProperties = prepareFieldProperties( idField, idDataGroup );


   pUseBFProperties = m_bfProprRepository.get( useFieldId, idField );

   pBFProperties->setSubstituteValues( pUseBFProperties->getAllSubstituteValues( ));
   notifyObservers( idField, idDataGroup, FIELD_NOTIFICATIONS, E_EVENT_PROPERTY_CHANGE, I_( "" ));
}

//******************************************************************************
void BFCBO::setGroup( const BFDataGroupId& idParentDataGroup, const BFDataGroupId& idDataGroup )
{
   METAGROUP_MAP_ITER  groupIter;

   assert( idParentDataGroup != idDataGroup );

   groupIter = _dataGroupMap.find( idDataGroup );

   if( groupIter == _dataGroupMap.end( ) )
   {
      GROUP_INFO * grpinfo = new GROUP_INFO( idParentDataGroup, 0 );
      _dataGroupMap.insert( METAGROUP_MAP::value_type( idDataGroup, grpinfo ));
   }
   else
      assert( 0 );
}

//******************************************************************************
bool BFCBO::setObject( const BFObjectKey& objKey, BFAbstractCBO* pObject, OBJ_DELETE eBaseDelete /* = DEFAULT */ )
{
   EXECHISTI( I_( "setObject( const BFObjectKey &, BFAbstractCBO *, OBJ_DELETE )" ) );
   BFAbstractCBO::OBJECT_MAP_ITER objIter = _objectMap.find( objKey );

   bool hasToNotify = false;

   BFObjIter bfIter( *this, BF::HOST );
   bfIter.positionByKey( objKey.getStringKey() );

   BFAbstractCBO::OBJECT_MAP_ITER objIterToCopyFlagsFrom;
   if( !bfIter.end( ) )
   {
      objIterToCopyFlagsFrom = _objectMap.find( bfIter.getKey( ));
   }

   if( objIter == _objectMap.end( ) ) //new addition to map?
   {
      BFAbstractCBO::OBJECT_INFO *pOI = new BFAbstractCBO::OBJECT_INFO;
      if( bfIter.end( ) )
      {
         long lStateFlags = pOI->getStateFlags();
         long lGroupFlags = pOI->getGroupFlags();
         setObjectFlags( objKey, lStateFlags, lGroupFlags );
         switch( eBaseDelete )
         {
            case NO_DELETE_ON_DTOR:
               lStateFlags |= NO_BASE_DELETE;
               break;
            case DELETE_ON_DTOR:
               lStateFlags &= ~NO_BASE_DELETE;
               break;
            default:
               break;
         }
         pOI->setStateFlags( lStateFlags );
         pOI->setGroupFlags( lGroupFlags );
         pOI->setOwnInstance( ( pOI->getStateFlags() & NO_BASE_DELETE ) == 0 );
      }
      else
      {
         long lStateFlags  = ( *objIterToCopyFlagsFrom ).second->getStateFlags();
         switch( eBaseDelete )
         {
            case NO_DELETE_ON_DTOR:
               lStateFlags |= NO_BASE_DELETE;
               break;
            case DELETE_ON_DTOR:
               lStateFlags &= ~NO_BASE_DELETE;
               break;
            default:
               break;
         }
         pOI->setStateFlags( lStateFlags );
         pOI->setGroupFlags( ( *objIterToCopyFlagsFrom ).second->getGroupFlags() );
         pOI->setOwnInstance( ( pOI->getStateFlags() & NO_BASE_DELETE ) == 0 && pObject != ( *objIterToCopyFlagsFrom ).second->getInstance() );
      }

      pOI->setInstance( pObject );
      _objectMap.insert( BFAbstractCBO::OBJECT_MAP::value_type( objKey, pOI ));
      hasToNotify = true;

   }
   else
   {
      //if obj is already there, different, and base owns, delete it
      if( ( *objIter ).second->getInstance() != pObject )
      {
         BFAbstractCBO::OBJECT_INFO *pOI = ( *objIter ).second;

         if( pOI->ownsInstance() )
         {
            delete pOI->getInstance();
         }

         long lStateFlags = pOI->getStateFlags();
         switch( eBaseDelete )
         {
            case NO_DELETE_ON_DTOR:
               lStateFlags |= NO_BASE_DELETE;
               break;
            case DELETE_ON_DTOR:
               lStateFlags &= ~NO_BASE_DELETE;
               break;
            default:
               break;
         }
         pOI->setStateFlags( lStateFlags );
         pOI->setOwnInstance( ( pOI->getStateFlags() & NO_BASE_DELETE ) == 0 );
         pOI->setInstance( pObject );
         hasToNotify = true;
      }
   }

   if( hasToNotify )
   {
      if( objKey.getDataGroupId() != BF::HOST )
      {
         // we should use in a BFObjIter the string map in order to keep the right ordering
         _hasNonBFHOSTsetObjects = true;
      }
      notifyObservers( ifds::NullFieldId, objKey.getDataGroupId(), NON_FIELD_NOTIFICATIONS, E_EVENT_CBO_OBJITER_UPDATE, I_( "" ));
   }

   return(true);
}

//******************************************************************************
bool BFCBO::setObject( BFAbstractCBO*  pObject,
                       const DString&  strKey,
                       BF_OBJ_ACTIVITY activity,
                       const BFDataGroupId& idDataGroup,
                       BF_OBJ_TYPE     type,
                       OBJ_DELETE      eBaseDelete /* = DEFAULT */ )
{
   BFObjectKey objKey( strKey, isVersionable() ? idDataGroup : BF::HOST, activity, type );
   return(setObject( objKey, pObject, eBaseDelete ));
}

//******************************************************************************
bool BFCBO::resetObjectKey( const BFObjectKey& keyOrig, 
                            const BFObjectKey& keyNew )
{
   EXECHISTI( I_( "resetObjectKey( const BFObjectKey &, const BFObjectKey & )" ) );
   BFAbstractCBO::OBJECT_MAP_ITER itNew = _objectMap.find( keyNew );
   if( _objectMap.end() == itNew ) {
      BFAbstractCBO::OBJECT_MAP_ITER itOrig;
      itOrig = _objectMap.find( keyOrig );
      if( _objectMap.end() != itOrig ) {
         BFAbstractCBO::OBJECT_INFO* pObjInfo = (*itOrig).second;
         _objectMap.erase( itOrig );
         _objectMap.insert( BFAbstractCBO::OBJECT_MAP::value_type( keyNew, pObjInfo ) );
         return( true );
      }
   }
   return( false );
}

//******************************************************************************
SEVERITY BFCBO::validateAll( const BFDataGroupId& idDataGroup, long lValidateGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::BFBASE_CONDITION,
                          CLASSNAME,
                          I_( "validateAll( const BFDataGroupId &, long )" ) );
   SEVERITY sevRtn      = NO_CONDITION;
   SEVERITY maxSevRtn   = NO_CONDITION;
   SEVERITY objSevRtn   = NO_CONDITION;

   if( false == isVersionable() ) { return GETCURRENTHIGHESTSEVERITY(); }

   doPreValidateAll( idDataGroup );
   DString dstrFieldValue;
   //check the fields if are updated
   for( FIELD_MAP_ITER fieldIter = _fieldMap.begin( ); fieldIter != _fieldMap.end( ); ++fieldIter )
   {
      const BFFieldKey& rKey = (*fieldIter).first;
      FieldInfo* pFI = (*fieldIter).second;

      if( ( pFI->checkGroupFlag( lValidateGroup ) || lValidateGroup == 0 ) &&
          rKey.getDataGroupId() == idDataGroup &&
          !(pFI->checkStateFlag( VALID ) ) )
      {
         dstrFieldValue = ( NULL != pFI->getStrValue() ) ? *(pFI->getStrValue()) : NULL_STRING;
         sevRtn = validateField(rKey.getFieldId(), dstrFieldValue , idDataGroup );
         maxSevRtn = maxSevRtn >= sevRtn ? maxSevRtn : sevRtn;
      }
   }
   //if not already updated,
   //check the children objects if are updated
   clearDataGroupErrors( idDataGroup );

   BFAbstractCBO::OBJECT_MAP_ITER objIter;
   for( objIter = _objectMap.begin( ); objIter != _objectMap.end( ); ++objIter )
   {
      if( isNew( )&& !isList( ) && ( *objIter ).first.getDataGroupId() == BF::HOST &&
          ( *objIter ).second->getStateFlags() & REQUIRED &&
          (( *objIter ).second->getGroupFlags() & lValidateGroup || lValidateGroup == 0 ) )
      {
         BFObjIter bfIter( *this, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED, false );
         bfIter.begin( OBJ_TYPE_NONE, OBJ_ACTIVITY_NONE, ( *objIter ).first.getStringKey() );
         BFAbstractCBO * bfb = bfIter.getObject( );
         if( bfb != NULL && bfb->isList( ) && !bfb->hasNonDummyEntries( idDataGroup ) )
         {
            DString error = I_( "" );
            addIDITagValue( error, IDI_TAG, ( *objIter ).first.getStringKey() );
            ADDCONDITIONFROMFILEIDI( CND::ERR_OBJ_REQUIRED_IN_LIST, error );
            objSevRtn = SEVERE_ERROR;
         }
         else if( bfb == NULL || ( !bfb->isList( ) &&  bfb->isNew( ) && ( bfIter.getKey( ).getDataGroupId() == idDataGroup ) && !bfb->isUpdated( true )) )
         {
            DString error = I_( "" );
            addIDITagValue( error, IDI_TAG, ( *objIter ).first.getStringKey() );
            ADDCONDITIONFROMFILEIDI( CND::ERR_OBJ_REQUIRED, error );
            objSevRtn = SEVERE_ERROR;
         }

      }
   }

   sevRtn = doValidateAll( idDataGroup, lValidateGroup );
   objSevRtn = objSevRtn > sevRtn ? objSevRtn : sevRtn;
   PROMOTECONDITIONS( );

   METAGROUP_MAP::iterator groupIter;

   findDataGroup( groupIter, idDataGroup );

   if( groupIter != _dataGroupMap.end( ) )
   {
      GROUP_INFO * lGroupInfo = ( *groupIter ).second;

      if( objSevRtn > NO_CONDITION )
      {

         int count = CURRENTCONDITIONCOUNT( );
         Condition *pCondition = NULL;
         for( int i = 0; i < count; i++ )
         {
            pCondition = new Condition( *GETCURRENTCONDITION( i ));
            lGroupInfo->addCondition( pCondition );
         }
      }
   }

   _objLastValidationError = GETCURRENTHIGHESTSEVERITY( );

   _objChildrenLastValidationError = NO_CONDITION;

   BFObjIter bfObjIter( *this, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED );
   while( !bfObjIter.end( ) )
   {
      const BFObjectKey& rKey = bfObjIter.getKey( );
      BFAbstractCBO* pBase = bfObjIter.getObject( );
      long lGroupFlags = bfObjIter.getGroupFlags( );
      if( lGroupFlags & lValidateGroup || lValidateGroup == 0 )
      {
         if( rKey.getActivity() != OBJ_ACTIVITY_DELETED    &&
             pBase && pBase->isUpdatedForDataGroup( idDataGroup, true ) )
         {
            sevRtn = pBase->validateAll( idDataGroup );
            if( sevRtn > NO_CONDITION )
            {
               PROMOTECONDITIONS( );
               maxSevRtn = maxSevRtn >= sevRtn ? maxSevRtn : sevRtn;
            }
            _objChildrenLastValidationError  = _objChildrenLastValidationError > sevRtn ? _objChildrenLastValidationError : sevRtn;
         }
      }
      ++bfObjIter;

   }

   findDataGroup( groupIter, idDataGroup );

   if( groupIter != _dataGroupMap.end( ) )
   {
      ( *groupIter ).second->setLastValidationError( _objLastValidationError );
      ( *groupIter ).second->setLastChildValidationError( _objChildrenLastValidationError );
   }
   return(GETCURRENTHIGHESTSEVERITY( ));

}

//******************************************************************************
SEVERITY BFCBO::validateField( const BFFieldId& idField,
                               const DString& strValue,
                               const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::BFBASE_CONDITION,
                          CLASSNAME,
                          I_( "validateField( const BFFieldId &, const DString &, const BFDataGroupId & )" ) );
   SEVERITY sevRtn = NO_CONDITION;

   if( false == isVersionable() ) { return GETCURRENTHIGHESTSEVERITY(); }

   clearFieldErrors( idField, idDataGroup );
   FieldInfo * pFieldInfo = getFieldInfoPointer( idField, idDataGroup, false );
   if( pFieldInfo != NULL && !( pFieldInfo->checkStateFlag( VALID ) ) )
   {
      doValidateField( idField, strValue, idDataGroup );
      sevRtn = GETCURRENTHIGHESTSEVERITY( );

      const BFDataFieldProperties* pProp = BFDataFieldProperties::get( idField );

      if( ( sevRtn <= WARNING ) &&
          ( pFieldInfo->checkStateFlag( REQUIRED ) ) &&
          ( strValue == NULL_STRING ) )
      {
         DString error = I_( "" );         
		 
         if( bfutil::isServerContext() )
         {			
			addIDITagValue( error, IDI_TAG, idField.getName() );             
            ADDCONDITIONFROMFILEIDI( CND::ERR_FIELD_REQUIRED, error );
         }
         else 
         {		
			addIDITagValue( error, IDI_TAG, I_( " ( " ) + DString::asString( idField.getId() ) + I_( " )" ) );
            ADDCONDITIONFROMFILEIDI( CND::ERR_FIELD_REQUIRED_GUI, error );
         }
      }

      // confirm that field has valid value from substitution list if
      // field has a substitution list
      BFProperties* pBFP  = getFieldProperties(idField,idDataGroup);
      sevRtn = GETCURRENTHIGHESTSEVERITY( );
      if( (sevRtn <= WARNING ) && (NULL != pBFP) && (NULL != pProp) &&
          pProp->getSubstitutionSet( ClientLocaleContext::get() ) )
      {
         // to do a Key or Value check the comparison value must have trailing spaces trimmed.
         DString strValueNC = strValue;
         strValueNC.stripTrailing();
         DString strValueNCUppercase = strValueNC;
         strValueNCUppercase.upperCase();

         if( ( !pFieldInfo->checkStateFlag( REQUIRED ) && // field is optional and blank
               ( strValue == NULL_STRING ) ) ||
             pBFP->isValidKey( strValueNC ) ||         // or field has valid key
             pBFP->isValidKey( strValueNCUppercase ) ||         // or field has valid key
             pBFP->isValidValue( strValueNC ) )        // or field has valid value
         {
            // field's value is in the substitution list ... do nothing
         }
         else
         {
            // The field's value is not in the substition list.  Add a condition
            // unfortuately we need different message depending upon the execution context
            // (server or gui).  if we are in server context then we want to include the
            // field name in the message.
            if( bfutil::isServerContext() )
            {
               DString idi;
               addIDITagValue( idi, I_( "FIELD" ), idField.getName().c_str() );
               ADDCONDITIONFROMFILEIDI( CND::ERR_FIELD_VALUE_NOT_VALID, idi );
            }
            else
            {
               ADDCONDITIONFROMFILE( CND::ERR_FIELD_VALUE_NOT_VALID_GUI );
            }
            bf::log::LogStream s( bf::log::field | bf::log::cbo );
            s << bf::log::severe << I_( "Field required condition for field: " ) << idField.getName() << I_('[' ) << idField.getId() << I_("].") << bf::log::endlf;
         }
      }

      sevRtn = GETCURRENTHIGHESTSEVERITY( );

      if( sevRtn < WARNING )
      {
         pFieldInfo->setStateFlag( VALID );
      }
      else
      {
         pFieldInfo->clearStateFlag( VALID );
      }
   }

   if( sevRtn > NO_CONDITION )
   {
      pFieldInfo->clearConditionVector();
      int count = CURRENTCONDITIONCOUNT( );
      Condition* pCondition = NULL;
      for( int i = 0; i < count; i++ )
      {
         pCondition = new Condition( *GETCURRENTCONDITION( i ));
         pFieldInfo->addCondition( pCondition );
      }
   }

   return(sevRtn);
}

//******************************************************************************
void BFCBO::formatField( const BFFieldId& idField, DString& strValue, const BFDataGroupId& idDataGroup ) const
{
   // If there are extant BFProperties then use those, otherwise use the field properties.
   BFProperties* pBFP = NULL;
   FieldInfo* pFI = NULL;
   if( NULL != ( pFI = getFieldInfoPointer( idField, isVersionable() ? idDataGroup : BF::HOST ) ) )
   {
      pBFP = pFI->getFieldProperties();
   }

   // If we have a BFProperties object then it should be given first crack at formatting
   // the value.  In the event that it decides not to format it (a pretty common occurrence)
   // then we will use the BFDataField::formatValue method
   if( NULL != pBFP && true == pBFP->formatValue( idField, strValue, true ) )
   {
      return;
   }

   BFDataField::formatValue( idField, strValue, true );
   //Temp fix for space padding.
   strValue.stripTrailing ();
}

//******************************************************************************
void BFCBO::unformatField( const BFFieldId& idField, DString& strValue, const BFDataGroupId& idDataGroup ) const
{
   // If there are extant BFProperties then use those, otherwise use the field properties.
   BFProperties* pBFP = NULL;
   FieldInfo* pFI = NULL;
   if( NULL != ( pFI = getFieldInfoPointer( idField, isVersionable() ? idDataGroup : BF::HOST ) ) )
   {
      pBFP = pFI->getFieldProperties();
   }

   // If we have a BFProperties object then it should be given first crack at formatting
   // the value.  In the event that it decides not to format it (a pretty common occurrence)
   // then we will use the BFDataField::formatValue method
   if( NULL != pBFP && true == pBFP->unformatValue( idField, strValue, true ) )
   {
      return;
   }
   BFDataField::unformatValue( idField, strValue, true );
   //Temp fix for space padding.
   strValue.stripTrailing ();
}

//******************************************************************************
bool BFCBO::dumpAllFieldsToFile(const DString& dstrFileName, const BFCBO &pbfbase)
{
   DStringA dstraFileName(dstrFileName);
   i_ofstream OutputFile(dstraFileName.c_str(), std::ios::out);

   if( !OutputFile )
   {
      return(false);
   }

   OutputFile << allfields << recurse_objects << pbfbase << resetbfbaseio << std::endl;

   OutputFile.close();

   return(true);
}

#ifdef _DEBUG
bool BFCBO::dump( const char* pszFileName )
{
   bool bRc = false;
   FILE* pFile = fopen( pszFileName, "w" );
   if( NULL != pFile ) 
   {
      bRc = privDump( pFile, false );
      fclose( pFile );
   }
   return( bRc );
}

bool BFCBO::dumpTree( const char* pszFileName )
{
   bool bRc = false;
   FILE* pFile = fopen( pszFileName, "w" );
   if( NULL != pFile ) 
   {
      bRc = privDump( pFile, true );
      fclose( pFile );
   }
   return( bRc );
}

bool BFCBO::privDump( FILE* pFile, bool bRecurse )
{
   const type_info &ti = typeid(*this);
   fwprintf( pFile, I_( "\n\nCBO: %S (%08x)\n" ), ti.name(), this );

   privDumpFields( pFile );

   if( true == bRecurse )
   {
      fwprintf( pFile, I_( "\nContained CBOs\n" ) );

      BFAbstractCBO::OBJECT_MAP::iterator it = _objectMap.begin();
      for( ; it != _objectMap.end(); ++it )
      {
         OBJECT_INFO* pOI = (*it).second;
         if( NULL != pOI )
         {
            (dynamic_cast< BFCBO* >(pOI->getInstance()))->privDump( pFile, bRecurse );
         }
      }
   }
   return( true );
}

bool BFCBO::privDumpFields( FILE* pFile )
{
   const ClientLocale& cl = ClientLocaleContext::get();

   // Data objects
   DATA_VECTOR_ITER itData = _vecData.begin();
   for(; itData != _vecData.end(); ++itData )
   {
      const BFData& rData = *(*itData);
      fwprintf( pFile, I_( "---------------------------------\n" ) );
      fwprintf( pFile, I_( "Data object %s\n" ), rData.getId().getName().c_str() );

      BFConstDataFieldIter itField( rData, true );
      for( ; itField; ++itField )
      {
         const BFDataField& df = itField();
         const BFFieldId& id = df.getId();
         DString dstrField = df.get( true, cl, NULL );
         fwprintf( pFile, I_( "   %s: >>%s<<\n" ), id.getName().c_str(), dstrField.c_str() );
      }
   }

   fwprintf( pFile, I_( "---------------------------------\n" ) );
   fwprintf( pFile, I_( "Updated fields\n" ) );
   // updated fields
   FIELD_MAP_ITER itFlds = _fieldMap.begin();
   for( ; itFlds != _fieldMap.end(); ++itFlds )
   {
      const BFFieldKey& rKey = (*itFlds).first;
      FieldInfo* pFI = (*itFlds).second;
      fwprintf( pFile, I_( "   %s (dg=%d): %c%c%c%c%c%c >>%s<<\n" ), 
                rKey.getFieldId().getName().c_str(),
                rKey.getDataGroupId().getId(),
                pFI->checkStateFlag( READ_ONLY ) ? I_( 'r' ) : I_( '_' ),
                pFI->checkStateFlag( REQUIRED ) ? I_( 'R' ) : I_( '_' ),
                pFI->checkStateFlag( UPDATED ) ? I_( 'u' ) : I_( '_' ),
                pFI->checkStateFlag( VALID ) ? I_( 'v' ) : I_( '_' ),
                pFI->checkStateFlag( PRIVATE_USE ) ? I_( 'p' ) : I_( '_' ),
                pFI->checkStateFlag( CALCULATED_FIELD ) ? I_( 'c' ) : I_( '_' ),
                pFI->checkStateFlag( APPEND_VALUE_TO_SUBST ) ? I_( 's' ) : I_( '_' ),
                pFI->getStrValue() == NULL ? I_( "(NULL)" ) : pFI->getStrValue()->c_str() );
   }

   return( true );
}
#endif // _DEBUG


/******************************************************************************
 * protected methods
/******************************************************************************/

//******************************************************************************
void BFCBO::addCrossEdit( const BFFieldId& crossEdtId, const BFFieldId& idField )
{
   std::pair<CROSS_EDIT_MAP_ITER, CROSS_EDIT_MAP_ITER> crossMapPair;
   CROSS_EDIT_MAP_ITER IterCrossMap;

   crossMapPair = m_crossEditGroupToFieldMap.equal_range( crossEdtId );

   IterCrossMap = crossMapPair.first;
   while( IterCrossMap != crossMapPair.second )
   {
      if( ( *IterCrossMap ).second == idField )
         break;
      else
         ++IterCrossMap;
   }
   if( IterCrossMap == crossMapPair.second )
      m_crossEditGroupToFieldMap.insert( CROSS_EDIT_MAP::value_type( crossEdtId, idField ));


   crossMapPair = m_crossEditFieldToGroupMap.equal_range( idField );

   IterCrossMap = crossMapPair.first;
   while( IterCrossMap != crossMapPair.second )
   {
      if( ( *IterCrossMap ).second == crossEdtId )
         break;
      else
         ++IterCrossMap;
   }
   if( IterCrossMap == crossMapPair.second )
      m_crossEditFieldToGroupMap.insert( CROSS_EDIT_MAP::value_type( idField, crossEdtId ));
}

//******************************************************************************
DString BFCBO::attachDataObject( BFData &data,
                                 bool bBaseDelete,
                                 bool bInsertLast,
                                 const DString&  dstKey )
{
   EXECHISTI( I_( "attachDataObject( BFData &, bool, bool, const DString & )" ) );

   //add to back or front of data obj vector
   if( bInsertLast )
   {
      _vecData.push_back( &data );
   }
   else
   {
      _vecData.insert( _vecData.begin( ), &data );
   }

   DATA_XREF_INFO *pDXI = new DATA_XREF_INFO;
   pDXI->m_pData = &data;
   pDXI->m_bBaseDelete = bBaseDelete;

   DString key = dstKey;
   if( key == NULL_STRING )
      key = DString::asString( _dataMapKey++ ).padLeft( 5, '0' );;

   _dataXrefMap.insert( DATA_XREF_MAP::value_type( key, pDXI ));

   return(key);
}

//******************************************************************************
void BFCBO::clearFieldErrors( const BFFieldId& idField, const BFDataGroupId& idDataGroup )
{
   CONDITIONVECTOR * cndVec = NULL;
   SEVERITY sevRtn = NO_CONDITION;

   FIELD_MAP_ITER  fieldIter;
   fieldIter = _fieldMap.find( BFFieldKey( idDataGroup, idField ));
   if( fieldIter != _fieldMap.end( ) )
   {
      FieldInfo * pFI = ( *fieldIter ).second;
      pFI->clearConditionVector();
   }
}

//******************************************************************************
void BFCBO::clearFieldMap( )
{
   EXECHISTI( I_( "clearFieldMap(  )" ) );

   for( FIELD_MAP_ITER fieldIter = _fieldMap.begin( ); fieldIter != _fieldMap.end( ); ++fieldIter )
   {
      FieldInfo* pFI = ( *fieldIter ).second;
      if( NULL != pFI )
      {
         const BFFieldKey& rKey = (*fieldIter).first;
         if( rKey.getDataGroupId() != BF::HOST )
         {
            delete pFI;
            fieldIter = _fieldMap.erase( fieldIter );
         }
         else
         {
            if( pFI->getStrValue() )
            {
               pFI->resetStrValue();
            }
            pFI->clearConditionVector( );
         }
      }
   }
}

//******************************************************************************
SEVERITY BFCBO::createObjectForEachRepeat( const BFData &data )
{
   try
   {
      int cRepeats = data.getRepeatCount( );

      if( cRepeats != 0 )
      {
         // for each repeat, call the derived class' doCreateObject
         for( int i = 0; i < cRepeats; i++ )
         {
            BFCBO *pObj = NULL;
            doCreateObject( data.getRepeat( i ), pObj );

            if( pObj != NULL )
            {
               BFObjectKey objKey;
               getKey( objKey, &( data.getRepeat( i ) ) );
               setObject( objKey, pObj );

               // clear this for HOST
               pObj->clearUpdatedFlags( BF::HOST );
               pObj->setAllFieldsValid( BF::HOST );
            }
         }
      }
   }
   catch( BFDataException& /*e*/ )
   {
      BF_RETHROW( e );
   }
   catch( ... )
   {
      assert( 0 );
      throw;
   }
   return(NO_CONDITION);
}

//******************************************************************************
SEVERITY BFCBO::doCreateObject( const BFData& data, BFCBO *&pObjOut )
{
   MAKEFRAMEAUTOPROMOTE2( CND::BFBASE_CONDITION,
                          CLASSNAME,
                          I_( "doCreateObject( const BFData &, BFCBO *& )" ) );
   pObjOut = new GenericBFCBO( this );
   pObjOut->attachDataObject( const_cast< BFData& >( data ), false, true );

   return( GETCURRENTHIGHESTSEVERITY() );
}

//******************************************************************************
void BFCBO::eraseDataObjectContainers( )
{
   EXECHISTI( I_( "eraseDataObjectContainers(  )" ) );

   //erase map
   DATA_XREF_MAP_ITER dataIter =    _dataXrefMap.begin( );
   DATA_XREF_MAP_ITER dataIterEnd = _dataXrefMap.end( );
   while( dataIter != dataIterEnd )
   {
      DATA_XREF_INFO* pXrefInfo = (*dataIter).second;
      if( pXrefInfo->m_bBaseDelete )
      {
         delete pXrefInfo->m_pData;
      }
      delete pXrefInfo;
      dataIter = _dataXrefMap.erase( dataIter );
   }
   //erase vector
   _vecData.erase( _vecData.begin( ), _vecData.end( ));

}

//******************************************************************************
void BFCBO::eraseIteratorsVector( )
{
   EXECHISTI( I_( "eraseIteratorsVector(  )" ) );
   ITERATORS_VECTOR_ITER vecIter    = _iteratorsVec.begin( );
   ITERATORS_VECTOR_ITER vecIterEnd = _iteratorsVec.end( );

   while( vecIter != vecIterEnd )
   {
      delete *vecIter;
      ++vecIter;
   }
   _iteratorsVec.erase( _iteratorsVec.begin( ), vecIterEnd );
}

//******************************************************************************
void BFCBO::eraseObjectContainer( )
{
   EXECHISTI( I_( "eraseObjectContainer(  )" ) );

   BFAbstractCBO::OBJECT_MAP_ITER  objIter      = _objectMap.begin( );
   BFAbstractCBO::OBJECT_MAP_ITER  objIterEnd   = _objectMap.end( );

   while( objIter != objIterEnd )
   {
      OBJECT_INFO* pOI = (*objIter).second;
      if( ( NULL != pOI ) && pOI->getInstance() &&
          !flagsAreOn( pOI->getStateFlags(), NO_BASE_DELETE ) )
      {
         if( pOI->ownsInstance() )
            delete pOI->getInstance();
      }
      delete pOI;
      objIter = _objectMap.erase( objIter );
   }
}

//******************************************************************************
bool BFCBO::fieldExists( const BFFieldId& idField ) const
{
   EXECHISTI( I_( "fieldExists( const BFFieldId & )" ) );
   bool retVal = false;
   FieldInfo * pFieldInfo = getFieldInfoPointer( idField, BF::HOST );
   if( pFieldInfo )
      retVal = true;
   if( !retVal )
   {
      DATA_VECTOR_ITER  dataIter    = const_cast<BFCBO *>( this )->_vecData.begin( );
      DATA_VECTOR_ITER  dataIterEnd = const_cast<BFCBO *>( this )->_vecData.end( );

      while( dataIter != dataIterEnd )
      {
         if( ( *dataIter )->exists( idField ) )
         {
            retVal = true;
            break;
         }
         ++dataIter;
      }
   }
   return(retVal);
}


//******************************************************************************
BFAbstractCBO* BFCBO::findObject( const BFObjectKey & objKey, bool lookIntoParents ) const
{
   EXECHISTI( I_( "findObject( const BFObjectKey &, bool )" ) );


   BFConstObjIter bfIter( *this, objKey.getDataGroupId(), false, BFConstObjIter::ITERTYPE::NON_DELETED, false );
   bfIter.begin( objKey.getType(), objKey.getActivity(), objKey.getStringKey() );

   if( bfIter.end( ) || ( !lookIntoParents && bfIter.getKey( ).getDataGroupId() != objKey.getDataGroupId() ) )
      return(NULL_POINTER);
   else
      return(bfIter.getObject( ));
}

//******************************************************************************
long BFCBO::getFieldGroupFlags( const BFFieldId& idField, const BFDataGroupId& idDataGroup )
{
   FieldInfo * pFieldInfo = getFieldInfoPointer( idField, isVersionable() ? idDataGroup : BF::HOST );
   if( pFieldInfo != NULL )
   {
      return(  pFieldInfo->getGroupFlags() );
   }

   return(0);
}


//******************************************************************************
bool BFCBO::checkFieldStateFlag( const BFFieldId& idField, const BFDataGroupId& idDataGroup, long f )
{
   FieldInfo * pFieldInfo = getFieldInfoPointer( idField, isVersionable() ? idDataGroup : BF::HOST );
   if( pFieldInfo != NULL )
      return( pFieldInfo->checkStateFlag( f ) );
   return( false );
}

//******************************************************************************
BFData * BFCBO::getDataObject( const DString&  dstKey )
{
   EXECHISTI( I_( "getDataObject( const DString & )" ) );
   DATA_XREF_MAP_ITER iter = _dataXrefMap.find( dstKey );
   if( iter == _dataXrefMap.end() )
      return(NULL);

   DATA_XREF_INFO * ptr = (*iter).second;
   if( !ptr )
      return(NULL);

   return(ptr->m_pData);
}

//******************************************************************************
BFObjIter & BFCBO::getObjectIter( const BFDataGroupId& idDataGroup , bool matchSubStrings )
{
   MAKEFRAMEAUTOPROMOTE2( CND::BFBASE_CONDITION,
                          CLASSNAME,
                          I_( "getObjectIter( const BFDataGroupId &, bool )" ) );
   BFObjIter * pIter = new BFObjIter( *this, isVersionable() ? idDataGroup : BF::HOST, matchSubStrings );
   _iteratorsVec.push_back( pIter );
   return(*pIter);
}

//******************************************************************************
SEVERITY BFCBO::initDefaults( const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::BFBASE_CONDITION,
                          CLASSNAME,
                          I_( "initDefaults( const BFDataGroupId & )" ) );
   FIELD_MAP_ITER  iter    = _fieldMap.begin( );

   while( iter != _fieldMap.end( ) )
   {
      if( ( *iter ).second->checkStateFlag( INIT_TO_DEFAULT ) )
      {
         BFProperties * bfProp = getFieldProperties(( *iter ).first.getFieldId(), ( *iter ).first.getDataGroupId() );
         if( ( *iter ).second->getStrValue() == NULL )
         {
            DString defVal;
            bfProp->getDefaultValue( defVal );
            ( *iter ).second->setValue( &defVal );
         }
      }
      ++iter;
   }
   return(GETCURRENTHIGHESTSEVERITY( ));

}

//******************************************************************************
bool BFCBO::isFieldUpdated( const BFFieldId& idField, const BFDataGroupId& idDataGroup )
{
   return( checkFieldStateFlag( idField, isVersionable() ? idDataGroup : BF::HOST, UPDATED ) );
}

//******************************************************************************
bool BFCBO::isFieldRequired( const BFFieldId& idField, const BFDataGroupId& idDataGroup )
{
   return( checkFieldStateFlag( idField, isVersionable() ? idDataGroup : BF::HOST, REQUIRED ) );
}

//******************************************************************************
bool BFCBO::isFieldReadOnly( const BFFieldId& idField, const BFDataGroupId& idDataGroup )
{
   return( checkFieldStateFlag( idField, isVersionable() ? idDataGroup : BF::HOST, READ_ONLY ) );
}

//******************************************************************************
bool BFCBO::isFieldValid( const BFFieldId& idField, const BFDataGroupId& idDataGroup )
{
   return( checkFieldStateFlag( idField, isVersionable() ? idDataGroup : BF::HOST, VALID ) );
}

//******************************************************************************
SEVERITY BFCBO::processCrossEdits( const BFFieldId& idField, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::BFBASE_CONDITION,
                          CLASSNAME,
                          I_( "processCrossEdits( const BFFieldId &, const BFDataGroupId & )" ) );

   bool allFieldsValid = true;

   if( false == isVersionable() ) { return GETCURRENTHIGHESTSEVERITY(); }

   std::pair<CROSS_EDIT_MAP_ITER, CROSS_EDIT_MAP_ITER> crossEditsMapPair;
   std::pair<CROSS_EDIT_MAP_ITER, CROSS_EDIT_MAP_ITER> fieldsMapPair;

   CROSS_EDIT_MAP_ITER fieldIter;
   CROSS_EDIT_MAP_ITER crossEditIter;

// all crossEdits to which this field belongs
   crossEditsMapPair = m_crossEditFieldToGroupMap.equal_range( idField );
   crossEditIter     = crossEditsMapPair.first;


   while( crossEditIter != crossEditsMapPair.second )
   {
//    all fields that belongs to this crossEdit
      const BFFieldId& currentCrossEditId = (*crossEditIter).second;
      FieldInfo *pFieldInfo = getFieldInfoPointer( currentCrossEditId, idDataGroup );

      if( pFieldInfo && pFieldInfo->checkStateFlag( IMMEDIATE_VALIDATION ) )
      {
         fieldsMapPair      = m_crossEditGroupToFieldMap.equal_range( currentCrossEditId );
         fieldIter          = fieldsMapPair.first;

         bool allFieldsValid = true;

         while( fieldIter != fieldsMapPair.second )
         {
            const BFFieldId& idRHS = (*fieldIter).second;
            if( !isFieldValid( idRHS, idDataGroup ) && getErrorState( idRHS, idDataGroup ) != WARNING )
            {
               // if we have all fields valid we want to call validation for that crossEdit
               allFieldsValid = false;
               break;
            }
            ++fieldIter;
         }

         if( allFieldsValid )
         {
            SEVERITY sevRtn = validateField( currentCrossEditId, I_(""), idDataGroup );

            // if we have recursive CrossEdit containment we want to process containing CrossEdits to
//            if ( sevRtn <= WARNING )
            {
               fieldsMapPair      = m_crossEditGroupToFieldMap.equal_range( currentCrossEditId );
               fieldIter          = fieldsMapPair.first;

               while( fieldIter != fieldsMapPair.second )
               {
                  notifyObservers( (*fieldIter).second, idDataGroup, FIELD_NOTIFICATIONS, E_EVENT_VALUE_CHANGE, I_( "" ));
                  ++fieldIter;
               }

               doApplyRelatedChanges( currentCrossEditId, idDataGroup );
               processCrossEdits( currentCrossEditId, idDataGroup );
            }
         }
      }
      ++crossEditIter;
   }

   return(GETCURRENTHIGHESTSEVERITY( ));

}

//******************************************************************************
bool BFCBO::registerMemberData( long                      lNumberFields,
                                const CLASS_FIELD_INFO  * pClassFieldInfo,
                                long                      lNumberObjects,
                                const CLASS_OBJECT_INFO * pClassObjectInfo )
{
   EXECHISTI( I_( "registerMemberData( long, const CLASS_FIELD_INFO *, long, const CLASS_OBJECT_INFO * )" ) );

   _receivingData.wait(INFINITE);
   BFCBOGuard g( _baseLock );
   if( pClassFieldInfo )
   {
      //add item to host part of FieldMap for each classFieldInfo item
      for( int i = 0; i < lNumberFields; i++, pClassFieldInfo++ )
      {
         FieldInfo * pFieldInfo = new FieldInfo( BF::HOST, pClassFieldInfo->m_lStateFlags,
                                                 pClassFieldInfo->m_lGroupFlags );
         _fieldMap.insert( FIELD_MAP::value_type( BFFieldKey( BF::HOST, pClassFieldInfo->getFieldId() ), pFieldInfo ));
      }
   }

   if( pClassObjectInfo )
   {
      //add item to _objectMap for each classObjectInfo item
      for( int i = 0; i < lNumberObjects; i++, pClassObjectInfo++ )
      {
         BFAbstractCBO::OBJECT_INFO *pObjectInfo = new BFAbstractCBO::OBJECT_INFO;
         pObjectInfo->setStateFlags( pClassObjectInfo->m_lStateFlags );
         pObjectInfo->setGroupFlags( pClassObjectInfo->m_lGroupFlags );
         pObjectInfo->setInstance( NULL );
         if( ( pClassObjectInfo->m_lStateFlags & NO_BASE_DELETE ) == 0 )
            pObjectInfo->setOwnInstance( true );
         _objectMap.insert( BFAbstractCBO::OBJECT_MAP::value_type( BFObjectKey( pClassObjectInfo->m_strName ), pObjectInfo ));
      }
   }

   return(true);
}

//******************************************************************************
void BFCBO::setCrossEditInvalid( const BFFieldId& idField, const BFDataGroupId& idDataGroup )
{
   EXECHISTI( I_( "setCrossEditInvalid( const BFFieldId &, const BFDataGroupId & )" ) );
   clearFieldErrors( idField, isVersionable() ? idDataGroup : BF::HOST );

   std::pair<CROSS_EDIT_MAP_ITER, CROSS_EDIT_MAP_ITER> crossMapPair;
   CROSS_EDIT_MAP_ITER IterCrossMap;

   crossMapPair = m_crossEditFieldToGroupMap.equal_range( idField );
   IterCrossMap = crossMapPair.first;

   while( IterCrossMap != crossMapPair.second )
   {
      setFieldInvalid(( *IterCrossMap ).second, isVersionable() ? idDataGroup : BF::HOST );
      ++IterCrossMap;
   }
}

//******************************************************************************
void BFCBO::setFieldGroupFlags( const BFFieldId& idField, const BFDataGroupId& idDataGroup, long lFlags )
{
   EXECHISTI( I_( "setFieldGroupFlags( const BFFieldId &, const BFDataGroupId &, long )" ) );
   FieldInfo * pFieldInfo = prepareFieldInfoPointer( idField, isVersionable() ? idDataGroup : BF::HOST );
   if( pFieldInfo != NULL )
      pFieldInfo->setGroupFlags( lFlags );
}

//******************************************************************************
SEVERITY BFCBO::setFieldNoValidate( const BFFieldId& idField,
                                    const DString& strValue,
                                    const BFDataGroupId& idDataGroup,
                                    bool  lFormatted,
                                    bool  lValid,
                                    bool  lSideEffect,
                                    bool  bApplyRelChanges )
{
   MAKEFRAMEAUTOPROMOTE2( CND::BFBASE_CONDITION,
                          CLASSNAME,
                          I_( "setFieldNoValidate( const BFFieldId &, const DString &, const BFDataGroupId &, bool, bool, bool, bool )" ) );

   //TODO - reject if read-only

   DString unformatedValue = strValue;
   if( lFormatted )
   {
      unformatField( idField, unformatedValue, isVersionable() ? idDataGroup : BF::HOST );
   }

   FieldInfo * pFieldInfo = prepareFieldInfoPointer( idField, isVersionable() ? idDataGroup : BF::HOST );

   // Determine if the field which is being set is in the CLASSFIELDINFO struct for the
   // concrete BFCBO class.  If it is *NOT* in that struct then the set will have no effect.
   // THIS IS A PROGRAMMING ERROR!  Either add the field to the CLASSFIELDINFO struct or
   // don't do the setFieldNoValidate() - CP20040518
   assert( NULL != pFieldInfo );

   if( pFieldInfo != NULL && ( !pFieldInfo->getStrValue()  || *pFieldInfo->getStrValue() != strValue ) )
   {
      pFieldInfo->setValue( &unformatedValue );
      lValid ? pFieldInfo->setStateFlag( VALID ) : pFieldInfo->clearStateFlag( VALID );
      if( lSideEffect )
         notifyObservers( idField, isVersionable() ? idDataGroup : BF::HOST, FIELD_NOTIFICATIONS, E_EVENT_VALUE_CHANGE, I_( "" ));
   }

   clearFieldErrors( idField, isVersionable() ? idDataGroup : BF::HOST );

   if( !lValid ) {
      setCrossEditInvalid( idField, isVersionable() ? idDataGroup : BF::HOST );
   }
   if( bApplyRelChanges ) {
      doApplyRelatedChanges( idField, isVersionable() ? idDataGroup : BF::HOST );
   }

   return(GETCURRENTHIGHESTSEVERITY( ));
}

//******************************************************************************
void BFCBO::setObjectFlags( const BFObjectKey & objKey, long& lStateFlags , long& lGroupFlags )
{
   lStateFlags = BFCBO::STATE_FLAGS::NONE;
   lGroupFlags = BFCBO::STATE_FLAGS::NONE;
}

//******************************************************************************
void BFCBO::setNoBaseDelete( const BFObjectKey &objKey, bool bNoDelete )
{
   BFAbstractCBO::OBJECT_MAP_ITER objIter = _objectMap.find( objKey );
   if( objIter != _objectMap.end() )
   {
      OBJECT_INFO* pOI = (*objIter).second;
      if( bNoDelete )
      {
         pOI->setStateFlag( NO_BASE_DELETE );
      }
      else
      {
         pOI->clearStateFlag( NO_BASE_DELETE );
      }
   }
}

//******************************************************************************
void BFCBO::setUpdatedFlag( const BFFieldId& idField, const BFDataGroupId& idDataGroup, bool bValue )
{
   EXECHISTI( I_( "setUpdatedFlag( const BFFieldId &, const BFDataGroupId &, bool )" ) );
   FieldInfo * pFieldInfo = prepareFieldInfoPointer( idField, isVersionable() ? idDataGroup : BF::HOST );
   if( pFieldInfo != NULL )
   {
      if( bValue )
      {
         pFieldInfo->setStateFlag( UPDATED ); 
      }
      else
      {
         pFieldInfo->clearStateFlag( UPDATED );
      }
   }

}

//******************************************************************************
void BFCBO::setValidFlag( const BFFieldId& idField, const BFDataGroupId& idDataGroup, bool bValue )
{
   EXECHISTI( I_( "setValidFlag( const BFFieldId &, const BFDataGroupId &, bool )" ) );
   FieldInfo * pFieldInfo = prepareFieldInfoPointer( idField, isVersionable() ? idDataGroup : BF::HOST );
   if( pFieldInfo != NULL )
   {
      if( bValue )
      {
         pFieldInfo->setStateFlag( VALID ); 
      }
      else
      {
         pFieldInfo->clearStateFlag( VALID );
      }
   }

}

/******************************************************************************
 * private methods
/******************************************************************************/

//******************************************************************************
void BFCBO::clearDataGroupErrors( const BFDataGroupId& idDataGroup )
{
   EXECHISTI( I_( "clearDataGroupErrors( const BFDataGroupId & )" ) );
   METAGROUP_MAP_ITER  groupIter;
   findDataGroup( groupIter, isVersionable() ? idDataGroup : BF::HOST );

   if( groupIter != _dataGroupMap.end( ) )
   {
      GROUP_INFO * grpInfo = ( *groupIter ).second;
      grpInfo->clearConditions();
   }
}

//******************************************************************************
SEVERITY BFCBO::eraseDataGroupFields( const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::BFBASE_CONDITION,
                          CLASSNAME,
                          I_( "eraseDataGroupFields( const BFDataGroupId & )" ) );

   // BF::HOST - not valid, it is the committed data group
   assert( idDataGroup != BF::HOST );
   assert( true == isVersionable() );

   METAGROUP_MAP_ITER groupIter;

   for( groupIter = _dataGroupMap.begin( ); groupIter != _dataGroupMap.end( ); ++groupIter )
   {
      if( ( *groupIter ).second->getParentDataGroupId() == idDataGroup )
      {
         eraseDataGroupFields(( *groupIter ).first );
      }
   }

   // if it has parent set parentgroup to it, otherwise set parentGroup to BF::HOST

   FIELD_MAP_ITER  _fieldIter       = _fieldMap.lower_bound( BFFieldKey( idDataGroup, ifds::NullFieldId ));
   FIELD_MAP_ITER  _fieldIterEnd    = _fieldMap.upper_bound( BFFieldKey( idDataGroup, ifds::MaxFieldId ));

   while( _fieldIter != _fieldIterEnd )
   {
      delete ( *_fieldIter ).second;
      _fieldIter = _fieldMap.erase( _fieldIter );
   }

   return(GETCURRENTHIGHESTSEVERITY( ));
}

//******************************************************************************
SEVERITY BFCBO::eraseOrphanGroups( )
{
   MAKEFRAMEAUTOPROMOTE2( CND::BFBASE_CONDITION,
                          CLASSNAME,
                          I_( "eraseOrphanGroups(  )" ) );

   METAGROUP_MAP_ITER groupIter = _dataGroupMap.begin( );

   while( groupIter != _dataGroupMap.end( ) )
   {
      if( ( *groupIter ).second->getParentDataGroupId() == BF::NullDataGroupId )     //???
      {
         delete ( *groupIter ).second;
         groupIter = _dataGroupMap.erase( groupIter );
      }
      else
         ++groupIter;
   }

   return(GETCURRENTHIGHESTSEVERITY( ));
}

//******************************************************************************
void BFCBO::findDataGroup( METAGROUP_MAP_CONST_ITER & iter, const BFDataGroupId& idDataGroup ) const
{
   EXECHISTI( I_( "findDataGroup( METAGROUP_MAP_CONST_ITER &, const BFDataGroupId & )" ) );
   iter = _dataGroupMap.find( idDataGroup );
   if( iter == _dataGroupMap.end( ) )
   {
      const BFDataGroupId& idParentDataGroup = idDataGroup.getParent();
      // KLUDGE: we want this method to be const, but it calls setGroup.
      //         problem won't exist in BFCBO - CP 23Jan2002
      (const_cast< BFCBO* >( this ))->setGroup( idParentDataGroup , idDataGroup );
      iter = _dataGroupMap.find( idDataGroup );
   }
}

//******************************************************************************
BFCBO::FieldInfo * BFCBO::getFieldInfoPointer( const BFFieldId& idField, const BFDataGroupId& idDataGroup, bool useParentGroups ) const
{
   EXECHISTI( I_( "getFieldInfoPointer( const BFFieldId &, const BFDataGroupId &, bool )" ) );
   FIELD_MAP_CONST_ITER  fieldIter;

   fieldIter = _fieldMap.find( BFFieldKey( isVersionable() ? idDataGroup : BF::HOST, idField ));
   if( false == useParentGroups ||
       false == isVersionable() )
   {
      if( fieldIter == _fieldMap.end( ) )
      {
         return(NULL);
      }
      else
      {
         return( *fieldIter ).second;
      }
   }

   METAGROUP_MAP_ITER groupIter;
   BFDataGroupId idWorkingDataGroup = idDataGroup;
   while( fieldIter == _fieldMap.end( ) )
   {
      if( idWorkingDataGroup == BF::HOST ) //all fields must be in hostMap
      {
         return(NULL);
      }
      else //finding field in parent group interim map
      {
         ( const_cast<BFCBO *>( this ))->findDataGroup( groupIter, idWorkingDataGroup );
         idWorkingDataGroup = ( *groupIter ).second->getParentDataGroupId();
         fieldIter = _fieldMap.find( BFFieldKey( idWorkingDataGroup , idField ));
      }
   }

   return( *fieldIter ).second;

}

//******************************************************************************
bool BFCBO::isDummy( const BFAbstractCBO::OBJECT_MAP_CONST_ITER & iter ) const
{
   bool retVal = true;

   if( !isList( ) )
      retVal = false;                                          // non lists cannot have dummy items
   else if( ( *iter ).first.getActivity() != OBJ_ACTIVITY_ADDED )
      retVal = false;                                          // in order to be dummy an item must be added
   else if( ( *iter ).second->getStateFlags() & NO_BASE_DELETE )
      retVal = false;                                          // in order to be dummy an item must be owned
   else if( !( *iter ).second->getInstance() )
      retVal = false;                                          //a dummy item should have an instance
   else if( ( *iter ).second->getInstance()->getNonDummyFlag( ) )
      retVal = false;                                          //list elements can be marked as non dummy using NON_DUMMY flag
   else if( ( *iter ).second->getInstance()->isUpdated( false ) )
      retVal = false;                                          //if an object has field updates it is not dummy
   return(retVal);
}

//******************************************************************************
BFCBO& BFCBO::operator=( const BFCBO& copy )
{

   return(*this);
}

//******************************************************************************
BFCBO::FieldInfo * BFCBO::prepareFieldInfoPointer( const BFFieldId& idField, const BFDataGroupId& idDataGroup )
//returns a field info for this groupId if it does not exist it will create one
{
   FIELD_MAP_ITER  fieldIter;

   FieldInfo * pFieldInfo = getFieldInfoPointer( idField, isVersionable() ? idDataGroup : BF::HOST );

   if( pFieldInfo != NULL )
   {
      if( pFieldInfo->getDataGroupId() != idDataGroup )
      {
         FieldInfo* pNew = new FieldInfo( idDataGroup );
         DString strValue;
         BFCBO::getField( idField, strValue, idDataGroup, false );
         pNew->makeLike( pFieldInfo, strValue );
         _fieldMap.insert( FIELD_MAP::value_type( BFFieldKey( idDataGroup, idField ), pNew ));
         return( pNew );

      }
   }
   else // fields that are not in Host map must be read only
   {
      return(NULL);
   }

   return(pFieldInfo);
}

//******************************************************************************
BFProperties* BFCBO::prepareFieldProperties( const BFFieldId& idField, const BFDataGroupId& idDataGroup )
{
   FieldInfo * pFieldInfo = prepareFieldInfoPointer( idField, idDataGroup );
   if( pFieldInfo )
   {
      pFieldInfo->initFieldProperties( idField );
   }
   else
   {
      assert( 0 );
      return( NULL );
   }

   return( pFieldInfo->getFieldProperties() );
}

//******************************************************************************
void BFCBO::setFieldInvalid( const BFFieldId& idField, const BFDataGroupId& idDataGroup )
{
   FieldInfo * pFieldInfo = prepareFieldInfoPointer( idField, isVersionable() ? idDataGroup : BF::HOST );
   if( pFieldInfo != NULL )
   {
      pFieldInfo->setStateFlag( UPDATED );
      pFieldInfo->clearStateFlag( VALID );
   }

   setCrossEditInvalid( idField, isVersionable() ? idDataGroup : BF::HOST );
}
//******************************************************************************
void BFCBO::getFieldConditionVector( const BFFieldId& idField, const BFDataGroupId& idDataGroup, CONDITIONVECTOR*& pCondVect )
{
   FieldInfo * pFieldInfo = prepareFieldInfoPointer( idField, isVersionable() ? idDataGroup : BF::HOST );

   pCondVect = pFieldInfo->getConditionVector();
}
//******************************************************************************
void BFCBO::setFieldConditionVector( const BFFieldId& idField, const BFDataGroupId& idDataGroup, CONDITIONVECTOR* pCondVect )
{
   FieldInfo * pFieldInfo = prepareFieldInfoPointer( idField, idDataGroup );
   pFieldInfo->setConditionVector( pCondVect );
}
//*******************************************************************************
bool BFCBO::hasFieldsUpdateForGroup( long lGroup ) const
{
   for( FIELD_MAP_CONST_ITER fieldIter = _fieldMap.begin( ); fieldIter != _fieldMap.end( ); ++fieldIter )
   {
      FieldInfo* pFI = ( *fieldIter ).second;
      if( pFI->checkStateFlag( UPDATED ) && 
          !(pFI->checkStateFlag( CALCULATED_FIELD ) ) &&
          ( *fieldIter ).first.getDataGroupId() == BF::HOST && 
          pFI->checkGroupFlag( lGroup ) )
      {
         return( true );
      }
   }

   return( false );
}

//******************************************************************************
void BFCBO::addBFCondition() const
{
   MAKEFRAMEAUTOPROMOTE2( CND::BFBASE_CONDITION,
                          CLASSNAME,
                          I_( "addBFCondition(  )" ) );
   SEVERITY sevRtn;
   sevRtn = _lastrequestCondition->getSeverity();
   if( sevRtn > WARNING )
   {
      MYFRAME()->addCondition ( new Condition(*_lastrequestCondition) );
   }
   _setCondition = false;
}

//*****************************************************************************
SEVERITY BFCBO::revalidateField( const BFFieldId& idField,
                                 const BFDataGroupId& idDataGroup )
{
   DString strValue;
   getField( idField, strValue, isVersionable() ? idDataGroup : BF::HOST );
   setValidFlag( idField, isVersionable() ? idDataGroup : BF::HOST, false );
   return(validateField( idField, strValue, isVersionable() ? idDataGroup : BF::HOST ));
}

//******************************************************************************
bool BFCBO::isObjectDirty (const BFDataGroupId &idDataGroup)
{
   bool bIsDirty (false);

   for (FIELD_MAP_CONST_ITER fieldIter = _fieldMap.begin (); 
        fieldIter != _fieldMap.end( ); 
        ++fieldIter)
   {
      const BFFieldKey& rKey = (*fieldIter).first;
      FieldInfo* pFI = (*fieldIter).second;
      
      if ( pFI->checkStateFlag (UPDATED) && 
           !(pFI->checkStateFlag (CALCULATED_FIELD)) &&
           rKey.getDataGroupId() == idDataGroup)
      {
         DString oldValue,
            newValue (*pFI->getStrValue ());
         
         getFieldBeforeImage (rKey.getFieldId(), oldValue, false);         
         newValue.stripTrailing ();
         oldValue.stripTrailing ();
         bIsDirty = newValue != oldValue;
         if (bIsDirty)
         {
            break;
         }
      }
   }
   return bIsDirty;
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/core/bfcbo/bfcbo.cpp-arc  $
//
//   Rev 1.60   May 29 2012 11:26:30   if991250
//support for cleaning the BFPropertyRepository on language change
//
//   Rev 1.59   Jan 04 2011 10:19:30   purdyech
//Tweaked logging message
//
//   Rev 1.58   Dec 17 2010 06:03:10   purdyech
//Improved logging for SSBG Performance analysis
//
//   Rev 1.57   Nov 11 2009 15:44:10   popescu
//Static Data project  - added isObjectDirty
//
//   Rev 1.56   Nov 11 2009 09:55:14   popescu
//Static Data project  - added isObjectDirty
//
//   Rev 1.55   05 May 2009 10:18:24   popescu
//Added support for drop down comboxes. The value typed in is appended to the subst set.
//
//   Rev 1.54   Feb 20 2009 14:47:50   purdyech
//ZTS Revision 6
//


//   Rev 1.53   08 Oct 2008 11:08:56   popescu


//Incident  1190617 - set asynch done to true if Desktop works on stub mode and asynch calls to the back-end are made


//


//   Rev 1.52   24 Jul 2008 12:03:42   popescu


//Incident  1190617 - added flag/method that notifies when an asynch retrieve call is done


//


//   Rev 1.51   Apr 18 2006 11:15:42   popescu


//Partially back-out fix for 562038 - BPServer memory leaks 


//


//   Rev 1.50   Feb 06 2006 09:36:34   FENGYONG


//small change - memery leak


//


//   Rev 1.49   Apr 22 2005 17:12:08   Fengyong


//#Incident 281621 - add field name to api error message field is required


//


//   Rev 1.48   Dec 09 2004 15:18:16   purdyech


//PET910 - Revert Cross-Edit processing to previous behaviour


//


//   Rev 1.47   Dec 07 2004 09:06:06   purdyech


//PET910 - Updated MAKEFRAMEAUTOPROMOTE2 statements for each function which has one.  (per Serban's request)


//


//   Rev 1.46   Nov 19 2004 10:47:42   PURDYECH


//PET910 - Problems uncovered by use of optimization code.


//


//   Rev 1.45   Nov 15 2004 10:43:44   PURDYECH


//Sync 1.43.1.0 back to trunk.


//
//   Rev 1.44   Oct 22 2004 08:53:48   PURDYECH
//PET910 - .NET Conversion Fixes
//
//   Rev 1.43   May 28 2004 14:10:10   PURDYECH
//Added an assert to make sure that a field is updateable when setField is called.  This may cause problems?
//
//   Rev 1.42   Mar 05 2004 13:27:20   SMITHDAV
//Make changes to support new ElementWriter semantics.
//
//   Rev 1.41   Feb 23 2004 11:18:14   PURDYECH
//Get rid of some EXECHIST2 statements
//
//   Rev 1.40   Feb 18 2004 15:11:38   PURDYECH
//Added EXECHIST macros to execution history tracking
//
//   Rev 1.39   Feb 13 2004 09:31:46   PURDYECH
//Silly little typo ... grrrr!
//
//   Rev 1.38   Feb 03 2004 08:53:08   PURDYECH
//Added isVersionable() and setVersionable() to allow a CBO to be marked as non-updateable.
//
//   Rev 1.37   Oct 01 2003 16:51:40   PURDYECH
//Added function resetObjectKey to change the key of an entry in the object map.
//
//   Rev 1.36   Sep 09 2003 15:25:18   PURDYECH
//Sync 1.34.1.1 back to trunk
//
//   Rev 1.35   Aug 12 2003 10:07:56   PURDYECH
//Added new logging method (bf::log::...)
//
//   Rev 1.34   May 29 2003 10:00:58   PURDYECH
//PTS 10011013 - Added condition ERR_FIELD_VALUE_INVALID_GUI.  This condition is a duplicate of ERR_FIELD_VALUE_INVALID except that it includes the name of field.  
//
//   Rev 1.33   May 20 2003 10:48:28   PURDYECH
//PTS 10016972.  setValidField() and setUpdatedField() (deprecated names for setFieldValid and setFieldUpdated) were using getFieldInfoPointer() instead of prepareFieldInfoPointer() so no new entry was being created for a new datagroup.
//
//   Rev 1.32   May 08 2003 15:31:44   PURDYECH
//Added ability to force a delete of a contained object.
//
//   Rev 1.31   May 01 2003 10:47:54   PURDYECH
//Made BFCBOEvent an inner class of BFCBO.
//Added dump() functions for debugging
//
//   Rev 1.30   Apr 30 2003 09:05:28   PURDYECH
//Sync 1.29.1.1 back to trunk
// 
//    Rev 1.29.1.1   Apr 15 2003 14:01:10   PURDYECH
// Documentation fixes.  Signature changes.
// 
//    Rev 1.29.1.0   Apr 11 2003 18:03:40   PURDYECH
// temp serialize fixes for KOVACSRO.
// 
//    Rev 1.29   Apr 03 2003 09:23:06   PURDYECH
// Field Properties were not getting propogated properly during setField* methods.
// 
//    Rev 1.28   Apr 02 2003 13:19:10   PURDYECH
// Explicitly dereference iterators to make debugging easier.
// Revert BFCBO::reset logic back to revision 1.26
// Remove 'memory leak' fix in BFCBO::reset and BFCBO::rollbackDataGroup due to lack of communication between objectMaps which contain references to the same object.
// 
//    Rev 1.27   Mar 14 2003 08:52:06   PURDYECH
// Added serialize() support for FAST.  It was all there idea!
// Also, fixed a memory leak in reset() (thanks to KOVACSRO)
// 
//    Rev 1.26   Mar 12 2003 09:07:16   PURDYECH
// Change BFCBOGuard to use new syntax for boost overrides.
// 
//    Rev 1.25   Mar 12 2003 09:05:34   PURDYECH
// Added isFieldRequired and isFieldValid.
// Added setFieldValid
// Restored get/setFieldGroupFlags
// 
//    Rev 1.24   Feb 26 2003 09:41:22   PURDYECH
// Remove updateLevel 
// 
//    Rev 1.23   Feb 12 2003 14:13:30   PURDYECH
// prepareFieldInfoPointer was returning the original pointer when a new FieldInfo object was constructed.
// 
//    Rev 1.22   Feb 07 2003 10:44:28   PURDYECH
// FieldInfo is now encapsulated properly.
// 
//    Rev 1.21   Jan 14 2003 11:03:04   PURDYECH
// DataGroupid parentage knowledge
// 
//    Rev 1.20   Jan 06 2003 16:40:06   PURDYECH
// BFDataGroupId changeover
// 
//    Rev 1.18   Nov 14 2002 10:48:54   SMITHDAV
// Sync-up from old source database.
// 
//    Rev 1.17   Oct 09 2002 17:40:00   PURDYECH
// New PVCS Database
// 
//    Rev 1.16   Sep 17 2002 10:56:14   SMITHDAV
// Remove unused functions.
// 
//    Rev 1.15   Sep 03 2002 11:05:02   PURDYECH
// Further BFFieldId fixes
// 
//    Rev 1.14   Aug 29 2002 12:51:06   SMITHDAV
// ClientLocale and typed field changes.
// 
//    Rev 1.13   Aug 15 2002 11:19:24   PURDYECH
// Fix problem with fields with warnings in processCrossEdit 
// 
//    Rev 1.12   Jul 22 2002 15:58:08   HSUCHIN
// bug fix for format/unformat field again. 
// 
//    Rev 1.11   Jul 19 2002 14:44:44   HSUCHIN
// bug fix to strip trailing spaces in the getField method.
// 
//    Rev 1.10   Jul 10 2002 13:56:42   PURDYECH
// Use custom substitution list in getFieldBeforeImage logic in getField
// 
//    Rev 1.9   Jul 05 2002 11:43:58   PURDYECH
// Infrastructure Fixup ... no more ICU!
// 
//    Rev 1.8   Jun 17 2002 11:56:30   PURDYECH
// Small performance improvement in CommitDataGroup
// 
//    Rev 1.7   Jun 12 2002 16:14:22   PURDYECH
// InitWithDefaultValues was doing a superfluous unformatField.
// formatField/unformatField should call BFDataField::formatField/unformatField if the BFProperties object couldn't format/unformat the value.
// 
//    Rev 1.6   Jun 08 2002 13:38:12   YINGBAOL
// fix FormatField
// 
//    Rev 1.5   Jun 05 2002 16:25:40   PURDYECH
// FormatField/UnformatField changes
// 
//    Rev 1.4   24 May 2002 12:00:04   KOVACSRO
// checkLocale before doPresetField.
// 
//    Rev 1.3   May 24 2002 11:37:42   PURDYECH
// Changed signature of doPreSetField to include the original formatted state and the ClientLocale
// Applied some fixes which got lost during the BFBase conversion.
// 
//    Rev 1.2   22 May 2002 17:54:16   PURDYECH
// BFData Implementation
// 
//    Rev 1.1   22 Mar 2002 15:13:56   PURDYECH
// Removed compile-time "including..." message
// Use #pragma once as include guard
// Include files with lower-case only names


