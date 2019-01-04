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
//    Copyright 2000 by DST Systems, Inc.
//
//******************************************************************************
//
// ^FILE   : TaxExemptAuthorizationProcess.cpp
// ^AUTHOR : Celia Zhang
// ^DATE   : 14/07/2004
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : TaxExemptAuthorizationProcess
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include "stdafx.h"
#include "TaxExemptAuthorizationprocess.hpp"
#include <ifastcbo\TaxExemptAuthorizationlist.hpp>
#include "TaxExemptAuthorizationProcessIncludes.h"
#include <ifastcbo\mgmtco.hpp>
#include <ifastcbo\MFAccount.hpp>
#include <ifastcbo\dstcommonfunction.hpp>
#include <ifastbp/ifasthistoricalparameters.hpp>
extern IFASTBP_LINKAGE const I_CHAR* CMD_GUI_TAX_EXEMPT_AUTHORIZATION;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_TAX_EXEMPT_AUTHORIZATION;
#include <bfproc\concreteprocesscreator.hpp>
static ConcreteProcessCreator< TaxExemptAuthorizationProcess > processCreator( CMD_BPROC_TAX_EXEMPT_AUTHORIZATION );

namespace 
{
   // Trace literals
   const I_CHAR * const CLASSNAME = I_( "TaxExemptAuthorizationProcess" );
   const I_CHAR * const Y = I_( "Y" );
   const I_CHAR * const N = I_( "N" );
}

namespace CND
{
   extern CLASS_IMPORT const long BP_ERR_UNKNOWN_EXCEPTION;
}

namespace UAF
{
	extern CLASS_IMPORT I_CHAR * const TAX_EXEMPT_AUTHORIZATION;
}

namespace ifds
{   
	extern CLASS_IMPORT const BFTextFieldId FundNumber;
	extern CLASS_IMPORT const BFTextFieldId FundCode;
	extern CLASS_IMPORT const BFTextFieldId ClassCode;
	extern CLASS_IMPORT const BFTextFieldId FundName;
	extern CLASS_IMPORT const BFTextFieldId FundWKN;
	extern CLASS_IMPORT const BFTextFieldId FundISIN;
}

//******************************************************************************
//              Public Methods
//******************************************************************************
TaxExemptAuthorizationProcess::TaxExemptAuthorizationProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: AbstractProcess( pGIC, pGIParent, rCommand )
, _pTaxExemptAuthorizationList( NULL ),
_rpChildGI( NULL )

{
   TRACE_CONSTRUCTOR(CLASSNAME, NULL_STRING );

   addContainer( IFASTBP_PROC::TAX_EXEMPT_AUTHORIZATION_LIST, true, BF::NullContainerId, true );

   addContainer( IFASTBP_PROC::MFACCOUNT_CBO, false, BF::NullContainerId, false );

   addFieldDetails( ifds::ShrNum, IFASTBP_PROC::MFACCOUNT_CBO );
   addFieldDetails( ifds::AccountNum, IFASTBP_PROC::MFACCOUNT_CBO );
    
   addFieldDetails( ifds::EffectiveDate, IFASTBP_PROC::TAX_EXEMPT_AUTHORIZATION_LIST );
   addFieldDetails( ifds::StopDate, IFASTBP_PROC::TAX_EXEMPT_AUTHORIZATION_LIST );
   addFieldDetails( ifds::TaxExType, IFASTBP_PROC::TAX_EXEMPT_AUTHORIZATION_LIST );
   addFieldDetails( ifds::TaxJurisCode, IFASTBP_PROC::TAX_EXEMPT_AUTHORIZATION_LIST );
   addFieldDetails( ifds::ExemptAmtOrig, IFASTBP_PROC::TAX_EXEMPT_AUTHORIZATION_LIST );
   addFieldDetails( ifds::ExemptAmountUsed, IFASTBP_PROC::TAX_EXEMPT_AUTHORIZATION_LIST );
   addFieldDetails( ifds::ExemptAmtRemain, IFASTBP_PROC::TAX_EXEMPT_AUTHORIZATION_LIST, SUBCLASS_PROCESS);
   addFieldDetails( ifds::DeregAmtYrToDate, IFASTBP_PROC::TAX_EXEMPT_AUTHORIZATION_LIST, SUBCLASS_PROCESS);

   // Show Admin Dates support
   addFieldDetails(ifds::ModUser,           IFASTBP_PROC::TAX_EXEMPT_AUTHORIZATION_LIST );	
   addFieldDetails(ifds::ModDate,           IFASTBP_PROC::TAX_EXEMPT_AUTHORIZATION_LIST );	
   addFieldDetails(ifds::ProcessDate,       IFASTBP_PROC::TAX_EXEMPT_AUTHORIZATION_LIST );	
   addFieldDetails(ifds::Username,          IFASTBP_PROC::TAX_EXEMPT_AUTHORIZATION_LIST );

   addFieldDetails(ifds::EntityId,				 IFASTBP_PROC::TAX_EXEMPT_AUTHORIZATION_LIST);
   addFieldDetails(ifds::CertNumber,			 IFASTBP_PROC::TAX_EXEMPT_AUTHORIZATION_LIST);
   addFieldDetails(ifds::ExemptionScope,	     IFASTBP_PROC::TAX_EXEMPT_AUTHORIZATION_LIST);
   addFieldDetails(ifds::ExemptionReasonCode,	 IFASTBP_PROC::TAX_EXEMPT_AUTHORIZATION_LIST);	

   addFieldDetails(ifds::FundNumber,	IFASTBP_PROC::TAX_EXEMPT_AUTHORIZATION_LIST);	
   addFieldDetails(ifds::FundCode,		IFASTBP_PROC::TAX_EXEMPT_AUTHORIZATION_LIST);	
   addFieldDetails(ifds::ClassCode,		IFASTBP_PROC::TAX_EXEMPT_AUTHORIZATION_LIST);	
   addFieldDetails(ifds::FundName,		IFASTBP_PROC::TAX_EXEMPT_AUTHORIZATION_LIST);	
   addFieldDetails(ifds::FundWKN,		IFASTBP_PROC::TAX_EXEMPT_AUTHORIZATION_LIST);	
   addFieldDetails(ifds::FundISIN,		IFASTBP_PROC::TAX_EXEMPT_AUTHORIZATION_LIST);	
}

//******************************************************************************

TaxExemptAuthorizationProcess::~TaxExemptAuthorizationProcess()
{
   TRACE_DESTRUCTOR( CLASSNAME )
}

//******************************************************************************
//              Protected Methods
//******************************************************************************

SEVERITY TaxExemptAuthorizationProcess::doInit()
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, DOINIT );
   SEVERITY sevRtn = SEVERE_ERROR;

   try
   {
      getParent()->getParameter( TAXEXEMPT::ACCOUNT_NUMBER, strAccountNum );

      strAccountNum.stripAll();

      DSTCWorkSession* dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
      sevRtn = dstcWorkSession->getMFAccount(  getDataGroupId( ), strAccountNum, _pMFAccount );
      if( WARNING >= sevRtn && _pMFAccount )
      {
         setContainer( IFASTBP_PROC::MFACCOUNT_CBO, _pMFAccount );
   
			sevRtn = _pMFAccount->getTaxExemptAuthorizationList( _pTaxExemptAuthorizationList,strAccountNum, getDataGroupId( ) );
			if( WARNING >= sevRtn )
			{
				setContainer( IFASTBP_PROC::TAX_EXEMPT_AUTHORIZATION_LIST, _pTaxExemptAuthorizationList );
			}
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

E_COMMANDRETURN TaxExemptAuthorizationProcess::doProcess()
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
         getParent()->setParameter( TAXEXEMPT::ACCOUNT_NUMBER, strAccountNum );

         bool bPermTaxExempt= hasReadPermission( UAF::TAX_EXEMPT_AUTHORIZATION );
         if( bPermTaxExempt ) 
         {
            rtn = invokeCommand( this, CMD_GUI_TAX_EXEMPT_AUTHORIZATION, getProcessType(), isModal(), &_rpChildGI );
			}
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
bool TaxExemptAuthorizationProcess::doModelessSetFocus( GenericInterface *rpGICaller )
{  // This is implemented to pass set focus on to child dialog.
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, DOMODELESSSETFOCUS );
   SEVERITY sevRtn = SEVERE_ERROR;

   bool bRtn = false;
	try
   {
      assert(_rpChildGI && isValidModelessInterface(_rpChildGI));
      getParent()->getParameter( TAXEXEMPT::ACCOUNT_NUMBER, strAccountNum );
      strAccountNum.stripAll();
      if( isValidModelessInterface( _rpChildGI ) )
      {  
			// Only if child still exists            
			setContainer( IFASTBP_PROC::TAX_EXEMPT_AUTHORIZATION_LIST, NULL );
			getParent()->setParameter( TAXEXEMPT::ACCOUNT_NUMBER, strAccountNum );
            		
			bRtn = _rpChildGI->refresh( this, I_("ReloadParams" ) );
         bRtn = _rpChildGI->modelessSetFocus( rpGICaller );
      }
   }

/*
   try
   {
      getParent()->getParameter( TAXEXEMPT::ACCOUNT_NUMBER, strAccountNum );

      strAccountNum.stripAll();

      DSTCWorkSession* dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());

      sevRtn = dstcWorkSession->getMFAccount(  getDataGroupId( ), strAccountNum, _pMFAccount );
      if( WARNING >= sevRtn )
      {
         //register CBOs with base
         setContainer( IFASTBP_PROC::MFACCOUNT_CBO, _pMFAccount );
      }

      sevRtn = _pMFAccount->getTaxExemptAuthorizationList( _pTaxExemptAuthorizationList,strAccountNum, getDataGroupId( ) );
      if( WARNING >= sevRtn )
      {
         setContainer( IFASTBP_PROC::TAX_EXEMPT_AUTHORIZATION_LIST, _pTaxExemptAuthorizationList );
      }
      getParent()->setParameter( TAXEXEMPT::ACCOUNT_NUMBER, strAccountNum );

      if( !( bRtn = _rpChildGI->refresh( this, NULL ) ) )
      {
         return(bRtn);// false
      }
      bRtn = _rpChildGI->modelessSetFocus( rpGICaller );
   }*/
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

bool TaxExemptAuthorizationProcess::doModelessChildComplete( const Command &cmd )
{
   return( cmd.getKey() == CMD_GUI_TAX_EXEMPT_AUTHORIZATION );
}


//******************************************************************************

bool TaxExemptAuthorizationProcess::doRefresh( GenericInterface *rpGICaller, const I_CHAR *szOriginalCommand )
{
   TRACE_METHOD( CLASSNAME, DOREFRESH );
   setParameter( TAXEXEMPT::ACCOUNT_NUMBER, strAccountNum );
   
   return(_rpChildGI->refresh( this, NULL ));

}
	
//******************************************************************************

void TaxExemptAuthorizationProcess::doPostOk( GenericInterface *rpGICaller, bool bSuccessFlag )
{
   setParameter( TAXEXEMPT::ACCOUNT_NUMBER, strAccountNum );
}

//******************************************************************************

void TaxExemptAuthorizationProcess::doGetField( const GenericInterface *rpGICaller,
                                      const BFContainerId& idContainer,
                                      const BFFieldId& idField,
                                      const BFDataGroupId& idDataGroup,
                                      DString &strValueOut,
                                      bool bFormatted
                                    ) const
{
   
   if( idField == ifds::DeregAmtYrToDate )
   {
		strValueOut =_pTaxExemptAuthorizationList->getDeregAmtYrToDate();
     
	}
	else if ( idField == ifds::ExemptAmtRemain )
	{
		DString dstrExemptAmtOrig, dstrExemptAmountUsed;
		const_cast <TaxExemptAuthorizationProcess*> (this)->getField( rpGICaller, IFASTBP_PROC::TAX_EXEMPT_AUTHORIZATION_LIST, 
                                                             ifds::ExemptAmtOrig, dstrExemptAmtOrig, false);
		const_cast <TaxExemptAuthorizationProcess*> (this)->getField( rpGICaller, IFASTBP_PROC::TAX_EXEMPT_AUTHORIZATION_LIST, 
                                                             ifds::ExemptAmountUsed, dstrExemptAmountUsed, false);

		double dec_ExemptAmtOrig = DSTCommonFunctions::convertToDouble( dstrExemptAmtOrig );
		double dec_ExemptAmountUsed = DSTCommonFunctions::convertToDouble( dstrExemptAmountUsed );
		double dec_ExemptAmtRemain = dec_ExemptAmtOrig - dec_ExemptAmountUsed;
		strValueOut = DSTCommonFunctions::doubleToDString( ifds::ExemptAmtRemain, dec_ExemptAmtRemain );
	}
 
}
//******************************************************************************
void *TaxExemptAuthorizationProcess::getPtrForContainer( const BFContainerId& idContainer,
																		    const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2(CND::BPBASE_CONDITION, CLASSNAME, I_("getPtrForContainer"));
   
	void *ptr = NULL;
   SEVERITY sevRtn = SEVERE_ERROR;
   try
   {  
    	if( IFASTBP_PROC::MFACCOUNT_CBO == idContainer )
      {
       
			DSTCWorkSession* dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
         if( dstcWorkSession->getMFAccount( getDataGroupId(), strAccountNum, _pMFAccount ) 
             <= WARNING && _pMFAccount )
            ptr = _pMFAccount;
        
      }	
		else if ( IFASTBP_PROC::TAX_EXEMPT_AUTHORIZATION_LIST == idContainer )
		{			
			if ( _pMFAccount )
			{
				sevRtn = _pMFAccount->getTaxExemptAuthorizationList( _pTaxExemptAuthorizationList,strAccountNum, getDataGroupId( ) );
				if( WARNING >= sevRtn )
				{
					ptr = _pTaxExemptAuthorizationList;
				}
			}
		}
   }
   catch (ConditionException &)
   {
      throw;
   }
   catch (...)
   {
      assert(0);
      THROWFROMFILE2(CND::BPBASE_CONDITION, CLASSNAME, I_("getPtrForContainer"),
                      CND::BP_ERR_UNKNOWN_EXCEPTION);
   }
   return ptr;
}

//******************************************************************************
bool TaxExemptAuthorizationProcess::doMoreRecordsExist( GenericInterface *rpGICaller, const BFContainerId& idSearch )
{
	return (rpGICaller == NULL || _pTaxExemptAuthorizationList == NULL ? 
		    false : _pTaxExemptAuthorizationList->doMoreRecordsExist() );
}

//*********************************************************************************************

SEVERITY TaxExemptAuthorizationProcess::performSearch( GenericInterface *rpGI, 
                                                       const BFContainerId& idSearch, 
													   E_SEARCHACTION eSearchAction )

{  
	MAKEFRAMEAUTOPROMOTE2(CND::BPBASE_CONDITION, CLASSNAME, GETHISTORICALPARAMETERS);
	try
	{
		TaxExemptAuthorizationList* pList = (TaxExemptAuthorizationList* ) (getPtrForContainer(IFASTBP_PROC::TAX_EXEMPT_AUTHORIZATION_LIST, getDataGroupId()));      
     
		if( pList )
			pList->getMore();         
	}
	catch( ConditionException &ce )
	{
		SETCONDITIONFROMEXCEPTION( ce );
	}
	catch( ... )
	{
		assert( 0 );
		THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, I_( "performSearch" ), CND::BP_ERR_UNKNOWN_EXCEPTION );
	}

	return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
const BFProperties *TaxExemptAuthorizationProcess::doGetFieldAttributes ( const GenericInterface *rpGICaller, 
                                                                    const BFContainerId &idContainer, 
                                                                    const BFFieldId &idField, 
                                                                    const BFDataGroupId &idDataGroup
                                                                  )
{
	MAKEFRAMEAUTOPROMOTE2 ( CND::BPBASE_CONDITION, CLASSNAME, DOGETFIELDATTRIBUTES );

    const BFProperties * pBFProp = NULL;

    if( idField == ifds::ExemptAmtRemain )
	{
		BFAbstractCBO *rpPtr = getCBOItem( idContainer, idDataGroup );
		if( rpPtr )
			pBFProp = rpPtr->getFieldProperties( idField, idDataGroup );
	}

	return(pBFProp);
}

//******************************************************************************
bool TaxExemptAuthorizationProcess::doRegisterObserver ( const GenericInterface *rpGICaller,
                                          const BFContainerId &idContainer,
                                          const BFFieldId &idField,
                                          const BFDataGroupId &idDataGroup,
                                          BFObserver &rpObserver
                                        ) 
{   
   bool bRegistered = false;

   if (idContainer == IFASTBP_PROC::TAX_EXEMPT_AUTHORIZATION_LIST)
   {
      if ( idField == ifds::ExemptAmtRemain )
      {
         BFAbstractCBO *rpPtr = getCBOItem ( IFASTBP_PROC::TAX_EXEMPT_AUTHORIZATION_LIST, idDataGroup );
         if (rpPtr)
         {
            bRegistered = rpPtr->registerObserver ( idField, idDataGroup, &rpObserver, FIELD_NOTIFICATIONS, E_EVENT_ALL );
         }
      }
   }
   return bRegistered;
}


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/TaxExemptAuthorizationProcess.cpp-arc  $
// 
//    Rev 1.3   Nov 28 2005 09:39:24   jankovii
// PET1228_FN02_ EU Savings Directive Phase Two
// 
//    Rev 1.2   Mar 04 2005 16:27:04   georgeet
// PET1171 FN01 - EU Savings Directive Tax Exemption.  Modified the existing screen to include four new fields with appropriate business logic.
// 
//    Rev 1.1   Sep 20 2004 10:24:00   ZHANGCEL
// PET1082 -- New Quebec witholding tax enhancement
// 
//    Rev 1.0   Aug 06 2004 17:37:18   ZHANGCEL
// Initial revision.
 * 
 */
