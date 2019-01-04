

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
//    Copyright 2003 by International Financial.
//
//
//******************************************************************************
//
// ^FILE   : FeeParamSysSearchCriteria.cpp
// ^AUTHOR : 
// ^DATE   : Jan. 8,  2003
//
// ^CLASS    : FeeParamSysSearchCriteria
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "FeeParamSysSearchCriteria.hpp"
#include "FundCommGroupList.hpp"
#include "FundClassRules.hpp"
#include "broker.hpp"
#include "brokerlist.hpp"
#include "mgmtco.hpp"
#include "feeparamsyslist.hpp"
#include "grouplist.hpp"
#include "branchlist.hpp"
#include "agentlist.hpp"

#include "feeparamconfiglist.hpp"
#include "feeparamconfig.hpp"


#pragma  warning(disable:4355 )
namespace
{
   const I_CHAR * const CLASSNAME						   = I_( "FeeParamSysSearchCriteria" );
   const I_CHAR * const YES								   = I_( "Y" );
   const I_CHAR * const SEARCH_TYPE_ALL					= I_( "AllSys" );
   const I_CHAR * const SEARCH_TYPE_FUNDCLASS			= I_( "FundClass" );
   const I_CHAR * const SEARCH_TYPE_BROKER				= I_( "Broker" );
   const I_CHAR * const SEARCH_TYPE_FEE_CODE			   = I_( "FeeCode" );
   const I_CHAR * const SEARCH_TYPE_COMMISSION_GROUP	= I_( "CommGroup" );
   const I_CHAR * const SEARCH_TYPE_SHARE_GROUP			= I_( "ShGroup" );
   const I_CHAR * const FEE_PARAM_SYS_LIST				= I_( "FeeParamSysList" );
   const I_CHAR * const SEARCH_TYPE_BRANCH				= I_( "Branch" );
   const I_CHAR * const SEARCH_TYPE_SALES_REP			= I_( "SlsRep" );
   const I_CHAR * const SEARCH_TYPE_FEE_MODEL_FUND_CLASS = I_( "FeeModelFundClass" );
	


}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId SysFeeSearchType;
   extern CLASS_IMPORT const BFTextFieldId BrokerCode;
   extern CLASS_IMPORT const BFTextFieldId FundCode;
   extern CLASS_IMPORT const BFTextFieldId ClassCode;
   extern CLASS_IMPORT const BFTextFieldId CommGroup;
   extern CLASS_IMPORT const BFTextFieldId FeeCode;
   extern CLASS_IMPORT const BFTextFieldId ShGroup;  //shareholder group
   extern CLASS_IMPORT const BFTextFieldId BranchCode;
   extern CLASS_IMPORT const BFTextFieldId SlsrepCode;
   extern CLASS_IMPORT const BFTextFieldId RepByBranch;
   extern CLASS_IMPORT const BFTextFieldId BrokerBranch;
   extern CLASS_IMPORT const BFTextFieldId FeeModelCode;
   extern CLASS_IMPORT const BFTextFieldId SearchAll;
   extern CLASS_IMPORT const BFDateFieldId AsofDate;
   extern CLASS_IMPORT const BFTextFieldId AdvisorFeeAppl;
   extern CLASS_IMPORT const BFTextFieldId FeeCodeOverrideDescription;
}

namespace FEE_PARAM_VALIDATION_GROUP
{

   const long FEE_PARAM_SEARCH = 0x0001;

}

//-------------------------------------------------------------------
const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = {
//  Field DD Id,            State Flags,             Group Flags 
   { ifds::SysFeeSearchType,  BFCBO::NONE, FEE_PARAM_VALIDATION_GROUP::FEE_PARAM_SEARCH },
   { ifds::BrokerCode,        BFCBO::NONE, FEE_PARAM_VALIDATION_GROUP::FEE_PARAM_SEARCH },
   { ifds::FundCode,          BFCBO::NONE, FEE_PARAM_VALIDATION_GROUP::FEE_PARAM_SEARCH },
   { ifds::ClassCode,         BFCBO::NONE, FEE_PARAM_VALIDATION_GROUP::FEE_PARAM_SEARCH },
   { ifds::CommGroup,         BFCBO::NONE, FEE_PARAM_VALIDATION_GROUP::FEE_PARAM_SEARCH },
   { ifds::FeeCode,           BFCBO::NONE, FEE_PARAM_VALIDATION_GROUP::FEE_PARAM_SEARCH },
   { ifds::ShGroup,           BFCBO::NONE, FEE_PARAM_VALIDATION_GROUP::FEE_PARAM_SEARCH },
   { ifds::BranchCode,        BFCBO::NONE, FEE_PARAM_VALIDATION_GROUP::FEE_PARAM_SEARCH },
   { ifds::SlsrepCode,        BFCBO::NONE, FEE_PARAM_VALIDATION_GROUP::FEE_PARAM_SEARCH },
   { ifds::FeeModelCode,      BFCBO::NONE, FEE_PARAM_VALIDATION_GROUP::FEE_PARAM_SEARCH },
   { ifds::SearchAll,         BFCBO::NONE, FEE_PARAM_VALIDATION_GROUP::FEE_PARAM_SEARCH },
   { ifds::AsofDate,          BFCBO::NONE, FEE_PARAM_VALIDATION_GROUP::FEE_PARAM_SEARCH },
};

static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );


const BFCBO::CLASS_OBJECT_INFO classObjectInfo[] = {
//  Object Label,            State Flags,           Group Flags 
   {  I_(""),        BFCBO::REQUIRED,         0}
};

static const int NUM_OBJECTS = sizeof( classObjectInfo ) / sizeof( BFCBO::CLASS_OBJECT_INFO );


namespace CND
{  // Conditions used
   extern const long ERR_FIELD_MANDATORY_F4_FOR_SEARCH;
   extern const long ERR_FIELD_INVALID_F4_FOR_SEARCH;
}

//****************************************************************************
FeeParamSysSearchCriteria::FeeParamSysSearchCriteria( BFAbstractCBO &parent )
: MFCanBFCbo( parent )
,  m_FundClassRules(*this)
{
   TRACE_CONSTRUCTOR( CLASSNAME , NULL_STRING );
    registerMemberData( NUM_FIELDS,
                       (const CLASS_FIELD_INFO *)&classFieldInfo,
                       0,
							  NULL );
}

//****************************************************************************
FeeParamSysSearchCriteria::~FeeParamSysSearchCriteria()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}     

//****************************************************************************
SEVERITY FeeParamSysSearchCriteria::init( const BFDataGroupId& idDataGroup,
   const DString& dstrTrack /*= I_("N")*/, 
   const DString& dstrPageName /*= NULL_STRING*/)
{
   MAKEFRAME2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("init") );
   setFieldNoValidate(ifds::SysFeeSearchType,SEARCH_TYPE_FEE_CODE,idDataGroup,false,true,true );
//   setFieldNoValidate(ifds::AsofDate,I_("12319999"),idDataGroup,false,true,false, false);
	//FundCommGroupList* pFundCommGroupList = NULL;
	//if(getMgmtCo().getFundCommGroupList( pFundCommGroupList ) <= WARNING )
	//{
	//	DString dstrSubList;
	//	pFundCommGroupList->getCommGroupSubstitute(dstrSubList);
	//	setFieldAllSubstituteValues( ifds::CommGroup,idDataGroup, dstrSubList );	
	//}
	
   m_FundClassRules.init( ifds::NullFieldId,ifds::FundCode,ifds::ClassCode,ifds::NullFieldId );
	setFieldNoValidate(ifds::SysFeeSearchType,SEARCH_TYPE_ALL,idDataGroup,false);

   GroupList*  pGroupList= NULL;
   DString dstSubstList = NULL_STRING;

   if( getMgmtCo().getGroupList( pGroupList )  <= WARNING )
   {
      pGroupList->getGroupSubstList( dstSubstList, true);
      dstSubstList.upperCase();
      setFieldAllSubstituteValues( ifds::ShGroup, idDataGroup, dstSubstList );
   }
    _salesRepByBranch = NULL_STRING;

    //Change description from Dealer Service Fee(94) to Advisor Fee.
    DString dstrAdvisorFeeAppl, dstrFeeCodeSubList, newDescription;
    BFProperties *pBFPropertiesFeeCode =  getFieldProperties(ifds::FeeCode, idDataGroup);

    getWorkSession().getOption(ifds::AdvisorFeeAppl, dstrAdvisorFeeAppl, idDataGroup, false);
      
    if (pBFPropertiesFeeCode && dstrAdvisorFeeAppl.stripAll().upperCase() == YES)
    {
        pBFPropertiesFeeCode->getAllSubstituteValues(dstrFeeCodeSubList);

        newDescription = I_("94=94 - ") + DSTCommonFunctions::getDescription(I_("94"), ifds::FeeCodeOverrideDescription) + I_(";");

        DString tmpSubList(dstrFeeCodeSubList);
        int nPos = dstrFeeCodeSubList.find(I_("94="));

        if (nPos != -1)
        {
            dstrFeeCodeSubList = tmpSubList.left(nPos) + newDescription;
            tmpSubList = tmpSubList.right(tmpSubList.length() - nPos);

            int rnPos = tmpSubList.find(';');

            if (rnPos != -1)
            {
                dstrFeeCodeSubList = dstrFeeCodeSubList + tmpSubList.right(tmpSubList.length() - rnPos - 1);
            }

            setFieldAllSubstituteValues(ifds::FeeCode, idDataGroup, dstrFeeCodeSubList);
        }
    }

	return(GETCURRENTHIGHESTSEVERITY());
}

//***********************************************************************************
SEVERITY FeeParamSysSearchCriteria::doValidateFields( const BFFieldId& idField, 
																	  const DString& strValue, const BFDataGroupId& idDataGroup)

{
   MAKEFRAME2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("doValidateFields") );
	if( idField == ifds::FundCode )
	{
		m_FundClassRules.validateFundCode( idDataGroup );
	}
	else if( idField == ifds::ClassCode)
	{
		m_FundClassRules.validateClassCode( idDataGroup );	
	}
	else if( idField == ifds::BrokerCode )
	{
		validateBrokerCode( idDataGroup);	
	}
	else if ( idField == ifds::BranchCode )
	{
		validateBranchCode( idDataGroup );
	}
	else if ( idField == ifds::SlsrepCode )
	{
		validateSalesRepCode( idDataGroup );
	}

	return(GETCURRENTHIGHESTSEVERITY());

}
//**********************************************************************************
SEVERITY FeeParamSysSearchCriteria::doApplyRelatedChanges( const BFFieldId& idField, 
																			 const BFDataGroupId& idDataGroup )
{
   MAKEFRAME2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("doApplyRelatedChanges") );
	if( idField == ifds::SysFeeSearchType )
	{
	
		SearchTypeRelatedChanges( idDataGroup );
	
	}
   else if ( idField == ifds::BrokerCode )
	{
		doBrokerCodeRelatedChanges( idDataGroup );
	}
   else if ( idField == ifds::FeeCode)
	{
		doFeeCodeRelatedChanges( idDataGroup );
	}


	return(GETCURRENTHIGHESTSEVERITY());
}

//***************************************************************************************
SEVERITY FeeParamSysSearchCriteria::validateBrokerCode(const BFDataGroupId& idDataGroup)
{

   MAKEFRAME2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("validateBrokerCode") );
   DString dstrSearchType;
   getField(ifds::SysFeeSearchType,dstrSearchType,idDataGroup,false);
   if( SEARCH_TYPE_BROKER != dstrSearchType.strip() &&
	   SEARCH_TYPE_BRANCH != dstrSearchType.strip() &&
	   SEARCH_TYPE_SALES_REP != dstrSearchType.strip() ) 
   {
	   return NO_CONDITION;
   }

   BrokerList *pBrokerList;
   Broker *pBroker = NULL;
   DString BrokerField = I_( "Broker Code" );  
	DString dstrBrokerCode;
	getField(ifds::BrokerCode,dstrBrokerCode,idDataGroup,false );
	dstrBrokerCode.strip();	
	
   if( dstrBrokerCode == NULL_STRING )
   {
      ADDCONDITIONFROMFILEIDI( CND::ERR_FIELD_MANDATORY_F4_FOR_SEARCH, DString(I_("FIELDNAME=")) + BrokerField );
   }
   else
   {
      SEVERITY sevRtn1,sevRtn2;
      DString dstrVolSettleType;
      sevRtn1= getWorkSession().getBrokerList(pBrokerList);
      if( pBrokerList )
         sevRtn2 = pBrokerList->getBroker(dstrBrokerCode, pBroker);

      sevRtn1 = sevRtn1 >  sevRtn2?sevRtn1:sevRtn2;        
      if( sevRtn1 > WARNING || pBroker == NULL )
      {
         ADDCONDITIONFROMFILEIDI( CND::ERR_FIELD_INVALID_F4_FOR_SEARCH, DString(I_("FIELDNAME=")) + BrokerField );
      }
   }

	return(GETCURRENTHIGHESTSEVERITY());
}

//***************************************************************************************
SEVERITY FeeParamSysSearchCriteria::validateBranchCode(const BFDataGroupId& idDataGroup)
{

   MAKEFRAME2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("validateBrokerCode") );
   DString dstrSearchType;
   getField(ifds::SysFeeSearchType,dstrSearchType,idDataGroup,false);
   if( SEARCH_TYPE_BRANCH != dstrSearchType.strip() &&
	   SEARCH_TYPE_SALES_REP != dstrSearchType.strip()) 
   {
	   return NO_CONDITION;
   }

	DString BranchField = I_( "Branch Code" );  
	DString dstrBranchCode, brokerCode;
	getField(ifds::BranchCode,dstrBranchCode,idDataGroup,false );
	dstrBranchCode.strip();	
	
   if( dstrBranchCode == NULL_STRING )
   {
      ADDCONDITIONFROMFILEIDI( CND::ERR_FIELD_MANDATORY_F4_FOR_SEARCH, DString(I_("FIELDNAME=")) + BranchField );
   }
   else
   {
	  if( validateBrokerCode(idDataGroup ) <= WARNING )
	  {
		 BranchList branchList( *this );
		 getField( ifds::BrokerCode, brokerCode, idDataGroup );
		 //checks for the validity of the branch code. by making a view call
		 if( branchList.init( brokerCode, dstrBranchCode ) <= WARNING )
		 {
			return(NO_CONDITION);
		 }
		 else
		 {
			return(GETCURRENTHIGHESTSEVERITY());
		 }
	  }
	}

	return(GETCURRENTHIGHESTSEVERITY());
}

//***************************************************************************************
SEVERITY FeeParamSysSearchCriteria::validateSalesRepCode(const BFDataGroupId& idDataGroup)
{

   MAKEFRAME2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("validateSalesRepCode") );
   DString dstrSearchType;
   getField(ifds::SysFeeSearchType,dstrSearchType,idDataGroup,false);
   if( SEARCH_TYPE_SALES_REP != dstrSearchType.strip()) 
   {
	   return NO_CONDITION;
   }

	DString SalesRepField = I_( "SalesRep Code" );  
	DString dstrBranchCode, dstrBrokerCode,dstrSalesRepCode;
	getField(ifds::SlsrepCode,dstrSalesRepCode,idDataGroup,false );
	dstrSalesRepCode.strip();	
	
   if( dstrSalesRepCode == NULL_STRING )
   {
      ADDCONDITIONFROMFILEIDI( CND::ERR_FIELD_MANDATORY_F4_FOR_SEARCH, DString(I_("FIELDNAME=")) + SalesRepField );
   }
   else
   {
	  if( validateBranchCode(idDataGroup ) <= WARNING )
	  {
		    AgentList agentList( *this );

		   if( agentList.init( dstrBrokerCode, dstrBranchCode, dstrSalesRepCode) <= WARNING )
		   {
			   return NO_CONDITION;
		   }
		   else
		   {
			  return(GETCURRENTHIGHESTSEVERITY());
		   }
	  }
	}

	return(GETCURRENTHIGHESTSEVERITY());

}
//****************************************************************************************
void FeeParamSysSearchCriteria::SearchTypeRelatedChanges(const BFDataGroupId& idDataGroup )
{

   BFFieldId lFieldIds1[10] = { ifds::NullFieldId, ifds::NullFieldId, ifds::NullFieldId, 
		ifds::NullFieldId, ifds::NullFieldId, ifds::NullFieldId,ifds::NullFieldId,ifds::NullFieldId,ifds::NullFieldId,ifds::NullFieldId};

   BFFieldId lFieldIds2[9] = { ifds::NullFieldId, ifds::NullFieldId, ifds::NullFieldId, 
		ifds::NullFieldId, ifds::NullFieldId, ifds::NullFieldId, ifds::NullFieldId,ifds::NullFieldId,ifds::NullFieldId};
	DString dstrSearchType;
	getField(ifds::SysFeeSearchType,dstrSearchType,idDataGroup,false);
	if( dstrSearchType == SEARCH_TYPE_ALL )
	{
		lFieldIds1[0] = ifds::BrokerCode;
		lFieldIds1[1] = ifds::FundCode;	
		lFieldIds1[2] = ifds::ClassCode;
		lFieldIds1[3] = ifds::CommGroup;
		lFieldIds1[4] = ifds::FeeCode;
		lFieldIds1[5] = ifds::ShGroup;
		lFieldIds1[6] = ifds::BranchCode;
		lFieldIds1[7] = ifds::SlsrepCode;
      lFieldIds1[8] = ifds::FeeModelCode;

		clearFieldsValue( lFieldIds1, idDataGroup);
		setFieldsAsRequired( lFieldIds1,idDataGroup,false );
	}
	else if(	dstrSearchType == SEARCH_TYPE_FUNDCLASS	)
	{
		lFieldIds1[0] = ifds::FundCode;	
		lFieldIds1[1] = ifds::ClassCode;

		lFieldIds2[0] = ifds::CommGroup;
		lFieldIds2[1] = ifds::FeeCode;
		lFieldIds2[2] = ifds::ShGroup;
		lFieldIds2[3] = ifds::BrokerCode;
		lFieldIds2[4] = ifds::BranchCode;
		lFieldIds2[5] = ifds::SlsrepCode;
      lFieldIds2[6] = ifds::FeeModelCode;

		clearFieldsValue( lFieldIds2, idDataGroup);	
		clearFieldsValue( lFieldIds1, idDataGroup);
		setFieldsAsRequired( lFieldIds1,idDataGroup,true );
		setFieldsAsRequired( lFieldIds2,idDataGroup,false );
	}
	else if(	dstrSearchType == SEARCH_TYPE_BROKER	)
	{
		lFieldIds1[0] = ifds::BrokerCode;

		lFieldIds2[0] = ifds::FundCode;	
		lFieldIds2[1] = ifds::ClassCode;
		lFieldIds2[2] = ifds::CommGroup;
		lFieldIds2[3] = ifds::FeeCode;
		lFieldIds2[4] = ifds::ShGroup;
		lFieldIds2[5] = ifds::BranchCode;
		lFieldIds2[6] = ifds::SlsrepCode;
      lFieldIds2[7] = ifds::FeeModelCode;

		clearFieldsValue( lFieldIds2, idDataGroup);	
		clearFieldsValue( lFieldIds1, idDataGroup);
		setFieldsAsRequired( lFieldIds1,idDataGroup,true );
		setFieldsAsRequired( lFieldIds2,idDataGroup,false );
	}
	else if(	dstrSearchType == SEARCH_TYPE_FEE_CODE	)
	{
		lFieldIds1[0] = ifds::FeeCode;

		lFieldIds2[0] = ifds::FundCode;	
		lFieldIds2[1] = ifds::ClassCode;
		lFieldIds2[2] = ifds::CommGroup;
		lFieldIds2[3] = ifds::BrokerCode;
		lFieldIds2[4] = ifds::ShGroup;
		lFieldIds2[5] = ifds::BranchCode;
		lFieldIds2[6] = ifds::SlsrepCode;
      lFieldIds2[7] = ifds::FeeModelCode;

		clearFieldsValue( lFieldIds2, idDataGroup);	
		clearFieldsValue( lFieldIds1, idDataGroup);
		setFieldsAsRequired( lFieldIds1,idDataGroup,true );
		setFieldsAsRequired( lFieldIds2,idDataGroup,false );
	}
	else if(	dstrSearchType == SEARCH_TYPE_COMMISSION_GROUP	)
	{
		lFieldIds1[0] = ifds::CommGroup;
		lFieldIds1[1] = ifds::FeeCode;

		lFieldIds2[0] = ifds::FundCode;	
		lFieldIds2[1] = ifds::ClassCode;
		lFieldIds2[2] = ifds::BrokerCode;
		lFieldIds2[3] = ifds::ShGroup;
		lFieldIds2[4] = ifds::BranchCode;
		lFieldIds2[5] = ifds::SlsrepCode;
      lFieldIds2[6] = ifds::FeeModelCode;

		clearFieldsValue( lFieldIds2, idDataGroup);	
		clearFieldsValue( lFieldIds1, idDataGroup);
		setFieldsAsRequired( lFieldIds1,idDataGroup,true );
		setFieldsAsRequired( lFieldIds2,idDataGroup,false );
	}
	else if(	dstrSearchType == SEARCH_TYPE_SHARE_GROUP	)
	{
		lFieldIds1[0] = ifds::ShGroup;

		lFieldIds2[0] = ifds::FundCode;	
		lFieldIds2[1] = ifds::ClassCode;
		lFieldIds2[2] = ifds::FeeCode;
		lFieldIds2[3] = ifds::BrokerCode;
		lFieldIds2[4] = ifds::CommGroup;
		lFieldIds2[5] = ifds::BranchCode;
		lFieldIds2[6] = ifds::SlsrepCode;
        lFieldIds2[7] = ifds::FeeModelCode;

		clearFieldsValue( lFieldIds2, idDataGroup);	
		clearFieldsValue( lFieldIds1, idDataGroup);
		setFieldsAsRequired( lFieldIds1,idDataGroup,true );
		setFieldsAsRequired( lFieldIds2,idDataGroup,false );
	}
	else if(	dstrSearchType == SEARCH_TYPE_BRANCH	)
	{
		lFieldIds1[0] = ifds::BrokerCode;
		lFieldIds1[1] = ifds::BranchCode;

		lFieldIds2[0] = ifds::FundCode;	
		lFieldIds2[1] = ifds::ClassCode;
		lFieldIds2[2] = ifds::CommGroup;
		lFieldIds2[3] = ifds::FeeCode;
		lFieldIds2[4] = ifds::ShGroup;
		lFieldIds2[5] = ifds::SlsrepCode;
        lFieldIds2[6] = ifds::FeeModelCode;

		clearFieldsValue( lFieldIds2, idDataGroup);	
		clearFieldsValue( lFieldIds1, idDataGroup);

		setFieldsAsRequired( lFieldIds1,idDataGroup,true );
		setFieldsAsRequired( lFieldIds2,idDataGroup,false );
	}
	else if(	dstrSearchType == SEARCH_TYPE_SALES_REP	)
	{
		lFieldIds1[0] = ifds::BrokerCode;
		lFieldIds1[1] = ifds::BranchCode;
		lFieldIds1[2] = ifds::SlsrepCode;

		lFieldIds2[0] = ifds::FundCode;	
		lFieldIds2[1] = ifds::ClassCode;
		lFieldIds2[2] = ifds::CommGroup;
		lFieldIds2[3] = ifds::FeeCode;
		lFieldIds2[4] = ifds::ShGroup;
      lFieldIds2[5] = ifds::FeeModelCode;

		clearFieldsValue( lFieldIds2, idDataGroup);	
		clearFieldsValue( lFieldIds1, idDataGroup);	
		setFieldsAsRequired( lFieldIds1,idDataGroup,true );
		setFieldsAsRequired( lFieldIds2,idDataGroup,false );
	}
   else 	if( dstrSearchType == SEARCH_TYPE_FEE_MODEL_FUND_CLASS )
	{
      lFieldIds1[0] = ifds::FeeModelCode;
		
      lFieldIds2[0] = ifds::BrokerCode;
      lFieldIds2[1] = ifds::FundCode;	
		lFieldIds2[2] = ifds::ClassCode;
		lFieldIds2[3] = ifds::CommGroup;
		lFieldIds2[4] = ifds::FeeCode;
		lFieldIds2[5] = ifds::ShGroup;
		lFieldIds2[6] = ifds::BranchCode;
		lFieldIds2[7] = ifds::SlsrepCode;

		clearFieldsValue( lFieldIds2, idDataGroup);	
		clearFieldsValue( lFieldIds1, idDataGroup);	
		setFieldsAsRequired( lFieldIds1,idDataGroup,true );
		setFieldsAsRequired( lFieldIds2,idDataGroup,false );
	}


}
//*********************************************************************************
void FeeParamSysSearchCriteria::setFieldsAsRequired( const BFFieldId idField[], const BFDataGroupId& idDataGroup,bool bReqired )
{
   int i = 0;  
   while( idField[i] != ifds::NullFieldId )
   {
      setFieldRequired( idField[i],idDataGroup,bReqired );
		setValidFlag(  idField[i], idDataGroup, false);



      i++;
   }
}
//***********************************************************************************
void FeeParamSysSearchCriteria::clearFieldsValue( const BFFieldId idField[], const BFDataGroupId& idDataGroup)
{
   int i = 0;  
   while( idField[i] != ifds::NullFieldId )
   {
      setFieldNoValidate( idField[i],NULL_STRING,idDataGroup,false,true,true );
      i++;
   }
}


//****************************************************************************************
SEVERITY FeeParamSysSearchCriteria::GetFeeParamSysList(FeeParamSysList*& pFeeParamSysList, 
												 const BFDataGroupId& idDataGroup,
												 bool bInq,bool bRemObj,
												 bool bCreateNew,bool bDel)
																		 
{

   MAKEFRAME2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("GetFeeParamSysList") );
   if( bRemObj )
   {
      setObject( NULL, FEE_PARAM_SYS_LIST, OBJ_ACTIVITY_NONE, BF::HOST ); 

   }
   pFeeParamSysList = dynamic_cast<FeeParamSysList*>( BFCBO::getObject( FEE_PARAM_SYS_LIST, idDataGroup ) );
   BFDataGroupId idWorkingDataGroup = idDataGroup;
   if( !pFeeParamSysList )
   {
	  if (bDel)
	  {
		 pFeeParamSysList = NULL;
	  }

      if( bInq )
      {

         DString dstrSeachType;
         getField(ifds::SysFeeSearchType,dstrSeachType,idDataGroup,false);
         dstrSeachType.strip();

         pFeeParamSysList = new FeeParamSysList( *this );
         pFeeParamSysList->init(idDataGroup );
         //if we inquire the database the group id should be the host
         idWorkingDataGroup = BF::HOST;
      }
	  if (bCreateNew )
	  {
		 pFeeParamSysList = new FeeParamSysList( *this );		
	  }
      if( pFeeParamSysList )
      {
         if( GETCURRENTHIGHESTSEVERITY() <= WARNING )
         {
            //TODO: should be idWorkingDataGroup???
            setObject( pFeeParamSysList, FEE_PARAM_SYS_LIST, OBJ_ACTIVITY_NONE, BF::HOST ); 
            
         }
         else
         {
            delete pFeeParamSysList;
            pFeeParamSysList = NULL;
         }
      }
   }
	return(GETCURRENTHIGHESTSEVERITY());

}
//*****************************************************************************************
void FeeParamSysSearchCriteria::clearUpdateFlags(const BFDataGroupId& idDataGroup)
{

   clearUpdatedFlags( idDataGroup );
   setAllFieldsValid( idDataGroup );


}
//*****************************************************************************************
void FeeParamSysSearchCriteria::doBrokerCodeRelatedChanges(const BFDataGroupId& idDataGroup)
{
	 DString dstrSearchType;
	 getField(ifds::SysFeeSearchType,dstrSearchType,idDataGroup,false);

	 if( (SEARCH_TYPE_SALES_REP == dstrSearchType.strip() || SEARCH_TYPE_BRANCH == dstrSearchType.strip()) && !slsRepByBranch (idDataGroup) ) 
	 {

		 DString brokerBranch, branchCode=NULL_STRING;

		 if( getWorkSession().getOption( ifds::BrokerBranch, brokerBranch, idDataGroup, false ) <= WARNING )
		 {
			if( brokerBranch == YES )
			{
				DString dstrBrokerCode;
				getField( ifds::BrokerCode, dstrBrokerCode, idDataGroup );

			    branchCode = dstrBrokerCode;
			}
			else
			{
			    branchCode = I_( "0000" );
			}
		 }
//         setFieldRequired( ifds::BranchCode,idDataGroup,false );
		 setFieldNoValidate( ifds::BranchCode, branchCode, idDataGroup, false, false, true );
		 setFieldNoValidate( ifds::SlsrepCode, NULL_STRING, idDataGroup, false, false, true );
//		 setFieldReadOnly(ifds::BranchCode, idDataGroup,true); 

	 }
}


void FeeParamSysSearchCriteria::doFeeCodeRelatedChanges(const BFDataGroupId& idDataGroup)
{
	 DString dstrFeeCode;
	 getField(ifds::FeeCode, dstrFeeCode,idDataGroup,false);

	FeeParamConfigList* pFeeParamConfigList = NULL;
   FeeParamConfig* pFeeParamConfig = NULL;
   if (getMgmtCo().getFeeParamConfigList(pFeeParamConfigList) <= WARNING)
   {
      pFeeParamConfigList->getFeeParamConfig(pFeeParamConfig, dstrFeeCode, idDataGroup);
   }
	
   if(pFeeParamConfig)
   {
      DString dstrGroupType = NULL_STRING;
		pFeeParamConfig->getFundGroupType(dstrGroupType);

		DString dstrSubList = I_("NA=;");
		if (dstrGroupType != NULL_STRING)
		{
			FundCommGroupList* pFundCommGroupListP = NULL;

			if(getMgmtCo().getFundCommGroupList(dstrGroupType.strip().upperCase(), pFundCommGroupListP ) <= WARNING )
			{
				pFundCommGroupListP->getCommGroupSubstitute(dstrSubList);
			}

		}
		setFieldAllSubstituteValues( ifds::CommGroup,idDataGroup, dstrSubList );
   }
}
//*****************************************************************************************
bool FeeParamSysSearchCriteria::slsRepByBranch ( const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "slsRepByBranch" ) );

  
   if( _salesRepByBranch == NULL_STRING )
   {
      getWorkSession().getOption( ifds::RepByBranch, _salesRepByBranch, idDataGroup, false );
   }

   return( _salesRepByBranch == YES );
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/FeeParamSysSearchCriteria.cpp-arc  $
// 
//    Rev 1.18   Nov 14 2004 14:40:26   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.17   Sep 22 2004 16:44:20   YINGBAOL
// PET1117  FN05: change SEARCH_TYPE_ALL from "All" to "AllSys"
// 
//    Rev 1.16   Jun 09 2003 11:45:46   linmay
// BranchCode change to updatable.
// 
//    Rev 1.15   Jun 05 2003 11:21:28   linmay
// change value of SEARCH_TYPE_SALES_REP to SlsRep;
// 
//    Rev 1.14   May 27 2003 18:29:38   popescu
// due to several memory leaks found in some list getters at the DSTCWorkSession level caused by copy/paste, I've created a common template function to retrieve the dependent objects
// 
//    Rev 1.13   May 02 2003 15:02:08   linmay
// added logic for new search option: BranchCode, SalesRepCode
// 
//    Rev 1.12   Apr 04 2003 16:58:50   PURDYECH
// Sync 1.9.1.0 back to trunk
// 
//    Rev 1.11   Mar 25 2003 14:45:56   linmay
// fix bug
// 
//    Rev 1.10   Mar 21 2003 18:09:44   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.9   Mar 10 2003 14:49:08   linmay
// modified init
// 
//    Rev 1.8   Jan 30 2003 15:36:08   YINGBAOL
// Broker code is not required when search FundClass
// 
//    Rev 1.7   Jan 23 2003 18:07:50   YINGBAOL
// change SearchTypeRelatedChanges(const BFDataGroupId& idDataGroup ) to cover all cases
// 
//    Rev 1.6   Jan 22 2003 16:25:54   YINGBAOL
// change clearUpdateFlags
// 
//    Rev 1.5   Jan 21 2003 16:11:52   YINGBAOL
// change datagroup ID
// 
//    Rev 1.4   Jan 21 2003 11:16:20   YINGBAOL
// sync. FundClassRules change
// 
//    Rev 1.2   Jan 16 2003 15:33:36   YINGBAOL
// add classfieldinfo etc. 
// 
//    Rev 1.1   Jan 09 2003 15:44:40   YINGBAOL
// change pointer to instance
// 
//    Rev 1.0   Jan 09 2003 10:05:38   YINGBAOL
// Initial Revision
// 

 *
 * 
 */









