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
// ^FILE   : AccountInquiryProcess.cpp
// ^AUTHOR : Adrian Vasile
// ^DATE   : 16/03/2001
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : AccountInquiryProcess
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include "stdafx.h"
#include "accountinquiryprocess.hpp"
#include <ifastcbo\accountinquirylist.hpp>
#include "accountinquiryprocessincludes.h"
#include "etrackheader.h"

extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_ACCOUNT_INQUIRY;

#include <bfproc\concreteprocesscreator.hpp>
static ConcreteProcessCreator< AccountInquiryProcess > processCreator( CMD_BPROC_ACCOUNT_INQUIRY );

namespace
{
   // Trace literals
   const I_CHAR *CLASSNAME = I_( "AccountInquiryProcess" );
}

namespace CND
{
   extern CLASS_IMPORT const long BP_ERR_UNKNOWN_EXCEPTION;
}

namespace ACCINQUIRYLIT //entity search literals
{
   const I_CHAR * const FIRSTNAME = I_( "TXFirstName" );
   const I_CHAR * const LASTNAME = I_( "TXLastName" );
   const I_CHAR * const SIN_NO = I_( "TXSin_no" );
   const I_CHAR * const SHRNUM = I_( "TXShrNum" );
   const I_CHAR * const ACCOUNTNUM = I_( "TXAccountNum" );
   const I_CHAR * const ALTACCOUNTNUM = I_( "AltAccountNum" );
   const I_CHAR * const BROKERCODE = I_( "txBrokerCode" );
   const I_CHAR * const BRANCHCODE = I_( "txBranchCode" );
   const I_CHAR * const SLSREP = I_( "txSlsrep" );
   const I_CHAR * const CORPINDIV = I_( "CorpIndiv" );
   const I_CHAR * const NEXTORPREVIOUS = I_( "NextOrPrevious" );
   const I_CHAR * const NEXT_KEY = I_( "NextKey" );
   const I_CHAR * const INTERMCODE = I_( "IntermCode" );
   const I_CHAR * const INTERMACCT = I_( "InterAccount" );
}

//******************************************************************************
//              Public Methods
//******************************************************************************

AccountInquiryProcess::AccountInquiryProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: AbstractProcess( pGIC, pGIParent, rCommand )
, _pAccountInquiryList( NULL )
, _rpChildGI( NULL )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );

   addContainer( IFASTBP_PROC::ACCOUNT_INQUIRY_LIST,         true,  BF::NullContainerId, false, I_( "AccountInquiryList" ) );
   addContainer( IFASTBP_PROC::ACCOUNT_INQUIRY_LIST_DETAILS, false, BF::NullContainerId, false, I_( "AccountInquiryListDetails" ) );

// from list vw 118
   addFieldDetails( ifds::AccountNum,       IFASTBP_PROC::ACCOUNT_INQUIRY_LIST );
   addFieldDetails( ifds::SIN,              IFASTBP_PROC::ACCOUNT_INQUIRY_LIST );
   addFieldDetails( ifds::LastName,         IFASTBP_PROC::ACCOUNT_INQUIRY_LIST );
   addFieldDetails( ifds::FirstName,        IFASTBP_PROC::ACCOUNT_INQUIRY_LIST );
   addFieldDetails( ifds::AcctType,         IFASTBP_PROC::ACCOUNT_INQUIRY_LIST );
   addFieldDetails( ifds::AcctDesignation,  IFASTBP_PROC::ACCOUNT_INQUIRY_LIST );
   addFieldDetails( ifds::AcctStatus,       IFASTBP_PROC::ACCOUNT_INQUIRY_LIST );
   addFieldDetails( ifds::AltAccount,       IFASTBP_PROC::ACCOUNT_INQUIRY_LIST );
   addFieldDetails( ifds::BrokerCode,       IFASTBP_PROC::ACCOUNT_INQUIRY_LIST );
   addFieldDetails( ifds::SalesRepCode,     IFASTBP_PROC::ACCOUNT_INQUIRY_LIST );
   addFieldDetails( ifds::InTrustJoint,     IFASTBP_PROC::ACCOUNT_INQUIRY_LIST );
   addFieldDetails( ifds::InTrustJointName, IFASTBP_PROC::ACCOUNT_INQUIRY_LIST );
   addFieldDetails( ifds::TaxType,          IFASTBP_PROC::ACCOUNT_INQUIRY_LIST );
   addFieldDetails( ifds::IntermCode,       IFASTBP_PROC::ACCOUNT_INQUIRY_LIST );
   addFieldDetails( ifds::InterAccount,     IFASTBP_PROC::ACCOUNT_INQUIRY_LIST );

   addFieldDetails( ifds::TotalRecords,     IFASTBP_PROC::ACCOUNT_INQUIRY_LIST_DETAILS, SUBCLASS_PROCESS );

}

//******************************************************************************

AccountInquiryProcess::~AccountInquiryProcess()
{
   TRACE_DESTRUCTOR( CLASSNAME );

   if( _pAccountInquiryList )
   {
      delete _pAccountInquiryList;
      _pAccountInquiryList = NULL;
   }
   _rpChildGI = NULL;
}


//******************************************************************************

SEVERITY AccountInquiryProcess::doInit()
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTBP_CONDITION, CLASSNAME, DOINIT );
   SEVERITY sevRtn = SEVERE_ERROR;
   try
   {
      DString firstname, lastname, sinno, shrnum, acctnum, altacctnum;
      DString dstrTrack,dstrActivity, NextOrPrevious, NextKey;
      DString BrokerCode,BranchCode,Slsrep, corpIndiv, intermCode, intermAcct;

      getParameter( ACCINQUIRYLIT::FIRSTNAME, firstname );
      getParameter( ACCINQUIRYLIT::LASTNAME, lastname );
      getParameter( ACCINQUIRYLIT::SIN_NO, sinno );
      getParameter( ACCINQUIRYLIT::SHRNUM, shrnum );
      getParameter( ACCINQUIRYLIT::ACCOUNTNUM, acctnum );
      getParameter( ACCINQUIRYLIT::ALTACCOUNTNUM, altacctnum );
      getParameter( ACCINQUIRYLIT::BROKERCODE, BrokerCode ); 
      getParameter( ACCINQUIRYLIT::BRANCHCODE, BranchCode );
      getParameter( ACCINQUIRYLIT::SLSREP, Slsrep );
      getParameter( ACCINQUIRYLIT::CORPINDIV, corpIndiv );
      getParameter( ACCINQUIRYLIT::INTERMCODE, intermCode );
      getParameter( ACCINQUIRYLIT::INTERMACCT, intermAcct );
      getParameter( ACCINQUIRYLIT::NEXTORPREVIOUS, NextOrPrevious );
      getParameter( ACCINQUIRYLIT::NEXT_KEY, NextKey );
      getParameter( ETRACK::TRACK, dstrTrack );
      getParameter( ETRACK::ACTIVITY, dstrActivity );
      if( dstrTrack.strip() == NULL_STRING )dstrTrack = I_("N");

      acctnum.strip();
      NextOrPrevious.strip();
      if( NextOrPrevious == NULL_STRING )
         NextOrPrevious = I_( "Y" );
      NextKey.strip();
      firstname.strip();
      lastname.strip();
      sinno.strip();
      shrnum.strip();
      altacctnum.strip();
      BrokerCode.strip();
      BranchCode.strip();
      Slsrep.strip();
      corpIndiv.strip();
      if( corpIndiv == NULL_STRING )
         corpIndiv = I_( "N" );

      _pAccountInquiryList = new AccountInquiryList( *getBFWorkSession() );

      sevRtn = _pAccountInquiryList->init( BrokerCode, BranchCode, Slsrep, acctnum, sinno, shrnum,
                                           altacctnum, lastname, firstname, corpIndiv, NULL_STRING, intermCode, intermAcct,
                                           NextOrPrevious, NextKey, dstrTrack, dstrActivity );
      if( WARNING >= sevRtn )
      {
         setContainer( IFASTBP_PROC::ACCOUNT_INQUIRY_LIST, _pAccountInquiryList );
      }
      else
      {
         return(GETCURRENTHIGHESTSEVERITY());
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

E_COMMANDRETURN AccountInquiryProcess::doProcess()
{  
   MAKEFRAME2( CND::IFASTBP_CONDITION, CLASSNAME, DOPROCESS );
   E_COMMANDRETURN rtn = CMD_FAILURE;

   rtn = CMD_MODELESS_INPROCESS;

   return(rtn);
}

void AccountInquiryProcess::doGetField(
                                      const GenericInterface *rpGICaller,
                                      const BFContainerId& idContainer,
                                      const BFFieldId& idField,
                                      const BFDataGroupId& idDataGroup,
                                      DString &strValueOut,
                                      bool bFormatted
                                      ) const
{  
   if( idField == ifds::TotalRecords && idContainer == IFASTBP_PROC::ACCOUNT_INQUIRY_LIST_DETAILS )
   {
      DString strTotalRecords;
      _pAccountInquiryList->getField( ifds::TotalRecords, strTotalRecords, BF::HOST, true );
      strValueOut = strTotalRecords.strip();
   }
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/AccountInquiryProcess.cpp-arc  $
// 
//    Rev 1.14   Apr 02 2003 12:19:12   PURDYECH
// Code cleanup
// 
//    Rev 1.13   Mar 21 2003 17:34:28   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.12   Oct 09 2002 23:52:58   PURDYECH
// PVCS Database Conversion
// 
//    Rev 1.11   Aug 29 2002 16:42:32   SMITHDAV
// Condition split.
// 
//    Rev 1.10   Aug 29 2002 12:54:08   SMITHDAV
// ClientLocale and typed field changes.
// 
//    Rev 1.9   22 May 2002 18:23:46   PURDYECH
// BFData Implementation
// 
//    Rev 1.8   27 Mar 2002 19:54:28   PURDYECH
// Process/WindowFactory overhaul
// 
//    Rev 1.7   Nov 12 2001 14:51:46   VASILEAD
// Added search by iterm info
// 
//    Rev 1.6   Aug 22 2001 10:20:20   VASILEAD
// Added InTrustJointName
// 
//    Rev 1.5   Aug 16 2001 17:42:34   VASILEAD
// Added tracking support
// 
//    Rev 1.4   Jul 25 2001 14:09:50   YINGBAOL
// sync. up version 1.2.1.0
// 
//    Rev 1.3   03 May 2001 14:05:14   SMITHDAV
// Session management restructuring.
// 
//    Rev 1.2   Mar 26 2001 10:16:20   VASILEAD
// Added TaxType to the FieldDetails
// 
//    Rev 1.1   Mar 18 2001 18:18:04   VASILEAD
// Fixes for UAT release
// 
//    Rev 1.0   Mar 16 2001 15:05:48   VASILEAD
// Initial revision.
 * 
 *    Rev 1.20   Feb 28 2001 11:24:02   VASILEAD
 * Added string descriptions for containers
 * 
 */
