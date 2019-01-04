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
//    Copyright 2002 by International Financial.
//
//
//******************************************************************************
//
// ^FILE   : FundCommGroupList.cpp
// ^AUTHOR : Yingbao Li, May Lin
// ^DATE   : Dec. 31, 2002
//
// ^CLASS    : FundCommGroupList 
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "FundCommGroupList.hpp"
#include <ifastdataimpl\dse_dstc0229_vw.hpp>
#include <ifastdataimpl\dse_dstc0229_req.hpp>
#include "mgmtco.hpp"
#include "mgmtcooptions.hpp"
#include "dstcommonfunction.hpp"

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest FUND_COMM_GROUP_LIST;
}

namespace  
{
   const I_CHAR * const CLASSNAME = I_( "FundCommGroupList" );  
}

namespace CND
{
   extern CLASS_IMPORT const long ERR_INVALID_FUND_GROUP_TYPE;
}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

FundCommGroupList::FundCommGroupList( BFAbstractCBO &parent )
: MFCanBFCbo( parent )
, _bFirst(true)
, _pRequestData(NULL)

{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   setObjectAsList();
   //setVersionable( false );

}

//*********************************************************************************

FundCommGroupList::~FundCommGroupList()
{
	TRACE_DESTRUCTOR( CLASSNAME );
	if( _pRequestData ) delete _pRequestData;
}
//**********************************************************************************
SEVERITY FundCommGroupList::init(const DString& dstrComm,
                                 const DString& dstrTrack,
                                 const DString& dstrPageName)

{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init(DString&" ) );
   _dstrCommGroupCode = dstrComm;
   if( _bFirst )
   {
      DString mgmtCoIdOut;
      _pRequestData = new BFData(ifds::DSTC0229_REQ );
	  _pRequestData->setElementValue( ifds::CompanyId, getMgmtCoId( mgmtCoIdOut ) );
      _pRequestData->setElementValue( ifds::Track, dstrTrack );
      _pRequestData->setElementValue( ifds::Activity, dstrPageName ); 
   }
   _pRequestData->setElementValue( ifds::GroupType, dstrComm ); 

//CP20030409   BFData *responseData = new BFData(ifds::DSTC0229_VW);
   
   DSTCRequestor requestor( getSecurity(), true);
   requestor.filterHostCondition (CND::ERR_INVALID_FUND_GROUP_TYPE);
   ReceiveData(DSTC_REQUEST::FUND_COMM_GROUP_LIST, *_pRequestData, ifds::DSTC0229_VW, requestor);

   return(GETCURRENTHIGHESTSEVERITY());

}
//**********************************************************************************
void  FundCommGroupList::getStrKey( DString &strKey, const BFData *data  )
{
   DString dstrCommGroupCode;
	if( data )
	{
		dstrCommGroupCode = data->getElementValue( I_( "FundGroup" ) );
		dstrCommGroupCode.strip().upperCase();
		strKey = dstrCommGroupCode;
	}
	else 
	{
		BFCBO::getStrKey( strKey , NULL );
	}
}

//**********************************************************************************
void FundCommGroupList::getCommGroupSubstitute(DString& dstrSubstitute,bool bAddEmpty)
{
   BFObjIter iter( *this, BF::HOST,true,BFObjIter::ITERTYPE::NON_DELETED );
	DString dstrCode(I_("NA") ),dstrName(I_(" ")) ;
	dstrSubstitute = NULL_STRING;
	if(bAddEmpty ) {
		dstrSubstitute = 	dstrCode + I_("=") + dstrName + I_(";");
	}

	while(!iter.end() )
	{
		iter.getObject()->getField(ifds::FundGroup,dstrCode,BF::HOST,false);
		iter.getObject()->getField(ifds::GroupName,dstrName,BF::HOST,false);
		if (dstrName.strip() == NULL_STRING)
		{
			dstrName = dstrCode;
		}
		dstrSubstitute += dstrCode+I_("=") + dstrName + I_(";");
		++iter; 	
	}
}

//**********************************************************************************

SEVERITY FundCommGroupList::getFundGroupListByType(const DString&dstrFundGroupType, FundCommGroupList*& pFundGroupList)
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getFundGroupListByType" ) );
	DString dstrGroupType(dstrFundGroupType);
	dstrGroupType.strip().upperCase();
	
	pFundGroupList = dynamic_cast<FundCommGroupList *>(getObject(dstrGroupType, BF::HOST ));


	if( pFundGroupList == NULL )
	{
      // if it is not existed, create a new one
      pFundGroupList = new FundCommGroupList((BFAbstractCBO&)(*this));
      pFundGroupList->init(dstrFundGroupType);
	}
	if (pFundGroupList)
	{
		 if( GETCURRENTHIGHESTSEVERITY() <= WARNING )
		 {
			setObject( pFundGroupList, dstrGroupType, OBJ_ACTIVITY_NONE, BF::HOST );
		 }
		 else
		 {
			delete pFundGroupList;
			pFundGroupList = NULL;
		 }
	}

	return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/FundCommGroupList.cpp-arc  $
// 
//    Rev 1.13   Feb 14 2005 10:23:56   yingbaol
// PTS10038536: Not all Fund Comgroup has been pull over to desktop side.
// 
//    Rev 1.12   Nov 24 2004 10:18:16   yingbaol
// PET1117:temperary take out version features
// 
//    Rev 1.11   Nov 18 2004 13:28:04   YINGBAOL
// PET1117: Perfermance Tunning
// 
//    Rev 1.10   Nov 14 2004 14:41:50   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.9   May 02 2003 14:44:56   linmay
// modified getCommGroupSubstitute
// 
//    Rev 1.8   Apr 16 2003 09:53:42   PURDYECH
// Removed memory leak in ReceiveData
// 
//    Rev 1.7   Mar 21 2003 18:10:50   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.6   Mar 10 2003 14:50:04   linmay
// added getGroupListbytype
// 
//    Rev 1.5   Jan 17 2003 14:10:44   YINGBAOL
// fix getfield
// 
//    Rev 1.4   Jan 09 2003 15:46:16   YINGBAOL
// add getCommGroupSubstitute(DString& dstrSubstitute,bool bAddEmpty)  method
// 

 *
 * 
 */

