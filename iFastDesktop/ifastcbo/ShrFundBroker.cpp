//*****************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by International Financial Data Services
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2004 by International Financial Data Services
//
//*****************************************************************************
//
//    ^FILE   : ShrFundBroker.cpp
//    ^AUTHOR : Monica Vadeanu
//    ^DATE   : November, 2004
//    Copyright 2004 by International Financial Data Services
//
//-----------------------------------------------------------------------------
//
// ^CLASS  : ShrFundBroker
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS :
//
//*****************************************************************************
#include "stdafx.h"

//#include "dstcworksession.hpp"
#include "fundbroker.hpp"
#include "fundbrokerlist.hpp"
#include "funddetail.hpp"
#include "funddetaillist.hpp"
#include "fundbrokerelig.hpp"
#include "fundmaster.hpp"
#include "fundmasterlist.hpp"
#include "mgmtco.hpp"
#include "shrfundbroker.hpp"
#include "shrfundbrokerlist.hpp"


#include <ifastdataimpl\dse_dstc0063_vw.hpp>                // Fund Master
#include <ifastdataimpl\dse_dstc0069_vw.hpp>                // Shareholder

#include <ifastdataimpl\dse_dstc0321_req.hpp>               // Fund Broker Elig
#include <ifastdataimpl\dse_dstc0326_req.hpp>               // Fund Broker List

#include <ifastdataimpl\dse_dstc0327_req.hpp>               // Shareholder Fund Broker Inquiry
#include <ifastdataimpl\dse_dstc0327_vwrepeat_record.hpp>   // Shareholder Fund Broker Inquiry

#include <ifastdataimpl\dse_dstc0328_reqrepeat_record.hpp>  // ShareholderFundBroker Update

namespace ifds
{
   //field ids used, not found in the above view   
	extern CLASS_IMPORT const BFTextFieldId FundWKN;
   extern CLASS_IMPORT const BFTextFieldId FundISIN;
	extern CLASS_IMPORT const BFTextFieldId FundName;	
	extern CLASS_IMPORT const BFTextFieldId FundBrokerName;	
   extern CLASS_IMPORT const BFTextFieldId FundEligBrokerLvl;  // used for cross edit between Fund and FundBroker
   extern CLASS_IMPORT const BFTextFieldId IsDefault;          // For the update view
}

namespace CND
{
   extern const long ERR_INVALID_FUND;
   extern const long ERR_INVALID_FUND_WKN;
   extern const long ERR_INVALID_FUND_ISIN;
   extern const long ERR_INVALID_FUND_BROKER;
   extern const long ERR_INVALID_FUND_FUND_BROKER_COMBINATION;
}

// Constants
namespace 
{
   const I_CHAR * CLASSNAME = I_("ShrFundBroker");
}


const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = {
   // Field DD Id,            State Flags,        Group Flags 
   { ifds::FundCode,          BFCBO::REQUIRED,             0 }, 
   { ifds::FundWKN,           BFCBO::NONE,                 0 }, 
	{ ifds::FundISIN,          BFCBO::NONE,                 0 }, 
	{ ifds::FundName,          BFCBO::NONE,                 0 }, 
	{ ifds::FundBroker,        BFCBO::REQUIRED,             0 }, 
   { ifds::FundBrokerName,    BFCBO::NONE,                 0 }, 
   { ifds::FundEligBrokerLvl, BFCBO::IMMEDIATE_VALIDATION, 0 },    
   { ifds::IsDefault,         BFCBO::NONE,                 0 },       
};

static const int NUM_FIELDS = sizeof(classFieldInfo) / sizeof(BFCBO::CLASS_FIELD_INFO);

//******************************************************************************
ShrFundBroker::ShrFundBroker(BFAbstractCBO &parent) 
: MFCanBFCbo(parent)
{
   TRACE_CONSTRUCTOR(CLASSNAME , NULL_STRING);

   registerMemberData( NUM_FIELDS,
                       (const CLASS_FIELD_INFO *)&classFieldInfo,
                       0,
                       NULL);     

   addCrossEdit( ifds::FundEligBrokerLvl, ifds::FundCode );
   addCrossEdit( ifds::FundEligBrokerLvl, ifds::FundBroker );   
}

//******************************************************************************
ShrFundBroker::~ShrFundBroker()
{
   TRACE_DESTRUCTOR(CLASSNAME);
}

//******************************************************************************
SEVERITY ShrFundBroker::init( const BFData &viewData )
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("init"));

   attachDataObject (const_cast<BFData&>(viewData), false, true);
   	
	DString dstrFund( viewData.getElementValue( ifds::FundCode ) );             
   dstrFund.stripAll().upperCase();
	
   getFundDetailInformation( I_("FUND"),
									  dstrFund,                                                                                                                          
									  I_( "" ),
                             I_( "" ),
                             BF::HOST ); 

   setFundBrokerName( BF::HOST );

   setFieldReadOnly( ifds::FundCode,   BF::HOST, true );
   setFieldReadOnly( ifds::FundWKN,    BF::HOST, true );
   setFieldReadOnly( ifds::FundISIN,   BF::HOST, true );
   setFieldReadOnly( ifds::FundBroker, BF::HOST, true );
   
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY ShrFundBroker::init( const BFDataGroupId &idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("init"));         
	
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
void ShrFundBroker::doInitWithDefaultValues( const BFDataGroupId &idDataGroup )
{   		
   setFieldNoValidate( ifds::IsDefault, I_( "Y" ), idDataGroup );
}

//******************************************************************************
void ShrFundBroker::doReset (const BFDataGroupId &idDataGroup)
{
   if( isNew() )
   {
      init( idDataGroup );
   }
}

//******************************************************************************
SEVERITY ShrFundBroker::doApplyRelatedChanges( const BFFieldId &idField, 
																		   const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("doApplyRelatedChanges"));

   DString dstrFund, dstrWKN, dstrISIN;

   if( idField == ifds::FundCode )
   {      
		getField (ifds::FundCode, dstrFund, idDataGroup );
		getFundDetailInformation( I_("FUND"),
										  dstrFund,                                                                                                                          
										  dstrWKN,
                                dstrISIN,
										  idDataGroup ); 
   }	
	else if ( idField == ifds::FundWKN  )
	{		
		getField( ifds::FundWKN, dstrWKN, idDataGroup );
		getFundDetailInformation( I_("WKN"),
										  dstrFund,                                                                                                                          
										  dstrWKN,
                                dstrISIN,
										  idDataGroup ); 
	}
	else if ( idField == ifds::FundISIN )
	{		
		getField( ifds::FundISIN, dstrISIN, idDataGroup );
		getFundDetailInformation( I_("ISIN"),
										  dstrFund,                                                                                                                          
										  dstrWKN,
                                dstrISIN,
										  idDataGroup ); 
	}
	else if ( idField == ifds::FundBroker )
	{
		setFundBrokerName( idDataGroup );
	}

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY ShrFundBroker::doValidateField( const BFFieldId &idField, 
																   const DString &strValue, 
																   const BFDataGroupId &idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("doValidateField") );
      
   if ( idField == ifds::FundCode )
   {
      validateFundCode( idDataGroup, strValue );
   }
   else if ( idField == ifds::FundWKN )
   {
      validateFundWKN( idDataGroup, strValue );
   }
   else if ( idField == ifds::FundISIN )
   {
      validateFundISIN( idDataGroup, strValue );
   }   
   else if ( idField == ifds::FundBroker )
   {
      validateFundBrokerCode( idDataGroup, strValue );
   }
   else if( idField == ifds::FundEligBrokerLvl )
   {
		// First check if this is a valid combination
      if ( isFundBrokerEligForFund( idDataGroup ) )
      {       		
		   // Duplicate Check
		   ShrFundBrokerList *pShrFundBrokerList = dynamic_cast<ShrFundBrokerList*>( getParent( ) );      
		   if ( NULL != pShrFundBrokerList )
		   {
			   // Call duplicate check from Parent
			   pShrFundBrokerList->checkDuplicate( this, idDataGroup );		
		   }
      }
   } 	

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY ShrFundBroker::validateFundCode( const BFDataGroupId &idDataGroup, 
                                          const DString &dstrFundCode )
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateFundCode" ) );

   DString dstrLocalFundCode = dstrFundCode;
   dstrLocalFundCode.upperCase();

   bool bFundExists = false;

   FundDetailList *pFundDetailList = new FundDetailList( *this );
   if( pFundDetailList->init( I_("FUND"), 
		                        dstrLocalFundCode, 
		 							   I_( "" ), 
										I_( "" ), 
										I_( "" ), 
										I_( "" ), 
										I_( "" ) ) <= WARNING &&
		 NULL != pFundDetailList )
	{
      BFObjIter iterList( *pFundDetailList, BF::HOST , false, BFObjIter::ITERTYPE::NON_DELETED );	         
         
      iterList.begin();
      while( !iterList.end() )
      {
         FundDetail *pFundDetail = dynamic_cast<FundDetail*>(iterList.getObject( ) );	
			if ( NULL != pFundDetail )
         {
            DString dstrCurrentFundCode;
            pFundDetail->getField( ifds::FundCode, dstrCurrentFundCode, BF::HOST );
            
            if ( dstrLocalFundCode == dstrCurrentFundCode.strip().upperCase() )                  
            {
               bFundExists = true;
               break;
            }
         }
      }
   }

   if ( false == bFundExists )
	{
      // Fund does not exist, please enter an existing one or leave it blank and select a valid fund.		
      ADDCONDITIONFROMFILE( CND::ERR_INVALID_FUND );						  				
	}

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY ShrFundBroker::validateFundWKN( const BFDataGroupId &idDataGroup, 
                                         const DString &dstrFundWKN )
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateFundWKN" ) );

   DString dstrLocalFundWKN = dstrFundWKN;
   dstrLocalFundWKN.upperCase();

   bool bFundExists = false;

   FundDetailList *pFundDetailList = new FundDetailList( *this );
   if( pFundDetailList->init( I_( "WKN" ), 
		                        I_( "" ), 
		 							   I_( "" ), 
										I_( "" ), 
										I_( "" ), 
										dstrLocalFundWKN, 
										I_( "" ) ) <= WARNING &&
		 NULL != pFundDetailList )
	{
      BFObjIter iterList( *pFundDetailList, BF::HOST , false, BFObjIter::ITERTYPE::NON_DELETED );	         
         
      iterList.begin();
      while( !iterList.end() )
      {
         FundDetail *pFundDetail = dynamic_cast<FundDetail*>(iterList.getObject( ) );	
			if ( NULL != pFundDetail )
         {
            DString dstrCurrentFundWKN;
            pFundDetail->getField( ifds::FundWKN, dstrCurrentFundWKN, BF::HOST );
            
            if ( dstrLocalFundWKN == dstrCurrentFundWKN.strip().upperCase() )                  
            {
               bFundExists = true;
               break;
            }
         }
      }
   }

   if ( false == bFundExists )
	{
      // Fund does not exist for selected WKN, please enter a valid WKN.
		ADDCONDITIONFROMFILE( CND::ERR_INVALID_FUND_WKN );
	}

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY ShrFundBroker::validateFundISIN( const BFDataGroupId &idDataGroup, 
                                          const DString &dstrFundISIN )
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateFundISIN" ) );

   DString dstrLocalFundISIN = dstrFundISIN;
   dstrLocalFundISIN.upperCase();

   bool bFundExists = false;

   FundDetailList *pFundDetailList = new FundDetailList( *this );
   if( pFundDetailList->init( I_( "ISIN" ), 
		                        I_( "" ), 
		 							   I_( "" ), 
										I_( "" ), 
										I_( "" ), 
										I_( "" ), 
										dstrLocalFundISIN ) <= WARNING &&
		 NULL != pFundDetailList )
	{
      BFObjIter iterList( *pFundDetailList, BF::HOST , false, BFObjIter::ITERTYPE::NON_DELETED );	         
         
      iterList.begin();
      while( !iterList.end() )
      {
         FundDetail *pFundDetail = dynamic_cast<FundDetail*>(iterList.getObject( ) );	
			if ( NULL != pFundDetail )
         {
            DString dstrCurrentFundISIN;
            pFundDetail->getField( ifds::FundISIN, dstrCurrentFundISIN, BF::HOST );
            
            if ( dstrLocalFundISIN == dstrCurrentFundISIN.strip().upperCase() )                  
            {
               bFundExists = true;
               break;
            }
         }
      }
   }

   if ( false == bFundExists )
	{
      // Fund does not exist for selected ISIN, please enter a valid ISIN.
		ADDCONDITIONFROMFILE( CND::ERR_INVALID_FUND_ISIN );
	}

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY ShrFundBroker::validateFundBrokerCode( const BFDataGroupId &idDataGroup, 
                                                const DString &dstrFundBroker )
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateFundBrokerCode" ) );

   DString dstrLocalFundBroker = dstrFundBroker;
   dstrLocalFundBroker.strip();
	
   // Use View 326
   FundBrokerList *pFundBrokerList = NULL;
   if( getWorkSession().getFundBrokerList( pFundBrokerList, idDataGroup, true, dstrFundBroker ) <= WARNING &&
       NULL != pFundBrokerList )
   {
      FundBroker *pFundBroker = NULL;
      if ( pFundBrokerList->getFundBroker ( dstrLocalFundBroker, idDataGroup, pFundBroker ) > WARNING ||
           NULL == pFundBroker )
      {         
         // Invalid Fund Broker
         ADDCONDITIONFROMFILE( CND::ERR_INVALID_FUND_BROKER );
      }
   }
   // else View 326 returns error 561 "Invalid Fund Broker Code"

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
bool ShrFundBroker::isFundBrokerEligForFund( const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_( "isFundBrokerEligForFund" ) );
     
   bool bEligible = false;

   DString dstrFundCode, dstrFundBrokerCode;
   getField (ifds::FundCode,   dstrFundCode,       idDataGroup, false );
   getField( ifds::FundBroker, dstrFundBrokerCode, idDataGroup, false );

   if( !dstrFundCode.empty() && !dstrFundBrokerCode.empty() ) 
   {     
      // Use View 321
      FundBrokerElig fundBrokerElig (*this);
      if ( fundBrokerElig.init( dstrFundBrokerCode, dstrFundCode ) <= WARNING )
      {         
         if ( fundBrokerElig.isFundBrokerEligToTradeFund ( dstrFundBrokerCode, 
                                                           dstrFundCode, 
                                                           idDataGroup ) )
         {  
            bEligible = true;
         }
      }

      if ( false == bEligible )
      {
         // Invalid Fund and Fund Broker combination
         ADDCONDITIONFROMFILE( CND::ERR_INVALID_FUND_FUND_BROKER_COMBINATION );
      }
   }
   
   return bEligible;
}

//******************************************************************************
SEVERITY ShrFundBroker::getFundDetailInformation( const DString& dstrSearchType,
																  const DString& dstrFund,                                                                                                                          
																  const DString& dstrWKN,
                                                  const DString& dstrISIN,
																  const BFDataGroupId &idDataGroup ) 
{
	MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("getFundDetailInformation") );

   DString dstrLocalFund = dstrFund,
           dstrLocalWKN  = dstrWKN,
           dstrLocalISIN = dstrISIN;

   dstrLocalFund.strip().upperCase();
   dstrLocalWKN.strip().upperCase();
   dstrLocalISIN.strip().upperCase();

	FundDetailList *pFundDetailList = new FundDetailList( *this );
   if( pFundDetailList->init( dstrSearchType, 
		                        dstrLocalFund, 
		 							   I_( "" ), 
										I_( "" ), 
										I_( "" ), 
										dstrLocalWKN, 
										dstrLocalISIN ) <= WARNING &&
		 NULL != pFundDetailList )
	{
      BFObjIter iterList( *pFundDetailList, BF::HOST , false, BFObjIter::ITERTYPE::NON_DELETED );	         
         
      iterList.begin();
      while( !iterList.end() )
      {
         FundDetail *pFundDetail = dynamic_cast<FundDetail*>(iterList.getObject( ) );	
			if ( NULL != pFundDetail )
         {
            DString dstrCurrentFundCode, dstrCurrentWKN, dstrCurrentISIN;
            pFundDetail->getField( ifds::FundCode, dstrCurrentFundCode, BF::HOST );
            pFundDetail->getField( ifds::FundWKN,  dstrCurrentWKN,      BF::HOST );
            pFundDetail->getField( ifds::FundISIN, dstrCurrentISIN,     BF::HOST );

            if ( ( !dstrLocalFund.empty() && dstrLocalFund == dstrCurrentFundCode.strip().upperCase() ) ||
                 ( !dstrLocalWKN.empty()  && dstrLocalWKN  == dstrCurrentWKN.upperCase() ) ||
                 ( !dstrLocalISIN.empty() && dstrLocalISIN == dstrCurrentISIN.upperCase() ) )
            {               
				   DString dstrCurrentFundCode, dstrCurrentFundWKN, dstrCurrentFundISIN;
				   pFundDetail->getField( ifds::FundCode, dstrCurrentFundCode, idDataGroup );
				   pFundDetail->getField( ifds::FundWKN,  dstrCurrentFundWKN,  idDataGroup );
				   pFundDetail->getField( ifds::FundISIN, dstrCurrentFundISIN, idDataGroup );

               setFieldNoValidate( ifds::FundCode, dstrCurrentFundCode, idDataGroup, false, false, false, false );
				   setFieldNoValidate( ifds::FundWKN,  dstrCurrentFundWKN,  idDataGroup, false, false, false, false );
				   setFieldNoValidate( ifds::FundISIN, dstrCurrentFundISIN, idDataGroup, false, false, false, false );              

				   setFundName( idDataGroup );

               break;
            }
         }

         ++iterList;
      }                  		

		delete pFundDetailList;
		pFundDetailList = NULL;		
   }            

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY ShrFundBroker::setFundName( const BFDataGroupId &idDataGroup ) 
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("setFundName"));
	
	DString dstrFund;
	getField( ifds::FundCode, dstrFund, idDataGroup );
	dstrFund.stripAll().upperCase();

	if ( !dstrFund.empty() )
	{
		FundMasterList *pFundMasterList = NULL;
		if ( getMgmtCo ().getFundMasterList( pFundMasterList ) <= WARNING &&
			  NULL != pFundMasterList )
		{
			FundMaster *pFundMaster = NULL;
			if( pFundMasterList->getFundMaster( dstrFund, idDataGroup, pFundMaster) &&
				 NULL != pFundMaster )
			{
				DString dstrFundName;
				pFundMaster->getField( ifds::ElongName1, dstrFundName, idDataGroup );
				setFieldNoValidate( ifds::FundName, dstrFundName, idDataGroup );	
			}                		
		}
	}
		
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY ShrFundBroker::setFundBrokerName( const BFDataGroupId &idDataGroup )
{
	MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("setFundName"));
	
	DString dstrFundBroker;
	getField( ifds::FundBroker, dstrFundBroker, idDataGroup );
	dstrFundBroker.stripAll().upperCase();

   // Use View 326
   FundBrokerList *pFundBrokerList = NULL;
   if( getWorkSession().getFundBrokerList( pFundBrokerList, idDataGroup, true, dstrFundBroker ) <= WARNING &&
       NULL != pFundBrokerList )
   {
      FundBroker *pFundBroker = NULL;
      if ( pFundBrokerList->getFundBroker ( dstrFundBroker, idDataGroup, pFundBroker ) <= WARNING &&
           NULL != pFundBroker )
      {
         DString dstrBrokerFirstName, dstrBrokerLastName;
         pFundBroker->getField( ifds::FirstName, dstrBrokerFirstName, idDataGroup );
         pFundBroker->getField( ifds::Name,      dstrBrokerLastName,  idDataGroup );

         DString dstrFundBrokerName = dstrBrokerFirstName + I_( " " ) + dstrBrokerLastName;
         setFieldNoValidate( ifds::FundBrokerName, dstrFundBrokerName, idDataGroup );
      }
   }
			
   return GETCURRENTHIGHESTSEVERITY();
}

//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastcbo/ShrFundBroker.cpp-arc  $
// 
//    Rev 1.3   Nov 28 2004 14:01:32   vadeanum
// PET1117 FN08 - Shareholder Fund Broker support.
// 
//    Rev 1.2   Nov 14 2004 16:31:38   purdyech
// Sync 1.0.1.0
// 
//    Rev 1.1   Nov 11 2004 16:38:38   vadeanum
// PET1117 FN08 - Shareholder Fund Broker support - work in progress
// 
//    Rev 1.0   Nov 04 2004 17:24:58   VADEANUM
// Initial revision.
//


