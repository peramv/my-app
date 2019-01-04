//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by International Financial Data Services,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2007, By International Financial Data Service
//
//
//******************************************************************************
//
// ^FILE   : AMSAcctLvl.cpp
// ^AUTHOR : Monica Porteanu
// ^DATE   : June 19, 2007
//
// ^CLASS    : AMSAcctLvl
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include "stdafx.h"

#include "amsacctlvl.hpp"

#include "amsfundalloclist.hpp"
#include "amslmtoverridelist.hpp"
#include "amslmtoverride.hpp"
#include "amsrebdatecalc.hpp"
#include "amsmstrinfo.hpp"
#include "amsmstrlist.hpp"
#include "brokeramssearch.hpp"
#include "brokerams.hpp"
#include "brokeramslist.hpp"
#include "currencylist.hpp"
#include "currency.hpp"
#include "datevalidation.hpp"
#include "DefAcctAllocList.hpp"
#include "DefFundAllocList.hpp"
#include "errmsgruleslist.hpp"
#include "frequency.hpp"
#include "frequencylist.hpp"
#include "fundmaster.hpp"
#include "fundmasterlist.hpp"
#include "funddetaillist.hpp"
#include "mgmtcooptions.hpp"
#include "mgmtco.hpp"
#include "mfaccount.hpp"

#include "mfaccountholdinglist.hpp"
#include "mfaccountlist.hpp"
#include "pendingtradelist.hpp"
#include "shareholder.hpp"
#include "shralloctypelist.hpp"
#include "systematiclist.hpp"

#include "AMSDeltaAllocList.hpp"
#include "AMSDeltaAlloc.hpp"

#include <bfutil\bfdate.hpp>

#include <ifastdataimpl\dse_dstc0083_vw.hpp>
#include <ifastdataimpl\dse_dstc0149_vw.hpp>
#include <ifastdataimpl\dse_dstc0179_vw.hpp>
#include <ifastdataimpl\dse_dstc0179_req.hpp>
#include <ifastdataimpl\dse_dstc0218_vw.hpp>
#include <ifastdataimpl\dse_dstc0219_req.hpp>
#include <ifastdataimpl\dse_dstc0219_vw.hpp>
#include <ifastdataimpl\dse_dstc0380_vw.hpp>   // AMS Account Inquiry
#include <ifastdataimpl\dse_dstc0380_req.hpp>  // AMS Account Inquiry
#include <ifastdataimpl\dse_dstc0380_vwrepeat_record.hpp>
#include <ifastdataimpl\dse_dstc0383_vw.hpp>   // AMS Next Process Date Inquiry
#include <ifastdataimpl\dse_dstc0383_req.hpp>  // AMS Next Process Date Inquiry
#include <ifastdataimpl\dse_dstc0384_req.hpp>
#include <ifastdataimpl\dse_dstc0384_vw.hpp>
#include <ifastdataimpl\dse_dstc0483_vw.hpp>

#include "amsfundalloc.hpp"

#include <conditions\iFastLayer\iFast\ifastcbo\IFast_IFast_ifastcbo_Err_stopping_ams_model_require_full_money_out_trade.h>
#include <conditions\iFastLayer\iFast\ifastcbo\IFast_IFast_ifastcbo_warn_stopping_ams_model_require_full_money_out_trade.h>

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest AMS_NEXT_PROC_DATE_INQUIRY;
   extern CLASS_IMPORT const DSTCRequest NON_EXCHANGABLE_FUNDS;
}

namespace
{
   // Trace literals
   const I_CHAR * const CLASSNAME      = I_( "AMSAcctLvl" );
   const I_CHAR * const YES            = I_( "Y" );
   const I_CHAR * const NO             = I_( "N" );
   const I_CHAR * const REBALANCE      = I_("RB");
   const I_CHAR * const TARGET_ASSET   = I_("R0");
   const I_CHAR * const BUSINESS_DATE  = I_( "3" );
   const I_CHAR * const PENDING        = I_( "0" );
   const I_CHAR * const CANCEL         = I_( "2" );
   const double dSmallValue            = .0000000001;

   const int FULL_LIST = 0;
   const I_CHAR * const RRIF_TAX_TYPE  = I_( "2" );
   const I_CHAR * const INACTIVE       = I_( "4" );
   const I_CHAR * const STOP           = I_( "3" );
   const I_CHAR * const BANKRUPTCY     = I_( "43" ); //IN2818924 - DSK_AMS Validation for CDIC
   const I_CHAR * const AMSDELTAALLOCLIST = I_( "AMSDeltaAllocList" );
   const I_CHAR * const MarketValueWeight = I_("M");
}

namespace CND
{
//   extern const long ERR_VALUE_CANNOT_BE_ZERO;
   extern const long ERR_ENTRY_EMPTY_OR_CONTAINS_ONLY_SPACE;
   extern const long ERR_VALUE_BETWEEN_0_AND_100;
   extern const long ERR_STOP_DATE_LESS_THAN_DEFF;
   extern const long ERR_DATE_CANNOT_EARLIER_THAN_CURRENT_BUSINESS_DATE;
   extern const long ERR_DATE_NOT_LAST_BUSINESS_DAY_OF_WEEK;
   extern const long ERR_DATE_CANNOT_GREATER_THAN_LAST_REB_DATE;
   extern const long ERR_GRAND_FATHER_DATE_CANNOT_EARLIER_THAN_EFFECTIVE_DATE;
   extern const long ERR_NEXT_REB_DATE_CANNOT_EARLIER_THAN_EFFECTIVE_DATE;
   extern const long ERR_DATE_MUST_BE_BUSINESS_DATE;

   extern const long ERR_INVALID_AMSCODE_REBALANCING_ASSET_MIX;
   extern const long ERR_INVALID_AMSCODE_TARGET_ASSET_MIX;
   extern const long ERR_REBALANCING_NOT_ALLOWED;
   extern const long ERR_AMS_GRAND_FATHER_DATED;
   extern const long ERR_AMS_CODE_FOR_BROKER_IS_BAD;
   extern const long ERR_AMS_CODE_NOT_AVAILABLE_FOR_BROKER;

   extern const long ERR_EFFECTIVE_DATE_BEFORE_CURBUSDATE;
   extern const long ERR_FUNDS_IN_ALLOC_NOT_EXCHANGABLE;
   extern const long ERR_DUPLICATE_RECORD;
   extern const long ERR_MIN_TWO_FUNDS;
   extern const long WARN_MIN_TWO_FUNDS;
   extern const long ERR_FUTURE_DATED_STOPDATE;
   extern const long WARN_FUTURE_DATED_STOPDATE;
   extern const long WARN_AMS_GAP_BETWEEN_RECCORDS;
   extern const long ERR_REBALANCING_STATUS;
   extern const long WARN_REBALANCING_STATUS;
   extern const long ERR_SYSTEM_REBALANCING_STATUS;
   extern const long WARN_ALLOC_CHANGE_RATE_OF_RETURN;
   extern const long WARN_EFFECTIVE_DATE_BEFORE_CURBUSDATE;
   extern const long ERR_CLOSED_COUNTRY_RESIDENT_FOR_MONEY_IN;
   extern const long ERR_BLANK_FREQENCY;
   extern const long ERR_FUND_CLASS_STOP_FLAG_ON; //IN2818924 - DSK_AMS Validation for CDIC
   extern const long ERR_THE_AMS_MODEL_ASSOCIATED_WITH_ANOTHER_ACCT_SAME_SHRHLDR;
   extern const long WARN_THE_AMS_MODEL_ASSOCIATED_WITH_ANOTHER_ACCT_SAME_SHRHLDR;
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId AcctDesignation;
   extern CLASS_IMPORT const BFTextFieldId AcctType;
   extern CLASS_IMPORT const BFTextFieldId BrokerCode;
   extern CLASS_IMPORT const BFTextFieldId ResProvCode;
   extern CLASS_IMPORT const BFNumericFieldId ShrNum;
   extern CLASS_IMPORT const BFTextFieldId TaxJurisCode;
   extern CLASS_IMPORT const BFTextFieldId TaxType;
   extern CLASS_IMPORT const BFTextFieldId EffectiveStopDate;
   extern CLASS_IMPORT const BFTextFieldId Rebalance;
   extern CLASS_IMPORT const BFTextFieldId UpdatePACSWP;
   extern CLASS_IMPORT const BFTextFieldId DefaultRebFreq;
   extern CLASS_IMPORT const BFTextFieldId NextRebDateApplicable;
   extern CLASS_IMPORT const BFIntegerFieldId AMSStat2;
   extern CLASS_IMPORT const BFDecimalFieldId RebalPrcnt;
   extern CLASS_IMPORT const BFTextFieldId AMSCurrency;
   extern CLASS_IMPORT const BFTextFieldId IsClosedCountryResident;
   extern CLASS_IMPORT const BFTextFieldId AMSCodeBuffer;
   extern CLASS_IMPORT const BFTextFieldId AcctStatus;

   extern CLASS_IMPORT const BFTextFieldId RebalDateFormat;
   extern CLASS_IMPORT const BFTextFieldId AMSRebalPending;
   extern CLASS_IMPORT const BFDateFieldId ActualRebalanceDate;
   extern CLASS_IMPORT const BFTextFieldId AMSRebReqMode;
   extern CLASS_IMPORT const BFTextFieldId AllocationUpdated;
}

namespace UAF
{
   extern CLASS_IMPORT I_CHAR * const AMS_STATUS_UPDATE;
   extern CLASS_IMPORT I_CHAR * const UPD_NEXT_REB_DATE;
   extern CLASS_IMPORT I_CHAR * const AMS_REBAL_REQ_ON_DEMAND;
}

namespace IFASTERR
{
   extern CLASS_IMPORT I_CHAR * const FUTURE_DATED_STOPDATE;
   extern CLASS_IMPORT I_CHAR * const REBALANCING_STATUS;
   extern CLASS_IMPORT I_CHAR * const ACCT_LVL_EFFECTIVE_DATE;
   extern CLASS_IMPORT I_CHAR * const THE_AMS_MODEL_ASSOCIATED_WITH_ANOTHER_ACCT_SAME_SHRHLDR;
   extern CLASS_IMPORT I_CHAR * const STOPPING_AMS_MODEL_REQUIRE_FULL_MONEY_OUT_TRADE;
}

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] =
{
   //  Field DD Id,              State Flags,       Group Flags
   { ifds::AMSCode,              BFCBO::REQUIRED,        0 },
   { ifds::AMSType,              BFCBO::REQUIRED,        0 },
   { ifds::Deff,                 BFCBO::NONE,            0 },
   { ifds::StopDate,             BFCBO::NONE,            0 },
   { ifds::NextProcessDate,      BFCBO::NONE,            0 },
   { ifds::LastProcessDate,      BFCBO::NONE,            0 },
   { ifds::FreqOverride,         BFCBO::NONE,            0 },
   { ifds::SchedSetupFreqID,     BFCBO::NONE,            0 },
   { ifds::AMSStat,              BFCBO::NONE,            0 },
   { ifds::ActivationDate,       BFCBO::NONE,            0 },
   { ifds::Currency,             BFCBO::NONE,            0 },
   { ifds::ThresholdPrcnt,       BFCBO::NONE,            0 },

   { ifds::Rebalance,            BFCBO::REQUIRED,        0 },
   { ifds::UpdatePACSWP,         BFCBO::REQUIRED,        0 },
//for quering existing allocations the shareholder number is needed.
   { ifds::ShrNum,               BFCBO::NONE,            0 },
   { ifds::EffectiveStopDate,    BFCBO::NONE,            0 },
   { ifds::AMSCodeBuffer,        BFCBO::NOT_ON_HOST,     0 },
   { ifds::AMSRebReqMode,        BFCBO::NONE,            0 },
   { ifds::ActualRebalanceDate,  BFCBO::CALCULATED_FIELD,0 },
   { ifds::TargetMixOption,		 BFCBO::NONE,			 0 },
   { ifds::AMSDeltaRequestUUID,  BFCBO::NONE,			 0 },
};

static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );

//******************************************************************************
AMSAcctLvl::AMSAcctLvl( BFAbstractCBO &parent )
: MFCanBFCbo( parent )
, bRecalcRebDate(true)
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   registerMemberData( NUM_FIELDS,
                       (const CLASS_FIELD_INFO *)&classFieldInfo,
                       0, NULL );

   addCrossEdit(ifds::EffectiveStopDate, ifds::Deff );
   addCrossEdit(ifds::EffectiveStopDate, ifds::StopDate );
}

//******************************************************************************
AMSAcctLvl::~AMSAcctLvl()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************
SEVERITY AMSAcctLvl::init( const BFData& data )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );
   attachDataObject(const_cast<BFData&>(data), false);

   commonInit( BF::HOST );

   DString dstrFreqOverride;
   getField (ifds::FreqOverride, dstrFreqOverride, BF::HOST, false );
//   if ( dstrFreqOverride == I_("1") ) {
//      setFieldReadOnly ( ifds::SchedSetupFreqID, BF::HOST, false );
//   } else {
//      setFieldReadOnly ( ifds::SchedSetupFreqID, BF::HOST, true );
//   }

   setFieldNoValidate( ifds::UpdatePACSWP, NO, BF::HOST );

   DString shrNum;

   getParent()->getField (ifds::ShrNum, shrNum, BF::HOST);
   setFieldNoValidate (ifds::ShrNum, shrNum, BF::HOST);


   DString dstrRebalStatus;
   getField (ifds::AMSStat, dstrRebalStatus, BF::HOST, false );

   if (dstrRebalStatus == INACTIVE)
   {
      DString dstrCurBusDate, dstrStopDate;
      getWorkSession().getOption( ifds::CurrBusDate, dstrCurBusDate, BF::HOST, false );

      getField (ifds::StopDate, dstrStopDate, BF::HOST, false );

      if (DSTCommonFunctions::CompareDates( dstrStopDate, dstrCurBusDate ) == DSTCommonFunctions::FIRST_EARLIER ||
         DSTCommonFunctions::CompareDates( dstrStopDate, dstrCurBusDate ) == DSTCommonFunctions::EQUAL) 
      {
         setFieldReadOnly( ifds::StopDate, BF::HOST, true);
         setFieldReadOnly( ifds::AMSStat, BF::HOST, true);
      }
   }


   //IN2818924 - DSK_AMS Validation for CDIC
   DString dstrFundCode, dstrClassCode;
   if(isAmsFundAllocAppliedBankruptcy( dstrFundCode,dstrClassCode , BF::HOST))
   {
      setFieldReadOnly( ifds::AMSCode, BF::HOST, true);
      setFieldReadOnly( ifds::AMSType, BF::HOST, true);
      setFieldReadOnly( ifds::Deff, BF::HOST, true);
      setFieldReadOnly( ifds::NextProcessDate, BF::HOST, true);
      setFieldReadOnly( ifds::LastProcessDate, BF::HOST, true);
      setFieldReadOnly( ifds::FreqOverride, BF::HOST, true); //checkbox
      setFieldReadOnly( ifds::AMSStat, BF::HOST, true);
      setFieldReadOnly( ifds::ActivationDate, BF::HOST, true);
      setFieldReadOnly( ifds::Rebalance, BF::HOST, true);
      setFieldReadOnly( ifds::UpdatePACSWP, BF::HOST, true);
      setFieldReadOnly( ifds::ThresholdPrcnt, BF::HOST, true);
      setFieldReadOnly( ifds::Currency, BF::HOST, true);
      setFieldReadOnly ( ifds::SchedSetupFreqID, BF::HOST, true );
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//*******************************************************************************
SEVERITY AMSAcctLvl::initNew(const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "initNew" ) );
   setObjectNew( );
   commonInit( idDataGroup );

   return GETCURRENTHIGHESTSEVERITY();
}

//*******************************************************************************
void AMSAcctLvl::doInitWithDefaultValues( const BFDataGroupId& idDataGroup )
{
   commonInit( idDataGroup );

   DString firstAMSType;
   DString dstrAMSFreqOvrd;
   
   getWorkSession().getOption( ifds::AMSFreqOvrd, dstrAMSFreqOvrd, idDataGroup, false );
   
   setAMSTypeSubstitutionList( idDataGroup, firstAMSType );
   setFieldNoValidate( ifds::AMSType, firstAMSType, idDataGroup );

   if (dstrAMSFreqOvrd == YES)
   {
      setFieldNoValidate (ifds::FreqOverride, I_("1"), idDataGroup );
      setAMSFrequencySubstSet(idDataGroup);
   }
   else
   {
      setFieldNoValidate( ifds::FreqOverride, I_("0"), idDataGroup );
   }

    DString dstrStopDate,  dstrCurrBusDate;

    getWorkSession().getOption (ifds::CurrBusDate, dstrCurrBusDate, idDataGroup, false);
    getWorkSession().getDateInHostFormat(dstrStopDate, DSTCWorkSession::DATE_TYPE::DAY12319999, idDataGroup);

   setFieldNoValidate( ifds::Deff, dstrCurrBusDate, idDataGroup );
   setFieldNoValidate( ifds::ActivationDate, dstrCurrBusDate, idDataGroup );
   setFieldNoValidate( ifds::StopDate, dstrStopDate, idDataGroup, false, true, true );


   setFieldNoValidate( ifds::Rebalance, YES, idDataGroup );
   setFieldNoValidate( ifds::UpdatePACSWP, NO, idDataGroup );

   setFieldNoValidate( ifds::ThresholdPrcnt, I_("0.00"), idDataGroup, true, false, false, false );

   DString companyCode (NULL_STRING);
   getWorkSession().getOption (ifds::CompanyCode, companyCode, idDataGroup, false);
   companyCode = companyCode.upperCase();
   if ( companyCode == I_("AIM") || companyCode == I_("ATS") )
   {
    setFieldNoValidate( ifds::AMSStat, I_("0"), idDataGroup );
   } else {
    setFieldNoValidate( ifds::AMSStat, I_("1"), idDataGroup );
   }
   DString shrNum;

   getParent()->getField (ifds::ShrNum, shrNum, idDataGroup);
   setFieldNoValidate (ifds::ShrNum, shrNum, idDataGroup);
}

//*******************************************************************************
SEVERITY AMSAcctLvl::commonInit (const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("commonInit" ));

   DString  lastProcessDate;

   getField (ifds::LastProcessDate,lastProcessDate,idDataGroup,false);

   setFieldReadOnly (ifds::AMSStat, idDataGroup, !getWorkSession().hasUpdatePermission (UAF::AMS_STATUS_UPDATE));
   bool bAMSCodeReadOnly = !isNew();
   MFAccount* pMFAccount = NULL;
   DString dstrAccountNum;
   getParent()->getField(ifds::AccountNum, dstrAccountNum, idDataGroup);

   DString dstrMstrActActive;
   getWorkSession().getOption( ifds::MstrActActive, dstrMstrActActive, BF::HOST, false );
   

   if (!bAMSCodeReadOnly && dstrMstrActActive.strip().upperCase() == I_("Y") &&
      getWorkSession().getMFAccount (idDataGroup, dstrAccountNum, pMFAccount) <= WARNING  && pMFAccount &&
      pMFAccount->hasAMSTrades(idDataGroup))
   {
      bAMSCodeReadOnly = true;
   }

   bool bIsMasterActWithOneChild = getWorkSession().isMasterActWithOneChild(idDataGroup);

   if (bIsMasterActWithOneChild && isNew())
   {
      // In the master account with one child environment, it support money-in with non-ams fund
      // while master account with multiple children environment won't.
      // when there is an non-ams asset under the account, it should allow to set up a new 
      // ams for the account

      bAMSCodeReadOnly = false;
   }

   setFieldReadOnly (ifds::AMSCode, idDataGroup, bAMSCodeReadOnly);
   
   setFieldReadOnly (ifds::AMSType, idDataGroup, !isNew());
   
   //IN 1154478 - open up the effective date   
   if (!(DSTCommonFunctions::CompareDates (lastProcessDate, I_("12319999")) == DSTCommonFunctions::EQUAL))
   {
      setFieldReadOnly (ifds::Deff, idDataGroup, !isNew());
   }
   
//   setFieldReadOnly( ifds::SchedSetupFreqID, idDataGroup, true );

   // enable UpdatePACSWP only when the item is new
   setFieldReadOnly(ifds::Rebalance, idDataGroup, isNew() ? false : !getWorkSession().hasUpdatePermission(UAF::AMS_REBAL_REQ_ON_DEMAND));

   setFieldReadOnly (ifds::UpdatePACSWP, idDataGroup, !isNew());

   // we may need to remove this line as well, this field 
   // will be opened to update regardless new or not
   //setFieldReadOnly (ifds::Rebalance,idDataGroup, !isNew());

   DString amsCode;

   getField (ifds::AMSCode, amsCode, idDataGroup, false);

   //when threshold override (ifds::OvrdRBLThrshld) is not active, do not allow override. Winnie, Feb. 8, 2008
   DString dstrOverrideThresholdPrcnt;
   getWorkSession().getOption( ifds::OvrdRBLThrshld, dstrOverrideThresholdPrcnt, BF::HOST, false );
   if (dstrOverrideThresholdPrcnt.strip().upperCase() == I_("Y"))
   {
      setFieldReadOnly (ifds::ThresholdPrcnt, idDataGroup, isAmsCodeGlobal(amsCode.strip(), idDataGroup));
   }
   else
   {
      setFieldReadOnly (ifds::ThresholdPrcnt, idDataGroup, true);
   }

   setFieldReadOnly ( ifds::LastProcessDate, idDataGroup, true );

   DString dstrApplicable;

   getWorkSession().getMgmtCoOptions()->getField (ifds::NextRebDateApplicable, dstrApplicable, idDataGroup ,false);
   bool bPermission = getWorkSession().hasUpdatePermission(UAF::UPD_NEXT_REB_DATE );
   bool bReadOnly = bPermission && dstrApplicable == YES ? false : true;

   setFieldReadOnly (ifds::NextProcessDate, idDataGroup, bReadOnly);
   setAMSFrequencySubstSet(BF::HOST);
   return GETCURRENTHIGHESTSEVERITY();
}

//*************************************************************************************
SEVERITY AMSAcctLvl::doValidateField( const BFFieldId& idField,
                                      const DString& strValue,
                                      const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("doValidateField" ));

   if (idField == ifds::EffectiveStopDate)
    {
      DString effDateStr,
              stopDateStr;

      getField (ifds::Deff, effDateStr, idDataGroup, false);
      getField (ifds::StopDate, stopDateStr, idDataGroup, false);

      // IN2818924 - DSK_AMS Validation for CDIC
      // DString dstrFundCode, dstrClassCode;
      // if(!isAmsFundAllocAppliedBankruptcy( dstrFundCode,dstrClassCode , idDataGroup) )
      // { 
      if (DSTCommonFunctions::CompareDates( stopDateStr, effDateStr ) == DSTCommonFunctions::FIRST_EARLIER )
      {
         ADDCONDITIONFROMFILE (CND::ERR_STOP_DATE_LESS_THAN_DEFF);
      }
      // }

      if (GETCURRENTHIGHESTSEVERITY() <= WARNING)
      {
         DString amsType;

         getField (ifds::AMSType, amsType, idDataGroup, false);
//ams should not overlap - check dates and type
         BFObjIter iterList (*getParent (), idDataGroup, true, BFObjIter::ITERTYPE::NON_DELETED);

         bool  hasStopDateBefore = false,
               hasEffDateAfter = false,
               stopOneDayBefore = false,
               effOneDayAfter = false;

         while (!iterList.end ())
         {
            AMSAcctLvl *pAMSAcctLvl = dynamic_cast <AMSAcctLvl*> (iterList.getObject ());

            if (pAMSAcctLvl && pAMSAcctLvl != this)
            {
               DString _effDateStr, _stopDateStr, _amsType;

               pAMSAcctLvl->getField (ifds::Deff, _effDateStr, idDataGroup, false);
               pAMSAcctLvl->getField (ifds::StopDate, _stopDateStr, idDataGroup, false);
               pAMSAcctLvl->getField (ifds::AMSType, _amsType, idDataGroup, false);
               if (amsType == _amsType)
               {
	
                  //effDate and stopDate are the date of current object
                  //_effDate and _stopDate are the date of object in the list
                  BFDate effDate(effDateStr,BFDate::DF_HOST),
                        stopDate(stopDateStr,BFDate::DF_HOST),
                        _effDate(_effDateStr,BFDate::DF_HOST),
                        _stopDate(_stopDateStr,BFDate::DF_HOST);
                  if(!(stopDate < _effDate || _stopDate < effDate))
                  {
                     ADDCONDITIONFROMFILE (CND::ERR_DUPLICATE_RECORD);
                     break;
                  } // if(!(stopDate < _effDate || _stopDate < effDate))

                  if(_stopDate<effDate)
                  {
                     hasStopDateBefore = true;
                     // There is a record that has stop date 1 day prior the current reccord's effective date.
                     if((_stopDate+1) == effDate )
                     {
                        stopOneDayBefore = true;
                     }
                  } // if(_stopDate<effDate)

                  if(stopDate<_effDate)
                  {
                     hasEffDateAfter = true;
                     // There is a record that has effective date 1 day after the current reccord's stop date.
                     if( (stopDate +1 ) == _effDate )
                     {
                        effOneDayAfter = true;
                     }
                  } // if(stopDate<_effDate)

                  /*
                  if (DSTCommonFunctions::CompareDates (stopDateStr, _effDateStr) == DSTCommonFunctions::FIRST_EARLIER ||
                      DSTCommonFunctions::CompareDates (_stopDateStr, effDateStr) == DSTCommonFunctions::FIRST_EARLIER)
                  {
                     ; //no overlapping
                  }
                  else
                  {
                     ADDCONDITIONFROMFILE (CND::ERR_DUPLICATE_RECORD);
                     break;
                  }
                  */
               }
            } // if (pAMSAcctLvl && pAMSAcctLvl != this)
            ++iterList;
         } // while (!iterList.end ())

         if(hasStopDateBefore && (!stopOneDayBefore))
         {
            ADDCONDITIONFROMFILE (CND::WARN_AMS_GAP_BETWEEN_RECCORDS);
         }

         if(hasEffDateAfter && (!effOneDayAfter))
         {
            ADDCONDITIONFROMFILE (CND::WARN_AMS_GAP_BETWEEN_RECCORDS);
         }
      }
    }
   else if ( idField == ifds::NextProcessDate )
   {
      validateNextRebDate( strValue, idDataGroup );
   }
   else if (idField == ifds::ActualRebalanceDate)
   {
      validateNextRebDate( strValue, idDataGroup );
   }
   else if( idField == ifds::AMSType )
   {
      validateAMSType( strValue, idDataGroup );
   }
   else if( idField == ifds::AMSCode )
   {
      validateAMSCode( strValue, idDataGroup );

      //IN2818924 - DSK_AMS Validation for CDIC
      DString dstrFundCode, dstrClassCode;

      if( isAmsFundAllocAppliedBankruptcy(dstrFundCode,dstrClassCode,idDataGroup) )
      {
         DString idiStr;  
         addIDITagValue( idiStr, I_("TRADE_TYPE"), I_(" ") );
         addIDITagValue( idiStr, I_("FUND"), dstrFundCode );
         addIDITagValue( idiStr, I_("CLASS"), dstrClassCode );
         ADDCONDITIONFROMFILEIDI( CND::ERR_FUND_CLASS_STOP_FLAG_ON, idiStr );
      }

   }
   else if( idField == ifds::ThresholdPrcnt )
   {
      validateThresholdPrcnt( strValue, idDataGroup );
   }
   else if ( idField == ifds::SchedSetupFreqID )
   {
      //validateSchedSetupFreqID( strValue, idDataGroup );
   }
   else if ( idField == ifds::Deff )
   {
      validateEffectiveDate(strValue, idDataGroup);
   }
   else if ( idField == ifds::StopDate )
   {
      validateStopDate(strValue, idDataGroup);
   }
   else if (idField == ifds::AMSStat)
   {
      if (strValue == PENDING || strValue == CANCEL)
      {
         getErrMsg ( IFASTERR::REBALANCING_STATUS, 
                     CND::ERR_REBALANCING_STATUS, 
                     CND::WARN_REBALANCING_STATUS, 
                     idDataGroup); 

         validateAgainstStopStatus (idDataGroup);
      }
      else if (strValue == INACTIVE)
      {
         ADDCONDITIONFROMFILE (CND::ERR_SYSTEM_REBALANCING_STATUS);

         validateAgainstStopStatus (idDataGroup);
      }
      else if (strValue == STOP)
      {
         validateAgainstStopStatus (idDataGroup);
      }
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//*******************************************************************************
SEVERITY AMSAcctLvl::doValidateAll( const BFDataGroupId& idDataGroup, long lValidateGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doValidateAll" ) );

   DefFundAllocList *pFundAllocList = NULL;

   DString dstrFreq;

   getField(ifds::SchedSetupFreqID, dstrFreq, idDataGroup, false);
   validateSchedSetupFreqID( dstrFreq, idDataGroup );

   if ( getAMSAcctLvlAllocation (pFundAllocList, idDataGroup, false) <= WARNING &&
        pFundAllocList)
   {

      if( pFundAllocList->isUpdatedForDataGroup( idDataGroup ) )
      {
         DString dstrEffectiveDate, dstrCurBusDate;
         getField(ifds::Deff, dstrEffectiveDate, idDataGroup, false);
         getWorkSession().getOption( ifds::CurrBusDate, dstrCurBusDate, idDataGroup, false );
         if ( DSTCommonFunctions::CompareDates( dstrEffectiveDate, dstrCurBusDate ) == DSTCommonFunctions::FIRST_EARLIER )
         {
            ADDCONDITIONFROMFILE (CND::WARN_ALLOC_CHANGE_RATE_OF_RETURN);
         }
      }
      BFObjIter iter (*pFundAllocList, idDataGroup, true, BFObjIter::ITERTYPE::NON_DELETED);
      iter.begin();

      DString amsType;

      getField (ifds::AMSType, amsType, idDataGroup, false);
      if (iter.getNumberOfItemsInList () <= 1 && amsType == I_("RB"))
      {
//         ADDCONDITIONFROMFILE (CND::ERR_MIN_TWO_FUNDS);
//should add a rej-error
         ADDCONDITIONFROMFILE (CND::WARN_MIN_TWO_FUNDS);
      }

      if (GETCURRENTHIGHESTSEVERITY() <= WARNING)
      {
         DString dstrFundCodeSet (NULL_STRING),
         dstrClassCodeSet(NULL_STRING);
         bool first=true;
         DString dstrStopDate;
         DString dstrCurBusDate;

         getField (ifds::StopDate, dstrStopDate, idDataGroup, false);
         getWorkSession().getOption( ifds::CurrBusDate, dstrCurBusDate, idDataGroup, false );

         if (!dstrStopDate.empty ())
         {
            if (DSTCommonFunctions::CompareDates ( dstrStopDate, dstrCurBusDate ) == DSTCommonFunctions::FIRST_EARLIER ||
               DSTCommonFunctions::CompareDates ( dstrStopDate, dstrCurBusDate ) == DSTCommonFunctions::EQUAL)
            {
               return GETCURRENTHIGHESTSEVERITY();
            }
         }

         while (!iter.end())
          {
            DString dstrFundCode,
               dstrClassCode;

            iter.getObject()->getField( ifds::FundCode, dstrFundCode,     idDataGroup );
             iter.getObject()->getField( ifds::ClassCode, dstrClassCode,     idDataGroup );
            if (!dstrFundCode.empty () && !dstrClassCode.empty())
            {
               if ( first ) {
                  first = false;
               }else {
                  dstrFundCodeSet += I_(",");
                  dstrClassCodeSet += I_(",");
               }
               dstrFundCodeSet += dstrFundCode;
               dstrClassCodeSet += dstrClassCode;
            }
            ++iter;
          }
         if (!dstrFundCodeSet.empty() && !dstrClassCodeSet.empty())
         {
            BFData requestData (ifds::DSTC0384_REQ);
            BFData *responseData = new BFData(ifds::DSTC0384_VW);

            DString mgmtCoIdOut;
            requestData.setElementValue (ifds::FundCode, dstrFundCodeSet);
            requestData.setElementValue (ifds::ClassCode, dstrClassCodeSet);
            requestData.setElementValue (ifds::CompanyId, getMgmtCoId (mgmtCoIdOut));
            requestData.setElementValue (ifds::Track, I_("N"));
            requestData.setElementValue (ifds::Activity, NULL_STRING);

            if (BFDataBroker::getInstance ()->receive ( DSTC_REQUEST::NON_EXCHANGABLE_FUNDS,
                                                      requestData,
                                                      *responseData,
                                                      DSTCRequestor (getSecurity ())) <= WARNING)
            {
               int rCount = (int)responseData->getRepeatCount();
               for ( int i=0; i<rCount; i++ ) {
                  const BFData &repeat = responseData->getRepeat(i);
                  DString idiStr;

                  addIDITagValue (idiStr, I_("TO_FUND"), repeat.getElementValue( ifds::ToFund ).strip());
                  addIDITagValue (idiStr, I_("TO_CLASS"), repeat.getElementValue( ifds::ToClass ).strip());
                  addIDITagValue (idiStr, I_("FROM_FUND"), repeat.getElementValue( ifds::FromFund ).strip());
                  addIDITagValue (idiStr, I_("FROM_CLASS"), repeat.getElementValue( ifds::FromClass ).strip());
                  ADDCONDITIONFROMFILEIDI (CND::ERR_FUNDS_IN_ALLOC_NOT_EXCHANGABLE, idiStr);
               }
            }
         }
      }

      DString dstrTargetMixOpt;
      getField(ifds::TargetMixOption, dstrTargetMixOpt, idDataGroup, false);
      if(dstrTargetMixOpt == MarketValueWeight)
      {
        AMSDeltaAllocList* pAMSDeltaAllocList;
        getAMSDeltaAllocList(pAMSDeltaAllocList,idDataGroup);

        bool bIsAMSUpdated = isUpdated(false);
        bool bIsAMSFundUpdated = pFundAllocList->isUpdated();
        if(pAMSDeltaAllocList && (bIsAMSUpdated || bIsAMSFundUpdated))
        {
          setObject(NULL, AMSDELTAALLOCLIST, OBJ_ACTIVITY_NONE, idDataGroup);
        }
      }	  
   }

   if (!isNew()) //for exsiting ams records...
   {
      validateAccountClosedCountry (idDataGroup);
   }
   return GETCURRENTHIGHESTSEVERITY();
}


//*******************************************************************************
//NextRebDate must be on a business date
//Next rebalance date must be earlier than the last rebalancing date.
//Next reblance date must not be less than the current business date for existing AMS code.
//Next rebalance date must be greater than current business date if it is a new AMS code.
//Next Rebalance Date can not be earlier than the effective date of ams master record
//Edit check to provide warning if the Next rebalancing date is not the last busniess day of a week.
SEVERITY AMSAcctLvl::validateNextRebDate(const DString& strValue, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2  (CND::IFASTCBO_CONDITION, CLASSNAME, I_("validateNextRebDate" ));

   DString dstrNextRebDate(strValue), 
      dstrLastRebDate, 
      dstrCurBusDate;
   dstrNextRebDate.strip();

   if (DSTCommonFunctions::CompareDates (I_("12319999"), dstrNextRebDate) != DSTCommonFunctions::EQUAL)
   {
      getField (ifds::LastRebDate, dstrLastRebDate, idDataGroup, false);
      dstrLastRebDate.strip();
      if ( !dstrLastRebDate.empty() && DSTCommonFunctions::CompareDates( dstrNextRebDate, dstrLastRebDate ) != DSTCommonFunctions::FIRST_EARLIER )
      {
         ADDCONDITIONFROMFILE( CND::ERR_DATE_CANNOT_GREATER_THAN_LAST_REB_DATE );
         return GETCURRENTHIGHESTSEVERITY();
      }

      getWorkSession().getOption( ifds::CurrBusDate, dstrCurBusDate, idDataGroup, false );
      if ( DSTCommonFunctions::CompareDates( dstrNextRebDate, dstrCurBusDate ) == DSTCommonFunctions::FIRST_EARLIER ) {
         ADDCONDITIONFROMFILE( CND::ERR_DATE_CANNOT_EARLIER_THAN_CURRENT_BUSINESS_DATE );
         return GETCURRENTHIGHESTSEVERITY();
      }

      DString dstrEffectiveDate;
      getField(ifds::Deff, dstrEffectiveDate, idDataGroup);
      if( DSTCommonFunctions::CompareDates( dstrNextRebDate, dstrEffectiveDate )
            != DSTCommonFunctions::SECOND_EARLIER ) {
         ADDCONDITIONFROMFILE( CND::ERR_NEXT_REB_DATE_CANNOT_EARLIER_THAN_EFFECTIVE_DATE );
      }


      if ( !isBusinessDate(strValue, idDataGroup) ) {
            DString idiStr;

            addIDITagValue( idiStr, I_("FIELDNAME"), I_("Next Rebalance Date" ));
            ADDCONDITIONFROMFILEIDI( CND::ERR_DATE_MUST_BE_BUSINESS_DATE, idiStr );
            return GETCURRENTHIGHESTSEVERITY();
      }

      if ( !isLastBusDayOfWeek(strValue, idDataGroup)) {
         ADDCONDITIONFROMFILE( CND::ERR_DATE_NOT_LAST_BUSINESS_DAY_OF_WEEK );
      }
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY AMSAcctLvl::validateAMSCode( const DString& strValue, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateAMSCode" ) );

   DString dstrAMSCode (strValue);
   dstrAMSCode.strip().upperCase ();

   if (dstrAMSCode.empty()) 
   {
      return GETCURRENTHIGHESTSEVERITY();
   }

   DString dstrAccountNum;
   getParent()->getField (ifds::AccountNum, dstrAccountNum, idDataGroup);

   MFAccount* pMFAccount = NULL;
   if (getWorkSession().getMFAccount (idDataGroup, dstrAccountNum, pMFAccount) <= WARNING  && pMFAccount)
   {
      if (!pMFAccount->isAMSAnOption (idDataGroup)) 
      {
         // "Not allowed to set Rebalancing AMS Code"
         ADDCONDITIONFROMFILE (CND::ERR_REBALANCING_NOT_ALLOWED);
      }

      if (GETCURRENTHIGHESTSEVERITY() <= WARNING)
      {
         DString dstrAMSType;
         getField (ifds::AMSType, dstrAMSType, idDataGroup, false);

         AmsMstrInfo *pAmsMstrInfo = NULL;

         if (getAMSMasterInfo (pAmsMstrInfo, idDataGroup) <= WARNING &&
             pAmsMstrInfo)
         {
            if (pAmsMstrInfo->isGrandFatherDateStamped (idDataGroup))
            {
               ADDCONDITIONFROMFILE (CND::ERR_AMS_GRAND_FATHER_DATED);
            }
            if (GETCURRENTHIGHESTSEVERITY() <= WARNING)
            {
               if (dstrAMSType == REBALANCE)
               {
                  validateAMSRestrictions (pAmsMstrInfo, pMFAccount, idDataGroup);
                  validateAMSCodeWithUnderSameShr(strValue, pMFAccount, idDataGroup);
               }
            }
         }
         else
         {
            if (dstrAMSType == REBALANCE)
            {
               ADDCONDITIONFROMFILE (CND::ERR_INVALID_AMSCODE_REBALANCING_ASSET_MIX);
            }
            else
            {
               ADDCONDITIONFROMFILE (CND::ERR_INVALID_AMSCODE_TARGET_ASSET_MIX);
            }
         }
         validateAMSRestrictionForBrokers( dstrAMSCode, pMFAccount, idDataGroup );
      }
   }  
  
   validateAccountClosedCountry (idDataGroup);
   
   return GETCURRENTHIGHESTSEVERITY();
}

//************************************************************************************
SEVERITY AMSAcctLvl::validateAMSRestrictions ( AmsMstrInfo* pAmsMstrInfo,
                                               MFAccount* pMFAccount,
                                               const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("validateAMSRRIF"));

   DString dstrAcctType,
      dstrTaxJuris,
      dstrResProv,
      dstrAcctDes,
      dstrShrNum,
      dstrTaxType;

   pMFAccount->getField (ifds::TaxType, dstrTaxType, idDataGroup, false);
   dstrTaxType.strip();
   pMFAccount->getField (ifds::AcctType, dstrAcctType, idDataGroup, false);
   dstrAcctType.strip().upperCase();
   pMFAccount->getField (ifds::AcctDesignation, dstrAcctDes, idDataGroup, false);
   dstrAcctDes.strip().upperCase();
   pMFAccount->getField (ifds::ShrNum, dstrShrNum, idDataGroup, false);
   dstrShrNum.strip();
   Shareholder* pShaholder (NULL);
   getWorkSession().getShareholder (idDataGroup, dstrShrNum, pShaholder);
   if (pShaholder)
   {
      pShaholder->getField (ifds::TaxJurisCode, dstrTaxJuris, idDataGroup, false);
      dstrTaxJuris.strip().upperCase();
      pShaholder->getField (ifds::ResProvCode,dstrResProv,idDataGroup,false );
      dstrResProv.strip().upperCase();
   }
   pAmsMstrInfo->canPurchase( dstrTaxJuris, dstrResProv, dstrAcctType, dstrTaxType,
                              dstrAcctDes, idDataGroup);
   pAmsMstrInfo->canRedeem( dstrTaxJuris, dstrResProv, dstrAcctType, dstrTaxType,
                            dstrAcctDes,  idDataGroup);
   pAmsMstrInfo->canTransferIn( dstrTaxJuris, dstrResProv, dstrAcctType, dstrTaxType,
                                dstrAcctDes,  idDataGroup);
   pAmsMstrInfo->canTransferOut( dstrTaxJuris, dstrResProv, dstrAcctType, dstrTaxType,
                                 dstrAcctDes,  idDataGroup);
   return  GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY AMSAcctLvl::validateAMSRestrictionForBrokers( const DString&  dstrAMSCode,
                                                       MFAccount* pMFAccount,
                                                       const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "ValidateAMSRestrictionForBrokers" ) );

   DString dstrRestrictAMSBroker;
   DString dstrBrokerCode;

   if( getWorkSession().getOption( ifds::RestrictAMSBroker, dstrRestrictAMSBroker, idDataGroup, false ) <= WARNING &&
         I_("Y") == dstrRestrictAMSBroker )
   {
      BrokerAMSsearch *pBrokerAMSsearch = NULL;
      if ( getWorkSession().getBrokerAMSsearch( pBrokerAMSsearch, idDataGroup, true ) <= WARNING &&
           NULL != pBrokerAMSsearch )
      {
         // Get Broker Code
         pMFAccount->getField( ifds::BrokerCode, dstrBrokerCode, idDataGroup, false );
         BrokerAMSList *pBrokerAMSList = NULL;
         if ( pBrokerAMSsearch->getBrokerAMSList( pBrokerAMSList, idDataGroup, dstrBrokerCode,  dstrAMSCode) <= WARNING &&
              NULL != pBrokerAMSList )
         {
            BrokerAMS *pBrokerAMS = NULL;
            // Find Good BrokerAMS
            if ( pBrokerAMSList->getBrokerAMS( dstrAMSCode, I_( "Y" ), idDataGroup, pBrokerAMS ) <= WARNING &&
               NULL != pBrokerAMS )
            {
               pBrokerAMS->validateBrokerAMSDeff( idDataGroup );
            }
            // else if only Bad record exists, throw an error
            else if ( pBrokerAMSList->getBrokerAMS( dstrAMSCode, I_( "N" ), idDataGroup, pBrokerAMS ) <= WARNING &&
               NULL != pBrokerAMS )
            {
               // no good record available
               DString dstrIDITagValue;
               addIDITagValue( dstrIDITagValue, I_( "BROKER_CODE") , dstrBrokerCode );
               ADDCONDITIONFROMFILEIDI( CND::ERR_AMS_CODE_FOR_BROKER_IS_BAD, dstrIDITagValue );

            }
            // else no Broker AMS available
            else if ( NULL == pBrokerAMS )
            {
               DString dstrIDITagValue;
               addIDITagValue( dstrIDITagValue, I_( "BROKER_CODE") , dstrBrokerCode );
               ADDCONDITIONFROMFILEIDI( CND::ERR_AMS_CODE_NOT_AVAILABLE_FOR_BROKER, dstrIDITagValue );
            }
         }
      }
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//************************************************************************************
SEVERITY AMSAcctLvl::validateAMSType( const DString& dstrAMSType, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateAMSType" ) );

   if ( dstrAMSType == REBALANCE )
   {
      DString dstrAccountNum;
      getParent()->getField(ifds::AccountNum, dstrAccountNum, idDataGroup);
      MFAccount* pMFAccount = NULL;
      DefFundAllocList *pFundAllocList = NULL;
      getAMSAcctLvlAllocation ( pFundAllocList, idDataGroup, false);
      if( getWorkSession().getMFAccount( idDataGroup, dstrAccountNum, pMFAccount) <= WARNING  && pMFAccount  )
      {
         pMFAccount->validateAMSForStopPurchaseRedeem (idDataGroup);
         //pMFAccount->validateAMSForEscrow (idDataGroup);
         pMFAccount->validateAMSforCertificates(idDataGroup,pFundAllocList);
         pMFAccount->validateAMSForInstitutionalCode (idDataGroup);
         pMFAccount->validateAMSRBForFundCurrency (idDataGroup);
         pMFAccount->validateAMSRBForPendingPAC (idDataGroup);
         pMFAccount->validateAMSRBForGICFund (idDataGroup);
         pMFAccount->validateAMSRBForSWP (idDataGroup);
         pMFAccount->validateAMSRBForEscrow (idDataGroup);
      }
   }
   return( GETCURRENTHIGHESTSEVERITY() );
}


//************************************************************************************
SEVERITY AMSAcctLvl::validateThresholdPrcnt(const DString& strValue, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("validateThresholdPrcnt") );

   DString strThresholdPrcnt( strValue );
   strThresholdPrcnt.strip();
   double dThres = DSTCommonFunctions::convertToDouble(strThresholdPrcnt);

//   if (dThres == 0)
//   {
//      ADDCONDITIONFROMFILE (CND::ERR_VALUE_CANNOT_BE_ZERO);
//   }
//   else
   if( dThres < 0-dSmallValue || dThres > 100+dSmallValue )
   {
      ADDCONDITIONFROMFILE( CND::ERR_VALUE_BETWEEN_0_AND_100 );
   }


   return GETCURRENTHIGHESTSEVERITY();
}

//*******************************************************************************
//Modify the Effective date to earlier then the original effective date is not allowed (existing CIBC rule) for existing record
SEVERITY AMSAcctLvl::validateEffectiveDate(const DString& strValue, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateEffectiveDate" ) );

   //You can comment out the following validation. Thanks.Winnie Dec.31,2007
   //Comment removed as requested in incident 10044692
   DString dstrEffectiveDate(strValue);
   dstrEffectiveDate.strip();

   DString dstrCurrBusDate;
   getWorkSession().getOption (ifds::CurrBusDate, dstrCurrBusDate, idDataGroup, false);

   if (DSTCommonFunctions::CompareDates (dstrEffectiveDate, dstrCurrBusDate) == DSTCommonFunctions::FIRST_EARLIER)
    {
       getErrMsg (IFASTERR::ACCT_LVL_EFFECTIVE_DATE,
                  CND::ERR_EFFECTIVE_DATE_BEFORE_CURBUSDATE,
                  CND::WARN_EFFECTIVE_DATE_BEFORE_CURBUSDATE,
                  idDataGroup);
        //ADDCONDITIONFROMFILE(CND::ERR_EFFECTIVE_DATE_BEFORE_CURBUSDATE);
    }

   return GETCURRENTHIGHESTSEVERITY();

}

//*******************************************************************************
//Modify the Stop date to later than the current business date is not allowed
SEVERITY AMSAcctLvl::validateStopDate(const DString& strValue, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateEffectiveDate" ) );

   DString dstrStopDate(strValue);
   dstrStopDate.strip();

   DString dstrCurrBusDate;
   getWorkSession().getOption (ifds::CurrBusDate, dstrCurrBusDate, idDataGroup, false);
   dstrCurrBusDate.strip();

   if ( DSTCommonFunctions::CompareDates (dstrStopDate, dstrCurrBusDate) == DSTCommonFunctions::SECOND_EARLIER &&
        !DSTCommonFunctions::CompareDates (dstrStopDate, I_( "12319999" ) ) == DSTCommonFunctions::EQUAL )
   {
      getErrMsg (IFASTERR::FUTURE_DATED_STOPDATE,
                 CND::ERR_FUTURE_DATED_STOPDATE,
                 CND::WARN_FUTURE_DATED_STOPDATE,
                 idDataGroup);
   }

   validateAgainstStopStatus (idDataGroup);


 
   //IN2818924 - DSK_AMS Validation for CDIC
   //DString dstrFundCode, dstrClassCode;
   //if(isAmsFundAllocAppliedBankruptcy( dstrFundCode,dstrClassCode , idDataGroup) )
   //{  /*
   //   if( DSTCommonFunctions::CompareDates( dstrStopDate, dstrCurrBusDate ) 
   //   != DSTCommonFunctions::FIRST_EARLIER )*/
   //   if( DSTCommonFunctions::CompareDates( dstrStopDate, dstrCurrBusDate ) 
   //      == DSTCommonFunctions::SECOND_EARLIER ) 
   //   {      
   //      ADDCONDITIONFROMFILE( CND::ERR_FUTURE_DATED_STOPDATE );
   //      /*
   //      getErrMsg (IFASTERR::FUTURE_DATED_STOPDATE,
   //      CND::ERR_FUTURE_DATED_STOPDATE,
   //      CND::WARN_FUTURE_DATED_STOPDATE,
   //      idDataGroup);*/ //DYN: dont have err 977 
   //   }
   //}


   return GETCURRENTHIGHESTSEVERITY();
}


//************************************************************************************
SEVERITY AMSAcctLvl::validateSchedSetupFreqID(const DString& strValue, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("validatevalidateSchedSetupFreqID") );

   DString dstrFreqOverride;
   DString dstrAmsType;

   getField (ifds::AMSType, dstrAmsType, idDataGroup, false);
   if (dstrAmsType != I_("RB"))
      return GETCURRENTHIGHESTSEVERITY();

   getField (ifds::FreqOverride, dstrFreqOverride, idDataGroup, false );
   if ( dstrFreqOverride == I_("1") ) {
      DString strSchedSetupFreqID( strValue );
      strSchedSetupFreqID.strip();
      if( strSchedSetupFreqID.empty() )
      {
         ADDCONDITIONFROMFILE( CND::ERR_BLANK_FREQENCY );
      }
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//***************************************************************************************
SEVERITY AMSAcctLvl::doApplyRelatedChanges( const BFFieldId& idField, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("doApplyRelatedChanges") );

   if( idField == ifds::AMSCode )
   {
      // If AMS Code changed, then the Effective Date needs to be updated.
      // Stop Date of the previous AMS will be updated behind the scenes (view)
      // with the current Effective Date
      setFieldReadOnly ( ifds::Deff, idDataGroup, false );
      setFieldRequired( ifds::Deff, idDataGroup, true );
      DString amsCode;

      getField (ifds::AMSCode, amsCode, idDataGroup, false);
      //the following only applies for AMSType = RB
      DString dstrAMSType;
      getField( ifds::AMSType, dstrAMSType, idDataGroup ,false );
      if( dstrAMSType.strip() == REBALANCE )
      {
         //Global AMS should always display the threshold % in the AMS Master.(Winnie, Feb 07, 2008)
         if( isAmsCodeGlobal( amsCode.strip(), idDataGroup ) )
         {
            //and it should be read only (Winnie, Feb 8, 2008)
            setFieldReadOnly ( ifds::ThresholdPrcnt, idDataGroup, true );

			//TargetMixOption will be grey out if AMS Code is not "0001"
			setFieldReadOnly ( ifds::TargetMixOption, idDataGroup, true );

            DString dstrAccountNum, dstrEffectiveDate;
            getParent()->getField(ifds::AccountNum, dstrAccountNum, idDataGroup);
            MFAccount* pMFAccount = NULL;
            if( getWorkSession().getMFAccount( idDataGroup, dstrAccountNum, pMFAccount) <= WARNING  && pMFAccount  )
            {
               getField(ifds::Deff, dstrEffectiveDate, idDataGroup);
               AMSMstrList *pAMSMstrList = NULL;
               pMFAccount->getAMSMstrList( pAMSMstrList, idDataGroup, dstrEffectiveDate );

               AmsMstrInfo* pAmsMstrInfo = NULL;
               pAMSMstrList->getAMSMstrInfo (dstrAMSType, amsCode, dstrEffectiveDate, pAmsMstrInfo, idDataGroup );
               if( pAmsMstrInfo ) 
               {
                  DString dstrTresholdPrct, dstrSchedSetupFreqID, dstrTargetMixOption;
                  pAmsMstrInfo->getField(ifds::Percentage, dstrTresholdPrct, idDataGroup, false );
                  pAmsMstrInfo->getField(ifds::SchedSetupFreqID, dstrSchedSetupFreqID, idDataGroup, false );
				  pAmsMstrInfo->getField(ifds::TargetMixOption, dstrTargetMixOption, idDataGroup, false );

                  setFieldNoValidate( ifds::ThresholdPrcnt, dstrTresholdPrct, idDataGroup, false, true, true );
				  setFieldNoValidate( ifds::TargetMixOption, dstrTargetMixOption, idDataGroup, false, true, true);

                  dstrSchedSetupFreqID.strip().upperCase();

                  if (getWorkSession().isMasterActWithOneChild(idDataGroup))
                  {
                     setFieldNoValidate( ifds::SchedSetupFreqID, dstrSchedSetupFreqID, idDataGroup, false, true, true );
                  }
               }
            }
			
         }
         else
         {
            //AMS code has changed; it is not a global code, so reset the treshold percent to zero
            if( bRecalcRebDate )
            {
               setFieldNoValidate( ifds::ThresholdPrcnt, I_("0.00"), idDataGroup, false, true, true );
            }

            DString dstrOvrdRBLThrshld;
            getWorkSession().getOption( ifds::OvrdRBLThrshld, dstrOvrdRBLThrshld, BF::HOST, false );
            if( dstrOvrdRBLThrshld.strip().upperCase() == I_( "Y" ) )
            {
               setFieldReadOnly ( ifds::ThresholdPrcnt, idDataGroup, false );
            }
            else
            {
               setFieldReadOnly ( ifds::ThresholdPrcnt, idDataGroup, true );
            }

			//TargetMixOption is able to edit if AMS Code is "0001"
			setFieldReadOnly ( ifds::TargetMixOption, idDataGroup, false );
         }

         if( bRecalcRebDate )
         {
            CalculateNextRebDate(idDataGroup);
         }
      }
//      applyDefaultRBChanges(idDataGroup);
//to catch validation of the AmsType when user hits okay...
      setFieldValid (ifds::AMSType, idDataGroup, false);
   }
   else if ( idField == ifds::AMSCodeBuffer )
   {
      DString strAMSCodeBuffer;
      getField( idField, strAMSCodeBuffer, idDataGroup, false);
      strAMSCodeBuffer.strip().upperCase();
      bRecalcRebDate = false;
      setFieldNoValidate( ifds::AMSCode, strAMSCodeBuffer, idDataGroup, false, false, true, true );
      setFieldValid (ifds::AMSCode, idDataGroup, false);
      bRecalcRebDate = true;
   }
   if( idField == ifds::FreqOverride )
   {
      DString dstrFreqOverride;
        getField (ifds::FreqOverride, dstrFreqOverride, idDataGroup, false );

      if ( dstrFreqOverride == I_("1") ) {
         setFieldReadOnly ( ifds::SchedSetupFreqID, idDataGroup, false );
//         setAMSFrequencySubstSet( idDataGroup );

         DString dstrFreq;
         getWorkSession().getMgmtCoOptions()->getField( ifds::DefaultRebFreq, dstrFreq, idDataGroup ,false );
         if ( dstrFreq == NULL_STRING ) {
            FrequencyList *pFrequencyList = NULL;
            if ( getMgmtCo().getFrequencyList( pFrequencyList ) <= WARNING && NULL != pFrequencyList )
            {
               BFObjIter FrequencyListIter( *pFrequencyList, idDataGroup, true, BFObjIter::ITERTYPE::NON_DELETED );

               FrequencyListIter.begin();
               if( !FrequencyListIter.end() )
                {
                   FrequencyListIter.getObject()->getField( ifds::SchedSetupFreqID, dstrFreq,     idDataGroup );
                }
            }
         }
         DString dstrAMSFreqOvrd;

         getWorkSession().getOption( ifds::AMSFreqOvrd, dstrAMSFreqOvrd, idDataGroup, false );

         if (dstrAMSFreqOvrd != YES)
            setFieldNoValidate(ifds::SchedSetupFreqID, dstrFreq, idDataGroup, false, false);

         //setFieldRequired( ifds::SchedSetupFreqID, idDataGroup, true );

      } else {
//         setFieldAllSubstituteValues( ifds::SchedSetupFreqID, idDataGroup, NULL_STRING );
           setFieldNoValidate( ifds::SchedSetupFreqID, NULL_STRING, idDataGroup, false );
//         setFieldReadOnly ( ifds::SchedSetupFreqID, idDataGroup, true );
      }

   }
   if( idField == ifds::Deff )
   {
      CalculateNextRebDate(idDataGroup);
   }
   if( idField == ifds::SchedSetupFreqID )
   {
      CalculateNextRebDate(idDataGroup);
   }
   if( idField == ifds::Currency )
   {
      AbstractAlloc *pAcctAlloc (NULL);

      if (getAcctAlloc (pAcctAlloc, idDataGroup) <= WARNING &&
          pAcctAlloc)
      {
         DString dstrCurrency;
           getField (ifds::Currency, dstrCurrency, idDataGroup, false );
         pAcctAlloc->setField(ifds::AMSCurrency, dstrCurrency, idDataGroup, false);
      }
   }
   if( idField == ifds::ThresholdPrcnt )
   {
      AbstractAlloc *pAcctAlloc (NULL);
      if (getAcctAlloc (pAcctAlloc, idDataGroup) <= WARNING &&
          pAcctAlloc)
      {
         DString dstrThresholdPrcnt;
           getField (ifds::ThresholdPrcnt, dstrThresholdPrcnt, idDataGroup, false );
         pAcctAlloc->setField (ifds::RebalPrcnt, dstrThresholdPrcnt, idDataGroup, false);
      }
   }
   if (idField == ifds::AMSType)
   {
      setFieldValid (ifds::EffectiveStopDate, idDataGroup, false);
   }
   if (idField == ifds::UpdatePACSWP)
   {
      DString strKey = I_("AllocationList");
      ShrAllocTypeList* pAllocationList =   dynamic_cast <ShrAllocTypeList*> (getObject (strKey, idDataGroup));
      if( pAllocationList )
      {
         DString value;
         getField(ifds::UpdatePACSWP, value, idDataGroup, false);
         pAllocationList->setField( ifds::UpdatePACSWP, value, idDataGroup, false);
      }
   }
   //if (idField == ifds::Rebalance)
   //{
   //   setFieldNoValidate( ifds::AMSRebReqMode, I_("ReqRebalance"), idDataGroup, false );
   //}
   if (idField == ifds::ActualRebalanceDate)
   {
      DString dstrApplicable, dstrRebalDateFormat, dstrActualRebalanceDate;
      getWorkSession().getOption (ifds::NextRebDateApplicable, dstrApplicable, BF::HOST ,false);
      getWorkSession().getOption( ifds::RebalDateFormat, dstrRebalDateFormat, BF::HOST, false );
      getField( ifds::ActualRebalanceDate, dstrActualRebalanceDate, idDataGroup, false);
      dstrRebalDateFormat.strip().upperCase();
      dstrApplicable.strip().upperCase();

      // only environment where 'update next rebalance date' is applicable while it 
      // also supports display rebalance date, if there is any change on next rebalance date
      // by user, it would be synced to 'next processing date' as well
      bool bPermission = getWorkSession().hasUpdatePermission(UAF::UPD_NEXT_REB_DATE );
      if (bPermission && dstrApplicable == YES && dstrRebalDateFormat == I_("1")){
         setFieldNoValidate( ifds::NextProcessDate, dstrActualRebalanceDate, idDataGroup, false, false, true );
      }
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//*****************************************************************************
//DS Not used need clarification.
void AMSAcctLvl::applyDefaultRBChanges(const BFDataGroupId& idDataGroup) {
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "ApplyDefaultRBChanges" ) );

   if ( isNew() ) {
      DString dstrAMSType;
      getField( ifds::AMSType, dstrAMSType, idDataGroup ,false );

      if ( dstrAMSType == REBALANCE ) {
         DString dstrEffectiveDate;
         getField(ifds::Deff, dstrEffectiveDate, idDataGroup);

         DString dstrAccountNum;
         getParent()->getField(ifds::AccountNum, dstrAccountNum, idDataGroup);
         MFAccount* pMFAccount = NULL;
         if( getWorkSession().getMFAccount( idDataGroup, dstrAccountNum, pMFAccount) <= WARNING  && pMFAccount  )
         {
            AMSMstrList *pAMSMstrList = NULL;
             pMFAccount->getAMSMstrList( pAMSMstrList, idDataGroup, dstrEffectiveDate );

            DString dstrAMSCode;
            getField( ifds::AMSCode, dstrAMSCode, idDataGroup ,false );
            AmsMstrInfo* pAmsMstrInfo = NULL;
            pAMSMstrList->getAMSMstrInfo (dstrAMSType, dstrAMSCode, dstrEffectiveDate, pAmsMstrInfo, idDataGroup );
             if( pAmsMstrInfo ) {
               DString dstrFundAlloc;
               pAmsMstrInfo->getField(ifds::FundAlloc, dstrFundAlloc, idDataGroup, false );

               if (dstrFundAlloc == YES) {

               } else {
               }
            }
         }
      }
   }

}

//*****************************************************************************
void AMSAcctLvl::CalculateNextRebDate(const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "CalculateNextRebDate" ) );

    DString dstrAMSCode, dstrEffectiveDate, dstrFreq, dstrTargetMixOption;

    getField(ifds::LastProcessDate,dstrEffectiveDate,idDataGroup,false);
    if( dstrEffectiveDate.strip() == NULL_STRING ||
        DSTCommonFunctions::CompareDates (dstrEffectiveDate, I_( "12319999" ) ) == DSTCommonFunctions::EQUAL )
    {
        getField(ifds::Deff,dstrEffectiveDate,idDataGroup,false);
    }

    getField(ifds::SchedSetupFreqID, dstrFreq, idDataGroup, false);
    dstrFreq.strip();
    dstrEffectiveDate.strip();

   getField(ifds::TargetMixOption, dstrTargetMixOption, idDataGroup, false);
   dstrTargetMixOption.strip();

   if ( (!dstrFreq.empty() && dstrFreq!=I_("0")) || (dstrTargetMixOption == I_("M") && (dstrFreq ==I_("0") || dstrFreq.empty()))) {
	   // added a further condition for “Market weighted” Target Mix Option and N/A or Frequency unchecked

       AMSRebDateCalc *pAMSRebDateCalc = new AMSRebDateCalc(*this);
       if( pAMSRebDateCalc->init( dstrEffectiveDate ,dstrFreq) <= WARNING ) {
           DString dstrNextRebDate, dstrActualRebalanceDate;
           pAMSRebDateCalc->getField(ifds::NextProcessDate,dstrNextRebDate,idDataGroup,false);
           setFieldNoValidate(ifds::NextProcessDate, dstrNextRebDate, idDataGroup, false, true, true);
           pAMSRebDateCalc->getField(ifds::ActualRebalanceDate,dstrActualRebalanceDate,idDataGroup,false);
           setFieldNoValidate(ifds::ActualRebalanceDate, dstrActualRebalanceDate, idDataGroup, false, true, true);
           setFieldUpdated(ifds::ActualRebalanceDate, idDataGroup, false);
       } else {
           CLEARCONDITIONS();
       }

      if (pAMSRebDateCalc)  {
           delete pAMSRebDateCalc;
           pAMSRebDateCalc =NULL;
       }
   }
   else
   {
      DString dstrAccountNum, dstrEffectiveDate, dstrAMSType,amsCode;
      getField (ifds::AMSCode, amsCode, idDataGroup, false);
      getField( ifds::AMSType, dstrAMSType, idDataGroup ,false );
      getParent()->getField(ifds::AccountNum, dstrAccountNum, idDataGroup);
      MFAccount* pMFAccount = NULL;
      if( getWorkSession().getMFAccount( idDataGroup, dstrAccountNum, pMFAccount) <= WARNING  && pMFAccount  )
      {
         getField(ifds::Deff, dstrEffectiveDate, idDataGroup);
         AMSMstrList *pAMSMstrList = NULL;
         pMFAccount->getAMSMstrList( pAMSMstrList, idDataGroup, dstrEffectiveDate );
         AmsMstrInfo* pAmsMstrInfo = NULL;
         pAMSMstrList->getAMSMstrInfo (dstrAMSType, amsCode, dstrEffectiveDate, pAmsMstrInfo, idDataGroup );
         if( pAmsMstrInfo ) 
         {
            pAmsMstrInfo->getField(ifds::SchedSetupFreqID, dstrFreq, idDataGroup, false);
            dstrFreq.strip();
            AMSRebDateCalc *pAMSRebDateCalc = new AMSRebDateCalc(*this);
            if( pAMSRebDateCalc->init( dstrEffectiveDate ,dstrFreq) <= WARNING ) {
               DString dstrNextRebDate, dstrActualRebalanceDate;
               pAMSRebDateCalc->getField(ifds::NextProcessDate,dstrNextRebDate,idDataGroup,false);
               setFieldNoValidate(ifds::NextProcessDate, dstrNextRebDate, idDataGroup, false, true, true);
               pAMSRebDateCalc->getField(ifds::ActualRebalanceDate,dstrActualRebalanceDate,idDataGroup,false);
               setFieldNoValidate(ifds::ActualRebalanceDate, dstrActualRebalanceDate, idDataGroup, false, true, true);
               setFieldUpdated(ifds::NextProcessDate, idDataGroup, false);
               setFieldUpdated(ifds::ActualRebalanceDate, idDataGroup, false);
            } else {
               CLEARCONDITIONS();
            }

            if (pAMSRebDateCalc)  {
               delete pAMSRebDateCalc;
               pAMSRebDateCalc =NULL;
            }
         }
      }
   }
}

//******************************************************************************
// as copied from MFAccount
SEVERITY AMSAcctLvl::setAMSTypeSubstitutionList(const BFDataGroupId& idDataGroup, DString& firstCode)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("setAMSTypeSubstitutionList" ));

   DString  dstrClientAMSType, dstrSubstitution, dstrList;
   DString  dstrCode, dstrAMSType( NULL_STRING ), dstrAMSTypeDesc;

   firstCode = NULL_STRING;

   getWorkSession().getOption( ifds::ClientAMSType, dstrClientAMSType, idDataGroup, false );    // RO,RB
   dstrClientAMSType.stripAll().upperCase();

   // The goal is to take DString( I_("RO,RB")) to
   // "RO=Target Asset Mix;RB=Rebalancing Asset Mix;"

   // Parse dstrAMSTypeList (Comma-delimited).
   BFProperties * pBFProperties = getFieldProperties(ifds::AMSType, idDataGroup);

   dstrList = dstrClientAMSType;
   int pos = 0;

   do
   {
      pos = dstrList.find(  I_CHAR(',') );  // index into string
      if (pos != -1)
      {
         dstrCode = dstrList.substr(0, pos);  // get code
         dstrList = dstrList.substr(pos+1);   // advance list
      }
      else
      {
         dstrCode = dstrList;
         dstrList = NULL_STRING;
      }

      if ( I_( "FOF" ) == dstrCode )
         continue;

/*      if ( REBALANCE == dstrCode ) {
         DString dstrAccountNum;
         getParent()->getField(ifds::AccountNum, dstrAccountNum, idDataGroup);
         MFAccount* pMFAccount = NULL;
         if( getWorkSession().getMFAccount( idDataGroup, dstrAccountNum, pMFAccount) > WARNING
                  || !pMFAccount
                  || !pMFAccount->isAMSRBAllowed(idDataGroup) ){
            continue;
         }
      }
*/

      if (firstCode == NULL_STRING) {
         firstCode = dstrCode;
      }

      dstrAMSTypeDesc = dstrCode;
      pBFProperties->formatValue(ifds::AMSType, dstrAMSTypeDesc, true );   // -> should return description "Target Asset Mix"
      dstrSubstitution += dstrCode + I_("=") + dstrAMSTypeDesc + I_(";");  // RO=Target Asset Mix;
      if( dstrAMSType.empty() )
      {
         dstrAMSType = dstrCode;
      }
   } while(dstrList.length());

   setFieldAllSubstituteValues(ifds::AMSType, idDataGroup, dstrSubstitution);

   return GETCURRENTHIGHESTSEVERITY();
}

//***********************************************************************************************
bool AMSAcctLvl::isBusinessDate( const DString& strValue, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("isBusinessDate" ));

   DateValidation* _dateValidation = new DateValidation ( *this );

   DString fundCode = NULL_STRING,classCode = NULL_STRING;
   DString effectiveDate(strValue);
   effectiveDate.stripAll();
   DString validationType(BUSINESS_DATE);

    SEVERITY sevRtn = _dateValidation->init( validationType,  //validationType
                                             NULL_STRING,     //tradeDate
                                             NULL_STRING,     //settleDate
                                             effectiveDate,   //depositDate
                                             NULL_STRING,     //valueDate
                                             NULL_STRING,     //transType
                                             NULL_STRING,     //payType
                                             NULL_STRING,     //broker
                                             fundCode,        //fundCode
                                             classCode,       //classCode
                                             NULL_STRING,     //toFund
                                             NULL_STRING,     //toClass
                                             NO,              //orderType
                                             NULL_STRING,     //dealDate
                                             NULL_STRING,     //dealTime
                                             NULL_STRING,     //settleCurrency
                                             NULL_STRING,     //amount
                                             NULL_STRING,     //amountType
                                             NULL_STRING,     //settleInDate
                                             NULL_STRING,     //brokerTo
                                             NULL_STRING,     //accountNum,
                                             NULL_STRING,     //accountNumTo,
                                             NULL_STRING,     //fromCurrency,
                                             NULL_STRING,     //toCurrency,
                                             I_("N"),         //Track,
                                             NULL_STRING);    //PageName

   if (sevRtn > WARNING)
   {

      delete _dateValidation;
      return false;
   }

   DString dstrBusDate;

   _dateValidation->getField (ifds::EffectiveDate, dstrBusDate, idDataGroup, false);
   dstrBusDate.stripAll();
   delete _dateValidation;
   return dstrBusDate.empty();
}


//*******************************************************************************
bool AMSAcctLvl::isLastBusDayOfWeek ( const DString& strValue, const BFDataGroupId& idDataGroup )
{
   DString dstrDateIn(strValue);
   BFDate::DATE_FORMAT fmt = BFDate::inferFormat( dstrDateIn.c_str() );
   assert( fmt != BFDate::DF_NULL );
   BFDate dateIn( dstrDateIn.c_str(), fmt );
   int iwd = dateIn.getWeekDay();
   if (iwd == 5)
       return true;
   else if ( iwd == 4 )
   {
        dateIn.addDays( 1 );
        return (!isBusinessDate(dateIn.get (fmt), idDataGroup));
   }
   else
       return false;

}

//*************************************************************************************
SEVERITY AMSAcctLvl::setAMSFrequencySubstSet( const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("setAMSFrequencySubstSet" ));

   DString dstrAMSFreqOvrd;
   getWorkSession().getOption( ifds::AMSFreqOvrd, dstrAMSFreqOvrd, idDataGroup, false );
   if ( YES == dstrAMSFreqOvrd )
   {
      DString dstrFrequencySubstSet;
      FrequencyList *pFrequencyList = NULL;
      if ( getMgmtCo().getFrequencyList( pFrequencyList ) <= WARNING && NULL != pFrequencyList )
      {
         pFrequencyList->getFrequencySubstitutionSet( dstrFrequencySubstSet, idDataGroup);
      }

      setFieldAllSubstituteValues( ifds::SchedSetupFreqID, idDataGroup, dstrFrequencySubstSet );
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//********************************************************************************************
SEVERITY AMSAcctLvl::getAcctAlloc ( AbstractAlloc *&pAcctAlloc,
                                    const BFDataGroupId& idDataGroup)
{
    MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("getAMSAcctAllocList") );

   pAcctAlloc = NULL;
   DString strKey = I_("AllocationList");

   ShrAllocTypeList* pAllocationList =
         dynamic_cast <ShrAllocTypeList*> (getObject (strKey, idDataGroup));

   if (pAllocationList)
   {
      DString amsType,
         effectiveDate,
         accountNum;

      getParent()->getField(ifds::AccountNum, accountNum, idDataGroup);
      getField (ifds::Deff, effectiveDate, idDataGroup, false);
      getField (ifds::AMSType, amsType, idDataGroup ,false);

      DefAcctAllocList *pAcctAllocList = NULL;

      if (pAllocationList->getDefaultAcctAllocList (amsType, pAcctAllocList, idDataGroup, accountNum, effectiveDate) <= WARNING &&
          pAcctAllocList)
      {
         pAcctAllocList->getAllocation (NULL_STRING, pAcctAlloc, idDataGroup);
      }
   }
    return(GETCURRENTHIGHESTSEVERITY());
}

//*****************************************************************************
SEVERITY AMSAcctLvl::getAMSAcctLvlAllocation ( DefFundAllocList *&pFundAllocList,
                                               const BFDataGroupId& idDataGroup,
                                               bool bCreate /*= true*/)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("getAMSAcctAllocList") );

   pFundAllocList = NULL;
   DString strKey = I_("AllocationList");
   
   ShrAllocTypeList* pAllocationList =
         dynamic_cast <ShrAllocTypeList*> (getObject (strKey, idDataGroup));

   bool bNeedSetObject = false;

   if (!pAllocationList && bCreate)
   {
      if (isNew ()) //check if the amsacctlvl is new
      {
         pAllocationList = new ShrAllocTypeList (*this);
         pAllocationList->initNew (idDataGroup);
         bNeedSetObject = true;
      }
      else
      {
         pAllocationList = new ShrAllocTypeList (*this);
         pAllocationList->initExisting ();
         bNeedSetObject = true;
      }
   }

   if (bNeedSetObject && pAllocationList)
   {
      if (GETCURRENTHIGHESTSEVERITY () <= WARNING)
      {
         setObject (pAllocationList, strKey, OBJ_ACTIVITY_NONE, idDataGroup);
      }
      else
      {
         delete pAllocationList;
         pAllocationList = NULL;
      }
   }
//we've created the ShrAllocList - now we need to get a hold of the fund alloc
   if (pAllocationList)
   {
      DString amsType,
         accountNumber,
         effectiveDate;

      getField (ifds::AMSType, amsType, idDataGroup, false);
      getField (ifds::Deff, effectiveDate, idDataGroup, false);
      getParent()->getField(ifds::AccountNum, accountNumber, idDataGroup);
      pAllocationList->getDefaultFundAllocList ( amsType,
                                                 accountNumber,
                                                 pFundAllocList,
                                                 idDataGroup,
                                                 effectiveDate);
      if (!pFundAllocList) //still not finding the list...
      {
//first remove any latest allocation         
         pAllocationList->removeShrAllocType ( accountNumber, 
                                               amsType,
                                               NULL_STRING,
                                               idDataGroup);
         pAllocationList->addNewShrAllocType (amsType, accountNumber, idDataGroup, effectiveDate);
         pAllocationList->getDefaultFundAllocList ( amsType,
                                                    accountNumber,
                                                    pFundAllocList,
                                                    idDataGroup,
                                                    effectiveDate);
      }
   }
    return GETCURRENTHIGHESTSEVERITY();
}

//*****************************************************************************
SEVERITY AMSAcctLvl::getAMSMasterInfo (AmsMstrInfo *&pAmsMstrInfo, const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("getAMSMasterInfo"));
   pAmsMstrInfo = NULL;
   MFAccount* pMFAccount = NULL;

   DString accountNum;
   getParent()->getField (ifds::AccountNum, accountNum, idDataGroup);

   if( getWorkSession().getMFAccount (idDataGroup, accountNum, pMFAccount) <= WARNING  &&
       pMFAccount)
   {
      DString effectiveDate (NULL_STRING);
      AMSMstrList *pAMSMstrList (NULL);

      getField (ifds::Deff, effectiveDate, idDataGroup, false);
      if ( pMFAccount->getAMSMstrList (pAMSMstrList, idDataGroup, effectiveDate) &&
           pAMSMstrList)
      {
         DString amsCode,
            amsType;

         getField (ifds::AMSCode, amsCode, idDataGroup, false);
         getField (ifds::AMSType, amsType, idDataGroup, false);
         pAMSMstrList->getAMSMstrInfo (amsType, amsCode, effectiveDate, pAmsMstrInfo, idDataGroup);
      }
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//*****************************************************************************
bool AMSAcctLvl::isAmsCodeGlobal( const DString &dstrAMSCode, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("isAmsCodeGlobal"));
   bool bGlobalCode = false;

   //an AMS code is 'global' if a fund allocation has been setup for it, in ams master info (Winnie, Feb 8, 2008)

   DString strAMSCode( dstrAMSCode );

   if( strAMSCode.strip() == NULL_STRING )
   {
      return bGlobalCode;
   }

   DString dstrAccountNum, dstrEffectiveDate,dstrAMSType;
   getParent()->getField(ifds::AccountNum, dstrAccountNum, idDataGroup);
   MFAccount* pMFAccount = NULL;
   if( dstrAccountNum.strip() != NULL_STRING &&
      getWorkSession().getMFAccount( idDataGroup, dstrAccountNum, pMFAccount) <= WARNING  && pMFAccount  )
   {
      getField(ifds::Deff, dstrEffectiveDate, idDataGroup);
      getField(ifds::AMSType, dstrAMSType, idDataGroup);
      AMSMstrList *pAMSMstrList = NULL;
      pMFAccount->getAMSMstrList( pAMSMstrList, idDataGroup, dstrEffectiveDate );
      AmsMstrInfo* pAmsMstrInfo = NULL;
      if( dstrAMSType.strip() != NULL_STRING && dstrEffectiveDate.strip() != NULL_STRING )
      {
         pAMSMstrList->getAMSMstrInfo (dstrAMSType, dstrAMSCode, dstrEffectiveDate, pAmsMstrInfo, idDataGroup );
         if( pAmsMstrInfo )
         {
            AmsFundAllocList *pAmsFundAllocList = NULL;
            pAmsMstrInfo->getAMSFundAllocList( pAmsFundAllocList, idDataGroup );
            if( pAmsFundAllocList )
            {
               BFObjIter iter( *pAmsFundAllocList, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED);
               bGlobalCode = iter.getNumberOfItemsInList() != 0;
            }
         }
      }
   }

   return bGlobalCode;
}

//***********************************************************************************
SEVERITY AMSAcctLvl::validateAccountClosedCountry (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, CLASSNAME, I_("validateAccountClosedCountry"));
   
   DString dstrAccountNum;
   getParent()->getField(ifds::AccountNum, dstrAccountNum, idDataGroup);      
   
   MFAccount *pMFAccount = NULL;
   // get MFAccount
   if ( getWorkSession().getMFAccount ( idDataGroup, 
                                        dstrAccountNum, 
                                        pMFAccount ) <= WARNING && pMFAccount )
   {
      DString dstrIsClosedCountryResident;
      pMFAccount->getField( ifds::IsClosedCountryResident, dstrIsClosedCountryResident, idDataGroup, false );  
      
      if ( dstrIsClosedCountryResident.strip().upperCase() == YES )
      {
         // Raise error message, No AMS allowed for closed country resident.
         DString idiStr;
         addIDITagValue (idiStr, I_("TRADETYPE"), I_("AMS"));    
         ADDCONDITIONFROMFILEIDI (CND::ERR_CLOSED_COUNTRY_RESIDENT_FOR_MONEY_IN , idiStr);
      }      
    
   }
   
   return GETCURRENTHIGHESTSEVERITY ();
}

//*****************************************************************************
//IN2818924 - DSK_AMS Validation for CDIC
bool AMSAcctLvl::isAmsFundAllocAppliedBankruptcy( DString& fundCode,
                                                  DString& classCode,
                                                  const BFDataGroupId& idDataGroup )
{
   DString dstrAMSCode;
   bool ret(false);

   getField( ifds::AMSCode, dstrAMSCode, idDataGroup ,false );

   if( dstrAMSCode.strip() == NULL_STRING )
   {
      return ret;
   }

   MFAccount* pMFAccount = NULL;

   DString dstrAccountNum;
   getParent()->getField(ifds::AccountNum, dstrAccountNum, idDataGroup);

   if( dstrAccountNum.strip() != NULL_STRING &&
      getWorkSession().getMFAccount( idDataGroup, dstrAccountNum, pMFAccount) <= WARNING  && pMFAccount  )
   {
      DString dstrEffectiveDate,dstrAMSType;
      getField(ifds::Deff, dstrEffectiveDate, idDataGroup);
      getField(ifds::AMSType, dstrAMSType, idDataGroup);
      AMSMstrList *pAMSMstrList = NULL;
      pMFAccount->getAMSMstrList( pAMSMstrList, idDataGroup, dstrEffectiveDate );
      AmsMstrInfo* pAmsMstrInfo = NULL;
      if( dstrAMSType.strip() != NULL_STRING && dstrEffectiveDate.strip() != NULL_STRING )
      {
         pAMSMstrList->getAMSMstrInfo (dstrAMSType, dstrAMSCode, dstrEffectiveDate, pAmsMstrInfo, idDataGroup );
         if( pAmsMstrInfo )
         {
            DString dstrDefaultAlloc, dstrFundAlloc;

            pAmsMstrInfo->getField(ifds::DefaultAlloc, dstrDefaultAlloc, idDataGroup, false);
            pAmsMstrInfo->getField(ifds::FundAlloc, dstrFundAlloc, idDataGroup, false);

            if(dstrFundAlloc == I_("Y"))
            {
               AmsFundAllocList *pAmsFundAllocList = NULL;
               pAmsMstrInfo->getAMSFundAllocList( pAmsFundAllocList, idDataGroup );
               if( pAmsFundAllocList )
               {
                  ret = pAmsFundAllocList->isBankruptcyApplied(fundCode, classCode,idDataGroup);
               }
            }
            else if(dstrDefaultAlloc == I_("Y"))//0001
            {
               DefFundAllocList *pFundAllocList = NULL;

               if ( getAMSAcctLvlAllocation (pFundAllocList, idDataGroup, false) <= WARNING &&
                  pFundAllocList)
               {

                  ret = pFundAllocList->isBankruptcyApplied( idDataGroup ) ;
               }
            }
         }

      }

   }

   return ret;
}

//*****************************************************************************
SEVERITY AMSAcctLvl::validateAMSCodeWithUnderSameShr(const DString& strValue,
                                                     MFAccount* pMFAccount,
                                                     const BFDataGroupId&  idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, CLASSNAME, I_("validateAMSCodeWithUnderSameShr"));

   DString dstrShrNum;
   pMFAccount->getField (ifds::ShrNum, dstrShrNum, idDataGroup, false);
   dstrShrNum.strip();
   Shareholder* pShareholder (NULL);
   getWorkSession().getShareholder (idDataGroup, dstrShrNum, pShareholder);

   DString dstrAMSCode(strValue);
   dstrAMSCode.strip().upperCase();
   bool bFoundUsedAMSCode = false;
   if (pShareholder)
   {
      MFAccountList* pMFAccountList = NULL;
      if( pShareholder->getMFAccountList (pMFAccountList, idDataGroup, true ) <= WARNING &&
         pMFAccountList )
      {
         BFObjIter iter( *pMFAccountList, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED);

         while (!iter.end())
         {
            DString dstrAcctAMSCode, dstrAcctStatus;
            MFAccount* pAccount = dynamic_cast<MFAccount*>(iter.getObject());
            MFAccount* pParentAccount = dynamic_cast<MFAccount*>(getParent()->getParent());

            // make sure that owner of account level AMS is not the same with
            // iterating account
            if(pAccount && pParentAccount && (pParentAccount != pAccount))
            {
               pAccount->getField (ifds::AcctStatus, dstrAcctStatus, idDataGroup, false);
               pAccount->getField( ifds::AMSCode, dstrAcctAMSCode,idDataGroup, false );
               dstrAcctAMSCode.strip().upperCase();
               dstrAcctStatus.strip().upperCase();

               if((dstrAcctAMSCode == dstrAMSCode) && (dstrAcctStatus != I_("30")))
               {
                  bFoundUsedAMSCode = true;
                  break;
               }
            }
            ++iter;
         }
      }
   }

   if(bFoundUsedAMSCode)
   {
      // if AMS code is using by other account under same shareholder then raise error
      getErrMsg (IFASTERR::THE_AMS_MODEL_ASSOCIATED_WITH_ANOTHER_ACCT_SAME_SHRHLDR,
                 CND::ERR_THE_AMS_MODEL_ASSOCIATED_WITH_ANOTHER_ACCT_SAME_SHRHLDR,
                 CND::WARN_THE_AMS_MODEL_ASSOCIATED_WITH_ANOTHER_ACCT_SAME_SHRHLDR,
                 idDataGroup);
      //ADDCONDITIONFROMFILE( CND::ERR_THE_AMS_MODEL_ASSOCIATED_WITH_ANOTHER_ACCT_SAME_SHRHLDR );
   }

   return GETCURRENTHIGHESTSEVERITY ();
}

//*****************************************************************************
SEVERITY AMSAcctLvl::validateAgainstStopStatus ( const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("validateAgainstStopStatus"));

   DString strRestrictUpdateStat;
   getField(ifds::RestrictUpdateStat,strRestrictUpdateStat,idDataGroup,false);

   if(strRestrictUpdateStat.strip().upperCase() == YES)
   {
      CND::CIFast_IFast_ifastcbo_warn_stopping_ams_model_require_full_money_out_trade warnCond;
      CND::CIFast_IFast_ifastcbo_err_stopping_ams_model_require_full_money_out_trade errCond;

      MFCanBFCbo::getErrMsg (IFASTERR::STOPPING_AMS_MODEL_REQUIRE_FULL_MONEY_OUT_TRADE,
                              errCond,
                              warnCond,
                              idDataGroup);
   }

   return GETCURRENTHIGHESTSEVERITY ();
}

//*****************************************************************************
SEVERITY AMSAcctLvl::getAMSDeltaAllocList(AMSDeltaAllocList *&pAMSDeltaAllocList,const BFDataGroupId& idDataGroup,bool bCreate)
{
  MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, CLASSNAME, I_("getAMSDeltaAllocList"));
  AbstractAlloc *pAcctAlloc (NULL);
  DefFundAllocList* pAMSFundAllocList = NULL;
  getAMSAcctLvlAllocation(pAMSFundAllocList, idDataGroup, false);

  pAMSDeltaAllocList = dynamic_cast<AMSDeltaAllocList*>(getObject(AMSDELTAALLOCLIST, idDataGroup));

  if(pAMSDeltaAllocList)
    return GETCURRENTHIGHESTSEVERITY();

  DString strAMSCode, dstrEffectiveDate, dstrAMSDeltaReqUUID, strAccountNum; 
  bool bRemoveObj = true; /*In case AMSDeltaAlloc is not found */
  if(!pAMSDeltaAllocList && bCreate)
  {
    getField(ifds::AMSCode, strAMSCode, idDataGroup, false);
    getField(ifds::Deff, dstrEffectiveDate, idDataGroup, false);
    getParent()->getField(ifds::AccountNum, strAccountNum, idDataGroup);		
    getField(ifds::AMSDeltaRequestUUID, dstrAMSDeltaReqUUID, idDataGroup, false);
    pAMSDeltaAllocList = new AMSDeltaAllocList( * this );
    pAMSDeltaAllocList->init(strAMSCode,dstrEffectiveDate,strAccountNum,dstrAMSDeltaReqUUID);
		
    if(pAMSFundAllocList)
    {
      BFObjIter iter(*pAMSDeltaAllocList, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED );
      if(!iter.end())
      bRemoveObj = false;

      if(!bRemoveObj)			
      {
        BFObjIter fundAllocList(*pAMSFundAllocList,idDataGroup,false,BFObjIter::ITERTYPE::ALL);
        for(fundAllocList.begin();!fundAllocList.end();fundAllocList++)
        {
          DString fundCode, classCode, allocPrcnt, toFundNumber;
          FundAlloc* pAMSFundAlloc = dynamic_cast<FundAlloc*> (fundAllocList.getObject());
          pAMSFundAlloc->getField(ifds::FundCode, fundCode, idDataGroup);
          pAMSFundAlloc->getField(ifds::ClassCode, classCode, idDataGroup);
          pAMSFundAlloc->getField(ifds::ToFundNumber, toFundNumber, idDataGroup);
          pAMSFundAlloc->getField(ifds::AllocPercentage, allocPrcnt, idDataGroup);

          BFObjIter deltaAllocList(*pAMSDeltaAllocList, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED);
          for(deltaAllocList.begin();!deltaAllocList.end();!deltaAllocList++)
          {
            DString deltaFund,deltaClass;
            AMSDeltaAlloc* pAMSDeltaAlloc = dynamic_cast<AMSDeltaAlloc*> (deltaAllocList.getObject());
            pAMSDeltaAlloc->getField(ifds::FundCode, deltaFund, idDataGroup);
            pAMSDeltaAlloc->getField(ifds::ClassCode, deltaClass, idDataGroup);

            if(fundCode == deltaFund && classCode == deltaClass)
            {							
              pAMSDeltaAlloc->setField(ifds::ToFundNumber, toFundNumber, idDataGroup);
              pAMSDeltaAlloc->setField(ifds::AllocPercentage, allocPrcnt, idDataGroup);							
            }
          }
        }
        setObject(pAMSDeltaAllocList, AMSDELTAALLOCLIST, OBJ_ACTIVITY_NONE, idDataGroup);
      }
      else
      {
        pAMSDeltaAllocList = NULL;
        if(pAMSFundAllocList )
        initAMSDeltaAllocList(pAMSFundAllocList, pAMSDeltaAllocList, idDataGroup);
      }
    }      
  }

  return(GETCURRENTHIGHESTSEVERITY());
}

//*****************************************************************************
SEVERITY AMSAcctLvl::initAMSDeltaAllocList(DefFundAllocList *pAMSFundAllocList, AMSDeltaAllocList *&pAMSDeltaAllocList, const BFDataGroupId& idDataGroup)
{
  MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, CLASSNAME, I_("initAMSDeltaAllocList"));
  
  BFObjIter iter(*pAMSFundAllocList, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED);
  DString AMSCode, accountNum, effectiveDate, status, AMSDeltaRequestUUID;

  getField(ifds::AMSCode, AMSCode, idDataGroup, false);
  getParent()->getField(ifds::AccountNum, accountNum, idDataGroup, false);
   
  DString currBusDate;
  getWorkSession().getDateInHostFormat(currBusDate, DSTCWorkSession::CURRENT_BUSINESS_DAY, idDataGroup);

  pAMSDeltaAllocList = new AMSDeltaAllocList(*this);
  pAMSDeltaAllocList->setField(ifds::AMSCode,AMSCode,idDataGroup);
  pAMSDeltaAllocList->setField(ifds::AccountNum,accountNum,idDataGroup);
  pAMSDeltaAllocList->setField(ifds::EffectiveDate,currBusDate,idDataGroup);

  for(iter.begin();!iter.end();iter++)
  {
    DString dstrToFundNumber, dstrFundCode, dstrClassCode, dstrAllocPrcnt;
    FundAlloc* pFundAlloc = dynamic_cast<FundAlloc*> (iter.getObject());
    pFundAlloc->getField(ifds::FundCode, dstrFundCode, idDataGroup);
    pFundAlloc->getField(ifds::ClassCode, dstrClassCode, idDataGroup);
    pFundAlloc->getField(ifds::ToFundNumber, dstrToFundNumber, idDataGroup);
    pFundAlloc->getField(ifds::AllocPercentage, dstrAllocPrcnt, idDataGroup);
    pAMSDeltaAllocList->doCopyCurrAlloc(dstrToFundNumber, dstrFundCode, dstrClassCode, dstrAllocPrcnt, idDataGroup);
  }
  
  setObject(pAMSDeltaAllocList, AMSDELTAALLOCLIST, OBJ_ACTIVITY_NONE, idDataGroup);    
  return(GETCURRENTHIGHESTSEVERITY());
}
   
//*****************************************************************************
//              Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastcbo/AMSAcctLvl.cpp-arc  $
// 
//    Rev 1.53   Feb 24 2012 04:06:04   panatcha
// IN2844236 - Cannot put a stop date on PAC/SWP/Automatic Transfer
// 
//    Rev 1.52   Jan 31 2012 07:35:08   panatcha
// IN2818924 - DSK_AMS Validation for CDIC
// 
//    Rev 1.51   Jan 13 2010 14:49:36   jankovii
// IN 1973716 - Unable to set up Target Allocation
// 
//    Rev 1.50   Dec 17 2009 14:05:06   jankovii
// IN 1950595 - iFast Desktop error - X mark without error description on AMS screen
// 
//    Rev 1.49   Oct 26 2009 16:33:52   jankovii
// PET157825 FN08 FN11 FN14 AMS Gaps
// 
//    Rev 1.48   15 Jun 2009 15:26:54   popescu
// PET157837 FN02 - Country Schedule Daily Non Resident Schedule A
// 
//    Rev 1.47   15 Jun 2009 07:50:50   popescu
// PET157837 FN02 - Country Schedule Daily Non Resident Schedule A
// 
//    Rev 1.46   Jun 09 2009 05:35:58   kitticha
// PET157837 FN02 - Country Schedule Daily Non Resident Schedule A
// 
//    Rev 1.45   Mar 10 2009 10:52:50   jankovii
// IN 1619627 - Account Level AMS screen
// 
//    Rev 1.44   Jan 30 2009 11:45:12   jankovii
// IN 1522650 - repopulating allowable transfers table for merged funds
// 
//    Rev 1.43   Jan 30 2009 10:26:00   jankovii
// IN 1543838 - AMS Rebalancing - AMS Mstr Setup -R91 - QA Testing
// 
//    Rev 1.42   07 Oct 2008 14:10:48   popescu
// Incident  1154478 - before creating new allocation remove the latest ones. However this fix is not complete since vew does not remove the default allocations.
// 
//    Rev 1.41   18 Jul 2008 12:49:34   popescu
// IN 1154478 - AMS account level effective date - back the code out
// 
//    Rev 1.40   11 Jun 2008 10:22:04   popescu
// in#1283327 - Trade created with invalid settlement date, Code review regarding modification of Trade and DateValidation CBO.
// 
//    Rev 1.39   Apr 14 2008 14:50:00   jankovii
// IN 1154478 - AMS account level effective date.
// 
//    Rev 1.38   Apr 11 2008 10:12:48   jankovii
// IN 1240143 - User is not able to modify Next Rebalance Date value manually.
// 
//    Rev 1.37   Mar 21 2008 19:18:56   wongsakw
// IN#1201511 Update NextRebalDate when effective date is change (with FreqOverride = no)
// 
//    Rev 1.36   Feb 15 2008 10:52:36   yingz
// more to 1101619, make rebalance flag behaves the same as updatepacswp flag
// 
//    Rev 1.35   13 Feb 2008 10:54:44   kovacsro
// IN#1101612 - added a warning message whenever the user changes the allocations and the effective date is prior to current business date
// 
//    Rev 1.34   12 Feb 2008 16:20:28   kovacsro
// IN# 1101605 : changed boolean into bool for isAmsCodeGlobal
//
//    Rev 1.33   Feb 12 2008 15:54:50   yingz
// fix 1101619 - When submit the modification of Acct level AMS code or AMS allocation, user has a choice to refresh the existing PAC with the same allocation. The refresh should be done with the effective AMS allcation
// 
//    Rev 1.32   08 Feb 2008 15:21:44   kovacsro
// IN#1101605 - cleaned up treshold percentage mess
// 
//    Rev 1.31   31 Dec 2007 15:05:32   kovacsro
// checked in for Winnie (no IN#, no PET#)
// 
//    Rev 1.30   Dec 05 2007 15:02:52   jankovii
// IN 1098016 - Desktop Account Level AMS screen 'Status' Field.
// 
//    Rev 1.29   Dec 04 2007 09:59:26   jankovii
// IN 1098016 - fixed misspelled company code.
// 
//    Rev 1.28   28 Nov 2007 16:11:58   kovacsro
// IN# 1093158 - don't create AMS allocations, when it is not necessary
// 
//    Rev 1.27   Nov 21 2007 12:08:42   smithdav
// IN #1003565 - Soft edit to ensure next AMS
//
//    Rev 1.26   20 Nov 2007 13:32:34   kovacsro
// IN#1046953 - pass last scheduled date into 383, unless unknown (when pass Effective date)
//
//    Rev 1.25   Nov 06 2007 18:30:46   smithdav
// IN1024380 -  Change AMS certificates edit to check at the fund level instead of the account level.
//
//    Rev 1.24   Oct 24 2007 19:10:28   smithdav
// IN1024380 - AMSAcctLevel active Certificates edit.
//
//    Rev 1.23   19 Oct 2007 16:16:20   kovacsro
// IN#1038318 - added rej erros / hard edit to prevent users from entering future dated Stop dates on AMS and modifying Effective Date for RB/RO default allocations on Allocation screen
//
//    Rev 1.22   Oct 10 2007 18:02:06   smithdav
// Do note make SchedSetupFreqID read only. Causing problems with combo-box in gui..
//
//    Rev 1.21   21 Sep 2007 16:24:34   popescu
// Incident 1015469 -  added bCreate to the allocations method
//
//    Rev 1.20   21 Sep 2007 14:31:56   popescu
// Incident 10002765 Added AMS setup edit for institutional accounts
// Checks AMS limitation rules for StopPurchase/StopRedemption/Transfer out and Tarsnfer In
//
//    Rev 1.19   20 Sep 2007 10:55:20   popescu
// Incident 1002765 - fixed the validation for institutional code AMS
//
//    Rev 1.18   14 Sep 2007 14:49:16   popescu
// Incident 1003672 - setup restriction one AMS funds allocation for 100% is not allowed - soft edit
//
//    Rev 1.17   14 Sep 2007 12:22:00   popescu
// Incident 1003672 - setup restriction one AMS funds allocation for 100% is not allowed
//
//    Rev 1.16   14 Sep 2007 10:59:18   popescu
// Incident 1003183 (GAP2360/02) - fixed AMS allocations
//
//    Rev 1.15   11 Sep 2007 14:42:12   popescu
// Incident 1003183 - small fix to have the error for exchangeable funds pop-up. Also changed the value of the company code from AIS to ATS
//
//    Rev 1.14   11 Sep 2007 13:45:18   popescu
// Incident 1003183 - disbled the threshold for all acct lvl ams but 0001
//
//    Rev 1.13   Sep 11 2007 09:02:16   smithdav
// IN 979244 - Non exchangable funds edit.
//
//    Rev 1.12   Sep 07 2007 14:26:36   smithdav
// IN 982733 - set Account level Alloc fields from AMSAcct.
//
//    Rev 1.11   Aug 27 2007 11:01:26   smithdav
// PET 2360 FN02 - Fix RebDate edit, allow 0% threshold
//
//    Rev 1.10   Aug 17 2007 10:30:26   smithdav
// IN #973657
//
//    Rev 1.9   Aug 16 2007 18:04:34   smithdav
// IN #978244
//
//    Rev 1.8   Aug 10 2007 17:08:02   smithdav
// PET 2360 FN02 - fix BrokerAMS edit bug.
//
//    Rev 1.7   Aug 03 2007 09:34:50   smithdav
// PET 2360 FN02
//
//    Rev 1.6   Jul 30 2007 09:19:26   smithdav
// PET 2360 FN02 - Fix FreqOverride flag to use "0","1" instead of "N", "Y". Hide currency, threshold temporarily as it is not working.
//
//    Rev 1.5   Jul 27 2007 11:34:10   smithdav
// PET2360 FN02 - Add NextReb date edits. Add som fiield inits.
//
//    Rev 1.4   Jul 19 2007 14:23:50   smithdav
// PET2360 FN02 - Fix NextRebalanceDate recalc.
//
//    Rev 1.3   Jul 18 2007 09:35:30   smithdav
// PET2360 FN02
//
//    Rev 1.2   Jun 28 2007 16:38:08   porteanm
// PET 2360 FN02 - AMS - work in progress.
//
//    Rev 1.1   Jun 22 2007 14:18:04   porteanm
// PET 2360 FN02 - AMS - work in progress.
//
//    Rev 1.0   Jun 20 2007 11:42:38   porteanm
// Initial revision.
//
