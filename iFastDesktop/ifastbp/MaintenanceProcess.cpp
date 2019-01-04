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
// ^FILE   : MaintenanceProcess.cpp
// ^AUTHOR : Adrian Vasile
// ^DATE   : 08/02/2000
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : MaintenanceProcess
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include "stdafx.h"
#include "maintenanceprocess.hpp"
#include "maintenanceprocessincludes.h"
#include <ifastcbo\grouplist.hpp>
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_MAINTENANCE;
#include <bfproc\concreteprocesscreator.hpp>
static ConcreteProcessCreator< MaintenanceProcess > processCreator( CMD_BPROC_MAINTENANCE );

namespace CND
{  // Conditions used
   extern CLASS_IMPORT const long BP_ERR_UNKNOWN_EXCEPTION;
}


namespace
{
   // Trace literals
   const I_CHAR *CLASSNAME = I_( "MaintenanceProcess" );
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId TaxType;
   extern CLASS_IMPORT const BFTextFieldId AcctType;
   extern CLASS_IMPORT const BFTextFieldId Salutation;
   extern CLASS_IMPORT const BFTextFieldId EntityType;
   extern CLASS_IMPORT const BFTextFieldId LanguageCode;
   extern CLASS_IMPORT const BFTextFieldId DepositionCode;
   extern CLASS_IMPORT const BFTextFieldId JointType;
   extern CLASS_IMPORT const BFTextFieldId AddrCode;
   extern CLASS_IMPORT const BFTextFieldId CountryCode;
   extern CLASS_IMPORT const BFTextFieldId AcctStatus;
   extern CLASS_IMPORT const BFTextFieldId Currency;
   extern CLASS_IMPORT const BFTextFieldId AcctDesignation;
   extern CLASS_IMPORT const BFTextFieldId TaxJurisCode;
   extern CLASS_IMPORT const BFTextFieldId ResProvCode;
   extern CLASS_IMPORT const BFTextFieldId RelateCodeShip;
   extern CLASS_IMPORT const BFTextFieldId TradesPayType;
   extern CLASS_IMPORT const BFTextFieldId FlatPercent;
   extern CLASS_IMPORT const BFTextFieldId AmtType;
   extern CLASS_IMPORT const BFTextFieldId AmountTypeExchange;
   extern CLASS_IMPORT const BFTextFieldId DividentInstructions;
   extern CLASS_IMPORT const BFTextFieldId ManagementStyle;
   extern CLASS_IMPORT const BFTextFieldId Discretionary;
}

//******************************************************************************
//              Public Methods
//******************************************************************************

//CP20030319MaintenanceProcess::MaintenanceProcess():
MaintenanceProcess::MaintenanceProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: AbstractProcess( pGIC, pGIParent, rCommand )
, _pGroupList(NULL)
{
   TRACE_CONSTRUCTOR( CLASSNAME, "" );
   addContainer( IFASTBP_PROC::GROUP_LIST, true );
   addFieldDetails( ifds::GroupName, IFASTBP_PROC::GROUP_LIST );
   addFieldDetails( ifds::rxGroupCode, IFASTBP_PROC::GROUP_LIST );

   addSubstituteList( ifds::TaxType ,I_("TaxType"));
   addSubstituteList( ifds::AcctType ,I_("AcctType"));
   addSubstituteList( ifds::Salutation,I_("Salutation") );
   addSubstituteList( ifds::EntityType ,I_("EntityType"));
   addSubstituteList( ifds::LanguageCode ,I_("LanguageCode"));
   addSubstituteList( ifds::DepositionCode ,I_("DepositionCode"));
   addSubstituteList( ifds::JointType ,I_("JointType"));
   addSubstituteList( ifds::AddrCode ,I_("AddrCode"));
   addSubstituteList( ifds::CountryCode ,I_("CountryCode"));
   addSubstituteList( ifds::AcctStatus,I_("AcctStatus") );
   addSubstituteList( ifds::Currency ,I_("Currency"));
   addSubstituteList( ifds::AcctDesignation ,I_("AcctDesignation"));
   addSubstituteList( ifds::TaxJurisCode ,I_("TaxJurisCode"));
   addSubstituteList( ifds::ResProvCode ,I_("ResProvCode"));
   addSubstituteList( ifds::RelateCodeShip,I_("RelateCodeShip"));
   addSubstituteList( ifds::TradesPayType,I_("TradesPayType"));
   addSubstituteList( ifds::FlatPercent,I_("FlatPercent"));
   addSubstituteList( ifds::AmtType,I_("AmtType"));
   addSubstituteList( ifds::AmountTypeExchange,I_("AmountTypeExchange"));
   addSubstituteList( ifds::DividentInstructions,I_("DividentInstructions"));
   addSubstituteList( ifds::ManagementStyle,I_("ManagementStyle"));
   addSubstituteList( ifds::Discretionary,I_("Discretionary"));
}

//******************************************************************************

MaintenanceProcess::~MaintenanceProcess()
{
   TRACE_DESTRUCTOR( CLASSNAME );

   if( _pGroupList != NULL ) delete _pGroupList;
   _pGroupList = NULL;
}

//******************************************************************************
//              Protected Methods
//******************************************************************************

SEVERITY MaintenanceProcess::doInit()
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, DOINIT );
   SEVERITY sevRtn = SEVERE_ERROR;
   DString _secondValue;

   try
   {
      _pGroupList = new GroupList( *getBFWorkSession() );
      if( _pGroupList->init( NULL_STRING ) >= SEVERE_ERROR )
      {
         return(GETCURRENTHIGHESTSEVERITY());
      }
      else
      {
         //register list with base
         setContainer( IFASTBP_PROC::GROUP_LIST, _pGroupList );
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

E_COMMANDRETURN MaintenanceProcess::doProcess()
{  
   MAKEFRAME2( CND::BPBASE_CONDITION, CLASSNAME, DOPROCESS );
   E_COMMANDRETURN rtn = CMD_FAILURE;

   rtn = CMD_MODELESS_INPROCESS;
   return(rtn);
}

//******************************************************************************


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastbp/MaintenanceProcess.cpp-arc  $
 // 
 //    Rev 1.17   Mar 21 2003 17:44:34   PURDYECH
 // BFDataGroupId/BFContainerId changeover
 // 
 //    Rev 1.16   Oct 09 2002 23:53:28   PURDYECH
 // PVCS Database Conversion
 // 
 //    Rev 1.15   Aug 29 2002 16:45:04   SMITHDAV
 // Condition split.
 // 
 //    Rev 1.14   Aug 29 2002 12:54:30   SMITHDAV
 // ClientLocale and typed field changes.
 // 
 //    Rev 1.13   22 May 2002 18:24:38   PURDYECH
 // BFData Implementation
 // 
 //    Rev 1.12   27 Mar 2002 19:55:18   PURDYECH
 // Process/WindowFactory overhaul
 // 
 //    Rev 1.11   14 Jun 2001 11:58:04   SMITHDAV
 // Removed references to UserAccessProcess.
 // 
 //    Rev 1.10   May 08 2001 11:50:56   FENGYONG
 // Add name for API
 // 
 //    Rev 1.9   03 May 2001 14:05:34   SMITHDAV
 // Session management restructuring.
 // 
 //    Rev 1.8   Mar 29 2001 12:35:00   FENGYONG
 // add two substitutionset
 // 
 //    Rev 1.7   15 Dec 2000 12:43:42   PURDYECH
 // Use precompiled header stdafx.h.
 // Removed unnecessary header files.
 // 
 //    Rev 1.6   Dec 06 2000 12:16:16   VASILEAD
 // Added AmountTypeExch
 // 
 //    Rev 1.5   Nov 27 2000 11:37:26   VASILEAD
 // Added AllFundInfo support to provide with fund information for the global object in ECOMM
 // 
 //    Rev 1.4   Nov 21 2000 15:01:30   FENGYONG
 // Add flatpercent,amttype,tradespaytype set for trading page
 // 
 //    Rev 1.3   Sep 08 2000 13:44:38   YINGZ
 // bug fix
 // 
 //    Rev 1.2   Aug 14 2000 17:30:02   FENGYONG
 // Add fields
 // 
 //    Rev 1.1   Aug 08 2000 12:18:26   FENGYONG
 // Add AcctDesignation field
 * 
 */
