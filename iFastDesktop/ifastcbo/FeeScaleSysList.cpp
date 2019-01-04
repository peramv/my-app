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
// ^FILE   : FeeScaleSysList.cpp
// ^AUTHOR : Yingbao Li, May Lin
// ^DATE   : January 08, 2003
//
// ^CLASS    : FeeScaleSysList 
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "FeeScaleSyslist.hpp"
#include "FeeScaleSys.hpp"
#include <ifastdataimpl\dse_dstc0231_req.hpp>
#include <ifastdataimpl\dse_dstc0231_vw.hpp>
#include "mgmtco.hpp"
#include "mgmtcooptions.hpp"

namespace  
{
   const I_CHAR * const CLASSNAME = I_( "FeeScaleSysList" );  
   const I_CHAR * IDISCALE = I_( "SCALE" );

}


namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest FEE_PARAM_SYSTEM_SCALE_LIST;
}




//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

//*********************************************************************************
FeeScaleSysList::FeeScaleSysList( BFAbstractCBO &parent )
: FeeScaleBaseList( parent )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
}

//*********************************************************************************
FeeScaleSysList::~FeeScaleSysList()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//*********************************************************************************
SEVERITY FeeScaleSysList:: init( const DString& SysFeeParamId, bool bDefault, const DString& dstrTrack,
                             const DString& dstrPageName   )

{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init( DString&" ) );

	DString mgmtCoIdOut;
	bDefault_ = bDefault;
	BFData requestData(ifds::DSTC0231_REQ);  
	requestData.setElementValue( ifds::CompanyId, getMgmtCoId( mgmtCoIdOut ) );
	//   requestData230->setElementValue( ifds::Track, dstrTrack );
	//   requestData230->setElementValue( ifds::Activity, dstrPageName );
	requestData.setElementValue( ifds::NextKey,     NULL_STRING );
	requestData.setElementValue( ifds::FeeID, SysFeeParamId );
   requestData.setElementValue( ifds::Track, dstrTrack );
   requestData.setElementValue( ifds::Activity, dstrPageName );
	BFData* responseData = new BFData(ifds::DSTC0231_VW);
	ReceiveData(DSTC_REQUEST::FEE_PARAM_SYSTEM_SCALE_LIST, requestData, *responseData, DSTCRequestor( getSecurity(),false,false ) );
   if( !bDefault_ )
	{
		int iLevel = 0;
		DString dstrLevel;
	   BFObjIter iterScale(*this,BF::HOST,false,BFObjIter::ITERTYPE::NON_DELETED );   
		while( !iterScale.end() )
		{
			BFCBO* pCBO = dynamic_cast<BFCBO *>(iterScale.getObject());
			if( pCBO )
			{
				pCBO->getField(ifds::Level,dstrLevel,BF::HOST,false);
				dstrLevel.strip();
				int iTLevel = dstrLevel.asInteger();
				if( iTLevel > iLevel ) 
				{
					iLevel = iTLevel;
				}		
			}
			++ iterScale;
		}	
		initLevel(iLevel);	
	}	
	return(GETCURRENTHIGHESTSEVERITY());
}
//****************************************************************************
SEVERITY FeeScaleSysList::initNew(const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_( "initNew" ));

	return GETCURRENTHIGHESTSEVERITY();
}

//*********************************************************************************
void  FeeScaleSysList::getStrKey (DString &strKey, const BFData *data)
{
	if (data)
	{
      DString dstrLow,
         genKey;

      BFCBO::getStrKey (genKey, NULL);
		dstrLow = data->getElementValue (I_( "LowerBound"));
		dstrLow.strip().upperCase();
      strKey = I_("Key=") + genKey + I_(";LowerBound") + dstrLow; 
	}
	else 
	{
		BFCBO::getStrKey( strKey , NULL );
	}
}

//**********************************************************************************
SEVERITY FeeScaleSysList::doCreateObject( const BFData& data, BFCBO *&pObjOut )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateObject") );
   pObjOut =  new FeeScaleSys( *this );
   ((FeeScaleSys*) pObjOut)->init( data, bDefault_);
	return(GETCURRENTHIGHESTSEVERITY());
}

//***********************************************************************************

SEVERITY FeeScaleSysList::doCreateNewObject( BFCBO *&pBase, DString &strKey, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateObject") );
   pBase =  new FeeScaleSys( *this );
   ((FeeScaleSys*) pBase)->init( idDataGroup );


	return(GETCURRENTHIGHESTSEVERITY());
}
//******************************************************************************

SEVERITY FeeScaleSysList::AddNewFeeScale( FeeScaleBaseList *pFeeScaleList, const DString& strKey, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "AddNewFeeScale" ) );

   BFObjIter iterScale(*pFeeScaleList,BF::HOST,false,BFObjIter::ITERTYPE::NON_DELETED );
   
   while( !iterScale.end() )
  {
	   BFCBO* pCBO = dynamic_cast<BFCBO *>(iterScale.getObject());

	   BFObjectKey objKey( strKey, idDataGroup );

	   FeeScaleSys *pFeeScaleSys = dynamic_cast<FeeScaleSys*>(getNewListItem( objKey ));

	   pFeeScaleSys->setValueFromDefault(pCBO, idDataGroup );

       ++ iterScale;

  }

   return(GETCURRENTHIGHESTSEVERITY());
}

SEVERITY FeeScaleSysList::clone(const BFDataGroupId& idDataGroup, FeeScaleSysList*& pFeeScaleSysListClone)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "clone" ) );

   pFeeScaleSysListClone = new FeeScaleSysList((BFAbstractCBO&)(*this));

   BFObjIter iter(*this,idDataGroup,false,BFObjIter::ITERTYPE::NON_DELETED );
   while( !iter.end() )
   {
      FeeScaleSys* pFeeScaleSys = dynamic_cast<FeeScaleSys*>(iter.getObject());
      if(pFeeScaleSys)
      {
         FeeScaleSys* pFeeScaleSysClone = NULL;
         pFeeScaleSys->clone(idDataGroup, pFeeScaleSysClone);
         if(pFeeScaleSysClone)
         { 
            BFObjectKey objKey(iter.getKey().getStringKey(), idDataGroup, OBJ_ACTIVITY_ADDED);

            pFeeScaleSysListClone->setObject(objKey, pFeeScaleSysClone);
            pFeeScaleSysClone->setFieldUpdated(ifds::Level, idDataGroup, true);
         }
      }
      ++iter;
   }

   return(GETCURRENTHIGHESTSEVERITY());
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/FeeScaleSysList.cpp-arc  $
// 
//    Rev 1.11   Jan 18 2006 16:25:34   popescu
// Incident# 523433 - fix the key so scales can be displayed in the order given by the view.
// 
//    Rev 1.10   Nov 14 2004 14:40:42   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.9   Oct 20 2004 16:26:22   YINGBAOL
// PTS10034800: take care of Level
// 
//    Rev 1.8   Jun 26 2003 10:18:48   linmay
// modified addNewFeeScaleList()
// 
//    Rev 1.7   Jun 20 2003 16:29:24   linmay
// PTS#10014935
// 
//    Rev 1.6   Mar 21 2003 18:10:16   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.5   Mar 03 2003 14:51:06   YINGBAOL
// change key to lowerbound
// 
//    Rev 1.4   Jan 18 2003 17:27:42   YINGBAOL
// implement docreatenewobject
// 
//    Rev 1.3   Jan 17 2003 14:10:14   YINGBAOL
// implemt init method
// 
//    Rev 1.2   Jan 15 2003 15:19:06   linmay
// added log comment
*/