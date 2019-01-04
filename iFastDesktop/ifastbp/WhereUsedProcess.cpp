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
// ^FILE   : WhereUsedProcess.cpp
// ^AUTHOR : Celia 
// ^DATE   : 16/04/99
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : WhereUsedProcess
//    This class manages the management company and profile selection.
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include "stdafx.h"
#include "whereusedprocess.hpp"
#include <ifastcbo\accountentityxref.hpp>
#include <ifastcbo\accountentityxrefobject.hpp>
#include <ifastcbo\entity.hpp>
#include <ifastcbo\whereusedlist.hpp>
#include <ifastcbo\whereused.hpp>

#include "whereusedprocessincludes.h"
extern IFASTBP_LINKAGE const I_CHAR* CMD_GUI_WHEREUSED;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_WHEREUSED;
#include <bfproc\concreteprocesscreator.hpp>
static ConcreteProcessCreator< WhereUsedProcess > processCreator( CMD_BPROC_WHEREUSED );

namespace
{
   // Trace literals
   const I_CHAR * const CLASSNAME = I_( "WhereUsedProcess" );
   const I_CHAR * const PERFORMSEARCH = I_( "performSearch" );
   const DString EMPTY_STRING;
}

namespace WHEREUSEDPROC
{
   const I_CHAR * const ENTITY_ID = I_( "EntityId" );
   const I_CHAR * const ENTITY_NAME = I_( "EntityName" );
   const I_CHAR * const BIRTHENTITY_NAME = I_( "BirthEntityName" );
   const I_CHAR * const CALLER = I_( "Caller" );
   const I_CHAR * const WHEREUSEDLG = I_( "WhereUsedDlg" );
}

namespace CND
{
   extern CLASS_IMPORT const long BP_ERR_UNKNOWN_EXCEPTION;
}
namespace ifds
{
   extern CLASS_IMPORT const BFNumericFieldId EntityId;
}




//******************************************************************************
//              Public Methods
//******************************************************************************

//CP20030319WhereUsedProcess::WhereUsedProcess() : 
WhereUsedProcess::WhereUsedProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: AbstractProcess( pGIC, pGIParent, rCommand )
, _rpChildGI( NULL )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );

   addContainer( IFASTBP_PROC::WHEREUSED_LIST, true );
   addFieldDetails( ifds::AccountNum, IFASTBP_PROC::WHEREUSED_LIST );
   addFieldDetails( ifds::EntityType, IFASTBP_PROC::WHEREUSED_LIST,  SUBCLASS_PROCESS );
   addFieldDetails( ifds::EntityTypeDesc, IFASTBP_PROC::WHEREUSED_LIST );
   addFieldDetails( ifds::ShrNum, IFASTBP_PROC::WHEREUSED_LIST );
   addFieldDetails( ifds::TaxTypeDesc, IFASTBP_PROC::WHEREUSED_LIST );
   addFieldDetails( ifds::TaxType, IFASTBP_PROC::WHEREUSED_LIST );
   addFieldDetails( ifds::AcctType, IFASTBP_PROC::WHEREUSED_LIST );
   addFieldDetails( ifds::AcctTypeDesc, IFASTBP_PROC::WHEREUSED_LIST );
   addFieldDetails( ifds::AcctStatusDesc, IFASTBP_PROC::WHEREUSED_LIST );
   addFieldDetails( ifds::AcctStatus, IFASTBP_PROC::WHEREUSED_LIST );
   addFieldDetails( ifds::Currency, IFASTBP_PROC::WHEREUSED_LIST );
   addFieldDetails( ifds::AccountBalance, IFASTBP_PROC::WHEREUSED_LIST );
   addFieldDetails( ifds::EntityTypeSeq, IFASTBP_PROC::WHEREUSED_LIST );
   addFieldDetails( ifds::WhereUse, IFASTBP_PROC::WHEREUSED_LIST);
   addFieldDetails( ifds::WhereUseCode, IFASTBP_PROC::WHEREUSED_LIST);
}

//******************************************************************************
WhereUsedProcess::~WhereUsedProcess()
{
   TRACE_DESTRUCTOR( CLASSNAME );
   _rpChildGI = NULL;
}

//******************************************************************************
SEVERITY WhereUsedProcess::doInit()
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, DOINIT );

   try
   {
      DSTCWorkSession *dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());

      getParameter( WHEREUSEDPROC::ENTITY_ID, _dstrEntityID );
      getParameter( WHEREUSEDPROC::ENTITY_NAME, _dstrEntityName );
      getParameter( WHEREUSEDPROC::BIRTHENTITY_NAME, _dstrEntityBirtyName );
/*      if( dstcWorkSession->getAccountEntityXref( getDataGroupId(), _pAccountEntityXref ) <= WARNING &&
          _pAccountEntityXref->PopulateWhereUsed( _dstrEntityID ) <= WARNING )*/

	  DString dstrCaller;
      getParameter( WHEREUSEDPROC::CALLER, dstrCaller );

	  if (dstrCaller != WHEREUSEDPROC::WHEREUSEDLG)
	  {
		Entity::bUsedByEntityAlone = true;
	  }

	  if( dstcWorkSession->getWhereUsedList(_pWhereUsedList, getDataGroupId(), true, _dstrEntityID ) <= WARNING )
      {
         setContainer( IFASTBP_PROC::WHEREUSED_LIST, _pWhereUsedList );
      }
   }
   catch( ConditionException &ce )
   {
      SETCONDITIONFROMEXCEPTION( ce );
   }
   catch( ... )
   {
      assert(0);
      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, DOINIT,
                      CND::BP_ERR_UNKNOWN_EXCEPTION );
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
bool WhereUsedProcess::doModelessChildComplete( const Command &cmd )
{
   // End when GUI ends
   return( cmd.getKey() == CMD_GUI_WHEREUSED );
}

//******************************************************************************
E_COMMANDRETURN WhereUsedProcess::doProcess()
{  
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, DOPROCESS );
   E_COMMANDRETURN rtn = CMD_FAILURE;

   try
   {
      setParameter( WHEREUSEDPROC::ENTITY_NAME, _dstrEntityName );
      setParameter( WHEREUSEDPROC::BIRTHENTITY_NAME, _dstrEntityBirtyName );

      rtn = invokeCommand( this, CMD_GUI_WHEREUSED, getProcessType(), isModal(), &_rpChildGI );
   }
   catch( ConditionException &ce )
   {
      assert( 0 );
      SETCONDITIONFROMEXCEPTION( ce );
   }
   catch( ... )
   {
      assert( 0 );
      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, DOPROCESS, CND::BP_ERR_UNKNOWN_EXCEPTION );
   }
   return(rtn);
}

//******************************************************************************
const DString& WhereUsedProcess::getFirstListItemKey(
                                                    const GenericInterface *rpGICaller,
                                                    const BFContainerId& idList
                                                    )
{  
   TRACE_METHOD( CLASSNAME, GETFIRSTLISTITEMKEY );

   DString key;
/*
   try
   {
      if( idList == IFASTBP_PROC::WHEREUSED_LIST )
      {
         BFObjIter iterAccountEntityXrefOut( *_pAccountEntityXref, getDataGroupId(), true );

         DString searchKey;

         AccountEntityXref::buildPartialKeyForEntityId( searchKey, _dstrEntityID );
         if( iterAccountEntityXrefOut.begin( OBJ_TYPE_NONE, OBJ_ACTIVITY_NONE, searchKey ) )
         {
            DString key = iterAccountEntityXrefOut.getStringKey();
            AbstractProcess::setCurrentListItem( rpGICaller, idList, key );
            return(iterAccountEntityXrefOut.getStringKey());
         }
         return(EMPTY_STRING);
      }
   }
   catch( ConditionException & )
   {
      throw;
   }
   catch( ... )
   {  // Just to catch at earliest point
      assert( 0 );
      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, GETFIRSTLISTITEMKEY,
                      CND::BP_ERR_UNKNOWN_EXCEPTION );
   }
*/
   return(AbstractProcess::getFirstListItemKey( rpGICaller, idList ));
}

//******************************************************************************
const DString& WhereUsedProcess::getNextListItemKey(
                                                   const GenericInterface *rpGICaller,
                                                   const BFContainerId& idList
                                                   )
{  
   TRACE_METHOD( CLASSNAME, GETNEXTLISTITEMKEY );
   DString key;

/*   try
   {
      if( idList == IFASTBP_PROC::WHEREUSED_LIST )
      {
         BFObjIter iterAccountEntityXrefOut( *_pAccountEntityXref, getDataGroupId(), true, BFObjIter::ITERTYPE::NON_DELETED);

         DString acctListCurrentItemKey = getCurrentListItemKey( rpGICaller, idList );
         DString searchKey;

         AccountEntityXref::buildPartialKeyForEntityId( searchKey, _dstrEntityID );
         if( iterAccountEntityXrefOut.begin( OBJ_TYPE_NONE, OBJ_ACTIVITY_NONE, searchKey ) )
         {
            iterAccountEntityXrefOut.positionByKey( acctListCurrentItemKey );
            if( !++iterAccountEntityXrefOut )
               return(EMPTY_STRING);
            DString key = iterAccountEntityXrefOut.getStringKey();
            AbstractProcess::setCurrentListItem( rpGICaller, idList, key );
            return(iterAccountEntityXrefOut.getStringKey());
         }
         return(EMPTY_STRING);
      }
   }
   catch( ConditionException & )
   {
      throw;
   }
   catch( ... )
   {  // Just to catch at earliest point
      assert( 0 );
      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, GETNEXTLISTITEMKEY,
                      CND::BP_ERR_UNKNOWN_EXCEPTION );
   }*/
   return(AbstractProcess::getNextListItemKey( rpGICaller, idList ));
}
//************************************************************************************************************
void WhereUsedProcess::doGetField(
                               const GenericInterface *rpGICaller,
                               const BFContainerId& idContainer,
                               const BFFieldId& idField,
                               const BFDataGroupId& idDataGroup,
                               DString &strValueOut,
                               bool bFormatted
                               ) const
{
    if(  idField == ifds::EntityType)
    {
       WhereUsed *pObj = dynamic_cast<WhereUsed*>(
						const_cast <WhereUsedProcess*>(this)->getCBOItem(
                                IFASTBP_PROC::WHEREUSED_LIST, idDataGroup  ));        

       if( pObj )
       {
            DString entityType,whereUse;
            pObj->getField( ifds::EntityType,entityType,idDataGroup,false );
            pObj->getField( ifds::WhereUse,whereUse,idDataGroup,false );
            whereUse.strip();
            entityType.strip();            
            if( _dstrEntityID != NULL_STRING )
            {
                    if( _pWhereUsedList )
                    {
                        _pWhereUsedList->getFiedByEntityTypeWhereUseCode( 
                                entityType,
                                whereUse,    
                                idField,
                                strValueOut,
                                idDataGroup,
                                bFormatted
                                );
                    }  
            }    
       }
    }
}

//******************************************************************************
bool WhereUsedProcess::doMoreRecordsExist( GenericInterface *rpGICaller, const BFContainerId& idSearch )
{
   return(rpGICaller == NULL || _pWhereUsedList == NULL ? false : _pWhereUsedList->doMoreRecordsExist());
}

//******************************************************************************
SEVERITY WhereUsedProcess::performSearch( GenericInterface *rpGI, const BFContainerId& idSearch, E_SEARCHACTION eSearchAction )
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, PERFORMSEARCH );
   SEVERITY sevRtn = SEVERE_ERROR;

   try
   {
      if( _pWhereUsedList != NULL )
      {
         sevRtn = _pWhereUsedList->getMore();
         setContainer( IFASTBP_PROC::WHEREUSED_LIST, NULL );
         setContainer( IFASTBP_PROC::WHEREUSED_LIST, _pWhereUsedList );
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
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/WhereUsedProcess.cpp-arc  $
 * 
 *    Rev 1.19   Mar 23 2009 15:39:20   jankovii
 * IN 1623318 - R91 - Desktop - Entity field is greyed out if "Whereused" option selected
 * 
 *    Rev 1.18   Dec 02 2005 09:28:28   jankovii
 * Incident #468333-fixed Status in where used.
 * 
 *    Rev 1.17   May 17 2005 12:22:38   Fengyong
 * #Incident 272055 - set Entity::bUsedByEntityAlone = true;
 * 
 *    Rev 1.16   May 17 2005 11:32:18   Fengyong
 * #Incident 272055 - Add more button to where used screen
 * 
 *    Rev 1.15   Apr 21 2005 13:20:36   yingbaol
 * Incident290503: add dogetField method
 * 
 *    Rev 1.14   Dec 03 2004 11:20:16   georgeet
 * PET 1117 FN54 - Added fields details for WhereUsedList
 * 
 *    Rev 1.13   May 01 2003 14:35:28   HERNANDO
 * PTS 10016678 - Added TaxType and AcctType Field details.
 * 
 *    Rev 1.12   Mar 21 2003 17:50:06   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.11   Oct 09 2002 23:53:44   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.10   Aug 29 2002 16:45:20   SMITHDAV
 * Condition split.
 * 
 *    Rev 1.9   Aug 15 2002 13:26:58   KOVACSRO
 * bug fixed (system was crashing when delete an entity and click on where used for another entity with the same entityId)
 * 
 *    Rev 1.8   22 May 2002 18:25:24   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.7   27 Mar 2002 19:56:24   PURDYECH
 * Process/WindowFactory overhaul
 * 
 *    Rev 1.6   15 May 2001 15:39:00   YINGZ
 * data group id clean up
 * 
 *    Rev 1.5   03 May 2001 14:05:48   SMITHDAV
 * Session management restructuring.
 * 
 *    Rev 1.4   15 Dec 2000 12:43:58   PURDYECH
 * Use precompiled header stdafx.h.
 * Removed unnecessary header files.
 * 
 *    Rev 1.3   Sep 21 2000 14:08:22   OLTEANCR
 * .
 * 
 *    Rev 1.2   Mar 06 2000 13:22:30   DT24433
 * removed substitute list
 * 
 *    Rev 1.1   Feb 15 2000 18:57:20   MCNABBGL
 * changed comment format
 * 
 *    Rev 1.0   Feb 15 2000 10:59:44   SMITHDAV
 * Initial revision.
// 
//    Rev 1.12   Jan 14 2000 15:59:18   VASILEAD
// Where used fixes
// 
//    Rev 1.11   Jan 14 2000 08:51:34   POPESCUS
// finally made those dialogs and processes work
// 
//    Rev 1.10   Dec 07 1999 14:20:26   YINGZ
// add group to doset/get fiels
// 
//    Rev 1.9   Nov 22 1999 10:46:36   ZHANGCEL
// add a substitution list
// 
//    Rev 1.8   Nov 11 1999 17:54:06   VASILEAD
// Changed to the new AccountEntityXref list
// 
//    Rev 1.7   Oct 29 1999 14:24:56   DT24433
// removed doOk/doCancel
// 
//    Rev 1.6   Oct 27 1999 10:16:56   ZHANGCEL
// modify for new process
// 
//    Rev 1.5   Oct 18 1999 16:18:54   POPESCUS
// Fixed compiling error
// 
//    Rev 1.4   Aug 30 1999 18:42:50   DT24433
// changed dogetfield/dosetfield parms
// 
//    Rev 1.3   Aug 20 1999 11:18:08   DT24433
// finished removing FieldDetails array
// 
//    Rev 1.2   Aug 20 1999 09:50:28   DT24433
// remove static FieldDetails array
// 
//    Rev 1.1   Jul 27 1999 16:01:50   BUZILA
// Increment M2
// 
//    Rev 1.0   Jul 22 1999 17:23:32   BUZILA
// Initial revision.
*/ 

