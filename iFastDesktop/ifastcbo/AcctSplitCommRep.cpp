//*****************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by DST Canada, Inc.,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2001 by DST Canada, Inc.
//
//*****************************************************************************
//
// ^FILE   : AcctSplitCommRep.cpp
// ^AUTHOR : 
// ^DATE   : Aug 22, 2001
//
//-----------------------------------------------------------------------------
//
// ^CLASS  : AcctSplitCommRep
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS :
//
//*****************************************************************************
#include "stdafx.h"
#include "acctsplitcomm.hpp"
#include "acctsplitcommlist.hpp"
#include "acctsplitcommrep.hpp"
#include "acctsplitcommreplist.hpp"
#include "agent.hpp"
#include "agentlist.hpp"
#include "branch.hpp"
#include "branchlist.hpp"
#include "broker.hpp"
#include "brokerlist.hpp"
#include "fundservbrokervalidation.hpp"
#include "mfaccount.hpp"
#include "mgmtco.hpp"

#include <ifastdataimpl\dse_dstc0175_vw.hpp>

namespace
{
   // Trace literals
   const I_CHAR * const BRANCH_CODE             = I_( "BRNH" );
   const I_CHAR * const BROKER_CODE             = I_( "BROK" );
   const I_CHAR * const CLASSNAME               = I_( "AcctSplitCommRep" );   
   const I_CHAR * const COMM_LEVEL_BRANCH       = I_( "30" );
   const I_CHAR * const COMM_LEVEL_BROKER       = I_( "20" );
   const I_CHAR * const COMM_LEVEL_MGMT         = I_( "10" );
   const I_CHAR * const COMM_LEVEL_SLSREP       = I_( "40" );   
   const I_CHAR * const MGMT_CODE               = I_( "CNTX" );
   const I_CHAR * const SLSREP_CODE             = I_( "SREP" );
   const I_CHAR * const YES                     = I_( "Y" );
   const I_CHAR * const FUND                    = I_( "FUND" );
   const I_CHAR * const CLASS                   = I_( "CLASS" );
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId BrokerCode;
   extern CLASS_IMPORT const BFTextFieldId CommEntType;
   extern CLASS_IMPORT const BFTextFieldId CompanyId;
   extern CLASS_IMPORT const BFTextFieldId RepByBranch;
   extern CLASS_IMPORT const BFTextFieldId Slsrep;
   extern CLASS_IMPORT const BFTextFieldId SystematicCrossField1;
   extern CLASS_IMPORT const BFTextFieldId RedemptionPayType;
   extern CLASS_IMPORT const BFTextFieldId GuaranteeCalcByRules;
   extern CLASS_IMPORT const BFTextFieldId FundServBroker;
   extern CLASS_IMPORT const BFTextFieldId BrokerBranchRepXEdit;
   extern CLASS_IMPORT const BFTextFieldId FundSERVValidation;
   extern CLASS_IMPORT const BFTextFieldId LTAIndicator;
   extern CLASS_IMPORT const BFTextFieldId ModifyCompAgent;
   extern CLASS_IMPORT const BFTextFieldId ValidationPassed;
   extern CLASS_IMPORT const BFNumericFieldId AccountNum;
   extern CLASS_IMPORT const BFTextFieldId FundEligSlsRepLvl;
   extern CLASS_IMPORT const BFIntegerFieldId WarnCode;
   extern CLASS_IMPORT const BFTextFieldId AutoUpdateSvcAgent;
   extern CLASS_IMPORT const BFTextFieldId FundEliPSG;
   extern CLASS_IMPORT const BFTextFieldId FundAllow;
   extern CLASS_IMPORT const BFTextFieldId ServiceAgentUpdated;
}

namespace IFASTERR
{
   extern CLASS_IMPORT I_CHAR * const SERVICE_AGENT_MUST_BE_CHANGED;
   extern CLASS_IMPORT I_CHAR * const ONE_COMPENSATION_AGENT_IS_ALLOWED;
   extern CLASS_IMPORT I_CHAR * const SERVICE_AGENT_CHANGED_BY_COMPENSATION_AGENT;
}

namespace CND
{
   extern const long ERR_ENTITY_TYPE_EMPTY;
   extern const long ERR_BRANCH_EMPTY;
   extern const long ERR_BROKER_EMPTY;
   extern const long ERR_SALES_REP_EMPTY;
   extern const long ERR_INVALID_PERCENT;
   extern const long ERR_FUND_CLASS_NOT_AVAILABLE_FOR_SALESREP;
   extern const long ERR_SERVICE_AGENT_MUST_BE_CHANGED;
   extern const long WARN_SERVICE_AGENT_MUST_BE_CHANGED;
   extern const long ERR_ONE_COMPENSATION_AGENT_IS_ALLOWED;
   extern const long WARN_ONE_COMPENSATION_AGENT_IS_ALLOWED;
   extern const long ERR_SERVICE_AGENT_CHANGED_BY_COMPENSATION_AGENT;
   extern const long WARN_SERVICE_AGENT_CHANGED_BY_COMPENSATION_AGENT;
   extern const long ERR_BROKER_NOT_ELIGIBLE_FOR_ACCT;
}

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = {
//  Field DD Id,                    State Flags,               Group Flags    
   { ifds::Active,                  BFCBO::NONE,                  0 }, 
   { ifds::AgencyCode,              BFCBO::NONE,                  0 }, 
   { ifds::AgentCode,               BFCBO::NONE,                  0 }, 
   { ifds::BranchCode,              BFCBO::NONE,                  0 }, 
   { ifds::BranchName,              BFCBO::NONE,                  0 }, 
   { ifds::BrokerName,              BFCBO::NONE,                  0 }, 
   { ifds::CommEntType,             BFCBO::REQUIRED,              0 }, 
   { ifds::CommLevel,               BFCBO::NONE,                  0 }, 
   { ifds::CommLevelDesc,           BFCBO::NONE,                  0 }, 
   { ifds::CommPrcnt,               BFCBO::REQUIRED,              0 }, 
   { ifds::EffectiveDate,           BFCBO::NONE,                  0 }, 
   { ifds::EntityName,              BFCBO::NONE,                  0 }, 
   { ifds::GrossOrNet,              BFCBO::NONE,                  0 }, 
   { ifds::SlsrepName,              BFCBO::NONE,                  0 }, 
   { ifds::SplCommRid,              BFCBO::NONE,                  0 }, 
   { ifds::StopDate,                BFCBO::NONE,                  0 }, 
   { ifds::TradesPayType,           BFCBO::NONE,                  0 }, 
   { ifds::BrokerBranchRepXEdit,    BFCBO::IMMEDIATE_VALIDATION,  0 },
   { ifds::AutoUpdateSvcAgent,      BFCBO::NOT_ON_HOST,           0 },
};

static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );

//******************************************************************************
// Constructor
//******************************************************************************
AcctSplitCommRep::AcctSplitCommRep( BFAbstractCBO &parent ) 
: MFCanBFCbo( parent )
, _salesRepByBranch( NULL_STRING )
, _brokerName( NULL_STRING )
, _branchName( NULL_STRING )
, _branchCode( NULL_STRING )
, _agentName( NULL_STRING )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );

   // Registers fields to be used for storing data
   registerMemberData( NUM_FIELDS, (const CLASS_FIELD_INFO *)&classFieldInfo,0,NULL);  

   addCrossEdit(ifds::BrokerBranchRepXEdit, ifds::AgencyCode);
   addCrossEdit(ifds::BrokerBranchRepXEdit, ifds::BranchCode);
   addCrossEdit(ifds::BrokerBranchRepXEdit, ifds::AgentCode);

   setFieldAllSubstituteValues( ifds::TradesPayType, BF::HOST, ifds::RedemptionPayType );
}

//******************************************************************************
// Destructor
//******************************************************************************
AcctSplitCommRep::~AcctSplitCommRep()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************
// Creates the AcctSplitCommRep CBO based on the data passed in.
// @param   const Data& data - pointer to data returned from the view.
// @param   bool bBaseDelete - Flag to detemine who deletes the CBO
//******************************************************************************
SEVERITY AcctSplitCommRep::init( const BFData& data, bool bBaseDelete )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

   // Call BFCBO attachDataObject for 
   BFData *copyData = new BFData (data);
   attachDataObject( *copyData, bBaseDelete );
   DString dstrCommLevel, dstrActive;
   getField ( ifds::CommLevel, dstrCommLevel, BF::HOST );
   getField ( ifds::Active, dstrActive, BF::HOST, false );
   allFieldsReadOnly ( dstrActive != YES, BF::HOST );
   if( dstrCommLevel == COMM_LEVEL_MGMT )
   {
      setFieldNoValidate ( ifds::CommEntType, MGMT_CODE, BF::HOST, false, true, false, false  );
   }
   else if( dstrCommLevel == COMM_LEVEL_BROKER )
   {
      setFieldNoValidate ( ifds::CommEntType, BROKER_CODE, BF::HOST, false, true, false, false  );
   }
   else if( dstrCommLevel == COMM_LEVEL_BRANCH )
   {
      setFieldNoValidate ( ifds::CommEntType, BRANCH_CODE, BF::HOST, false, true, false, false  );
   }
   else if( dstrCommLevel == COMM_LEVEL_SLSREP )
   {
      setFieldNoValidate ( ifds::CommEntType, SLSREP_CODE, BF::HOST, false, true, false, false  );
      if( !slsRepByBranch(BF::HOST) )
         setFieldReadOnly( ifds::BranchCode, BF::HOST, true );
   }
   // Need to clear the updated flag from setFieldNoValidate
   clearUpdatedFlags ( BF::HOST );
   setAllFieldsValid ( BF::HOST );

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY AcctSplitCommRep::doApplyRelatedChanges( const BFFieldId& idField, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doApplyRelatedChanges" ) );

   DString dstrCommEntType;      
   getField( ifds::CommEntType, dstrCommEntType, idDataGroup, false);

   if( idField == ifds::CommEntType )
   {
      if( dstrCommEntType == MGMT_CODE )
      {
         DString dstrCompanyId, dstrtempCompanyId, dstrCompanyName;
         setFieldNoValidate( ifds::CommLevel, COMM_LEVEL_MGMT, idDataGroup );

         getMgmtCo().getField( ifds::CompanyId, dstrCompanyId, BF::HOST);        
         const DSTCSecurity* pSecurity = const_cast<DSTCSecurity *> (dynamic_cast<const DSTCSecurity *> (getSecurity()));
         long lnumCompany = pSecurity->getNumberOfCompanies();
         for( int i=0; i < lnumCompany; ++i )
         {
            pSecurity->getCompanyInfo( i, dstrtempCompanyId, dstrCompanyName );
            if( dstrtempCompanyId == dstrCompanyId )
            {
               break;
            }
         }        
         setFieldNoValidate( ifds::CommLevelDesc, dstrCompanyName, idDataGroup );
         setFieldNoValidate( ifds::EntityName, dstrCompanyName, idDataGroup );
      }
      else if( dstrCommEntType == BROKER_CODE )
      {
         setFieldNoValidate( ifds::CommLevel, COMM_LEVEL_BROKER, idDataGroup );
         setValidFlag(ifds::AgencyCode, idDataGroup, false);   // to force validation
         setFieldNoValidate( ifds::CommLevelDesc, NULL_STRING, idDataGroup );
      }
      else if( dstrCommEntType == BRANCH_CODE )
      {
         setFieldNoValidate( ifds::CommLevel, COMM_LEVEL_BRANCH, idDataGroup );
         setValidFlag(ifds::AgencyCode, idDataGroup, false);   // to force validation
         setValidFlag(ifds::BranchCode, idDataGroup, false);   // to force validation
         setFieldReadOnly ( ifds::BranchCode, idDataGroup, false );
         setFieldNoValidate( ifds::CommLevelDesc, NULL_STRING, idDataGroup );
//         setFieldNoValidate( ifds::AgentCode, NULL_STRING, idDataGroup, false, true, true, NULL, false );
      }
      else if( dstrCommEntType == SLSREP_CODE )
      {
         setFieldNoValidate( ifds::CommLevel, COMM_LEVEL_SLSREP, idDataGroup );
         setValidFlag(ifds::AgencyCode, idDataGroup, false);   // to force validation
         setValidFlag(ifds::BranchCode, idDataGroup, false);   // to force validation
         setValidFlag(ifds::AgentCode, idDataGroup, false);   // to force validation
         setFieldNoValidate( ifds::CommLevelDesc, NULL_STRING, idDataGroup );
         if( !slsRepByBranch(BF::HOST) )
            setFieldReadOnly( ifds::BranchCode, idDataGroup, true );
      }

   }
   else if( idField == ifds::AgencyCode )
   {
      setFieldNoValidate( ifds::BranchCode, NULL_STRING, idDataGroup, false, true, true, false );         
      setFieldNoValidate( ifds::BranchName, NULL_STRING, idDataGroup, false, true, true, false );         
      setFieldNoValidate( ifds::AgentCode, NULL_STRING, idDataGroup, false, true, true, false );
      setFieldNoValidate( ifds::SlsrepName, NULL_STRING, idDataGroup, false, true, true, false );
   }
   else if( idField == ifds::BranchCode )
   {
      setFieldNoValidate( ifds::AgentCode, NULL_STRING, idDataGroup, false, true, true, false );
      setFieldNoValidate( ifds::SlsrepName, NULL_STRING, idDataGroup, false, true, true, false );
   }
   else if( idField == ifds::Active )
   {
      DString dstr;
      getField( idField, dstr, idDataGroup, false);
      allFieldsReadOnly ( ( dstr != YES ), idDataGroup );
   }
   else if( idField == ifds::BrokerBranchRepXEdit )
   {
      FundSERVBrokerValidation fundSERVBrokerValidation(*this);
      DString brokerCodeHost, 
         branchCodeHost,
         slsRepHost,
         dstrAccountNum,
         dstrBrokerCode,
         dstrBranchCode,
         dstrSlsRepCode;
         
      getField ( ifds::AgencyCode, dstrBrokerCode, idDataGroup,  false);
      getField ( ifds::BranchCode, dstrBranchCode, idDataGroup,  false);
      getField ( ifds::AgentCode, dstrSlsRepCode, idDataGroup,  false);
      
      AcctSplitCommList* pAcctSplitCommList = dynamic_cast <AcctSplitCommList*> ( getParent()->getParent()->getParent() );
      pAcctSplitCommList->getAccountNum ( dstrAccountNum );

      dstrBrokerCode.strip().upperCase();
      dstrBranchCode.strip().upperCase();
      dstrSlsRepCode.strip().upperCase(); 
      dstrAccountNum.strip().upperCase();

      if( !pAcctSplitCommList->getParent()->isNew() ) // new account would have 'old' broker\branch\slsrep as blank
      {
         if(!isNew())
         {
            getFieldBeforeImage( ifds::AgencyCode, brokerCodeHost);
            getFieldBeforeImage( ifds::BranchCode, branchCodeHost);
            getFieldBeforeImage( ifds::AgentCode,slsRepHost);

            brokerCodeHost.strip().upperCase();
            branchCodeHost.strip().upperCase();
            slsRepHost.strip().upperCase();
         }
         else
         {
            AcctSplitCommList* pAcctSplitCommList = (AcctSplitCommList*)(getParent()->getParent()->getParent());
            AcctSplitComm* pLastActiveAcctSplitComm = pAcctSplitCommList->getLastActiveAcctSplitComm();
            AcctSplitCommRepList* pAcctSplitCommRepList = NULL;
            if(pLastActiveAcctSplitComm)
            {
               pLastActiveAcctSplitComm->getAcctSplitCommRepList ( pAcctSplitCommRepList, idDataGroup);

            BFObjIter iterAcctSplitCommRep( *pAcctSplitCommRepList, idDataGroup );

            iterAcctSplitCommRep.begin();
            if( !iterAcctSplitCommRep.end() )
            {
               AcctSplitCommRep* pAcctSplitCommRep = (AcctSplitCommRep*)iterAcctSplitCommRep.getObject();
               pAcctSplitCommRep->getField(ifds::AgencyCode, brokerCodeHost, idDataGroup);
               pAcctSplitCommRep->getField(ifds::BranchCode, branchCodeHost, idDataGroup);
               pAcctSplitCommRep->getField(ifds::AgentCode,slsRepHost, idDataGroup);

               brokerCodeHost.strip().upperCase();
               branchCodeHost.strip().upperCase();
               slsRepHost.strip().upperCase();
               }
            }
         }






         if( fundSERVBrokerValidation.init(I_("CommAgent"),
                                             dstrAccountNum,
                                             brokerCodeHost,
                                             branchCodeHost,
                                             slsRepHost,
                                             dstrBrokerCode,
                                             dstrBranchCode,
                                             dstrSlsRepCode)<= WARNING)
         {
            // no data broker error but it might some result return
            DString warnCode,
               autoUpdateSvcAgent;
            fundSERVBrokerValidation.getField( ifds::WarnCode, warnCode, idDataGroup, false );
            fundSERVBrokerValidation.getField( ifds::AutoUpdateSvcAgent, autoUpdateSvcAgent, idDataGroup, false );
            warnCode.strip().upperCase();
            autoUpdateSvcAgent.strip().upperCase();

            if(warnCode.asInteger() == 1249 )
            {
               if(autoUpdateSvcAgent == I_("Y"))
               {
                  updateSvcAgentRelatedChanges(idDataGroup);
               }
            }
         }
      }
      else
      {
         if(dstrBrokerCode.stripAll() != I_(""))
         {
            BrokerList* pBrokerList = NULL;
            if ( getWorkSession().getBrokerList (pBrokerList) <= WARNING && 
               pBrokerList)
            {   
               Broker *pBroker = NULL;

               if ( pBrokerList->getBroker (dstrBrokerCode, pBroker) <= WARNING && pBroker)
               {
                  DString dstrFundServBroker;
                  pBroker->getField(ifds::FundServBroker, dstrFundServBroker, idDataGroup);
                  if(dstrFundServBroker.upperCase().stripAll() == I_("Y"))
                  {
                     pAcctSplitCommList->getParent()->setField(ifds::BrokerCode,dstrBrokerCode,idDataGroup, false, true, false);
                     pAcctSplitCommList->getParent()->setField(ifds::BranchCode,dstrBranchCode,idDataGroup, false, true, false);
                     pAcctSplitCommList->getParent()->setField(ifds::Slsrep,dstrSlsRepCode,idDataGroup, false, true, false);
                  }
               }
            }
         }
      }
   }

   setFieldsInvalid ( dstrCommEntType, idField, idDataGroup );

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY AcctSplitCommRep::doValidateField( const BFFieldId& idField, const DString& strValue, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doValidateField" ) );
   SEVERITY sevRtn = NO_CONDITION;
   DString dstrCommEntType;
   getField( ifds::CommEntType, dstrCommEntType, idDataGroup);

   if( idField == ifds::AgencyCode )
   {
      if( dstrCommEntType != MGMT_CODE )
      {
         if( strValue == NULL_STRING )
         {
            ADDCONDITIONFROMFILE( CND::ERR_BROKER_EMPTY );
         }
         else if( checkBroker( strValue, idDataGroup, true ) <= WARNING )
         {
            setFieldNoValidate( ifds::BrokerName, _brokerName, idDataGroup, false, true, false, false );
         }
         if( dstrCommEntType == BROKER_CODE )
         {
            setFieldNoValidate( ifds::CommLevelDesc, _brokerName, idDataGroup, false, true, false, false );
            setFieldNoValidate( ifds::BrokerName, _brokerName, idDataGroup, false, true, false, false );
            setFieldNoValidate( ifds::EntityName, _brokerName, idDataGroup, false, true, false, false );            
         }
      }
   }
   else if( idField == ifds::BranchCode )
   {
      if( ( dstrCommEntType == SLSREP_CODE ) || ( dstrCommEntType == BRANCH_CODE ) )
      {
         DString dstrAgencyCode;
         getField( ifds::AgencyCode, dstrAgencyCode, idDataGroup );
         if( validateField( ifds::AgencyCode, dstrAgencyCode, idDataGroup ) <= WARNING )
         {
            if( strValue == NULL_STRING )
            {
               if( ( ( dstrCommEntType == SLSREP_CODE ) && ( slsRepByBranch ( idDataGroup )) ) || ( dstrCommEntType == BRANCH_CODE ) )
                  ADDCONDITIONFROMFILE( CND::ERR_BRANCH_EMPTY);
            }
            else if( checkBranches( strValue, idDataGroup, true ) <= WARNING )
            {
               setFieldNoValidate( ifds::BranchName, _branchName, idDataGroup, false, true, false, false );
            }
         }
         if( dstrCommEntType == BRANCH_CODE )
         {
            setFieldNoValidate( ifds::CommLevelDesc, _branchName, idDataGroup, false, true, false, false );
            setFieldNoValidate( ifds::BranchName, _branchName, idDataGroup, false, true, false, false );
            setFieldNoValidate( ifds::EntityName, _branchName, idDataGroup, false, true, false, false );
         }
      }
   }
   else if( idField == ifds::AgentCode )
   {
      if( dstrCommEntType == SLSREP_CODE )
      {
         DString dstrBranchCode, slsrepName;
         SEVERITY sevRtn = NO_CONDITION;
         if( slsRepByBranch ( idDataGroup ) )
         {
            getField( ifds::BranchCode, dstrBranchCode, idDataGroup );
            sevRtn = validateField ( ifds::BranchCode, dstrBranchCode, idDataGroup );
         }
         if( sevRtn <= WARNING )
         {
            if( strValue == NULL_STRING )
            {
               ADDCONDITIONFROMFILE( CND::ERR_SALES_REP_EMPTY );
            }
            else if( checkAgents( strValue, idDataGroup, true ) <= WARNING )
            {
               if( !slsRepByBranch ( idDataGroup ) )
                  setFieldNoValidate( ifds::BranchCode, _branchCode, idDataGroup, false, true, false, false );
               setFieldNoValidate( ifds::CommLevelDesc, _agentName, idDataGroup, false, true, false, false );
               setFieldNoValidate( ifds::SlsrepName, _agentName, idDataGroup, false, true, false, false );
               setFieldNoValidate( ifds::EntityName, _agentName, idDataGroup, false, true, false, false );
            }
         }
      }
   }
   else if( idField == ifds::CommEntType )
   {
      if( strValue == NULL_STRING )
      {
         ADDCONDITIONFROMFILE( CND::ERR_ENTITY_TYPE_EMPTY );
      }
   }
   else if( idField == ifds::CommPrcnt )
   {
      DString dstrCommPrcnt;
      double dPercent;
      getField ( ifds::CommPrcnt, dstrCommPrcnt, idDataGroup );
      dPercent = DSTCommonFunctions::convertToDouble( dstrCommPrcnt );
      if( ( dPercent <= 0 ) || ( dPercent > 100 ) )
         ADDCONDITIONFROMFILE( CND::ERR_INVALID_PERCENT );
   }
   else if ( idField == ifds::BrokerBranchRepXEdit)
   {
      DString brokerCode, branchCode, slsRep;
      getField (ifds::AgencyCode, brokerCode, idDataGroup,false);
      getField( ifds::BranchCode, branchCode, idDataGroup,false );
      getField( ifds::AgentCode, slsRep, idDataGroup,false );

      validateBlockTransfer(brokerCode,branchCode,slsRep,idDataGroup);
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY AcctSplitCommRep::checkBroker( const DString& brokerCode, 
                                        const BFDataGroupId& idDataGroup,
                                        bool condition_returned )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "checkBroker" ) );

   BrokerList brokerList ( *this );

   //checks for the validity of the broker code. by making a view call, and raising a condition
   //we do not want to make the view call when the broker code is NULL, because the view will
   //return us all the brokers

   MFAccount* pMFAccount;
   DString dstrAgencyCode,
      dstrAccountNum;
   AcctSplitCommList* pAcctSplitCommList = dynamic_cast <AcctSplitCommList*> ( getParent()->getParent()->getParent() );
   pAcctSplitCommList->getAccountNum ( dstrAccountNum );
   getWorkSession().getMFAccount ( idDataGroup, dstrAccountNum, pMFAccount );
   if( pMFAccount )
   {
      pMFAccount->getField ( ifds::BrokerCode, dstrAgencyCode, idDataGroup, false );
   }         
   
   if( brokerCode != NULL_STRING ) 
   {
      DString fundEliPSG;
      getWorkSession().getOption (ifds::FundEliPSG, fundEliPSG, idDataGroup, false );
      fundEliPSG.strip().upperCase(); 
      
      if( fundEliPSG == I_("Y"))
      {
         if( brokerList.init2( brokerCode, NULL_STRING, I_( "L" ), dstrAccountNum, I_("Trade") ) <= WARNING )
         {
            BFObjIter bfIter( brokerList, idDataGroup );
            DString dstrStopDate;
            if( !bfIter.end() )
            {
               Broker* pBroker = dynamic_cast <Broker*> (bfIter.getObject());
               pBroker->getField( ifds::BrokerName, _brokerName, idDataGroup ); 
               DString dstrEffectiveDate;
               getField ( ifds::EffectiveDate, dstrEffectiveDate, idDataGroup );
               if ( pBroker->checkEffective ( dstrEffectiveDate, idDataGroup ) <= WARNING )
               {
                  DString dstrFundAllow;
                  pBroker->getField ( ifds::FundAllow, dstrFundAllow, idDataGroup );
                  dstrFundAllow.strip().upperCase();

                  bool bIsSameAgent = true;
                  DString strBrokerBefore;
                  getFieldBeforeImage(ifds::AgencyCode, strBrokerBefore);
                  bIsSameAgent = dstrAgencyCode.strip().upperCase() == 
                                 strBrokerBefore.strip().upperCase();

                  if (dstrFundAllow == I_("N"))// && bIsSameAgent) 
                  {
                     ADDCONDITIONFROMFILE (CND::ERR_BROKER_NOT_ELIGIBLE_FOR_ACCT);
                  }
               }
            }
         }
         else
         {
            _brokerName = NULL_STRING;
         }
      }
      else
      {       
         // 'L' for the request type will do a search for broker by code
         if( brokerList.init( brokerCode, NULL_STRING, I_( "L" ) ) <= WARNING )
         {
            BFObjIter bfIter( brokerList, idDataGroup );
            DString dstrStopDate;
            if( !bfIter.end() )
            {
               Broker* pBroker = dynamic_cast <Broker*> (bfIter.getObject());
               pBroker->getField( ifds::BrokerName, _brokerName, idDataGroup ); 
               DString dstrEffectiveDate;
               getField ( ifds::EffectiveDate, dstrEffectiveDate, idDataGroup );
               if ( pBroker->checkEffective ( dstrEffectiveDate, idDataGroup ) <= WARNING)
               {
                  DString dstrFundAllow;
                  pBroker->getField ( ifds::FundAllow, dstrFundAllow, idDataGroup );
                  dstrFundAllow.strip().upperCase();

                  bool bIsSameAgent = true;
                  DString strBrokerBefore;
                  getFieldBeforeImage(ifds::AgencyCode, strBrokerBefore);
                  bIsSameAgent = dstrAgencyCode.strip().upperCase() == 
                                 strBrokerBefore.strip().upperCase();
                  if (dstrFundAllow == I_("N") && bIsSameAgent) 
                  {
                     ADDCONDITIONFROMFILE (CND::ERR_BROKER_NOT_ELIGIBLE_FOR_ACCT);
                  }
               }
            }
         }
         else
         {
            _brokerName = NULL_STRING;
         }
      }
   }
   else
   {
      _brokerName = NULL_STRING;
   }

   if( condition_returned == true )
      return(GETCURRENTHIGHESTSEVERITY());
   else
      return(NO_CONDITION);

}

//******************************************************************************
SEVERITY AcctSplitCommRep::checkBranches( const DString& branchCode, 
                                          const BFDataGroupId& idDataGroup,
                                          bool condition_returned )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "checkBranches" ) );

   BranchList branchList ( *this );
   DString brokerCode;

   getField( ifds::AgencyCode, brokerCode, idDataGroup );
   //checks for the validity of the branch code. by making a view call, and raising a condition
   //we do not want to make the view call when the branch code is NULL, because the view will
   //return us all the branches for this broker
   if( branchCode != NULL_STRING && 
       branchList.init( brokerCode, branchCode ) <= WARNING )
   {
      BFObjIter bfIter( branchList, idDataGroup );
      DString branchName;      
      if( !bfIter.end() )
      {
         Branch* pBranch = dynamic_cast <Branch*> ( bfIter.getObject() );
         DString dstrEffectiveDate;
         getField ( ifds::EffectiveDate, dstrEffectiveDate, idDataGroup );
         pBranch->getField( ifds::BranchName, _branchName, idDataGroup );
         pBranch->checkEffective ( dstrEffectiveDate, idDataGroup );
      }
   }
   else
   {
      _branchName = NULL_STRING;
   }

   if( condition_returned == true )
      return(GETCURRENTHIGHESTSEVERITY());
   else
      return(NO_CONDITION);
}

//******************************************************************************
SEVERITY AcctSplitCommRep::checkAgents( const DString& slsrepCode, 
                                        const BFDataGroupId& idDataGroup,
                                        bool condition_returned )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "checkAgents" ) );

   AgentList agentList( *this );
   DString brokerCode, branchCode;

   getField( ifds::AgencyCode, brokerCode, idDataGroup );
   if( slsRepByBranch ( idDataGroup ) )
      getField( ifds::BranchCode, branchCode, idDataGroup );
   else
      branchCode = NULL_STRING;

   //checks for the validity of the agent code. by making a view call, and raising a condition
   //we do not want to make the view call when the slslrep code is NULL, because the view will
   //return us all the agents for this broker and branch
   if( slsrepCode != NULL_STRING && 
       agentList.init( brokerCode, branchCode, slsrepCode ) <= WARNING )
   {
      BFObjIter bfIter( agentList, idDataGroup );
      DString slsrepName, slsrepAltName;
      if( !bfIter.end() )
      {
         Agent* pAgent = dynamic_cast <Agent*> ( bfIter.getObject() );
         pAgent->getField( ifds::SlsrepName, _agentName, idDataGroup );
         pAgent->getField( ifds::BranchCode, _branchCode, idDataGroup );
         pAgent->getField( ifds::BranchName, _branchName, idDataGroup );
         DString dstrEffectiveDate;
         getField ( ifds::EffectiveDate, dstrEffectiveDate, idDataGroup );
         pAgent->checkEffective ( dstrEffectiveDate, idDataGroup );
      }
   }
   else
   {
      _agentName = NULL_STRING;
      if( !slsRepByBranch ( idDataGroup) )
      {
         _branchCode = NULL_STRING;
         _branchName = NULL_STRING;
      }
   }

   if( condition_returned == true )
      return(GETCURRENTHIGHESTSEVERITY());
   else
      return(NO_CONDITION);
}

//******************************************************************************
bool AcctSplitCommRep::slsRepByBranch ( const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "slsRepByBranc" ) );

   if( _salesRepByBranch == NULL_STRING )
   {
      getWorkSession().getOption( ifds::RepByBranch, _salesRepByBranch, idDataGroup );
   }

   return( _salesRepByBranch == YES );
}

//******************************************************************************
void AcctSplitCommRep::allFieldsReadOnly( bool benable, const BFDataGroupId& idDataGroup )
{
   const CLASS_FIELD_INFO* pClassFieldInfo = (const CLASS_FIELD_INFO *)&classFieldInfo;
   for( int i = 0; i < NUM_FIELDS; i++, pClassFieldInfo++ )
   {
      setFieldReadOnly ( pClassFieldInfo->m_fieldId, idDataGroup, benable );
   }   
   //This is a bug fix for the Substitute values, setFieldReadOnly does not copy the 
   //substituion value overrides from datagroup BF::HOST, rather it uses the original set defined
   //in the datadictionary, hence we have to override it again of the new data group.
   setFieldAllSubstituteValues( ifds::TradesPayType, idDataGroup, ifds::RedemptionPayType );
}

//******************************************************************************
void AcctSplitCommRep::doInitWithDefaultValues( const BFDataGroupId& idDataGroup )
{
   //retrieve the effective and stop date from the parent list.
   DString dstrStopDate, dstrEffectiveDate, dstrAgencyCode, dstrBranchCode, dstrAgentCode, dstrAccountNum;
   DString dstrEntityName, dstrCommEntType, dstrCommLevelDesc, dstrBranchName, dstrBrokerName, dstrSlsrepName;

   AcctSplitComm* pAcctSplitComm = dynamic_cast <AcctSplitComm*>( getParent()->getParent() );
   pAcctSplitComm->getField( ifds::EffectiveDate, dstrEffectiveDate, idDataGroup, false );
   pAcctSplitComm->getField( ifds::StopDate, dstrStopDate, idDataGroup, false );
   setFieldNoValidate ( ifds::EffectiveDate, dstrEffectiveDate, BF::HOST, false, true, false, false );
   setFieldNoValidate ( ifds::StopDate, dstrStopDate, BF::HOST, false, true, false, false );

// Retrieve values
   if( pAcctSplitComm->isNew() )
   {
      MFAccount* pMFAccount;
      AcctSplitCommList* pAcctSplitCommList = dynamic_cast <AcctSplitCommList*> ( getParent()->getParent()->getParent() );
      pAcctSplitCommList->getAccountNum ( dstrAccountNum );
      getWorkSession().getMFAccount ( idDataGroup, dstrAccountNum, pMFAccount );
      if( pMFAccount->isNew () )
      {
         pMFAccount->getField ( ifds::BrokerCode, dstrAgencyCode, idDataGroup, false );
         pMFAccount->getField ( ifds::BranchCode, dstrBranchCode, idDataGroup, false );
         pMFAccount->getField ( ifds::Slsrep, dstrAgentCode, idDataGroup, false );
         pMFAccount->getField ( ifds::BrokerName, dstrBrokerName, idDataGroup, false );
         pMFAccount->getField ( ifds::BranchName, dstrBranchName, idDataGroup, false );
         pMFAccount->getField ( ifds::SlsrepName, dstrSlsrepName, idDataGroup, false );

         // Setup Sales Rep as default
         setFieldNoValidate ( ifds::CommEntType, SLSREP_CODE, BF::HOST, false, true, false, false );  
         setFieldNoValidate ( ifds::CommLevel, COMM_LEVEL_SLSREP, BF::HOST,  false, true, false, false  );
         setFieldNoValidate ( ifds::AgencyCode, dstrAgencyCode, BF::HOST,  false, true, false, false  );
         setFieldNoValidate ( ifds::BranchCode, dstrBranchCode, BF::HOST,  false, true, false, false  );
         setFieldNoValidate ( ifds::AgentCode, dstrAgentCode, BF::HOST,  false, true, false, false  );
         setFieldNoValidate ( ifds::CommPrcnt, I_( "100" ), BF::HOST,  false, true, false, false  );      
         setFieldNoValidate ( ifds::SlsrepName, dstrSlsrepName, BF::HOST,  false, true, false, false  );
         setFieldNoValidate ( ifds::BranchName, dstrBranchName, BF::HOST,  false, true, false, false  );
         setFieldNoValidate ( ifds::BrokerName, dstrBrokerName, BF::HOST,  false, true, false, false  );
         setFieldNoValidate ( ifds::EntityName, dstrSlsrepName, BF::HOST,  false, true, false, false  );         

         if( !slsRepByBranch(BF::HOST) )
            setFieldReadOnly( ifds::BranchCode, BF::HOST, true );
      }
      setNonDummyFlag();
   }
}

//******************************************************************************
void AcctSplitCommRep::setFieldsInvalid ( DString dstrCommEntType, const BFFieldId& idField, const BFDataGroupId& idDataGroup )
{
   if( idField == ifds::AgencyCode )
   {
      if( dstrCommEntType == BRANCH_CODE )
      {
         setValidFlag(ifds::BranchCode, idDataGroup, false);
      }
      else if( dstrCommEntType == SLSREP_CODE )
      {
         if( !slsRepByBranch ( idDataGroup ) )
            setValidFlag(ifds::BranchCode, idDataGroup, false);
         setValidFlag(ifds::AgentCode, idDataGroup, false);
      }
   }
   else if( idField == ifds::BranchCode )
   {
      if( dstrCommEntType == SLSREP_CODE )
      {
         setValidFlag(ifds::AgencyCode, idDataGroup, false);
         setValidFlag(ifds::AgentCode, idDataGroup, false);
      }
   }
}

//******************************************************************************
SEVERITY AcctSplitCommRep::validateBlockTransfer( const DString& brokerCode, 
                                                  const DString& branchCode,
                                                  const DString& slsRep, 
                                                  const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateBlockTransfer" ) );	

   AcctSplitCommList* pAcctSplitCommList = dynamic_cast <AcctSplitCommList*> ( getParent()->getParent()->getParent() );
   MFAccount* pMFAccount = dynamic_cast <MFAccount*> ( pAcctSplitCommList->getParent() ); 

   if(pMFAccount && !pMFAccount->isNew()) // temporary fixed for IN2988339 - need to use mfaccaunt-isnew
   {
      DString accountNum;

      AcctSplitCommList* pAcctSplitCommList = dynamic_cast <AcctSplitCommList*> ( getParent()->getParent()->getParent() );
      pAcctSplitCommList->getAccountNum ( accountNum );
      accountNum.strip().upperCase();

      FundSERVBrokerValidation fundSERVBrokerValidation(*this);
      DString brokerCodeHost, 
         branchCodeHost,
         slsRepHost;

      if(!isNew())
      {
         getFieldBeforeImage( ifds::AgencyCode, brokerCodeHost);
         getFieldBeforeImage( ifds::BranchCode, branchCodeHost);
         getFieldBeforeImage( ifds::AgentCode,slsRepHost);

         brokerCodeHost.strip().upperCase();
         branchCodeHost.strip().upperCase();
         slsRepHost.strip().upperCase();
      }
      else
      {
         AcctSplitCommList* pAcctSplitCommList = (AcctSplitCommList*)(getParent()->getParent()->getParent());
         AcctSplitComm* pLastActiveAcctSplitComm = pAcctSplitCommList->getLastActiveAcctSplitComm();
         AcctSplitCommRepList* pAcctSplitCommRepList = NULL;
         if(pLastActiveAcctSplitComm)
         {
         pLastActiveAcctSplitComm->getAcctSplitCommRepList ( pAcctSplitCommRepList, idDataGroup);

         BFObjIter iterAcctSplitCommRep( *pAcctSplitCommRepList, idDataGroup );

         iterAcctSplitCommRep.begin();
         if( !iterAcctSplitCommRep.end() )
         {
            AcctSplitCommRep* pAcctSplitCommRep = (AcctSplitCommRep*)iterAcctSplitCommRep.getObject();
            pAcctSplitCommRep->getField(ifds::AgencyCode, brokerCodeHost, idDataGroup);
            pAcctSplitCommRep->getField(ifds::BranchCode, branchCodeHost, idDataGroup);
            pAcctSplitCommRep->getField(ifds::AgentCode,slsRepHost, idDataGroup);

            brokerCodeHost.strip().upperCase();
            branchCodeHost.strip().upperCase();
            slsRepHost.strip().upperCase();
            }
         }
      }

      // new account would have 'old' broker\branch\slsrep as blank
      if( fundSERVBrokerValidation.init(I_("CommAgent"),
                                          accountNum,
                                          brokerCodeHost,
                                          branchCodeHost,
                                          slsRepHost,
                                          brokerCode,
                                          branchCode,
                                          slsRep)<= WARNING)
      {
         // no data broker error but it might some result return
         DString warnCode,
            autoUpdateSvcAgent;
         fundSERVBrokerValidation.getField( ifds::WarnCode, warnCode, idDataGroup, false );
         fundSERVBrokerValidation.getField( ifds::AutoUpdateSvcAgent, autoUpdateSvcAgent, idDataGroup, false );
         warnCode.strip().upperCase();
         autoUpdateSvcAgent.strip().upperCase();
         setFieldNoValidate ( ifds::AutoUpdateSvcAgent, autoUpdateSvcAgent, idDataGroup,  false, true, false, false  );

         if(warnCode.asInteger() == 1247 )
         {
            getErrMsg( IFASTERR::ONE_COMPENSATION_AGENT_IS_ALLOWED, 
                       CND::ERR_ONE_COMPENSATION_AGENT_IS_ALLOWED, 
                       CND::WARN_ONE_COMPENSATION_AGENT_IS_ALLOWED, 
                       idDataGroup);
         }
         else if(warnCode.asInteger() == 1248 )
         {
            getErrMsg( IFASTERR::SERVICE_AGENT_MUST_BE_CHANGED, 
                       CND::ERR_SERVICE_AGENT_MUST_BE_CHANGED, 
                       CND::WARN_SERVICE_AGENT_MUST_BE_CHANGED, 
                       idDataGroup);
         }
      }
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY AcctSplitCommRep::getServiceBroker ( Broker *&pBroker, 
                                              const DString& dstrBrokerCode,
                                              const BFDataGroupId &idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, CLASSNAME, I_("getServiceBroker") );

   pBroker = NULL;

   DString dstrAccountNum;
   AcctSplitCommList* pAcctSplitCommList = dynamic_cast <AcctSplitCommList*> ( getParent()->getParent()->getParent() );
   pAcctSplitCommList->getAccountNum ( dstrAccountNum );

   MFAccount* pMFAccount;
   getWorkSession().getMFAccount ( idDataGroup, dstrAccountNum, pMFAccount );

   if (pMFAccount != NULL && !dstrBrokerCode.empty())
   {
      pMFAccount->getBroker(pBroker,dstrBrokerCode,idDataGroup);
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY AcctSplitCommRep::validateSalesrepFund( const DString& dstrBroker,
                                                 const DString& dstrBranch,
                                                 const DString& dstrSlsRep,
                                                 const DString& dstrFund, 
                                                 const DString& dstrClass, 
                                                 const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("validateSalesrepFund"));
   
   AgentList agentList ( *this );
   
   //if( dstrFund.empty() || dstrClass.empty() )
   //{
   //   GETCURRENTHIGHESTSEVERITY ();
   //}
   
   DString dstrAccountNum,
      dstrValidationPassed;
   AcctSplitCommList* pAcctSplitCommList = dynamic_cast <AcctSplitCommList*> ( getParent()->getParent()->getParent() );
   pAcctSplitCommList->getAccountNum ( dstrAccountNum );
   dstrAccountNum.strip().upperCase();
   
   if( agentList.init2( dstrBroker, 
                        dstrBranch, 
                        dstrSlsRep, 
                        dstrFund, 
                        dstrClass, 
                        dstrAccountNum ) <= WARNING )
   {
      BFObjIter iterAgent( agentList, idDataGroup );

      iterAgent.begin();
      if( !iterAgent.end() )
      {
         iterAgent.getObject()->getField( ifds::ValidationPassed, dstrValidationPassed, idDataGroup,false );
         
         if (dstrValidationPassed != YES)
         {
            DString idiStr;
            addIDITagValue( idiStr, FUND, dstrFund );
            addIDITagValue( idiStr, CLASS, dstrClass );
            addIDITagValue( idiStr, I_("AGENT"), dstrSlsRep );

            ADDCONDITIONFROMFILEIDI( CND::ERR_FUND_CLASS_NOT_AVAILABLE_FOR_SALESREP, idiStr );
         }
      }
   }   

   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY AcctSplitCommRep::getBroker ( Broker *&pBroker, 
                                       const DString& dstrBrokerCode,
                                       const BFDataGroupId &idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, CLASSNAME, I_("getBroker") );

   pBroker = NULL;
   BrokerList brokerList ( *this );

   if( dstrBrokerCode != NULL_STRING && 
       brokerList.init( dstrBrokerCode, NULL_STRING, I_( "L" ) ) <= WARNING )
   {
      BFObjIter bfIter (brokerList, idDataGroup);
      bfIter.begin();

      while (!bfIter.end())
      {
         DString strBrokerCode;
         bfIter.getObject()->getField(ifds::BrokerCode, strBrokerCode, idDataGroup, false);
         strBrokerCode.strip().upperCase();

         if(strBrokerCode == dstrBrokerCode)
         {
            pBroker = dynamic_cast <Broker*> (bfIter.getObject());
            break;
         }

         ++bfIter;
      }
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY AcctSplitCommRep::updateSvcAgentRelatedChanges(const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, CLASSNAME, I_("updateSvcAgentRelatedChanges") );

   DString dstrAccountNum;
   AcctSplitCommList* pAcctSplitCommList = dynamic_cast <AcctSplitCommList*> ( getParent()->getParent()->getParent() );
   pAcctSplitCommList->getAccountNum ( dstrAccountNum );

   MFAccount* pMFAccount;
   getWorkSession().getMFAccount ( idDataGroup, dstrAccountNum, pMFAccount );

   if (pMFAccount != NULL )
   {
      DString dstrBrokerCode,
         dstrBranchCode,
         dstrSlsRepCode;

      getField ( ifds::AgencyCode, dstrBrokerCode, idDataGroup,  false);
      getField ( ifds::BranchCode, dstrBranchCode, idDataGroup,  false);
      getField ( ifds::AgentCode, dstrSlsRepCode, idDataGroup,  false);

      dstrBrokerCode.strip().upperCase();
      dstrBranchCode.strip().upperCase();
      dstrSlsRepCode.strip().upperCase();

      pMFAccount->setField(ifds::BrokerCode,dstrBrokerCode,idDataGroup, false, true, false);
      pMFAccount->setField(ifds::BranchCode,dstrBranchCode,idDataGroup, false, true, false);
      pMFAccount->setField(ifds::Slsrep,dstrSlsRepCode,idDataGroup, false, true, false);
      pMFAccount->setField(ifds::ServiceAgentUpdated,I_("Y"),idDataGroup, false, true, false);
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY AcctSplitCommRep::validateServiceAgentUpdated(const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateServiceAgentUpdated" ) );

   DString autoUpdateSvcAgent;
   getField( ifds::AutoUpdateSvcAgent, autoUpdateSvcAgent, idDataGroup, false );

   if( (isFieldUpdated (ifds::AgencyCode,   idDataGroup) || 
        isFieldUpdated (ifds::BranchCode,   idDataGroup) || 
        isFieldUpdated (ifds::AgentCode,   idDataGroup) ) && 
       (autoUpdateSvcAgent == I_("Y")) && !isSameCompensationServiceAgent(idDataGroup))
   {
      getErrMsg( IFASTERR::SERVICE_AGENT_CHANGED_BY_COMPENSATION_AGENT, 
                 CND::ERR_SERVICE_AGENT_CHANGED_BY_COMPENSATION_AGENT, 
                 CND::WARN_SERVICE_AGENT_CHANGED_BY_COMPENSATION_AGENT, 
                 idDataGroup);
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY AcctSplitCommRep::doValidateAll( const BFDataGroupId& idDataGroup, long lValidateGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doValidateAll" ) );

   validateServiceAgentUpdated(idDataGroup);

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
bool AcctSplitCommRep::isSameCompensationServiceAgent( const BFDataGroupId& idDataGroup)
{
   bool bReturn = true;
   DString dstrAccountNum;
   AcctSplitCommList* pAcctSplitCommList = dynamic_cast <AcctSplitCommList*> ( getParent()->getParent()->getParent() );
   pAcctSplitCommList->getAccountNum ( dstrAccountNum );

   MFAccount* pMFAccount;
   getWorkSession().getMFAccount ( idDataGroup, dstrAccountNum, pMFAccount );

   DString dstrBrokerCode,
      dstrBranchCode,
      dstrSlsRepCode,
      dstrSvcBrokerCode,
      dstrSvcBranchCode,
      dstrSvcSlsRepCode;

   getField ( ifds::AgencyCode, dstrBrokerCode, idDataGroup,  false);
   getField ( ifds::BranchCode, dstrBranchCode, idDataGroup,  false);
   getField ( ifds::AgentCode, dstrSlsRepCode, idDataGroup,  false);

   dstrBrokerCode.strip().upperCase();
   dstrBranchCode.strip().upperCase();
   dstrSlsRepCode.strip().upperCase();

   if (pMFAccount != NULL )
   {
      pMFAccount->getField( ifds::BrokerCode, dstrSvcBrokerCode, idDataGroup, false );
      pMFAccount->getField( ifds::BranchCode, dstrSvcBranchCode, idDataGroup, false );
      pMFAccount->getField( ifds::Slsrep, dstrSvcBranchCode, idDataGroup, false );
   }

   dstrSvcBrokerCode.strip().upperCase();
   dstrSvcBranchCode.strip().upperCase();
   dstrSvcSlsRepCode.strip().upperCase();

   if( (dstrSvcBrokerCode != dstrBrokerCode) || 
       (dstrSvcBranchCode != dstrBranchCode) ||
       (dstrSlsRepCode != dstrSvcBranchCode))
   {
      bReturn = false;
   }

   return bReturn;
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/AcctSplitCommRep.cpp-arc  $
// 
//    Rev 1.27   Jul 11 2012 22:41:52   dchatcha
// IN# 2994672 - Block Service Unit Transfers, simplified logic that let account cbo update b\b\s
// 
//    Rev 1.26   Jul 11 2012 22:20:16   dchatcha
// IN# 2994672 - Block Service Unit Transfers.
// 
//    Rev 1.25   Jul 10 2012 18:35:58   dchatcha
// IN# 2994672 - Block Service Unit Transfers.
// 
//    Rev 1.24   Jul 09 2012 19:21:14   dchatcha
// IN# 2994672 - Block Service Unit Transfers.
// 
//    Rev 1.23   Jun 21 2012 10:01:12   panatcha
// IN2988339 -  New account setup issue in Desktop
// 
//    Rev 1.22   Jun 21 2012 09:55:42   panatcha
// IN2988339 -  New account setup issue in Desktop
// 
//    Rev 1.21   May 18 2012 15:23:36   dchatcha
// P0186479 FN10 -Gap 14G - Block Service Unit Transfers, revise code.
// 
//    Rev 1.20   May 14 2012 16:22:46   dchatcha
// P0186479 FN10 -Gap 14G - Block Service Unit Transfers.
// 
//    Rev 1.19   May 14 2012 15:43:16   dchatcha
// P0186479 FN10 -Gap 14G - Block Service Unit Transfers.
// 
//    Rev 1.18   Jun 15 2005 19:09:20   popescu
// Incident # 327862 - validation will not be performed for the existing data objects - read from the database
// 
//    Rev 1.17   Nov 14 2004 14:25:22   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.16   Mar 21 2003 17:56:10   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.15   Mar 05 2003 14:37:30   HSUCHIN
// PTS 10014446 - validation effective date of broker/branch/sales rep
// 
//    Rev 1.14   Oct 29 2002 11:34:40   HSUCHIN
// sync up with release 49 - 1.13
// 
//    Rev 1.13   Oct 09 2002 23:53:58   PURDYECH
// PVCS Database Conversion
// 
//    Rev 1.12   Aug 29 2002 12:54:58   SMITHDAV
// ClientLocale and typed field changes.
// 
//    Rev 1.11   Aug 13 2002 15:08:18   HSUCHIN
// bug fix for cancel from coa. 
// 
//    Rev 1.10   Aug 08 2002 15:21:38   HSUCHIN
// bug fix to doapplyrelated changes to force validation on cross edit fields
// 
//    Rev 1.9   Jul 18 2002 17:04:18   HSUCHIN
// PTS - 10009022 - bug fix for duplicate validation of sales rep. 
// 
//    Rev 1.8   22 May 2002 18:26:18   PURDYECH
// BFData Implementation
// 
//    Rev 1.7   23 Nov 2001 11:04:50   HSUCHIN
// BranchCode enable/disable functionality fix
// 
//    Rev 1.6   16 Nov 2001 16:30:36   HSUCHIN
// minor fix for required field
// 
//    Rev 1.5   Nov 01 2001 09:57:04   ZHANGCEL
// Fixed the bugs regarding of BrokerName, BranchName and SaleRepName displaying problem
// 
//    Rev 1.4   25 Sep 2001 15:10:18   HSUCHIN
// removed dopresetfield and changed logic for renunciation calculation
// 
//    Rev 1.3   13 Sep 2001 10:22:10   HSUCHIN
// changed so that full default values now only occurs during new account setup and default values treated as Non dummy
// 
//    Rev 1.2   03 Sep 2001 13:22:00   HSUCHIN
// code cleanup and new bus rule enhancement
// 
//    Rev 1.1   29 Aug 2001 16:10:58   HSUCHIN
// added enhancements and validations
// 
//    Rev 1.0   23 Aug 2001 14:51:12   HSUCHIN
// Initial revision.
*/

