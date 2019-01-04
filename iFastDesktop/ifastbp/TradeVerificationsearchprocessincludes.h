#pragma once
//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by DST Systems, Inc.,
//    are proprietary in nature and as such are confIdential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2002 by DST Systems, Inc.
//
//******************************************************************************

// Import/Export resolution
#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif
#include <ifastdataimpl\dse_dstc0053_vw.hpp>
#include <ifastdataimpl\dse_dstc0053_req.hpp>
#include <ifastdataimpl\dse_dstc0053_vwrepeat_record.hpp>
#include <ifastdataimpl\dse_dstc0463_req.hpp>
#include <ifastdataimpl\dse_dstc0463_reqrepeat_record.hpp>
#include <ifastdataimpl\dse_dstc0463_vw.hpp>
#include <ifastdataimpl\dse_dstc0463_vwrepeat_record.hpp>
#include <ifastdataimpl\dse_dstc0464_vw.hpp>
#include <ifastdataimpl\dse_dstc0464_req.hpp>
#include <ifastdataimpl\dse_dstc0464_vwrepeat_record.hpp>

namespace IFASTBP_PROC
{
   extern IFASTBP_LINKAGE const BFContainerId CRITERIA;
   extern IFASTBP_LINKAGE const BFContainerId TRADE_VERIFICATION_LIST;
   extern IFASTBP_LINKAGE const BFContainerId TRADE_OVERIDE_WARNINGS_LIST;
}
namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId TradeVerificationSearchHeading;
   extern CLASS_IMPORT const BFTextFieldId ValidTradeCriteria;
   extern CLASS_IMPORT const BFTextFieldId VerifyAll;
   extern CLASS_IMPORT const BFTextFieldId DeleteAll;
   extern CLASS_IMPORT const BFTextFieldId ExcludeVerifiedTrades;
   extern CLASS_IMPORT const BFTextFieldId VerifyTrade;
   extern CLASS_IMPORT const BFTextFieldId DeleteTrade;
}

