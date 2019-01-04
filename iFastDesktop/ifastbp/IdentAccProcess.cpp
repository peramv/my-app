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
// ^FILE   : IdentAccProcess.cpp
// ^AUTHOR : Mihai Virgil Buzila
// ^DATE   : 03 Feb 2000
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : IdentAccProcess
//    
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include "stdafx.h"
#include <ifastcbo\accountentityxref.hpp>
#include <ifastcbo\accountentityxrefobject.hpp>
#include "accinfoprocessincludes.h"
#include <ifastcbo\entitysearchlist.hpp>
#include <ifastcbo\entity.hpp>
#include <ifastcbo\entityidslist.hpp>
#include "entitysearchprocess.hpp"
#include "identaccprocess.hpp"
#include "identaccprocessincludes.h"
#include <ifastcbo\mfaccount.hpp>
#include "nasuprocessincludes.h"
extern IFASTBP_LINKAGE const I_CHAR* CMD_GUI_IDENT_ACC;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_NASU;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_IDENT_ACC;
#include <bfproc\concreteprocesscreator.hpp>
static ConcreteProcessCreator< IdentAccProcess > processCreator( CMD_BPROC_IDENT_ACC );

namespace
{
   const I_CHAR * const CLASSNAME = I_( "IdentAccProcess" );
   const I_CHAR * const PERFORMSEARCH = I_( "performSearch" );
   const DString EMPTY_STRING;
   const I_CHAR * const YES = I_( "Y" );
   const I_CHAR * const NO = I_( "N" );

}

namespace CND
{
   extern CLASS_IMPORT const long BP_ERR_UNKNOWN_EXCEPTION;
}

namespace IDENTACCPROC
{
   const I_CHAR * const ACCOUNT_NUM = I_( "AccountNum" );
   const I_CHAR * const CREATE_NEW_ACCOUNT = I_( "NewAccount" );
   const I_CHAR * const CREATE_NEW_SHAREHOLDER = I_( "NewShareholder" );
   const I_CHAR * const FROM_SYSTEMATIC = I_("FromSystematic");

}

namespace ifds
{
   extern CLASS_IMPORT const BFNumericFieldId LastActiveAccountNum;
}

//******************************************************************************
//              Public Methods
//******************************************************************************
IdentAccProcess::IdentAccProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: AbstractProcess( pGIC, pGIParent, rCommand )
, _pEntitySearchList( NULL ), bGotAccount(false)
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );

   //add containers
   addContainer( IFASTBP_PROC::ENTITY_SEARCH_LIST, true, BF::NullContainerId );
   //although the entity ids list is not updatable we need to
   //add a row if there are no ids for an entity
   addContainer( IFASTBP_PROC::ENTITY_IDS_LIST, true, IFASTBP_PROC::ENTITY_SEARCH_LIST, true );
   addContainer( IFASTBP_PROC::ACCOUNT_LIST, true, BF::NullContainerId, true );
   //entity list
   addFieldDetails( ifds::AccountNum, IFASTBP_PROC::ENTITY_SEARCH_LIST );
   addFieldDetails( ifds::LastName, IFASTBP_PROC::ENTITY_SEARCH_LIST );
   addFieldDetails( ifds::FirstName, IFASTBP_PROC::ENTITY_SEARCH_LIST );
   addFieldDetails( ifds::SIN, IFASTBP_PROC::ENTITY_SEARCH_LIST );
   addFieldDetails( ifds::BirthDate, IFASTBP_PROC::ENTITY_SEARCH_LIST );
   addFieldDetails( ifds::TaxType, IFASTBP_PROC::ENTITY_SEARCH_LIST );
   addFieldDetails( ifds::TaxTypeDesc, IFASTBP_PROC::ENTITY_SEARCH_LIST );
   addFieldDetails( ifds::HomePhone, IFASTBP_PROC::ENTITY_SEARCH_LIST );
   addFieldDetails( ifds::EntityId, IFASTBP_PROC::ENTITY_SEARCH_LIST );
   addFieldDetails( ifds::Address1, IFASTBP_PROC::ENTITY_SEARCH_LIST );
   addFieldDetails( ifds::Address2, IFASTBP_PROC::ENTITY_SEARCH_LIST );
   addFieldDetails( ifds::Address3, IFASTBP_PROC::ENTITY_SEARCH_LIST );
   addFieldDetails( ifds::Address4, IFASTBP_PROC::ENTITY_SEARCH_LIST );
   addFieldDetails( ifds::Address5, IFASTBP_PROC::ENTITY_SEARCH_LIST );
   addFieldDetails( ifds::PostalCode, IFASTBP_PROC::ENTITY_SEARCH_LIST );
   addFieldDetails( ifds::BirthLastName, IFASTBP_PROC::ENTITY_SEARCH_LIST );
   addFieldDetails( ifds::BirthFirstName, IFASTBP_PROC::ENTITY_SEARCH_LIST );
   addFieldDetails( ifds::MultipleReln, IFASTBP_PROC::ENTITY_SEARCH_LIST );
   addFieldDetails( ifds::Addr11Line1, IFASTBP_PROC::ENTITY_SEARCH_LIST );
   addFieldDetails( ifds::Addr11Line2, IFASTBP_PROC::ENTITY_SEARCH_LIST );
   addFieldDetails( ifds::Addr11Line3, IFASTBP_PROC::ENTITY_SEARCH_LIST );
   addFieldDetails( ifds::Addr11Line4, IFASTBP_PROC::ENTITY_SEARCH_LIST );
   addFieldDetails( ifds::Addr11Line5, IFASTBP_PROC::ENTITY_SEARCH_LIST );
   addFieldDetails( ifds::PostalCode11, IFASTBP_PROC::ENTITY_SEARCH_LIST );

   //entity ids list
   addFieldDetails( ifds::IdType, IFASTBP_PROC::ENTITY_IDS_LIST );
   addFieldDetails( ifds::IdValue, IFASTBP_PROC::ENTITY_IDS_LIST );
   addFieldDetails( ifds::IdDate, IFASTBP_PROC::ENTITY_IDS_LIST );
   addFieldDetails( ifds::IdTypeDesc, IFASTBP_PROC::ENTITY_IDS_LIST );
   addFieldDetails( ifds::IdStatus, IFASTBP_PROC::ENTITY_IDS_LIST );
   addFieldDetails (ifds::CountryOfIssue, IFASTBP_PROC::ENTITY_IDS_LIST ); 
   addFieldDetails( ifds::IdExpireDate, IFASTBP_PROC::ENTITY_IDS_LIST);

   //account list
   addFieldDetails( ifds::AccountNum, IFASTBP_PROC::ACCOUNT_LIST, SUBCLASS_PROCESS );
   addFieldDetails( ifds::TaxType, IFASTBP_PROC::ACCOUNT_LIST, SUBCLASS_PROCESS );
   addFieldDetails( ifds::TaxTypeDesc, IFASTBP_PROC::ACCOUNT_LIST, SUBCLASS_PROCESS );
   addFieldDetails( ifds::AcctTypeDesc, IFASTBP_PROC::ACCOUNT_LIST, SUBCLASS_PROCESS );
   addFieldDetails( ifds::AcctType, IFASTBP_PROC::ACCOUNT_LIST );
   addFieldDetails( ifds::InterAccount, IFASTBP_PROC::ACCOUNT_LIST, SUBCLASS_PROCESS );
   addFieldDetails( ifds::AltAccount, IFASTBP_PROC::ACCOUNT_LIST, SUBCLASS_PROCESS );
   addFieldDetails( ifds::RegistrationInfo, IFASTBP_PROC::ACCOUNT_LIST, SUBCLASS_PROCESS );

   //fields
   addFieldDetails( IDENTACCPROC::FIRST_VALUE, BF::NullContainerId, SUBCLASS_PROCESS );
   addFieldDetails( IDENTACCPROC::SECOND_VALUE, BF::NullContainerId, SUBCLASS_PROCESS );
   addFieldDetails( IDENTACCPROC::SEARCH_CODE, BF::NullContainerId, SUBCLASS_PROCESS );
   addFieldDetails( IDENTACCPROC::ACC_HOLDER_KANA_NAME, BF::NullContainerId, SUBCLASS_PROCESS );
   addFieldDetails( IDENTACCPROC::ACC_HOLDER_KANJI_NAME, BF::NullContainerId, SUBCLASS_PROCESS );
}

//******************************************************************************
IdentAccProcess::~IdentAccProcess()
{
   TRACE_DESTRUCTOR( CLASSNAME );

   if( _pEntitySearchList != NULL )
   {
      delete _pEntitySearchList;
      _pEntitySearchList = NULL;
   }
}

//******************************************************************************
SEVERITY IdentAccProcess::doInit()
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, DOINIT );

   try
   {
      getParent()->getParameter( IDENTACCPROC::FROM_SYSTEMATIC, m_dstrsystematic );

      DSTCWorkSession *dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
      if( dstcWorkSession->getAccountEntityXref( getDataGroupId(), _pAccountEntityXref ) <= WARNING )
      {
         setContainer( IFASTBP_PROC::ACCOUNT_LIST, _pAccountEntityXref );
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
void IdentAccProcess::doGetField(
                                const GenericInterface *rpGICaller,
                                const BFContainerId& idContainer,
                                const BFFieldId& idField,
                                const BFDataGroupId& idDataGroup, 
                                DString &strValueOut,
                                bool bFormatted
                                ) const
{  
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, DOGETFIELD );

   if( idContainer == IFASTBP_PROC::ACCOUNT_LIST )
   {
      BFAbstractCBO *rpPtr = const_cast<IdentAccProcess*>(this)->getCBOItem( IFASTBP_PROC::ACCOUNT_LIST, idDataGroup );
      DString accNum;

      if( rpPtr != NULL )
      {
         rpPtr->getField( ifds::AccountNum, accNum, idDataGroup );

         MFAccount *pMFAccount = NULL;

         DSTCWorkSession *dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
         if( dstcWorkSession->getMFAccount( idDataGroup, accNum, pMFAccount ) <= WARNING )
         {
            pMFAccount->getField( idField, strValueOut, idDataGroup, bFormatted );
         }
      }
   }
   else if( BF::NullContainerId == idContainer )
   {
      BFAbstractCBO *rpPtr = const_cast<IdentAccProcess*>(this)->getCBOItem( IFASTBP_PROC::ACCOUNT_LIST, idDataGroup );
      DString accNum;

      if( idField == IDENTACCPROC::ACC_HOLDER_KANA_NAME )
      {
         if( rpPtr != NULL )
         {
            rpPtr->getField( ifds::AccountNum, accNum, idDataGroup );
            DSTCWorkSession *dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
            dstcWorkSession->getFirstSequenced01AccountholderEntityName( idDataGroup, accNum, strValueOut, false );
         }
      }
      else if( idField == IDENTACCPROC::ACC_HOLDER_KANJI_NAME )
      {
         if( rpPtr != NULL )
         {
            rpPtr->getField( ifds::AccountNum, accNum, idDataGroup );
            DSTCWorkSession *dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
            dstcWorkSession->getFirstSequenced01AccountholderEntityName( idDataGroup, accNum, strValueOut );
         }
      }
   }
}

//******************************************************************************
SEVERITY IdentAccProcess::doSetField(
                                    const GenericInterface *rpGICaller,
                                    const BFContainerId& idContainer,
                                    const BFFieldId& idField,
                                    const BFDataGroupId& idDataGroup,
                                    const DString& strValue,
                                    bool bFormatted
                                    )
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, DOSETFIELD );

   if( BF::NullContainerId == idContainer )
   {
      if( idField == IDENTACCPROC::FIRST_VALUE )
      {
         _firstValue = strValue;
      }
      else if( idField == IDENTACCPROC::SECOND_VALUE )
      {
         _secondValue = strValue;
      }
      else if( idField == IDENTACCPROC::SEARCH_CODE )
      {
         _searchCode = strValue;
      }
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
const DString& IdentAccProcess::getFirstListItemKey( const GenericInterface *rpGICaller, const BFContainerId& idList )
{
   TRACE_METHOD( CLASSNAME, GETFIRSTLISTITEMKEY );

   try
   {
      if( idList == IFASTBP_PROC::ACCOUNT_LIST )
      {
         BFObjIter iterAccountEntityXrefOut( *_pAccountEntityXref, 
                                             getDataGroupId(), true, BFObjIter::ITERTYPE::NON_DELETED );
         BFAbstractCBO *rpPtr = getCBOItem( IFASTBP_PROC::ENTITY_SEARCH_LIST, getDataGroupId() );

         if( rpPtr != NULL )
         {
            DString entityId, searchKey;

            rpPtr->getField( ifds::EntityId, entityId, getDataGroupId() );
            AccountEntityXref::buildPartialKeyForEntityId( searchKey, entityId );
            if( iterAccountEntityXrefOut.begin( OBJ_TYPE_NONE, OBJ_ACTIVITY_NONE, searchKey ) )
            {
               DString key = iterAccountEntityXrefOut.getStringKey();

               AbstractProcess::setCurrentListItem( rpGICaller, idList, key );
               return(iterAccountEntityXrefOut.getStringKey());
            }
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
   return(AbstractProcess::getFirstListItemKey( rpGICaller, idList ));
}

//******************************************************************************
const DString& IdentAccProcess::getNextListItemKey( const GenericInterface *rpGICaller, const BFContainerId& idList )
{  
   TRACE_METHOD( CLASSNAME, GETNEXTLISTITEMKEY );

   try
   {
      if( idList == IFASTBP_PROC::ACCOUNT_LIST )
      {
         BFObjIter iterAccountEntityXrefOut( *_pAccountEntityXref, 
                                             getDataGroupId(), true, BFObjIter::ITERTYPE::NON_DELETED );
         BFAbstractCBO *rpPtr = getCBOItem( IFASTBP_PROC::ENTITY_SEARCH_LIST, getDataGroupId() );

         DString acctListCurrentItemKey = getCurrentListItemKey( rpGICaller, idList );
         if( rpPtr != NULL )
         {
            DString entityId, searchKey;

            rpPtr->getField( ifds::EntityId, entityId, getDataGroupId() );
            AccountEntityXref::buildPartialKeyForEntityId( searchKey, entityId );

            if( iterAccountEntityXrefOut.begin( OBJ_TYPE_NONE, OBJ_ACTIVITY_NONE, searchKey ) )
            {
               iterAccountEntityXrefOut.positionByKey( acctListCurrentItemKey );

               if( !++iterAccountEntityXrefOut )
                  return(EMPTY_STRING);

               if( !iterAccountEntityXrefOut.end() )
               {
                  DString key = iterAccountEntityXrefOut.getStringKey();
                  AbstractProcess::setCurrentListItem( rpGICaller, idList, key );
                  return(iterAccountEntityXrefOut.getStringKey());
               }
            }
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
   return(AbstractProcess::getNextListItemKey( rpGICaller, idList ));
}

//******************************************************************************
E_COMMANDRETURN IdentAccProcess::doProcess()
{  
   MAKEFRAME2( CND::BPBASE_CONDITION, CLASSNAME, DOPROCESS );
   E_COMMANDRETURN rtn = CMD_FAILURE;

   try
   {
      setParameter( IDENTACCPROC::FROM_SYSTEMATIC, m_dstrsystematic );
      rtn = invokeCommand( this, CMD_GUI_IDENT_ACC, getProcessType(), isModal(), NULL );
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

//**********************************************************************
void *IdentAccProcess::getPtrForContainer( const BFContainerId& idContainer, const BFDataGroupId& idDataGroup )
{
   MAKEFRAME2( CND::BPBASE_CONDITION, CLASSNAME, I_( "getPtrForContainer" ) );

   void *ptr = NULL;

   try
   {
      if( IFASTBP_PROC::ENTITY_IDS_LIST == idContainer )
      {
         {
            BFAbstractCBO *rpPtr = getCBOItem( IFASTBP_PROC::ENTITY_SEARCH_LIST, idDataGroup );

            if( rpPtr != NULL )
            {
               DString entityId;
               Entity* entity;

               rpPtr->getField( ifds::EntityId, entityId, idDataGroup );

               DSTCWorkSession *dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
               if( dstcWorkSession->getEntity( idDataGroup, entityId, entity ) <= WARNING )
               {
                  EntityIdsList* entityIds = NULL;

                  if( entity->getEntityIdsList( entityIds, idDataGroup ) <= WARNING )
                  {
                     ptr = entityIds;
                  }
               }
            }
         }
      }
      else
      {
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

//**********************************************************************
SEVERITY IdentAccProcess::performSearch( GenericInterface *rpGI, const BFContainerId& idSearch, 
                                         E_SEARCHACTION eSearchAction )
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, PERFORMSEARCH );
   SEVERITY sevRtn = SEVERE_ERROR;

   try
   {
      if( idSearch == IFASTBP_PROC::SEARCH_INIT ) //creates a new entity search list
      {
         if( _pEntitySearchList != NULL )
         {
            delete _pEntitySearchList;
            _pEntitySearchList = NULL;
         }
         _pEntitySearchList = new EntitySearchList( *getBFWorkSession() );
         //reset the container
//         setContainer( IDENTACCPROC::ENTITY_SEARCH_LIST, NULL );
         //search only for account holders
         if( _pEntitySearchList->init( EntitySearchProcess::getEntitySearchCboType( _searchCode ), 
                                       _firstValue, _secondValue, false ) <= WARNING )
         {
            setContainer( IFASTBP_PROC::ENTITY_SEARCH_LIST, _pEntitySearchList );
         }
      }
      else if( idSearch == IFASTBP_PROC::SEARCH_MORE ) //resets the containers
      {
         sevRtn = _pEntitySearchList->search();
         if( sevRtn <= WARNING )
         {
            setContainer( IFASTBP_PROC::ENTITY_SEARCH_LIST, NULL );
            setContainer( IFASTBP_PROC::ENTITY_SEARCH_LIST, _pEntitySearchList );
         }
      }
      else if( idSearch == IFASTBP_PROC::SEARCH_ACCOUNTS )
      {
         const BFDataGroupId& idDataGroup = getDataGroupId();
         BFAbstractCBO *rpPtr = getCBOItem( IFASTBP_PROC::ENTITY_SEARCH_LIST, idDataGroup );

         if( rpPtr != NULL )
         {
            DString entityId;

            rpPtr->getField( ifds::EntityId, entityId, idDataGroup );
            //reset the container
            setContainer( IFASTBP_PROC::ACCOUNT_LIST, NULL );
            //does the view calls
            if( _pAccountEntityXref->PopulateWhereUsed( entityId ) <= WARNING )
            {
               setContainer( IFASTBP_PROC::ACCOUNT_LIST, _pAccountEntityXref );
               bGotAccount = true;
            }
         }
      }
      else
      {
         assert( 0 );
         throw;
      }
   }
   catch( ConditionException &ce )
   {
      SETCONDITIONFROMEXCEPTION( ce );
      throw ce;
   }
   catch( ... )
   {
      assert( 0 );
      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, PERFORMSEARCH, CND::BP_ERR_UNKNOWN_EXCEPTION );
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
bool IdentAccProcess::doMoreRecordsExist( GenericInterface *rpGICaller, const BFContainerId& idSearch )
{
   return(_pEntitySearchList == NULL ? false : _pEntitySearchList->doMoreRecordsExist());
}

//******************************************************************************
void IdentAccProcess::doPostOk( GenericInterface *rpGICaller, bool bSuccessFlag )
{
   if( bSuccessFlag )
   {
      DString accountNum;

      if( bGotAccount && getNumberOfItemsInList( rpGICaller, IFASTBP_PROC::ACCOUNT_LIST ) != 0 )
      {
         getField( rpGICaller, IFASTBP_PROC::ACCOUNT_LIST, ifds::AccountNum, accountNum );
         setParameter( IDENTACCPROC::ACCOUNT_NUM, accountNum );
      }
   }
}
//******************************************************************************

bool IdentAccProcess::doSend( GenericInterface * rpGICaller, const I_CHAR * szMessage )
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, I_( "doSend" ) );

   if( szMessage == IDENTACCPROC::CREATE_NEW_SHAREHOLDER )
   {
      E_COMMANDRETURN eRtn = CMD_FAILURE;

      try
      {
         setParameter( NASULIT::CREATING_SHAREHOLDER, YES );
         setParameter( NASULIT::CREATING_ACCOUNT, YES );
         setParameter(NASULIT::PARM_CALLED_FROM, CLASSNAME);
         eRtn = invokeCommand( CMD_BPROC_NASU, PROC_NO_TYPE, true, NULL );
         switch( eRtn )
         {
            case CMD_OK:
            case CMD_MODELESS_INPROCESS:
               break;
            case CMD_CANCEL:
               return(false);
            default:
               return(false);
         }
      }
      catch( ... )
      {
         ADDCONDITIONFROMFILE( CND::BP_ERR_UNKNOWN_EXCEPTION );
         return(false);
      }
      if( GETCURRENTHIGHESTSEVERITY() <= WARNING )
      {
         DString accountNum;
         getGlobal( WORK_GLOBAL, ifds::LastActiveAccountNum, accountNum );
         setParameter(IDENTACCPROC::ACCOUNT_NUM, accountNum);
      }
   }
   else if( szMessage == IDENTACCPROC::CREATE_NEW_ACCOUNT )
   {
      E_COMMANDRETURN eRtn = CMD_FAILURE;

      try
      {
         setParameter( NASULIT::CREATING_SHAREHOLDER, NO );
         setParameter( NASULIT::CREATING_ACCOUNT, YES );
         setParameter(NASULIT::PARM_CALLED_FROM, CLASSNAME);
         DString strAccountNum, strShrNum;
         getParameter( IDENTACCPROC::ACCOUNT_NUM, strAccountNum );
         if( strAccountNum != NULL_STRING )
         {
            //get the ShrNum
            MFAccount *pMFAccount;
            DSTCWorkSession *dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
            if( dstcWorkSession->getMFAccount( getDataGroupId(), strAccountNum, pMFAccount) )
            {
               pMFAccount->getField( ifds::ShrNum, strShrNum, getDataGroupId(), false );
               setParameter( ACCINFOPROC::SHAREHOLDER_NUM, strShrNum );
               setParameter( ACCINFOPROC::MODEL_ACCOUNT_NUM, strAccountNum );
               eRtn = invokeCommand( CMD_BPROC_NASU, PROC_NO_TYPE, true, NULL );
               switch( eRtn )
               {
                  case CMD_OK:
                  case CMD_MODELESS_INPROCESS:
                     break;
                  case CMD_CANCEL:
                     return(false);
                  default:
                     return(false);
               }
            }
         }
      }
      catch( ... )
      {
         ADDCONDITIONFROMFILE( CND::BP_ERR_UNKNOWN_EXCEPTION );
         return(false);
      }
      if( GETCURRENTHIGHESTSEVERITY() <= WARNING )
      {
         DString accountNum;
         getGlobal( WORK_GLOBAL, ifds::LastActiveAccountNum, accountNum );
         setParameter(IDENTACCPROC::ACCOUNT_NUM, accountNum);
      }
   }
   if( GETCURRENTHIGHESTSEVERITY() <= WARNING )
      return(true);
   else
      return(false);
}
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/IdentAccProcess.cpp-arc  $
 * 
 *    Rev 1.31   Jul 19 2012 12:08:34   dchatcha
 * P0179630 FN01 FATCA Project - Entity level.
 * 
 *    Rev 1.30   12 Jul 2007 17:09:58   popescu
 * AIM GAP 2 AMS - added an extra field to trading CloneAcctAMS - used in AllTransfer to copy AMS to the to acct.
 * 
 *    Rev 1.29   Aug 11 2004 11:59:50   AGUILAAM
 * PET1117_FN02:  Account Static enhancement for SSBG - added new acct categories, and contact person, registrationinfo fields
 * 
 *    Rev 1.28   Jul 02 2003 15:44:18   HERNANDO
 * Added Field Details for AcctType.
 * 
 *    Rev 1.27   Jun 06 2003 14:51:10   PURDYECH
 * Was using BP_ERR_UNKNOWN_EXCEPTION and should have been using ERR_UNKNOWN_EXCEPTION
 * 
 *    Rev 1.26   Mar 21 2003 17:41:48   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.25   Mar 07 2003 15:01:00   PURDYECH
 * Fixed some bad container IDs
 * 
 *    Rev 1.24   Oct 09 2002 23:53:18   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.23   Sep 30 2002 11:01:04   PURDYECH
 * BFFieldId no longer has operator long(), so explicit getId() calls are needed in places.
 * 
 *    Rev 1.22   Aug 29 2002 16:44:58   SMITHDAV
 * Condition split.
 * 
 *    Rev 1.21   Aug 29 2002 12:54:24   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.20   22 May 2002 18:24:20   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.19   27 Mar 2002 19:54:58   PURDYECH
 * Process/WindowFactory overhaul
 * 
 *    Rev 1.18   17 Jan 2002 10:51:38   KOVACSRO
 * If user did not do a search, leave AccountNum empty.
 * 
 *    Rev 1.17   Aug 10 2001 12:57:22   YINGBAOL
 * disable NASU if it is launched from systematic and allocation
 * 
 *    Rev 1.16   08 Aug 2001 12:17:14   HSUCHIN
 * beautified source
 * 
 *    Rev 1.15   08 Aug 2001 12:15:50   HSUCHIN
 * bug fix to performsearch to display error conditions properly
 * 
 *    Rev 1.14   15 May 2001 15:38:46   YINGZ
 * data group id clean up
 * 
 *    Rev 1.13   03 May 2001 14:05:26   SMITHDAV
 * Session management restructuring.
 * 
 *    Rev 1.12   Mar 23 2001 16:39:18   OLTEANCR
 * fixed bug
 * 
 *    Rev 1.11   15 Dec 2000 12:43:32   PURDYECH
 * Use precompiled header stdafx.h.
 * Removed unnecessary header files.
 * 
 *    Rev 1.10   Nov 13 2000 12:24:50   DINACORN
 * addFieldDetails for InterAccount and AltAccount
 * 
 *    Rev 1.9   Oct 19 2000 17:16:20   KOVACSRO
 * Bug fixed.
 * 
 *    Rev 1.8   Oct 11 2000 14:23:02   KOVACSRO
 * Implemented doSend().
 * 
 *    Rev 1.7   Aug 02 2000 15:32:02   BUZILA
 * "locale" changes
 * 
 *    Rev 1.6   Mar 08 2000 13:05:32   POPESCUS
 * search only for the account holders
 * 
 *    Rev 1.5   Mar 07 2000 17:01:34   POPESCUS
 * display kana and kanji name
 * 
 *    Rev 1.4   Mar 07 2000 15:45:02   POPESCUS
 * more work on the account search screen
 * 
 *    Rev 1.3   Mar 03 2000 19:34:02   POPESCUS
 * save the work
 * 
 *    Rev 1.2   Mar 03 2000 12:11:08   POPESCUS
 * account search work
 * 
 *    Rev 1.1   Feb 29 2000 15:37:00   BUZILA
 * changes
// 
*/
