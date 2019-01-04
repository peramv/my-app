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
//    Copyright 2000 by DST Systems, Inc.
//
//******************************************************************************
//
// ^FILE   : FileInquiryProcess.cpp
// ^AUTHOR : Celia Zhang
// ^DATE   : 2 /11/2004
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : FileInquiryProcess
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include "stdafx.h"
#include "FileInquiryProcess.hpp"
#include <ifastcbo\MessageEnvelopelist.hpp>
#include <ifastcbo\MessageEnvelope.hpp>
#include <ifastcbo\MsgEventList.hpp>
#include "FileInquiryProcessInclude.h"
#include <ifastcbo\mgmtco.hpp>
#include <ifastcbo\dstcommonfunction.hpp>

extern IFASTBP_LINKAGE const I_CHAR* CMD_GUI_FILE_INQUIRY;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_FILE_INQUIRY;
#include <bfproc\concreteprocesscreator.hpp>
static ConcreteProcessCreator< FileInquiryProcess > processCreator( CMD_BPROC_FILE_INQUIRY );

namespace 
{
   // Trace literals
   const I_CHAR * const CLASSNAME					= I_( "FileInquiryProcess" );
	const I_CHAR * const PERFORMSEARCH           = I_( "performSearch" ); 
   const I_CHAR * const Y = I_( "Y" );
   const I_CHAR * const N = I_( "N" );
}

namespace CND
{
   extern CLASS_IMPORT const long BP_ERR_UNKNOWN_EXCEPTION;
}

//******************************************************************************
//              Public Methods
//******************************************************************************
FileInquiryProcess::FileInquiryProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: AbstractProcess( pGIC, pGIParent, rCommand )
, _pMessageEnvelopeList( NULL )
/*, _pMsgEventList(NULL)*/
, _rpChildGI( NULL )

{
	TRACE_CONSTRUCTOR(CLASSNAME, NULL_STRING );

	addContainer( IFASTBP_PROC::MSG_ENVELOPE_LIST, true,//repeatable
									BF::NullContainerId, false, // un-updatable
									I_("MessageEnvelopeList"));

	addContainer( IFASTBP_PROC::MSG_EVENT_LIST, true,//repeatable
									IFASTBP_PROC::MSG_ENVELOPE_LIST, false, //un-updatable
									I_("MsgEventList"));
	 
	addFieldDetails( ifds::NetworkID,		IFASTBP_PROC::MSG_ENVELOPE_LIST );
	addFieldDetails( ifds::FileName,			IFASTBP_PROC::MSG_ENVELOPE_LIST );
	addFieldDetails( ifds::EnvelopeStatus, IFASTBP_PROC::MSG_ENVELOPE_LIST );
	addFieldDetails( ifds::ProcessDate,		IFASTBP_PROC::MSG_ENVELOPE_LIST );
	addFieldDetails( ifds::ProcessTime,		IFASTBP_PROC::MSG_ENVELOPE_LIST );
	addFieldDetails( ifds::EnvelopeID,		IFASTBP_PROC::MSG_ENVELOPE_LIST );
	
	addFieldDetails( ifds::EventCode, IFASTBP_PROC::MSG_EVENT_LIST );
	addFieldDetails( ifds::EventType, IFASTBP_PROC::MSG_EVENT_LIST );
	addFieldDetails( ifds::EventText, IFASTBP_PROC::MSG_EVENT_LIST);
}



//******************************************************************************

FileInquiryProcess::~FileInquiryProcess()
{
   TRACE_DESTRUCTOR( CLASSNAME )
}

//******************************************************************************
//              Protected Methods
//******************************************************************************

SEVERITY FileInquiryProcess::doInit()
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, DOINIT );
   SEVERITY sevRtn = SEVERE_ERROR;

   try
   {
     processParameters();
	  DSTCWorkSession *pDSTCWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
	  if( pDSTCWorkSession->getMessageEnvelopeList( _dstrNetWorkId, _dstrFileName, _dstrStartDate,
			_dstrEndDate, _pMessageEnvelopeList, getDataGroupId()) 
			<= WARNING && _pMessageEnvelopeList )
      {
		  setContainer( IFASTBP_PROC::MSG_ENVELOPE_LIST, _pMessageEnvelopeList );
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
   return GETCURRENTHIGHESTSEVERITY();
}


//******************************************************************************

E_COMMANDRETURN FileInquiryProcess::doProcess()
{  
   MAKEFRAME2( CND::BPBASE_CONDITION, CLASSNAME, DOPROCESS );
   E_COMMANDRETURN rtn = CMD_FAILURE;

   try
   {
      
      rtn = invokeCommand( this, CMD_GUI_FILE_INQUIRY, getProcessType(), true, &_rpChildGI );
		
      
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
bool FileInquiryProcess::doModelessSetFocus( GenericInterface *rpGICaller )
{  // This is implemented to pass set focus on to child dialog.
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, DOMODELESSSETFOCUS );
   SEVERITY sevRtn = SEVERE_ERROR;

   bool bRtn = false;
	try
   {
      assert(_rpChildGI && isValidModelessInterface(_rpChildGI));
      if( isValidModelessInterface( _rpChildGI ) )
      {  
			// Only if child still exists            
			//setContainer( IFASTBP_PROC::MSG_ENVELOPE_LIST, NULL );
			//setContainer( IFASTBP_PROC::MSG_EVENT_LIST, NULL );
 
			bRtn = _rpChildGI->refresh( this, NULL );
         bRtn = _rpChildGI->modelessSetFocus( rpGICaller );
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

   return(bRtn);
}

//******************************************************************************
bool FileInquiryProcess::doModelessChildComplete( const Command &cmd )
{
   return( cmd.getKey() == CMD_GUI_FILE_INQUIRY );
}

//******************************************************************************
bool FileInquiryProcess::doRefresh( GenericInterface *rpGICaller, const I_CHAR *szOriginalCommand )
{
   TRACE_METHOD( CLASSNAME, DOREFRESH );  
   return(_rpChildGI->refresh( this, NULL ));

}
//******************************************************************************
void *FileInquiryProcess::getPtrForContainer( const BFContainerId &idContainer,
                                                  const BFDataGroupId &idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2 (CND::BPBASE_CONDITION, CLASSNAME, I_("getPtrForContainer"));
	void *ptr = NULL;
	
	try
	{
 		if (IFASTBP_PROC::MSG_EVENT_LIST == idContainer)
		{						
         MessageEnvelope* rpMessageEnvelope = dynamic_cast <MessageEnvelope*> 
               (getCBOItem (IFASTBP_PROC::MSG_ENVELOPE_LIST, idDataGroup));
          
			if (rpMessageEnvelope)
         {
             MsgEventList *pMsgEventList = NULL;
            if ( rpMessageEnvelope->getMsgEventList (pMsgEventList, idDataGroup) <= WARNING &&
                 pMsgEventList)
            {
               ptr = pMsgEventList;
            }
         }
		}
	}
   catch (ConditionException &ce)
   {
      SETCONDITIONFROMEXCEPTION( ce );
   }
   catch (...)
   {
      assert( 0 );
      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, DOINIT, CND::BP_ERR_UNKNOWN_EXCEPTION );
   }
	return ptr;
}

//******************************************************************************
SEVERITY FileInquiryProcess::processParameters()
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTBP_CONDITION, CLASSNAME, I_("processParameters"));
   _dstrNetWorkId = _dstrFileName = NULL_STRING;
   getParameter(FILESEARCH::NETWORKID, _dstrNetWorkId);
   getParameter(FILESEARCH::FILENAME, _dstrFileName);
   getParameter(FILESEARCH::STARTDATE, _dstrStartDate);
   getParameter(FILESEARCH::ENDDATE, _dstrEndDate);
	_dstrNetWorkId.stripAll().upperCase();
	_dstrFileName.stripAll().upperCase();
  
    return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
bool FileInquiryProcess::doMoreRecordsExist(GenericInterface *rpGICaller,
   const BFContainerId &idSearch)
{
	 if( rpGICaller == NULL )
			return(false);
    return (_pMessageEnvelopeList == NULL) ? false : _pMessageEnvelopeList->doMoreRecordsExist();
}
   

//******************************************************************************
SEVERITY FileInquiryProcess::performSearch( GenericInterface *rpGI, const BFContainerId& idSearch, 
   E_SEARCHACTION eSearchAction )
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, PERFORMSEARCH );
   SEVERITY sevRtn = SEVERE_ERROR;

   try
   {
      if( _pMessageEnvelopeList != NULL )
      {
         sevRtn = _pMessageEnvelopeList->getMore();
      }
   }
   catch( ConditionException &ce )
   {
      SETCONDITIONFROMEXCEPTION( ce );
   }
   catch( ... )
   {
      assert( 0 );
      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, 
         PERFORMSEARCH, CND::BP_ERR_UNKNOWN_EXCEPTION );
   }
   return(sevRtn); 
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/FileInquiryProcess.cpp-arc  $
// 
//    Rev 1.0   Feb 24 2005 17:17:56   ZHANGCEL
// Initial revision.
// 
*/
