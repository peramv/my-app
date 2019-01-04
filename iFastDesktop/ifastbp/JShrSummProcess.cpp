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
// ^FILE   : JShrSummProcess.cpp
// ^AUTHOR : Yongmei Feng
// ^DATE   : 25/02/2000
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : ShrSummProcess
//    This class manages the remarks information.
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include "stdafx.h"
#include <time.h>
#include "jshrsummprocess.hpp"
#include <ifastdataimpl\dse_dstc0103_req.hpp>
#include "jshrsummprocessincludes.h"
#include <ifastcbo\jshrsumm.hpp>
#include <ifastcbo\mgmtcooptions.hpp>
#include <ifastcbo\mgmtco.hpp>
#include "etrackheader.h"
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_JSHRSUMM;
#include <bfproc\concreteprocesscreator.hpp>
static ConcreteProcessCreator< ShrSummProcess > processCreator( CMD_BPROC_JSHRSUMM );

namespace
{
   // Trace literals
   const I_CHAR * const CLASSNAME = I_( "ShrSummProcess" );
}

namespace SHRSUMMLIT  //stands for account details literals
{
   const I_CHAR * const SHRNUM = I_( "TxShrNum" );  
}

namespace CND
{  // Conditions used
   extern CLASS_IMPORT const long BP_ERR_UNKNOWN_EXCEPTION;
   extern CLASS_IMPORT const long BP_ERR_NO_DATA_AREA;
}

//******************************************************************************
//              Public Methods
//******************************************************************************

//CP20030319ShrSummProcess::ShrSummProcess() : 
ShrSummProcess::ShrSummProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: AbstractProcess( pGIC, pGIParent, rCommand )
, _pJShrSumm( NULL ),
_pTranslationList( NULL ),
_rpChildGI( NULL )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );

   addContainer( IFASTBP_PROC::SHRSUMM_LIST, true );
   addContainer( IFASTBP_PROC::TRANSLATION_LIST, true );

   addSubstituteList( ifds::TaxType );

   addFieldDetails( ifds::FundCode, IFASTBP_PROC::SHRSUMM_LIST );
   addFieldDetails( ifds::ClassCode, IFASTBP_PROC::SHRSUMM_LIST );
   addFieldDetails( ifds::ValueAsAt, IFASTBP_PROC::SHRSUMM_LIST );
   addFieldDetails( ifds::Currency, IFASTBP_PROC::SHRSUMM_LIST );
   addFieldDetails( ifds::UnitValue, IFASTBP_PROC::SHRSUMM_LIST );
   addFieldDetails( ifds::FundUnits, IFASTBP_PROC::SHRSUMM_LIST );
   addFieldDetails( ifds::FundPercent, IFASTBP_PROC::SHRSUMM_LIST );
   addFieldDetails( ifds::FundAmt, IFASTBP_PROC::SHRSUMM_LIST );
   addFieldDetails( ifds::TaxType, IFASTBP_PROC::SHRSUMM_LIST );
   addFieldDetails( ifds::TaxTypeDesc, IFASTBP_PROC::SHRSUMM_LIST );
   addFieldDetails( ifds::ProductPercent, IFASTBP_PROC::SHRSUMM_LIST );
   addFieldDetails( ifds::ProductAmount, IFASTBP_PROC::SHRSUMM_LIST );
   addFieldDetails( ifds::ShrBalance, IFASTBP_PROC::SHRSUMM_LIST );

   addFieldDetails(ifds::FundCode, IFASTBP_PROC::TRANSLATION_LIST );
   addFieldDetails(ifds::FundName, IFASTBP_PROC::TRANSLATION_LIST );
   addFieldDetails(ifds::LangCode, IFASTBP_PROC::TRANSLATION_LIST );
}

//******************************************************************************

ShrSummProcess::~ShrSummProcess()
{
   TRACE_DESTRUCTOR( CLASSNAME );

   delete _pJShrSumm;
   _rpChildGI = NULL;
}

bool ShrSummProcess::doGetData(
                              GenericInterface * ,
                              BFData * 
                              ) const
{
   _pJShrSumm->getMore();
   ShrSummProcess * _pAbsPr = const_cast < ShrSummProcess * >(this);
   _pAbsPr->setContainer( IFASTBP_PROC::SHRSUMM_LIST, NULL );
   _pAbsPr->setContainer( IFASTBP_PROC::SHRSUMM_LIST, _pJShrSumm );
   return(true);
}

bool ShrSummProcess::doMoreRecordsExist(
                                       GenericInterface *rpGICaller,
                                       const BFContainerId& idContainer 
                                       )
{
   return( _pJShrSumm->doMoreRecordsExist() );
}



//******************************************************************************
//              Protected Methods
//******************************************************************************

SEVERITY ShrSummProcess::doInit()
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, DOINIT );
   SEVERITY sevRtn = SEVERE_ERROR;

   DString _ShrNum;
   try
   {
      getParameter( SHRSUMMLIT::SHRNUM, _ShrNum );

      DString dstrTrack,dstrActivity;
      getParameter( ETRACK::TRACK, dstrTrack );
      getParameter( ETRACK::ACTIVITY, dstrActivity );
      if( dstrTrack.strip() == NULL_STRING )dstrTrack = I_("N");

      DSTCWorkSession *dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());

      _pJShrSumm = new JShrSumm( *dstcWorkSession );

      sevRtn = _pJShrSumm->init( _ShrNum,dstrTrack,dstrActivity);

      if( WARNING >= sevRtn )
      {
         setContainer( IFASTBP_PROC::SHRSUMM_LIST, _pJShrSumm );
      }

      sevRtn = dstcWorkSession->getMgmtCo().getTranslationList( _pTranslationList );
      if( WARNING >= sevRtn )
      {
         setContainer( IFASTBP_PROC::TRANSLATION_LIST, _pTranslationList );
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

E_COMMANDRETURN ShrSummProcess::doProcess()
{  
   MAKEFRAME2( CND::BPBASE_CONDITION, CLASSNAME, DOPROCESS );
   E_COMMANDRETURN rtn = CMD_FAILURE;

   rtn = CMD_MODELESS_INPROCESS;
   return(rtn);
}

//******************************************************************************
//******************************************************************************
//              Private Methods
//******************************************************************************

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/JShrSummProcess.cpp-arc  $
 * 
 *    Rev 1.18   Mar 21 2003 17:44:20   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.17   Mar 09 2003 15:56:16   PURDYECH
 * Small fixes around DataGroupIds and ContainerIds.
 * 
 *    Rev 1.16   Oct 09 2002 23:53:26   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.15   Aug 29 2002 16:45:04   SMITHDAV
 * Condition split.
 * 
 *    Rev 1.14   Aug 29 2002 12:54:30   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.13   22 May 2002 18:24:38   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.12   27 Mar 2002 19:55:16   PURDYECH
 * Process/WindowFactory overhaul
 * 
 *    Rev 1.11   03 May 2001 14:05:34   SMITHDAV
 * Session management restructuring.
 * 
 *    Rev 1.10   Jan 31 2001 16:05:34   YINGBAOL
 * to prevent  track para from being empty 
 * 
 *    Rev 1.9   Jan 23 2001 15:17:52   YINGBAOL
 * add eTrack
 * 
 *    Rev 1.8   15 Dec 2000 12:43:42   PURDYECH
 * Use precompiled header stdafx.h.
 * Removed unnecessary header files.
 * 
 *    Rev 1.7   Dec 06 2000 15:11:18   VASILEAD
 * Fix the name of the parameter for ShrNum
 * 
 *    Rev 1.6   Sep 08 2000 13:44:32   YINGZ
 * bug fix
 * 
 *    Rev 1.5   Aug 22 2000 16:54:52   FENGYONG
 * Fix for french fundname and French desc
 * 
 *    Rev 1.4   Jul 27 2000 17:28:14   VASILEAD
 * Change the short fund name to long fund name
 * 
 *    Rev 1.3   Jul 05 2000 13:45:16   VASILEAD
 * Added ShortName from FundMasterList
 * 
 *    Rev 1.2   Mar 30 2000 15:47:42   FENGYONG
 * For error handle
 * 
 *    Rev 1.1   Mar 24 2000 12:22:56   POPESCUS
 * Make things happen for Vision
// 
//    Rev 1.1   Mar 10 2000 09:57:30   FENGYONG
// For Nextkey
// 
//    Rev 1.0   Feb 25 2000 16:17:44   FENGYONG
// Initial revision.
// 
// Initial revision.
 * 
 */


