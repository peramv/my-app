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
//    Copyright 2003 by IFDS, Inc.
//
//
//******************************************************************************
//
// ^FILE   : DSTCFinancialInstitutionTrxnBuilder.cpp
// ^AUTHOR : 
// ^DATE   : 
//
// ----------------------------------------------------------
//
// ^CLASS : DSTCFinancialInstitutionTrxnBuilder
//
// ^MEMBER VARIABLES :  
//
// ^CODING COMMENTS  :
//
//******************************************************************************
#include "stdafx.h"
#include "dstcfinancialinstitutiontrxnbuilder.hpp"
#include "dstclisttrxnbuilder.hpp"
#include <ifastcbo\financialinstitutionlistrepository.hpp>
#include <ifastcbo\financialinstitution.hpp>
#include <ifastcbo\financialinstitutionlist.hpp>
#include <ifastcbo\financialinstitutiontransit.hpp>
#include <ifastcbo\financialinstitutiontransitlist.hpp>

#include <ifastdataimpl\dse_dstc0264_req.hpp>
#include <ifastdataimpl\dse_dstc0264_vw.hpp>

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest FINANCIAL_INSTITUTION_LIST_UPDATE;
}

namespace
{
   const I_CHAR* CLASSNAME          = I_( "DSTCFinancialInstitutionTrxnBuilder" );
   const I_CHAR* BUILDTRANSACTIONS  = I_( "buildTransactions" );
}

namespace CND
{
}

extern BF_OBJ_TYPE OBJ_TYPE_FINANCIAL_INSTITUTION_LIST;
extern BF_OBJ_TYPE OBJ_TYPE_FINANCIAL_INSTITUTION_TRANSIT_LIST;

//******************************************************************************
void DSTCFinancialInstitutionTrxnBuilder::buildTrxnKey (DString &strKey)
{
}

//******************************************************************************
SEVERITY DSTCFinancialInstitutionTrxnBuilder::buildTransactions(
   DSTCWorkSession &workSession,
   BFAbstractCBO *pBFCBO, 
   HostTransactionContainer *pTrCont, 
   BF_OBJ_ACTIVITY objActivity /*= OBJ_ACTIVITY_NONE*/)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, BUILDTRANSACTIONS);

   FinancialInstitutionListRepository *pFinancialInstitutionListRepository = 
      dynamic_cast<FinancialInstitutionListRepository*>(pBFCBO);

   if (pFinancialInstitutionListRepository)
   {
      //see whether we have transits updates
      BFObjIter iter (*pFinancialInstitutionListRepository, BF::HOST);

      while (!iter.end())
      {
         const BF_OBJ_TYPE& objType = iter.getKey().getType();
         if (objType == OBJ_TYPE_FINANCIAL_INSTITUTION_LIST)
         {
            FinancialInstitutionList *pFinancialInstitutionList = 
               dynamic_cast<FinancialInstitutionList *>(iter.getObject());
            DSTCListTrxnBuilder<FinancialInstitution*> financialInstitutionTrxnBuilder;
            TRXNINFO financialInstitutionTrxnInfo(I_("AFinancialInstitutionList"), 
               DSTC_REQUEST::FINANCIAL_INSTITUTION_LIST_UPDATE,
               ifds::DSTC0264_REQ,
               ifds::DSTC0264_REQRepeat_Record,
               ifds::DSTC0264_VW);

            financialInstitutionTrxnBuilder.buildTransactions(workSession, pTrCont, 
               pFinancialInstitutionList, financialInstitutionTrxnInfo);
         }
         else if (objType == OBJ_TYPE_FINANCIAL_INSTITUTION_TRANSIT_LIST)
         {
            FinancialInstitutionTransitList *pFinancialInstitutionTransitList = 
               dynamic_cast<FinancialInstitutionTransitList *>(iter.getObject());
            DSTCListTrxnBuilder<FinancialInstitutionTransit*> financialInstitutionTransitTrxnBuilder;
            TRXNINFO financialInstitutionTransitTrxnInfo(I_("AFinancialInstitutionTransitList"), 
               DSTC_REQUEST::FINANCIAL_INSTITUTION_LIST_UPDATE,
               ifds::DSTC0264_REQ,
               ifds::DSTC0264_REQRepeat_Record,
               ifds::DSTC0264_VW);

            financialInstitutionTransitTrxnBuilder.buildTransactions (workSession, pTrCont, 
               pFinancialInstitutionTransitList, financialInstitutionTransitTrxnInfo);
         }
         ++iter;
      }
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/DSTCFinancialInstitutionTrxnBuilder.cpp-arc  $
// 
//    Rev 1.2   Nov 14 2004 14:32:30   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.1   Oct 24 2003 17:19:18   popescu
// CIBC PET 809, FN 13
// 
//    Rev 1.0   Oct 06 2003 15:38:56   popescu
// Initial revision.
// 
 */