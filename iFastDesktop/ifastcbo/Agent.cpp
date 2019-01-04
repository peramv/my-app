//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by International Financial.,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2003 by International Financial.
//
//
//******************************************************************************
//
// ^FILE   : Agent.cpp
// ^AUTHOR : 
// ^DATE   : Mar 04, 2003
//
// ^CLASS    : Agent
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "agent.hpp"
#include "errmsgruleslist.hpp"
#include "mgmtco.hpp"
#include <ifastdataimpl\dse_dstc0092_vwrepeat_record.hpp>

namespace
{
   const I_CHAR * const CLASSNAME = I_( "Agent" );   
   const I_CHAR * const YES = I_( "Y" );
}

namespace CND
{
	extern const long ERR_AGENT_INVALID_AS_OF_DATE;
	extern const long ERR_AGENT_NOT_EFFECTIVE;   
   extern const long AGENT_ERR_NASU_SLS_REP_LVL_NOT_MET;
   extern const long AGENT_WARN_NASU_SLS_REP_LVL_NOT_MET;
   extern const long AGENT_ERR_PURCHASE_SLS_REP_LVL_NOT_MET;
   extern const long AGENT_WARN_PURCHASE_SLS_REP_LVL_NOT_MET;
   extern const long AGENT_ERR_AGENT_NOT_ACTIVE;
}

//****************************************************************************
// Constructor
//****************************************************************************
Agent::Agent( BFAbstractCBO &parent )
: MFCanBFCbo( parent )
{
   TRACE_CONSTRUCTOR( CLASSNAME , NULL_STRING );
}

//****************************************************************************
// Destructor
//****************************************************************************
Agent::~Agent()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}     

//****************************************************************************
//Initializes the CBO
//@param const BFData& InstData - Data object to attach to AgentList.
//@returns SEVERITY
//****************************************************************************
SEVERITY Agent::init( const BFData& InstData )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );
   attachDataObject( const_cast<BFData&>(InstData), false, true );
   return(GETCURRENTHIGHESTSEVERITY());
}

//****************************************************************************
//Compares the date passed in with the effective and stop date of the Agent.
//Returns NO_CONDITION when the date passed in is within the effective and stop
//date range.
//@param const DString& dstAsOfDate - Date to compare to.
//       const BFDataGroupId& idDataGroup - current data group id.
//@returns SEVERITY - ERR_AGENT_INVALID_AS_OF_DATE - date is later than stop date
//                    ERR_AGENT_NOT_EFFECTIVE - date is before effective date.
//****************************************************************************
SEVERITY Agent::checkEffective( const DString& dstrAsOfDate, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "checkEffective" ) );
   DString dstrAgentStatus;
   getField ( ifds::AgentStat, dstrAgentStatus, idDataGroup, false );
   // If the AgentStat is Yes then it means the Agent is inactive.
   if ( dstrAgentStatus == YES ) {
      ADDCONDITIONFROMFILE( CND::AGENT_ERR_AGENT_NOT_ACTIVE );      
   } else {
      DString dstrEffectiveDate, dstrStopDate, idiStr;
      getField( ifds::StopDate, dstrStopDate, idDataGroup, false );
      getField( ifds::EffectiveDate, dstrEffectiveDate, idDataGroup, false );   
      if ( (DSTCommonFunctions::CompareDates( dstrStopDate,dstrAsOfDate) != DSTCommonFunctions::SECOND_EARLIER) ) {            
         getField( ifds::StopDate, dstrStopDate, idDataGroup, true );
         addIDITagValue( idiStr, I_("DATE"), dstrStopDate);
         ADDCONDITIONFROMFILEIDI( CND::ERR_AGENT_INVALID_AS_OF_DATE, idiStr );
      } else if ( (DSTCommonFunctions::CompareDates( dstrAsOfDate, dstrEffectiveDate ) == DSTCommonFunctions::FIRST_EARLIER) ) {
         getField( ifds::EffectiveDate, dstrEffectiveDate, idDataGroup, true );
         addIDITagValue( idiStr, I_("DATE"), dstrEffectiveDate);
         ADDCONDITIONFROMFILEIDI( CND::ERR_AGENT_NOT_EFFECTIVE, idiStr );            
      }
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//****************************************************************************
SEVERITY Agent::canPurchase( const BFDataGroupId& idDataGroup, bool bCheckLevel )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "canPurchase" ) );
   DString dstrRepLevel = NULL_STRING;
   getField ( ifds::RepLevel, dstrRepLevel, idDataGroup );
   double dRepLevel = DSTCommonFunctions::convertToDouble ( dstrRepLevel );
   if ( dRepLevel < 3 ) {
      DString dstrErrValue;
      ErrMsgRulesList* pErrMsgRulesList = NULL;
      getMgmtCo().getErrMsgRulesList( pErrMsgRulesList );
      pErrMsgRulesList->getEWIValue(I_("390"), idDataGroup, dstrErrValue );
      if( dstrErrValue == I_("E") ) {
         ADDCONDITIONFROMFILE( CND::AGENT_ERR_PURCHASE_SLS_REP_LVL_NOT_MET ); 
      } else if (dstrErrValue == I_("W") ) {
         ADDCONDITIONFROMFILE( CND::AGENT_WARN_PURCHASE_SLS_REP_LVL_NOT_MET ); 
      }
   }   
   return(GETCURRENTHIGHESTSEVERITY());
}

//****************************************************************************
SEVERITY Agent::canCreateAccount( const BFDataGroupId& idDataGroup, bool bCheckLevel )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "canPurchase" ) );
   DString dstrRepLevel = NULL_STRING;
   getField ( ifds::RepLevel, dstrRepLevel, idDataGroup );
   double dRepLevel = DSTCommonFunctions::convertToDouble ( dstrRepLevel );
   if ( dRepLevel < 2 ) {
      DString dstrErrValue;
      ErrMsgRulesList* pErrMsgRulesList = NULL;
      getMgmtCo().getErrMsgRulesList( pErrMsgRulesList );
      pErrMsgRulesList->getEWIValue(I_("391"), idDataGroup, dstrErrValue );
      if( dstrErrValue == I_("E") ) {
         ADDCONDITIONFROMFILE( CND::AGENT_ERR_NASU_SLS_REP_LVL_NOT_MET ); 
      } else if (dstrErrValue == I_("W") ) {
         ADDCONDITIONFROMFILE( CND::AGENT_WARN_NASU_SLS_REP_LVL_NOT_MET ); 
      }
   }   
   return(GETCURRENTHIGHESTSEVERITY()); 
}
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/Agent.cpp-arc  $
// 
//    Rev 1.6   Jul 27 2005 18:42:24   AGUILAAM
// IN 353952 - refine validations of Systematic records against broker/branch/rep effective/stop dates.
// 
//    Rev 1.5   Sep 20 2003 10:19:48   HSUCHIN
// Added missed enhancement to check to see if the Agent is active or not.
// 
//    Rev 1.4   Sep 02 2003 09:43:56   HSUCHIN
// bug fix for level check and change ewi codes due to base change.
// 
//    Rev 1.3   Aug 20 2003 10:33:02   HSUCHIN
// removed hard coding of sales level
// 
//    Rev 1.2   Aug 19 2003 09:07:16   HSUCHIN
// added canCreateAccount/canPurchase level check
// 
//    Rev 1.1   Mar 21 2003 17:56:52   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.0   Mar 05 2003 12:04:28   HSUCHIN
// Initial revision.
 */