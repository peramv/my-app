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
//    Copyright 2002 by International Financial Data Services
//
//******************************************************************************
//
// ^FILE   : AmsLmtOverrideProcess.cpp
// ^AUTHOR : Yingbao Li
// ^DATE   : Nov 5,2002
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : AmsLmtOverrideProcess
//    
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include "stdafx.h"
#include "AmsLmtOverrideProcess.hpp"
#include "AmsLmtOverrideProcessincludes.h"
#include <ifastcbo\AmsLmtOverridelist.hpp>
#include <ifastcbo\AmsLmtOverride.hpp>
#include "mfcaninterprocparam.hpp"
#include "confirmationprocessincludes.h"
#include <ifastcbo\AmsMstrlist.hpp>
#include <ifastcbo\AmsMstrInfo.hpp>
#include "AmsmstProcessincludes.h"

#include <ifastdataimpl\dse_dstcglob_vw.hpp>

extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_AMS_LMT_OVERRIDE;
extern IFASTBP_LINKAGE const I_CHAR* CMD_GUI_AMS_LMT_OVERRIDE;

#include <bfproc\concreteprocesscreator.hpp>
static ConcreteProcessCreator< AmsLmtOverrideProcess > processCreator( CMD_BPROC_AMS_LMT_OVERRIDE );

namespace CND
{
   extern CLASS_IMPORT const long BP_ERR_UNKNOWN_EXCEPTION;
}


namespace 
{
   const I_CHAR * const CLASSNAME      = I_( "AmsLmtOverrideProcess" );
   const I_CHAR * const YES            = I_("Y");
   const I_CHAR * const NO             = I_("N");
}

namespace AMS_LMT_Para
{
	const I_CHAR * const AMS_CODE			= I_("AMSCode");
//	const I_CHAR * const AMS_TYPE			= I_("AMSType");
//	const I_CHAR * const AMS_EFFECTIVE_DATE	= I_("EffectiveDate");
	const I_CHAR * const AMS_REC_ID			= I_("AMSRecId");
    const I_CHAR * const FROM_SCR			= I_( "FromScr" );

}

namespace AUDITTYPE
{
   extern CLASS_IMPORT I_CHAR * const AMSRU;
}

//******************************************************************************
//              Public Methods
//******************************************************************************
AmsLmtOverrideProcess::AmsLmtOverrideProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: AbstractProcess( pGIC, pGIParent, rCommand )
, _rpChildGI( NULL )
,_pAmsLmtOverrideList(NULL)
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );

   addContainer( IFASTBP_PROC::AMS_LMT_OVERRIDE_LIST,        true, BF::NullContainerId,        true, I_("AmsLmtOverrideList") );

   addSubstituteList(ifds::AmsLmtOverrideHeading);

   //AMS_LMT_OVERRIDE_LIST
   addFieldDetails( ifds::RuleType,          IFASTBP_PROC::AMS_LMT_OVERRIDE_LIST );
   addFieldDetails( ifds::OverrideDecimal,   IFASTBP_PROC::AMS_LMT_OVERRIDE_LIST );
   addFieldDetails( ifds::OverrideLogical,   IFASTBP_PROC::AMS_LMT_OVERRIDE_LIST );
   addFieldDetails( ifds::OverrideFundLevel, IFASTBP_PROC::AMS_LMT_OVERRIDE_LIST );
   addFieldDetails( ifds::AMSTaxJurisCode,      IFASTBP_PROC::AMS_LMT_OVERRIDE_LIST );
   addFieldDetails( ifds::AMSResProvCode,       IFASTBP_PROC::AMS_LMT_OVERRIDE_LIST );
   addFieldDetails( ifds::AMSTaxType,           IFASTBP_PROC::AMS_LMT_OVERRIDE_LIST );
   addFieldDetails( ifds::AMSAcctType,          IFASTBP_PROC::AMS_LMT_OVERRIDE_LIST );
   addFieldDetails( ifds::AMSAcctDesignation,   IFASTBP_PROC::AMS_LMT_OVERRIDE_LIST );
   addFieldDetails( ifds::OnLineEWI,         IFASTBP_PROC::AMS_LMT_OVERRIDE_LIST );
   addFieldDetails( ifds::CycleEWI,          IFASTBP_PROC::AMS_LMT_OVERRIDE_LIST );
   addFieldDetails( ifds::ESGEWI,            IFASTBP_PROC::AMS_LMT_OVERRIDE_LIST );
   addFieldDetails( ifds::AMSRuleId,         IFASTBP_PROC::AMS_LMT_OVERRIDE_LIST );

   addFieldDetails( ifds::ModUser,			 IFASTBP_PROC::AMS_LMT_OVERRIDE_LIST );
   addFieldDetails( ifds::ProcessDate,       IFASTBP_PROC::AMS_LMT_OVERRIDE_LIST );
   addFieldDetails( ifds::ModDate,			 IFASTBP_PROC::AMS_LMT_OVERRIDE_LIST );
   addFieldDetails( ifds::Username,			 IFASTBP_PROC::AMS_LMT_OVERRIDE_LIST );

   addFieldDetails( ifds::AMSType,			BF::NullContainerId, SUBCLASS_PROCESS );
   addFieldDetails( ifds::AMSCode,			BF::NullContainerId, SUBCLASS_PROCESS );
   addFieldDetails( ifds::EffectiveDate,    BF::NullContainerId, SUBCLASS_PROCESS );


}

//******************************************************************************
AmsLmtOverrideProcess::~AmsLmtOverrideProcess()
{
   TRACE_DESTRUCTOR( CLASSNAME );

}

//******************************************************************************
SEVERITY AmsLmtOverrideProcess::doInit()
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, I_("doInit") );
   SEVERITY sevRtn=NO_CONDITION;

   getParameter( AMS_Para::EFFECTIVE_DATE, _dstrEffectiveDate );
   getParameter( AMS_Para::AMS_CODE, _dstrAmsCode );
   getParameter( AMS_Para::AMS_TYPE, _dstrAmsType );
   getParameter( AMS_LMT_Para::AMS_REC_ID, _dstrAmsRecId );
   getParameter( AMS_LMT_Para::AMS_CODE, _dstrAmsCodeSearch );
   getParameter( AMS_LMT_Para::FROM_SCR,  _dstrFromScr );
 
   _dstrEffectiveDate.strip();
   _dstrAmsCode.strip().upperCase();
   _dstrAmsCodeSearch.strip().upperCase();
   
   DString tmp;
   DSTCommonFunctions::UnformatDate( _dstrEffectiveDate, tmp );
   _dstrEffectiveDate = tmp;


   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
//              Protected Methods
//******************************************************************************
bool AmsLmtOverrideProcess::doModelessChildComplete( const Command &cmd )
{
   // End when GUI ends
   return( cmd.getKey() == CMD_BPROC_AMS_LMT_OVERRIDE );
}

//******************************************************************************
bool AmsLmtOverrideProcess::doModelessSetFocus( GenericInterface *rpGICaller )
{  // This is implemented to pass set focus on to child dialog.

   bool bRtn = false;
   try
   {
      assert( _rpChildGI && isValidModelessInterface( _rpChildGI ) );
   }
   catch( ConditionException &ce )
   {
      MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, I_("doModelessSetFocus") );
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
E_COMMANDRETURN AmsLmtOverrideProcess::doProcess()
{  
   MAKEFRAME2( CND::BPBASE_CONDITION, CLASSNAME, DOPROCESS );
   E_COMMANDRETURN rtn = CMD_FAILURE;

   try
   {
      if( !bfutil::isServerContext() )
      {
		 setParameter( AMS_Para::AMS_CODE, _dstrAmsCode );
         setParameter( AMS_Para::AMS_TYPE, _dstrAmsType );
		 setParameter( AMS_Para::EFFECTIVE_DATE, _dstrEffectiveDate );
		 setParameter( AMS_LMT_Para::AMS_REC_ID, _dstrAmsRecId );
		 setParameter( AMS_LMT_Para::AMS_CODE, _dstrAmsCodeSearch );
         setParameter( AMS_LMT_Para::FROM_SCR,  _dstrFromScr );

         rtn = invokeCommand( this, CMD_GUI_AMS_LMT_OVERRIDE, getProcessType(), isModal(),
                              &_rpChildGI );
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

//******************************************************************************
void* AmsLmtOverrideProcess::getPtrForContainer( const BFContainerId& idContainer, const BFDataGroupId& idDataGroup )
{
   void *ptr = NULL;
   SEVERITY sevRtn = NO_CONDITION;
   DSTCWorkSession* dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
   AMSMstrList * pAmsMstrList = NULL;
   AmsMstrInfo * pAmsMstrInfo = NULL;   
	DString dstrAmsCode, dstrAmsType, dstrEffectiveDate;
   try
   {

	  if( IFASTBP_PROC::AMS_LMT_OVERRIDE_LIST == idContainer )
      {
        if( bfutil::isServerContext() || !_pAmsLmtOverrideList )
        {

           DSTCWorkSession* dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
           sevRtn = dstcWorkSession->getAMSMstrList( pAmsMstrList,_dstrAmsType, _dstrAmsCode,_dstrEffectiveDate, idDataGroup,true,false );
           if( sevRtn <= WARNING && pAmsMstrList )
           {

			  BFObjIter iter( *pAmsMstrList, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED );
			  if (iter.positionByKey( _dstrAmsRecId ))
			  {
				  pAmsMstrInfo = dynamic_cast<AmsMstrInfo*>(iter.getObject());
				  if( pAmsMstrInfo )
				  {
					 if( pAmsMstrInfo->getAmsLmtOverrideList(_pAmsLmtOverrideList, idDataGroup,true, false, false) <= WARNING )
					 {
						 setContainer( IFASTBP_PROC::AMS_LMT_OVERRIDE_LIST, _pAmsLmtOverrideList );
						 ptr = _pAmsLmtOverrideList;
					 }
				  }
			  }
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

bool AmsLmtOverrideProcess::doMoreRecordsExist( GenericInterface *rpGICaller, const BFContainerId& idSearch )
{
   return(rpGICaller == NULL || _pAmsLmtOverrideList == NULL ? false : _pAmsLmtOverrideList->doMoreRecordsExist());
}

//******************************************************************************
SEVERITY AmsLmtOverrideProcess::performSearch(GenericInterface *rpGI, 
   const BFContainerId& idSearch, E_SEARCHACTION eSearchAction)
{
	   MAKEFRAMEAUTOPROMOTE2(CND::BPBASE_CONDITION, CLASSNAME, I_("PerformSearch"));
	   SEVERITY sevRtn = SEVERE_ERROR;

	   try
	   {
		  if (_pAmsLmtOverrideList != NULL)
		  {
			 sevRtn = _pAmsLmtOverrideList->getMore();
		  }
	   }
	   catch (ConditionException &ce)
	   {
		  SETCONDITIONFROMEXCEPTION(ce);
	   }
	   catch (...)
	   {
		  assert(0);
		  THROWFROMFILE2(CND::BPBASE_CONDITION, CLASSNAME, 
			 I_("PerformSearch"), CND::BP_ERR_UNKNOWN_EXCEPTION);
	   }
	   return sevRtn;
}

//******************************************************************************
SEVERITY AmsLmtOverrideProcess::doValidateAll( BFAbstractCBO *rpWSD, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, I_("doValidateAll") );  
   SEVERITY sev = NO_CONDITION; 
   if( _pAmsLmtOverrideList )
      sev = _pAmsLmtOverrideList->validateAll( idDataGroup );
   return(sev);
}

//******************************************************************************

SEVERITY AmsLmtOverrideProcess::getHistoricalParameters( const BFContainerId& idContainer, HISTORICAL_VECTOR &vectorHistorical )
{
   MAKEFRAMEAUTOPROMOTE2(CND::BPBASE_CONDITION, CLASSNAME, GETHISTORICALPARAMETERS);

   DString keyStringIDI( NULL_STRING ), dstrRecord;
   getField( this, IFASTBP_PROC::AMS_LMT_OVERRIDE_LIST, ifds::AMSRuleId, dstrRecord, false );
   HistoricalElement historicalElement( dstrRecord, AUDITTYPE::AMSRU, keyStringIDI );
   vectorHistorical.push_back( historicalElement );

   return GETCURRENTHIGHESTSEVERITY();
}

//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastbp/AmsLmtOverrideProcess.cpp-arc  $
// 
//    Rev 1.10   Mar 10 2004 12:19:30   HERNANDO
// PET965 FN11 - Changed getHistoricalParameters.
// 
//    Rev 1.9   Aug 18 2003 16:08:16   HERNANDO
// Added keys to getHistoricalParameters.
// 
//    Rev 1.8   Aug 18 2003 11:46:50   linmay
// modified doInit()
// 
//    Rev 1.7   Aug 13 2003 16:21:42   linmay
// modified doInit(), doProcess()
// 
//    Rev 1.6   Aug 13 2003 12:09:58   linmay
// added doValidateAll()
// 
//    Rev 1.5   Aug 13 2003 10:23:36   linmay
// change TaxType to AMSTaxType,..
// 
//    Rev 1.4   Aug 11 2003 09:42:32   linmay
// fix bug
// 
//    Rev 1.3   Aug 05 2003 11:28:46   linmay
// fix bug
// 
//    Rev 1.2   Jul 31 2003 14:57:56   linmay
// changed to amsru for audit type
// 
//    Rev 1.0   Jul 23 2003 09:24:40   linmay
// Initial Revision
// 
