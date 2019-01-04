//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by International Financial Data Services,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2004 by International Financial Data Services
//
//
//******************************************************************************
//
// ^FILE   : FileSearchProcess.cpp
// ^AUTHOR : Celia Zhang
// ^DATE   : 02/17/2005
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : FileSearchProcess
//    
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include "stdafx.h"


#include <ifastcbo\FileSearchCriteria.hpp>
#include "FileSearchProcess.hpp"
#include "FileSearchProcessinclude.h"
#include "FileInquiryProcessInclude.h"
#include <ifastcbo\MessageEnvelopelist.hpp>

#include <ifastcbo\dstcworksession.hpp>



extern IFASTBP_LINKAGE const I_CHAR* CMD_GUI_FILE_SEARCH;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_FILE_SEARCH;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_FILE_INQUIRY;

#include <bfproc\concreteprocesscreator.hpp>
static ConcreteProcessCreator< FileSearchProcess > processCreator( CMD_BPROC_FILE_SEARCH );

namespace CND
{  // Conditions used
   extern CLASS_IMPORT const long BP_ERR_UNKNOWN_EXCEPTION;
}

namespace
{
   // Trace literals
   const I_CHAR *CLASSNAME             = I_( "FileSearchProcess" );
   const I_CHAR * const PERFORMSEARCH  = I_( "performSearch" );   


   const I_CHAR * const YES            = I_( "Y" );
   const I_CHAR * const NO             = I_( "N" );
   const I_CHAR * const YES_STRING     = I_( "Yes" );
   const I_CHAR * const NO_STRING      = I_( "No" );

}
namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId  NetworkID;
	extern CLASS_IMPORT const BFTextFieldId  FileName;
	extern CLASS_IMPORT const BFDateFieldId  StartDate;
	extern CLASS_IMPORT const BFDateFieldId  EndDate;
}

namespace UAF
{
	extern CLASS_IMPORT I_CHAR * const FILE_SEARCH;
}

//******************************************************************************
//              Public Methods
//******************************************************************************

//CP20030319FileSearchProcess::FileSearchProcess() : 
FileSearchProcess::FileSearchProcess (GenericInterfaceContainer* pGIC, 
   GenericInterface* pGIParent, const Command& rCommand)
: AbstractProcess( pGIC, pGIParent, rCommand)
, _rpChildGI( NULL )
{
   TRACE_CONSTRUCTOR( CLASSNAME, "" );

   //add containers
   addContainer( IFASTBP_PROC::CRITERIA, 
      false, BF::NullContainerId, true, I_("Criteria") );
  // addContainer( IFASTBP_PROC::MSG_ENVELOPE_LIST, 
      //true, IFASTBP_PROC::CRITERIA, false, I_("MessageEnvelopList") );
   
   //CRITERIA fields
   addFieldDetails( ifds::NetworkID,						IFASTBP_PROC::CRITERIA );
   addFieldDetails( ifds::FileName,							IFASTBP_PROC::CRITERIA );
   addFieldDetails( ifds::StartDate,						IFASTBP_PROC::CRITERIA );
   addFieldDetails( ifds::EndDate,							IFASTBP_PROC::CRITERIA );
}

//******************************************************************************

FileSearchProcess::~FileSearchProcess()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************
//              Protected Methods
//******************************************************************************

SEVERITY FileSearchProcess::doInit()
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, DOINIT );
	SEVERITY sevRtn = SEVERE_ERROR;
   try
   {
	  DSTCWorkSession *pDSTCWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
	  if( pDSTCWorkSession->getFileSearchCriteria( pFileSearchCriteria, getDataGroupId() ) 
			<= WARNING && pFileSearchCriteria )
     {
		  setContainer( IFASTBP_PROC::CRITERIA, pFileSearchCriteria );
	  }
	}


   catch(ConditionException& ce)
   {
      SETCONDITIONFROMEXCEPTION(ce);
   }
   catch(...)
   {
      assert(0);
      THROWFROMFILE2(CND::BPBASE_CONDITION, CLASSNAME, DOINIT, 
         CND::BP_ERR_UNKNOWN_EXCEPTION);
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************

E_COMMANDRETURN FileSearchProcess::doProcess()
{  
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, DOPROCESS );
   E_COMMANDRETURN rtn = CMD_FAILURE;
   try
   {
      rtn = invokeCommand( this, CMD_GUI_FILE_SEARCH, getProcessType(),
                           isModal(), &_rpChildGI );
   }
   catch( ConditionException &ce )
   {
      //assert( 0 );
      SETCONDITIONFROMEXCEPTION( ce );
   }
   catch( ... )
   {
      //assert( 0 );
      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, DOPROCESS, CND::BP_ERR_UNKNOWN_EXCEPTION );
   }
   return(rtn);
}

//******************************************************************************
void *FileSearchProcess::getPtrForContainer (const BFContainerId& idContainer, 
                                              const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTBP_CONDITION, CLASSNAME, I_("getPtrForContainer") );

   void *ptr = NULL;
   DSTCWorkSession* dstcWorkSession = 
      dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
	
   try
   {
      if (IFASTBP_PROC::CRITERIA == idContainer)
      {
         //FileSearchCriteria* pFileSearchCriteria = NULL;

         if (dstcWorkSession->getFileSearchCriteria (pFileSearchCriteria, idDataGroup ) <= WARNING)
         {
            ptr = pFileSearchCriteria;
         }
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

SEVERITY FileSearchProcess::ok2( GenericInterface *rpGICaller )
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, I_("ok2") );
   //there is nothing to be committed to the host; reset the whole thing here
   reset(rpGICaller, IFASTBP_PROC::CRITERIA);
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************

SEVERITY FileSearchProcess::performSearch (
   GenericInterface *rpGICaller, 
   const BFContainerId& idSearch, 
   E_SEARCHACTION eSearchAction )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTBP_CONDITION, CLASSNAME, PERFORMSEARCH );
	
   E_COMMANDRETURN CmdRet = CMD_FAILURE;
	
   const BFDataGroupId& idDataGroup = getDataGroupId ();
   try
   {
      if (eSearchAction == SEARCH_START)
      {
			DString dstrNetWorkId, dstrFileName, dstrStartDate, dstrEndDate;
			getField(this, idSearch, ifds::NetworkID, dstrNetWorkId, false);
			setParameter(FILESEARCH::NETWORKID, dstrNetWorkId.strip());

			getField(this, idSearch, ifds::FileName, dstrFileName, false);
			setParameter(FILESEARCH::FILENAME,  dstrFileName.strip());

			getField(this, idSearch, ifds::StartDate, dstrStartDate, false);
			setParameter(FILESEARCH::STARTDATE, dstrStartDate.strip());

			getField(this, idSearch, ifds::EndDate, dstrEndDate, false);
			setParameter(FILESEARCH::ENDDATE,   dstrEndDate.strip());

         CmdRet = invokeCommand(this, CMD_BPROC_FILE_INQUIRY, 
                  getProcessType(),true, NULL);
			
			if( CmdRet == CMD_OK )
         {
            rpGICaller->send( this, I_("CLOSE") );
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
      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, PERFORMSEARCH, CND::BP_ERR_UNKNOWN_EXCEPTION );
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
bool FileSearchProcess::doModelessChildComplete(const Command &cmd)
{
   return( cmd.getKey() == CMD_GUI_FILE_SEARCH );
}
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/FileSearchProcess.cpp-arc  $
// 
//    Rev 1.1   Feb 28 2005 17:00:28   ZHANGCEL
// PET1117 - FN 66-68  --  deal with the close button issue
// 
//    Rev 1.0   Feb 24 2005 17:18:20   ZHANGCEL
// Initial revision.
// 
*/