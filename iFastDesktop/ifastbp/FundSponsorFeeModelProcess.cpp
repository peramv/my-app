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
// ^FILE   : FundSponsorFeeModelProcess.cpp
// ^AUTHOR : 
// ^DATE   : July 21, 2004  
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : FundSponsorFeeModelProcess
//    This class manages the address book process.
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include "stdafx.h"
#include "fundsponsorfeemodelprocessinclude.h"
#include "fundsponsorfeemodelprocess.hpp"
#include <ifastcbo\mfaccount.hpp>
#include <ifastcbo\FundSponsorFeeModelList.hpp>
#include <ifastcbo\FundSponsorFeeModel.hpp>
#include <ifastcbo\FeeScaleList.hpp>
#include <ifastcbo\FundSponsorFee.hpp>
#include <ifastcbo\FundSponsorFeeList.hpp>
#include <ifastcbo\mgmtco.hpp>
#include <ifastcbo\MFAccountList.hpp>
#include <ifastcbo\Shareholder.hpp>
#include <ifastcbo\FundSponsorsList.hpp>
#include <bfcbo\bfobjiter.hpp>
#include <ifastcbo\FeeModelList.hpp>

extern IFASTBP_LINKAGE const I_CHAR* CMD_GUI_FUNDSPONSOR_FEE_MODEL;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_FUNDSPONSOR_FEE_MODEL;

#include <bfproc\concreteprocesscreator.hpp>
static ConcreteProcessCreator< FundSponsorFeeModelProcess > processCreator( CMD_BPROC_FUNDSPONSOR_FEE_MODEL );

namespace
{
   // Trace literals
   const I_CHAR *CLASSNAME = I_( "FundSponsorFeeModelProcess" );
   const I_CHAR * const YES	= I_( "Y" );
   const I_CHAR * const NO	= I_( "N" );
}

namespace FUNDSPONSORFEEMODEL
{
   const I_CHAR * const FROM_SCR = I_( "from_screen" );
   const I_CHAR * const ACCOUNTNUM = I_( "AccountNum" );
   const I_CHAR * const FEE_MODEL_CODE = I_( "FeeModelCode" );
   const I_CHAR * const SEARCHTYPE = I_( "SearchType" );   
   const I_CHAR * const FUND_SPONSOR_CODE = I_( "FundSponsorCode" );
   const I_CHAR * const SYSTEM = I_( "System" );
   const I_CHAR * const ALL = I_( "All" );
   const I_CHAR * const ACCOUNTSCR = I_( "Account" );   

   const I_CHAR * const FEEMODELLIST = I_( "FeeModelList" );
   const I_CHAR * const FEELIST = I_( "FeeList" );
   const I_CHAR * const SCALE	= I_( "2" );
   const I_CHAR * const TIER	= I_( "3" );
}

namespace CND
{  // Conditions used
   extern CLASS_IMPORT const long BP_ERR_UNKNOWN_EXCEPTION;
}
namespace ifds
{   
   extern CLASS_IMPORT const BFTextFieldId FeeModelCode;
   extern CLASS_IMPORT const BFTextFieldId FeeModelDesc;
   extern CLASS_IMPORT const BFTextFieldId Username;
   extern CLASS_IMPORT const BFTextFieldId ModUser;
   extern CLASS_IMPORT const BFTextFieldId SearchModelCode;

   extern CLASS_IMPORT const BFTextFieldId FundGroup;
   extern CLASS_IMPORT const BFTextFieldId FundGroupDesc;
   extern CLASS_IMPORT const BFTextFieldId ChargeOption;
   extern CLASS_IMPORT const BFTextFieldId FeeModelOption;
   extern CLASS_IMPORT const BFTextFieldId FeeCode;
   extern CLASS_IMPORT const BFTextFieldId ParamFeeType;
   extern CLASS_IMPORT const BFDecimalFieldId Rate;
   extern CLASS_IMPORT const BFTextFieldId Currency;

   extern CLASS_IMPORT const BFDateFieldId EffectiveDate;
   extern CLASS_IMPORT const BFDateFieldId StopDate;
   extern CLASS_IMPORT const BFDateFieldId ProcessDate;
   extern CLASS_IMPORT const BFDateFieldId ModDate;

   extern CLASS_IMPORT const BFDecimalFieldId ScaleRate;
   extern CLASS_IMPORT const BFDecimalFieldId UpperBound;
   extern CLASS_IMPORT const BFDecimalFieldId LowerBound;
   extern CLASS_IMPORT const BFDecimalFieldId MinFee;
   extern CLASS_IMPORT const BFDecimalFieldId MaxFee;
   extern CLASS_IMPORT const BFNumericFieldId AccountNum;
   extern CLASS_IMPORT const BFNumericFieldId ShrNum;
   extern CLASS_IMPORT const BFDecimalFieldId Level;
   extern CLASS_IMPORT const BFTextFieldId CommGroup;
   extern CLASS_IMPORT const BFTextFieldId SearchModelDesc;

   extern CLASS_IMPORT const BFTextFieldId AccountNumList;
}
//******************************************************************************
//              Public Methods
//******************************************************************************

//CP20030319FundSponsorFeeModelProcess::FundSponsorFeeModelProcess() 
FundSponsorFeeModelProcess::FundSponsorFeeModelProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: AbstractProcess( pGIC, pGIParent, rCommand )
,  _pShareholder( NULL )
,  _rpChildGI( NULL )
, _pFundSponsorFeeModelList (NULL)
{
   TRACE_CONSTRUCTOR( CLASSNAME, I_( "FundSponsorFeeModelProcess" ) );

   addContainer( IFASTBP_PROC::FUNDSPONSOR_FEE_MODEL_LIST, true, BF::NullContainerId, true, I_("FundSponsorFeeModel") );
   addContainer( IFASTBP_PROC::FUNDSPONSOR_FEE_LIST, true, IFASTBP_PROC::FUNDSPONSOR_FEE_MODEL_LIST, true, I_("FundSponsorFee") );
   addContainer( IFASTBP_PROC::FEE_SCALE_LIST, true, IFASTBP_PROC::FUNDSPONSOR_FEE_LIST, true );
   
   addContainer( IFASTBP_PROC::SHAREHOLDER_CBO, false, BF::NullContainerId, true );
   //addContainer( IFASTBP_PROC::MFACCOUNT_LIST,  true, IFASTBP_PROC::SHAREHOLDER_CBO, true );
   addContainer( IFASTBP_PROC::MFACCOUNT_CBO,   false, BF::NullContainerId, true, I_("Account") );

   addFieldDetails( ifds::FeeModelCode,   IFASTBP_PROC::FUNDSPONSOR_FEE_MODEL_LIST );
   addFieldDetails( ifds::FeeModelDesc,   IFASTBP_PROC::FUNDSPONSOR_FEE_MODEL_LIST );
   addFieldDetails( ifds::FundGroup,      IFASTBP_PROC::FUNDSPONSOR_FEE_MODEL_LIST );
   addFieldDetails( ifds::FundGroupDesc,  IFASTBP_PROC::FUNDSPONSOR_FEE_MODEL_LIST );
   addFieldDetails( ifds::FeeModelOption, IFASTBP_PROC::FUNDSPONSOR_FEE_MODEL_LIST );
   addFieldDetails( ifds::EffectiveDate,  IFASTBP_PROC::FUNDSPONSOR_FEE_MODEL_LIST );   
   addFieldDetails( ifds::StopDate,       IFASTBP_PROC::FUNDSPONSOR_FEE_MODEL_LIST );
   addFieldDetails( ifds::ProcessDate,    IFASTBP_PROC::FUNDSPONSOR_FEE_MODEL_LIST );
   addFieldDetails( ifds::ModDate,        IFASTBP_PROC::FUNDSPONSOR_FEE_MODEL_LIST );
   addFieldDetails( ifds::Username,       IFASTBP_PROC::FUNDSPONSOR_FEE_MODEL_LIST );
   addFieldDetails( ifds::ModUser,        IFASTBP_PROC::FUNDSPONSOR_FEE_MODEL_LIST );

   addFieldDetails( ifds::FeeCode,        IFASTBP_PROC::FUNDSPONSOR_FEE_LIST );
   addFieldDetails( ifds::ParamFeeType,   IFASTBP_PROC::FUNDSPONSOR_FEE_LIST );
   addFieldDetails( ifds::Rate,           IFASTBP_PROC::FUNDSPONSOR_FEE_LIST );
   addFieldDetails( ifds::EffectiveDate,  IFASTBP_PROC::FUNDSPONSOR_FEE_LIST );
   addFieldDetails( ifds::StopDate,       IFASTBP_PROC::FUNDSPONSOR_FEE_LIST );
   addFieldDetails( ifds::Currency,       IFASTBP_PROC::FUNDSPONSOR_FEE_LIST );
   addFieldDetails( ifds::ChargeOption,   IFASTBP_PROC::FUNDSPONSOR_FEE_LIST );
   addFieldDetails( ifds::FeeModelCode,   IFASTBP_PROC::FUNDSPONSOR_FEE_LIST );
   addFieldDetails( ifds::CommGroup,      IFASTBP_PROC::FUNDSPONSOR_FEE_LIST );
   addFieldDetails( ifds::MinFee,         IFASTBP_PROC::FUNDSPONSOR_FEE_LIST );
   addFieldDetails( ifds::MaxFee,         IFASTBP_PROC::FUNDSPONSOR_FEE_LIST );

   addFieldDetails( ifds::ScaleRate,      IFASTBP_PROC::FEE_SCALE_LIST );
   addFieldDetails( ifds::UpperBound,     IFASTBP_PROC::FEE_SCALE_LIST );
   addFieldDetails( ifds::LowerBound,     IFASTBP_PROC::FEE_SCALE_LIST );
   addFieldDetails( ifds::MinFee,         IFASTBP_PROC::FEE_SCALE_LIST );
   addFieldDetails( ifds::MaxFee,         IFASTBP_PROC::FEE_SCALE_LIST );
   addFieldDetails( ifds::Level,          IFASTBP_PROC::FEE_SCALE_LIST );
   addFieldDetails( ifds::FeeCode,        IFASTBP_PROC::FEE_SCALE_LIST );

   addFieldDetails( ifds::FeeModelCode,   IFASTBP_PROC::MFACCOUNT_CBO ); 
   addFieldDetails( ifds::AccountNum,     IFASTBP_PROC::MFACCOUNT_CBO, SUBCLASS_PROCESS);   
   addFieldDetails( ifds::FeeModelDesc,   IFASTBP_PROC::MFACCOUNT_CBO, SUBCLASS_PROCESS);

   addFieldDetails( ifds::FeeModelCode,   IFASTBP_PROC::SHAREHOLDER_CBO );
   addFieldDetails( ifds::ShrNum,         IFASTBP_PROC::SHAREHOLDER_CBO );
   addFieldDetails( ifds::FeeModelDesc,   IFASTBP_PROC::SHAREHOLDER_CBO, SUBCLASS_PROCESS );

   addFieldDetails( ifds::AccountNumList,  IFASTBP_PROC::SHAREHOLDER_CBO );

   addFieldDetails( ifds::SearchModelCode, BF::NullContainerId, SUBCLASS_PROCESS );
   addFieldDetails( ifds::SearchModelDesc, BF::NullContainerId, SUBCLASS_PROCESS ); 
   addFieldDetails( FUNDSPONSORFEEMODEL::FeeModelExists, BF::NullContainerId, SUBCLASS_PROCESS);
   
   LlistParam * feemodellistParam = new LlistParam(IFASTBP_PROC::FUNDSPONSOR_FEE_MODEL_LIST);
   LlistParam * feelistParam = new LlistParam(IFASTBP_PROC::FUNDSPONSOR_FEE_LIST);

   _listmap.insert( LIST_MAP_VALUE_TYPE( FUNDSPONSORFEEMODEL::FEEMODELLIST, feemodellistParam) );
   _listmap.insert( LIST_MAP_VALUE_TYPE( FUNDSPONSORFEEMODEL::FEELIST, feelistParam) );

}

//******************************************************************************
FundSponsorFeeModelProcess::~FundSponsorFeeModelProcess()
{
   TRACE_DESTRUCTOR( CLASSNAME );

	LIST_MAP_ITER iter = _listmap.begin();
   while( iter != _listmap.end() )
   {
      delete (*iter).second;
      ++iter;
   }
   _listmap.clear();	
}

//******************************************************************************
SEVERITY FundSponsorFeeModelProcess::doInit()
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, DOINIT );
   DSTCWorkSession *pDSTCWorkSession = dynamic_cast<DSTCWorkSession *> (getBFWorkSession());
   const BFDataGroupId& idDataGroup = getDataGroupId();
   SEVERITY sevRtn = NO_CONDITION;
   
   try
   {
      processParameters ();
      if (!m_AcctNum.empty())
      {
         MFAccount* mfAccount = NULL;

         if ( pDSTCWorkSession->getMFAccount (idDataGroup, m_AcctNum, mfAccount) <= WARNING &&
              mfAccount)
         {
            setContainer (IFASTBP_PROC::MFACCOUNT_CBO, mfAccount); 
            DString dstrShrNum;

			   mfAccount->getField (ifds::ShrNum, dstrShrNum, idDataGroup);
            if ( pDSTCWorkSession->getShareholder (idDataGroup, dstrShrNum, _pShareholder) <= WARNING &&
                 _pShareholder)
            {
               setContainer (IFASTBP_PROC::SHAREHOLDER_CBO, _pShareholder);
               
               MFAccountList *pMFAccountList = NULL;
               if ( _pShareholder->getMFAccountList (pMFAccountList, idDataGroup) <= WARNING &&
                    pMFAccountList)
               { 
                  pMFAccountList->getAccountNumSubstList (m_AccountNumSubList, idDataGroup);
               }
               _pShareholder->setFieldAllSubstituteValues (ifds::AccountNumList, idDataGroup, m_AccountNumSubList);
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
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
E_COMMANDRETURN FundSponsorFeeModelProcess::doProcess()
{  
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, DOPROCESS );
   E_COMMANDRETURN rtn = CMD_FAILURE;

   try
   {
      if (isXMLAPIContext())
      {
         rtn = CMD_MODELESS_INPROCESS;
      }
      else
      {
         setParameter (FUNDSPONSORFEEMODEL::FROM_SCR, m_frSCR);
         setParameter (FUNDSPONSORFEEMODEL::SEARCHTYPE, m_SearchType);
         setParameter (FUNDSPONSORFEEMODEL::ACCOUNTNUM, m_AcctNum);
         setParameter (FUNDSPONSORFEEMODEL::FEE_MODEL_CODE, m_FeeModelCode);
         setParameter (FUNDSPONSORFEEMODEL::FUND_SPONSOR_CODE, m_FundSponsorCode);
         rtn = invokeCommand (this, CMD_GUI_FUNDSPONSOR_FEE_MODEL, getProcessType(), isModal(), &_rpChildGI);
      }
   }
   catch (ConditionException &ce)
   {
      SETCONDITIONFROMEXCEPTION (ce);
   }
   catch ( ... )
   {
      assert (0);
      THROWFROMFILE2 (CND::BPBASE_CONDITION, CLASSNAME, DOPROCESS, CND::BP_ERR_UNKNOWN_EXCEPTION);
   }
   return rtn;
}

//******************************************************************************
bool  FundSponsorFeeModelProcess::doModelessSetFocus (GenericInterface *rpGICaller)
{  
   MAKEFRAMEAUTOPROMOTE2 (CND::BPBASE_CONDITION, CLASSNAME, DOMODELESSSETFOCUS);

   bool bRtn = false;
   try
   {
      assert (_rpChildGI && isValidModelessInterface (_rpChildGI));
      if (isValidModelessInterface(_rpChildGI))
      {  // Only if child still exists
         processParameters ();
         setContainer (IFASTBP_PROC::FUNDSPONSOR_FEE_MODEL_LIST, NULL);
         setParameter (FUNDSPONSORFEEMODEL::FROM_SCR, m_frSCR);
         setParameter (FUNDSPONSORFEEMODEL::SEARCHTYPE, m_SearchType);
         setParameter (FUNDSPONSORFEEMODEL::ACCOUNTNUM, m_AcctNum);
         setParameter (FUNDSPONSORFEEMODEL::FEE_MODEL_CODE, m_FeeModelCode);
         setParameter (FUNDSPONSORFEEMODEL::FUND_SPONSOR_CODE, m_FundSponsorCode);
         bRtn = _rpChildGI->refresh (this, I_("ReloadParams"));
         bRtn = _rpChildGI->modelessSetFocus (rpGICaller);
      }
   }
   catch (ConditionException &ce)
   {
      SETCONDITIONFROMEXCEPTION(ce);
   }
   catch (...)
   {
      assert(0);
      THROWFROMFILE2(CND::BPBASE_CONDITION, CLASSNAME, DOMODELESSSETFOCUS,
         CND::BP_ERR_UNKNOWN_EXCEPTION);
   }
   return bRtn;
}

//******************************************************************************
bool  FundSponsorFeeModelProcess::doModelessChildComplete (const Command &cmd)
{
   // End when GUI ends
   return cmd.getKey() == CMD_GUI_FUNDSPONSOR_FEE_MODEL;
}

//******************************************************************************
void* FundSponsorFeeModelProcess::getPtrForContainer ( const BFContainerId &idContainer, 
                                                       const BFDataGroupId &idDataGroup)
{
   void *ptr = NULL;
   DSTCWorkSession *pDSTCWorkSession = dynamic_cast <DSTCWorkSession *> (getBFWorkSession());
   try
   {
      if (idContainer == IFASTBP_PROC::FUNDSPONSOR_FEE_MODEL_LIST)
      {
         if ( pDSTCWorkSession->getFundSponsorFeeModelList ( _pFundSponsorFeeModelList, 
                                                             idDataGroup,
                                                             true,
                                                             m_FeeModelCode,
                                                             m_FundSponsorCode,
                                                             m_frSCR == FUNDSPONSORFEEMODEL::ACCOUNTSCR && 
                                                             !m_FeeModelCode.empty() && 
                                                             m_FundSponsorCode.empty()) <= WARNING &&
              _pFundSponsorFeeModelList)
         {			
            ptr = _pFundSponsorFeeModelList;
         }
      }
      else if (idContainer == IFASTBP_PROC::FUNDSPONSOR_FEE_LIST)
      { 
         FundSponsorFeeList *_pFundSponsorFeeList = NULL;
         if ( isContainerValid (IFASTBP_PROC::FUNDSPONSOR_FEE_MODEL_LIST) && 
               getNumberOfItemsInList (this, IFASTBP_PROC::FUNDSPONSOR_FEE_MODEL_LIST) > 0)
         {			 
			FundSponsorFeeModel * pFundSponsorFeeModel = NULL;
			if( m_frSCR == FUNDSPONSORFEEMODEL::ACCOUNTSCR && 
				!m_FeeModelCode.empty() && m_FundSponsorCode.empty())
			{
				_pFundSponsorFeeModelList->getFundSponsorFeeModel(m_FeeModelCode, pFundSponsorFeeModel, idDataGroup );
				if( pFundSponsorFeeModel )
				{
					pFundSponsorFeeModel = dynamic_cast < FundSponsorFeeModel *> (getCBOItem( IFASTBP_PROC::FUNDSPONSOR_FEE_MODEL_LIST, idDataGroup ));
				}
			}
			else
			{
				pFundSponsorFeeModel = dynamic_cast < FundSponsorFeeModel *> (getCBOItem( IFASTBP_PROC::FUNDSPONSOR_FEE_MODEL_LIST, idDataGroup ));
			}
			
			if (pFundSponsorFeeModel) 
			{
				pFundSponsorFeeModel->getFundSponsorFeeList(_pFundSponsorFeeList, idDataGroup);
			}
         
            if (_pFundSponsorFeeList)
            {
               BFObjIter iterFundSponsorFeeList(*_pFundSponsorFeeList, getDataGroupId());

               LIST_MAP_ITER iter = _listmap.find( FUNDSPONSORFEEMODEL::FEELIST );
               if( iter != _listmap.end())
               {
                  LlistParam * feelistParam = (*iter).second;
                  feelistParam->m_totalNum = iterFundSponsorFeeList.getNumberOfItemsInList();
                  if( feelistParam->m_totalNum > 25 ) feelistParam->m_dispNum = 25;
                  else feelistParam->m_dispNum = feelistParam->m_totalNum;
                  feelistParam->setEndKey(asString(feelistParam->m_dispNum + 512 -1 ));
               }
            }
         }
         ptr = _pFundSponsorFeeList;
      }
      else if (idContainer == IFASTBP_PROC::FEE_SCALE_LIST)
      {
         FeeScaleBaseList *pFeeScaleList = NULL;
         if ( isContainerValid (IFASTBP_PROC::FUNDSPONSOR_FEE_LIST) && 
              getNumberOfItemsInList (this, IFASTBP_PROC::FUNDSPONSOR_FEE_LIST) > 0)
         {
            FundSponsorFee *pFundSponsorFee = 
               dynamic_cast <FundSponsorFee*> (getCBOItem (IFASTBP_PROC::FUNDSPONSOR_FEE_LIST, idDataGroup));
         
            if (pFundSponsorFee)
            {               
               if ( pFundSponsorFee->getFeeScaleList (pFeeScaleList, idDataGroup) <= WARNING && 
                    pFeeScaleList)
               {
                  ptr = pFeeScaleList;
               }
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
      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, DOINIT,
                      CND::BP_ERR_UNKNOWN_EXCEPTION );
   }
   return(ptr);
}

//******************************************************************************
bool FundSponsorFeeModelProcess::doRefresh ( GenericInterface *rpGICaller,
                                             const I_CHAR *szOriginalCommand)
{
   return _rpChildGI->refresh (this, NULL);
}

//******************************************************************************
void FundSponsorFeeModelProcess::doGetField( const GenericInterface *rpGICaller,
                                             const BFContainerId& idContainer,
                                             const BFFieldId& idField,
                                             const BFDataGroupId& idDataGroup,
                                             DString &strValueOut,
                                             bool bFormatted) const
{
   DSTCWorkSession *dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());

   if (idContainer == IFASTBP_PROC::MFACCOUNT_CBO)
   {      
      const BFAbstractCBO *rpPtr = 
         ( const_cast < FundSponsorFeeModelProcess*>( this ) )->getCBOItem (IFASTBP_PROC::MFACCOUNT_CBO, idDataGroup);
      if (idField == ifds::FeeModelDesc)
      {
         DString dstrFeeModelCode;
         if (rpPtr)
         {              
            rpPtr->getField (ifds::FeeModelCode, dstrFeeModelCode, idDataGroup, false);            
         }

         FeeModelList* pFeeModelList = NULL;

         if ( dstrFeeModelCode.stripAll() != NULL_STRING && 
              dstcWorkSession->getFeeModelList(pFeeModelList, BF::HOST, NULL_STRING, NULL_STRING, dstrFeeModelCode) <= WARNING &&
              pFeeModelList)
         {
            pFeeModelList->getDescByFeeModelCode (getDataGroupId(), dstrFeeModelCode, strValueOut);
	      }
      }
      else if (idField == ifds::AccountNum)
      {
         if (rpPtr)
         {              
            rpPtr->getField (ifds::AccountNum, strValueOut, idDataGroup, false);            
         }
      }
   }
   else if (idContainer == IFASTBP_PROC::SHAREHOLDER_CBO)
   {
      const BFAbstractCBO *rpPtr = 
         ( const_cast < FundSponsorFeeModelProcess*>( this ) )->getCBOItem (IFASTBP_PROC::SHAREHOLDER_CBO, idDataGroup);

      if (idField == ifds::FeeModelDesc)
      {
         DString dstrFeeModelCode;

         if (rpPtr)
         {              
            rpPtr->getField( ifds::FeeModelCode, dstrFeeModelCode, idDataGroup, false );            
         }

         FeeModelList* pFeeModelList = NULL;
         if (dstrFeeModelCode.stripAll() != NULL_STRING && 
             dstcWorkSession->getFeeModelList (pFeeModelList, BF::HOST, NULL_STRING, NULL_STRING, dstrFeeModelCode) <= WARNING &&
              pFeeModelList)
         {
            pFeeModelList->getDescByFeeModelCode(getDataGroupId(), dstrFeeModelCode, strValueOut);
	      }
      }
   }
   else if (idContainer == BF::NullContainerId)
   {
      if (idField == ifds::SearchModelCode)
      {
         if (m_SearchType == FUNDSPONSORFEEMODEL::FEE_MODEL_CODE)
         {
            strValueOut = m_FeeModelCode;
         }
         else if (m_SearchType == FUNDSPONSORFEEMODEL::FUND_SPONSOR_CODE)
         {
            strValueOut = m_FundSponsorCode;
         }
         else if (m_frSCR == FUNDSPONSORFEEMODEL::ACCOUNTSCR)
         {          
            if (m_AcctNum != NULL_STRING)
            {
               MFAccount* mfAccount = NULL;

               dstcWorkSession->getMFAccount( getDataGroupId(), m_AcctNum, mfAccount );
               if (mfAccount) 
               {
                  mfAccount->getField(ifds::FeeModelCode, strValueOut, getDataGroupId());
               }
            }         
         }
      }
      else if (idField == ifds::SearchModelDesc)
      {
         if (m_SearchType == FUNDSPONSORFEEMODEL::FUND_SPONSOR_CODE)
         {
		      FundSponsorsList* pFundSponsorsList = NULL;      
		      if ( dstcWorkSession->getMgmtCo ().getFundSponsorsList (pFundSponsorsList) <= WARNING &&
			        pFundSponsorsList)
		      {
			      BFAbstractCBO *pFundSponsor = NULL;
			      if ( pFundSponsorsList->getFundSponsor (m_FundSponsorCode, pFundSponsor) <= WARNING &&
				        pFundSponsor)
			      {				
				      pFundSponsor->getField( ifds::FundGroupDesc, strValueOut, BF::HOST, false );				   
			      }                		
		      }
         }
         else if (m_SearchType == FUNDSPONSORFEEMODEL::FEE_MODEL_CODE)
         {
            FeeModelList* pFeeModelList = NULL;

            if(m_FeeModelCode != NULL_STRING)
            {
               dstcWorkSession->getFeeModelList (pFeeModelList, BF::HOST, NULL_STRING, NULL_STRING, m_FeeModelCode);
               if (pFeeModelList)
               {
                  pFeeModelList->getDescByFeeModelCode(getDataGroupId(), m_FeeModelCode, strValueOut);
	            }	
            }
         }
      }
      else if (idField == FUNDSPONSORFEEMODEL::FeeModelExists)
      {
         FeeModelList* pFeeModelList = NULL;         
         FeeModel *pFeeModel = NULL;

         if ( m_FeeModelCode != NULL_STRING && dstcWorkSession->getFeeModelList (pFeeModelList, BF::HOST, NULL_STRING, NULL_STRING, m_FeeModelCode) <= WARNING &&
              pFeeModelList)
         {            
            pFeeModelList->getFeeModel (m_FeeModelCode, pFeeModel, getDataGroupId());
	      }
         strValueOut = pFeeModel ? I_("Y") : I_("N");
      }
   }  
}

//*****************************************************************************
SEVERITY FundSponsorFeeModelProcess::doSetField ( const GenericInterface *rpGICaller,
                                                  const BFContainerId &idContainer,
                                                  const BFFieldId &fieldID,
                                                  const BFDataGroupId &idDataGroup,
                                                  const DString &strValue,
                                                  bool bFormatted )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTBP_CONDITION, CLASSNAME, DOSETFIELD );
   
   DSTCWorkSession *dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
   
   if (idContainer == BF::NullContainerId)
   {
      if (fieldID == ifds::SearchModelCode)
      {
         if (m_frSCR == FUNDSPONSORFEEMODEL::ACCOUNTSCR)
         {
            if (m_AcctNum != NULL_STRING)
            {
               MFAccount* mfAccount;
               
               dstcWorkSession->getMFAccount(getDataGroupId(), m_AcctNum, mfAccount);
               if (mfAccount) 
               {
                  mfAccount->setField (ifds::FeeModelCode, strValue, getDataGroupId());
               }
            }
         }
      }
   }
   if (idContainer == IFASTBP_PROC::MFACCOUNT_CBO)
   {
      if (fieldID == ifds::AccountNum)
      {
         if (m_frSCR == FUNDSPONSORFEEMODEL::ACCOUNTSCR)
         {
            MFAccount* mfAccount;
            
            dstcWorkSession->getMFAccount (getDataGroupId(), strValue, mfAccount);
            if (mfAccount) 
            {               
               //change of the container if user changes the account num of the combo field
               setContainer (IFASTBP_PROC::MFACCOUNT_CBO, NULL);
               setContainer (IFASTBP_PROC::MFACCOUNT_CBO, mfAccount);
            }
         }
      }
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//*****************************************************************************
SEVERITY FundSponsorFeeModelProcess::performSearch ( GenericInterface *rpGI, 
                                                     const BFContainerId &idSearch, 
                                                     E_SEARCHACTION eSearchAction)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::BPBASE_CONDITION, CLASSNAME, I_("performSearch"));
   SEVERITY sevRtn = NO_CONDITION;

   try
   {
      if (idSearch == IFASTBP_PROC::FUNDSPONSOR_FEE_MODEL_LIST)
      {
         if (_pFundSponsorFeeModelList)
         {
            _pFundSponsorFeeModelList->getMore();
         }
      }
      else
      { 
         adjustKey (idSearch);
      }
   }
   catch (ConditionException &ce)
   {
      SETCONDITIONFROMEXCEPTION (ce);
   }
   catch (...)
   {
      assert( 0 );
      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, I_("performSearch"), CND::BP_ERR_UNKNOWN_EXCEPTION );
   }
   return sevRtn; 
}

//***********************************************************************************
bool FundSponsorFeeModelProcess::doMoreRecordsExist ( GenericInterface *rpGICaller,
                                                      const BFContainerId& idSearch)
{
   if (idSearch == IFASTBP_PROC::FUNDSPONSOR_FEE_MODEL_LIST)
   {
      return 
         (rpGICaller == NULL || _pFundSponsorFeeModelList == NULL) ?    
            false : _pFundSponsorFeeModelList->doMoreRecordsExist();
   }
   if (idSearch == IFASTBP_PROC::FUNDSPONSOR_FEE_LIST)
   {
      LIST_MAP_ITER iter = _listmap.find (FUNDSPONSORFEEMODEL::FEELIST);
      if( iter.operator->() != NULL && iter != _listmap.end() )
      {
         LlistParam * feemodellistParam = (*iter).second;
         if( feemodellistParam->m_dispNum < feemodellistParam->m_totalNum )
            return true;
         else 
            return false;
      }         
   }
   return false;
}

//******************************************************************************
bool FundSponsorFeeModelProcess::doOk (GenericInterface *rpGICaller)
{
   TRACE_METHOD (CLASSNAME, I_("doOk"));

	SEVERITY sev = NO_CONDITION;

   if (_pShareholder)
   {
     sev = _pShareholder->validateModelCode (getDataGroupId());
	}
   return sev <= WARNING;
}

//******************************************************************************
const DString& FundSponsorFeeModelProcess::getNextListItemKey ( const GenericInterface *rpGICaller, 
                                                                const BFContainerId &idList)
{  
   TRACE_METHOD( CLASSNAME, GETNEXTLISTITEMKEY );

   static DString key = NULL_STRING;

   try
   {
      if (idList == IFASTBP_PROC::FUNDSPONSOR_FEE_LIST)
      {
         LIST_MAP_ITER iter = _listmap.find( FUNDSPONSORFEEMODEL::FEELIST );
         if( iter != _listmap.end() )
         {
            LlistParam * feelistParam = (*iter).second;
            if( feelistParam->getPrevKey() == feelistParam->getEndKey() )
            {
               return key;
            }  
            else
            {               
               feelistParam->setPrevKey(AbstractProcess::getNextListItemKey( rpGICaller, idList ));
               return AbstractProcess::getCurrentListItemKey (rpGICaller, idList);
            }
         }         
      }
      if ( idList == IFASTBP_PROC::FEE_SCALE_LIST ||
           idList == IFASTBP_PROC::FUNDSPONSOR_FEE_MODEL_LIST)
      {
         return AbstractProcess::getNextListItemKey( rpGICaller, idList );
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

   return key;
}

//******************************************************************************
const DString& FundSponsorFeeModelProcess::getFirstListItemKey ( const GenericInterface *rpGICaller, 
                                                                 const BFContainerId &idList)
{  
   TRACE_METHOD (CLASSNAME, GETFIRSTLISTITEMKEY);

   const static DString key = NULL_STRING;
   try
   {
      if (idList == IFASTBP_PROC::FUNDSPONSOR_FEE_LIST)
      {
         if( !isContainerValid(idList) ) return key;

         LIST_MAP_ITER iter = _listmap.find( FUNDSPONSORFEEMODEL::FEELIST );
         if( iter != _listmap.end() )
         {
            LlistParam * feelistParam = (*iter).second;
            feelistParam->setPrevKey( AbstractProcess::getFirstListItemKey( rpGICaller, idList ) );

            return (AbstractProcess::getCurrentListItemKey( rpGICaller, idList ));
         }
      }
      if( idList == IFASTBP_PROC::FEE_SCALE_LIST ||
          idList == IFASTBP_PROC::FUNDSPONSOR_FEE_MODEL_LIST)
      {
         if (!isContainerValid (idList)) return key;
         return AbstractProcess::getFirstListItemKey (rpGICaller, idList);
      }
   }
   catch( ConditionException & )
   {
      throw;
   }
   catch ( ... )
   {  // Just to catch at earliest point
      assert( 0 );
      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, GETFIRSTLISTITEMKEY,
                      CND::BP_ERR_UNKNOWN_EXCEPTION );
   }
   return key;
}

//******************************************************************************
void FundSponsorFeeModelProcess::processParameters ()
{
   getParent()->getParameter (FUNDSPONSORFEEMODEL::FROM_SCR, m_frSCR);
   m_frSCR.stripLeading( '0' ).strip();
   getParent()->getParameter (FUNDSPONSORFEEMODEL::ACCOUNTNUM, m_AcctNum);
   m_AcctNum.stripLeading( '0' ).strip();
   getParent()->getParameter (FUNDSPONSORFEEMODEL::FEE_MODEL_CODE, m_FeeModelCode);
   m_FeeModelCode.strip();
   getParent()->getParameter (FUNDSPONSORFEEMODEL::FUND_SPONSOR_CODE, m_FundSponsorCode);
   m_FundSponsorCode.strip();
   getParent()->getParameter (FUNDSPONSORFEEMODEL::SEARCHTYPE, m_SearchType);
   m_SearchType.strip();
}

//******************************************************************************
void FundSponsorFeeModelProcess::adjustKey( const BFContainerId& idList )
{
   if( idList == IFASTBP_PROC::FUNDSPONSOR_FEE_LIST )
   {
      FundSponsorFeeList * _pFundSponsorFeeList;
      FundSponsorFeeModel * pFundSponsorFeeModel = 
         dynamic_cast < FundSponsorFeeModel *> (getCBOItem( IFASTBP_PROC::FUNDSPONSOR_FEE_MODEL_LIST, getDataGroupId() ));
      pFundSponsorFeeModel->getFundSponsorFeeList(_pFundSponsorFeeList, getDataGroupId());

      if( _pFundSponsorFeeList )
      {
         LIST_MAP_ITER iter = _listmap.find( FUNDSPONSORFEEMODEL::FEELIST );
         if( iter != _listmap.end() )
         {
            LlistParam * feelistParam = (*iter).second;
            if( feelistParam->m_totalNum > feelistParam->m_dispNum + 25 )
            {
               feelistParam->m_dispNum = feelistParam->m_dispNum  + 25;
               feelistParam->m_More++;
            }
            else
            {
               feelistParam->m_dispNum = feelistParam->m_totalNum;
            }

            BFObjIter fundsponsoriter( *_pFundSponsorFeeList, getDataGroupId(), true, BFObjIter::ITERTYPE::NON_DELETED, false, true );
            int i=0;
            DString dstrKey; 
            while (/*i<feelistParam->m_dispNum && */!fundsponsoriter.end()) // think about dummy record
            {
               dstrKey = fundsponsoriter.getStringKey();
               ++fundsponsoriter;
               i++;
            }             
            feelistParam->setEndKey( dstrKey );                      
         }  
      }
   }
   return;
}

//******************************************************************************
bool FundSponsorFeeModelProcess::doSend(GenericInterface *rpGICaller, const I_CHAR *szMessage ) 
{
   DString dstrMessage( szMessage );
   if (dstrMessage == I_("CLEAR FEE PARAMETER CONTAINER"))
   {
      setContainer (IFASTBP_PROC::FUNDSPONSOR_FEE_LIST, NULL);
      setContainer (IFASTBP_PROC::FEE_SCALE_LIST, NULL );
      return true;
   }
   else if (dstrMessage == I_("CLEAR FEE SCALE CONTAINER"))
   {
      setContainer( IFASTBP_PROC::FEE_SCALE_LIST, NULL );
      return  true;
   }
   else if (dstrMessage == I_("Refresh_FeeModelCode"))
   {
      if (m_frSCR == FUNDSPONSORFEEMODEL::ACCOUNTSCR)
      {
         getParameter (I_("FeeModelCode"), m_FeeModelCode);
         setContainer (IFASTBP_PROC::FUNDSPONSOR_FEE_MODEL_LIST, NULL);
         setContainer (IFASTBP_PROC::FUNDSPONSOR_FEE_LIST, NULL);
         setContainer (IFASTBP_PROC::FEE_SCALE_LIST, NULL);
      }
      return true;
   }
   return false;
}


//******************************************************************************
LlistParam::LlistParam( BFContainerId idList )
{
   this->idList = idList;
   this->m_dispNum = 0;
   this->m_totalNum = 0;
   this->m_dstrPrevKey = NULL_STRING;
   this->m_dstrEndKey = NULL_STRING;
}

void LlistParam::setPrevKey( DString dstrPrevKey )
{
   this->m_dstrPrevKey = dstrPrevKey;
}

const DString& LlistParam::getPrevKey()
{
   return m_dstrPrevKey;
}

void LlistParam::setEndKey( DString dstrEndKey )
{
   this->m_dstrEndKey = dstrEndKey;
}

const DString& LlistParam::getEndKey()
{
   return m_dstrEndKey;
}


//******************************************************************************
//              Private Methods
//******************************************************************************

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/FundSponsorFeeModelProcess.cpp-arc  $
// 
//    Rev 1.19   Jul 27 2005 15:42:26   Fengyong
// Incident 352435 - continue fix 
// 
//    Rev 1.18   Jul 19 2005 15:52:22   Fengyong
// Incident 352435 - fix crash problem
// 
//    Rev 1.17   Jul 13 2005 17:37:32   popescu
// Incident 352435 - improved performance on the fund sponsor fee model screen - get rid of the wacky keys
// 
//    Rev 1.16   Mar 24 2005 16:00:00   Fengyong
// Incident #260676 - Add max min to fundsponsor fee parameter
// 
//    Rev 1.15   Jan 21 2005 17:34:04   Fengyong
// PET10037902 - show all the records after click more button
// 
//    Rev 1.14   Dec 22 2004 09:17:16   yingbaol
// PTS10037147: Fix more button issue.
// 
//    Rev 1.13   Sep 24 2004 18:52:50   FENGYONG
// Add dosend function
// 
//    Rev 1.12   Sep 21 2004 16:56:20   FENGYONG
// show search model desc on the screen
// 
//    Rev 1.9   Sep 20 2004 16:50:38   FENGYONG
// Add CommGroup
// 
//    Rev 1.8   Sep 20 2004 15:37:24   FENGYONG
// add fields for gui filter
// 
//    Rev 1.7   Sep 20 2004 11:10:46   YINGBAOL
// PET1117:FN05 Fee Model at account/shareholder level can be part of NASU
// 
//    Rev 1.6   Sep 09 2004 16:54:10   FENGYONG
// implemant child relation ship between lists
// 
//    Rev 1.5   Sep 09 2004 12:39:04   FENGYONG
// more button - PET1117 FN5
// 
//    Rev 1.4   Sep 02 2004 12:34:24   FENGYONG
// temp check in for other people test
// 
//    Rev 1.3   Aug 31 2004 17:32:00   FENGYONG
// change field name
// 
//    Rev 1.2   Aug 11 2004 18:40:14   FENGYONG
// PET 1117 FN05 Syncup after get files resource 
// 
//    Rev 1.1   Aug 10 2004 11:12:08   FENGYONG
// PET117 FN5 - Client Condition Fee
// 
//    Rev 1.0   Aug 09 2004 10:04:22   FENGYONG
// Initial revision.
// 
 *
 */
