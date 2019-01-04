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
//    Copyright 1999 by DST Canada Inc.
//
//
//******************************************************************************
//
// ^FILE   : AccountDistributionList.cpp
// ^AUTHOR : Zijian Ying + Yingbao (M2)
// ^DATE   : 04/22/99
//
// ^CLASS    : AccountDistributionList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "accountdistribution.hpp"
#include "accountdistributionlist.hpp"
#include "accountmailinginfo.hpp"
#include "accountmailinglist.hpp"
#include <ifastdataimpl\dse_dstc0016_req.hpp>
#include <ifastdataimpl\dse_dstc0016_vw.hpp>
#include "funddetaillist.hpp"
#include "fundmasterlist.hpp"
#include "mgmtco.hpp"
#include "mgmtcooptions.hpp"
#include "shareholder.hpp"
#include "dstcworksession.hpp"

namespace
{
   //Trace literals
   const I_CHAR * const CLASSNAME         = I_( "AccountDistributionList" );  
   const I_CHAR * const CASH              = I_( "CASH" );  //cash
   const I_CHAR * const EFT_PAY_TYPE      = I_( "E" );  //EFT to Account
   const I_CHAR * const A                 = I_( "A" );
   const I_CHAR * const IDI_TAG           = I_( "TAG" );
   const I_CHAR * const MFR               = I_( "MR" );
   const I_CHAR * const DISTRIB_LEVEL     = I_("02");
   const I_CHAR * const DISTRIB_CATEGORY  = I_("2");
   const I_CHAR * const INCOME_DISTRIB    = I_("ID");
   const I_CHAR * const UNVERIFIED        = I_("02");
   const I_CHAR * const VERIFIED          = I_("01");
}

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest ACC_DISTRIB;
}

namespace CND
{  // Conditions used
   extern const long ERR_ENTRY_EMPTY_OR_CONTAINS_ONLY_SPACE;
   extern const long ERR_INVALID_CHAR;
   extern const long ERR_ENTRY_BOTH_FIELDS;
   extern const long ERR_EFFECTIVE_DATE_LATE_THAN_STOP_DATE;
   extern const long ERR_INSTCODE_NOT_EXIST;
   extern const long ERR_ACCT_FUND_CLASS_NOT_UNIQUE;
   extern const long ERR_PERCENTAGE_NOT_EQUAL_100;
   extern CLASS_IMPORT const long ERR_DATA_NOT_FOUND;
   extern const long ERR_SUM_OF_PERCENTAGES_NOT_100;
   extern const long ERR_FIELD_REQUIRED;
   extern const long ERR_FIELD_REQUIRED_PLS_ENTER;
   extern const long ERR_INCOMPLETE_FROM_FUND_INFORMATION;
   extern const long ERR_INCOMPLETE_TO_INFORMATION;
   extern const long ERR_DISTRIB_MIX_NOT_ALLOWED;
   extern const long ERR_UNVERIFIED_DELETED_BEING_DUPLICATE;
   extern const long ERR_SUM_OF_DISTRIBUTION_RATES_NOT_RECENT_DISTRIBUTION;  
   extern const long WARN_SUM_OF_DISTRIBUTION_RATES_NOT_RECENT_DISTRIBUTION;  

}

namespace ifds
{  // Conditions used
   extern CLASS_IMPORT const BFTextFieldId DivChqAddr;
   extern CLASS_IMPORT const BFTextFieldId DistribGBCD;
   extern CLASS_IMPORT const BFTextFieldId DelDistribAlloc;
   extern CLASS_IMPORT const BFTextFieldId DistribInstrAsRatioOpt;
   extern CLASS_IMPORT const BFDecimalFieldId LastIDRate;
   extern CLASS_IMPORT const BFDecimalFieldId TotalDistribRate;
   extern CLASS_IMPORT const BFTextFieldId DistribInputMethod;
   extern CLASS_IMPORT const BFDecimalFieldId TotalAllocPercent;
   extern CLASS_IMPORT const BFTextFieldId ToSoftCapCheck;
}

namespace IFASTERR
{
   extern CLASS_IMPORT I_CHAR * const SUM_OF_DISTRIBUTION_RATES_NOT_RECENT_DISTRIBUTION;      
}

//******************************************************************************

AccountDistributionList::AccountDistributionList( BFAbstractCBO &parent ) 
: MFCanBFCbo( parent ),
_level( UNDEFINED_LEVEL ),
_requestData0016(ifds::DSTC0016_REQ),
_pResponseData0016(NULL),
isDistributionBankList( false )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   setObjectAsList();
}

//******************************************************************************

AccountDistributionList::~AccountDistributionList( void )
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************

SEVERITY AccountDistributionList::init( bool bRetrieveFromHost, 
                                        const BFDataGroupId& idDataGroup,
                                        const DString& dstrAccountNum,
                                        const DString& dstrShareholderNum,
                                        DISTRIBUTION_LEVEL level,
                                        BFData *distributionData,
                                        const DString& dstrFundCode, 
                                        const DString& dstrClassCode,
                                        const DString& dstrEffectiveDate,
                                        const DString& dstrTransType,
                                        const DString& dstrTrack,
                                        const DString& dstrPageName )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );


   assert( !bRetrieveFromHost || level == ACCOUNT_LEVEL );

   _level = level;
   _dstrAccountNum = dstrAccountNum;
   _dstrShareholderNum = dstrShareholderNum;

   if( _level == ACCOUNT_LEVEL )
   {
      assert( !distributionData );
      if( bRetrieveFromHost )
      {
         assert( idDataGroup == BF::HOST );

         //BFData requestData(ifds::DSTC0016_REQ);
         //BFData *responseData = new BFData(ifds::DSTC0016_VW);

         _pResponseData0016 = new BFData(ifds::DSTC0016_VW);

         DString mgmtCoIdOut;
         //requestData.setElementValue( ifds::CompanyId, getMgmtCoId( mgmtCoIdOut ) );
         //requestData.setElementValue( ifds::Track, dstrTrack );
         //requestData.setElementValue( ifds::Activity, dstrPageName );
         //requestData.setElementValue( ifds::AccountNum, _dstrAccountNum ); 

         _requestData0016.setElementValue( ifds::CompanyId, getMgmtCoId( mgmtCoIdOut ) );
         _requestData0016.setElementValue( ifds::Track, dstrTrack );
         _requestData0016.setElementValue( ifds::Activity, dstrPageName );
         _requestData0016.setElementValue( ifds::AccountNum, _dstrAccountNum ); 


         SEVERITY sevRtn = 
         BFDataBroker::getInstance( )->receive( DSTC_REQUEST::ACC_DISTRIB, 
                                                                  _requestData0016, 
                                                                  *_pResponseData0016, 
                                                   DSTCRequestor(getSecurity(), false),
                                                &_moreRecordsAvailable );

         if( sevRtn > WARNING )
         {
            delete _pResponseData0016;
            _pResponseData0016 = NULL;
            return(sevRtn);
         }

         distributionData = _pResponseData0016;
      }
   }

   initDistributionData( distributionData,
                         idDataGroup,
                         _dstrAccountNum,
                         _dstrShareholderNum,
                         dstrFundCode, 
                         dstrClassCode,
                         dstrEffectiveDate,
                         dstrTransType,
                         dstrTrack,
                         dstrPageName );

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************

void AccountDistributionList::getStrKey( DString &strKey, const BFData *data )
{
   TRACE_METHOD( CLASSNAME, I_( "getStrKey" ) );

   bool bVerificationEnabled = false;
   getWorkSession ().isVerificationEnabled ( BF::HOST, 
                                             DISTRIB_CATEGORY, 
                                             DISTRIB_LEVEL, 
                                             bVerificationEnabled);

   if( !data ) // is asking for cash key for banking
   {
      strKey = I_("CASH A");
      return;
   }

   if( _level == ACCOUNT_LEVEL )
   {
      DString dstrFund, dstrClass, dstrTransType, dstrEffDate;
      data->getElementValue( ifds::FundCode, dstrFund );
      data->getElementValue( ifds::ClassCode, dstrClass );
      data->getElementValue( ifds::TransType, dstrTransType );
      data->getElementValue( ifds::EffectiveDate, dstrEffDate );
      dstrFund.strip().upperCase();
      dstrClass.strip().upperCase();
      dstrTransType.strip().upperCase();
      dstrEffDate.strip();

      strKey = dstrTransType + I_( " " ) + 
               dstrFund      + I_( " " ) + 
               dstrClass     + I_( " " ) + 
               dstrEffDate;

      if ( bVerificationEnabled )
      {
         DString strVerifyStatus, strDistribGBCD;
         data->getElementValue( ifds::VerifyStat, strVerifyStatus );
         data->getElementValue( ifds::DistribGBCD, strDistribGBCD );
         strVerifyStatus.strip().upperCase();
         strDistribGBCD.strip().upperCase();

         strKey += I_(" ");
         strKey += strDistribGBCD;
      }
   }
   else if( _level == FUND_CLASS_LEVEL )
   {
      DString dstrFundTo, dstrClassTo;

      data->getElementValue( ifds::FundToCode, dstrFundTo );
      data->getElementValue( ifds::ClassToCode, dstrClassTo );

      dstrFundTo.strip().upperCase();
      dstrClassTo.strip().upperCase();
      strKey = dstrFundTo + I_( " " ) + dstrClassTo;

      if ( bVerificationEnabled )
      {
         DString dstrDistribGBCD;
         data->getElementValue( ifds::DistribGBCD, dstrDistribGBCD );
         strKey = strKey + I_( " " ) + dstrDistribGBCD;
      }
   }
   else
   {
      assert( 0 );
   }
}

//******************************************************************************
SEVERITY AccountDistributionList::doCreateObject( const BFData& data, 
                                                  BFCBO *&pObjOut )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateObject" ) );

   assert( 0 );//should not be called with the current design of init function

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY AccountDistributionList::doCreateNewObject( BFCBO *&pBase, 
                                                     DString &dstrKey, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateNewObject" ) );

   AccountDistribution *pAcctDist = new AccountDistribution( *this );
   setFundMastDetailList(pAcctDist);

   bool bVerificationEnabled = false;
   getWorkSession ().isVerificationEnabled ( idDataGroup, 
                                             DISTRIB_CATEGORY, 
                                             DISTRIB_LEVEL, 
                                             bVerificationEnabled);

   // if system has verification functionality, for each new distrib record
   // it's new object flag (NOT_ON_HOST) must be set before calling init method
   // otherwise some initialization logic might be failed
   if ( bVerificationEnabled )
   {
      pAcctDist->setObjectNew();
   }

   pAcctDist->init( idDataGroup, _dstrAccountNum, _dstrShareholderNum, _level );

   pBase = pAcctDist;

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY AccountDistributionList::doValidateAll( const BFDataGroupId& idDataGroup, long lValidateGroup )
{ 
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doValidateAll" ) );

   short nLevelEntries = 0;

   std::set< DString > setCharacteristic;
   BFObjIter iter1( *this, idDataGroup, false, 
                    BFObjIter::ITERTYPE::NON_DELETED );

   bool bVerificationEnabled = false;
   getWorkSession ().isVerificationEnabled ( idDataGroup, 
                                             DISTRIB_CATEGORY, 
                                             DISTRIB_LEVEL, 
                                             bVerificationEnabled);

   if( iter1.end() || iter1.isDummy() )
      return(GETCURRENTHIGHESTSEVERITY());

   while( !iter1.end() )
   {
      if( _level == ACCOUNT_LEVEL )
      {
         DString dstrFundCode, dstrClassCode, dstrTransType;
         iter1.getObject()->getField( ifds::FundCode, dstrFundCode, 
                                      idDataGroup );
         dstrFundCode.strip().upperCase();     
         iter1.getObject()->getField( ifds::ClassCode, dstrClassCode, 
                                      idDataGroup );
         dstrClassCode.strip().upperCase();

         iter1.getObject()->getField( ifds::TransType, dstrTransType, idDataGroup );

         DString dstr = dstrFundCode + I_(" ") + dstrClassCode + I_(" ") + dstrTransType;

         // for static data project , need to add DistribGBCD as key for distrib record
         if ( bVerificationEnabled )
         {
            DString dstrVerifyStat,dstrDistribGBCD;
            iter1.getObject()->getField( ifds::VerifyStat, dstrVerifyStat, idDataGroup, false );
            iter1.getObject()->getField( ifds::DistribGBCD, dstrDistribGBCD, idDataGroup, false );

            dstrVerifyStat.strip().upperCase();
            dstrDistribGBCD.strip().upperCase();

            dstr += I_(" ");
            dstr += dstrDistribGBCD;
         }

         if( !setCharacteristic.insert( dstr ).second )
         {
            // Need to change this message to also say the trans type is not unique.
            ADDCONDITIONFROMFILE( CND::ERR_ACCT_FUND_CLASS_NOT_UNIQUE );
            break;
         }

         AccountDistribution* pAcctDistrib = dynamic_cast<AccountDistribution*>( iter1.getObject() );
         if( pAcctDistrib && pAcctDistrib->isAllFundsMode( idDataGroup ) )
         {
            pAcctDistrib->validateAllFundsDistrib( idDataGroup );
            ++nLevelEntries;
         }
         else if (pAcctDistrib && bVerificationEnabled )
         {
            pAcctDistrib->validateDeletedChildDistrib( idDataGroup );			
            ++nLevelEntries;
         }
         else if( !dstrFundCode.empty() && !dstrClassCode.empty() )
         {
            ++nLevelEntries;
         }		 
      }
      else if( _level == FUND_CLASS_LEVEL )
      {
         AccountDistribution* pAcctDistrib = dynamic_cast<AccountDistribution*>( iter1.getObject() );
         if( pAcctDistrib && pAcctDistrib->isAllFundsMode( idDataGroup ) )
         {
            ++nLevelEntries;
         }
         else
         {
            DString dstr;
            DString dstrFundToCode;
            iter1.getObject()->getField( ifds::FundToCode, dstrFundToCode, 
                                         idDataGroup );
            dstrFundToCode.strip().upperCase();

            DString dstrClassToCode;
            iter1.getObject()->getField( ifds::ClassToCode, dstrClassToCode, 
                                         idDataGroup );
            dstrClassToCode.strip().upperCase();

            DString dstrDistribGBCD;
            iter1.getObject()->getField( ifds::DistribGBCD, dstrDistribGBCD, 
                                         idDataGroup );
            dstrDistribGBCD.strip().upperCase();

            if( (!dstrFundToCode.empty() && !dstrClassToCode.empty()) || dstrFundToCode == CASH )
            {
               dstr = dstrFundToCode;
               if( dstrFundToCode != CASH )
               {
                  dstr += I_(" ") + dstrClassToCode;
               }

               if ( bVerificationEnabled )
               {
                  dstr += I_(" ") + dstrDistribGBCD;
               }

               if( !setCharacteristic.insert( dstr ).second )
               {
                  ADDCONDITIONFROMFILE( CND::ERR_ACCT_FUND_CLASS_NOT_UNIQUE );
                  break;
               }

               ++nLevelEntries;
            }
         }
         ((AccountDistribution*)iter1.getObject())->CopyInfoToFundClassLevel(iter1.getObject()->getParent()->getParent(), idDataGroup);
      }

      ++iter1;
   }

   if( nLevelEntries == 0 )
   {
      ADDCONDITIONFROMFILE( _level == ACCOUNT_LEVEL ? CND::ERR_INCOMPLETE_FROM_FUND_INFORMATION : CND::ERR_INCOMPLETE_TO_INFORMATION );
   }
   else if( nLevelEntries > 1 && _level == FUND_CLASS_LEVEL )
   {
      BFCBO* parent = getParent();
      AccountDistribution* pAcctDistrib = dynamic_cast<AccountDistribution*>( parent );
      if( pAcctDistrib && pAcctDistrib->isAllFundsMode( idDataGroup ) )
      {
         ADDCONDITIONFROMFILE( CND::ERR_DISTRIB_MIX_NOT_ALLOWED );
      }
   }

   if( _level == FUND_CLASS_LEVEL )
   {	  
      double dTotalPercent = 0;
	  double dTotalDistRate = 0;
      BFObjIter iter2( *this, idDataGroup, false, 
                       BFObjIter::ITERTYPE::NON_DELETED );
      while( !iter2.end() )
      {
         DString dstr, dstrGoodBad, dstrDistRate;
         iter2.getObject()->getField( ifds::AllocPercent, dstr, idDataGroup );
         iter2.getObject()->getField( ifds::DistribGBCD, dstrGoodBad, idDataGroup, false );
		 iter2.getObject()->getField( ifds::DistribRate, dstrDistRate, idDataGroup );
         dstrGoodBad.strip().upperCase();
         dstr.strip().stripAll( I_CHAR( ',' ) );
         I_CHAR *stopstring;

         // if system has verification enable only sum with good record
         // otherwise sum all records
         if ( bVerificationEnabled )
         {
            if ( dstrGoodBad != I_("N") )
            {
               dTotalPercent += wcstod( dstr.c_str(), &stopstring );
			   dTotalDistRate += DSTCommonFunctions::convertToDouble(dstrDistRate);
            }
            else
            {
               ++iter2;
               continue;
            }
         }
         else
         {
            dTotalPercent += wcstod( dstr.c_str(), &stopstring );
			dTotalDistRate += DSTCommonFunctions::convertToDouble(dstrDistRate);
         }

         ++iter2;
      }

      bool bValidateSum = true;
      if( bVerificationEnabled )
      {
         BFCBO* parent = getParent();
         AccountDistribution* pAcctDistrib = dynamic_cast<AccountDistribution*>( parent );
         if( pAcctDistrib  )
         {
            DString strVerifyStat, strDistribGBCD, strVerifyStatHostGrp;
            pAcctDistrib->getField( ifds::VerifyStat, strVerifyStat, idDataGroup, false );
            pAcctDistrib->getField( ifds::DistribGBCD, strDistribGBCD, idDataGroup, false );
            pAcctDistrib->getField( ifds::VerifyStat, strVerifyStatHostGrp, BF::HOST, false );
            
            // if parent's verify stat is unverified and bad, mean deleted record waiting
            // for verification therefore not sum at all
            if( strDistribGBCD == I_("N") )
            {
               if ( strVerifyStat == UNVERIFIED )
               {
                  // this deleted record is not verified yet and stay as same as original from
                  // backend
                  bValidateSum = false;
               }
               else if ( strVerifyStat == VERIFIED && strVerifyStatHostGrp == UNVERIFIED )
               {
                  // deleted record is verified
                  bValidateSum = false;
               }
            }
         }
      }
      else
      {
         bValidateSum = true;
      }

      if ( bValidateSum )
      {
		  if (dTotalDistRate > 0.0) 
		  {			 
			  BFCBO* parent = getParent();
			  AccountDistribution* pAcctDistrib = dynamic_cast<AccountDistribution*>( parent );
			  if( pAcctDistrib )
			  {
				  DString dstrLastIDRate;

				  pAcctDistrib->getField( ifds::LastIDRate, dstrLastIDRate, idDataGroup, false );
				  double dLastIDRate = DSTCommonFunctions::convertToDouble(dstrLastIDRate);

				  if (fabs( dTotalDistRate - dLastIDRate ) > .000001) 
				  {
					  getErrMsg (IFASTERR::SUM_OF_DISTRIBUTION_RATES_NOT_RECENT_DISTRIBUTION,
						  CND::ERR_SUM_OF_DISTRIBUTION_RATES_NOT_RECENT_DISTRIBUTION,
						  CND::WARN_SUM_OF_DISTRIBUTION_RATES_NOT_RECENT_DISTRIBUTION,
						  idDataGroup); 
				  }
			  }			  
		  } 

		  if( fabs( dTotalPercent - 100 ) > .0000000001 )
		  {
			  ADDCONDITIONFROMFILE( CND::ERR_SUM_OF_PERCENTAGES_NOT_100 );
		  }
		
      }
   }

   if( _level == FUND_CLASS_LEVEL )
   {
      BFObjIter iter( *this, idDataGroup, 0, BFObjIter::ITERTYPE::NON_DELETED);
      BFAbstractCBO *pBFCBO;
      DString str, dstrTransType;

      while( !iter.end() )
      {
         pBFCBO = iter.getObject();
         if( !iter.isDummy()  && pBFCBO )
         {
            pBFCBO->getField(ifds::DistributionPayType, str, idDataGroup, false);
            getField ( ifds::TransType, dstrTransType, idDataGroup, false );
            if( str == I_("S") && dstrTransType != MFR )
            {
               // need clean up
               Shareholder *pShareholder;
               getWorkSession().getShareholder( idDataGroup, _dstrShareholderNum, pShareholder );

               AccountMailingList *pAccountMailingList;
               pShareholder->getAccountMailingList( pAccountMailingList, idDataGroup );

               DString strKey;
               pAccountMailingList->buildKey( strKey, _dstrAccountNum );

               BFObjIter iter(*pAccountMailingList, BF::HOST, false, BFObjIter::ITERTYPE::NON_DELETED );

               if( iter.positionByKey( strKey ) )
               {
                  DString str;
                  iter.getObject()->getField(ifds::DivChqAddr, str, idDataGroup, false );
                  if( str.strip() == NULL_STRING )
                  {
                     DString dstrFieldName;
//                     PropertyRepository::getInstance()->getFieldNameFromId( DBR::DivChqAddr, dstrFieldName );
//CP                            DP::getFieldNameFromId(DBR::DivChqAddr, dstrFieldName );
                     ADDCONDITIONFROMFILE(CND::ERR_FIELD_REQUIRED_PLS_ENTER );
                  }
               }
            }
         }
         ++iter;
      }
   }
  
   validateDeletedRecord(idDataGroup);   

   return(GETCURRENTHIGHESTSEVERITY());
};

//******************************************************************************
void AccountDistributionList::setObjectFlags( const BFObjectKey & objKey, long &lStateFlags, 
                                              long &lGroupFlags )
{
   if( isDistributionBankList )
   {
      lStateFlags = BFCBO::NO_BASE_DELETE;
      lGroupFlags = 0;
   }
   else
   {
      BFCBO::setObjectFlags( objKey, lStateFlags, lGroupFlags );
   }
}

//**************************************************************************
SEVERITY AccountDistributionList::setFundMastDetailList(AccountDistribution* pAcct)

{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getFundMastDetailList" ) );

   FundMasterList* pFundMastList;
   FundDetailList* pFundDetailList;

   SEVERITY sevRtn1 = getMgmtCo().getFundMasterList( pFundMastList );
   SEVERITY sevRtn2 = getMgmtCo().getFundDetailList( pFundDetailList );
   if( sevRtn1 > WARNING || sevRtn2 > WARNING )
   {
      // this should never hapen
      assert(0);
   }
   pAcct->SetListPointer(pFundDetailList,pFundMastList);

   return(GETCURRENTHIGHESTSEVERITY());
}

//**************************************************************************
SEVERITY AccountDistributionList::getMore()
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getMore" ) );

    if( doMoreRecordsExist() )
    {
        BFData *pNewResponseData0016 = new BFData(ifds::DSTC0016_VW);

        SEVERITY sevRtn = 
        BFDataBroker::getInstance( )->receive( DSTC_REQUEST::ACC_DISTRIB, 
                                               _requestData0016, 
                                               *pNewResponseData0016, 
                                               DSTCRequestor(getSecurity(), false),
                                               &_moreRecordsAvailable );

        if( sevRtn > WARNING )
        {
            delete pNewResponseData0016;
            pNewResponseData0016 = NULL;
            return(sevRtn);
        }

        initDistributionData( pNewResponseData0016,
                              BF::HOST,
                              _dstrAccountNum,
                              _dstrShareholderNum);
    }

   return(GETCURRENTHIGHESTSEVERITY());
}

//**************************************************************************
SEVERITY AccountDistributionList::initDistributionData( const BFData*  distributionData,
                                                        const BFDataGroupId& idDataGroup,
                                                        const DString& dstrAccountNum,
                                                        const DString& dstrShareholderNum,
                                                        const DString& dstrFundCode, 
                                                        const DString& dstrClassCode,
                                                        const DString& dstrEffectiveDate,
                                                        const DString& dstrTransType,
                                                        const DString& dstrTrack,
                                                        const DString& dstrPageName )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "initDistributionData" ) );

   bool bVerificationEnabled = false;
   getWorkSession ().isVerificationEnabled ( idDataGroup, 
                                             DISTRIB_CATEGORY, 
                                             DISTRIB_LEVEL, 
                                             bVerificationEnabled);

   BFData*  distributionData2 = const_cast<BFData*>(distributionData);

   if( distributionData2 )
   {
      int iRptCount = distributionData2->getRepeatCount();

      for( int i = 0; i < iRptCount; i++ )
      {
         BFData &data = const_cast<BFData &> ( distributionData2->getRepeat( i ) );

         if( _level == ACCOUNT_LEVEL )
         {
            DString dstrKeyDistrib;
            getStrKey( dstrKeyDistrib, &data );

            if( !getObject( dstrKeyDistrib, idDataGroup ) )
            {
               // top level CBO object does not exist, so we create it 
               AccountDistribution *pAcctDist = new AccountDistribution( *this );
               setFundMastDetailList(pAcctDist);

               pAcctDist->init( idDataGroup, 
                                dstrAccountNum, 
                                dstrShareholderNum, 
                                _level, 
                                &data, 
                                distributionData2 );

               setObject( pAcctDist, dstrKeyDistrib, OBJ_ACTIVITY_NONE, idDataGroup );
            }
         }
         else if( _level == FUND_CLASS_LEVEL )
         {
            DString dstr (data.getElementValue( ifds::FundCode ));
            dstr.strip().upperCase();

            if( dstr == dstrFundCode )
            {
               DString dstr (data.getElementValue( ifds::ClassCode ));
               dstr.strip().upperCase();

               if( dstr == dstrClassCode )
               {
                  DString dstr (data.getElementValue( ifds::EffectiveDate ));
                  dstr.strip();

                  if( dstr == dstrEffectiveDate )
                  {
                     DString dstr (data.getElementValue( ifds::TransType ));
                     dstr.strip().upperCase();

                     if ( dstr == dstrTransType )
                     {
                        DString dstrKeyDistrib;
                        getStrKey( dstrKeyDistrib, &data );

                        bool bInitDistrib = false;

                        if ( bVerificationEnabled )
                        {
                           AccountDistribution *pParentAcctDist =
                              dynamic_cast<AccountDistribution *>(getParent());

                           assert( pParentAcctDist );
                           if( pParentAcctDist )
                           {
                              DString strDistribGBCD, strSubDistribGBCD;
                              pParentAcctDist->getField( ifds::DistribGBCD, strDistribGBCD, idDataGroup, false );
                              strSubDistribGBCD = data.getElementValue( ifds::DistribGBCD );
                              strDistribGBCD.strip().upperCase();
                              strSubDistribGBCD.strip().upperCase();

                              // assume that parent and child should have everythings on
                              // From-side same
                              if ( strDistribGBCD == strSubDistribGBCD )
                              {
                                 bInitDistrib = true;
                              }
                           }
                        }
                        else
                        {
                           bInitDistrib = true;
                        }

                        if ( bInitDistrib )
                        {
                           AccountDistribution *pAcctDist = new AccountDistribution( *this );
                           setFundMastDetailList(pAcctDist);

                           pAcctDist->init( idDataGroup,
                                          _dstrAccountNum,
                                          _dstrShareholderNum,
                                          _level,
                                          &data,
                                          distributionData2 );
                           setObject( pAcctDist, dstrKeyDistrib, OBJ_ACTIVITY_NONE, idDataGroup );
                        }

                        //AccountDistribution *pAcctDist = new AccountDistribution( *this );
                        //setFundMastDetailList(pAcctDist);

                        //pAcctDist->init( idDataGroup,
                        //                 _dstrAccountNum,
                        //                 _dstrShareholderNum,
                        //                 _level,
                        //                 &data,
                        //                 distributionData2 );

                        //setObject( pAcctDist, dstrKeyDistrib, OBJ_ACTIVITY_NONE, idDataGroup );
                     }
                  }
               }
            }
         }
         else
         {
            assert( 0 );
         }
      } // end for iRptCount

	  double dTotalDistRate = 0.0;
	  getTotalDistribRate(idDataGroup, dTotalDistRate);
	  setTotalDistribRate(idDataGroup, dTotalDistRate);	 

   } // end if

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY AccountDistributionList::doDeleteObject ( const DString & strKey, const BFDataGroupId& idDataGroup, bool bIsObjectDestroyed ) 
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, 
                          CLASSNAME, 
                          I_( "doDeleteObject" ) );

   bool bVerificationEnabled = false;
   getWorkSession ().isVerificationEnabled ( idDataGroup, 
                                             DISTRIB_CATEGORY, 
                                             DISTRIB_LEVEL, 
                                             bVerificationEnabled);

   if( _level == FUND_CLASS_LEVEL && bVerificationEnabled )
   {
      DString strTrantype;
      getParent()->getField( ifds::TransType, strTrantype, idDataGroup, false );
      strTrantype.strip().upperCase();

      // deletion allocation of distrib record, set it's parent DistribGBCD to Good
      if (strTrantype == INCOME_DISTRIB )
      {
         getParent()->setField( ifds::DistribGBCD, I_("Y"), idDataGroup, false );

         BFObjIter iterDistribToList( *this, idDataGroup );

         DString strDelObjKey(strKey);
         strDelObjKey.strip().upperCase();

         while( !iterDistribToList.end() )
         {
            AccountDistribution *pToDistrib = 
               dynamic_cast<AccountDistribution *>(iterDistribToList.getObject());
            if (pToDistrib)
            {
               DString strCurObjKey;
               DString dstrFundToCode, dstrClassToCode, dstrDistribGBCD;

               pToDistrib->getField( ifds::FundToCode, dstrFundToCode, idDataGroup, false );
               pToDistrib->getField( ifds::ClassToCode, dstrClassToCode, idDataGroup, false );
               pToDistrib->getField( ifds::DistribGBCD, dstrDistribGBCD, idDataGroup, false );
               dstrFundToCode.strip().upperCase();
               dstrClassToCode.strip().upperCase();
               dstrDistribGBCD.strip().upperCase();

               if( (!dstrFundToCode.empty() && !dstrClassToCode.empty()) || dstrFundToCode == CASH )
               {
                  strCurObjKey = dstrFundToCode;
                  if( dstrFundToCode != CASH )
                  {
                     strCurObjKey += I_(" ") + dstrClassToCode;
                  }
                  strCurObjKey += I_(" ") + dstrDistribGBCD;
               }

               strCurObjKey.strip().upperCase();

               if ( strDelObjKey == strCurObjKey)
               {
                  pToDistrib->setField( ifds::DelDistribAlloc, I_("Y"), idDataGroup, false );
                  break;
               }
            }
            ++iterDistribToList;
         }
      }
   }
   else if ( _level == ACCOUNT_LEVEL && bVerificationEnabled )
   {
      BFObjIter iterDistrib( *this, idDataGroup );
      while( !iterDistrib.end() )
      {
         DString strTransType,strFund,strClass,strEffDate,strTempStringKey,
                 strVerifyStatus, strDistribGBCD;

         iterDistrib.getObject()->getField(ifds::TransType,strTransType,idDataGroup, false);
         iterDistrib.getObject()->getField(ifds::FundCode, strFund,idDataGroup, false );
         iterDistrib.getObject()->getField(ifds::ClassCode, strClass,idDataGroup, false );
         iterDistrib.getObject()->getField(ifds::EffectiveDate, strEffDate,idDataGroup, false );
         iterDistrib.getObject()->getField(ifds::VerifyStat, strVerifyStatus,idDataGroup, false );
         iterDistrib.getObject()->getField(ifds::DistribGBCD, strDistribGBCD,idDataGroup, false );

         strFund.strip().upperCase();
         strClass.strip().upperCase();
         strTransType.strip().upperCase();
         strVerifyStatus.strip().upperCase();
         strDistribGBCD.strip().upperCase();
         strEffDate.strip();
         strTempStringKey = strTransType     + I_( " " ) + 
                            strFund          + I_( " " ) + 
                            strClass         + I_( " " ) + 
                            strEffDate       + I_( " " ) + 
                            strDistribGBCD;

         // deletion account level distrib record, DistribGBCD to Bad
         // and due to modification of record therefore verify status 
         // must be 'UNVERIFIED'
         if (strTransType == INCOME_DISTRIB && strTempStringKey == strKey )
         {
            iterDistrib.getObject()->setField(ifds::DistribGBCD, I_("N"), idDataGroup, false );
            // for deletion of account level(their allocation also get delete though) 
            // mark 'DelDistribAlloc' as 'N', and object activity flag will be handled by 
            // framework
            iterDistrib.getObject()->setField(ifds::DelDistribAlloc, I_("N"), idDataGroup, false );
            if ( strVerifyStatus == VERIFIED || 
                 strVerifyStatus == UNVERIFIED )
            {
               AccountDistribution *pDistrib = 
                  dynamic_cast<AccountDistribution *>(iterDistrib.getObject());
               if (pDistrib)
               {
                  pDistrib->verifyStatusChangesFromDeletion(idDataGroup);

                  AccountDistributionList* toDistribList;
                  pDistrib->getSplitList( toDistribList );

                  if( toDistribList != NULL )
                  {
                     BFObjIter iterDistribToList( *toDistribList, idDataGroup );

                     while( !iterDistribToList.end() )
                     {
                        AccountDistribution *pToDistrib = 
                           dynamic_cast<AccountDistribution *>(iterDistribToList.getObject());
                        if (pToDistrib)
                        {
                           pToDistrib->verifyStatusChangesFromDeletion(idDataGroup);
                           pToDistrib->setField(ifds::DelDistribAlloc, I_("N"), idDataGroup, false );
                        }
                        ++iterDistribToList;
                     }
                  }
               }
            }
            break;
         }
         ++iterDistrib;
      }
   }

   recalculatePercentages( idDataGroup, bVerificationEnabled, strKey );

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
/** Iterate through the list of deleted items, and then look for a similar unverified bad record.
    If there are similar reccord, raised a hard edit. */
SEVERITY AccountDistributionList::validateDeletedRecord( const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, 
                          CLASSNAME, 
                          I_( "validateDeletedRecord" ) );

   bool bVerificationEnabled = false;
   getWorkSession ().isVerificationEnabled ( idDataGroup, 
                                             DISTRIB_CATEGORY, 
                                             DISTRIB_LEVEL, 
                                             bVerificationEnabled);

   if ( _level == ACCOUNT_LEVEL && bVerificationEnabled && !isNew() )
   {
      DString strKeyDel, strKeyCurObj;
      bool bError = false;

      BFObjIter iterDistrib( *this, idDataGroup, false, BFObjIter::DELETED );

      // Iterate through deleted records
      while( !iterDistrib.end() )
      {
		AccountDistribution* pDistrib = 
			dynamic_cast<AccountDistribution*>(iterDistrib.getObject());
		if ( pDistrib )
		{
			DString dstrFund, dstrClass, dstrTransType;
			pDistrib->getField( ifds::FundCode, dstrFund, idDataGroup, false );
			pDistrib->getField( ifds::ClassCode, dstrClass, idDataGroup, false  );
			pDistrib->getField( ifds::TransType, dstrTransType, idDataGroup, false  );
			dstrFund.strip().upperCase();
			dstrClass.strip().upperCase();
			dstrTransType.strip().upperCase();

			strKeyDel = dstrTransType + I_( " " ) + 
						dstrFund      + I_( " " ) + 
						dstrClass;
			strKeyDel.strip().upperCase();
		}
		if(!strKeyDel.empty())
		{
			BFObjIter iterNonDel( *this, idDataGroup, false, BFObjIter::NON_DELETED );
			iterNonDel.begin();
			// look for an unverified bad record which have similar criteria to the deleted record.
			while( !iterNonDel.end() )
			{   
				AccountDistribution* pNonDelDistrib = 
						dynamic_cast<AccountDistribution*>(iterNonDel.getObject());
				if ( pNonDelDistrib )
				{
					DString dstrFund, dstrClass, dstrTransType;
					pNonDelDistrib->getField( ifds::FundCode, dstrFund, idDataGroup, false );
					pNonDelDistrib->getField( ifds::ClassCode, dstrClass, idDataGroup, false  );
					pNonDelDistrib->getField( ifds::TransType, dstrTransType, idDataGroup, false  );
					dstrFund.strip();
					dstrClass.strip();
					dstrTransType.strip();

					strKeyCurObj = dstrTransType + I_( " " ) + 
									dstrFund      + I_( " " ) + 
									dstrClass;
					strKeyCurObj.strip().upperCase();
						
					if ( !strKeyCurObj.empty() && strKeyCurObj == strKeyDel )
					{
						DString dstrVerifyStat, dstrDistribGBCD;
						pNonDelDistrib->getField( ifds::VerifyStat, dstrVerifyStat, idDataGroup, false );
						pNonDelDistrib->getField( ifds::DistribGBCD, dstrDistribGBCD, idDataGroup, false );
						    
						if ( dstrVerifyStat == UNVERIFIED && dstrDistribGBCD == I_("N"))
						{
							bError = true;
							break;
						}
					}
				}
				++iterNonDel;
			}
		}
		if( bError)
		{
			ADDCONDITIONFROMFILE( CND::ERR_UNVERIFIED_DELETED_BEING_DUPLICATE );
			break;
		}
         ++iterDistrib;
      }
   }

   return(GETCURRENTHIGHESTSEVERITY());   
}

//******************************************************************************
void AccountDistributionList::getTotalDistribRate( const BFDataGroupId& idDataGroup, double& dTotalDistribRate, const DString& strKey )
{		
	DString dstrGoodBad, dstrDistribRate, dstrTotalDistribRate;	

	BFObjIter iter( *this, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED );
	iter.begin();	

	while( !iter.end() )
	{
		iter.getObject()->getField( ifds::DistribGBCD, dstrGoodBad, idDataGroup, false );
		dstrGoodBad.strip().upperCase();

		iter.getObject()->getField( ifds::DistribRate, dstrDistribRate, idDataGroup, false );

		if ( iter.getStringKey () != strKey && dstrGoodBad != I_("N") )
		{
			dTotalDistribRate += DSTCommonFunctions::convertToDouble(dstrDistribRate); 		
		}
		else
		{
			++iter;
			continue;
		}
		++iter;
	}
}

//******************************************************************************
void AccountDistributionList::setAllAllocsFndClsValidFlag(bool isValid, const BFDataGroupId& idDataGroup)
{
    BFObjIter iter(*this, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED);

    while (!iter.end())
    {
        AccountDistribution *pAccountDistribution = dynamic_cast<AccountDistribution*>(iter.getObject());

        if (pAccountDistribution && !iter.isDummy())
        {
            pAccountDistribution->setFieldValid(ifds::ToSoftCapCheck, idDataGroup, isValid);
            pAccountDistribution->setFieldUpdated(ifds::ToSoftCapCheck, idDataGroup, true);
        }

        ++iter;
    }
}

//******************************************************************************
void AccountDistributionList::setTotalDistribRate( const BFDataGroupId& idDataGroup, double& dTotalDistribRate )
{		
	DString dstrTotalDistribRate;	
	
	dstrTotalDistribRate = DSTCommonFunctions::doubleToDString(ifds::TotalDistribRate, dTotalDistribRate);

	BigDecimal bdTotalDistribRate = DSTCommonFunctions::convertToBigDecimal(dstrTotalDistribRate);  
	BigDecimal bdZero = DSTCommonFunctions::convertToBigDecimal(I_("0.0"));

	BFObjIter iter( *this, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED );
	iter.begin();	

	while( !iter.end() )
	{		 		
		iter.getObject()->setField( ifds::TotalDistribRate, dstrTotalDistribRate, idDataGroup, false );						
		++iter;
	}		

}

//******************************************************************************
void AccountDistributionList::recalculatePercentages( const BFDataGroupId& idDataGroup, bool bVerificationEnabled, const DString& strKey )
{	
	double dTotalDistRate = 0.0;
	getTotalDistribRate(idDataGroup, dTotalDistRate, strKey);

	DString dstrTotalDistribRate = DSTCommonFunctions::doubleToDString(ifds::TotalDistribRate, dTotalDistRate);
	BigDecimal bdTotalDistribRate = DSTCommonFunctions::convertToBigDecimal(dstrTotalDistribRate);  
	BigDecimal bdZero = DSTCommonFunctions::convertToBigDecimal(I_("0.0"));
	if (bdTotalDistribRate == bdZero) 
		return;

	DString dstrGoodBad, dstrAllocPercent, dstrDistribRate;
	double dDistribRate = 0.0, dTotalDistribRate = 0.0, dAllocPercent = 0.0;
	
	BFObjIter iter( *this, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED );
	iter.begin();	

	double dTotalPercent = 0.0;
	while( !iter.end() )
	{
		iter.getObject()->getField( ifds::DistribGBCD, dstrGoodBad, idDataGroup, false );
		dstrGoodBad.strip().upperCase();

		iter.getObject()->getField( ifds::AllocPercent, dstrAllocPercent, idDataGroup, false );

		if ( bVerificationEnabled )
		{
			if ( iter.getStringKey () != strKey && dstrGoodBad != I_("N") )
			{
				iter.getObject()->getField( ifds::DistribRate, dstrDistribRate, idDataGroup, false );
				dDistribRate =  DSTCommonFunctions::convertToDouble( dstrDistribRate );				
				dAllocPercent = dDistribRate / dTotalDistRate * 100;
				dstrAllocPercent = DSTCommonFunctions::doubleToDString( ifds::AllocPercent, dAllocPercent );

				BigDecimal bdAllocPercent = DSTCommonFunctions::convertToBigDecimal(dstrAllocPercent);  
				if (bdAllocPercent != bdZero) {
					iter.getObject()->setField( ifds::AllocPercent, dstrAllocPercent, idDataGroup, false );
					dTotalPercent += DSTCommonFunctions::convertToDouble(dstrAllocPercent); 
				}				
			}
			else
			{
				++iter;
				continue;
			}
		}
		else if ( iter.getStringKey () != strKey )
		{
			iter.getObject()->getField( ifds::DistribRate, dstrDistribRate, idDataGroup, false );
			dDistribRate =  DSTCommonFunctions::convertToDouble( dstrDistribRate );				
			dAllocPercent = dDistribRate / dTotalDistRate * 100;
			dstrAllocPercent = DSTCommonFunctions::doubleToDString( ifds::AllocPercent, dAllocPercent );

			BigDecimal bdAllocPercent = DSTCommonFunctions::convertToBigDecimal(dstrAllocPercent);  
			if (bdAllocPercent != bdZero) {
				iter.getObject()->setField( ifds::AllocPercent, dstrAllocPercent, idDataGroup, false );
				dTotalPercent += DSTCommonFunctions::convertToDouble(dstrAllocPercent); 
			}
		}
		++iter;		
	}

	DString dstrTotalPercent = DSTCommonFunctions::doubleToDString(ifds::AllocPercent, dTotalPercent);
	BigDecimal bdTotalPercent = DSTCommonFunctions::convertToBigDecimal(dstrTotalPercent);  
	BigDecimal bd100 = DSTCommonFunctions::convertToBigDecimal(I_("100.0"));
	if (bdTotalPercent == bd100) 
		return;

	roundOffLastPercent( idDataGroup, dTotalPercent );
}

//******************************************************************************
void AccountDistributionList::roundOffLastPercent( const BFDataGroupId& idDataGroup, double& dTotalPercent)
{			
	DString dstrGoodBad, dstrAllocPercent, dstrRoundedAllocPercent, keyPrcnt;
	double dAllocPercent, dRoundedAllocPercent;
	
	BFObjIter iter( *this, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED );
	iter.begin();	

	while( !iter.end() )
	{
		iter.getObject()->getField( ifds::DistribGBCD, dstrGoodBad, idDataGroup, false );
		dstrGoodBad.strip().upperCase();
	
		if ( dstrGoodBad != I_("N") )
		{
			keyPrcnt = iter.getStringKey();				
		}
		else
		{
			++iter;
			continue;
		}
		++iter;
	}
	
	iter.positionByKey( keyPrcnt );
	iter.getObject()->getField( ifds::AllocPercent, dstrAllocPercent, idDataGroup, false );
	dAllocPercent =  DSTCommonFunctions::convertToDouble( dstrAllocPercent );			
	dRoundedAllocPercent = 100 - dTotalPercent + dAllocPercent;

	dstrRoundedAllocPercent = DSTCommonFunctions::doubleToDString( ifds::AllocPercent, dRoundedAllocPercent );
	iter.getObject()->setField(ifds::AllocPercent, dstrRoundedAllocPercent, idDataGroup, false );		
	
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/AccountDistributionList.cpp-arc  $
 * 
 *    Rev 1.48   Feb 25 2011 08:07:16   wutipong
 * IN#2327932 - Correct the code comments.
 * 
 *    Rev 1.46   Feb 14 2011 10:24:30   wutipong
 * IN#2327932 MFM - Unable to verify distribution option records
 * 
 *    Rev 1.45   Feb 08 2010 22:12:02   dchatcha
 * IN# 1988872 - R97_Static Data_Cannot add Distrib Option identical to unverified deleted one.
 * 
 *    Rev 1.44   Feb 06 2010 17:23:48   dchatcha
 * Restored 1.41
 * 
 *    Rev 1.43   Feb 04 2010 09:52:10   dchatcha
 * IN# 1988872 - R97_Static Data_Cannot add Distrib Option identical to unverified deleted one, More case on verification of unverified deleted record.
 * 
 *    Rev 1.42   Feb 03 2010 19:02:28   dchatcha
 * IN# 1988872 - R97_Static Data_Cannot add Distrib Option identical to unverified deleted one.
 * 
 *    Rev 1.41   Dec 23 2009 01:45:16   dchatcha
 * IN# 1953647 - R97 Cannot delete distribution option.
 * 
 *    Rev 1.40   Dec 03 2009 03:18:32   dchatcha
 * PET0166583 FN02 FN03 - Static Verification Phase 2.
 * 
 *    Rev 1.39   23 Feb 2009 15:32:38   kovacsro
 * P0155543_FN01_ Account Level Distribution 
 * 
 *    Rev 1.36   Feb 26 2008 15:09:56   daechach
 * In# 1160207 - Desktop distribution - Added 'More' button to account distribution screen.
 * 
 *    Rev 1.35   24 Dec 2007 09:52:36   kovacsro
 * PET2400FN01R2.0 - added validation when account level bulking is not turned on
 * 
 *    Rev 1.34   21 Dec 2007 14:43:26   kovacsro
 * PET2400FN01 - account level distribution instruction
 * 
 *    Rev 1.33   Nov 26 2004 09:39:42   yingbaol
 * PTS10036215: retrieve more than 25 records
 * 
 *    Rev 1.32   Aug 16 2004 16:12:06   popescu
 * PTS 10033088, with this fix the account distribution list handles different distribution trans types (ID, MR, etc)
 * 
 *    Rev 1.31   Jun 03 2003 16:05:18   popescu
 * removed obsolete getDistributionBankList
 * 
 *    Rev 1.30   Mar 21 2003 17:54:02   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.29   Oct 09 2002 23:53:50   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.28   Aug 29 2002 18:46:20   SMITHDAV
 * Sync-up branches.
 * 
 *    Rev 1.27   Aug 29 2002 12:54:50   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.26   Jul 05 2002 16:08:56   HERNANDO
 * Added validation check - empty list item from either account or fund list will cause incomplete distribution entry error.
 * 
 *    Rev 1.25   22 May 2002 18:26:06   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.24   18 Apr 2002 15:27:28   HSUCHIN
 * Added support for Management Fee Rebate Distribution
 * 
 *    Rev 1.23   Feb 25 2002 18:55:08   PURDYECH
 * Phase 1 of BFData Rollout - Base Component Compatibility
 * 
 *    Rev 1.22   Aug 04 2001 22:01:54   YINGBAOL
 * condition clearance
 * 
 *    Rev 1.21   Jun 26 2001 12:54:56   PURDYECH
 * Infrastructure Release 1.9 Integration.
 * 
 *    Rev 1.20   09 May 2001 11:30:38   HSUCHIN
 * Sync up with SSB
 * 
 *    Rev 1.19   03 May 2001 14:05:50   SMITHDAV
 * Session management restructuring.
 * 
 *    Rev 1.18   Feb 15 2001 14:36:42   DINACORN
 * Add Revision Control Entries
 * 
 */