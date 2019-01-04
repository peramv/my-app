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
// ^FILE   : BrokerAddressProcess.cpp
// ^AUTHOR : Yingbao Li
// ^DATE   : March 30,2003
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : BrokerAddressProcess
//    This class manages the Branch information.
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include "stdafx.h"
#include "BrokerAddressProcess.hpp"
#include "BrokerAddressProcessincludes.h"
#include <ifastcbo\MFAccount.hpp>
#include <ifastcbo\BrokerList.hpp>
#include <ifastcbo\Broker.hpp>
#include <ifastcbo\NomineeInterAddrList.hpp>
#include <ifastcbo\NomineeInterAddr.hpp>
#include <ifastcbo\IntermediaryList.hpp>
#include <ifastcbo\Intermediary.hpp>
#include <ifastcbo\mgmtco.hpp>

#include <ifastcbo\DSTCWorkSession.hpp>





extern IFASTBP_LINKAGE const I_CHAR* CMD_GUI_BROKER_ADDRESS;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_BROKER_ADDRESS;
#include <bfproc\concreteprocesscreator.hpp>
static ConcreteProcessCreator< BrokerAddressProcess > processCreator( CMD_BPROC_BROKER_ADDRESS );

namespace
{
   // Trace literals
   const I_CHAR * const CLASSNAME = I_( "BrokerAddressProcess" );
}

namespace CND
{
   extern CLASS_IMPORT const long BP_ERR_UNKNOWN_EXCEPTION;
}

namespace ADDRLIT
{

	const I_CHAR * const AddrLine1 = I_("AddrLine1" );
	const I_CHAR * const AddrLine2 = I_("AddrLine2" );
	const I_CHAR * const AddrLine3 = I_("AddrLine3" );
	const I_CHAR * const AddrLine4 = I_("AddrLine4" );
	const I_CHAR * const AddrLine5 = I_("AddrLine5" );
	const I_CHAR * const CountryCode = I_("CountryCode" );
	const I_CHAR * const PostCode = I_("PostCode" );
		
}



//******************************************************************************
//              Public Methods
//******************************************************************************
BrokerAddressProcess::BrokerAddressProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: AbstractProcess( pGIC, pGIParent, rCommand )
, _rpChildGI( 0)
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );

   addContainer( IFASTBP_PROC::BROKER_ADDRESS_LIST, true );
   addSubstituteList(ifds::BrokerAddressHeadingSet);  

   addFieldDetails( ifds::BrokerCode,		IFASTBP_PROC::BROKER_ADDRESS_LIST );
   addFieldDetails( ifds::BrokerName,		IFASTBP_PROC::BROKER_ADDRESS_LIST );
   addFieldDetails( ifds::RegAddrCode,		IFASTBP_PROC::BROKER_ADDRESS_LIST );
   addFieldDetails( ifds::Addr11Line1,		IFASTBP_PROC::BROKER_ADDRESS_LIST );
   addFieldDetails( ifds::Addr11Line2,		IFASTBP_PROC::BROKER_ADDRESS_LIST );
   addFieldDetails( ifds::Addr11Line3,		IFASTBP_PROC::BROKER_ADDRESS_LIST );
   addFieldDetails( ifds::Addr11Line4,		IFASTBP_PROC::BROKER_ADDRESS_LIST );
   addFieldDetails( ifds::Addr11Line5,		IFASTBP_PROC::BROKER_ADDRESS_LIST );
   addFieldDetails( ifds::AddrCntryCode,	IFASTBP_PROC::BROKER_ADDRESS_LIST );
   addFieldDetails( ifds::PostalCode,		IFASTBP_PROC::BROKER_ADDRESS_LIST );
   addFieldDetails( ifds::TaxType,			IFASTBP_PROC::BROKER_ADDRESS_LIST );
  

}

//******************************************************************************
BrokerAddressProcess::~BrokerAddressProcess()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************
SEVERITY BrokerAddressProcess::doInit()
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTBP_CONDITION, CLASSNAME, DOINIT );
   SEVERITY sevRtn = SEVERE_ERROR;
   BFDataGroupId lDataGroupID = getDataGroupId();

   try
   {
		DString dstrAccountNum;

      getParameter( ADDRLIT::ACCOUNT_NUM, dstrAccountNum );
      if( dstrAccountNum.strip().stripLeading( '0' ) != NULL_STRING )
      {

         DSTCWorkSession *dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
			if( dstrAccountNum != NULL_STRING )
			{
				MFAccount* pMFAccount = NULL;
				DString dstrAcctDesignation;
				if( dstcWorkSession->getMFAccount( lDataGroupID, dstrAccountNum, pMFAccount ) <= WARNING )
				{
					pMFAccount->getField( ifds::AcctDesignation, dstrAcctDesignation, lDataGroupID, false );
					dstrAcctDesignation.strip();
					if(dstrAcctDesignation == I_("2") ) //broker
					{
						BrokerList* pBrokerList;
						dstcWorkSession->getBrokerList(pBrokerList);
						if( pBrokerList )
						{
							DString dstrBrokerCode;
							pMFAccount->getField(ifds::BrokerCode,	dstrBrokerCode,lDataGroupID,false );
							dstrBrokerCode.strip();
							Broker*  pBroker;
							pBrokerList->getBroker(dstrBrokerCode, pBroker);
							if(pBroker )
							{
								NomineeInterAddrList* pNomineeInterAddrList = NULL;
								pBroker->getNomineeInterAddressList( lDataGroupID, pNomineeInterAddrList);
								setContainer( IFASTBP_PROC::BROKER_ADDRESS_LIST, pNomineeInterAddrList );
							}						
						}				
					}
					else if(dstrAcctDesignation == I_("3") )  //Nominee
					{		
						MgmtCo& mMgmtco = dstcWorkSession->getMgmtCo();
						IntermediaryList* pIntermediaryList;
						mMgmtco.getIntermediaryList( pIntermediaryList );
						if(pIntermediaryList )
						{
							DString dstrInterCode;
							pMFAccount->getField(ifds::InterCode,	dstrInterCode,lDataGroupID,false );
							dstrInterCode.strip();
							Intermediary* pIntermediary;
							pIntermediaryList->getIntermediary(lDataGroupID,dstrInterCode,pIntermediary );
							if( pIntermediary )
							{
									NomineeInterAddrList* pNomineeInterAddrList = NULL;
									if(pIntermediary->getNomineeInterAddressList(lDataGroupID,pNomineeInterAddrList ) <= WARNING )
									{
									  setContainer( IFASTBP_PROC::BROKER_ADDRESS_LIST, pNomineeInterAddrList );										
									}										
							}
						}
					}
					else
					{
						assert(0); // AcctDesignation has to be 2 or 3
					}			
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

E_COMMANDRETURN BrokerAddressProcess::doProcess()
{  
   MAKEFRAME2( CND::BPBASE_CONDITION, CLASSNAME, DOPROCESS );
   E_COMMANDRETURN rtn = CMD_FAILURE;

   try
   {
      rtn = invokeCommand( this, CMD_GUI_BROKER_ADDRESS, getProcessType(), isModal(), &_rpChildGI );
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

bool BrokerAddressProcess::doModelessChildComplete( const Command &cmd )
{
   // End when GUI ends
   return( cmd.getKey() == CMD_GUI_BROKER_ADDRESS );
}

//******************************************************************************

void BrokerAddressProcess::doPostOk( GenericInterface *rpGICaller, bool bSuccessFlag )
{
   if( bSuccessFlag )
   {
      DString dstrValue;

      getField( rpGICaller,IFASTBP_PROC::BROKER_ADDRESS_LIST, ifds::RegAddrCode, dstrValue );
      setParameter( ADDRLIT::ADDRESS_CODE, dstrValue );

      getField( rpGICaller,IFASTBP_PROC::BROKER_ADDRESS_LIST, ifds::Addr11Line1, dstrValue );
      setParameter( ADDRLIT::AddrLine1, dstrValue );
      getField( rpGICaller,IFASTBP_PROC::BROKER_ADDRESS_LIST, ifds::Addr11Line2, dstrValue );
      setParameter( ADDRLIT::AddrLine2, dstrValue );
      getField( rpGICaller,IFASTBP_PROC::BROKER_ADDRESS_LIST, ifds::Addr11Line3, dstrValue );
      setParameter( ADDRLIT::AddrLine3, dstrValue );
      getField( rpGICaller,IFASTBP_PROC::BROKER_ADDRESS_LIST, ifds::Addr11Line4, dstrValue );
      setParameter( ADDRLIT::AddrLine4, dstrValue );
      getField( rpGICaller,IFASTBP_PROC::BROKER_ADDRESS_LIST, ifds::Addr11Line5, dstrValue );
      setParameter( ADDRLIT::AddrLine5, dstrValue );

      getField( rpGICaller,IFASTBP_PROC::BROKER_ADDRESS_LIST, ifds::AddrCntryCode, dstrValue );
      setParameter( ADDRLIT::CountryCode, dstrValue );
      getField( rpGICaller,IFASTBP_PROC::BROKER_ADDRESS_LIST, ifds::PostalCode, dstrValue );
      setParameter( ADDRLIT::PostCode, dstrValue );



   }
}


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/BrokerAddressProcess.cpp-arc  $
// 
//    Rev 1.3   Jan 12 2004 13:02:16   YINGBAOL
// PTS10021623---Let user choose address from broker address screen Work has not been saved in previous version
// 
//    Rev 1.1   Apr 03 2003 15:45:48   YINGBAOL
// put TaxType in
// 
//    Rev 1.0   Apr 03 2003 09:36:08   YINGBAOL
// Initial revision.
 * 

*/
