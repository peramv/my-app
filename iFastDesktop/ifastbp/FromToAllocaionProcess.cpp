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
//    Copyright 2003 by DST Systems, Inc.
//
//******************************************************************************
//
// ^FILE   : FromToAllocationProcess.cpp
// ^AUTHOR : Yingbao  Li
// ^DATE   : May 28, 2003  
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : FromToAllocationProcess
//    This class manages the address book process.
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include "stdafx.h"
#include "FromToAllocationProcessIncludes.h"
#include "FromToAllocationProcess.hpp"
#include <ifastcbo\mfaccount.hpp>
#include <ifastcbo\FromFundAllocList.hpp>
#include <ifastcbo\ToFundAllocList.hpp>
#include <ifastcbo\AbstractAllocList.hpp>

#include <ifastcbo\RRIF_LIF_LRIF_InfoList.hpp>
#include <ifastcbo\RRIF_LIF_LRIF_Info.hpp>
#include <ifastcbo\mgmtco.hpp>

extern IFASTBP_LINKAGE const I_CHAR* CMD_GUI_FROM_TO_ALLOCATION;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_FROM_TO_ALLOCATION;

#include <bfproc\concreteprocesscreator.hpp>
static ConcreteProcessCreator< FromToAllocationProcess > processCreator( CMD_BPROC_FROM_TO_ALLOCATION );

namespace
{
   // Trace literals
   const I_CHAR *CLASSNAME = I_( "FromToAllocationProcess" );
}

namespace FTALLOCATION
{
   const I_CHAR * const ACCOUNT_NUM = I_( "AccountNum" );
   const I_CHAR * const CURRENT_KEY = I_( "CurrentKey" );
}

namespace CND
{  // Conditions used
   extern CLASS_IMPORT const long BP_ERR_UNKNOWN_EXCEPTION;
}

namespace AUDITTYPE
{
   extern CLASS_IMPORT I_CHAR * const FEP;
}

//******************************************************************************
//              Public Methods
//******************************************************************************

//CP20030319FromToAllocationProcess::FromToAllocationProcess() 
FromToAllocationProcess::FromToAllocationProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: AbstractProcess( pGIC, pGIParent, rCommand )
,  _rpChildGI( NULL )
{
   TRACE_CONSTRUCTOR( CLASSNAME, I_( "FromToAllocationProcess" ) );

   addContainer( IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST, true, BF::NullContainerId, 
									true, I_("RRIFInfo") );
   addContainer( IFASTBP_PROC::RRIF_FROM_ALLOC_LIST, true, 
								   IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST, true );

   addContainer( IFASTBP_PROC::RRIF_TO_ALLOC_LIST, true, 
								   IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST, true );
   addContainer( IFASTBP_PROC::MFACOUNT, false, BF::NullContainerId, false );  //readonly CBO

// from Allocation
	addFieldDetails( ifds::FundCode,					IFASTBP_PROC::RRIF_FROM_ALLOC_LIST );
	addFieldDetails( ifds::ClassCode,				IFASTBP_PROC::RRIF_FROM_ALLOC_LIST );
	addFieldDetails( ifds::AllocPercentage,		IFASTBP_PROC::RRIF_FROM_ALLOC_LIST );
	addFieldDetails( ifds::AllocAmount,				IFASTBP_PROC::RRIF_FROM_ALLOC_LIST );
	addFieldDetails( ifds::ToFundNumber,			IFASTBP_PROC::RRIF_FROM_ALLOC_LIST );
	addFieldDetails( ifds::AllocType,				IFASTBP_PROC::RRIF_FROM_ALLOC_LIST,SUBCLASS_PROCESS );
	addFieldDetails( ifds::TotAmount,				IFASTBP_PROC::RRIF_FROM_ALLOC_LIST,SUBCLASS_PROCESS );
	addFieldDetails( ifds::TotPercentage,			IFASTBP_PROC::RRIF_FROM_ALLOC_LIST,SUBCLASS_PROCESS );	
	addFieldDetails( ifds::TransType,				IFASTBP_PROC::RRIF_FROM_ALLOC_LIST,SUBCLASS_PROCESS );	



// to Allocation
	addFieldDetails( ifds::FundCode,					IFASTBP_PROC::RRIF_TO_ALLOC_LIST );
	addFieldDetails( ifds::ClassCode,				IFASTBP_PROC::RRIF_TO_ALLOC_LIST );
	addFieldDetails( ifds::AllocPercentage,		IFASTBP_PROC::RRIF_TO_ALLOC_LIST );
	addFieldDetails( ifds::AllocAmount,				IFASTBP_PROC::RRIF_TO_ALLOC_LIST );
	addFieldDetails( ifds::ToFundNumber,				IFASTBP_PROC::RRIF_TO_ALLOC_LIST );
	addFieldDetails( ifds::AllocType,				IFASTBP_PROC::RRIF_TO_ALLOC_LIST,SUBCLASS_PROCESS );
	addFieldDetails( ifds::TotAmount,				IFASTBP_PROC::RRIF_TO_ALLOC_LIST,SUBCLASS_PROCESS );
	addFieldDetails( ifds::TotPercentage,			IFASTBP_PROC::RRIF_TO_ALLOC_LIST,SUBCLASS_PROCESS );	
	addFieldDetails( ifds::TransType,				IFASTBP_PROC::RRIF_TO_ALLOC_LIST,SUBCLASS_PROCESS );	

// RRIF Information
	addFieldDetails( ifds::EffectiveFrom,			IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST );
	addFieldDetails( ifds::RRIFAmount,				IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST );
	addFieldDetails( ifds::AmountType,				IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST );
	// set  from Allocation as default
	addFieldDetails( ifds::SetAsDefault,			IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST );
   // set to allocation as default
	addFieldDetails( ifds::SetRTAsDefault,			IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST );
	addFieldDetails( ifds::RIFPayType,				IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST );
	addFieldDetails( ifds::AccountTo,				IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST );
	addFieldDetails( ifds::GoodBad,				   IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST );
	// for rrif it should be always dollor
   addFieldDetails( ifds::ShrNum,			IFASTBP_PROC::MFACOUNT  );
   addFieldDetails( ifds::AccountNum,		IFASTBP_PROC::MFACOUNT  );
   addFieldDetails( ifds::Currency,	   	IFASTBP_PROC::MFACOUNT  );


   //addFieldDetails(FEEPARAM::PRIMARY_ACCOUNT_OWNER, BF::NullContainerId, SUBCLASS_PROCESS);

}

//******************************************************************************
FromToAllocationProcess::~FromToAllocationProcess()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************
SEVERITY FromToAllocationProcess::doInit()
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, DOINIT );

   try
   {
		prePareListContainer();	
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
E_COMMANDRETURN FromToAllocationProcess::doProcess()
{  
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, DOPROCESS );
   E_COMMANDRETURN rtn = CMD_FAILURE;

   try
   {

       setParameter( FTALLOCATION::CURRENT_KEY, _currentKey );
  
		
		if( isXMLAPIContext() )
      {
         rtn = CMD_MODELESS_INPROCESS;
      }
      else
      {
         rtn = invokeCommand( this, CMD_GUI_FROM_TO_ALLOCATION, getProcessType(), isModal(), &_rpChildGI );
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
bool  FromToAllocationProcess::doModelessSetFocus( GenericInterface *rpGICaller )
{  // This is implemented to pass set focus on to child dialog.
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, DOMODELESSSETFOCUS );
   bool bRtn = false;

   try
   {
		prePareListContainer();
      if( !( bRtn = _rpChildGI->refresh( this, NULL ) ) )
      {
         return(bRtn);  // false
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
bool  FromToAllocationProcess::doModelessChildComplete( const Command &cmd )
{
   // End when GUI ends
   return( cmd.getKey() == CMD_GUI_FROM_TO_ALLOCATION );
}

//******************************************************************************
bool FromToAllocationProcess::doRefresh(
                               GenericInterface *rpGICaller,
                               const I_CHAR *szOriginalCommand
                               )
{
   setParameter( FTALLOCATION::ACCOUNT_NUM, _accountNum );
   return(_rpChildGI->refresh( this, NULL ));
}

//******************************************************************************

void FromToAllocationProcess::doGetField(
                                const GenericInterface *rpGICaller,
                                const BFContainerId& idContainer,
                                const BFFieldId& idField,
                                const BFDataGroupId& idDataGroup,
                                DString &strValueOut,
                                bool bFormatted
                                ) const
{

   if( idField == FTALLOCATION::PRIMARY_ACCOUNT_OWNER )
   {
      strValueOut = _dstrEntityName;
   }
	else if( idField == ifds::TransType )
	{
	
		if(idContainer == IFASTBP_PROC::RRIF_FROM_ALLOC_LIST || idContainer == 	IFASTBP_PROC::RRIF_TO_ALLOC_LIST ) 
		{	
			AbstractAllocList* pAllocList = dynamic_cast<AbstractAllocList*>
						  ((const_cast< FromToAllocationProcess * >( this ))->getCBOList(idContainer, idDataGroup));

			if( pAllocList )
			{
				pAllocList->getField(ifds::TransType,strValueOut,idDataGroup,bFormatted );
			}	
		}	
	}
	else if( idField == ifds::TotPercentage )
	{
		if(idContainer == IFASTBP_PROC::RRIF_FROM_ALLOC_LIST || idContainer == 	IFASTBP_PROC::RRIF_TO_ALLOC_LIST ) 
		{	
			AbstractAllocList* pAllocList = dynamic_cast<AbstractAllocList*>
						  ((const_cast< FromToAllocationProcess * >( this ))->getCBOList(idContainer, idDataGroup));

			if( pAllocList )
			{
				pAllocList->getTotalPercentage(strValueOut, idDataGroup, bFormatted);
				strValueOut.strip();
			}
		}
	}
	else if( idField == ifds::TotAmount  )
	{
		if(idContainer == IFASTBP_PROC::RRIF_FROM_ALLOC_LIST || idContainer == 	IFASTBP_PROC::RRIF_TO_ALLOC_LIST ) 
		{	
			AbstractAllocList* pAllocList = dynamic_cast<AbstractAllocList*>
						  ((const_cast< FromToAllocationProcess * >( this ))->getCBOList(idContainer, idDataGroup));

			if( pAllocList )
			{
			   pAllocList->getTotalAmount(strValueOut, idDataGroup, bFormatted);
				strValueOut.strip();			
			}
		}
	}
   else
   {
      assert( 0 );   
   }
}
//********************************************************************************
SEVERITY FromToAllocationProcess::
					doSetField( const GenericInterface* rpGICaller,
                                const BFContainerId& idContainer,
                                const BFFieldId &fieldID,
                                const BFDataGroupId& idDataGroup,
                                const DString &strValue,
                                bool bFormatted )
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, I_("doSetField") );

   if( fieldID == ifds::AllocType )
	{

		
	
	}

  return( GETCURRENTHIGHESTSEVERITY() );
}
//********************************************************************************
SEVERITY FromToAllocationProcess::prePareListContainer()
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, I_("prePareListContainer") );
   getParent()->getParameter( FTALLOCATION::ACCOUNT_NUM, _accountNum );
   getParent()->getParameter( FTALLOCATION::CURRENT_KEY, _currentKey );
   _accountNum.stripLeading( '0' ).strip();
   const BFDataGroupId& idDataGroup = getDataGroupId();
   DString _shrNum;
   if( _accountNum != NULL_STRING )
   {
      MFAccount* pMFAccount = NULL;

      DSTCWorkSession *dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
      if( dstcWorkSession->getMFAccount( idDataGroup, _accountNum, pMFAccount ) <= WARNING )
      {
			RRIF_LIF_LRIF_InfoList* pRRIF_LIF_LRIF_InfoList = NULL;

			SEVERITY sevRtn = pMFAccount->getRRIF_LIF_LRIF_InfoList( pRRIF_LIF_LRIF_InfoList, idDataGroup);
			if( WARNING >= sevRtn && pRRIF_LIF_LRIF_InfoList )
			{
				setContainer( IFASTBP_PROC::MFACOUNT, pMFAccount );
				setContainer( IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST, pRRIF_LIF_LRIF_InfoList );
            dstcWorkSession->getFirstSequenced01AccountholderEntityName( idDataGroup, 
					_accountNum, _dstrEntityName);
			}		
      }

	}
   return( GETCURRENTHIGHESTSEVERITY() );
}

//********************************************************************************
void* FromToAllocationProcess::getPtrForContainer( const BFContainerId& idContainer, const BFDataGroupId& idDataGroup )
{
   void *ptr = NULL;
   DSTCWorkSession *dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());

   try
   {
      if( IFASTBP_PROC::RRIF_FROM_ALLOC_LIST == idContainer )
      {
         

				RRIF_LIF_LRIF_Info* pInfo =  dynamic_cast<RRIF_LIF_LRIF_Info*>( 
					getCBOItem( IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST, idDataGroup ) );
				if( pInfo != NULL )
				{
					FromFundAllocList* pFromFundAllocList;
               if(pInfo->getFromFundAllocList(pFromFundAllocList, idDataGroup ) <= WARNING &&
								pFromFundAllocList )
					{
						ptr = pFromFundAllocList;
					}

				}
			
		}
		else if( IFASTBP_PROC::RRIF_TO_ALLOC_LIST == idContainer )
		{
			RRIF_LIF_LRIF_Info* pInfo =  dynamic_cast<RRIF_LIF_LRIF_Info*>( 
				getCBOItem( IFASTBP_PROC::RRIF_LIF_LRIF_INFO_LIST, idDataGroup ) );
			if( pInfo != NULL )
			{
				DString dstrPayType;
				pInfo->getField(ifds::RIFPayType,dstrPayType,idDataGroup,false );
				dstrPayType.strip().upperCase();
				if(dstrPayType == I_("T") )
				{
					ToFundAllocList*	pToFundAllocList;

					if(pInfo->getToFundAllocList(pToFundAllocList, idDataGroup ) <= WARNING && 
						pToFundAllocList )
					{
							ptr = pToFundAllocList;
					}	
				}		
			}				
		}
		else {
			assert(0);
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

//****************************************************************************************
SEVERITY FromToAllocationProcess::doValidateAll( BFAbstractCBO *rpWSD, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, I_("doValidateAll") );

	FundAllocList* pFundAllocList= NULL;

	pFundAllocList = (FundAllocList* )( getPtrForContainer( IFASTBP_PROC::RRIF_FROM_ALLOC_LIST, idDataGroup ) );
	if( pFundAllocList )
	{
		pFundAllocList->validateAll( idDataGroup );
		pFundAllocList= NULL;
	}
	pFundAllocList = (FundAllocList* )( getPtrForContainer( IFASTBP_PROC::RRIF_TO_ALLOC_LIST, idDataGroup ) );
	if( pFundAllocList )
	{
		pFundAllocList->validateAll( idDataGroup );
		pFundAllocList= NULL;
	}
   return( GETCURRENTHIGHESTSEVERITY() );

}
//******************************************************************************
//              Private Methods
//******************************************************************************

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/FromToAllocaionProcess.cpp-arc  $
// 
//    Rev 1.1   Jun 24 2003 09:46:44   YINGBAOL
// implement DoValidateAll
// 
//    Rev 1.0   Jun 09 2003 11:16:46   YINGBAOL
// Initial revision.
// 

 *
 */
