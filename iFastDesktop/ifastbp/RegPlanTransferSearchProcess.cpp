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
// ^FILE   : RegPlanTransferSearchProcess.cpp
// ^AUTHOR : Mihai Buzila
// ^DATE   : November 4, 2016
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : RegPlanTransferSearchProcess
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include "stdafx.h"
#include <ifastcbo\regplantransferlist.hpp>
#include <ifastcbo\regplantransfersearchcriteria.hpp>
#include "regplantransfersearchprocess.hpp"
#include "regplantransfersearchprocessincludes.h"
#include <ifastdataimpl\dse_dstc0472_req.hpp>
#include <ifastcbo\regplantransfer.hpp>


#include <ifastcbo\taxtyperule.hpp>
#include <ifastcbo\taxtyperulelist.hpp>
#include <ifastcbo\entitylist.hpp>
#include <ifastcbo\entity.hpp>
#include <ifastcbo\mfaccount.hpp>
#include <ifastcbo\accountentityxref.hpp>
#include <ifastcbo\accountentityxrefobject.hpp>

#include <ifastdataimpl\dse_dstc0472_vw.hpp>
#include <ifastcbo\mgmtco.hpp>
extern IFASTBP_LINKAGE const I_CHAR* CMD_GUI_REG_PLAN_TRANSFER_SEARCH;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_REG_PLAN_TRANSFER_SEARCH;
#include <bfproc\concreteprocesscreator.hpp>
static ConcreteProcessCreator< RegPlanTransferSearchProcess > processCreator( CMD_BPROC_REG_PLAN_TRANSFER_SEARCH );

namespace 
{
   // Trace literals
   const I_CHAR * const CLASSNAME   = I_( "RegPlanTransferSearchProcess" );
   const I_CHAR * const PERFORMSEARCH = I_( "PerformSearch" );
   const I_CHAR * const Y           = I_( "Y" );
   const I_CHAR * const N           = I_( "N" );
}

namespace REG_PLAN_TRANSFER_SEARCH
{
   extern IFASTBP_LINKAGE const BFFieldId Validation_OK(100);
}

namespace CND
{
   extern CLASS_IMPORT const long BP_ERR_UNKNOWN_EXCEPTION;
}


namespace ifds
{
   extern CLASS_IMPORT const BFDecimalFieldId Percentage;
   extern CLASS_IMPORT const BFDecimalFieldId Amount;
   extern CLASS_IMPORT const BFTextFieldId FundNumber;
   extern CLASS_IMPORT const BFTextFieldId RegTransferSearchCriteria;
   extern CLASS_IMPORT const BFTextFieldId RegPlanTransferSrchHeadingSet;
}

namespace UAF
{
   extern CLASS_IMPORT I_CHAR * const SEG_FUND_MULTI_CONTRACT;
}

//******************************************************************************
//              Public Methods
//******************************************************************************

//CP20030319RegPlanTransferSearchProcess::RegPlanTransferSearchProcess() : 
RegPlanTransferSearchProcess::RegPlanTransferSearchProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: AbstractProcess( pGIC, pGIParent, rCommand )
, _rpChildGI( NULL )
{
   TRACE_CONSTRUCTOR(CLASSNAME, NULL_STRING );

   DSTCWorkSession *dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
   pRegPlanTransferList = new RegPlanTransferList(*dstcWorkSession);
   pSearchCriteria= new RegPlanTransferSearchCriteria(*dstcWorkSession);
   pSearchCriteria->init(getDataGroupId());

   addContainer( IFASTBP_PROC::REG_PLAN_TRANSFER_LIST,          true, BF::NullContainerId, true, I_("RegPlanTransf"));
   addContainer( IFASTBP_PROC::REG_PLAN_TRANSFER_SRCH_CRITERIA, false, BF::NullContainerId, true, I_("SearchCriteria"));

   addFieldDetails( ifds::RegTransferSearchCriteria,     IFASTBP_PROC::REG_PLAN_TRANSFER_SRCH_CRITERIA);
   addFieldDetails( ifds::RegPlanTransferSrchHeadingSet, IFASTBP_PROC::REG_PLAN_TRANSFER_SRCH_CRITERIA);
   
   addFieldDetails( ifds::SrchAccountNum,     IFASTBP_PROC::REG_PLAN_TRANSFER_SRCH_CRITERIA);
   addFieldDetails( ifds::SrchExtInst,        IFASTBP_PROC::REG_PLAN_TRANSFER_SRCH_CRITERIA);
   addFieldDetails( ifds::SrchExtInstName,    IFASTBP_PROC::REG_PLAN_TRANSFER_SRCH_CRITERIA);
   addFieldDetails( ifds::SrchExtInstAcct,    IFASTBP_PROC::REG_PLAN_TRANSFER_SRCH_CRITERIA);
   addFieldDetails( ifds::SrchBroker,         IFASTBP_PROC::REG_PLAN_TRANSFER_SRCH_CRITERIA);
   addFieldDetails( ifds::SrchBranch,         IFASTBP_PROC::REG_PLAN_TRANSFER_SRCH_CRITERIA);
   addFieldDetails( ifds::SrchSlsrep,         IFASTBP_PROC::REG_PLAN_TRANSFER_SRCH_CRITERIA);
   addFieldDetails( ifds::BrokerName,         IFASTBP_PROC::REG_PLAN_TRANSFER_SRCH_CRITERIA);
   addFieldDetails( ifds::BranchName,         IFASTBP_PROC::REG_PLAN_TRANSFER_SRCH_CRITERIA);
   addFieldDetails( ifds::SlsrepName,         IFASTBP_PROC::REG_PLAN_TRANSFER_SRCH_CRITERIA);
   addFieldDetails( ifds::SlsrepAltName,      IFASTBP_PROC::REG_PLAN_TRANSFER_SRCH_CRITERIA);

   addFieldDetails( ifds::AccountNum,                IFASTBP_PROC::REG_PLAN_TRANSFER_LIST);
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

   addFieldDetails( REG_PLAN_TRANSFER_SEARCH::Validation_OK,   BF::NullContainerId, SUBCLASS_PROCESS);
}

//******************************************************************************
RegPlanTransferSearchProcess::~RegPlanTransferSearchProcess()
{
   TRACE_DESTRUCTOR( CLASSNAME );
   if(pRegPlanTransferList != NULL)
   {
      delete pRegPlanTransferList;
      pRegPlanTransferList = NULL;
   }

   if(pSearchCriteria != NULL)
   {
      delete pSearchCriteria;
      pSearchCriteria = NULL;
   }
   

   _rpChildGI = NULL;
}

//******************************************************************************
//              Protected Methods
//******************************************************************************

SEVERITY RegPlanTransferSearchProcess::doInit()
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, DOINIT );
   SEVERITY sevRtn = SEVERE_ERROR;

   try
   {
      setContainer( IFASTBP_PROC::REG_PLAN_TRANSFER_LIST, pRegPlanTransferList);
      setContainer( IFASTBP_PROC::REG_PLAN_TRANSFER_SRCH_CRITERIA, pSearchCriteria);
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

E_COMMANDRETURN RegPlanTransferSearchProcess::doProcess()
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
         // Folowing parameters are for DofBirth checking
         rtn = invokeCommand( this, CMD_GUI_REG_PLAN_TRANSFER_SEARCH, PROC_NO_TYPE, isModal(), &_rpChildGI );
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
const BFProperties *RegPlanTransferSearchProcess::doGetFieldAttributes( const GenericInterface *rpGICaller,
                                                               const BFContainerId& idContainer, 
                                                               const BFFieldId& idField, 
                                                               const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, I_("doGetFieldAttributes") );

   const BFProperties * pBFProp = NULL;

   return(pBFProp);
}

//******************************************************************************
void *RegPlanTransferSearchProcess::getPtrForContainer( const BFContainerId& idContainer,
                                                  const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, I_( "getPtrForContainer" ) );

   void *ptr = NULL;
   DSTCWorkSession *dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());

   try
   {
      if (IFASTBP_PROC::REG_PLAN_TRANSFER_LIST == idContainer)
      {
         return pRegPlanTransferList;
      }
      else if(IFASTBP_PROC::REG_PLAN_TRANSFER_SRCH_CRITERIA == idContainer)
      {
         return pSearchCriteria;
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

SEVERITY  RegPlanTransferSearchProcess::getNext()
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, I_( "getPtrForContainer" ) );

   RegPlanTransferList* pRegPlanTransferList= NULL;
   pRegPlanTransferList = (RegPlanTransferList*)getPtrForContainer(IFASTBP_PROC::REG_PLAN_TRANSFER_LIST, getDataGroupId() );
   if(pRegPlanTransferList)
      pRegPlanTransferList->getNext();

   return(GETCURRENTHIGHESTSEVERITY());

}   


bool RegPlanTransferSearchProcess::doSend( GenericInterface* rpGICaller,const I_CHAR* szMessage )
{
   bool  retVal = false;
   DString msg(szMessage);
   if(I_("RESET") == msg)
   {
      if(pRegPlanTransferList)
      {
         delete pRegPlanTransferList;
         DSTCWorkSession *dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
         pRegPlanTransferList = new RegPlanTransferList(*dstcWorkSession);
      }

      setContainer( IFASTBP_PROC::REG_PLAN_TRANSFER_LIST,          NULL);
      pSearchCriteria->setField(ifds::RegTransferSearchCriteria, I_(""), getDataGroupId());
      pSearchCriteria->setField(ifds::RegTransferSearchCriteria, REG_TRANSF_SEARCH_CRITERIA::ACCOUNT_NUM, getDataGroupId());
      //setContainer( IFASTBP_PROC::REG_PLAN_TRANSFER_SRCH_CRITERIA, NULL);
   }

   return retVal;
}
//***********************************************************************************
bool RegPlanTransferSearchProcess::doMoreRecordsExist( GenericInterface *rpGICaller, const BFContainerId& idSearch )
{
   RegPlanTransferList* pRegPlanTransferList= NULL;
   pRegPlanTransferList = (RegPlanTransferList*)getPtrForContainer(IFASTBP_PROC::REG_PLAN_TRANSFER_LIST, getDataGroupId() );

   return( pRegPlanTransferList ? pRegPlanTransferList->doMoreRecordsExist( ): false );
}

SEVERITY RegPlanTransferSearchProcess::performSearch( GenericInterface *rpGI, const BFContainerId& idSearch, E_SEARCHACTION eSearchAction )
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, PERFORMSEARCH );
   SEVERITY sevRtn = SEVERE_ERROR;

   try
   {
      if(eSearchAction == SEARCH_START)
      {
         if(pRegPlanTransferList)
         {
            delete pRegPlanTransferList;
         }     
         DSTCWorkSession *dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
         pRegPlanTransferList = new RegPlanTransferList(*dstcWorkSession);
         pSearchCriteria->getRegPlanTransferList(pRegPlanTransferList, getDataGroupId());
      }
      else
      {
           sevRtn = getNext();
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

bool RegPlanTransferSearchProcess::doModelessChildComplete( const Command &cmd )
{
   // End when GUI ends
   return( cmd.getKey() == CMD_GUI_REG_PLAN_TRANSFER_SEARCH);
}

void RegPlanTransferSearchProcess::doGetField(const GenericInterface *rpGICaller, const BFContainerId& idContainer, const BFFieldId& fieldID,
                                   const BFDataGroupId& idDataGroup, DString &strValueOut, bool bFormatted ) const
{
   if( fieldID == REG_PLAN_TRANSFER_SEARCH::Validation_OK )
   {
      strValueOut = N;

      if(pSearchCriteria->validateAll(idDataGroup) <= WARNING)
         strValueOut = Y;
   }
   else
      assert(0);

}
