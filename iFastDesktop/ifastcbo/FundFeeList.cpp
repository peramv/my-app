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
// ^FILE   : FundFeeList.cpp
// ^AUTHOR : Yingbao Li
// ^DATE   : Feb. 1, 2002
//
// ^CLASS    : FundFeeList 
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "fundfeelist.hpp"
#include <ifastdataimpl\dse_dstc0197_vw.hpp>
#include <ifastdataimpl\dse_dstc0197_req.hpp>

#include "mgmtco.hpp"
#include "mgmtcooptions.hpp"
#include "dstcommonfunction.hpp"

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest FUND_FEE;
}

namespace  
{
   const I_CHAR * const CLASSNAME = I_ ("FundFeeList");  
   const I_CHAR * ACCOUNT_NUMBER_FIELD = I_ ("AccountNum");
}

//*********************************************************************************
FundFeeList::FundFeeList (BFAbstractCBO &parent)
: MFCanBFCbo (parent)
{
   TRACE_CONSTRUCTOR (CLASSNAME, NULL_STRING);
   setObjectAsList();
}


//*********************************************************************************
FundFeeList::~FundFeeList()
{
   TRACE_DESTRUCTOR (CLASSNAME);
}

//*********************************************************************************
SEVERITY FundFeeList::init (const DString &dstrFeeCode,
                            const DString &dstrFundCode, 
                            const DString &dstrClassCode,
                            const DString &dstrCommGroupCode,
                            const DString &dstrEffectiveDate,
                            const DString &dstrAcctNum,
                            const DString &dstrValidateType,
                            const DString &dstrFeeId,
                            const DString &dstrFamilyCode,     /*= NULL_STRING*/
                            const DString &dstrFundFrom,       /*= NULL_STRING*/
                            const DString &dstrClassFrom,      /*= NULL_STRING*/
                            const DString &dstrStopDate,       /*= NULL_STRING*/
                            const DString &dstrBrokerCode,     /*= NULL_STRING*/
                            const DString &dstrShGroup,        /*= NULL_STRING*/
                            const DString &dstrBranchCode,     /*= NULL_STRING*/
                            const DString &dstrSalesRepCode,   /*= NULL_STRING*/
                            const DString &dstrExclFeeCode,    /*= NULL_STRING*/
                            const DString &dstrFeeModelCode,   /*= NULL_STRING*/
                            const DString &dstrDistributionChannel,   /*= NULL_STRING*/
                            const DString &dstrTrack,          /*= I_("N")*/
                            const DString &dstrPageName        /*= NULL_STRING*/
                         )

{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, 
                          CLASSNAME, 
                          I_("init")
                       );
   
   DString mgmtCoIdOut;   
   BFData requestData (ifds::DSTC0197_REQ);

   requestData.setElementValue (ifds::CompanyId, getMgmtCoId (mgmtCoIdOut));
   requestData.setElementValue (ifds::Track, dstrTrack);
   requestData.setElementValue (ifds::Activity, dstrPageName); 
   requestData.setElementValue (ifds::FeeCode, dstrFeeCode); 
   requestData.setElementValue (ifds::FundCode, dstrFundCode); 
   requestData.setElementValue (ifds::ClassCode, dstrClassCode); 
   requestData.setElementValue (ifds::CommGroup, dstrCommGroupCode);
   requestData.setElementValue (ifds::EffectiveDate, dstrEffectiveDate); 
   requestData.setElementValue (ifds::AccountNum, dstrAcctNum); 
   requestData.setElementValue (ifds::FamilyCode, dstrFamilyCode); 
   requestData.setElementValue (ifds::FundFromCode, dstrFundFrom); 
   requestData.setElementValue (ifds::ClassFromCode, dstrClassFrom); 
   requestData.setElementValue (ifds::StopDate, dstrStopDate); 
   requestData.setElementValue (ifds::BrokerCode, dstrBrokerCode); 
   requestData.setElementValue (ifds::ShGroup, dstrShGroup); 
   requestData.setElementValue (ifds::ValidateType, dstrValidateType); 
   requestData.setElementValue (ifds::BranchCode, dstrBranchCode); 
   requestData.setElementValue (ifds::SlsrepCode, dstrSalesRepCode); 
   requestData.setElementValue (ifds::FeeID, dstrFeeId);
   requestData.setElementValue (ifds::ExclFeeCode, dstrExclFeeCode);
   requestData.setElementValue (ifds::FeeModelCode, dstrFeeModelCode);
   requestData.setElementValue (ifds::DistributionChannel, dstrDistributionChannel);
	
   BFData *responseData = new BFData (ifds::DSTC0197_VW);

   ReceiveData ( DSTC_REQUEST::FUND_FEE, 
                 requestData, 
                 *responseData, 
                 DSTCRequestor (getSecurity())
               );
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/FundFeeList.cpp-arc  $
// 
//    Rev 1.19   Oct 31 2011 10:12:00   kitticha
// PETP0186479 FN01 - IA Base Commission.
// 
//    Rev 1.18   Nov 23 2004 12:29:46   popescu
// PET 1117/56, added fee model code as parameter for request
// 
//    Rev 1.17   Nov 14 2004 14:42:22   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.16   Mar 18 2004 10:39:56   YINGBAOL
// PTS10021889:Add ExclFeeCode to view 197 
// 
//    Rev 1.15   Apr 04 2003 10:18:18   popescu
// split commsion work
// 
//    Rev 1.14   Apr 02 2003 13:36:06   YINGBAOL
// add FeeID
// 
//    Rev 1.13   Mar 18 2003 21:10:26   popescu
// Exchange out fee work
// 
//    Rev 1.12   Mar 10 2003 14:51:02   linmay
// modified init
// 
//    Rev 1.11   Feb 17 2003 10:24:18   YINGBAOL
// view change
// 
//    Rev 1.10   Jan 22 2003 18:00:40   YINGBAOL
// fix CommGroup
// 
//    Rev 1.9   Jan 20 2003 16:58:50   linmay
// rename FundGroup to CommGroup
// 
//    Rev 1.8   Jan 03 2003 16:25:20   linmay
// rename CommGroupCode to FundGroup
// 
//    Rev 1.7   Jan 02 2003 15:24:58   linmay
// modified getFundFeeObject, init
// 
//    Rev 1.6   Oct 09 2002 23:54:32   PURDYECH
// PVCS Database Conversion
// 
//    Rev 1.5   Aug 29 2002 12:55:56   SMITHDAV
// ClientLocale and typed field changes.
// 
//    Rev 1.4   22 May 2002 18:28:44   PURDYECH
// BFData Implementation
// 
//    Rev 1.3   Mar 05 2002 13:42:32   YINGBAOL
// change sort date
// 
//    Rev 1.2   Feb 22 2002 14:18:44   YINGBAOL
// more function added
// 
//    Rev 1.1   Feb 05 2002 11:02:40   YINGBAOL
// small fix
//
//    Rev 1.0   Feb 05 2002 10:50:36   YINGBAOL
// Initial revision.
//

 */