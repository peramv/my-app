

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
// ^FILE   : RegPlanTransferSearchCriteria.cpp
// ^AUTHOR : Mihai Buzila
// ^DATE   : November 4, 2016
//
// ^CLASS    : RegPlanTransferSearchCriteria
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "regplantransfersearchcriteria.hpp"
#include "MgmtCoOptions.hpp"
#include <ifastdataimpl\dse_dstc0472_req.hpp>
#include "regplantransferlist.hpp"
#include "broker.hpp"
#include "brokerlist.hpp"
#include "branchlist.hpp"
#include "branch.hpp"
#include "agentlist.hpp"
#include "agent.hpp"
#include "translationtablebyasyncreading.hpp"
#include "mgmtco.hpp"

namespace
{
   const I_CHAR * const CLASSNAME         = I_( "RegPlanTransferSearchCriteria" );
   const I_CHAR * const YES               = I_( "Y" );

}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId RegTransferSearchCriteria;
   extern CLASS_IMPORT const BFTextFieldId RegPlanTransferSrchHeadingSet;
   extern CLASS_IMPORT const BFTextFieldId BrokerName;
   extern CLASS_IMPORT const BFTextFieldId BranchName;
   extern CLASS_IMPORT const BFTextFieldId SlsrepName;
   extern CLASS_IMPORT const BFTextFieldId SlsrepAltName;
   extern CLASS_IMPORT const BFTextFieldId RepByBranch;
   extern CLASS_IMPORT const BFTextFieldId BranchCode;
}

namespace CND
{
   // Conditions used
   extern const long ERR_BROKER_EMPTY;
   extern const long ERR_BRANCH_EMPTY;
   extern const long ERR_SALES_REP_EMPTY;
   extern const long ERR_AGENT_NOT_FOUND_FOR_BROKER_BRANCH;
   extern CLASS_IMPORT const long ERR_NO_BRANCH_FOUND;
   extern const long ERR_ACCOUNT_EMPTY;
   extern const long ERR_INVALID_INSTITUTION_CODE;
   extern const long WARN_INVALID_INSTITUTION_CODE;
}

namespace REG_TRANSF_SEARCH_CRITERIA
{
   extern CLASS_EXPORT I_CHAR* const ACCOUNT_NUM    = I_("AccountNum");
   const I_CHAR* const BRANCH_BROKER_SLSREP         = I_("BranchBrokerSlsrep");
   const I_CHAR* const EXTERNAL_INSTITUTION         = I_("ExternalInstitution");
   const I_CHAR* const EXTERNAL_INSTITUTION_ACCT    = I_("ExternalInstitutionAcct");
   extern CLASS_EXPORT const BFFieldId Validation_OK(100);
}

namespace IFASTERR
{
   extern CLASS_IMPORT I_CHAR * const INVALID_INSTITUTION_CODE;
}


//-------------------------------------------------------------------
const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = {
//  Field DD Id,            State Flags,             Group Flags 
   { ifds::SrchAccountNum,                BFCBO::NONE, 0}, 
   { ifds::RegTransferSearchCriteria,     BFCBO::NONE, 0}, 
   { ifds::RegPlanTransferSrchHeadingSet, BFCBO::NONE, 0}, 
   { ifds::SrchExtInst,                   BFCBO::NONE, 0}, 
   { ifds::SrchExtInstName,               BFCBO::NONE, 0}, 
   { ifds::SrchExtInstAcct,               BFCBO::NONE, 0}, 
   { ifds::SrchBroker,                    BFCBO::NONE, 0}, 
   { ifds::SrchBranch,                    BFCBO::NONE, 0}, 
   { ifds::SrchSlsrep,                    BFCBO::NONE, 0}, 
   { ifds::BrokerName,                    BFCBO::NONE, 0}, 
   { ifds::BranchName,                    BFCBO::NONE, 0}, 
   { ifds::SlsrepName,                    BFCBO::NONE, 0}, 
   { ifds::SlsrepAltName,                 BFCBO::NONE, 0}, 
};

static const int NUM_FIELDS = sizeof(classFieldInfo) / sizeof(BFCBO::CLASS_FIELD_INFO);

//****************************************************************************
RegPlanTransferSearchCriteria::RegPlanTransferSearchCriteria( BFAbstractCBO &parent )
: MFCanBFCbo( parent )
{
   TRACE_CONSTRUCTOR( CLASSNAME , NULL_STRING );
    registerMemberData( NUM_FIELDS, (const CLASS_FIELD_INFO *)&classFieldInfo, 0, NULL );
}

//****************************************************************************
RegPlanTransferSearchCriteria::~RegPlanTransferSearchCriteria()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}     

//****************************************************************************
SEVERITY RegPlanTransferSearchCriteria::init( const BFDataGroupId& idDataGroup,
   const DString& dstrTrack /*= I_("N")*/, 
   const DString& dstrPageName /*= NULL_STRING*/)
{
   MAKEFRAME2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("init") );
   setField(ifds::RegTransferSearchCriteria, I_("AccountNum"), BF::HOST, false, false, false);

   if( !slsRepByBranch (idDataGroup) )
   {
      setFieldReadOnly( ifds::SrchBranch, idDataGroup, true );
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//**********************************************************************************
SEVERITY RegPlanTransferSearchCriteria::doApplyRelatedChanges( const BFFieldId& idField, const BFDataGroupId& idDataGroup )
{
   MAKEFRAME2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("doApplyRelatedChanges") );


   if (idField == ifds::SrchBranch)
   {
      if( slsRepByBranch (idDataGroup) ) // blank out the branchcode trigger the blanking out of salesrep
      {
         //clear the name, clears out related fields, branch
         DString _branchName = NULL_STRING;
         //mark the field as invalid and notify the observers
         setFieldNoValidate( ifds::SrchBranch, NULL_STRING, idDataGroup, false, false, true );
      }
      else // blank out salesrep -> trigger branch code assignment
      {

      }
   }
   else if(idField == ifds::RegTransferSearchCriteria)
   {
      SearchTypeRelatedChanges(idDataGroup );
   }
   else if (idField == ifds::SrchExtInst)
   {
      DString dstrExternalInstitution;
      getField (ifds::SrchExtInst, dstrExternalInstitution, idDataGroup, false);
      dstrExternalInstitution.stripAll().upperCase();

      MiscInfoExternalInstitutionList *pMiscInfoExternalInstitutionList = nullptr;
      if(getMgmtCo().getMiscInfoExternalInstitutionList(pMiscInfoExternalInstitutionList) <= WARNING && pMiscInfoExternalInstitutionList != NULL)
      {
         DString strDescription;
         bool isOther = false;
         if(isOther)
            strDescription = I_("");
         if(pMiscInfoExternalInstitutionList->getDescription(dstrExternalInstitution, strDescription, isOther))
         {
            setFieldReadOnly(ifds::SrchExtInstName, idDataGroup, !isOther);
            setField(ifds::SrchExtInstName, strDescription, idDataGroup, false, true);
         }
      }
   }

   return(GETCURRENTHIGHESTSEVERITY());
}


//****************************************************************************************
void RegPlanTransferSearchCriteria::SearchTypeRelatedChanges(const BFDataGroupId& idDataGroup )
{


   DString dstrSearchType;
   getField(ifds::RegTransferSearchCriteria, dstrSearchType, idDataGroup, false);

   BFFieldId lFieldIds1[4] = { ifds::NullFieldId, ifds::NullFieldId, ifds::NullFieldId, ifds::NullFieldId};

   BFFieldId lFieldIds2[10] = { ifds::NullFieldId, ifds::NullFieldId, ifds::NullFieldId, ifds::NullFieldId, ifds::NullFieldId, ifds::NullFieldId, ifds::NullFieldId, ifds::NullFieldId, ifds::NullFieldId, ifds::NullFieldId};

   BFFieldId lFieldIds3[6] = { ifds::SrchExtInstName, ifds::BrokerName, ifds::BranchName, ifds::SlsrepName, ifds::SlsrepAltName, ifds::NullFieldId };

   //clearDataGroupErrors(idDataGroup );

   if( dstrSearchType == REG_TRANSF_SEARCH_CRITERIA::ACCOUNT_NUM )
   {
      lFieldIds1[0] = ifds::SrchAccountNum;

      lFieldIds2[0] = ifds::SrchExtInst;
      lFieldIds2[1] = ifds::SrchExtInstAcct;
      lFieldIds2[2] = ifds::SrchBroker;    
      lFieldIds2[3] = ifds::SrchBranch;    
      lFieldIds2[4] = ifds::SrchSlsrep;    
   }
   else if(dstrSearchType == REG_TRANSF_SEARCH_CRITERIA::BRANCH_BROKER_SLSREP)
   {
      lFieldIds1[0] = ifds::SrchBroker;    
      
      lFieldIds2[0] = ifds::SrchBranch;    
      lFieldIds2[1] = ifds::SrchSlsrep;    
      lFieldIds2[2] = ifds::SrchAccountNum;
      lFieldIds2[3] = ifds::SrchExtInst;
      lFieldIds2[4] = ifds::SrchExtInstAcct;
   }
   else if(dstrSearchType == REG_TRANSF_SEARCH_CRITERIA::EXTERNAL_INSTITUTION)
   {
      lFieldIds1[0] = ifds::SrchExtInst;

      lFieldIds2[0] = ifds::SrchAccountNum;
      lFieldIds2[1] = ifds::SrchExtInstAcct;
      lFieldIds2[2] = ifds::SrchBroker;    
      lFieldIds2[3] = ifds::SrchBranch;    
      lFieldIds2[4] = ifds::SrchSlsrep;    
   }
   else if(dstrSearchType == REG_TRANSF_SEARCH_CRITERIA::EXTERNAL_INSTITUTION_ACCT)
   {
      lFieldIds1[0] = ifds::SrchExtInstAcct;

      lFieldIds2[0] = ifds::SrchAccountNum;
      lFieldIds2[1] = ifds::SrchExtInst;
      lFieldIds2[2] = ifds::SrchBroker;    
      lFieldIds2[3] = ifds::SrchBranch;    
      lFieldIds2[4] = ifds::SrchSlsrep;    
   }
   else
      return;

   clearFieldValues( lFieldIds1,idDataGroup);
   clearFieldValues( lFieldIds2,idDataGroup);
   clearFieldValues( lFieldIds3,idDataGroup);

   setFieldsAsRequired( lFieldIds1,idDataGroup,true );
   setFieldsAsRequired( lFieldIds2,idDataGroup,false );
   setFieldsAsRequired( lFieldIds3,idDataGroup,false );
   

}
//*********************************************************************************
void RegPlanTransferSearchCriteria::setFieldsAsRequired( const BFFieldId idField[], const BFDataGroupId& idDataGroup,bool bReqired )
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
void RegPlanTransferSearchCriteria::clearFieldValues( const BFFieldId idField[], const BFDataGroupId& idDataGroup)
{
   int i = 0;  
   while( idField[i] != ifds::NullFieldId )
   {
      //clearFieldErrors(idField[i], idDataGroup);
      setFieldNoValidate( idField[i],NULL_STRING,idDataGroup,false,true,true );
      i++;
   }
}

//*****************************************************************************************
void RegPlanTransferSearchCriteria::clearUpdateFlags(const BFDataGroupId& idDataGroup)
{
   clearUpdatedFlags( idDataGroup );
   setAllFieldsValid( idDataGroup );
}

//****************************************************************************
SEVERITY RegPlanTransferSearchCriteria::getRegPlanTransferList( RegPlanTransferList *&pRegPlanTransferList, const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getRegPlanTransferList" ) );
 
   DString dstrRegTransferSearchCriteria;
   getField(ifds::RegTransferSearchCriteria, dstrRegTransferSearchCriteria, idDataGroup);

   DString dstrAccountNum;
   DString dstrSrchBroker;
   DString dstrSrchBranch;
   DString dstrSrchSlsrep;
   DString dstrSrchExtInst;
   DString dstrSrchExtInstName;
   DString dstrSrchExtInstAcct;

   if(REG_TRANSF_SEARCH_CRITERIA::ACCOUNT_NUM == dstrRegTransferSearchCriteria)
   {
      getField(ifds::SrchAccountNum, dstrAccountNum, idDataGroup);
   }
   else if(REG_TRANSF_SEARCH_CRITERIA::BRANCH_BROKER_SLSREP == dstrRegTransferSearchCriteria)
   {
      getField(ifds::SrchBroker, dstrSrchBroker, idDataGroup);
      getField(ifds::SrchBranch, dstrSrchBranch, idDataGroup);
      getField(ifds::SrchSlsrep, dstrSrchSlsrep, idDataGroup);
   }
   else if(REG_TRANSF_SEARCH_CRITERIA::EXTERNAL_INSTITUTION == dstrRegTransferSearchCriteria)
   {
      getField(ifds::SrchExtInst, dstrSrchExtInst, idDataGroup);
      getField(ifds::SrchExtInstName, dstrSrchExtInstName, idDataGroup);
   }
   else if(REG_TRANSF_SEARCH_CRITERIA::EXTERNAL_INSTITUTION_ACCT == dstrRegTransferSearchCriteria)
   {
      getField(ifds::SrchExtInstAcct, dstrSrchExtInstAcct, idDataGroup);
   }
   
   pRegPlanTransferList->init( idDataGroup, dstrAccountNum, N, NULL_STRING, dstrSrchBroker, dstrSrchBranch, dstrSrchSlsrep, dstrSrchExtInst, dstrSrchExtInstName, dstrSrchExtInstAcct);

    return(GETCURRENTHIGHESTSEVERITY());
}

bool RegPlanTransferSearchCriteria::slsRepByBranch ( const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "slsRepByBranc" ) );

   if( _salesRepByBranch == NULL_STRING )
   {
      getWorkSession().getOption( ifds::RepByBranch, _salesRepByBranch, idDataGroup, false );
   }

   return( _salesRepByBranch == YES );
}

SEVERITY RegPlanTransferSearchCriteria::doValidateField( const BFFieldId& idField, const DString& strValue, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doValidateField" ) );
   SEVERITY sevRtn = NO_CONDITION;
   DString dstrSearchType;
   getField(ifds::RegTransferSearchCriteria, dstrSearchType, idDataGroup, false);

   if(dstrSearchType == REG_TRANSF_SEARCH_CRITERIA::BRANCH_BROKER_SLSREP)
   {
      if (idField == ifds::SrchBroker)
      {
         DString brokerCode (strValue);
         brokerCode.stripAll();

         if (brokerCode.empty())
         {
            ADDCONDITIONFROMFILE (CND::ERR_BROKER_EMPTY);
         }
         else
         {
            checkBroker (brokerCode, idDataGroup, true);
         }
      }
      else if (idField == ifds::SrchBranch)
      {
         DString brokerCode, 
            branchCode (strValue);

         branchCode.stripAll();
         if (!branchCode.empty() || !slsRepByBranch (idDataGroup))
         //{
         //   ADDCONDITIONFROMFILE (CND::ERR_BRANCH_EMPTY);
         //}
         //else
         {
            getField (ifds::SrchBroker, brokerCode, idDataGroup);
            if (validateField (ifds::SrchBroker, brokerCode, idDataGroup) <= WARNING)
            {
               checkBranches (branchCode, idDataGroup, true);
            }
            else
            {
               CLEARCONDITIONS ();
            }
         }
      }
      else if( idField == ifds::SrchSlsrep )
      {
         DString branchCode;
         DString agentCode(strValue);

         {
            agentCode.stripAll();
            if(agentCode == NULL_STRING )
            {
               setFieldNoValidate( ifds::SlsrepName, I_(""), idDataGroup, true, true, true, false);
               setFieldNoValidate( ifds::SlsrepAltName, I_(""), idDataGroup, true, true, true, false);
               if (!slsRepByBranch (idDataGroup) ) 
               {
                  setFieldNoValidate( ifds::SrchBranch, I_(""), idDataGroup, false, false, true );
                  setFieldNoValidate( ifds::BranchName, I_(""), idDataGroup, true, true, true, false);
               }
            }
            else
            {
               if( slsRepByBranch ( idDataGroup ) )
               {
                  getField( ifds::SrchBranch, branchCode, idDataGroup );
                  sevRtn = validateField( ifds::SrchBranch, branchCode, idDataGroup );
               }
               else
               {
                  sevRtn = NO_CONDITION;
               }

               if( sevRtn <= WARNING )
               {
                  bool bNewAgent = false;
                  checkAgents( strValue, idDataGroup, true, bNewAgent );
               }
            }

            if(GETCURRENTHIGHESTSEVERITY () <= WARNING)
            {
               //Rule: If NewBusiness-92 is No and SegClient = Yes issue warning 
               //   "Salesperson is not permitted new business activity"
               AgentList agentList( *this );
               DString brokerCode,
                  slsrepCode;


               getField( ifds::SrchBroker, brokerCode, idDataGroup );
               getField( ifds::SrchBranch, branchCode, idDataGroup );
               getField( ifds::SrchSlsrep, slsrepCode, idDataGroup );
               if( slsrepCode != NULL_STRING )
               {
                  agentList.init( brokerCode, branchCode, slsrepCode );
               }
            }
         }
      }
   }
   else if(dstrSearchType == REG_TRANSF_SEARCH_CRITERIA::ACCOUNT_NUM)
   {
      if( idField == ifds::SrchAccountNum && (I_("0") == strValue || I_("") == strValue))
      {
         ADDCONDITIONFROMFILE(CND::ERR_ACCOUNT_EMPTY)
         setFieldUpdated(ifds::SrchAccountNum, idDataGroup, true);
      }
   }
   else if(idField == ifds::SrchExtInst)
   {
      validateExternalInst(strValue, idDataGroup);
   }
   return GETCURRENTHIGHESTSEVERITY();
}

SEVERITY RegPlanTransferSearchCriteria::checkBroker( const DString& brokerCode, const BFDataGroupId& idDataGroup, bool condition_returned )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "checkBroker" ) );

   Broker *pBroker (NULL);
   if ( getBroker (pBroker, brokerCode, idDataGroup) <= WARNING && pBroker) 
   {
      _brokerName = NULL_STRING;

      DString brokerName;
      pBroker->getField( ifds::BrokerName, brokerName, idDataGroup );

      parseName (brokerName, _brokerName);	

   }
   
   setFieldNoValidate( ifds::BrokerName, _brokerName, idDataGroup, true, true, true, false);

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY RegPlanTransferSearchCriteria::checkBranches( const DString& branchCode, const BFDataGroupId& idDataGroup, bool condition_returned )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "checkBranches" ) );

   BranchList branchList( *this );
   DString brokerCode;

   getField( ifds::SrchBroker, brokerCode, idDataGroup );
   //checks for the validity of the branch code. by making a view call, and raising a condition
   //we do not want to make the view call when the branch code is NULL, because the view will
   //return us all the branches for this broker
   if( branchCode != NULL_STRING && 
       branchList.init( brokerCode, branchCode ) <= WARNING )
   {
      BFObjIter bfIter( branchList, idDataGroup );
      DString branchName;

      bfIter.begin();
      if( !bfIter.end() )
      {
         DString branchName;
         Branch* pBranch = dynamic_cast <Branch*> ( bfIter.getObject() );
         pBranch->getField( ifds::BranchName, branchName, idDataGroup );

         parseName (branchName, _branchName);
      }
   }
   else
   {
      _branchName = NULL_STRING;

   }
   setFieldNoValidate( ifds::BranchName, _branchName, idDataGroup, true, true, true, false);
   if( condition_returned == true )
      return(GETCURRENTHIGHESTSEVERITY());
   else
      return(NO_CONDITION);
}

//******************************************************************************
void RegPlanTransferSearchCriteria::parseName (const DString &originalName, DString &newName)
{
   if( originalName.find( I_CHAR('&')) == DString::npos )
   {
      newName = originalName;
      return;
   }

   DString tmpBrokerName = originalName;
   int iPos = 0;
   bool bFound = false;

   newName = NULL_STRING;

   while (iPos != -1)
   {
      iPos = tmpBrokerName.find( I_CHAR('&') );

      if (iPos == -1 && bFound)
      {
         newName += tmpBrokerName;
      }
      else
      {
         newName += tmpBrokerName.substr (0, iPos + 1) + I_("&");
         tmpBrokerName = tmpBrokerName.substr (iPos + 1, tmpBrokerName.length ());
         bFound = true;
      }
   }
}

//******************************************************************************
SEVERITY RegPlanTransferSearchCriteria::getBroker( Broker *&pBroker, const DString& dstrBrokerCode, const BFDataGroupId &idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, CLASSNAME, I_("getBroker") );
   pBroker = NULL;

   SEVERITY sevRtn = NO_CONDITION;

   if (!dstrBrokerCode.empty())
   {
      DString strKey (I_("Broker=") + dstrBrokerCode);
//look for the list
      BrokerList *pBrokerList = dynamic_cast <BrokerList*> (getObject ( strKey, idDataGroup));
      if (!pBrokerList) //make view call
      {
         pBrokerList = new BrokerList (*this);
         sevRtn = pBrokerList->init2 ( dstrBrokerCode, NULL_STRING, I_("L"), NULL_STRING , NULL_STRING );

         if ( sevRtn <= WARNING )
         {
            setObject ( pBrokerList, strKey, OBJ_ACTIVITY_NONE, idDataGroup );
         }            
         else 
         {
            delete pBrokerList;
            pBrokerList = NULL;
         }
      }
//get the broker
      if (pBrokerList)
      {
         BFObjIter bfIter (*pBrokerList, idDataGroup);

         if (!bfIter.end())
         {
            pBroker = dynamic_cast <Broker*> (bfIter.getObject());
         }
      }
   }
   return GETCURRENTHIGHESTSEVERITY();
}
//******************************************************************************
SEVERITY RegPlanTransferSearchCriteria::checkAgents( const DString& slsrepCode, const BFDataGroupId& idDataGroup, bool condition_returned, bool& bNewAgent )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "checkAgents" ) );

   AgentList agentList( *this );
   Agent* pAgent = NULL;
   DString brokerCode, branchCode;

   getField( ifds::SrchBroker, brokerCode, idDataGroup );
   getField( ifds::SrchBranch, branchCode, idDataGroup );

   DString dstrAccountNum;
   SEVERITY sevRtn;
   sevRtn = agentList.init2( brokerCode, branchCode, slsrepCode, NULL_STRING, NULL_STRING, dstrAccountNum, NULL_STRING ); 

   if (sevRtn > WARNING )
   {
      int count = CONDITIONCOUNT();
      Condition   *c = NULL;
      for( int i = 0; i < count; i++ )
      {
         c = GETCONDITION( i );
         int condCode = c->getCode();
         if ( condCode == CND::ERR_NO_BRANCH_FOUND )
         {
            CLEARCONDITION( i );
            break;
         }
      }

      DString _slsrepCode(slsrepCode);

      //getField (ifds::CreateRep, createRep, idDataGroup, false);
      DString idiStr;
      addIDITagValue( idiStr, I_("AGENT"), _slsrepCode.upperCase() );
      addIDITagValue( idiStr, I_("BROKER"), brokerCode.upperCase() );
      addIDITagValue( idiStr, I_("BRANCH"), branchCode.upperCase() );
      ADDCONDITIONFROMFILEIDI( CND::ERR_AGENT_NOT_FOUND_FOR_BROKER_BRANCH, idiStr.c_str() ); 
   }
   //checks for the validity of the agent code. by making a view call, and raising a condition
   //we do not want to make the view call when the slslrep code is NULL, because the view will
   //return us all the agents for this broker and branch
   if( slsrepCode != NULL_STRING && sevRtn <= WARNING )
   {
      BFObjIter bfIter( agentList, idDataGroup );
      int iNumItems = bfIter.getNumberOfItemsInList ();
      bNewAgent = iNumItems > 0  ? false : true;
      DString slsrepName;
      DString slsrepAltName;

      bfIter.begin();
      if( !bfIter.end() )
      {
         DString branchName, agentName;
         pAgent = dynamic_cast <Agent*> ( bfIter.getObject() );
         pAgent->getField( ifds::SlsrepName, agentName, idDataGroup );
         pAgent->getField( ifds::SlsrepAltName, _agentAltName, idDataGroup );
         pAgent->getField( ifds::BranchCode, _branchCode, idDataGroup );
         pAgent->getField( ifds::BranchName, branchName, idDataGroup );

         parseName (branchName, _branchName);
         parseName (agentName, _agentName);
      }
   }
   else
   {
      _agentName = NULL_STRING;
      _agentAltName = NULL_STRING;
      _branchCode = NULL_STRING;
      _branchName = NULL_STRING;
      bNewAgent = true;
   }

   setFieldNoValidate( ifds::SlsrepName, _agentName, idDataGroup, true, true, true, false);
   setFieldNoValidate( ifds::SlsrepAltName, _agentAltName, idDataGroup, true, true, true, false);
   if ( !slsRepByBranch (idDataGroup) ) 
   {
      setFieldNoValidate( ifds::SrchBranch, _branchCode, idDataGroup, false, false, true );
      setFieldNoValidate( ifds::BranchName, _branchName, idDataGroup, true, true, true, false);
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

void RegPlanTransferSearchCriteria::doReset ( const BFDataGroupId& idDataGroup )
{
   //MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "checkAgents" ) );
   //setField( ifds::SrchAccountNum, I_(""), idDataGroup, false, true);
   //setField(ifds::RegTransferSearchCriteria, I_("AccountNum"), BF::HOST, false, false, false);
   //setField(ifds::RegTransferSearchCriteria, REG_TRANSF_SEARCH_CRITERIA::ACCOUNT_NUM, idDataGroup, false);

};

SEVERITY RegPlanTransferSearchCriteria::validateExternalInst(const DString& strValue, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateExternalInst" ) );

   MiscInfoExternalInstitutionList *pMiscInfoExternalInstitutionList = nullptr;
   if(getMgmtCo().getMiscInfoExternalInstitutionList(pMiscInfoExternalInstitutionList) <= WARNING && pMiscInfoExternalInstitutionList != NULL)
   {
      DString lookupValue(strValue);
      lookupValue.stripAll().upperCase();

      if(!pMiscInfoExternalInstitutionList->codeExists(lookupValue))
      {
         getErrMsg(IFASTERR::INVALID_INSTITUTION_CODE, CND::ERR_INVALID_INSTITUTION_CODE, CND::WARN_INVALID_INSTITUTION_CODE, idDataGroup );
      };
   }


   return(GETCURRENTHIGHESTSEVERITY());
}
