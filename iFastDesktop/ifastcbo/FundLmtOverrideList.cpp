//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by Internation Financial Data Services
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2003 by Internation Financial Data Services
//
//
//******************************************************************************
//
// ^FILE   : FundLmtOverrideList.cpp
// ^AUTHOR : Winnie Shiu
// ^DATE   : January 09, 2003
//
// ^CLASS    : FundLmtOverrideList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "FundLmtOverride.hpp"
#include "FundLmtOverrideList.hpp"
#include "MFAccount.hpp"
#include "Shareholder.hpp"
#include <ifastdataimpl\dse_dstc0236_req.hpp>
#include <ifastdataimpl\dse_dstc0236_vw.hpp>

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest FUNDLMTOVERRIDELIST;
}

namespace
{
   //Trace literals
   const I_CHAR * const CLASSNAME             = I_ ("FundLmtOverrideList");
   const I_CHAR * const FUND_CODE_FIELD       = I_ ("FundCode");
   const I_CHAR * const CLASS_CODE_FIELD      = I_ ("ClassCode");
   const I_CHAR * const NO                    = I_ ("N");
   const I_CHAR * const YES                   = I_ ("Y");
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId OverrideExists;
   extern CLASS_IMPORT const BFNumericFieldId ShrNum;
}

namespace CND
{
}

namespace RULE_TYPE
{

   /***** Possible Limitmation Code (misc-info group code 'FY')
   Code   Description
   ----------------------------------
   01     Min. Init. Purchase
   02     Min. Subseq. Purchase
   03     Stop Purchase
   04     Stop Redemption
   05     Stop Transfer In
   06     Stop Transfer Out
   07     P.A.C. Minimum
   08     Stop P.A.C.
   09     Stop S.W.P.
   10     Stop Auto Transfer In
   11     Stop Auto Transfer Out
   15     Min. Units Purchase
   20     Broker Elig. Override-Redemption/Transfer Out
   21     Broker Elig. Override-Trf In Kind
   38	  Rollover Ignore acct stop Transfer In
   39	  Rollover Ignore acct stop Transfer Out
   *******/
   extern const I_CHAR * const MIN_INIT_PUR_AMT    = I_("01");  
   extern const I_CHAR * const MIN_SUB_SEQ_PUR     = I_("02");  
   extern const I_CHAR * const STOP_PUR            = I_("03");  
   extern const I_CHAR * const STOP_RED            = I_("04");  
   extern const I_CHAR * const STOP_TRFER_IN       = I_("05");  
   extern const I_CHAR * const STOP_TRFER_OUT      = I_("06");  
   extern const I_CHAR * const PAC_MIN_AMT         = I_("07");  
   extern const I_CHAR * const STOP_PAC            = I_("08");  
   extern const I_CHAR * const STOP_SWP            = I_("09");  
   extern const I_CHAR * const STOP_ATI            = I_("10");  
   extern const I_CHAR * const STOP_ATO            = I_("11");  
   extern const I_CHAR * const MIN_UNIT_PUR        = I_("15");  
   extern const I_CHAR * const BRK_TRFIN_KIND      = I_("21");
   extern const I_CHAR * const BRK_PW_TRFOUT       = I_("23");
   extern const I_CHAR * const STOP_AMT_TRADE      = I_("36");
   extern const I_CHAR * const BANKRUPTCY          = I_("43");
   extern const I_CHAR * const SKIP_ACCT_STOP_FOR_ROLLOVER_EXCHANGE_IN  = I_("38");
   extern const I_CHAR * const SKIP_ACCT_STOP_FOR_ROLLOVER_EXCHANGE_OUT = I_("39");
}

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = 
{
//  Field DD Id,           State Flags,    Group Flags 
   {ifds::OverrideExists, BFCBO::NONE, 0},
};

static const int NUM_FIELDS = sizeof (classFieldInfo) / sizeof (BFCBO::CLASS_FIELD_INFO);


//******************************************************************************
FundLmtOverrideList::FundLmtOverrideList (BFAbstractCBO &parent) :
 MFCanBFCbo (parent)
{
   TRACE_CONSTRUCTOR (CLASSNAME , NULL_STRING);
   setObjectAsList ();
   registerMemberData (NUM_FIELDS,
                       (const CLASS_FIELD_INFO *)&classFieldInfo,
                       0,
                       NULL);

}

//******************************************************************************
FundLmtOverrideList::~FundLmtOverrideList()
{
   TRACE_DESTRUCTOR (CLASSNAME);
}


//******************************************************************************
SEVERITY FundLmtOverrideList::init ( const DString &dstrFundCode, 
                                     const DString &dstrClassCode, 
                                     const DString &dstrTransType, 
                                     const DString &dstrTrack,
                                     const DString &dstrPageName)

{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_ ("init"));

   BFData queryData (ifds::DSTC0236_REQ);
   BFData *receivedData = new BFData (ifds::DSTC0236_VW);

   DString mgmtCoIdOut;
   queryData.setElementValue (ifds::CompanyId, getMgmtCoId (mgmtCoIdOut));
   queryData.setElementValue (ifds::Track, dstrTrack);
   queryData.setElementValue (ifds::Activity, dstrPageName);
   queryData.setElementValue (ifds::FundCode, dstrFundCode);
   queryData.setElementValue (ifds::ClassCode, dstrClassCode);
   queryData.setElementValue (ifds::TransType, dstrTransType);

   setFieldNoValidate (ifds::OverrideExists, NO, BF::HOST, false);
   if (ReceiveData ( DSTC_REQUEST::FUNDLMTOVERRIDELIST, 
                     queryData, 
                     *receivedData, 
                     DSTCRequestor (getSecurity())) <= WARNING
      )
   {
      DString numOfRecords;
      
      receivedData->getElementValue (ifds::RepeatCount, numOfRecords);

      double dec_counter = DSTCommonFunctions::convertToDouble (numOfRecords);

// No object in the list indicates there is no override --> use the FundDetail level set up
      if (dec_counter > 0)
      {
         setFieldNoValidate (ifds::OverrideExists, YES, BF::HOST, false);
      }
   }
   return GETCURRENTHIGHESTSEVERITY();
}


//******************************************************************************
SEVERITY FundLmtOverrideList::doCreateObject (const BFData& data, BFCBO *&pObjOut)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_ ("doCreateObject"));

   FundLmtOverride * pFundLmtOverride = new FundLmtOverride (*this);
   pFundLmtOverride->init (data);
   pObjOut = pFundLmtOverride;
   return GETCURRENTHIGHESTSEVERITY();
}


//*****************************************************************************
SEVERITY FundLmtOverrideList::getFundLmtOverride ( const DSTCWorkSession &workSession,
                                                   const DString &accountNum,
                                                   const DString &limitationCode,
                                                   FundLmtOverride *&pFundLmtOverride,
                                                   const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("getFundLmtOverride"));
   pFundLmtOverride = NULL;
   MFAccount *pMFAccount = NULL;
   DSTCWorkSession *pDSTCWorkSession = const_cast <DSTCWorkSession *>(&workSession);
   
   if ( pDSTCWorkSession->getMFAccount ( idDataGroup, 
                                         accountNum, 
                                         pMFAccount) <= WARNING && 
        pMFAccount)
   {
      DString taxJuris, 
         resProvCode, 
         taxType, 
         acctType, 
         acctDesignation, 
         shrNum;
   
      pMFAccount->getField (ifds::TaxType, taxType, idDataGroup, false);
      pMFAccount->getField (ifds::AcctType, acctType, idDataGroup, false);
      pMFAccount->getField (ifds::AcctDesignation, acctDesignation, idDataGroup, false);
      pMFAccount->getField (ifds::ShrNum, shrNum, idDataGroup, false);

      Shareholder* pShareholder = NULL;
      
      if ( pDSTCWorkSession->getShareholder ( idDataGroup, 
                                              shrNum, 
                                              pShareholder) <= WARNING &&
           pShareholder)
      {
         pShareholder->getField (ifds::TaxJurisCode, taxJuris, idDataGroup);
         pShareholder->getField (ifds::ResProvCode, resProvCode, idDataGroup);
         taxType.strip().upperCase();
         acctType.strip().upperCase();
         acctDesignation.strip().upperCase();
         taxJuris.strip().upperCase();
         resProvCode.strip().upperCase();

         BFObjIter iter (*this, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED);

         while (!iter.end()) 
         {
            DString _taxJuris, 
               _resProvCode, 
               _taxType, 
               _acctType, 
               _acctDesignation, 
               _ruleType;

            iter.getObject()->getField (ifds::RuleType, _ruleType, idDataGroup, false);
            iter.getObject()->getField (ifds::TaxType, _taxType, idDataGroup, false);
            iter.getObject()->getField (ifds::AcctType, _acctType, idDataGroup, false);
            iter.getObject()->getField (ifds::AcctDesignation, _acctDesignation, idDataGroup, false);
            iter.getObject()->getField (ifds::TaxJurisCode, _taxJuris, idDataGroup, false);
            iter.getObject()->getField (ifds::ResProvCode, _resProvCode, idDataGroup, false);
            _taxType.strip().upperCase();
            _acctType.strip().upperCase();
            _acctDesignation.strip().upperCase();
            _taxJuris.strip().upperCase();
            _resProvCode.strip().upperCase();
// find the corresponding record by matching the rule type with the limitation code
            if ( isCodeInList (limitationCode, _ruleType) &&  
            //if ( DSTCommonFunctions::codeInList(_ruleType,limitationCode) &&
                 isCodeInList (taxType, _taxType) && 
                 isCodeInList (acctType, _acctType) && 
                 isCodeInList (acctDesignation, _acctDesignation) && 
                 isCodeInList (taxJuris, _taxJuris) && 
                 isCodeInList (resProvCode, _resProvCode))
            {
               pFundLmtOverride = 
                     dynamic_cast<FundLmtOverride*> (iter.getObject());  
               break;
            }
            ++iter;
         }
      }
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//*****************************************************************************
SEVERITY FundLmtOverrideList::getFundLevelFundLmtOverride ( const DSTCWorkSession &workSession,
                                                            const DString &limitationCode,
                                                            FundLmtOverride *&pFundLmtOverride,
                                                            const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("getFundLmtOverride"));
   pFundLmtOverride = NULL;
   MFAccount *pMFAccount = NULL;
   DSTCWorkSession *pDSTCWorkSession = const_cast <DSTCWorkSession *>(&workSession);
   
   BFObjIter iter (*this, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED);

   while (!iter.end()) 
   {
      DString _taxJuris, _resProvCode, _taxType, _acctType, _acctDesignation, _ruleType;

      iter.getObject()->getField (ifds::RuleType, _ruleType, idDataGroup, false);
      iter.getObject()->getField (ifds::TaxType, _taxType, idDataGroup, false);
      iter.getObject()->getField (ifds::AcctType, _acctType, idDataGroup, false);
      iter.getObject()->getField (ifds::AcctDesignation, _acctDesignation, idDataGroup, false);
      iter.getObject()->getField (ifds::TaxJurisCode, _taxJuris, idDataGroup, false);
      iter.getObject()->getField (ifds::ResProvCode, _resProvCode, idDataGroup, false);
      _taxType.strip().upperCase();
      _acctType.strip().upperCase();
      _acctDesignation.strip().upperCase();
      _taxJuris.strip().upperCase();
      _resProvCode.strip().upperCase();
// find the corresponding record by matching the rule type with the limitation code
      if ( isCodeInList (limitationCode, _ruleType) &&  
           isCodeInList (I_("*"), _taxType) && 
           isCodeInList (I_("*"), _acctType) && 
           isCodeInList (I_("*"), _acctDesignation) && 
           isCodeInList (I_("*"), _taxJuris) && 
           isCodeInList (I_("*"), _resProvCode))
      {
         pFundLmtOverride = dynamic_cast<FundLmtOverride*> (iter.getObject());  
         break;
      }
      ++iter;
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/FundLmtOverrideList.cpp-arc  $
// 
//    Rev 1.17   Jan 16 2012 16:22:50   dchatcha
// IN# 2796443 - Validation rule for Allocated Auto Transfer, back-end take stop flag to be considered.
// 
//    Rev 1.16   Dec 26 2011 21:04:24   dchatcha
// IN# 2783697 - Description changes for table 0999 and Escrow
// 
//    Rev 1.15   Jul 20 2011 15:25:10   wp040027
// PET P0186065 - Aggregated Amount Orders via Swift- Implementation of Rule 36 on Fund
// 
//    Rev 1.14   24 Jul 2007 20:12:58   popescu
// GAP 20 -22 AIM
// 
//    Rev 1.13   Nov 14 2004 14:42:42   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.12   Nov 04 2004 17:37:38   popescu
// PET 1117/06, Trade processing
// 
//    Rev 1.11   Jun 25 2004 19:05:02   popescu
// PTS 10031525, Fund limitation overrides issue
// 
//    Rev 1.10   Jun 25 2004 16:38:20   popescu
// PST 10031525, fund limitation override issues
// 
//    Rev 1.9   Nov 26 2003 10:52:20   linmay
// added isCodeInList().. for PTS#10024397
// 
//    Rev 1.8   Aug 21 2003 09:10:18   HSUCHIN
// fixed bug in comparison in method getFundLmtOverride
// 
//    Rev 1.7   Apr 12 2003 13:46:14   FENGYONG
// small change
// 
//    Rev 1.6   Apr 11 2003 10:10:52   FENGYONG
// check init minimum amount for purchase
// 
//    Rev 1.5   Mar 21 2003 18:11:50   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.4   Mar 08 2003 12:46:48   WINNIE
// Bug fix : Need new parameter LimitationCode to locate the corresponding record. Existing logic stop as soon as the first record is found even though the record is for different purposes
// 
//    Rev 1.3   Jan 30 2003 19:04:56   WINNIE
// Call by reference for input parameters of getStopFlag, override and minimum amount 
// 
//    Rev 1.2   Jan 29 2003 15:07:00   WINNIE
// Bug fix for override logic : repeatcount not working; should not override the input parameter value if override not found; 
// 
//    Rev 1.1   Jan 21 2003 18:29:08   WINNIE
// add method getMinAmountFlag for systematic min amount edit check
// 
//    Rev 1.0   Jan 12 2003 16:05:34   WINNIE
// Initial revision.
// 
*/