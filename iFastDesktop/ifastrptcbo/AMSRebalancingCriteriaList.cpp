//*****************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by International Financial, Inc.,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2002 by International Financial, Inc.
//
//*****************************************************************************
//
// ^FILE   : AMSRebalancingCriteriaList.cpp
// ^AUTHOR : 
// ^DATE   : Nov 15, 2002
//
//-----------------------------------------------------------------------------
//
// ^CLASS  : AMSRebalancingCriteriaList
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS :
//
//*****************************************************************************

#include "stdafx.h"
#include "amsrebalancingcriterialist.hpp"
#include "amsrebalancingcriteria.hpp"

namespace
{
   const I_CHAR * const CLASSNAME = I_( "AMSRebalancingCriteriaList" );
};

struct CriteriaTypeCardinality
{
   const I_CHAR* CriteriaType;
   unsigned int min;
   unsigned int max;
};

const struct CriteriaTypeCardinality m_CriteriaTypeCardinality[] = 
{
   // Criteria Type        Min   Max
   I_( "StartDate" ),      1,    1,
   I_( "PendingTrade" ),   1,    1,
   I_( "AccountNum" ),     0,    -1,      // -1 Represent infinte
   I_( "AMSCode" ),        0,    -1,
   I_( "BrokerCode" ),     0,    -1,
   I_( "GroupCode" ),      0,    -1,
};

static const int numCriteriaTypeCardinality = sizeof( m_CriteriaTypeCardinality ) / sizeof( CriteriaTypeCardinality );

//*****************************************************************************
// Constructor
//*****************************************************************************

AMSRebalancingCriteriaList::AMSRebalancingCriteriaList( BFAbstractCBO &parent )
:  ifastReportCriteriaList( parent )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );   
   setObjectAsList();
}

//*****************************************************************************
// Destructor
//*****************************************************************************

AMSRebalancingCriteriaList::~AMSRebalancingCriteriaList()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//*****************************************************************************
// The init will set up the cardinality rules.  Refer to the struct 
// m_CriteriaTypeCardinality for the rules.
// @param   void.
// @returns void.
//*****************************************************************************
void AMSRebalancingCriteriaList::init ( )
{
   for ( int i = 0; i <= numCriteriaTypeCardinality; i++ ) {
      addFieldCardinality ( DString (m_CriteriaTypeCardinality[i].CriteriaType),
                            m_CriteriaTypeCardinality[i].min,
                            m_CriteriaTypeCardinality[i].max );
   }
}

//*****************************************************************************
// This method will create a new AMSRebalancingCriteria cbo.
// @param   BFCBO*& pBase - pointer to new AMSRebalancing cbo.
//          DString& strKey - key of new AMSRebalacing cbo.
//          long lDataGroupId - current data group id.
// @returns SEVERITY - NO_CONDITION most of the time.
//*****************************************************************************
SEVERITY AMSRebalancingCriteriaList::doCreateNewObject( BFCBO*& pBase, DString & strKey, long lDataGroupId  )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateNewObject" ) );

   pBase = new AMSRebalancingCriteria ( *this );
   return GETCURRENTHIGHESTSEVERITY();
}
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastrptcbo/AMSRebalancingCriteriaList.cpp-arc  $
// 
//    Rev 1.0   Nov 19 2002 11:28:14   HSUCHIN
// Initial Revision
*/
