#include "stdafx.h"

#include "txnstats.hpp"
#include "BFExecutionContext.hpp"
#include "bfguard.hpp"
#include "elementwriter.hpp"

static const DString TxnStatsKey;

bool TxnStats::s_bAutoEnable = false;

//******************************************************************************
bool TxnStats::autoEnable( bool bAutoEnable )
{
   bool bOld = s_bAutoEnable;
   s_bAutoEnable = bAutoEnable;
   return( bOld );
}

//******************************************************************************
bool TxnStats::isEnabled() const
{
   return(_bEnabled);
}

//******************************************************************************
bool TxnStats::enable( bool bEnabled )
{
   bool bOrig = _bEnabled;
   _bEnabled = s_bAutoEnable == true ? true : bEnabled;
   return( bOrig );
}

//******************************************************************************
TxnStats* TxnStats::get()
{
   BFExecutionContext* pContext = BFExecutionContext::get();

   TxnStats* pTxnStats = dynamic_cast< TxnStats* >( pContext->getObject( TxnStatsKey ) );
   if( NULL == pTxnStats )
   {
      pTxnStats = new TxnStats();
      pContext->addObject( TxnStatsKey, pTxnStats );
   }

   return( pTxnStats );
}

//******************************************************************************
TxnStats::TxnStats()
: _bEnabled( s_bAutoEnable )
{
   BFFileTime createTime;
   BFFileTime exitTime;
   ::GetThreadTimes( ::GetCurrentThread(), createTime, exitTime, kernelTime_, userTime_ );
}

//******************************************************************************
TxnStats::~TxnStats()
{
   reset();
}

//******************************************************************************
void TxnStats::reset()
{
   BFGuard g( _cs );
   // clean out the element group map, and all of the element lists underlying them
   TXNSTATELEMGROUP_ITER itGroup;
   for( itGroup =  _mapElemGroup.begin();
      itGroup != _mapElemGroup.end();
      ++itGroup )
   {
      TXNSTATELEM_LIST* pElemList = (*itGroup).second;
      TXNSTATELEM_ITER itElem;
      for( itElem =  pElemList->begin();
         itElem != pElemList->end();
         ++itElem )
      {
         delete *itElem;
      }
      delete pElemList;
   }

   _mapElemGroup.clear();

   BFFileTime createTime;
   BFFileTime exitTime;
   ::GetThreadTimes( ::GetCurrentThread(), createTime, exitTime, kernelTime_, userTime_ );
}

//******************************************************************************
bool TxnStats::getThreadTimes( DWORD& msKernel, DWORD& msUser ) const
{
   BFFileTime createTime, exitTime, kernelTime, userTime;
   if( 0 == ::GetThreadTimes( ::GetCurrentThread(), createTime, exitTime, kernelTime, userTime ) )
      return( false );

   msKernel = ( (DWORD)(kernelTime - kernelTime_) ) / 10 / 1000;
   msUser = ( (DWORD)( userTime - userTime_ ) ) / 10 / 1000;

   return( true );
}

//******************************************************************************
void TxnStats::startTimeChop()
{
   startTime_.reset();
}

//******************************************************************************
DWORD TxnStats::endTimeChop()
{
   return( startTime_.elapsed() );
}

//******************************************************************************
DWORD TxnStats::timeSinceAccept() const
{
   return( acceptTime_.elapsed() );
}

//******************************************************************************
void TxnStats::resetAcceptTime()
{
   acceptTime_.reset();
}

//******************************************************************************
void TxnStats::addElementGroup( const DString& dstrGroup )
{
   BFGuard g( _cs );

   TXNSTATELEMGROUP_ITER itGroup = _mapElemGroup.find( dstrGroup );
   if( itGroup == _mapElemGroup.end() )
   {
      TXNSTATELEM_LIST* pElemList = new TXNSTATELEM_LIST;
      _mapElemGroup[ dstrGroup ] = pElemList;
   }
   return;
}

//******************************************************************************
void TxnStats::addElement( const DString& dstrGroup,
                           TxnStatElement* pElement )
{
   BFGuard g( _cs );

   TXNSTATELEM_LIST* pElemList = NULL;

   TXNSTATELEMGROUP_ITER itGroup = _mapElemGroup.find( dstrGroup );
   if( itGroup == _mapElemGroup.end() )
   {
      pElemList = new TXNSTATELEM_LIST;
      _mapElemGroup[ dstrGroup ] = pElemList;
   }
   else
   {
      pElemList = (*itGroup).second;
   }

   pElemList->push_back( pElement );

   return;
}

//******************************************************************************
const TXNSTATELEM_LIST& TxnStats::getElementGroup( const DString& dstrGroup )
{
   BFGuard g( _cs );

   TXNSTATELEMGROUP_ITER itGroup = _mapElemGroup.find( dstrGroup );
   if( itGroup != _mapElemGroup.end() )
   {
      return( *((*itGroup).second) );
   }
   throw( TxnStatsException() );
}

//******************************************************************************
DString TxnStats::getAsIDIString() const
{
   DString dstrIDI;

   BFGuard g( _cs );

   TXNSTATELEMGROUP_CONST_ITER itGroup;
   for( itGroup =  _mapElemGroup.begin();
      itGroup != _mapElemGroup.end();
      ++itGroup )
   {
      TXNSTATELEM_LIST* pElemList = (*itGroup).second;
      TXNSTATELEM_ITER itElem;
      for( itElem =  pElemList->begin();
         itElem != pElemList->end();
         ++itElem )
      {
         TxnStatElement* pElem = (*itElem);
         if( NULL != pElem )
         {
            dstrIDI += pElem->getAsIDIString();
         }
      }
   }
   return( dstrIDI );
}

//******************************************************************************
void TxnStats::writeXML( BFDocument& out ) const
{
   BFGuard g(_cs);

   TXNSTATELEMGROUP_CONST_ITER itGroup;
   for( itGroup =  _mapElemGroup.begin();
      itGroup != _mapElemGroup.end();
      ++itGroup )
   {
      ElementWriter ew( out, (*itGroup).first );

      TXNSTATELEM_LIST* pElemList = (*itGroup).second;
      TXNSTATELEM_ITER itElem;

      for( itElem =  pElemList->begin();
         itElem != pElemList->end();
         ++itElem )
      {
         TxnStatElement* pElem = (*itElem);

         if( NULL != pElem )
         {
            pElem->writeXML( out );
         }
      }

   }
}


//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF Core/bfutil/txnstats.cpp-arc  $
//
//   Rev 1.13   Oct 22 2004 09:01:22   PURDYECH
//PET910 - .NET Conversion Fixes
//
//   Rev 1.12   Mar 05 2004 13:27:28   SMITHDAV
//Make changes to support new ElementWriter semantics.
//
//   Rev 1.11   Mar 02 2004 10:56:02   SMITHDAV
//Change element writers to make them mor robust.
// 
//    Rev 1.10   Oct 09 2002 17:41:34   PURDYECH
// New PVCS Database
// 
//    Rev 1.9   Sep 19 2002 09:28:14   IVESPAUL
// Adapted the transaction stats to write results using XML ElementWriter.  Moved ElementAttribute and ElementWriter to BFUtil.
//
