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
// ^FILE   : RespBenRelProcess.cpp
// ^AUTHOR : Robert Kovacs
// ^DATE   : 20/07/2000
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : RespBenRelProcess
//    This class manages RESP Beneficiary Relationships.
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include "stdafx.h"
#include "respbenrelprocess.hpp"
#include "respbenrelprocessincludes.h"
#include <ifastcbo\accountentityxref.hpp>
#include <ifastcbo\mfaccount.hpp>
#include <ifastcbo\mgmtco.hpp>
#include <ifastcbo\entity.hpp>
#include "entityprocessincludes.h"
extern IFASTBP_LINKAGE const I_CHAR* CMD_GUI_RESPBENREL;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_RESPBENREL;
#include <bfproc\concreteprocesscreator.hpp>
static ConcreteProcessCreator< RespBenRelProcess > processCreator( CMD_BPROC_RESPBENREL );

namespace CND
{  // Conditions used
   extern CLASS_IMPORT const long BP_ERR_UNKNOWN_EXCEPTION;
   extern const long BP_ERR_RESP_BENEFICIARY;

}

namespace RESPBEN  
{
   const I_CHAR * const ACCOUNT_NUMBER   = I_( "AccountNum" );
   const I_CHAR * const CURRENT_RESP_BEN = I_( "CurrentRespBen" );
   const I_CHAR * const BTN_JOIN         = I_( "Btn Join");
   const I_CHAR * const BTN_REMOVE       = I_( "Btn Remove");
   const I_CHAR * const ENTITY_ID        = I_( "EntityId" );

}

namespace
{
   // Trace literals
   const I_CHAR *CLASSNAME = I_( "RespBenRelProcess" );

   const I_CHAR * const Y             = I_( "Y" );
   const I_CHAR * const N             = I_( "N" );
   const DString EMPTY_STRING;

}



//******************************************************************************
//              Public Methods
//******************************************************************************

//CP20030319RespBenRelProcess::RespBenRelProcess()
RespBenRelProcess::RespBenRelProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: AbstractProcess( pGIC, pGIParent, rCommand )
{
   TRACE_CONSTRUCTOR( CLASSNAME, "" );

   addContainer( IFASTBP_PROC::RESP_ACCOUNT_BEN,  true, BF::NullContainerId, true );//repeatable and updatable
   addContainer( IFASTBP_PROC::RESP_BEN_TO_JOIN_LIST,  true );
   addContainer( IFASTBP_PROC::RESP_BEN_JOINED_LIST,  true );


   addFieldDetails( ifds::LastName,      IFASTBP_PROC::RESP_ACCOUNT_BEN );
   addFieldDetails( ifds::FirstName,     IFASTBP_PROC::RESP_ACCOUNT_BEN );
   addFieldDetails( ifds::EntityType,    IFASTBP_PROC::RESP_ACCOUNT_BEN );
   addFieldDetails( ifds::RESPParentSeq, IFASTBP_PROC::RESP_ACCOUNT_BEN );
   addFieldDetails( ifds::RESPDesInstSeq,IFASTBP_PROC::RESP_ACCOUNT_BEN );

   addFieldDetails( ifds::LastName,      IFASTBP_PROC::RESP_BEN_TO_JOIN_LIST  );
   addFieldDetails( ifds::FirstName,     IFASTBP_PROC::RESP_BEN_TO_JOIN_LIST );
   addFieldDetails( ifds::EntityType,    IFASTBP_PROC::RESP_BEN_TO_JOIN_LIST );
   addFieldDetails( ifds::SeqNumber,     IFASTBP_PROC::RESP_BEN_TO_JOIN_LIST  );

   addFieldDetails( ifds::LastName,      IFASTBP_PROC::RESP_BEN_JOINED_LIST  );
   addFieldDetails( ifds::FirstName,     IFASTBP_PROC::RESP_BEN_JOINED_LIST );
   addFieldDetails( ifds::EntityType,    IFASTBP_PROC::RESP_BEN_JOINED_LIST );
   addFieldDetails( ifds::SeqNumber,     IFASTBP_PROC::RESP_BEN_JOINED_LIST );

}

//******************************************************************************

RespBenRelProcess::~RespBenRelProcess()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************
//              Protected Methods
//******************************************************************************

SEVERITY RespBenRelProcess::doInit()
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, DOINIT );
   SEVERITY sevRtn = SEVERE_ERROR;

   try
   {
      DSTCWorkSession *dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());

      sevRtn = dstcWorkSession->getAccountEntityXref( BF::HOST, _pAccountEntityXref );

      getParameter( RESPBEN::ACCOUNT_NUMBER, _strAccountNumber );
      getParameter( RESPBEN::ENTITY_ID, _strCurrEntityId);

      if( _strAccountNumber != NULL_STRING )
      {
         _strAccountNumber.stripLeading( '0' );
         _pAccountEntityXref->setCurrentAccounNum( _strAccountNumber ); 
      }
      else
         return(sevRtn);
      if( _strCurrEntityId != NULL_STRING )
         _strCurrEntityId.stripLeading( '0' );

      sevRtn = _pAccountEntityXref->PopulateEntitiesList( getDataGroupId(), _strAccountNumber );

      if( WARNING >= sevRtn )
      {
         setContainer( IFASTBP_PROC::RESP_ACCOUNT_BEN, _pAccountEntityXref );
         setContainer( IFASTBP_PROC::RESP_BEN_TO_JOIN_LIST, _pAccountEntityXref );
         setContainer( IFASTBP_PROC::RESP_BEN_JOINED_LIST, _pAccountEntityXref );
      }
      else
         return(GETCURRENTHIGHESTSEVERITY());
      //get the entity for _strCurrEntityId, and get it's full name, in order to pass it to the dlg.
      Entity * selectedEntity;
      const BFDataGroupId& idDataGroup = getDataGroupId();
      dstcWorkSession->getEntity(idDataGroup, _strCurrEntityId, selectedEntity);
      DString strFirstName;
      DString strLastName;
      selectedEntity->getField( ifds::FirstName, strFirstName, idDataGroup );
      selectedEntity->getField( ifds::LastName, strLastName, idDataGroup );
      _strCurrentRespBenName = strFirstName + I_(" ") + strLastName;
   }
   catch( ConditionException &ce )
   {
      SETCONDITIONFROMEXCEPTION( ce );
   }
   catch( ... )
   {
      //assert( 0 );
      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, DOINIT, CND::BP_ERR_UNKNOWN_EXCEPTION );
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************

E_COMMANDRETURN RespBenRelProcess::doProcess()
{  
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, DOPROCESS );
   E_COMMANDRETURN rtn = CMD_FAILURE;
   setParameter( RESPBEN::ACCOUNT_NUMBER, _strAccountNumber );
   setParameter( RESPBEN::CURRENT_RESP_BEN, _strCurrentRespBenName );
   try
   {
      rtn = invokeCommand( this, CMD_GUI_RESPBENREL, getProcessType(),
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

const DString& RespBenRelProcess::getFirstListItemKey( const GenericInterface *rpGICaller, const BFContainerId& idList )
{  
   TRACE_METHOD( CLASSNAME, GETFIRSTLISTITEMKEY );

   DString key;
   const BFDataGroupId& idDataGroup = getDataGroupId();

   try
   {

      if( idList == IFASTBP_PROC::RESP_ACCOUNT_BEN )
      {
         BFObjIter iterAccountEntityXrefOut( *_pAccountEntityXref, getDataGroupId(), true, BFObjIter::ITERTYPE::NON_DELETED, false, true );
         DString searchKey;
         iterAccountEntityXrefOut.begin( OBJ_TYPE_NONE, OBJ_ACTIVITY_NONE, searchKey );
         while( !iterAccountEntityXrefOut.end() )
         {
            DString entityType;
            DString firstName, lastName;
            iterAccountEntityXrefOut.getObject()->getField(ifds::EntityType, entityType, idDataGroup);
            iterAccountEntityXrefOut.getObject()->getField(ifds::FirstName, firstName, idDataGroup);
            iterAccountEntityXrefOut.getObject()->getField(ifds::LastName, lastName, idDataGroup);

            if( entityType == I_("50") )
            {
               DString key = iterAccountEntityXrefOut.getStringKey();
               setCurrentListItem( rpGICaller, idList, key );
               return(iterAccountEntityXrefOut.getStringKey());
            }
            ++iterAccountEntityXrefOut;
         }
         return(EMPTY_STRING);
      }
      else if( idList == IFASTBP_PROC::RESP_BEN_TO_JOIN_LIST )
      {
         BFObjIter iterAccountEntityXrefOut( *_pAccountEntityXref, getDataGroupId(), true, BFObjIter::ITERTYPE::NON_DELETED, false, true );
         DString searchKey;
         iterAccountEntityXrefOut.begin( OBJ_TYPE_NONE, OBJ_ACTIVITY_NONE, searchKey );
         while( !iterAccountEntityXrefOut.end() )
         {
            DString entityType;
            iterAccountEntityXrefOut.getObject()->getField(ifds::EntityType, entityType, idDataGroup);
            if( (entityType == I_("51")) || (entityType == I_("52")) )
            {
               DString key = iterAccountEntityXrefOut.getStringKey();
               setCurrentListItem( rpGICaller, idList, key );
               return(iterAccountEntityXrefOut.getStringKey());
            }
            ++iterAccountEntityXrefOut;
         }
         return(EMPTY_STRING);
      }
      else if( idList == IFASTBP_PROC::RESP_BEN_JOINED_LIST )
      {
         updateRESPPISeqs(rpGICaller);
         bDesInsDisplayed = false;
         BFObjIter iterAccountEntityXrefOut( *_pAccountEntityXref, getDataGroupId(), true, BFObjIter::ITERTYPE::NON_DELETED, false, true );
         DString searchKey;
         iterAccountEntityXrefOut.begin( OBJ_TYPE_NONE, OBJ_ACTIVITY_NONE, searchKey );
         if( strRESPParentSeq != NULL_STRING ) //a parent / legal guardian
         {
            while( !iterAccountEntityXrefOut.end() )
            {
               DString strEntityType;
               iterAccountEntityXrefOut.getObject()->getField(ifds::EntityType, strEntityType, idDataGroup);
               if( strEntityType == I_("51") )
               {
                  DString strSeqNumber;
                  iterAccountEntityXrefOut.getObject()->getField(ifds::SeqNumber, strSeqNumber, idDataGroup);
                  if( strSeqNumber.stripLeading( '0' ) == strRESPParentSeq )
                  {
                     DString key = iterAccountEntityXrefOut.getStringKey();
                     setCurrentListItem( rpGICaller, idList, key );
                     return(iterAccountEntityXrefOut.getStringKey());
                  }
               }
               ++iterAccountEntityXrefOut;
            }
         }
         iterAccountEntityXrefOut.begin( OBJ_TYPE_NONE, OBJ_ACTIVITY_NONE, searchKey ); 
         if( strRESPDesInstSeq != NULL_STRING ) //a designated institution
         {
            while( !iterAccountEntityXrefOut.end() )
            {
               DString strEntityType;
               iterAccountEntityXrefOut.getObject()->getField(ifds::EntityType, strEntityType, idDataGroup);
               if( strEntityType == I_("52") )
               {
                  DString strSeqNumber ;
                  iterAccountEntityXrefOut.getObject()->getField(ifds::SeqNumber, strSeqNumber, idDataGroup);
                  if( strSeqNumber.stripLeading( '0' ) == strRESPDesInstSeq )
                  {
                     bDesInsDisplayed = true;
                     DString key = iterAccountEntityXrefOut.getStringKey();
                     setCurrentListItem( rpGICaller, idList, key );
                     return(iterAccountEntityXrefOut.getStringKey());
                  }
               }
               ++iterAccountEntityXrefOut;
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

const DString& RespBenRelProcess::getNextListItemKey( const GenericInterface *rpGICaller, const BFContainerId& idList )
{  
   TRACE_METHOD( CLASSNAME, GETNEXTLISTITEMKEY );
   DString key;
   const BFDataGroupId& idDataGroup = getDataGroupId();

   try
   {
      if( idList == IFASTBP_PROC::RESP_ACCOUNT_BEN )
      {
         BFObjIter iterAccountEntityXrefOut( *_pAccountEntityXref, getDataGroupId(), true, BFObjIter::ITERTYPE::NON_DELETED, false, true );
         DString searchKey;
         iterAccountEntityXrefOut.begin( OBJ_TYPE_NONE, OBJ_ACTIVITY_NONE, searchKey );
         DString entityListCurrentItemKey = getCurrentListItemKey( rpGICaller, idList );
         iterAccountEntityXrefOut.positionByKey( entityListCurrentItemKey );
         ++iterAccountEntityXrefOut;
         while( !iterAccountEntityXrefOut.end() )
         {
            DString entityType;
            iterAccountEntityXrefOut.getObject()->getField(ifds::EntityType, entityType, idDataGroup);
            if( entityType == I_("50") )
            {
               DString key = iterAccountEntityXrefOut.getStringKey();
               setCurrentListItem( rpGICaller, idList, key );
               return(iterAccountEntityXrefOut.getStringKey());
            }
            ++iterAccountEntityXrefOut;
         }
         return(EMPTY_STRING);
      }
      else if( idList == IFASTBP_PROC::RESP_BEN_TO_JOIN_LIST )
      {
         BFObjIter iterAccountEntityXrefOut( *_pAccountEntityXref, getDataGroupId(), true, BFObjIter::ITERTYPE::NON_DELETED, false, true );
         DString searchKey;
         AccountEntityXref::buildPartialKeyForAccount(searchKey, _strAccountNumber);

         iterAccountEntityXrefOut.begin( OBJ_TYPE_NONE, OBJ_ACTIVITY_NONE, searchKey );
         DString entityListCurrentItemKey = getCurrentListItemKey( rpGICaller, idList );
         iterAccountEntityXrefOut.positionByKey( entityListCurrentItemKey );
         ++iterAccountEntityXrefOut;
         while( !iterAccountEntityXrefOut.end() )
         {
            DString entityType;
            iterAccountEntityXrefOut.getObject()->getField(ifds::EntityType, entityType, idDataGroup);
            if( (entityType == I_("51")) || (entityType == I_("52")) )
            {

               DString key = iterAccountEntityXrefOut.getStringKey();
               setCurrentListItem( rpGICaller, idList, key );
               return(iterAccountEntityXrefOut.getStringKey());
            }
            ++iterAccountEntityXrefOut;
         }
         return(EMPTY_STRING);
      }
      else if( idList == IFASTBP_PROC::RESP_BEN_JOINED_LIST )
      {
         updateRESPPISeqs(rpGICaller);
         BFObjIter iterAccountEntityXrefOut( *_pAccountEntityXref, getDataGroupId(), true, BFObjIter::ITERTYPE::NON_DELETED, false, true );
         DString searchKey;
         iterAccountEntityXrefOut.begin( OBJ_TYPE_NONE, OBJ_ACTIVITY_NONE, searchKey ); 
         if( (strRESPDesInstSeq != NULL_STRING) && !bDesInsDisplayed )//don't check here for a parent / legal guardian (because we can have at most one)
         //and only return the designated institution if it was not returned by getFirst...
         {
            while( !iterAccountEntityXrefOut.end() )
            {
               DString entityType;
               iterAccountEntityXrefOut.getObject()->getField(ifds::EntityType, entityType, idDataGroup);
               if( entityType == I_("52") )
               {
                  DString strSeqNumber ;
                  iterAccountEntityXrefOut.getObject()->getField(ifds::SeqNumber, strSeqNumber, idDataGroup);
                  if( strSeqNumber.stripLeading( '0' ) == strRESPDesInstSeq )
                  {
                     DString key = iterAccountEntityXrefOut.getStringKey();
                     setCurrentListItem( rpGICaller, idList, key );
                     bDesInsDisplayed = true;
                     return(iterAccountEntityXrefOut.getStringKey());
                  }
               }
               ++iterAccountEntityXrefOut;
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
      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, GETNEXTLISTITEMKEY,
                      CND::BP_ERR_UNKNOWN_EXCEPTION );
   }
   return(AbstractProcess::getNextListItemKey( rpGICaller, idList ));
}

//******************************************************************************

void RespBenRelProcess::setCurrentListItem(
                                          const GenericInterface *rpGICaller,
                                          const BFContainerId& idList,
                                          const DString& strListItemKey
                                          )
{  
   TRACE_METHOD( CLASSNAME, I_( "setCurrentListItem" ) );

//CP20030319   switch( idList )
//CP20030319   {
//CP20030319      case RESPBEN::RESP_ACCOUNT_BEN:
   if( IFASTBP_PROC::RESP_ACCOUNT_BEN == idList )
   {
      if( strListItemKey == I_( "RESET" ) )
      {
         setContainer( IFASTBP_PROC::RESP_ACCOUNT_BEN, NULL );
         setContainer( IFASTBP_PROC::RESP_ACCOUNT_BEN, _pAccountEntityXref );
         getFirstListItemKey( rpGICaller, idList );
         return;
      }
//CP20030319         break;

//CP20030319      case RESPBEN::RESP_BEN_TO_JOIN_LIST:
   }
   else if( IFASTBP_PROC::RESP_BEN_TO_JOIN_LIST == idList )
   {
//CP20030319         break;
//CP20030319   }
   }

   AbstractProcess::setCurrentListItem( rpGICaller, idList, strListItemKey );
   return;
}

//******************************************************************************

void RespBenRelProcess::updateRESPPISeqs(const GenericInterface *rpGICaller)
{
   TRACE_METHOD( CLASSNAME, I_("updateRESPPISeqs") );
   const BFDataGroupId& idDataGroup = getDataGroupId();
   DString entityListCurrentItemKey = getCurrentListItemKey( rpGICaller, IFASTBP_PROC::RESP_ACCOUNT_BEN );//get the current RESP Ben (type 50)
   BFObjIter iterAccountEntityXrefOut( *_pAccountEntityXref, idDataGroup, true, BFObjIter::ITERTYPE::NON_DELETED );
   iterAccountEntityXrefOut.positionByKey( entityListCurrentItemKey );
   if( iterAccountEntityXrefOut.getObject() )
   {
      iterAccountEntityXrefOut.getObject()->getField(ifds::RESPParentSeq, strRESPParentSeq, idDataGroup);
      iterAccountEntityXrefOut.getObject()->getField(ifds::RESPDesInstSeq, strRESPDesInstSeq, idDataGroup);    
      strRESPParentSeq.stripLeading( '0' );
      strRESPDesInstSeq.stripLeading( '0' );
   }
   else
   {
      strRESPParentSeq  = NULL_STRING;
      strRESPDesInstSeq = NULL_STRING;
   }
}

//******************************************************************************

bool RespBenRelProcess::doSend( GenericInterface * rpGICaller, const I_CHAR * szMessage )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTBP_CONDITION, CLASSNAME, I_( "doSend" ) );
   DString dstrMessage = szMessage;
   SEVERITY sev = NO_CONDITION;
   if( dstrMessage == RESPBEN::BTN_JOIN )
   {

      DString strEntityType;
      DString strSeqNo;
      DString strOldValue;

      getField(rpGICaller, IFASTBP_PROC::RESP_BEN_TO_JOIN_LIST, ifds::EntityType, strEntityType, false);
      getField(rpGICaller, IFASTBP_PROC::RESP_BEN_TO_JOIN_LIST, ifds::SeqNumber, strSeqNo, false);
      strEntityType.strip();
      strSeqNo.strip().stripLeading('0');

      DString entityListCurrentItemKey = getCurrentListItemKey( rpGICaller, IFASTBP_PROC::RESP_ACCOUNT_BEN );//get the current RESP Ben (type 50) - for debugging only

      if( strEntityType == I_("51") )
      {
         getField(rpGICaller, IFASTBP_PROC::RESP_ACCOUNT_BEN, ifds::RESPParentSeq, strOldValue, false);
         if( strOldValue.strip().stripLeading('0') == NULL_STRING )
            sev = setField(rpGICaller, IFASTBP_PROC::RESP_ACCOUNT_BEN, ifds::RESPParentSeq, strSeqNo, false);
         else
            ADDCONDITIONFROMFILE( CND::BP_ERR_RESP_BENEFICIARY );
      }
      if( strEntityType == I_("52") )
      {
         getField(rpGICaller, IFASTBP_PROC::RESP_ACCOUNT_BEN, ifds::RESPDesInstSeq, strOldValue, false);
         if( strOldValue.strip().stripLeading('0') == NULL_STRING )
            sev = setField(rpGICaller, IFASTBP_PROC::RESP_ACCOUNT_BEN, ifds::RESPDesInstSeq, strSeqNo, false);
         else
            ADDCONDITIONFROMFILE( CND::BP_ERR_RESP_BENEFICIARY );
      }
   }
   if( dstrMessage == RESPBEN::BTN_REMOVE )
   {
      DString strEntityType;

      getField(rpGICaller, IFASTBP_PROC::RESP_BEN_JOINED_LIST, ifds::EntityType, strEntityType, false);
      if( strEntityType == I_("51") )
         sev = setField(rpGICaller, IFASTBP_PROC::RESP_ACCOUNT_BEN, ifds::RESPParentSeq, NULL_STRING, false);
      if( strEntityType == I_("52") )
         sev = setField(rpGICaller, IFASTBP_PROC::RESP_ACCOUNT_BEN, ifds::RESPDesInstSeq, NULL_STRING, false);
   }
   sev = GETCURRENTHIGHESTSEVERITY();
   if( sev == NO_CONDITION )
      return(true);
   else
      return(false);
}

//******************************************************************************
SEVERITY RespBenRelProcess::doValidateAll( BFAbstractCBO *rpWSD, const BFDataGroupId& idDataGroup )
{
   //don't want to do any validation here
   return(NO_CONDITION);
}
//******************************************************************************

/*void *RespBenRelProcess::getPtrForContainer( const BFContainerId& idContainer, const BFDataGroupId& idDataGroup )
{
   void *ptr = NULL;
   SEVERITY sevRtn = NO_CONDITION;

   // How do we handle init conditions??  (throw them?)
   try
   {
      switch( idContainer )
      {
      case RESPBEN::RESP_BEN_TO_JOIN_LIST:
      case RESPBEN::RESP_BEN_JOINED_LIST:
      case RESPBEN::RESP_ACCOUNT_BEN:
      {
               ptr = _pAccountEntityXref;
         }
         break;
      }
   }
   catch( ConditionException & )
   {
      throw;
   }
   catch(...)
   {  
      assert( 0 );
      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, DOINIT,
         CND::BP_ERR_UNKNOWN_EXCEPTION );
   }
   return ptr;
}*/
