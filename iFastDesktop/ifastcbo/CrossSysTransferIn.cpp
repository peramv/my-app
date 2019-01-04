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
//    Copyright 2000 by International Financial Data Services
//
//******************************************************************************
//
// ^FILE   : CrossSysTransferIn.hpp
// ^AUTHOR : Robbins Kuriakose
// ^DATE   : Nov, 2014
//
// ^CLASS    :CrossSysTransferIn
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************


#include "stdafx.h"
#include "CrossSysTransferIn.hpp"
#include "dstcworksession.hpp"
#include <ifastcbo\FundDetailList.hpp>
#include <ifastcbo\Funddetail.hpp>
#include <ifastcbo\mgmtco.hpp>
#include <conditions\iFastLayer\iFast\ifastcbo\IFast_IFast_ifastcbo_err_warn_includes.h>

namespace ifds
{
    //attributes grid
   extern CLASS_IMPORT const BFTextFieldId TradeAttributesFields;
   extern CLASS_IMPORT const BFTextFieldId PurchaseAttributes;
   extern CLASS_IMPORT const BFTextFieldId PurchasePayType;
   extern CLASS_IMPORT const BFTextFieldId G1G2CalcMethd;
   extern CLASS_IMPORT const BFTextFieldId G1G2TrackType;
   extern CLASS_IMPORT const BFTextFieldId FundClassSheduleAvailable;
   extern CLASS_IMPORT const BFTextFieldId G1G2UnitsXEdit;
   extern CLASS_IMPORT const BFDecimalFieldId UnitsPrecision;
   extern CLASS_IMPORT const BFDecimalFieldId USDollar;
 }

namespace CND
{
   extern const long  ERR_FIELD_REQUIRED_PLS_ENTER;
   CIFast_IFast_ifastcbo_err_g1_g2_total_not_matching;
   CIFast_IFast_ifastcbo_warn_cross_system_acct_num_empty;
   CIFast_IFast_ifastcbo_err_cross_system_acct_num_empty;
}

namespace IFASTERR
{
   extern CLASS_IMPORT I_CHAR * const CROSS_SYSTEM_ACCT_NUM_EMPTY;
}

namespace TRADETYPE
{
   extern CLASS_IMPORT I_CHAR * const CROSS_SYSTEM_TRANSFER_IN;
}

namespace
{
   //Trace literals
   const I_CHAR * const CLASSNAME   =   I_ ("CrossSysTransferIn");
   const I_CHAR * GROSS			    =   I_("Y");
   const I_CHAR * NET			    =   I_("N");
   const I_CHAR * UNITS			    =   I_("U");
   const I_CHAR * DIRECT			=   I_("N");
   const I_CHAR * G1G2_INV_TRACKING_ON	 =   I_("1");
   const I_CHAR * const G1G2_APPLICABLE  = I_( "01" );
}

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = {
   //Field DD Id,                 State Flags,                    Group Flags
   { ifds::CrossSysAcctNum,      BFCBO::NONE,                         0 },

};
static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );

const BFFieldId CrossSysTransferInReadOnlyFields[] =
{
  ifds::AmtType,
  ifds::GrossOrNet,
  ifds::TradesPayType,
  ifds::OrderType,
  //ifds::PurchasePayType,
};

static const int num_CrossSysTransferInReadOnlyFields= sizeof( CrossSysTransferInReadOnlyFields ) / sizeof( BFFieldId );

//******************************************************************************
CrossSysTransferIn::CrossSysTransferIn (BFAbstractCBO &parent) : Purchase (parent), Trade (parent)
{
   TRACE_CONSTRUCTOR ( CLASSNAME, 
                       NULL_STRING);
   registerMemberData( NUM_FIELDS, (const CLASS_FIELD_INFO *)&classFieldInfo,
                       0,NULL);
}

//******************************************************************************
CrossSysTransferIn::~CrossSysTransferIn ()
{
   TRACE_DESTRUCTOR (CLASSNAME);
}  

//(ED98,PW98) does not provide support for  allocations, fees, commissions
//******************************************************************************
bool CrossSysTransferIn::isSplitCommissionAllowed (const BFDataGroupId &idDataGroup) 
{ 
    MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("isSplitCommissionAllowed"));
    return false; 
}
//******************************************************************************
bool CrossSysTransferIn::isROAApplicable (const BFDataGroupId &idDataGroup)        
{ 
    MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("isROAApplicable"));
    return false; 
}
//******************************************************************************
bool CrossSysTransferIn::isEUSDApplicable (const BFDataGroupId &idDataGroup)    
{ 
    MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("isEUSDApplicable"));
    return false; 
}
//******************************************************************************
bool CrossSysTransferIn::isAssociationToOriginalContribAllowed (const BFDataGroupId &idDataGroup) 
{ 
    MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("isAssociationToOriginalContribAllowed"));
    return false; 
}
//******************************************************************************
bool CrossSysTransferIn::areAllocationsAllowed (const BFDataGroupId &idDataGroup)
{ 
    MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("areAllocationsAllowed"));
    return false; 
}
//******************************************************************************
bool CrossSysTransferIn::areTaxRatesAllowed (const BFDataGroupId &idDataGroup)
{ 
    MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("areTaxRatesAllowed"));
    return false; 
}
//******************************************************************************
bool CrossSysTransferIn::supportsAllocations (const BFDataGroupId &idDataGroup)
{ 
    MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("supportsAllocations"));
    return false; 
}
//******************************************************************************
bool CrossSysTransferIn::supportsFromAllocations (const BFDataGroupId &idDataGroup)
{ 
    MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("supportsFromAllocations"));
    return false; 
}
//******************************************************************************
bool CrossSysTransferIn::areRESPBenefAllocationsAllowed (const BFDataGroupId &idDataGroup)
{ 
    MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("areRESPBenefAllocationsAllowed"));
    return false; 
}
//******************************************************************************
bool CrossSysTransferIn::isRESPTransferAllowed (const BFDataGroupId &idDataGroup)
{ 
    MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("isRESPTransferAllowed"));
    return false; 
}
//******************************************************************************
bool CrossSysTransferIn::isRDSPTransferAllowed (const BFDataGroupId &idDataGroup)
{ 
    MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("isRDSPTransferAllowed"));
    return false; 
}
//******************************************************************************
//set the default from tarde default and not apply purchase overrides
void CrossSysTransferIn::setDefaultPayType ( const DString dstrAccountNum, 
                                                DString &payType,
                                                const BFDataGroupId &idDataGroup)
{ 
    MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("setDefaultPayType"));
    ////get the default configuration form GC and set it so that the purchase overide for these fields are nullified 
    return; 
}
//******************************************************************************   
SEVERITY CrossSysTransferIn::getDefaultFundClassPayType (const DString dstrAccountNum, 
                                                            DString &payType,
                                                            const DString dstrFundCode,
                                                            const DString dstrClassCode,
                                                            const BFDataGroupId &idDataGroup)
{ 
    MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("getDefaultFundClassPayType"));
   setDefaultPayType (dstrAccountNum, payType,idDataGroup);
   return NO_SEVERITY; 
}
//******************************************************************************  
//the value i set by the system.So just return without validation.
SEVERITY CrossSysTransferIn::validateAmtTypeGrossNet (const BFDataGroupId &idDataGroup) 
{ 
    MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("validateAmtTypeGrossNet"));
    return NO_SEVERITY; 
}  
//only direct trades are allowed
//******************************************************************************
bool CrossSysTransferIn::isWireSupported (const BFDataGroupId &idDataGroup)
{
  MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("isWireSupported"));
    return false;
}
//******************************************************************************
SEVERITY CrossSysTransferIn::doInit (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("doInit"));
   setFieldNoValidate ( ifds::TradesTransType, 
                        TRADETYPE::CROSS_SYSTEM_TRANSFER_IN, 
                        idDataGroup, 
                        false);
//attributes grid,set this as default, just to show something on the screen
   return GETCURRENTHIGHESTSEVERITY ();
}
//******************************************************************************
SEVERITY CrossSysTransferIn::doInit (const BFData &data)
{
    MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                            CLASSNAME, 
                            I_("doInit"));
   Purchase::doInit(data);
   commonInit(BF::HOST);
   return GETCURRENTHIGHESTSEVERITY ();
}
//******************************************************************************
void CrossSysTransferIn::doInitWithDefaultValues (const BFDataGroupId &idDataGroup)
{
    MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                            CLASSNAME, 
                            I_("doInitWithDefaultValues"));
    Purchase::doInitWithDefaultValues(idDataGroup);
    //get the default configuration form GC and set it so that the purchase overide for these fields are nullified
    DString dstrPayType, dstrAmtType, dstrNullString = NULL_STRING;
    getTradeDefaults ( dstrPayType, dstrAmtType,
                       dstrNullString, dstrNullString, 
                       idDataGroup);
    setFieldNoValidate( ifds::AmtType, dstrAmtType, idDataGroup, false); //should be from Generic control...
    setFieldNoValidate( ifds::TradesPayType, defaultPayType, idDataGroup, false); //should be from Generic control...
    //setFieldNoValidate( ifds::PurchasePayType, dstrPayType, idDataGroup, false);
    setFieldNoValidate( ifds::OrderType, DIRECT, idDataGroup, false, 
						false, true, true);
    setFieldNoValidate( ifds::GrossOrNet, NET, idDataGroup, false, 
						false, true, true);

    commonInit(idDataGroup);
   
}
//******************************************************************************
void CrossSysTransferIn::commonInit (const BFDataGroupId &idDataGroup)
{

    MAKEFRAMEAUTOPROMOTE2 (  CND::IFASTCBO_CONDITION, 
                             CLASSNAME, 
                             I_("commonInit"));

    for(int i= 0; i < num_CrossSysTransferInReadOnlyFields; i++ )
    {
        setFieldReadOnly(CrossSysTransferInReadOnlyFields[i], idDataGroup, true);
    }
    if(isRebook() || isNew())
    {
        setFieldNoValidate( ifds::G1Impact, NULL_STRING, idDataGroup, false, false, true, true);
        setFieldNoValidate( ifds::G2Impact, NULL_STRING, idDataGroup, false, false, true, true);
        setFieldNoValidate( ifds::Amount, NULL_STRING, idDataGroup, false, false, true, true);
    }
    setG1G2ReadOnlyForFundClass(idDataGroup);
}
//******************************************************************************
SEVERITY CrossSysTransferIn::preInitWithDefaultValues (const BFDataGroupId &idDataGroup)
{
    MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                            CLASSNAME, 
                            I_("preInitWithDefaultValues"));
    
   Purchase::preInitWithDefaultValues(idDataGroup);
    
   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY CrossSysTransferIn::doValidateField ( const BFFieldId &idField, 
                                                  const DString &strValue, 
                                                  const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (  CND::IFASTCBO_CONDITION, 
                            CLASSNAME, 
                            I_("doValidateField"));

   Purchase::doValidateField(idField, strValue, idDataGroup);
   if( ifds::G1G2UnitsXEdit == idField )
    {
        validateG1G2Entries(idDataGroup);
    }
   return GETCURRENTHIGHESTSEVERITY ();
}
//******************************************************************************
SEVERITY CrossSysTransferIn::doValidateAll ( const BFDataGroupId &idDataGroup, 
                                                long lValidateGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (  CND::IFASTCBO_CONDITION, 
                            CLASSNAME, 
                            I_("doValidateField"));

   if( Purchase::doValidateAll(idDataGroup, lValidateGroup) <= WARNING)
   {
       DString dstrCrossSysAcctNum;  
       getField( ifds::CrossSysAcctNum, dstrCrossSysAcctNum, idDataGroup );
       if(dstrCrossSysAcctNum.empty())
         {
            CND::CIFast_IFast_ifastcbo_err_cross_system_acct_num_empty err_cross_system_acct_num_empty;
            CND::CIFast_IFast_ifastcbo_warn_cross_system_acct_num_empty warn_cross_system_acct_num_empty;
            getErrMsg(  IFASTERR::CROSS_SYSTEM_ACCT_NUM_EMPTY,
                        err_cross_system_acct_num_empty, 
                        warn_cross_system_acct_num_empty, 
                        idDataGroup);
         }
   }
   return GETCURRENTHIGHESTSEVERITY ();
}
//******************************************************************************
void CrossSysTransferIn::validateG1G2Entries ( const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (  CND::IFASTCBO_CONDITION, 
                            CLASSNAME, 
                            I_("validateG1G2Entries"));
   if(!isG1G2ApplicableTrade( idDataGroup))
      return;
   DString dstrAmount, dstrG1Impact, dstrG2Impact;
   getField( ifds::Amount, dstrAmount, idDataGroup );
   getField( ifds::G1Impact, dstrG1Impact, idDataGroup);
   getField( ifds::G2Impact, dstrG2Impact, idDataGroup);
   double dAmount, dG1Impact, dG2Impact;
   dAmount   = DSTCommonFunctions::convertToDouble (dstrAmount);
   dG1Impact = DSTCommonFunctions::convertToDouble (dstrG1Impact);
   dG2Impact = DSTCommonFunctions::convertToDouble (dstrG2Impact);

   if( dstrAmount.empty() || dAmount <   0.00000000001 )
   {
     return;//if amount is zero dont validate 
   }   
   if(  dstrG1Impact.empty() &&
        dG1Impact <   0.00000000001 &&
        dstrG2Impact.empty() && 
		dG2Impact <  0.00000000001 )
   {
     ADDCONDITIONFROMFILE( CND::ERR_FIELD_REQUIRED_PLS_ENTER);
   } 
   if( dAmount != dG1Impact + dG2Impact )
   {
     CND::CIFast_IFast_ifastcbo_err_g1_g2_total_not_matching err_g1_g2_total_not_matching; 
     ADDCONDITIONFROMOBJECT( err_g1_g2_total_not_matching );
   }
}
//******************************************************************************
bool CrossSysTransferIn::isG1G2ApplicableTrade(const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "isG1G2ApplicableTrade" ) );
   
   DString dstrFrFund, dstrFrClass, dstrG1G2CalcMethod, dstrG1G2TrackType;
   getField(ifds::FromFund, dstrFrFund, idDataGroup );
   getField(ifds::FromClass, dstrFrClass, idDataGroup );
   getWorkSession().getOption ( ifds::G1G2CalcMethd, dstrG1G2CalcMethod, BF::HOST, false);   
   if( G1G2_INV_TRACKING_ON != dstrG1G2CalcMethod )
       return false;
   if(!dstrFrFund.stripAll().empty() && !dstrFrClass.stripAll().empty())
   {
     FundDetailList *pFundDetailList = NULL;
     if(getMgmtCo().getFundDetailList(pFundDetailList) <= WARNING  && pFundDetailList)
     {	   
	  FundDetail *pFundDetail = NULL;
   	  if( pFundDetailList->getFundDetail(dstrFrFund, dstrFrClass, BF::HOST, pFundDetail ) && 
          pFundDetail )
		  pFundDetail->getField( ifds::G1G2TrackType, dstrG1G2TrackType, BF::HOST, false);
   	 }      
   }
   DString dstrG1G2Appl = (G1G2_APPLICABLE == dstrG1G2TrackType) ? I_("Y") : I_("N");
   return(G1G2_APPLICABLE == dstrG1G2TrackType );
}
//******************************************************************************
SEVERITY CrossSysTransferIn::doApplyRelatedChanges ( const BFFieldId &idField, 
                                                   const BFDataGroupId &idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doApplyRelatedChanges" ) );

   if (Purchase::doApplyRelatedChanges (idField, idDataGroup) <= WARNING)
   {
     if( ifds::FromFund == idField|| ifds::FromClass == idField)
     {
       setFieldNoValidate( ifds::G1Impact, NULL_STRING, idDataGroup, false ,false, true, true);
       setFieldNoValidate( ifds::G2Impact, NULL_STRING, idDataGroup, false ,false, true, true);
       DString  dstrFundCode, dstrClassCode, dstrFundCurrency;
       getFundField (ifds::FundCode, dstrFundCode, idDataGroup);
       getFundField (ifds::ClassCode, dstrClassCode, idDataGroup);
       if (!dstrFundCode.empty () && !dstrClassCode.empty())
           getFundField (dstrFundCode, dstrClassCode, ifds::Currency, dstrFundCurrency);
       setFieldNoValidate (ifds::SettleCurrency, dstrFundCurrency, idDataGroup, false, true, true, true);         
       if(isG1G2ApplicableTrade(idDataGroup))
          setG1G2ReadOnlyForFundClass(idDataGroup);
     }
   }
   //Whatever may be purchase overides the below fields should be read only 
   for(int i= 0; i < num_CrossSysTransferInReadOnlyFields; i++ )
   {
        setFieldReadOnly(CrossSysTransferInReadOnlyFields[i], idDataGroup, true);
   }
   return GETCURRENTHIGHESTSEVERITY ();
}
//******************************************************************************
void CrossSysTransferIn::setG1G2ReadOnlyForFundClass(const BFDataGroupId &idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "setG1G2ReadOnlyForFundClass" ) );
   DString dstrFrFund, dstrFrClass, dstrFundClassSheduleAvailable;
   getField(ifds::FromFund, dstrFrFund, idDataGroup );
   getField(ifds::FromClass, dstrFrClass, idDataGroup );
   bool bG1G2ApplicableTrade = isG1G2ApplicableTrade(idDataGroup);
   if( bG1G2ApplicableTrade )
   {
     FundDetailList *pFundDetailList = NULL;
     if(getMgmtCo().getFundDetailList(pFundDetailList) <= WARNING  && pFundDetailList)
     {	   
	  FundDetail *pFundDetail = NULL;
   	  if( pFundDetailList->getFundDetail(dstrFrFund, dstrFrClass, BF::HOST, pFundDetail ) && 
          pFundDetail )
		  pFundDetail->getField( ifds::FundClassSheduleAvailable, dstrFundClassSheduleAvailable, BF::HOST, false);
   	 }     
   }
   setFieldReadOnly(ifds::G2Impact, idDataGroup, !bG1G2ApplicableTrade );
   setFieldReadOnly(ifds::G1Impact, idDataGroup, I_("Y") != dstrFundClassSheduleAvailable );
}
//******************************************************************************
SEVERITY CrossSysTransferIn::setField ( const BFFieldId &idField, 
                                         const DString &dstrValue,
                                         const BFDataGroupId &idDataGroup, 
                                         bool bFormatted, 
                                         bool bSideEffect, 
                                         bool bCheckCurrentValue)
{
    MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, CLASSNAME, I_("setField"));
    DString value (dstrValue);
    Trade::setField(idField, value, idDataGroup, bFormatted, bSideEffect, bCheckCurrentValue);
    if( ifds::G1Impact ==  idField || ifds::G2Impact ==  idField  )
    {
      getFormattedG1G2Units (idDataGroup, value);
      BFCBO::setField ( idField, value, idDataGroup, bFormatted && !value.empty(), true, bCheckCurrentValue );
    }
   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
void CrossSysTransferIn::getField ( const BFFieldId &idField, 
                       DString &fieldValue, 
                       const BFDataGroupId &idDataGroup, 
                       bool formattedReturn) const
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, CLASSNAME, I_("getField"));
   Trade::getField( idField, fieldValue, idDataGroup, formattedReturn ); 
   if( ifds::G1Impact ==  idField || ifds::G2Impact ==  idField)
   {
       BFCBO::getField (idField, fieldValue, idDataGroup, false);
       getFormattedG1G2Units(idDataGroup, fieldValue);
   }   
}
//**********************************************************
void CrossSysTransferIn::getFormattedG1G2Units ( const BFDataGroupId &idDataGroup, 
                                    DString &value) const
{

   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, CLASSNAME, I_("getFormattedG1G2Units"));
   //format only if 
   if (getErrorState (ifds::G1G2UnitsXEdit, idDataGroup) <= WARNING )
   {
      DString amtType, 
         settleCurrency;

      getField (ifds::AmtType, amtType, idDataGroup, false);
      amtType.strip ();
      getField (ifds::SettleCurrency, settleCurrency, idDataGroup, false);
      settleCurrency.strip ();

      if (amtType != I_("U"))
      {
         CurrencyClass::getFormattedValue (getWorkSession (), value, settleCurrency, amtType);
      }
      else
      {
         int iUnitsPrecision = 0;

         FundDetail *pFundDetail = NULL;
         DString unitsPrecision, 
            fundCode, 
            classCode;

         getField (ifds::FromFund, fundCode, idDataGroup, false);
         getField (ifds::FromClass, classCode, idDataGroup, false);

         if ( const_cast <CrossSysTransferIn*>(this)->
              getFundField ( fundCode, classCode, ifds::UnitsPrecision, unitsPrecision) <= WARNING &&
              !unitsPrecision.empty())
         {
            iUnitsPrecision = unitsPrecision.asInteger (); 
         }
         DSTCommonFunctions::formattedField (ifds::USDollar, iUnitsPrecision, value); 
      }
   }
   else //use a default formatter
   {
      formatField (ifds::G1Impact, value, idDataGroup);
      formatField (ifds::G2Impact, value, idDataGroup);
   }
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/CrossSysTransferIn.cpp-arc  $
 
*/  



