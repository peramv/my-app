//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by International Financial Data Services,
//    are proprietary in nature and as such are confIdential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2010 by International Financial Data Services.
//
//******************************************************************************
//
// ^FILE   : AcctGuaranteeGuardOptProcess.cpp
// ^AUTHOR : 
// ^DATE   : 
//
// -----------------------------------------------------------------------------
//
// ^CLASS  : AcctGuaranteeGuardOptProcess
//
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include "stdafx.h"

#include <bfdata\bfdatafielditer.hpp>

#include "AcctGuaranteeGuardOptProcessIncludes.h"
#include "AcctGuaranteeGuardOptProcess.hpp"

#include <bfproc\genericinterfacecontainer.hpp>
#include <bfproc\concreteprocesscreator.hpp>

#include <ifastcbo\mfaccount.hpp>
#include <ifastcbo\shareholder.hpp>
#include <ifastcbo\AcctGuaranteeGuardOpt.hpp>
#include <ifastcbo\AcctGuaranteeGuardOptList.hpp>

#include <ifastdataimpl\dse_dstc0412_req.hpp>
#include <ifastdataimpl\dse_dstc0412_vw.hpp>
#include <ifastdataimpl\dse_dstc0412_vwrepeat_record.hpp>

#include "mfcaninterprocparam.hpp"

extern IFASTBP_LINKAGE const I_CHAR* CMD_GUI_ACCT_GUARNT_GUARD_OPTN;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_ACCT_GUARNT_GUARD_OPTN;

static ConcreteProcessCreator< AcctGuaranteeGuardOptProcess > processCreator( CMD_BPROC_ACCT_GUARNT_GUARD_OPTN );

namespace 
{
   // Trace literals
   const I_CHAR * const CLASSNAME         = I_( "AcctGuaranteeGuardOptProcess" );
   const I_CHAR * const FULL_REFRESH      = I_( "FullRefresh" );
   const I_CHAR * const PARTIAL_REFRESH   = I_( "PartialRefresh" );
   const I_CHAR * const YES               = I_( "Y" );
   const I_CHAR * const NO                = I_( "N" );
}

namespace CND
{
   extern CLASS_IMPORT const long BP_ERR_UNKNOWN_EXCEPTION;
}

namespace ifds
{
   extern CLASS_IMPORT const BFNumericFieldId AccountNum;
   extern CLASS_IMPORT const BFNumericFieldId ShrNum;
   extern CLASS_IMPORT const BFDateFieldId ProcessDate;
   extern CLASS_IMPORT const BFTextFieldId Username;
}

namespace MFCAN_IP_PARAM
{
   extern const I_CHAR * const CALLER;
   extern const I_CHAR * const ACCOUNT_NUM;
}

namespace AUDITTYPE
{
   //extern CLASS_IMPORT I_CHAR * const ACT_AUTH;
}

//******************************************************************************
//              Public Methods
//******************************************************************************
AcctGuaranteeGuardOptProcess::AcctGuaranteeGuardOptProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: AbstractProcess( pGIC, pGIParent, rCommand )
, _rpChildGI( NULL )
, _accountNum(NULL_STRING)
,_pAcctGuaranteeGuardOptList (NULL)
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );

   addContainer( IFASTBP_PROC::MFACCOUNT_CBO, false, BF::NullContainerId, false  );
   addContainer( IFASTBP_PROC::SHAREHOLDER_CBO, false, BF::NullContainerId, false );

   addContainer( IFASTBP_PROC::ACCT_GUARNT_GUARD_OPTN_LIST, true, IFASTBP_PROC::MFACCOUNT_CBO, true  );

   addFieldDetails( ifds::AccountNum         , IFASTBP_PROC::MFACCOUNT_CBO );

   addFieldDetails( ifds::GuardOptCurrent    , IFASTBP_PROC::ACCT_GUARNT_GUARD_OPTN_LIST );
   addFieldDetails( ifds::GuardOptAfter      , IFASTBP_PROC::ACCT_GUARNT_GUARD_OPTN_LIST );
   addFieldDetails( ifds::GBCD               , IFASTBP_PROC::ACCT_GUARNT_GUARD_OPTN_LIST );
   addFieldDetails( ifds::DeffUntil          , IFASTBP_PROC::ACCT_GUARNT_GUARD_OPTN_LIST );
   addFieldDetails( ifds::CreatedOn          , IFASTBP_PROC::ACCT_GUARNT_GUARD_OPTN_LIST );
   addFieldDetails( ifds::CreatedBy          , IFASTBP_PROC::ACCT_GUARNT_GUARD_OPTN_LIST );
   addFieldDetails( ifds::ModDate            , IFASTBP_PROC::ACCT_GUARNT_GUARD_OPTN_LIST );
   addFieldDetails( ifds::ModUser            , IFASTBP_PROC::ACCT_GUARNT_GUARD_OPTN_LIST );
   addFieldDetails( ifds::ProcessDate        , IFASTBP_PROC::ACCT_GUARNT_GUARD_OPTN_LIST, SUBCLASS_PROCESS );
   addFieldDetails( ifds::Username           , IFASTBP_PROC::ACCT_GUARNT_GUARD_OPTN_LIST, SUBCLASS_PROCESS );
   
   addFieldDetails( ifds::SEGGuarGuardID     , IFASTBP_PROC::ACCT_GUARNT_GUARD_OPTN_LIST );

   addFieldDetails( ifds::ShrNum,            BF::NullContainerId, SUBCLASS_PROCESS );
   addFieldDetails( PRIMARY_ACCOUNT_OWNER,   BF::NullContainerId, SUBCLASS_PROCESS );
   addFieldDetails( HasGoodGuarGuardRecordExist, BF::NullContainerId, SUBCLASS_PROCESS );
   addFieldDetails( HasRecordAdded             , BF::NullContainerId, SUBCLASS_PROCESS );
   addFieldDetails( AddNewAccountGuard          ,  IFASTBP_PROC::ACCT_GUARNT_GUARD_OPTN_LIST, SUBCLASS_PROCESS );
   addFieldDetails( IsNewAccountGuardList       ,  IFASTBP_PROC::ACCT_GUARNT_GUARD_OPTN_LIST, SUBCLASS_PROCESS );
}

//******************************************************************************
AcctGuaranteeGuardOptProcess::~AcctGuaranteeGuardOptProcess(void)
{
    TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************
SEVERITY AcctGuaranteeGuardOptProcess::doInit()
{
   MAKEFRAMEAUTOPROMOTE2(CND::BPBASE_CONDITION, CLASSNAME, I_("doInit"));

   getParameter( MFCAN_IP_PARAM::ACCOUNT_NUM, _accountNum );
   try
   {
      const BFDataGroupId& idDataGroup = getDataGroupId();

      DSTCWorkSession *pDSTCWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());

      MFAccount *pMFAccount = NULL;
      if (_accountNum != NULL_STRING)
      {
         if( pDSTCWorkSession->getMFAccount( getDataGroupId(), 
            _accountNum, pMFAccount, I_("N"), NULL_STRING, true, true) > WARNING )
         {
            return(GETCURRENTHIGHESTSEVERITY());
         }

         setContainer(IFASTBP_PROC::MFACCOUNT_CBO, pMFAccount);

         //AcctGuaranteeGuardOptList *pAcctGuaranteeGuardOptList = NULL;
         //pMFAccount->getAcctGuaranteeGuardOptList(pAcctGuaranteeGuardOptList,getDataGroupId() );

         //if ( ( GETCURRENTHIGHESTSEVERITY() <= WARNING ) && pAcctGuaranteeGuardOptList)
         //{
         //   setContainer(IFASTBP_PROC::ACCT_GUARNT_GUARD_OPTN_LIST, pAcctGuaranteeGuardOptList);
         //   _pAcctGuaranteeGuardOptList = pAcctGuaranteeGuardOptList;
         //}
      }
   }
   catch( ConditionException &ce )
   {
      SETCONDITIONFROMEXCEPTION( ce );
   }
   catch( ... )
   {
      throw EXCEPTIONFROMFILE( CND::BP_ERR_UNKNOWN_EXCEPTION );
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
E_COMMANDRETURN AcctGuaranteeGuardOptProcess::doProcess()
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, DOPROCESS );
   E_COMMANDRETURN rtn = CMD_FAILURE;

   try
   {
      if (!isXMLAPIContext() )
      {
         rtn = invokeCommand( this, CMD_GUI_ACCT_GUARNT_GUARD_OPTN, getProcessType(), isModal(), &_rpChildGI );
      }
      else
      {
         rtn = CMD_MODELESS_INPROCESS;
      }
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
bool AcctGuaranteeGuardOptProcess::doModelessChildComplete( const Command &cmd )
{
    return( cmd.getKey() == CMD_GUI_ACCT_GUARNT_GUARD_OPTN  );
}

//******************************************************************************
void *AcctGuaranteeGuardOptProcess::getPtrForContainer( const BFContainerId& idContainer, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, I_("getPtrForContainer") );

   void *ptr = NULL;

   DSTCWorkSession* dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
   MgmtCo &pMgmtCo = dstcWorkSession->getMgmtCo();
   assert(dstcWorkSession);

   try
   {
      MFAccount *pMFAccount = NULL;
      Shareholder* pShareholder = NULL;
      DString strShrNum;

      AcctGuaranteeGuardOptProcess* pThis = 
            const_cast<AcctGuaranteeGuardOptProcess*>(this);

      pMFAccount = dynamic_cast<MFAccount*>(pThis->getCBOItem( IFASTBP_PROC::MFACCOUNT_CBO, idDataGroup ));
      assert(pMFAccount);

      if ( IFASTBP_PROC::SHAREHOLDER_CBO == idContainer )
      {       
         pMFAccount->getField( ifds::ShrNum, strShrNum,getDataGroupId(),false);
         if( dstcWorkSession->getShareholder( getDataGroupId(), 
            strShrNum, pShareholder ) > WARNING )
         {
            throw;
         }

         ptr = pShareholder;
      }
      else if (IFASTBP_PROC::ACCT_GUARNT_GUARD_OPTN_LIST == idContainer)
      {
         AcctGuaranteeGuardOptList *pAcctGuaranteeGuardOptList = NULL;
         pMFAccount->getAcctGuaranteeGuardOptList(pAcctGuaranteeGuardOptList, idDataGroup);

         if(pAcctGuaranteeGuardOptList)
         {
            _pAcctGuaranteeGuardOptList = pAcctGuaranteeGuardOptList;
            ptr = pAcctGuaranteeGuardOptList;
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
      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, I_("getPtrForContainer"),
                      CND::BP_ERR_UNKNOWN_EXCEPTION );
   }
   return(ptr);
}

//******************************************************************************
bool AcctGuaranteeGuardOptProcess::doRefresh( GenericInterface *rpGICaller,const I_CHAR *szOriginalCommand )
{
    TRACE_METHOD( CLASSNAME, I_("doRefresh") );

    return ( _rpChildGI->refresh(this, FULL_REFRESH) );
}

//******************************************************************************
void AcctGuaranteeGuardOptProcess::doGetField( const GenericInterface *rpGICaller,
                                                   const BFContainerId& idContainer,
                                                   const BFFieldId& idField,
                                                   const BFDataGroupId& idDataGroup,
                                                   DString &strValueOut,
                                                   bool bFormatted ) const
{
    TRACE_METHOD( CLASSNAME, I_("doGetField") );

    try
    {
        if( BF::NullContainerId == idContainer )
        {
            if( idField == ifds::ShrNum )
            {
                AcctGuaranteeGuardOptProcess* pThis = 
                  const_cast<AcctGuaranteeGuardOptProcess*>(this);
                Shareholder* pShareholder = NULL;

                pShareholder = dynamic_cast<Shareholder*>(pThis->getCBOItem( IFASTBP_PROC::SHAREHOLDER_CBO, idDataGroup ));

                if( pShareholder )
                    pShareholder->getField( ifds::ShrNum, strValueOut, idDataGroup, bFormatted);
            }
            else if( idField == PRIMARY_ACCOUNT_OWNER )
            {
                DSTCWorkSession* dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
                DString dstrAccountNum = _accountNum;
                dstcWorkSession->getFirstSequenced01AccountholderEntityName( getDataGroupId(), dstrAccountNum, strValueOut );
                strValueOut.strip();
            }
            else if( idField == HasGoodGuarGuardRecordExist ||
                     idField == HasRecordAdded )
            {
               // checking good record
               DSTCWorkSession* dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
               AcctGuaranteeGuardOptProcess* pThis = const_cast<AcctGuaranteeGuardOptProcess*>(this);

               MFAccount *pMFAccount = NULL;
               pMFAccount = dynamic_cast<MFAccount*>(pThis->getCBOItem( IFASTBP_PROC::MFACCOUNT_CBO, idDataGroup ));
               assert(pMFAccount);

               AcctGuaranteeGuardOptList *pAcctGuaranteeGuardOptList = NULL;
               pMFAccount->getAcctGuaranteeGuardOptList(pAcctGuaranteeGuardOptList, idDataGroup);

               if(idField == HasGoodGuarGuardRecordExist)
               {
                  bool isGoodRecordExist = false;
                  if(pAcctGuaranteeGuardOptList)
                  {
                     BFObjIter iter ( *pAcctGuaranteeGuardOptList, 
                                       idDataGroup, 
                                       false, 
                                       BFObjIter::ITERTYPE::NON_DELETED);
                     DString dstrGBCD;
                     iter.begin();

                     while(!iter.end())
                     {
                        iter.getObject()->getField(ifds::GBCD, dstrGBCD, idDataGroup, false);
                        dstrGBCD.strip().upperCase();

                        if(dstrGBCD == YES)
                        {
                           isGoodRecordExist = true;
                           break;
                        }
                        ++iter;
                     }
                  }
                  strValueOut = isGoodRecordExist ? YES : NO;
               }
               else if(idField == HasRecordAdded)
               {
                  bool isRecordExist = false;
                  if(pAcctGuaranteeGuardOptList)
                  {
                     BFObjIter iter ( *pAcctGuaranteeGuardOptList, 
                                       idDataGroup, 
                                       false, 
                                       BFObjIter::ITERTYPE::NON_DELETED);
                     iter.begin();

                     if(!iter.end())
                     {
                        isRecordExist = true;
                     }
                     strValueOut = isRecordExist ? YES : NO;
                  }
               }
            }

        }
        else if( IFASTBP_PROC::MFACCOUNT_CBO == idContainer )
        {
            if( idField == ifds::AccountNum )
            {
                strValueOut = _accountNum;
            }
        }
        else if ( IFASTBP_PROC::ACCT_GUARNT_GUARD_OPTN_LIST == idContainer )
        {
           AcctGuaranteeGuardOptProcess* pThis = 
              const_cast<AcctGuaranteeGuardOptProcess*>(this);

           if ( idField == ifds::ProcessDate || 
              idField == ifds::Username )
           {
              AcctGuaranteeGuardOpt* pObj = 
                 dynamic_cast<AcctGuaranteeGuardOpt*>(pThis->getCBOItem( IFASTBP_PROC::ACCT_GUARNT_GUARD_OPTN_LIST, idDataGroup ));

              if ( idField == ifds::ProcessDate )
              {
                 pObj->getField( ifds::CreatedOn, strValueOut, idDataGroup, bFormatted);
              }
              else if ( idField == ifds::Username )
              {
                 pObj->getField( ifds::CreatedBy, strValueOut, idDataGroup, bFormatted);
              }
           }
           else if ( idField == IsNewAccountGuardList )
           {
              AcctGuaranteeGuardOptList* pList =
                 dynamic_cast <AcctGuaranteeGuardOptList*> (pThis->getCBOList (IFASTBP_PROC::ACCT_GUARNT_GUARD_OPTN_LIST, idDataGroup));
              if( pList && pList->isNew() )
              {
                 strValueOut = I_("Y");
              }
              else
              {
                 strValueOut = I_("N");
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
       THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, I_("doGetField"),
                       CND::BP_ERR_UNKNOWN_EXCEPTION );
    }
}

//******************************************************************************
SEVERITY AcctGuaranteeGuardOptProcess::doSetField( const GenericInterface *rpGICaller,
                                                   const BFContainerId& idContainer,
                                                   const BFFieldId& idField,
                                                   const BFDataGroupId& idDataGroup,
                                                   const DString& strValue,
                                                   bool  bFormatted )
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, I_("doSetField") );

   try
   {
      if ( IFASTBP_PROC::ACCT_GUARNT_GUARD_OPTN_LIST == idContainer )
      {
         AcctGuaranteeGuardOptProcess* pThis = 
            const_cast<AcctGuaranteeGuardOptProcess*>(this);

         AcctGuaranteeGuardOpt* pObj = 
            dynamic_cast<AcctGuaranteeGuardOpt*>(pThis->getCBOItem( IFASTBP_PROC::ACCT_GUARNT_GUARD_OPTN_LIST, idDataGroup ));

         if ( idField == AddNewAccountGuard )
         {
            pObj->setUpdateStatus( idDataGroup, true );
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
      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, I_("doSetField"),
                      CND::BP_ERR_UNKNOWN_EXCEPTION );
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
bool AcctGuaranteeGuardOptProcess::doOk( GenericInterface *rpGICaller )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTBP_CONDITION, CLASSNAME, I_("doOk") );

   MFAccount *pMFAccount = NULL;
   const BFDataGroupId& idDataGroup = getDataGroupId();
   DSTCWorkSession *dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());

   if( NULL != dstcWorkSession &&
      dstcWorkSession->getMFAccount( idDataGroup, _accountNum, pMFAccount ) <= WARNING &&
      NULL != pMFAccount )
   {
      pMFAccount->refreshMe( true );
   }

   return ( GETCURRENTHIGHESTSEVERITY() <= WARNING );
}

//******************************************************************************
bool AcctGuaranteeGuardOptProcess::doModelessSetFocus( GenericInterface *rpGICaller )
{
    MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, I_("doModelessSetFocus") );

    bool bRtn = false;
    try
    {
        assert( _rpChildGI );

        if( isValidModelessInterface( _rpChildGI ) )
        {
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
        THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, I_("doModelessSetFocus"),
                        CND::BP_ERR_UNKNOWN_EXCEPTION );
    }

    return bRtn;
}

//*****************************************************************************
SEVERITY AcctGuaranteeGuardOptProcess::performSearch( GenericInterface *rpGI, const BFContainerId& idSearch, 
                                                      E_SEARCHACTION eSearchAction )
{
    MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, I_("performSearch") );

    const BFDataGroupId& idDataGroup = getDataGroupId ();
    DSTCWorkSession* dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
    MgmtCo &pMgmtCo = dstcWorkSession->getMgmtCo();

    try
    {
       switch( eSearchAction )
       {
         case SEARCH_START:
            {
               if( idSearch == IFASTBP_PROC::ACCT_GUARNT_GUARD_OPTN_LIST )
               {
                  if (_pAcctGuaranteeGuardOptList != NULL )
                  {
                     delete _pAcctGuaranteeGuardOptList;
                     _pAcctGuaranteeGuardOptList = NULL;
                  }

                  setContainer(IFASTBP_PROC::ACCT_GUARNT_GUARD_OPTN_LIST, NULL);

                  MFAccount *pMFAccount = NULL;
                  dstcWorkSession->getMFAccount( idDataGroup, _accountNum, pMFAccount );
                  if( pMFAccount->getAcctGuaranteeGuardOptList( _pAcctGuaranteeGuardOptList, idDataGroup ) <= WARNING )
                  {
                     setContainer(IFASTBP_PROC::ACCT_GUARNT_GUARD_OPTN_LIST, _pAcctGuaranteeGuardOptList);
                  }
               }
            }
            break;
         case SEARCH_NEXT_BLOCK:
            {
               if( idSearch == IFASTBP_PROC::ACCT_GUARNT_GUARD_OPTN_LIST )
               {
                  _pAcctGuaranteeGuardOptList->getMore ();        
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
      assert(0);
        THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, I_("performSearch"), CND::BP_ERR_UNKNOWN_EXCEPTION );
   }
    return(GETCURRENTHIGHESTSEVERITY()); 
}
//***********************************************************************************
bool AcctGuaranteeGuardOptProcess::doMoreRecordsExist( GenericInterface *rpGICaller,
                                                       const BFContainerId& idSearch )
{
   if( idSearch == IFASTBP_PROC::ACCT_GUARNT_GUARD_OPTN_LIST )
   {
      return (rpGICaller == NULL || _pAcctGuaranteeGuardOptList == NULL) ? 
         false : _pAcctGuaranteeGuardOptList->doMoreRecordsExist();      
   }
   else
   {
      return false;
   }
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
// $Log:   Y:/VCS/BF iFAST/ifastbp/AcctGuaranteeGuardOptProcess.cpp-arc  $
// 
//    Rev 1.1   Sep 17 2010 05:34:14   kitticha
// Cleaning the comment.
// 
//    Rev 1.0   Sep 17 2010 05:25:16   kitticha
// Initial revision.
// 