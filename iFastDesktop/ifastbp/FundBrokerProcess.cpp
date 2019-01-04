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
// ^FILE   : FundBrokerProcess.cpp
// ^AUTHOR : 
// ^DATE   : July 21, 2004  
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : FundBrokerProcess
//    This class manages the address book process.
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include "stdafx.h"
#include "FundBrokerProcessinclude.h"
#include "FundBrokerProcess.hpp"
#include <ifastcbo\mfaccount.hpp>
#include <ifastcbo\FundBrokerFeeList.hpp>
#include <ifastcbo\FundBrokerList.hpp>
#include <ifastcbo\FundBroker.hpp>
#include <ifastcbo\mgmtco.hpp>
#include <bfcbo\bfobjiter.hpp>
#include <ifastcbo\entity.hpp>
#include <ifastcbo\entityidslist.hpp>
#include <ifastdataimpl\dse_dstc0326_vw.hpp>
#include <ifastcbo\WorkSessionEntityList.hpp>

extern IFASTBP_LINKAGE const I_CHAR* CMD_GUI_FUND_BROKER;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_FUND_BROKER;

#include <bfproc\concreteprocesscreator.hpp>
static ConcreteProcessCreator< FundBrokerProcess > processCreator( CMD_BPROC_FUND_BROKER );

namespace
{
   // Trace literals
   const I_CHAR *CLASSNAME = I_( "FundBrokerProcess" );   
}

namespace FUNDBROKER
{
   const I_CHAR * const FUNDBROKERLIST = I_( "FundBrokerList" );
   const I_CHAR * const ENTITY_LIST = I_( "ENTITY_LIST" );
   const I_CHAR * const FEELIST = I_("FEE_LIST");


   const I_CHAR * const FROM_SCR = I_( "from_screen" );
   
   const I_CHAR * const FUNDBROKER_CODE = I_( "FundBrokerCode" );
   const I_CHAR * const SEARCHTYPE = I_( "SearchType" );   
   const I_CHAR * const FUNDBROKER_NAME = I_( "FundBrokerName" );
   const I_CHAR * const SYSTEM = I_( "System" );
   const I_CHAR * const ALL = I_( "All" );
   const I_CHAR * const YES = I_( "Y" );
   const I_CHAR * const NO = I_( "N" );
}

namespace CND
{  // Conditions used
   extern CLASS_IMPORT const long BP_ERR_UNKNOWN_EXCEPTION;
   extern const long ERR_BROKER_NAME_EMPTY;
}
namespace ifds
{  
   
   extern CLASS_IMPORT const BFTextFieldId ChargeOption;
   extern CLASS_IMPORT const BFTextFieldId FeeModelOption;
   extern CLASS_IMPORT const BFTextFieldId FeeCode;
   extern CLASS_IMPORT const BFTextFieldId ParamFeeType;
   extern CLASS_IMPORT const BFDecimalFieldId Rate;
   extern CLASS_IMPORT const BFTextFieldId Currency;
   extern CLASS_IMPORT const BFTextFieldId CommGroup;
   extern CLASS_IMPORT const BFTextFieldId IdValue;
   extern CLASS_IMPORT const BFTextFieldId IdType;
   extern CLASS_IMPORT const BFDateFieldId IdDate;
   extern CLASS_IMPORT const BFTextFieldId IdStatus;
   extern CLASS_IMPORT const BFTextFieldId BusinessPhone;
   extern CLASS_IMPORT const BFTextFieldId BusinessExt;
   extern CLASS_IMPORT const BFTextFieldId BusinessFax;
   extern CLASS_IMPORT const BFTextFieldId Email;
   extern CLASS_IMPORT const BFTextFieldId Contact;
   extern CLASS_IMPORT const BFDateFieldId StopDate;
   
   extern CLASS_IMPORT const BFTextFieldId AddrLine5;
   extern CLASS_IMPORT const BFTextFieldId LanguageCode;
   extern CLASS_IMPORT const BFTextFieldId LastName;
   extern CLASS_IMPORT const BFTextFieldId SetFundToInvestr;
   extern CLASS_IMPORT const BFTextFieldId Changed;

   extern CLASS_IMPORT const BFTextFieldId Nationality;
   extern CLASS_IMPORT const BFDateFieldId DofBirth;
   extern CLASS_IMPORT const BFTextFieldId OccupationCode;
   extern CLASS_IMPORT const BFTextFieldId TaxJuris;
   extern CLASS_IMPORT const BFNumericFieldId FundBrokerOffsetTime;   
   extern CLASS_IMPORT const BFTextFieldId FundBrokerRegAddr;   
   extern CLASS_IMPORT const BFTextFieldId CountryOfIssue;
   extern CLASS_IMPORT const BFDateFieldId IdExpireDate;
}
//******************************************************************************
//              Public Methods
//******************************************************************************

//CP20030319FundBrokerProcess::FundBrokerProcess() 
FundBrokerProcess::FundBrokerProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: AbstractProcess( pGIC, pGIParent, rCommand )
,  _rpChildGI( NULL )
, _pContact (I_("1"))
, m_FundBrokerName( I_("") )
, m_FundBrokerCode( I_("") )
, m_SearchType( I_("") )
{
   TRACE_CONSTRUCTOR( CLASSNAME, I_( "FundBrokerProcess" ) );

   addContainer( IFASTBP_PROC::FUND_BROKER_LIST, true, BF::NullContainerId, true, I_("FundBrokerList") );
   addContainer( IFASTBP_PROC::FEE_PARAM_LIST, true, IFASTBP_PROC::FUND_BROKER_LIST, true, I_("FundBrokerFee") );   
   addContainer( IFASTBP_PROC::ENTITY_LIST,   true );
   addContainer( IFASTBP_PROC::ENTITY_IDS_LIST, true, IFASTBP_PROC::FUND_BROKER_LIST, true, I_("EntityIds") );   

   addFieldDetails( ifds::FundBrokerCode,    IFASTBP_PROC::FUND_BROKER_LIST );
   addFieldDetails( ifds::EntityId,IFASTBP_PROC::FUND_BROKER_LIST );
   addFieldDetails( ifds::VersionNum,IFASTBP_PROC::FUND_BROKER_LIST );
   addFieldDetails( ifds::WhereUseFundBrokerRId,IFASTBP_PROC::FUND_BROKER_LIST );

   addFieldDetails( ifds::Name,       IFASTBP_PROC::FUND_BROKER_LIST );
   addFieldDetails( ifds::EffectiveDate,  IFASTBP_PROC::FUND_BROKER_LIST );   
   addFieldDetails( ifds::StopDate,  IFASTBP_PROC::FUND_BROKER_LIST );   
   addFieldDetails( ifds::PUEVCapable,    IFASTBP_PROC::FUND_BROKER_LIST );
   addFieldDetails( ifds::RoutingType,    IFASTBP_PROC::FUND_BROKER_LIST );
   addFieldDetails( ifds::PriceType,      IFASTBP_PROC::FUND_BROKER_LIST );
   addFieldDetails( ifds::Remarks1,        IFASTBP_PROC::FUND_BROKER_LIST );
   addFieldDetails( ifds::ProcessDate,    IFASTBP_PROC::FUND_BROKER_LIST );
   addFieldDetails( ifds::ModDate,        IFASTBP_PROC::FUND_BROKER_LIST );
   addFieldDetails( ifds::Username,       IFASTBP_PROC::FUND_BROKER_LIST );
   addFieldDetails( ifds::ModUser,        IFASTBP_PROC::FUND_BROKER_LIST );
   addFieldDetails( ifds::FundBrokerOffsetTime, IFASTBP_PROC::FUND_BROKER_LIST );

   addFieldDetails( ifds::AddrId,   		IFASTBP_PROC::FUND_BROKER_LIST );
   addFieldDetails( ifds::EntityAddrVer,	IFASTBP_PROC::FUND_BROKER_LIST );
   addFieldDetails( ifds::AddrLine1,		IFASTBP_PROC::FUND_BROKER_LIST );
   addFieldDetails( ifds::AddrLine2,		IFASTBP_PROC::FUND_BROKER_LIST );
   addFieldDetails( ifds::AddrLine3,		IFASTBP_PROC::FUND_BROKER_LIST );
   addFieldDetails( ifds::AddrLine4,		IFASTBP_PROC::FUND_BROKER_LIST );
   addFieldDetails( ifds::AddrLine5,		IFASTBP_PROC::FUND_BROKER_LIST );
   addFieldDetails( ifds::PostalCode,		IFASTBP_PROC::FUND_BROKER_LIST );
   addFieldDetails( ifds::Country,		IFASTBP_PROC::FUND_BROKER_LIST );

   addFieldDetails( ifds::SetFundToInvestr,		IFASTBP_PROC::FUND_BROKER_LIST );
   
   addFieldDetails( ifds::Contact1EntityID,			IFASTBP_PROC::FUND_BROKER_LIST );
   addFieldDetails( ifds::Contact1EntityVersion,   IFASTBP_PROC::FUND_BROKER_LIST );
   addFieldDetails( ifds::WhereUseContact1RecId,	IFASTBP_PROC::FUND_BROKER_LIST );
   addFieldDetails( ifds::Contact2EntityID,			IFASTBP_PROC::FUND_BROKER_LIST );
   addFieldDetails( ifds::Contact2EntityVersion,   IFASTBP_PROC::FUND_BROKER_LIST );
   addFieldDetails( ifds::WhereUseContact2RecId,	IFASTBP_PROC::FUND_BROKER_LIST );
   addFieldDetails( ifds::FrClearingMethod,	      IFASTBP_PROC::FUND_BROKER_LIST );
   addFieldDetails( ifds::Changed,	      IFASTBP_PROC::FUND_BROKER_LIST );
   addFieldDetails( ifds::RegAddrLine1,			IFASTBP_PROC::FUND_BROKER_LIST );
   addFieldDetails( ifds::RegAddrLine2,			IFASTBP_PROC::FUND_BROKER_LIST );
   addFieldDetails( ifds::RegAddrLine3,			IFASTBP_PROC::FUND_BROKER_LIST );
   addFieldDetails( ifds::RegAddrLine4,			IFASTBP_PROC::FUND_BROKER_LIST );
   addFieldDetails( ifds::RegPostalCode,			IFASTBP_PROC::FUND_BROKER_LIST );
   addFieldDetails( ifds::RegCountry,			IFASTBP_PROC::FUND_BROKER_LIST );
   addFieldDetails( ifds::FbDealer,			IFASTBP_PROC::FUND_BROKER_LIST );
   addFieldDetails( ifds::FbAgent,			IFASTBP_PROC::FUND_BROKER_LIST );
   addFieldDetails( ifds::FbBranch,			IFASTBP_PROC::FUND_BROKER_LIST );
   addFieldDetails( ifds::FbPortfolio,			IFASTBP_PROC::FUND_BROKER_LIST );
   addFieldDetails( ifds::AcctServicer,			IFASTBP_PROC::FUND_BROKER_LIST );
   addFieldDetails( ifds::RegName,			IFASTBP_PROC::FUND_BROKER_LIST );
   addFieldDetails( ifds::RegAcct,			IFASTBP_PROC::FUND_BROKER_LIST );
   addFieldDetails( ifds::FbAcctDesig,			IFASTBP_PROC::FUND_BROKER_LIST );
   addFieldDetails( ifds::FbTemplate,			IFASTBP_PROC::FUND_BROKER_LIST );
   addFieldDetails( ifds::FbSettleType,			IFASTBP_PROC::FUND_BROKER_LIST );
   addFieldDetails( ifds::FundBrokerRegAddr,			IFASTBP_PROC::FUND_BROKER_LIST );
   addFieldDetails( ifds::FeeCode,        IFASTBP_PROC::FEE_PARAM_LIST );
   addFieldDetails( ifds::ParamFeeType,   IFASTBP_PROC::FEE_PARAM_LIST );
   addFieldDetails( ifds::Rate,           IFASTBP_PROC::FEE_PARAM_LIST );
   addFieldDetails( ifds::EffectiveDate,  IFASTBP_PROC::FEE_PARAM_LIST );
   addFieldDetails( ifds::StopDate,       IFASTBP_PROC::FEE_PARAM_LIST );   
   addFieldDetails( ifds::FundBrokerCode, IFASTBP_PROC::FEE_PARAM_LIST );
   addFieldDetails( ifds::CommGroup,      IFASTBP_PROC::FEE_PARAM_LIST );

   addFieldDetails( ifds::IdValue,   IFASTBP_PROC::ENTITY_IDS_LIST ); 
   addFieldDetails( ifds::IdType,    IFASTBP_PROC::ENTITY_IDS_LIST );
   addFieldDetails( ifds::IdDate,    IFASTBP_PROC::ENTITY_IDS_LIST );   
   addFieldDetails (ifds::CountryOfIssue, IFASTBP_PROC::ENTITY_IDS_LIST ); 
   addFieldDetails( ifds::IdStatus,  IFASTBP_PROC::ENTITY_IDS_LIST );
   addFieldDetails( ifds::IdExpireDate, IFASTBP_PROC::ENTITY_IDS_LIST);   

   addFieldDetails( ifds::FirstName, BF::NullContainerId, SUBCLASS_PROCESS);
   addFieldDetails( ifds::LastName,  BF::NullContainerId, SUBCLASS_PROCESS);
   addFieldDetails( ifds::LanguageCode,  BF::NullContainerId, SUBCLASS_PROCESS);
   addFieldDetails( ifds::BusinessPhone,  BF::NullContainerId, SUBCLASS_PROCESS);
   addFieldDetails( ifds::BusinessExt,    BF::NullContainerId, SUBCLASS_PROCESS);
   addFieldDetails( ifds::BusinessFax,    BF::NullContainerId, SUBCLASS_PROCESS);
   addFieldDetails( ifds::Email,          BF::NullContainerId, SUBCLASS_PROCESS);

   addFieldDetails( ifds::Contact,        IFASTBP_PROC::FUND_BROKER_LIST, SUBCLASS_PROCESS );
   addFieldDetails( FUNDBROKER::NEWITEM,            IFASTBP_PROC::FUND_BROKER_LIST, SUBCLASS_PROCESS );
   addFieldDetails( FUNDBROKER::ISNAMEUPDATE,       IFASTBP_PROC::FUND_BROKER_LIST, SUBCLASS_PROCESS );

   addFieldDetails( ifds::FbTagent,		IFASTBP_PROC::FUND_BROKER_LIST );
   addFieldDetails( ifds::FbFndCmpny,	IFASTBP_PROC::FUND_BROKER_LIST );
   addFieldDetails( ifds::FbType,		IFASTBP_PROC::FUND_BROKER_LIST );
   addFieldDetails( ifds::FbClientGrp,	IFASTBP_PROC::FUND_BROKER_LIST );
   
}

//******************************************************************************
FundBrokerProcess::~FundBrokerProcess()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************
SEVERITY FundBrokerProcess::doInit()
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, DOINIT );

   SEVERITY sevRtn = NO_CONDITION;
   try
   {
      getParent()->getParameter( FUNDBROKER::SEARCHTYPE, m_SearchType );
      m_SearchType.strip();

	  getParent()->getParameter( FUNDBROKER::FUNDBROKER_CODE, m_FundBrokerCode );
	  m_FundBrokerCode.strip();      

	  getParent()->getParameter( FUNDBROKER::FUNDBROKER_NAME, m_FundBrokerName );
      m_FundBrokerName.strip();

	//2319580 - This logic is to force fundbroker name criteria to be the fundbroker name 
	//that couldn't be found anywhere so that it can bring up the Fund Broker screen 
	//with empty fund broker row just like the existing function when do a search 
	//for a non-existing fund broker by name.
	//We should replace the existing fuction when do a seach for a non-existing 
	//fund broker by name to return "data not found instead of bring up fund broker screen 
	//with empty fund broker row.
	  DSTCWorkSession *dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession()); 
	  dstcWorkSession->getFundBrokerList( _pFundBrokerList, BF::HOST, true, m_FundBrokerCode, m_FundBrokerName,
			( m_FundBrokerName == I_("-fromnewfb-") ) ? false : true );	  

      if( _pFundBrokerList )
      {
		setContainer( IFASTBP_PROC::FUND_BROKER_LIST, _pFundBrokerList ); 
      }
      else
      {
		//return(GETCURRENTHIGHESTSEVERITY());
      }
	  
      WorkSessionEntityList *pWorkSessionEntityList = NULL;
      if (dstcWorkSession->getWorkSessionEntityList( pWorkSessionEntityList) <= WARNING && pWorkSessionEntityList)
      { 
         setContainer( IFASTBP_PROC::ENTITY_LIST, pWorkSessionEntityList );
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
   return(GETCURRENTHIGHESTSEVERITY());
}


//******************************************************************************
E_COMMANDRETURN FundBrokerProcess::doProcess()
{  
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, DOPROCESS );
   E_COMMANDRETURN rtn = CMD_FAILURE;

   try
   {
      if( isXMLAPIContext() )
      {
         rtn = CMD_MODELESS_INPROCESS;
      }
      else
      {
         rtn = invokeCommand( this, CMD_GUI_FUND_BROKER, getProcessType(), isModal(), &_rpChildGI );
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
bool  FundBrokerProcess::doModelessSetFocus( GenericInterface *rpGICaller )
{  // This is implemented to pass set focus on to child dialog.
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, DOMODELESSSETFOCUS );
   bool bRtn = false;
   try
   {
      assert( _rpChildGI && isValidModelessInterface( _rpChildGI ) );
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
bool  FundBrokerProcess::doModelessChildComplete( const Command &cmd )
{
   // End when GUI ends
   return( cmd.getKey() == CMD_GUI_FUND_BROKER );
}
//******************************************************************************
void* FundBrokerProcess::getPtrForContainer( const BFContainerId& idContainer, const BFDataGroupId& idDataGroup )
{
   void *ptr = NULL;
   DSTCWorkSession *dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());

   try
   {
      if( idContainer == IFASTBP_PROC::FEE_PARAM_LIST )
      { 
            FundBroker * pFundBroker = 
                  dynamic_cast < FundBroker *> (getCBOItem( IFASTBP_PROC::FUND_BROKER_LIST, idDataGroup ));
            if( pFundBroker )
            {
                  pFundBroker->getFundBrokerFeeList(_pFundBrokerFeeList, idDataGroup);
            }

            ptr = _pFundBrokerFeeList;
      }
      if( idContainer == IFASTBP_PROC::ENTITY_IDS_LIST )
      {
            DString entityId;
            BFAbstractCBO *rpPtr = getCBOItem( IFASTBP_PROC::FUND_BROKER_LIST, idDataGroup );

            EntityIdsList * _pEntityIdsList = NULL;
            rpPtr->getField( ifds::EntityId, entityId, idDataGroup );
            entityId.stripLeading( '0' );

            Entity *pEntity = NULL;
            if( entityId != NULL_STRING )
            {               
               dynamic_cast<DSTCWorkSession *>(getBFWorkSession())->getEntity( idDataGroup, entityId, pEntity );               
            }
            if( pEntity )
            {
               pEntity->getEntityIdsList( _pEntityIdsList, idDataGroup, true );
               if (_pEntityIdsList)
               {
                  //give it a dummy record if it does not have any
                  BFObjIter iter ( *_pEntityIdsList, 
                                    idDataGroup, 
                                    true, 
                                    BFObjIter::ITERTYPE::NON_DELETED);
                  if (iter.end()) //no record
                  {
                     DString emptyKey;

                     _pEntityIdsList->getObject ( emptyKey, //should be passed in as null_string
                                                  idDataGroup);
                  }
                  ptr = _pEntityIdsList;
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
bool FundBrokerProcess::doRefresh(
                               GenericInterface *rpGICaller,
                               const I_CHAR *szOriginalCommand
                               )
{
   return(_rpChildGI->refresh( this, NULL ));
}

//******************************************************************************

void FundBrokerProcess::doGetField(
                                const GenericInterface *rpGICaller,
                                const BFContainerId& idContainer,
                                const BFFieldId& idField,
                                const BFDataGroupId& idDataGroup,
                                DString &strValueOut,
                                bool bFormatted
                                ) const
{
   DSTCWorkSession *dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());


   if( idContainer == BF::NullContainerId )
   {
      if( idField == ifds::LastName || idField == ifds::FirstName || 
         idField == ifds::LanguageCode || idField == ifds::BusinessPhone || 
         idField == ifds::BusinessExt || idField == ifds::BusinessFax ||
         idField == ifds::Email )
      {
         BFFieldId fieldid;
         if(_pContact == I_("1") )
         {
            fieldid = ifds::Contact1EntityID;
         }
         else if( _pContact == I_("2"))
         {
            fieldid = ifds::Contact2EntityID;
         }
         else
         {
            return;
         }

         DString dstrEntityID;   
         FundBrokerProcess *rpNonConstThis = const_cast < FundBrokerProcess*> ( this );
         BFAbstractCBO *rpPtr = rpNonConstThis->getCBOItem( IFASTBP_PROC::FUND_BROKER_LIST, idDataGroup );
         rpPtr->getField( fieldid, dstrEntityID, idDataGroup );
         dstrEntityID.strip().stripLeading( '0' );
            
         if( dstrEntityID != NULL_STRING )
         {              
            Entity* pEntity;
            DSTCWorkSession *dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
            if( dstcWorkSession->getEntity( idDataGroup, dstrEntityID, pEntity ) <= WARNING )
            {
               pEntity->getField( idField, strValueOut, idDataGroup );
            }
         }
      }
   }

   if(idField == ifds::Contact )
   {
      strValueOut = _pContact;
   } 
   else if(idField == FUNDBROKER::NEWITEM )
   {
      FundBrokerProcess *rpNonConstThis = const_cast < FundBrokerProcess*> ( this );
      BFAbstractCBO *rpPtr = rpNonConstThis->getCBOItem( IFASTBP_PROC::FUND_BROKER_LIST, idDataGroup );
      if(rpPtr && rpPtr->isNew())
      {
         strValueOut = FUNDBROKER::YES;
      }
      else strValueOut = FUNDBROKER::NO;
   }
   else if(idField == FUNDBROKER::ISNAMEUPDATE )
   {
      
      FundBrokerProcess *rpNonConstThis = const_cast < FundBrokerProcess*> ( this );
      BFAbstractCBO *rpPtr = rpNonConstThis->getCBOItem( IFASTBP_PROC::FUND_BROKER_LIST, idDataGroup );	  
      //rpPtr->isFieldUpdated(ifds::LastName,strValueOut,idDataGroup );
      strValueOut = FUNDBROKER::YES;      
   }
}

//******************************************************************************
SEVERITY FundBrokerProcess::doSetField( const GenericInterface *rpGICaller,
                                        const BFContainerId& idContainer,
                                        const BFFieldId& fieldID,
                                        const BFDataGroupId& idDataGroup,
                                        const DString& strValue,
                                        bool bFormatted )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTBP_CONDITION, CLASSNAME, DOSETFIELD );

   if( idContainer == BF::NullContainerId )
   {
      if( fieldID == ifds::LastName || fieldID == ifds::FirstName || 
         fieldID == ifds::LanguageCode || fieldID == ifds::BusinessPhone || 
         fieldID == ifds::BusinessExt || fieldID == ifds::BusinessFax ||
         fieldID == ifds::Email )
      {
         BFFieldId fieldid;
         if(_pContact == I_("1") )
         {
            fieldid = ifds::Contact1EntityID;
         }
         else if(_pContact == I_("2") )
         {
            fieldid = ifds::Contact2EntityID;
         }
         else 
         {
            return(GETCURRENTHIGHESTSEVERITY());
         }

         DString dstrEntityID;
         FundBrokerProcess *rpNonConstThis = const_cast < FundBrokerProcess*> ( this );
         BFAbstractCBO *rpPtr = rpNonConstThis->getCBOItem( IFASTBP_PROC::FUND_BROKER_LIST, idDataGroup );
         rpPtr->getField(fieldid,dstrEntityID,idDataGroup );
         dstrEntityID.strip().stripLeading( '0' );
         Entity* pEntity = NULL;
         DSTCWorkSession *dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
         if( dstrEntityID != NULL_STRING )
         {            
            if( dstcWorkSession->getEntity( idDataGroup, dstrEntityID, pEntity ) <= WARNING )
            {
               pEntity->setField (fieldID, strValue, getDataGroupId(), false);
			   
			   DString dstrlastname, dstrfirstname, dstrlanguage, dstrphone, dstrfax, dstremail, dstrext;
			   pEntity->getField(ifds::LastName,dstrlastname,idDataGroup );
			   pEntity->getField(ifds::FirstName,dstrfirstname,idDataGroup );			   
			   pEntity->getField(ifds::BusinessPhone,dstrphone,idDataGroup );
			   pEntity->getField(ifds::BusinessFax,dstrfax,idDataGroup );
			   pEntity->getField(ifds::Email,dstremail,idDataGroup );

			   pEntity->getField(ifds::BusinessExt,dstrext,idDataGroup );
			   pEntity->getField(ifds::LanguageCode,dstrlanguage,idDataGroup );

               if( dstrlastname == NULL_STRING && dstrfirstname == NULL_STRING &&
				   dstrphone == NULL_STRING && dstrfax == NULL_STRING &&
				   dstremail == NULL_STRING /*&& dstrlanguage == NULL_STRING && dstrext == NULL_STRING*/ )
               {                  
				  pEntity->reset( getDataGroupId() );
				  rpPtr->setField( fieldid, I_(""), idDataGroup );
               }
            }
         }
         else if( strValue != NULL_STRING )
         {
            WorkSessionEntityList *pWorkSessionEntityList = NULL;
            if (dstcWorkSession->getWorkSessionEntityList( pWorkSessionEntityList) <= WARNING && pWorkSessionEntityList)
            {               
               DString tempentityID;
               pWorkSessionEntityList->getNewEntity(idDataGroup, pEntity);
               pEntity->getEntityId (tempentityID);
               //pEntity->getField(ifds::EntityId,tempentityID,idDataGroup);	
               rpPtr->setField( fieldid, tempentityID, idDataGroup );

			   pEntity->setFieldValid( ifds::Nationality, idDataGroup, true );
			   pEntity->setFieldValid( ifds::DofBirth, idDataGroup, true );
			   pEntity->setFieldValid( ifds::OccupationCode, idDataGroup, true );
			   pEntity->setFieldValid( ifds::TaxJuris, idDataGroup, true );

            }
            pEntity->setField (fieldID, strValue, getDataGroupId(), false);
         }
		 CLEARCURRENTCONDITIONS();
      }
   }

   if(fieldID == ifds::Contact )
   {
      _pContact = strValue;
   }
   

   return(GETCURRENTHIGHESTSEVERITY());
}
//*****************************************************************************

SEVERITY FundBrokerProcess::performSearch( GenericInterface *rpGI, const BFContainerId& idSearch, 
                                         E_SEARCHACTION eSearchAction )
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, I_("performSearch") );   

   try
   {
      adjustKey( idSearch );
   }
   catch( ConditionException &ce )
   {
      SETCONDITIONFROMEXCEPTION( ce );
   }
   catch( ... )
   {
      assert( 0 );
      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, I_("performSearch"), CND::BP_ERR_UNKNOWN_EXCEPTION );
   }
   return(GETCURRENTHIGHESTSEVERITY()); 
}
//***********************************************************************************
bool FundBrokerProcess::doMoreRecordsExist(
                                        GenericInterface *rpGICaller,
                                        const BFContainerId& idSearch
                                        )
{
   if( idSearch == IFASTBP_PROC::FUND_BROKER_LIST )
   {
		return (rpGICaller == NULL || _pFundBrokerList == NULL) ? 
			false : _pFundBrokerList->doMoreRecordsExist();      
   }

   if( idSearch == IFASTBP_PROC::FEE_PARAM_LIST )
   {
	   const BFDataGroupId& idDataGroup = getDataGroupId();
		FundBroker * pFundBroker = 
                dynamic_cast < FundBroker *> (getCBOItem( IFASTBP_PROC::FUND_BROKER_LIST, idDataGroup ));
        if( pFundBroker )
		{
              pFundBroker->getFundBrokerFeeList(_pFundBrokerFeeList, idDataGroup);
		}

		return (rpGICaller == NULL || _pFundBrokerFeeList == NULL) ? 
			false : _pFundBrokerFeeList->doMoreRecordsExist();        
   }

   return false;
}

//******************************************************************************

bool FundBrokerProcess::doOk( GenericInterface *rpGICaller )
{
   TRACE_METHOD( CLASSNAME, I_("doOK") );

	SEVERITY sev = NO_CONDITION;

   return(sev == NO_CONDITION);
}

//******************************************************************************
const DString& FundBrokerProcess::getNextListItemKey( const GenericInterface *rpGICaller, const BFContainerId& idList )
{  
   TRACE_METHOD( CLASSNAME, GETNEXTLISTITEMKEY );

   static DString key = NULL_STRING;

   try
   {
      if( idList == IFASTBP_PROC::ENTITY_IDS_LIST )
      {
         if( !isContainerValid(idList) ) return key;
      }
   }
   catch( ConditionException & )
   {
      throw;
   }
   catch( ... )
   {  // Just to catch at earliest point
      assert( 0 );
      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, GETNEXTLISTITEMKEY,
                      CND::BP_ERR_UNKNOWN_EXCEPTION );
   }

   return (AbstractProcess::getNextListItemKey( rpGICaller, idList ));
}

//******************************************************************************
const DString& FundBrokerProcess::getFirstListItemKey( const GenericInterface *rpGICaller, const BFContainerId& idList )
{  
   TRACE_METHOD( CLASSNAME, GETFIRSTLISTITEMKEY );

   const static DString key = NULL_STRING;
   try
   {
      if( idList == IFASTBP_PROC::ENTITY_IDS_LIST )
      {
         if( !isContainerValid(idList) ) return key;         
      }
   }
   catch( ConditionException & )
   {
      throw;
   }
   catch( ... )
   {  // Just to catch at earliest point
      assert( 0 );
      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, GETFIRSTLISTITEMKEY,
                      CND::BP_ERR_UNKNOWN_EXCEPTION );
   }
   return (AbstractProcess::getFirstListItemKey( rpGICaller, idList ));
}

//******************************************************************************
void FundBrokerProcess::adjustKey( const BFContainerId& idList )
{

      if( idList == IFASTBP_PROC::FUND_BROKER_LIST )
      {
		 _pFundBrokerList->getMore ();        
      }
      if( idList == IFASTBP_PROC::FEE_PARAM_LIST )
      {
         FundBrokerFeeList * _pFundBrokerFeeList;
         FundBroker * pFundBroker = 
            dynamic_cast < FundBroker *> (getCBOItem( IFASTBP_PROC::FUND_BROKER_LIST, getDataGroupId() ));
         pFundBroker->getFundBrokerFeeList(_pFundBrokerFeeList, getDataGroupId());

         if( _pFundBrokerFeeList )
         {
            _pFundBrokerFeeList->getMore();  
         }
      }


   return;
}


//******************************************************************************
bool FundBrokerProcess::doSend(GenericInterface *rpGICaller, const I_CHAR *szMessage ) 
{
   return( false );
}

//**********************************************************************
SEVERITY FundBrokerProcess::doValidateAll(BFAbstractCBO *rpWSD, 
   const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::BPBASE_CONDITION, CLASSNAME, I_("doValidateAll"));

   _pFundBrokerList->validateAll (idDataGroup);

   WorkSessionEntityList *pWorkSessionEntityList = NULL;
   DSTCWorkSession *dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
   if (dstcWorkSession->getWorkSessionEntityList( pWorkSessionEntityList) <= WARNING && pWorkSessionEntityList)
   { 
      pWorkSessionEntityList->validateAll (idDataGroup);
   }
         
   return GETCURRENTHIGHESTSEVERITY();
}
//******************************************************************************
//              Private Methods
//******************************************************************************

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/FundBrokerProcess.cpp-arc  $
// 
//    Rev 1.21   Jul 20 2012 14:18:24   dchatcha
// P0179630 FN01 FATCA Project - Entity level. - build error.
// 
//    Rev 1.20   Jul 19 2012 12:07:34   dchatcha
// P0179630 FN01 FATCA Project - Entity level.
// 
//    Rev 1.19   Apr 04 2012 20:44:22   wp040039
// PETP0187485-Entity Maintenance
// 
//    Rev 1.18   Dec 17 2011 19:49:10   wp040133
//  P0192479 AFT out bOund Order Ehnacement
// 
//    Rev 1.17   Aug 03 2011 11:32:58   wp040027
// P0186774 - Mutual Fund Order Processing
// 
//    Rev 1.16   Jan 20 2011 07:13:56   wichian
// IN#2319580 - Updated code according to code review 579300 w/o
// 
//    Rev 1.14   Sep 18 2007 06:33:06   smithdav
// IN 1002026 addFieldDetails for idStatus.
// 
//    Rev 1.13   Dec 15 2005 19:42:56   popescu
// Incident# 467783 no internal error when user adds a new fund broker.
// 
//    Rev 1.12   May 05 2005 17:23:02   Fengyong
// #Incident 300186 - continue fix for the syncup incident.
// fund broker entity should not have occupation ... mandatory fields.
// 
//    Rev 1.11   Dec 02 2004 11:52:16   Fengyong
// PET1117FN54 - minor change
// 
//    Rev 1.10   Nov 30 2004 13:05:10   Fengyong
// Add setfundtoinvestor
// 
//    Rev 1.9   Nov 24 2004 16:51:00   Fengyong
// more button fix
// 
//    Rev 1.8   Nov 23 2004 17:26:08   Fengyong
// PET1117 FN54 - adjustment after first day intergretion test
// 
//    Rev 1.7   Nov 18 2004 09:51:14   Fengyong
// Add parameters
// 
//    Rev 1.6   Nov 15 2004 17:43:06   Fengyong
// claearcondition for set field
// 
//    Rev 1.5   Nov 15 2004 15:55:48   Fengyong
// Syncup after .net conversion
// 
//    Rev 1.4   Nov 08 2004 09:41:12   FENGYONG
// view number change
// 
//    Rev 1.3   Nov 05 2004 10:52:42   FENGYONG
// view team change the number of view from 319 to 326
// 
//    Rev 1.2   Nov 04 2004 17:50:02   FENGYONG
// PET1117 FN54 - Fund Broker static : Add IDS validation
// 
//    Rev 1.1   Nov 04 2004 10:59:44   FENGYONG
// PET1117 FN54 - Fund broker static temp check in for 59 build
// 
//    Rev 1.0   Oct 19 2004 14:41:40   FENGYONG
// Initial revision.
 *
 */
