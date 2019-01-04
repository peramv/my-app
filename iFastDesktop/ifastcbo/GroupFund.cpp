//*****************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by DST Systems, Inc.,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2000 by DST Systems, Inc.
//
//*****************************************************************************
//
//    ^FILE   : GroupFund.cpp
//    ^AUTHOR : 
//    Copyright 2000 by DST Canada, Inc.
//
//-----------------------------------------------------------------------------
//
// ^CLASS  : GroupFund
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS :
//
//*****************************************************************************
#include "stdafx.h"
#include "groupfund.hpp"
#include "funddetaillist.hpp"
#include "funddetail.hpp"
#include "fundmasterlist.hpp"
#include "groupfund.hpp"
#include "groupfundlist.hpp"
#include "mgmtco.hpp"
#include <ifastdataimpl\dse_dstc0056_vwrepeat_record.hpp>

namespace 
{
   const I_CHAR *  CLASSNAME = I_( "GroupFund" );

   const I_CHAR * const PURCHASE_CODE              = I_( "ED" );     // trade trans type Purchase
   const I_CHAR * const REDEMPTION_CODE            = I_( "PW" );     // trade trans type Redemption
   const I_CHAR * const EXCHANGE_TRANSFER_CODE     = I_( "TR" );     // trade trans type Transfer 
   const I_CHAR * const EX_FER_IN_CODE             = I_( "XFIN" );   // trade trans type Exchange In 
   const I_CHAR * const EX_FER_OUT_CODE            = I_( "XFOUT" );  // trade trans type Exchange Out
   const I_CHAR * const PAC_CODE                   = I_( "P" );      
   const I_CHAR * const SWP_CODE                   = I_( "S" ); 

   const I_CHAR * const TRADE_TYPE                 = I_( "TRADE_TYPE") ;
   const I_CHAR * const PURCHASE                   = I_( "Purchase" );     // trade trans type description
   const I_CHAR * const REDEMPTION                 = I_( "Redemption" );  // trade trans type description
   const I_CHAR * const EXCHANGE_IN                = I_( "Exchange In" );  // trade trans type description
   const I_CHAR * const EXCHANGE_OUT               = I_( "Exchange Out" ); // trade trans type description

   const I_CHAR * const FRPURCHASE                   = I_( "Souscription" );     // trade trans type description
   const I_CHAR * const FRREDEMPTION                 = I_( "rachat" );  // trade trans type description
   const I_CHAR * const FREXCHANGE_IN                = I_( "échanges" );  // trade trans type description
   const I_CHAR * const FREXCHANGE_OUT               = I_( "échanges sortants" ); // trade trans type description

   const I_CHAR * const NO                         = I_( "N" );
   const I_CHAR * const YES                        = I_( "Y" );

   const I_CHAR * const FUND                       = I_( "FUND" );
   const I_CHAR * const CLASS                      = I_( "CLASS" );

   const I_CHAR * const FUNDNAME1                  = I_( "FUNDNAME" );
   const I_CHAR * const CLASSNAME1                 = I_( "CLASSNAME" );

}

namespace CND
{  // Conditions used
   extern const long ERR_FUND_CLASS_STOP_FLAG_ON;
   extern const long ERR_FUND_CLASS_NOT_EFFECTIVE;
   extern const long ERR_FUND_NOT_EFFECTIVE;

}

namespace ifds
{
   extern CLASS_IMPORT const BFDateFieldId DetlEffectiveDate;
};

//******************************************************************************
GroupFund::GroupFund( BFAbstractCBO &parent ) 
: MFCanBFCbo( parent )
, m_pFundDetail( NULL )
, m_pFundMaster( NULL )
{
   TRACE_CONSTRUCTOR( CLASSNAME , NULL_STRING );
}

//******************************************************************************

GroupFund::~GroupFund()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************

SEVERITY GroupFund::init( const BFData &viewData )
{
   MAKEFRAME2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("init") );

   attachDataObject( const_cast<BFData&>( viewData ), false, true );

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
void GroupFund::getField( const BFFieldId& idField,
                          DString& strValue,
                          const BFDataGroupId& idDataGroup, 
                          bool formattedReturn ) const 
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getField" ));

   DString tmp;
   BFFieldId transFieldId = idField;

   if( idField == ifds::DetlEffectiveDate )
   {
      transFieldId = ifds::EffectiveDate;
   };

   if( idField == ifds::DetlEffectiveDate ||
       idField == ifds::StopDate     ||
       idField == ifds::StopPurchase ||
       idField == ifds::StopRed      ||
       idField == ifds::StopXferIn   ||
       idField == ifds::StopXferOut  ||
       idField == ifds::ESoPEligible ||       
       idField == ifds::MgtFeeElig   ||
       idField == ifds::MgtFeeRbtElig 
     )
   {
      if( !m_pFundDetail || !m_pFundMaster )
      {
         const_cast < GroupFund * >(this)->storeFundDetailPtr( idDataGroup );
      };
      if( m_pFundDetail )
         m_pFundDetail->getField( transFieldId, strValue, idDataGroup, formattedReturn );

      if( idField == ifds::StopDate && m_pFundMaster )
      {
         m_pFundMaster->getField( transFieldId, tmp, idDataGroup, formattedReturn );

         if( DSTCommonFunctions::CompareDates( tmp, strValue ) 
             == DSTCommonFunctions::FIRST_EARLIER )
            strValue = tmp;
      }
   }
   else
      BFCBO::getField( idField, strValue, idDataGroup,  formattedReturn );

}

//******************************************************************************
void GroupFund::storeFundDetailPtr( const BFDataGroupId& idDataGroup ) 
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "storeFundDetailPtr" ));

   DString dstFundCode  = NULL_STRING;
   DString dstClassCode = NULL_STRING;
   DString dstKey       = NULL_STRING;
   getField( ifds::FundCode,  dstFundCode,  idDataGroup );
   getField( ifds::ClassCode, dstClassCode, idDataGroup );

   FundDetailList * pFundDetailList = NULL;
   FundMasterList * pFundMasterList = NULL;
   GroupFundList  * pGroupFundList   = NULL;
   MgmtCo         * pMgmtCo          = NULL;

   if( pGroupFundList = dynamic_cast< GroupFundList * >( getParent() ) )
   {
      if( pMgmtCo = dynamic_cast < MgmtCo * > ( getParent()->getParent()->getParent()->getParent() ) )
      {
         pMgmtCo->getFundDetailList( pFundDetailList );
         pMgmtCo->getFundMasterList( pFundMasterList );
      }
   };

   if( pFundDetailList )
   {
      FundDetail *pFundDetail = NULL;
      if( pFundDetailList->getFundDetail( dstFundCode, dstClassCode, BF::HOST, pFundDetail ) )
      {
         m_pFundDetail = pFundDetail;
      }
   };
   if( pFundMasterList )
   {
      BFObjIter iter( *pFundMasterList, idDataGroup );
      pFundMasterList->buildKey( dstFundCode, dstKey );
      iter.setKeyFilter( dstKey );
      if( ! iter.end() )
         m_pFundMaster = dynamic_cast< BFCBO* >( iter.getObject() );
   };

}

//******************************************************************************
SEVERITY GroupFund::validateFndClsTradeType( const DString dstrTradeDate, const BFDataGroupId& idDataGroup ) 
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateFndClsTradeType" ) );

   DString idiStr, strKey;
   DString fundCode, classCode;

   getField(ifds::FundCode, fundCode, BF::HOST, false );
   getField(ifds::ClassCode, classCode, BF::HOST, false );

   DString dstrFundDetailEffDate, dstrGroupFundEffDate, dstrStopDate;
   // Check if the trade date falls between the effective date and stopdate
   getField(ifds::DetlEffectiveDate, dstrFundDetailEffDate, BF::HOST, false );
   getField(ifds::StopDate,          dstrStopDate, BF::HOST, false );
   getField(ifds::EffectiveDate,     dstrGroupFundEffDate, BF::HOST, false );

   DString idiStr1;
   addIDITagValue( idiStr1, FUNDNAME1, fundCode );
   addIDITagValue( idiStr1, CLASSNAME1, classCode );

   FundMasterList* pFundMasterList = NULL;
   if( getMgmtCo().getFundMasterList(pFundMasterList) <= WARNING && pFundMasterList )
   {
      if( !(pFundMasterList->IsFundValidAtDate(fundCode,dstrTradeDate,idDataGroup) ) )
      {
         DString msg( I_( "FUNDNAME=" ) );
         msg += fundCode;
         ADDCONDITIONFROMFILEIDI( CND::ERR_FUND_NOT_EFFECTIVE, msg.c_str() );
         //if fund is not effective, no need to check if fund/class is effective
         return(GETCURRENTHIGHESTSEVERITY());  
      }
   }

   // check if fund detail effective as of trade date
   if( !DSTCommonFunctions::IsDateBetween( dstrFundDetailEffDate.strip(),
                                           dstrStopDate.strip(), dstrTradeDate ) )
   {
      ADDCONDITIONFROMFILEIDI( CND::ERR_FUND_CLASS_NOT_EFFECTIVE, idiStr1 );
      return(GETCURRENTHIGHESTSEVERITY());  
   }
   // check if group fund is effective as of trade date
   else if( DSTCommonFunctions::CompareDates( dstrTradeDate, dstrGroupFundEffDate ) 
            == DSTCommonFunctions::FIRST_EARLIER )
   {
      ADDCONDITIONFROMFILEIDI( CND::ERR_FUND_CLASS_NOT_EFFECTIVE, idiStr1 );
   }

   return(GETCURRENTHIGHESTSEVERITY());  
}



//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/GroupFund.cpp-arc  $
 // 
 //    Rev 1.29   Dec 09 2004 15:07:32   purdyech
 // PET910 - Fixed an access violation in getField() due to non-initialization of m_pFundMaster
 // 
 //    Rev 1.28   Nov 29 2004 13:25:02   hernando
 // PET1117 - Tuning Project - Revised use of FundDetailList.
 // 
 //    Rev 1.27   Nov 14 2004 14:43:32   purdyech
 // PET910 - .NET Conversion
 // 
 //    Rev 1.26   Mar 21 2003 18:12:36   PURDYECH
 // BFDataGroupId/BFContainerId changeover
 // 
 //    Rev 1.25   Feb 27 2003 19:09:48   WINNIE
 // 10013834 : no need to check if fund/class or fund/class/group is effective if the fund itself is not even effective
 // 
 //    Rev 1.24   Oct 09 2002 23:54:34   PURDYECH
 // PVCS Database Conversion
 // 
 //    Rev 1.23   Aug 29 2002 12:55:58   SMITHDAV
 // ClientLocale and typed field changes.
 // 
 //    Rev 1.22   Jul 29 2002 16:26:04   WINNIE
 // Fix bug for date checking
 // 
 //    Rev 1.21   Jul 26 2002 15:01:04   KOVACSRO
 // Checking the fund if it is effective.
 // 
 //    Rev 1.20   22 May 2002 18:28:48   PURDYECH
 // BFData Implementation
 // 
 //    Rev 1.19   Feb 28 2002 16:14:34   PURDYECH
 // Fixed up a bad dynamic_cast or two.
 // 
 //    Rev 1.18   25 Feb 2002 20:13:50   PURDYECH
 // BFData Implementation Quick Fixes
 // 
 //    Rev 1.17   25 Feb 2002 12:24:18   WINNIE
 // remove stop flag checking logic; Purchase, Redemption  and Transfer will call the method directly in FundDetail
 // 
 //    Rev 1.15   Nov 29 2001 16:23:48   ZHANGCEL
 // Fixed problem those are caused due to moving GroupFundList to Group CBO
 // 
 //    Rev 1.14   Oct 17 2001 15:04:20   FENGYONG
 // Add french con parm
 // 
 //    Rev 1.13   14 Aug 2001 15:18:24   KOVACSRO
 // Added ESoPEligible.
 // 
 //    Rev 1.12   03 May 2001 14:06:38   SMITHDAV
 // Session management restructuring.
 // 
 //    Rev 1.11   Feb 13 2001 17:14:58   FENGYONG
 // compare tradedate to both fundmasterlist and funddetailslist and change && to || when validateFndClsTradeType
 // 
 //    Rev 1.10   Dec 20 2000 16:12:36   WINNIE
 // Give proper error message
 // 
 //    Rev 1.9   Dec 17 2000 20:23:34   OLTEANCR
 // changed to use a precompiled header
 // 
 //    Rev 1.8   Sep 01 2000 14:35:40   ZHANGCEL
 // Add the ClientLocale parameter in getField() 
 // 
 //    Rev 1.7   Aug 09 2000 14:14:30   HUANGSHA
 // fix for checking the redemption stop flag
 // 
 //    Rev 1.6   Jun 29 2000 15:41:10   WINNIE
 // Sychronize changes in the branch. Branch should be deleted
 // 
 //    Rev 1.5.1.0   Jun 19 2000 11:02:28   BUZILA
 // cond fix
 // 
 //    Rev 1.5   Jun 01 2000 14:41:54   WINNIE
 // Fix error message to display fund and class code
 // 
 //    Rev 1.4   May 04 2000 14:09:10   BUZILA
 // changed tha way FunDetails is found. Now we are using getParent mechanism
 // 
 //    Rev 1.3   May 03 2000 13:36:12   HSUCHIN
 // added baycom to getfield
 // 
 //    Rev 1.2   Apr 15 2000 15:28:26   WINNIE
 // fix for index set up in funtolist; fix allowable exchange edit chk; fix account balance ;
 // 
 //    Rev 1.1   Apr 14 2000 17:55:40   WINNIE
 // Move validation to Groupfund and MFAccount CBO to allow other CBO to use the same method. Bug fix for NumOfDecimals function
 // 
 //    Rev 1.0   Apr 13 2000 10:33:38   BUZILA
 // Initial revision.
 * 
*/