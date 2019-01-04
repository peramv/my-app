#include "stdafx.h"
#include "bfdata.hpp"
#include "bfdatafieldfactory.hpp"
#include "bfdatafielditer.hpp"
#include "bfdatafieldexists.hpp"
#include "bfmask.hpp"

class NullDataImpl : public BFDataImpl
{
public:
   NullDataImpl()
   : BFDataImpl( 0 )
   {}

   virtual unsigned long getDefinedByteLength() const { return( 0 );}
protected:
   virtual const BFDataField* getElementByIndex(unsigned int idx) const {
      return( NULL );
   }
   virtual BFDataImpl* clone() {
      return( new NullDataImpl );
   }
   virtual BFDataField* getElement(const BFFieldId& id) {
      return( NULL );
   }
   virtual BFDataField* getElementByIndex(unsigned int idx) {
      return( NULL );
   }
   virtual unsigned long getLargestDefinedField() const { return( 0 );}
   virtual const BFDataField* getElement(const BFFieldId& id) const {
      return( NULL );
   }
   virtual bool exists( const BFFieldId& id ) const { return( false );}
};


namespace
{
   static const DString SEPARATOR_CHAR = I_("=");
   static const DString TERMINATOR_CHAR = I_(";");
   static const DString EOL_CHAR = I_("\n");
}

const DString BFData::EMPTY_STRING( I_("") );

BFDataImplFactory* BFData::s_pImplFactory_ = NULL;
BFDataFieldExists* BFData::s_pExists_ = NULL;


void BFData::setImplFactory( BFDataImplFactory* pImplFactory )
{
//   delete s_pImplFactory_;
   s_pImplFactory_ = pImplFactory;
}

BFDataImplFactory* BFData::getImplFactory( void )
{
   return(s_pImplFactory_);
}

void BFData::setExistsObject( BFDataFieldExists* pExists )
{
//   delete s_pImplFactory_;
   s_pExists_ = pExists;
}

BFDataFieldExists* BFData::getExistsObject( void )
{
   return(s_pExists_);
}

BFData::BFData()
: pExtraFields_( NULL )
, pRepeats_( NULL )
, pImpl_( NULL )
{
   //assert( pImpl_ != NULL );
   pImpl_ = new NullDataImpl;
}

BFData::BFData( const BFDataId& id )
: pExtraFields_( NULL )
, pRepeats_( NULL )
, pImpl_( NULL )
{
   pImpl_ = s_pImplFactory_->createImplementer( id );
}

BFData::BFData( const BFData& rhs )
: pExtraFields_( NULL )
, pRepeats_( NULL )
, pImpl_( NULL )
{
   *this = rhs;
}

BFData & BFData::operator= ( const BFData &rhs )
{
   // blank out existing data
   delete pImpl_;
   pImpl_ = NULL;
   removeAllRepeats();
   removeExtraFields();

   // copy the implementation object
   pImpl_ = rhs.pImpl_->clone();


   // copy the right hand side repeats
   if( NULL != rhs.pRepeats_ )
   {
      for( RepeatVector_Iter iter = rhs.pRepeats_->begin();
         iter != rhs.pRepeats_->end();
         ++iter )
      {
         addRepeat( *(*iter) );
      }
   }

   // copy the 'extra' fields
   if( NULL != rhs.pExtraFields_ )
   {
      for( ExtraFieldsMap_Iter iter = rhs.pExtraFields_->begin();
         iter != rhs.pExtraFields_->end();
         ++iter )
      {
         addElement( *((*iter).second) );
      }
   }

   return( *this );
}



BFData::~BFData()
{
   removeAllRepeats();
   removeExtraFields();
   delete pImpl_;
}

void BFData::removeExtraFields()
{
   // remove the "extra" fields
   if( NULL != pExtraFields_ )
   {
      for( ExtraFieldsMap_Iter iter = pExtraFields_->begin();
         iter != pExtraFields_->end();
         )
      {
         delete (*iter).second;
         pExtraFields_->erase( iter++ );
      }
      delete pExtraFields_;
      pExtraFields_ = NULL;
   }
}

void BFData::reset()
{
   removeAllRepeats();
   removeExtraFields();
   const BFDataId& id = pImpl_->getId();
   if( id.getId() != 0 )
   {
      // only delete/recreate if the implementer is not the NullDataImpl object
      delete pImpl_;
      pImpl_ = s_pImplFactory_->createImplementer( id );
   }
}

BFData&
BFData::operator[]( unsigned int index )
{
   if( NULL != pRepeats_ && index < pRepeats_->size() )
   {
      return( *((*pRepeats_)[index]) );
   }
   BF_THROW( BFDataRepeatNotFoundException );
}

bool
BFData::addRepeat( const BFData& newRepeat )
{
   if( pRepeats_ == NULL )
   {
      pRepeats_ = new RepeatVector();
   }
   BFData* p = new BFData( newRepeat );
   pRepeats_->push_back( p );
   return( true );
}

bool
BFData::exists( const BFFieldId& id ) const
{
   bool bRc = pImpl_->exists( id );
   if( false == bRc )
   {
      // it's not part of the BFData object's static definition
      // look in the Extra Fields
      if( NULL != pExtraFields_ )
      {
         ExtraFieldsMap_Iter iter = pExtraFields_->find( id );
         if( iter != pExtraFields_->end() )
         {
            return( true );
         }
      }
      return( false );
   }
   return( true );
}

bool
BFData::exists( const DString& componentName ) const
{
   if( componentName == I_("Repeat_Record") )
   {
      assert( pImpl_ != NULL );
      if( pImpl_->getRepeatId() != 0 ) return( true );
      return( false );
   }
   const BFFieldId* pID = BFFieldId::_getId( componentName );
   if( NULL != pID )
   {
      return( exists(*pID) );
   }

   return( false );
}

bool
BFData::exists( const BFDataId& idData, const BFFieldId& idField )
{
   if( NULL != getExistsObject() )
   {
      return(getExistsObject()->exists( idData, idField ));
   }
   return( false );
}

void  BFData::getAllValues( DString &idiString,
                            bool bInsertEOLs /*= false*/,
                            bool bUsePropertiesOrder /*= false*/,
                            unsigned long flags /*= 0L*/ ) const
{

   DString tmpStr;

   idiString.erase();
   unsigned long cFields = pImpl_->getFieldCount();

   const ClientLocale& rLocale = ClientLocaleContext::get();

   for( unsigned long iField = 0;  iField < cFields;  ++iField )
   {
      const BFDataField* pDF = pImpl_->getElementByIndex( iField );
//CP20030410      const BFDataFieldProperties* pProps = pDF->getProperties();
      const BFFieldId& idField = pDF->getId();
      idiString.append( idField.getName() );
      idiString.append( SEPARATOR_CHAR );
      // formatted means either use substitutes or use mask?
      idiString.append( pDF->get( tmpStr, ( flags & 3 ) != 0, rLocale, NULL ) );
      idiString.append( TERMINATOR_CHAR );
      if( bInsertEOLs )
      {
         idiString.append( EOL_CHAR );
      }
   }
   if( NULL != pExtraFields_ )
   {
      ExtraFieldsMap_Const_Iter it = pExtraFields_->begin();
      ExtraFieldsMap_Const_Iter itEnd = pExtraFields_->end();
      for( ; it != itEnd; ++it )
      {
         const BFDataField* pDF = (*it).second;
//CP20030410         const BFDataFieldProperties* pProps = pDF->getProperties();
         const BFFieldId& idField = pDF->getId();
         idiString.append( idField.getName() );
         idiString.append( SEPARATOR_CHAR );
         // formatted means either use substitutes or use mask?
         idiString.append( pDF->get( tmpStr, ( flags & 3 ) != 0, rLocale, NULL ) );
         idiString.append( TERMINATOR_CHAR );
         if( bInsertEOLs )
         {
            idiString.append( EOL_CHAR );
         }
      }
   }

   return;
}

unsigned long
BFData::getAsUnsignedCharBuffer( I_CHAR* pBuffer,
                                 unsigned long cbBuffer,
                                 const ClientLocale& rLocale ) const
{
   assert( NULL != pImpl_ );
   assert( cbBuffer > 0 );
   unsigned long cbTotalCopied = 0;
   unsigned long cbCopied = pImpl_->toBuffer( pBuffer, cbBuffer, rLocale );

   cbTotalCopied += cbCopied;

   // any repeats?  then get 'em
   if( NULL != pRepeats_ )
   {
      RepeatVector::const_iterator itRepeat = pRepeats_->begin();
      RepeatVector::const_iterator itRepeatEnd = pRepeats_->end();

      for( ; itRepeat != itRepeatEnd; ++itRepeat )
      {
         const BFData& dataRepeat = *(*itRepeat);
         cbCopied = dataRepeat.getAsUnsignedCharBuffer( pBuffer + cbTotalCopied, cbBuffer - cbTotalCopied, rLocale );
         cbTotalCopied += cbCopied;
      }
   }
   return( cbTotalCopied );
}

unsigned long BFData::setFromCharBuffer( const I_CHAR* pBuffer, 
                                         long cbBuffer,
                                         unsigned long cchFixed,
                                         unsigned long cRepeats,
                                         unsigned long cchRepeat )
{
   if( NULL != pExtraFields_ )
   {
      for( ExtraFieldsMap_Iter iter = pExtraFields_->begin();
         iter != pExtraFields_->end();
         )
      {
         delete (*iter).second;
         pExtraFields_->erase( iter++ );
      }
      delete pExtraFields_;
      pExtraFields_ = NULL;
   }
   removeAllRepeats();

   assert( NULL != pImpl_ );
   if( cbBuffer == -1 )
   {
      cbBuffer = i_strlen( pBuffer );
   }
   unsigned long cbTotalCopied = 0;
   if( cbBuffer < cchFixed )
   {
      // if buffer isn't big enough to fully populate a record then do nothing
      return( 0 );
   }
   unsigned long cbCopied = pImpl_->fromBuffer( pBuffer, pBuffer + cchFixed, cbBuffer );

   cbTotalCopied += cbCopied;
   cbBuffer = ( cbBuffer < cbCopied ) ? 0 : cbBuffer - cbCopied;

   // any repeats?  then add 'em
   if( pImpl_->isRepeatable() && cbBuffer != 0 )
   {
      const BFDataId& idRepeat = pImpl_->getRepeatId();
      BFData dataRepeat( idRepeat );

      if( cchRepeat == -1 || cchRepeat == 0 )
      {
         cchRepeat = dataRepeat.getTotalMaxByteLength() / sizeof( I_CHAR );
      }
      while( cbBuffer >= cchRepeat )
      {
         cbCopied = dataRepeat.setFromCharBuffer( pBuffer + cbTotalCopied, 
                                                  cbBuffer, 
                                                  cchRepeat, 
                                                  0,
                                                  0 );
         cbBuffer = ( cbBuffer < cbCopied ) ? 0 : cbBuffer - cbCopied;
         cbTotalCopied += cbCopied;

         addRepeat( dataRepeat );
      }
   }
   return( cbTotalCopied );
}

const BFData &
BFData::getData( unsigned long id ) const
{
   if( id == pImpl_->getRepeatId() && id != 0 )
   {
      if( getRepeatCount() > 0 )
      {
         return( getRepeat(0) );
      }
   }
   BF_THROW( BFDataRepeatNotFoundException );
}



const BFDataFieldProperties *
BFData::getElementProperties( const BFFieldId& id ) const
{
   const BFDataField* pDF = _getElement(id);
   if( NULL != pDF )
   {
      return(pDF->getProperties());
   }
   return( NULL );
}

const BFDataFieldProperties *
BFData::getElementProperties( const DString& name ) const
{
   const BFFieldId* pID = BFFieldId::_getId( name );
   if( NULL != pID )
   {
      const BFDataField* pDF = _getElement( *pID );
      if( NULL != pDF )
      {
         return(pDF->getProperties());
      }
   }
   return( NULL );
}

DString &
BFData::getElementValue( const BFFieldId& id,
                         DString &outputValue,
                         unsigned long formatFlags /*= 0L*/,
                         const DString &i18nFormat /*= EMPTY_STRING*/ ) const
{
   const BFDataField* pDF = _getElement( id );
   if( NULL == pDF )
   {
      BF_THROW( BFDataFieldNotFoundException );
   }
   // formatted means either use substitutes or use mask?
   const ClientLocale& rLocale = ClientLocaleContext::get();
   pDF->get( outputValue, ( formatFlags & 3 ) != 0, rLocale, i18nFormat == EMPTY_STRING ? NULL : &BFMask( i18nFormat ) );
   return( outputValue );
}


DString&
BFData::getElementValue( const DString &name,
                         DString &outputValue,
                         unsigned long formatFlags /*= 0L*/,
                         const DString &i18nFormat /*= EMPTY_STRING*/ ) const
{
   const BFFieldId* pID = BFFieldId::_getId( name );
   if( NULL != pID )
   {
      return( getElementValue( *pID,outputValue, formatFlags, i18nFormat) );
   }
   BF_THROW( BFDataFieldNotFoundException );
}

DString
BFData::getElementValue( const DString &name,
                         unsigned long formatFlags /* = 0L*/,
                         const DString &i18nFormat /*= EMPTY_STRING */) const
{
   DString value;
   return( getElementValue( name, value, formatFlags, i18nFormat ) );
}

DString
BFData::getElementValue( const BFFieldId& id,
                         unsigned long formatFlags /*= 0L*/,
                         const DString &i18nFormat /*= EMPTY_STRING*/ ) const
{
   const BFDataField* df = _getElement( id );
   if( NULL == df )
   {
      BF_THROW( BFDataFieldNotFoundException );
   }
   // formatted means either use substitutes or use mask?
   const ClientLocale& rLocale = ClientLocaleContext::get();
   return( df->get( ( formatFlags & 3 ) != 0, rLocale, i18nFormat == EMPTY_STRING ? NULL : &BFMask( i18nFormat ) ) );
}

const BFDataField&
BFData::getElement( const BFFieldId& id ) const
{
   assert( NULL != pImpl_ );
   const BFDataField* pField = pImpl_->getElement( id );
   if( NULL != pField )
   {
      return( *pField );
   }
   ExtraFieldsMap::const_iterator it = getExtraFieldsMap().find( id );
   if( it != getExtraFieldsMap().end() )
   {
      return( *( (*it).second ) );
   }
   BF_THROW( BFDataFieldNotFoundException );
}

BFDataField&
BFData::getElement( const BFFieldId& id )
{
   assert( NULL != pImpl_ );
   BFDataField* pField = pImpl_->getElement( id );
   if( NULL != pField )
   {
      return( *pField );
   }
   ExtraFieldsMap::iterator it = getExtraFieldsMap().find( id );
   if( it != getExtraFieldsMap().end() )
   {
      return( *( (*it).second ) );
   }
   BF_THROW( BFDataFieldNotFoundException );
}

BFDataField* BFData::_getElement( const BFFieldId& id )
{
   assert( pImpl_ != NULL );
   BFDataField* pField = pImpl_->getElement( id );
   if( NULL == pField )
   {
      ExtraFieldsMap::iterator it = getExtraFieldsMap().find( id );
      if( it != getExtraFieldsMap().end() )
      {
         return( ( (*it).second ) );
      }
   }
   return( pField );
}

const BFDataField* BFData::_getElement( const BFFieldId& id ) const
{
   assert( pImpl_ != NULL );
   BFDataField* pField = pImpl_->getElement( id );
   if( NULL == pField )
   {
      ExtraFieldsMap::const_iterator it = getExtraFieldsMap().find( id );
      if( it != getExtraFieldsMap().end() )
      {
         return( ( (*it).second ) );
      }
   }
   return( pField );
}

const BFFieldId&
BFData::getFieldIdFromName( const DString &name ) const
{
   return( BFFieldId::getId( name ) );
}

const DString &
BFData::getFieldNameFromId( const BFFieldId& id ) const
{
   return( static_cast< const DString& >( id.getName() ) );
}

BFDataId BFData::getId() const
{
   assert( pImpl_ != NULL );
   return(pImpl_->getId());
}

unsigned long
BFData::getMaxLength() const
{
   assert( pImpl_ != NULL );
   long biggest = pImpl_->getLargestDefinedField();

   if( NULL != pExtraFields_ )
   {
      for( ExtraFieldsMap_Iter iter = pExtraFields_->begin();
         iter != pExtraFields_->end();
         ++iter )
      {
         BFDataField* pField = (*iter).second;
         if( pField->getProperties()->isVarText() ) {
            biggest = std::max( long(static_cast< BFVarTextField* >( pField )->getVarText().size()), biggest );
         } else {
            biggest = std::max( long(pField->getProperties()->getLength()), biggest );
         }
      }
   }

   return( biggest );
}

const DString& BFData::getName() const
{
   return( BFDataId::getName( getId() ) );
}

const BFData &
BFData::getRepeat( unsigned long repeatIndex ) const
{
   if( NULL != pRepeats_ && repeatIndex < pRepeats_->size() )
   {
      return( *( (*pRepeats_)[ repeatIndex ] ) );
   }
   BF_THROW( BFDataRepeatNotFoundException );
}

unsigned long
BFData::getRepeatCount() const
{
   if( NULL != pRepeats_ )
   {
      return( (unsigned long)pRepeats_->size() );
   }
   return( 0 );
}

bool BFData::getSelectedValues( BFData &data )
{
   bool bAllOK = true;
   DString tmpStr;
   BFDataFieldIter dIter( *this, false );

   for( ;dIter;++dIter )
   {
      BFDataField& fld = dIter();
      if( data.exists( fld.getId() ) )
      {
         data.setElementValue( fld );
      }
      else
      {
         bAllOK = false;
      }
   }

   // now add 'extra' fields
   if( NULL != pExtraFields_ )
   {
      for( ExtraFieldsMap_Iter iter = pExtraFields_->begin();
         iter != pExtraFields_->end();
         ++iter )
      {
         BFDataField* pField = (*iter).second;
         data.setElementValue( *pField );
      }
   }

   return(bAllOK);
}

unsigned long
BFData::getTotalMaxByteLength() const
{
   assert( pImpl_ != NULL );

   unsigned long maxSize = pImpl_->getDefinedByteLength();

   if( NULL != pExtraFields_ )
   {
      for( ExtraFieldsMap_Iter iter = pExtraFields_->begin();
         iter != pExtraFields_->end();
         ++iter )
      {
         BFDataField* pField = (*iter).second;
         if( pField->getProperties()->isVarText() ) {
            maxSize += static_cast< BFVarTextField* >( pField )->getVarText().size();
         } else {
            maxSize += pField->getProperties()->getLength();
         }
      }
   }

   // add the length of any repeats we may have.  If we have no repeats then assume that
   // we have none.
   if( pImpl_->isRepeatable() )
   {
      if( NULL != pRepeats_ )
      {
         RepeatVector::const_iterator it = pRepeats_->begin();
         RepeatVector::const_iterator itEnd = pRepeats_->end();
         for( ; it != itEnd; ++it )
         {
            maxSize += (*it)->getTotalMaxByteLength();
         }
      }
   }

   return( maxSize );
}

bool
BFData::isDefault( const BFFieldId& id ) const
{
   const BFDataField& df = getElement( id );
   return( df.isDefault( ClientLocaleContext::get() ) );
}

bool
BFData::isDefault( const DString &name ) const
{
   const BFFieldId& id = BFFieldId::getId( name );
   return( isDefault( id ) );
}


bool
BFData::isDefault() const
{
   BFConstDataFieldIter iter( *this, true );
   for( ;iter;++iter )
   {
      const BFDataField& fld = iter();
      if( false == fld.isDefault( ClientLocaleContext::get() ) )
      {
         return( false );
      }
   }
   return( true );
}

void
BFData::removeAllRepeats()
{
   if( NULL != pRepeats_ )
   {
      while( pRepeats_->size() != 0 )
      {
         BFData* p = pRepeats_->back();
         delete p;
         pRepeats_->pop_back();
      }
      delete pRepeats_;
      pRepeats_ = NULL;
   }
}

bool
BFData::removeRepeat( unsigned long removeAt )
{
   if( NULL != pRepeats_ )
   {
      if( pRepeats_->size() > removeAt )
      {
         delete (*pRepeats_)[ removeAt ];
         pRepeats_->erase( pRepeats_->begin() + removeAt );
         return( true );
      }
   }
   return( false );
}

void
BFData::resetValue( )
{
   // ignore ClientLocale!
   // set all fields, including appended ones, to their default value
   BFDataFieldIter iter( *this, true );
   for( ;iter;++iter )
   {
      BFDataField& fld = iter();
      resetElementValue( fld.getId() );
   }
}

void
BFData::resetElementValue( const BFFieldId& id )
{
   BFDataField* pDF = _getElement( id );
   if( NULL != pDF )
   {
      pDF->reset();
   }
   else
   {
      ExtraFieldsMap& extraFieldsMap = getExtraFieldsMap();
      ExtraFieldsMap::iterator it = extraFieldsMap.find( id );
      if( it != extraFieldsMap.end() )
      {
         // reset it to the default value
         pDF = (*it).second;
         pDF->reset();
      }
      else
      {
         BF_THROW( BFDataFieldNotFoundException );
      }
   }
   return;
}

void
BFData::resetElementValue( const DString &componentName )
{
   const BFFieldId* pID = BFFieldId::_getId( componentName );
   if( NULL != pID )
   {
      resetElementValue( *pID );
   }
   else
   {
         BF_THROW( BFDataFieldNotFoundException );
   }
   return;
}

bool
BFData::setElementValue( const BFFieldId& id,
                         const DString &value,
                         EAPPEND_MODE eAppend,
                         bool bReserved /* ignored */,
                         const DString &i18nFormat /*= EMPTY_STRING*/)
{
   return( setElementValue( id, value, eAppend == EAPPEND_MODE::APPEND, bReserved, i18nFormat ) );
}

bool
BFData::setElementValue( const BFFieldId& id,
                         const DString &value ,
                         bool bAppendNew /*= false*/,
                         bool bReserved /* ignored */,
                         const DString &i18nFormat /*= EMPTY_STRING*/)
{
   bool bRc = true;
   BFDataField* pDF = _getElement( id );
   if( NULL != pDF )
   {
      pDF->set( value, bReserved, ClientLocaleContext::get() );
   }
   else
   {
      if( bAppendNew )
      {
         ExtraFieldsMap& extraFieldsMap = getExtraFieldsMap();
         ExtraFieldsMap::iterator it = extraFieldsMap.find( id );
         if( it == extraFieldsMap.end() )
         {
            addElement( id, value, bReserved );
         }
      }
      else
      {
         bRc = false;
      }
   }
   return( bRc );
}

bool
BFData::setElementValue( const DString& name,
                         const DString& value,
                         bool bAppendNew /*= false*/,
                         bool bReserved /* ignored */,
                         const DString &i18nFormat /*= EMPTY_STRING*/)
{
   // find field id from name in handy-dandy
   const BFFieldId* pID = BFFieldId::_getStaticId( name );
   if( NULL == pID && true == bAppendNew )
   {
      pID = BFFieldId::_getDynamicId( name );
   }
   if( NULL == pID )
   {
      return( false );
   }
   return( setElementValue( *pID, value, bAppendNew, bReserved, i18nFormat ) ); 
}

bool
BFData::setElementValue( const DString &name,
                         const DString &value,
                         EAPPEND_MODE eAppend,
                         bool bReserved /* ignored */,
                         const DString &i18nFormat /*= EMPTY_STRING*/)
{
   bool bRc = true;
   // find field id from name in handy-dandy
   const BFFieldId* pID = BFFieldId::_getStaticId( name );
   if( NULL != pID && EAPPEND_MODE::APPEND == eAppend )
   {
      pID = BFFieldId::_getDynamicId( name );
   }
   if( NULL == pID ) 
   {
      return( false );
   }
   return( setElementValue( *pID, value, eAppend, bReserved, i18nFormat) );
}

void
BFData::setRepeatCount( unsigned long repeatCount )
{
   if( NULL == pRepeats_ )
   {
      pRepeats_ = new RepeatVector();
   }
   pRepeats_->reserve( repeatCount );
}

bool
BFData::setValues( const DString &idiString,
                   bool appendNew /*= false*/,
                   bool ignoreOnNoAppend /*= true*/ )
{
   bool done = false;
   bool doesExist = true;
   bool allOK = true;
   bool matchesFound = false;

   int length = idiString.length();
   int start = 0;
   DString::size_type separatorPosition;
   DString::size_type terminatorPosition;
   DString key;
   DString value;

   while( !done )
   {
      if( start >= length - 1 )
      {
         return(allOK);
      }

      separatorPosition = idiString.find( SEPARATOR_CHAR, start );
      if( DString::npos == separatorPosition )
      {
         done = true;
      }
      else
      {
         // Extract the key & look for the next terminator
         key = strip( idiString.substr( start, separatorPosition - start ) );

         // Check if the key indicates a replacement but doesn't exist
         doesExist = exists( key );
         if( !doesExist  &&  !appendNew  &&  !ignoreOnNoAppend )
         {
            allOK = false;
         }

         terminatorPosition = idiString.find( TERMINATOR_CHAR,
                                              separatorPosition + 1 );

         if( DString::npos == terminatorPosition )
         {
            // Stop if a terminator was not found, but
            terminatorPosition = length;
            done = true;
         }

         // Extract the value & add it to the object
         value = strip( idiString.substr( separatorPosition + 1,
                                          terminatorPosition - separatorPosition - 1 ) );

         if( doesExist )
         {
            matchesFound = true;
            if( !setElementValue( key, value, EAPPEND_MODE::NO_APPEND, true ) )
            {
               allOK = false;
            }
         } 
         else 
         {
            // field does not exist.  Deal with ignoreOnNoAppend flag
            if( appendNew )
            {
               matchesFound = true;
               if( !setElementValue( key, value, EAPPEND_MODE::APPEND, true ) )
               {
                  allOK = false;
               }
            }
            else
            {
               if( !ignoreOnNoAppend )
               {
                  // don't append new fields, and don't ignore required appends.
                  allOK = false;
               }
            }
         }

         start = terminatorPosition + 1;
      }
   }

   if( !matchesFound )
   {
      return(false);
   }

   return(allOK);
}

bool
BFData::setValues( const BFData &data,
                   bool appendNew /*= false*/,
                   bool ignoreOnNoAppend /*= true*/ )
{
   BFDataFieldIter iter( *this, false );
   for( ;iter;++iter )
   {
      BFDataField& fld = iter();
      fld = data.getElement( fld.getId() );
   }
   return( true );
}

void
BFData::addElement( BFDataField &dataEl )
{
   BFDataField* pField = dataEl.clone();

   ExtraFieldsMap& extraFieldsMap = getExtraFieldsMap();
   ExtraFieldsMap_Iter iter = extraFieldsMap.find( dataEl.getId() );
   if( iter == extraFieldsMap.end() )
   {
      extraFieldsMap.insert( ExtraFieldsMap::value_type( dataEl.getId(), pField ) );
   }
   else
   {
      delete (*iter).second;
      extraFieldsMap[dataEl.getId()] = pField;
   }
}

void
BFData::addElement( const BFFieldId& id
                    , const DString& value
                    , bool bDisplayFormat )
{

   BFDataField* pField = NULL;
   if( id.isDynamic() )
   {
      pField = new BFVarTextField( static_cast< const BFVarTextFieldId& >( id ) );
   }
   else
   {
      pField = BFDataField::getFactory()->createField( id );
   }
   pField->set( value, bDisplayFormat, ClientLocaleContext::get() );

   ExtraFieldsMap& extraFieldsMap = getExtraFieldsMap();
   ExtraFieldsMap_Iter iter = extraFieldsMap.find( id );
   if( iter == extraFieldsMap.end() )
   {
      extraFieldsMap.insert( ExtraFieldsMap::value_type( id, pField ) );
   }
   else
   {
      delete (*iter).second;
      extraFieldsMap[id] = pField;
   }
}

unsigned int
BFData::getFieldCount() const
{
   assert( pImpl_ != NULL );
   return( pImpl_->getFieldCount() );
}


const BFDataField&
BFData::getElementByIndex( unsigned int idx ) const
{
   assert( pImpl_ != NULL );
   const BFDataField* pDF = pImpl_->getElementByIndex( idx );
   if( NULL != pDF )
   {
      return( *pDF );
   }
   BF_THROW( BFDataFieldNotFoundException );
}

BFDataField*
BFData::_getElementByIndex( unsigned int idx )
{
   assert( pImpl_ != NULL );
   return( pImpl_->getElementByIndex( idx ) );
}

const BFDataField*
BFData::_getElementByIndex( unsigned int idx ) const
{
   assert( pImpl_ != NULL );
   return( pImpl_->getElementByIndex( idx ) );
}

void BFData::commit( BFData* pTarget )
{
   const ClientLocale& rLocale = ClientLocaleContext::get();
   // commit ourself to the target BFData object
   BFDataFieldIter iter( *this, true );
   for( ;iter;++iter )
   {
      BFDataField& fld = iter();
      BFDataField& targetField = pTarget->getElement( fld.getId() );
      targetField.set( fld.get( false, rLocale, NULL ), false, rLocale );
   }
}

const BFDataId& BFData::getRepeatId() const
{
   assert( pImpl_ != NULL );
   return( pImpl_->getRepeatId() );
}

unsigned long BFData::getDefaultMarket()
{
   return( BFDataImpl::getDefaultMarket() );
}

unsigned long BFData::getDefaultClient()
{
   return( BFDataImpl::getDefaultClient() );
}

const DString& BFData::getDefaultLocale()
{
   return( BFDataImpl::getDefaultLocale() );
}



//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF Core/bfdata/bfdata.cpp-arc  $
// 
//    Rev 1.22   Apr 10 2003 10:45:30   PURDYECH
// Removed obsolete code.
// Use BFFieldId::getName() instead of BFDataFieldProperties::getName() to get field names
// 
//    Rev 1.21   Mar 14 2003 08:36:44   PURDYECH
// Added support for variable length fields and dynamic fieldIds.
// Removed 'extra string fiields' support as dynamic fieldIds allows arbitrary fields to be added to the 'extra fields'
// Fixed some parameter names (cosmetic)
// 
//    Rev 1.20   Mar 11 2003 10:00:22   PURDYECH
// Added precompiled header
// 
//    Rev 1.19   Feb 13 2003 09:49:04   PURDYECH
// Implement appendNew properly
// 
//    Rev 1.18   Nov 07 2002 14:18:52   PURDYECH
// in setFromCharBuffer() we must handle cases where the size of the input buffer is mismatched with the actual sizes.
// 
//    Rev 1.17   Nov 01 2002 15:02:40   PURDYECH
// In setFromCharBuffer() make sure that the size of the repeat object is not something silly like -1 or 0.  FAST views will sometimes pass back silly values like that.
// 
//    Rev 1.16   Oct 31 2002 10:10:40   PURDYECH
// Implement tighter checking for FAST style toBuffer and fromBuffer methods.
// 
//    Rev 1.15   Oct 30 2002 15:19:32   PURDYECH
// new signature for setCharFromBuffer().
// 
//    Rev 1.14   Oct 09 2002 17:40:26   PURDYECH
// New PVCS Database
// 
//    Rev 1.13   Aug 29 2002 12:49:08   PURDYECH
// ClientLocale corrections
// 
//    Rev 1.12   Jul 05 2002 11:55:40   PURDYECH
// Infra fixup
// 
//    Rev 1.11   Jun 17 2002 11:58:20   PURDYECH
// BFDataField flags have been removed (performance improvement).
// 
//    Rev 1.10   Jun 07 2002 12:26:50   PURDYECH
// reset() would fail if the Implementer was the NullDataImpl object.
// 
//    Rev 1.9   Jun 06 2002 17:14:36   PURDYECH
// added reset/remove methods to clean up object during assignment.
// 
//    Rev 1.8   Jun 05 2002 14:41:26   ROSIORUC
// CP - Fixed the "fixes" to the FAST stream handling
// 
//    Rev 1.7   May 30 2002 11:56:56   PURDYECH
// Made BFData::getAsUnsignedCharBuffer accept an I_CHAR, which is what it works with anyway.
// 
//    Rev 1.6   May 29 2002 15:33:42   PURDYECH
// Substitution sets weren't converting for formatted getElementValue calls.
// 
//    Rev 1.5   May 29 2002 15:26:32   PURDYECH
// Fixed a bug in setElementValue with respect to extra string field  appending.
// 
//    Rev 1.4   May 28 2002 12:15:22   PURDYECH
// BFData Implementation - Phase II
// 
//    Rev 1.2   May 23 2002 23:22:34   IVESPAUL
// Corrected repeat handling in setFromCharBuffer.
//
