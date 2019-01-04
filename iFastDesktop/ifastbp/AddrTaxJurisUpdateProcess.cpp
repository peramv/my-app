
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
// ^FILE   : AddrTaxJurisUpdateProcess.cpp
// ^AUTHOR : Wutipong W.  
// ^DATE   : 14/10/2008
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : AddrTaxJurisUpdateProcess
//    This class manages the management company and profile selection.
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include "stdafx.h"
#include "AddrTaxJurisUpdateProcess.hpp"
extern IFASTBP_LINKAGE const I_CHAR* CMD_GUI_ADDR_TAX_JURIS_UPDATE;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_ADDR_TAX_JURIS_UPDATE;
#include <bfproc\concreteprocesscreator.hpp>
#include <ifastcbo\shareholder.hpp>
#include <ifastcbo\AccountEntityXref.hpp>
#include <ifastcbo\Entity.hpp>
static ConcreteProcessCreator< AddrTaxJurisUpdateProcess > processCreator( CMD_BPROC_ADDR_TAX_JURIS_UPDATE );

namespace CND
{  // Conditions used
   extern CLASS_IMPORT const long BP_ERR_UNKNOWN_EXCEPTION;
}

namespace
{
   const I_CHAR *CLASSNAME             = I_( "AddrTaxJurisUpdateProcess" );

}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId OldTaxJuris;
   extern CLASS_IMPORT const BFTextFieldId OldResProv;
   extern CLASS_IMPORT const BFTextFieldId UpdShrTaxJuris;
   extern CLASS_IMPORT const BFTextFieldId UpdShrProvRes;
   
   extern CLASS_IMPORT const BFTextFieldId ResProvCode;
   extern CLASS_IMPORT const BFTextFieldId TaxJurisCode;
   extern CLASS_IMPORT const BFTextFieldId AccountNum;
   extern CLASS_IMPORT const BFTextFieldId TaxJuris;
   extern CLASS_IMPORT const BFTextFieldId FirstName;
   extern CLASS_IMPORT const BFTextFieldId LastName;
   extern CLASS_IMPORT const BFTextFieldId OldAcctOwnersTaxJuris;
}

namespace IFASTBP_PROC
{
   extern IFASTBP_LINKAGE const BFContainerId ADDR_TAX_JURIS_UPDATE;
}

namespace ADDRLIT
{
   const I_CHAR * const ACCOUNT_NUM = I_( "AccountNum" );
   const I_CHAR * const SHAREHOLDER_NUM = I_( "ShareholderNum" );
   const I_CHAR * const SETTLEMENT = I_( "Settlement" );
   const I_CHAR * const ADDRESS_KEY = I_( "AddressKey" );   
   const I_CHAR * const ENTITY_ID  = I_( "EntityID" );
   const I_CHAR * const UPDATE_TAX_JURIS  = I_( "UpdShrTaxJuris" );
   const I_CHAR * const UPDATE_PROV_RES  = I_( "UpdShrProvRes" );
}

//******************************************************************************

AddrTaxJurisUpdateProcess::AddrTaxJurisUpdateProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: AbstractProcess( pGIC, pGIParent, rCommand )
, _rpChildGI(NULL)

{
   TRACE_CONSTRUCTOR( CLASSNAME , NULL_STRING );
   
   //addContainer(IFASTBP_PROC::ADDR_TAX_JURIS_UPDATE, true, BF::NullContainerId);
   addFieldDetails(ifds::OldTaxJuris, BF::NullContainerId, SUBCLASS_PROCESS);
   addFieldDetails(ifds::OldResProv, BF::NullContainerId, SUBCLASS_PROCESS);
   addFieldDetails(ifds::UpdShrTaxJuris, BF::NullContainerId, SUBCLASS_PROCESS);
   addFieldDetails(ifds::UpdShrProvRes, BF::NullContainerId, SUBCLASS_PROCESS);

   addFieldDetails(ifds::OldAcctOwnersTaxJuris, BF::NullContainerId, SUBCLASS_PROCESS);

}

//******************************************************************************

AddrTaxJurisUpdateProcess::~AddrTaxJurisUpdateProcess()
{

}

//******************************************************************************

void AddrTaxJurisUpdateProcess::doGetField( const GenericInterface *rpGICaller,
                                    const BFContainerId& idContainer,
                                    const BFFieldId& idField,
                                    const BFDataGroupId& idDataGroup,
                                    DString &strValueOut,
                                    bool bFormatted ) const
{

   DSTCWorkSession *dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());

   if(idContainer == BF::NullContainerId)
   {      
      if(idField == ifds::OldTaxJuris)
      {
         m_pShareholder->getField(ifds::TaxJurisCode,strValueOut, idDataGroup, true);
      }
      else if(idField == ifds::OldResProv)
      {
         m_pShareholder->getField(ifds::ResProvCode,strValueOut, idDataGroup, true);
      }
      else if(idField == ifds::UpdShrProvRes)
      {     
         strValueOut = m_dstrProvRes;
      }
      else if(idField == ifds::UpdShrTaxJuris)
      {
         strValueOut = m_dstrTaxJuris;
      }
	  else if(idField == ifds::OldAcctOwnersTaxJuris)
	  {
		   MFAccount *pMFAccount = NULL;
		   		   
		   dstcWorkSession->getMFAccount( getDataGroupId(), m_dstrAcctNum, pMFAccount );

		   ENTITIES_VECTOR acctOwnerEntities;

		   pMFAccount->getAcctOwnerEntities (acctOwnerEntities, idDataGroup) ;

		   int iNumOfEntities = acctOwnerEntities.size();            

		   for (int i = 0; i < iNumOfEntities; ++i)
		   {
			   Entity *pEntity = NULL;
			   DString dstrEntityId = acctOwnerEntities [i];
			   DString dstrTaxJuris = NULL_STRING;
 
			   if( dstcWorkSession->getEntity( idDataGroup, dstrEntityId, pEntity ) <= WARNING )
			   {
				   pEntity->getField(ifds::TaxJuris, dstrTaxJuris, idDataGroup, true);				   

				   // inquire the name
				   DString  dstrFirstName, dstrLastName, dstrNewLine = I_("\r\n");
				   pEntity->getField(ifds::FirstName, dstrFirstName, idDataGroup, false);				   						   
				   pEntity->getField(ifds::LastName, dstrLastName, idDataGroup, false);
				   
				   strValueOut += dstrLastName + I_(";") + dstrFirstName + I_(" = ") + dstrTaxJuris + dstrNewLine;

			   }

		   }			   


	  }
   }
}

//******************************************************************************
SEVERITY AddrTaxJurisUpdateProcess::doSetField( const GenericInterface* rpGICaller,
                                const BFContainerId& idContainer,
                                const BFFieldId &fieldID,
                                const BFDataGroupId& idDataGroup,
                                const DString &strValue,
                                bool bFormatted )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTBP_CONDITION, CLASSNAME, I_("doSetField") );
    if(idContainer == BF::NullContainerId)
   {      
      if(fieldID == ifds::UpdShrProvRes)
      { 
         m_dstrProvRes = strValue;
      }
      else if(fieldID == ifds::UpdShrTaxJuris)
      {
         m_dstrTaxJuris = strValue;
      }
   }
   
   return GETHIGHESTSEVERITY();
}

//******************************************************************************

SEVERITY AddrTaxJurisUpdateProcess::doInit()
{
    MAKEFRAMEAUTOPROMOTE2( CND::IFASTBP_CONDITION, CLASSNAME, DOINIT );

   // SEVERITY sevRtn = SEVERE_ERROR, sevRtn1 = SEVERE_ERROR;
   try
   {
      getParameter(ADDRLIT::ACCOUNT_NUM, m_dstrAcctNum);
      getParameter(ADDRLIT::SHAREHOLDER_NUM, m_dstrShrNum);
      
      dynamic_cast<DSTCWorkSession*>(getBFWorkSession())->
         getShareholder(getDataGroupId(),
            m_dstrShrNum, m_pShareholder);
      
      //Default = set to 'y' (update).
      m_dstrTaxJuris = I_("Y");
      m_dstrProvRes = I_("Y");
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

bool AddrTaxJurisUpdateProcess::doModelessChildComplete( const Command &cmd )
{
   return( cmd.getKey()==CMD_GUI_ADDR_TAX_JURIS_UPDATE );
}

//******************************************************************************

bool AddrTaxJurisUpdateProcess::doModelessSetFocus( GenericInterface *rpGICaller )
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

E_COMMANDRETURN AddrTaxJurisUpdateProcess::doProcess()
{  
   MAKEFRAME2( CND::IFASTBP_CONDITION, CLASSNAME, DOPROCESS );
   E_COMMANDRETURN rtn = CMD_FAILURE;

   // Set Display Type
   
   try
   {
      if(!isXMLAPIContext())
         rtn = invokeCommand( this, CMD_GUI_ADDR_TAX_JURIS_UPDATE, getProcessType(),
                           isModal(), &_rpChildGI );
      else
         rtn = CMD_MODELESS_INPROCESS;
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
bool AddrTaxJurisUpdateProcess::doOk (GenericInterface* rpGICaller)
{
   setParameter( ADDRLIT::UPDATE_TAX_JURIS, m_dstrTaxJuris);
   setParameter( ADDRLIT::UPDATE_PROV_RES,  m_dstrProvRes );
   
   return true;
}
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastbp/AddrTaxJurisUpdateProcess.cpp-arc  $ */
// 
//    Rev 1.0   Oct 29 2008 21:14:12   wongsakw
// Initial revision.
