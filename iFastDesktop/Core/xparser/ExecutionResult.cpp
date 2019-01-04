#include "stdafx.h"
#include ".\executionresult.hpp"

void xp::ExecResult::incrementConditionCount( SEVERITY severity ) {
   switch ( severity ) {
      case CRITICAL_ERROR:
         ++criticalErrorCount_;
         break;
      case SEVERE_ERROR:
         ++severeErrorCount_;
         break;
      case WARNING:
         ++warningCount_;
         break;
      case INFORMATIONAL:
         ++informationalCount_;
         break;
      default:
         break;
   }
}

//*********************************************
xp::ProcessResult::ProcessResult( xp::ProcessAction action ) 
: action_()
{
   for ( int i=0; i < xp::CBO_ACTION_COUNT; i++ ) {
      cboActionCount_[i] = 0;
   }
}

