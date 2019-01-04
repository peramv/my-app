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
// ^FILE   : RegPlanTransferProcess.cpp
// ^AUTHOR : Mihai Buzila
// ^DATE   : November 4, 2016
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : RegPlanTransferProcess
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include "stdafx.h"
#include "RegPlanTransferprocess.hpp"
#include "regplantransferprocessincludes.h"
#include <ifastcbo\regplantransfer.hpp>
#include <ifastcbo\regplantransferlist.hpp>
#include <ifastcbo\regplantransferalloclist.hpp>

#include <ifastcbo\taxtyperule.hpp>
#include <ifastcbo\taxtyperulelist.hpp>
#include <ifastcbo\entitylist.hpp>
#include <ifastcbo\entity.hpp>
#include <ifastcbo\mfaccount.hpp>
#include <ifastcbo\accountentityxref.hpp>
#include <ifastcbo\accountentityxrefobject.hpp>

#include <ifastdataimpl\dse_dstc0472_vw.hpp>
#include <ifastdataimpl\dse_dstc0474_req.hpp>
#include <ifastdataimpl\dse_dstc0473_vw.hpp>
#include <ifastcbo\mgmtco.hpp>
extern IFASTBP_LINKAGE const I_CHAR* CMD_GUI_REG_PLAN_TRANSFER;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_REG_PLAN_TRANSFER;
#include <bfproc\concreteprocesscreator.hpp>
static ConcreteProcessCreator< RegPlanTransferProcess > processCreator( CMD_BPROC_REG_PLAN_TRANSFER );

namespace 
{
   // Trace literals
   const I_CHAR * const CLASSNAME   = I_( "RegPlanTransferProcess" );
   const I_CHAR * const PERFORMSEARCH = I_( "PerformSearch" );
   const I_CHAR * const Y           = I_( "Y" );
   const I_CHAR * const N           = I_( "N" );
}

namespace REG_PLAN_TRANSFER
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

   extern CLASS_IMPORT const BFDecimalFieldId Percentage;
   extern CLASS_IMPORT const BFDecimalFieldId Amount;
   extern CLASS_IMPORT const BFTextFieldId FundNumber;

   extern CLASS_IMPORT const BFDecimalFieldId USDollar;
}

namespace UAF
{
}

namespace UAF
{
   extern CLASS_IMPORT I_CHAR * const SEG_FUND_MULTI_CONTRACT;
}

//******************************************************************************
//              Public Methods
//******************************************************************************

//CP20030319RegPlanTransferProcess::RegPlanTransferProcess() : 
RegPlanTransferProcess::RegPlanTransferProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: AbstractProcess( pGIC, pGIParent, rCommand )
, _pRegPlanTransferList( NULL )
, _rpChildGI( NULL )
, _bIsDuringNASU(false)
, _dstrNewShareholder(NULL_STRING)
, _dstrNewAccount(NULL_STRING)
{
   TRACE_CONSTRUCTOR(CLASSNAME, NULL_STRING );

   addSubstituteList( ifds::ContractListHeading );
   //addSubstituteList( ifds::Status );

   //addSubstituteList( ifds::ProvinceCanada );
///   addSubstituteList( ifds::MaturityType );

   addContainer( IFASTBP_PROC::REG_PLAN_TRANSFER_LIST, true, BF::NullContainerId, true, I_("RegPlanTransf"));
   addContainer( IFASTBP_PROC::REG_PLAN_TRANSFER_ALLOC_LIST, true, IFASTBP_PROC::REG_PLAN_TRANSFER_LIST, true, I_("RegPlanTransfAlloc"));
   addContainer( IFASTBP_PROC::MFACCOUNT_CBO, false );

   addFieldDetails( ifds::AccountNum, IFASTBP_PROC::MFACCOUNT_CBO );
   addFieldDetails( ifds::BrokerCode, IFASTBP_PROC::MFACCOUNT_CBO );
   addFieldDetails( ifds::BrokerName, IFASTBP_PROC::MFACCOUNT_CBO );
   addFieldDetails( ifds::BranchCode, IFASTBP_PROC::MFACCOUNT_CBO );
   addFieldDetails( ifds::BranchName, IFASTBP_PROC::MFACCOUNT_CBO );
   addFieldDetails( ifds::Slsrep, IFASTBP_PROC::MFACCOUNT_CBO );
   addFieldDetails( ifds::SlsrepName, IFASTBP_PROC::MFACCOUNT_CBO );
   addFieldDetails( ifds::SlsrepAltName, IFASTBP_PROC::MFACCOUNT_CBO );

       
   addFieldDetails( ifds::RegTransferStatus,         IFASTBP_PROC::REG_PLAN_TRANSFER_LIST);
   addFieldDetails( ifds::ExternalInstitution,       IFASTBP_PROC::REG_PLAN_TRANSFER_LIST);
   addFieldDetails( ifds::ExternalInstitutionName,   IFASTBP_PROC::REG_PLAN_TRANSFER_LIST);
   addFieldDetails( ifds::ExternalInstitutionAcct,   IFASTBP_PROC::REG_PLAN_TRANSFER_LIST);
   addFieldDetails( ifds::ExpectedAmt,               IFASTBP_PROC::REG_PLAN_TRANSFER_LIST);
   addFieldDetails( ifds::ActualAmount,              IFASTBP_PROC::REG_PLAN_TRANSFER_LIST);
   addFieldDetails( ifds::AmountTypeAlloc,           IFASTBP_PROC::REG_PLAN_TRANSFER_LIST);
   addFieldDetails( ifds::InitiationDate,            IFASTBP_PROC::REG_PLAN_TRANSFER_LIST);
   addFieldDetails( ifds::OutstandingDays,           IFASTBP_PROC::REG_PLAN_TRANSFER_LIST);
   addFieldDetails( ifds::ClosedDate,                IFASTBP_PROC::REG_PLAN_TRANSFER_LIST);
   addFieldDetails( ifds::Version,                   IFASTBP_PROC::REG_PLAN_TRANSFER_LIST);
   addFieldDetails( ifds::ModDate,                   IFASTBP_PROC::REG_PLAN_TRANSFER_LIST);
   addFieldDetails( ifds::ModUser,                   IFASTBP_PROC::REG_PLAN_TRANSFER_LIST);
   addFieldDetails( ifds::ProcessDate,               IFASTBP_PROC::REG_PLAN_TRANSFER_LIST);
   addFieldDetails( ifds::Username,                  IFASTBP_PROC::REG_PLAN_TRANSFER_LIST);
   addFieldDetails(REG_PLAN_TRANSFER::AreAllRecordsInactive, BF::NullContainerId, SUBCLASS_PROCESS);


   addFieldDetails( ifds::RegTransferMstrUUID,   IFASTBP_PROC::REG_PLAN_TRANSFER_ALLOC_LIST);
   addFieldDetails( ifds::RegTransferAllocUUID,  IFASTBP_PROC::REG_PLAN_TRANSFER_ALLOC_LIST);
   addFieldDetails( ifds::TotPercentage,         IFASTBP_PROC::REG_PLAN_TRANSFER_ALLOC_LIST, SUBCLASS_PROCESS);
   addFieldDetails( ifds::TotAmount,             IFASTBP_PROC::REG_PLAN_TRANSFER_ALLOC_LIST, SUBCLASS_PROCESS);
   addFieldDetails( ifds::FundNumber,            IFASTBP_PROC::REG_PLAN_TRANSFER_ALLOC_LIST);
   addFieldDetails( ifds::FundCode,              IFASTBP_PROC::REG_PLAN_TRANSFER_ALLOC_LIST);
   addFieldDetails( ifds::ClassCode,             IFASTBP_PROC::REG_PLAN_TRANSFER_ALLOC_LIST); 
   addFieldDetails( ifds::Percentage,            IFASTBP_PROC::REG_PLAN_TRANSFER_ALLOC_LIST);
   addFieldDetails( ifds::Amount,                IFASTBP_PROC::REG_PLAN_TRANSFER_ALLOC_LIST);
   addFieldDetails( ifds::Commission,            IFASTBP_PROC::REG_PLAN_TRANSFER_ALLOC_LIST);
   addFieldDetails( ifds::AllocAmount,           IFASTBP_PROC::REG_PLAN_TRANSFER_ALLOC_LIST);
   addFieldDetails( ifds::Version,               IFASTBP_PROC::REG_PLAN_TRANSFER_ALLOC_LIST);
   addFieldDetails( ifds::ModDate,               IFASTBP_PROC::REG_PLAN_TRANSFER_ALLOC_LIST);
   addFieldDetails( ifds::ModUser,               IFASTBP_PROC::REG_PLAN_TRANSFER_ALLOC_LIST);
   addFieldDetails( ifds::ProcessDate,           IFASTBP_PROC::REG_PLAN_TRANSFER_ALLOC_LIST);
   addFieldDetails( ifds::Username,              IFASTBP_PROC::REG_PLAN_TRANSFER_ALLOC_LIST);
}

//******************************************************************************
RegPlanTransferProcess::~RegPlanTransferProcess()
{
   TRACE_DESTRUCTOR( CLASSNAME );

   _rpChildGI = NULL;
}

//******************************************************************************
//              Protected Methods
//******************************************************************************

SEVERITY RegPlanTransferProcess::doInit()
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, DOINIT );
   SEVERITY sevRtn = SEVERE_ERROR;

   try
   {
      getParent()->getParameter( REG_PLAN_TRANSFER::ACCOUNT_NUMBER, _strAccountNum );

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

E_COMMANDRETURN RegPlanTransferProcess::doProcess()
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
         getParent()->setParameter( REG_PLAN_TRANSFER::SHAREHOLD_NUMBER, strShareholdNum );
         getParent()->setParameter( REG_PLAN_TRANSFER::ACCOUNT_NUMBER, _strAccountNum );
         // Folowing parameters are for DofBirth checking
         rtn = invokeCommand( this, CMD_GUI_REG_PLAN_TRANSFER, PROC_NO_TYPE, isModal(), &_rpChildGI );
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
bool RegPlanTransferProcess::doModelessSetFocus( GenericInterface *rpGICaller )
{  // This is implemented to pass set focus on to child dialog.
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, DOMODELESSSETFOCUS );
   SEVERITY sevRtn = SEVERE_ERROR;

   bool bRtn = false;
   try
   {
      getParent()->getParameter( REG_PLAN_TRANSFER::SHAREHOLD_NUMBER, strShareholdNum);
      getParent()->getParameter( REG_PLAN_TRANSFER::ACCOUNT_NUMBER, _strAccountNum );

      getParent()->setParameter( REG_PLAN_TRANSFER::SHAREHOLD_NUMBER, strShareholdNum);
      getParent()->setParameter( REG_PLAN_TRANSFER::ACCOUNT_NUMBER, _strAccountNum );

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
bool RegPlanTransferProcess::doModelessChildComplete( const Command &cmd )
{
   return( cmd.getKey() == CMD_GUI_REG_PLAN_TRANSFER );
}


//******************************************************************************

bool RegPlanTransferProcess::doRefresh( GenericInterface *rpGICaller, const I_CHAR *szOriginalCommand )
{
   TRACE_METHOD( CLASSNAME, DOREFRESH );

   setParameter( REG_PLAN_TRANSFER::ACCOUNT_NUMBER, _strAccountNum );
   setParameter( REG_PLAN_TRANSFER::SHAREHOLD_NUMBER, strShareholdNum );

   return(_rpChildGI->refresh( this, NULL ));
}

//******************************************************************************
SEVERITY RegPlanTransferProcess::doSetField( const GenericInterface *rpGICaller,
                                          const BFContainerId& idContainer,
                                          const BFFieldId& idField,
                                          const BFDataGroupId& idDataGroup,
                                          const DString& strValue,
                                          bool bFormatted )
{
   if( BF::NullContainerId == idContainer && idField == REG_PLAN_TRANSFER::ORG_KEY )
   {
      _dstrOrgKey = strValue;
   }
   else if( idField == ifds::IsDuringNASU)
   {
      DString strIsDuringNasu(strValue);
      strIsDuringNasu.strip().upperCase();
      _bIsDuringNASU = (strIsDuringNasu == I_("Y"))?true:false;
      
      setField(this, IFASTBP_PROC::REG_PLAN_TRANSFER_LIST, ifds::IsDuringNASU, strIsDuringNasu, false);
   }
   return(NO_CONDITION);
}


//******************************************************************************
void RegPlanTransferProcess::doPostOk( GenericInterface *rpGICaller, bool bSuccessFlag )
{
   //preserve param value in NASU flow
   //setParameter( REG_PLAN_TRANSFER::SHAREHOLD_NUMBER, strShareholdNum );
   setParameter( REG_PLAN_TRANSFER::ACCOUNT_NUMBER, _strAccountNum );
}

//******************************************************************************
void RegPlanTransferProcess::doGetField( const GenericInterface *rpGICaller,
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
   else if( idField == ifds::TotPercentage)
   {
      RegPlanTransferAllocList* pRegPlanTransferAllocList= NULL;
      pRegPlanTransferAllocList = (RegPlanTransferAllocList*)(const_cast<RegPlanTransferProcess*>(this))->getPtrForContainer(IFASTBP_PROC::REG_PLAN_TRANSFER_ALLOC_LIST, idDataGroup);
      if(pRegPlanTransferAllocList)
      {
         BigDecimal bdTotalAmount;
         BigDecimal bdTotalPercentage;
         pRegPlanTransferAllocList->getTotalAllocAmountPercent(idDataGroup, bdTotalAmount, bdTotalPercentage);
         
         strValueOut = bdTotalPercentage.asDString();
         BFDataField::formatValue( ifds::Percentage, strValueOut);
      //{
      //   DSTCommonFunctions::formattedField( ifds::USDollar, 0, strValueOut);
}
   }
   else if( idField == ifds::TotAmount)
   {
      RegPlanTransferAllocList* pRegPlanTransferAllocList= NULL;
      pRegPlanTransferAllocList = (RegPlanTransferAllocList*)(const_cast<RegPlanTransferProcess*>(this))->getPtrForContainer(IFASTBP_PROC::REG_PLAN_TRANSFER_ALLOC_LIST, idDataGroup);
      if(pRegPlanTransferAllocList)
      {
         BigDecimal bdTotalAmount;
         BigDecimal bdTotalPercentage;
         pRegPlanTransferAllocList->getTotalAllocAmountPercent(idDataGroup, bdTotalAmount, bdTotalPercentage);
         strValueOut = bdTotalAmount.asDString();
         DSTCWorkSession *dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
         CurrencyClass::getFormattedValue(*dstcWorkSession, strValueOut, I_(""), I_("D"));
         //DSTCommonFunctions::formattedField( ifds::TotAmount, 2, strValueOut);
      }
   }
   else if (idField == REG_PLAN_TRANSFER::AreAllRecordsInactive)
   {
      RegPlanTransferList *pRegPlanTransferList =  dynamic_cast < RegPlanTransferList*> (( const_cast < RegPlanTransferProcess *> ( this ) )->getCBOList (IFASTBP_PROC::REG_PLAN_TRANSFER_LIST, idDataGroup));
      if (pRegPlanTransferList)
      {
         strValueOut = pRegPlanTransferList->areAllRecordsInactive (idDataGroup) ? I_("Y"): I_("N");
      }
   }

}

//******************************************************************************
const BFProperties *RegPlanTransferProcess::doGetFieldAttributes( const GenericInterface *rpGICaller,
                                                               const BFContainerId& idContainer, 
                                                               const BFFieldId& idField, 
                                                               const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, I_("doGetFieldAttributes") );

   const BFProperties * pBFProp = NULL;

   return(pBFProp);
}

//******************************************************************************
void *RegPlanTransferProcess::getPtrForContainer( const BFContainerId& idContainer,
                                                  const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, I_( "getPtrForContainer" ) );

   void *ptr = NULL;
   DSTCWorkSession *dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());

   try
   {
      if (IFASTBP_PROC::REG_PLAN_TRANSFER_LIST == idContainer)
      {
         MFAccount *pMFAccount = NULL;
         RegPlanTransferProcess* pThis = const_cast<RegPlanTransferProcess*> (this);
         pMFAccount = dynamic_cast<MFAccount*>(pThis->getCBOItem (IFASTBP_PROC::MFACCOUNT_CBO, getDataGroupId()));

         RegPlanTransferList* pRegPlanTransferList= NULL;
         if(pMFAccount && 
            pMFAccount->getRegPlanTransferList( pRegPlanTransferList, getDataGroupId() ) <= WARNING )
         {
            ptr = pRegPlanTransferList;
            _pRegPlanTransferList = pRegPlanTransferList;
         }
      }
      else if(IFASTBP_PROC::REG_PLAN_TRANSFER_ALLOC_LIST == idContainer)
      {

         RegPlanTransferProcess* pThis = const_cast<RegPlanTransferProcess*> (this);
         RegPlanTransfer* pRegPlanTransfer = dynamic_cast<RegPlanTransfer*>(pThis->getCBOItem (IFASTBP_PROC::REG_PLAN_TRANSFER_LIST, idDataGroup));

         RegPlanTransferAllocList* pRegPlanTransferAllocList = NULL;
         if(pRegPlanTransfer && pRegPlanTransfer->getRegPlanTransferAllocList(idDataGroup, pRegPlanTransferAllocList) <= WARNING)
         {
            ptr = pRegPlanTransferAllocList;
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

SEVERITY  RegPlanTransferProcess::getNext()
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, I_( "getPtrForContainer" ) );

   RegPlanTransferList* pRegPlanTransferList= NULL;
   pRegPlanTransferList = (RegPlanTransferList*)getPtrForContainer(IFASTBP_PROC::REG_PLAN_TRANSFER_LIST, getDataGroupId() );
   if(pRegPlanTransferList)
      pRegPlanTransferList->getNext();

   return(GETCURRENTHIGHESTSEVERITY());

}   

//******************************************************************************
SEVERITY RegPlanTransferProcess::getHistoricalParameters( const BFContainerId& idContainer, 
                                                       HISTORICAL_VECTOR &vectorHistorical )
{
   MAKEFRAMEAUTOPROMOTE2(CND::BPBASE_CONDITION, CLASSNAME, GETHISTORICALPARAMETERS);

   if( idContainer == IFASTBP_PROC::REG_PLAN_TRANSFER_LIST)
   {   
      DString keyStringIDI( NULL_STRING ), 
         dstrCotAcctRecord;

   }

   return GETCURRENTHIGHESTSEVERITY();
}

//***********************************************************************************
bool RegPlanTransferProcess::doMoreRecordsExist( GenericInterface *rpGICaller,
                                          const BFContainerId& idSearch )
{
   RegPlanTransferList* pRegPlanTransferList= NULL;
   pRegPlanTransferList = (RegPlanTransferList*)getPtrForContainer(IFASTBP_PROC::REG_PLAN_TRANSFER_LIST, getDataGroupId() );

   return( pRegPlanTransferList ? pRegPlanTransferList->doMoreRecordsExist( ): false );
}

//******************************************************************************
bool RegPlanTransferProcess::doOk (GenericInterface* rpGICaller)
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

SEVERITY RegPlanTransferProcess::performSearch( GenericInterface *rpGI, const BFContainerId& idSearch, E_SEARCHACTION eSearchAction )
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, PERFORMSEARCH );
   SEVERITY sevRtn = SEVERE_ERROR;

   try
   {
        sevRtn = getNext();
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

SEVERITY RegPlanTransferProcess::copyData( GenericInterface *rpGI, const DString& fromKey, const DString& toKey )
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, PERFORMSEARCH );
   SEVERITY sevRtn = SEVERE_ERROR;

   RegPlanTransferList* pRegPlanTransferList= NULL;
   pRegPlanTransferList = (RegPlanTransferList*)getPtrForContainer(IFASTBP_PROC::REG_PLAN_TRANSFER_LIST, getDataGroupId() );

   if(pRegPlanTransferList)
      pRegPlanTransferList->CopyData(getDataGroupId(), fromKey, toKey);

   sevRtn = GETCURRENTHIGHESTSEVERITY();
   return sevRtn; 
}
