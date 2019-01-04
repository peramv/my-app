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
//    Copyright 1998 by DST Systems, Inc.
//
//
//******************************************************************************
//
// ^FILE   : FundMaster.cpp
// ^AUTHOR : Mike Metzger
// ^DATE   : Mar 5, 1999
//
// ^CLASS    : FundMaster
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "fundmaster.hpp"

#include "reinvestpurchaseschedule.hpp"

//fund master view
#include <ifastdataimpl\dse_dstc0063_vw.hpp>
#include <ifastdataimpl\dse_dstc0063_req.hpp>

namespace
{
   //Trace literals
   const I_CHAR * const CLASSNAME = I_ ("FundMaster");
}

namespace CND
{
   extern const long ERR_CAPPEDFUND_STATUSE;
   extern const long ERR_CAPPEDFUND_STATUSW;
}

namespace IFASTERR
{
   extern CLASS_IMPORT I_CHAR * const FUND_IS_CAPPED_VERIFY_IF_TRANSACTION_IS_ALLOWED;
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId FLongName;
   extern CLASS_IMPORT const BFTextFieldId FLongName2;
   extern CLASS_IMPORT const BFTextFieldId FShortName;
}
//******************************************************************************
FundMaster::FundMaster (BFAbstractCBO &parent) 
: MFCanBFCbo (parent)
{
   TRACE_CONSTRUCTOR (CLASSNAME , NULL_STRING);
}

//******************************************************************************
FundMaster::~FundMaster()
{
   TRACE_DESTRUCTOR (CLASSNAME);
}

//******************************************************************************
SEVERITY FundMaster::init (const BFData &viewData)
{
   MAKEFRAME2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("init"));

   attachDataObject (const_cast<BFData&> (viewData), false, true);
   return GETCURRENTHIGHESTSEVERITY();
}


//******************************************************************************
SEVERITY FundMaster::cappedFundRule ( const DString &effectiveDate, 
                                      const BFDataGroupId& idDataGroup
                                    )
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("cappedFundRule")
                         );

   if (isCappedFund (effectiveDate, idDataGroup))
   {
      DString fundCode;

      getField (ifds::FundCode, fundCode, idDataGroup);
      getErrMsg ( IFASTERR::FUND_IS_CAPPED_VERIFY_IF_TRANSACTION_IS_ALLOWED, 
                  CND::ERR_CAPPEDFUND_STATUSE, 
                  CND::ERR_CAPPEDFUND_STATUSW, 
                  idDataGroup,
                  I_("FUND=") + fundCode
                ); 
   }
   return GETCURRENTHIGHESTSEVERITY();
};

//******************************************************************************
bool FundMaster::isCappedFund ( const DString &effectiveDate, 
                                const BFDataGroupId &idDataGroup
                              )
{
   DString fundStatus, 
      statusDate;

   getField (ifds::FundStatus, fundStatus, idDataGroup, false);
   fundStatus.strip();
   getField (ifds::StatusDate, statusDate, idDataGroup, false);
   return 
         fundStatus == I_("02") &&
         DSTCommonFunctions::CompareDates (statusDate, effectiveDate) == DSTCommonFunctions::FIRST_EARLIER ||
         DSTCommonFunctions::CompareDates (statusDate, effectiveDate) == DSTCommonFunctions::EQUAL;
}

//******************************************************************************
SEVERITY FundMaster::getReinvestPurchaseSchedule ( ReinvestPurchaseSchedule *&pReinvestPurchaseSchedule,
                                                   const BFDataGroupId& idDataGroup
                                                 )
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("getReinvestPurchaseSchedule")
                         );
   pReinvestPurchaseSchedule = 
         dynamic_cast <ReinvestPurchaseSchedule*> ( getObject ( I_("ReinvestPurchaseSchedule"), 
                                                                idDataGroup
                                                              )
                                                  );
   if (!pReinvestPurchaseSchedule)
   {
      DString fundCode;
      
      getField (ifds::FundCode, fundCode, idDataGroup, false);
      pReinvestPurchaseSchedule = new ReinvestPurchaseSchedule (*this);
      if (pReinvestPurchaseSchedule->init (fundCode) <= WARNING)
      {
         setObject ( pReinvestPurchaseSchedule, 
                     I_("ReinvestPurchaseSchedule"), 
                     OBJ_ACTIVITY_NONE, 
                     idDataGroup
                   );
      }
      else
      {
         delete pReinvestPurchaseSchedule;
         pReinvestPurchaseSchedule = NULL;
      }
   }
   return GETCURRENTHIGHESTSEVERITY();
}

void FundMaster::getField( const BFFieldId& idField, 
                                 DString& strFieldValue,
                                 const BFDataGroupId& idDataGroup, 
                                 bool formattedReturn ) const
{
   BFFieldId idFieldNew = idField;
   if(idField == ifds::ElongName1 || idField == ifds::ElongName2 || idField == ifds::EShortName)
   {
     DString dstLocaleStr = ClientLocaleContext::get().getLocale();
     if(dstLocaleStr == I_("frCA"))
     {
        if(idField == ifds::ElongName1)
           idFieldNew = ifds::FLongName;
        else if (idField == ifds::ElongName2)
           idFieldNew = ifds::FLongName2;
        else if (idField == ifds::EShortName)
           idFieldNew = ifds::FShortName;
     }
   }
   BFCBO::getField( idFieldNew, strFieldValue, idDataGroup, formattedReturn);
}
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/fundmaster.cpp-arc  $
 // 
 //    Rev 1.17   Jun 06 2012 14:06:02   if991250
 // INA: using French fund names when French locales are on
 // 
 //    Rev 1.16   Nov 14 2004 14:42:44   purdyech
 // PET910 - .NET Conversion
 // 
 //    Rev 1.15   Nov 04 2004 17:37:42   popescu
 // PET 1117/06, Trade processing
 // 
 //    Rev 1.14   May 11 2004 15:49:18   popescu
 // PET 985, FN 01, LSIF Trade Entry, added handy methods to fund master list, to check whether a fund is LSIF/Money Market, GIC
 // 
 //    Rev 1.13   Apr 14 2004 14:54:46   VADEANUM
 // PTS 10029064/10028846 - Cash Date.
 // 
 //    Rev 1.12   Apr 01 2004 16:45:40   popescu
 // PTS 10021181, Systematic Purchases on Capped Funds,  consider the fund as a capped fund if the status date is equal to effective date, an addition to the already existing logic of being less then effective date
 // 
 //    Rev 1.11   Mar 21 2003 18:11:54   PURDYECH
 // BFDataGroupId/BFContainerId changeover
 // 
 //    Rev 1.10   Feb 06 2003 18:21:46   HSUCHIN
 // added method iscappedfund
 // 
 //    Rev 1.9   Oct 09 2002 23:54:34   PURDYECH
 // PVCS Database Conversion
 // 
 //    Rev 1.8   Aug 29 2002 12:55:56   SMITHDAV
 // ClientLocale and typed field changes.
 // 
 //    Rev 1.7   Jun 07 2002 17:46:42   KOVACSRO
 // Removed doformatfield
 // 
 //    Rev 1.6   22 May 2002 18:28:44   PURDYECH
 // BFData Implementation
 // 
 //    Rev 1.5   12 Mar 2002 09:52:48   WINNIE
 // Bug fix for Capped Fund
 // 
 //    Rev 1.4   20 Feb 2002 17:53:32   WINNIE
 // add capped fund logic : logic to be removed from systematic and trade
 // 
 //    Rev 1.3   10 May 2001 14:29:14   HSUCHIN
 // Sync up with SSB (1.1.1.0)
 // 
 //    Rev 1.2   03 May 2001 14:06:36   SMITHDAV
 // Session management restructuring.
 // 
 //    Rev 1.1   Dec 17 2000 20:23:28   OLTEANCR
 // changed to use a precompiled header
 // 
 //    Rev 1.0   Aug 03 2000 16:39:20   BUZILA
 // Initial revision.
 * 
*/