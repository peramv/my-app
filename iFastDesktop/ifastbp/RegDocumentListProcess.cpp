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
//    Copyright 1999 by DST Systems, Inc.
//
//******************************************************************************
//
// ^FILE   : RegDocumentListProcess.cpp
// ^AUTHOR :
// ^DATE   :
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : RegDocumentListProcess
//    This class manages the Regulatory Document List information.
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************
//ifastbp
#include "stdafx.h"
#include "regdocumentlistprocessincludes.h"
#include "regdocumentlistprocess.hpp"
#include <ifastcbo\entity.hpp>
#include <ifastcbo\mfaccount.hpp>
#include <ifastcbo\regdocumentlist.hpp>
#include <ifastcbo\worksessionentitylist.hpp>
#include <ifastcbo\errmsgruleslist.hpp>
#include <ifastcbo\mgmtco.hpp>
#include <ifastcbo\Demographics.hpp>

#include <ifastdataimpl\dse_dstcglob_vw.hpp>

extern IFASTBP_LINKAGE const I_CHAR* CMD_GUI_REG_DOCUMENT_LIST;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_REG_DOCUMENT_LIST;
#include <bfproc\concreteprocesscreator.hpp>
static ConcreteProcessCreator< RegDocumentListProcess > processCreator( CMD_BPROC_REG_DOCUMENT_LIST); //CMD_BPROC_ACCT_CATEGORY );

namespace
{
   // Trace literals
   const I_CHAR *CLASSNAME = I_( "RegDocumentListProcess" );
}

namespace CND
{
   extern CLASS_IMPORT const long BP_ERR_UNKNOWN_EXCEPTION;
   extern const long BP_ERR_DOCUMENT_LIST_DATA_REQUIRED;
   extern const long BP_WARN_DOCUMENT_LIST_DATA_REQUIRED;
}

namespace
{
   const I_CHAR * const ACCOUNT_NUM = I_( "AccountNum" );
   const I_CHAR * const ENTITY_ID   = I_( "EntityId" );
   const I_CHAR * const ENTITY      = I_( "Entity" );
   const I_CHAR * const DATE9999	  = I_( "12319999" );
}

namespace AUDITTYPE
{
   extern CLASS_IMPORT I_CHAR * const REGDOCUMENT;
}

namespace NASULIT //nasu literals
{
   extern const I_CHAR * const CREATING_ACCOUNT;
   extern const I_CHAR * const CREATING_SHAREHOLDER;
}

namespace IFASTERR
{
   extern CLASS_IMPORT I_CHAR * const DOCUMENT_LIST_DATA_REQUIRED;
}

namespace ifds
{
   extern CLASS_IMPORT const BFDateFieldId EffectiveDate;
   extern CLASS_IMPORT const BFDateFieldId ExpireDate;
   extern CLASS_IMPORT const BFDateFieldId RequestDate;
   extern CLASS_IMPORT const BFTextFieldId RefNum;
   extern CLASS_IMPORT const BFTextFieldId RegulatoryStandard;
   extern CLASS_IMPORT const BFTextFieldId TaxJurisAppl;
}

namespace COMPLY_RULE
{
   extern CLASS_IMPORT const DString TaxCompliant;
   extern CLASS_IMPORT const DString AccountholderRisk;
}

//******************************************************************************
//              Public Methods
//******************************************************************************
RegDocumentListProcess::RegDocumentListProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: AbstractProcess( pGIC, pGIParent, rCommand )
, _rpChildGI( NULL )
, m_strAcctNum(NULL_STRING)
, m_strEntityId(NULL_STRING)
, m_strNewShareholder(NULL_STRING)
, m_strNewAccount(NULL_STRING)
, m_propEntityNames (NULL)
, m_pDummyRegulatoryStandardList (NULL)
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );

   addContainer( IFASTBP_PROC::MFACCOUNT,     false, BF::NullContainerId,     false, I_("MFAccount") );
   addContainer( IFASTBP_PROC::DOCUMENT_LIST, true,  IFASTBP_PROC::MFACCOUNT, true,  I_("RegDocumentList") );

   addFieldDetails( ifds::RegDocId,          IFASTBP_PROC::DOCUMENT_LIST);
   addFieldDetails( ifds::RegDocName,        IFASTBP_PROC::DOCUMENT_LIST);
   addFieldDetails( ifds::RegDocStatus,      IFASTBP_PROC::DOCUMENT_LIST);
   addFieldDetails( ifds::DocReceivedDate,   IFASTBP_PROC::DOCUMENT_LIST);
   addFieldDetails( ifds::RegDocRemarks,     IFASTBP_PROC::DOCUMENT_LIST);
   addFieldDetails( ifds::ProcessDate,       IFASTBP_PROC::DOCUMENT_LIST);
   addFieldDetails( ifds::Username,          IFASTBP_PROC::DOCUMENT_LIST);
   addFieldDetails( ifds::ModUser,           IFASTBP_PROC::DOCUMENT_LIST);
   addFieldDetails( ifds::ModDate,           IFASTBP_PROC::DOCUMENT_LIST);
   addFieldDetails( ifds::RecId,             IFASTBP_PROC::DOCUMENT_LIST);
   addFieldDetails( ifds::RegDocComplyRule,  IFASTBP_PROC::DOCUMENT_LIST);

   addFieldDetails ( ifds::AccountNum,       IFASTBP_PROC::MFACCOUNT);
   addFieldDetails ( HasRegStandard,         IFASTBP_PROC::MFACCOUNT, SUBCLASS_PROCESS);
   addFieldDetails (CrtEntityId,             BF::NullContainerId, SUBCLASS_PROCESS);
   addFieldDetails (DeathEntityId,           BF::NullContainerId, SUBCLASS_PROCESS);
   addFieldDetails (TaxCompliantEntityId,    BF::NullContainerId, SUBCLASS_PROCESS);
   addFieldDetails (AccountholderRiskEntityId,    BF::NullContainerId, SUBCLASS_PROCESS);

   addFieldDetails (ifds::ComplyRule,        BF::NullContainerId, SUBCLASS_PROCESS);
   addFieldDetails (ifds::EffectiveDate,      IFASTBP_PROC::DOCUMENT_LIST);
   addFieldDetails (ifds::ExpireDate,         IFASTBP_PROC::DOCUMENT_LIST, SUBCLASS_PROCESS);
   addFieldDetails (ifds::RequestDate,        IFASTBP_PROC::DOCUMENT_LIST);
   addFieldDetails (ifds::RefNum,             IFASTBP_PROC::DOCUMENT_LIST);
   addFieldDetails( ifds::RegDocJurisdiction, IFASTBP_PROC::DOCUMENT_LIST );
   addFieldDetails (ifds::TaxJurisAppl,       IFASTBP_PROC::DOCUMENT_LIST );

   addFieldDetails (ifds::TransmitMode,       IFASTBP_PROC::DOCUMENT_LIST );
   addFieldDetails (ifds::CountryOfIssue,     IFASTBP_PROC::DOCUMENT_LIST );
   addFieldDetails (ifds::VerifiedDate,       IFASTBP_PROC::DOCUMENT_LIST );
   addFieldDetails (ifds::DocSource,          IFASTBP_PROC::DOCUMENT_LIST );
   addFieldDetails (ifds::IDMethod,           IFASTBP_PROC::DOCUMENT_LIST );
}

//******************************************************************************
RegDocumentListProcess::~RegDocumentListProcess()
{
   TRACE_DESTRUCTOR( CLASSNAME );

   if (!m_propEntityNames)
   {
      delete m_propEntityNames;
      m_propEntityNames = NULL;
   }

   if (m_pDummyRegulatoryStandardList)
   {
      delete m_pDummyRegulatoryStandardList;
      m_pDummyRegulatoryStandardList = NULL;
   }
}

//******************************************************************************
//              Protected Methods
//******************************************************************************

//******************************************************************************
SEVERITY RegDocumentListProcess::doInit()
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, DOINIT );

   getParameter (ACCOUNT_NUM, m_strAcctNum);
   getParameter (ENTITY_ID, m_strEntityId);

   getParameter (NASULIT::CREATING_SHAREHOLDER, m_strNewShareholder);
   getParameter (NASULIT::CREATING_ACCOUNT, m_strNewAccount);

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
bool RegDocumentListProcess::doModelessChildComplete( const Command &cmd )
{
   // End when GUI ends
   return( cmd.getKey() == CMD_GUI_REG_DOCUMENT_LIST);
}

//******************************************************************************
SEVERITY RegDocumentListProcess::doSetField ( const GenericInterface *rpGICaller,
                                              const BFContainerId &idContainer,
                                              const BFFieldId &idField,
                                              const BFDataGroupId &idDataGroup,
                                              const DString &strValue,
                                              bool bFormatted)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::BPBASE_CONDITION,
                           CLASSNAME,
                           I_("doSetField"));

   if ( idContainer == BF::NullContainerId &&
       (idField == CrtEntityId || idField == DeathEntityId || idField == TaxCompliantEntityId ||
        AccountholderRiskEntityId == idField ))
   {
      setContainer (IFASTBP_PROC::DOCUMENT_LIST, NULL);
      m_strEntityId = strValue;
   }
   else if(idContainer == BF::NullContainerId && idField == ifds::ComplyRule) {
      m_strComplyRule = strValue;
      if(strValue == I_("0"))//Acct Registration
      {
         setField(rpGICaller, BF::NullContainerId, CrtEntityId, I_(""), false);
      }
      else if (strValue == I_("1")) // Death Claim
      {
         setField(rpGICaller, BF::NullContainerId, DeathEntityId, I_(""), false);
      }
      else if(strValue == COMPLY_RULE::TaxCompliant) //Tax Compliant
      {
         setField(rpGICaller, BF::NullContainerId, TaxCompliantEntityId, I_(""), false);
      }
      else if(strValue == COMPLY_RULE::AccountholderRisk) //Accountholder Risk
      {
         setField(rpGICaller, BF::NullContainerId, AccountholderRiskEntityId, I_(""), false);
      }
   }
   else if(idContainer == IFASTBP_PROC::DOCUMENT_LIST)
   {
	   if(idField == ifds::ExpireDate)
	   {
	       BFAbstractCBO *rpPtr = getCBOItem(IFASTBP_PROC::DOCUMENT_LIST, idDataGroup);
           if(rpPtr)
		   {
			   rpPtr->setField(ifds::ExpireDate, strValue, idDataGroup, true);
			   if(strValue == I_( "" ))
			   {
			       rpPtr->setField(ifds::ExpireDate, DATE9999, idDataGroup, true);
			   }
		   }
	  }
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
void RegDocumentListProcess::doGetField ( const GenericInterface *rpGICaller,
                                          const BFContainerId &idContainer,
                                          const BFFieldId &idField,
                                          const BFDataGroupId &idDataGroup,
                                          DString &strValueOut,
                                          bool bFormatted) const
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::BPBASE_CONDITION,
                           CLASSNAME,
                           I_("doGetField"));

   if (idContainer == BF::NullContainerId &&
       (idField == CrtEntityId || idField == DeathEntityId || idField == TaxCompliantEntityId ||
        AccountholderRiskEntityId == idField ))
   {
      if (!m_strEntityId.empty())
      {
         if (idField == CrtEntityId)
         {
            MFAccount *pMFAccount = NULL;
            DSTCWorkSession *dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());

            if (dstcWorkSession->getMFAccount (idDataGroup, m_strAcctNum, pMFAccount) <= WARNING &&
                pMFAccount)
            {
               ENTITIES_VECTOR acctOwnerEntities;

               pMFAccount->getAcctOwnerEntities (acctOwnerEntities, idDataGroup);
               int iNumOfEntities = acctOwnerEntities.size();

               bool isEntityAccountOwner (false);

               for (int i = 0; i < iNumOfEntities; ++i)
               {
                  DString entityId = acctOwnerEntities [i];
                  if (entityId == m_strEntityId)
                  {
                     isEntityAccountOwner = true;
                     break;
                  }
               }
               if (!isEntityAccountOwner)
               {
                  (const_cast<RegDocumentListProcess* > (this))->m_strEntityId = NULL_STRING;
               }
            }
         }
      }
      if (m_strEntityId.empty()) //retrieve the first one in the list.
      {
         bool bDeath = idContainer == BF::NullContainerId && idField == DeathEntityId;
         MFAccount *pMFAccount = NULL;
         DSTCWorkSession *dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());

         if (dstcWorkSession->getMFAccount (idDataGroup, m_strAcctNum, pMFAccount) <= WARNING &&
             pMFAccount)
         {
            DString substList;

            if (!bDeath)
            {
               pMFAccount->getEntitySubstList (idDataGroup, substList, bDeath);
            }
            else
            {
               pMFAccount->getDeadEntities (idDataGroup, substList);
            }

            I_CHAR *temp = const_cast<I_CHAR*> (substList.c_str ());
            DString entityId,
               entityName;

            do
            {
               temp = parseIdiString (temp, entityId, entityName);
               if (!entityId.empty()) //get the first one if the current entity is blank..
               {
                  break;
               }
            } while (temp && temp != NULL_STRING && *temp);

            (const_cast<RegDocumentListProcess* > (this))->m_strEntityId = entityId;
         }
      }
      strValueOut = m_strEntityId;
   }
   else if ( idContainer == BF::NullContainerId && idField == ifds::ComplyRule)
   {
      strValueOut = m_strComplyRule;
   }
   else if (idContainer == IFASTBP_PROC::MFACCOUNT)
   {
       if (idField == HasRegStandard)
       {
           MFAccount *pMFAccount = NULL;
           DSTCWorkSession *dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());

           strValueOut = I_("N");

           if (dstcWorkSession->getMFAccount(idDataGroup, m_strAcctNum, pMFAccount) <= WARNING && pMFAccount)
           {
               DString dstrRegStd;
               Demographics *pDemogrph = NULL;
               if (pMFAccount->getDemographicsList(pDemogrph, idDataGroup) <= WARNING && pDemogrph)
               {
                   pDemogrph->getField(ifds::RegulatoryStandard, dstrRegStd, idDataGroup);
                   strValueOut = dstrRegStd.empty() ? I_("N"):I_("Y");
               }
           }
       }
   }
   else if(idContainer == IFASTBP_PROC::DOCUMENT_LIST)
   {
       if(idField == ifds::ExpireDate)
	   {
		   BFAbstractCBO *rpPtr = const_cast<RegDocumentListProcess*>(this)->getCBOItem(IFASTBP_PROC::DOCUMENT_LIST, idDataGroup);
           if(rpPtr)
		   {
		       rpPtr->getField(ifds::ExpireDate, strValueOut, idDataGroup, bFormatted);
		       if(strValueOut == I_( "" ))
		       {
		           rpPtr->setField(ifds::ExpireDate, DATE9999, idDataGroup, true);
		       }
		   }
       }
   }
}

//******************************************************************************
const BFProperties *RegDocumentListProcess::doGetFieldAttributes ( const GenericInterface *rpGICaller,
                                                                   const BFContainerId &idContainer,
                                                                   const BFFieldId &idField,
                                                                   const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::BPBASE_CONDITION, CLASSNAME, DOGETFIELDATTRIBUTES);

   const BFProperties *pBFProperties = NULL;

   if (idContainer == BF::NullContainerId &&
        (idField == DeathEntityId || idField == CrtEntityId || idField == TaxCompliantEntityId ||
         AccountholderRiskEntityId ==  idField ))
   {
      MFAccount *pMFAccount = NULL;
      DSTCWorkSession *dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
      bool bDeath = idContainer == BF::NullContainerId && idField == DeathEntityId;

      if (dstcWorkSession->getMFAccount (idDataGroup, m_strAcctNum, pMFAccount) <= WARNING &&
          pMFAccount)
      {
         DString substList;

         if (m_propEntityNames)
         {
            delete m_propEntityNames;
            m_propEntityNames = NULL;
         }
         const BFDataFieldProperties* pProps = BFDataFieldProperties::get (ifds::RegDocName);
         m_propEntityNames = new BFProperties (pProps);

		 if(idField == DeathEntityId)
		 {
			 pMFAccount->getDeadEntities (idDataGroup, substList);
		 }
		 else if(idField == CrtEntityId || AccountholderRiskEntityId ==  idField )
		 {
			 pMFAccount->getEntitySubstList (idDataGroup, substList, bDeath);
		 }
		 else if (idField == TaxCompliantEntityId)
		 {
			 pMFAccount->getEntitySubstSet(idDataGroup, substList);
		 }

         m_propEntityNames->setAllSubstituteValues (substList);

         pBFProperties = m_propEntityNames;
      }
   }

   return pBFProperties;
}


//******************************************************************************
bool RegDocumentListProcess::doModelessSetFocus( GenericInterface *rpGICaller )
{  // This is implemented to pass set focus on to child dialog.
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, DOMODELESSSETFOCUS );
   bool bRtn = false;

   try
   {
      getParameter (ACCOUNT_NUM, m_strAcctNum );
      getParameter (ENTITY_ID, m_strEntityId);
      setContainer (IFASTBP_PROC::MFACCOUNT, NULL);
      setContainer (IFASTBP_PROC::DOCUMENT_LIST, NULL);

      if (isValidModelessInterface (_rpChildGI))
      {  // Only if child still exists
         bRtn = _rpChildGI->refresh (this, NULL);
      }
      if( isValidModelessInterface( _rpChildGI ) )
      {  // Only if child still exists
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
      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, DOMODELESSSETFOCUS,
         CND::BP_ERR_UNKNOWN_EXCEPTION );
   }

   return(bRtn);
}

//******************************************************************************
E_COMMANDRETURN RegDocumentListProcess::doProcess()
{
   MAKEFRAME2( CND::BPBASE_CONDITION, CLASSNAME, DOPROCESS );
   E_COMMANDRETURN rtn = CMD_FAILURE;

   setParameter (ACCOUNT_NUM, m_strAcctNum);
   setParameter (ENTITY_ID, m_strEntityId);

   try
   {
      rtn = invokeCommand( this, CMD_GUI_REG_DOCUMENT_LIST, getProcessType(), isModal(),
         &_rpChildGI );
   }
   catch( ConditionException &ce )
   {
      assert( 0 );
      SETCONDITIONFROMEXCEPTION( ce );
   }
   catch( ... )
   {
      assert( 0 );
      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, DOPROCESS,
         CND::BP_ERR_UNKNOWN_EXCEPTION );
   }

   return(rtn);
}

//******************************************************************************
void *RegDocumentListProcess::getPtrForContainer( const BFContainerId& idContainer,
                                                  const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, I_( "getPtrForContainer" ) );

   void *ptr = NULL;
   DSTCWorkSession *dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());

   try
   {
      if (IFASTBP_PROC::MFACCOUNT == idContainer)
      {
         MFAccount *pMFAccount = NULL;
         if( dstcWorkSession->getMFAccount (getDataGroupId(), m_strAcctNum, pMFAccount)
            <= WARNING && pMFAccount)
            ptr = pMFAccount;
      }
      else if (IFASTBP_PROC::DOCUMENT_LIST == idContainer)
      {
         MFAccount *pMFAccount = NULL;
         RegDocumentList *pRegDocumentList = NULL;
         if( dstcWorkSession->getMFAccount (idDataGroup, m_strAcctNum, pMFAccount)
            <= WARNING && pMFAccount)
         {
            WorkSessionEntityList *pWorkEntityList = NULL;
            dstcWorkSession->getWorkSessionEntityList (pWorkEntityList);
            if (pWorkEntityList)
            {
               Entity *pEntity (NULL);

               pWorkEntityList->getEntity (idDataGroup, m_strEntityId, pEntity);

               if(m_strComplyRule == COMPLY_RULE::TaxCompliant)
               {
                  if( pMFAccount->getRegDocumentsList( pRegDocumentList,
                                                      m_strEntityId,
                                                      m_strComplyRule,
                                                      I_(""),
                                                      idDataGroup, true) <= WARNING &&
                     pRegDocumentList)
                  {
                     ptr = pRegDocumentList;
                  }
               }
               else if( COMPLY_RULE::AccountholderRisk == m_strComplyRule )
               {
                 //Acocunt holder risk is not atatched to regulatory but to the entity risk level ,so regStandard is NULL_STRING
                 if(pEntity)
                 {
                     bool bAcctRegDocListForDeadEntity = pEntity->isDead (idDataGroup);
                     if( pMFAccount->getRegDocumentsList(pRegDocumentList, m_strEntityId, m_strComplyRule, NULL_STRING, idDataGroup, true,
                                                             bAcctRegDocListForDeadEntity) <= WARNING &&
                            pRegDocumentList)
                        {
                            ptr = pRegDocumentList;
                        }
                        else if (!pRegDocumentList)
                        {
                           if (!m_pDummyRegulatoryStandardList)
                           {
                              m_pDummyRegulatoryStandardList = new RegDocumentList (*dstcWorkSession);
                           }
                           ptr = m_pDummyRegulatoryStandardList;
                        }
                }
               }
			   else
			   {
				  bool bAcctRegDocListForDeadEntity = pEntity->isDead (idDataGroup) && (m_strComplyRule == I_("1"));

                  if( pMFAccount->getRegDocumentsList( pRegDocumentList,
                                                    m_strEntityId,
                                                    idDataGroup,
													true,
													bAcctRegDocListForDeadEntity) <= WARNING &&
                     pRegDocumentList)
                  {
                     ptr = pRegDocumentList;
                  }
                  else if (!pRegDocumentList)
                  {
                     if (!m_pDummyRegulatoryStandardList)
                     {
                        m_pDummyRegulatoryStandardList = new RegDocumentList (*dstcWorkSession);
                     }
                     ptr = m_pDummyRegulatoryStandardList;
                  }
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
bool RegDocumentListProcess::doOk (GenericInterface *rpGICaller)
{
   //MAKEFRAMEAUTOPROMOTE2 (CND::BPBASE_CONDITION, CLASSNAME, I_("doOk"));
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTBP_CONDITION, CLASSNAME, I_( "doOk" ) );

   RegDocumentList *pRegDocumentList = NULL;
   RegDocumentList *pRegTaxCompliantDocList = NULL;
   MFAccount *pMFAccount = NULL;
   DSTCWorkSession *dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
	bool bWarningContinue = getIgnoreWarningsOnOk2();
	SEVERITY sevRtnDoc = NO_CONDITION;
   SEVERITY sevRtnTaxDoc = NO_CONDITION;
   if (dstcWorkSession->getMFAccount (getDataGroupId(), m_strAcctNum, pMFAccount) <= WARNING && pMFAccount)
   {
      DString strEntityId;
      ENTITIES_VECTOR acctOwnerEntities;

      pMFAccount->getAcctOwnerEntities( acctOwnerEntities, getDataGroupId() );

      int iNumOfEntities = acctOwnerEntities.size();

      for (int i = 0; i < iNumOfEntities; ++i)
      {
         strEntityId = acctOwnerEntities[i] ;

         WorkSessionEntityList *pWorkEntityList = NULL;
         dstcWorkSession->getWorkSessionEntityList (pWorkEntityList);
         if (pWorkEntityList)
         {
            Entity *pEntity (NULL);

            pWorkEntityList->getEntity (getDataGroupId(), strEntityId, pEntity);
            if ( pMFAccount->getRegDocumentsList (pRegDocumentList,
                                                  strEntityId,
                                                  getDataGroupId()) <= WARNING &&
                 pRegDocumentList)
            {
               pRegDocumentList->validateAll (getDataGroupId());
            }

            if(pMFAccount->getRegDocumentsList (pRegTaxCompliantDocList,
                                                            strEntityId,
                                                            COMPLY_RULE::TaxCompliant,
                                                            I_(""),
                                                            getDataGroupId(), true) <= WARNING &&
                  pRegTaxCompliantDocList)
            {
               pRegTaxCompliantDocList->validateAll(getDataGroupId());
            }

            if ( m_strNewShareholder.stripAll().upperCase() == I_("Y") ||
                 m_strNewAccount.stripAll().upperCase()     == I_("Y") )
            {
               BFAbstractCBO *rpPtr = getCBOItem (IFASTBP_PROC::DOCUMENT_LIST, getDataGroupId() );

               if (!rpPtr->hasNonHostUpdates() )
               {
                  DString strErrValue;
                  ErrMsgRulesList* pErrMsgRulesList = NULL;
                  dstcWorkSession->getMgmtCo().getErrMsgRulesList( pErrMsgRulesList );

                  if( pErrMsgRulesList )
                  {
                     pErrMsgRulesList->getEWIValue( IFASTERR::DOCUMENT_LIST_DATA_REQUIRED ,
                                                   getDataGroupId(),
                                                   strErrValue );

                     strErrValue.strip().upperCase();
                     if( strErrValue == I_("E") )
                     {
                        ADDCONDITIONFROMFILE (CND::BP_ERR_DOCUMENT_LIST_DATA_REQUIRED);
                     }
                     else if ( strErrValue == I_("W") )
                     {
                        ADDCONDITIONFROMFILE (CND::BP_WARN_DOCUMENT_LIST_DATA_REQUIRED);
                     }
                  }
                  else
                  {
                     assert(0);
                  }
               }
            }
         }

		if( (sevRtnDoc == WARNING )||(sevRtnTaxDoc == WARNING)&&
			bWarningContinue && !bfutil::isServerContext() )
			{
			bWarningContinue = rpGICaller->send( rpGICaller, I_( "WarningConfirm" ));
			if(!bWarningContinue)
			return GETCURRENTHIGHESTSEVERITY () < WARNING;
			}
      }
      //If there are any documents that have been updated, ask the MFAccount CBO to refresh itself.
      BFObjIter iter(*getCBOList(IFASTBP_PROC::DOCUMENT_LIST, getDataGroupId()), getDataGroupId());
      while(!iter.end())
      {
         if(iter.getObject()->hasNonHostUpdates())
         {
            pMFAccount->refreshMe(true);
            break;
         }
         ++iter;
      }
   }
   return GETCURRENTHIGHESTSEVERITY () <= WARNING;
}

//******************************************************************************
SEVERITY RegDocumentListProcess::getHistoricalParameters( const BFContainerId& idContainer,
                                                          BFFieldId &recordIdField,
                                                          DString& tableId,
                                                          DString& dstrKey)
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, GETHISTORICALPARAMETERS );

   if (idContainer == IFASTBP_PROC::DOCUMENT_LIST)
   {
      recordIdField = ifds::RecId;
      tableId = AUDITTYPE::REGDOCUMENT;
      dstrKey = NULL_STRING;
   }
   else
   {
      assert(0);
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY RegDocumentListProcess::getHistoricalParameters( const BFContainerId& idContainer,
                                                          HISTORICAL_VECTOR &vectorHistorical)
{
   MAKEFRAMEAUTOPROMOTE2(CND::BPBASE_CONDITION, CLASSNAME, GETHISTORICALPARAMETERS);
   return GETCURRENTHIGHESTSEVERITY();
}

//***********************************************************************************
bool RegDocumentListProcess::doMoreRecordsExist(
                                        GenericInterface *rpGICaller,
                                        const BFContainerId& idBFContainerId
                                        )
{
  MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, I_("doMoreRecordsExist" ));

  if(IFASTBP_PROC::DOCUMENT_LIST != idBFContainerId )
     return false;

   return getCBOList(idBFContainerId, getDataGroupId())->doMoreRecordsExist();
}

//******************************************************************************
SEVERITY RegDocumentListProcess::performSearch( GenericInterface *rpGI, const BFContainerId& idSearch, E_SEARCHACTION eSearchAction )
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, I_("PerformSearch" ));

   if(IFASTBP_PROC::DOCUMENT_LIST != idSearch )
     return GETCURRENTHIGHESTSEVERITY();

   SEVERITY sevRtn = SEVERE_ERROR;
   try
   {
      RegDocumentList* pRegDocumentListList = (RegDocumentList* ) (getPtrForContainer(IFASTBP_PROC::DOCUMENT_LIST, getDataGroupId()));
      if(  SEARCH_NEXT_BLOCK == eSearchAction && pRegDocumentListList )
      {
         sevRtn = pRegDocumentListList->getMore();
      }
   }
   catch( ConditionException &ce )
   {
      SETCONDITIONFROMEXCEPTION( ce );
   }
   catch( ... )
   {
      assert( 0 );
      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, I_("PerformSearch") , CND::BP_ERR_UNKNOWN_EXCEPTION );
   }
   return(sevRtn);
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastbp/RegDocumentListProcess.cpp-arc  $
//
//    Rev 1.13   Jul 23 2012 12:22:08   wutipong
// PETP0179630_FN01 FATCA Account Entity Document Tracking
//
//    Rev 1.12   Jun 02 2010 07:06:18   wutipong
// R101 - IN2098027 - Stop Flag of account doesn't get refreshed accordingly on COA screen
//
//    Rev 1.11   Apr 24 2009 04:25:28   dchatcha
// IN 1653090 - The KYC screen need to made mandatory in the NASU process.
//
//    Rev 1.10   06 Nov 2008 17:09:52   popescu
// KYC/AML - Joint accounts feature - after System Integrated Testing
//
//    Rev 1.9   03 Nov 2008 17:32:12   popescu
// KYC/AML - Joint accounts feature - after System Integrated Testing
//
//    Rev 1.8   31 Oct 2008 16:17:20   popescu
// KYC/AML - joint accounts feature
//
//    Rev 1.7   28 Oct 2008 13:11:46   popescu
// PET 59888 FN03 AML KYC - check in to fix complile issues
//
//    Rev 1.6   Oct 28 2008 08:26:30   jankovii
// PET 59888 FN03 AML KYC.
//
//    Rev 1.5   Aug 29 2008 14:30:22   jankovii
// IN 1388930.
//
//    Rev 1.4   Aug 28 2008 14:25:04   jankovii
// IN 1388930 - NASU flow does not update document list unless at least one document.
//
//    Rev 1.3   Aug 01 2008 11:42:42   jankovii
// PET 59888 FN01 AML Enhancement.
//
//    Rev 1.2   Aug 01 2008 10:43:42   jankovii
// PET 59888 FN01 AML Enhancement.
 */
