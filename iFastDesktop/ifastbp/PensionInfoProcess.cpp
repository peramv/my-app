//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by International Financial Inc.,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2002 by International Financial.
//
//******************************************************************************
//
// ^FILE   : PensionInfoProcess.cpp
// ^AUTHOR : 
// ^DATE   : May 26, 2002
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : PensionInfoProcess
//    This class manages the remarks information.
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include "stdafx.h"
#include <ifastcbo\mfaccount.hpp>
#include "nasuprocessincludes.h"
#include <ifastcbo\pensioninfo.hpp>
#include "pensioninfoprocess.hpp"
#include "pensioninfoprocessincludes.h"

extern IFASTBP_LINKAGE const I_CHAR* CMD_GUI_PENSION_INFO;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_PENSION_INFO;

#include <bfproc\concreteprocesscreator.hpp>
static ConcreteProcessCreator< PensionInfoProcess > processCreator( CMD_BPROC_PENSION_INFO );

namespace
{
   // Trace literals
   const I_CHAR * const ACCOUNT_NUM             = I_( "AccountNum" );   
   const I_CHAR * const CLASSNAME               = I_( "PensionInfoProcess" );
   const I_CHAR * const YES                     = I_( "Y" );    
}

namespace CND
{  // Conditions used
   extern CLASS_IMPORT const long BP_ERR_UNKNOWN_EXCEPTION;
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId TaxType;
   extern CLASS_IMPORT const BFTextFieldId AcctType;
   extern CLASS_IMPORT const BFTextFieldId PensionJuris;
}

//******************************************************************************
// Constructor - Container and field details are initialized here.
//******************************************************************************

//CP20030319PensionInfoProcess::PensionInfoProcess() : 
PensionInfoProcess::PensionInfoProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: AbstractProcess( pGIC, pGIParent, rCommand )
, _rpChildGI( NULL )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );

   //readonly
   addContainer( IFASTBP_PROC::PENSION_INFO, false, BF::NullContainerId, true );   
   addContainer( IFASTBP_PROC::MFACCOUNT_CBO, false, BF::NullContainerId, false );

   // Interest Search Criteria

   addFieldDetails( ifds::AccountNum, IFASTBP_PROC::MFACCOUNT_CBO );
   addFieldDetails( ifds::TaxType, IFASTBP_PROC::MFACCOUNT_CBO );   
   addFieldDetails( ifds::AcctType, IFASTBP_PROC::MFACCOUNT_CBO );
   addFieldDetails( ifds::PensionJuris, IFASTBP_PROC::MFACCOUNT_CBO );
   addFieldDetails( ifds::ShrNum, IFASTBP_PROC::MFACCOUNT_CBO );

   addFieldDetails( ifds::PenSourceLine1, IFASTBP_PROC::PENSION_INFO );
   addFieldDetails( ifds::PenSourceLine2, IFASTBP_PROC::PENSION_INFO );
   addFieldDetails( ifds::PenSourceLine3, IFASTBP_PROC::PENSION_INFO );
   addFieldDetails( ifds::EffectiveDate, IFASTBP_PROC::PENSION_INFO );
   addFieldDetails( ifds::MinWithAge, IFASTBP_PROC::PENSION_INFO );
   addFieldDetails( ifds::UniSexPer, IFASTBP_PROC::PENSION_INFO );
   addFieldDetails( ifds::SexDistinctPer, IFASTBP_PROC::PENSION_INFO );
   addFieldDetails( PENSION_INFO::PORTION_CURRENT_MARKET_VALUE, IFASTBP_PROC::PENSION_INFO, SUBCLASS_PROCESS );

   // for AdminDates
   addFieldDetails( ifds::ModUser, IFASTBP_PROC::PENSION_INFO );
   addFieldDetails( ifds::ModDate, IFASTBP_PROC::PENSION_INFO );
   addFieldDetails( ifds::ProcessDate, IFASTBP_PROC::PENSION_INFO );
   addFieldDetails( ifds::Username, IFASTBP_PROC::PENSION_INFO );
}

//******************************************************************************
// Destructor
//******************************************************************************

PensionInfoProcess::~PensionInfoProcess()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************
// Function which get the container pointer on demand.
// @param   const BFContainerId& idContainer - Id to the container.
//          const BFDataGroupId& idDataGroup - group id.
// @returns void.
//******************************************************************************

void *PensionInfoProcess::getPtrForContainer(
                                            const BFContainerId& idContainer,
                                            const BFDataGroupId& idDataGroup
                                            )
{
   void *ptr = NULL;
   SEVERITY sevRtn = NO_CONDITION;
   try
   {
//CP20030319      switch( idContainer )
//CP20030319      {
//CP20030319         case PENSION_INFO::PENSION_INFO :
      if( IFASTBP_PROC::PENSION_INFO == idContainer )
      {
         {    

            _pMFAccount->getPensionInfo( _pPensionInfo, idDataGroup);
            if( _pPensionInfo )
               ptr = _pPensionInfo;
         }
//CP20030319            break;
//CP20030319         case PENSION_INFO::MFACCOUNT_CBO:
      }
      else if( IFASTBP_PROC::MFACCOUNT_CBO == idContainer )
      {
         {
            if( _pMFAccount )
               ptr = _pMFAccount;
         }
//CP20030319            break;
//CP20030319      }
      }
   }
   catch( ConditionException & )
   {
      throw;
   }
   catch( ... )
   {
      //Show we throw?
   }
   return(ptr);
}

//******************************************************************************
// Override for field which are defined in the Constructor as SUBCLASS_PROCESS.
// The following fields are processed.
// PORTION_CURRENT_MARKET_VALUE
// @param   const GenericInterface *rpGICaller - pointer to parent object.
//          const BFContainerId& idContainer - container id.
//          const BFFieldId& idField - field requested.
//          const BFDataGroupId& idDataGroup - group id.
//          DString &strValueOut - Field value returned.
//          bool bFormatted - boolean indicating value to be formatted or not.
// @returns void.
//******************************************************************************

void PensionInfoProcess::doGetField(
                                   const GenericInterface *rpGICaller,
                                   const BFContainerId& idContainer,
                                   const BFFieldId& idField,
                                   const BFDataGroupId& idDataGroup,
                                   DString &strValueOut,
                                   bool bFormatted
                                   ) const
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, DOGETFIELD );

   if( !_pPensionInfo )
   {
      strValueOut == NULL_STRING;
      return;
   }

   if( idContainer == IFASTBP_PROC::PENSION_INFO )
   {
      if( idField == PENSION_INFO::PORTION_CURRENT_MARKET_VALUE )
      {
         strValueOut = _pPensionInfo->getSexDistinctCurrentMarketValue( idDataGroup );
      }
      else
      {
         strValueOut == NULL_STRING;
      }
   }
}

//******************************************************************************
// Initializes pension info cbo.
// @returns SEVERITY.
//******************************************************************************

SEVERITY PensionInfoProcess::doInit()
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, DOINIT );
   SEVERITY sevRtn = SEVERE_ERROR;

   try
   {
      DString dstrRefresh;
      getParameter( PENSION_INFO::ACCOUNT_NUM, _dstrAccountNum );
      getParameter( PENSION_INFO::REFRESH, dstrRefresh );
      const BFDataGroupId& idDataGroup = getDataGroupId();
      DSTCWorkSession *pDSTCWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
      sevRtn = pDSTCWorkSession->getMFAccount( idDataGroup, _dstrAccountNum, _pMFAccount );
      if( WARNING >= sevRtn )
      {
         setContainer( IFASTBP_PROC::MFACCOUNT_CBO, _pMFAccount );
      }
      _pMFAccount->getPensionInfo( _pPensionInfo, idDataGroup);
      if( YES == dstrRefresh )
      {
         _pPensionInfo->refreshJurisdiction ( idDataGroup );
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
// Function which tells the generic interface container that the modeless child
// has been destroyed.
// @param   const Command &cmd - cmd indicating the child is destroyed.
// @returns bool - true when successful.
//******************************************************************************

bool PensionInfoProcess::doModelessChildComplete( const Command &cmd )
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, DOMODELESSCHILDCOMPLETE );

   // End when GUI ends
   return( cmd.getKey() == CMD_GUI_PENSION_INFO );
}


//******************************************************************************
// Functions which brings the Pension Info dialog to focus and top of the window 
// stack.  It also notifies Pension Info to refresh in case account information 
// has changed.
// @param   GenericInterface *rpGICaller - pointer to parent object.
// @return bool - true when successful, false otherwise.
//******************************************************************************

bool PensionInfoProcess::doModelessSetFocus( GenericInterface *rpGICaller )
{  // This is implemented to pass set focus on to child dialog.
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, DOMODELESSSETFOCUS );

   bool bRtn = false;
   try
   {
      assert( _rpChildGI && isValidModelessInterface( _rpChildGI ) );

      if( isValidModelessInterface( _rpChildGI ) )
      {  // Only if child still exists
         DString dstrNewAccountNum;
         getParameter( ACCOUNT_NUM, dstrNewAccountNum );
         if( dstrNewAccountNum != _dstrAccountNum )
         {
            // Reset the Pension info container
            setContainer ( IFASTBP_PROC::PENSION_INFO, NULL );
            doInit();
         }
         bRtn = _rpChildGI->refresh( this, NULL );
         bRtn = _rpChildGI->modelessSetFocus( rpGICaller );
      }
      return(bRtn);
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
   return(false);
}

//******************************************************************************
// This functions starts the Pension Info Dialog
// @returns E_COMMANDRETURN.
//******************************************************************************

E_COMMANDRETURN PensionInfoProcess::doProcess()
{  
   MAKEFRAME2( CND::BPBASE_CONDITION, CLASSNAME, DOPROCESS );
   E_COMMANDRETURN rtn = CMD_FAILURE;

   try
   {
      setParameter ( PENSION_INFO::ACCOUNT_NUM, _dstrAccountNum );
      setParameter( NASULIT::CREATING_ACCOUNT, _dstrCreatingAcct );
      setParameter( NASULIT::CREATING_SHAREHOLDER, _dstrCreatingShr );
      rtn = invokeCommand( this, CMD_GUI_PENSION_INFO, getProcessType(),
                           isModal(), &_rpChildGI );
   }
   catch( ConditionException &ce )
   {
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
SEVERITY PensionInfoProcess::doValidateAll( BFAbstractCBO *rpWSD, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, I_("doValidateAll") );
   if( _pPensionInfo )
   {
      if( _pPensionInfo->isUpdatedForDataGroup(idDataGroup) )//if it is updated, ok2 will call validateAll on it
         _pPensionInfo->validateAll(idDataGroup);
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
bool PensionInfoProcess::doOk(GenericInterface *rpGICaller)
{
   MFAccount *pMFAccount;
   const BFDataGroupId& idDataGroup = getDataGroupId();
   DSTCWorkSession* dstcWorkSession = dynamic_cast<DSTCWorkSession *>( getBFWorkSession() );
   dstcWorkSession->getMFAccount( idDataGroup, _dstrAccountNum, pMFAccount );
   pMFAccount->setField( ifds::PensionJurisExists, YES, idDataGroup, false );
   return(true);
}

//******************************************************************************
bool PensionInfoProcess::doCancel(GenericInterface *rpGICaller)
{
   const BFDataGroupId& idDataGroup = getDataGroupId();

   BFObjIter iter (*_pMFAccount, idDataGroup);

   iter.positionByKey (I_("aaPensionInfo")); 

   if (!iter.end ())
   {
      iter.removeObjectFromMap (true);
   }

   return(true);
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/PensionInfoProcess.cpp-arc  $
// 
//    Rev 1.9   Jan 27 2012 02:21:46   wutipong
// IN2774749 Pension Information screens become invalid when the screen is opened the second time with an account whose does not have pention information setup.
// 
//    Rev 1.8   Mar 21 2003 17:45:46   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.7   Oct 09 2002 23:53:32   PURDYECH
// PVCS Database Conversion
// 
//    Rev 1.6   Aug 29 2002 16:45:10   SMITHDAV
// Condition split.
// 
//    Rev 1.5   Aug 29 2002 12:54:36   SMITHDAV
// ClientLocale and typed field changes.
// 
//    Rev 1.4   Aug 09 2002 16:14:04   HSUCHIN
// added refresh support
// 
//    Rev 1.3   Aug 08 2002 15:09:42   HSUCHIN
// added function doOk to modify account lvl pensionjurisexists flag
// 
//    Rev 1.2   Jul 25 2002 14:27:16   YINGBAOL
// fix crash problem    PTS10009145
// 
//    Rev 1.1   Jun 21 2002 16:38:58   ZHANGCEL
// Added fields for Admin/Dates
// 
//    Rev 1.0   Jun 02 2002 17:58:38   HSUCHIN
// Initial revision.
 */
