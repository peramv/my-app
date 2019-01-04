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
//    Copyright 1999 by DST Systems, Inc.
//
//******************************************************************************
//
// ^FILE   : BrokerAMSProcess.cpp
// ^AUTHOR : Yongmei Feng
// ^DATE   : 18/02/1999
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : BrokerAMSProcess
//    This class manages the remarks information.
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include "stdafx.h"
#include "BrokerAMSProcess.hpp"
#include "BrokerAMSProcessincludes.h"
#include <ifastcbo\BrokerAMS.hpp>
#include <ifastcbo\BrokerAMSList.hpp>
#include <ifastcbo\BrokerAMSsearch.hpp>
#include <ifastcbo\amsmstrlist.hpp>
#include <ifastcbo\BrokerList.hpp>
#include <ifastcbo\Broker.hpp>

#include "etrackheader.h"
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_AMSBROKER;
#include <bfproc\concreteprocesscreator.hpp>
static ConcreteProcessCreator< BrokerAMSProcess > processCreator( CMD_BPROC_AMSBROKER );

extern IFASTBP_LINKAGE const I_CHAR* CMD_GUI_AMSBRKLVL;
namespace
{
   // Trace literals
   const I_CHAR * const CLASSNAME = I_( "BrokerAMSProcess" );

   const I_CHAR* pBROKERCODE = I_( "BrokerCode" );
   const I_CHAR* pAMSCODE = I_( "AMSCode" );
   const I_CHAR* pAMSTYPE = I_( "AMSType" );
   const I_CHAR* const YES 		= I_( "Y" );
   const I_CHAR* const NO  		= I_( "N" );


   //const I_CHAR *pRXAMSCODE = I_( "rxAMSCode" );
}


namespace CND
{  // Conditions used
   extern CLASS_IMPORT const long BP_ERR_UNKNOWN_EXCEPTION;
   extern CLASS_IMPORT const long BP_ERR_NO_DATA_AREA;
}

namespace  BROKE_AMS
{
   const I_CHAR * const REFRESH_ALLOCTION = I_( "RefreshAllocation" );
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId AMSCode;
   extern CLASS_IMPORT const BFTextFieldId FundName;
   extern CLASS_IMPORT const BFTextFieldId BrokerAMSList;
   extern CLASS_IMPORT const BFTextFieldId AMSFundAllocHeading;
   extern CLASS_IMPORT const BFTextFieldId Name;
}
//******************************************************************************
//              Public Methods
//******************************************************************************

//CP20030319BrokerAMSProcess::BrokerAMSProcess() : 
BrokerAMSProcess::BrokerAMSProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: AbstractProcess( pGIC, pGIParent, rCommand )
, _pBrokerAMSList( NULL ),
_pamsmstrList( NULL ),
_pBrokerList( NULL ),
_pBrokerAMSsearch ( NULL ),
_pAMSFundAllocList ( NULL ),
_rpChildGI( NULL )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );

   addContainer( IFASTBP_PROC::BROKERAMS_LIST, true,BF::NullContainerId,true, I_("BrokerAMS") );
  // addContainer( IFASTBP_PROC::AMSMSTR_LIST, true );
   addContainer( IFASTBP_PROC::BROKER_LIST, true );
   addContainer( IFASTBP_PROC::BROKERAMSSEARCH, false,BF::NullContainerId,true );
   addContainer( IFASTBP_PROC::AMS_FUND_ALLOC_LIST, true, IFASTBP_PROC::BROKERAMS_LIST, true, I_("AMSFundAlloc") );

   addSubstituteList(ifds::BrokerAMSList);
   addSubstituteList(ifds::AMSFundAllocHeading );

   //addFieldDetails( ifds::BrokerCode, BROKERAMS_LIST );
   addFieldDetails( ifds::AMSCode, IFASTBP_PROC::BROKERAMS_LIST );
   addFieldDetails( ifds::AMSName,   IFASTBP_PROC::BROKERAMS_LIST );
   addFieldDetails( ifds::EffectiveDate, IFASTBP_PROC::BROKERAMS_LIST );
   addFieldDetails( ifds::ProcessDate, IFASTBP_PROC::BROKERAMS_LIST );
   addFieldDetails( ifds::Username, IFASTBP_PROC::BROKERAMS_LIST );
   addFieldDetails( ifds::ModDate, IFASTBP_PROC::BROKERAMS_LIST );
   addFieldDetails( ifds::ModUser, IFASTBP_PROC::BROKERAMS_LIST );
   addFieldDetails( ifds::BrokerAMSVer, IFASTBP_PROC::BROKERAMS_LIST );
   addFieldDetails( ifds::BrokerAMSRId, IFASTBP_PROC::BROKERAMS_LIST );
   addFieldDetails( ifds::GoodBad, IFASTBP_PROC::BROKERAMS_LIST );

   addFieldDetails( ifds::AMSCode,     IFASTBP_PROC::BROKERAMSSEARCH );
   addFieldDetails( ifds::BrokerCode,  IFASTBP_PROC::BROKERAMSSEARCH );
   addFieldDetails( ifds::BrokerName,  IFASTBP_PROC::BROKERAMSSEARCH );
   addFieldDetails( BROKE_AMS::HAS_OBJECT_UPDATE,  IFASTBP_PROC::BROKERAMSSEARCH,SUBCLASS_PROCESS );
   addFieldDetails( ifds::FundCode,    IFASTBP_PROC::AMS_FUND_ALLOC_LIST );
   addFieldDetails( ifds::ClassCode,   IFASTBP_PROC::AMS_FUND_ALLOC_LIST );
   addFieldDetails( ifds::ToFundNumber,  IFASTBP_PROC::AMS_FUND_ALLOC_LIST );
   addFieldDetails( ifds::AllocPercentage,   IFASTBP_PROC::AMS_FUND_ALLOC_LIST );
}

//******************************************************************************

BrokerAMSProcess::~BrokerAMSProcess()
{
   TRACE_DESTRUCTOR( CLASSNAME );

   _rpChildGI = NULL;
}


//******************************************************************************
//              Protected Methods
//******************************************************************************

SEVERITY BrokerAMSProcess::doInit()
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, DOINIT );
   SEVERITY sevRtn = SEVERE_ERROR;

   DString _BrokerCode,_AMSCode, _dstrAmsType;
   DString _Allresult;
   DString dstrTrack,dstrActivity;
   try
   {
      getParameter( pBROKERCODE, _BrokerCode );
      getParameter( pAMSCODE, _AMSCode );
      getParameter( pAMSTYPE, _dstrAmsType );

      getParameter( ETRACK::TRACK, dstrTrack );
      getParameter( ETRACK::ACTIVITY, dstrActivity );
      if( dstrTrack.strip() == NULL_STRING ) dstrTrack = I_("N");

      DSTCWorkSession *dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
      sevRtn = dstcWorkSession->getBrokerAMSsearch(  _pBrokerAMSsearch, getDataGroupId(), true);
  //    _pBrokerAMSsearch->setParameters(_BrokerCode, _AMSCode, getDataGroupId());

      if( WARNING >= sevRtn )
      {
         setContainer( IFASTBP_PROC::BROKERAMSSEARCH, _pBrokerAMSsearch );
      }
      else
      {
         return(GETCURRENTHIGHESTSEVERITY());
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

//******************************************************************************

E_COMMANDRETURN BrokerAMSProcess::doProcess()
{  
   MAKEFRAME2( CND::BPBASE_CONDITION, CLASSNAME, DOPROCESS );
   E_COMMANDRETURN rtn = CMD_FAILURE;
   TRACE_METHOD( CLASSNAME, DOPROCESS );

   try
   {
      if( !bfutil::isServerContext() )
      {
         rtn = invokeCommand( this, CMD_GUI_AMSBRKLVL, PROC_NO_TYPE,
                              isModal(), &_rpChildGI );    
      }
      else
      {
         rtn = CMD_MODELESS_INPROCESS;
      }
   }
   catch( ConditionException &ce )
   {
      assert( 0 );
      SETCONDITIONFROMEXCEPTION( ce );
   }
   catch( ... )
   {
      assert( 0 );
      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, DOPROCESS,
                      CND::BP_ERR_UNKNOWN_EXCEPTION );
   }
   return(rtn);
}

void BrokerAMSProcess::setCurrentListItem(
                                         const GenericInterface *rpGICaller,
                                         const BFContainerId& idList,
                                         const DString& strListItemKey
                                         )
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, SETCURRENTLISTITEM ); 
   AbstractProcess::setCurrentListItem( rpGICaller, idList, strListItemKey );
}

void BrokerAMSProcess::doPostOk( GenericInterface *rpGICaller, bool bSuccessFlag )
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, DOOK );
}

//******************************************************************************

void *BrokerAMSProcess::getPtrForContainer(const BFContainerId& idContainer, const BFDataGroupId& idDataGroup )
{
   void *ptr = NULL;
   SEVERITY sevRtn = NO_CONDITION;

   try
   {
      if( IFASTBP_PROC::BROKERAMS_LIST == idContainer )
      {
         {
            sevRtn = _pBrokerAMSsearch->getBrokerAMSList( _pBrokerAMSList, idDataGroup, false, false);

            if( sevRtn <= WARNING )
            {
               ptr = _pBrokerAMSList;          
            }
         }
      }
      else if( IFASTBP_PROC::AMS_FUND_ALLOC_LIST == idContainer )
      {
         
         DString dstrAMSCode;
         //getParameter( pRXAMSCODE, dstrAMSCode );
         getParameter( pAMSCODE, dstrAMSCode );
         DString CurrentItemKey = getCurrentListItemKey( this, IFASTBP_PROC::BROKERAMS_LIST );
         if( NULL_STRING != CurrentItemKey ) 
         {
            BrokerAMS *_pBrokerAMS = dynamic_cast< BrokerAMS * >( getCBOItem(IFASTBP_PROC::BROKERAMS_LIST, idDataGroup ) );
            AmsFundAllocList* pAmsFundAllocList = NULL;
            if( _pBrokerAMS->getAMSFundAllocList( pAmsFundAllocList,idDataGroup ) <= WARNING )
            {
               if( bfutil::isServerContext() )
               {
                  setContainer( IFASTBP_PROC::AMS_FUND_ALLOC_LIST, pAmsFundAllocList );
               }
               ptr = pAmsFundAllocList;
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
// TODO  If severity > warning, throw error returned from above
   return(ptr);
}
//*************************************************************************************************
void BrokerAMSProcess::doGetField( const GenericInterface *rpGICaller,
                            const BFContainerId& idContainer,
                            const BFFieldId& idField,
                            const BFDataGroupId& idDataGroup,
                            DString &strValueOut,
                            bool bFormatted ) const
{
	if( idField == BROKE_AMS::HAS_OBJECT_UPDATE )
	{
	   if( _pBrokerAMSList )
		{
			strValueOut = _pBrokerAMSList->isUpdatedForDataGroup( idDataGroup )?  YES:NO;		
		}
	}
}
//****************************************************************************************************

bool BrokerAMSProcess::doMoreRecordsExist( GenericInterface *rpGICaller, const BFContainerId& idSearch )
{
   return(rpGICaller == NULL || _pBrokerAMSList == NULL ? false : _pBrokerAMSList->doMoreRecordsExist());
}
//****************************************************************************************************

namespace BROKER_AMS_SEARCH_GROUP
{
   const long BROKER_AMS_SEARCH = 0x0001;
}
SEVERITY BrokerAMSProcess::performSearch( GenericInterface *rpGI, const BFContainerId& idSearch,E_SEARCHACTION eSearchAction )
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, I_( "performSearch" ) );
   SEVERITY sevRtn = SEVERE_ERROR;
   try
   {
	  if( idSearch == IFASTBP_PROC::BROKERAMS_LIST )
	  {
		  if( SEARCH_START == eSearchAction )
		  {
		    sevRtn = _pBrokerAMSsearch->validateAll( getDataGroupId(), BROKER_AMS_SEARCH_GROUP::BROKER_AMS_SEARCH  );

         if( sevRtn <= WARNING )
         {

				 sevRtn = _pBrokerAMSsearch->getBrokerAMSList( _pBrokerAMSList, getDataGroupId(), false, true);

				 if( sevRtn <= WARNING )
				 {
					setContainer( IFASTBP_PROC::BROKERAMS_LIST, _pBrokerAMSList );
				 }
			}
		  }
		  else if( SEARCH_NEXT_BLOCK == eSearchAction )
		  {
			 if( _pBrokerAMSList )
				sevRtn = _pBrokerAMSList->getMore();
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
   return(sevRtn); 
}

//********************************************************************************
bool BrokerAMSProcess::doSend(GenericInterface *rpGICaller, const I_CHAR *szMessage ) 
{
	if( szMessage == BROKE_AMS::REFRESH_ALLOCTION )
	{



	   BrokerAMS *_pBrokerAMS = dynamic_cast< BrokerAMS * >( getCBOItem(IFASTBP_PROC::BROKERAMS_LIST, getDataGroupId() ) );
      AmsFundAllocList* pAmsFundAllocList = NULL;
		// delete existing list and create a new one
      if( _pBrokerAMS->getAMSFundAllocList( pAmsFundAllocList,getDataGroupId(),true,true ) <= WARNING )
		{
			setContainer( IFASTBP_PROC::AMS_FUND_ALLOC_LIST, pAmsFundAllocList );
			return true;
		}	
	}
	return false;
}

//******************************************************************************
//******************************************************************************
//              Private Methods
//******************************************************************************

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//



