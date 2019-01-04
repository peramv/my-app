//******************************************************************************
//
// COPYRIGHT:
// 
//    The computer systems, procedures, data bases and
//    programs created and maintained by International Financial Data Services,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    AUTHOR : Monica Vadeanu
//    DATE   : June 2004
//
//
//    Copyright 2004 by International Financial Data Services
//
//******************************************************************************
//
// ^CLASS    : ShrFundSponsorAgreementProcess
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include "stdafx.h"

#include "mfcaninterprocparam.hpp"
#include "ShrFundSponsorAgreementProcess.hpp"
#include "ShrFundSponsorAgreementProcessincludes.h"


#include <ifastcbo\shareholder.hpp>
#include <ifastcbo\ShrFundSponsorAgreementList.hpp>

extern IFASTBP_LINKAGE const I_CHAR* CMD_GUI_SHR_FUND_SPONSOR_AGREEMENT;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_SHR_FUND_SPONSOR_AGREEMENT;

#include <bfproc\concreteprocesscreator.hpp>
static ConcreteProcessCreator< ShrFundSponsorAgreementProcess > processCreator( CMD_BPROC_SHR_FUND_SPONSOR_AGREEMENT );

namespace 
{
   // Trace literals
   const I_CHAR * const CLASSNAME = I_("ShrFundSponsorAgreementProcess");
}

namespace CND
{
   extern CLASS_IMPORT const long BP_ERR_UNKNOWN_EXCEPTION;
}

//******************************************************************************
//              Public Methods
//******************************************************************************
ShrFundSponsorAgreementProcess::ShrFundSponsorAgreementProcess( GenericInterfaceContainer* pGIC, 
																					 GenericInterface* pGIParent, 
																					 const Command& rCommand )
: AbstractProcess(pGIC, pGIParent, rCommand),
_rpChildGI(NULL),
_pShrFundSponsorAgreementList( NULL )
{
   TRACE_CONSTRUCTOR(CLASSNAME, NULL_STRING);
   
   addContainer( IFASTBP_PROC::SHR_FUND_SPONSOR_AGREEMENT_LIST, true,  BF::NullContainerId, true, I_("ShrFundSponsorAgreementList"));	
   
	addFieldDetails(ifds::FundGroup,         IFASTBP_PROC::SHR_FUND_SPONSOR_AGREEMENT_LIST );
	addFieldDetails(ifds::FundGroupDesc,     IFASTBP_PROC::SHR_FUND_SPONSOR_AGREEMENT_LIST );
	addFieldDetails(ifds::EffectiveDate,     IFASTBP_PROC::SHR_FUND_SPONSOR_AGREEMENT_LIST );
	addFieldDetails(ifds::DistribCoopAgrmnt, IFASTBP_PROC::SHR_FUND_SPONSOR_AGREEMENT_LIST );
	
	// Show Admin Dates support
	addFieldDetails(ifds::ModUser,           IFASTBP_PROC::SHR_FUND_SPONSOR_AGREEMENT_LIST );	
	addFieldDetails(ifds::ModDate,           IFASTBP_PROC::SHR_FUND_SPONSOR_AGREEMENT_LIST );	
	addFieldDetails(ifds::ProcessDate,       IFASTBP_PROC::SHR_FUND_SPONSOR_AGREEMENT_LIST );	
	addFieldDetails(ifds::Username,          IFASTBP_PROC::SHR_FUND_SPONSOR_AGREEMENT_LIST );		
}

//******************************************************************************
ShrFundSponsorAgreementProcess::~ShrFundSponsorAgreementProcess()
{
   TRACE_DESTRUCTOR(CLASSNAME);
   _rpChildGI = NULL;   
}

//************************************************************************************
SEVERITY ShrFundSponsorAgreementProcess::doInit()
{
   MAKEFRAMEAUTOPROMOTE2(CND::BPBASE_CONDITION, CLASSNAME, DOINIT);

   try
   {
      processParameters();
   }
   catch(ConditionException& ce)
   {
      SETCONDITIONFROMEXCEPTION(ce);
   }
   catch(...)
   {
      assert(0);
      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, DOINIT, CND::BP_ERR_UNKNOWN_EXCEPTION );
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
E_COMMANDRETURN ShrFundSponsorAgreementProcess::doProcess()
{  
   MAKEFRAME2(CND::BPBASE_CONDITION, CLASSNAME, DOPROCESS);
   E_COMMANDRETURN rtn = CMD_FAILURE;

   try
   {
      setParameter( SHR_FUND_SPONSOR_AGREEMENT::ACCOUNT_NUMBER,     _dstrAccount );
		setParameter( SHR_FUND_SPONSOR_AGREEMENT::SHAREHOLDER_NUMBER, _dstrShareholder );		            

      rtn = invokeCommand( this, 
			                  CMD_GUI_SHR_FUND_SPONSOR_AGREEMENT, 
                           PROC_NO_TYPE, 
									isModal(), 
									&_rpChildGI);
   }
   catch(ConditionException &ce)
   {
      assert(0);
      SETCONDITIONFROMEXCEPTION(ce);
   }
   catch(...)
   {
      assert(0);
      THROWFROMFILE2(CND::BPBASE_CONDITION, CLASSNAME, DOPROCESS, 
         CND::BP_ERR_UNKNOWN_EXCEPTION);
   }
   return rtn;
}

//******************************************************************************
SEVERITY ShrFundSponsorAgreementProcess::doValidateAll(BFAbstractCBO *rpWSD,
   const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::BPBASE_CONDITION, CLASSNAME, I_("doValidateAll"));
	
   if( NULL != _pShrFundSponsorAgreementList )
   {
      _pShrFundSponsorAgreementList->validateAll( idDataGroup );
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
bool ShrFundSponsorAgreementProcess::doModelessSetFocus(GenericInterface *rpGICaller)
{  
	// This is implemented to pass set focus on to child dialog.
   MAKEFRAMEAUTOPROMOTE2(CND::BPBASE_CONDITION, CLASSNAME, DOMODELESSSETFOCUS);

   bool bRtn = false;
   try
   {
      assert(_rpChildGI && isValidModelessInterface(_rpChildGI));
      if( processParameters() <= WARNING )
      {
         if( isValidModelessInterface( _rpChildGI ) )
         {  
				// Only if child still exists            
				setContainer( IFASTBP_PROC::SHR_FUND_SPONSOR_AGREEMENT_LIST, NULL );
            			
				setParameter( SHR_FUND_SPONSOR_AGREEMENT::ACCOUNT_NUMBER,     _dstrAccount );
				setParameter( SHR_FUND_SPONSOR_AGREEMENT::SHAREHOLDER_NUMBER, _dstrShareholder );
				
            bRtn = _rpChildGI->refresh( this, I_("ReloadParams" ) );
            bRtn = _rpChildGI->modelessSetFocus( rpGICaller );
         }
      }
   }
   catch( ConditionException &ce )
   {
      SETCONDITIONFROMEXCEPTION( ce );
   }
   catch(...)
   {
      assert(0);
      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, DOMODELESSSETFOCUS, CND::BP_ERR_UNKNOWN_EXCEPTION );
   }
   return bRtn;
}

//******************************************************************************
bool ShrFundSponsorAgreementProcess::doModelessChildComplete(const Command &cmd)
{
   // End when GUI ends
   return cmd.getKey() == CMD_GUI_SHR_FUND_SPONSOR_AGREEMENT;
}

//******************************************************************************
void *ShrFundSponsorAgreementProcess::getPtrForContainer( const BFContainerId& idContainer,
																		    const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2(CND::BPBASE_CONDITION, CLASSNAME, I_("getPtrForContainer"));
   
	void *ptr = NULL;
      
   try
   {      		
		if ( IFASTBP_PROC::SHR_FUND_SPONSOR_AGREEMENT_LIST == idContainer )
		{			
			DSTCWorkSession* pDSTCWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());

			if( !_dstrShareholder.strip().empty() &&
				 NULL != pDSTCWorkSession )
         {
				Shareholder *pShareholder = NULL;
				if( pDSTCWorkSession->getShareholder( idDataGroup, 
										 						  _dstrShareholder, 
																  pShareholder ) <= WARNING &&
					 NULL != pShareholder )
				{					
					if ( pShareholder->getShrFundSponsorAgreementList( _pShrFundSponsorAgreementList, 
						                                                I_( "" ), 
																						idDataGroup, 
																						true ) < WARNING &&
						  NULL != _pShrFundSponsorAgreementList )
					{
						ptr = _pShrFundSponsorAgreementList;
					}
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
SEVERITY ShrFundSponsorAgreementProcess::processParameters()
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTBP_CONDITION, CLASSNAME, I_("processParameters"));

   getParameter( SHR_FUND_SPONSOR_AGREEMENT::ACCOUNT_NUMBER,     _dstrAccount );
	getParameter( SHR_FUND_SPONSOR_AGREEMENT::SHAREHOLDER_NUMBER, _dstrShareholder );
	
	_dstrAccount.stripAll();
	_dstrShareholder.stripAll();
	
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
bool ShrFundSponsorAgreementProcess::doOk( GenericInterface *rpGICaller )
{	   
	DString dstrShrFundSponsorAgrmntFlag = I_( "N" );

   const BFDataGroupId& idDataGroup = getDataGroupId();
   DSTCWorkSession *pDSTCWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());

	Shareholder *pShareholder = NULL;
   if( NULL != pDSTCWorkSession &&
		 pDSTCWorkSession->getShareholder( idDataGroup, _dstrShareholder, pShareholder ) <= WARNING &&
		 NULL != pShareholder )
   {      
		if ( NULL != _pShrFundSponsorAgreementList )
      {
         BFObjIter iter( *_pShrFundSponsorAgreementList, 
				             idDataGroup, 
								 false, 
								 BFObjIter::ITERTYPE::NON_DELETED );

         while( !iter.end() )
         {
            if( !iter.isDummy() )
            {
               dstrShrFundSponsorAgrmntFlag = I_( "Y" );
               break;
            }
            ++iter;
         }
         
			pShareholder->setField( ifds::ShrFndSpAgrExists, dstrShrFundSponsorAgrmntFlag, idDataGroup, false );
      }
   }
   
   return(true);
}

//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastbp/ShrFundSponsorAgreementProcess.cpp-arc  $
// 
//    Rev 1.1   Jul 27 2004 15:48:08   VADEANUM
// PET1117 FN01 - Shareholder Static Data - first working version.
// 
//    Rev 1.0   Jul 26 2004 10:30:32   VADEANUM
// Initial revision.
//
