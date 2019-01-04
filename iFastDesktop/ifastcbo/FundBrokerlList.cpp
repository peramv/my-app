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
//    Copyright 2002 By International Financial
//
//
//******************************************************************************
//
// ^FILE   : FundBrokerList.cpp
// ^AUTHOR : 
// ^DATE   : July 21, 2004
//
// ^CLASS    : FundBrokerList 
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "fundbrokerlist.hpp"

#include "dstcommonfunction.hpp"
#include "mgmtco.hpp"
#include "fundbroker.hpp"
#include <ifastdataimpl\dse_dstc0326_req.hpp>
#include <ifastdataimpl\dse_dstc0326_vw.hpp>


namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest FUND_BROKER_LIST;
}

namespace  
{
   const I_CHAR * const CLASSNAME    = I_( "FundBrokerList");  
}

namespace CND
{
   //extern const long ERR_FUND_BROKER_ALREADY_IN_SYSTEM;
}

//*********************************************************************************
FundBrokerList::FundBrokerList( BFAbstractCBO &parent ) : MFCanBFCbo( parent )
,requestData326( NULL )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   setObjectAsList();
}

//*********************************************************************************
FundBrokerList::~FundBrokerList()
{
   TRACE_DESTRUCTOR( CLASSNAME );
   if ( requestData326 != NULL )
   {
      delete requestData326;
   }
}

//*********************************************************************************
SEVERITY FundBrokerList::init ( const BFDataGroupId &idDataGroup, 
                                const DString &track, /*=I_("N")*/
                                const DString &pageName /*=NULL_STRING*/
                              )
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_( "init" ) 
                         );
   return init (NULL_STRING, NULL_STRING, idDataGroup, track, pageName);
}

//*********************************************************************************
SEVERITY FundBrokerList::init ( const DString &fundBrokerCode,
							    const DString &fundBrokerName,
                                const BFDataGroupId &idDataGroup, 
                                const DString &dstrTrack, /*=I_("N")*/
                                const DString &dstrPageName, /*=NULL_STRING*/
								const bool noDataIsErrorCondition /*false*/
                              )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );
// receive data from back end

    DString mgmtCoIdOut;	
	requestData326 = new BFData(ifds::DSTC0326_REQ);
	requestData326->setElementValue( ifds::CompanyId, getMgmtCoId( mgmtCoIdOut ) );
	requestData326->setElementValue( ifds::Track, dstrTrack );
	requestData326->setElementValue( ifds::Activity, dstrPageName );
	requestData326->setElementValue( ifds::NextKey, NULL_STRING);
	requestData326->setElementValue( ifds::FundBrokerCode, fundBrokerCode);
	requestData326->setElementValue( ifds::Name, fundBrokerName);

	BFData* responseData = new BFData (ifds::DSTC0326_VW);
	ReceiveData ( DSTC_REQUEST::FUND_BROKER_LIST, 
                 *requestData326, 
                 *responseData, 
                 DSTCRequestor( getSecurity(),false,noDataIsErrorCondition ) 
               );
   return GETCURRENTHIGHESTSEVERITY();
}
//********************************************************************************
SEVERITY FundBrokerList::doCreateObject (const BFData& data, BFCBO *&pObjOut)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, 
                          CLASSNAME, 
                          I_( "doCreateObject" ) 
                        );

   pObjOut =  new FundBroker( *this );
   ((FundBroker* )pObjOut )->Init(data);

   return GETCURRENTHIGHESTSEVERITY();
}

//*********************************************************************************
SEVERITY FundBrokerList::doCreateNewObject (BFCBO *&pBase, DString &strKey, const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, 
                          CLASSNAME, 
                          I_( "doCreateNewObject" ) 
                        );
   FundBroker* pFundBroker = new FundBroker( *this );
   pFundBroker->InitNew( idDataGroup  );
   pBase = pFundBroker;
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
void FundBrokerList::buildKey (const DString &fundBrokerCode, DString &strKey)
{
   DString fundBrokerCode_(fundBrokerCode);
   
   fundBrokerCode_.strip().upperCase();
   strKey = I_("FundBrokerCode=") + fundBrokerCode_;
}

//******************************************************************************
void FundBrokerList::getStrKey (DString &strKey, const BFData *data)
{
   TRACE_METHOD (CLASSNAME, I_("getStrKey"));

   if (data)
   {
      buildKey (data->getElementValue (ifds::FundBrokerCode), strKey);
   }
   else
   {
      BFCBO::getStrKey (strKey , NULL);
   }
}

//******************************************************************************
bool FundBrokerList::canDeleteObject( const DString& strKey, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doValidateAll" ) );   

   DString dstrFundBroker, 
      dstrCodeInUse = I_("N");
   BFAbstractCBO* pObj = getObject(strKey, idDataGroup);
   assert( pObj );

   pObj->getField (ifds::FundBrokerCode,dstrFundBroker,idDataGroup,false);
   //call view 126 check if fund broker is in use by any fund
   if (pObj->isNew() || dstrCodeInUse != I_("Y"))
   {
      return(true);
   }
   //ADDCONDITIONFROMFILE( CND::ERR_FUND_BROKER_CODE_IN_USE );

   return false;

}
//******************************************************************************
SEVERITY FundBrokerList::getMore()
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getMore" ) );

   if( doMoreRecordsExist() )
   {
      const DSTCSecurity* security = dynamic_cast<const DSTCSecurity *> ( getSecurity() );
      ReceiveData(DSTC_REQUEST::FUND_BROKER_LIST, *requestData326, ifds::DSTC0326_VW, DSTCRequestor(getSecurity(), false) );
   }

   return(GETCURRENTHIGHESTSEVERITY());
}
//******************************************************************************
SEVERITY FundBrokerList::getFundBroker ( const DString &fundBrokerCode, 
									              const BFDataGroupId& idDataGroup, 
										           FundBroker *&pFundBroker )
{
	MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_( "getFundBroker" ) );

	pFundBroker = NULL;
   DString dstrLocalFundBrokerCode = fundBrokerCode; 
   dstrLocalFundBrokerCode.stripAll().upperCase();

   BFObjIter iter( *this, 
		             idDataGroup, 
						 true, 
						 BFObjIter::ITERTYPE::NON_DELETED );

   iter.begin();      
	while (!iter.end())
   {
		FundBroker *pCurrentFundBroker = dynamic_cast <FundBroker*> (iter.getObject());
      if ( NULL != pCurrentFundBroker )
		{
			DString dstrCurrentFundBrokerCode;

         pCurrentFundBroker->getField (ifds::FundBrokerCode, dstrCurrentFundBrokerCode, idDataGroup ); 
			
         if ( dstrCurrentFundBrokerCode.stripAll().upperCase() == dstrLocalFundBrokerCode )
         {
            pFundBroker = pCurrentFundBroker;
            break;
         }
		}
		++iter;
	} 

	return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY FundBrokerList::getFundBrokerCodeSubstList (DString &dstrFundBrokerCodeSubstList)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_( "getFundBrokerCodeSubstList" ) 
                         );
   
	dstrFundBrokerCodeSubstList = NULL_STRING;
	BFObjIter iter( *this, 
		             BF::HOST, 
						 true, 
						 BFObjIter::ITERTYPE::NON_DELETED );

   iter.begin();      
	while (!iter.end())
   {
		FundBroker *pFundBroker = dynamic_cast <FundBroker*> (iter.getObject());
      if (pFundBroker)
		{
			DString fundBrokerCode;

         pFundBroker->getField (ifds::FundBrokerCode, fundBrokerCode, BF::HOST); //??
			dstrFundBrokerCodeSubstList += fundBrokerCode + I_("=") + fundBrokerCode + I_(";");
		}
		++iter;
	}
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/FundBrokerlList.cpp-arc  $
// 
//    Rev 1.10   Jan 13 2011 03:58:46   wichian
// IN#2319580 - Add New fund broker button on Feature Search screen.
// 
//    Rev 1.9   Dec 09 2004 19:16:40   vadeanum
// PET1117 FN08 - Shareholder Fund Broker - fixed getFundBroker().
// 
//    Rev 1.8   Nov 25 2004 13:44:14   vadeanum
// PET1117 FN08 - Shareholder Fund Broker - fixed getFundBroker().
// 
//    Rev 1.7   Nov 24 2004 16:50:00   Fengyong
// receive 25 record each time
// 
//    Rev 1.6   Nov 23 2004 17:25:20   Fengyong
// PET1117FN54 - adjustment after first day intergretion test
// 
//    Rev 1.5   Nov 19 2004 11:26:44   popescu
// PET 1117/06, cleaned-up the keys assignement, changed getFundBroker method to find an object using 'positionByKey', added new init for DSTCWorkSession
// 
//    Rev 1.4   Nov 19 2004 10:30:10   aguilaam
// PET1117_FN21 : settlement instructions enhancement
// 
//    Rev 1.3   Nov 14 2004 14:41:40   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.2   Nov 05 2004 10:50:22   FENGYONG
// view team change the number of view from 319 to 326
// 
//    Rev 1.1   Nov 04 2004 11:00:54   FENGYONG
// PET1117 FN54 - Fund broker static temp check in for 59 build
// 
//    Rev 1.0   Oct 19 2004 14:44:20   FENGYONG
// Initial revision.
*/
