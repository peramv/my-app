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
// ^FILE   : AsPensionPlanProcess.cpp
// ^AUTHOR : Karen Jan
// ^DATE   : July 24, 2001
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : AsPensionPlanProcess
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include "stdafx.h"
#include <ifastcbo\aspensionplan.hpp>
#include "aspensionplanprocess.hpp"
#include "aspensionplanprocessincludes.h"
#include <ifastcbo\mfaccount.hpp>
extern IFASTBP_LINKAGE const I_CHAR* CMD_GUI_AS_PENSION_PLAN;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_AS_PENSION_PLAN;
#include <bfproc\concreteprocesscreator.hpp>
static ConcreteProcessCreator< AsPensionPlanProcess > processCreator( CMD_BPROC_AS_PENSION_PLAN );

namespace
{
   // Trace literals
   const I_CHAR* CLASSNAME = I_( "AsPensionPlanProcess" );
}

namespace ASPENSIONPLANLIT
{
   const I_CHAR*  const ACCOUNT_NUM     = I_( "AccountNum" );
   const I_CHAR*  const SHAREHOLDER_NUM = I_( "ShareholdNum" );
   const I_CHAR*  const ACCOUNT_TYPE    = I_( "AccountType" );
   const I_CHAR*  const TAX_TYPE        = I_( "TaxType" );
}

namespace CND
{
   extern CLASS_IMPORT const long BP_ERR_UNKNOWN_EXCEPTION;
   extern CLASS_IMPORT const long BP_ERR_INVALID_METHOD_CALL;
}


//******************************************************************************
//              Public Methods
//******************************************************************************
AsPensionPlanProcess::AsPensionPlanProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: AbstractProcess( pGIC, pGIParent, rCommand )
, _rpChildGI(NULL)  

{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );

   addContainer( IFASTBP_PROC::ASPENSIONPLAN, false, BF::NullContainerId, true, I_("AsPensionPlan") );

   addSubstituteList( ifds::ASStatus );

   //As Pension Plan fields 
   addFieldDetails( ifds::StartDate,  IFASTBP_PROC::ASPENSIONPLAN );
   addFieldDetails( ifds::EndDate,    IFASTBP_PROC::ASPENSIONPLAN );
   addFieldDetails( ifds::ASStatus,   IFASTBP_PROC::ASPENSIONPLAN );
   addFieldDetails( ifds::MaturDate,  IFASTBP_PROC::ASPENSIONPLAN );
   addFieldDetails( ifds::AccountNum, BF::NullContainerId, SUBCLASS_PROCESS );
   addFieldDetails( ifds::ShrNum,     BF::NullContainerId, SUBCLASS_PROCESS );
   addFieldDetails( ifds::EntityName, BF::NullContainerId, SUBCLASS_PROCESS );
}

//******************************************************************************
AsPensionPlanProcess::~AsPensionPlanProcess()
{
   TRACE_DESTRUCTOR( CLASSNAME );

   _rpChildGI = NULL;
}

//******************************************************************************
//              Protected Methods
//******************************************************************************

//******************************************************************************
SEVERITY AsPensionPlanProcess::doInit()
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, DOINIT );

   try
   {
      getParameter( ASPENSIONPLANLIT::SHAREHOLDER_NUM, _shrNum);
      getParameter( ASPENSIONPLANLIT::ACCOUNT_NUM, _accountNum );
      _accountNum.strip().stripLeading( '0' );
      _shrNum.strip().stripLeading( '0' );
      _pAsPensionPlan = NULL;
      DSTCWorkSession* dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
      if( dstcWorkSession->getMFAccount(getDataGroupId( ), _accountNum, _pMFAccount ) <= WARNING )
      {
         if( _pMFAccount->getAsPensionPlan(_pAsPensionPlan, getDataGroupId( )) <= WARNING && _pAsPensionPlan )
         {
            setContainer( IFASTBP_PROC::ASPENSIONPLAN, _pAsPensionPlan );
         }

      }
      else
      {
         return( NO_CONDITION );
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
E_COMMANDRETURN AsPensionPlanProcess::doProcess()
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
         DSTCWorkSession* dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
         SEVERITY sevRtn = dstcWorkSession->getMFAccount(  getDataGroupId( ), _accountNum, _pMFAccount );

         if( sevRtn <= WARNING )
         {
            DString dstrAcctType, dstrTaxType;

            _pMFAccount->getField( ifds::AcctType, dstrAcctType, getDataGroupId());
            _pMFAccount->getField( ifds::TaxType, dstrTaxType, getDataGroupId());

            if( dstrAcctType == I_( "0" ) && dstrTaxType == I_( "P" ) )
            {
               rtn = invokeCommand( this, CMD_GUI_AS_PENSION_PLAN, getProcessType(), isModal(),
                                    &_rpChildGI );
            }
         }
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
bool AsPensionPlanProcess::doModelessChildComplete( const Command &cmd )
{
   // End when GUI ends
   return(cmd.getKey() == CMD_GUI_AS_PENSION_PLAN);
}

//******************************************************************************
bool AsPensionPlanProcess::doModelessSetFocus( GenericInterface *rpGICaller )
{  // This is implemented to pass set focus on to child dialog.
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, DOMODELESSSETFOCUS );
   SEVERITY sevRtn = SEVERE_ERROR;

   bool bRtn = false;

   if( rpGICaller->getCommand().getKey() == CMD_GUI_AS_PENSION_PLAN )
   {
      //register CBOs with base
      setContainer( IFASTBP_PROC::ASPENSIONPLAN, _pAsPensionPlan );
   }

   if( !( bRtn = _rpChildGI->refresh( this, NULL ) ) )
   {
      return(bRtn);// false
   }

   bRtn = _rpChildGI->modelessSetFocus( rpGICaller );

   return(bRtn);
}
//******************************************************************************

void AsPensionPlanProcess::doGetField(
                                     const GenericInterface *rpGICaller,
                                     const BFContainerId& idContainer,
                                     const BFFieldId& idField,
                                     const BFDataGroupId& idDataGroup, 
                                     DString &strValueOut,
                                     bool bFormatted
                                     ) const
{  
//CP20030402   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, I_("doGetField") );
   DSTCWorkSession* dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());

   if( idField == ifds::AccountNum )
   {
      strValueOut = _accountNum;
   }
   else if( idField == ifds::ShrNum )
   {
      if( _pMFAccount )
         _pMFAccount->getField(ifds::ShrNum, strValueOut, getDataGroupId( ), bFormatted);
      strValueOut.strip().stripLeading('0');
   }
   else if( idField == ifds::EntityName )
   {
      DString accNum(_accountNum);
      dstcWorkSession->getFirstSequenced01AccountholderEntityName( getDataGroupId(), accNum, strValueOut );
      strValueOut.strip();
   }
   else
   {
      assert( 0 );   
      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, GETFIELD, CND::BP_ERR_INVALID_METHOD_CALL );
   }
}
//******************************************************************************
SEVERITY AsPensionPlanProcess::doSetField(
                                         const GenericInterface *rpGICaller, 
                                         const BFContainerId& idContainer, 
                                         const BFFieldId& idField,
                                         const BFDataGroupId& idDataGroup, 
                                         const DString& strValue, 
                                         bool bFormatted
                                         ) 
{  
//CP20030402   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, I_("doSetField") );
   assert( 0 );   
   THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, GETFIELD, CND::BP_ERR_INVALID_METHOD_CALL );
//CP20030402
//CP20030402   return(GETCURRENTHIGHESTSEVERITY());
}
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/AsPensionPlanProcess.cpp-arc  $
// 
//    Rev 1.10   Apr 02 2003 12:19:40   PURDYECH
// Code cleanup
// 
//    Rev 1.9   Mar 21 2003 17:36:08   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.8   Oct 09 2002 23:53:02   PURDYECH
// PVCS Database Conversion
// 
//    Rev 1.7   Aug 29 2002 16:42:34   SMITHDAV
// Condition split.
// 
//    Rev 1.6   Aug 29 2002 12:54:12   SMITHDAV
// ClientLocale and typed field changes.
// 
//    Rev 1.5   Jun 03 2002 16:42:14   FENGYONG
// Add names for API
// 
//    Rev 1.4   22 May 2002 18:23:50   PURDYECH
// BFData Implementation
// 
//    Rev 1.3   27 Mar 2002 19:54:34   PURDYECH
// Process/WindowFactory overhaul
// 
//    Rev 1.2   04 Jan 2002 17:24:52   KOVACSRO
// Added AccountNum, ShrNum and EntityName fields as SUBCLASS_PROCESS
// 
//    Rev 1.1   Dec 27 2001 10:46:02   YINGBAOL
// check CBO pointer
// 
//    Rev 1.0   Aug 23 2001 13:09:18   JANKAREN
// Initial revision.
 * 
 *
 */
