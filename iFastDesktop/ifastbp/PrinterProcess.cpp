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
// ^FILE   : PrinterProcess.cpp
// ^AUTHOR : 
// ^DATE   : Dec 8, 2002
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : PrinterProcess
//   
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include "stdafx.h"
#include "printerprocess.hpp"
#include "printerprocessincludes.h"

extern IFASTBP_LINKAGE const I_CHAR* CMD_GUI_PRINTER_LIST;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_PRINTER_LIST;

#include <bfproc\concreteprocesscreator.hpp>
static ConcreteProcessCreator< PrinterProcess > processCreator( CMD_BPROC_PRINTER_LIST );

namespace
{
   // Trace literals
   const I_CHAR * const CLASSNAME               = I_( "ReportViewProcess" );      
}

namespace CND
{  // Conditions used
   extern CLASS_IMPORT const long BP_ERR_UNKNOWN_EXCEPTION;
}

//******************************************************************************
// Constructor - Container and field details are initialized here.
//******************************************************************************

//CP20030319PrinterProcess::PrinterProcess() : 
PrinterProcess::PrinterProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: AbstractProcess( pGIC, pGIParent, rCommand )
, _rpChildGI ( NULL )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING ); 
   addContainer( IFASTBP_PROC::PRINTER_LIST, true, BF::NullContainerId, false ); 
   addFieldDetails( ifds::PrinterName, IFASTBP_PROC::PRINTER_LIST );   
   addFieldDetails( ifds::Description, IFASTBP_PROC::PRINTER_LIST );
}

//******************************************************************************
// Destructor 
//******************************************************************************

PrinterProcess::~PrinterProcess()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************
// @returns SEVERITY.
//******************************************************************************

SEVERITY PrinterProcess::doInit()
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTBP_CONDITION, CLASSNAME, DOINIT );
   getParameter ( PRINTER::COMPANY, _dstrCompanyId );
   getParameter ( PRINTER::LOCAL, _dstrLocal );
   return(NO_CONDITION);
}

//******************************************************************************
// Function which get the container pointer on demand.
// @param   const BFContainerId& idContainer - Id to the container.
//          const BFDataGroupId& idDataGroup - group id.
// @returns void.
//******************************************************************************

void *PrinterProcess::getPtrForContainer(
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
      // RSP Contribution List
//CP20030319         case PRINTER::PRINTER_LIST:
      if( IFASTBP_PROC::PRINTER_LIST == idContainer )
      {
         {            
            PrinterList* pPrinterList = NULL;
            DSTCUserSession &pDSTCUserSession = dynamic_cast<DSTCUserSession &>(getBFSession()->getUserSession());
            pDSTCUserSession.getPrinterList( pPrinterList, idDataGroup );
            if( pPrinterList )
               ptr = pPrinterList;
            else
            {
               pDSTCUserSession.createPrinterList( _dstrCompanyId, pPrinterList, idDataGroup );
               ptr = pPrinterList;
            }
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
// Function which tells the generic interface container that the modeless child
// has been destroyed.
// @param   const Command &cmd - cmd indicating the child is destroyed.
// @returns bool - true when successful.
//******************************************************************************

bool PrinterProcess::doModelessChildComplete( const Command &cmd )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTBP_CONDITION, CLASSNAME, DOMODELESSCHILDCOMPLETE );

   // End when GUI ends
   return( cmd.getKey() == CMD_GUI_PRINTER_LIST );
}

//******************************************************************************
// This functions starts the Reports Dialog
// @returns E_COMMANDRETURN.
//******************************************************************************

E_COMMANDRETURN PrinterProcess::doProcess()
{  
   MAKEFRAME2( CND::IFASTBP_CONDITION, CLASSNAME, DOPROCESS );
   E_COMMANDRETURN rtn = CMD_FAILURE;

   try
   {
      setParameter ( PRINTER::LOCAL, _dstrLocal );
      rtn = invokeCommand( this, CMD_GUI_PRINTER_LIST, getProcessType(),
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

SEVERITY PrinterProcess::ok2( GenericInterface *rpGI )
{
   MAKEFRAME2( CND::IFASTBP_CONDITION, CLASSNAME, OK2 );
   DString dstrPrinterName;
   const_cast <PrinterProcess*> (this)->getField(this, IFASTBP_PROC::PRINTER_LIST, ifds::PrinterName, dstrPrinterName, false);
   setParameter ( PRINTER::NAME, dstrPrinterName );
   return(NO_CONDITION);
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/PrinterProcess.cpp-arc  $
// 
//    Rev 1.1   Mar 21 2003 17:46:00   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.0   Dec 08 2002 22:10:40   HSUCHIN
// Initial Revision
 */
