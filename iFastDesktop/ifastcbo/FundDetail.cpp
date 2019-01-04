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
// ^FILE   : FundDetail.cpp
// ^AUTHOR : Karen Jan
// ^DATE   : Dec 19, 2000
//
// ^CLASS    : FundDetail
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "funddetail.hpp"
#include "fundtolist.hpp"
#include "feeinfoinquiry.hpp"
#include "fundtranstypelist.hpp"
#include "FundRuleList.hpp"
#include "FundGroupTypeList.hpp"
#include "mgmtco.hpp"

#include <ifastdataimpl\dse_dstc0056_vw.hpp>
#include <ifastdataimpl\dse_dstc0056_req.hpp>
#include <ifastdataimpl\dse_dstc0107_vw.hpp>
#include <ifastdataimpl\dse_dstc0056_vwrepeat_record.hpp>

namespace
{
   //Trace literals
   const I_CHAR * const CLASSNAME              = I_("FundDetail");
   const I_CHAR * const MINIMUM_AMT            = I_("MINIMUM_AMT");
   const I_CHAR * const FUND                   = I_("FUND");
   const I_CHAR * const CLASS                  = I_("CLASS");
   const I_CHAR * const TRADE_TYPE             = I_("TRADE_TYPE");
   const I_CHAR * const NO                     = I_("N");
   const I_CHAR * const YES                    = I_("Y");
   const I_CHAR   EQUAL_SIGN                   = I_( '=') ;
   const I_CHAR   COMMA_SIGN                   = I_( ',') ;
   const I_CHAR * IDI_EMPTY_MARK               = I_( "(null)" );
}

namespace AMS_MODEL_TYPE
{
    extern CLASS_EXPORT I_CHAR * const NOT_APPLICABLE  = I_("00");
    extern CLASS_EXPORT I_CHAR * const PARENT_FND_CLS  = I_("01");
    extern CLASS_EXPORT I_CHAR * const CHILD_FND_CLS   = I_("02");
}

namespace FUND_LOAD_TYPE
{
    extern CLASS_EXPORT I_CHAR * const BACKEND_LOAD  = I_("BEL");
    extern CLASS_EXPORT I_CHAR * const CHARGEBACK    = I_("CB");
}

namespace TRADETYPE
{
   extern CLASS_IMPORT I_CHAR * const TRANSFER_OUT;
   extern CLASS_IMPORT I_CHAR * const TRANSFER_IN;
   extern CLASS_IMPORT I_CHAR * const EXCHANGE_OUT;
   extern CLASS_IMPORT I_CHAR * const EXCHANGE_IN;
   extern CLASS_IMPORT I_CHAR * const EXCHANGE;
   extern CLASS_IMPORT I_CHAR * const TRANSFER;
   extern CLASS_IMPORT I_CHAR * const ALL_FUND_TRANSFER ;
   extern CLASS_IMPORT I_CHAR * const REDEMPTION;
   extern CLASS_IMPORT I_CHAR * const PURCHASE;
   extern CLASS_IMPORT I_CHAR * const MGMT_FEE;
   extern CLASS_IMPORT I_CHAR * const PAC;
   extern CLASS_IMPORT I_CHAR * const SWP;
   extern CLASS_IMPORT I_CHAR * const AUTO_TRANSFER;
   extern CLASS_IMPORT I_CHAR * const AUTO_TRANSFER_IN;
   extern CLASS_IMPORT I_CHAR * const AUTO_TRANSFER_OUT;
   extern CLASS_IMPORT I_CHAR * const ADMIN_FEE;
   extern CLASS_IMPORT I_CHAR * const ROLLOVER_EXCHANGE;
   extern CLASS_IMPORT I_CHAR * const INTER_CLASS_SWITCH;
   extern CLASS_IMPORT I_CHAR * const INTER_CLASS_SWITCH_IN;
   extern CLASS_IMPORT I_CHAR * const INTER_CLASS_SWITCH_OUT;
}

namespace CND
{
   extern CLASS_IMPORT const long ERR_DATA_NOT_FOUND;
   extern const long ERR_FUND_INVALID_FOR_REGISTER_ACCOUNT;
   extern const long ERR_MINIMUM_INIT_AMT;
   extern const long ERR_MINIMUM_SUBSEQUENT_AMT;
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId CUSIP;
   extern CLASS_IMPORT const BFTextFieldId TDCC;
   extern CLASS_IMPORT const BFTextFieldId Valoren;
   extern CLASS_IMPORT const BFTextFieldId Fund_ID_Values; 
   extern CLASS_IMPORT const BFTextFieldId GrossOrNet; 
   extern CLASS_IMPORT const BFTextFieldId FundGroupCode;
   extern CLASS_IMPORT const BFTextFieldId ApplPUDbyBEL;
   extern CLASS_IMPORT const BFTextFieldId ApplPUDbyCB;
   extern CLASS_IMPORT const BFTextFieldId ApplPUDbyDefault;
}
namespace FUND_ID_CODE
{
 const I_CHAR * const VALOREN	=	I_("Valoren");
 const I_CHAR * const TDCC		=	I_("TDCC");
 const I_CHAR * const CUSIP		=	I_("CUSIP");
}

namespace FUND_RULE_TYPE
{
    extern CLASS_IMPORT I_CHAR * const SOFT_CAPPED;
}

namespace FUND_GROUP_TYPE
{
    extern CLASS_IMPORT I_CHAR * const SOFT_CAPPED;
}

namespace FUND_SUB_CATAGORY
{
   extern CLASS_EXPORT const I_CHAR * const CUSTOM_PAYOUT                 = I_ ("26");
   extern CLASS_EXPORT const I_CHAR * const PORTFOLIO_PAYOUT              = I_ ("27");
}

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = 
{
//  Field DD Id,			State Flags,		Group Flags 
   { ifds::Valoren,        BFCBO::CALCULATED_FIELD,                 0 },
   { ifds::TDCC,           BFCBO::CALCULATED_FIELD,                 0 },
   { ifds::CUSIP,          BFCBO::CALCULATED_FIELD,                 0 },
};

const BFFieldId fundIDFields[]=
{
   ifds::Valoren,
   ifds::TDCC	 ,
   ifds::CUSIP  ,
};

static const int NUM_FIELDS      = sizeof (classFieldInfo) / sizeof ( BFCBO::CLASS_FIELD_INFO );
static const int numfundIDFields = sizeof (fundIDFields)  / sizeof ( BFFieldId );

//******************************************************************************
FundDetail::FundDetail(BFAbstractCBO &parent)
: MFCanBFCbo (parent)
, _pFundToList(NULL)
, _pFeeInfoInquiry(NULL)
, _pFundTransTypeList(NULL)
{
   TRACE_CONSTRUCTOR(CLASSNAME , NULL_STRING);
   registerMemberData ( NUM_FIELDS, (const CLASS_FIELD_INFO *)&classFieldInfo,
                        0, NULL);
   setObjectAsList();
}

//******************************************************************************
FundDetail::~FundDetail()
{
   TRACE_DESTRUCTOR(CLASSNAME);
   delete _pFundToList;
   _pFundToList = NULL;
   delete _pFeeInfoInquiry;
   _pFeeInfoInquiry = NULL;
   if (_pFundTransTypeList)
   {
      delete _pFundTransTypeList;
      _pFundTransTypeList = NULL;
   }
}

//******************************************************************************
SEVERITY FundDetail::init(const BFData &viewData)
{
   MAKEFRAME2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("init"));     

   attachDataObject (const_cast<BFData&>(viewData), false, true);
   _pFundToList = NULL;
   _pFeeInfoInquiry = NULL;
   _pFundTransTypeList = NULL;
   commonInit(BF::HOST);
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY FundDetail::fundClassForPlanType(const DString& dstrPlanType, const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("fundClassForPlanType"));

   DString dstrRSPflag (NULL_STRING), 
      dstrRIFflag (NULL_STRING);

   getField (ifds::RSPflag, dstrRSPflag, idDataGroup);
   getField (ifds::RIFflag, dstrRIFflag, idDataGroup);
   dstrRSPflag.strip().upperCase();
   dstrRIFflag.strip().upperCase();

   if(dstrRSPflag == NO && (dstrPlanType == I_("RSP") || dstrPlanType == I_("LIRA") || dstrPlanType == I_("LRSP")))
   {
      ADDCONDITIONFROMFILE(CND::ERR_FUND_INVALID_FOR_REGISTER_ACCOUNT);      
   }

   if (dstrRIFflag == NO &&  dstrPlanType == I_("RIF"))
   {
      ADDCONDITIONFROMFILE(CND::ERR_FUND_INVALID_FOR_REGISTER_ACCOUNT);      
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
void FundDetail::getFeeInfoInquiryField( const BFFieldId &idField, 
                                         DString &strValue, 
                                         const BFDataGroupId &idDataGroup, 
                                         bool formattedReturn) 
{
   DString dstrFund, 
      dstrClass;

   getField(ifds::FundCode, dstrFund, BF::HOST, false);
   getField(ifds::ClassCode, dstrClass, BF::HOST, false);

   if (!_pFeeInfoInquiry)
   {
      _pFeeInfoInquiry = new FeeInfoInquiry(*this);
      if(_pFeeInfoInquiry->init(dstrFund, dstrClass, NULL_STRING) >= WARNING)
      {
         delete _pFeeInfoInquiry;
         _pFeeInfoInquiry = NULL;
      }
   }
   if (_pFeeInfoInquiry)
   {
      if ( idField == ifds::ClientLvlExch || 
           idField == ifds::ClientLvlTfr)
      {
         _pFeeInfoInquiry->getField (idField, strValue, idDataGroup, formattedReturn);
      }
      else
      {
         BFData data;
         data.setElementValue (ifds::FundCode, dstrFund, true, false);
         data.setElementValue (ifds::ClassCode, dstrClass, true, false);
         DString dstrKey;
         _pFeeInfoInquiry->getStrKey (dstrKey, &data);

         BFObjIter bfIter (*_pFeeInfoInquiry, idDataGroup);
         if (bfIter.positionByKey (dstrKey))
         {
            bfIter.getObject()->getField (idField, strValue, idDataGroup, formattedReturn);
         }
      }
   }
}

//******************************************************************************
bool FundDetail::IsFundValidAtDate (const DString &dstrEffectiveDate, 
                                    const BFDataGroupId &idDataGroup) 
{

   DString dstrFundClassEffectiveDate, 
      dstrFundClassStopDate;

   getField (ifds::EffectiveDate, dstrFundClassEffectiveDate, idDataGroup);
   dstrFundClassEffectiveDate.strip();

   getField (ifds::StopDate, dstrFundClassStopDate, idDataGroup);
   dstrFundClassStopDate.strip();

   return DSTCommonFunctions::IsDateBetween (dstrFundClassEffectiveDate, 
                                             dstrFundClassStopDate, 
                                             dstrEffectiveDate);
}

//******************************************************************************
bool FundDetail::splitCommActive( const DSTCWorkSession &dstcWorkSession, 
                                  const DString &dstrTransType, 
                                  const BFDataGroupId &idDataGroup)
{

   bool bSplitComm(false);
   DString dstrSplitComm(I_("N"));

   dstcWorkSession.getOption (ifds::SplitComm, dstrSplitComm, idDataGroup, false);
   if(dstrSplitComm == I_("Y"))
   {
      if (dstrTransType == TRADETYPE::SWP || dstrTransType == I_("AW"))
      {
         getField(ifds::SplitCommSWP, dstrSplitComm, idDataGroup);      
      }
      else if (dstrTransType == TRADETYPE::PAC)
      {
         getField (ifds::SplitCommPAC, dstrSplitComm, idDataGroup);
      }
      else if(dstrTransType == TRADETYPE::AUTO_TRANSFER || dstrTransType == TRADETYPE::TRANSFER)
      {
         getField(ifds::SplitCommTrfln, dstrSplitComm, idDataGroup);      
      }
      else if (dstrTransType == TRADETYPE::EXCHANGE || dstrTransType == TRADETYPE::INTER_CLASS_SWITCH ||
               dstrTransType == TRADETYPE::EXCHANGE_IN || dstrTransType == TRADETYPE::INTER_CLASS_SWITCH_IN)
      {
         getField(ifds::SplitCommExIn, dstrSplitComm, idDataGroup);
      }
      else if(dstrTransType == TRADETYPE::PURCHASE)
      {
         getField(ifds::SplitCommPur, dstrSplitComm, idDataGroup);      
      }
      else if(dstrTransType == TRADETYPE::REDEMPTION)
      {
         getField(ifds::SplitCommRed, dstrSplitComm, idDataGroup);
      }
		else if(dstrTransType == TRADETYPE::ADMIN_FEE)
      {
         dstrSplitComm = I_('N');
      }
      else if(TRADETYPE::ROLLOVER_EXCHANGE == dstrTransType)
	  {
	     dstrSplitComm = I_("N");
	  }
   }
   bSplitComm = dstrSplitComm == I_("Y");
   return bSplitComm;
}

//******************************************************************************
SEVERITY FundDetail::getFundTransTypeList (FundTransTypeList *&pFundTransTypeList)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("getFundTransTypeList"));

   if (!_pFundTransTypeList)
   {
      _pFundTransTypeList = new FundTransTypeList(*this);
      if (pFundTransTypeList->init() >= SEVERE_ERROR)
      {
         delete _pFundTransTypeList;
         _pFundTransTypeList = NULL;
      }
   }
   pFundTransTypeList = _pFundTransTypeList;
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
bool FundDetail::isFundSoftCapped(const BFDataGroupId &idDataGroup)
{
   DString dstrSoftCapLvl;
   getField(ifds::SoftCapLvl, dstrSoftCapLvl, idDataGroup, false);

   return !dstrSoftCapLvl.empty();
}

//******************************************************************************
bool FundDetail::hasFundSubCat(const DString &fundSubCat, const BFDataGroupId &idDataGroup)
{
   DString fundSubCatList;
   getField(ifds::FundSubCat, fundSubCatList, idDataGroup, false);

   return DSTCommonFunctions::codeInList(fundSubCat, fundSubCatList);
}

//******************************************************************************
bool FundDetail::isCustomPayoutFund(const BFDataGroupId &idDataGroup)
{
    return hasFundSubCat(FUND_SUB_CATAGORY::CUSTOM_PAYOUT, idDataGroup);
}

//******************************************************************************
bool FundDetail::isPortfolioPayoutFund(const BFDataGroupId &idDataGroup)
{
    return hasFundSubCat(FUND_SUB_CATAGORY::PORTFOLIO_PAYOUT, idDataGroup);
}

//******************************************************************************
bool FundDetail::isFundERISAProhibited (const BFDataGroupId &idDataGroup)
{
   DString dstrERISAProhibited;
   
   getField (ifds::ERISAProhibited, dstrERISAProhibited, idDataGroup, false);
  
   return (dstrERISAProhibited == I_("Y"));
}

/******************************************************************************
 Input: IdField,dataGroup,Formatted Return
 OutPut:strValue
 Return:None
 Functionality:	Const function that returns the Fund ID value for the idField
 ******************************************************************************/
void FundDetail::getFundIdValue( const BFFieldId &idField, DString &dstrValue, 
								 const BFDataGroupId &idDataGroup, bool formattedReturn )const
{
   dstrValue = NULL_STRING;
   DString dstrFundIDvalues;
   getField( ifds::Fund_ID_Values, dstrFundIDvalues, idDataGroup );
   if(!dstrFundIDvalues.stripAll().empty())
	{
		DString dstrTDCCValue,dstrCUSIPValue,dstrValorenValue;
		I_CHAR *temp = const_cast<I_CHAR*> (dstrFundIDvalues.c_str ());
		do
		{
			DString dstrFundIDCode,dstrFundIDValue;
			temp = parseIdiString (temp, dstrFundIDCode, dstrFundIDValue, EQUAL_SIGN, COMMA_SIGN );
			if( FUND_ID_CODE::VALOREN == dstrFundIDCode && ifds::Valoren == idField  )
			{
				dstrValue = dstrFundIDValue;   			 
				break;
			}
			else if( FUND_ID_CODE::TDCC == dstrFundIDCode && ifds::TDCC == idField  )
			{
				dstrValue = dstrFundIDValue;
				break;
			}
			else if( FUND_ID_CODE::CUSIP == dstrFundIDCode  && ifds::CUSIP == idField )
			{
				dstrValue = dstrFundIDValue;
				break;
			} 
		}while (temp && temp != NULL_STRING && *temp);
   }
   if( IDI_EMPTY_MARK == dstrValue )
		dstrValue = NULL_STRING;
}

/******************************************************************************
 Input: DataGroup
 OutPut:None
 Return:None
 Functionality:Implementation of common init procedures for the CBO 
******************************************************************************/
SEVERITY FundDetail::commonInit ( const BFDataGroupId &idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                            CLASSNAME, 
                            I_("commonInit"));
   for (int i = 0; i< numfundIDFields; i++)
   {
      DString dstrValue = NULL_STRING;
      getFundIdValue( fundIDFields[i], dstrValue, idDataGroup );
      setFieldNoValidate( fundIDFields[i], dstrValue, idDataGroup, false, true, true );
   }
   return GETCURRENTHIGHESTSEVERITY() ;
}

//******************************************************************************
// Input: DataGroup
// Output:None
// Return:booean 
// Functionality:to indicate whether fund is an AMS parent fund or not
//        regardless its validity period
//******************************************************************************/
bool FundDetail::isAMSParentFund(const BFDataGroupId &idDataGroup)
{
   bool bRetValue = false;
   DString strAMSModelType;
   getField(ifds::AMSModelType,strAMSModelType,idDataGroup,false);
   strAMSModelType.strip().upperCase();

   bRetValue = strAMSModelType == AMS_MODEL_TYPE::PARENT_FND_CLS;

   return bRetValue;
}

//******************************************************************************
// Input: DataGroup
// Output:None
// Return:booean 
// Functionality: to indicate whether fund is an AMS child fund or not 
//         regardless its validity period
//******************************************************************************/
bool FundDetail::isAMSChildFund(const BFDataGroupId &idDataGroup)
{
   bool bRetValue = false;
   DString strAMSModelType;
   getField(ifds::AMSModelType,strAMSModelType,idDataGroup,false);
   strAMSModelType.strip().upperCase();

   bRetValue = strAMSModelType == AMS_MODEL_TYPE::CHILD_FND_CLS;

   return bRetValue;
}
//******************************************************************************
// Input: DataGroup
// Output:GrossNetDefault configured at Fund Class Level
// Return:void 
// Functionality: GrossNetDefault configured at Fund Class Level else NULL_STRING
//******************************************************************************/
void FundDetail::getGrossNetDefault(const BFDataGroupId &idDataGroup, DString &dstrGrossNetDefault, DString& dstrFormattedValue)
{
  MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                            CLASSNAME, 
                            I_("getGrossNetDefault"));
  dstrFormattedValue = NULL_STRING;
  dstrGrossNetDefault = NULL_STRING;
  getField(ifds::GrossOrNet, dstrGrossNetDefault, idDataGroup, false);
  if(!dstrGrossNetDefault.empty())
      getField(ifds::GrossOrNet, dstrFormattedValue, idDataGroup, true);
}

//******************************************************************************/
bool FundDetail::isSoftCapped(const DString& date,
                              const BFDataGroupId &idDataGroup)
{
    bool isSoftCapped = false;
    DString dstrFundCode, dstrClassCode;
    FundRuleList *pSoftCapRuleList = NULL;
    FundGroupTypeList *pFundGroupTypeList = NULL;

    getField(ifds::FundCode, dstrFundCode, idDataGroup, false);
    getField(ifds::ClassCode, dstrClassCode, idDataGroup, false);

    if (!dstrFundCode.empty() && 
        !dstrClassCode.empty() &&
        getMgmtCo().getFundGroupTypeList(pFundGroupTypeList, FUND_GROUP_TYPE::SOFT_CAPPED) <= WARNING && pFundGroupTypeList)
    {
        DString dstrFundGroupCode;
        dstrFundGroupCode = pFundGroupTypeList->getFundGroupCode(dstrFundCode, dstrClassCode);

        if (getMgmtCo().getFundRuleList(FUND_RULE_TYPE::SOFT_CAPPED, pSoftCapRuleList) <= WARNING && pSoftCapRuleList)
        {
            isSoftCapped = pSoftCapRuleList->isSoftCapped(dstrFundCode, dstrClassCode, dstrFundGroupCode, date);
        }
    }

    return isSoftCapped;
}

//******************************************************************************
bool FundDetail::isAmtTypeValidForLoadType(const DSTCWorkSession &dstcWorkSession, 
                                           const DString &amtType, 
                                           const BFDataGroupId &idDataGroup)
{
    DString validAmtTypeList, dstrLoadType, dstrAmtType(amtType);

    getField(ifds::LoadType, dstrLoadType, idDataGroup);
    dstrLoadType.stripAll().upperCase();
    dstrAmtType.stripAll().upperCase();

    if (dstrLoadType == FUND_LOAD_TYPE::BACKEND_LOAD)
    {
        dstcWorkSession.getOption(ifds::ApplPUDbyBEL, validAmtTypeList, idDataGroup);

        if (validAmtTypeList.stripAll().empty())
            dstcWorkSession.getOption(ifds::ApplPUDbyDefault, validAmtTypeList, idDataGroup);
    }
    else if (dstrLoadType == FUND_LOAD_TYPE::CHARGEBACK)
    {
        dstcWorkSession.getOption(ifds::ApplPUDbyCB, validAmtTypeList, idDataGroup);

        if (validAmtTypeList.stripAll().empty())
            dstcWorkSession.getOption(ifds::ApplPUDbyDefault, validAmtTypeList, idDataGroup);
    }
    else
    {
        dstcWorkSession.getOption(ifds::ApplPUDbyDefault, validAmtTypeList, idDataGroup);
    }

    return DSTCommonFunctions::codeInList(dstrAmtType, validAmtTypeList);
}

//******************************************************************************
bool FundDetail::amountInventoryAppl(const BFDataGroupId &idDataGroup)
{
    DString dstrAmtInvAppl;
    getField(ifds::AmountInventoryAppl, dstrAmtInvAppl, idDataGroup);

    return dstrAmtInvAppl.stripAll() == YES;
}
      

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/FundDetail.cpp-arc  $
// 
//    Rev 1.30   Jan 20 2012 15:39:56   wp040027
// P0188394_Performance Fees - Order Entry
// 
//    Rev 1.29   Oct 08 2007 12:16:16   smithdav
// IN  1005517,1020252 - LRSP logic
// 
//    Rev 1.28   23 Jul 2007 16:49:40   popescu
// PET 2360 - FN 20 - GAP 20 Soft cap functionality
// 
//    Rev 1.27   Nov 18 2004 13:28:06   YINGBAOL
// PET1117: Perfermance Tunning
// 
//    Rev 1.26   Nov 14 2004 14:41:52   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.25   Sep 08 2004 18:09:28   ZHANGCEL
// PET1094-FN8 -- AdminFee related changes
// 
//    Rev 1.24   Jun 25 2004 19:04:52   popescu
// PTS 10031525, Fund limitation overrides issue
// 
//    Rev 1.23   Jun 25 2004 16:37:56   popescu
// PST 10031525, fund limitation override issues
// 
//    Rev 1.22   Apr 21 2003 15:19:02   popescu
// the split comm allowed method is looking at the SplitCommExIn flag in order to allow a split commision for the Exchange; before it looked at the SplitComm Trfln flag.
// 
//    Rev 1.21   Mar 21 2003 18:10:56   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.20   Jan 29 2003 15:07:24   WINNIE
// wrong variable name
// 
//    Rev 1.19   Jan 13 2003 14:32:26   WINNIE
// Add Stop flag methods with only the GroupID as parameters
// 
//    Rev 1.18   Jan 12 2003 15:33:42   WINNIE
// Add new stopflag such as StopPAC,StopSWP and Stop Automatic Transfer in/out. These edit checks no longer share with same flag with Purchase, Redemption and Transfer in/out etc. Add new class FundTransTypeList, FundTransType to allow StopFlag override at TaxType, TaxJuris, ProvofResident, Acct Type and Acct Designation level. It allow flexibility of setting the severity to Error, Warning or Ignore
// 
//    Rev 1.17   Oct 09 2002 23:54:32   PURDYECH
// PVCS Database Conversion
// 
//    Rev 1.16   Sep 09 2002 13:33:22   PURDYECH
// initialize member variables in ctor
// 
//    Rev 1.15   Aug 29 2002 12:55:54   SMITHDAV
// ClientLocale and typed field changes.
// 
//    Rev 1.14   22 May 2002 18:28:42   PURDYECH
// BFData Implementation
// 
//    Rev 1.13   20 Feb 2002 17:58:04   WINNIE
// new method for each stopflag
// 
//    Rev 1.12   Nov 29 2001 16:15:40   ZHANGCEL
// Correct mistak "delete pFundToList" to " delete _pFundToList"
// 
//    Rev 1.11   Oct 30 2001 18:01:44   ZHANGCEL
// Added more codes in order to get field's value of FeeInfo
// 
//    Rev 1.10   Oct 29 2001 16:09:32   ZHANGCEL
// Added a new method: getFeeInfoInquiryField()
// 
//    Rev 1.9   Sep 18 2001 15:47:44   YINGBAOL
// fix memory leak
// 
//    Rev 1.8   13 Jul 2001 14:47:08   YINGZ
// fix 0 cut problem for cnd
// 
//    Rev 1.7   Jul 11 2001 10:52:04   JANKAREN
// Bug fix
// 
//    Rev 1.6   17 May 2001 10:42:32   HSUCHIN
// added DSTCWorkSession param to SplitCommActive
// 
//    Rev 1.5   09 May 2001 14:16:28   HSUCHIN
// Sync up with SSB
// 
//    Rev 1.3.1.2   Apr 27 2001 17:08:32   WINNIE
// include more trans type for split comm
// 
//    Rev 1.3.1.1   Apr 26 2001 10:10:10   WINNIE
// set worksession id
// 
//    Rev 1.3.1.0   Apr 24 2001 18:36:42   WINNIE
// new method to check if splitCommission is active
// 
//    Rev 1.3   Mar 22 2001 14:34:44   WINNIE
// new method to check if fund is active
// 
//    Rev 1.2   Mar 10 2001 15:14:12   WINNIE
// fund detail own the fundlist instead having master list : to improve performance for transfer/exchange
// 
//    Rev 1.1   Feb 06 2001 11:41:06   JANKAREN
// Add idiString tag assignment for checkMinInitAmt and checkMinSubAmt
// 
//    Rev 1.0   Jan 31 2001 11:19:32   JANKAREN
// Initial revision.

*/