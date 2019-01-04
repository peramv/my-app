//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by IFDS Co., Ltd.,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2016 by IFDS Co., Ltd.
//
//******************************************************************************
//
// ^FILE   : ExternalInstitutionSearchProcess.cpp
// ^AUTHOR : 
// ^DATE   : Mar 2016
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : ExternalInstitutionSearchProcess
//    This class manages searching for external insitution.
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include "stdafx.h"
#include "ExternalInstitutionSearchProcess.hpp"

#include <ifastcbo\externalinstitution.hpp>
#include <ifastcbo\externalinstitutionlist.hpp>
#include <ifastcbo\mgmtco.hpp>
#include <ifastcbo\trade.hpp>
#include <ifastcbo\worksessiontradeslist.hpp>

extern IFASTBP_LINKAGE const I_CHAR* CMD_GUI_EXTERNAL_INSTITUTION_SEARCH;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_EXTERNAL_INSTITUTION_SEARCH;

#include <bfproc\concreteprocesscreator.hpp>
static ConcreteProcessCreator< ExternalInstitutionSearchProcess > processCreator( CMD_BPROC_EXTERNAL_INSTITUTION_SEARCH );

namespace
{
   // Trace literals
   const I_CHAR * CLASSNAME                   = I_( "ExternalInstitutionSearch" );
   const I_CHAR * const PERFORMSEARCH         = I_( "performSearch" );
   const I_CHAR * YES                         = I_( "Y" );
   const I_CHAR * const REG_PLAN_TRANSFER     = I_("RegPlanTransfer");

}

namespace IFASTBP_PROC
{
   extern IFASTBP_LINKAGE const BFContainerId TRADE;
   extern IFASTBP_LINKAGE const BFContainerId EXTERNAL_INSTITUTION;
   extern IFASTBP_LINKAGE const BFContainerId EXTERNAL_INSTITUTION_SEARCH;
}

namespace CND
{
   extern CLASS_IMPORT const long BP_ERR_UNKNOWN_EXCEPTION;
   extern CLASS_IMPORT const long BP_ERR_INVALID_METHOD_CALL;
}

namespace ifds
{
    extern CLASS_IMPORT const BFTextFieldId CompanyName;
    extern CLASS_IMPORT const BFTextFieldId CompanyCode;
    extern CLASS_IMPORT const BFTextFieldId SearchType;
    extern CLASS_IMPORT const BFTextFieldId KeyString;
    extern CLASS_IMPORT const BFTextFieldId ExternalInstitution;
    extern CLASS_IMPORT const BFTextFieldId SearchExternalInstitution;
    extern CLASS_IMPORT const BFTextFieldId SearchExternalInstitutionUsing;
}

namespace MFCAN_IP_PARAM
{
//list key
   extern IFASTBP_LINKAGE const I_CHAR * const LIST_KEY;
   extern IFASTBP_LINKAGE const I_CHAR * const CALLER;
}

//******************************************************************************
//              Public Methods
//******************************************************************************

ExternalInstitutionSearchProcess::ExternalInstitutionSearchProcess ( GenericInterfaceContainer* pGIC, 
   GenericInterface* pGIParent, const Command& rCommand)
: AbstractProcess( pGIC, pGIParent, rCommand )
, _searchExternalInstitution(NULL_STRING)
, _searchExternalInstitutionUsing(NULL_STRING)
, _searchKey(NULL_STRING)
, _fPropExternalInstitution(nullptr)
, _fPropSearchExternalInstitution(nullptr)
, _fPropSearchExternalInstitutionUsing(nullptr)
, _fPropKeyString(nullptr)
, _pExternalInstitutionList(nullptr)
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );

   addContainer (IFASTBP_PROC::TRADE, false, BF::NullContainerId, true, I_("Trade"));
   addContainer (IFASTBP_PROC::EXTERNAL_INSTITUTION_SEARCH, false, BF::NullContainerId, true);
   addContainer (IFASTBP_PROC::EXTERNAL_INSTITUTION, true, BF::NullContainerId);

   addFieldDetails (ifds::ExternalInstitution,             IFASTBP_PROC::EXTERNAL_INSTITUTION_SEARCH, SUBCLASS_PROCESS);
   addFieldDetails (ifds::SearchExternalInstitution,       IFASTBP_PROC::EXTERNAL_INSTITUTION_SEARCH, SUBCLASS_PROCESS);
   addFieldDetails (ifds::SearchExternalInstitutionUsing,  IFASTBP_PROC::EXTERNAL_INSTITUTION_SEARCH, SUBCLASS_PROCESS);
   addFieldDetails (ifds::KeyString,                       IFASTBP_PROC::EXTERNAL_INSTITUTION_SEARCH, SUBCLASS_PROCESS);

   addFieldDetails (ifds::CompanyName     , IFASTBP_PROC::EXTERNAL_INSTITUTION );
   addFieldDetails (ifds::CompanyCode     , IFASTBP_PROC::EXTERNAL_INSTITUTION );
}

//******************************************************************************

ExternalInstitutionSearchProcess::~ExternalInstitutionSearchProcess()
{
   TRACE_DESTRUCTOR( CLASSNAME );

   if (_fPropExternalInstitution!=nullptr)
   {
      delete _fPropExternalInstitution;
      _fPropExternalInstitution = nullptr;
   }

   if (_fPropKeyString!=nullptr)
   {
      delete _fPropKeyString;
      _fPropKeyString = nullptr;
   }

   if (_fPropSearchExternalInstitution!=nullptr)
   {
      delete _fPropSearchExternalInstitution;
      _fPropSearchExternalInstitution = nullptr;
   }

   if (_fPropSearchExternalInstitutionUsing!=nullptr)
   {
      delete _fPropSearchExternalInstitutionUsing;
      _fPropSearchExternalInstitutionUsing = nullptr;
   }
}

//******************************************************************************
//              Protected Methods
//******************************************************************************

SEVERITY ExternalInstitutionSearchProcess::doInit()
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, DOINIT );
   SEVERITY sevRtn = SEVERE_ERROR;
   try
   {
      getParameter (MFCAN_IP_PARAM::LIST_KEY, _TradeListKey);
      getParameter (MFCAN_IP_PARAM::CALLER,   _caller);
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
E_COMMANDRETURN ExternalInstitutionSearchProcess::doProcess()
{  
   MAKEFRAME2( CND::BPBASE_CONDITION, CLASSNAME, DOPROCESS );
   E_COMMANDRETURN rtn = CMD_FAILURE;

   try
   {
      rtn = invokeCommand( this, CMD_GUI_EXTERNAL_INSTITUTION_SEARCH, getProcessType(), isModal(), &m_rpChildGI );
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

void ExternalInstitutionSearchProcess::doPostOk( GenericInterface *rpGICaller, bool bSuccessFlag )
{
   DString strMarket = DSTCommonFunctions::getMarket();

   if( bSuccessFlag )
   {
      DString extInstitutionCode;
      
      if (isContainerValid(IFASTBP_PROC::EXTERNAL_INSTITUTION))
      {
          DString CurrentItemKey = getCurrentListItemKey( this, IFASTBP_PROC::EXTERNAL_INSTITUTION );
          if( NULL_STRING != CurrentItemKey ) 
          {
              ExternalInstitution *pExternalInstitution = nullptr;
              pExternalInstitution = dynamic_cast<ExternalInstitution*>( getCBOItem(IFASTBP_PROC::EXTERNAL_INSTITUTION, getDataGroupId() ) );
              if( pExternalInstitution != nullptr)
              {
                  pExternalInstitution->getField(ifds::CompanyCode,extInstitutionCode, getDataGroupId(),false);
                  extInstitutionCode.strip().upperCase();
              }
          }
      }

      setParameter (I_("ExternalInstitution"), extInstitutionCode);
   }
}

//******************************************************************************

void ExternalInstitutionSearchProcess::doGetField(
                                 const GenericInterface *rpGICaller,
                                 const BFContainerId& idContainer,
                                 const BFFieldId& idField,
                                 const BFDataGroupId& idDataGroup,
                                 DString &strValueOut,
                                 bool bFormatted
                                 ) const
{
   if (idField == ifds::SearchExternalInstitution)
   {
      strValueOut = _searchExternalInstitution;
   }
   else if (idField == ifds::SearchExternalInstitutionUsing)
   {
      strValueOut = _searchExternalInstitutionUsing;
   }
   else if (idField == ifds::KeyString)
   {
      strValueOut = _searchKey;
   }
}

//******************************************************************************
SEVERITY ExternalInstitutionSearchProcess::performSearch( GenericInterface *rpGICaller, const BFContainerId& idSearch, E_SEARCHACTION eSearchAction )
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, PERFORMSEARCH );
   SEVERITY sevRtn = SEVERE_ERROR;

   try
   {
      if( idSearch == IFASTBP_PROC::EXTERNAL_INSTITUTION_SEARCH )
      {
         DString searchBy, searchKey;
         getField (this, IFASTBP_PROC::EXTERNAL_INSTITUTION_SEARCH, ifds::SearchExternalInstitutionUsing, searchBy, false);
         getField (this, IFASTBP_PROC::EXTERNAL_INSTITUTION_SEARCH, ifds::KeyString, searchKey, false);
         searchBy.strip().upperCase();
         searchKey.strip().upperCase();

         ExternalInstitutionList *pExternalInstitutionList = nullptr;
         if(REG_PLAN_TRANSFER == _caller)
         {
            DSTCWorkSession *pDSTCWorkSession = dynamic_cast<DSTCWorkSession *> (getBFWorkSession());
            if(pDSTCWorkSession != nullptr)
                 pDSTCWorkSession->getExternalInstitutionList(pExternalInstitutionList,getDataGroupId());
         }
         else
         {
            Trade *pTrade = dynamic_cast <Trade*> (getCBOItem (IFASTBP_PROC::TRADE, getDataGroupId()));
            if(pTrade != nullptr)
                 pTrade->getExternalInstitutionList(pExternalInstitutionList,getDataGroupId());
         };

         if( eSearchAction == SEARCH_START )
         {
            if ( pExternalInstitutionList != nullptr)
            {
               sevRtn = pExternalInstitutionList->doSearch(false,searchBy,searchKey,getDataGroupId());
               setContainer(IFASTBP_PROC::EXTERNAL_INSTITUTION,NULL);
               setContainer(IFASTBP_PROC::EXTERNAL_INSTITUTION,pExternalInstitutionList);
               _pExternalInstitutionList = pExternalInstitutionList;
            }
         }
         else // SEARCH_NEXT_BLOCK
         {
            if ( pExternalInstitutionList != nullptr)
            {
               sevRtn = pExternalInstitutionList->doSearch(true,searchBy,searchKey,getDataGroupId());
               setContainer(IFASTBP_PROC::EXTERNAL_INSTITUTION,NULL);
               setContainer(IFASTBP_PROC::EXTERNAL_INSTITUTION,pExternalInstitutionList);
               _pExternalInstitutionList = pExternalInstitutionList;
            }
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

   return(sevRtn); 
}

//******************************************************************************
void *ExternalInstitutionSearchProcess::getPtrForContainer( const BFContainerId& idContainer,
                                                            const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2(CND::BPBASE_CONDITION, CLASSNAME, I_("getPtrForContainer"));
   
   void *ptr = NULL;
   SEVERITY sevRtn = SEVERE_ERROR;

   DSTCWorkSession *pDSTCWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
   try
   {  
      if( IFASTBP_PROC::EXTERNAL_INSTITUTION == idContainer )
      {
         ptr = _pExternalInstitutionList;
      }
      else if (IFASTBP_PROC::TRADE == idContainer)
      {
         WorksessionTradesList *pTradesList (NULL);

         if( pDSTCWorkSession->getTradesList (pTradesList, idDataGroup) <= WARNING && 
            pTradesList)
         {
            BFObjIter iter (*pTradesList, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED);

            iter.positionByKey (_TradeListKey);
            if (!iter.end())
            {
               ptr = dynamic_cast <Trade*>(iter.getObject());
            }
         }
      }
   }
   catch (ConditionException &)
   {
      throw;
   }
   catch (...)
   {
      assert(0);
      THROWFROMFILE2(CND::BPBASE_CONDITION, CLASSNAME, I_("getPtrForContainer"),
                      CND::BP_ERR_UNKNOWN_EXCEPTION);
   }
   return ptr;
}

//******************************************************************************
bool ExternalInstitutionSearchProcess::doModelessSetFocus( GenericInterface *rpGICaller )
{
   bool bRtn = false;
   if( m_rpChildGI && isValidModelessInterface( m_rpChildGI ) )
   {
      bRtn = m_rpChildGI->refresh( this, NULL );
      bRtn = m_rpChildGI->modelessSetFocus( rpGICaller );
   }
   return(bRtn);
}

//******************************************************************************
bool ExternalInstitutionSearchProcess::doModelessChildComplete( const Command &cmd )
{
   DString dslCommandKey;
   dslCommandKey = cmd.getKey();
   if( dslCommandKey == CMD_GUI_EXTERNAL_INSTITUTION_SEARCH )
      return(true);  
   else
      return(false); 
}

//******************************************************************************
bool ExternalInstitutionSearchProcess::doMoreRecordsExist( GenericInterface *rpGICaller,  const BFContainerId& idSearch )
{
   ExternalInstitutionSearchProcess *pThis = const_cast<ExternalInstitutionSearchProcess*>(this);
   ExternalInstitutionList* pExternalInstitutionList = nullptr;

   pExternalInstitutionList = 
      dynamic_cast<ExternalInstitutionList*>(pThis->getCBOList (IFASTBP_PROC::EXTERNAL_INSTITUTION, getDataGroupId()));

   if(pExternalInstitutionList)
   {
      return(pExternalInstitutionList->doMoreRecordsExist());
   }
   else
   {
      return false;
   }
}

//******************************************************************************
SEVERITY ExternalInstitutionSearchProcess::doSetField( const GenericInterface *rpGICaller,
                                                       const BFContainerId& idContainer,
                                                       const BFFieldId& idField,
                                                       const BFDataGroupId& idDataGroup,
                                                       const DString& strValue,
                                                       bool bFormatted )
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, I_( "doSetField" ) );

   if (idField == ifds::SearchExternalInstitution)
   {
      _searchExternalInstitution = strValue;
   }
   else if (idField == ifds::SearchExternalInstitutionUsing)
   {
      _searchExternalInstitutionUsing = strValue;
   }
   else if(idField == ifds::KeyString)
   {
      _searchKey = strValue;
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
const BFProperties *ExternalInstitutionSearchProcess::doGetFieldAttributes ( const GenericInterface *rpGICaller,
                                                                             const BFContainerId &idContainer, 
                                                                             const BFFieldId &idField, 
                                                                             const BFDataGroupId &idDataGroup)
{
  MAKEFRAMEAUTOPROMOTE2 ( CND::BPBASE_CONDITION, 
                           CLASSNAME, 
                           I_("doGetFieldAttributes"));
   BFProperties  *pBFProperties = NULL;

   if (ifds::SearchExternalInstitution == idField)
   {
      if (_fPropSearchExternalInstitution == nullptr)
      {
         const BFDataFieldProperties* pProps = BFDataFieldProperties::get (idField);
         _fPropSearchExternalInstitution = new BFProperties (pProps);
         assert( _fPropSearchExternalInstitution );
      }

      pBFProperties = _fPropSearchExternalInstitution;
   }
   else if(ifds::SearchExternalInstitutionUsing == idField)
   {
      if (_fPropSearchExternalInstitutionUsing == nullptr)
      {
         const BFDataFieldProperties* pProps = BFDataFieldProperties::get (idField);
         _fPropSearchExternalInstitutionUsing = new BFProperties (pProps);
         assert( _fPropSearchExternalInstitutionUsing );
      }

      pBFProperties = _fPropSearchExternalInstitutionUsing;
   }
   else if (ifds::KeyString==idField)
   {
      if (_fPropKeyString==nullptr)
      {
         const BFDataFieldProperties* pProps = BFDataFieldProperties::get (idField);
         _fPropKeyString = new BFProperties (pProps);
         assert( _fPropKeyString );
      }

      pBFProperties = _fPropKeyString;
   }
   else if (ifds::ExternalInstitution == idField)
   {
      if (_fPropExternalInstitution == nullptr)
      {
         const BFDataFieldProperties* pProps = BFDataFieldProperties::get (idField);
         _fPropExternalInstitution = new BFProperties (pProps);
         assert( _fPropExternalInstitution );
      }

      pBFProperties = _fPropExternalInstitution;
   }

   return pBFProperties;
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastbp/ExternalInstitutionSearchProcess.cpp-arc  $
// 
