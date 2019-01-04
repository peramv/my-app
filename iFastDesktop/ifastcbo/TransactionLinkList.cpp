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
//    Copyright 2005 by International Financial.
//
//
//******************************************************************************
//
// ^FILE   : TransactionLinkList.cpp
// ^AUTHOR : Yingbao Li
// ^DATE   : June 30,2005
//
// ^CLASS    : TransactionLinkList 
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "TransactionLinkList.hpp"
#include <ifastdataimpl\dse_dstc0350_vw.hpp>
#include <ifastdataimpl\dse_dstc0350_req.hpp>

#include "mgmtco.hpp"
#include "mgmtcooptions.hpp"
#include "dstcommonfunction.hpp"

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest INTERNAL_TRANSLINK_LIST;
}

namespace  
{
   const I_CHAR * const CLASSNAME = I_ ("TransactionLinkList");  
}

//*********************************************************************************
TransactionLinkList::TransactionLinkList (BFAbstractCBO &parent)
: MFCanBFCbo (parent)
{
   TRACE_CONSTRUCTOR (CLASSNAME, NULL_STRING);
   setObjectAsList();
}
//*********************************************************************************
TransactionLinkList::~TransactionLinkList()
{
   TRACE_DESTRUCTOR (CLASSNAME);
}

//*********************************************************************************
SEVERITY TransactionLinkList::init (
                            const DString &dstrTransNum, 
                            const DString &dstrTrack,          /*= I_("N")*/
                            const DString &dstrPageName        /*= NULL_STRING*/
                         )

{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, 
                          CLASSNAME, 
                          I_("init")
                       );
   
   DString mgmtCoIdOut;   
   BFData requestData (ifds::DSTC0350_REQ);

   requestData.setElementValue (ifds::CompanyId, getMgmtCoId (mgmtCoIdOut));
   requestData.setElementValue (ifds::Track, dstrTrack);
   requestData.setElementValue (ifds::Activity, dstrPageName); 
   requestData.setElementValue (ifds::TransNum, dstrTransNum); 
	requestData.setElementValue( ifds::OverrideRepeats,   I_("25") );

   BFData *responseData = new BFData (ifds::DSTC0350_VW);

   ReceiveData ( DSTC_REQUEST::INTERNAL_TRANSLINK_LIST, 
                 requestData, 
                 *responseData, 
                 DSTCRequestor (getSecurity())
               );

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/TransactionLinkList.cpp-arc  $
// 
//    Rev 1.2   Jul 18 2005 15:19:54   Yingbaol
// PET1235,FN01:Pass overriderepeat
// 
//    Rev 1.1   Jul 15 2005 14:02:04   Yingbaol
// PEt1235,FN01: put the logic back after view is ready.
// 
//    Rev 1.0   Jul 06 2005 15:56:04   Yingbaol
// Initial revision.
// 

 */