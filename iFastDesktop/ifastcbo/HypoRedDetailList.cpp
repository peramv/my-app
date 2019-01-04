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
//    Copyright 2000 by DST Canada Inc.
//
//
//******************************************************************************
//
// ^FILE   : HypoRedDetailList.cpp
// ^AUTHOR : Robert Kovacs
// ^DATE   : 10/28/2002
//
// ^CLASS    : HypoRedDetailList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "hyporeddetail.hpp"
#include "hyporeddetaillist.hpp"
#include <ifastdataimpl\dse_dstc0227_vw.hpp>

namespace  
{
   const I_CHAR * const CLASSNAME            = I_( "HypoRedDetailList" );

}


namespace  CND
{
   extern CLASS_IMPORT const long ERR_DATA_NOT_FOUND;
}

//****************************************************************************
HypoRedDetailList::HypoRedDetailList( BFAbstractCBO &parent )
: MFCanBFCbo( parent )
{
   TRACE_CONSTRUCTOR( CLASSNAME , NULL_STRING );
   setObjectAsList( );
}

//****************************************************************************
HypoRedDetailList::~HypoRedDetailList()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}   

//****************************************************************************

SEVERITY HypoRedDetailList::init( const DString& strFundCode, const DString& strClassCode, 
								const BFData& allDetailsData, const DString& dstrTrack /*= I_("N")*/,
                         const DString& dstrPageName /*= NULL_STRING*/ )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

	int cRepeats = allDetailsData.getRepeatCount();
   if( 0 != cRepeats )
   {
      for( int i = 0; i < cRepeats; i++ )
      {
         const BFData &data = allDetailsData.getRepeat( i );
         DString strDataFundCode, strDataClassCode, dstrKey;
			getStrKeyForNewItem(dstrKey);
         data.getElementValue(ifds::FundCode, strDataFundCode);
         data.getElementValue(ifds::ClassCode, strDataClassCode);
			if (strDataFundCode.strip() == strFundCode && 
				strDataClassCode.strip() == strClassCode)
			{
				HypoRedDetail *pHypoRedDetail = new HypoRedDetail( *this );
				setObject( pHypoRedDetail, dstrKey, OBJ_ACTIVITY_NONE, BF::HOST );
				pHypoRedDetail->init( data );
			}
      }
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************

SEVERITY HypoRedDetailList::doCreateObject( const BFData& data, BFCBO *&pObjOut )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateObject" ) );
	assert(0);//with the current design it should never be called
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/HypoRedDetailList.cpp-arc  $
// 
//    Rev 1.3   Nov 14 2004 14:44:42   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.2   Mar 21 2003 18:14:22   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.1   Nov 25 2002 09:41:02   KOVACSRO
// Added implementation.
// 
//    Rev 1.0   Oct 29 2002 10:50:54   KOVACSRO
// Initial Revision
// 
 
*/


