//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by International Financial, Inc.,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2013 by International Financial, Inc.
//
//******************************************************************************

#include "stdafx.h"
#include "awdhistoryprocess.hpp"
#include "awdhistoryprocessincludes.h"

#include <ifastcbo\mfaccount.hpp>
#include <ifastcbo\awdhistoryworklist.hpp>
#include <ifastcbo\awdhistorywork.hpp>
#include <ifastcbo\awdhistorysourcelist.hpp>

extern IFASTBP_LINKAGE const I_CHAR* CMD_GUI_AWDHISTORY;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_AWDHISTORY;

#include <bfproc\concreteprocesscreator.hpp>
static ConcreteProcessCreator< AWDHistoryProcess > processCreator( CMD_BPROC_AWDHISTORY );

namespace
{
   // Trace literals
   const I_CHAR * const CLASSNAME = I_( "AdminDatesProcess" );
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId AWDObjectId;
   extern CLASS_IMPORT const BFTextFieldId AWDType;
   extern CLASS_IMPORT const BFTextFieldId AWDStatus;
   extern CLASS_IMPORT const BFTextFieldId AWDImageURL;
}

namespace CND
{
   extern CLASS_IMPORT const long BP_ERR_UNKNOWN_EXCEPTION;
}

namespace MFCAN_IP_PARAM
{
//    extern const I_CHAR * const CALLER;
    extern const I_CHAR * const ACCOUNT_NUM;
}

AWDHistoryProcess::AWDHistoryProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: AbstractProcess( pGIC, pGIParent, rCommand )
, _rpChildGI(NULL)
, _accountNum(NULL_STRING)
, _pAWDHistoryWorkList(NULL)
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );

   addContainer(IFASTBP_PROC::AWDWORK_LIST, true);
   addFieldDetails(ifds::AWDObjectId, IFASTBP_PROC::AWDWORK_LIST);
   addFieldDetails(ifds::AWDType, IFASTBP_PROC::AWDWORK_LIST);
   addFieldDetails(ifds::AWDStatus, IFASTBP_PROC::AWDWORK_LIST);

   addContainer(IFASTBP_PROC::AWDSOURCE_LIST, true);
   addFieldDetails(ifds::AWDObjectId, IFASTBP_PROC::AWDSOURCE_LIST);
   addFieldDetails(ifds::AWDType, IFASTBP_PROC::AWDSOURCE_LIST);
   addFieldDetails(ifds::AWDContentId, IFASTBP_PROC::AWDSOURCE_LIST);
   addFieldDetails(ifds::AWDImageURL, IFASTBP_PROC::AWDSOURCE_LIST);

   addFieldDetails( AWDHIST_PROC::AWDImageAuth, BF::NullContainerId, SUBCLASS_PROCESS );
}

AWDHistoryProcess::~AWDHistoryProcess(void)
{
}

//******************************************************************************

SEVERITY AWDHistoryProcess::doInit()
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTBP_CONDITION, CLASSNAME, DOINIT );

   getParameter( MFCAN_IP_PARAM::ACCOUNT_NUM, _accountNum );

   try
   {
      const BFDataGroupId& idDataGroup = getDataGroupId();

      DSTCWorkSession *dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());

      MFAccount *pMFAccount;

      if( dstcWorkSession->getMFAccount( idDataGroup, _accountNum, pMFAccount ) <= WARNING &&
                NULL != pMFAccount )
      {
          _pAWDHistoryWorkList  = pMFAccount->getAWDHistoryList();
         if (  NULL != _pAWDHistoryWorkList )
         {
            setContainer( IFASTBP_PROC::AWDWORK_LIST, _pAWDHistoryWorkList );
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
      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, DOINIT,
                      CND::BP_ERR_UNKNOWN_EXCEPTION );
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************

E_COMMANDRETURN AWDHistoryProcess::doProcess()
{  
   MAKEFRAME2( CND::IFASTBP_CONDITION, CLASSNAME, DOPROCESS );
   E_COMMANDRETURN rtn = CMD_FAILURE;

   try
   {
      rtn = invokeCommand( this, CMD_GUI_AWDHISTORY, getProcessType(), isModal(), &_rpChildGI );
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

//******************************************************************************

void AWDHistoryProcess::doGetField( const GenericInterface *rpGICaller,
                                const BFContainerId& idContainer,
                                const BFFieldId& idField,
                                const BFDataGroupId& idDataGroup,
                                DString &strValueOut,
                                bool bFormatted ) const
{
   if( idField == AWDHIST_PROC::AWDImageAuth )
   {
      if ( _pAWDHistoryWorkList != NULL ) {
         strValueOut = _pAWDHistoryWorkList->getImageAuth();
      }
   }
}

//******************************************************************************

void *AWDHistoryProcess::getPtrForContainer( const BFContainerId& idContainer, const BFDataGroupId& idDataGroup )
{
   void *ptr = NULL;
   SEVERITY sevRtn = NO_CONDITION;

   try
   {
      DSTCWorkSession *dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
      if (IFASTBP_PROC::AWDWORK_LIST == idContainer)
      {

      } 
      else if (IFASTBP_PROC::AWDSOURCE_LIST == idContainer)
      {
           
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

void AWDHistoryProcess::setCurrentListItem(
                                            const GenericInterface *rpGICaller,
                                            const BFContainerId& idList,
                                            const DString& strListItemKey
                                            )
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, SETCURRENTLISTITEM ); 
   AbstractProcess::setCurrentListItem( rpGICaller, idList, strListItemKey );

   if( idList == IFASTBP_PROC::AWDWORK_LIST )
   {

      AWDHistoryWork* histWork = (AWDHistoryWork*)_pAWDHistoryWorkList->getObject(strListItemKey, BF::HOST);

      if ( NULL != histWork )
      {
         AWDHistorySourceList* sourceList = histWork->getSourceList();
         setContainer( IFASTBP_PROC::AWDSOURCE_LIST, sourceList);
      }
   }

}


