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
//    Copyright 2003 by International Financial Data Services
//
//******************************************************************************
//
// ^FILE   : MktIndexValuesMaintProcess.cpp
// ^AUTHOR : 
// ^DATE   : 
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : MktIndexValuesMaintProcess
//    
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include "stdafx.h"
#include "MktIndexValuesMaintProcess.hpp"
#include "MktIndexValuesMaintProcessincludes.h"
#include <ifastcbo\MktIndexValuesList.hpp>
#include <ifastcbo\MktIndexValues.hpp>
#include <ifastcbo\MktIndexFundsList.hpp>
#include <ifastcbo\MktIndexFunds.hpp>
#include <ifastcbo\FundMasterList.hpp>
#include <ifastcbo\mgmtco.hpp>
#include "mfcaninterprocparam.hpp"
#include "confirmationprocessincludes.h"

#include <ifastdataimpl\dse_dstcglob_vw.hpp>

extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_MKT_INDEX_VALUES;
extern IFASTBP_LINKAGE const I_CHAR* CMD_GUI_MKT_INDEX_VALUES;

#include <bfproc\concreteprocesscreator.hpp>
static ConcreteProcessCreator< MktIndexValuesMaintProcess > processCreator( CMD_BPROC_MKT_INDEX_VALUES );

namespace CND
{
   extern CLASS_IMPORT const long BP_ERR_UNKNOWN_EXCEPTION;
}

namespace 
{
   const I_CHAR * const CLASSNAME = I_( "MktIndexValuesMaintProcess" );
}
namespace ifds 
{
   extern CLASS_IMPORT const BFTextFieldId SearchIndexType;   
}
//******************************************************************************
//              Public Methods
//******************************************************************************
//CP20030319MktIndexValuesMaintProcess::MktIndexValuesMaintProcess() 
MktIndexValuesMaintProcess::MktIndexValuesMaintProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: AbstractProcess( pGIC, pGIParent, rCommand )
,  m_rpChildGI( NULL  ), m_pMktIndexValuesList( NULL )
, m_strSearchType(NULL) , m_strIndexCode(NULL), m_strSearchFromDate(NULL), m_pSearchMktIndexList(NULL)
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );

   addContainer( IFASTBP_PROC::INDICES_LIST, true, BF::NullContainerId, true, I_("IndicesList") );
   addContainer( IFASTBP_PROC::FUNDS_LIST, true, IFASTBP_PROC::INDICES_LIST, true, I_("FundsList") );
   addContainer( MKT_INDEX_SEARCH, false, BF::NullContainerId, true);

   addSubstituteList(ifds::IndexValuesHeading );
   addSubstituteList(ifds::IndexFundsHeading );

   addFieldDetails (ifds::SearchIndexType,	MKT_INDEX_SEARCH); 
   addFieldDetails (ifds::FromDate,		    MKT_INDEX_SEARCH); 

   // Indices List
   addFieldDetails( ifds::EffectiveDate, IFASTBP_PROC::INDICES_LIST );
   addFieldDetails( ifds::IndexCode, IFASTBP_PROC::INDICES_LIST );
   addFieldDetails( ifds::ClosingValue, IFASTBP_PROC::INDICES_LIST );
   addFieldDetails( ifds::GoodBad, IFASTBP_PROC::INDICES_LIST );
   addFieldDetails( ifds::PercentageChanged, IFASTBP_PROC::INDICES_LIST);
   addFieldDetails( ifds::HurdleRate, IFASTBP_PROC::INDICES_LIST ); 
 
   // Admin/Dates details
   addFieldDetails( ifds::ProcessDate, IFASTBP_PROC::INDICES_LIST );
   addFieldDetails( ifds::Username, IFASTBP_PROC::INDICES_LIST );
   addFieldDetails( ifds::ModDate, IFASTBP_PROC::INDICES_LIST );
   addFieldDetails( ifds::ModUser, IFASTBP_PROC::INDICES_LIST );

   // Funds List
   addFieldDetails( ifds::FundCode, IFASTBP_PROC::FUNDS_LIST );
   addFieldDetails( ifds::ClassCode, IFASTBP_PROC::FUNDS_LIST );

   //
   addFieldDetails( INDEX_VALUES::FUNDDESC, IFASTBP_PROC::FUNDS_LIST, SUBCLASS_PROCESS );
   addFieldDetails( InputDataType, IFASTBP_PROC::INDICES_LIST, SUBCLASS_PROCESS );
   addFieldDetails( HAS_OBJECT_UPDATE, IFASTBP_PROC::INDICES_LIST, SUBCLASS_PROCESS );
}

//******************************************************************************

MktIndexValuesMaintProcess::~MktIndexValuesMaintProcess()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************

SEVERITY MktIndexValuesMaintProcess::doInit()
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, I_("doInit") );

   const BFDataGroupId& idDataGroup = getDataGroupId();

   DSTCWorkSession* dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
   dstcWorkSession->getMgmtCo().getFundMasterList( m_pFundMasterList );
   {
      try
      {
    	  if( !m_pSearchMktIndexList )
		  {
			  m_pSearchMktIndexList = new MktIndexValuesList(*dstcWorkSession);
			  SEVERITY sevRtn = dstcWorkSession->setMktIndexValuesList( m_pSearchMktIndexList);
			  if( sevRtn <= WARNING && m_pSearchMktIndexList )
			  {
				  setContainer( IFASTBP_PROC::INDICES_LIST, m_pSearchMktIndexList );      
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
         THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, DOMODELESSSETFOCUS,
                         CND::BP_ERR_UNKNOWN_EXCEPTION );
      }
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
//              Protected Methods
//******************************************************************************

bool MktIndexValuesMaintProcess::doModelessChildComplete( const Command &cmd )
{
   return( cmd.getKey() == CMD_GUI_MKT_INDEX_VALUES );
}

//******************************************************************************

bool MktIndexValuesMaintProcess::doModelessSetFocus( GenericInterface *rpGICaller )
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, I_("doModelessSetFocus") );

   bool bRtn = false;
   try
   {
      assert( m_rpChildGI );
      if( isValidModelessInterface( m_rpChildGI ) )
      {
         bRtn = m_rpChildGI->refresh( this, NULL );
         bRtn = m_rpChildGI->modelessSetFocus( rpGICaller );
      }
   }
   catch( ConditionException &ce )
   {
      SETCONDITIONFROMEXCEPTION( ce );
   }
   catch( ... )
   {
      assert( 0 );
      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, DOMODELESSSETFOCUS,
                      CND::BP_ERR_UNKNOWN_EXCEPTION );
   }

   return( bRtn );
}

//******************************************************************************

E_COMMANDRETURN MktIndexValuesMaintProcess::doProcess()
{  
   MAKEFRAME2( CND::BPBASE_CONDITION, CLASSNAME, DOPROCESS );
   E_COMMANDRETURN rtn = CMD_FAILURE;

   try
   {
      rtn = invokeCommand( this, CMD_GUI_MKT_INDEX_VALUES, getProcessType(), isModal(), &m_rpChildGI );
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

   return( rtn );
}

//******************************************************************************

void* MktIndexValuesMaintProcess::getPtrForContainer( const BFContainerId& idContainer, const BFDataGroupId& idDataGroup )
{
   void *ptr = NULL;
   DSTCWorkSession *dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
   try
   {
      if( IFASTBP_PROC::FUNDS_LIST == idContainer )
      {
		  MktIndexValues *pMktIndexValues = dynamic_cast< MktIndexValues * >( getCBOItem(IFASTBP_PROC::INDICES_LIST, idDataGroup ) );
		  MktIndexFundsList* pMktIndexFundsList = NULL;
		  if( pMktIndexValues->getMktIndexFundsList( pMktIndexFundsList, idDataGroup ) <= WARNING )
		  {
			  ptr = pMktIndexFundsList;
		  }
      }
      else if( IFASTBP_PROC::INDICES_LIST == idContainer )
      {
		  if( dstcWorkSession->getMktIndexValuesList (	m_pMktIndexValuesList,
															idDataGroup,															
															m_strIndexCode,															
															m_strSearchFromDate,
															m_strSearchType,
															NULL_STRING) <= WARNING && m_pMktIndexValuesList)
		  {
			  ptr = m_pMktIndexValuesList;
		  }
      }
	  else if (MKT_INDEX_SEARCH == idContainer)
	  {
		  if (m_pSearchMktIndexList)
		  {
			  ptr = m_pSearchMktIndexList;
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
      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, DOINIT, CND::BP_ERR_UNKNOWN_EXCEPTION );
   }
   return(ptr);
}

//******************************************************************************

bool MktIndexValuesMaintProcess::doSend(GenericInterface *rpGICaller, const I_CHAR *szMessage ) 
{
   DString dstrMessage( szMessage );
   if( dstrMessage == I_("REFRESH") )
   {
      setContainer( IFASTBP_PROC::FUNDS_LIST, NULL );
      return( true );
   }
   if ( dstrMessage == I_("RefreshIndexData") )
	{				

		DString strKey = I_("MktIndexValuesList;SearchType=") + m_strSearchType + 
			I_(";IndexCode=")		+ m_strIndexCode +
			I_(";FromDate=")		+ m_strSearchFromDate  + 
			I_(";ToDate=");
		const BFDataGroupId& idDataGroup = getDataGroupId();
		DSTCWorkSession* dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
		if(dstcWorkSession)
		{
			BFObjIter bfIter (*dstcWorkSession, idDataGroup);
			if (bfIter.positionByKey (strKey))
			{
				bfIter.removeObjectFromMap (true);

			}
			setContainer (IFASTBP_PROC::INDICES_LIST, NULL);
			return( true );
		}
	}
   return(false);
}

//******************************************************************************

SEVERITY MktIndexValuesMaintProcess::performSearch( GenericInterface *rpGI, 
                                                    const BFContainerId& idSearch, 
                                                    E_SEARCHACTION eSearchAction )
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, I_( "performSearch" ) );
   try
   {
	   if(eSearchAction == SEARCH_START)
	   {
		   readSearchParameters ();
		   setContainer (IFASTBP_PROC::INDICES_LIST, NULL);
	   }
	   else if (eSearchAction == SEARCH_NEXT_BLOCK)
	   {
		   if (idSearch == IFASTBP_PROC::INDICES_LIST)
		   {
			   if (m_pMktIndexValuesList)
			   {
				   m_pMktIndexValuesList->getMore();
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
      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, I_( "performSearch" ), 
                      CND::BP_ERR_UNKNOWN_EXCEPTION );
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************

bool MktIndexValuesMaintProcess::doMoreRecordsExist( GenericInterface *rpGICaller, const BFContainerId& idSearch )
{
   return(rpGICaller == NULL || m_pMktIndexValuesList == NULL ? false : 
          m_pMktIndexValuesList->doMoreRecordsExist());
}

//******************************************************************************

bool MktIndexValuesMaintProcess::doOk(GenericInterface *rpGICaller)
{
   setParameter( CONFPROC::PARM_CALLED_FROM, I_("MktIndex") );
   return( true );
}

//******************************************************************************

void MktIndexValuesMaintProcess::doGetField(
                                           const GenericInterface *rpGICaller,
                                           const BFContainerId& idContainer,
                                           const BFFieldId& idField,
                                           const BFDataGroupId& idDataGroup,
                                           DString &strValueOut,
                                           bool bFormatted
                                           ) const
{
   if( idField == INDEX_VALUES::FUNDDESC )
   {
      DString dstrFundCode;
      const_cast<MktIndexValuesMaintProcess*>(this)->getField( rpGICaller, IFASTBP_PROC::FUNDS_LIST, ifds::FundCode, 
                                                               dstrFundCode, false);
      if( !dstrFundCode.empty() )
         m_pFundMasterList->getFundName (dstrFundCode, strValueOut);
      else
         strValueOut = NULL_STRING;
   }
   else  if( idField == InputDataType )
   {
	   if (m_pMktIndexValuesList)
	   {
		   DString strIndexCode;
		   getParameter (MKTINDEXPROC::INDEX_CODE, strIndexCode);
		   strValueOut = m_pMktIndexValuesList->getInputDataType(strIndexCode,idDataGroup,true);
	   }
   }
   else if( idField == HAS_OBJECT_UPDATE )
   {
      if( m_pMktIndexValuesList )
      {
         if( m_pMktIndexValuesList->isUpdatedForDataGroup( idDataGroup ) )
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
//******************************************************************************
void  MktIndexValuesMaintProcess::readSearchParameters ()
{
	getParameter (MKTINDEXPROC::SEARCH_TYPE, m_strSearchType);
	getParameter (MKTINDEXPROC::INDEX_CODE, m_strIndexCode);
	getParameter (MKTINDEXPROC::DATE, m_strSearchFromDate);
	
	m_strSearchType.strip();
	m_strIndexCode.strip();
	m_strSearchFromDate.strip();	
}
// ******************************************************************************
// Revision Control Entries
// ******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastbp/MktIndexValuesMaintProcess.cpp-arc  $
// 
//    Rev 1.10   Mar 06 2012 16:19:34   wp040133
// IN# 2845411 Market Index Value Maintainance Screen Issues. - WO # 743727
// [Check in for Code Review Comments Implementation].
// Issue:After press Search button, then press Add button and Search button again, system will create some record and user can press OK button to confirm.No error but nothing was updated after the confirmation.
// 
// 
//    Rev 1.9   Mar 06 2012 22:40:34   wp040132
// Dosend( ) is called to refresh the indices list when 'Search' button is clicked. Performance Fees - P0188394 and Incident #2845411
// 
//    Rev 1.8   Jan 26 2012 10:52:56   wp040027
// P0188394_Performance Fees - Benchmark Upload (Modifying Search Functionality)
// 
//    Rev 1.7   Jan 16 2012 14:38:52   wp040027
// P0188394_Performance Fees - Benchmark Upload
// 
//    Rev 1.6   Nov 17 2004 15:18:56   popescu
// PET 1117/56, removed 'getField' method at the fund master list level, 
// 
//    Rev 1.5   Mar 21 2003 17:45:30   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.4   Feb 07 2003 14:14:58   HERNANDO
// Added Fund Description.
// 
//    Rev 1.3   Feb 06 2003 18:14:54   HERNANDO
// Revised PercentageChanged field.
// 
//    Rev 1.2   Jan 31 2003 11:27:08   HERNANDO
// Added doOk.
// 
//    Rev 1.1   Jan 29 2003 18:32:48   HERNANDO
// Added doSend.
// 
//    Rev 1.0   Jan 29 2003 12:50:52   HERNANDO
// Initial Revision
// 
//    Rev 1.0   Jan 23 2003 10:26:56   HERNANDO
// Initial Revision
 */
