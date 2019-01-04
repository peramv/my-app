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
//    Copyright 2005 by International Financial Data Services
//
//
//******************************************************************************
//
// ^FILE   : BulkCancel.cpp
// ^AUTHOR : Monica Porteanu
// ^DATE   : November 2005
//
// ^CLASS    : BulkCancel
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "bulkcancel.hpp"

#include "dstcommonfunction.hpp"
#include "dilutionalloclist.hpp"
#include "dilutionalloc.hpp"

#include "mgmtco.hpp"

#include <ifastdataimpl\dse_dstc0337_req.hpp>
#include <ifastdataimpl\dse_dstc0337_vw.hpp>
#include <ifastdataimpl\dse_dstc0127_req.hpp>
#include <ifastdataimpl\dse_dstc0127_vw.hpp>

namespace  
{
   const I_CHAR * const CLASSNAME    = I_( "BulkCancel");  
   
   const I_CHAR * const UNVERIFIED	                    = I_("01");
   const I_CHAR * const VERIFIED	                    = I_("02");
   const I_CHAR * const DELETED		                    = I_("03");
   // Statutes for Bulk Cancellation
   const I_CHAR * const CANCEL_UNVERIFIED		        = I_("04");
   const I_CHAR * const CANCEL_VERIFIED		            = I_("05");
   const I_CHAR * const CANCELLATION_PROCEEDING		    = I_("06");
   const I_CHAR * const CANCELLATION_DONE		        = I_("07");
   const I_CHAR * const REBOOK_UNVERIFIED		        = I_("08");
   const I_CHAR * const REBOOK_VERIFIED		            = I_("09");
   const I_CHAR * const REBOOK_PROCEEDING		        = I_("10");
   const I_CHAR * const REBOOK_PENDING_TRADE_UNVERIFIED = I_("11");
   const I_CHAR * const REBOOK_PENDING_TRADE_VERIFIED	= I_("12");
   const I_CHAR * const REBOOK_DONE		                = I_("13");
   const I_CHAR * const ALL		                        = I_("All");

   const I_CHAR * const YES	 = I_("Y");
   const I_CHAR * const NO	 = I_("N");
	
   const I_CHAR * const SUPPRESS_INDICATOR_DEFAULT_CODE	= I_("2");
}

namespace ifds
{
	extern CLASS_IMPORT const BFTextFieldId MCHBulkCancel;
	extern CLASS_IMPORT const BFTextFieldId SRBulkCancel; 
	extern CLASS_IMPORT const BFTextFieldId MCHBulkRbk;
	extern CLASS_IMPORT const BFTextFieldId SRBulkRbk; 
	extern CLASS_IMPORT const BFTextFieldId MCHSRActive;
}

namespace UAF
{
	extern CLASS_IMPORT I_CHAR * const VERIFY_CANCEL_INSTRUCTION;
	extern CLASS_IMPORT I_CHAR * const MCH_AND_SECUR_REC_FILE_INDICATOR;
}

//*********************************************************************************
const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = {
   //Field DD Id,      State Flags,   Group Flags      
   { ifds::TransNum,	            BFCBO::NONE,	 0 },  
   { ifds::TranStatus,              BFCBO::NONE,     0 },       
   { ifds::Rebook,                  BFCBO::NONE,     0 },   
   { ifds::TradeDate,               BFCBO::REQUIRED, 0 }, 
   { ifds::Fund,                    BFCBO::REQUIRED, 0 }, 
   { ifds::Class,                   BFCBO::REQUIRED, 0 },    
   { ifds::Accountable,	            BFCBO::NONE,	 0 },      
   { ifds::RvCode,		            BFCBO::REQUIRED, 0 },   
   { ifds::OnStmt,		            BFCBO::REQUIRED, 0 },      
   { ifds::ConfirmRequired,         BFCBO::REQUIRED, 0 },   
   { ifds::CancelCheque,            BFCBO::REQUIRED, 0 },   
   { ifds::Remarks1,                BFCBO::NONE,	 0 },
   { ifds::Remarks2,	            BFCBO::NONE,	 0 },
   { ifds::Remarks3,	            BFCBO::NONE,	 0 },
   { ifds::ModPermission,	        BFCBO::NONE,	 0 },
   { ifds::Version,			        BFCBO::NONE,	 0 },
   { ifds::TransType,               BFCBO::NONE,     0 },
   { ifds::TransId,                 BFCBO::NONE,     0 },
   { ifds::Batch,                   BFCBO::NONE,     0 }, 
   { ifds::Trace,                   BFCBO::NONE,     0 },    
   { ifds::CancellationType,        BFCBO::NONE,     0 },
   { ifds::MCHFileIndicator,		BFCBO::NONE,     0 },  
   { ifds::SecRecFileIndicator,	    BFCBO::NONE,     0 },
   { ifds::RbkMCHFileIndicator,		BFCBO::NONE,     0 },
   { ifds::RbkSecRecFileIndicator,	BFCBO::NONE,     0 },
};

static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );

//*********************************************************************************
BulkCancel::BulkCancel( BFAbstractCBO &parent ) : TransCancel( parent )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );   
   registerMemberData( NUM_FIELDS,
                       (const CLASS_FIELD_INFO *)&classFieldInfo,
                       0, NULL );   
}

//******************************************************************************************
SEVERITY BulkCancel::init( const BFData& data )

{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init(BFData&)" ) );  

   attachDataObject (const_cast<BFData&>(data), false);    

   DString transNum = data.getElementValue( ifds::TransNum );   
   transNum.strip ();
   commonInit( BF::HOST,
               transNum );   

   return GETCURRENTHIGHESTSEVERITY();
}

//*********************************************************************************
BulkCancel::~BulkCancel()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************
SEVERITY BulkCancel::restore( const BFDataGroupId &idDataGroup )
{
	MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                            CLASSNAME, 
                            I_( "refresh" ) );	
      
   DString dstrBefAccountable,
		dstrBefRvCode,
		dstrBefOnStmt,
		dstrBefConfirmRequired,
		dstrBefCancelCheque,
		dstrBefRemarks1,
		dstrBefRemarks2,
		dstrBefRemarks3,
		dstrBefTransStat,
		dstrBefRebook,
		dstrMCHFileIndicator,
		dstrSecRecFileIndicator,
		dstrRbkMCHFileIndicator,
		dstrRbkSecRecFileIndicator;

   getFieldBeforeImage( ifds::Accountable,              dstrBefAccountable );       
   getFieldBeforeImage( ifds::RvCode,                   dstrBefRvCode );       
   getFieldBeforeImage( ifds::OnStmt,                   dstrBefOnStmt );       
   getFieldBeforeImage( ifds::ConfirmRequired,          dstrBefConfirmRequired );       
   getFieldBeforeImage( ifds::CancelCheque,             dstrBefCancelCheque );       
   getFieldBeforeImage( ifds::Remarks1,                 dstrBefRemarks1 );       
   getFieldBeforeImage( ifds::Remarks2,                 dstrBefRemarks2 );       
   getFieldBeforeImage( ifds::Remarks3,                 dstrBefRemarks3 );       
   getFieldBeforeImage( ifds::TranStatus,               dstrBefTransStat ); 
   getFieldBeforeImage( ifds::Rebook,                   dstrBefRebook );      
   getFieldBeforeImage( ifds::MCHFileIndicator,			dstrMCHFileIndicator );
   getFieldBeforeImage( ifds::SecRecFileIndicator,		dstrSecRecFileIndicator );
   getFieldBeforeImage( ifds::RbkMCHFileIndicator,		dstrRbkMCHFileIndicator );
   getFieldBeforeImage( ifds::RbkSecRecFileIndicator,	dstrRbkSecRecFileIndicator );   

   setFieldNoValidate( ifds::Accountable,               dstrBefAccountable,         idDataGroup );
   setFieldNoValidate( ifds::RvCode,                    dstrBefRvCode,              idDataGroup );
   setFieldNoValidate( ifds::OnStmt,                    dstrBefOnStmt,              idDataGroup );
   setFieldNoValidate( ifds::ConfirmRequired,           dstrBefConfirmRequired,     idDataGroup );
   setFieldNoValidate( ifds::CancelCheque,              dstrBefCancelCheque,        idDataGroup );
   setFieldNoValidate( ifds::Remarks1,                  dstrBefRemarks1,            idDataGroup );
   setFieldNoValidate( ifds::Remarks2,                  dstrBefRemarks2,            idDataGroup );
   setFieldNoValidate( ifds::Remarks3,                  dstrBefRemarks3,            idDataGroup );
   setFieldNoValidate( ifds::TranStatus,                dstrBefTransStat,           idDataGroup );
   setFieldNoValidate( ifds::Rebook,                    dstrBefRebook,              idDataGroup );
   setFieldNoValidate( ifds::MCHFileIndicator,			dstrMCHFileIndicator,		idDataGroup );
   setFieldNoValidate( ifds::SecRecFileIndicator,		dstrSecRecFileIndicator,	idDataGroup );    
   setFieldNoValidate( ifds::RbkMCHFileIndicator,		dstrRbkMCHFileIndicator,	idDataGroup );
   setFieldNoValidate( ifds::RbkSecRecFileIndicator,	dstrRbkSecRecFileIndicator,	idDataGroup ); 
	
   setSuppressIndicatorsSet(idDataGroup);
   setSuppressIndicatorsReadOnlyFlags(idDataGroup);

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY BulkCancel::getDilutionAllocList ( const BFDataGroupId &idDataGroup, 
										    DilutionAllocList *&pDilutionAllocList )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("getDilutionAllocList"));
   
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY BulkCancel::getBatchNum ( const BFDataGroupId &idDataGroup,
                                   const DString &track /*= I_("N")*/,
                                   const DString &pageName /*= NULL_STRING*/)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_( "getBatchNum" ) );
   //init batch by call view 127 so that a batch is created if AutoBatch is turned on in the environment.
   TransCancel::getBatchNum(idDataGroup);
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY BulkCancel::setNewTransStatus( const BFDataGroupId &idDataGroup )
{
	MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                            CLASSNAME, 
                            I_( "setTransStatus" ) );

	setFieldNoValidate (ifds::TranStatus, CANCEL_UNVERIFIED, idDataGroup, false, false, true);	

	return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY BulkCancel::setTransNum( const BFDataGroupId &idDataGroup )
{
	MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                            CLASSNAME, 
                            I_( "setTransNum" ) );	
	
	return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
bool BulkCancel::isModifiableBasedOnStatus( const BFDataGroupId &idDataGroup )
{
	MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("isModifiableBasedOnStatus"));

	bool bModifiable = false;

   DString dstrTranStatus;
	getField (ifds::TranStatus, dstrTranStatus, idDataGroup, false );

	if( dstrTranStatus == CANCEL_UNVERIFIED ||     
		dstrTranStatus == CANCEL_VERIFIED )
		bModifiable = true;

	return bModifiable;
}

//******************************************************************************
bool BulkCancel::isIndividualTransCancelAllowed()
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "isIndividualTransCancelAllowed" ) );	

	// If we are here already, the BULK_CANCELLATION function has already been checked
	return true;
}

//******************************************************************************
SEVERITY BulkCancel::setDefaultSuppressIndicators( const BFDataGroupId &idDataGroup )
{
	MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                            CLASSNAME, 
                            I_( "setDefaultSuppressIndicators" ) );

	DString dstrMCHBulkCancel, dstrSRBulkCancel, dstrMCHBulkRbk, dstrSRBulkRbk;

	getWorkSession().getOption ( ifds::MCHBulkCancel, dstrMCHBulkCancel, BF::HOST, false);
	getWorkSession().getOption ( ifds::SRBulkCancel, dstrSRBulkCancel, BF::HOST, false);
	getWorkSession().getOption ( ifds::MCHBulkRbk, dstrMCHBulkRbk, BF::HOST, false);
	getWorkSession().getOption ( ifds::SRBulkRbk, dstrSRBulkRbk, BF::HOST, false);

	setFieldNoValidate( ifds::MCHFileIndicator,		dstrMCHBulkCancel,	idDataGroup, false, true, false, false);
	setFieldNoValidate( ifds::SecRecFileIndicator,	dstrSRBulkCancel,		idDataGroup, false, true, false, false);
	setFieldNoValidate( ifds::RbkMCHFileIndicator,		dstrMCHBulkRbk,		idDataGroup, false, true, false, false);
	setFieldNoValidate( ifds::RbkSecRecFileIndicator,	dstrSRBulkRbk,			idDataGroup, false, true, false, false);
	
	setFieldReadOnly( ifds::RbkMCHFileIndicator,	idDataGroup, true );
	setFieldReadOnly( ifds::RbkSecRecFileIndicator,	idDataGroup, true );

	return GETCURRENTHIGHESTSEVERITY();

}

//******************************************************************************
bool BulkCancel::areSuppressIndicatorsModifiableBasedOnStatus( const BFDataGroupId &idDataGroup )
{
	MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("isModifiableBasedOnStatus"));

	bool bSuppressIndicatorsModifiable = false;

   DString dstrTranStatus;
	getField (ifds::TranStatus, dstrTranStatus, idDataGroup, false );
	dstrTranStatus.stripAll();

	if( dstrTranStatus == CANCEL_UNVERIFIED ||     
		dstrTranStatus == CANCEL_VERIFIED )

		bSuppressIndicatorsModifiable = true;

	return bSuppressIndicatorsModifiable;
}

//******************************************************************************
SEVERITY BulkCancel::doApplyRelatedChanges ( const BFFieldId &idField, 
                                              const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("doApplyRelatedChanges"));

	TransCancel::doApplyRelatedChanges(idField,idDataGroup);

	if ( idField == ifds::Rebook)
	{
		bool bReadOnly = true;

		DString dstrRebook;
		getField (ifds::Rebook, dstrRebook, idDataGroup, false);
		dstrRebook.stripAll().upperCase();
		
		DString dstrMCHSRActive;
	
		getWorkSession().getOption ( ifds::MCHSRActive, dstrMCHSRActive, BF::HOST, false);
		dstrMCHSRActive.stripAll().upperCase();
		
		if (getWorkSession ().hasUpdatePermission(UAF::MCH_AND_SECUR_REC_FILE_INDICATOR) && (dstrMCHSRActive == YES))
		{
			DString dstrMCHBulkRbk, dstrSRBulkRbk;
				
			getWorkSession().getOption ( ifds::MCHBulkRbk, dstrMCHBulkRbk, BF::HOST, false);
			getWorkSession().getOption ( ifds::SRBulkRbk, dstrSRBulkRbk, BF::HOST, false);
			dstrMCHBulkRbk.stripAll();
			dstrSRBulkRbk.stripAll();

			setFieldNoValidate( ifds::RbkMCHFileIndicator,		dstrMCHBulkRbk,	idDataGroup, false, true, false, false);
			setFieldNoValidate( ifds::RbkSecRecFileIndicator,	dstrSRBulkRbk,		idDataGroup, false, true, false, false);

			if (dstrRebook == YES)
			{				                				
				bReadOnly = false;								
			}
			else
			{	
				if (isNew())
				{
					setSuppressIndicatorsPerm(idDataGroup);					
				}				               	
			}

			setRbkSuppressIndicatorsSet(idDataGroup);
		}		

		setFieldReadOnly( ifds::RbkMCHFileIndicator,	idDataGroup, bReadOnly );
		setFieldReadOnly( ifds::RbkSecRecFileIndicator,	idDataGroup, bReadOnly );
	}

	return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY BulkCancel::setSuppressIndicatorsSet(const BFDataGroupId &idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                            CLASSNAME, 
                            I_( "setSuppressIndicatorsSet" ) );	

	BFProperties *pBFProperties;
	DString dstrSuppressIndicatorSubst;

	pBFProperties = getFieldProperties (ifds::MCHFileIndicator, idDataGroup);
   pBFProperties->getAllSubstituteValues (dstrSuppressIndicatorSubst);
	dstrSuppressIndicatorSubst = removeItemFromSubtList( dstrSuppressIndicatorSubst, SUPPRESS_INDICATOR_DEFAULT_CODE );   
	setFieldAllSubstituteValues( ifds::MCHFileIndicator, 
											idDataGroup, 
											dstrSuppressIndicatorSubst );

	pBFProperties = getFieldProperties (ifds::SecRecFileIndicator, idDataGroup);
   pBFProperties->getAllSubstituteValues (dstrSuppressIndicatorSubst);
	dstrSuppressIndicatorSubst = removeItemFromSubtList( dstrSuppressIndicatorSubst, SUPPRESS_INDICATOR_DEFAULT_CODE );   
	setFieldAllSubstituteValues( ifds::SecRecFileIndicator, 
											idDataGroup, 
											dstrSuppressIndicatorSubst );

	setRbkSuppressIndicatorsSet(idDataGroup);

	return GETCURRENTHIGHESTSEVERITY();

}

//******************************************************************************
SEVERITY BulkCancel::setRbkSuppressIndicatorsSet(const BFDataGroupId &idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                            CLASSNAME, 
                            I_( "setSuppressIndicatorsSet" ) );	

	BFProperties *pBFProperties;
	DString dstrSuppressIndicatorSubst;

	pBFProperties = getFieldProperties (ifds::RbkMCHFileIndicator, idDataGroup);
   pBFProperties->getAllSubstituteValues (dstrSuppressIndicatorSubst);
	dstrSuppressIndicatorSubst = removeItemFromSubtList( dstrSuppressIndicatorSubst, SUPPRESS_INDICATOR_DEFAULT_CODE );   
	setFieldAllSubstituteValues( ifds::RbkMCHFileIndicator, 
											idDataGroup, 
											dstrSuppressIndicatorSubst );

	pBFProperties = getFieldProperties (ifds::RbkSecRecFileIndicator, idDataGroup);
   pBFProperties->getAllSubstituteValues (dstrSuppressIndicatorSubst);
	dstrSuppressIndicatorSubst = removeItemFromSubtList( dstrSuppressIndicatorSubst, SUPPRESS_INDICATOR_DEFAULT_CODE );   
	setFieldAllSubstituteValues( ifds::RbkSecRecFileIndicator, 
											idDataGroup, 
											dstrSuppressIndicatorSubst );

	return GETCURRENTHIGHESTSEVERITY();

}

//******************************************************************************
SEVERITY BulkCancel::setSuppressIndicatorsInactive(const BFDataGroupId &idDataGroup, const bool isNew)
{
	MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                            CLASSNAME, 
                            I_( "setSuppressIndicatorsInactive" ) );	

	if (isNew)
	{
		setFieldNoValidate( ifds::MCHFileIndicator,			SUPPRESS_INDICATOR_DEFAULT_CODE,	idDataGroup, false, true, false, true);
		setFieldNoValidate( ifds::SecRecFileIndicator,		SUPPRESS_INDICATOR_DEFAULT_CODE,	idDataGroup, false, true, false, true);
		setFieldNoValidate( ifds::RbkMCHFileIndicator,		SUPPRESS_INDICATOR_DEFAULT_CODE,	idDataGroup, false, true, false, true);
		setFieldNoValidate( ifds::RbkSecRecFileIndicator,	SUPPRESS_INDICATOR_DEFAULT_CODE,	idDataGroup, false, true, false, true);
	
	}

	setFieldReadOnly( ifds::MCHFileIndicator,			idDataGroup, true );
	setFieldReadOnly( ifds::SecRecFileIndicator,		idDataGroup, true );
	setFieldReadOnly( ifds::RbkMCHFileIndicator,		idDataGroup, true );
	setFieldReadOnly( ifds::RbkSecRecFileIndicator,	idDataGroup, true );

	return GETCURRENTHIGHESTSEVERITY();

}

//******************************************************************************
SEVERITY BulkCancel::setSuppressIndicatorsReadOnlyFlags(const BFDataGroupId &idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                            CLASSNAME, 
                            I_( "setSuppressIndicatorsReadOnlyFlags" ) );	
	
    bool bReversalReadOnly   = false;
	bool bBulkRebookReadOnly = false;

	bool bVerification = getWorkSession().hasReadPermission( UAF::VERIFY_CANCEL_INSTRUCTION ); 
	DString dstrModPerm;
	getField( ifds::ModPermission, dstrModPerm, idDataGroup, false );
	dstrModPerm.stripAll();

	if ((!areSuppressIndicatorsModifiableBasedOnStatus(idDataGroup)) || 
			(!getWorkSession ().hasUpdatePermission(UAF::MCH_AND_SECUR_REC_FILE_INDICATOR)) ||
			(dstrModPerm == I_("1") && !isIndividualTransCancelAllowed()) ||
			(dstrModPerm == I_("2") && !bVerification))
	{		
		bReversalReadOnly   = true;
		bBulkRebookReadOnly = true;
	}
	else
	{					
		DString dstrRebook;        
		getField (ifds::Rebook, dstrRebook, idDataGroup, false);
		dstrRebook.stripAll().upperCase();

		if ( dstrRebook == YES )
		{
			DString dstrTransStat;
			getField( ifds::TranStatus, dstrTransStat, idDataGroup );
			if ( CANCEL_UNVERIFIED == dstrTransStat )
			{
				 DString dstrCurrentUserName, dstrUserName;
				 getField( ifds::Username, dstrUserName, idDataGroup ); 
 				 
				 dstrCurrentUserName = dynamic_cast<const DSTCSecurity *>( getWorkSession ().getSecurity(DSTCHost::getPrimaryHost()))->getUserId();        
         
				 if ( !dstrUserName.empty() &&
						( dstrCurrentUserName.stripAll().upperCase() != dstrUserName.stripAll().upperCase() ) )
				 {
					bBulkRebookReadOnly = !( getWorkSession ().hasUpdatePermission( UAF::VERIFY_CANCEL_INSTRUCTION ) && dstrModPerm == I_( "2" ) );
				 }
			}			
		}
		else
			bBulkRebookReadOnly = true;
	}

	setFieldReadOnly( ifds::MCHFileIndicator,	    idDataGroup, bReversalReadOnly );
	setFieldReadOnly( ifds::SecRecFileIndicator,	idDataGroup, bReversalReadOnly );
	setFieldReadOnly( ifds::RbkMCHFileIndicator,	idDataGroup, bBulkRebookReadOnly );
	setFieldReadOnly( ifds::RbkSecRecFileIndicator,	idDataGroup, bBulkRebookReadOnly );

	return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
void BulkCancel::setSuppressIndicatorsPerm(const BFDataGroupId &idDataGroup)
{
	if (getWorkSession ().hasUpdatePermission(UAF::MCH_AND_SECUR_REC_FILE_INDICATOR))
	{
		setFieldReadOnly( ifds::MCHFileIndicator,	idDataGroup, false );
		setFieldReadOnly( ifds::SecRecFileIndicator,	idDataGroup, false );
		setFieldReadOnly( ifds::RbkMCHFileIndicator,	idDataGroup, false );
		setFieldReadOnly( ifds::RbkSecRecFileIndicator,	idDataGroup, false );
	}
	else
	{
		setFieldReadOnly( ifds::MCHFileIndicator,	idDataGroup, true );
		setFieldReadOnly( ifds::SecRecFileIndicator,	idDataGroup, true );
		setFieldReadOnly( ifds::RbkMCHFileIndicator,	idDataGroup, true );
		setFieldReadOnly( ifds::RbkSecRecFileIndicator,	idDataGroup, true );
	}
}
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/BulkCancel.cpp-arc  $
// 
//    Rev 1.14   Jan 23 2006 12:28:38   porteanm
// PET1295_FN01: Trade Suppress Indicator for MCH and SR Files -- Rbk Indicators based on Rebook and User I or II permissions.
// 
//    Rev 1.13   Jan 18 2006 17:31:30   porteanm
// PET1295_FN01: Trade Suppress Indicator for MCH and SR Files -- Verify.
// 
//    Rev 1.12   Jan 18 2006 13:52:00   zhengcon
// PET1295_FN01: Trade Suppress Indicator for MCH and SR Files -- Verify (checked and unchecked)
// 
//    Rev 1.11   Jan 12 2006 16:09:40   zhengcon
// PET1295_FN01: Trade Suppress Indicator for MCH and SR Files -- Trade Cancellation: Individual and rebook
// 
//    Rev 1.10   Nov 27 2005 10:06:28   porteanm
// PET1286 FN01 - Bulk Cancellation - restore.
// 
//    Rev 1.9   Nov 26 2005 17:31:14   porteanm
// PET1286 FN01 - Bulk Cancellation.
// 
//    Rev 1.8   Nov 23 2005 17:11:26   porteanm
// PET1286 FN01 - Bulk Cancellation.
// 
//    Rev 1.7   Nov 18 2005 13:01:18   porteanm
// PET 1286 FN01 - Bulk Cancellation.
// 
//    Rev 1.6   Nov 12 2005 16:45:34   porteanm
// PET 1286 FN01 - Bulk Cancellation.
// 
//    Rev 1.5   Nov 12 2005 13:46:40   porteanm
// PET 1286 FN01 - Bulk Cancellation.
// 
//    Rev 1.4   Nov 12 2005 11:55:30   porteanm
// PET 1286 FN01 - Bulk Cancellation.
// 
//    Rev 1.3   Nov 11 2005 17:16:16   porteanm
// PET 1286 FN01 - Bulk Cancellation.
// 
//    Rev 1.2   Nov 09 2005 19:50:06   porteanm
// PET 1286 FN01 - Bulk Cancellation.
// 
//    Rev 1.1   Nov 06 2005 14:00:34   porteanm
// PET 1286 FN01 - Bulk Cancellation - work in progress.
// 
//    Rev 1.0   Nov 05 2005 15:07:30   porteanm
// Initial revision.
// 
*/