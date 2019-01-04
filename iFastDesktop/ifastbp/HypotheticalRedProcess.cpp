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
// ^FILE   : HypotheticalRedProcess.cpp
// ^AUTHOR : Zijian Ying
// ^DATE   : 04/20/2000
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : HypotheticalRedProcess
//    This class manages the Bank Instructions information.
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include "stdafx.h"
#include "hypotheticalredprocess.hpp"
#include "hypotheticalredprocessincludes.h"
#include <ifastcbo\hypotheticalred.hpp>
extern IFASTBP_LINKAGE const I_CHAR* CMD_GUI_HYPOTHETICALRED;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_HYPOTHETICALRED;
#include <bfproc\concreteprocesscreator.hpp>
static ConcreteProcessCreator< HypotheticalRedProcess > processCreator( CMD_BPROC_HYPOTHETICALRED );

namespace
{
   // Trace literals
   const I_CHAR * const CLASSNAME = I_( "HypotheticalRedProcess" );
}

namespace CND
{
   extern CLASS_IMPORT const long BP_ERR_UNKNOWN_EXCEPTION;
}

namespace HYPOTHETICALREDINFOLIT  
{
   const I_CHAR * const ACCOUNTNUM = I_( "AccountNum" );
   const I_CHAR * const FUNDCODE = I_( "FundCode" );
   const I_CHAR * const CLASSCODE = I_( "ClassCode" );
   const I_CHAR * const TRADEDATE = I_( "TradeDate" );
   const I_CHAR * const GROSSORNET = I_( "GrossOrNet" );
   const I_CHAR * const AMOUNTTYPE = I_( "AmountType" );
   const I_CHAR * const FULLREDEM = I_( "FullRedem" );
   const I_CHAR * const REDCODE = I_( "RedCode" );
   const I_CHAR * const AMOUNT = I_( "Amount" );
   const I_CHAR * const BAYCOM = I_( "Baycom" );
}


//******************************************************************************
//              Public Methods
//******************************************************************************

HypotheticalRedProcess::HypotheticalRedProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: AbstractProcess( pGIC, pGIParent, rCommand )
, _rpChildGI( NULL ),
_pHypotheticalRed( NULL )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );

   addContainer( IFASTBP_PROC::HYPOTHETICALRED, false, BF::NullContainerId, false, I_("HypoRedemption") );
   addFieldDetails( ifds::TotalRedAmt, IFASTBP_PROC::HYPOTHETICALRED );
   addFieldDetails( ifds::TotalDSC, IFASTBP_PROC::HYPOTHETICALRED );
   addFieldDetails( ifds::Fee, IFASTBP_PROC::HYPOTHETICALRED );
   addFieldDetails( ifds::WithHoldTax, IFASTBP_PROC::HYPOTHETICALRED );
   addFieldDetails( ifds::NetAmt, IFASTBP_PROC::HYPOTHETICALRED );
   addFieldDetails( ifds::FedTax, IFASTBP_PROC::HYPOTHETICALRED );
   addFieldDetails( ifds::ProvTax, IFASTBP_PROC::HYPOTHETICALRED );

   addContainer( IFASTBP_PROC::HYPOTHETICALRED_DETAIL_LIST, true, IFASTBP_PROC::HYPOTHETICALRED, false, I_("HypoRedemptionDetail") );
   addFieldDetails( ifds::rxFundCode, IFASTBP_PROC::HYPOTHETICALRED_DETAIL_LIST );
   addFieldDetails( ifds::rxClassCode, IFASTBP_PROC::HYPOTHETICALRED_DETAIL_LIST );
   addFieldDetails( ifds::GrossAmt, IFASTBP_PROC::HYPOTHETICALRED_DETAIL_LIST );
   addFieldDetails( ifds::Units, IFASTBP_PROC::HYPOTHETICALRED_DETAIL_LIST );
   addFieldDetails( ifds::DSC, IFASTBP_PROC::HYPOTHETICALRED_DETAIL_LIST );
   addFieldDetails( ifds::FeeFreeAmt, IFASTBP_PROC::HYPOTHETICALRED_DETAIL_LIST );
   addFieldDetails( ifds::FeeFreeUnits, IFASTBP_PROC::HYPOTHETICALRED_DETAIL_LIST );
   addFieldDetails( ifds::FeeApplAmt, IFASTBP_PROC::HYPOTHETICALRED_DETAIL_LIST );
   addFieldDetails( ifds::FeeApplUnits, IFASTBP_PROC::HYPOTHETICALRED_DETAIL_LIST );
   addFieldDetails( ifds::ValueAsAt, IFASTBP_PROC::HYPOTHETICALRED_DETAIL_LIST );
   addFieldDetails( ifds::FundNAV, IFASTBP_PROC::HYPOTHETICALRED_DETAIL_LIST );
   addFieldDetails( ifds::rxBaycom, IFASTBP_PROC::HYPOTHETICALRED_DETAIL_LIST );
   addFieldDetails( ifds::ElongName1, IFASTBP_PROC::HYPOTHETICALRED_DETAIL_LIST );
   addFieldDetails( ifds::AcctUnits, IFASTBP_PROC::HYPOTHETICALRED_DETAIL_LIST );

}

//******************************************************************************

HypotheticalRedProcess::~HypotheticalRedProcess()
{
   TRACE_DESTRUCTOR( CLASSNAME );

   if( _pHypotheticalRed )delete _pHypotheticalRed;
}

//******************************************************************************
//              Protected Methods
//******************************************************************************

//******************************************************************************

E_COMMANDRETURN HypotheticalRedProcess::doProcess()
{  
   MAKEFRAME2( CND::BPBASE_CONDITION, CLASSNAME, DOPROCESS );
   E_COMMANDRETURN rtn = CMD_FAILURE;

//   try
//   {
//      rtn = invokeCommand( this, CMD_GUI_HYPOTHETICALRED, getProcessType(),
//                           isModal(), &_rpChildGI );
//   }
//   catch( ConditionException &ce )
//   {
//      assert( 0 );
//      SETCONDITIONFROMEXCEPTION( ce );
//   }
//   catch( ... )
//   {
//      assert( 0 );
//      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, DOPROCESS,
//                      CND::BP_ERR_UNKNOWN_EXCEPTION );
//   }

   rtn = CMD_MODELESS_INPROCESS;
   return(rtn);
}

//******************************************************************************

bool HypotheticalRedProcess::doModelessChildComplete( const Command &cmd )
{
   // End when GUI ends
   return( cmd.getKey() == CMD_GUI_HYPOTHETICALRED );
}

//******************************************************************************
SEVERITY HypotheticalRedProcess::doInit()
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, I_("doInit") );
   SEVERITY sevRtn = NO_CONDITION;

   try
   {
      DString AccountNum;
      DString FundCode;
      DString ClassCode;
      DString TradeDate;
      DString GrossOrNet;
      DString AmountType;
      DString FullRedem;
      DString RedCode;
      DString Amount;
      DString Baycom;

      getParameter( HYPOTHETICALREDINFOLIT::ACCOUNTNUM, AccountNum );
      getParameter( HYPOTHETICALREDINFOLIT::FUNDCODE, FundCode );
      getParameter( HYPOTHETICALREDINFOLIT::CLASSCODE, ClassCode );
      getParameter( HYPOTHETICALREDINFOLIT::TRADEDATE, TradeDate );
      getParameter( HYPOTHETICALREDINFOLIT::GROSSORNET, GrossOrNet );
      getParameter( HYPOTHETICALREDINFOLIT::AMOUNTTYPE, AmountType );
      getParameter( HYPOTHETICALREDINFOLIT::FULLREDEM, FullRedem );
      getParameter( HYPOTHETICALREDINFOLIT::REDCODE, RedCode );
      getParameter( HYPOTHETICALREDINFOLIT::AMOUNT, Amount );
      getParameter( HYPOTHETICALREDINFOLIT::BAYCOM, Baycom );

      if ( FullRedem.stripTrailing() == NULL_STRING ) {
         FullRedem = I_("N");
      }

      _pHypotheticalRed = new HypotheticalRed( *getBFWorkSession() );
      sevRtn = _pHypotheticalRed->init( AccountNum,
                                        FundCode,
                                        ClassCode,
                                        TradeDate,
                                        GrossOrNet,
                                        AmountType,
                                        FullRedem,
                                        RedCode,
                                        Amount,
                                        Baycom );
      if( sevRtn <= WARNING ) 
      {	
         setContainer( IFASTBP_PROC::HYPOTHETICALRED, _pHypotheticalRed );
         setContainer( IFASTBP_PROC::HYPOTHETICALRED_DETAIL_LIST, _pHypotheticalRed );
	  }
      else
	  {
         return(sevRtn);
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

   return(sevRtn);
}


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/HypotheticalRedProcess.cpp-arc  $
// 
//    Rev 1.11   22 Jun 2004 15:36:24   SMITHDAV
// Expose hypothetical redemptions as an API interface.
// 
//    Rev 1.10   Mar 21 2003 17:41:36   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.9   Oct 09 2002 23:53:18   PURDYECH
// PVCS Database Conversion
// 
//    Rev 1.8   Aug 29 2002 16:44:58   SMITHDAV
// Condition split.
// 
//    Rev 1.7   Aug 29 2002 12:54:24   SMITHDAV
// ClientLocale and typed field changes.
// 
//    Rev 1.6   22 May 2002 18:24:20   PURDYECH
// BFData Implementation
// 
//    Rev 1.5   27 Mar 2002 19:54:56   PURDYECH
// Process/WindowFactory overhaul
// 
//    Rev 1.4   Feb 25 2002 18:54:22   PURDYECH
// Phase 1 of BFData Rollout - Base Component Compatibility
// 
//    Rev 1.3   03 May 2001 14:05:26   SMITHDAV
// Session management restructuring.
// 
//    Rev 1.2   15 Dec 2000 12:43:32   PURDYECH
// Use precompiled header stdafx.h.
// Removed unnecessary header files.
// 
//    Rev 1.1   May 10 2000 10:07:06   YINGZ
// check in
 */
