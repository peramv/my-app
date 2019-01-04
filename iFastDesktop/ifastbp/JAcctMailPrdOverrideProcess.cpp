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
// ^FILE   : JAcctMailPrdOverrideProcess.cpp
// ^AUTHOR :  Celia Zhang
// ^DATE   : 29/09/2005
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : JAcctMailPrdOverrideProcess
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include "stdafx.h"
#include "JAcctMailPrdOverrideProcess.hpp"
#include <ifastcbo\mfaccount.hpp>
#include <ifastcbo\AcctMailingOverrideList.hpp>
#include <ifastcbo\AcctMailingOverride.hpp>
#include <ifastcbo\DecodeAcctID.hpp>
#include <ifastcbo\mgmtco.hpp>
#include <ifastcbo\mgmtcooptions.hpp>
#include <ifastcbo\DefaultMailOptionList.hpp>
#include "JAcctMailPrdOverrideProcessincludes.h"
#include "etrackheader.h"
#include <ifastdataimpl\dse_dstcglob_vw.hpp>
#include <ifastdataimpl\dse_dstc0214_vw.hpp>
#include <ifastdataimpl\dse_dstc0356_vw.hpp>

extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_JACCTMAILPRD_OVERRIDE;
#include <bfproc\concreteprocesscreator.hpp>
static ConcreteProcessCreator< JAcctMailPrdOverrideProcess > processCreator( CMD_BPROC_JACCTMAILPRD_OVERRIDE );

namespace
{
   // Trace literals
   const I_CHAR *CLASSNAME          = I_( "JAcctMailPrdOverrideProcess" );
	const I_CHAR *AcctIdentifier     = I_( "AccountID" );
	const I_CHAR *DocumentType       = I_( "DocumentType" );
	const I_CHAR *AWDStatus			   = I_( "AWDStatus" );

	//const I_CHAR * const ANNL_RPT_HOLD       = I_( "10" );
	//const I_CHAR * const SEMI_RPT_ANNL_HOLD  = I_( "16" );
	//const I_CHAR * const ANNL_MRFP_HOLD      = I_( "20" );
	//const I_CHAR * const SEMI_ANNL_MRFP_HOLD = I_( "21" );
}

namespace ADDRLIT 
{
   const I_CHAR * const pACCOUNTNUM = I_( "AccountNum" );
	const I_CHAR * const pSHAREHOLDERNUM = I_( "ShareholderNum" );

}  

namespace CND
{
   extern CLASS_IMPORT const long BP_ERR_UNKNOWN_EXCEPTION;
}

//******************************************************************************
//              Public Methods
//******************************************************************************

//CP20030319JAcctMailPrdOverrideProcess::JAcctMailPrdOverrideProcess() : 
JAcctMailPrdOverrideProcess::JAcctMailPrdOverrideProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: AbstractProcess( pGIC, pGIParent, rCommand ),
_rpChildGI( NULL ),
_pDecodeAcctID( NULL ),
_pAcctMailingOverrideList( NULL ),
pWorkSession( NULL )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );

   addContainer( IFASTBP_PROC::DECODE_ACCTID_CBO, false, // not repeatable
		                     BF::NullContainerId,   true, // updateable
									I_( "DecodeAcctID" ) );
	
	addContainer( IFASTBP_PROC::ACCT_MAILING_OVERRIDE_LIST, true, // repeatable  
		                     BF::NullContainerId,            true, // updateable 
									I_("MailingOverride") );

	addFieldDetails( ifds::DocumentType,	  IFASTBP_PROC::ACCT_MAILING_OVERRIDE_LIST );
	addFieldDetails( ifds::FundGroup,        IFASTBP_PROC::ACCT_MAILING_OVERRIDE_LIST );
   addFieldDetails( ifds::OnHold,           IFASTBP_PROC::ACCT_MAILING_OVERRIDE_LIST, SUBCLASS_PROCESS );
	addFieldDetails( ifds::AuthCode,	        IFASTBP_PROC::ACCT_MAILING_OVERRIDE_LIST );
	addFieldDetails( ifds::EntityAddrCode,	  IFASTBP_PROC::ACCT_MAILING_OVERRIDE_LIST );

	
	addFieldDetails( ifds::AccountNum,       IFASTBP_PROC::DECODE_ACCTID_CBO );
	addFieldDetails( ifds::ShareholderNum,   IFASTBP_PROC::DECODE_ACCTID_CBO );

}

//******************************************************************************

JAcctMailPrdOverrideProcess::~JAcctMailPrdOverrideProcess()
{
   TRACE_DESTRUCTOR( CLASSNAME );

   _rpChildGI = NULL;
}

//******************************************************************************
//              Protected Methods
//******************************************************************************

SEVERITY JAcctMailPrdOverrideProcess::doInit()
{ 
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, DOINIT );
   SEVERITY sevRtn = SEVERE_ERROR;

   try
   {
		pWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
     
		getParameter( AcctIdentifier, m_dstrAcctIdentifier );	
		m_dstrAcctIdentifier.strip();
	
		getParameter( AWDStatus, m_dstrStatus );

		getParameter( ADDRLIT::pACCOUNTNUM, m_dstrAccountNum );
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

//******************************************************************************

E_COMMANDRETURN JAcctMailPrdOverrideProcess::doProcess()
{  
   MAKEFRAME2( CND::BPBASE_CONDITION, CLASSNAME, DOPROCESS );
   E_COMMANDRETURN rtn = CMD_FAILURE;


   rtn = CMD_MODELESS_INPROCESS;
   return(rtn);
}

//******************************************************************************
SEVERITY JAcctMailPrdOverrideProcess::setFreshList( GenericInterface *rpGI )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTBP_CONDITION, CLASSNAME, I_("setFreshList") );

   const BFDataGroupId& idDataGroup = getDataGroupId();

	if ( _pDecodeAcctID != NULL )
	{
		_pDecodeAcctID->getField( ifds::AccountNum, m_dstrAccountNum, idDataGroup );
	}

   m_dstrAccountNum.stripLeading( '0' ).strip();

	setGlobal( WORK_GLOBAL, ifds::LastActiveAccountNum, m_dstrAccountNum );

   try
   {
      if( m_dstrAccountNum != NULL_STRING )
      {
         //MFAccount cbo
         MFAccount* pMFAccount = NULL;

         if( pWorkSession->getMFAccount( idDataGroup, m_dstrAccountNum, pMFAccount, I_("N"), NULL_STRING, true, true) <= WARNING )
         {
            _pAcctMailingOverrideList = NULL;

				if(pMFAccount->getAcctMailingOverrideList(_pAcctMailingOverrideList, idDataGroup)<=WARNING )
				{
					setContainer(IFASTBP_PROC::ACCT_MAILING_OVERRIDE_LIST, _pAcctMailingOverrideList);
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
void JAcctMailPrdOverrideProcess::setCurrentListItem( const GenericInterface* rpGICaller,
                                    const BFContainerId& idList,
                                    const BFData* pKeyInfo )
{
	MAKEFRAMEAUTOPROMOTE2 (CND::IFASTBP_CONDITION, CLASSNAME, I_( "setCurrentListItem" ) ); 

	if ( idList ==  IFASTBP_PROC::ACCT_MAILING_OVERRIDE_LIST )
	{
		DString searchKey, strSelectionKey;
      
		m_dstrFundGroup = pKeyInfo->getElementValue (ifds::FundGroup);
      m_dstrFundGroup.strip();
      m_dstrDocumentType = pKeyInfo->getElementValue (ifds::DocumentType );
      m_dstrDocumentType.strip();

		assert (_pAcctMailingOverrideList);

	   _pAcctMailingOverrideList->buildKey (m_dstrFundGroup, m_dstrDocumentType, searchKey );
      
      BFObjIter iter ( *_pAcctMailingOverrideList, 
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
			AbstractProcess::getKeyForNewListItem( rpGICaller, idList );
		}
		
		DefaultMailOptionList* pDefaultMailOptionList = NULL;
		if( pWorkSession->getMgmtCo().getDefaultMailOptionList( pDefaultMailOptionList ) <= WARNING  
			&& pDefaultMailOptionList )
		{
			m_dstrDocumentType.stripAll();
			m_DefOnHold  = pDefaultMailOptionList->getDefaultHoldFlag ( m_dstrDocumentType ); 
			
		}
	}
}

//******************************************************************************
SEVERITY JAcctMailPrdOverrideProcess::doSetField( const GenericInterface* rpGICaller,
												  const BFContainerId& idContainer,
		                                const BFFieldId &fieldID,
			                             const BFDataGroupId& idDataGroup,
					                       const DString &strValue,
							                 bool bFormatted )
{
	MAKEFRAMEAUTOPROMOTE2(CND::BPBASE_CONDITION, CLASSNAME, DOSETFIELD);

	DString dstrDocumentType, dstrOnHold;
	if ( idContainer == IFASTBP_PROC::ACCT_MAILING_OVERRIDE_LIST && m_dstrStatus != I_("REJECT") )
	{
		
		BFAbstractCBO *rpPtr =
			 				dynamic_cast<AcctMailingOverride*>( getCBOItem( idContainer, idDataGroup ) );

		if ( rpPtr != NULL && rpPtr->isNew())
		{
			
			dynamic_cast<AcctMailingOverride*>(rpPtr)->setObjectAsUpdated( m_dstrDocumentType, m_dstrFundGroup, idDataGroup );
		}
		
		if ( fieldID == ifds::OnHold)
		{	
					
			if (rpPtr)
			{
				if (strValue == I_("1") )
				{
					if ( m_DefOnHold == I_("Y") )
						rpPtr->setField( ifds::OnHold, I_("N"), idDataGroup );
					else
						rpPtr->setField( ifds::OnHold, I_("Y"), idDataGroup );
				}
				else
				{
					rpPtr->setField( ifds::OnHold, m_DefOnHold, idDataGroup );
				}
				rpPtr->setField( ifds::AuthCode, I_("A"), idDataGroup );
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
/* $Log:   Y:/VCS/BF iFAST/ifastbp/JAcctMailPrdOverrideProcess.cpp-arc  $
// 
//    Rev 1.3   Dec 05 2005 16:44:08   ZHANGCEL
// PET1332 FN09 -- Add logic to compare with the DefaultMailOption
// 
//    Rev 1.2   Nov 14 2005 11:05:38   ZHANGCEL
// PET1332 FN09 -- Fine tuner
// 
//    Rev 1.1   Nov 08 2005 16:14:34   ZHANGCEL
// PET1332 FN09 -- Add logic regarding parameter AccountNumber
// 
//    Rev 1.0   Oct 24 2005 17:37:24   ZHANGCEL
// Initial revision.
 */
