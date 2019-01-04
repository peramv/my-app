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
// ^FILE   : AllFundInfoProcess.cpp
// ^AUTHOR : 
// ^DATE   : 03/09/1999
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : AllFundInfoProcess
//    This class manages the remarks information.
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include "stdafx.h"
#include "allfundinfoprocess.hpp"
#include <ifastdataimpl\dse_dstc0063_req.hpp>
#include <ifastdataimpl\dse_dstc0056_req.hpp>
#include <ifastdataimpl\dse_dstc0136_vw.hpp>
#include <ifastdataimpl\dse_dstc0148_vw.hpp>
#include <ifastdataimpl\dse_dstc0107_vw.hpp>
#include "allfundinfoprocessincludes.h"
#include <ifastcbo\acqfeeinquiry.hpp>
#include <ifastcbo\feeinfoinquiry.hpp>
#include <ifastcbo\currencyclass.hpp>
#include <ifastcbo\fundmasterlist.hpp>
#include <ifastcbo\funddetaillist.hpp>
#include <ifastcbo\mgmtcooptions.hpp>
#include <ifastcbo\mgmtco.hpp>
#include <ifastcbo\feeinfoinquiry.hpp>
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_ALLFUNDINFO;
#include <bfproc\concreteprocesscreator.hpp>
static ConcreteProcessCreator< AllFundInfoProcess > processCreator( CMD_BPROC_ALLFUNDINFO );

namespace
{
   // Trace literals
   const I_CHAR * const CLASSNAME = I_( "AllFundInfoProcess" );
}

namespace ALLFUNDINFOLIT  //stands for account details literals
{
   const I_CHAR * const FUND_CODE = I_( "FundCode" ); 
   const I_CHAR * const CLASS_CODE = I_( "ClassCode" );
}

namespace CND
{  // Conditions used
   extern CLASS_IMPORT const long BP_ERR_UNKNOWN_EXCEPTION;
}

//******************************************************************************
//              Public Methods
//******************************************************************************

AllFundInfoProcess::AllFundInfoProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: AbstractProcess( pGIC, pGIParent, rCommand )
, _pFundMasterList( NULL )
, _pmgmtcooptions(NULL)
, _pTranslationList( NULL )
, _rpChildGI( NULL )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );

   addContainer( IFASTBP_PROC::FUNDDETAILS_LIST,   true );
   addContainer( IFASTBP_PROC::FUNDMASTER_LIST,    true );
   addContainer( IFASTBP_PROC::FUNDSPONSORS_LIST,  true );
   addContainer( IFASTBP_PROC::MGMTCOOPTIONS_LIST, false );
   addContainer( IFASTBP_PROC::TRANSLATION_LIST,   true );
   addContainer( IFASTBP_PROC::ACQFEEINQUIRY_CBO,  false );
   addContainer( IFASTBP_PROC::FEEINFOINQUIRY_CBO, true );

   addFieldDetails( ifds::CurrBusDate,   IFASTBP_PROC::MGMTCOOPTIONS_LIST );

   addFieldDetails( ifds::FundCode,      IFASTBP_PROC::FUNDMASTER_LIST );
   addFieldDetails( ifds::FundGroup,     IFASTBP_PROC::FUNDMASTER_LIST );

   addFieldDetails( ifds::FundGroup,     IFASTBP_PROC::FUNDSPONSORS_LIST );
   addFieldDetails( ifds::FundGroupDesc, IFASTBP_PROC::FUNDSPONSORS_LIST );

   addFieldDetails( ifds::FundCode,      IFASTBP_PROC::FUNDDETAILS_LIST );
   addFieldDetails( ifds::ClassCode,     IFASTBP_PROC::FUNDDETAILS_LIST );
   addFieldDetails( ifds::Currency,      IFASTBP_PROC::FUNDDETAILS_LIST );
   addFieldDetails( ifds::LoadType,      IFASTBP_PROC::FUNDDETAILS_LIST );

   addFieldDetails(ifds::LangCode,       IFASTBP_PROC::TRANSLATION_LIST );
   addFieldDetails(ifds::FundCode,       IFASTBP_PROC::TRANSLATION_LIST );
   addFieldDetails(ifds::FundName,       IFASTBP_PROC::TRANSLATION_LIST );

   addFieldDetails( ifds::AcqFee,        IFASTBP_PROC::ACQFEEINQUIRY_CBO, SUBCLASS_PROCESS );
   addFieldDetails( ifds::AcqFeeType,    IFASTBP_PROC::ACQFEEINQUIRY_CBO, SUBCLASS_PROCESS );
}

//******************************************************************************

AllFundInfoProcess::~AllFundInfoProcess()
{
   TRACE_DESTRUCTOR( CLASSNAME );

   _rpChildGI = NULL;
   if( _pFeeInfoInquiry )
   {
      delete _pFeeInfoInquiry;   _pFeeInfoInquiry = NULL;
   }
}

//******************************************************************************
//              Protected Methods
//******************************************************************************

SEVERITY AllFundInfoProcess::doInit()
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTBP_CONDITION, CLASSNAME, DOINIT );
   SEVERITY sevRtn = SEVERE_ERROR;
   DString _pFundSponsor= NULL_STRING,_pFundCode = NULL_STRING, _pClassCode = NULL_STRING;
   try
   {

      DSTCWorkSession* dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
      MgmtCo &mgmtCoOut = dstcWorkSession->getMgmtCo();

      sevRtn = mgmtCoOut.getFundDetailList( _pFundDetailsList );
      if( WARNING >= sevRtn )
      {
         setContainer( IFASTBP_PROC::FUNDDETAILS_LIST, _pFundDetailsList );
      }

      sevRtn = mgmtCoOut.getFundMasterList( _pFundMasterList );
      if( WARNING >= sevRtn )
      {
         setContainer( IFASTBP_PROC::FUNDMASTER_LIST, _pFundMasterList );
      }

      sevRtn = mgmtCoOut.getFundSponsorsList( _pFundSponsorsList );
      if( WARNING >= sevRtn )
      {
         setContainer( IFASTBP_PROC::FUNDSPONSORS_LIST, _pFundSponsorsList );
      }

      sevRtn = mgmtCoOut.getMgmtCoOptions( _pmgmtcooptions );

      if( WARNING >= sevRtn )
      {
         setContainer( IFASTBP_PROC::MGMTCOOPTIONS_LIST, _pmgmtcooptions );
      }

      sevRtn = mgmtCoOut.getTranslationList( _pTranslationList );
      if( WARNING >= sevRtn )
      {
         setContainer( IFASTBP_PROC::TRANSLATION_LIST, _pTranslationList );
      }

      _pFeeInfoInquiry = new FeeInfoInquiry( *dstcWorkSession );
      sevRtn = _pFeeInfoInquiry->init( _pFundCode, _pClassCode, _pFundSponsor);

      if( WARNING >= sevRtn )
      {
         setContainer( IFASTBP_PROC::FEEINFOINQUIRY_CBO, _pFeeInfoInquiry );
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

E_COMMANDRETURN AllFundInfoProcess::doProcess()
{  
   MAKEFRAME2( CND::IFASTBP_CONDITION, CLASSNAME, DOPROCESS );
   E_COMMANDRETURN rtn = CMD_FAILURE;

   rtn = CMD_MODELESS_INPROCESS;
   return(rtn);
}

void AllFundInfoProcess::doGetField( const GenericInterface *rpGICaller, const BFContainerId& idContainer, const BFFieldId& idField,
                                     const BFDataGroupId& idDataGroup, DString &strValueOut, bool bFormatted ) const
{
   DSTCWorkSession *dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
   AllFundInfoProcess *rpNonConstThis = const_cast < AllFundInfoProcess*> ( this );

   if( idContainer == IFASTBP_PROC::ACQFEEINQUIRY_CBO && ( idField == ifds::AcqFee || idField == ifds::AcqFeeType ) )
   {
      DString fundCode, classCode;
      rpNonConstThis->getField( rpGICaller, IFASTBP_PROC::FUNDDETAILS_LIST, ifds::FundCode, fundCode, false );
      rpNonConstThis->getField( rpGICaller, IFASTBP_PROC::FUNDDETAILS_LIST, ifds::ClassCode, classCode, false );

      AcqFeeInquiry *pAcqFeeInquiry;
      try
      {
         pAcqFeeInquiry= new AcqFeeInquiry( *dstcWorkSession );
         pAcqFeeInquiry->init( NULL, NULL, NULL, NULL, NULL, fundCode, classCode, NULL, NULL, NULL, NULL );
         pAcqFeeInquiry->getField( idField, strValueOut, idDataGroup, bFormatted );
      }
      catch( ... )
      {
         strValueOut = NULL_STRING;
      }

      if( idField == ifds::AcqFeeType && strValueOut == NULL_STRING )
         strValueOut = I_( "0" );

      if( idField == ifds::AcqFee && strValueOut != NULL_STRING )
      {
         DString dstrCurrency, acqFeeType;

         pAcqFeeInquiry->getField( ifds::AcqFeeType, acqFeeType, idDataGroup, bFormatted );

         if( acqFeeType == I_( "0" ) ) // Flat
         {
            if( fundCode.strip() != NULL_STRING && classCode.strip() != NULL_STRING )
               CurrencyClass::getFundCurrency( *dstcWorkSession, fundCode, classCode, dstrCurrency );

            CurrencyClass::getFormattedValue( *dstcWorkSession, strValueOut, dstrCurrency );
         }
      }
      delete pAcqFeeInquiry; pAcqFeeInquiry = NULL;

   }
}

//******************************************************************************
//              Private Methods
//******************************************************************************

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/AllFundInfoProcess.cpp-arc  $
// 
//    Rev 1.15   Apr 02 2003 14:03:20   PURDYECH
// Cleaned up obsolete code.
// 
//    Rev 1.14   Mar 21 2003 17:35:32   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.13   Oct 09 2002 23:53:02   PURDYECH
// PVCS Database Conversion
// 
//    Rev 1.12   Aug 29 2002 16:42:34   SMITHDAV
// Condition split.
// 
//    Rev 1.11   Aug 29 2002 12:54:12   SMITHDAV
// ClientLocale and typed field changes.
// 
//    Rev 1.10   22 May 2002 18:23:50   PURDYECH
// BFData Implementation
// 
//    Rev 1.9   27 Mar 2002 19:54:32   PURDYECH
// Process/WindowFactory overhaul
// 
//    Rev 1.8   11 May 2001 16:33:34   YINGZ
// code sync up
// 
//    Rev 1.7   May 08 2001 11:29:58   FENGYONG
// Add #107
// 
//    Rev 1.6   03 May 2001 14:05:16   SMITHDAV
// Session management restructuring.
// 
//    Rev 1.5   Apr 02 2001 10:51:44   FENGYONG
// fix leak problem
// 
//    Rev 1.4   Jan 17 2001 12:08:16   VASILEAD
// Added workSessionId param for MgmtCo::getMgmtCoOptions()
// 
//    Rev 1.3   15 Dec 2000 12:43:18   PURDYECH
// Use precompiled header stdafx.h.
// Removed unnecessary header files.
// 
//    Rev 1.2   Dec 11 2000 11:54:54   VASILEAD
// Added back end funds support
// 
//    Rev 1.1   Nov 27 2000 11:37:14   VASILEAD
// Added AllFundInfo support to provide with fund information for the global object in ECOMM
// 
//    Rev 1.0   Nov 20 2000 17:53:20   VASILEAD
// Initial revision.
 * 
 *    Rev 1.6   Aug 22 2000 16:54:52   FENGYONG
 * Fix for french fundname and French desc
 * 
 */


