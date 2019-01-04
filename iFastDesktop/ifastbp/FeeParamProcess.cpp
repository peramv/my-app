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
// ^FILE   : FeeParamProcess.cpp
// ^AUTHOR : Yingbao  Li
// ^DATE   : January 25, 2002  
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : FeeParamProcess
//    This class manages the address book process.
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include "stdafx.h"
#include "feeparamprocessinclude.h"
#include "feeparamprocess.hpp"
#include <ifastcbo\mfaccount.hpp>
#include <ifastcbo\feeparamlist.hpp>
#include <ifastcbo\feeparam.hpp>
#include <ifastcbo\feescalelist.hpp>
#include <ifastcbo\feescale.hpp>
#include <ifastcbo\FundCommGroupList.hpp>
#include <ifastcbo\mgmtco.hpp>

extern IFASTBP_LINKAGE const I_CHAR* CMD_GUI_FEE_PARAMETER;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_FEE_PARAMETER;

#include <bfproc\concreteprocesscreator.hpp>
static ConcreteProcessCreator< FeeParamProcess > processCreator( CMD_BPROC_FEE_PARAMETER );

namespace
{
   // Trace literals
   const I_CHAR *CLASSNAME             = I_( "FeeParamProcess" );
   const I_CHAR * const FLAT           = I_( "0" );
   const I_CHAR * const PERCENT        = I_( "1" );
   const I_CHAR * const SCALE          = I_( "2" );
   const I_CHAR * const TIER           = I_( "3" );

}

namespace FEEPARAM
{
   const I_CHAR * const ACCOUNT_NUM = I_( "AccountNum" );
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

//CP20030319FeeParamProcess::FeeParamProcess() 
FeeParamProcess::FeeParamProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: AbstractProcess( pGIC, pGIParent, rCommand )
,  _rpChildGI( NULL )
{
   TRACE_CONSTRUCTOR( CLASSNAME, I_( "FeeParamProcess" ) );

   addContainer( IFASTBP_PROC::FEE_PARAM_LIST, true, BF::NullContainerId, true, I_("FeeParam") );
   addContainer( IFASTBP_PROC::FEE_SCALE_LIST, true, IFASTBP_PROC::FEE_PARAM_LIST, true );

   addContainer( IFASTBP_PROC::MFACOUNT, false, BF::NullContainerId, false );  //readonly CBO

   addFieldDetails( ifds::AcctFeeParamId,   IFASTBP_PROC::FEE_PARAM_LIST );
   addFieldDetails( ifds::FeeParamRid,      IFASTBP_PROC::FEE_PARAM_LIST );
   addFieldDetails( ifds::FundCode,     IFASTBP_PROC::FEE_PARAM_LIST );
   addFieldDetails( ifds::ClassCode,    IFASTBP_PROC::FEE_PARAM_LIST );
   addFieldDetails( ifds::FundFromCode,   IFASTBP_PROC::FEE_PARAM_LIST );
   addFieldDetails( ifds::ClassFromCode,  IFASTBP_PROC::FEE_PARAM_LIST );
   addFieldDetails( ifds::FeeCode,      IFASTBP_PROC::FEE_PARAM_LIST );
   addFieldDetails( ifds::ParamFeeType,   IFASTBP_PROC::FEE_PARAM_LIST );
   addFieldDetails( ifds::Rate,       IFASTBP_PROC::FEE_PARAM_LIST );
   addFieldDetails( ifds::MinFee,     IFASTBP_PROC::FEE_PARAM_LIST );
   addFieldDetails( ifds::MaxFee,     IFASTBP_PROC::FEE_PARAM_LIST );
   addFieldDetails( ifds::EffectiveDate,  IFASTBP_PROC::FEE_PARAM_LIST );
   addFieldDetails( ifds::StopDate,     IFASTBP_PROC::FEE_PARAM_LIST );
   addFieldDetails( ifds::FreqMinMaxApp,  IFASTBP_PROC::FEE_PARAM_LIST );
   addFieldDetails( ifds::ChrgOnPrtlRed,  IFASTBP_PROC::FEE_PARAM_LIST );
   addFieldDetails( ifds::ChrgOnFullRed,  IFASTBP_PROC::FEE_PARAM_LIST );
   addFieldDetails( ifds::Currency,     IFASTBP_PROC::FEE_PARAM_LIST );
   addFieldDetails( ifds::FundNumber,   IFASTBP_PROC::FEE_PARAM_LIST );
   addFieldDetails( ifds::Status,     IFASTBP_PROC::FEE_PARAM_LIST );
   addFieldDetails( ifds::ProcessDate,    IFASTBP_PROC::FEE_PARAM_LIST );
   addFieldDetails( ifds::ModDate,      IFASTBP_PROC::FEE_PARAM_LIST );
   addFieldDetails( ifds::Username,     IFASTBP_PROC::FEE_PARAM_LIST );
   addFieldDetails( ifds::ModUser,      IFASTBP_PROC::FEE_PARAM_LIST );
   addFieldDetails( ifds::CommGroup,    IFASTBP_PROC::FEE_PARAM_LIST );
   addFieldDetails( ifds::BrokerCode,   IFASTBP_PROC::FEE_PARAM_LIST );
   addFieldDetails( ifds::ModPerm,      IFASTBP_PROC::FEE_PARAM_LIST );
   addFieldDetails( ifds::BasedOn,		IFASTBP_PROC::FEE_PARAM_LIST );

   addFieldDetails( ifds::AcctFeeParamId,    IFASTBP_PROC::FEE_SCALE_LIST );
   addFieldDetails( ifds::ScaleRate,    IFASTBP_PROC::FEE_SCALE_LIST );
   addFieldDetails( ifds::UpperBound,   IFASTBP_PROC::FEE_SCALE_LIST  );
   addFieldDetails( ifds::LowerBound,   IFASTBP_PROC::FEE_SCALE_LIST  );
   addFieldDetails( ifds::FeeCode,      IFASTBP_PROC::FEE_SCALE_LIST  );
   addFieldDetails( ifds::Level,        IFASTBP_PROC::FEE_SCALE_LIST  );
   addFieldDetails( ifds::FeeParamRid,    IFASTBP_PROC::FEE_SCALE_LIST );

   addFieldDetails( ifds::ShrNum,     IFASTBP_PROC::MFACOUNT  );
   addFieldDetails( ifds::GSTExempt,    IFASTBP_PROC::MFACOUNT  );
   addFieldDetails( ifds::AccountNum,   IFASTBP_PROC::MFACOUNT  );

   addFieldDetails(FEEPARAM::PRIMARY_ACCOUNT_OWNER, BF::NullContainerId, SUBCLASS_PROCESS);

}

//******************************************************************************
FeeParamProcess::~FeeParamProcess()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************
SEVERITY FeeParamProcess::doInit()
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, DOINIT );

   try
   {
      getParent()->getParameter( FEEPARAM::ACCOUNT_NUM, _accountNum );

      _accountNum.stripLeading( '0' ).strip();
      const BFDataGroupId& idDataGroup = getDataGroupId();
      DString _shrNum;
      if( _accountNum != NULL_STRING )
      {
         MFAccount* pMFAccount = NULL;

         DSTCWorkSession *dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
         if( dstcWorkSession->getMFAccount( idDataGroup, _accountNum, pMFAccount ) <= WARNING )
         {
            if( pMFAccount->getFeeParamList(_pFeeParamList,idDataGroup) <= WARNING )
            {
               setContainer( IFASTBP_PROC::FEE_PARAM_LIST, _pFeeParamList ); 
               setContainer( IFASTBP_PROC::MFACOUNT, pMFAccount ); 

               dstcWorkSession->getFirstSequenced01AccountholderEntityName( idDataGroup, _accountNum, _dstrEntityName);


            }

         }
      }
      else
      {
         //TODO
         //add condition
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
E_COMMANDRETURN FeeParamProcess::doProcess()
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
         rtn = invokeCommand( this, CMD_GUI_FEE_PARAMETER, getProcessType(), isModal(), &_rpChildGI );
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
bool  FeeParamProcess::doModelessSetFocus( GenericInterface *rpGICaller )
{  // This is implemented to pass set focus on to child dialog.
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, DOMODELESSSETFOCUS );
   bool bRtn = false;

   try
   {
      getParent()->getParameter( FEEPARAM::ACCOUNT_NUM, _accountNum );

      _accountNum.stripLeading( '0' ).strip();
      const BFDataGroupId& idDataGroup = getDataGroupId();
      DString _shrNum;
      if( _accountNum != NULL_STRING )
      {
         MFAccount* pMFAccount = NULL;

         DSTCWorkSession *dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
         if( dstcWorkSession->getMFAccount( idDataGroup, _accountNum, pMFAccount ) <= WARNING )
         {
            if( pMFAccount->getFeeParamList(_pFeeParamList,idDataGroup) <= WARNING )
            {
               setContainer( IFASTBP_PROC::FEE_PARAM_LIST, _pFeeParamList ); 
               setContainer( IFASTBP_PROC::MFACOUNT, pMFAccount ); 

            }
         }
      }
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
bool  FeeParamProcess::doModelessChildComplete( const Command &cmd )
{
   // End when GUI ends
   return( cmd.getKey() == CMD_GUI_FEE_PARAMETER );
}
//******************************************************************************
void* FeeParamProcess::getPtrForContainer( const BFContainerId& idContainer, const BFDataGroupId& idDataGroup )
{
   void *ptr = NULL;
   DSTCWorkSession *dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());

   try
   {
//CP20030319      switch( idContainer )
//CP20030319      {
//CP20030319         case FEEPARAM::FEE_SCALE_LIST:
      if( IFASTBP_PROC::FEE_SCALE_LIST == idContainer )
      {
         {
            FeeParam *pFeeParam = dynamic_cast< FeeParam * >( getCBOItem( IFASTBP_PROC::FEE_PARAM_LIST, idDataGroup ) );
            if( pFeeParam )
            {
               DString strFeeType;
               pFeeParam->getField(ifds::ParamFeeType,strFeeType,idDataGroup,false );
               if(SCALE == strFeeType || TIER == strFeeType )
               {
                  FeeScaleList* pFeeScaleList;
                  pFeeParam->getFeeScaleList( pFeeScaleList, idDataGroup );
                  ptr = pFeeScaleList;
               }
            }
//CP20030319               break;
         }

//CP20030319         default:
      }
      else
      {
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
      assert( 0 );
      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, DOINIT,
                      CND::BP_ERR_UNKNOWN_EXCEPTION );
   }
   return(ptr);
}

//******************************************************************************
bool FeeParamProcess::doRefresh( GenericInterface *rpGICaller,
                                 const I_CHAR *szOriginalCommand )
{
   setParameter( FEEPARAM::ACCOUNT_NUM, _accountNum );
   return(_rpChildGI->refresh( this, NULL ));
}

//******************************************************************************

void FeeParamProcess::doGetField( const GenericInterface *rpGICaller,
                                  const BFContainerId& idContainer,
                                  const BFFieldId& idField,
                                  const BFDataGroupId& idDataGroup,
                                  DString &strValueOut,
                                  bool bFormatted
                                 ) const
{

   if( idField == FEEPARAM::PRIMARY_ACCOUNT_OWNER )
   {
      strValueOut = _dstrEntityName;
   }
   else
   {
      assert( 0 );   
   }
}

//*****************************************************************************
SEVERITY FeeParamProcess::performSearch( GenericInterface *rpGI, 
                                         const BFContainerId& idSearch, 
                                         E_SEARCHACTION eSearchAction )
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, I_("performSearch") );
   SEVERITY sevRtn = SEVERE_ERROR;

   try
   {
      if( _pFeeParamList != NULL && rpGI != NULL )
      {
         sevRtn = _pFeeParamList->init(_accountNum,getDataGroupId(),true);
         setContainer(IFASTBP_PROC::FEE_PARAM_LIST, _pFeeParamList );
      }
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
   return(sevRtn); 
}

//***********************************************************************************
bool FeeParamProcess::doMoreRecordsExist( GenericInterface *rpGICaller,
                                          const BFContainerId& idSearch )
{
   return(_pFeeParamList->doMoreRecordsExist( ));
}

//******************************************************************************
SEVERITY FeeParamProcess::getHistoricalParameters(const BFContainerId& idContainer, 
                                                  BFFieldId &recordIdField, 
                                                  DString& tableId,
                                                  DString& dstrKeys) 
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, GETHISTORICALPARAMETERS );

   if( idContainer == IFASTBP_PROC::FEE_PARAM_LIST || 
       idContainer == IFASTBP_PROC::FEE_SCALE_LIST )
   {
      recordIdField = ifds::AcctFeeParamId;
      tableId = AUDITTYPE::FEP;
      dstrKeys = NULL_STRING;
   }
   else
   {
      assert(0);
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
bool FeeParamProcess::doOk( GenericInterface *rpGICaller )
{
   MFAccount *pMFAccount = NULL;   
   const BFDataGroupId& idDataGroup = getDataGroupId();
   DSTCWorkSession *dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
   if( dstcWorkSession->getMFAccount( idDataGroup, _accountNum, pMFAccount ) <= WARNING )
   {
      FeeParamList *pFeeParamList = NULL;
      if( pMFAccount && pMFAccount->getFeeParamList(pFeeParamList,idDataGroup) <= WARNING )
      {
         if ( pFeeParamList && pFeeParamList->isUpdatedForDataGroup( getDataGroupId() ) )
            pMFAccount->refreshMe ( true );
      }
   }
   return(true);
}

//******************************************************************************
SEVERITY FeeParamProcess::getHistoricalParameters( const BFContainerId& idContainer, 
                                                   HISTORICAL_VECTOR &vectorHistorical )
{
   MAKEFRAMEAUTOPROMOTE2(CND::BPBASE_CONDITION, CLASSNAME, GETHISTORICALPARAMETERS);
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
//              Private Methods
//******************************************************************************

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/FeeParamProcess.cpp-arc  $
// 
//    Rev 1.27   Mar 12 2012 15:02:38   dchatcha
// IN# 2864027 - NCE_MF Offset Rate_Program error if setup offset with FeeType Scale or Tier
// 
//    Rev 1.26   Jan 15 2008 10:44:02   yingz
// fix incident 1103280
// 
//    Rev 1.25   Mar 10 2004 13:14:14   HERNANDO
// PET965 FN11 - Added getHistoricalParameters.
// 
//    Rev 1.24   Mar 03 2004 16:21:18   popescu
// PTS 10027578, refresh the account information after updating the mailing address info and demographics info; changed the name of the refreshMe method, to be consistent with the shareholder object
// 
//    Rev 1.23   Dec 08 2003 15:40:38   HSUCHIN
// PTS 10024902 - bug fix with mfaccount refresh to show updated cautions list.
// 
//    Rev 1.22   Aug 18 2003 16:09:12   HERNANDO
// Added keys to getHistoricalParameters.
// 
//    Rev 1.21   Jun 03 2003 10:06:26   linmay
// added BasedOn field
// 
//    Rev 1.20   Apr 03 2003 09:36:56   YINGBAOL
// fix FeeParamId
// 
//    Rev 1.19   Mar 21 2003 17:39:36   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.18   Mar 11 2003 13:49:48   PURDYECH
// Fixes to help the DataGroupId source code converters work more smoothly.
// 
//    Rev 1.17   Mar 05 2003 11:22:32   PURDYECH
// IFastBaseProcess no longer exists.  Classes now derive from AbstractProcess (again) and the Protocol class IFastHistoricalParameters.
// 
//    Rev 1.16   Feb 20 2003 09:26:34   YINGBAOL
// add ModPerm field
// 
//    Rev 1.15   Feb 14 2003 16:25:52   linmay
// added brokercode
// 
//    Rev 1.14   Feb 07 2003 16:31:30   HSUCHIN
// historical bug fix
// 
//    Rev 1.13   Feb 05 2003 12:06:48   popescu
// Changes related to adding a new audit type id, for PAC/SWP and testing the FeeParam/Sys Historical button
// 
//    Rev 1.12   Jan 29 2003 16:22:04   popescu
// Added the historical button for FeeParamSysDlg and FeeParamDlg
// 
//    Rev 1.11   Jan 22 2003 17:50:10   YINGBAOL
// Fund Group is not a must list
// 
//    Rev 1.10   Jan 03 2003 19:45:18   YINGBAOL
// add FundGroupCommList and corresponding logic
// 
//    Rev 1.9   Jan 03 2003 16:28:22   linmay
// rename CommGroupCode to FundGroup
// 
//    Rev 1.8   Jan 02 2003 15:37:02   linmay
// added field CommGroup
// 
//    Rev 1.7   Oct 09 2002 23:53:14   PURDYECH
// PVCS Database Conversion
// 
//    Rev 1.6   Aug 29 2002 16:44:54   SMITHDAV
// Condition split.
// 
//    Rev 1.5   Aug 29 2002 12:54:20   SMITHDAV
// ClientLocale and typed field changes.
// 
//    Rev 1.4   Jun 03 2002 16:42:26   FENGYONG
// Add name for API
// 
//    Rev 1.3   22 May 2002 18:24:14   PURDYECH
// BFData Implementation
// 
//    Rev 1.2   27 Mar 2002 19:54:50   PURDYECH
// Process/WindowFactory overhaul
// 
//    Rev 1.1   Feb 22 2002 14:21:36   YINGBAOL
// more function added
//
//    Rev 1.0   Feb 01 2002 15:18:14   YINGBAOL
// Initial revision.
//


 *
 */
