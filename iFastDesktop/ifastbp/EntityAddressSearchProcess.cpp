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
// ^FILE   : EntityAddressSearchProcess.cpp
// ^AUTHOR : Celia Zhang
// ^DATE   : 01/07/2005
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : EntityAddressSearchProcess
//    
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include "stdafx.h"


#include <ifastcbo\EntityAddressSearchCriteria.hpp>
#include "EntityAddressSearchProcess.hpp"
#include "EntityAddressSearchProcessincludes.h"
#include <ifastcbo\AddressEntitylist.hpp>
#include "mfcaninterprocparam.hpp"

#include <ifastcbo\dstcworksession.hpp>



extern IFASTBP_LINKAGE const I_CHAR* CMD_GUI_ENTITY_ADDRESS_SEARCH;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_ENTITY_ADDRESS_SEARCH;

#include <bfproc\concreteprocesscreator.hpp>
static ConcreteProcessCreator< EntityAddressSearchProcess > processCreator( CMD_BPROC_ENTITY_ADDRESS_SEARCH );

namespace CND
{  // Conditions used
   extern CLASS_IMPORT const long BP_ERR_UNKNOWN_EXCEPTION;
}

namespace
{
   // Trace literals
   const I_CHAR *CLASSNAME             = I_( "EntityAddressSearchProcess" );
   const I_CHAR * const PERFORMSEARCH  = I_( "performSearch" );   


   const I_CHAR * const YES            = I_( "Y" );
   const I_CHAR * const NO             = I_( "N" );
   const I_CHAR * const YES_STRING     = I_( "Yes" );
   const I_CHAR * const NO_STRING      = I_( "No" );

}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId  SearchType;
	extern CLASS_IMPORT const BFTextFieldId  SearchFirstName;
	extern CLASS_IMPORT const BFTextFieldId  SearchLastName;
	extern CLASS_IMPORT const BFDecimalFieldId AddrId;
	extern CLASS_IMPORT const BFTextFieldId  SearchPSTL;
	extern CLASS_IMPORT const BFTextFieldId  SearchCountry;
	extern CLASS_IMPORT const BFTextFieldId  EntityAddrSrch;
	extern CLASS_IMPORT const BFTextFieldId SearchFieldCriteria1;
	extern CLASS_IMPORT const BFTextFieldId SearchFieldCriteria2;

}

//******************************************************************************
//              Public Methods
//******************************************************************************

EntityAddressSearchProcess::EntityAddressSearchProcess (GenericInterfaceContainer* pGIC, 
   GenericInterface* pGIParent, const Command& rCommand)
: AbstractProcess( pGIC, pGIParent, rCommand)
,_rpChildGI( NULL )
,_pEntityAddressSearchCriteria( NULL )
,_pAddressEntityList(NULL)
{
   TRACE_CONSTRUCTOR( CLASSNAME, "" );

   //add containers
   addContainer( IFASTBP_PROC::CRITERIA, false, //repeatable
		           BF::NullContainerId, true  // updateabel
					  );
   addContainer( IFASTBP_PROC::ENTITY_ADDRESS_LIST, true,// repeatable
		           IFASTBP_PROC::CRITERIA, false //un-updatable
					  );
   
   //CRITERIA fields
   addFieldDetails( ifds::SearchType,						IFASTBP_PROC::CRITERIA );
   addFieldDetails( ifds::SearchFirstName,				IFASTBP_PROC::CRITERIA );
   addFieldDetails( ifds::SearchLastName,				   IFASTBP_PROC::CRITERIA );
   addFieldDetails( ifds::AddrId,							IFASTBP_PROC::CRITERIA );
	addFieldDetails( ifds::SearchPSTL,						IFASTBP_PROC::CRITERIA );
   addFieldDetails( ifds::SearchCountry,					IFASTBP_PROC::CRITERIA );
   addFieldDetails( ifds::SearchFieldCriteria1,       IFASTBP_PROC::CRITERIA );
   addFieldDetails( ifds::SearchFieldCriteria2,       IFASTBP_PROC::CRITERIA );
   
   //ENTITY_ADDRESS_LIST fields
   addFieldDetails( ifds::LastName,          IFASTBP_PROC::ENTITY_ADDRESS_LIST );
   addFieldDetails( ifds::FirstName,         IFASTBP_PROC::ENTITY_ADDRESS_LIST );
   addFieldDetails( ifds::AddrLine1,			IFASTBP_PROC::ENTITY_ADDRESS_LIST );
	addFieldDetails( ifds::AddrLine2,         IFASTBP_PROC::ENTITY_ADDRESS_LIST );
	addFieldDetails( ifds::AddrLine3,         IFASTBP_PROC::ENTITY_ADDRESS_LIST );
   addFieldDetails( ifds::City,					IFASTBP_PROC::ENTITY_ADDRESS_LIST );
   addFieldDetails( ifds::Province,          IFASTBP_PROC::ENTITY_ADDRESS_LIST );
	addFieldDetails( ifds::ProvinceName,      IFASTBP_PROC::ENTITY_ADDRESS_LIST );
   addFieldDetails( ifds::Country,           IFASTBP_PROC::ENTITY_ADDRESS_LIST );
	addFieldDetails( ifds::CountryName,       IFASTBP_PROC::ENTITY_ADDRESS_LIST );
   addFieldDetails( ifds::PostalCode,        IFASTBP_PROC::ENTITY_ADDRESS_LIST );
   addFieldDetails( ifds::AddrId,				IFASTBP_PROC::ENTITY_ADDRESS_LIST );
   addFieldDetails( ifds::EntityAddrSrch,    IFASTBP_PROC::ENTITY_ADDRESS_LIST ); //, SUBCLASS_PROCESS);

}

//******************************************************************************

EntityAddressSearchProcess::~EntityAddressSearchProcess()
{
   TRACE_DESTRUCTOR( CLASSNAME );
	_rpChildGI = NULL;
	
	if (_pAddressEntityList)
	{
		delete _pAddressEntityList;
      _pAddressEntityList = NULL;
	}
}

//******************************************************************************
//              Protected Methods
//******************************************************************************

SEVERITY EntityAddressSearchProcess::doInit()
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, DOINIT );
   try
   {
		DSTCWorkSession *pDSTCWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
				
		getParameter( MFCAN_IP_PARAM::ADDRSS_ID, _dstrAddressId );
		getParameter(MFCAN_IP_PARAM::SEARCH_TYPE, _strSearchType);
		_strSearchType.strip();
		_pEntityAddressSearchCriteria = new EntityAddressSearchCriteria ( *pDSTCWorkSession );
      if( _pEntityAddressSearchCriteria->init( _strSearchType, BF::HOST ) <= WARNING )
      {
         setContainer( IFASTBP_PROC::CRITERIA, _pEntityAddressSearchCriteria );
      }
   }
   catch (ConditionException& ce)
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

E_COMMANDRETURN EntityAddressSearchProcess::doProcess()
{  
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, DOPROCESS );
   E_COMMANDRETURN rtn = CMD_FAILURE;
   try
   {
      setParameter( MFCAN_IP_PARAM::ADDRSS_ID, _dstrAddressId );
      rtn = invokeCommand( this, CMD_GUI_ENTITY_ADDRESS_SEARCH, getProcessType(),
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
void *EntityAddressSearchProcess::getPtrForContainer (const BFContainerId& idContainer, 
                                              const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTBP_CONDITION, CLASSNAME, I_("getPtrForContainer") );

   void *ptr = NULL;
   DSTCWorkSession* dstcWorkSession = 
      dynamic_cast<DSTCWorkSession *>(getBFWorkSession());

   try
   {
      if( IFASTBP_PROC::ENTITY_ADDRESS_LIST == idContainer )
      {
         EntityAddressSearchCriteria* pEntityAddressSearchCriteria = dynamic_cast<EntityAddressSearchCriteria*>(
            getCBOItem (IFASTBP_PROC::CRITERIA, idDataGroup));

			if (pEntityAddressSearchCriteria)
			{
				_pAddressEntityList = NULL;
				if (pEntityAddressSearchCriteria->getAddressEntityList (_pAddressEntityList, idDataGroup) <= WARNING)
				{
					ptr = _pAddressEntityList;
				}
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

SEVERITY EntityAddressSearchProcess::performSearch (
   GenericInterface *rpGICaller, 
   const BFContainerId& idSearch, 
   E_SEARCHACTION eSearchAction )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTBP_CONDITION, CLASSNAME, PERFORMSEARCH );
	
   const BFDataGroupId& idDataGroup = getDataGroupId ();
   try
   {
      switch (eSearchAction)
      {
         case SEARCH_START:
            {
               if (idSearch == IFASTBP_PROC::ENTITY_ADDRESS_LIST)
						_pAddressEntityList = NULL;
               
               setContainer (idSearch, NULL);
            }
            break;
         case SEARCH_NEXT_BLOCK:
            {
               if (idSearch == IFASTBP_PROC::ENTITY_ADDRESS_LIST)
               {
                  if (_pAddressEntityList)
                     _pAddressEntityList->getMore ();
               }
            }
            break;
         default:
            break;
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
bool EntityAddressSearchProcess::doMoreRecordsExist( GenericInterface *rpGICaller,
                                             const BFContainerId& idSearch )
{
   if (!rpGICaller)
      return(false);

   if (IFASTBP_PROC::ENTITY_ADDRESS_LIST == idSearch)
   {
      return _pAddressEntityList == NULL ? false : _pAddressEntityList->doMoreRecordsExist();
   }
   return false;
}

//******************************************************************************
bool EntityAddressSearchProcess::doModelessChildComplete(const Command &cmd)
{
   return( cmd.getKey() == CMD_GUI_ENTITY_ADDRESS_SEARCH );
}

//******************************************************************************
void EntityAddressSearchProcess::doPostOk( GenericInterface *rpGICaller, bool bSuccessFlag )
{
   if( bSuccessFlag )
   {
      DString dstrSearchItemFound = NULL_STRING;
      getParameter( PARM_SEARCHITEMFOUND, dstrSearchItemFound);

      if( !dstrSearchItemFound.empty() )
      {
         DString dstrAddrId, dstrAddrLine1, dstrAddrLine2, dstrAddrLine3, dstrCity;
			DString dstrProvince, dstrCountry, dstrPostalCode;

         getField( rpGICaller, IFASTBP_PROC::ENTITY_ADDRESS_LIST, ifds::AddrId, dstrAddrId );
         setParameter( MFCAN_IP_PARAM::ADDRSS_ID, dstrAddrId );
			getField( rpGICaller, IFASTBP_PROC::ENTITY_ADDRESS_LIST, ifds::AddrLine1, dstrAddrLine1 );
         setParameter( MFCAN_IP_PARAM::ADDRESS_LINE1, dstrAddrLine1);
			getField( rpGICaller, IFASTBP_PROC::ENTITY_ADDRESS_LIST, ifds::AddrLine2, dstrAddrLine2 );
         setParameter( MFCAN_IP_PARAM::ADDRESS_LINE2, dstrAddrLine2 );
			getField( rpGICaller, IFASTBP_PROC::ENTITY_ADDRESS_LIST, ifds::AddrLine3, dstrAddrLine3 );
         setParameter( MFCAN_IP_PARAM::ADDRESS_LINE3, dstrAddrLine3 );
			getField( rpGICaller, IFASTBP_PROC::ENTITY_ADDRESS_LIST, ifds::City, dstrCity);
         setParameter( MFCAN_IP_PARAM::CITY, dstrCity);
			getField( rpGICaller, IFASTBP_PROC::ENTITY_ADDRESS_LIST, ifds::Province, dstrProvince );
         setParameter( MFCAN_IP_PARAM::PROVICE, dstrProvince );
			getField( rpGICaller, IFASTBP_PROC::ENTITY_ADDRESS_LIST, ifds::Country, dstrCountry);
         setParameter( MFCAN_IP_PARAM::COUNTRY, dstrCountry );
			getField( rpGICaller, IFASTBP_PROC::ENTITY_ADDRESS_LIST, ifds::PostalCode, dstrPostalCode );
         setParameter( MFCAN_IP_PARAM::POST_CODE, dstrPostalCode );
		}
	}
}


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/EntityAddressSearchProcess.cpp-arc  $
// 
//    Rev 1.2   Mar 18 2005 08:05:38   porteanm
// PET 1171 FN01 - EUSD Entity Address Update support.
// 
//    Rev 1.1   Mar 18 2005 07:43:32   porteanm
// PET 1171 FN01 - EUSD Entity Address Update support.
// 
//    Rev 1.0   Mar 10 2005 16:39:56   ZHANGCEL
// Initial revision.
// 
*/