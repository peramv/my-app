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
// ^FILE   : ReinvestPurchaseSchedule.cpp
// ^AUTHOR : Serban Popescu 
// ^DATE   : October 2004
//
// ^CLASS    : ReinvestPurchaseSchedule
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "reinvestpurchaseschedule.hpp"
#include <ifastdataimpl\dse_dstc0310_req.hpp>
#include <ifastdataimpl\dse_dstc0310_vw.hpp>

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest REINVEST_PURCHASE_SCHEDULE;
}

namespace
{
   //Trace literals
   const I_CHAR * const CLASSNAME = I_("ReinvestPurchaseSchedule");
}

namespace CND
{
}

//******************************************************************************
ReinvestPurchaseSchedule::ReinvestPurchaseSchedule  (BFAbstractCBO &parent) 
: MFCanBFCbo (parent)
{
   TRACE_CONSTRUCTOR  (CLASSNAME , NULL_STRING);
   setObjectAsList ();
}

//******************************************************************************
ReinvestPurchaseSchedule::~ReinvestPurchaseSchedule ()
{
   TRACE_DESTRUCTOR (CLASSNAME);
}

//******************************************************************************
SEVERITY ReinvestPurchaseSchedule::init ( const DString &fundCode,
                                          const DString &dstrTrack, 
                                          const DString &dstrPageName
                                        )
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("init")
                         );

   BFData queryData (ifds::DSTC0310_REQ);

   DString mgmtCoIdOut;
   queryData.setElementValue (ifds::FundCode, fundCode);
   queryData.setElementValue (ifds::CompanyId, getMgmtCoId (mgmtCoIdOut));
   queryData.setElementValue (ifds::Track, dstrTrack);
   queryData.setElementValue (ifds::Activity, dstrPageName);

   ReceiveData ( DSTC_REQUEST::REINVEST_PURCHASE_SCHEDULE, 
                 queryData, 
                 ifds::DSTC0310_VW, 
                 DSTCRequestor (getSecurity (), true)
               );
   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
void ReinvestPurchaseSchedule::buildKey (const DString &calendarYear, DString &strKey)
{
   strKey = I_("Year=") + calendarYear;
   strKey.strip ();
   strKey.upperCase ();
}

//******************************************************************************
void ReinvestPurchaseSchedule::getStrKey  (DString &strKey, const BFData *data)
{
   TRACE_METHOD (CLASSNAME, I_("getStrKey"));

   if (data)
   {
      DString genKey;

      buildKey (data->getElementValue (ifds::CalendarYear), strKey);
      BFCBO::getStrKey (genKey, data);
      strKey = I_("Key=") + genKey + I_(";") + strKey;
   }
   else
   {
      BFCBO::getStrKey (strKey , NULL);
   }
}

//*****************************************************************************
bool ReinvestPurchaseSchedule::isDateWithinReinvestmentSchedule ( const DString &tradeDate, 
                                                                  const BFDataGroupId &idDataGroup
                                                                )
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("isDateWithinReinvestmentSchedule")
                         );

   bool bWithinDates = false;
   int year = 0;
   DString tempDate (tradeDate);
   BFDate date (tempDate, BFDate::DF_DDATE_DEPRECATED);   
   
   if (!tempDate.strip ().empty ())
   {
      year = date.getYear ();
   }
   if (year != 0)
   {
      BFObjIter bfIter (*this, BF::HOST);

      for (bfIter.begin(); !bfIter.end(); ++bfIter)
      {
         DString startDate,
            endDate,
            calendarYear;
         
         bfIter.getObject ()->getField (ifds::CalendarYear, calendarYear, idDataGroup, false);
         bfIter.getObject ()->getField (ifds::StartDate, startDate, idDataGroup, false);
         bfIter.getObject ()->getField (ifds::EndDate, endDate, idDataGroup, false);
         if ( calendarYear == asString (year) &&
              !startDate.empty() && 
              !endDate.empty()
            )
         {
            bWithinDates = 
                  ( DSTCommonFunctions::CompareDates (startDate, tradeDate) == DSTCommonFunctions::FIRST_EARLIER ||
                    DSTCommonFunctions::CompareDates (startDate, tradeDate) == DSTCommonFunctions::EQUAL
                  ) &&
                  ( DSTCommonFunctions::CompareDates (tradeDate, endDate) == DSTCommonFunctions::FIRST_EARLIER ||
                    DSTCommonFunctions::CompareDates (tradeDate, endDate) == DSTCommonFunctions::EQUAL
                  );
         }
         if (bWithinDates) //found a match
         {
            break;
         }
      }
   }
   return bWithinDates;
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/ReinvestPurchaseSchedule.cpp-arc  $
// 
//    Rev 1.3   Dec 03 2004 10:46:10   popescu
// PET 1117/06, fees processing
// 
//    Rev 1.2   Nov 14 2004 14:51:46   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.1   Nov 04 2004 17:38:28   popescu
// PET 1117/06, Trade processing
// 
//    Rev 1.0   Oct 29 2004 20:27:36   popescu
// Initial revision.
*/