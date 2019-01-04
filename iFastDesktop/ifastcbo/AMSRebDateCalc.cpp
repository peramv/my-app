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
// ^FILE   : AMSRebDateCalc.cpp
// ^AUTHOR : May Lin
// ^DATE   : July 24, 2003
//
// ^CLASS    : AMSRebDateCalc 
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "AMSRebDateCalc.hpp"
#include <ifastdataimpl\dse_dstc0383_vw.hpp>
#include <ifastdataimpl\dse_dstc0383_req.hpp>

#include "mgmtco.hpp"
#include "mgmtcooptions.hpp"
#include "dstcommonfunction.hpp"

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest AMS_NEXT_PROC_DATE_INQUIRY;
}

namespace  
{
   const I_CHAR * const CLASSNAME = I_( "AMSRebDateCalc" );  
}

namespace CND
{
   extern CLASS_IMPORT const long ERR_DATA_NOT_FOUND;
}
////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

//*********************************************************************************
AMSRebDateCalc::AMSRebDateCalc( BFAbstractCBO &parent )
: MFCanBFCbo( parent )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );

}


//*********************************************************************************
AMSRebDateCalc::~AMSRebDateCalc()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//*********************************************************************************
SEVERITY AMSRebDateCalc::init( const DString& dstrEffectiveDate, 
                               const DString& dstrRebFreq,
                               const DString& dstrTrack,
                               const DString& dstrPageName)

{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init(DString&, DString&, DString&, DString&)" ) );
   DString mgmtCoIdOut;
   BFData RequestData(ifds::DSTC0383_REQ );
   RequestData.setElementValue( ifds::CompanyId, getMgmtCoId( mgmtCoIdOut ) );
   RequestData.setElementValue( ifds::Track, dstrTrack );
   RequestData.setElementValue( ifds::Activity, dstrPageName ); 
   RequestData.setElementValue( ifds::Deff, dstrEffectiveDate ); 
   RequestData.setElementValue( ifds::SchedSetupFreqID, dstrRebFreq ); 

   BFData *responseData = new BFData(ifds::DSTC0383_VW);
   DSTCRequestor requestor(getSecurity(), true, false );
   ReceiveData(DSTC_REQUEST::AMS_NEXT_PROC_DATE_INQUIRY, RequestData, *responseData, requestor);

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/AMSRebDateCalc.cpp-arc  $
// 
//    Rev 1.5   Jul 19 2007 14:23:46   smithdav
// PET2360 FN02 - Fix NextRebalanceDate recalc.
// 
//    Rev 1.4   Oct 20 2003 12:04:38   popescu
// Undid the previous change, see comments...
// 
//    Rev 1.3   Oct 19 2003 17:36:22   popescu
// Commented out assignement of DayOfWeek, a field part of  the request view, since it has been removed in Pre55
// 
//    Rev 1.2   Oct 03 2003 15:49:52   linmay
// PTS Ticket#10022366, schema change
// 
//    Rev 1.1   Jul 31 2003 13:56:22   linmay
// added amstype
// 
//    Rev 1.0   Jul 28 2003 11:17:54   linmay
// Initial Revision
// 
//  
 */