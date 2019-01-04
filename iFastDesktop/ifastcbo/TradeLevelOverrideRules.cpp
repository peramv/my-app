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
//    Copyright 1997 by DST Systems, Inc.
//
//
//******************************************************************************
//
// ^FILE   : TradeLevelOverrideRules.cpp
// ^AUTHOR : Robbins Kuriakose
// ^DATE   : May, 2014
//
// ^CLASS  : TradeLevelOverrideRules
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include "stdafx.h"
#include "funddetail.hpp"
#include "funddetaillist.hpp"
#include "TradeLevelOverrideRules.hpp"
#include "mfaccount.hpp"
#include <ifastdataimpl\dse_dstc0462_req.hpp>
#include <ifastdataimpl\dse_dstc0462_vw.hpp>
#include "mgmtco.hpp"


namespace CORFAX
{
   extern CLASS_IMPORT const DSTCHost HOST;
   const char *const CFX_TRANS = "CFXTRAN";
}

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest TRADE_LEVEL_OVERRIDE_RULES;
}

namespace CND
{  
   extern const long ERR_STOP_FLAG_SET_FOR_FUND; /* %LEVEL% Level Stop Rule Active For the Fund %FUND% and Class %CLASS% for %TRANSTYPE%*/
   extern const long WARN_STOP_FLAG_SET_FOR_FUND;
   extern const long ERR_UNKNOWN_ERROR;
}

namespace IFASTERR
{
   extern CLASS_IMPORT I_CHAR * const KIID_ATTESTATION;
}
namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId StopRuleLevel;
}

namespace ERROR_NUM
{

//PURCHASE
   const long ACCT_PURCHASE_NOT_ALLOWED               = 735;
   const long BROKER_PURCHASE_NOT_ALLOWED             = 736;
   const long BRANCH_PURCHASE_NOT_ALLOWED             = 737;
   const long SLSREP_PURCHASE_NOT_ALLOWED             = 738;
   const long PURCHASE_NOT_ALLOWED                    = 739;

//REDEMPTION

   const long ACCT_REDEMPTION_NOT_ALLOWED             = 740;
   const long BROKER_REDEMPTION_NOT_ALLOWED           = 741;
   const long BRANCH_REDEMPTION_NOT_ALLOWED           = 742;
   const long SLSREP_REDEMPTION_NOT_ALLOWED           = 743;
   const long FUND_REDEMPTION_NOT_ALLOWED             = 744;

//TRANSFER OUT
   const long ACCT_TO_TRANSFER_NOT_ALLOWED            = 745;
   const long BROKER_TO_TRANSFER_NOT_ALLOWED          = 746;
   const long BRANCH_TO_TRANSFER_NOT_ALLOWED          = 747;
   const long SLSREP_TO_TRANSFER_NOT_ALLOWED          = 748;
   const long TO_TRANSFER_NOT_ALLOWED                 = 759;

//TRANSFER IN
   const long ACCT_FROM_TRANSFER_NOT_ALLOWED          = 750;
   const long BROKER_FROM_TRANSFER_NOT_ALLOWED        = 751;
   const long BRANCH_FROM_TRANSFER_NOT_ALLOWED        = 752;
   const long SLSREP_FROM_TRANSFER_NOT_ALLOWED        = 753;
   const long FROM_TRANSFER_NOT_ALLOWED               = 754;  
}
namespace
{
   const I_CHAR * const CLASSNAME                     = I_ ("TradeLevelOverrideRules");
   const I_CHAR * const YES                           = I_ ("Y");  
   const I_CHAR * const EWI_ERROR                     = I_ ("E");
   const I_CHAR * const EWI_WARNING                   = I_ ("W");
   const I_CHAR * const STR_COMMA_TAG                 = I_ (",");  
}
const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = 
{
   //  Field DD Id,                 State Flags,                        Group Flags 
   { ifds::StopRuleLevel,        BFCBO::NOT_ON_HOST,                  0}, 
};
static const int NUM_FIELDS = sizeof(classFieldInfo) / sizeof(BFCBO::CLASS_FIELD_INFO);

//******************************************************************************
TradeLevelOverrideRules::TradeLevelOverrideRules (BFAbstractCBO &parent)
: MFCanBFCbo (parent),
_dstrFundCode  (NULL_STRING),
_dstrClassCode  (NULL_STRING),
_dstrAccountNum(NULL_STRING)
{
   TRACE_CONSTRUCTOR (CLASSNAME , NULL_STRING);
   registerMemberData (NUM_FIELDS,  (const CLASS_FIELD_INFO *)&classFieldInfo, 0, NULL);
   setObjectAsList ();
}

//******************************************************************************
TradeLevelOverrideRules::~TradeLevelOverrideRules ()
{
   TRACE_DESTRUCTOR (CLASSNAME);
}

//******************************************************************************
SEVERITY TradeLevelOverrideRules::init (const DString &dstrAccountNum, 
                                        const DString &dstrFundCode, 
                                        const DString &dstrClassCode, 
                                        const DString &dstrTransType, 
                                        const DString &dstrEffectiveDate, 
                                        const DString &dstrBrokerCode, 
                                        const DString &dstrBranchCode,
								        const DString &dstrSalesRepCode,
                                        bool  bDataNotFounderror /*=false*/)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_ ("init"));
   BFData queryData  (ifds::DSTC0462_REQ);

   _dstrFundCode    = dstrFundCode;
   _dstrClassCode   = dstrClassCode;
   _dstrAccountNum  = dstrAccountNum;
   _dstrAccountNum.strip().stripLeading( '0' );
   _dstrEffectiveDate = dstrEffectiveDate;
   _dstrTransType     = dstrTransType;
   _dstrBrokerCode    = dstrBrokerCode;
   _dstrBranchCode    = dstrBranchCode;
   _dstrSalesRepCode  = dstrSalesRepCode;   

   DString mgmtCoIdOut;
   queryData.setElementValue (ifds::CompanyId, getMgmtCoId (mgmtCoIdOut));
   queryData.setElementValue (ifds::AccountNum, dstrAccountNum);
   queryData.setElementValue (ifds::FundCode,   dstrFundCode);
   queryData.setElementValue (ifds::ClassCode,  dstrClassCode);
   queryData.setElementValue (ifds::TransType,  dstrTransType);
   queryData.setElementValue (ifds::EffectiveDate, dstrEffectiveDate, false, false);
   queryData.setElementValue (ifds::BrokerCode, dstrBrokerCode);
   queryData.setElementValue (ifds::BranchCode, dstrBranchCode);
   queryData.setElementValue (ifds::SalesRepCode, dstrSalesRepCode);
   ReceiveData  (DSTC_REQUEST::TRADE_LEVEL_OVERRIDE_RULES, 
                 queryData, 
                 ifds::DSTC0462_VW,
                 DSTCRequestor  (getSecurity (), true, bDataNotFounderror));
   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY TradeLevelOverrideRules::addConditions (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2  (CND::IFASTCBO_CONDITION, CLASSNAME, I_ ("addConditions"));

   DString idiStr, dstrErrNum, dstrEWI;
   DString dstrMarket;
   dstrMarket = DSTCommonFunctions::getMarket();
   idiStr = NULL_STRING;
   getField  (ifds::ErrNum, dstrErrNum, BF::HOST, false);
   getField  (ifds::EWI, dstrEWI, BF::HOST, false);
   dstrEWI.upperCase ();         
   dstrErrNum.strip ().stripLeading ('0').stripAll();        
   if(dstrErrNum.empty()) 
      return (GETCURRENTHIGHESTSEVERITY ());
   DString  dstrErrorCodeList;
   BFProperties *pBFProperties = getFieldProperties (ifds::StopRuleLevel, idDataGroup); 
   assert (pBFProperties);
   if (pBFProperties) 
   {
    pBFProperties->getAllSubstituteValues (dstrErrorCodeList);
    I_CHAR *temp = const_cast<I_CHAR*> (dstrErrorCodeList.c_str ());
    do
    {
         DString dstrErrorCode, dstrErrorCodeDesc, dstrLevel, dstrRuleTransType, dstrLevelCode;
         temp = parseIdiString (temp, dstrErrorCode, dstrErrorCodeDesc);            
         if (dstrErrNum == dstrErrorCode )
         {
            DString::size_type iPosLevel     = dstrErrorCodeDesc.find( STR_COMMA_TAG );
            DString dstrTag = STR_COMMA_TAG;
            DString::size_type iTagLen = dstrTag .size();
            if( iPosLevel != std::string::npos )
            {
             dstrLevel = dstrErrorCodeDesc.substr(0, (iPosLevel ));
             dstrRuleTransType = dstrErrorCodeDesc.substr((iPosLevel + iTagLen ), dstrErrorCodeDesc.size());
             long nErrNum = dstrErrNum.strip ().stripLeading ('0').convertToULong (); 
             switch(nErrNum)
             {
                case  ERROR_NUM::ACCT_PURCHASE_NOT_ALLOWED :
                case  ERROR_NUM::ACCT_REDEMPTION_NOT_ALLOWED:
                case  ERROR_NUM::ACCT_TO_TRANSFER_NOT_ALLOWED:
                case  ERROR_NUM::ACCT_FROM_TRANSFER_NOT_ALLOWED:
                      {
                       dstrLevelCode = _dstrAccountNum;
                       break;
                      }
                case  ERROR_NUM::BROKER_PURCHASE_NOT_ALLOWED:
                case  ERROR_NUM::BROKER_REDEMPTION_NOT_ALLOWED:
                case  ERROR_NUM::BROKER_TO_TRANSFER_NOT_ALLOWED:
                case  ERROR_NUM::BROKER_FROM_TRANSFER_NOT_ALLOWED:
                      {
                       dstrLevelCode = _dstrBrokerCode;
                       break;
                      }
                case  ERROR_NUM::BRANCH_PURCHASE_NOT_ALLOWED :
                case  ERROR_NUM::BRANCH_REDEMPTION_NOT_ALLOWED:
                case  ERROR_NUM::BRANCH_TO_TRANSFER_NOT_ALLOWED:
                case  ERROR_NUM::BRANCH_FROM_TRANSFER_NOT_ALLOWED:
                      {
                       dstrLevelCode = _dstrBranchCode;
                       break;
                      }
                case  ERROR_NUM::SLSREP_PURCHASE_NOT_ALLOWED :
                case  ERROR_NUM::SLSREP_REDEMPTION_NOT_ALLOWED:
                case  ERROR_NUM::SLSREP_TO_TRANSFER_NOT_ALLOWED:
                case  ERROR_NUM::SLSREP_FROM_TRANSFER_NOT_ALLOWED:
                      {
                       dstrLevelCode = _dstrSalesRepCode;
                       break;
                      }
                default:
                       break;
             }
                          
             addIDITagValue (idiStr, I_("LEVEL"),    dstrLevel +  dstrLevelCode ); 
             addIDITagValue (idiStr, I_("FUND") ,   _dstrFundCode  );
             addIDITagValue (idiStr, I_("CLASS"),   _dstrClassCode );
             addIDITagValue (idiStr, I_("TRANSTYPE"),dstrRuleTransType);        
             if  (dstrEWI == EWI_WARNING)
                  ADDCONDITIONFROMFILEIDI (CND::WARN_STOP_FLAG_SET_FOR_FUND, idiStr);
             if  (dstrEWI == EWI_ERROR)
                  ADDCONDITIONFROMFILEIDI (CND::ERR_STOP_FLAG_SET_FOR_FUND, idiStr);
            }       
            break;
          }        
    } while (temp && temp != NULL_STRING && *temp);
   }
   return (GETCURRENTHIGHESTSEVERITY ());
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/TradeLevelOverrideRules.cpp-arc  $*/
// Rev 1.0   26-May-2014  Robbins
// Initial revision.
