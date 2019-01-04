//*****************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by International Financial Data Services
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2005 by International Financial Data Services
//
//*****************************************************************************
//
//    ^FILE   : OPCConfirmReprint.cpp
//    ^AUTHOR : Monica Porteanu
//    ^DATE   : May, 2005
//    Copyright 2005 by International Financial Data Services
//
//-----------------------------------------------------------------------------
//
// ^CLASS  : OPCConfirmReprint
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS :
//
//*****************************************************************************
#include "stdafx.h"

#include "OPCConfirmReprint.hpp"
#include "broker.hpp"
#include "brokerlist.hpp"
#include "mfaccount.hpp"

// Fields that are not part of the included views
namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId OPCConfirmReprint;
   extern CLASS_IMPORT const BFTextFieldId OPCNewConfirmReprint;
   extern CLASS_IMPORT const BFTextFieldId OPCExistingConfirmReprint;  
}

namespace CND
{  // Conditions used   
	extern const long ERR_TRANS_REPRINT_ALL_COPIES_INACTIVE;	
}

// Constants
namespace 
{
   const I_CHAR * CLASSNAME = I_("OPCConfirmReprint");
}

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = {
    //  Field DD Id,          State Flags, Group Flags 
    {ifds::OPCConfirmReprint, BFCBO::NONE, 0 }, 	
    {ifds::ClientCopy,        BFCBO::NONE, 0 }, 	
	{ifds::BrokerCopy,        BFCBO::NONE, 0 }, 	
	{ifds::SalesRepCopy,      BFCBO::NONE, 0 }, 	
	{ifds::SchedReprintDate,  BFCBO::NONE, 0 }, 	
	{ifds::RequestedBy,       BFCBO::NONE, 0 }, 	
};


static const int NUM_FIELDS = sizeof(classFieldInfo) / sizeof(BFCBO::CLASS_FIELD_INFO);
//******************************************************************************
OPCConfirmReprint::OPCConfirmReprint(BFAbstractCBO &parent) 
: ConfirmReprint(parent)
{
   TRACE_CONSTRUCTOR(CLASSNAME , NULL_STRING);

   registerMemberData( NUM_FIELDS,
                       (const CLASS_FIELD_INFO *)&classFieldInfo,
                       0,
                       NULL);     
}

//******************************************************************************
OPCConfirmReprint::~OPCConfirmReprint()
{
   TRACE_DESTRUCTOR(CLASSNAME);
}

//******************************************************************************
void OPCConfirmReprint::reprintReset (const BFDataGroupId &idDataGroup )
{
   DString dstrCurrentOPCConfirmReprint;
   getField( ifds::OPCConfirmReprint, dstrCurrentOPCConfirmReprint, idDataGroup );
   dstrCurrentOPCConfirmReprint.strip().upperCase();

   if( I_( "A" ) == dstrCurrentOPCConfirmReprint )
   {	   
	   initNew ( getTransId(), getAccountNum(), idDataGroup );
   }
   else
   {
		DString dstrOPCConfirmReprint,
			    dstrClientCopy, 
			    dstrBrokerCopy, 
				dstrSalesRepCopy;
		dstrOPCConfirmReprint = getRunMode();
		getFieldBeforeImage( ifds::ClientCopy,   dstrClientCopy );
		getFieldBeforeImage( ifds::BrokerCopy,   dstrBrokerCopy );
		getFieldBeforeImage( ifds::SalesRepCopy, dstrSalesRepCopy );

		setFieldNoValidate( ifds::OPCConfirmReprint, dstrOPCConfirmReprint, idDataGroup );
		setFieldNoValidate( ifds::ClientCopy,        dstrClientCopy,        idDataGroup );
		setFieldNoValidate( ifds::BrokerCopy,        dstrBrokerCopy,        idDataGroup );
		setFieldNoValidate( ifds::SalesRepCopy,      dstrSalesRepCopy,      idDataGroup );

		setExistingRecord( idDataGroup );
   }
}

//******************************************************************************
SEVERITY OPCConfirmReprint::doApplyRelatedChanges( const BFFieldId &idField, 
												   const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("doApplyRelatedChanges"));

   if ( ifds::OPCConfirmReprint == idField )
   {
	    bool bReadOnly = false;

		DString dstrOPCConfirmReprint;
		getField( ifds::OPCConfirmReprint, dstrOPCConfirmReprint, idDataGroup );

		if ( I_( "D" ) ==  dstrOPCConfirmReprint.strip() )
		{			
			setRunMode( I_( "D" ) );
			setUpdatedFlag( ifds::ClientCopy, idDataGroup, true ); 
			bReadOnly = true;
			
		}
		else if ( I_( "M" ) ==  dstrOPCConfirmReprint.strip() )
		{
			setRunMode( I_( "M" ) );
			bReadOnly = false;
		}

		setFieldReadOnly( ifds::ClientCopy,   idDataGroup, bReadOnly );
		setFieldReadOnly( ifds::BrokerCopy,   idDataGroup, bReadOnly );
		setFieldReadOnly( ifds::SalesRepCopy, idDataGroup, bReadOnly );
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY OPCConfirmReprint::doValidateAll( const BFDataGroupId& idDataGroup, long lValidateGroup ) 
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doValidateAll" ) );

   DString dstrOPCConfirmReprint, dstrClientCopy, dstrBrokerCopy, dstrSalesRepCopy;
   getField( ifds::OPCConfirmReprint, dstrOPCConfirmReprint, idDataGroup );
   getField( ifds::ClientCopy,        dstrClientCopy,        idDataGroup );
   getField( ifds::BrokerCopy,        dstrBrokerCopy,        idDataGroup );
   getField( ifds::SalesRepCopy,      dstrSalesRepCopy,      idDataGroup );

   if ( I_( "D" ) != dstrOPCConfirmReprint.strip().upperCase() &&
	    I_( "N" ) == dstrClientCopy.strip().upperCase() &&
	    I_( "N" ) == dstrBrokerCopy.strip().upperCase() &&
		I_( "N" ) == dstrSalesRepCopy.strip().upperCase() )
   {
		// At least one copy must be setup for Reprint
        ADDCONDITIONFROMFILE( CND::ERR_TRANS_REPRINT_ALL_COPIES_INACTIVE );
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY OPCConfirmReprint::setExistingRecord( const BFDataGroupId &idDataGroup )
{
	MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("setExistingRecord") );
	
	setFieldAllSubstituteValues ( ifds::OPCConfirmReprint, 
                                  idDataGroup, 
                                  ifds::OPCExistingConfirmReprint );		

	setFieldNoValidate( ifds::OPCConfirmReprint, I_( "M" ), idDataGroup );
    
	setAcctRelatedParameters( idDataGroup );

	DString dstrDefaultClientCopy, dstrDefaultBrokerCopy, dstrDefaultSalesRepCopy;
	getCopyParameters( idDataGroup,
					   dstrDefaultClientCopy,
					   dstrDefaultBrokerCopy,
					   dstrDefaultSalesRepCopy );

	dstrDefaultClientCopy.strip().upperCase();
	dstrDefaultBrokerCopy.strip().upperCase();
	dstrDefaultSalesRepCopy.strip().upperCase();

	setFieldReadOnly( ifds::ClientCopy,   idDataGroup, dstrDefaultClientCopy   == I_( "N" ) );
	setFieldReadOnly( ifds::BrokerCopy,   idDataGroup, dstrDefaultBrokerCopy   == I_( "N" )  );
	setFieldReadOnly( ifds::SalesRepCopy, idDataGroup, dstrDefaultSalesRepCopy == I_( "N" ) );

	return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY OPCConfirmReprint::setNewRecord( const BFDataGroupId &idDataGroup )
{
	MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("setExistingRecord") );
	
	setFieldAllSubstituteValues ( ifds::OPCConfirmReprint, 
                                  idDataGroup, 
                                  ifds::OPCExistingConfirmReprint );		

	setFieldAllSubstituteValues ( ifds::OPCConfirmReprint, 
                                  idDataGroup, 
                                  ifds::OPCNewConfirmReprint );			

	setFieldNoValidate( ifds::OPCConfirmReprint, I_( "A" ), idDataGroup );

	setAcctRelatedParameters( idDataGroup );
	DString dstrDefaultClientCopy, dstrDefaultBrokerCopy, dstrDefaultSalesRepCopy;
	getCopyParameters( idDataGroup,
					   dstrDefaultClientCopy,
					   dstrDefaultBrokerCopy,
					   dstrDefaultSalesRepCopy );

	dstrDefaultClientCopy.strip().upperCase();
	dstrDefaultBrokerCopy.strip().upperCase();
	dstrDefaultSalesRepCopy.strip().upperCase();

	setFieldReadOnly( ifds::ClientCopy,   idDataGroup, I_( "N" ) == dstrDefaultClientCopy );
	setFieldReadOnly( ifds::BrokerCopy,   idDataGroup, I_( "N" ) == dstrDefaultBrokerCopy );
	setFieldReadOnly( ifds::SalesRepCopy, idDataGroup, I_( "N" ) == dstrDefaultSalesRepCopy );
	
	setFieldNoValidate( ifds::ClientCopy,    dstrDefaultClientCopy,   idDataGroup );
	setFieldNoValidate( ifds::BrokerCopy,    dstrDefaultBrokerCopy,   idDataGroup );
	setFieldNoValidate( ifds::SalesRepCopy,  dstrDefaultSalesRepCopy, idDataGroup );

	if ( I_( "Y" ) == dstrDefaultClientCopy )
		setUpdatedFlag( ifds::ClientCopy, idDataGroup, true ); 
	if ( I_( "Y" ) == dstrDefaultBrokerCopy )
		setUpdatedFlag( ifds::BrokerCopy, idDataGroup, true ); 
	if ( I_( "Y" ) == dstrDefaultSalesRepCopy )
		setUpdatedFlag( ifds::SalesRepCopy, idDataGroup, true ); 

	return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY OPCConfirmReprint::setAcctRelatedParameters( const BFDataGroupId &idDataGroup )
{
	MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("setAcctRelatedParameters") );

	DString dstrAccountNum = getAccountNum();
	MFAccount *pMFAccount = NULL;
    if ( getWorkSession().getMFAccount ( idDataGroup, 
		                                 dstrAccountNum, 
										 pMFAccount, 
										 I_("N"), 
										 NULL_STRING, true, true ) <= WARNING &&
		 NULL != pMFAccount )
	{		
		pMFAccount->getField( ifds::AcctDesignation, _dstrAcctDesignation, idDataGroup );	
		pMFAccount->getField( ifds::BrokerCode,      _dstrAcctBroker,      idDataGroup );			
	}

	return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY OPCConfirmReprint::getCopyParameters( const BFDataGroupId &idDataGroup,
											   DString &dstrDefaultClientCopy,
											   DString &dstrDefaultBrokerCopy,
											   DString &dstrDefaultSalesRepCopy )
{
	MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("getClientCopyParameters") );

	BrokerList *pBrokerList = NULL;		
	if ( getWorkSession().getBrokerList( pBrokerList ) <= WARNING &&
	 	 NULL != pBrokerList )
	{
		Broker *pBroker = NULL;
		if ( pBrokerList->getBroker( _dstrAcctBroker, pBroker ) <= WARNING &&
		 	 NULL != pBroker )
		{				
			if ( I_( "1" ) == _dstrAcctDesignation ||         // Client Account 
				 I_( "9" ) == _dstrAcctDesignation )          // TP Managed or else
			{
				pBroker->getField( ifds::ConfClientCli, dstrDefaultClientCopy,   idDataGroup );
				pBroker->getField( ifds::ConfBrkCli,    dstrDefaultBrokerCopy,   idDataGroup );
				pBroker->getField( ifds::ConfRepCli,    dstrDefaultSalesRepCopy, idDataGroup );
			}			
			else if ( I_( "2" ) == _dstrAcctDesignation )     // Nominee Account
			{
				pBroker->getField( ifds::ConfClientNom, dstrDefaultClientCopy,   idDataGroup );
				pBroker->getField( ifds::ConfBrkNom,    dstrDefaultBrokerCopy,   idDataGroup );
				pBroker->getField( ifds::ConfRepNom,    dstrDefaultSalesRepCopy, idDataGroup );
			}			
			else if ( I_( "3" ) == _dstrAcctDesignation )     // Intermediary Account
			{
				pBroker->getField( ifds::ConfClientOth, dstrDefaultClientCopy,   idDataGroup );
				pBroker->getField( ifds::ConfBrkOth,    dstrDefaultBrokerCopy,   idDataGroup );
				pBroker->getField( ifds::ConfRepOth,    dstrDefaultSalesRepCopy, idDataGroup );
			}			
			else      // Not applicable for now
			{ 
				dstrDefaultClientCopy   = I_( "N" );
                dstrDefaultBrokerCopy   = I_( "N" );
				dstrDefaultSalesRepCopy = I_( "N" );
			}
		}
	}

	return GETCURRENTHIGHESTSEVERITY();
}


//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastcbo/OPCConfirmReprint.cpp-arc  $
// 
//    Rev 1.6   May 31 2005 15:54:30   porteanm
// PET OPC Confirm Reprint - Commit and Reset.
// 
//    Rev 1.5   May 26 2005 17:56:40   porteanm
// PET OPC Confirm Reprint - Cleanup.
// 
//    Rev 1.4   May 26 2005 17:22:24   porteanm
// PET OPC Confirm Reprint - Setting fields properties.
// 
//    Rev 1.3   May 26 2005 10:25:18   porteanm
// PET OPC Confirm Reprint - Setting fields properties.
// 
//    Rev 1.2   May 25 2005 15:01:46   porteanm
// PET OPC Confirm Reprint - Commit and Reset.
// 
//    Rev 1.1   May 24 2005 12:38:08   porteanm
// PET OPC Confirm Reprint - Renamed OPC files. Changed class hierarchy.
// 



