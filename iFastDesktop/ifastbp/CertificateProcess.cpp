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
// ^FILE   : CertificateProcess.cpp
// ^AUTHOR : 
// ^DATE   : 03/04/1999
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : CertificateProcess
//    This class manages the management company and profile selection.
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include "stdafx.h"
#include <ifastcbo\certificatelist.hpp>
#include "certificateprocess.hpp"
#include "certificateprocessincludes.h"
#include <ifastdataimpl\dse_dstcglob_vw.hpp>
#include <ifastcbo\mgmtco.hpp>
extern IFASTBP_LINKAGE const I_CHAR* CMD_GUI_CERTIFICATE;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_CERTIFICATE;
#include <bfproc\concreteprocesscreator.hpp>
static ConcreteProcessCreator< CertificateProcess > processCreator( CMD_BPROC_CERTIFICATE );

namespace CERTLIT //stands for certificate literals
{
   const I_CHAR * const INACCTNUM   = I_( "InAcctNum" );
   const I_CHAR * const INFUND      = I_( "InFund" );
   const I_CHAR * const INCERTNUM   = I_( "InCertNum" );
   const I_CHAR * const INXREFNUM   = I_( "InXrefNum" );
   const I_CHAR * const IGNOREDNF   = I_( "IgnoreDataNotFound" );
   const I_CHAR * const IGNORENOTENINFO   = I_( "IgnoreNotEnoughInfo" );
}

namespace
{
   // Trace literals
   const I_CHAR * const CLASSNAME = I_( "CertificateProcess" );
}

namespace CND
{
   extern CLASS_IMPORT const long BP_ERR_UNKNOWN_EXCEPTION;
}

//******************************************************************************
//              Public Methods
//******************************************************************************

//CP20030319CertificateProcess::CertificateProcess() : 
CertificateProcess::CertificateProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: AbstractProcess( pGIC, pGIParent, rCommand )
, _pCertificateList( NULL ),
_rpChildGI(NULL)
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );

   addContainer( IFASTBP_PROC::CERTIFICATE_LIST, true );
   addContainer( IFASTBP_PROC::FUND_DETAIL_LIST, true, BF::NullContainerId, false );

   addFieldDetails( ifds::rxAcctNum,       IFASTBP_PROC::CERTIFICATE_LIST );
   addFieldDetails( ifds::rxFundCode,      IFASTBP_PROC::CERTIFICATE_LIST );
   addFieldDetails( ifds::rxClassCode,     IFASTBP_PROC::CERTIFICATE_LIST );
   addFieldDetails( ifds::CertNumber,      IFASTBP_PROC::CERTIFICATE_LIST );
   addFieldDetails( ifds::XrefNumber,      IFASTBP_PROC::CERTIFICATE_LIST );
   addFieldDetails( ifds::StatusCode,      IFASTBP_PROC::CERTIFICATE_LIST );
   addFieldDetails( ifds::StatusDesc,      IFASTBP_PROC::CERTIFICATE_LIST );
   addFieldDetails( ifds::Units,           IFASTBP_PROC::CERTIFICATE_LIST );
   addFieldDetails( ifds::Issued,          IFASTBP_PROC::CERTIFICATE_LIST );
   addFieldDetails( ifds::IssueDate,       IFASTBP_PROC::CERTIFICATE_LIST );
   addFieldDetails( ifds::AcctUnits,       IFASTBP_PROC::CERTIFICATE_LIST );
   addFieldDetails( ifds::IssuedUnits,     IFASTBP_PROC::CERTIFICATE_LIST );
   addFieldDetails( ifds::UnIssuedUnits,   IFASTBP_PROC::CERTIFICATE_LIST );
   addFieldDetails( ifds::LastStatusCode,  IFASTBP_PROC::CERTIFICATE_LIST );
   addFieldDetails( ifds::LastStatusDesc,  IFASTBP_PROC::CERTIFICATE_LIST );
   addFieldDetails( ifds::Reported,        IFASTBP_PROC::CERTIFICATE_LIST );
   addFieldDetails( ifds::LastRptDate,     IFASTBP_PROC::CERTIFICATE_LIST );
   addFieldDetails( ifds::AddrCode,        IFASTBP_PROC::CERTIFICATE_LIST );
   addFieldDetails( ifds::AddrLine1,       IFASTBP_PROC::CERTIFICATE_LIST );
   addFieldDetails( ifds::AddrLine2,       IFASTBP_PROC::CERTIFICATE_LIST );
   addFieldDetails( ifds::AddrLine3,       IFASTBP_PROC::CERTIFICATE_LIST );
   addFieldDetails( ifds::AddrLine4,       IFASTBP_PROC::CERTIFICATE_LIST );
   addFieldDetails( ifds::AddrLine5,       IFASTBP_PROC::CERTIFICATE_LIST );
   addFieldDetails( ifds::PostalCode,      IFASTBP_PROC::CERTIFICATE_LIST );
   addFieldDetails( ifds::Comments,        IFASTBP_PROC::CERTIFICATE_LIST );
   addFieldDetails( ifds::Username,        IFASTBP_PROC::CERTIFICATE_LIST );
   addFieldDetails( ifds::ProcessDate,     IFASTBP_PROC::CERTIFICATE_LIST );
   addFieldDetails( ifds::ModUser,         IFASTBP_PROC::CERTIFICATE_LIST );
   addFieldDetails( ifds::ModDate,         IFASTBP_PROC::CERTIFICATE_LIST );
   addFieldDetails( ifds::CountryCode,     IFASTBP_PROC::CERTIFICATE_LIST );
   addFieldDetails( ifds::CountryName,     IFASTBP_PROC::CERTIFICATE_LIST );
   addFieldDetails( ifds::Address,         IFASTBP_PROC::CERTIFICATE_LIST, SUBCLASS_PROCESS );
   addFieldDetails( ifds::FundCode,        IFASTBP_PROC::FUND_DETAIL_LIST );
   addFieldDetails( ifds::ClassCode,       IFASTBP_PROC::FUND_DETAIL_LIST );   
   addFieldDetails( ifds::Baycom,          IFASTBP_PROC::FUND_DETAIL_LIST );
}

//******************************************************************************

CertificateProcess::~CertificateProcess()
{
   TRACE_DESTRUCTOR( CLASSNAME );

   _rpChildGI = NULL;
   delete _pCertificateList;
   _pCertificateList = NULL;
}

//******************************************************************************
//              Protected Methods
//******************************************************************************

SEVERITY CertificateProcess::doInit()
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, DOINIT );
   SEVERITY sevRtn = SEVERE_ERROR;

   try
   {
      DString strAcctNum;
      DString strFund;
      DString strCertNum;
      DString strXrefNum;
      DString strIgnoreDataNotFound;
      DString strIgnoreNotEnoughInfo;

      _pCertificateList = new CertificateList( *getBFWorkSession() );
      getParameter( CERTLIT::INACCTNUM, strAcctNum );
      getParameter( CERTLIT::INFUND, strFund );
      getParameter( CERTLIT::INCERTNUM, strCertNum );
      getParameter( CERTLIT::INXREFNUM, strXrefNum );
      getParameter( CERTLIT::IGNOREDNF, strIgnoreDataNotFound );
      getParameter( CERTLIT::IGNORENOTENINFO, strIgnoreNotEnoughInfo );

      //if the strIgnoreDataNotFound is NULL_STRING then ignore data not found
      sevRtn = _pCertificateList->init( strAcctNum, 
                                        strFund, strCertNum, strXrefNum, 
                                        strIgnoreDataNotFound == I_( "Y" ) || 
                                        strIgnoreDataNotFound == NULL_STRING,
                                        strIgnoreNotEnoughInfo == I_( "Y" ) ||
                                        strIgnoreNotEnoughInfo == NULL_STRING );
      if( WARNING >= sevRtn )
      {
         setContainer( IFASTBP_PROC::CERTIFICATE_LIST, _pCertificateList );
         strAcctNum.stripLeading( '0' );
         strAcctNum.strip();
         if( strAcctNum != NULL_STRING )
         {
            setGlobal( WORK_GLOBAL, ifds::LastActiveAccountNum, strAcctNum );         
            FundDetailList *_pFundDetailList;
            sevRtn = dynamic_cast<DSTCWorkSession *>(getBFWorkSession())->getMgmtCo().getFundDetailList( _pFundDetailList );
            if( WARNING >= sevRtn )
            {
               setContainer( IFASTBP_PROC::FUND_DETAIL_LIST, _pFundDetailList );
            }
         }
      }
   }
   catch( ConditionException &ce )
   {
      SETCONDITIONFROMEXCEPTION( ce );
   }
   catch( ... )
   {
      assert( 0 );
      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, DOINIT,
                      CND::BP_ERR_UNKNOWN_EXCEPTION );
   }
   return(sevRtn);
}

//******************************************************************************

E_COMMANDRETURN CertificateProcess::doProcess()
{  
   MAKEFRAME2( CND::BPBASE_CONDITION, CLASSNAME, DOPROCESS );
   E_COMMANDRETURN rtn = CMD_FAILURE;

   try
   {
      rtn = invokeCommand( this, CMD_GUI_CERTIFICATE, getProcessType(),
                           isModal(), &_rpChildGI );
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

bool CertificateProcess::doModelessSetFocus( GenericInterface *rpGICaller )
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

bool CertificateProcess::doModelessChildComplete( const Command &cmd )
{
   // End when GUI ends
   return( cmd.getKey() == CMD_GUI_CERTIFICATE );
}

//******************************************************************************
void CertificateProcess::doGetField(
                                   const GenericInterface *rpGICaller,
                                   const BFContainerId& idContainer,
                                   const BFFieldId& idField,
                                   const BFDataGroupId& idDataGroup, 
                                   DString &strValueOut,
                                   bool bFormatted
                                   ) const
{  
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, I_("doGetField") );

   if( idField == ifds::Address )
   {
      strValueOut = NULL_STRING;
      const BFAbstractCBO *rpPtr = ( const_cast < CertificateProcess* >( this ) )->getCBOItem( idContainer, idDataGroup );
      if( rpPtr )
      {

         DString tempStr = NULL_STRING;
         rpPtr->getField( ifds::AddrLine1, tempStr, idDataGroup, false );
         if( tempStr.strip() != NULL_STRING )
         {
            strValueOut += tempStr;
         };
         rpPtr->getField( ifds::AddrLine2, tempStr, idDataGroup, false );
         if( tempStr.strip() != NULL_STRING )
         {
            strValueOut += I_("\r\n");
            strValueOut += tempStr;
         };
         rpPtr->getField( ifds::AddrLine3, tempStr, idDataGroup, false );
         if( tempStr.strip() != NULL_STRING )
         {
            strValueOut += I_("\r\n");
            strValueOut += tempStr;
         };
         rpPtr->getField( ifds::AddrLine4, tempStr, idDataGroup, false );
         if( tempStr.strip() != NULL_STRING )
         {
            strValueOut += I_("\r\n");
            strValueOut += tempStr;
         };
         rpPtr->getField( ifds::AddrLine5, tempStr, idDataGroup, false );
         if( tempStr.strip() != NULL_STRING )
         {
            strValueOut += I_("\r\n");
            strValueOut += tempStr;
         };
      };
   }
}

//******************************************************************************
SEVERITY CertificateProcess::doSetField(
                                       const GenericInterface *rpGICaller, 
                                       const BFContainerId& idContainer, 
                                       const BFFieldId& idField,
                                       const BFDataGroupId& idDataGroup, 
                                       const DString& strValue, 
                                       bool bFormatted
                                       )
{  
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, I_("doSetField") );
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
const BFProperties *CertificateProcess::doGetFieldAttributes( const GenericInterface *rpGICaller, const BFContainerId& idContainer, const BFFieldId& idField, const BFDataGroupId& idDataGroup )
{
   const BFProperties * pBFProp = NULL;

   if( idField == ifds::Address )
   {
      BFAbstractCBO *rpPtr = getCBOItem( idContainer, idDataGroup );
      if( rpPtr )
         pBFProp = rpPtr->getFieldProperties( idField, idDataGroup );
   };

   return(pBFProp);
}

//******************************************************************************
SEVERITY CertificateProcess::doGetErrors( const GenericInterface *rpGICaller, const BFContainerId& idContainer,
                                          const BFFieldId& idField, const BFDataGroupId& idDataGroup, CONDITIONVECTOR &conditions ) const
{

   SEVERITY sevRtn = NO_CONDITION;
   if( idField == ifds::Address )
   {
      BFAbstractCBO *rpPtr = (const_cast < CertificateProcess *>(this))->getCBOItem( idContainer, idDataGroup );
      sevRtn = rpPtr->getErrors( idField, idDataGroup, conditions );
   }
   else
   {
      sevRtn = AbstractProcess::doGetErrors( rpGICaller, idContainer, idField, idDataGroup, conditions );
   };
   return(sevRtn);

}
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/CertificateProcess.cpp-arc  $
 * 
 *    Rev 1.13   Mar 21 2003 17:37:36   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.12   Oct 09 2002 23:53:06   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.11   Aug 29 2002 16:44:50   SMITHDAV
 * Condition split.
 * 
 *    Rev 1.10   Aug 29 2002 12:54:16   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.9   22 May 2002 18:24:08   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.8   27 Mar 2002 19:54:44   PURDYECH
 * Process/WindowFactory overhaul
 * 
 *    Rev 1.7   03 May 2001 14:05:20   SMITHDAV
 * Session management restructuring.
 * 
 *    Rev 1.6   15 Dec 2000 12:43:22   PURDYECH
 * Use precompiled header stdafx.h.
 * Removed unnecessary header files.
 * 
 *    Rev 1.5   Oct 18 2000 11:33:52   ZHANGCEL
 * crash fixed
 * 
 *    Rev 1.4   Aug 02 2000 15:31:58   BUZILA
 * "locale" changes
 * 
 *    Rev 1.3   Jun 06 2000 08:39:46   BUZILA
 * finished M3 syncup
 * 
 *    Rev 1.2   Mar 19 2000 10:37:26   HSUCHIN
 * substitution list definition removed
 * 
 *    Rev 1.1   Mar 13 2000 17:28:36   HSUCHIN
 * C2 sync up
 * 
 *    Rev 1.0   Feb 15 2000 10:59:32   SMITHDAV
 * Initial revision.
 * 
 *    Rev 1.8   Jan 17 2000 11:25:22   HSUCHIN
 * set last active account number
 * 
 *    Rev 1.7   Dec 05 1999 18:58:10   VASILEAD
 * Friday night changes( don't be so hard on us )
 * 
 *    Rev 1.6   Oct 28 1999 17:54:40   DT24433
 * removed doOk/doCancel
 * 
 *    Rev 1.5   Aug 17 1999 15:17:28   DT24433
 * removed static FieldDetails array
 * 
 *    Rev 1.4   Jul 20 1999 13:56:46   POPESCUS
 * Ignore data not found when the param is empty
 * 
 *    Rev 1.3   Jul 20 1999 11:13:56   VASILEAD
 * New conditions update
 * 
 *    Rev 1.2   Jul 14 1999 17:07:08   POPESCUS
 * Added a new param to igonore data not found
 * 
 *    Rev 1.1   Jul 08 1999 10:01:54   SMITHDAV
 * Modify revision history commaent format to old
 * style comment -- I can't seem to get new style comments to work.
 *
 */
