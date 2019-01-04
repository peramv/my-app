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
//    Copyright 1999 by DST Canada Inc.
//
//
//******************************************************************************
//
// ^FILE   : SavingPlanMasterList.cpp
// ^AUTHOR : Zijian Ying
// ^DATE   : 05/23/2001
//
// ^CLASS    : SavingPlanMasterList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include "stdafx.h"
#include "savingplanmasterlist.hpp"
#include "savingplanmaster.hpp"
#include <ifastdataimpl\dse_dstc0159_req.hpp>
#include <ifastdataimpl\dse_dstc0159_vw.hpp>

namespace
{
   //Trace literals
   const I_CHAR * const CLASSNAME = I_( "SavingPlanMasterList" );
}

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest SAVINGPLAN_MASTER_LIST;
}

//******************************************************************************
SavingPlanMasterList::SavingPlanMasterList( BFAbstractCBO &parent ) 
: MFCanBFCbo( parent )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   setObjectAsList( );
   setVersionable( false );

}


//******************************************************************************
SavingPlanMasterList::~SavingPlanMasterList()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************
SEVERITY SavingPlanMasterList::init( const DString& dstrTrack,const DString& dstrPageName )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

   BFData queryData(ifds::DSTC0159_REQ);
   BFData *receivedData = new BFData(ifds::DSTC0159_VW);

   DString mgmtCoIdOut;
   queryData.setElementValue( ifds::CompanyId, getMgmtCoId( mgmtCoIdOut ) );
   queryData.setElementValue( ifds::PlanCode, NULL_STRING );
   queryData.setElementValue( ifds::OverrideRepeats, I_("0") );
   queryData.setElementValue( ifds::Track, dstrTrack );
   queryData.setElementValue( ifds::Activity, dstrPageName );

   ReceiveData( DSTC_REQUEST::SAVINGPLAN_MASTER_LIST, 
                queryData, *receivedData, DSTCRequestor( getSecurity(), true) );

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY SavingPlanMasterList::doCreateObject( const BFData& data, BFCBO *&pObjOut )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateObject" ) );

   SavingPlanMaster * pSavingPlanMaster = new SavingPlanMaster( *this );
   pSavingPlanMaster->init( data );
   pObjOut = pSavingPlanMaster;

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
void SavingPlanMasterList::getStrKey (DString &strKey, const BFData *data)
{
   TRACE_METHOD( CLASSNAME, I_( "getStrKey" ) );

   if( data )
   {
      DString strPlanCode = data->getElementValue( I_( "RxPlanCode" ) );
      strKey = strPlanCode.strip().upperCase();
   }
   else
   {
      BFCBO::getStrKey( strKey , NULL );
   }

}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/SavingPlanMasterList.cpp-arc  $
// 
//    Rev 1.10   Dec 10 2004 14:53:48   hernando
// PET1117 - Recovered version feature.
// 
//    Rev 1.9   Nov 24 2004 10:18:48   yingbaol
// PET1117:temperary take out version features
// 
//    Rev 1.8   Nov 18 2004 13:28:26   YINGBAOL
// PET1117: Perfermance Tunning
// 
//    Rev 1.7   Nov 14 2004 14:53:42   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.6   Mar 21 2003 18:23:36   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.5   Oct 09 2002 23:54:56   PURDYECH
// PVCS Database Conversion
// 
//    Rev 1.4   Aug 29 2002 12:56:36   SMITHDAV
// ClientLocale and typed field changes.
// 
//    Rev 1.3   22 May 2002 18:29:50   PURDYECH
// BFData Implementation
// 
//    Rev 1.2   31 May 2001 11:14:56   YINGZ
// check in for Chin
// 
//    Rev 1.1   25 May 2001 15:07:40   YINGZ
// just save a copy
*/