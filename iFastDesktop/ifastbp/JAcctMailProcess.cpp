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
// ^FILE   : JAcctMailProcess.cpp
// ^AUTHOR :  Celia Zhang
// ^DATE   : 29/09/2005
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : JAcctMailProcess
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include "stdafx.h"
#include "JAcctMailProcess.hpp"

#include <ifastcbo\shareholder.hpp>
#include <ifastcbo\MFAccount.hpp>
#include <ifastcbo\accountmailinglist.hpp>
#include <ifastcbo\DecodeAcctID.hpp>
#include <ifastcbo\AccountMailingInfo.hpp>
#include <ifastcbo\mgmtco.hpp>
#include <ifastcbo\mgmtcooptions.hpp>
#include <ifastcbo\DefaultMailOptionList.hpp>
#include <ifastdataimpl\dse_dstcglob_vw.hpp>
#include "JAcctMailProcessincludes.h"
#include "etrackheader.h"
#include <ifastdataimpl\dse_dstc0113_vw.hpp>
#include <ifastdataimpl\dse_dstc0356_vw.hpp>

extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_JACCTMAIL;
#include <bfproc\concreteprocesscreator.hpp>
static ConcreteProcessCreator< JAcctMailProcess > processCreator( CMD_BPROC_JACCTMAIL );

namespace
{
   // Trace literals
   const I_CHAR *CLASSNAME      = I_( "JAcctMailProcess" );
	const I_CHAR *AcctIdentifier = I_( "AccountID" );
	const I_CHAR *AWDStatus		  = I_( "AWDStatus" );
	const I_CHAR *AccountNum	  = I_( "AccountNum" );
}

namespace CND
{
   extern CLASS_IMPORT const long BP_ERR_UNKNOWN_EXCEPTION;
}


namespace ifds
{
	extern CLASS_IMPORT const BFNumericFieldId ShrNum;
}


//******************************************************************************
//              Public Methods
//******************************************************************************

//CP20030319JAcctMailProcess::JAcctMailProcess() : 
JAcctMailProcess::JAcctMailProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: AbstractProcess( pGIC, pGIParent, rCommand ),
_rpChildGI( NULL ),
_pDecodeAcctID( NULL ),
_pAccountMailingList( NULL ),
pWorkSession ( NULL )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );

   addContainer( IFASTBP_PROC::DECODE_ACCTID_CBO, false, // not repeatable
		                     BF::NullContainerId,   true, // updateable
									I_( "DecodeAcctID" ) );
	addContainer( IFASTBP_PROC::ACCOUNT_MAILING_LIST, true, // repeatable
		                     BF::NullContainerId,      true, // updateable
									I_("Mailing") );

   addFieldDetails( ifds::SemiAnnualOnHold, IFASTBP_PROC::ACCOUNT_MAILING_LIST, SUBCLASS_PROCESS );
	addFieldDetails( ifds::SmAnnlRptsAuth,   IFASTBP_PROC::ACCOUNT_MAILING_LIST );
   addFieldDetails( ifds::AnnlRptsHold,     IFASTBP_PROC::ACCOUNT_MAILING_LIST, SUBCLASS_PROCESS );
	addFieldDetails( ifds::AnnlRptsAuth,	  IFASTBP_PROC::ACCOUNT_MAILING_LIST );
	addFieldDetails( ifds::SmAnnlMRFPAuth,   IFASTBP_PROC::ACCOUNT_MAILING_LIST );
   addFieldDetails( ifds::SmAnnlMRFPHold,   IFASTBP_PROC::ACCOUNT_MAILING_LIST, SUBCLASS_PROCESS );
   addFieldDetails( ifds::AnnlMRFPAuth,	  IFASTBP_PROC::ACCOUNT_MAILING_LIST );
   addFieldDetails( ifds::AnnlMRFPHold,     IFASTBP_PROC::ACCOUNT_MAILING_LIST, SUBCLASS_PROCESS );
	addFieldDetails( ifds::AccountNum,       IFASTBP_PROC::DECODE_ACCTID_CBO );
	addFieldDetails( ifds::ShareholderNum,   IFASTBP_PROC::DECODE_ACCTID_CBO );

}

//******************************************************************************

JAcctMailProcess::~JAcctMailProcess()
{
   TRACE_DESTRUCTOR( CLASSNAME );

   _rpChildGI = NULL;
}

//******************************************************************************
//              Protected Methods
//******************************************************************************

SEVERITY JAcctMailProcess::doInit()
{ 
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, DOINIT );
   SEVERITY sevRtn = SEVERE_ERROR;

   try
   {
		pWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
 		getParameter( AcctIdentifier, m_dstrAcctIdentifier );	
		m_dstrAcctIdentifier.strip();

		getParameter( AWDStatus, m_dstrStatus );

		getParameter( AccountNum, m_dstrAccountNum );
		m_dstrAccountNum.stripLeading( '0' ).strip();
		if ( m_dstrAccountNum == NULL_STRING )
		{
			if( pWorkSession )
			{
				_pDecodeAcctID = new DecodeAcctID( *getBFWorkSession() );
				sevRtn = _pDecodeAcctID->init( m_dstrAcctIdentifier );
				if( WARNING >= sevRtn )
				{ 
					setContainer( IFASTBP_PROC::DECODE_ACCTID_CBO, _pDecodeAcctID );
				}
				else
				{
					return(GETCURRENTHIGHESTSEVERITY());
				}
			}
		}
	
		setFreshList(NULL);
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

E_COMMANDRETURN JAcctMailProcess::doProcess()
{  
   MAKEFRAME2( CND::BPBASE_CONDITION, CLASSNAME, DOPROCESS );
   E_COMMANDRETURN rtn = CMD_FAILURE;

   rtn = CMD_MODELESS_INPROCESS;
   return(rtn);
}

//******************************************************************************
SEVERITY JAcctMailProcess::setFreshList( GenericInterface *rpGI )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTBP_CONDITION, CLASSNAME, I_("setFreshList") );
 
   const BFDataGroupId& idDataGroup = getDataGroupId();
	if ( _pDecodeAcctID != NULL )
	{
		_pDecodeAcctID->getField( ifds::AccountNum, m_dstrAccountNum, idDataGroup );
		_pDecodeAcctID->getField( ifds::ShareholderNum, m_dstrShrNum, idDataGroup );
		m_dstrAccountNum.stripLeading( '0' ).strip();
	}

	else  
	{
		if( m_dstrAccountNum != NULL_STRING )
		{
			MFAccount* pMFAccount;
         pWorkSession->getMFAccount (idDataGroup, m_dstrAccountNum, pMFAccount);
         if (pMFAccount)
         {
            pMFAccount->getField (ifds::ShrNum, m_dstrShrNum, idDataGroup, true);

         }
		}
	}
	
	setGlobal( WORK_GLOBAL, ifds::LastActiveAccountNum, m_dstrAccountNum );
   m_dstrShrNum.stripLeading( '0' ).strip();
   try
   {
     
      if( m_dstrShrNum != NULL_STRING && m_dstrAccountNum != NULL_STRING )
      {
         //shareholder cbo
         Shareholder* pShareholder = NULL;

         if( pWorkSession->getShareholder( idDataGroup, m_dstrShrNum, pShareholder ) <= WARNING )
         {
            //acount mailing list
            _pAccountMailingList = NULL;

				if (pShareholder->getAccountMailingList (_pAccountMailingList, idDataGroup ) <= WARNING )
				{
					setContainer( IFASTBP_PROC::ACCOUNT_MAILING_LIST, _pAccountMailingList );
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
      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, DOINIT, CND::BP_ERR_UNKNOWN_EXCEPTION );
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
void JAcctMailProcess::setCurrentListItem( const GenericInterface* rpGICaller,
                                    const BFContainerId& idList,
                                    const BFData* pKeyInfo )
{
	MAKEFRAMEAUTOPROMOTE2 (CND::IFASTBP_CONDITION, CLASSNAME, I_( "setCurrentListItem" ) ); 

	if ( idList ==  IFASTBP_PROC::ACCOUNT_MAILING_LIST )
	{
		DString searchKey, strSelectionKey;
         
		assert (_pAccountMailingList);
      _pAccountMailingList->buildKey (searchKey, m_dstrAccountNum );
      
      BFObjIter iter ( *_pAccountMailingList, 
                        getDataGroupId(), 
                        true, //match substrings
                        BFObjIter::ITERTYPE::NON_DELETED);
      if (iter.positionByKey (searchKey))
      {
			
			strSelectionKey = iter.getStringKey();
			assert (!strSelectionKey.empty());
			AbstractProcess::setCurrentListItem (rpGICaller, idList, strSelectionKey);
		}
		else
		{
			//_pAccountMailingList->initNew( m_dstrShrNum );
			AbstractProcess::getKeyForNewListItem( rpGICaller, idList );
			//AbstractProcess::setCurrentListItem( rpGICaller, idList, strKey );
		}
		
		DefaultMailOptionList* pDefaultMailOptionList = NULL;
		if( pWorkSession->getMgmtCo().getDefaultMailOptionList( pDefaultMailOptionList ) <= WARNING  
			&& pDefaultMailOptionList )
		{
			defHoldAnnlRpts   = pDefaultMailOptionList->getDefaultHoldFlag ( I_( "10" ) ); 
			defHoldSemiAnnual = pDefaultMailOptionList->getDefaultHoldFlag ( I_( "16" ) ); 
			defHoldAnnlMRFP   = pDefaultMailOptionList->getDefaultHoldFlag ( I_( "20" ) ); 
			defHoldSmAnnlMRFP = pDefaultMailOptionList->getDefaultHoldFlag ( I_( "21" ) ); 

		}
	}
}

//******************************************************************************
SEVERITY JAcctMailProcess::doSetField( const GenericInterface* rpGICaller,
												   const BFContainerId& idContainer,
		                                 const BFFieldId &fieldID,
			                              const BFDataGroupId& idDataGroup,
					                        const DString &strValue,
							                  bool bFormatted )
{
	MAKEFRAMEAUTOPROMOTE2(CND::BPBASE_CONDITION, CLASSNAME, DOSETFIELD);

	DString dstrSemiAnnualOnHold, dstrAnnlRptsHold, dstrSmAnnlMRFPHold, dstrAnnlMRFPHold;
	
	if ( idContainer == IFASTBP_PROC::ACCOUNT_MAILING_LIST && m_dstrStatus != I_("REJECT") )
	{
		BFAbstractCBO *rpPtr = getCBOItem (idContainer, idDataGroup);
		if (rpPtr)
		{
			if ( fieldID == ifds::SemiAnnualOnHold )
			{	
				if (strValue == I_("1") )
				{
					if ( defHoldSemiAnnual == I_("Y") )
						rpPtr->setField( ifds::SemiAnnualOnHold, I_("N"), idDataGroup );
					else
						rpPtr->setField( ifds::SemiAnnualOnHold, I_("Y"), idDataGroup );
				}
				else
				{
					rpPtr->setField( ifds::SemiAnnualOnHold, defHoldSemiAnnual, idDataGroup );
				}
				rpPtr->setField( ifds::SmAnnlRptsAuth, I_("A"), idDataGroup );
			}
			else if ( fieldID == ifds::AnnlRptsHold  )
			{
				if (strValue == I_("1") )
				{
					if ( defHoldAnnlRpts == I_("Y") )
						rpPtr->setField( ifds::AnnlRptsHold, I_("N"), idDataGroup );
					else
						rpPtr->setField( ifds::AnnlRptsHold, I_("Y"), idDataGroup );
				}
				else
				{
					rpPtr->setField( ifds::AnnlRptsHold, defHoldAnnlRpts, idDataGroup );
				}
				rpPtr->setField( ifds::AnnlRptsAuth, I_("A"), idDataGroup );
			}
			else if ( fieldID == ifds::SmAnnlMRFPHold  )
			{
				if (strValue == I_("1") )
				{
					if ( defHoldSmAnnlMRFP == I_("Y") )
						rpPtr->setField( ifds::SmAnnlMRFPHold, I_("N"), idDataGroup );
					else
						rpPtr->setField( ifds::SmAnnlMRFPHold, I_("Y"), idDataGroup );
				}
				else
				{
					rpPtr->setField( ifds::SmAnnlMRFPHold, defHoldSmAnnlMRFP, idDataGroup );
				}
				rpPtr->setField( ifds::SmAnnlMRFPAuth, I_("A"), idDataGroup );
			}
			else if ( fieldID == ifds::AnnlMRFPHold  )
			{
				if (strValue == I_("1") )
				{
					if ( defHoldAnnlMRFP == I_("Y") )
						rpPtr->setField( ifds::AnnlMRFPHold, I_("N"), idDataGroup );
					else
						rpPtr->setField( ifds::AnnlMRFPHold, I_("Y"), idDataGroup );
				}
				else
				{
					rpPtr->setField( ifds::AnnlMRFPHold, defHoldAnnlMRFP, idDataGroup );
				}
				rpPtr->setField( ifds::AnnlMRFPAuth, I_("A"), idDataGroup );
			}
		}
	}
  	return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
//              Private Methods
//******************************************************************************

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/JAcctMailProcess.cpp-arc  $
// 
//    Rev 1.3   Dec 05 2005 16:45:58   ZHANGCEL
// PET1332 FN09 -- Add logic to compare with the DefaultMailOption
// 
//    Rev 1.2   Nov 14 2005 10:59:16   ZHANGCEL
// OET1332 FN09 -- Fine tuner 
// 
//    Rev 1.1   Nov 08 2005 16:15:08   ZHANGCEL
// PET1332 FN09 -- Add logic regarding parameter AccountNumber
// 
//    Rev 1.0   Oct 24 2005 17:37:38   ZHANGCEL
// Initial revision.
 */
