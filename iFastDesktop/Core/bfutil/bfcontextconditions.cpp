#include "stdafx.h"

#include <bfutil/bfcontextconditions.hpp>
#include <bfutil/bfguard.hpp>
#include <vector>

static const DString keyBFContextConditions( I_( "ContextConditions" ) );

BFContextConditions* BFContextConditions::get()
{
   BFExecutionContext* pContext = BFExecutionContext::get();

   BFContextConditions* pBFContextConditions = dynamic_cast< BFContextConditions* >( pContext->getObject( keyBFContextConditions ) );
   if( NULL == pBFContextConditions )
   {
      pBFContextConditions = new BFContextConditions();
      pContext->addObject( keyBFContextConditions, pBFContextConditions );
   }

   return( pBFContextConditions );
}

BFContextConditions::BFContextConditions()
{
}

BFContextConditions::~BFContextConditions()
{
   BFGuard g( cs_ );
   clear();
}

void BFContextConditions::add( const Condition* pCondition )
{
   BFGuard g( cs_ );
   vConditions_.push_back( new Condition( *pCondition ) );
}

void BFContextConditions::add( const CONDITIONVECTOR& rvConditions )
{
   BFGuard g( cs_ );
   CONDITIONVECTOR::const_iterator it = rvConditions.begin();
   for( ; rvConditions.end() != it; ++it )
   {
      vConditions_.push_back( new Condition( *(*it) ) );
   }
}

void BFContextConditions::clear()
{
   BFGuard g(cs_);
   CONDITIONVECTOR::iterator it = vConditions_.begin();
   for( ; vConditions_.end() != it; ++it )
   {
      delete (*it);
   }
   vConditions_.clear();
}

CONDITIONVECTOR BFContextConditions::getConditions() const 
{
   BFGuard g( cs_ );
   CONDITIONVECTOR vConditionsCopy;

   CONDITIONVECTOR::const_iterator it = vConditions_.begin();
   for( ; vConditions_.end() != it; ++it )
   {
      vConditionsCopy.push_back( new Condition( *(*it) ) );
   }
   return( vConditionsCopy );
}

