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
// ^FILE   : RESPAcctInfoProcess.cpp
// ^AUTHOR : 
// ^DATE   : 
//
// -----------------------------------------------------------------------------
//
// ^CLASS  : RESPAcctInfoProcess
//
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include "stdafx.h"

#include <bfdata\bfdatafielditer.hpp>

#include "RESPAcctInfoProcessIncludes.h"
#include "RESPAcctInfoProcess.hpp"

#include <bfproc\genericinterfacecontainer.hpp>
#include <bfproc\concreteprocesscreator.hpp>

#include <ifastcbo\mfaccount.hpp>
#include <ifastcbo\shareholder.hpp>

#include "mfcaninterprocparam.hpp"

extern IFASTBP_LINKAGE const I_CHAR* CMD_GUI_RESP_ACCT_INFO_NASU;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_RESP_ACCT_INFO_NASU;

static ConcreteProcessCreator< RESPAcctInfoProcess > processCreator( CMD_BPROC_RESP_ACCT_INFO_NASU );

namespace 
{
   // Trace literals
   const I_CHAR * const CLASSNAME         = I_( "RESPAcctInfoProcess" );
   const I_CHAR * const FULL_REFRESH      = I_( "FullRefresh" );
   const I_CHAR * const PARTIAL_REFRESH   = I_( "PartialRefresh" );
   const I_CHAR * const YES               = I_( "Y" );
   const I_CHAR * const NO                = I_( "N" );
}

namespace CND
{
   extern CLASS_IMPORT const long BP_ERR_UNKNOWN_EXCEPTION;
}

namespace ACCOUNT_GROUPING

{
	extern CLASS_IMPORT const long ACCOUNT_RESP_INFO;
}

namespace ifds
{
   extern CLASS_IMPORT const BFNumericFieldId AccountNum;
   extern CLASS_IMPORT const BFNumericFieldId ShrNum;
   extern CLASS_IMPORT const BFTextFieldId CESGEligible;
   extern CLASS_IMPORT const BFTextFieldId SiblingOnly;
   extern CLASS_IMPORT const BFTextFieldId Pre98Contrib;
   extern CLASS_IMPORT const BFTextFieldId RES2Client;
   extern CLASS_IMPORT const BFTextFieldId RESPPlanNumber;
   extern CLASS_IMPORT const BFTextFieldId RESPInceptionDate;
   extern CLASS_IMPORT const BFTextFieldId RESPMatureDate;
   extern CLASS_IMPORT const BFTextFieldId RESPReportHRDC;
}

namespace MFCAN_IP_PARAM
{
   extern const I_CHAR * const CALLER;
   extern const I_CHAR * const ACCOUNT_NUM;
}

//******************************************************************************
//              Public Methods
//******************************************************************************
RESPAcctInfoProcess::RESPAcctInfoProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: AbstractProcess( pGIC, pGIParent, rCommand )
, _rpChildGI( NULL )
, _accountNum(NULL_STRING)
,_bSuccessFlag (false)
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );

   addContainer( IFASTBP_PROC::MFACCOUNT_CBO, false, BF::NullContainerId, true  );
   addContainer( IFASTBP_PROC::SHAREHOLDER_CBO, false, BF::NullContainerId, false );

   addFieldDetails( ifds::AccountNum,               IFASTBP_PROC::MFACCOUNT_CBO );
   //addFieldDetails( ifds::CESGEligible,             IFASTBP_PROC::MFACCOUNT_CBO );
   addFieldDetails( ifds::SiblingOnly,              IFASTBP_PROC::MFACCOUNT_CBO );
   addFieldDetails( ifds::CESGEligible,             IFASTBP_PROC::MFACCOUNT_CBO );
   addFieldDetails( ifds::Pre98Contrib,             IFASTBP_PROC::MFACCOUNT_CBO );


   addFieldDetails( ifds::ShrNum,            BF::NullContainerId, SUBCLASS_PROCESS );
   addFieldDetails( PRIMARY_ACCOUNT_OWNER,   BF::NullContainerId, SUBCLASS_PROCESS );
}

//******************************************************************************
RESPAcctInfoProcess::~RESPAcctInfoProcess(void)
{
    TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************
SEVERITY RESPAcctInfoProcess::doInit()
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

         pMFAccount->setFieldValid( ifds::SiblingOnly, idDataGroup, false );
         pMFAccount->validateAll( idDataGroup, ACCOUNT_GROUPING::ACCOUNT_RESP_INFO);
         setContainer (IFASTBP_PROC::MFACCOUNT_CBO, pMFAccount);
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
E_COMMANDRETURN RESPAcctInfoProcess::doProcess()
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, DOPROCESS );
   E_COMMANDRETURN rtn = CMD_FAILURE;

   try
   {
      if (!isXMLAPIContext() )
      {
         rtn = invokeCommand( this, CMD_GUI_RESP_ACCT_INFO_NASU, getProcessType(), isModal(), &_rpChildGI );
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
bool RESPAcctInfoProcess::doModelessChildComplete( const Command &cmd )
{
    return( cmd.getKey() == CMD_GUI_RESP_ACCT_INFO_NASU  );
}

//******************************************************************************
void *RESPAcctInfoProcess::getPtrForContainer( const BFContainerId& idContainer, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, I_("getPtrForContainer") );

   void *ptr = NULL;

   DSTCWorkSession* dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
   MgmtCo &pMgmtCo = dstcWorkSession->getMgmtCo();
   assert(dstcWorkSession);

   try
   {
      if ( IFASTBP_PROC::SHAREHOLDER_CBO == idContainer )
      {
         MFAccount *pMFAccount = NULL;
         Shareholder* pShareholder = NULL;
         DString strShrNum;

         RESPAcctInfoProcess* pThis = 
            const_cast<RESPAcctInfoProcess*>(this);

         pMFAccount = dynamic_cast<MFAccount*>(pThis->getCBOItem( IFASTBP_PROC::MFACCOUNT_CBO, idDataGroup ));
         pMFAccount->getField( ifds::ShrNum, strShrNum,getDataGroupId(),false);
         
         if( dstcWorkSession->getShareholder( getDataGroupId(), 
             strShrNum, pShareholder ) > WARNING )
         {
            throw;
         }

         ptr = pShareholder;
      }
      else
      {
         throw;
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
bool RESPAcctInfoProcess::doRefresh( GenericInterface *rpGICaller,const I_CHAR *szOriginalCommand )
{
    TRACE_METHOD( CLASSNAME, I_("doRefresh") );

    return ( _rpChildGI->refresh(this, FULL_REFRESH) );
}

//******************************************************************************
void RESPAcctInfoProcess::doGetField( const GenericInterface *rpGICaller,
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
                RESPAcctInfoProcess* pThis = 
                  const_cast<RESPAcctInfoProcess*>(this);
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
            else if( idField == ifds::AccountNum )
            {
                strValueOut = _accountNum;
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
SEVERITY RESPAcctInfoProcess::doSetField( const GenericInterface *rpGICaller,
                                          const BFContainerId& idContainer,
                                          const BFFieldId& idField,
                                          const BFDataGroupId& idDataGroup,
                                          const DString& strValue,
                                          bool  bFormatted )
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, I_("doSetField") );

   try
   {

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
SEVERITY RESPAcctInfoProcess::ok2( GenericInterface *rpGICaller )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTBP_CONDITION, CLASSNAME, I_("ok2") );

   MFAccount *pMFAccount = NULL;
   DSTCWorkSession *dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
   const BFDataGroupId& idDataGroup = getDataGroupId();
   
   if( NULL != dstcWorkSession &&
       dstcWorkSession->getMFAccount( idDataGroup, _accountNum, pMFAccount ) <= WARNING &&
       NULL != pMFAccount )
   {
      if (pMFAccount->validateAll( idDataGroup, ACCOUNT_GROUPING::ACCOUNT_RESP_INFO ) <= WARNING)
      {
         pMFAccount->commitDataGroup (idDataGroup);
      }
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
bool RESPAcctInfoProcess::doCancel (GenericInterface *rpGICaller)
{
   setParameter( MFCAN_IP_PARAM::ACCOUNT_NUM, _accountNum );

   return true;
}

//******************************************************************************
bool RESPAcctInfoProcess::doModelessSetFocus( GenericInterface *rpGICaller )
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

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
// $Log:   Y:/VCS/BF iFAST/ifastbp/RESPAcctInfoProcess.cpp-arc  $
// 
//    Rev 1.4   Nov 27 2011 19:39:24   popescu
// INA Commission Work
// 
//    Rev 1.3   Apr 19 2010 08:28:14   dchatcha
// PET165541_FN01_QESI - RESP Gap_Dsk
// 
//    Rev 1.2   Apr 09 2010 21:08:16   popescu
// PET165541_FN01_QESI - RESP Gap_Dsk_NASU
// 
//    Rev 1.1   Mar 26 2010 09:34:24   dchatcha
// PET165541_FN01_QESI - RESP Gap_Dsk_NASU
// 
//    Rev 1.0   Mar 12 2010 14:21:28   dchatcha
// Initial revision.
//

