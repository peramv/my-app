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
// ^FILE   : DirectTradingList.cpp
// ^AUTHOR : 
// ^DATE   : 
//
// ^CLASS    : DirectTradingList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include "stdafx.h"
#include "DirectTradinglist.hpp"
#include "mgmtcooptions.hpp"
#include "mgmtco.hpp"
#include "mfaccount.hpp"
#include "DirectTrading.hpp"
#include "shareholder.hpp"
#include <ifastdataimpl\dse_dstc0265_req.hpp>
#include <ifastdataimpl\dse_dstc0265_vw.hpp>
#include <ifastdataimpl\dse_dstc0266_vw.hpp>
#include <ifastdataimpl\dse_dstc0052_req.hpp>
#include <ifastdataimpl\dse_dstc0069_vw.hpp>
#include <ifastdataimpl\dse_dstc0004_vw.hpp>

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest DIRECT_TRADING;
}

namespace
{
   // Trace literals
   const I_CHAR * const CLASSNAME       = I_( "DirectTradingList" );
}

namespace CND
{
	extern CLASS_IMPORT const long ERR_DATA_NOT_FOUND;
}
namespace ifds
{
   extern CLASS_IMPORT const BFNumericFieldId AccountNum;
   extern CLASS_IMPORT const BFDateFieldId CurrBusDate;
}

//******************************************************************************
DirectTradingList::DirectTradingList( BFAbstractCBO &parent )
: MFCanBFCbo( parent )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   setObjectAsList();
}

//******************************************************************************
DirectTradingList::~DirectTradingList( void )
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************
SEVERITY DirectTradingList::initNew( const DString& dstrAccountNum )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

   _AccountNum = dstrAccountNum;   

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY DirectTradingList::init( DString& dstrAccountNum, 
							bool ignoreDataNotFound,
                            const DString& dstrTrack,
                            const DString& dstrPageName )               

{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

   _AccountNum = dstrAccountNum;

   BFData queryData(ifds::DSTC0265_REQ);
   BFData *response = new BFData(ifds::DSTC0265_VW);

   DString mgmtCoIdOut;
   queryData.setElementValue( ifds::CompanyId, getMgmtCoId( mgmtCoIdOut ) );
   queryData.setElementValue( ifds::AccountNum, dstrAccountNum ); 
   queryData.setElementValue( ifds::Track, dstrTrack );
   queryData.setElementValue( ifds::Activity, dstrPageName );

   DSTCRequestor requestor( getSecurity(), true, false );

   if( ignoreDataNotFound )
   {
      requestor.filterHostCondition(CND::ERR_DATA_NOT_FOUND);
   }

   if( BFDataBroker::getInstance()->receive( DSTC_REQUEST::DIRECT_TRADING, queryData, *response, requestor )  > WARNING )
   {
      delete response;
      response = NULL;
   }
   else
   {
      attachDataObject( *response, true, true );
      init2( *response );
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//------------------------------------------------------------------------------------
SEVERITY DirectTradingList::init2(const BFData& recData ) 
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init2" ) );

   if( recData.getRepeatCount() > 0 )
   {

      int nNumRepeats = recData.getRepeatCount();
      BFCBO * pObj = NULL;
      DString strKey;

      for( int i = 0; i < nNumRepeats; i++ )
      {
         DString strKey;
         getStrKey( strKey, &recData.getRepeat(i) );
         DirectTrading* _pDirectTrading = new DirectTrading( *this );
         _pDirectTrading->init( this, recData.getRepeat(i) );
         setObject( _pDirectTrading, strKey, OBJ_ACTIVITY_NONE, BF::HOST );
      } 
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
void  DirectTradingList::getStrKey(DString &strKey, const BFData *data)  //key by AddrCode and effective date
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getStrKey" ) );
   DString  dstrEffectiveDate = data->getElementValue(ifds::EffectiveDate );
   dstrEffectiveDate.stripLeading();
   strKey = dstrEffectiveDate; 
   _dstrKey = strKey;
}

//******************************************************************************
SEVERITY DirectTradingList::doCreateNewObject(BFCBO *&pBase, DString &strKey, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateNewObject" ) );

   pBase = new DirectTrading( *this );

   ((DirectTrading* )pBase)->init( this, idDataGroup );   

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY DirectTradingList::doCreateObject( const BFData& data, BFCBO *&pObjOut )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateObject" ) );

   DirectTrading * pDirectTrading = new DirectTrading( *this );
   pDirectTrading->init( this, data );
   pObjOut = pDirectTrading;

   return(GETCURRENTHIGHESTSEVERITY());
}
//-----------------------------------------------------------------------------------
bool DirectTradingList::IsCurrentObjectEffective(const DString& strKey,const BFDataGroupId& idDataGroup)
{
   DString strEffect,strStop,curDate,strCode;
   getWorkSession().getMgmtCoOptions()->getField(ifds::CurrBusDate,curDate,idDataGroup);
   curDate.strip();
   getObject(strKey, idDataGroup)->getField(ifds::EffectiveDate,strEffect,idDataGroup);
   getObject(strKey, idDataGroup)->getField(ifds::StopDate,strStop,idDataGroup);
   if( DSTCommonFunctions::IsDateBetween(strEffect, strStop,curDate) )
   {
      return(true);
   }
   return(false);
}


//******************************************************************************
SEVERITY DirectTradingList:: doValidateAll( const BFDataGroupId& idDataGroup, long lValidateGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doValidateAll" ) );

   BFObjIter DirectTradingIter( *this, idDataGroup, true, BFObjIter::ITERTYPE::NON_DELETED );
   //no DirectTrading for this shareholder, then raise a condition
   if( DirectTradingIter.getNumberOfItemsInList() < 1 )
   {
      //ADDCONDITIONFROMFILE( CND::ERR_NO_DIRECTTRADINGES_FOR_THIS_SHAREHOLDER );
   }

   return(GETCURRENTHIGHESTSEVERITY());

}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/DirectTradingList.cpp-arc  $
// 
//    Rev 1.3   Nov 14 2004 14:30:44   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.2   Oct 23 2003 17:53:22   FENGYONG
// StrKey will be Effective date
// 
//    Rev 1.1   Oct 16 2003 12:17:52   FENGYONG
// PET809 FN08 Direct Trading enhancement
// 
//    Rev 1.0   Oct 07 2003 10:16:00   FENGYONG
// Initial Revision
 * 
 */

