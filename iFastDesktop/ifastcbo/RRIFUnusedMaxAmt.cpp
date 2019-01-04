//*****************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by International Financial Data Services
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2006 by International Financial Data Services
//
//*****************************************************************************
//
//    ^FILE   : RRIFUnusedMaxAmt.cpp
//    ^AUTHOR : Monica Vadeanu
//    ^DATE   : November, 2004
//    Copyright 2004 by International Financial Data Services
//
//-----------------------------------------------------------------------------
//
// ^CLASS  : RRIFUnusedMaxAmt
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS :
//
//*****************************************************************************
#include "stdafx.h"

#include "RRIFUnusedMaxAmt.hpp"

#include <ifastdataimpl\dse_dstc0375_req.hpp>
#include <ifastdataimpl\dse_dstc0375_vw.hpp>

// Constants
namespace 
{
   const I_CHAR * CLASSNAME = I_("RRIFUnusedMaxAmt");
}

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest RRIF_UNUSED_MAX_AMOUNT;
}

//******************************************************************************
RRIFUnusedMaxAmt::RRIFUnusedMaxAmt(BFAbstractCBO &parent) 
: MFCanBFCbo(parent)
{
   TRACE_CONSTRUCTOR(CLASSNAME , NULL_STRING);   
}

//******************************************************************************
RRIFUnusedMaxAmt::~RRIFUnusedMaxAmt()
{
   TRACE_DESTRUCTOR(CLASSNAME);
}

//******************************************************************************
SEVERITY RRIFUnusedMaxAmt::init( const DString &dstrAccount,
								 const DString &dstrEffectiveDate,
								 const DString &dstrRRIFId,
								 const DString &dstrOverrideUnusedMax,
								 const DString &dstrOverrideMndAmt,								 
							     const BFDataGroupId &idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("init"));
   
   _pRequestData = new BFData(ifds::DSTC0375_REQ);

   DString dstrMgmtCoIdOut;

   _pRequestData->setElementValue(ifds::AccountNum,        dstrAccount );      
   _pRequestData->setElementValue(ifds::EffectiveDate,     dstrEffectiveDate );      
   _pRequestData->setElementValue(ifds::RIFId,             dstrRRIFId );      
   _pRequestData->setElementValue(ifds::OverrideUnusedMax, dstrOverrideUnusedMax );      
   _pRequestData->setElementValue(ifds::OverrideMndAmt,    dstrOverrideMndAmt );      
   _pRequestData->setElementValue(ifds::CompanyId,         getMgmtCoId( dstrMgmtCoIdOut ) );
   _pRequestData->setElementValue(ifds::Track,             I_( "N" ) );   

   ReceiveData( DSTC_REQUEST::RRIF_UNUSED_MAX_AMOUNT, 
	            *_pRequestData, 
                ifds::DSTC0375_VW, 
				DSTCRequestor( getSecurity(), 
				false ) );   

   return GETCURRENTHIGHESTSEVERITY();            
}

//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastcbo/RRIFUnusedMaxAmt.cpp-arc  $
// 
//    Rev 1.0   Sep 06 2006 11:08:22   porteanm
// Initial revision.
// 
// 


