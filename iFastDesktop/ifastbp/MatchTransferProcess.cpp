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
// ^FILE   : MatchTransferProcess.cpp
// ^AUTHOR : Celia Zhang
// ^DATE   : August 9, 2001
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : MatchTransferProcess
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include "stdafx.h"
#include "matchtransferprocessincludes.h"
#include "matchtransferprocess.hpp"
#include <ifastcbo\fundmasterlist.hpp>
#include <ifastcbo\mfaccount.hpp>
#include <ifastcbo\matchtransferlist.hpp>
#include <ifastcbo\matchtransferdetails.hpp>
#include <ifastcbo\mgmtco.hpp>
#include <ifastdbrkr\dstcsecurity.hpp>
#include <ifastdbrkr\dstchost.hpp>
extern IFASTBP_LINKAGE const I_CHAR* CMD_GUI_MATCHTRANSFER;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_MATCHTRANSFER;
#include <bfproc\concreteprocesscreator.hpp>
static ConcreteProcessCreator< MatchTransferProcess > processCreator( CMD_BPROC_MATCHTRANSFER );

namespace
{
   // Trace literals
   const I_CHAR *CLASSNAME = I_( "MatchTransferProcess" );

   const I_CHAR *Y = I_( "Y" );
   const I_CHAR *N = I_( "N" );
   const I_CHAR *pINQUIRYONLY  = I_( "InquiryOnly" );

}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId AltAccount;
   extern CLASS_IMPORT const BFTextFieldId SettleBatch;
   extern CLASS_IMPORT const BFTextFieldId OrderBatch;
   extern CLASS_IMPORT const BFTextFieldId Baycom;
   extern CLASS_IMPORT const BFTextFieldId Currency;
   extern CLASS_IMPORT const BFTextFieldId RemarksLine;
   extern CLASS_IMPORT const BFNumericFieldId ShrNum;
   extern CLASS_IMPORT const BFTextFieldId MatchTransferAttrTop;
   extern CLASS_IMPORT const BFTextFieldId MatchTransferAttrLeft;
}

namespace CND
{
   extern CLASS_IMPORT const long BP_ERR_UNKNOWN_EXCEPTION; 
   extern CLASS_IMPORT const long BP_ERR_INVALID_METHOD_CALL;
}
//******************************************************************************
//              Public Methods
//******************************************************************************

//CP20030319MatchTransferProcess::MatchTransferProcess() : 
MatchTransferProcess::MatchTransferProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: AbstractProcess( pGIC, pGIParent, rCommand )
, _pMatchTransferList( NULL ),
_rpChildGI( NULL )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );

   addContainer( IFASTBP_PROC::MATCHTRANSFER_CBO, true );
   addContainer( IFASTBP_PROC::FUNDMASTER_LIST, true );

// from vw 22
   addFieldDetails( ifds::TfrFund,         IFASTBP_PROC::MATCHTRANSFER_CBO );
   addFieldDetails( ifds::TfrClass,        IFASTBP_PROC::MATCHTRANSFER_CBO );
   addFieldDetails( ifds::TransNum,        IFASTBP_PROC::MATCHTRANSFER_CBO );
   addFieldDetails( ifds::PrevUnitBal,     IFASTBP_PROC::MATCHTRANSFER_CBO );
   addFieldDetails( ifds::SettleDate,      IFASTBP_PROC::MATCHTRANSFER_CBO );
   addFieldDetails( ifds::SettleBatch,     IFASTBP_PROC::MATCHTRANSFER_CBO );
   addFieldDetails( ifds::OrderBatch,      IFASTBP_PROC::MATCHTRANSFER_CBO );
   addFieldDetails( ifds::NetAmt,          IFASTBP_PROC::MATCHTRANSFER_CBO );
   addFieldDetails( ifds::AltAccount,      IFASTBP_PROC::MATCHTRANSFER_CBO );
   addFieldDetails( ifds::BrokerName,      IFASTBP_PROC::MATCHTRANSFER_CBO );
   addFieldDetails( ifds::BranchName,      IFASTBP_PROC::MATCHTRANSFER_CBO );
   addFieldDetails( ifds::SlsrepName,      IFASTBP_PROC::MATCHTRANSFER_CBO );
   addFieldDetails( ifds::rxFundCode,      IFASTBP_PROC::MATCHTRANSFER_CBO );
   addFieldDetails( ifds::rxClassCode,     IFASTBP_PROC::MATCHTRANSFER_CBO );
   addFieldDetails( ifds::Baycom,          IFASTBP_PROC::MATCHTRANSFER_CBO );
   addFieldDetails( ifds::Currency,        IFASTBP_PROC::MATCHTRANSFER_CBO,   SUBCLASS_PROCESS );

   addFieldDetails( ifds::TradeDate,       IFASTBP_PROC::MATCHTRANSFER_CBO );
   addFieldDetails( ifds::TransType,       IFASTBP_PROC::MATCHTRANSFER_CBO );
   addFieldDetails( ifds::RemarksLine,     IFASTBP_PROC::MATCHTRANSFER_CBO );
   addFieldDetails( ifds::UnitPrice,       IFASTBP_PROC::MATCHTRANSFER_CBO );
   addFieldDetails( ifds::Units,           IFASTBP_PROC::MATCHTRANSFER_CBO );
   addFieldDetails( ifds::GrossAmt,        IFASTBP_PROC::MATCHTRANSFER_CBO,   SUBCLASS_PROCESS );
   addFieldDetails( ifds::UnitBalance,     IFASTBP_PROC::MATCHTRANSFER_CBO );
   addFieldDetails( ifds::Accountable,     IFASTBP_PROC::MATCHTRANSFER_CBO );
   addFieldDetails( ifds::AcctableDesc,    IFASTBP_PROC::MATCHTRANSFER_CBO );
   addFieldDetails( ifds::BackDatedReason, IFASTBP_PROC::MATCHTRANSFER_CBO );
   addFieldDetails( ifds::Commission,      IFASTBP_PROC::MATCHTRANSFER_CBO,   SUBCLASS_PROCESS );
   addFieldDetails( ifds::SplitComm,       IFASTBP_PROC::MATCHTRANSFER_CBO );
   addFieldDetails( ifds::TfrAcct,         IFASTBP_PROC::MATCHTRANSFER_CBO );

   addFieldDetails( ifds::GBCD,            IFASTBP_PROC::MATCHTRANSFER_CBO );
   addFieldDetails( ifds::FeePercent,      IFASTBP_PROC::MATCHTRANSFER_CBO );
   addFieldDetails( ifds::RedCode,         IFASTBP_PROC::MATCHTRANSFER_CBO );
   addFieldDetails( ifds::RedCodeDesc,     IFASTBP_PROC::MATCHTRANSFER_CBO );
   addFieldDetails( ifds::DepositType,     IFASTBP_PROC::MATCHTRANSFER_CBO );
   addFieldDetails( ifds::DepositTypeDesc, IFASTBP_PROC::MATCHTRANSFER_CBO );
   addFieldDetails( ifds::SetGrossAmt,     IFASTBP_PROC::MATCHTRANSFER_CBO );
   addFieldDetails( ifds::SetNetAmt,       IFASTBP_PROC::MATCHTRANSFER_CBO );
   addFieldDetails( ifds::Allocation,      IFASTBP_PROC::MATCHTRANSFER_CBO );
   addFieldDetails( ifds::SlsrepAltName,   IFASTBP_PROC::MATCHTRANSFER_CBO );
   addFieldDetails( ifds::OrderSource,     IFASTBP_PROC::MATCHTRANSFER_CBO );
   addFieldDetails( ifds::OrderSrcDesc,    IFASTBP_PROC::MATCHTRANSFER_CBO );
   addFieldDetails( ifds::SettleSource,    IFASTBP_PROC::MATCHTRANSFER_CBO );
   addFieldDetails( ifds::SettleSrcDesc,   IFASTBP_PROC::MATCHTRANSFER_CBO );
   addFieldDetails( ifds::SettleType,      IFASTBP_PROC::MATCHTRANSFER_CBO );
   addFieldDetails( ifds::SettleTypeDesc,  IFASTBP_PROC::MATCHTRANSFER_CBO );
   addFieldDetails( ifds::SharesElig,      IFASTBP_PROC::MATCHTRANSFER_CBO );
   addFieldDetails( ifds::DepositDate,     IFASTBP_PROC::MATCHTRANSFER_CBO );
   addFieldDetails( ifds::CashDate,        IFASTBP_PROC::MATCHTRANSFER_CBO );
   addFieldDetails( ifds::HoldBackAmt,     IFASTBP_PROC::MATCHTRANSFER_CBO );
   addFieldDetails( ifds::HoldBackRate,    IFASTBP_PROC::MATCHTRANSFER_CBO );
   addFieldDetails( ifds::GrossOrNet,      IFASTBP_PROC::MATCHTRANSFER_CBO );
   addFieldDetails( ifds::RoundFlag,       IFASTBP_PROC::MATCHTRANSFER_CBO );
   addFieldDetails( ifds::ProvSales,       IFASTBP_PROC::MATCHTRANSFER_CBO );
   addFieldDetails( ifds::PartFull,        IFASTBP_PROC::MATCHTRANSFER_CBO );
   addFieldDetails( ifds::RvCode,          IFASTBP_PROC::MATCHTRANSFER_CBO );
   addFieldDetails( ifds::RvCodeDesc,      IFASTBP_PROC::MATCHTRANSFER_CBO );
   addFieldDetails( ifds::Initial,         IFASTBP_PROC::MATCHTRANSFER_CBO );
   addFieldDetails( ifds::DealDate,        IFASTBP_PROC::MATCHTRANSFER_CBO );
   addFieldDetails( ifds::DealTime,        IFASTBP_PROC::MATCHTRANSFER_CBO );
   addFieldDetails( ifds::SettleCurrency,  IFASTBP_PROC::MATCHTRANSFER_CBO );
   addFieldDetails( ifds::ExchRate,        IFASTBP_PROC::MATCHTRANSFER_CBO );
   addFieldDetails( ifds::PartnerShip,     IFASTBP_PROC::MATCHTRANSFER_CBO );
   addFieldDetails( ifds::Indc,            IFASTBP_PROC::MATCHTRANSFER_CBO );
   addFieldDetails( ifds::SeqNum,          IFASTBP_PROC::MATCHTRANSFER_CBO );
   addFieldDetails( ifds::OverrideDSCDesc, IFASTBP_PROC::MATCHTRANSFER_CBO );
   addFieldDetails( ifds::OverrideAmt,     IFASTBP_PROC::MATCHTRANSFER_CBO );
   addFieldDetails( ifds::ConfIssued,      IFASTBP_PROC::MATCHTRANSFER_CBO );
   addFieldDetails( ifds::ConfirmReq,      IFASTBP_PROC::MATCHTRANSFER_CBO );
   addFieldDetails( ifds::RecptIssued,     IFASTBP_PROC::MATCHTRANSFER_CBO );
   addFieldDetails( ifds::OnStmt,          IFASTBP_PROC::MATCHTRANSFER_CBO );
   addFieldDetails( ifds::CertRequired,    IFASTBP_PROC::MATCHTRANSFER_CBO );
   addFieldDetails( ifds::SettledBy,       IFASTBP_PROC::MATCHTRANSFER_CBO );
   addFieldDetails( ifds::SettledByDesc,   IFASTBP_PROC::MATCHTRANSFER_CBO );
   addFieldDetails( ifds::PostUnsettled,   IFASTBP_PROC::MATCHTRANSFER_CBO );
   addFieldDetails( ifds::ExpSetlGN,       IFASTBP_PROC::MATCHTRANSFER_CBO );
   addFieldDetails( ifds::ChqSupCode,      IFASTBP_PROC::MATCHTRANSFER_CBO ); 
   addFieldDetails( ifds::ChqSupCodeDesc,  IFASTBP_PROC::MATCHTRANSFER_CBO );
   addFieldDetails( ifds::GroupCode,       IFASTBP_PROC::MATCHTRANSFER_CBO );
   addFieldDetails( ifds::SrcOfAccount,    IFASTBP_PROC::MATCHTRANSFER_CBO );
   addFieldDetails( ifds::SrcOfFund,       IFASTBP_PROC::MATCHTRANSFER_CBO );
   addFieldDetails( ifds::SrcOfFundDesc,   IFASTBP_PROC::MATCHTRANSFER_CBO );
   addFieldDetails( ifds::PayType,         IFASTBP_PROC::MATCHTRANSFER_CBO );
   addFieldDetails( ifds::PayTypeDesc,     IFASTBP_PROC::MATCHTRANSFER_CBO );
   addFieldDetails( ifds::OrderTrace,      IFASTBP_PROC::MATCHTRANSFER_CBO );
   addFieldDetails( ifds::CancelBatch,     IFASTBP_PROC::MATCHTRANSFER_CBO );
   addFieldDetails( ifds::CancelTrace,     IFASTBP_PROC::MATCHTRANSFER_CBO );
   addFieldDetails( ifds::CancelUser,      IFASTBP_PROC::MATCHTRANSFER_CBO );
   addFieldDetails( ifds::SettleTrace,     IFASTBP_PROC::MATCHTRANSFER_CBO );
   addFieldDetails( ifds::SettleUser,      IFASTBP_PROC::MATCHTRANSFER_CBO );
   addFieldDetails( ifds::VerifiedBy,      IFASTBP_PROC::MATCHTRANSFER_CBO );
   addFieldDetails( ifds::Cancelled,       IFASTBP_PROC::MATCHTRANSFER_CBO );
   addFieldDetails( ifds::Remarks1,        IFASTBP_PROC::MATCHTRANSFER_CBO );
   addFieldDetails( ifds::Remarks2,        IFASTBP_PROC::MATCHTRANSFER_CBO );
   addFieldDetails( ifds::Remarks3,        IFASTBP_PROC::MATCHTRANSFER_CBO );
   addFieldDetails( ifds::OrderUser,       IFASTBP_PROC::MATCHTRANSFER_CBO );
   addFieldDetails( ifds::ProcessDate,     IFASTBP_PROC::MATCHTRANSFER_CBO );
   addFieldDetails( ifds::ModDate,         IFASTBP_PROC::MATCHTRANSFER_CBO );

   // from vw 63
   addFieldDetails( ifds::ElongName1,      IFASTBP_PROC::FUNDMASTER_LIST ); //,     SUBCLASS_PROCESS );

   addSubstituteList(ifds::RemarksLine);
   addSubstituteList(ifds::MatchTransferAttrTop);  
   addSubstituteList(ifds::MatchTransferAttrLeft); 
}

//******************************************************************************

MatchTransferProcess::~MatchTransferProcess()
{
   TRACE_DESTRUCTOR( CLASSNAME );

   delete _pMatchTransferList;
   _pMatchTransferList = NULL;
   _rpChildGI = NULL;
}

//******************************************************************************
//              Protected Methods
//******************************************************************************


//******************************************************************************

SEVERITY MatchTransferProcess::doInit()
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, DOINIT );
   SEVERITY sevRtn = SEVERE_ERROR;

   try
   {
      getParameter( MATCHTRANSFER::ACCOUNTNUM, _AccountNum );
      getParameter( MATCHTRANSFER::TRANSID, _TransId );
      getParameter( MATCHTRANSFER::ENTITYID, _EntityId );
      getParameter( pINQUIRYONLY, _InquiryOnly ); 

      _AccountNum.stripAll();
      _TransId.stripAll();

      DSTCWorkSession *dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
      if( _pMatchTransferList != NULL )
      {
         delete _pMatchTransferList;
         _pMatchTransferList = NULL;
      }
      _pMatchTransferList = new MatchTransferList( *dstcWorkSession );

      sevRtn = _pMatchTransferList->init( _TransId, I_( "N" ), NULL_STRING  );
      if( WARNING >= sevRtn )
      {
         setContainer( IFASTBP_PROC::MATCHTRANSFER_CBO, _pMatchTransferList );
      }
      else
      {
         return(GETCURRENTHIGHESTSEVERITY());
      }

      FundMasterList *_pFundMasterList;
      sevRtn = dstcWorkSession->getMgmtCo().getFundMasterList( _pFundMasterList );  // DSTC0063_VWRepeat_Record.hpp
      if( WARNING >= sevRtn )
      {
         setContainer( IFASTBP_PROC::FUNDMASTER_LIST, _pFundMasterList );
      }
      else
      {
         return(GETCURRENTHIGHESTSEVERITY());
      }

      if( _AccountNum != NULL_STRING )
      {
         MFAccount *mfAccount = NULL;
         dstcWorkSession->getMFAccount( getDataGroupId(), _AccountNum, mfAccount );

         if( mfAccount )
         {
            mfAccount->getField(ifds::ShrNum, _ShareholderNum, BF::HOST);
         }
      }
   }
   catch( ConditionException &ce )
   {
      SETCONDITIONFROMEXCEPTION( ce );
   }
   catch( ... )
   {
      throw EXCEPTIONFROMFILE(// CND::BPBASE_CONDITION, CLASSNAME, DOINIT,
                              CND::BP_ERR_UNKNOWN_EXCEPTION );
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************

E_COMMANDRETURN MatchTransferProcess::doProcess()
{  
   MAKEFRAME2( CND::BPBASE_CONDITION, CLASSNAME, DOPROCESS );
   E_COMMANDRETURN rtn = CMD_FAILURE;

   try
   {
      setParameter( MATCHTRANSFER::ACCOUNTNUM, _AccountNum );
      setParameter( MATCHTRANSFER::TRANSID, _TransId );
      setParameter( MATCHTRANSFER::SHAREHOLDERNUM, _ShareholderNum );
      setParameter( MATCHTRANSFER::ENTITYID, _EntityId );
      setParameter( pINQUIRYONLY, _InquiryOnly);

      rtn = invokeCommand( this, CMD_GUI_MATCHTRANSFER, getProcessType(), false,
                           &_rpChildGI );
   }
   catch( ConditionException &ce )
   {
      SETCONDITIONFROMEXCEPTION( ce );
   }
   catch( ... )
   {
      throw EXCEPTIONFROMFILE(// CND::BPBASE_CONDITION, CLASSNAME, DOINIT,
                              CND::BP_ERR_UNKNOWN_EXCEPTION );
   }
   return(rtn);
}

//******************************************************************************
void MatchTransferProcess::doGetField(
                                     const GenericInterface *rpGICaller,
                                     const BFContainerId& idContainer,
                                     const BFFieldId& idField,
                                     const BFDataGroupId& idDataGroup,
                                     DString &strValueOut,
                                     bool bFormatted ) const
{  
//CP20030319   switch( idContainer )
//CP20030319   {
//CP20030319      case MATCHTRANSFER_CBO :

   if( IFASTBP_PROC::MATCHTRANSFER_CBO == idContainer )
   {
      if( idField == ifds::Currency )
      {
         BFObjIter iter(*_pMatchTransferList, BF::HOST);
         if( !iter.end() )
            dynamic_cast<MatchTransferDetails *>(iter.getObject())->getCurrency( idDataGroup, strValueOut );

      }
      if( idField == ifds::NetAmt || idField == ifds::GrossAmt || idField == ifds::Commission )
      {
         BFObjIter iter(*_pMatchTransferList, BF::HOST);
         if( !iter.end() )
            dynamic_cast<MatchTransferDetails *>(iter.getObject())->getField( idField, strValueOut, idDataGroup, true );

      }
//CP20030319         break;

//CP20030319      default:
   }
   else
   {
      assert( 0 );   
      THROWFROMFILE2( CND::BPBASE_CONDITION, 
                      CLASSNAME, GETFIELD, CND::BP_ERR_INVALID_METHOD_CALL );

//CP20030319   }
   }

}

//**********************************************************************
void *MatchTransferProcess::getPtrForContainer( const BFContainerId& idContainer, const BFDataGroupId& idDataGroup )
{
   MAKEFRAME2( CND::BPBASE_CONDITION, CLASSNAME, I_( "getPtrForContainer" ) );

   void *ptr = NULL;

   try
   {
//CP20030319      switch( idContainer )
//CP20030319      {
//CP20030319         case MATCHTRANSFER_CBO:
      if( IFASTBP_PROC::MATCHTRANSFER_CBO == idContainer )
      {
         {

            ptr = _pMatchTransferList;

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
bool MatchTransferProcess::doModelessSetFocus( GenericInterface *rpGICaller )
{  // This is implemented to pass set focus on to child dialog.

   bool bRtn = false;
   if( _rpChildGI && isValidModelessInterface( _rpChildGI ) )
   {
      bRtn = _rpChildGI->refresh( this, NULL );
      bRtn = _rpChildGI->modelessSetFocus( rpGICaller );
   }
   return(bRtn);
}

//******************************************************************************

bool MatchTransferProcess::doModelessChildComplete( const Command &cmd )
{
   // End when GUI ends
   return(cmd.getKey() == CMD_GUI_MATCHTRANSFER);
}
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/MatchTransferProcess.cpp-arc  $
// 
//    Rev 1.10   May 11 2004 14:26:26   FENGYONG
// PET1046 FN1 - transfer-switch -Rel57
// 
//    Rev 1.9   Mar 21 2003 17:44:46   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.8   Mar 03 2003 14:08:06   KOVACSRO
// Added parameter InquiryOnly
// 
//    Rev 1.7   Oct 09 2002 23:53:28   PURDYECH
// PVCS Database Conversion
// 
//    Rev 1.6   Aug 29 2002 16:45:06   SMITHDAV
// Condition split.
// 
//    Rev 1.5   Aug 29 2002 12:54:30   SMITHDAV
// ClientLocale and typed field changes.
// 
//    Rev 1.4   22 May 2002 18:24:40   PURDYECH
// BFData Implementation
// 
//    Rev 1.3   27 Mar 2002 19:55:18   PURDYECH
// Process/WindowFactory overhaul
// 
//    Rev 1.2   Sep 14 2001 16:44:48   ZHANGCEL
// Fixed the bug regarding Admin/Date crash
// 
//    Rev 1.1   Sep 07 2001 16:25:58   ZHANGCEL
// Added new fields 
// 
//    Rev 1.0   Aug 16 2001 13:36:06   ZHANGCEL
// Initial revision.
 * 
 */
