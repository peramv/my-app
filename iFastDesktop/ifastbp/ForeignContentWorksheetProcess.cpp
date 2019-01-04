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
//    Copyright 2004 by International Financial Data Services
//
//******************************************************************************
//
// ^FILE   : ForeignContentWorksheetProcess.cpp
// ^AUTHOR : Monica Vadeanu
// ^DATE   : April 2004
//
// ----------------------------------------------------------
//
// ^CLASS    : ForeignContentWorksheetProcess
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :  This is the code for a list selection dialog

//******************************************************************************

#include "stdafx.h"
#include "foreigncontentworksheetprocess.hpp"
#include "foreigncontentworksheetprocessincludes.h"
#include "mfcaninterprocparam.hpp"

#include <ifastcbo\hypopurchase.hpp>
#include <ifastcbo\hyporedemption.hpp>
#include <ifastcbo\hypoexchange.hpp>
#include <ifastcbo\hyporollover.hpp>
#include <ifastcbo\hypotradeacb.hpp>
#include <ifastcbo\SupportedProductsList.hpp>
#include <ifastcbo\mgmtco.hpp>


extern IFASTBP_LINKAGE const I_CHAR* CMD_GUI_FOREIGN_CONTENT_WORKSHEET;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_FOREIGN_CONTENT_WORKSHEET;

#include <bfproc\concreteprocesscreator.hpp>
static ConcreteProcessCreator< ForeignContentWorksheetProcess > processCreator( CMD_BPROC_FOREIGN_CONTENT_WORKSHEET );

namespace 
{
   // Trace literals
   const I_CHAR * const CLASSNAME = I_("ForeignContentWorksheetProcess");
}

namespace CND
{
   extern CLASS_IMPORT const long BP_ERR_UNKNOWN_EXCEPTION;
   extern CLASS_IMPORT const long BP_ERR_INVALID_METHOD_CALL;
}

namespace TRADETYPE
{
   extern CLASS_IMPORT I_CHAR * const EXCHANGE;
   extern CLASS_IMPORT I_CHAR * const TRANSFER;
   extern CLASS_IMPORT I_CHAR * const ALL_FUND_TRANSFER;
   extern CLASS_IMPORT I_CHAR * const REDEMPTION;
   extern CLASS_IMPORT I_CHAR * const PURCHASE;
   extern CLASS_IMPORT I_CHAR * const MGMT_FEE;
   extern CLASS_IMPORT I_CHAR * const EXCHANGE_OUT;
   extern CLASS_IMPORT I_CHAR * const EXCHANGE_IN;
   extern CLASS_IMPORT I_CHAR * const TRANSFER_OUT;
   extern CLASS_IMPORT I_CHAR * const TRANSFER_IN;
   extern CLASS_IMPORT I_CHAR * const ROLLOVER;
}
//******************************************************************************
//              Public Methods
//******************************************************************************
ForeignContentWorksheetProcess::ForeignContentWorksheetProcess( GenericInterfaceContainer* pGIC, 
																					 GenericInterface* pGIParent, const Command& rCommand )
: AbstractProcess(pGIC, pGIParent, rCommand),
_rpChildGI(NULL),m_pTrade(NULL),m_pTransTypeProperty(NULL),m_bFirstTime(true)
{
   TRACE_CONSTRUCTOR(CLASSNAME, NULL_STRING);
	              // container ID                    // repeatable // parent container ID         / updateable // name 
	addContainer( IFASTBP_PROC::FOREIGN_CONTENT_TRADE,     false,  BF::NullContainerId,                   true,         I_("ForeignContentTrade"));	
	addContainer( IFASTBP_PROC::FOREIGN_CONTENT_WORKSHEET, true,  IFASTBP_PROC::FOREIGN_CONTENT_TRADE,   true,         I_("ForeignContentWorksheetList"));
   
	//extern CLASS_IMPORT const BFTextFieldId    AccountNum;   
	addFieldDetails(ifds::TradesTransType, IFASTBP_PROC::FOREIGN_CONTENT_TRADE, SUBCLASS_PROCESS );	
	addFieldDetails(ifds::EffectiveDate,   IFASTBP_PROC::FOREIGN_CONTENT_TRADE );	
	addFieldDetails(ifds::FromFundNumber,  IFASTBP_PROC::FOREIGN_CONTENT_TRADE );	
	addFieldDetails(ifds::FromFund,        IFASTBP_PROC::FOREIGN_CONTENT_TRADE );	
	addFieldDetails(ifds::FromClass,       IFASTBP_PROC::FOREIGN_CONTENT_TRADE );	
	addFieldDetails(ifds::ToFundNumber,    IFASTBP_PROC::FOREIGN_CONTENT_TRADE );	
	addFieldDetails(ifds::ToFund,          IFASTBP_PROC::FOREIGN_CONTENT_TRADE );	
	addFieldDetails(ifds::ToClass,         IFASTBP_PROC::FOREIGN_CONTENT_TRADE );	
	addFieldDetails(ifds::Amount,          IFASTBP_PROC::FOREIGN_CONTENT_TRADE );		
	addFieldDetails(ifds::AmtType,         IFASTBP_PROC::FOREIGN_CONTENT_TRADE );	
	
	addFieldDetails(ifds::FromFundName,    IFASTBP_PROC::FOREIGN_CONTENT_TRADE );		
	addFieldDetails(ifds::ToFundName,      IFASTBP_PROC::FOREIGN_CONTENT_TRADE );	

	addFieldDetails(ifds::DomesticACBAmtBefore,				IFASTBP_PROC::FOREIGN_CONTENT_WORKSHEET,SUBCLASS_PROCESS );		
	addFieldDetails(ifds::DomesticPrcntBefore,				IFASTBP_PROC::FOREIGN_CONTENT_WORKSHEET,SUBCLASS_PROCESS );		
	addFieldDetails(ifds::DomesticACBCAmtAfter,				IFASTBP_PROC::FOREIGN_CONTENT_WORKSHEET,SUBCLASS_PROCESS );		
	addFieldDetails(ifds::DomesticPrcntAfter,					IFASTBP_PROC::FOREIGN_CONTENT_WORKSHEET,SUBCLASS_PROCESS );		
	addFieldDetails(ifds::FrgnACBAmtBefore,					IFASTBP_PROC::FOREIGN_CONTENT_WORKSHEET,SUBCLASS_PROCESS );		
	addFieldDetails(ifds::FrgnPrcntBefore,						IFASTBP_PROC::FOREIGN_CONTENT_WORKSHEET,SUBCLASS_PROCESS );		
	addFieldDetails(ifds::FrgnACBAmtAfter,						IFASTBP_PROC::FOREIGN_CONTENT_WORKSHEET,SUBCLASS_PROCESS );		
	addFieldDetails(ifds::FrgnPrcntAfter,						IFASTBP_PROC::FOREIGN_CONTENT_WORKSHEET,SUBCLASS_PROCESS );		
	addFieldDetails(ifds::FrgnAllowedPrcntBefore,         IFASTBP_PROC::FOREIGN_CONTENT_WORKSHEET,SUBCLASS_PROCESS );		
	addFieldDetails(ifds::FrgnAllowedAmtBefore,				IFASTBP_PROC::FOREIGN_CONTENT_WORKSHEET,SUBCLASS_PROCESS );		
	addFieldDetails(ifds::Rate,									IFASTBP_PROC::FOREIGN_CONTENT_WORKSHEET,SUBCLASS_PROCESS );		
	addFieldDetails(ifds::ACBTotalAmtBefore,					IFASTBP_PROC::FOREIGN_CONTENT_WORKSHEET,SUBCLASS_PROCESS );		
//	addFieldDetails(ifds::ACBTotalPrcntBefore,				IFASTBP_PROC::FOREIGN_CONTENT_WORKSHEET );		
	addFieldDetails(ifds::ACBTotalAmtAfter,					IFASTBP_PROC::FOREIGN_CONTENT_WORKSHEET,SUBCLASS_PROCESS );		
//	addFieldDetails(ifds::ACBTotalPrcntAfter,					IFASTBP_PROC::FOREIGN_CONTENT_WORKSHEET,SUBCLASS_PROCESS );		
	addFieldDetails(ifds::FrgnAllowedAmtAfter,				IFASTBP_PROC::FOREIGN_CONTENT_WORKSHEET,SUBCLASS_PROCESS );		
	addFieldDetails(ifds::FrgnAllowedPrcntAfter,				IFASTBP_PROC::FOREIGN_CONTENT_WORKSHEET,SUBCLASS_PROCESS );		

}

//******************************************************************************
ForeignContentWorksheetProcess::~ForeignContentWorksheetProcess()
{
   TRACE_DESTRUCTOR(CLASSNAME);
   _rpChildGI = NULL;   	
	if(m_pTrade)
	{
		delete m_pTrade;
		m_pTrade = NULL;
	}
	if( m_pTransTypeProperty )
	{
		delete m_pTransTypeProperty;
		m_pTransTypeProperty = NULL;
	}
}

//************************************************************************************
SEVERITY ForeignContentWorksheetProcess::doInit()
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
E_COMMANDRETURN ForeignContentWorksheetProcess::doProcess()
{  
   MAKEFRAME2(CND::BPBASE_CONDITION, CLASSNAME, DOPROCESS);
   E_COMMANDRETURN rtn = CMD_FAILURE;

   try
   {
      setParameter( FOREIGN_CONTENT_WORKSHEET::ACCOUNT_NUMBER,     _dstrAccount );		
		setParameter( FOREIGN_CONTENT_WORKSHEET::SHAREHOLDER_NUMBER, _dstrShareholder );		
      
      rtn = invokeCommand( this, 
			                  CMD_GUI_FOREIGN_CONTENT_WORKSHEET, 
                           //PROC_NO_TYPE, 
									getProcessType(),
									isModal(), 
									&_rpChildGI );		
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
SEVERITY ForeignContentWorksheetProcess::doValidateAll(BFAbstractCBO *rpWSD,
   const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::BPBASE_CONDITION, CLASSNAME, I_("doValidateAll"));	   

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
bool ForeignContentWorksheetProcess::doModelessSetFocus(GenericInterface *rpGICaller)
{  // This is implemented to pass set focus on to child dialog.
   MAKEFRAMEAUTOPROMOTE2(CND::BPBASE_CONDITION, CLASSNAME, DOMODELESSSETFOCUS);

   bool bRtn = false;
   try
   {
      assert(_rpChildGI && isValidModelessInterface(_rpChildGI));
      if (processParameters() <= WARNING)
      {
         if (isValidModelessInterface(_rpChildGI))
         {  
				// Only if child still exists            
				//setContainer( IFASTBP_PROC::FOREIGN_CONTENT_WORKSHEET, NULL );           			
				setParameter( FOREIGN_CONTENT_WORKSHEET::ACCOUNT_NUMBER,     _dstrAccount );	
				setParameter( FOREIGN_CONTENT_WORKSHEET::SHAREHOLDER_NUMBER, _dstrShareholder );	

            bRtn = _rpChildGI->refresh(this, I_("ReloadParams"));
            bRtn = _rpChildGI->modelessSetFocus(rpGICaller);
         }
      }
   }
   catch(ConditionException &ce)
   {
      SETCONDITIONFROMEXCEPTION(ce);
   }
   catch(...)
   {
      assert(0);
      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, DOMODELESSSETFOCUS, CND::BP_ERR_UNKNOWN_EXCEPTION );
   }
   return bRtn;
}


//******************************************************************************
SEVERITY ForeignContentWorksheetProcess::doSetField( const GenericInterface *rpGICaller, 
																	  const BFContainerId& idContainer, 
																	  const BFFieldId& idField,
																	  const BFDataGroupId& idDataGroup, 
																	  const DString& strValue, 
																	  bool bFormatted ) 
{  
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, I_("doSetField") );   
   
	DSTCWorkSession* pWkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());

   if( idField == ifds::TradesTransType )  
   {
		if( m_pTrade )
		{
			delete m_pTrade;
			m_pTrade = NULL;			
		}
		DString strTemp(strValue);
		strTemp.strip();
/*		if( strTemp == m_dstrHypoTransType )
		{
			return NO_CONDITION;
		
		}*/
		m_dstrHypoTransType = strTemp;
		if( m_dstrHypoTransType ==TRADETYPE::PURCHASE ) 
		{
			m_pTrade = new HypoPurchase(*pWkSession);
			dynamic_cast< HypoPurchase* >(m_pTrade)->init(_dstrAccount, getDataGroupId() );
		}
		else if(m_dstrHypoTransType ==TRADETYPE::REDEMPTION )
		{
			m_pTrade = new HypoRedemption(*pWkSession);
			dynamic_cast< HypoRedemption* >(m_pTrade)->init(_dstrAccount, getDataGroupId() );
		
		}

		else if(m_dstrHypoTransType ==TRADETYPE::EXCHANGE )
		{
			m_pTrade = new HypoExchange(*pWkSession);
			dynamic_cast< HypoExchange* >(m_pTrade)->init(_dstrAccount, getDataGroupId() );
		
		}
		else if(m_dstrHypoTransType ==TRADETYPE::ROLLOVER )
		{
			m_pTrade = new HypoRollover(*pWkSession);
			dynamic_cast< HypoRollover* >(m_pTrade)->init(_dstrAccount, getDataGroupId() );	
		}
		else 
		{
			assert( 0 );
		}
		SEVERITY sevRtn = GETCURRENTHIGHESTSEVERITY();
		if(m_pTrade)
		{
		   setContainer( IFASTBP_PROC::FOREIGN_CONTENT_TRADE, m_pTrade );
		}

	}
   else
   {
      assert( 0 );   
      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, GETFIELD, CND::BP_ERR_INVALID_METHOD_CALL );
   };

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
void ForeignContentWorksheetProcess::doGetField( const GenericInterface *rpGICaller,
                                                 const BFContainerId& idContainer,
                                                 const BFFieldId &idField,
                                                 const BFDataGroupId& idDataGroup,
                                                 DString &strValueOut,
                                                 bool bFormatted ) const
{
	if(idContainer == IFASTBP_PROC::FOREIGN_CONTENT_TRADE )
	{
		if( idField == ifds::TradesTransType )  //here we know it is a valid existing account
		{
			strValueOut = m_dstrHypoTransType;	
		}
	}
	else if(idContainer == IFASTBP_PROC::FOREIGN_CONTENT_WORKSHEET )
	{

		HypoTradeACBInterface* pACBInterface = dynamic_cast<HypoTradeACBInterface* >(m_pTrade);
		if(pACBInterface)
		{
			HypoTradeACB*  pHypoTradeACB = NULL;
			SEVERITY sevRtn1 =pACBInterface->getHypoTradeACB(m_pTrade,pHypoTradeACB,
						getDataGroupId(),true);
			if(sevRtn1 <= WARNING &&  pHypoTradeACB)
			{

				pHypoTradeACB->getField(idField,strValueOut,idDataGroup,bFormatted);
			}	
		}	
	}
   else
   {
      assert( 0 );   
      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, GETFIELD, CND::BP_ERR_INVALID_METHOD_CALL );
   };
}

//*******************************************************************************

SEVERITY ForeignContentWorksheetProcess::doGetErrors( const GenericInterface* rpGICaller,
                                 const BFContainerId& idContainer,
                                 const BFFieldId& fieldID,
                                 const BFDataGroupId& idDataGroup,
                                 CONDITIONVECTOR& conditions ) const
{

   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, I_("doGetErrors") );   
	if(idContainer == IFASTBP_PROC::FOREIGN_CONTENT_TRADE )
	{
		if( fieldID == ifds::TradesTransType )  //here we know it is a valid existing account
		{
			 if(m_pTrade)
			 {
				return (m_pTrade->getErrors( fieldID, idDataGroup, conditions ) ); 		 
			 }
		
		}
	}
   
   
   AbstractProcess::doGetErrors( rpGICaller, idContainer, fieldID, idDataGroup, conditions );
   

   return(GETCURRENTHIGHESTSEVERITY());

}

//******************************************************************************
const BFProperties *ForeignContentWorksheetProcess::doGetFieldAttributes( const GenericInterface *rpGICaller, 																								 
																								  const BFContainerId& idContainer, 
																								  const BFFieldId& idField, 
																								  const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, I_("doGetFieldAttributes") );

   const BFProperties * pBFProp = NULL;
   if( idField == ifds::TradesTransType )
   {

		if(m_bFirstTime)
		{

			if(!m_pTransTypeProperty)
			{
				const BFDataFieldProperties* pProps = BFDataFieldProperties::get( ifds::HypoTransType );
				m_pTransTypeProperty = new BFProperties(pProps);

				SupportedProductsList* pSupportedProductsList = NULL;
				MgmtCo &mgmtCom = dynamic_cast<DSTCWorkSession *>(getBFWorkSession())->getMgmtCo();
				SEVERITY sevRtn = mgmtCom.getSupportedProductsList(pSupportedProductsList);
				

				if ( sevRtn <= WARNING &&  pSupportedProductsList)
				{
					if (!pSupportedProductsList->isLSIFProductActive ())
					{
						DString dstrSubst;
						m_pTransTypeProperty->getAllSubstituteValues(dstrSubst);
						int nPos = dstrSubst.find (TRADETYPE::ROLLOVER);
						dstrSubst = dstrSubst.left (nPos);
						m_pTransTypeProperty->setAllSubstituteValues(dstrSubst);					
					}				
				}				
				
			}
			pBFProp = m_pTransTypeProperty;
		}
		else
		{
			if(m_pTrade)
			{
				pBFProp = m_pTrade->getFieldProperties( idField, idDataGroup );
			}
		}
   }   
   else
   {
      assert( 0 );   
      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, GETFIELD, CND::BP_ERR_INVALID_METHOD_CALL );
   };

   return(pBFProp);
}

//******************************************************************************
bool ForeignContentWorksheetProcess::doModelessChildComplete(const Command &cmd)
{
   // End when GUI ends
   return cmd.getKey() == CMD_GUI_FOREIGN_CONTENT_WORKSHEET;
}

//******************************************************************************
SEVERITY ForeignContentWorksheetProcess::processParameters()
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTBP_CONDITION, CLASSNAME, I_("processParameters"));

   getParameter( FOREIGN_CONTENT_WORKSHEET::ACCOUNT_NUMBER,     _dstrAccount );
	getParameter( FOREIGN_CONTENT_WORKSHEET::SHAREHOLDER_NUMBER, _dstrShareholder );
	
	_dstrAccount.strip();
	_dstrShareholder.strip();
	
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************


SEVERITY ForeignContentWorksheetProcess::performSearch( GenericInterface *rpGI, 
                                           const BFContainerId& idSearch, 
														 E_SEARCHACTION eSearchAction )
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, I_( "performSearch" ) );
	if( m_pTrade )
	{
		SEVERITY sevRtn = m_pTrade->validateAll( getDataGroupId() );
		if( sevRtn <= WARNING )
		{

			HypoTradeACBInterface* pACBInterface = dynamic_cast<HypoTradeACBInterface* >(m_pTrade);
			if(pACBInterface)
			{
				HypoTradeACB*  pHypoTradeACB = NULL;
			   SEVERITY sevRtn1 =pACBInterface->getHypoTradeACB(m_pTrade,pHypoTradeACB,
							getDataGroupId(),true);
				if(sevRtn1 <= WARNING &&  pHypoTradeACB)
				{
					setContainer( IFASTBP_PROC::FOREIGN_CONTENT_WORKSHEET, pHypoTradeACB );				
				}			
			}
		}
	}
	return GETCURRENTHIGHESTSEVERITY();
}

//************************************************************************************
bool ForeignContentWorksheetProcess::doSend(
                               GenericInterface *rpGICaller,
                               const I_CHAR *szMessage
                               )
{
   TRACE_METHOD( CLASSNAME, DOSEND );
   DString str( szMessage );
   if( str == I_("OnBtnRefresh") )
   {

		m_bFirstTime = true;
   }
	else if(str == I_("TransTypeSelect")  )
	{
		m_bFirstTime = false;
	
	
	}
   return(true);
}





//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastbp/ForeignContentWorksheetProcess.cpp-arc  $
// 
//    Rev 1.6   Nov 07 2004 14:06:02   popescu
// PET 1117/06, synch changes
// 
//    Rev 1.5   Jun 03 2004 11:00:56   YINGBAOL
// PTS10030671:display Roll over depends on production support list
// 
//    Rev 1.4   May 26 2004 09:51:44   YINGBAOL
// PET985Limplement doGetError
// 
//    Rev 1.3   May 25 2004 10:07:34   YINGBAOL
// PET985: implement FundName
// 
//    Rev 1.2   May 19 2004 17:41:42   YINGBAOL
// PET985: make hypo work
// 
//    Rev 1.1   Apr 26 2004 14:01:30   VADEANUM
// PET985 FN01 - Foreign Content - work in progress.
// 
//    Rev 1.0   Apr 21 2004 15:38:02   VADEANUM
// Initial revision.
//
