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
//    Copyright 2005 by IFDS.
//
//******************************************************************************
//
// ^FILE   : EntityAloneProcess.cpp
// ^AUTHOR : Yingbao  Li
// ^DATE   : 01/29/2005
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : EntityAloneProcess
//    This class manages the address book process.
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include "stdafx.h"
#include "EntityAloneProcessincludes.h"

#include "EntityAloneProcess.hpp"
#include <ifastcbo\entity.hpp>
#include <ifastcbo\entitylist.hpp>
#include <ifastcbo\WhereUsedList.hpp>
#include <ifastcbo\entitysearchlist.hpp>
#include <ifastdataimpl\dse_dstcglob_vw.hpp>
#include "searchprocessincludes.h"
#include <ifastcbo\shareholder.hpp>
#include <ifastdataimpl\dse_dstc0051_vw.hpp>
#include <ifastdataimpl\dse_dstc0061_vw.hpp>
#include <ifastdataimpl\dse_dstc0003_vw.hpp>
#include <ifastcbo\mgmtco.hpp>
#include <ifastcbo\MgmtCoOptions.hpp>
#include "mfcaninterprocparam.hpp"
#include "fillsearchcriteriaprocessincludes.h"
#include "entitysearchprocessincludes.h"


extern IFASTBP_LINKAGE const I_CHAR* CMD_GUI_ENTITY_ALONE;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_ENTITY_ALONE_PROCESS;
#include <bfproc\concreteprocesscreator.hpp>
static ConcreteProcessCreator< EntityAloneProcess > processCreator( CMD_BPROC_ENTITY_ALONE_PROCESS );


namespace
{
   // Trace literals
   const I_CHAR *CLASSNAME = I_( "EntityAloneProcess" );
   const I_CHAR *LIST_KEY  = I_( "ListKey" );
   const I_CHAR *Y_STRING  = I_( "Y" );
   const I_CHAR *N_STRING  = I_( "N" );
   const I_CHAR *EntityId  = I_( "EntityId" );

   const I_CHAR *SPACE_STRING  = I_( " " ); 
   const DString EMPTY_STRING;
   const I_CHAR *pINQUIRYONLY  = I_( "InquiryOnly" );

}

namespace ENTITYALONE
{
   const I_CHAR * const  FIRST_NAME = I_( "FirstName" );
   const I_CHAR * const  LAST_NAME = I_( "LastName" );


}

namespace CND
{  // Conditions used
   extern CLASS_IMPORT const long BP_ERR_UNKNOWN_EXCEPTION;
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId NAME_LENGTH;
   extern CLASS_IMPORT const BFTextFieldId SalutationFormat; 
   extern CLASS_IMPORT const BFTextFieldId EntityWhereUseRelationship;
   extern CLASS_IMPORT const BFTextFieldId EUSDParticip;
   extern CLASS_IMPORT const BFDateFieldId StopDate;
   extern CLASS_IMPORT const BFTextFieldId CountryOfBirth;
   extern CLASS_IMPORT const BFTextFieldId ContactName;
   extern CLASS_IMPORT const BFDateFieldId IdExpireDate;
   extern CLASS_IMPORT const BFTextFieldId FATCAFFI;
}

namespace AUDITTYPE
{
   extern CLASS_IMPORT I_CHAR * const ENTIDS;
   extern CLASS_IMPORT I_CHAR * const ENTIDT;
}

namespace IDTYPE
{
   const I_CHAR * const DRIVER_LICENSE       = I_( "01" );
   const I_CHAR * const PASSPORT             = I_( "02" );
   const I_CHAR * const BIRTH_CERTIFICATE    = I_( "03" );
   const I_CHAR * const CREDIT_CARD          = I_( "04" );
   const I_CHAR * const NATIONAL_ID          = I_( "05" );
   const I_CHAR * const SOCIAL_SEC_INS_CARD  = I_( "06" );
   const I_CHAR * const OTHER                = I_( "99" );
};

namespace AllEntitySearchType
{
   const I_CHAR * const NAME        = I_( "NAME" );
   const I_CHAR * const SIN         = I_( "SIN" );
   const I_CHAR * const IDTYPE      = I_( "IDTYPE" );
   const I_CHAR * const WHEREUSE    = I_( "WHEREUSE" );
};

namespace WhereUseSearchType
{
   const I_CHAR * const FUND           = I_( "04" );
   const I_CHAR * const FUND_SPONSOR   = I_( "05" );
   const I_CHAR * const REG_AGENT      = I_( "14" );
};



//******************************************************************************
//              Public Methods
//******************************************************************************

//CP20030319EntityAloneProcess::EntityAloneProcess() : 
EntityAloneProcess::EntityAloneProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: AbstractProcess( pGIC, pGIParent, rCommand )
, _rpChildGI( NULL )
,_pEntitySearchList(NULL)
{
   TRACE_CONSTRUCTOR( CLASSNAME, I_( "EntityAloneProcess" ) );
//entity
   addContainer( IFASTBP_PROC::ENTITY_LIST, true, BF::NullContainerId, true,I_( "EntityAloneList" ) );
   addContainer( IFASTBP_PROC::ENTITY_IDS_LIST, true, IFASTBP_PROC::ENTITY_LIST, true,I_( "EntityIDSList" ) );
   addContainer( IFASTBP_PROC::WHEREUSED_LIST, true, IFASTBP_PROC::ENTITY_LIST, true,I_( "WhereUsedList" ) );

//entity
   addFieldDetails( ifds::Salutation,			IFASTBP_PROC::ENTITY_LIST  );
   addFieldDetails( ifds::LastName,				IFASTBP_PROC::ENTITY_LIST );
   addFieldDetails( ifds::FirstName,			IFASTBP_PROC::ENTITY_LIST );
   addFieldDetails( ifds::BirthLastName,		IFASTBP_PROC::ENTITY_LIST );
   addFieldDetails( ifds::BirthFirstName,		IFASTBP_PROC::ENTITY_LIST );
   addFieldDetails( ifds::DofBirth,				IFASTBP_PROC::ENTITY_LIST );
   addFieldDetails( ifds::Gender,				IFASTBP_PROC::ENTITY_LIST );
   addFieldDetails( ifds::SIN,					IFASTBP_PROC::ENTITY_LIST );
   addFieldDetails( ifds::OccupationCode,		IFASTBP_PROC::ENTITY_LIST );
   addFieldDetails( ifds::OccupationDesc,		IFASTBP_PROC::ENTITY_LIST );
   addFieldDetails( ifds::LanguageCode,			IFASTBP_PROC::ENTITY_LIST );
   addFieldDetails( ifds::Language,				IFASTBP_PROC::ENTITY_LIST ); 
   addFieldDetails( ifds::HomePhone,			IFASTBP_PROC::ENTITY_LIST );
   addFieldDetails( ifds::BusinessPhone,		IFASTBP_PROC::ENTITY_LIST );
   addFieldDetails( ifds::BusinessExt,			IFASTBP_PROC::ENTITY_LIST );
   addFieldDetails( ifds::BusinessFax,			IFASTBP_PROC::ENTITY_LIST );
   addFieldDetails( ifds::Telex,				IFASTBP_PROC::ENTITY_LIST );
   addFieldDetails( ifds::Email,				IFASTBP_PROC::ENTITY_LIST );
   addFieldDetails( ifds::ContactName,			IFASTBP_PROC::ENTITY_LIST );
   addFieldDetails( ifds::DofDeath,				IFASTBP_PROC::ENTITY_LIST );
   addFieldDetails( ifds::DofDeathNotice,		IFASTBP_PROC::ENTITY_LIST );
   addFieldDetails( ifds::EffectiveDate,		IFASTBP_PROC::ENTITY_LIST );
   addFieldDetails( ifds::ProcessDate,			IFASTBP_PROC::ENTITY_LIST );
   addFieldDetails( ifds::ModDate,				IFASTBP_PROC::ENTITY_LIST );
   addFieldDetails( ifds::Username,				IFASTBP_PROC::ENTITY_LIST );
   addFieldDetails( ifds::ModUser,				IFASTBP_PROC::ENTITY_LIST );
   addFieldDetails( ifds::HomeFax,				IFASTBP_PROC::ENTITY_LIST );
   addFieldDetails( ifds::EntityIdentityVer, IFASTBP_PROC::ENTITY_LIST );
   addFieldDetails( ifds::EntityIdentityRid, IFASTBP_PROC::ENTITY_LIST );
   addFieldDetails( ifds::HomePhoneCntry,    IFASTBP_PROC::ENTITY_LIST );
   addFieldDetails( ifds::HomePhoneArea,     IFASTBP_PROC::ENTITY_LIST );
   addFieldDetails( ifds::BusinessPhoneCntry,IFASTBP_PROC::ENTITY_LIST );
   addFieldDetails( ifds::BusinessPhoneArea, IFASTBP_PROC::ENTITY_LIST );
   addFieldDetails( ifds::HomeFaxCntry,      IFASTBP_PROC::ENTITY_LIST );
   addFieldDetails( ifds::HomeFaxArea,       IFASTBP_PROC::ENTITY_LIST );
   addFieldDetails( ifds::BusFaxCntry,       IFASTBP_PROC::ENTITY_LIST );
   addFieldDetails( ifds::BusFaxArea,        IFASTBP_PROC::ENTITY_LIST );
   addFieldDetails( ifds::EntityId,          IFASTBP_PROC::ENTITY_LIST );
   addFieldDetails( ifds::RiskLevel,         IFASTBP_PROC::ENTITY_LIST );
   addFieldDetails( ifds::OtherOccupation,   IFASTBP_PROC::ENTITY_LIST );
   addFieldDetails( ifds::Nationality,       IFASTBP_PROC::ENTITY_LIST );
   addFieldDetails( ifds::EmployeeClass,     IFASTBP_PROC::ENTITY_LIST );
   addFieldDetails( ifds::NAME_LENGTH,       IFASTBP_PROC::ENTITY_LIST );
   addFieldDetails( ifds::BirthPlace,        IFASTBP_PROC::ENTITY_LIST );
   addFieldDetails( ifds::CountryOfBirth,    IFASTBP_PROC::ENTITY_LIST );
   addFieldDetails( ifds::TaxJurisDeff,      IFASTBP_PROC::ENTITY_LIST );
   addFieldDetails( ifds::TaxJuris,          IFASTBP_PROC::ENTITY_LIST );
   addFieldDetails( ifds::EUSDTaxOption,     IFASTBP_PROC::ENTITY_LIST );
   //addFieldDetails( ifds::FATCAFFI,          IFASTBP_PROC::ENTITY_LIST );
   addFieldDetails( ifds::UpdShrTaxJuris,    IFASTBP_PROC::ENTITY_LIST );
   addFieldDetails( ifds::GoodBad,           IFASTBP_PROC::ENTITY_LIST );
   addFieldDetails( ifds::Email2,            IFASTBP_PROC::ENTITY_LIST );
   addFieldDetails( ifds::SecondPhoneNum,    IFASTBP_PROC::ENTITY_LIST );
   addFieldDetails( ifds::SecondPhoneNumExt, IFASTBP_PROC::ENTITY_LIST );
   addFieldDetails( ifds::CountryOfExposure, IFASTBP_PROC::ENTITY_LIST );

//entity_IDS
   addFieldDetails( ifds::IdType,             IFASTBP_PROC::ENTITY_IDS_LIST );
   addFieldDetails( ifds::IdValue,            IFASTBP_PROC::ENTITY_IDS_LIST );
   addFieldDetails( ifds::IdDate,             IFASTBP_PROC::ENTITY_IDS_LIST );
   addFieldDetails( ifds::IdTypeDesc,         IFASTBP_PROC::ENTITY_IDS_LIST );
   addFieldDetails( ifds::IdExpireDate,       IFASTBP_PROC::ENTITY_IDS_LIST );
   addFieldDetails( ifds::IdStatus,           IFASTBP_PROC::ENTITY_IDS_LIST );
   addFieldDetails( ifds::CountryOfIssue,     IFASTBP_PROC::ENTITY_IDS_LIST );
   //addFieldDetails( ifds::DuplicateSINcheck,  IFASTBP_PROC::ENTITY_IDS_LIST );

// where used
   addFieldDetails( ifds::AccountNum,		IFASTBP_PROC::WHEREUSED_LIST );
   addFieldDetails( ifds::EntityType,		IFASTBP_PROC::WHEREUSED_LIST );
   addFieldDetails( ifds::EntityTypeDesc,	IFASTBP_PROC::WHEREUSED_LIST );
   addFieldDetails( ifds::ShrNum,			IFASTBP_PROC::WHEREUSED_LIST );
   addFieldDetails( ifds::TaxTypeDesc,		IFASTBP_PROC::WHEREUSED_LIST );
   addFieldDetails( ifds::TaxType,			IFASTBP_PROC::WHEREUSED_LIST );
   addFieldDetails( ifds::AcctType,			IFASTBP_PROC::WHEREUSED_LIST );
   addFieldDetails( ifds::AcctTypeDesc,		IFASTBP_PROC::WHEREUSED_LIST );
   addFieldDetails( ifds::AcctStatusDesc,	IFASTBP_PROC::WHEREUSED_LIST );
   addFieldDetails( ifds::AcctStatus,		IFASTBP_PROC::WHEREUSED_LIST );
   addFieldDetails( ifds::Currency,			IFASTBP_PROC::WHEREUSED_LIST );
   addFieldDetails( ifds::AccountBalance,	IFASTBP_PROC::WHEREUSED_LIST );
   addFieldDetails( ifds::EntityTypeSeq,	IFASTBP_PROC::WHEREUSED_LIST );
   addFieldDetails( ifds::WhereUse,			IFASTBP_PROC::WHEREUSED_LIST);
   addFieldDetails( ifds::WhereUseCode,		IFASTBP_PROC::WHEREUSED_LIST);
   addFieldDetails( ifds::EffectiveDate,	IFASTBP_PROC::WHEREUSED_LIST);
   addFieldDetails( ifds::StopDate,			IFASTBP_PROC::WHEREUSED_LIST);

   addFieldDetails( EntityAlone::AGE_YEARS,           BF::NullContainerId,SUBCLASS_PROCESS  );
   addFieldDetails( EntityAlone::AGE_MONTHS,          BF::NullContainerId,SUBCLASS_PROCESS );
   addFieldDetails( EntityAlone::SALUTATION_EDIT,     BF::NullContainerId,SUBCLASS_PROCESS );
   addFieldDetails( EntityAlone::UPDATE_SHAREHOLDER,  BF::NullContainerId,SUBCLASS_PROCESS );
   addFieldDetails( EntityAlone::ACCOUNT_ENTITY,      BF::NullContainerId,SUBCLASS_PROCESS );
   addFieldDetails( ifds::EUSDParticip,               BF::NullContainerId,SUBCLASS_PROCESS );
   addFieldDetails( ifds::IsNetworkSender,            BF::NullContainerId,SUBCLASS_PROCESS);
}

//******************************************************************************
EntityAloneProcess::~EntityAloneProcess()
{
   TRACE_DESTRUCTOR( CLASSNAME );
   delete _pEntitySearchList;
}
//******************************************************************************
SEVERITY EntityAloneProcess::doInit()
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTBP_CONDITION, CLASSNAME, DOINIT );

   DString strEntityID;
   try
   {  
      getParent()->getParameter(ENTSRCHLIT::SEARCH_CODE, _searchUsing);
      getParent()->getParameter(ENTSRCHLIT::FIRST_VALUE, _firstValue);
      getParent()->getParameter(ENTSRCHLIT::SECOND_VALUE, _secondValue);
      Entity::bUsedByEntityAlone = true;

      populateWorkSessionEntityList( );
  
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
   return(GETCURRENTHIGHESTSEVERITY());
}

  
   

//******************************************************************************
E_COMMANDRETURN EntityAloneProcess::doProcess()
{  
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTBP_CONDITION, CLASSNAME, DOPROCESS );
   E_COMMANDRETURN rtn = CMD_FAILURE;

   try
   {
      if( !isXMLAPIContext() )
      {
         rtn = invokeCommand( this, CMD_GUI_ENTITY_ALONE, getProcessType(), isModal(), &_rpChildGI );
      }   
   }
   catch( ConditionException &ce )
   {
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
bool  EntityAloneProcess::doModelessSetFocus( GenericInterface *rpGICaller )
{  // This is implemented to pass set focus on to child dialog.
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTBP_CONDITION, CLASSNAME, DOMODELESSSETFOCUS );
   bool bRtn = false;

   try
   {
   ///   DString strAccountNum,strShrNum;
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
bool  EntityAloneProcess::doModelessChildComplete( const Command &cmd )
{
   // End when GUI ends
   return( cmd.getKey() == CMD_GUI_ENTITY_ALONE );
}



//******************************************************************************
void* EntityAloneProcess::getPtrForContainer( const BFContainerId& idContainer, const BFDataGroupId& idDataGroup )
{
   void *ptr = NULL;
   DSTCWorkSession *dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());

   try
   {
      if( idContainer  == IFASTBP_PROC::WHEREUSED_LIST )
      {

         Entity* pEntity =  dynamic_cast<Entity*>( getCBOItem( IFASTBP_PROC::ENTITY_LIST, idDataGroup ) );
         if( pEntity )
         {
            WhereUsedList* pWhereUsedList = NULL;
            pEntity->getWhereUsedList ( pWhereUsedList, idDataGroup );
            ptr = pWhereUsedList;
         }
      }
      else if( IFASTBP_PROC::ENTITY_IDS_LIST == idContainer )
      {
         Entity* pEntity =  dynamic_cast<Entity*>( getCBOItem( IFASTBP_PROC::ENTITY_LIST, idDataGroup ) );
         if( pEntity )
         {
            EntityIdsList* pEntityIdsList = NULL;
            pEntity->getEntityIdsList ( pEntityIdsList, idDataGroup );
            ptr = pEntityIdsList;
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

//-----------------------------------------------------------------------------


//************************************************************************************************************
void EntityAloneProcess::doGetField(
                               const GenericInterface *rpGICaller,
                               const BFContainerId& idContainer,
                               const BFFieldId& idField,
                               const BFDataGroupId& idDataGroup,
                               DString &strValueOut,
                               bool bFormatted
                               ) const
{  
   if( idField == EntityAlone::AGE_YEARS )
   {
      DString entityId;
      BFAbstractCBO *rpPtr = ( const_cast < EntityAloneProcess *> ( this ) )->getCBOItem( IFASTBP_PROC::ENTITY_LIST, idDataGroup );
      if( rpPtr )
      {
         DSTCWorkSession *dstcWorkSession = dynamic_cast<DSTCWorkSession *>( getBFWorkSession() );
         DString DateOfBirth, CurrentDate, months;
         rpPtr->getField( ifds::DofBirth, DateOfBirth, idDataGroup );
         dstcWorkSession->getDateInHostFormat( CurrentDate, DSTCWorkSession::CURRENT_SYSTEM_DAY, idDataGroup );
         if( DSTCommonFunctions::BuildAge( DateOfBirth, CurrentDate, strValueOut, months ) )
            strValueOut = I_( "" );
         
      }
   }
   else if( idField == EntityAlone::AGE_MONTHS )
   {
      
      BFAbstractCBO *rpPtr = ( const_cast < EntityAloneProcess *> ( this ) )->getCBOItem( IFASTBP_PROC::ENTITY_LIST, idDataGroup );
      if( rpPtr )
      {
            DSTCWorkSession *dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
            DString DateOfBirth, CurrentDate, years;
            rpPtr->getField( ifds::DofBirth, DateOfBirth, idDataGroup );
            dstcWorkSession->getDateInHostFormat( CurrentDate, DSTCWorkSession::CURRENT_SYSTEM_DAY, idDataGroup );
            if( DSTCommonFunctions::BuildAge( DateOfBirth, CurrentDate, years, strValueOut ) )
               strValueOut = I_( "" );
         
      }
   }
   else if ( idField == EntityAlone::SALUTATION_EDIT  )
   {
      // Return Yes for Salutation Edit is used or NO for Combo box.
      DString dstrValue;
      DSTCWorkSession *dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
      dstcWorkSession->getMgmtCoOptions()->getField( ifds::SalutationFormat, dstrValue, idDataGroup, false);
      dstrValue.upperCase().stripAll();
      strValueOut = ( dstrValue.substr( 0, 1 ) == I_("Y") ) ? I_("Y") : I_("N");         
   }
   else if ( idField ==  EntityAlone::UPDATE_SHAREHOLDER )
   {
      Entity* pEntity = dynamic_cast<Entity* >( ( const_cast < EntityAloneProcess *> ( this ) )->getCBOItem( IFASTBP_PROC::ENTITY_LIST, idDataGroup ) );
      if( pEntity )
      {
         strValueOut = pEntity->shouldUpdateShareholder(idDataGroup)? Y_STRING:N_STRING;            
      }         
   }
   else if ( idField ==  EntityAlone::ACCOUNT_ENTITY )
   {
      Entity* pEntity = dynamic_cast<Entity* >( ( const_cast < EntityAloneProcess *> ( this ) )->getCBOItem( IFASTBP_PROC::ENTITY_LIST, idDataGroup ) );
      if( pEntity )
      {
         strValueOut = pEntity->isAccountRelated(idDataGroup)? Y_STRING:N_STRING;            
      }                 
   }
   else if ( idField ==  ifds::EUSDParticip )
   {
      DSTCWorkSession* pWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());

      pWorkSession->getOption2( ifds::EUSDParticip, strValueOut, idDataGroup, false);
   }
   else if (idField == ifds::IsNetworkSender)
   {
      strValueOut = I_("N");  
      Entity* pEntity = dynamic_cast<Entity* >( ( const_cast < EntityAloneProcess *> ( this ) )->getCBOItem( IFASTBP_PROC::ENTITY_LIST, idDataGroup ) );
	   if (pEntity && !pEntity->isNew ())
	   {
		   WhereUsedList* pWhereUsedList = NULL;
		   pEntity->getWhereUsedList (pWhereUsedList, idDataGroup);
         if (pWhereUsedList)
         {
			   strValueOut = pWhereUsedList->isNetworkSender (idDataGroup) ? I_("Y") :  I_("N");
         }
	   }
   }
}


//******************************************************************************
bool EntityAloneProcess::doRefresh( GenericInterface *rpGICaller,
                                    const I_CHAR *szOriginalCommand)
{
   return(_rpChildGI->refresh( this, NULL ));
}

//******************************************************************************

SEVERITY EntityAloneProcess::getHistoricalParameters ( const BFContainerId &idContainer, 
                                                       BFFieldId &recordIdField, 
                                                       DString &tableId, 
                                                       DString &dstrKeys)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::BPBASE_CONDITION, CLASSNAME, GETHISTORICALPARAMETERS);
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************

SEVERITY EntityAloneProcess::getHistoricalParameters( const BFContainerId& idContainer, HISTORICAL_VECTOR &vectorHistorical )
{
   MAKEFRAMEAUTOPROMOTE2(CND::BPBASE_CONDITION, CLASSNAME, GETHISTORICALPARAMETERS);
   if ( idContainer == IFASTBP_PROC::ENTITY_LIST )
   {

      DString keyStringIDI, dstrRecord;
      DString dstrEntityType, dstrAccountNum, dstrSeqNumber, dstrAccountType;
      // Entity Identity
      // Key - EntityID
      DString dstrEntityId;
      getField( this, IFASTBP_PROC::ENTITY_LIST, ifds::EntityIdentityRid, dstrRecord, false );
      getField( this, IFASTBP_PROC::ENTITY_LIST, ifds::EntityId, dstrEntityId, false );
      addIDITagValue( keyStringIDI, MFCAN_IP_PARAM::ENTITY_ID, dstrEntityId );
      HistoricalElement heEntityIdentity( dstrRecord, AUDITTYPE::ENTIDT, keyStringIDI );
      vectorHistorical.push_back( heEntityIdentity );

  
      // Entity ID Historical Data
      getField( this, IFASTBP_PROC::ENTITY_LIST, ifds::EntityIdentityRid, dstrRecord, false );
      keyStringIDI = NULL_STRING;
      addIDITagValue( keyStringIDI, MFCAN_IP_PARAM::ENTITY_ID, dstrEntityId );
      HistoricalElement heEntityIDs( dstrRecord, AUDITTYPE::ENTIDS, keyStringIDI );
      vectorHistorical.push_back( heEntityIDs );
   }
   else 
   {
      assert(0);
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//*********************************************************************************
SEVERITY EntityAloneProcess::populateWorkSessionEntityList( )
{
   MAKEFRAMEAUTOPROMOTE2(CND::BPBASE_CONDITION, CLASSNAME, GETHISTORICALPARAMETERS);

   DSTCWorkSession* pWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
   if( pWorkSession )
   {  
      // support search by First Name and Last Name
      // SIN
      // EntityID Type
      // WhereUse
      _entity_id = NULL_STRING;
      DString firstName, lastName, sin, idType,idValue,whereUse, code, searchType,entity_id;
      searchType = NULL_STRING;
      if( _searchUsing == SEARCHALLENTITYUSING::NAME )
      {
         searchType = AllEntitySearchType::NAME;
         firstName = _firstValue;
         lastName = _secondValue;
      }
      else if( _searchUsing == SEARCHALLENTITYUSING::SOCIAL_INSURANCE_NUMBER )
      {
         searchType = AllEntitySearchType::SIN;
         sin = _firstValue;      
      }
      else if( _searchUsing == SEARCHALLENTITYUSING::BIRTH_CERTIFICATE )
      {
         idType = IDTYPE::BIRTH_CERTIFICATE;
         searchType = AllEntitySearchType::IDTYPE;
         idValue = _firstValue;      
      }
      else if( _searchUsing == SEARCHALLENTITYUSING::CREDIT_CARD )
      {
         searchType = AllEntitySearchType::IDTYPE;
         idType = IDTYPE::CREDIT_CARD;
         idValue = _firstValue;            
      }   
      else if (   _searchUsing == SEARCHALLENTITYUSING::DRIVER_LICENSE  )
      {
         searchType = AllEntitySearchType::IDTYPE;
         idType = IDTYPE::DRIVER_LICENSE;
         idValue = _firstValue;                     
      }
      else if (_searchUsing == SEARCHALLENTITYUSING::NATIONAL_ID )
      {
         searchType = AllEntitySearchType::IDTYPE;
         idType = IDTYPE::NATIONAL_ID;
         idValue = _firstValue;                     
      }
      else if (_searchUsing == SEARCHALLENTITYUSING::PASSPORT )
      {
         searchType = AllEntitySearchType::IDTYPE;
         idType = IDTYPE::PASSPORT;
         idValue = _firstValue;                     
      }
      else if (_searchUsing == SEARCHALLENTITYUSING::SOCIAL_SECURITY_INSURANCE_CARD )
      {
         searchType = AllEntitySearchType::IDTYPE;
         idType = IDTYPE::SOCIAL_SEC_INS_CARD;
         idValue = _firstValue;                     
      }
      else if( _searchUsing == SEARCHALLENTITYUSING::ENTITY_ID )
      {
  
         _entity_id = _firstValue;                           
      }
      else if ( _searchUsing == SEARCHALLENTITYUSING::WHEREUSE )
      {
         searchType = AllEntitySearchType::WHEREUSE;
         whereUse = _firstValue; 
		 if (whereUse == WhereUseSearchType::FUND || whereUse == WhereUseSearchType::FUND_SPONSOR || 
			 whereUse == WhereUseSearchType::REG_AGENT )
			 code = _secondValue;
		 else
			 code = NULL_STRING;
      }

      try
      {
           SEVERITY sevRtn = NO_CONDITION;
           if( searchType != NULL_STRING )
           {
               if( _pEntitySearchList == NULL )
               {
                     _pEntitySearchList = new EntitySearchList( *pWorkSession );
               }
               sevRtn = _pEntitySearchList->init( searchType,firstName,lastName,sin, 
                                    idType,idValue, whereUse, code ); 
           }
            if( sevRtn <= WARNING )
            {
               populateEntityByKey( );
               WorkSessionEntityList *pWorkSessionEntityList = NULL;
               if (pWorkSession->getWorkSessionEntityList (pWorkSessionEntityList) <= WARNING &&
                     pWorkSessionEntityList)
               {
                     setContainer( IFASTBP_PROC::ENTITY_LIST, pWorkSessionEntityList );
               }      
            }
            else
            {
               delete _pEntitySearchList;
               _pEntitySearchList = NULL;            
            }
         }
      catch( ConditionException &ce )
         {
            SETCONDITIONFROMEXCEPTION( ce );
         }
         catch( ... )
         {
            assert( 0 );
            THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, I_( "performSearch" ), 
                           CND::BP_ERR_UNKNOWN_EXCEPTION );
         }


   }
   return NO_CONDITION;
   //return GETCURRENTHIGHESTSEVERITY();
}
//*******************************************************************************************
SEVERITY EntityAloneProcess::populateEntityByKey(const DString dstrKey /* NULL_STRING */ )
{

   MAKEFRAMEAUTOPROMOTE2(CND::BPBASE_CONDITION, CLASSNAME, GETHISTORICALPARAMETERS);
   DSTCWorkSession* pWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
   if( pWorkSession && _pEntitySearchList )
   {  
         BFObjIter iter (*_pEntitySearchList, getDataGroupId()  );
         if (dstrKey != NULL_STRING )
         {  
            iter.positionByKey( dstrKey  );
         }
         while ( !iter.end() )
         {
               DString dstrEntityId;
               iter.getObject()->getField(ifds::EntityId,dstrEntityId, getDataGroupId(),false );
               dstrEntityId.strip();
               Entity*  pEntity = NULL;
               // populate all entity here
               pWorkSession->getEntity( getDataGroupId(), dstrEntityId,pEntity );
               ++iter;
         }
   }
   else if (pWorkSession && _entity_id != NULL_STRING )
   {
         Entity*  pEntity = NULL;
         // populate all entity here
         pWorkSession->getEntity( getDataGroupId(), _entity_id,pEntity );
   }
   return GETCURRENTHIGHESTSEVERITY();
}
//*********************************************************************************************

SEVERITY EntityAloneProcess::performSearch( GenericInterface *rpGI, 
                                           const BFContainerId& idSearch, E_SEARCHACTION eSearchAction )

{  
   MAKEFRAMEAUTOPROMOTE2(CND::BPBASE_CONDITION, CLASSNAME, GETHISTORICALPARAMETERS);
   try
   {

      if( IFASTBP_PROC::ENTITY_LIST == idSearch )
      {
         if( _pEntitySearchList )
         {
            if( eSearchAction == SEARCH_NEXT_BLOCK )
            {
               BFObjIter iter (*_pEntitySearchList, getDataGroupId()  );
               DString lastKey;
               while ( !iter.end() )
               {
                  lastKey = iter.getStringKey();
                  ++iter;
               }
               _pEntitySearchList->getMore();
               populateEntityByKey( lastKey );
            }
         }
      }
      else if( IFASTBP_PROC::WHEREUSED_LIST == idSearch )
      {
         WhereUsedList* pList = (WhereUsedList* ) (getPtrForContainer( 
                  IFASTBP_PROC::WHEREUSED_LIST, getDataGroupId() ) );      
         if( pList )
         {
            pList->getMore();         
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
      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, I_( "performSearch" ), 
                      CND::BP_ERR_UNKNOWN_EXCEPTION );
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
bool EntityAloneProcess::doMoreRecordsExist( GenericInterface *rpGICaller, const BFContainerId& idSearch )
{
   if(  idSearch == IFASTBP_PROC::ENTITY_LIST )
   {
         return(rpGICaller == NULL || _pEntitySearchList == NULL ? false : 
             _pEntitySearchList->doMoreRecordsExist() );

   }
   else if ( idSearch == IFASTBP_PROC::WHEREUSED_LIST )
   {
         WhereUsedList* pList = (WhereUsedList* ) (getPtrForContainer( 
                  IFASTBP_PROC::WHEREUSED_LIST, getDataGroupId() ) ); 
         if( pList )
         {
            return ( pList->doMoreRecordsExist() );
         }   
   }
   return false;
}

//******************************************************************************
//              Private Methods
//******************************************************************************

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/EntityAloneProcess.cpp-arc  $
// 
//    Rev 1.13   Jul 16 2012 12:22:34   dchatcha
// P0179630 FN01 FATCA Project - Entity level.
// 
//    Rev 1.12   Apr 04 2012 20:39:18   wp040039
// PETP0187485-Entity Maintenance
// 
//    Rev 1.10   Jul 27 2007 16:42:48   kovacsro
// PET 2372 FN02 FDP-AIM KYC
// 
//    Rev 1.9   Nov 20 2006 13:53:32   jankovii
// PET 2287 FN01 - Grupo Mundial Trade Aggregation.
// 
//    Rev 1.8   Jul 26 2006 13:39:30   popescu
// PET 2192 FN02 - Dealings-Sender Cut-Off Time.
// 
//    Rev 1.7   Jul 21 2006 14:04:02   jankovii
// PET 2192 FN02 - Dealings-Sender Cut-Off Time.
// 
//    Rev 1.6   Dec 05 2005 08:57:26   jankovii
// Resync for incident 468333 - status in where used.
// 
//    Rev 1.5   Nov 28 2005 09:34:32   jankovii
// PET1228_FN02_ EU Savings Directive Phase Two
// 
//    Rev 1.4   Oct 27 2005 10:06:36   jankovii
// PET1228_FN01-EU Savings Directive Phase
// 
//    Rev 1.3   May 19 2005 15:58:54   yingbaol
// Incident297032: add status for entity
// 
//    Rev 1.2   Apr 18 2005 09:20:24   yingbaol
// Incident 288575: add new search type:where use
// 
//    Rev 1.1   Mar 09 2005 16:07:02   yingbaol
// PET1171,FN01:EU saving entity update
// 
//    Rev 1.0   Mar 01 2005 09:56:38   yingbaol
// Initial revision.
 * 
 * 
 */
