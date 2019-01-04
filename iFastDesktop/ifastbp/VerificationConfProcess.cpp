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
// ^FILE   : VerificationConfProcess.cpp
// ^AUTHOR : 
// ^DATE   : 03/09/1999
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : VerificationConfProcess
//    This class manages the confirmation view for an update sent through AWD eMail.
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include "stdafx.h"
#include <time.h>
#include <fstream>
#include <ifastcbo\verificationconf.hpp>
#include "verificationconfprocess.hpp"
#include "verificationconfprocessincludes.h"
#include "etrackheader.h"
bool CLASS_EXPORT RIPProcessing = false;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_VERIFICATIONCONF;
#include <bfproc\concreteprocesscreator.hpp>
static ConcreteProcessCreator< VerificationConfProcess > processCreator( CMD_BPROC_VERIFICATIONCONF );

namespace
{
   // Trace literals
   const I_CHAR * const CLASSNAME = I_( "VerificationConfProcess" );
}


namespace CND
{  // Conditions used
   extern CLASS_IMPORT const long BP_ERR_UNKNOWN_EXCEPTION;
//   extern CLASS_IMPORT const long BP_ERR_NO_DATA_AREA;
}

//******************************************************************************
//              Public Methods
//******************************************************************************

//CP20030319VerificationConfProcess::VerificationConfProcess() : 
VerificationConfProcess::VerificationConfProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: AbstractProcess( pGIC, pGIParent, rCommand )
, _pVerificationConf( NULL )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );

   addContainer( IFASTBP_PROC::VERIFICATIONCONF_CBO, false );

   addFieldDetails( ifds::BODate, IFASTBP_PROC::VERIFICATIONCONF_CBO );
   addFieldDetails( ifds::BOTime, IFASTBP_PROC::VERIFICATIONCONF_CBO );
   addFieldDetails( ifds::BOZone, IFASTBP_PROC::VERIFICATIONCONF_CBO );
   addFieldDetails( ifds::FIDate, IFASTBP_PROC::VERIFICATIONCONF_CBO );
   addFieldDetails( ifds::FITime, IFASTBP_PROC::VERIFICATIONCONF_CBO );
   addFieldDetails( ifds::FIZone, IFASTBP_PROC::VERIFICATIONCONF_CBO );
   addFieldDetails( ifds::ConfNum, IFASTBP_PROC::VERIFICATIONCONF_CBO );

}

//******************************************************************************

VerificationConfProcess::~VerificationConfProcess()
{
   TRACE_DESTRUCTOR( CLASSNAME );

   _rpChildGI = NULL;
   delete _pVerificationConf;
   _pVerificationConf = NULL;

}

//******************************************************************************
//              Protected Methods
//******************************************************************************

SEVERITY VerificationConfProcess::doInit()
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, DOINIT );
   SEVERITY sevRtn = SEVERE_ERROR;

   try
   {
      /*
        DString temp;
        getParameter( VERIFICATIONCONFLT::SHRNUM_TRACKSHR, temp );
        _params.insert( PARAM_MAP_VALUE_TYPE( VERIFICATIONCONFLT::SHRNUM_TRACKSHR, temp ) );
        getParameter( VERIFICATIONCONFLT::ACCOUNTNUM_TRACKACT, temp );
        _params.insert( PARAM_MAP_VALUE_TYPE( VERIFICATIONCONFLT::ACCOUNTNUM_TRACKACT, temp ) );
  */
      DString temp;
      getParameter( VERIFICATIONCONF_INPUT, temp );
      DString dstrTrack,dstrActivity;
      getParameter( ETRACK::TRACK, dstrTrack );
      getParameter( ETRACK::ACTIVITY, dstrActivity );
      if( dstrTrack.strip() == NULL_STRING )dstrTrack = I_("N");


      _pVerificationConf = new VerificationConf( *getBFWorkSession() );
      sevRtn = _pVerificationConf->init( temp,dstrTrack,dstrActivity );
      if( WARNING >= sevRtn )
      {
         setContainer( IFASTBP_PROC::VERIFICATIONCONF_CBO, _pVerificationConf );
      }
// Activate when RIP is to be turned on.
      if( RIPProcessing )
         RIPFileOut();
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

E_COMMANDRETURN VerificationConfProcess::doProcess()
{  
   MAKEFRAME2( CND::BPBASE_CONDITION, CLASSNAME, DOPROCESS );
   E_COMMANDRETURN rtn = CMD_FAILURE;

   rtn = CMD_MODELESS_INPROCESS;
   return(rtn);
}

void VerificationConfProcess::RIPFileOut ()
{
   wchar_t wcPath[_MAX_PATH];
   _wgetcwd (wcPath,_MAX_PATH);   
   DString dstraPath(wcPath);
   DString dstrField,dstrValue,dstrInStream;   
   getParameter ( VERIFICATIONCONF_INPUT, dstrInStream );
   dstrField = I_("NAME");
   ExtractValue ( dstrField , dstrValue, dstrInStream );
   DStringA dstrA = dstraPath + I_("\\template\\") + dstrValue + I_(".tem");   
   std::ifstream ifInFile (dstrA.c_str());
   _pVerificationConf->getField (ifds::ConfNum, dstrField, getDataGroupId()/* was --> VERIFICATIONCONF_CBO ??? */, true);
   DStringA dstrB = dstraPath + I_("\\RIP\\") + dstrValue + dstrField + I_(".out");
   std::ofstream ofOutFile ( dstrB.c_str() );  //NET used to have ios::out as parm2
   char in;
   bool isVar = false;  
   dstrField = I_("");
   if( ifInFile && ofOutFile )
   {
      while( ifInFile.get(in) )
      {
         if( (!isVar) && (in == '<') )
            isVar = true;
         else if( (isVar) && (in == '<') )
         {
            DStringA dstrTemp = I_("<") + dstrField;
            ofOutFile << dstrTemp.c_str();
            dstrField = I_("");            
         }
         else if( (isVar) && (in == '>') )
         {
            ExtractValue ( dstrField.upperCase(), dstrValue, dstrInStream );
            DStringA dstrTemp = dstrValue;
            ofOutFile << dstrTemp.c_str();
            dstrField = I_("");
            isVar = false;
         }
         else if( isVar )
            dstrField = dstrField + I_CHAR(in);
         else
            ofOutFile << in;
      }
   }
}

void VerificationConfProcess::ExtractValue( DString &dstrField, DString &dstrValue, DString &dstrInStream)
{
   int start, finish;   
   if( dstrField == I_("CONFNUM") )
      _pVerificationConf->getField (ifds::ConfNum, dstrValue, getDataGroupId()/* was --> VERIFICATIONCONF_CBO ??? */, true);
   else if( dstrField == I_("BODATE") )
      _pVerificationConf->getField (ifds::BODate, dstrValue, getDataGroupId()/* was --> VERIFICATIONCONF_CBO ??? */, true);
   else if( dstrField == I_("BOTIME") )
      _pVerificationConf->getField (ifds::BOTime, dstrValue, getDataGroupId()/* was --> VERIFICATIONCONF_CBO ??? */, true);
   else if( dstrField == I_("BOZONE") )
      _pVerificationConf->getField (ifds::BOZone, dstrValue, getDataGroupId()/* was --> VERIFICATIONCONF_CBO ??? */, true);
   else if( dstrField == I_("FIDATE") )
      _pVerificationConf->getField (ifds::FIDate, dstrValue, getDataGroupId()/* was --> VERIFICATIONCONF_CBO ??? */, true);
   else if( dstrField == I_("FITIME") )
      _pVerificationConf->getField (ifds::FITime, dstrValue, getDataGroupId()/* was --> VERIFICATIONCONF_CBO ??? */, true);
   else if( dstrField == I_("FIZONE") )
      _pVerificationConf->getField (ifds::FIZone, dstrValue, getDataGroupId()/* was --> VERIFICATIONCONF_CBO ??? */, true);
   else
   {
      start = dstrInStream.find('=', dstrInStream.find(dstrField)) + 1;
      finish = dstrInStream.find(';', start);
      dstrValue = dstrInStream.substr (start,finish-start);
   }
}

//******************************************************************************
//******************************************************************************
//              Private Methods
//******************************************************************************

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/VerificationConfProcess.cpp-arc  $
 // 
 //    Rev 1.16   Nov 14 2004 14:23:06   purdyech
 // PET910 - .NET Conversion
 // 
 //    Rev 1.15   Mar 21 2003 17:50:00   PURDYECH
 // BFDataGroupId/BFContainerId changeover
 // 
 //    Rev 1.14   Mar 11 2003 13:50:00   PURDYECH
 // Fixes to help the DataGroupId source code converters work more smoothly.
 // 
 //    Rev 1.13   Mar 09 2003 15:56:48   PURDYECH
 // Small fixes around DataGroupIds and ContainerIds.
 // 
 //    Rev 1.12   Oct 09 2002 23:53:42   PURDYECH
 // PVCS Database Conversion
 // 
 //    Rev 1.11   Aug 29 2002 16:45:20   SMITHDAV
 // Condition split.
 // 
 //    Rev 1.10   Aug 29 2002 12:54:46   SMITHDAV
 // ClientLocale and typed field changes.
 // 
 //    Rev 1.9   22 May 2002 18:25:22   PURDYECH
 // BFData Implementation
 // 
 //    Rev 1.8   27 Mar 2002 19:56:24   PURDYECH
 // Process/WindowFactory overhaul
 // 
 //    Rev 1.7   03 May 2001 14:05:46   SMITHDAV
 // Session management restructuring.
 // 
 //    Rev 1.6   Jan 31 2001 16:05:34   YINGBAOL
 // to prevent  track para from being empty 
 // 
 //    Rev 1.5   Jan 23 2001 15:18:06   YINGBAOL
 // add eTrack
 // 
 //    Rev 1.4   15 Dec 2000 12:43:58   PURDYECH
 // Use precompiled header stdafx.h.
 // Removed unnecessary header files.
 // 
 //    Rev 1.3   Nov 24 2000 14:52:36   HSUCHIN
 // Added RIP Processing output.  Output is template driven
 // 
 //    Rev 1.2   Aug 08 2000 13:44:12   YINGZ
 // add VerificationStringProcessor
 // 
 //    Rev 1.1   Aug 03 2000 14:41:54   VASILEAD
 // Added tracking support to VerifConf
 // 
 //    Rev 1.0   Jul 26 2000 09:36:40   VASILEAD
 // Initial revision.
 * 
 *    Rev 1.3   Jun 28 2000 12:01:46   VASILEAD
 * Adapted to the new views
 * 
 *    Rev 1.2   Mar 30 2000 15:47:36   FENGYONG
 * For error handle
 * 
 *    Rev 1.1   Mar 24 2000 12:22:56   POPESCUS
 * Make things happen for Vision
// 
//    Rev 1.4   Mar 23 2000 11:44:24   FENGYONG
// fix
// 
//    Rev 1.3   Mar 13 2000 11:26:12   FENGYONG
// Fix Bug
// 
//    Rev 1.2   Mar 10 2000 16:18:48   FENGYONG
// fix bug
// 
//    Rev 1.1   Feb 29 2000 15:28:06   FENGYONG
// Add Current Date
// 
//    Rev 1.0   Nov 24 1999 09:21:36   FENGYONG
// Initial revision.
 * 
 */


