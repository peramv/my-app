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
// ^FILE   : HistoricalAccountProcess.cpp
// ^AUTHOR : Chin Hsu
// ^DATE   : 10/28/1999
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : HistoricalAccountProcess
//    This class manages the Historical Account information.
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include "stdafx.h"
#include "historicalaccountprocess.hpp"
#include <ifastcbo\historicalaccountlist.hpp>
#include "historicalaccountprocessincludes.h"
extern IFASTBP_LINKAGE const I_CHAR* CMD_GUI_HISTORICAL_ACCOUNT;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_HISTORICAL_ACCOUNT;
#include <bfproc\concreteprocesscreator.hpp>
static ConcreteProcessCreator< HistoricalAccountProcess > processCreator( CMD_BPROC_HISTORICAL_ACCOUNT );

namespace
{
   // Trace literals
   const I_CHAR * const CLASSNAME = I_( "HistoricalAccountProcess" );
   const I_CHAR * const ACCOUNT_NUM = I_( "AccountNum" );
   const I_CHAR * const NAME = I_( "Name" );
}

namespace CND
{  // Conditions used
   extern CLASS_IMPORT const long BP_ERR_UNKNOWN_EXCEPTION;
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId AcctType;
   extern CLASS_IMPORT const BFTextFieldId TaxType;
   extern CLASS_IMPORT const BFTextFieldId RecipientType;
   extern CLASS_IMPORT const BFTextFieldId Currency;
   extern CLASS_IMPORT const BFTextFieldId InterCode;
   extern CLASS_IMPORT const BFTextFieldId CountryCode;
   extern CLASS_IMPORT const BFTextFieldId AcctStatus;
}
//******************************************************************************
//              Public Methods
//******************************************************************************

//CP20030319HistoricalAccountProcess::HistoricalAccountProcess() : 
HistoricalAccountProcess::HistoricalAccountProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: AbstractProcess( pGIC, pGIParent, rCommand )
, _pHistoricalAccountList( 0 ),
_rpChildGI( 0 )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );

   addContainer( IFASTBP_PROC::HISTORICAL_ACCOUNT_LIST, true );

   addFieldDetails( ifds::ModDate, IFASTBP_PROC::HISTORICAL_ACCOUNT_LIST );
   addFieldDetails( ifds::FieldLabel, IFASTBP_PROC::HISTORICAL_ACCOUNT_LIST );
   addFieldDetails( ifds::PreviousDisp, IFASTBP_PROC::HISTORICAL_ACCOUNT_LIST, SUBCLASS_PROCESS );
   addFieldDetails( ifds::ModUser, IFASTBP_PROC::HISTORICAL_ACCOUNT_LIST );
}

//******************************************************************************

HistoricalAccountProcess::~HistoricalAccountProcess()
{
   TRACE_DESTRUCTOR( CLASSNAME );

   delete _pHistoricalAccountList;
}

//******************************************************************************
//              Protected Methods
//******************************************************************************

void HistoricalAccountProcess::doGetField(
                                         const GenericInterface *rpGICaller,
                                         const BFContainerId& idContainer,
                                         const BFFieldId& idField,
                                         const BFDataGroupId& idDataGroup,
                                         DString &strValueOut,
                                         bool bFormatted
                                         ) const
{
   if( idContainer == IFASTBP_PROC::HISTORICAL_ACCOUNT_LIST )
   {
      if( idField == ifds::PreviousDisp )
      {
         BFAbstractCBO *rpPtr = const_cast<HistoricalAccountProcess *>(this)->getCBOItem( idContainer, idDataGroup );
         DString strTmp;

         rpPtr->getField( ifds::PreviousDisp, strValueOut, idDataGroup, 
                          bFormatted );
         // Get associated label to find substitute sets
         rpPtr->getField( ifds::FieldLabel, strTmp, idDataGroup );
         if( strTmp == I_("XRefNum") )   // If the field XRefNum has been changed to XrefNum, the corresponding 
            strTmp = I_("XrefNum");     // change should take in substitute set HistoricalAccountFieldSet !!!!
         const BFFieldId& idField = BFFieldId::getId( strTmp );
         const BFDataFieldProperties* pProps = BFDataFieldProperties::get( idField );
         const BFSubstitutionSet* pSubSet = pProps->getSubstitutionSet(ClientLocaleContext::get());
         if( NULL != pSubSet && pSubSet->size() != 0 )
         {
            if( pSubSet->isKey( strValueOut ) )
            {
               strValueOut = pSubSet->getValue( strValueOut );
            }
            else if( pSubSet->isValue( strValueOut ) )
            {
               strValueOut = pSubSet->getKey( strValueOut );
            }
         }
      }
   }
}

//******************************************************************************

SEVERITY HistoricalAccountProcess::doInit()
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, DOINIT );
   SEVERITY sevRtn = SEVERE_ERROR;

   try
   {
      DString strAccountNumber;
      DString strName;
      getParameter( ACCOUNT_NUM, strAccountNumber );     
      AccountNumber = strAccountNumber.stripAll();
      getParameter( NAME, s_Name );
      _pHistoricalAccountList = new HistoricalAccountList( *getBFWorkSession() );
      sevRtn = _pHistoricalAccountList->init( AccountNumber );
      if( WARNING >= sevRtn )
      {  //register list with base
         setContainer( IFASTBP_PROC::HISTORICAL_ACCOUNT_LIST, _pHistoricalAccountList );
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

E_COMMANDRETURN HistoricalAccountProcess::doProcess()
{  
   MAKEFRAME2( CND::BPBASE_CONDITION, CLASSNAME, DOPROCESS );
   E_COMMANDRETURN rtn = CMD_FAILURE;

   setParameter( NAME, s_Name );
   setParameter( ACCOUNT_NUM, AccountNumber );

   try
   {
      rtn = invokeCommand( this, CMD_GUI_HISTORICAL_ACCOUNT, 
                           getProcessType(), isModal(), &_rpChildGI );
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

bool HistoricalAccountProcess::doModelessSetFocus(
                                                 GenericInterface *rpGICaller )
{  // This is implemented to pass set focus on to child dialog.
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, DOMODELESSSETFOCUS );
   SEVERITY sevRtn = SEVERE_ERROR;
   bool bRtn = false;
   try
   {
      assert( _rpChildGI && isValidModelessInterface( _rpChildGI ) );

      DString strNewAccountNumber;
      DString strName;
      getParameter( ACCOUNT_NUM, strNewAccountNumber );
      setParameter( ACCOUNT_NUM, strNewAccountNumber );
      getParameter( NAME, strName );
      setParameter( NAME, strName );
      if( strNewAccountNumber != AccountNumber )
      {
         delete _pHistoricalAccountList;
         AccountNumber = strNewAccountNumber.stripAll();
         _pHistoricalAccountList = new HistoricalAccountList( *getBFWorkSession() );
         sevRtn = _pHistoricalAccountList->init( AccountNumber );
         if( WARNING >= sevRtn )
         {  //register list with base
            setContainer( IFASTBP_PROC::HISTORICAL_ACCOUNT_LIST, _pHistoricalAccountList );
         }
         bRtn = _rpChildGI->refresh( this, I_( "FullRefresh" ) );
      }
      else
      {
         if( !( bRtn = _rpChildGI->refresh( this, I_( "PartialRefresh" ) ) ) )
         {
            return(bRtn);  // false
         }
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

bool HistoricalAccountProcess::doModelessChildComplete(const Command &cmd)
{
   // End when GUI ends   
   return( cmd.getKey() == CMD_GUI_HISTORICAL_ACCOUNT );
}

//******************************************************************************

bool HistoricalAccountProcess::doMoreRecordsExist( GenericInterface *rpGICaller, const BFContainerId& idSearch )
{
   return(rpGICaller == NULL || _pHistoricalAccountList == NULL ? false : 
          _pHistoricalAccountList->moreRecordsExist());
}

//******************************************************************************

SEVERITY HistoricalAccountProcess::performSearch( GenericInterface *rpGI, const BFContainerId& idSearch, 
                                                  E_SEARCHACTION eSearchAction )
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, I_( "doMore" ));
   DString NextKey;
   SEVERITY severity = SEVERE_ERROR;

   try
   {
      if( _pHistoricalAccountList != NULL && rpGI != NULL )
      {
         severity = _pHistoricalAccountList->search(eSearchAction == SEARCH_START);
         if( WARNING >= severity )
         {  //register list with base
            setContainer( IFASTBP_PROC::HISTORICAL_ACCOUNT_LIST, _pHistoricalAccountList );
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
      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, DOMODELESSSETFOCUS,
                      CND::BP_ERR_UNKNOWN_EXCEPTION );
   }
   return(GETCURRENTHIGHESTSEVERITY());
}
//*******************************************************************************
bool HistoricalAccountProcess::doRefresh(
                                        GenericInterface *rpGICaller,
                                        const I_CHAR *szOriginalCommand
                                        )
{
   setParameter( NAME, s_Name );
   setParameter( ACCOUNT_NUM, AccountNumber );
   return(_rpChildGI->refresh( this, I_( "FullRefresh" ) ));
}
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/HistoricalAccountProcess.cpp-arc  $
 * 
 *    Rev 1.14   Mar 21 2003 17:40:48   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.13   Oct 09 2002 23:53:16   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.12   Aug 29 2002 16:44:56   SMITHDAV
 * Condition split.
 * 
 *    Rev 1.11   Aug 29 2002 12:54:22   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.10   Jul 05 2002 08:56:26   PURDYECH
 * Fixed include files
 * Removed commented-out code.
 * 
 *    Rev 1.9   22 May 2002 18:24:18   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.8   27 Mar 2002 19:54:54   PURDYECH
 * Process/WindowFactory overhaul
 * 
 *    Rev 1.7   Jun 07 2001 10:56:44   YINGBAOL
 * fix refresh
 * 
 *    Rev 1.6   03 May 2001 14:05:26   SMITHDAV
 * Session management restructuring.
 * 
 *    Rev 1.5   15 Dec 2000 12:43:30   PURDYECH
 * Use precompiled header stdafx.h.
 * Removed unnecessary header files.
 * 
 *    Rev 1.4   Aug 08 2000 12:08:14   ZHANGCEL
 * Fixed the bug about XRefNum 
 * 
 *    Rev 1.3   Aug 02 2000 15:32:02   BUZILA
 * "locale" changes
 * 
 *    Rev 1.2   Jun 13 2000 18:20:32   DT24433
 * new Infra interfaces use ClientLocale
 * 
 *    Rev 1.1   Mar 15 2000 15:26:04   DT24433
 * removed substitute lists and added doGetField to handle getting display values for DBR::PreviousDisp
 * 
 */
