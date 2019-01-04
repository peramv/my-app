//*****************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by International Financial, Inc.,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2002 by International Financial, Inc.
//
//*****************************************************************************
//
// ^FILE   : ifastReportTrxnBuilder.cpp
// ^AUTHOR : 
// ^DATE   : Nov 18, 2002
//
//-----------------------------------------------------------------------------
//
// ^CLASS  : ifastReportTrxnBuilder
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS :
//
//*****************************************************************************

#include "stdafx.h"
#include "ifastreporttrxnbuilder.hpp"
#include "ifastcommonreportcriteria.hpp"
#include <ifastcbo\mgmtco.hpp>
#include <dataimpl\dse_dstc0220_req.hpp>
#include <dataimpl\dse_dstc0220_vw.hpp>
#include <ifastcbo\dstcworksession.hpp>

namespace
{
   const I_CHAR* CLASSNAME = I_( "ifastReportTrxnBuilder" );
   const I_CHAR* BUILDTRANSACTIONS = I_( "buildTransactions" );
}

namespace KEYTYPES
{
   extern CLASS_IMPORT I_CHAR * const ACCOUNTNUM;
}

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest REPORT_UPDATE;
}

//******************************************************************************
void ifastReportTrxnBuilder::buildTrxnKey( DString& strKey, ifastCommonReportCriteria* pifastCommonReportCriteria )
{
   DString dstrReportName;
   pifastCommonReportCriteria->getField( ifds::ReportName, dstrReportName, BF::HOST, true );
   //build the key    
   addIDITagValue( strKey, TRXNTAG::REPORTIDTAG, dstrReportName );   
}

//******************************************************************************
SEVERITY ifastReportTrxnBuilder::buildTransactions( DSTCWorkSession &workSession,
                                                 BFAbstractCBO* pObj,
                                                 HostTransactionContainer* pTrCont)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, BUILDTRANSACTIONS );

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastrptcbo/ifastReportTrxnBuilder.cpp-arc  $ 
// 
//    Rev 1.0   Nov 19 2002 11:28:20   HSUCHIN
// Initial Revision
*/