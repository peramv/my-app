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
//    Copyright 2005 by International Financial Data Services
//
//
//******************************************************************************
//
// ^FILE   : BulkCancelList.cpp
// ^AUTHOR : Monica Porteanu
// ^DATE   : November 2005
//
// ^CLASS    : BulkCancel
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "bulkcancellist.hpp"

#include "bulkcancel.hpp"
#include "mgmtco.hpp"
#include "transcancel.hpp"


#include <ifastdataimpl\dse_dstc0337_req.hpp>
#include <ifastdataimpl\dse_dstc0337_vw.hpp>
#include <ifastdataimpl\dse_dstc0127_req.hpp>
#include <ifastdataimpl\dse_dstc0127_vw.hpp>

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest TRANS_CANCEL;
   extern CLASS_IMPORT const DSTCRequest TRANS_NUM;
}

namespace  
{
   const I_CHAR * const CLASSNAME    = I_( "TransCancellist");  
}

namespace CND
{
   //extern const long ERR_DATA_NOT_FOUND;
   extern CLASS_IMPORT const long ERR_DATA_NOT_FOUND;
   extern const long ERR_FIELD_REQUIRED_PLS_ENTER;
   extern const long WARN_CASH_DIVIDEND_PAID_AFTER;
}

//*********************************************************************************
BulkCancellist::BulkCancellist( BFAbstractCBO &parent ) : TransCancellist( parent )
{
   TRACE_CONSTRUCTOR (CLASSNAME, NULL_STRING);
   setObjectAsList();
}

//*********************************************************************************
BulkCancellist::~BulkCancellist()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************
SEVERITY BulkCancellist::getBulkCancel( const DString &dstrTradeDate, 
	                                    const DString &dstrFund,
							            const DString &dstrClass,
                                        BulkCancel *&pBulkCancel, 
                                        const BFDataGroupId &idDataGroup )
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getBulkCancel" ) );

	pBulkCancel = NULL;

    DString dstrKey;
	buildKey( dstrKey, dstrTradeDate, dstrFund, dstrClass );

	pBulkCancel = dynamic_cast<BulkCancel*>( getObject( dstrKey, idDataGroup ) );
    
	return GETCURRENTHIGHESTSEVERITY();
}

//*********************************************************************************
SEVERITY BulkCancellist::doValidateAll( const BFDataGroupId& idDataGroup, long lValidateGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doValidateAll" ) );
   
   return GETCURRENTHIGHESTSEVERITY();
}

//********************************************************************************
SEVERITY BulkCancellist::doCreateObject (const BFData& data, BFCBO *&pObjOut)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, 
                          CLASSNAME, 
                          I_( "doCreateObject" ));

   pObjOut =  new BulkCancel( *this );
   ((BulkCancel* )pObjOut )->init( data );

   return GETCURRENTHIGHESTSEVERITY();
}

//*********************************************************************************
SEVERITY BulkCancellist::doCreateNewObject( BFCBO *&pBase, 
										    DString &strKey, 
											const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, 
                          CLASSNAME, 
                          I_( "doCreateNewObject" ));

   BulkCancel* pBulkCancel = new BulkCancel (*this);
   pBulkCancel->setObjectNew ();

   pBulkCancel->initNew( idDataGroup,
	                     I_( "" ) );

   pBulkCancel->setField( ifds::TradeDate, getTradeDate(), idDataGroup );
   pBulkCancel->setField( ifds::Fund,      getFund(),      idDataGroup );
   pBulkCancel->setField( ifds::Class,     getClass(),     idDataGroup );

   pBase = pBulkCancel;
   
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
void BulkCancellist::getStrKey( DString &dstrKey, const BFData *data )
{
   if( data ) 
   {
      DString dstrTradeDate, dstrFund, dstrClass;
      dstrTradeDate = data->getElementValue( ifds::TradeDate ); 
	  dstrFund      = data->getElementValue( ifds::Fund ); 
	  dstrClass     = data->getElementValue( ifds::Class );           
      
      buildKey( dstrKey, 
				dstrTradeDate, 
				dstrFund,
				dstrClass );
   }
   else
   {
      BFCBO::getStrKey( dstrKey, NULL);
   }
}

//******************************************************************************
void BulkCancellist::buildKey( DString &dstrKey, 
  							   const DString &dstrTradeDate,
							   const DString &dstrFund,
				               const DString &dstrClass )
{
	DString dstrLocalTradeDate( dstrTradeDate ), dstrLocalFund( dstrFund ), dstrLocalClass( dstrClass );

	dstrKey = dstrLocalTradeDate + dstrLocalFund + dstrLocalClass;
}

//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/BulkCancellist.cpp-arc  $
// 
//    Rev 1.4   Nov 10 2005 18:58:26   porteanm
// PET 1286 FN01 - Bulk Cancellation.
// 
//    Rev 1.3   Nov 09 2005 19:50:54   porteanm
// PET 1286 FN01 - Bulk Cancellation.
// 
//    Rev 1.2   Nov 08 2005 19:19:40   porteanm
// PET 1286 FN01 - Bulk Cancellation.
// 
//    Rev 1.1   Nov 06 2005 14:01:02   porteanm
// PET 1286 FN01 - Bulk Cancellation - work in progress.
// 
//    Rev 1.0   Nov 05 2005 15:07:52   porteanm
// Initial revision.
// 
*/