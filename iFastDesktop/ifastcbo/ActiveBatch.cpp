//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by International Financial Data Services,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2007, By International Financial Data Service
//
//
//******************************************************************************
//
// ^FILE   : ActiveBatch.cpp
// ^AUTHOR : Serban Popescu
// ^DATE   : Sept, 2007
//
// ^CLASS    : ActiveBatch
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include "stdafx.h"

#include "activebatch.hpp"
#include <bfsessn\bfcpsession.hpp>
#include "managementcompanieslist.hpp"
#include "mgmtcooptions.hpp"
#include "mgmtco.hpp"

//logon data
#include <ifastdataimpl\dse_dstc0001_req.hpp>
#include <ifastdataimpl\dse_dstc0001_vw.hpp>

//active batch
#include <ifastdataimpl\dse_dstc0124_req.hpp>
#include <ifastdataimpl\dse_dstc0124_vw.hpp>

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest ACTIVE_BATCH;
}

namespace
{
   // Trace literals
   const I_CHAR * const CLASSNAME = I_( "ActiveBatch" );	
}

namespace ifds
{	         
}

/*const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = 
{
   //  Field DD Id,			  State Flags,		 Group Flags 
};*/

//static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );

//******************************************************************************
ActiveBatch::ActiveBatch( BFAbstractCBO &parent )
: MFCanBFCbo( parent ),
_batchList (NULL_STRING)
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
/*   registerMemberData( NUM_FIELDS,
                       (const CLASS_FIELD_INFO *)&classFieldInfo,
                       0, NULL );*/
}

//******************************************************************************
ActiveBatch::~ActiveBatch()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}  

//*******************************************************************************
SEVERITY ActiveBatch::init ( BFSession *session,
                             const BFDataGroupId &idDataGroup)
{
//do not want to promote the errors
   MAKEFRAME2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("init"));
   ManagementCompaniesList mgmtCompaniesList (session->getUserSession());

//walk the list of management companies
   if (mgmtCompaniesList.init () <= WARNING)
   {
      BFObjIter iter ( mgmtCompaniesList, 
                       idDataGroup, 
                       true);
      while (!iter.end())
      {
         DString mgmCoId,
            companyName,
            batchName;
		 
         iter.getObject ()->getField (ifds::CompanyId, mgmCoId, idDataGroup);
         iter.getObject ()->getField (ifds::CompanyName, companyName, idDataGroup);

		 if( getGlobalSession().findMgmtCo( mgmCoId.strip() ) )
		 {
			//the user accessed this ManCo, so go ahead and check for active batch
			getActiveBatch (batchName, mgmCoId, idDataGroup);
			if (!batchName.empty ())
			{
				//add this to a list of batches...
				DString batch (batchName + I_(" (") + companyName + I_("); "));   
				_batchList += batch;
			}
		 }
         ++iter;
      }
   }
   CLEARCONDITIONS();
   return GETCURRENTHIGHESTSEVERITY();
}

//*****************************************************************************
void ActiveBatch::getActiveBatch ( DString &batchName, 
                                   const DString &mgmCoId,								   
                                   const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getActiveBatch" ) );

	batchName = NULL_STRING;
   //only for Canadian market...
   if (DSTCommonFunctions::getMarket() == MARKET_IDS::CANADA)
   {
      BFData queryData (ifds::DSTC0124_REQ),
         response (ifds::DSTC0124_VW);

      queryData.setElementValue (ifds::CompanyId, mgmCoId);  
      queryData.setElementValue (ifds::Track, I_("N"));
      queryData.setElementValue (ifds::Activity, NULL_STRING);

      if (BFDataBroker::getInstance()->
            receive ( DSTC_REQUEST::ACTIVE_BATCH, 
                     queryData, 
                     response, 
                     DSTCRequestor(getSecurity())) <= WARNING)
      {
	      DString checkCloseBatch;
            response.getElementValue (ifds::CheckCloseBatch, checkCloseBatch);
	      if( checkCloseBatch.strip() == I_( "Y" ) )
	      {
		      response.getElementValue (ifds::rxBatchName, batchName);
		      batchName.strip();
	      }	      
      }
	  else
	  {
		 DString dstrCheckCloseBatch = NULL_STRING;
		 
		 MgmtCo* pMgmtCo = NULL;
		 getGlobalSession().findMgmtCo( mgmCoId, pMgmtCo );
		 if( pMgmtCo )
		 {
			MgmtCoOptions *pMgmtCoOptions = NULL;
			pMgmtCo->getMgmtCoOptions(pMgmtCoOptions);
			if( pMgmtCoOptions )
			{
				pMgmtCoOptions->getField( ifds::CheckCloseBatch, dstrCheckCloseBatch, BF::HOST, false );
			}

			if( dstrCheckCloseBatch.strip().upperCase() == I_("Y") )
			{
				int count = CONDITIONCOUNT();
				
				for (int i = 0; i < count; i++)
				{
					Condition *c = GETCONDITION (i);
					if( c->getCode() == 40001422 )//ERR_BATCH_IS_LOCKED
					{
					   batchName = c->getMessage();
					}					
				}				
			}
		 }
	  }
   }
   //no matter what we do not want to raise the connectivity conditions....or any other..
   CLEARCONDITIONS();
//   return GETCURRENTHIGHESTSEVERITY();
}

//*****************************************************************************
void ActiveBatch::getActiveBatchesList (DString &batchList)
{
   batchList = _batchList;
}

//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastcbo/ActiveBatch.cpp-arc  $
// 
//    Rev 1.4   07 Mar 2008 14:09:32   kovacsro
// IN#1172388 - if CheckClosedBatch GC is on, show 'Batch is locked' error message, if that is the case
// 
//    Rev 1.3   22 Feb 2008 10:59:38   kovacsro
// IN#1191514 - fixed Desktop hanging at exit, as well as improved efficiency by only checking for active batch in those environments that have actually been accessed by the user
// 
//    Rev 1.2   28 Nov 2007 15:37:42   popescu
// IN#1015356 - only for Canadian markets
// 
//    Rev 1.1   17 Oct 2007 10:15:18   kovacsro
// IN#1015356 - now also checking CheckCloseBatch logical field
// 
//    Rev 1.0   25 Sep 2007 10:32:52   popescu
// Initial revision.
// 
//    Rev 1.21   21 Sep 2007 16:24:34   popescu
// Initial revision.
// 
