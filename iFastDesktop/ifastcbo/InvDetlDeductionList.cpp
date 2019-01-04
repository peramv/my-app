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
// ^FILE   : InvDetlDeductionList.cpp
// ^AUTHOR : Monica Vadeanu
// ^DATE   : June, 2004
//
// ^CLASS    : InvDetlDeductionList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include "stdafx.h"
#include "InvDetlDeduction.hpp"
#include "InvDetlDeductionlist.hpp"

#include <ifastdataimpl\dse_dstc0329_req.hpp>                 // Deduction Inventory Inquiry
#include <ifastdataimpl\dse_dstc0329_vw.hpp>                  // Deduction Inventory Inquiry
#include <ifastdataimpl\dse_dstc0329_vwrepeat_record.hpp>     // Deduction Inventory Inquiry


namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest INVENTORY_DETAIL_DEDUCTION_LIST;
}

namespace
{
   // Trace literals
   const I_CHAR *  CLASSNAME  = I_("InvDetlDeductionList");
}

//******************************************************************************
InvDetlDeductionList::InvDetlDeductionList(BFAbstractCBO &parent)
: MFCanBFCbo(parent),
_pRequestData(NULL)
{
   TRACE_CONSTRUCTOR(CLASSNAME, NULL_STRING);
   setObjectAsList();
}

//******************************************************************************
InvDetlDeductionList::~InvDetlDeductionList()
{
   TRACE_DESTRUCTOR(CLASSNAME);
   if (_pRequestData != NULL)
   {
      delete _pRequestData;
   }
}


//******************************************************************************
SEVERITY InvDetlDeductionList::init( const DString &dstrTransId, 
											    const BFDataGroupId &idDataGroup,     // BF::HOST 
											    const DString& dstrTrack,             // I_( "N" )
											    const DString &dstrPageName )         // NULL_STRING );			
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("init"));

	   
  	//setFieldNoValidate (ifds::TransId, dstrTransId,  idDataGroup, false );
    	
   _pRequestData = new BFData (ifds::DSTC0329_REQ);

   DString mgmtCoIdOut;

   _pRequestData->setElementValue (ifds::TransId,        dstrTransId );
   _pRequestData->setElementValue (ifds::CompanyId,      getMgmtCoId( mgmtCoIdOut ) );
   _pRequestData->setElementValue (ifds::Track,          dstrTrack );
   _pRequestData->setElementValue (ifds::Activity,       dstrPageName );
  
	ReceiveData( DSTC_REQUEST::INVENTORY_DETAIL_DEDUCTION_LIST, 
				    *_pRequestData, 
					 ifds::DSTC0329_VW, 
                DSTCRequestor (getSecurity(), false));
   

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY InvDetlDeductionList::doCreateObject( const BFData &data, BFCBO *&pObjOut )
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("doCreateObject"));

   InvDetlDeduction *pInvDetlDeduction = new InvDetlDeduction (*this);

   if (pInvDetlDeduction->init( data ) <= WARNING)
   {
      pObjOut = pInvDetlDeduction;
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
void InvDetlDeductionList::getStrKey( DString &dstrKey, const BFData *data )
{
   if( data ) 
   {    
      DString dstrInvDetlId, dstrDeductCode;
      dstrInvDetlId = data->getElementValue( ifds::InvDetlId );
      dstrDeductCode = data->getElementValue( ifds::DeductCode );
            
      buildKey(   dstrKey, 
					   dstrInvDetlId,
				      dstrDeductCode);
      
   }
   else
   {
      BFCBO::getStrKey( dstrKey, NULL);
   }
}

//******************************************************************************
void InvDetlDeductionList::buildKey( DString &dstrKey, 
											    const DString &dstrInvDetlId,
						                   const DString &dstrDeductCode )
{
   DString dstrLocalInvDetlId  (dstrInvDetlId),
           dstrLocalDeductCode ( dstrDeductCode ); 
   	
	dstrKey = I_("InvDetlId=") + dstrLocalInvDetlId.stripAll() +
			    I_(";DeductCode=") + dstrLocalDeductCode.stripAll().upperCase();

				 
}


//******************************************************************************
SEVERITY InvDetlDeductionList::getMore()
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("getMore"));

   if (doMoreRecordsExist())
   {
      
      ReceiveData( DSTC_REQUEST::INVENTORY_DETAIL_DEDUCTION_LIST, 
						 *_pRequestData, 
						 ifds::DSTC0329_VW, 
						 DSTCRequestor(getSecurity(), false));
                   
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//********************************************************************
SEVERITY InvDetlDeductionList::getInvDetlDeduction( const DString &dstrInvDetlId, 
		                                              const DString &dstrDeductCode,
															       const BFDataGroupId &idDataGroup,
															       InvDetlDeduction *&pInvDetlDeduction )
{
	MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("getInvDetlDeduction"));

	pInvDetlDeduction = NULL;

	DString dstrKey;	
	buildKey( dstrKey, 
				 dstrInvDetlId,
				 dstrDeductCode );

	pInvDetlDeduction = dynamic_cast<InvDetlDeduction*>( getObject( dstrKey, idDataGroup ) );
	
	return GETCURRENTHIGHESTSEVERITY();
}

//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastcbo/InvDetlDeductionList.cpp-arc  $
// 
//    Rev 1.1   Feb 17 2005 13:15:44   aguilaam
// PET1198_FN01: LSIF Reason Code enhancement. 
// 
//    Rev 1.0   Jan 28 2005 13:53:10   aguilaam
// Initial revision.
// 
