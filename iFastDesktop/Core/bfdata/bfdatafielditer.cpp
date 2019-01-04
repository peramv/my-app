#include "stdafx.h"
#include "bfdatafielditer.hpp"

BFDataFieldIter::BFDataFieldIter( BFData& in, bool bIncludeAppended /*=true*/ )
: data_( in )
, iFixed_( 0 )
, bIncludeAppended_( bIncludeAppended )
, eFieldArea_( BFDataFieldIter::Fixed )
{
   reset();
}

BFDataFieldIter::~BFDataFieldIter()
{
}

void BFDataFieldIter::reset()
{
   eFieldArea_ = BFDataFieldIter::Fixed;
   iFixed_ = 0;
   if( bIncludeAppended_ )
   {
      if( NULL != data_.pExtraFields_ )
      {
         itExtraFields_ = data_.pExtraFields_->begin();
      }
//CP20030312      if( NULL != data_.pExtraStringFields_ )
//CP20030312      {
//CP20030312         itExtraStringFields_ = data_.pExtraStringFields_->begin();
//CP20030312      }
      if( data_.getFieldCount() == 0 )
      {
         // increment this iterator to get us out of the fixed area
         ++(*this);
      }
   }
   else
   {
      if( data_.getFieldCount() == 0 )
      {
         // we are not included appended fields, and we have no fields,
         // so put us at the end
         eFieldArea_ = BFDataFieldIter::AtEnd;
      }
   }
}

void BFDataFieldIter::operator++()
{
   bool bExtraBegin = false;
//CP20030312   bool bExtraStringsBegin = false;

   if( eFieldArea_ == BFDataFieldIter::Fixed )
   {
      ++iFixed_;
      if( iFixed_ >= data_.getFieldCount() )
      {
         eFieldArea_ = bIncludeAppended_ ? BFDataFieldIter::Extra : BFDataFieldIter::AtEnd;
         bExtraBegin = true;
      }
   }

   if( eFieldArea_ == BFDataFieldIter::Extra )
   {
      if( NULL != data_.pExtraFields_ &&                   // there are extra fields!
          itExtraFields_ != data_.pExtraFields_->end() )   // and we are not at the end of them
      {
         if( !bExtraBegin )
         {
            ++itExtraFields_;
         }
         if( data_.pExtraFields_->end() == itExtraFields_ ) // if we are at the end of them
         {
//CP20030312            bExtraStringsBegin = true;
            eFieldArea_ = BFDataFieldIter::AtEnd;           // done
         }
      }
      else
      {
//CP20030312         bExtraStringsBegin = true;
         eFieldArea_ = BFDataFieldIter::AtEnd;    // done
      }
   }

//CP20030312   if( eFieldArea_ == BFDataFieldIter::ExtraStrings )
//CP20030312   {
//CP20030312      //TODO: ExtraStrings are not stored as BFDataField objects, so we can't iterate them!
//CP20030312#ifdef EXTRA_STRINGS_TREATED_AS_BFDATAFIELD
//CP20030312      if( NULL != data_.pExtraStringFields_ &&
//CP20030312          itExtraStringFields_ != data_.pExtraStringFields_->end() )
//CP20030312      {
//CP20030312         if( !bExtraStringsBegin )
//CP20030312         {
//CP20030312            ++itExtraStringFields_;
//CP20030312         }
//CP20030312         if( data.pExtraStringFields_.end() == itExtraStringFields_ )
//CP20030312         {
//CP20030312            eFieldArea_ = BFDataFieldIter::AtEnd;
//CP20030312         }
//CP20030312      }
//CP20030312      else
//CP20030312      {
//CP20030312         eFieldArea_ = BFDataFieldIter::AtEnd;
//CP20030312      }
//CP20030312#else
//CP20030312      eFieldArea_ = BFDataFieldIter::AtEnd;
//CP20030312#endif
//CP20030312   }
}

BFDataField& BFDataFieldIter::operator()()
{
   switch( eFieldArea_ )
   {
      case BFDataFieldIter::Fixed: 
         if( iFixed_ < data_.getFieldCount() )
         {
            return( *data_._getElementByIndex( iFixed_ ) );
         }
         break;
      case BFDataFieldIter::Extra:
         {
            BFDataField* pDF = (*itExtraFields_).second;
            if( NULL != pDF )
            {
               return( *pDF );
            }
            BF_THROW( BFDataFieldNotFoundException );
         }
//CP20030312      case BFDataFieldIter::ExtraStrings:
//CP20030312         break;
   }
   BF_THROW( BFDataFieldNotFoundException );
}

BFDataFieldIter::operator int() const
{
   if( eFieldArea_ == BFDataFieldIter::AtEnd )
   {
      return( 0 );
   }
   return( 1 );
}


BFConstDataFieldIter::BFConstDataFieldIter( const BFData& in, bool bIncludeAppended /*=true*/ )
: data_( in )
, iFixed_( 0 )
, bIncludeAppended_( bIncludeAppended )
, eFieldArea_( BFConstDataFieldIter::Fixed )
{
   reset();
}

BFConstDataFieldIter::~BFConstDataFieldIter()
{
}

void BFConstDataFieldIter::reset()
{
   eFieldArea_ = BFConstDataFieldIter::Fixed;
   iFixed_ = 0;
   if( bIncludeAppended_ )
   {
      if( NULL != data_.pExtraFields_ )
      {
         itExtraFields_ = data_.pExtraFields_->begin();
      }
//CP20030312      if( NULL != data_.pExtraStringFields_ )
//CP20030312      {
//CP20030312         itExtraStringFields_ = data_.pExtraStringFields_->begin();
//CP20030312      }
      if( data_.getFieldCount() == 0 )
      {
         // increment this iterator to get us out of the fixed area
         ++(*this);
      }
   }
   else
   {
      if( data_.getFieldCount() == 0 )
      {
         // we are not included appended fields, and we have no fields,
         // so put us at the end
         eFieldArea_ = BFConstDataFieldIter::AtEnd;
      }
   }
}

void BFConstDataFieldIter::operator++()
{
   bool bExtraBegin = false;
//CP20030312   bool bExtraStringsBegin = false;

   if( eFieldArea_ == BFConstDataFieldIter::Fixed )
   {
      ++iFixed_;
      if( iFixed_ >= data_.getFieldCount() )
      {
         eFieldArea_ = bIncludeAppended_ ? BFConstDataFieldIter::Extra : BFConstDataFieldIter::AtEnd;
         bExtraBegin = true;
      }
   }

   if( eFieldArea_ == BFConstDataFieldIter::Extra )
   {
      if( NULL != data_.pExtraFields_ &&                   // there are extra fields!
          itExtraFields_ != data_.pExtraFields_->end() )   // and we are not at the end of them
      {
         if( !bExtraBegin )
         {
            ++itExtraFields_;
         }
         if( data_.pExtraFields_->end() == itExtraFields_ ) // if we are at the end of them
         {
//CP20030312            bExtraStringsBegin = true;
            eFieldArea_ = BFConstDataFieldIter::AtEnd;      // done
         }
      }
      else
      {
//CP20030312         bExtraStringsBegin = true;
         eFieldArea_ = BFConstDataFieldIter::AtEnd;         // done
      }
   }

//CP20030312   if( eFieldArea_ == BFConstDataFieldIter::ExtraStrings )
//CP20030312   {
//CP20030312      //TODO: ExtraStrings are not stored as BFDataField objects, so we can't iterate them!
//CP20030312#ifdef EXTRA_STRINGS_TREATED_AS_BFDATAFIELD
//CP20030312      if( NULL != data_.pExtraStringFields_ &&
//CP20030312          itExtraStringFields_ != data_.pExtraStringFields_->end() )
//CP20030312      {
//CP20030312         if( !bExtraStringsBegin )
//CP20030312         {
//CP20030312            ++itExtraStringFields_;
//CP20030312         }
//CP20030312         if( data.pExtraStringFields_.end() == itExtraStringFields_ )
//CP20030312         {
//CP20030312            eFieldArea_ = BFConstDataFieldIter::AtEnd;
//CP20030312         }
//CP20030312      }
//CP20030312      else
//CP20030312      {
//CP20030312         eFieldArea_ = BFConstDataFieldIter::AtEnd;
//CP20030312      }
//CP20030312#else
//CP20030312      eFieldArea_ = BFConstDataFieldIter::AtEnd;
//CP20030312#endif
//CP20030312   }
}

const BFDataField& BFConstDataFieldIter::operator()() const
{
   switch( eFieldArea_ )
   {
      case BFConstDataFieldIter::Fixed: 
         return( data_.getElementByIndex( iFixed_ ) );
      case BFConstDataFieldIter::Extra:
         {
            const BFDataField* pDF = (*itExtraFields_).second;
            if( NULL != pDF )
            {
               return( *pDF );
            }
            BF_THROW( BFDataFieldNotFoundException );
         }
//CP20030312      case BFConstDataFieldIter::ExtraStrings:
//CP20030312         break;
   }
   BF_THROW( BFDataFieldNotFoundException );
}

BFConstDataFieldIter::operator int() const
{
   if( eFieldArea_ == BFConstDataFieldIter::AtEnd )
   {
      return( 0 );
   }
   return( 1 );
}


