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
// ^FILE   : JEntityProcess.cpp
// ^AUTHOR :  Zijian Ying
// ^DATE   : 04/19/1999
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : JEntityProcess
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include "stdafx.h"
#include "jentityprocess.hpp"
#include <ifastcbo\jentitylist.hpp>
#include <ifastcbo\Entity.hpp>


#include "jentityprocessincludes.h"
#include "etrackheader.h"
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_JENTITY;
#include <bfproc\concreteprocesscreator.hpp>
static ConcreteProcessCreator< JEntityProcess > processCreator( CMD_BPROC_JENTITY );

namespace
{
   // Trace literals
   const I_CHAR *CLASSNAME = I_( "JEntityProcess" );
   const I_CHAR *EntityId = I_( "EntityID" );

}

namespace ENTITYLIT //entity search literals
{
   const I_CHAR * const pACCOUNTNUM = I_( "AccountNum" );



}  

namespace CND
{
   extern CLASS_IMPORT const long BP_ERR_UNKNOWN_EXCEPTION;
}

//******************************************************************************
//              Public Methods
//******************************************************************************

//CP20030319JEntityProcess::JEntityProcess() : 
JEntityProcess::JEntityProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: AbstractProcess( pGIC, pGIParent, rCommand ),
_rpChildGI( NULL )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );

   addContainer( IFASTBP_PROC::ENTITY_LIST, false, BF::NullContainerId, true,I_( "EntityList" ) );

   addFieldDetails( ifds::Salutation, IFASTBP_PROC::ENTITY_LIST  );
   addFieldDetails( ifds::LastName, IFASTBP_PROC::ENTITY_LIST );
   addFieldDetails( ifds::FirstName, IFASTBP_PROC::ENTITY_LIST );
   addFieldDetails( ifds::BirthLastName, IFASTBP_PROC::ENTITY_LIST );
   addFieldDetails( ifds::BirthFirstName, IFASTBP_PROC::ENTITY_LIST );
   addFieldDetails( ifds::DofBirth, IFASTBP_PROC::ENTITY_LIST );
   addFieldDetails( ifds::Gender,	IFASTBP_PROC::ENTITY_LIST );
   addFieldDetails( ifds::SIN,	IFASTBP_PROC::ENTITY_LIST );
   addFieldDetails( ifds::OccupationCode,	IFASTBP_PROC::ENTITY_LIST );
   addFieldDetails( ifds::OccupationDesc,	IFASTBP_PROC::ENTITY_LIST );
   addFieldDetails( ifds::LanguageCode,	IFASTBP_PROC::ENTITY_LIST );
   addFieldDetails( ifds::Language,	IFASTBP_PROC::ENTITY_LIST ); 
   addFieldDetails( ifds::HomePhone,	IFASTBP_PROC::ENTITY_LIST );
   addFieldDetails( ifds::BusinessPhone,	IFASTBP_PROC::ENTITY_LIST );
   addFieldDetails( ifds::BusinessExt,	IFASTBP_PROC::ENTITY_LIST );
   addFieldDetails( ifds::BusinessFax,	IFASTBP_PROC::ENTITY_LIST );
   addFieldDetails( ifds::Telex,	IFASTBP_PROC::ENTITY_LIST );
   addFieldDetails( ifds::Email,	IFASTBP_PROC::ENTITY_LIST );
   addFieldDetails( ifds::DofDeath,	IFASTBP_PROC::ENTITY_LIST );
   addFieldDetails( ifds::DofDeathNotice,	IFASTBP_PROC::ENTITY_LIST );
   addFieldDetails( ifds::EffectiveDate,	IFASTBP_PROC::ENTITY_LIST );
   addFieldDetails( ifds::ProcessDate,	IFASTBP_PROC::ENTITY_LIST );
   addFieldDetails( ifds::ModDate,	IFASTBP_PROC::ENTITY_LIST );
   addFieldDetails( ifds::Username,	IFASTBP_PROC::ENTITY_LIST );
   addFieldDetails( ifds::ModUser,	IFASTBP_PROC::ENTITY_LIST );
   addFieldDetails( ifds::HomeFax,	IFASTBP_PROC::ENTITY_LIST );
   addFieldDetails( ifds::EntityIdentityVer,	IFASTBP_PROC::ENTITY_LIST );
   addFieldDetails( ifds::EntityIdentityRid,	IFASTBP_PROC::ENTITY_LIST );
   addFieldDetails( ifds::HomePhoneCntry,	IFASTBP_PROC::ENTITY_LIST );
   addFieldDetails( ifds::HomePhoneArea,	IFASTBP_PROC::ENTITY_LIST );
   addFieldDetails( ifds::BusinessPhoneCntry,	IFASTBP_PROC::ENTITY_LIST );
   addFieldDetails( ifds::BusinessPhoneArea,	IFASTBP_PROC::ENTITY_LIST );
   addFieldDetails( ifds::HomeFaxCntry,	IFASTBP_PROC::ENTITY_LIST );
   addFieldDetails( ifds::HomeFaxArea,	IFASTBP_PROC::ENTITY_LIST );
   addFieldDetails( ifds::BusFaxCntry,	IFASTBP_PROC::ENTITY_LIST );
   addFieldDetails( ifds::BusFaxArea,	IFASTBP_PROC::ENTITY_LIST );
   //addFieldDetails( ifds::EmployeeClass,	IFASTBP_PROC::ENTITY_LIST );
   //addFieldDetails( ifds::Nationality,	IFASTBP_PROC::ENTITY_LIST );
   //addFieldDetails( ifds::OtherOccupation,	IFASTBP_PROC::ENTITY_LIST );
   //addFieldDetails( ifds::SpouseEntityID,	IFASTBP_PROC::ENTITY_LIST );
   //addFieldDetails( ifds::BirthPlace,	IFASTBP_PROC::ENTITY_LIST );

}

//******************************************************************************

JEntityProcess::~JEntityProcess()
{
   TRACE_DESTRUCTOR( CLASSNAME );

   _rpChildGI = NULL;
}

//******************************************************************************
//              Protected Methods
//******************************************************************************

SEVERITY JEntityProcess::doInit()
{ 
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, DOINIT );
   SEVERITY sevRtn = SEVERE_ERROR;

   try
   {
      DString dstrEntityID;
      getParameter( EntityId, dstrEntityID );	
		dstrEntityID.strip().stripLeading( '0' );
		DSTCWorkSession* pWorkSession = NULL;
		pWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
		if( pWorkSession )
		{
			Entity*  pEntity;
         Entity::bUsedByEntityAlone = false;
			sevRtn = pWorkSession->getEntity( getDataGroupId(), dstrEntityID, pEntity );
			if( WARNING >= sevRtn )
			{
				setContainer( IFASTBP_PROC::ENTITY_LIST, pEntity );
			}
			else
			{
				return(GETCURRENTHIGHESTSEVERITY());
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
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************

bool JEntityProcess::doGetData(
                              GenericInterface * ,
                              BFData * 
                              ) const
{
//	_pEntityList->getMore();
   return(true);
}

//******************************************************************************

//******************************************************************************

E_COMMANDRETURN JEntityProcess::doProcess()
{  
   MAKEFRAME2( CND::BPBASE_CONDITION, CLASSNAME, DOPROCESS );
   E_COMMANDRETURN rtn = CMD_FAILURE;

   rtn = CMD_MODELESS_INPROCESS;
   return(rtn);
}

//******************************************************************************


//******************************************************************************
//              Private Methods
//******************************************************************************

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/JEntityProcess.cpp-arc  $
 // 
 //    Rev 1.13   Mar 10 2005 17:00:42   yingbaol
 // PET1171,FN01: EU Saving Entity update
 // 
 //    Rev 1.12   Sep 28 2004 10:30:20   YINGBAOL
 // PET1145 FN01 Entity update
 // 
 //    Rev 1.11   Mar 21 2003 17:43:42   PURDYECH
 // BFDataGroupId/BFContainerId changeover
 // 
 //    Rev 1.10   Oct 09 2002 23:53:24   PURDYECH
 // PVCS Database Conversion
 // 
 //    Rev 1.9   Aug 29 2002 16:45:02   SMITHDAV
 // Condition split.
 // 
 //    Rev 1.8   Aug 29 2002 12:54:28   SMITHDAV
 // ClientLocale and typed field changes.
 // 
 //    Rev 1.7   22 May 2002 18:24:34   PURDYECH
 // BFData Implementation
 // 
 //    Rev 1.6   27 Mar 2002 19:55:14   PURDYECH
 // Process/WindowFactory overhaul
 // 
 //    Rev 1.5   03 May 2001 14:05:32   SMITHDAV
 // Session management restructuring.
 // 
 //    Rev 1.4   Jan 23 2001 15:17:46   YINGBAOL
 // add eTrack
 // 
 //    Rev 1.3   15 Dec 2000 12:43:36   PURDYECH
 // Use precompiled header stdafx.h.
 // Removed unnecessary header files.
 // 
 //    Rev 1.2   Aug 13 2000 12:28:00   YINGZ
 // call JEntityList
 // 
 //    Rev 1.1   Aug 11 2000 14:23:02   FENGYONG
 // use AccountEntityXref instead of EntityList
 *
 */
