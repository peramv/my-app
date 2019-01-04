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
// ^FILE   : TaxRatesProcess.cpp
// ^AUTHOR : Dan Petolescu
// ^DATE   : 12/13/1999
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : TaxRatesProcess
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include "stdafx.h"
#include "taxratesprocess.hpp"
#include <ifastcbo\taxrateslist.hpp>
#include "taxratesprocessincludes.h"
#include <ifastcbo\mfaccount.hpp>
extern IFASTBP_LINKAGE const I_CHAR* CMD_GUI_TAXRATES;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_TAXRATES;
#include <bfproc\concreteprocesscreator.hpp>
static ConcreteProcessCreator< TaxRatesProcess > processCreator( CMD_BPROC_TAXRATES );

namespace
{
   // Trace literals
   const I_CHAR *CLASSNAME = I_( "TaxRatesProcess" );
   const I_CHAR * const PERFORMSEARCH = I_( "performSearch" );
}

namespace CND
{
   extern CLASS_IMPORT const long BP_ERR_UNKNOWN_EXCEPTION;
}

//******************************************************************************
//              Public Methods
//******************************************************************************

//CP20030319TaxRatesProcess::TaxRatesProcess() : 
TaxRatesProcess::TaxRatesProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: AbstractProcess( pGIC, pGIParent, rCommand )
, _pTaxRatesList( NULL ),
_rpChildGI( NULL )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );

//   addSubstituteList( DBR::TaxRatesHeadingSet );

   addContainer( IFASTBP_PROC::TAXRATES_LIST, true, BF::NullContainerId, false );

   addFieldDetails( ifds::TaxJurisCode, IFASTBP_PROC::TAXRATES_LIST );
   addFieldDetails( ifds::TaxJurisName, IFASTBP_PROC::TAXRATES_LIST );
   addFieldDetails( ifds::EffectiveDate, IFASTBP_PROC::TAXRATES_LIST );
   addFieldDetails( ifds::FedIncRate, IFASTBP_PROC::TAXRATES_LIST );
   addFieldDetails( ifds::FedRedRate, IFASTBP_PROC::TAXRATES_LIST );
   addFieldDetails( ifds::ProvIncRate, IFASTBP_PROC::TAXRATES_LIST );
   addFieldDetails( ifds::ProvRedRate, IFASTBP_PROC::TAXRATES_LIST );
   addFieldDetails( ifds::ProcessDate, IFASTBP_PROC::TAXRATES_LIST );
   addFieldDetails( ifds::LowerBound, IFASTBP_PROC::TAXRATES_LIST );
   addFieldDetails( ifds::UpperBound, IFASTBP_PROC::TAXRATES_LIST );
   addFieldDetails( ifds::PerPenRate, IFASTBP_PROC::TAXRATES_LIST );
   addFieldDetails( ifds::LumpPenRate, IFASTBP_PROC::TAXRATES_LIST );
   addFieldDetails( ifds::PAmtThreasholdCode, IFASTBP_PROC::TAXRATES_LIST );
   addFieldDetails( ifds::PAmtThreasholdDesc, IFASTBP_PROC::TAXRATES_LIST );
   addFieldDetails( ifds::Username, IFASTBP_PROC::TAXRATES_LIST );
   addFieldDetails( ifds::ModDate, IFASTBP_PROC::TAXRATES_LIST );
   addFieldDetails( ifds::ModName, IFASTBP_PROC::TAXRATES_LIST );
   addFieldDetails( ifds::TaxRateRid, IFASTBP_PROC::TAXRATES_LIST );

}

//******************************************************************************

TaxRatesProcess::~TaxRatesProcess()
{
   TRACE_DESTRUCTOR( CLASSNAME );

   delete _pTaxRatesList;
   _pTaxRatesList = NULL;
   _rpChildGI = NULL;
}

//******************************************************************************
//              Protected Methods
//******************************************************************************

bool TaxRatesProcess::doCancel(
                              GenericInterface *rpGI
                              )
{
   TRACE_METHOD( CLASSNAME, DOCANCEL );
   bool bRtn = true;

   return(bRtn); 
}


SEVERITY TaxRatesProcess::doInit()
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, DOINIT );
   SEVERITY sevRtn = SEVERE_ERROR;

   try
   {
      _pTaxRatesList = new TaxRatesList( *getBFWorkSession() );

      sevRtn = _pTaxRatesList->init();
      if( WARNING >= sevRtn )
      {
         setContainer( IFASTBP_PROC::TAXRATES_LIST, _pTaxRatesList );
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
      throw EXCEPTIONFROMFILE( CND::BP_ERR_UNKNOWN_EXCEPTION );
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************

bool TaxRatesProcess::doOk( GenericInterface *rpGI )
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, DOOK );

   return(true);
}

//******************************************************************************

E_COMMANDRETURN TaxRatesProcess::doProcess()
{  
   MAKEFRAME2( CND::BPBASE_CONDITION, CLASSNAME, DOPROCESS );
   E_COMMANDRETURN rtn = CMD_FAILURE;

   try
   {
      rtn = invokeCommand( this, CMD_GUI_TAXRATES, PROC_NO_TYPE, isModal(), &_rpChildGI );
   }
   catch( ConditionException &ce )
   {
      SETCONDITIONFROMEXCEPTION( ce );
   }
   catch( ... )
   {
      throw EXCEPTIONFROMFILE( CND::BP_ERR_UNKNOWN_EXCEPTION );
   }

   return(rtn);
}

//******************************************************************************
bool TaxRatesProcess::doMoreRecordsExist(
                                        GenericInterface *rpGICaller,
                                        const BFContainerId& idContainer 
                                        )
{
   return( _pTaxRatesList->doMoreRecordsExist() );//getFixedData().getElementValue( I_("MoreAvailable") ) )== I_("Y");
}

//******************************************************************************
SEVERITY TaxRatesProcess::performSearch( GenericInterface *rpGI, const BFContainerId& idSearch, E_SEARCHACTION eSearchAction )
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, PERFORMSEARCH );
   SEVERITY sevRtn = SEVERE_ERROR;

   try
   {
      if( _pTaxRatesList != NULL )
      {
         sevRtn = _pTaxRatesList->getMore();
         setContainer( IFASTBP_PROC::TAXRATES_LIST, NULL );
         setContainer( IFASTBP_PROC::TAXRATES_LIST, _pTaxRatesList );
      }
   }
   catch( ConditionException &ce )
   {
      SETCONDITIONFROMEXCEPTION( ce );
   }
   catch( ... )
   {
      assert( 0 );
      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, PERFORMSEARCH, CND::BP_ERR_UNKNOWN_EXCEPTION );
   }
   return(sevRtn); 
}

//******************************************************************************
bool TaxRatesProcess::doGetData(
                               GenericInterface * ,
                               BFData * 
                               ) const
{
   _pTaxRatesList->getMore();
   return(true);
}

//******************************************************************************
bool TaxRatesProcess::doModelessSetFocus( GenericInterface *rpGICaller )
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

bool TaxRatesProcess::doModelessChildComplete( const Command &cmd )
{
   DString dslCommandKey;
   dslCommandKey = cmd.getKey();
   if( dslCommandKey == CMD_GUI_TAXRATES )
      return(true);           // We do not want to be destroyed by a son process
   else
      return(false);          // All done, ready to be self destructed
}

//******************************************************************************
//              Private Methods
//******************************************************************************

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/TaxRatesProcess.cpp-arc  $
 * 
 *    Rev 1.9   Mar 21 2003 17:49:00   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.8   Oct 09 2002 23:53:40   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.7   Aug 29 2002 16:45:18   SMITHDAV
 * Condition split.
 * 
 *    Rev 1.6   Aug 29 2002 12:54:42   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.5   22 May 2002 18:25:06   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.4   27 Mar 2002 19:55:44   PURDYECH
 * Process/WindowFactory overhaul
 * 
 *    Rev 1.3   03 May 2001 14:05:44   SMITHDAV
 * Session management restructuring.
 * 
 *    Rev 1.2   15 Dec 2000 12:43:54   PURDYECH
 * Use precompiled header stdafx.h.
 * Removed unnecessary header files.
 * 
 *    Rev 1.1   Mar 22 2000 09:02:46   PETOLESC
 * Added Tax Rates and RESP dialogs.
 * 
 *    Rev 1.0   Feb 15 2000 10:59:38   SMITHDAV
 * Initial revision.
// 
//    Rev 1.2   Jan 17 2000 12:10:12   PETOLESC
// Corrected minor bug related to modeless process.
// 
//    Rev 1.1   Dec 30 1999 10:10:36   PETOLESC
// Cleaned the code.
// 
//    Rev 1.0   Dec 29 1999 17:24:32   PETOLESC
// Initial revision.
 * 
 *
 */
