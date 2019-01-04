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
//    Copyright 2004 by International Financial Data Services
//
//
//******************************************************************************
//
// ^FILE   : TransDecimalsList.cpp
// ^AUTHOR : Amelia Aguila
// ^DATE   : February 2005
//
// ^CLASS    : TransDecimalsList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include "stdafx.h"
#include "TransDecimals.hpp"
#include "TransDecimalslist.hpp"

#include <ifastdataimpl\dse_dstc0330_req.hpp>                 // TransDec Inquiry
#include <ifastdataimpl\dse_dstc0330_vw.hpp>                  // TransDec Inquiry
#include <ifastdataimpl\dse_dstc0330_vwrepeat_record.hpp>     // TransDec Inquiry


namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest TRANS_DECIMALS_LIST_INQUIRY;
}

namespace
{
   // Trace literals
   const I_CHAR *  CLASSNAME  = I_("TransDecimalsList");
}

//******************************************************************************
TransDecimalsList::TransDecimalsList(BFAbstractCBO &parent)
: MFCanBFCbo(parent),
_pRequestData(NULL)
{
   TRACE_CONSTRUCTOR(CLASSNAME, NULL_STRING);
   setObjectAsList();
}

//******************************************************************************
TransDecimalsList::~TransDecimalsList()
{
   TRACE_DESTRUCTOR(CLASSNAME);
   if (_pRequestData != NULL)
   {
      delete _pRequestData;
   }
}


//******************************************************************************
SEVERITY TransDecimalsList::init( const DString &dstrTransId, 
											    const BFDataGroupId &idDataGroup,     // BF::HOST 
											    const DString& dstrTrack,             // I_( "N" )
											    const DString &dstrPageName )         // NULL_STRING );			
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("init"));

	     	
   _pRequestData = new BFData (ifds::DSTC0330_REQ);

   DString mgmtCoIdOut;

   _pRequestData->setElementValue (ifds::TransId,        dstrTransId );
   _pRequestData->setElementValue (ifds::CompanyId,      getMgmtCoId( mgmtCoIdOut ) );
   _pRequestData->setElementValue (ifds::Track,          dstrTrack );
   _pRequestData->setElementValue (ifds::Activity,       dstrPageName );
  
	ReceiveData( DSTC_REQUEST::TRANS_DECIMALS_LIST_INQUIRY, 
				    *_pRequestData, 
					 ifds::DSTC0330_VW, 
                DSTCRequestor (getSecurity(), false));
   

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY TransDecimalsList::doCreateObject( const BFData &data, BFCBO *&pObjOut )
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("doCreateObject"));

   TransDecimals *pTransDecimals = new TransDecimals (*this);

   if (pTransDecimals->init( data ) <= WARNING)
   {
      pObjOut = pTransDecimals;
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
void TransDecimalsList::getStrKey( DString &dstrKey, const BFData *data )
{
   if( data ) 
   {    
      DString dstrDecimalType;
      dstrDecimalType = data->getElementValue( ifds::DecimalType );
            
      buildKey(   dstrKey, 
				      dstrDecimalType);
      
   }
   else
   {
      BFCBO::getStrKey( dstrKey, NULL);
   }
}

//******************************************************************************
void TransDecimalsList::buildKey(   DString &dstrKey, 
											   const DString &dstrDecimalType)
{
   DString dstrLocalDecimalType ( dstrDecimalType ); 
   	
	dstrKey = I_("DecimalType=") + dstrLocalDecimalType.stripAll().upperCase();

				 
}

//********************************************************************
SEVERITY TransDecimalsList::getTransDecimals( const DString &dstrDecimalType, 
															 const BFDataGroupId &idDataGroup,
															 TransDecimals *&pTransDecimals )
{
	MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("getTransDecimals"));

	pTransDecimals = NULL;

	DString dstrKey;	
	buildKey( dstrKey, 
				 dstrDecimalType );

	pTransDecimals = dynamic_cast<TransDecimals*>( getObject( dstrKey, idDataGroup ) );
	
	return GETCURRENTHIGHESTSEVERITY();
}

//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastcbo/TransDecimalsList.cpp-arc  $
// 
//    Rev 1.0   Mar 03 2005 14:42:36   aguilaam
// Initial revision.
// 

