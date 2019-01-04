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
//******************************************************************************
//
// ^FILE   : FundClassProcess.cpp
// ^AUTHOR : 
// ^DATE   : 04/17/2000
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : FundClassProcess
//    This class manages the management company and profile selection.
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include "stdafx.h"
#include <ifastdataimpl\dse_dstc0069_vw.hpp>
#include <ifastdataimpl\dse_dstc0056_req.hpp>
#include <ifastdataimpl\dse_dstc0098_vw.hpp>
#include "fundclassprocess.hpp"
#include "fundclassprocessincludes.h"
#include <ifastcbo\funddetaillist.hpp>
#include <ifastcbo\funddetaillistlite.hpp>
#include <ifastcbo\fundmaster.hpp>
#include <ifastcbo\fundmasterlist.hpp>
#include <ifastcbo\groupfundlist.hpp>
#include <ifastcbo\grouplist.hpp>
#include <ifastcbo\group.hpp>
#include <ifastcbo\mfaccount.hpp>
#include <ifastcbo\mgmtco.hpp>
#include <ifastcbo\shareholder.hpp>
extern IFASTBP_LINKAGE const I_CHAR* CMD_GUI_FUNDCLASS;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_FUNDCLASS;
#include <bfproc\concreteprocesscreator.hpp>
static ConcreteProcessCreator< FundClassProcess > processCreator( CMD_BPROC_FUNDCLASS );

namespace
{
   // Trace literals
   const I_CHAR * CLASSNAME             = I_( "FundClassProcess" );
   const I_CHAR * const PERFORMSEARCH       = I_( "performSearch" );
   const I_CHAR * GROUP_CODE              = I_( "GroupCode" );
   const I_CHAR * YES                        = I_("Y");

}

namespace CND
{
   extern CLASS_IMPORT const long BP_ERR_UNKNOWN_EXCEPTION;
   extern CLASS_IMPORT const long BP_ERR_INVALID_METHOD_CALL;
}

namespace FUNDCLASSLIST
{
   const I_CHAR * const FUND_CODE          = I_( "FundCode" );
   const I_CHAR * const CLASS_CODE         = I_( "ClassCode" );
   const I_CHAR * const FUND_NUMBER        = I_( "FundNumber" );
   const I_CHAR * const FUND_ISIN          = I_( "FundISIN" );
   const I_CHAR * const FUND_WKN           = I_( "FundWKN" );
   const I_CHAR * const FUND_LFC           = I_( "FundLFC" );
   const I_CHAR * const CUSIP              = I_( "CUSIP" );
   const I_CHAR * const GROUP_CODE         = I_( "GroupCode" );
   const I_CHAR * const SHR_NUM          = I_( "ShrNum" );
   const I_CHAR * const ACCT_NUM           = I_( "AccountNum" );
   const I_CHAR * const ONLY_ESOP_ELIGIBLE = I_( "OnlyESopEligible" );
   const I_CHAR * const MANAGEMENTFEE = I_( "ManagementFee" );
   const I_CHAR * const MANAGEMENTFEE_REBATE = I_( "ManagementFeeRebate" );

}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId AcctGroup;
   extern CLASS_IMPORT const BFTextFieldId ESoPEligible;
   extern CLASS_IMPORT const BFTextFieldId Name;
   extern CLASS_IMPORT const BFTextFieldId SearchFund;
   extern CLASS_IMPORT const BFTextFieldId CUSIP;
   extern CLASS_IMPORT const BFTextFieldId TDCC;
   extern CLASS_IMPORT const BFTextFieldId Valoren;
   extern CLASS_IMPORT const BFTextFieldId FundIDList;
}

namespace FUND_ID_CODE
{
 const I_CHAR * const VALOREN	=	I_("Valoren");
 const I_CHAR * const TDCC		=	I_("TDCC");
 const I_CHAR * const CUSIP		=	I_("CUSIP");
}


//******************************************************************************
//              Public Methods
//******************************************************************************

FundClassProcess::FundClassProcess ( GenericInterfaceContainer* pGIC, 
   GenericInterface* pGIParent, const Command& rCommand)
: AbstractProcess( pGIC, pGIParent, rCommand )
, m_pGroupFundList( NULL )
, m_pFundDetailList( NULL )
, m_pFundDetailListLite( NULL )
, m_rpChildGI( NULL )
, m_dstrBaseFilter( NULL_STRING )
, m_dstrFundCode( NULL_STRING )
, m_dstrFundNumber( NULL_STRING )
, m_dstrFundClass( NULL_STRING )
, m_strOnlyESoPEligible( NULL_STRING )
, m_strManagementFee( NULL_STRING )
, m_strManagementFeeRebate( NULL_STRING )
, m_dstrSearchType( NULL_STRING )
, m_dstrSearchFund( NULL_STRING )
, m_dstrGroupCode( NULL_STRING )
, m_fundCategory (NULL_STRING) //used to filter the fund entries based on fund type
, m_propSearchFundType(NULL)
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   addContainer( IFASTBP_PROC::FUNDDETAIL_LIST, true );
   addFieldDetails( ifds::ElongName1     , BF::NullContainerId, SUBCLASS_PROCESS );
   addFieldDetails( ifds::FLongName      , BF::NullContainerId, SUBCLASS_PROCESS );
   addFieldDetails( ifds::FundType       , BF::NullContainerId, SUBCLASS_PROCESS );
   addFieldDetails( ifds::FundCategory   , BF::NullContainerId, SUBCLASS_PROCESS );
   addFieldDetails( ifds::FundCode       , IFASTBP_PROC::FUNDDETAIL_LIST );
   addFieldDetails( ifds::ClassCode      , IFASTBP_PROC::FUNDDETAIL_LIST );
   addFieldDetails( ifds::Baycom         , IFASTBP_PROC::FUNDDETAIL_LIST );
   addFieldDetails( ifds::FundWKN        , IFASTBP_PROC::FUNDDETAIL_LIST );
   addFieldDetails( ifds::FundISIN       , IFASTBP_PROC::FUNDDETAIL_LIST );
   addFieldDetails( ifds::TDCC			 , IFASTBP_PROC::FUNDDETAIL_LIST );
   addFieldDetails( ifds::Valoren		 , IFASTBP_PROC::FUNDDETAIL_LIST );
   addFieldDetails( ifds::CUSIP			 , IFASTBP_PROC::FUNDDETAIL_LIST );
   addFieldDetails( ifds::FundLFC       , IFASTBP_PROC::FUNDDETAIL_LIST );
   addFieldDetails( ifds::RolloverExchangeAppl			, IFASTBP_PROC::FUNDDETAIL_LIST );
   addFieldDetails( ifds::RolloverExchangeToFundClass   , IFASTBP_PROC::FUNDDETAIL_LIST );
   addFieldDetails( ifds::RolloverExchangeAmountType    , IFASTBP_PROC::FUNDDETAIL_LIST );
   addFieldDetails( ifds::GrossOrNet			           , IFASTBP_PROC::FUNDDETAIL_LIST );

   addFieldDetails( ifds::SearchFundType , BF::NullContainerId, SUBCLASS_PROCESS );
   addFieldDetails( ifds::SearchFund     , BF::NullContainerId, SUBCLASS_PROCESS );
   addFieldDetails( ifds::ClassCode      , BF::NullContainerId, SUBCLASS_PROCESS );
   addFieldDetails( ifds::FundName       , BF::NullContainerId, SUBCLASS_PROCESS );
   addFieldDetails( ifds::Name           , BF::NullContainerId, SUBCLASS_PROCESS );
   addFieldDetails( FUNDCLASS::USE_GROUPFUNDLIST,        BF::NullContainerId, SUBCLASS_PROCESS );
   addFieldDetails( FUNDCLASS::IS_IN_GROUPFUNDLIST,      BF::NullContainerId, SUBCLASS_PROCESS );
}

//******************************************************************************

FundClassProcess::~FundClassProcess()
{
   TRACE_DESTRUCTOR( CLASSNAME );
   delete m_pFundDetailList;
   delete m_pFundDetailListLite;
   if (!m_propSearchFundType )
   {
      delete m_propSearchFundType;
      m_propSearchFundType = NULL;
   }
}

//******************************************************************************
//              Protected Methods
//******************************************************************************

SEVERITY FundClassProcess::doInit()
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, DOINIT );
   SEVERITY sevRtn = SEVERE_ERROR;
   try
   {
      DSTCWorkSession *dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());

      // Check for a shareholder number, if a shareholder number exists then filter 
      // the fund list for the specific shareholder otherwise the complete fund list will be
      // returned.

      DString dstrShareholder, dstrAcctNum;        
      getParameter ( FUNDCLASSLIST::SHR_NUM, dstrShareholder );     
      getParameter ( FUNDCLASSLIST::ACCT_NUM, dstrAcctNum );   
      getParameter ( FUNDCLASSLIST::ONLY_ESOP_ELIGIBLE, m_strOnlyESoPEligible );  
      m_strOnlyESoPEligible.strip();


      getParameter ( FUNDCLASSLIST::FUND_CODE, m_dstrFundCode);
      getParameter ( FUNDCLASSLIST::CLASS_CODE, m_dstrFundClass);
      getParameter ( FUNDCLASSLIST::FUND_NUMBER, m_dstrFundNumber);

      getParameter ( FUNDCLASSLIST::MANAGEMENTFEE, m_strManagementFee);
      getParameter ( FUNDCLASSLIST::MANAGEMENTFEE_REBATE, m_strManagementFeeRebate);

      getParameter ( I_("FundCategory"), m_fundCategory);

      // Group List
      if( !dstrAcctNum.strip().stripLeading('0').empty() )
      {
         MFAccount *mfAccount;
         sevRtn = dstcWorkSession->getMFAccount( getDataGroupId(), dstrAcctNum, mfAccount );
         mfAccount->getField( ifds::AcctGroup, m_dstrGroupCode, getDataGroupId());
      }
      else if( !dstrShareholder.strip().stripLeading('0').empty() )
      {
         Shareholder *pShareholder;
         sevRtn = dstcWorkSession->getShareholder ( getDataGroupId(), dstrShareholder, pShareholder );
         pShareholder->getField( ifds::GroupCode, m_dstrGroupCode, getDataGroupId() );
      }

		m_dstrGroupCode = NULL_STRING; // this is to	temporary disable the display by Fund Group due to the volumn issue until a solution is available
      GroupList* pGroupList;
      sevRtn = SEVERE_ERROR;
      if( !m_dstrGroupCode.strip().empty() )
      {
         if( dstcWorkSession->getMgmtCo().getGroupList( pGroupList ) <= WARNING )
         {
            BFObjIter glIter( *pGroupList, getDataGroupId() );
            if( glIter.positionByKey( m_dstrGroupCode ) )
            {
               Group* pGroup;
               if( pGroup = dynamic_cast<Group*>( glIter.getObject() ) )
               {
                  sevRtn = pGroup->getGroupFundList( m_pGroupFundList );
               }
            }
         }
      }

      DString dstrFilter;
      if( m_strOnlyESoPEligible == YES )
      {
         DString strESoPField = asString( ifds::ESoPEligible.getId() );
         //dstrFilter += I_(";");
         dstrFilter += strESoPField;
         dstrFilter += I_( "=" );
         dstrFilter += YES;
      }
      else if( m_strManagementFee == YES )
      {
         dstrFilter =  asString (ifds:: MgtFeeElig.getId() );
         dstrFilter += I_( "=" );
         dstrFilter += YES;   
      }
      else if( m_strManagementFeeRebate == YES )
      {
         dstrFilter =  asString (ifds:: MgtFeeRbtElig.getId() );
         dstrFilter += I_( "=" );
         dstrFilter += YES;       
      }
      if( WARNING >= sevRtn )
      {
         setDataFilter( IFASTBP_PROC::FUNDDETAIL_LIST, dstrFilter);
         m_dstrBaseFilter = dstrFilter;
      }

   }
   catch( ConditionException &ce )
   {
      SETCONDITIONFROMEXCEPTION( ce );
   }
   catch( ... )
   {
      assert( 0 );
      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, DOINIT, CND::BP_ERR_UNKNOWN_EXCEPTION );
   }

   // Defaults
   m_dstrSearchType = I_("FNAM");   // Name
   m_dstrSearchFund = I_("0");      // Fund

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************

E_COMMANDRETURN FundClassProcess::doProcess()
{  
   MAKEFRAME2( CND::BPBASE_CONDITION, CLASSNAME, DOPROCESS );
   E_COMMANDRETURN rtn = CMD_FAILURE;

   try
   {
/*
      setParameter (PARM_FUND_CODE, m_dstrFundCode);
      setParameter (PARM_FUND_NUMBER, m_dstrFundNumber);
      setParameter (PARM_FUND_CLASS, m_dstrFundClass);
*/
      setParameter (I_("FundCategory"), m_fundCategory);
      rtn = invokeCommand( this, CMD_GUI_FUNDCLASS, getProcessType(), isModal(), &m_rpChildGI );
   }
   catch( ConditionException &ce )
   {
      assert( 0 );
      SETCONDITIONFROMEXCEPTION( ce );
   }
   catch( ... )
   {
      assert( 0 );
      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, DOPROCESS, CND::BP_ERR_UNKNOWN_EXCEPTION );
   }
   return(rtn);
}

//******************************************************************************

void FundClassProcess::doPostOk( GenericInterface *rpGICaller, bool bSuccessFlag )
{
   DString strMarket = DSTCommonFunctions::getMarket();

   if( bSuccessFlag )
   {

      DString dstrSearchItemFound = NULL_STRING;
      getParameter( PARM_SEARCHITEMFOUND, dstrSearchItemFound);

      if( !dstrSearchItemFound.empty() )
      {
         DString dstrFundCode, dstrClassCode, dstrFundNum, dstrFundISIN, dstrFundWKN, dstrFundLFC,dstrFundCUSIP;

         // Fund Code
         getField( rpGICaller, IFASTBP_PROC::FUNDDETAIL_LIST, ifds::FundCode, dstrFundCode );
         setParameter( FUNDCLASSLIST::FUND_CODE, dstrFundCode );

         // Class Code
         getField( rpGICaller, IFASTBP_PROC::FUNDDETAIL_LIST, ifds::ClassCode, dstrClassCode );
         setParameter( FUNDCLASSLIST::CLASS_CODE, dstrClassCode );

         // Fund Number (for Canada and any other market)
         if( strMarket == MARKET_IDS::CANADA ||  
             strMarket == MARKET_IDS::LUXEMBOURG )
         {
            dstrFundCode.strip().upperCase();
            dstrClassCode.strip().upperCase();
            dynamic_cast<DSTCWorkSession *>(getBFWorkSession())->GetFundNumber( dstrFundCode, dstrClassCode, dstrFundNum );
            setParameter( FUNDCLASSLIST::FUND_NUMBER, dstrFundNum );
         }

         // Fund ISIN
         getField( rpGICaller, IFASTBP_PROC::FUNDDETAIL_LIST, ifds::FundISIN, dstrFundISIN );
         setParameter( FUNDCLASSLIST::FUND_ISIN, dstrFundISIN );

         // Fund WKN
         getField( rpGICaller, IFASTBP_PROC::FUNDDETAIL_LIST, ifds::FundWKN, dstrFundWKN );
         setParameter( FUNDCLASSLIST::FUND_WKN, dstrFundWKN );

         // Fund LFC
         getField( rpGICaller, IFASTBP_PROC::FUNDDETAIL_LIST, ifds::FundLFC, dstrFundLFC );
         setParameter( FUNDCLASSLIST::FUND_LFC, dstrFundLFC );

		 //Fund CUSIP
		 getField( rpGICaller, IFASTBP_PROC::FUNDDETAIL_LIST, ifds::CUSIP, dstrFundCUSIP );
		 setParameter( FUNDCLASSLIST::CUSIP, dstrFundCUSIP );
      }
      else
      {
         // Return original
         setParameter( FUNDCLASSLIST::FUND_CODE, m_dstrFundCode );
         setParameter( FUNDCLASSLIST::CLASS_CODE,  m_dstrFundClass );
         if( strMarket == MARKET_IDS::CANADA ||  
             strMarket == MARKET_IDS::LUXEMBOURG )
         {
            setParameter( FUNDCLASSLIST::FUND_NUMBER, m_dstrFundNumber );
         }
      }
   }
}

//******************************************************************************

void FundClassProcess::doGetField(
                                 const GenericInterface *rpGICaller,
                                 const BFContainerId& idContainer,
                                 const BFFieldId& idField,
                                 const BFDataGroupId& idDataGroup,
                                 DString &strValueOut,
                                 bool bFormatted
                                 ) const
{      
   if (idField == ifds::FLongName || 
         idField == ifds::ElongName1 ||
         idField == ifds::FundType ||
         idField == ifds::FundCategory)
   {
      strValueOut = NULL_STRING;      

      SEVERITY sevRtn;
      DSTCWorkSession *pDstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());

      FundMasterList *pFundMasterList = NULL;
      sevRtn = pDstcWorkSession->getMgmtCo().getFundMasterList ( pFundMasterList );
      if( sevRtn > WARNING )
      {
         return;
      }

      DString dstrFundCode = NULL_STRING;

      const_cast <FundClassProcess*> (this)->
         getField (rpGICaller, IFASTBP_PROC::FUNDDETAIL_LIST, ifds::FundCode, dstrFundCode, false);      

//      pFundMasterList->getField( dstrFundCode, idField, strValueOut, BF::HOST, false );
      FundMaster *pFundMaster = NULL;
      if (pFundMasterList->getFundMaster (dstrFundCode, idDataGroup, pFundMaster))
      {
         pFundMaster->getField (idField, strValueOut, idDataGroup, bFormatted);
      }
   } 
   else if( idField == ifds::SearchFundType )
   {
      strValueOut = m_dstrSearchType;      
   }
   else if( idField == ifds::SearchFund )
   {
      strValueOut = m_dstrSearchFund;
   }
   else if( idField == ifds::Name )
   {
      strValueOut = m_dstrValue;
   }
   else if( idField == FUNDCLASS::USE_GROUPFUNDLIST )
   {
      strValueOut = m_pGroupFundList ? I_("Y") : I_("N");
   }
   else if( idField == FUNDCLASS::IS_IN_GROUPFUNDLIST )
   {
      strValueOut = I_("N");
      if( m_pGroupFundList )
      {
         DString dstrFundCode, dstrClassCode;

         const_cast <FundClassProcess*> (this)->
            getField (rpGICaller, IFASTBP_PROC::FUNDDETAIL_LIST, ifds::FundCode, dstrFundCode, false);      
         const_cast <FundClassProcess*> (this)->
            getField (rpGICaller, IFASTBP_PROC::FUNDDETAIL_LIST, ifds::ClassCode, dstrClassCode, false);      
         strValueOut = m_pGroupFundList->doesGroupFundClassExist( m_dstrGroupCode, dstrFundCode, dstrClassCode ) ? I_("Y") : I_("N");
      }
   }
}


//******************************************************************************

SEVERITY FundClassProcess::performSearch( GenericInterface *rpGICaller, const BFContainerId& idSearch, E_SEARCHACTION eSearchAction )
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, PERFORMSEARCH );
   SEVERITY sevRtn = SEVERE_ERROR;

   try
   {
      if( idSearch == IFASTBP_PROC::FUNDDETAIL_LIST )
      {
         if( eSearchAction == SEARCH_START )
         {
            delete m_pFundDetailList;
            m_pFundDetailList = NULL;  // Making sure
            setContainer( IFASTBP_PROC::FUNDDETAIL_LIST, NULL );

            // All Funds
            if( m_dstrSearchFund == I_("1") )
            {
               DSTCWorkSession *dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
			      FundDetailList* pFundDetailList = NULL;
			      if( (sevRtn = dstcWorkSession->getMgmtCo().getFundDetailList( pFundDetailList )) <= WARNING 
                  && pFundDetailList )
			      {
				      setContainer( IFASTBP_PROC::FUNDDETAIL_LIST, pFundDetailList );
			      }
            }
            // View call for Name and Code
            else if( m_dstrSearchFund == I_("0") && (m_dstrSearchType == I_("FNAM") || m_dstrSearchType == I_("FUND") ))
            {
               // Make View Call
               m_pFundDetailList = new FundDetailList( *getBFWorkSession() );
               if( m_pFundDetailList )
               {
                  DString dstrFundCode, dstrClassCode, dstrFundName;
                  if( m_dstrSearchType == I_("FNAM") )
                     dstrFundName = m_dstrValue;
                  else if( m_dstrSearchType == I_("FUND") )
                     dstrFundCode = m_dstrValue;
                  sevRtn = m_pFundDetailList->init( (m_dstrSearchFund == I_("0")) ? m_dstrSearchType : NULL_STRING, dstrFundCode, dstrClassCode, dstrFundName, NULL_STRING, NULL_STRING, NULL_STRING );
                  setContainer( IFASTBP_PROC::FUNDDETAIL_LIST, m_pFundDetailList );
               }
            }
            // Fund lookup by Maps
            else
            {
               if( m_pFundDetailListLite )
               {
                  delete m_pFundDetailListLite;
                  m_pFundDetailListLite = NULL;
               }

               m_pFundDetailListLite = new FundDetailListLite( *getBFWorkSession() );
               if( m_pFundDetailListLite )
               {
                  m_pFundDetailListLite->AssociateObject( m_dstrSearchType, m_dstrValue );
               }
               sevRtn = NO_CONDITION;  //
               setContainer( IFASTBP_PROC::FUNDDETAIL_LIST, m_pFundDetailListLite );
            }
         }
         else // SEARCH_NEXT_BLOCK
         {
            if( m_pFundDetailList )
            {
               sevRtn = m_pFundDetailList->getMore();
            }
         }
      }
   }
   catch( ConditionException &ce )
   {
      SETCONDITIONFROMEXCEPTION( ce );
   }
   catch( ... )
   {
      assert( 0 );
      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, PERFORMSEARCH, CND::BP_ERR_UNKNOWN_EXCEPTION );
   }

   return(sevRtn); 
}

//******************************************************************************

bool FundClassProcess::doMoreRecordsExist( GenericInterface *rpGICaller,  const BFContainerId& idSearch )
{
   if( m_pFundDetailList )
   {
      return( m_pFundDetailList->doMoreRecordsExist() );
   }
   else
   {
      return( false );
   }
}

//******************************************************************************

SEVERITY FundClassProcess::doSetField( const GenericInterface *rpGICaller,
                                      const BFContainerId& idContainer,
                                      const BFFieldId& idField,
                                      const BFDataGroupId& idDataGroup,
                                      const DString& strValue,
                                      bool bFormatted )
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, I_( "doSetField" ) );

   if( BF::NullContainerId == idContainer )
   {
      if( idField == ifds::SearchFundType )
      {
         m_dstrSearchType = strValue;
      }
      else if( idField == ifds::SearchFund )
      {
         m_dstrSearchFund = strValue;
      }
      else if( idField == ifds::Name )
      {
         m_dstrValue = strValue;
      }
   }

   return(GETCURRENTHIGHESTSEVERITY());
}
/******************************************************************************
 Input: GenericInterface,ContainerID
 OutPut:None
 Return:BFProperties
 Functionality:Overide the getFiedl Attributs for subclassed fields 
******************************************************************************/
const BFProperties *FundClassProcess::doGetFieldAttributes ( const GenericInterface *rpGICaller,const BFContainerId &idContainer, 
                                                             const BFFieldId &idField, const BFDataGroupId &idDataGroup)
{
  MAKEFRAMEAUTOPROMOTE2 ( CND::BPBASE_CONDITION, 
                           CLASSNAME, 
                           I_("doGetFieldAttributes"));
   BFProperties  *pBFProperties = NULL;
   if( idField == ifds::SearchFundType )
	 {
	   if(!m_propSearchFundType)
	   {
		 const BFDataFieldProperties* pProps = BFDataFieldProperties::get (idField);
         m_propSearchFundType = new BFProperties (pProps);
		 assert( m_propSearchFundType );
		 DString dstrSubList (NULL_STRING), dstrNewSubList (NULL_STRING), dstrFundIDList(NULL_STRING);
		 pProps->getAllSubstituteValues (dstrSubList, ClientLocaleContext::get(), true );
		 DSTCWorkSession* dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
	     if( dstcWorkSession && WARNING >= dstcWorkSession->getOption(ifds::FundIDList, dstrFundIDList, BF::HOST, false ))
		 {
		  if( MARKET_IDS::CANADA == DSTCommonFunctions::getMarket())
			m_propSearchFundType->setAllSubstituteValues (dstrSubList);  //the fields are removed using DD for Canada
		  else
		   {
		   dstrNewSubList = dstrSubList;
		   DString dstrtempNewSubList = NULL_STRING; 
			if( DString::npos  == dstrFundIDList.find( FUND_ID_CODE::VALOREN ))
			{
				removeItemFromSubtList( dstrNewSubList , FUND_ID_CODE::VALOREN, dstrtempNewSubList );
				dstrNewSubList = dstrtempNewSubList; 
			}
			if( DString::npos  == dstrFundIDList.find( FUND_ID_CODE::TDCC ))
			{
				removeItemFromSubtList( dstrNewSubList , FUND_ID_CODE::TDCC, dstrtempNewSubList );
				dstrNewSubList = dstrtempNewSubList; 
			}
			if( DString::npos  == dstrFundIDList.find( FUND_ID_CODE::CUSIP ))
			{
				removeItemFromSubtList( dstrNewSubList , FUND_ID_CODE::CUSIP, dstrtempNewSubList );
				dstrNewSubList = dstrtempNewSubList; 
			}
		   m_propSearchFundType->setAllSubstituteValues( dstrNewSubList ); 
		   }
		 }
	   }
	   else
	   {
		    pBFProperties = m_propSearchFundType;
	   }
	 }
   
   return pBFProperties;
}
/******************************************************************************
 Input: InSubList,Value to be removed
 OutPut:OutSubList
 Return:Void
 Functionality:Remove the value from the input ';' seprated sublist. 
******************************************************************************/
void  FundClassProcess::removeItemFromSubtList( const DString &dstrSubList, const DString &dstrIDValue, DString &dstrOutSubList )
{
    dstrOutSubList = NULL_STRING;
	I_CHAR *temp = const_cast<I_CHAR*> (dstrSubList.c_str ());
	do
	{
	 DString dstrSubListCode,dstrSubListDescr;   
     temp = parseIdiString (temp, dstrSubListCode, dstrSubListDescr );
	 if( dstrIDValue != dstrSubListCode  )
		dstrOutSubList += dstrSubListCode + I_("=") + dstrSubListDescr + I_(";");
	}while (temp && temp != NULL_STRING && *temp);
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/*
 */
