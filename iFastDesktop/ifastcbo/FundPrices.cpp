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
// ^FILE   : FundPrices.cpp
// ^AUTHOR : 
// ^DATE   : 
//
// ^CLASS    : FundPrices
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "FundPrices.hpp"
#include "UnitFactorList.hpp"

#include <ifastdataimpl\dse_dstc0023_req.hpp>
#include <ifastdataimpl\dse_dstc0023_vw.hpp>

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = 
{
//  Field DD Id,					State Flags,			Group Flags 
   { ifds::UnitId,           BFCBO::NONE,                 0 }, 
};

static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );

namespace
{
   //Trace literals
   const I_CHAR * const CLASSNAME = I_("FundPrices");
}

namespace ifds
{
    extern CLASS_IMPORT const BFTextFieldId MultiPrices;
    extern CLASS_IMPORT const BFTextFieldId MultiPriceFund;
}

//******************************************************************************

FundPrices::FundPrices(BFAbstractCBO &parent)
: MFCanBFCbo (parent),
m_pUnitFactorList (NULL)
{
   TRACE_CONSTRUCTOR(CLASSNAME, NULL_STRING);
   registerMemberData( NUM_FIELDS, (const CLASS_FIELD_INFO *)&classFieldInfo, 0, NULL );
}

//******************************************************************************

FundPrices::~FundPrices()
{
   TRACE_DESTRUCTOR(CLASSNAME);
}

//******************************************************************************

SEVERITY FundPrices::init(const BFData &viewData)
{
   MAKEFRAME2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("init"));     

   attachDataObject(const_cast<BFData&>(viewData), false, true);
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************

SEVERITY FundPrices::initNew (const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "initNew" ) );
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
bool FundPrices::hasMultiplePrices(const BFDataGroupId & idDataGroup)
{
    DString dstrMultiPricesEnv, dstrMultiPriceFund, dstrTransType, priceCode2, priceCode3, priceCode4, priceCode5;

    getField(ifds::PriceCode2, priceCode2, idDataGroup, false);
    getField(ifds::PriceCode3, priceCode3, idDataGroup, false);
    getField(ifds::PriceCode4, priceCode4, idDataGroup, false);
    getField(ifds::PriceCode5, priceCode5, idDataGroup, false);
    getField(ifds::TransType, dstrTransType, idDataGroup, false);
    getField(ifds::MultiPriceFund, dstrMultiPriceFund, idDataGroup, false);

    getWorkSession().getOption(ifds::MultiPrices, dstrMultiPricesEnv, BF::HOST, false);

    bool foundMultiPrices = !priceCode2.stripAll().empty() ||
                            !priceCode3.stripAll().empty() ||
                            !priceCode4.stripAll().empty() ||
                            !priceCode5.stripAll().empty();
    
    return dstrMultiPricesEnv == I_("Y") && 
           dstrMultiPriceFund == I_("Y") &&
           foundMultiPrices && 
           dstrTransType.stripAll().upperCase() == I_("AV");
}

//******************************************************************************
SEVERITY FundPrices::getUnitFactorsList (UnitFactorList *&pUnitFactorList, const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("getUnitFactorsList"));

   if (!m_pUnitFactorList)
   {
      DString unitId;

      getField (ifds::UnitId, unitId, idDataGroup, false);
      m_pUnitFactorList = new UnitFactorList( *this );
      if (m_pUnitFactorList->init (unitId) >= SEVERE_ERROR)
      {
         delete m_pUnitFactorList;
         m_pUnitFactorList = NULL;
      }
   }
   pUnitFactorList = m_pUnitFactorList;
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/FundPrices.cpp-arc  $
// 
//    Rev 1.2   Nov 14 2004 14:42:56   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.1   Sep 17 2004 13:39:02   popescu
// PET1117 FN22 - revert fund factors dialog display to old logic
// 
//    Rev 1.0   Sep 09 2004 11:27:32   HERNANDO
// Initial revision.
*/