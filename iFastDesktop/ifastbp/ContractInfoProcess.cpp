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
//    Copyright 2005 by International Financial Data Services
//
//*****************************************************************************
//
// ^FILE   : ContractInfoProcess.cpp
// ^AUTHOR : Celia Zhang
// ^DATE   : 02/01/2000
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : ContractInfoProcess
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include "stdafx.h"
#include "contractinfoprocess.hpp"
#include <ifastcbo\contractinfo.hpp>
#include <ifastcbo\contractinfolist.hpp>
#include <ifastcbo\taxtyperule.hpp>
#include "contractinfoprocessincludes.h"
#include <ifastcbo\taxtyperulelist.hpp>
#include <ifastcbo\entitylist.hpp>
#include <ifastcbo\entity.hpp>
#include <ifastcbo\mfaccount.hpp>
#include <ifastcbo\accountentityxref.hpp>
#include <ifastcbo\accountentityxrefobject.hpp>
#include <ifastdataimpl\dse_dstc0087_vw.hpp>
#include <ifastdataimpl\dse_dstc0050_req.hpp>
#include <ifastdataimpl\dse_dstc0050_vw.hpp>
#include <ifastdataimpl\dse_dstc0051_vw.hpp>
#include <ifastcbo\mastercontractlist.hpp>
#include <ifastcbo\mgmtco.hpp>
extern IFASTBP_LINKAGE const I_CHAR* CMD_GUI_CONTRACTINFO;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_CONTRACTINFO;
#include <bfproc\concreteprocesscreator.hpp>
static ConcreteProcessCreator< ContractInfoProcess > processCreator( CMD_BPROC_CONTRACTINFO );

namespace 
{
   // Trace literals
   const I_CHAR * const CLASSNAME   = I_( "ContractInfoProcess" );
   const I_CHAR * const Y           = I_( "Y" );
   const I_CHAR * const N           = I_( "N" );
}

namespace CONTRACT
{
   const I_CHAR * const ACCOUNT_NUMBER   = I_( "AccountNum" );
   const I_CHAR * const SHAREHOLD_NUMBER = I_( "ShareholderNum" );
   const I_CHAR * const TRANSID_EMPTY    = I_( "TransIdEmpty" );

   // Folowing parameters are for DofBirth checking stuffs
   const I_CHAR * const OWNER_ENTITYID      = I_( "OwnerEntityId" );
   const I_CHAR * const OWNER_NAME          = I_( "OwnerName" );
   const I_CHAR * const SPOUSE_ENTITYID     = I_( "SpouseEntityId" );
   const I_CHAR * const SPOUSE_NAME         = I_( "SpouseName" );
   const I_CHAR * const ASK_SPOUSE_DOFBIRTH = I_( "AskSpouseDofBirth" );
   const I_CHAR * const ASK_ENTITY_DOFBIRTH = I_( "AskEntityDofBirty" );
   const I_CHAR * const NON_ANNUITANT_ENTITY = I_( "NonAnnuitantEntity" );
}

namespace CND
{
   extern CLASS_IMPORT const long BP_ERR_UNKNOWN_EXCEPTION;
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId ShouldAskForDofBirth;
   extern CLASS_IMPORT const BFNumericFieldId AccountNum;
   extern CLASS_IMPORT const BFNumericFieldId ShrNum;

   // Take these out as soon as we have them in the view
   extern CLASS_IMPORT const BFDateFieldId GWOCotAnnivDate;
   extern CLASS_IMPORT const BFDateFieldId UserDefinedMaturityDate;
   extern CLASS_IMPORT const BFTextFieldId PorfolioIsRequried;
   extern CLASS_IMPORT const BFTextFieldId AcctOwnerName;

   // exposed fields to AWD-10 for SLF
   extern CLASS_IMPORT const BFTextFieldId BrokerCode;
   extern CLASS_IMPORT const BFTextFieldId BrokerName;
   extern CLASS_IMPORT const BFTextFieldId BranchCode;
   extern CLASS_IMPORT const BFTextFieldId BranchName;

   extern CLASS_IMPORT const BFTextFieldId Slsrep;
   extern CLASS_IMPORT const BFTextFieldId SlsrepName;
   extern CLASS_IMPORT const BFTextFieldId SlsrepAltName;

   extern CLASS_IMPORT const BFTextFieldId AltAccount;
   extern CLASS_IMPORT const BFTextFieldId XrefNum;

   extern CLASS_IMPORT const BFTextFieldId AnnuitantName;
   extern CLASS_IMPORT const BFTextFieldId SuccessorAnnuitantName;
   extern CLASS_IMPORT const BFTextFieldId SuccessorName;
}

namespace UAF
{
   extern CLASS_IMPORT I_CHAR * const SEG_FUND_MULTI_CONTRACT;
}

//******************************************************************************
//              Public Methods
//******************************************************************************

//CP20030319ContractInfoProcess::ContractInfoProcess() : 
ContractInfoProcess::ContractInfoProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: AbstractProcess( pGIC, pGIParent, rCommand )
, _pContractInfoList( NULL )
, _pMasterContractList( NULL)
, _rpChildGI( NULL )
, _bIsDuringNASU(false)
, _dstrNewShareholder(NULL_STRING)
, _dstrNewAccount(NULL_STRING)
{
   TRACE_CONSTRUCTOR(CLASSNAME, NULL_STRING );

   addSubstituteList( ifds::ContractListHeading );
   addSubstituteList( ifds::Status );

   addSubstituteList( ifds::ProvinceCanada );
///   addSubstituteList( ifds::MaturityType );

   addContainer( IFASTBP_PROC::CONTRACTINFO_LIST, true, BF::NullContainerId, true, I_("ContractInfo"));
   addContainer( IFASTBP_PROC::MFACCOUNT_CBO, false );
   addContainer( IFASTBP_PROC::MASTER_CONTRACT_LIST, true );

   addFieldDetails( ifds::AcctGroup, IFASTBP_PROC::CONTRACTINFO_LIST, SUBCLASS_PROCESS);//needed for multiple contarcts

   addFieldDetails( ifds::AccountNum, IFASTBP_PROC::MFACCOUNT_CBO );
   addFieldDetails( ifds::AcctGroupName, IFASTBP_PROC::MFACCOUNT_CBO );
   addFieldDetails( ifds::AcctStatus, IFASTBP_PROC::MFACCOUNT_CBO );
   addFieldDetails( ifds::AcctType, IFASTBP_PROC::MFACCOUNT_CBO );
   addFieldDetails( ifds::TaxType, IFASTBP_PROC::MFACCOUNT_CBO );
   addFieldDetails( ifds::BrokerCode, IFASTBP_PROC::MFACCOUNT_CBO );
   addFieldDetails( ifds::BrokerName, IFASTBP_PROC::MFACCOUNT_CBO );
   addFieldDetails( ifds::BranchCode, IFASTBP_PROC::MFACCOUNT_CBO );
   addFieldDetails( ifds::BranchName, IFASTBP_PROC::MFACCOUNT_CBO );
   addFieldDetails( ifds::Slsrep, IFASTBP_PROC::MFACCOUNT_CBO );
   addFieldDetails( ifds::SlsrepName, IFASTBP_PROC::MFACCOUNT_CBO );
   addFieldDetails( ifds::SlsrepAltName, IFASTBP_PROC::MFACCOUNT_CBO );
   addFieldDetails( ifds::AltAccount, IFASTBP_PROC::MFACCOUNT_CBO );
   addFieldDetails( ifds::XrefNum, IFASTBP_PROC::MFACCOUNT_CBO );
   addFieldDetails( ifds::AnnuitantName, IFASTBP_PROC::MFACCOUNT_CBO, SUBCLASS_PROCESS );
   addFieldDetails( ifds::SuccessorAnnuitantName, IFASTBP_PROC::MFACCOUNT_CBO, SUBCLASS_PROCESS );
   addFieldDetails( ifds::SuccessorName, IFASTBP_PROC::MFACCOUNT_CBO, SUBCLASS_PROCESS );
   addFieldDetails( ifds::DateOfReg, IFASTBP_PROC::MFACCOUNT_CBO, SUBCLASS_PROCESS );

   addFieldDetails( ifds::ShrNum, IFASTBP_PROC::MFACCOUNT_CBO);

   addFieldDetails( ifds::PendingTrade, IFASTBP_PROC::MFACCOUNT_CBO );

   addFieldDetails( ifds::EffectiveDate, IFASTBP_PROC::CONTRACTINFO_LIST );
   addFieldDetails( ifds::StopDate, IFASTBP_PROC::CONTRACTINFO_LIST );

   addFieldDetails( ifds::Username, IFASTBP_PROC::CONTRACTINFO_LIST );
   addFieldDetails( ifds::ProcessDate, IFASTBP_PROC::CONTRACTINFO_LIST );
   addFieldDetails( ifds::ModDate, IFASTBP_PROC::CONTRACTINFO_LIST );
   addFieldDetails( ifds::ModUser, IFASTBP_PROC::CONTRACTINFO_LIST );

   addFieldDetails( ifds::ContractType, IFASTBP_PROC::CONTRACTINFO_LIST );
   addFieldDetails( ifds::ContractTypeId, IFASTBP_PROC::CONTRACTINFO_LIST );
   addFieldDetails( ifds::PolicyNum, IFASTBP_PROC::CONTRACTINFO_LIST );

   addFieldDetails( ifds::ContractTerm, IFASTBP_PROC::CONTRACTINFO_LIST );
   addFieldDetails( ifds::ClsPerTerm, IFASTBP_PROC::CONTRACTINFO_LIST );
   addFieldDetails( ifds::ContractTermDesc, IFASTBP_PROC::CONTRACTINFO_LIST );
   addFieldDetails( ifds::IssueDate, IFASTBP_PROC::CONTRACTINFO_LIST );
   addFieldDetails( ifds::AnnivMonth, IFASTBP_PROC::CONTRACTINFO_LIST );
   addFieldDetails( ifds::AnnivDay, IFASTBP_PROC::CONTRACTINFO_LIST );
   addFieldDetails( ifds::LastResetDate, IFASTBP_PROC::CONTRACTINFO_LIST );
   addFieldDetails( ifds::VersionDesc, IFASTBP_PROC::CONTRACTINFO_LIST );
   addFieldDetails( ifds::EnableOverride, IFASTBP_PROC::CONTRACTINFO_LIST );
   addFieldDetails( ifds::EnableSegDates, IFASTBP_PROC::CONTRACTINFO_LIST );
   addFieldDetails( ifds::ProvinceCanada, IFASTBP_PROC::CONTRACTINFO_LIST );
   addFieldDetails( ifds::ProvinceName, IFASTBP_PROC::CONTRACTINFO_LIST );
   addFieldDetails( ifds::AgeBasedOn, IFASTBP_PROC::CONTRACTINFO_LIST );
   addFieldDetails( ifds::AgeBasedOnDesc, IFASTBP_PROC::CONTRACTINFO_LIST );
   addFieldDetails( ifds::LegalMaturityDate, IFASTBP_PROC::CONTRACTINFO_LIST );
   addFieldDetails( ifds::Status, IFASTBP_PROC::CONTRACTINFO_LIST );
   addFieldDetails( ifds::StatusDesc, IFASTBP_PROC::CONTRACTINFO_LIST );
   addFieldDetails( ifds::BailMaturityDate, IFASTBP_PROC::CONTRACTINFO_LIST );
   addFieldDetails( ifds::CotAcctVer, IFASTBP_PROC::CONTRACTINFO_LIST );
   addFieldDetails( ifds::CotAcctRid, IFASTBP_PROC::CONTRACTINFO_LIST );
   addFieldDetails( ifds::ContractMaturityDate, IFASTBP_PROC::CONTRACTINFO_LIST );
   addFieldDetails( ifds::CDStartDate, IFASTBP_PROC::CONTRACTINFO_LIST );
   addFieldDetails( ifds::RedAgeDate, IFASTBP_PROC::CONTRACTINFO_LIST );
   addFieldDetails( ifds::SegTransExist, IFASTBP_PROC::CONTRACTINFO_LIST );

   addFieldDetails( ifds::SuspectGuarType, IFASTBP_PROC::CONTRACTINFO_LIST );
   addFieldDetails( ifds::LWAAgeUsed, IFASTBP_PROC::CONTRACTINFO_LIST );
   addFieldDetails( ifds::LWARateApplied, IFASTBP_PROC::CONTRACTINFO_LIST );
   addFieldDetails( ifds::LWAStartDate, IFASTBP_PROC::CONTRACTINFO_LIST );
   addFieldDetails( ifds::LWAElectDate, IFASTBP_PROC::CONTRACTINFO_LIST );
   addFieldDetails( ifds::ReqUnitAdj, IFASTBP_PROC::CONTRACTINFO_LIST );
   addFieldDetails( ifds::RefMatDate, IFASTBP_PROC::CONTRACTINFO_LIST );
   addFieldDetails( ifds::ContractVer, IFASTBP_PROC::CONTRACTINFO_LIST );
   addFieldDetails( ifds::ContractMatBasedOn, IFASTBP_PROC::CONTRACTINFO_LIST );
   addFieldDetails( ifds::RequiresGuarUnitAdjust, IFASTBP_PROC::CONTRACTINFO_LIST );
   addFieldDetails( ifds::MaturityID, IFASTBP_PROC::CONTRACTINFO_LIST );

   addFieldDetails( ifds::ContractType, IFASTBP_PROC::MASTER_CONTRACT_LIST);
   addFieldDetails( ifds::ContMatDateBasedOn, BF::NullContainerId, SUBCLASS_PROCESS );
   addFieldDetails( ifds::MatDateBasedOn, BF::NullContainerId, SUBCLASS_PROCESS );
   addFieldDetails( ifds::IsGWOContract, BF::NullContainerId, SUBCLASS_PROCESS );
   addFieldDetails( ifds::GroupCode, IFASTBP_PROC::CONTRACTINFO_LIST );

   // Folowing Field is for DofBirth checking
   addFieldDetails( ifds::ShouldAskForDofBirth, IFASTBP_PROC::CONTRACTINFO_LIST );
   addFieldDetails( ifds::ModPerm, IFASTBP_PROC::CONTRACTINFO_LIST );

   addFieldDetails( ifds::SettleDate,        IFASTBP_PROC::CONTRACTINFO_LIST );
   addFieldDetails( ifds::GWOCotAnnivDate,   IFASTBP_PROC::CONTRACTINFO_LIST );
   addFieldDetails( ifds::GWOContract,       IFASTBP_PROC::CONTRACTINFO_LIST, SUBCLASS_PROCESS );
   addFieldDetails( ifds::IsNewAcctContract, IFASTBP_PROC::CONTRACTINFO_LIST, SUBCLASS_PROCESS );

   addFieldDetails( ifds::IsDuringNASU, IFASTBP_PROC::CONTRACTINFO_LIST, SUBCLASS_PROCESS );

   addFieldDetails( ifds::UserDefinedMaturityDate, IFASTBP_PROC::CONTRACTINFO_LIST );

	addFieldDetails (ifds::CMPolicyYear,	IFASTBP_PROC::CONTRACTINFO_LIST);
	addFieldDetails (ifds::CMPolicyTerm,	IFASTBP_PROC::CONTRACTINFO_LIST);
	addFieldDetails (ifds::CMMaturityDate,	IFASTBP_PROC::CONTRACTINFO_LIST);
   addFieldDetails (ifds::GuaranteeFeeAppl, IFASTBP_PROC::CONTRACTINFO_LIST);
}

//******************************************************************************
ContractInfoProcess::~ContractInfoProcess()
{
   TRACE_DESTRUCTOR( CLASSNAME );

   _rpChildGI = NULL;
}

//******************************************************************************
//              Protected Methods
//******************************************************************************

SEVERITY ContractInfoProcess::doInit()
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, DOINIT );
   SEVERITY sevRtn = SEVERE_ERROR;

   try
   {
      getParent()->getParameter( CONTRACT::TRANSID_EMPTY, strTransIdEmpty );
      getParent()->getParameter( CONTRACT::ACCOUNT_NUMBER, _strAccountNum );

      getParameter (NASULIT::CREATING_SHAREHOLDER, _dstrNewShareholder);
      getParameter (NASULIT::CREATING_ACCOUNT, _dstrNewAccount);

      _dstrNewShareholder.strip().upperCase();
      _dstrNewAccount.strip().upperCase();
      
      if(_dstrNewAccount == I_("Y") || _dstrNewShareholder == I_("Y"))
      {
         _bIsDuringNASU = true;
      }

      _strAccountNum.stripAll();

      MFAccount* pMFAccount = NULL;
      DSTCWorkSession* dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
      if( WARNING >= dstcWorkSession->getMFAccount(  getDataGroupId( ), _strAccountNum, pMFAccount ))
      {
         setContainer( IFASTBP_PROC::MFACCOUNT_CBO, pMFAccount );
         pMFAccount->getField(ifds::ShrNum, strShareholdNum, getDataGroupId(), false );
      }
   }
   catch( ConditionException &ce )
   {
      SETCONDITIONFROMEXCEPTION( ce );
   }
   catch( ... )
   {
      throw EXCEPTIONFROMFILE( CND::BP_ERR_UNKNOWN_EXCEPTION );
   }
   return(GETCURRENTHIGHESTSEVERITY());
}


//******************************************************************************

E_COMMANDRETURN ContractInfoProcess::doProcess()
{  
   MAKEFRAME2( CND::BPBASE_CONDITION, CLASSNAME, DOPROCESS );
   E_COMMANDRETURN rtn = CMD_FAILURE;

   try
   {
      if( isXMLAPIContext() )
      {
         rtn = CMD_MODELESS_INPROCESS;
      }
      else
      {
         getParent()->setParameter( CONTRACT::TRANSID_EMPTY, strTransIdEmpty );
         getParent()->setParameter( CONTRACT::SHAREHOLD_NUMBER, strShareholdNum );
         getParent()->setParameter( CONTRACT::ACCOUNT_NUMBER, _strAccountNum );
         // Folowing parameters are for DofBirth checking
         getParent()->setParameter( CONTRACT::OWNER_NAME, _dstrOwnerName );
         getParent()->setParameter( CONTRACT::SPOUSE_NAME, _dstrSpouseName );
         getParent()->setParameter( CONTRACT::ASK_SPOUSE_DOFBIRTH, _dstrAskDofBirthSp );
         getParent()->setParameter( CONTRACT::ASK_ENTITY_DOFBIRTH, _dstrAskDofBirthEntity );

         rtn = invokeCommand( this, CMD_GUI_CONTRACTINFO, PROC_NO_TYPE, isModal(), &_rpChildGI );
      }
   }
   catch( ConditionException &ce )
   {
      SETCONDITIONFROMEXCEPTION( ce );
   }
   catch( ... )
   {
      throw EXCEPTIONFROMFILE( CND::BP_ERR_UNKNOWN_EXCEPTION );
   }

   return(rtn);
}


//******************************************************************************
bool ContractInfoProcess::doModelessSetFocus( GenericInterface *rpGICaller )
{  // This is implemented to pass set focus on to child dialog.
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, DOMODELESSSETFOCUS );
   SEVERITY sevRtn = SEVERE_ERROR;

   bool bRtn = false;
   try
   {
      getParent()->getParameter( CONTRACT::TRANSID_EMPTY, strTransIdEmpty );
      getParent()->getParameter( CONTRACT::SHAREHOLD_NUMBER, strShareholdNum);
      getParent()->getParameter( CONTRACT::ACCOUNT_NUMBER, _strAccountNum );

      getParent()->setParameter( CONTRACT::TRANSID_EMPTY, strTransIdEmpty );
      getParent()->setParameter( CONTRACT::SHAREHOLD_NUMBER, strShareholdNum);
      getParent()->setParameter( CONTRACT::ACCOUNT_NUMBER, _strAccountNum );

      if( !( bRtn = _rpChildGI->refresh( this, NULL ) ) )
      {
         return(bRtn);// false
      }
      bRtn = _rpChildGI->modelessSetFocus( rpGICaller );
   }
   catch( ConditionException &ce )
   {
      SETCONDITIONFROMEXCEPTION( ce );
   }
   catch( ... )
   {
      assert( 0 );
      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, DOMODELESSSETFOCUS,
                      CND::BP_ERR_UNKNOWN_EXCEPTION );
   }

   return(bRtn);
}

//******************************************************************************
bool ContractInfoProcess::doModelessChildComplete( const Command &cmd )
{
   return( cmd.getKey() == CMD_GUI_CONTRACTINFO );
}


//******************************************************************************

bool ContractInfoProcess::doRefresh( GenericInterface *rpGICaller, const I_CHAR *szOriginalCommand )
{
   TRACE_METHOD( CLASSNAME, DOREFRESH );

   setParameter( CONTRACT::ACCOUNT_NUMBER, _strAccountNum );
   setParameter( CONTRACT::SHAREHOLD_NUMBER, strShareholdNum );
   setParameter( CONTRACT::TRANSID_EMPTY, strTransIdEmpty );

   return(_rpChildGI->refresh( this, NULL ));
}

//******************************************************************************
SEVERITY ContractInfoProcess::doSetField( const GenericInterface *rpGICaller,
                                          const BFContainerId& idContainer,
                                          const BFFieldId& idField,
                                          const BFDataGroupId& idDataGroup,
                                          const DString& strValue,
                                          bool bFormatted )
{
   if( BF::NullContainerId == idContainer && idField == CONTRACT::ORG_KEY )
   {
      _dstrOrgKey = strValue;
   }
   else if( idField == ifds::IsDuringNASU)
   {
      DString strIsDuringNasu(strValue);
      strIsDuringNasu.strip().upperCase();
      _bIsDuringNASU = (strIsDuringNasu == I_("Y"))?true:false;
      
      setField(this, IFASTBP_PROC::CONTRACTINFO_LIST, ifds::IsDuringNASU, strIsDuringNasu, false);
   }
   return(NO_CONDITION);
}

//******************************************************************************
void ContractInfoProcess::GetDofBirth( const BFDataGroupId& idDataGroup, DString &strDofBirth )
{
//   DString dstrAcctType, dstrTaxType;
//   DString dstrEntityType, dstrSeqNumber; 
//   DString dstrOwnerName, dstrSpouseName, dstrFirstName, dstrLastName;
//   DString dstrDofBirthSp;
//
//   SEVERITY sevRtn = SEVERE_ERROR;
//   DSTCWorkSession* dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
////   getParent()->getParameter( CONTRACT::ACCOUNT_NUMBER, _strAccountNum );  
//
//   sevRtn = dstcWorkSession->getMFAccount(  idDataGroup, _strAccountNum, _pMFAccount );
//   if ( _pMFAccount )
//   {
//      _pMFAccount->getField( ifds::AcctType, dstrAcctType, idDataGroup, false );
//      _pMFAccount->getField( ifds::TaxType, dstrTaxType, idDataGroup, false );
//
//      AccountEntityXref *_pAccountEntityXref;
//      sevRtn = dstcWorkSession->getAccountEntityXref( BF::HOST, _pAccountEntityXref );
//      sevRtn = _pAccountEntityXref->PopulateEntitiesList(  getDataGroupId(), _strAccountNum );
//
//      BFObjIter iter(*_pAccountEntityXref, idDataGroup, true, BFObjIter::ITERTYPE::NON_DELETED );
//      DString searchKey;
//      _pAccountEntityXref->buildPartialKeyForAccount( searchKey, _strAccountNum );
//
//      // if tax type != "1" ( is not a RSP account ) and AcctType_4 = "1" (spouse account), 
//      // if the entity is a SpouseContributor( the EntityType_50 = "06" ), 
//      // this entity must have a valid EOfBirth_51
//      if ( dstrTaxType.stripAll() != I_("1") && dstrAcctType.stripAll() == I_("1") )
//      {
//         for ( iter.begin( OBJ_TYPE_NONE, OBJ_ACTIVITY_NONE, searchKey ); !iter.end(); ++iter )
//         {
//            iter.getObject( )->getField(ifds::EntityType, dstrEntityType, idDataGroup, false );
//            // EntityType = "06" means the spousal contributor. The program should check spouse's DofBirth
//            if ( dstrEntityType.stripAll() ==  I_("06") )  
//            {
//               // get spouse's entityId
//               iter.getObject( )->getField(ifds::EntityId, _dstrEntityIdSp, idDataGroup, false );
//               break;
//            }
//         }
//      }
//
//      //  For the non-registered tax type ( TexType_4 == "0" ), the annuitant entity type ( EntityType_50 = "05" )
//      //  with the seq is "1", this entity must have valid DOfBirth_51
//      DSTCWorkSession* dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
//      if ( dstcWorkSession->isNonRegLike( dstrTaxType.stripAll() ) )  // non-registered account
//      {
//         for ( iter.begin( OBJ_TYPE_NONE, OBJ_ACTIVITY_NONE, searchKey ); !iter.end(); ++iter )
//         {
//            iter.getObject( )->getField(ifds::EntityType, dstrEntityType, idDataGroup, false );
//            iter.getObject( )->getField(ifds::SeqNumber, dstrSeqNumber, idDataGroup, false );
//            // EntityType = "05" means an annuitant entity. The program should check annuitant's DofBirth
//            if ( dstrEntityType.stripAll() ==  I_("05") &&   
//               dstrSeqNumber.stripAll().stripLeading( I_CHAR( '0' ) ) == I_("1") )
//            {
//               // get annuitant's entityId
//               iter.getObject( )->getField(ifds::EntityId, _dstrEntityIdOw, idDataGroup, false );
//               break;
//            }
//         }
//      }
//      else  // registered account
//      {
//         for ( iter.begin( OBJ_TYPE_NONE, OBJ_ACTIVITY_NONE, searchKey ); !iter.end(); ++iter )
//         {
//            iter.getObject( )->getField(ifds::EntityType, dstrEntityType, idDataGroup, false );
//            iter.getObject( )->getField(ifds::SeqNumber, dstrSeqNumber, idDataGroup, false );
//            // EntityType = "01" means Owner . The program should check owner's DofBirth
//            if ( dstrEntityType.stripAll() ==  I_("01") &&   
//                 dstrSeqNumber.stripAll().stripLeading( I_CHAR( '0' ) ) == I_("1") )
//            {
//               // get owner's entityId
//               iter.getObject( )->getField(ifds::EntityId, _dstrEntityIdOw, idDataGroup, false );
//               break;
//            }
//         }
//      }
//
//      Entity *_pEntity;
//
//      // Deal with the spouse stuffs
//      if ( _dstrEntityIdSp != NULL_STRING )
//      {
//         sevRtn = dstcWorkSession->getEntity(  idDataGroup, _dstrEntityIdSp, _pEntity );
//         _pEntity->getField( ifds::DofBirth, dstrDofBirthSp, idDataGroup, false );
//         // Check spouse's DofBirth and set parameters for GUI process
//         if( dstrDofBirthSp == NULL_STRING )
//         {
//            _pEntity->getField( ifds::FirstName, dstrFirstName, idDataGroup, false ); 
//            _pEntity->getField( ifds::LastName, dstrLastName, idDataGroup, false );
//            _dstrSpouseName = dstrFirstName.strip() + I_( " " ) + dstrLastName.strip();
//            _dstrAskDofBirthSp = I_( "Y" );
//         }
//         else
//         {
//            _dstrAskDofBirthSp = I_( "N" );
//         }
//      }
//      else
//      {
//         _dstrAskDofBirthSp = I_( "N" );
//      }
//
//      // Deal with the owner stuffs
//      if ( _dstrEntityIdOw != NULL_STRING )
//      {
//         sevRtn = dstcWorkSession->getEntity(  idDataGroup, _dstrEntityIdOw, _pEntity );
//         _pEntity->getField( ifds::DofBirth, strDofBirth, idDataGroup, false );  // pass strDofBirth to CBO
//         if ( strDofBirth == NULL_STRING )
//         {
//            _pEntity->getField( ifds::FirstName, dstrFirstName, idDataGroup, false ); 
//            _pEntity->getField( ifds::LastName, dstrLastName, idDataGroup, false );
//            _dstrOwnerName = dstrFirstName.strip() + I_( " " ) + dstrLastName.strip();
//            _dstrAskDofBirthEntity = I_( "Y" );
//         }
//         else
//         {
//            _dstrAskDofBirthEntity = I_( "N" );
//         }
//      }
//      else
//      {
//         _dstrAskDofBirthEntity = I_( "N" );
//      }
//   }
}

//******************************************************************************
void ContractInfoProcess::doPostOk( GenericInterface *rpGICaller, bool bSuccessFlag )
{
   //preserve param value in NASU flow
   //setParameter( CONTRACT::SHAREHOLD_NUMBER, strShareholdNum );
   setParameter( CONTRACT::ACCOUNT_NUMBER, _strAccountNum );
}

//******************************************************************************
void ContractInfoProcess::doGetField( const GenericInterface *rpGICaller,
                                      const BFContainerId& idContainer,
                                      const BFFieldId& idField,
                                      const BFDataGroupId& idDataGroup,
                                      DString &strValueOut,
                                      bool bFormatted
                                    ) const
{
   if( idField == ifds::IsDuringNASU)
   {
      strValueOut = _bIsDuringNASU ? I_("Y"):I_("N");
   }
   else if( idField == ifds::ContMatDateBasedOn || 
            idField == ifds::MatDateBasedOn     ||
            idField == ifds::IsGWOContract )
   {
      MasterContractList *pMasterContractList = NULL;
      ContractInfoProcess* pThis = const_cast<ContractInfoProcess*> (this);
      pMasterContractList = dynamic_cast<MasterContractList*>(pThis->getCBOList (IFASTBP_PROC::MASTER_CONTRACT_LIST, getDataGroupId()));

      if( pMasterContractList )
      {
         DString GroupCode, ContractType, AccountNumber;
         ContractInfoProcess *pContractInfoProcess = const_cast<ContractInfoProcess *>(this);
         pContractInfoProcess->getField(rpGICaller, IFASTBP_PROC::CONTRACTINFO_LIST, ifds::ContractType, ContractType, false);

         SEVERITY sevRtn = SEVERE_ERROR;
         DSTCWorkSession* dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
         MFAccount *pMFAccount;
         sevRtn = dstcWorkSession->getMFAccount(  idDataGroup, _strAccountNum, pMFAccount );
         if ( pMFAccount )
         {
            pMFAccount->getField( ifds::AcctGroup, GroupCode, idDataGroup, false );
         }
         pMasterContractList->getFieldByGroupAndContractType( GroupCode, ContractType, idField, strValueOut, idDataGroup, bFormatted );
      }
   }
   else if ( idField == ifds::GWOContract )
   {
      DString dstrContractKey = const_cast<ContractInfoProcess*> (this)->getCurrentListItemKey ( this, IFASTBP_PROC::CONTRACTINFO_LIST);
      if ( !dstrContractKey.strip().empty() )
      {
         ContractInfo *pContractInfo = dynamic_cast <ContractInfo*> ( const_cast<ContractInfoProcess*> (this)->
            getCBOItem (IFASTBP_PROC::CONTRACTINFO_LIST, idDataGroup));

         if ( NULL!= pContractInfo )
         {
            strValueOut = pContractInfo->isGWOContract( idDataGroup ) ? I_("Y") : I_("N");
         }
      }
   }
   else if ( idField == ifds::IsNewAcctContract )
   {
      ContractInfoProcess* pThis = const_cast<ContractInfoProcess*> (this);
      if(pThis)
      {
         DString dstrContractKey = pThis->getCurrentListItemKey ( this, IFASTBP_PROC::CONTRACTINFO_LIST);
         if ( !dstrContractKey.strip().empty() )
         {
            ContractInfo *pContractInfo = 
               dynamic_cast <ContractInfo*> ( pThis->getCBOItem (IFASTBP_PROC::CONTRACTINFO_LIST, idDataGroup));
            if ( NULL!= pContractInfo )
            {
               strValueOut = pContractInfo->isNewContract( idDataGroup ) ? I_("Y") : I_("N");
            }
         }
      }
   }
   else if( idField == ifds::DateOfReg)
   {
      ContractInfoProcess* pThis = const_cast<ContractInfoProcess*> (this);
      if(pThis)
      {
         DString dstrContractKey = pThis->getCurrentListItemKey ( this, IFASTBP_PROC::CONTRACTINFO_LIST);
         if ( !dstrContractKey.strip().empty() )
         {
            ContractInfo *pContractInfo = 
               dynamic_cast <ContractInfo*> ( pThis->getCBOItem (IFASTBP_PROC::CONTRACTINFO_LIST, idDataGroup));
            if ( NULL!= pContractInfo )
            {
               pContractInfo->getAcctCreationDate(strValueOut,idDataGroup, bFormatted);
            }
         }
      }   
   }
   else if (idField == ifds::AnnuitantName || idField == ifds::SuccessorAnnuitantName ||
            idField == ifds::SuccessorName)
   {
      DSTCWorkSession* dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
      MFAccount *pMFAccount = NULL;
      AccountEntityXref *pAccountEntityXref = NULL;

      DString strEntityType; 
      
      if (idField == ifds::AnnuitantName)
      {
         strEntityType = I_("05");
      }
      else if (idField == ifds::SuccessorName)
      {
         strEntityType = I_("09");
      }
      else 
      {
         strEntityType = I_("15");
      }

      if ( dstcWorkSession->getMFAccount(  idDataGroup, _strAccountNum, pMFAccount ) <= WARNING &&
         pMFAccount )
      {
         if (dstcWorkSession->getAccountEntityXref (idDataGroup, pAccountEntityXref) <= WARNING &&
            pAccountEntityXref)
         {
            if (pAccountEntityXref->PopulateEntitiesList (idDataGroup, _strAccountNum) <= WARNING )
            {
               BFObjIter bfIter (*pAccountEntityXref, idDataGroup);
               for( ; !bfIter.end(); ++bfIter )
               {
                  BFAbstractCBO * pAcctXRef =  bfIter.getObject();
                  DString entityType, seqNum, firstName, lastName;
                  pAcctXRef->getField (ifds::EntityType,entityType,idDataGroup);
                  pAcctXRef->getField (ifds::SeqNumber, seqNum, idDataGroup);
                  pAcctXRef->getField (ifds::FirstName, firstName, idDataGroup);
                  pAcctXRef->getField (ifds::LastName, lastName, idDataGroup);

                  if (entityType == strEntityType && seqNum.asInteger() == 1)
                  {
                     strValueOut = lastName;
                     strValueOut += I_(";");
                     strValueOut += firstName;
                     break;
                  }
               }
            }
         }
      }
   }

}

//******************************************************************************
const BFProperties *ContractInfoProcess::doGetFieldAttributes( const GenericInterface *rpGICaller,
                                                               const BFContainerId& idContainer, 
                                                               const BFFieldId& idField, 
                                                               const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, I_("doGetFieldAttributes") );

   const BFProperties * pBFProp = NULL;

   return(pBFProp);
}

//******************************************************************************
void *ContractInfoProcess::getPtrForContainer( const BFContainerId& idContainer,
                                                  const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, I_( "getPtrForContainer" ) );

   void *ptr = NULL;
   DSTCWorkSession *dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());

   try
   {
      if (IFASTBP_PROC::CONTRACTINFO_LIST == idContainer)
      {
         MFAccount *pMFAccount = NULL;
         ContractInfoProcess* pThis = const_cast<ContractInfoProcess*> (this);
         pMFAccount = dynamic_cast<MFAccount*>(pThis->getCBOItem (IFASTBP_PROC::MFACCOUNT_CBO, getDataGroupId()));

         ContractInfoList* pContractInfoList= NULL;
         if(pMFAccount && 
            pMFAccount->getContractInfoList( pContractInfoList, getDataGroupId() ) <= WARNING )
         {
            ptr = pContractInfoList;
         }
      }
      else if(IFASTBP_PROC::MASTER_CONTRACT_LIST == idContainer)
      {
         MasterContractList* pMasterContractList = NULL;
         DString dstrPorfolioIsRequried;

         DSTCWorkSession *dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
         if ( dstcWorkSession )
         {
            dstcWorkSession->getOption( ifds::PorfolioIsRequried, dstrPorfolioIsRequried, idDataGroup, false );      
         }

         dstrPorfolioIsRequried.strip().upperCase();
         
         if( dstrPorfolioIsRequried == I_("Y") )
         {
            MFAccount *pMFAccount = NULL;
            ContractInfoProcess* pThis = const_cast<ContractInfoProcess*> (this);
            pMFAccount = dynamic_cast<MFAccount*>(pThis->getCBOItem (IFASTBP_PROC::MFACCOUNT_CBO, getDataGroupId()));
            
            if(pMFAccount &&
               pMFAccount->getMasterContractListByPortfolio(pMasterContractList,idDataGroup) <= WARNING &&
               pMasterContractList )
            {
               ptr = pMasterContractList;
            }
         }
         else
         {
            if( dstcWorkSession->getMgmtCo().getMasterContractList( pMasterContractList ) <= WARNING && 
                pMasterContractList )
            {
               ptr = pMasterContractList;
            }
         }
      }
   }
   catch( ConditionException & )
   {
      throw;
   }
   catch( ... )
   {
      assert( 0 );
      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, DOINIT,
         CND::BP_ERR_UNKNOWN_EXCEPTION );
   }

   return(ptr);
}

//******************************************************************************
SEVERITY ContractInfoProcess::getHistoricalParameters( const BFContainerId& idContainer, 
                                                       HISTORICAL_VECTOR &vectorHistorical )
{
   MAKEFRAMEAUTOPROMOTE2(CND::BPBASE_CONDITION, CLASSNAME, GETHISTORICALPARAMETERS);

   if( idContainer == IFASTBP_PROC::CONTRACTINFO_LIST)
   {   
      DString keyStringIDI( NULL_STRING ), 
         dstrCotAcctRecord;

   }

   return GETCURRENTHIGHESTSEVERITY();
}

//***********************************************************************************
bool ContractInfoProcess::doMoreRecordsExist( GenericInterface *rpGICaller,
                                          const BFContainerId& idSearch )
{
   return( _pContractInfoList ? _pContractInfoList->doMoreRecordsExist( ): false );
}

//******************************************************************************
bool ContractInfoProcess::doOk (GenericInterface* rpGICaller)
{

   MAKEFRAMEAUTOPROMOTE2( CND::IFASTBP_CONDITION, CLASSNAME, I_( "doOk" ) );
   
   MFAccount *pMFAccount = NULL;
   DSTCWorkSession* dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
   if( !_strAccountNum.empty() && 
       WARNING >= dstcWorkSession->getMFAccount(  getDataGroupId( ), _strAccountNum, pMFAccount ) &&
       pMFAccount)
   {
      pMFAccount->refreshMe(true);
   }

   return GETCURRENTHIGHESTSEVERITY () <= WARNING;
}
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/ContractInfoProcess.cpp-arc  $
 * 
 *    Rev 1.59   Aug 12 2012 23:59:50   popescu
 * IN2972860 - Cannot changes account status to death and death transfer.
 * 
 *    Rev 1.58   Aug 10 2012 18:04:20   kitticha
 * IN2972860 - Cannot changes account status to death and death transfer.
 * 
 *    Rev 1.57   Feb 21 2012 18:54:22   wp040100
 * P0186484 FN05 - Contract Maturity Instruction Changes
 * 
 *    Rev 1.56   Jan 30 2012 12:36:20   dchatcha
 * Synch up: IN# 2799812 - Contract Screen issues.
 * 
 *    Rev 1.55   Jan 21 2012 09:31:58   dchatcha
 * IN# 2799812 - Contract Screen issues.
 * 
 *    Rev 1.54   Jan 19 2012 12:39:24   dchatcha
 * Synch up: IN# 2799812 - Contract Screen issues. New requirement to display contract anniversary date. 
 * 
 *    Rev 1.53   Jan 17 2012 18:00:48   dchatcha
 * Synch up: IN# 2799812 - Contract Screen issues. Fix crashing during load contract infromation screen. 
 * 
 *    Rev 1.52   Jan 16 2012 20:29:18   dchatcha
 * P0186484 - FN 05 - SEG Processing Screen
 * 
 *    Rev 1.51   Jan 16 2012 20:04:06   dchatcha
 * IN# 2799812 - Contract Screen issues.
 * 
 *    Rev 1.50   Dec 27 2011 01:03:22   dchatcha
 * P0186484 - FN 05 - work on Contract Information Screen
 * 
 *    Rev 1.49   06 Oct 2008 13:16:06   kovacsro
 * PET142007  FN01 TFSA
 * 
 *    Rev 1.48   12 Sep 2008 16:14:30   kovacsro
 * PET142007 FN01 Tax Free Saving Account
 * 
 *    Rev 1.47   12 Sep 2008 15:39:54   kovacsro
 * PET142007.FN01 Tax Free Saving Account - code cleanup for taxType=0
 * 
 *    Rev 1.46   May 25 2006 17:46:00   ZHANGCEL
 * PET 2102 FN02 -- Add SettleDate in FieldsDetails
 * 
 *    Rev 1.45   Apr 21 2006 11:44:20   porteanm
 * PET2102 FN02 - For 71 - Some GWO support.
 * 
 *    Rev 1.44   Apr 20 2006 16:16:54   porteanm
 * PET2102 FN02 - For 71 - Some GWO support.
 * 
 *    Rev 1.43   Feb 14 2006 14:07:30   zhengcon
 * Incident #528284 - add one field ModPerm for updatable permission of User Defined Maturity Date of converted account 
 * 
 *    Rev 1.42   Aug 17 2005 16:53:00   porteanm
 * Incident 351033 - Removed single contract support.
 * 
 *    Rev 1.41   Jun 14 2005 15:32:06   porteanm
 * PET1024 FN40 - Guarantee Adjustments.
 * 
 *    Rev 1.40   Apr 18 2005 13:58:06   hernando
 * PET1024 FN02 - Changed the way values are retrieved from the Master Contract List.
 * 
 *    Rev 1.39   Mar 30 2005 14:54:30   hernando
 * PET1024 FN02 - Added SegTransExist.
 * 
 *    Rev 1.38   Mar 20 2005 20:02:16   hernando
 * PET1024 FN02 - Added Include ContMatDateBasedOn and MatDateBasedOn field details.
 * 
 *    Rev 1.37   Mar 16 2005 13:50:14   hernando
 * PET1024 FN02 - Removed MaturityType and UserMaturityDate.  Added a few fields.
 * 
 *    Rev 1.36   Mar 21 2003 17:38:18   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.35   Nov 29 2002 15:47:06   ZHANGCEL
 * Synced up to 1.34
 * 
 *    Rev 1.34   Oct 09 2002 23:53:10   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.33   Aug 29 2002 16:44:52   SMITHDAV
 * Condition split.
 * 
 *    Rev 1.32   Aug 29 2002 12:54:18   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.31   Aug 06 2002 16:53:12   ZHANGCEL
 * PTS 10009171: Allow user setting up a Contract for RSP spousal account when spousal birth date unknowing.
 * 
 *    Rev 1.30   Jun 03 2002 16:42:24   FENGYONG
 * Add name for API
 * 
 *    Rev 1.29   22 May 2002 18:24:10   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.28   27 Mar 2002 19:54:46   PURDYECH
 * Process/WindowFactory overhaul
 * 
 *    Rev 1.27   Nov 14 2001 11:43:28   ZHANGCEL
 *  hasPermission changes
 * 
 *    Rev 1.26   Nov 07 2001 14:33:54   ZHANGCEL
 * Many changes for multiple Contracts
 * 
 *    Rev 1.25   25 Oct 2001 14:02:46   SMITHDAV
 * hasPermission changes...
 * 
 *    Rev 1.24   Jul 25 2001 16:14:32   OLTEANCR
 * unchanged
 * 
 *    Rev 1.23   Jul 17 2001 09:37:30   OLTEANCR
 * added logic for multicontracts
 * 
 *    Rev 1.22   Jun 07 2001 10:47:14   YINGBAOL
 * sync. code
 * 
 *    Rev 1.21   Jun 07 2001 10:45:00   YINGBAOL
 * fix refresh issue
 * 
 *    Rev 1.20   14 May 2001 13:58:14   YINGZ
 * code sync up
 * 
 *    Rev 1.19   May 11 2001 16:01:38   OLTEANCR
 * unchanged
 * 
 *    Rev 1.18   15 Dec 2000 12:43:24   PURDYECH
 * Use precompiled header stdafx.h.
 * Removed unnecessary header files.
 * 
 *    Rev 1.17   Nov 30 2000 10:12:16   ZHANGCEL
 * added " const " for variables in the namespace and code clean up
 * 
 *    Rev 1.16   Oct 24 2000 11:06:54   KOVACSRO
 * Adedd tax type field.
 * 
 *    Rev 1.15   Oct 19 2000 17:19:00   KOVACSRO
 * Bugs fixed and deleted a param (Shareholder Number).
 * 
 *    Rev 1.14   Oct 18 2000 10:57:32   KOVACSRO
 * Modified parameter name to make it work from NASU.
 * 
 *    Rev 1.13   Oct 02 2000 12:06:02   ZHANGCEL
 * Added a condition for Province validation
 * 
 *    Rev 1.12   Sep 21 2000 14:42:54   ZHANGCEL
 * Bug fixed
 * 
 *    Rev 1.11   Aug 02 2000 15:32:00   BUZILA
 * "locale" changes
 * 
 *    Rev 1.10   Jul 26 2000 11:08:48   ZHANGCEL
 * Deal with the date overlap problem
 * 
 *    Rev 1.9   Jul 07 2000 10:23:32   ZHANGCEL
 * Deal with the leap year problem
 * 
 *    Rev 1.8   Jun 27 2000 12:41:14   BUZILA
 * fix contractInfoList deleteion on destructor
 * 
 *    Rev 1.7   May 18 2000 15:43:58   ZHANGCEL
 * Date culculate stuffs
 * 
 *    Rev 1.6   May 12 2000 17:55:44   ZHANGCEL
 * Deal with DofBirth checking problems
 * 
 *    Rev 1.5   Apr 20 2000 16:35:44   ZHANGCEL
 * Milestone check in
 * 
 *    Rev 1.4   Apr 11 2000 11:36:22   ZHANGCEL
 * Added a parameter for  DofBirth
 * 
 *    Rev 1.3   Mar 17 2000 16:45:38   ZHANGCEL
 * Checked in for release
 * 
 *    Rev 1.2   Mar 15 2000 10:02:12   ZHANGCEL
 * Fix some buges
 * 
 *    Rev 1.1   Mar 07 2000 10:26:22   HSUCHIN
 * changed to use new infra
 * 
 *    Rev 1.0   Feb 15 2000 10:59:32   SMITHDAV
 * Initial revision.
// 
//    Rev 1.0   Feb 03 2000 13:21:16   ZHANGCEL
// Initial revision.
 * 
 *
 */
